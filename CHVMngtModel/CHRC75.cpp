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

#include "stdVCH.h"
#include "CHRC75.h"
#include "CHRLegends.h"
#include <SPORTS/CH/DATA/CHMsgDefines.h>
#include <SPORTS/CH/DATA/CHRegister.h>
#include "CHReportDefines.h"

////////////////////////////////////////////////////////////////////////////////////
static int orderPoolResult(const GVectorElement** a, const GVectorElement** b)
{
	CHPoolResult * pPoolResultA = (CHPoolResult *) (*a)->getElement();
	CHPoolResult * pPoolResultB = (CHPoolResult *) (*b)->getElement();

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
,pLis(0)
,pPhase(pSelPhase)
,index(0)
,pLegends(0)
,round(roundSel)
,firstPage(true)
{
	pLegends=new CHRLegends(this,pReport,CHRLegends::eC75);
	
}

/////////////////////////////////////////////////////////////////////
CHRC75::~CHRC75()
{
	if ( pLegends )
		delete pLegends;
	vPoolResults.clearAndDestroy();
}

/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
RWCString CHRC75::getNameOfSourceLis(void)
{
	RWCString lang = DBApplication::getAppLanguage();
	
	return CHMemoryDataBase::getDiscipline().getCode()+".C75."+lang+".lis";
	
}

/////////////////////////////////////////////////////////////////////
void CHRC75::OnBeginReport()
{
	CReportManager& aReportMng = pReport->getManager();

	// Instanciamos una referencia al lis del report
	CLis& aLis = pReport->setLis(getNameOfSourceLis());
	pLis = &aLis;
	if( pLis && pLis->isValid() )
	{
		// Iniciamos variables
		aReportMng.setCtrlmargin(true);
		pReport->setCursor(0,0);
		pLis->setVari(1,getCenter());
		pLis->setVari(2,aReportMng.getXMax()-getRightMargin());

		bOkLis = true;
		// SetVaris Font
		setVaris(pLis);
				
				
		// Iniciamos funcion para el relleno de la tabla
		pLis->setCallBack(1,this);
		pLis->setCallBack(2,this);
		pLis->setCallBack(3,this);

		//Leyendas
		pLegends->setEvent((CHEvent*)pPhase->getEvent());
		pLegends->loadLis();
		
		buildVector();
		setGlobalVaris();

		if (pPhase->getEvent()->isTeam())
		{
			pLis->setData(1014, pLis->getData(1013));
			pLis->setVari(111,pLis->getVari(112));
		}
		else
		{
			pLis->setData(1014, "");
			pLis->setVari(111,pLis->getVari(113));
		}

	}
	else
	{	// Si hubo error en el report mostramos el error.
		AfxMessageBox(RWWString(aReportMng.getLastError(),RWWString::multiByte)+
					  _T("\n")+RWWString(getNameOfSourceLis(),RWWString::multiByte));
	}
}

/////////////////////////////////////////////////////////////////////
CReportBase::ReportReturn CHRC75::OnBody()
{
		
	// Controlamos que haya datos para pintar
	if( !vPoolResults.entries() )
	{
		AfxMessageBox(_T("There are not matche/s"));
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
	if( !pLegends->runLis() )
		return OnError(error,10);
		
	return exit;
}

/////////////////////////////////////////////////////////////////////
CReportBase::ReportReturn CHRC75::paintTemplateHeader()
{
	CHEvent * pEvent = (CHEvent *)pPhase->getEvent();
		
	char tmp[10];
	sprintf(tmp,"Round %d",round);
	if(round)
		 pLis->setData(2100,RWCString(tmp));
	
	// Pintamos la ronda
	if( !pLis->runline(5) )
		return OnError(error,10);
	

	// Pintamos la cabecera
	if( !pLis->runline(1) )
		return OnError(error,10);

	return exit;
}

/////////////////////////////////////////////////////////////////////
CReportBase::ReportReturn CHRC75::paintTemplateResults()
{
	CHEvent * pEvent = (CHEvent *)pPhase->getEvent();
			
	CHPoolResult * pPoolResult = 0;
				
	while( index < vPoolResults.entries() )
	{
		pPoolResult = (CHPoolResult *)vPoolResults[index]->getElement();
		
		if( !pPoolResult )
			return OnError(error,120);
				

		assignDataIndividual(pPoolResult);

		// Pintamos los datos 
		if( !pLis->runline(2) )
			return OnError(error,130);

				
		index++;
		
		// Comprobamos si hay salto de pagina
		if( IsPageBreak(short(pLis->getVari(800))) && index != vPoolResults.entries())
		{
			// Leyendas
			firstPage=false;
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
	
	CHEvent *pEvent=(CHEvent*)pPhase->getEvent();

	CHPoolResult *pPoolResult= 0;
	if(vPoolResults.entries())
		pPoolResult=(CHPoolResult *)vPoolResults[0]->getElement();

	pLis->setVari(109,0);
	pLis->setVari(110,0);
	pLis->setVari(114,0);
	pLis->setVari(115,0);

	if(pPoolResult)
	{
		CHPool *pPool=(CHPool*)pPoolResult->getPool();
		if(pPool && pPool->getStatus()>CHMemoryDataBase::eUnofficial)
		{
			pLis->setVari(109,pLis->getVari(120));
			pLis->setVari(110,pLis->getVari(121));
			pLis->setVari(114,pLis->getVari(122));
			pLis->setVari(115,pLis->getVari(123));
		}
	}

	// Winned by Members solo en Teams
	if(pEvent->isTeam())
		 pLis->setVari(107,1);
	else pLis->setVari(107,0);
	 
	// Corx centrada de la tabla
	int width=0;
	// Vari[21] son los posibles celdas a pintar
	for(int i=0;i<pLis->getVari(4);i++)
		width+=pLis->getVari(short(100+i))*pLis->getVari(short(200+i));
	
	long center=getCenter();
	long offsetx=center-(width/2);
	if (offsetx>25)
		pLis->setVari(3,offsetx-25);
	else
		pLis->setVari(3,10);
	

	// Codigo NOC, NPC, CGA, dependiente del .lis de cabeceras
	pLis->setData(1008,CReportTemplate::pLis->getData(300)); 
}
/////////////////////////////////////////////////////////////////////
RWDate CHRC75::OnGetEventDate() const
{
	return INVALID_RWDATE;
}
RWTime CHRC75::OnGetEventTime() const
{
	return INVALID_RWTIME;
}
RWWString CHRC75::OnGetLine(const int lineNumber,const char *language) const
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
	for(short i=0;i<short(pLis->getVari(4));i++)
		pLis->setData(2000+i,"");


	if(!pPoolResult)
		return;
		
	CHRegister *pRegister=(CHRegister*)pPoolResult->getRegister();
	CHInscription *pInscription=(CHInscription*)pPoolResult->getInscription();
	CHPool* pPool = (CHPool*)pPoolResult->getPool();

	// Rank
	if (pPoolResult->getQualitativeCode()!=OK)
		pLis->setData(2000,pPoolResult->getQualitativeSDescription());
	else if (pPoolResult->getRank())
		pLis->setData(2000,pPoolResult->getRank());
	
	// NOC Code
	if(pRegister)
		pLis->setData(2001,pRegister->getGroup());
	
	// Name 1
	if(pRegister)
		pLis->setData(2002,pRegister->getPrnLName());

	RWBoolean paintPoolResults=false;
	if (pPool->getNumRoundsPlayed()==round)
		paintPoolResults=true;
	// Games Played
	
	if (paintPoolResults)
		pLis->setData(2003,pPoolResult->getMPlayed());
	else
		pLis->setData(2003,pPoolResult->getMatchesPlayed(round));

	// Win 
	if (paintPoolResults)
		pLis->setData(2004,pPoolResult->getMWon());
	else
		pLis->setData(2004,pPoolResult->getMatchesWon(round));
		
	// Drawn
	if (paintPoolResults)
		pLis->setData(2005,pPoolResult->getMDrawn());
	else
		pLis->setData(2005,pPoolResult->getMatchesDrawn(round));

	// Lost
	if (paintPoolResults)
		pLis->setData(2006,pPoolResult->getMLost());
	else
		pLis->setData(2006,pPoolResult->getMatchesLost(round));

	// Puntos de Encuentro, Points for Won Matches
	if (paintPoolResults)
		pLis->setData(2007,pPoolResult->getAllRoundsPointsForWon());
	else
		pLis->setData(2007,pPoolResult->getPointsForWon(round));

	// Points 
	if (paintPoolResults)
		pLis->setData(2008,pPoolResult->getPointsFStr());
	else
		pLis->setData(2008,pPoolResult->getPoolPointsFStr(round));

	// Median SO
	if (paintPoolResults)
		pLis->setData(2011,pPoolResult->getMMedianSolkOffStr());
	else
		pLis->setData(2011,pPoolResult->getMedianSolkOffFStr(round));

	// SolkOff
	if (paintPoolResults)
		pLis->setData(2009,pPoolResult->getMSolkOffStr());
	else
		pLis->setData(2009,pPoolResult->getSolkOffFStr(round));
	
	// SonneBerger
	if (paintPoolResults)
		pLis->setData(2010,pPoolResult->getMSonneBergerStr());
	else
		pLis->setData(2010,pPoolResult->getSonneBergerFStr(round));

	// Progressive Score
	if (paintPoolResults)
		pLis->setData(2012,pPoolResult->getMProgressiveScoreStr());
	else
		pLis->setData(2012,pPoolResult->getProgressiveFStr(round));
	
}

void CHRC75::buildVector()
{
		
	RWSetIterator iter(CHMemoryDataBase::getColPoolResults());
	
	CHPoolResult *pPoolResult = 0;
	while ((pPoolResult = (CHPoolResult*) iter())!=0 )
	{
		if (pPoolResult->getPhase() == pPhase)
			vPoolResults.insert(pPoolResult);
	}

	vPoolResults.sort(orderPoolResult);
}
 
