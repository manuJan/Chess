/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHRC74.cpp
*	Description	:
*
*	Author		:CH Team
*	Date created:20-01-2006
* 	Project		:CHVMngtModel
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdafx.h"
#include "CHRC74.h"
#include "CHRLegends.h"
#include "..\CHMngtModel\CHPhase.h"
#include "..\CHMngtModel\CHMatch.h"
#include "..\CHMngtModel\CHPoolResult.h"
#include "..\CHMngtModel\CHInscription.h"
#include "..\CHMngtModel\CHRegister.h"

////////////////////////////////////////////////////////////////////////////////////
static int orderMatches(const MSLItem** a, const MSLItem** b)
{
	CHMatch * pMatchA = (CHMatch *) (*a);
	CHMatch * pMatchB = (CHMatch *) (*b);
	
	// Order by m_round
	int order = pMatchA->getRound() - pMatchB->getRound();
	if( order )
		return order;

	// Order by Match Code
	order = pMatchA->getCode() - pMatchB->getCode();
	if( order )
		return order;
	
	// Order by key
	return strcmp(pMatchA->getKey(),pMatchB->getKey());
}
/////////////////////////////////////////////////////////////////////
CHRC74::CHRC74(CReportManager& aReportManager,CReportConfig& aReportConfig,CHPhase * pSelPhase,short roundSel)
:CHReportTemplate(aReportManager,aReportConfig,pSelPhase)
,m_pLis(0)
,m_pPhase(pSelPhase)
,m_index(0)
,m_pLegends(0)
,m_round(roundSel)
,m_firstPage(true)
{
	m_pLegends=new CHRLegends(this,m_pReport,CH74);	
}

/////////////////////////////////////////////////////////////////////
CHRC74::~CHRC74()
{
	if ( m_pLegends )
		delete m_pLegends;	
}

/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
MSLString CHRC74::getNameOfSourceLis(void)
{
	return "CH.C74.lis";	
}

/////////////////////////////////////////////////////////////////////
void CHRC74::OnBeginReport()
{
	CReportManager& aReportMng = m_pReport->getManager();

	// Instanciamos una referencia al lis del report
	CLis& aLis = m_pReport->setLis(getNameOfSourceLis());
	m_pLis = &aLis;
	if( m_pLis && m_pLis->isValid() )
	{
		// Iniciamos variables
		aReportMng.setCtrlmargin(true);
		m_pReport->setCursor(0,0);
		m_pLis->setVari(1,getCenter());
		m_pLis->setVari(2,aReportMng.getXMax()-getRightMargin());

		m_bOkLis = true;
		// SetVaris Font
		setVaris(m_pLis);
				
		initLabels();
		setGlobalVaris();
		
		// Iniciamos funcion para el relleno de la tabla
		m_pLis->setCallBack(1,this);
		m_pLis->setCallBack(2,this);
		m_pLis->setCallBack(3,this);

		//Leyendas
		m_pLegends->loadLis();
		setDynamicLegends();

		buildVector();

		if (m_pPhase->isTeamEvent())
			m_pLis->setData(1000, m_pLis->getData(1009));
		else
			m_pLis->setData(1000, m_pLis->getData(1008));
	}
	else
	{	// Si hubo error en el report mostramos el error.
		MessageBox(0,MSLWString(aReportMng.getLastError()+"\n"+getNameOfSourceLis()),L"",MB_OK);
	}
}

void CHRC74::initLabels()
{
	m_pLis->setData(1001,getUserLabel(140)); // "Seed"				
	m_pLis->setData(1002,getUserLabel(141)); // "Title"			
	m_pLis->setData(1003,getUserLabel(142)); // "Name"				
	m_pLis->setData(1004,getUserLabel(143)); // "Points"			
	m_pLis->setData(1005,getUserLabel(144)); // "Result"			
	m_pLis->setData(1007,getUserLabel(145)); // "Code"				
	m_pLis->setData(1008,getUserLabel(146)); // "Game"				
	m_pLis->setData(1009,getUserLabel(147)); // "Match"			
	m_pLis->setData(1500,getUserLabel(148)); // "Legend"			
	m_pLis->setData(1501,getUserLabel(149)); // "Bye"		
}

/////////////////////////////////////////////////////////////////////
CReportBase::ReportReturn CHRC74::OnBody()
{
		
	// Controlamos que haya datos para pintar
	if( !m_vMatches.entries() )
	{
		MessageBox(0,L"There are not matche/s",L"",MB_OK);
		return error;
	}
		
	
	// Template de Cabeceras
	if( paintTemplateHeader() == error )
		return error;
	
	// Template de Results
	return paintTemplateResults();
	

}

CReportBase::ReportReturn CHRC74::paintLegends()
{
	// Pintamos las leyendas
	if( !m_pLegends->runLis() )
		return OnError(error,10);
		
	return exit;
}

/////////////////////////////////////////////////////////////////////
CReportBase::ReportReturn CHRC74::paintTemplateHeader()
{
	CHMatch *pMatchAux = (CHMatch *)m_vMatches[m_index];
	
	if(pMatchAux)
	{
		m_pLis->setData(2100,pMatchAux->getRoundAsString(true,true));
		// Pintamos la ronda
		if( !m_pLis->runline(5) )
			return OnError(error,10);
	}

	// Pintamos la cabecera
	if( !m_pLis->runline(1) )
		return OnError(error,10);

	return exit;
}

/////////////////////////////////////////////////////////////////////
CReportBase::ReportReturn CHRC74::paintTemplateResults()
{
	CHMatch * pMatch = 0;
				
	while( m_index < m_vMatches.entries() )
	{
		pMatch = (CHMatch *)m_vMatches[m_index];
		
		if( !pMatch )
			return OnError(error,120);
				

		assignDataIndividual(pMatch);

		// Pintamos los datos 
		if( !m_pLis->runline(2) )
			return OnError(error,130);

		if(pMatch->isTeam())
			paintMembers(pMatch);
		
		m_index++;
		
		// Comprobamos si hay salto de pagina
		if(( IsPageBreak(short(m_pLis->getVari(800))) || changeRound(pMatch)) && m_index != m_vMatches.entries())
		{
			// Leyendas
			m_firstPage=false;
			return ok;
		}
		
	}
	
	// Leyendas
	if( paintLegends() == error )
		return error;
	
	return exit;
}
void CHRC74::setGlobalVaris()
{
	
	CHEvent *pEvent=(CHEvent*)m_pPhase->getEvent();

	// En equipos no se pinta el Master Type1 ni Master Type2, no lo hay.
	if(pEvent->isTeam())
	{
		m_pLis->setVari(102,0);
		m_pLis->setVari(109,0);
		m_pLis->setVari(203,560);
		m_pLis->setVari(210,560);
	}
	else
	{
		m_pLis->setVari(102,1);
		m_pLis->setVari(109,1);
		m_pLis->setVari(203,500);
		m_pLis->setVari(210,500);
	}

	
	
	// Corx centrada de la tabla
	int width=0;
	// Vari[21] son los posibles celdas a pintar
	for(int i=0;i<m_pLis->getVari(4);i++)
		width+=m_pLis->getVari(short(100+i))*m_pLis->getVari(short(200+i));
	
	long center=getCenter();
	long offsetx=center-(width/2);
	if (offsetx>25)
		m_pLis->setVari(3,offsetx-25);
	else
		m_pLis->setVari(3,10);

	// Codigo NOC, NPC, CGA, dependiente del .lis de cabeceras
	m_pLis->setData(1006,CReportTemplate::m_pHeaderLis->getData(300)); 
}

/////////////////////////////////////////////////////////////////////
MSLDate CHRC74::OnGetEventDate() const
{
	return INVALID_DATE;
}

MSLTime CHRC74::OnGetEventTime() const
{
	return INVALID_TIME;
}

MSLWString CHRC74::OnGetLine(const int lineNumber,const char *language) const
{
	return CReportTemplate::OnGetLine(lineNumber,language);
}

unsigned short CHRC74::OnCallbackFn( struct USR_TAB * pTableInfo )
{
	return CReportBase::OnCallbackFn(pTableInfo);
}

void CHRC74::assignDataIndividual(CHMatch *pMatch)
{		
	// Reseteo
	for(short i=0;i<short(m_pLis->getVari(4));i++)
	{
		m_pLis->setData(2000+i,"");
		// En negrita la parte del equipo y en normal los miembros
		if(pMatch->isTeam())
			 m_pLis->setDataFont(2000+i,m_pLis->getVari(507));
		else m_pLis->setDataFont(2000+i,m_pLis->getVari(506));
	}
	

	CHMatchResult *pHome=(CHMatchResult *) pMatch->getHome();
	CHMatchResult *pAway=(CHMatchResult *) pMatch->getAway();

	CHPoolResult *pPoolHome=(CHPoolResult*)pHome->getPoolResult();
	CHPoolResult *pPoolAway=(CHPoolResult*)pAway->getPoolResult();

	CHInscription *pInsHome=(CHInscription*)pHome->getInscription();
	CHInscription *pInsAway=(CHInscription*)pAway->getInscription();

	// Bout Number
	if(pMatch->isTeam())
		 m_pLis->setData(2000,pMatch->getRoundMatch());
	else m_pLis->setData(2000,pMatch->getParent()?pMatch->getParent()->getCode():0);
	
	// Seed Number 1
	if(pInsHome)
		m_pLis->setData(2001,pInsHome->getSeed());
	
	// Master Type 1
	if(pInsHome)
		m_pLis->setData(2002,pInsHome->getRegMasterTypeSDescription());
	

	// Name 1
	if(pInsHome)
		 m_pLis->setData(2003,pInsHome->getPrnLName());
	else m_pLis->setData(2003,m_pLis->getData(1501));

	// NOC Code 1
	if(pInsHome)
		m_pLis->setData(2004,pInsHome->getGroup());

	// Points 1
	if(pPoolHome)
	{
		//m_pLis->setData(2005,pHome->getPointsAsString());
		m_pLis->setData(2005,pPoolHome->getPoolPointsFStr(pMatch->getRound()));
	}

	// Result
	
	if(pMatch->isTeam())
		 m_pLis->setData(2006,pMatch->getTotalResult(true));
	else m_pLis->setData(2006,pMatch->getResultAsString());
	

	// Points 2
	if(pPoolAway)
	{
		//m_pLis->setData(2007,pAway->getPointsAsString());
		m_pLis->setData(2007,pPoolAway->getPoolPointsFStr(pMatch->getRound()));
	}

	// Seed Number 2
	if(pInsAway)
		m_pLis->setData(2008,pInsAway->getSeed());

	// Master Type 2
	if(pInsAway)
		m_pLis->setData(2009,pInsAway->getRegMasterTypeSDescription());
	

	// Name 2
	if(pInsAway)
		 m_pLis->setData(2010,pInsAway->getPrnLName());
	else m_pLis->setData(2010,m_pLis->getData(1501));

	// NOC Code 2
	if(pInsAway)
		m_pLis->setData(2011,pInsAway->getGroup());	
	
}

CReportBase::ReportReturn CHRC74::paintMembers(CHMatch *pMatch)
{
	
	MSLSortedVector vSubMatches;
	pMatch->getSubMatchesVector(vSubMatches);
	CHMatch *pSubMatch=0;
	for(short i=0;i<vSubMatches.entries();i++)
	{
		pSubMatch=(CHMatch*)vSubMatches[i];
		if (!pSubMatch->hasTeamCompetitors())
			continue;
		
		assignDataMember(pSubMatch);
		// Pintamos la members
		if( !m_pLis->runline(3) )
			return OnError(error,10);
		
	}
	
	return exit;
}
void CHRC74::assignDataMember(CHMatch *pSubMatch)
{
		
	// Reseteo
	for(short i=0;i<short(m_pLis->getVari(4));i++)
		m_pLis->setData(3000+i,"");
	


	CHMatchResult *pHome=(CHMatchResult *)pSubMatch->getHome();
	CHMatchResult *pAway=(CHMatchResult *)pSubMatch->getAway();

	GTHMatchMember *pMatchMemHome=(GTHMatchMember*)pHome->getMatchMember(0);
	GTHMatchMember *pMatchMemAway=(GTHMatchMember*)pAway->getMatchMember(0);
	
	CHMember *pMemberHome=0;
	CHMember *pMemberAway=0;
	
	if(pMatchMemHome)
		pMemberHome=(CHMember*)pMatchMemHome->getMember();

	if(pMatchMemAway)
		pMemberAway=(CHMember*)pMatchMemAway->getMember();

	// Bout Number
	m_pLis->setData(3000,pSubMatch->getSubMatch());
	
		
	// Master Type 1
	if(pMatchMemHome)
	{
		CHRegister *pRegister=(CHRegister*)pMatchMemHome->getRegister();
		if(pRegister)
			m_pLis->setData(3001,pRegister->getMasterTypeSDescription());
		
	}

	// Name 1
	if(pMatchMemHome)
		 m_pLis->setData(3003,pMatchMemHome->getPrnLName());
	else if(pHome->getBye())
		m_pLis->setData(3003,m_pLis->getData(1501));

	// NOC Code 1
	if(pMatchMemHome)
		 m_pLis->setData(3004,pMatchMemHome->getGroup());

	// Rating 1
	/*(pMatchMemHome)
		m_pLis->setData(3005,pMatchMemHome->getPointsAsString());*/

	// Result
	m_pLis->setData(3006,pSubMatch->getResultAsString());

	
	// Rating 2
	/*(pMemberAway)
		m_pLis->setData(3007,pMemberAway->getPointsAsString());*/

	// Seed Number 2
	/*if(pMatchMemAway)
		m_pLis->setData(3008,pMatchMemAway->getSeed());*/

	// Master Type 2
	if(pMatchMemAway)
	{
		CHRegister *pRegister=(CHRegister*)pMatchMemAway->getRegister();
		if(pRegister)
			m_pLis->setData(3008,pRegister->getMasterTypeSDescription());
		
	}

	// Name 2
	if(pMatchMemAway)
		 m_pLis->setData(3010,pMatchMemAway->getPrnLName());
	else if(pAway->getBye())
		m_pLis->setData(3010,m_pLis->getData(1501));
	
	// NOC Code 2
	if(pMatchMemAway)
		 m_pLis->setData(3011,pMatchMemAway->getGroup());
	
	
}
void CHRC74::buildVector()
{		
	MSLSetIterator iter(CHMemoryDataBase::getCol(__CHMATCH));
	
	CHMatch *pMatch = 0;
	while ((pMatch = (CHMatch*) iter())!=0 )
	{
		if (pMatch->getPhase() == m_pPhase && !pMatch->getSubMatch() &&
			(m_round==pMatch->getRound() || m_round==ALL_ROUNDS))
			m_vMatches.insert(pMatch);
	}

	m_vMatches.setFcCompare(orderMatches);
	m_vMatches.sort();
}
 
bool CHRC74::changeRound(CHMatch *pMatch)
{
	CHMatch *pMatchAux = 0;
	if((m_index)<m_vMatches.entries())
		pMatchAux=(CHMatch *)m_vMatches[m_index];

	if(!pMatchAux)
		return false;

	if (pMatch->getPhaseCode()!=SWISS_ROUND)
		return false;

	if(pMatchAux->getRound()!=pMatch->getRound())
		return true;
	

	return false;
}

void CHRC74::setDynamicLegends()
{
	CHMasterType *pMasterType = 0;
	MSLSetIterator iter(CHMemoryDataBase::getCol(__CHMASTERTYPE));
	
	while ((pMasterType=(CHMasterType*)iter())!=0)
	{
		if(pMasterType->getMasterType())
			m_pLegends->setDynamic( pMasterType->getSDescription());							
	}

	m_pLegends->createDynamic();
}