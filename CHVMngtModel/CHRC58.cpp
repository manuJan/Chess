/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHRC58.cpp
*   Description	: 
*
*	Author		: CH Team
*	Date created:  2-1-2006
* 	Project		:
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#include "stdafx.h"
#include "CHRC58.h"
#include "CHRLegends.h"

#include "..\CHMngtModel\CHEvent.h"
#include "..\CHMngtModel\CHMatch.h"
#include "..\CHMngtModel\CHMatchResult.h"
#include "..\CHMngtModel\CHInscription.h"
#include "..\CHMngtModel\CHRegister.h"
#include "..\CHMngtModel\CHPoolResult.h"
#include "..\CHMngtModel\CHPhaseBase.h"

static int orderEventsByOrder(const MSLItem** a, const MSLItem** b)
{
	CHEvent *pEvent1=(CHEvent *)(*a);
	CHEvent *pEvent2=(CHEvent *)(*b);

	int rc = pEvent1->getOrder() - pEvent2->getOrder();
	if( !rc )
		rc = strcmp(pEvent1->getKey(),pEvent2->getKey());
	return rc;
}
static
int orderMatchesBySessionAndMatchNumber(const MSLItem** a, const MSLItem** b)
{
	CHMatch * pA=((CHMatch *)(*a));
	CHMatch * pB=((CHMatch *)(*b));

	int order = pA->getSessionCode() - pB->getSessionCode();
	if(order)
		return order;

	return pA->getMatchNumber() - pB->getMatchNumber();
}

static int orderMatchesByDateTime(const MSLItem** a, const MSLItem** b)
{
	CHMatch * pMatchA=(CHMatch *)(*a);
	CHMatch * pMatchB=(CHMatch *)(*b);
	// Compare date

	if( pMatchA->getStartDateAsString("%Y%m%d")==NULLSTRING  &&
		pMatchB->getStartDateAsString("%Y%m%d")==NULLSTRING  )
		return strcmp(pMatchA->getKey(),pMatchB->getKey());

	if( pMatchA->getStartDateAsString("%Y%m%d")==NULLSTRING )
		return 1;
	if( pMatchB->getStartDateAsString("%Y%m%d")==NULLSTRING )
		return -1;

	int order=pMatchA->getStartDate().value()-pMatchB->getStartDate().value();
	if( order ) 
		return order;

	// Compare time
	if( pMatchA->getStartTimeAsString("%H:%M")==NULLSTRING &&
		pMatchB->getStartTimeAsString("%H:%M")==NULLSTRING )
		return strcmp(pMatchA->getKey(),pMatchB->getKey());

	if( pMatchA->getStartTimeAsString("%H:%M")==NULLSTRING )
		return 1;
	if( pMatchB->getStartTimeAsString("%H:%M")==NULLSTRING )
		return -1;

	order=strcmp(pMatchA->getStartTimeAsString("%H:%M"),
				 pMatchB->getStartTimeAsString("%H:%M") );

	if(order)
		return order;

	order = ((CHEvent*)pMatchA->getEvent())->getOrder() - ((CHEvent*)pMatchB->getEvent())->getOrder();
	if (order)
		return order;

	order = pMatchA->getCourtCode() - pMatchB->getCourtCode();
	if(order)
		return order;

	return strcmp(pMatchA->getKey(),pMatchB->getKey());
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHRC58::CHRC58(CReportManager& aReportManager,CReportConfig& aReportConfig,MSLDate aDate)
:CHReportTemplate(aReportManager,aReportConfig,aDate)
,m_pData(0)
,m_pLis(0)
,m_pSession(0)
,m_date(aDate)
,m_pLegends(0)
,m_paintSession(false)
,m_vMatches()
,m_posVector(0)
{
	m_pLegends = new CHRLegends(this,m_pReport,CH58);
}

CHRC58::~CHRC58()
{
	m_vMatches.clear();
	if (m_pLegends)
		delete m_pLegends;
}

unsigned short CHRC58::OnCallbackFn( struct USR_TAB * pTableInfo )
{
	switch(pTableInfo->Tb)
	{
	case 101:
		return tablaHeader(pTableInfo);
		break;
	case 102:
		return tablaMatch(pTableInfo);
		break;
	}
	return CReportBase::OnCallbackFn(pTableInfo);
}

unsigned short CHRC58::tablaHeader( struct USR_TAB * pTableInfo )
{
	UNREFERENCED_PARAMETER( pTableInfo );
    return PRNALL;
}

unsigned short CHRC58::tablaMatch( struct USR_TAB * pTableInfo )
{
	UNREFERENCED_PARAMETER( pTableInfo );
    return PRNALL;
}

CReportBase::ReportReturn CHRC58::OnBody()
{
	bool first=true;
	// ------------------------------------------------------
	// Bucle de pintado por cada pagina.
	// ------------------------------------------------------
	
	paintDateEvent();

	for (short i=m_posVector;i<m_vMatches.entries();i++)
	{
		CHMatch *pMatchSel =(CHMatch *)m_vMatches[i];
		GSession *pSessionAux = (GSession *)pMatchSel->getSession();

		if (m_pSession && pSessionAux &&
			m_pSession->getSession() != pSessionAux->getSession())
		{
			m_pSession = 0;
			return ok;
		}

		if (!m_pSession || m_pSession->getSession() != pSessionAux->getSession())
		{
			m_pSession = pSessionAux;
			m_paintSession = true;
			// Pintamos el letrero de la sesión
			if( m_pSession )
			{
				MSLString sessionDetailed=getSessionDetailed();
				m_pLis->setData(2000,sessionDetailed);
				if ( !m_pLis->runline( 1020 ) )
					return OnError(error,1020);
			}
		}	

		if( first || m_paintSession )
		{
			paintHeader();
			first = false;
			m_paintSession = false;
		}
		
		m_posVector++;

		setDataMatch(pMatchSel);
		paintMatch();

		if ( IsPageBreak(short(m_pLis->getVari(900))) && i<m_vMatches.entries()-1)
		{
			return ok;
		}
	}
				
	paintLegend();

	return exit;
}

void CHRC58::OnBeginReport()
{
	MSLString sLisName = "CH.C58.lis";
	CReportManager& aReportMng  = m_pReport->getManager();
	// Instanciamos una referencia al lis del report Ctry Event.
	CLis& aLis=m_pReport->setLis(sLisName);
	m_pLis=&aLis;
	if( m_pLis->isValid() )
	{	// Activamos control de margenes para pintar nuestro body
		aReportMng.setCtrlmargin( true );
		
		centerReport();
		m_pReport->setCursor(0,0);
		m_bOkLis=true;
		m_bHeaderAsOf=true;
		// Inicializamos funciones de tablas
		m_pLis->setCallBack( 101, this );
		m_pLis->setCallBack( 102, this );
		
		initLabels();
		// SetVaris Font
		setVaris(m_pLis);

		buildVector();
		m_pLis->setData(1020,CReportTemplate::m_pHeaderLis->getData(300));

		
		m_pLegends->loadLis();
		//setDynamicLegends();
	}
	else
	{	// Si hubo error en el report mostramos el error.
		if ( aReportMng.getError(NOLIS)==aReportMng.getLastError())
			MessageBox(0,MSLWString(aReportMng.getLastError()+"\n"+sLisName),L"",MB_OK);
		else
			MessageBox(0,MSLWString(aReportMng.getLastError()),L"",MB_OK);
	}
}

void CHRC58::initLabels()
{
	m_pLis->setData(1000, getUserLabel(110));// "Session",	
	m_pLis->setData(1001, getUserLabel(111));// "matches",	
	m_pLis->setData(1002, getUserLabel(112));// "match",		
	m_pLis->setData(1003, getUserLabel(113));// "Legend:",	
	m_pLis->setData(1006, getUserLabel(114));// "BYE" ,		
	m_pLis->setData(1007, getUserLabel(115));// "Total",		
	m_pLis->setData(1010, getUserLabel(116));// "Starting",	
	m_pLis->setData(1011, getUserLabel(117));// "Time",		
	m_pLis->setData(1012, getUserLabel(118));// "Round",		
	m_pLis->setData(1013, getUserLabel(119));// "Match",		
	m_pLis->setData(1014, getUserLabel(120));// "Num.",		
	m_pLis->setData(1015, getUserLabel(121));// "Event",		
	m_pLis->setData(1016, getUserLabel(122));// "Name",		
	m_pLis->setData(1017, getUserLabel(123));// "Phase",		
	m_pLis->setData(1018, getUserLabel(124));// "Table",		
	m_pLis->setData(1019, getUserLabel(125));// "Match",		
	m_pLis->setData(1021, getUserLabel(126));// "Code",		
	m_pLis->setData(1022, getUserLabel(127));// "Official",		
	m_pLis->setData(1024, getUserLabel(128));// "vs"
}

void CHRC58::centerReport()
{
	// Title coor x
	
	int width = m_pLis->getVari(1001)+	// NOC
				m_pLis->getVari(1002)+	// Country
				m_pLis->getVari(1003)+	// Name	
				m_pLis->getVari(1004)+
				m_pLis->getVari(1005)+
				m_pLis->getVari(1006)+
				m_pLis->getVari(1007)+
				m_pLis->getVari(1008)+
				m_pLis->getVari(1009)+
				m_pLis->getVari(1010);	// Date of Birth

	int corx  = getCenter()-(width/2);

	m_pLis->setVari(1000,corx);
}

CReportBase::ReportReturn CHRC58::paintHeader()
{	// Pintamos la cabecera de la tabla
	if ( !m_pLis->runline( 1000 ) )
		return OnError(error,1000);

	return exit;
}

CReportBase::ReportReturn CHRC58::paintMatch()
{	// Pintamos los datos
	if ( !m_pLis->runline( 1010 ) )
		return OnError(error,1010);
	
	return exit;
}

void CHRC58::setDataMatch(CHMatch* pMatch)
{
	MSLString aux = NULLSTRING;
	MSLWString auxW = NULLWSTRING;
	CHMatchResult *pMatchResult = 0;	
	MSLWString competitor=NULLWSTRING;

	m_pLis->setData( 2010,aux);	m_pLis->setData( 2011,aux);	m_pLis->setData( 2012,aux);
	m_pLis->setData( 2013,aux);	m_pLis->setData( 2014,aux);	m_pLis->setData( 2015,aux);
	m_pLis->setData( 2016,aux);	m_pLis->setData( 2017,aux);	m_pLis->setData( 2018,aux);
	m_pLis->setData( 2019,aux);	m_pLis->setData( 2020,aux);	m_pLis->setData( 2021,aux);
	m_pLis->setData( 2022,aux);	m_pLis->setData( 2023,aux);	m_pLis->setData( 2024,aux);
	m_pLis->setData( 2025,aux);	m_pLis->setData( 2026,aux);	m_pLis->setData( 2027,aux);
	// Starting Time
	MSLString time = NULLSTRING;
	time = (pMatch->getStartTimeAsString("%H:%M")).strip(MSLString::leading,'0');
	m_pLis->setData( 2010, time);
	//Round
	if ( pMatch->getRound() )
		m_pLis->setData(2011, pMatch->getRound());
	// Mesa
	if( pMatch->getCourt() )
		m_pLis->setData( 2027, pMatch->getCourt()->getCourt());
	// Match Number
	char sMN[35] = {0};
	//sprintf(sMN,"%s%d",pMatch->getEvent()->getSDescription().toAscii(),pMatch->getMatchNumber());
	if( pMatch->areTeamIndividual() )
	{
		CHMatch *pParentMatch=(CHMatch *) pMatch->getParent();
		sprintf_s(sMN,"%d-%d",pParentMatch->getMatchNumber(),pMatch->getSubMatch());
	}
	else sprintf_s(sMN,"%d",pMatch->getMatchNumber());
	m_pLis->setData( 2012, sMN);
	// Event - Hay que escribir el Evento en dos líneas. 
	// Cojo la descripción larga y la separo en dos lineas a partir del espacio entre las dos palabras
	MSLString eventDesc=pMatch->getEventLDescription().toAscii();

	m_pLis->setData( 2013, pMatch->getEventCodeReports() );
	
	// Phase or Round(as called for this report)
	m_pLis->setData( 2014, pMatch->getPhaseSDescription());

	//aLegend.addlegend(pMatch->getPhaseSDescription().toAscii(), "-", pMatch->getPhaseLDescription().toAscii());

	MSLSortedVector vCompetitors;
	pMatch->getMatchResultsVector(vCompetitors);

	if( vCompetitors.entries() )
	{
		pMatchResult = (CHMatchResult*)pMatch->getWhite();
		aux = NULLSTRING;
		if( pMatchResult->getBye() )
		{
			m_pLis->setData( 2017, m_pLis->getData(1006));
		}
		else
		{
			CHInscription *pInscription = (CHInscription *)pMatchResult->getInscription();
			if( pInscription )
			{
				if( pInscription->getSeed())
					m_pLis->setVari(1300, m_pLis->getVari(1200));
				else
					m_pLis->setVari(1300, m_pLis->getVari(1100));

				//pLis->setData( 2015, pInscription->getRankInscriptionAsString());
				
				CHRegister *pRegister = (CHRegister *)pInscription->getRegister();
				if( pRegister )
				{
					if( ((CHEvent*)pInscription->getEvent())->getRegType()!=GRegister::team )
					{
						if( pInscription->getSeed())
							competitor = pRegister->getPrnLName() + L" (" + TOWSTRING(pInscription->getSeed()) + L")";
						else
							competitor = pRegister->getPrnLName();
					}
					else
					{
						
						if( pInscription->getSeed() )
							competitor = pMatchResult->getMatchMemberLDescription() + L" (" + TOWSTRING(pInscription->getSeed()) + L")";
						else
							competitor = pMatchResult->getMatchMemberLDescription();
					}
					m_pLis->setData( 2017,competitor);
					
					//aux=pInscription->getRegister()->getGroup();
					//pLis->setData( 2019,aux);
					m_pLis->setData( 2019, pRegister->getGroup());
				}
			}
			else
			{
				m_pLis->setVari(1300, m_pLis->getVari(1100));
				CHPoolResult *pPoolResult = (CHPoolResult *)pMatchResult->getPoolResult();
				auxW = NULLWSTRING;
				if( pPoolResult )
					auxW = pPoolResult->getIDCompetitor();
				m_pLis->setData( 2017, auxW);
			}
		}
	}
	
	if( vCompetitors.entries() >= 2 )
	{
		pMatchResult = (CHMatchResult*)pMatch->getBlack();
		aux = NULLSTRING;
		if( pMatchResult->getBye() )
		{
			m_pLis->setData( 2018, m_pLis->getData(1006));
		}
		else
		{
			CHInscription *pInscription = (CHInscription *)pMatchResult->getInscription();
			if( pInscription )
			{
				if (pInscription->getSeed())
					m_pLis->setVari(1301,m_pLis->getVari(1200));
				else
					m_pLis->setVari(1301,m_pLis->getVari(1100));

				//pLis->setData( 2016,pInscription->getRankInscriptionAsString());
				if ( pInscription->getRegister() )
				{
					if(((CHEvent*)pInscription->getEvent())->getRegType()!=GRegister::team)
					{
						if (pInscription->getSeed())
							competitor = pInscription->getPrnLName() + L" (" + TOWSTRING(pInscription->getSeed()) + L")";
						else 
							competitor = pInscription->getPrnLName();
					}
					else
					{
						if( pInscription->getSeed() )
							competitor = pMatchResult->getMatchMemberLDescription() + L" (" + TOWSTRING(pInscription->getSeed()) + L")";
						else
							competitor = pMatchResult->getMatchMemberLDescription();
					}

					m_pLis->setData( 2018,competitor);
					aux=pInscription->getRegister()->getGroup();
					m_pLis->setData( 2020,aux);
				}
			}
			else
			{
				m_pLis->setVari(1301,m_pLis->getVari(1100));
				CHPoolResult* pPoolResult=(CHPoolResult*)pMatchResult->getPoolResult();
				auxW=NULLWSTRING;
				if (pPoolResult)
					auxW=pPoolResult->getIDCompetitor();
				m_pLis->setData( 2018, auxW);
			}
		}
	}

	MSLSortedVector vMatchJudges;
	pMatch->getMatchJudgesVector(vMatchJudges);	
	for (short i=0;i<vMatchJudges.entries();i++)
	{
		/*GTHMatchJudge* pMatchJudge=(GTHMatchJudge*)vMatchJudges[i];
		if ( pMatchJudge->getPosition() && 
		   ( pMatchJudge->getPositionCode()==CHRegister::eUmpire1 ||
			 pMatchJudge->getPositionCode()==CHRegister::eUmpire2) &&
			 pMatchJudge->getRegister())
		{
			short posicion=short(pMatchJudge->getPosition()->getPosition()-1);
			m_pLis->setData(short(2021+posicion),pMatchJudge->getRegister()->getPrnLName());
			m_pLis->setData(short(2024+posicion),pMatchJudge->getRegister()->getGroup());
		}*/
	}
}

MSLWString CHRC58::getSessionDetailed()
{
	MSLWString aux = NULLWSTRING;
	int counterTotal = 0;
	if( m_pSession )
	{
		aux = m_pLis->getData(1000);
		aux += " ";
		aux += TOWSTRING(m_pSession->getSession());
		aux += ": ";
		
		bool first = true;
		MSLSortedVector vEvents(CHMemoryDataBase::getCol(__CHEVENT),orderEventsByOrder);
		MSLSortedVector aVector = getMatchesSession(m_pSession);
		if(aVector.entries())
		{
			CHEvent *pEvent = 0;
			for( short i=0; i<vEvents.entries(); i++ )
			{
				pEvent = (CHEvent *)vEvents[i];
				
				int counter = 0;
				for( short j=0; j<aVector.entries(); j++ )
				{
					CHMatch *pMatch = (CHMatch *)aVector[j];
					if( pMatch->getEvent()==pEvent )
					{
						//aLegend.addlegend(pEvent->getSDescription().toAscii(), "-", pEvent->getLDescription().toAscii());
						counter++;
					}
				}
				
				if( counter )
				{
					counterTotal += counter;
					if( !first )
						aux += ", ";
					else
						first = false;

					aux += pEvent->getSDescription();
					aux += " ";
					aux += TOWSTRING(counter);
					aux += " ";
					if( counter>1 )
						aux += m_pLis->getData(1001);
					else
						aux += m_pLis->getData(1002);
				}
			}
		}
	}

	if( counterTotal )
	{
		aux += ", ";
		aux += m_pLis->getData(1007);
		aux += " ";
		aux += TOWSTRING(counterTotal);
		aux += " ";		
		if( counterTotal>1 )
			aux += m_pLis->getData(1001);
		else
			aux += m_pLis->getData(1002);
	}

	return aux;
}

CReportBase::ReportReturn CHRC58::paintDateEvent()
{
	if(m_date==INVALID_DATE)
		return exit;

	MSLString sInformation = m_date.asString("%a %d %b %Y");
	sInformation.toUpper();
	m_pLis->setData(208,sInformation);
	return exit;
}

void CHRC58::buildVector()
{
	MSLSetIterator iter(CHMemoryDataBase::getCol(__CHMATCH));
	CHMatch *pMatch = 0;
	while((pMatch = (CHMatch *)iter()) != 0)
	{
		/*if (pMatch->areTeamIndividual())
			continue;*/
		if (pMatch->areTeams())
			continue;
		if(pMatch->getSession() && 
			(pMatch->getStartDate()==m_date) && pMatch->getCourt())
			m_vMatches.insert(pMatch);
	}
	if(m_pLis->getVari(901))
		m_vMatches.setFcCompare(orderMatchesBySessionAndMatchNumber);
	else 
		m_vMatches.setFcCompare(orderMatchesByDateTime);

	m_vMatches.sort();
}

MSLSortedVector CHRC58::getMatchesSession(GSession *pSession)
{
	MSLSetIterator iter(CHMemoryDataBase::getCol(__CHMATCH));
	CHMatch *pMatch = 0;
	MSLSortedVector vMatchs;

	while((pMatch = (CHMatch *)iter()) != 0)
	{
		/*if (pMatch->areTeamIndividual())
			continue;*/
		if (pMatch->areTeams())
			continue;

		if(pMatch->getSession() && 
			(pSession->getKey() == pMatch->getSession()->getKey()))
			vMatchs.insert(pMatch);
	}
	return vMatchs;
}

MSLDate CHRC58::OnGetEventDate() const
{
	return INVALID_DATE;
}

MSLTime CHRC58::OnGetEventTime() const
{
	return INVALID_TIME;
}
CReportBase::ReportReturn CHRC58::paintLegend()
{
	m_pLegends->runLis(); // Pintamos las leyendas.
	return exit;
					 	
}

void CHRC58::setDynamicLegends()
{
	CHEvent *pEvent = 0;
	MSLSetIterator iter(CHMemoryDataBase::getCol(__CHEVENT));
	while ((pEvent=(CHEvent*)iter())!=0)
	{
		m_pLegends->setDynamic( pEvent->getSDescription());							
	}

	CHPhaseBase *pPhaseBase = 0;
	MSLSetIterator iter2(CHMemoryDataBase::getCol(__CHPHASEBASE));
	while ((pPhaseBase=(CHPhaseBase*)iter2())!=0)
	{
		m_pLegends->setDynamic( pPhaseBase->getSDescription());							
	}

	//m_pLegends->createDynamic();
}
