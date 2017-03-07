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
#include "stdVCH.h"
#include "CHRC58.h"
#include <Sports/CH/Data/CHDiscipline.h>
#include <Sports/CH/Data/CHRegister.h>
#include <Sports/CH/Data/CHInscription.h>
#include <Sports/CH/Data/CHMember.h>
#include <Sports/CH/Data/CHJudge.h>
#include <Sports/CH/Data/CHEvent.h>
#include <Sports/CH/Data/CHMatch.h>
#include <Sports/CH/Data/CHMatchResult.h>
#include <Sports/CH/Data/CHMatchJudge.h>
#include <Sports/CH/Data/CHSession.h>
#include <Sports/CH/Data/CHPoolResult.h>

static int orderEventsByOrder(const GVectorElement** a, const GVectorElement** b)
{
	CHEvent *pEvent1=(CHEvent *)(*a)->getElement();
	CHEvent *pEvent2=(CHEvent *)(*b)->getElement();

	int rc = pEvent1->getOrderEvent() - pEvent2->getOrderEvent();
	if( !rc )
		rc = strcmp(pEvent1->getKey(),pEvent2->getKey());
	return rc;
}
static
int orderMatchesBySessionAndMatchNumber(const GVectorElement** a, const GVectorElement** b)
{
	CHMatch * pA=((CHMatch *)(*a)->getElement());
	CHMatch * pB=((CHMatch *)(*b)->getElement());

	int order = pA->getSessionCode() - pB->getSessionCode();
	if(order)
		return order;

	return pA->getMatchNumber() - pB->getMatchNumber();
}
static int orderMatchesByDateTime(const GVectorElement** a, const GVectorElement** b)
{
	CHMatch * pMatchA=(CHMatch *)(*a)->getElement();
	CHMatch * pMatchB=(CHMatch *)(*b)->getElement();
	// Compare date

	if( pMatchA->getStartDateAsString("%Y%m%d")==NULLRWSTRING  &&
		pMatchB->getStartDateAsString("%Y%m%d")==NULLRWSTRING  )
		return strcmp(pMatchA->getKey(),pMatchB->getKey());

	if( pMatchA->getStartDateAsString("%Y%m%d")==NULLRWSTRING )
		return 1;
	if( pMatchB->getStartDateAsString("%Y%m%d")==NULLRWSTRING )
		return -1;

	int order=strcmp(pMatchA->getStartDateAsString("%Y%m%d"),
					 pMatchB->getStartDateAsString("%Y%m%d"));
	if( order ) 
		return order;
	// Compare time
	if( pMatchA->getStartTimeAsString("%H:%M")==NULLRWSTRING &&
		pMatchB->getStartTimeAsString("%H:%M")==NULLRWSTRING )
		return strcmp(pMatchA->getKey(),pMatchB->getKey());

	if( pMatchA->getStartTimeAsString("%H:%M")==NULLRWSTRING )
		return 1;
	if( pMatchB->getStartTimeAsString("%H:%M")==NULLRWSTRING )
		return -1;

	order=strcmp(pMatchA->getStartTimeAsString("%H:%M"),
				 pMatchB->getStartTimeAsString("%H:%M") );

	if(order)
		return order;


	order = ((CHEvent*)pMatchA->getEvent())->getOrderEvent() - ((CHEvent*)pMatchB->getEvent())->getOrderEvent();
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
CHRC58::CHRC58(CReportManager& aReportManager,CReportConfig& aReportConfig,RWDate aDate)
:CHReportTemplate(aReportManager,aReportConfig,aDate)
,pData(0)
,pLis(0)
,pSession(0)
,date(aDate)
,pLegends(0)
,paintSession(false)
,vMatches()
,posVector(0)
{
	pLegends = new CHRLegends(this,pReport,CHRLegends::eC58);
}

CHRC58::~CHRC58()
{
	vMatches.clearAndDestroy();
	if (pLegends)
		delete pLegends;
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
	RWBoolean first=true;
	// ------------------------------------------------------
	// Bucle de pintado por cada pagina.
	// ------------------------------------------------------
	
	paintDateEvent();

	for (size_t i=posVector;i<vMatches.entries();i++)
	{
		CHMatch *pMatchSel =(CHMatch *)vMatches[i]->getElement();
		CHSession *pSessionAux = (CHSession *)pMatchSel->getSession();

		if (pSession && pSessionAux &&
			pSession->getSession() != pSessionAux->getSession())
		{
			pSession = 0;
			return ok;
		}

		if (!pSession || pSession->getSession() != pSessionAux->getSession())
		{
			pSession = pSessionAux;
			paintSession = true;
			// Pintamos el letrero de la sesión
			if( pSession )
			{
				RWCString sessionDetailed=getSessionDetailed();
				pLis->setData(2000,sessionDetailed);
				if ( !pLis->runline( 1020 ) )
					return OnError(error,1020);
			}
		}	

		if( first || paintSession )
		{
			paintHeader();
			first = false;
			paintSession = false;
		}
		
		posVector++;

		setDataMatch(pMatchSel);
		paintMatch();

		if ( IsPageBreak(short(pLis->getVari(900))) && i<vMatches.entries()-1)
		{
			return ok;
		}
	}
				
	paintLegend();

	return exit;
}

void CHRC58::OnBeginReport()
{
	RWCString sLang = DBApplication::getAppLanguage();
	RWCString sDisc = CHMemoryDataBase::getDiscipline().getCode();
	RWCString sLisName = sDisc + ".C58." + sLang + ".lis";
	CReportManager& aReportMng  = pReport->getManager();
	// Instanciamos una referencia al lis del report Ctry Event.
	CLis& aLis=pReport->setLis(sLisName);
	pLis=&aLis;
	if( pLis->isValid() )
	{	// Activamos control de margenes para pintar nuestro body
		aReportMng.setCtrlmargin( true );
		pLis->setVari(1000,getCenter());
		pReport->setCursor(0,0);
		bOkLis=true;
		// Inicializamos funciones de tablas
		pLis->setCallBack( 101, this );
		pLis->setCallBack( 102, this );
		// SetVaris Font
		setVaris(pLis);

		buildVector();
		pLis->setData(1020,CReportTemplate::pLis->getData(300));

		
		pLegends->loadLis();
		setDynamicLegends();
	}
	else
	{	// Si hubo error en el report mostramos el error.
		if ( aReportMng.getError(NOLIS)==aReportMng.getLastError())
			AfxMessageBox(RWWString(aReportMng.getLastError()+"\n"+sLisName,RWWString::ascii));
		else
			AfxMessageBox(RWWString(aReportMng.getLastError(),RWWString::ascii));
	}
}

CReportBase::ReportReturn CHRC58::paintHeader()
{	// Pintamos la cabecera de la tabla
	if ( !pLis->runline( 1000 ) )
		return OnError(error,1000);

	return exit;
}

CReportBase::ReportReturn CHRC58::paintMatch()
{	// Pintamos los datos
	if ( !pLis->runline( 1010 ) )
		return OnError(error,1010);
	
	return exit;
}

void CHRC58::setDataMatch(CHMatch* pMatch)
{
	RWCString aux = NULLRWSTRING;
	RWWString auxW = NULLRWWSTRING;
	CHMatchResult *pMatchResult = 0;
	CHMatchJudge *pMatchJudge = 0;
	char competitor[35] = {0};
	pLis->setData( 2010,aux);	pLis->setData( 2011,aux);	pLis->setData( 2012,aux);
	pLis->setData( 2013,aux);	pLis->setData( 2014,aux);	pLis->setData( 2015,aux);
	pLis->setData( 2016,aux);	pLis->setData( 2017,aux);	pLis->setData( 2018,aux);
	pLis->setData( 2019,aux);	pLis->setData( 2020,aux);	pLis->setData( 2021,aux);
	pLis->setData( 2022,aux);	pLis->setData( 2023,aux);	pLis->setData( 2024,aux);
	pLis->setData( 2025,aux);	pLis->setData( 2026,aux);	pLis->setData( 2027,aux);
	// Starting Time
	RWCString time = NULLRWSTRING;
	time = (pMatch->getStartTimeAsString("%H:%M")).strip(RWCString::leading,'0');
	pLis->setData( 2010, time);
	//Round
	if ( pMatch->getRound() )
		pLis->setData(2011, pMatch->getRound());
	// Mesa
	if( pMatch->getCourt() )
		pLis->setData( 2027, pMatch->getCourt()->getCourt());
	// Match Number
	char sMN[35] = {0};
	//sprintf(sMN,"%s%d",pMatch->getEvent()->getSDescription().toAscii(),pMatch->getMatchNumber());
	if( pMatch->areTeamIndividual() )
	{
		CHMatch *pParentMatch=pMatch->getParentMatch();

		sprintf(sMN,"%d-%d",pParentMatch->getMatchNumber(),pMatch->getSubMatch());
	}
	else sprintf(sMN,"%d",pMatch->getMatchNumber());
	pLis->setData( 2012, sMN);
	// Event - Hay que escribir el Evento en dos líneas. 
	// Cojo la descripción larga y la separo en dos lineas a partir del espacio entre las dos palabras
	RWCString eventDesc=pMatch->getEventLDescription().toAscii();

	int po   = eventDesc.first(' ');
	// Cojo la primera parte del evento "Men´s"
	RWCString sSex(eventDesc,po);
	// Cojo la segunda parte del evento "Singles"
	RWCString sEvent=eventDesc;
	sEvent=sEvent.remove(0, po+1);
		
	pLis->setData( 2013, sSex );
	pLis->setData( 3013, sEvent);
	// Phase or Round(as called for this report)
	pLis->setData( 2014, pMatch->getPhase()->getSDescription());

	//aLegend.addlegend(pMatch->getPhaseSDescription().toAscii(), "-", pMatch->getPhaseLDescription().toAscii());

	if( pMatch->getCompetitorsVector().entries() )
	{
		pMatchResult = (CHMatchResult*)pMatch->getWhite();
		aux = NULLRWSTRING;
		if( pMatchResult->getBye() )
		{
			pLis->setData( 2017, pLis->getData(1006));
		}
		else
		{
			CHInscription *pInscription = (CHInscription *)pMatchResult->getInscription();
			if( pInscription )
			{
				if( pInscription->getSeed())
					pLis->setVari(1300, pLis->getVari(1200));
				else
					pLis->setVari(1300, pLis->getVari(1100));

				//pLis->setData( 2015, pInscription->getRankInscriptionAsString());
				
				CHRegister *pRegister = (CHRegister *)pInscription->getRegister();
				if( pRegister )
				{
					if( ((CHEvent*)pInscription->getEvent())->getMode()!=CHEvent::eTeam )
					{
						if( pInscription->getSeed())
							sprintf(competitor, "%s (%d)", pRegister->getPrnLName().toAscii(), pInscription->getSeed());
						else
							sprintf(competitor, "%s", pRegister->getPrnLName().toAscii());
					}
					else
					{
						
						if( pInscription->getSeed() )
							sprintf(competitor, "%s (%d)", pMatchResult->getMatchMemberLDescription().toAscii(), pInscription->getSeed());
						else
							sprintf(competitor, "%s", pMatchResult->getMatchMemberLDescription().toAscii());
					}
					pLis->setData( 2017,competitor);
					
					//aux=pInscription->getRegister()->getGroup();
					//pLis->setData( 2019,aux);
					pLis->setData( 2019, pRegister->getGroup());
				}
			}
			else
			{
				pLis->setVari(1300, pLis->getVari(1100));
				CHPoolResult *pPoolResult = (CHPoolResult *)pMatchResult->getPoolResult();
				auxW = NULLRWWSTRING;
				if( pPoolResult )
					auxW = pPoolResult->getIDCompetitor();
				pLis->setData( 2017, auxW);
			}
		}
	}
	
	if( pMatch->getCompetitorsVector().entries()>=2 )
	{
		pMatchResult = (CHMatchResult*)pMatch->getBlack();
		aux = NULLRWSTRING;
		if( pMatchResult->getBye() )
		{
			pLis->setData( 2018, pLis->getData(1006));
		}
		else
		{
			CHInscription *pInscription = (CHInscription *)pMatchResult->getInscription();
			if( pInscription )
			{
				if (pInscription->getSeed())
					pLis->setVari(1301,pLis->getVari(1200));
				else
					pLis->setVari(1301,pLis->getVari(1100));

				//pLis->setData( 2016,pInscription->getRankInscriptionAsString());
				if ( pInscription->getRegister() )
				{
					if(((CHEvent*)pInscription->getEvent())->getMode()!=CHEvent::eTeam)
					{
						if (pInscription->getSeed())
							 sprintf(competitor,"%s (%d)",pInscription->getRegister()->getPrnLName().toAscii(),pInscription->getSeed());
						else sprintf(competitor,"%s",pInscription->getRegister()->getPrnLName().toAscii());
					}
					else
					{
						if( pInscription->getSeed() )
							sprintf(competitor, "%s (%d)", pMatchResult->getMatchMemberLDescription().toAscii(), pInscription->getSeed());
						else
							sprintf(competitor, "%s", pMatchResult->getMatchMemberLDescription().toAscii());
					}

					pLis->setData( 2018,competitor);
					aux=pInscription->getRegister()->getGroup();
					pLis->setData( 2020,aux);
				}
			}
			else
			{
				pLis->setVari(1301,pLis->getVari(1100));
				CHPoolResult* pPoolResult=(CHPoolResult*)pMatchResult->getPoolResult();
				auxW=NULLRWWSTRING;
				if (pPoolResult)
					auxW=pPoolResult->getIDCompetitor();
				pLis->setData( 2018, auxW);
			}
		}
	}
	
	for (size_t i=0;i<pMatch->getJudgesVector().entries();i++)
	{
		pMatchJudge=(CHMatchJudge*)pMatch->getJudgesVector()[i]->getElement();
		if ( pMatchJudge->getPosition() && 
		   ( pMatchJudge->getPosition()->getPosition()==CHMatchJudge::eUmpire1 ||
			 pMatchJudge->getPosition()->getPosition()==CHMatchJudge::eUmpire2) &&
			 pMatchJudge->getRegister())
		{
			short posicion=short(pMatchJudge->getPosition()->getPosition()-1);
			pLis->setData(short(2021+posicion),pMatchJudge->getRegister()->getPrnLName());
			pLis->setData(short(2024+posicion),pMatchJudge->getRegister()->getGroup());
		}
	}
}

RWCString CHRC58::getSessionDetailed()
{
	RWCString aux = NULLRWSTRING;
	int counterTotal = 0;
	if( pSession )
	{
		char tmp[10] = {0};
		aux = pLis->getData(1000);
		aux += " ";
		aux += itoa(pSession->getSession(),tmp,10);
		aux += ": ";
		
		RWBoolean first = true;
		GSortedVector vEvents(CHMemoryDataBase::getColEvents(),orderEventsByOrder);
		GSortedVector aVector = getMatchesSession(pSession);
		if(aVector.entries())
		{
			CHEvent *pEvent = 0;
			for( size_t i=0; i<vEvents.entries(); i++ )
			{
				pEvent = (CHEvent *)vEvents[i]->getElement();
				
				int counter = 0;
				for( size_t j=0; j<aVector.entries(); j++ )
				{
					CHMatch *pMatch = (CHMatch *)aVector[j]->getElement();
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

					aux += pEvent->getSDescription().toAscii();
					aux += " ";
					aux += itoa(counter,tmp,10);
					aux += " ";
					if( counter>1 )
						aux += pLis->getData(1001);
					else
						aux += pLis->getData(1002);
				}
			}
		}
	}

	if( counterTotal )
	{
		char tmp[10]={0};
		aux += ", ";
		aux += pLis->getData(1007);
		aux += " ";
		aux += itoa(counterTotal,tmp,10);
		aux += " ";
		
		if( counterTotal>1 )
			aux += pLis->getData(1001);
		else
			aux += pLis->getData(1002);
	}

	return aux;
}

CReportBase::ReportReturn CHRC58::paintDateEvent()
{
	if(date==INVALID_RWDATE)
		return exit;
	RWCString sInformation = toUpper(date.asString("%a %d %b %Y"));
	pLis->setData(208,sInformation);
	if(!pLis->runline(105))
		return OnError(error,105);
	return exit;
}

void CHRC58::buildVector()
{
	RWSetIterator iter(CHMemoryDataBase::getColMatchs());
	CHMatch *pMatch = 0;
	while((pMatch = (CHMatch *)iter()) != 0)
	{
		/*if (pMatch->areTeamIndividual())
			continue;*/
		if (pMatch->areTeams())
			continue;
		if(pMatch->getSession() && 
			(pMatch->getStartDate()==date) && pMatch->getCourt())
			vMatches.insert(pMatch);
	}
	if(pLis->getVari(901))
		 vMatches.sort(orderMatchesBySessionAndMatchNumber);
	else vMatches.sort(orderMatchesByDateTime);
}

GSortedVector CHRC58::getMatchesSession(CHSession *pSession)
{
	RWSetIterator iter(CHMemoryDataBase::getColMatchs());
	CHMatch *pMatch = 0;
	GSortedVector vMatchs;

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

RWDate CHRC58::OnGetEventDate() const
{
	return INVALID_RWDATE;
}

RWTime CHRC58::OnGetEventTime() const
{
	return INVALID_RWTIME;
}
CReportBase::ReportReturn CHRC58::paintLegend()
{
	pLegends->runLis(); // Pintamos las leyendas.
	return exit;
					 	
}

void CHRC58::setDynamicLegends()
{
	CHEvent *pEvent = 0;
	RWSetIterator iter(CHMemoryDataBase::getColEvents());
	while ((pEvent=(CHEvent*)iter())!=0)
	{
		pLegends->setDynamic( pEvent->getSDescription());							
	}

	CHPhaseBase *pPhaseBase = 0;
	RWSetIterator iter2(CHMemoryDataBase::getColPhaseNames());
	while ((pPhaseBase=(CHPhaseBase*)iter2())!=0)
	{
		pLegends->setDynamic( pPhaseBase->getSDescription());							
	}

	pLegends->createDynamic();
}
