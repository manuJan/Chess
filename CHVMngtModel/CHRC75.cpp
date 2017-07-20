/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHRC75.cpp
*	Description	:
*
*	Author		:CH Team
*	Date created:24-01-2006
* 	Project		:CHVMngtModel
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdafx.h"
#include "CHRC75.h"
#include "CHRLegends.h"
#include "..\CHMngtModel\CHEvent.h"
#include "..\CHMngtModel\CHPhase.h"
#include "..\CHMngtModel\CHPool.h"
#include "..\CHMngtModel\CHPoolResult.h"
#include "..\CHMngtModel\CHRegister.h"
#include "..\CHMngtModel\CHInscription.h"

////////////////////////////////////////////////////////////////////////////////////
static int orderPoolResult(const MSLItem** a, const MSLItem** b)
{
	CHPoolResult * pPoolResultA = (CHPoolResult *) (*a);
	CHPoolResult * pPoolResultB = (CHPoolResult *) (*b);

	CHPool *pPoolA=(CHPool*)pPoolResultA->getPool();
	CHPool *pPoolB=(CHPool*)pPoolResultB->getPool();

	// Order by Pool
	int order = pPoolA->getOrder() - pPoolB->getOrder();
	if( order )
		return order;

	// Si alguno de ellos no tienen la sesión asignada va para abajo.
	if (!pPoolResultA->getRankPo())
		return 1;
	if (!pPoolResultB->getRankPo())
		return -1;

	// Order by Rank Po
	order = pPoolResultA->getRankPo() - pPoolResultB->getRankPo();
	if( order )
		return order;

	// Si alguno de ellos no tienen la sesión asignada va para abajo.
	if (!pPoolResultA->getRank())
		return 1;
	if (!pPoolResultB->getRank())
		return -1;

	// Order by Rank 
	order = pPoolResultA->getRank() - pPoolResultB->getRank();
	if( order )
		return order;
	
	// Order by key
	return strcmp(pPoolResultA->getKey(),pPoolResultB->getKey());
}
/////////////////////////////////////////////////////////////////////
CHRC75::CHRC75(CReportManager& aReportManager,CReportConfig& aReportConfig,CHPhase * pSelPhase,short roundSel)
:CHReportTemplate(aReportManager,aReportConfig,(CHEvent*)pSelPhase->getEvent())
,m_pLis(0)
,m_pPhase(pSelPhase)
,m_index(0)
,m_pLegends(0)
,m_round(roundSel)
,m_firstPage(true)
{
	m_pLegends=new CHRLegends(this,m_pReport,CH75);
	
}

/////////////////////////////////////////////////////////////////////
CHRC75::~CHRC75()
{
	if ( m_pLegends )
		delete m_pLegends;
}

/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
MSLString CHRC75::getNameOfSourceLis(void)
{
	return "CH.C75.lis";
	
}

/////////////////////////////////////////////////////////////////////
void CHRC75::OnBeginReport()
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

		initLabels();

		// SetVaris Font
		setVaris(m_pLis);
								
		// Iniciamos funcion para el relleno de la tabla
		m_pLis->setCallBack(1,this);
		m_pLis->setCallBack(2,this);
		m_pLis->setCallBack(3,this);

		//Leyendas		
		m_pLegends->loadLis();
		
		buildVector();
		setGlobalVaris();

		if (m_pPhase->isTeamEvent())
		{
			m_pLis->setData(1014, m_pLis->getData(1013));
			m_pLis->setVari(111,m_pLis->getVari(112));
		}
		else
		{
			m_pLis->setData(1014, "");
			m_pLis->setVari(111,m_pLis->getVari(113));
		}

	}
	else
	{	// Si hubo error en el report mostramos el error.
		MessageBox(0,MSLWString(aReportMng.getLastError()+"\n"+getNameOfSourceLis()),L"",MB_OK);
	}
}

void CHRC75::initLabels()
{
	m_pLis->setData(1000,getUserLabel(160)); // "Rank"		
	m_pLis->setData(1001,getUserLabel(161)); // "Name"		
	m_pLis->setData(1002,getUserLabel(162)); // "Played"		
	m_pLis->setData(1003,getUserLabel(163)); // "Won"			
	m_pLis->setData(1004,getUserLabel(164)); // "Drawn"		
	m_pLis->setData(1005,getUserLabel(165)); // "Lost"		
	m_pLis->setData(1006,getUserLabel(166)); // "Match"		
	m_pLis->setData(1007,getUserLabel(167)); // "Points"			
	m_pLis->setData(1009,getUserLabel(168)); // "Code"		
	m_pLis->setData(1010,getUserLabel(169)); // "Points"		
	m_pLis->setData(1011,getUserLabel(170)); // "BH."			
	m_pLis->setData(1012,getUserLabel(171)); // "SB"			
	m_pLis->setData(1013,getUserLabel(172)); // "Game"				
	m_pLis->setData(1015,getUserLabel(173)); // "After Round "	
	m_pLis->setData(1500,getUserLabel(174)); // "Legend"		
}

/////////////////////////////////////////////////////////////////////
CReportBase::ReportReturn CHRC75::OnBody()
{
		
	// Controlamos que haya datos para pintar
	if( !m_vPoolResults.entries() )
	{
		MessageBox(0,L"No entries found",L"",MB_OK);		
		return error;
	}
		
	
	// Template de Cabeceras
	if( paintTemplateHeader() == error )
		return error;
	
	// Template de Results
	return paintTemplateResults();
}

CReportBase::ReportReturn CHRC75::paintLegends()
{
	if( !m_pLegends->runLis() )
		return OnError(error,10);
		
	return exit;
}

/////////////////////////////////////////////////////////////////////
CReportBase::ReportReturn CHRC75::paintTemplateHeader()
{
	MSLWString tmp = TOWSTRING(m_round);
	if(m_round)
	{
		MSLWString roundDesc = m_pLis->getData(1015) + tmp;
		m_pLis->setData(2100, roundDesc );
	}
	
	// Pintamos la ronda
	if( !m_pLis->runline(5) )
		return OnError(error,10);
	

	// Pintamos la cabecera
	if( !m_pLis->runline(1) )
		return OnError(error,10);

	return exit;
}

/////////////////////////////////////////////////////////////////////
CReportBase::ReportReturn CHRC75::paintTemplateResults()
{
	CHPoolResult * pPoolResult = 0;
				
	while( m_index < m_vPoolResults.entries() )
	{
		pPoolResult = (CHPoolResult *)m_vPoolResults[m_index];
		
		if( !pPoolResult )
			return OnError(error,120);
				

		assignDataIndividual(pPoolResult);

		// Pintamos los datos 
		if( !m_pLis->runline(2) )
			return OnError(error,130);

				
		m_index++;
		
		// Comprobamos si hay salto de pagina
		if( IsPageBreak(short(m_pLis->getVari(800))) && m_index != m_vPoolResults.entries())
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
void CHRC75::setGlobalVaris()
{
	
	CHEvent *pEvent=(CHEvent*)m_pPhase->getEvent();

	CHPoolResult *pPoolResult= 0;
	if(m_vPoolResults.entries())
		pPoolResult=(CHPoolResult *)m_vPoolResults[0];

	m_pLis->setVari(109,0);
	m_pLis->setVari(110,0);
	m_pLis->setVari(114,0);
	m_pLis->setVari(115,0);

	if(pPoolResult)
	{
		CHPool *pPool=(CHPool*)pPoolResult->getPool();
		if(pPool && pPool->getStatus()>CHMemoryDataBase::eUnofficial)
		{
			m_pLis->setVari(109,m_pLis->getVari(120));
			m_pLis->setVari(110,m_pLis->getVari(121));
			m_pLis->setVari(114,m_pLis->getVari(122));
			m_pLis->setVari(115,m_pLis->getVari(123));
		}
	}

	// Winned by Members solo en Teams
	if(pEvent->isTeam())
		 m_pLis->setVari(107,1);
	else m_pLis->setVari(107,0);
	 
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
	m_pLis->setData(1008,CReportTemplate::m_pHeaderLis->getData(300)); 
}
/////////////////////////////////////////////////////////////////////
MSLDate CHRC75::OnGetEventDate() const
{
	return INVALID_DATE;
}
MSLTime CHRC75::OnGetEventTime() const
{
	return INVALID_TIME;
}
MSLWString CHRC75::OnGetLine(const int lineNumber,const char *language) const
{
	return CReportTemplate::OnGetLine(lineNumber,language);
}
unsigned short CHRC75::OnCallbackFn( struct USR_TAB * pTableInfo )
{
	return CReportBase::OnCallbackFn(pTableInfo);
}

void CHRC75::assignDataIndividual(CHPoolResult *pPoolResult)
{
		
	// Reseteo
	for(short i=0;i<short(m_pLis->getVari(4));i++)
		m_pLis->setData(2000+i,"");


	if(!pPoolResult)
		return;
		
	CHRegister *pRegister=(CHRegister*)pPoolResult->getRegister();
	CHPool* pPool = (CHPool*)pPoolResult->getPool();

	// Rank
	if (pPoolResult->getQualitativeCode()!=OK)
		m_pLis->setData(2000,pPoolResult->getQualitativeSDescription());
	else if (pPoolResult->getRank())
		m_pLis->setData(2000,pPoolResult->getRank());
	
	// NOC Code
	if(pRegister)
		m_pLis->setData(2001,pRegister->getGroup());
	
	// Name 1
	if(pRegister)
		m_pLis->setData(2002,pRegister->getPrnLName());

	bool paintPoolResults=false;
	if (pPool->getNumRoundsPlayed()==m_round)
		paintPoolResults=true;
	// Games Played
	
	if (paintPoolResults)
		m_pLis->setData(2003,pPoolResult->getMPlayed());
	else
		m_pLis->setData(2003,pPoolResult->getMatchesPlayed(m_round));

	// Win 
	if (paintPoolResults)
		m_pLis->setData(2004,pPoolResult->getMWon());
	else
		m_pLis->setData(2004,pPoolResult->getMatchesWon(m_round));
		
	// Drawn
	if (paintPoolResults)
		m_pLis->setData(2005,pPoolResult->getMDrawn());
	else
		m_pLis->setData(2005,pPoolResult->getMatchesDrawn(m_round));

	// Lost
	if (paintPoolResults)
		m_pLis->setData(2006,pPoolResult->getMLost());
	else
		m_pLis->setData(2006,pPoolResult->getMatchesLost(m_round));

	// Puntos de Encuentro, Points for Won Matches
	if (paintPoolResults)
		m_pLis->setData(2007,pPoolResult->getMatchPointsStr());
	else
		m_pLis->setData(2007,pPoolResult->getPointsForWon(m_round));

	// Points 
	if (paintPoolResults)
		m_pLis->setData(2008,pPoolResult->getPointsFStr());
	else
		m_pLis->setData(2008,pPoolResult->getPoolPointsFStr(m_round));

	// Median SO
	if (paintPoolResults)
		m_pLis->setData(2011,pPoolResult->getMedianSolkOffFStr());
	else
		m_pLis->setData(2011,pPoolResult->getMedianSolkOffFStr(m_round));

	// SolkOff
	if (paintPoolResults)
		m_pLis->setData(2009,pPoolResult->getSolkOffFStr());
	else
		m_pLis->setData(2009,pPoolResult->getSolkOffFStr(m_round));
	
	// SonneBerger
	if (paintPoolResults)
		m_pLis->setData(2010,pPoolResult->getSonneBergerFStr());
	else
		m_pLis->setData(2010,pPoolResult->getSonneBergerFStr(m_round));

	// Progressive Score
	if (paintPoolResults)
		m_pLis->setData(2012,pPoolResult->getMProgressiveScoreStr());
	else
		m_pLis->setData(2012,pPoolResult->getProgressiveFStr(m_round));
	
}

void CHRC75::buildVector()
{
		
	MSLSetIterator iter(CHMemoryDataBase::getCol(__CHPOOLRESULT));
	
	CHPoolResult *pPoolResult = 0;
	while ((pPoolResult = (CHPoolResult*) iter())!=0 )
	{
		if (pPoolResult->getPhase() == m_pPhase && !pPoolResult->getBye())
			m_vPoolResults.insert(pPoolResult);
	}

	m_vPoolResults.setFcCompare(orderPoolResult);
	m_vPoolResults.sort();
}
 
