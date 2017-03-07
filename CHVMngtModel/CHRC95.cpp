/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHRC95.cpp
*   Description	: 
*
*	Author		: CH Team
*	Date created: 5-1-2006
* 	Project		:
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#include "stdVCH.h"
#include "CHRC95.h"
#include <Reports/V/GMedalCounter.h>
#include <Sports/CH/data/CHEvent.h>
#include <REPORTS/V/RLegend.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHRC95::CHRC95(CReportManager & aReportManager,CReportConfig& aReportConfig)
:CHReportTemplate(aReportManager,aReportConfig)
,pLis(0)
,okLis(false)
,pLegend(0)
{
	eventsMedals = fillColEventsMedals();
	pLegend = new CHRLegends (this,pReport,CHRLegends::eC95);
}

CHRC95::~CHRC95()
{
	if (pLegend)			delete pLegend;
	eventsMedals.clear();
}

RWCString CHRC95::getNameOfSourceLis()
{
	RWCString lang=DBApplication::getAppLanguage();
	return GMemoryDataBase::getDiscipline().getCode()+".C95."+lang+".lis";
}

void CHRC95::OnBeginReport()
{
	bOkLis=false;
	RWCString MSlisName = getNameOfSourceLis();
	CReportManager & aReportMng = pReport->getManager();
	// Controlamos que se tengan elementos para pintar
	if(!aVMedalStandings.getEntryPoint().entries())
	{
		AfxMessageBox(RWWString("There aren´t Medallists",RWWString::ascii));
		return;
	}
	// Instanciamos una referencia al lis del report Medal Standings
	CLis &aLis=pReport->setLis(MSlisName);
	pLis=&aLis;
	if( pLis->isValid() )
	{	// Legendas
		
		if (!pLegend)
		{ 
			AfxMessageBox(RWWString("Legends Error!!!",RWWString::ascii));
			return ; 
		}
		// Activamos control de margenes para pintar nuestro body
		aReportMng.setCtrlmargin(true);
		pReport->setCursor(0,0);
		// Asignamos variables
		pReport->setZeroAs("0");
		pLis->setCallBack(100,this);
		pLis->setCallBack(400,this);
		pLis->setCallBack(450,this);
		pLis->setVari(101,100);
		pLis->setVari(100,getCenter());
		// Codigo NOC, NPC, CGA, dependiente del .lis de cabeceras 
		pLis->setData(120,CReportTemplate::pLis->getData(300)); 
		
		char tmp[100];
		RWCString totalCountrys=pLis->getData(303);
		sprintf(tmp,totalCountrys,CReportTemplate::pLis->getData(300));		
		// Codigo NOC, NPC, CGA, dependiente del .lis de cabeceras 
		pLis->setData(301,RWCString(tmp)); 

		pLegend->loadLis();
	}
	else
	{	// Si hubo error en el report mostramos el error.
		AfxMessageBox(RWWString(aReportMng.getLastError(),RWWString::ascii));
	}
	bHeaderAsOf=true;
	bOkLis=true;
}

CReportBase::ReportReturn CHRC95::OnBody()
{ 
	RWDate dateAct;

	int rc=END_REPORT;
	
	
	char title[1000];
	sprintf(title, "AFTER %d OF %d EVENTS",eventsMedals.entries(), CHMemoryDataBase::getColEvents().entries());
	pLis->setData(500,title);

	if( !pLis->runline(100) )
		return error;

	while( (rc=aVMedalStandings++) != END_REPORT )
	{
		GData * pData = aVMedalStandings.getData(rc);
		GMedalsByNoc * pMedalsByNoc = (GMedalsByNoc *)pData;
		// Asignamos Rank By Gold
		pLis->setData(401,pMedalsByNoc->getRk()                  );

		pLis->setData(404,""              );
		pLis->setData(405,""              );
		pLis->setData(406,""              );
		pLis->setData(407,""              );
		pLis->setData(408,""              );
		pLis->setData(409,""              );
		pLis->setData(410,""              );
		pLis->setData(411,""              );
		pLis->setData(412,""              );
		pLis->setData(413,""              );
		pLis->setData(414,""              );
		pLis->setData(415,""              );
		pLis->setData(416,""              );
		pLis->setData(417,""              );
		pLis->setData(418,""              );
		pLis->setData(419,""              );
		pLis->setData(420,""              );

		RWWString countryName = pMedalsByNoc->getGroup()->getSDescription();
		RWCString countryNocName = pMedalsByNoc->getGroup()->getGroup() + " - " + countryName.toMultiByte();
		pLis->setData(402, countryNocName);
		pLis->setData(403,pMedalsByNoc->getGroup()->getGroup()       );
		if(pMedalsByNoc->getMaleGolds() )
			pLis->setData(404,pMedalsByNoc->getMaleGolds()               );
		if(pMedalsByNoc->getMaleSilvers())
			pLis->setData(405,pMedalsByNoc->getMaleSilvers()             );
		if(pMedalsByNoc->getMaleBronzes())
			pLis->setData(406,pMedalsByNoc->getMaleBronzes()             );
		if(pMedalsByNoc->getTotalMaleMedals())
			pLis->setData(407,pMedalsByNoc->getTotalMaleMedals()         );
		if(pMedalsByNoc->getFemaleGolds())
			pLis->setData(408,pMedalsByNoc->getFemaleGolds()             );
		if(pMedalsByNoc->getFemaleSilvers())
			pLis->setData(409,pMedalsByNoc->getFemaleSilvers()           );
		if(pMedalsByNoc->getFemaleBronzes())
			pLis->setData(410,pMedalsByNoc->getFemaleBronzes()           );
		if(pMedalsByNoc->getTotalFemaleMedals())
			pLis->setData(411,pMedalsByNoc->getTotalFemaleMedals()       );
		if(pMedalsByNoc->getMixGolds())
			pLis->setData(412,pMedalsByNoc->getMixGolds()				 );
		if(pMedalsByNoc->getMixSilvers())
			pLis->setData(413,pMedalsByNoc->getMixSilvers()				 );
		if(pMedalsByNoc->getMixBronzes())
			pLis->setData(414,pMedalsByNoc->getMixBronzes()				 );
		if(pMedalsByNoc->getTotalMixMedals())
			pLis->setData(415,pMedalsByNoc->getTotalMixMedals()			 );
		if(pMedalsByNoc->getTotalGolds())
			pLis->setData(416,pMedalsByNoc->getTotalGolds()              );
		if(pMedalsByNoc->getTotalSilvers())
			pLis->setData(417,pMedalsByNoc->getTotalSilvers()            );
		if(pMedalsByNoc->getTotalBronzes())
			pLis->setData(418,pMedalsByNoc->getTotalBronzes()            );
		if(pMedalsByNoc->getTotalMedals())
			pLis->setData(419,pMedalsByNoc->getTotalMedals()             );
		// Asignamos Rank By Total
		//if( pMedalsByNoc->getRkTotal() < pMedalsByNoc->getRkPoTotal())
		if (otherHasEqualRank(pMedalsByNoc))
		{
			RWCString equalRkTotal("");
			char buffer[200]; sprintf(buffer,"%d",pMedalsByNoc->getRkTotal());

			equalRkTotal=buffer;
			equalRkTotal.insert(0,"=");
			pLis->setData(420,equalRkTotal                           );
		}
		else
			pLis->setData(420,pMedalsByNoc->getRkTotal()             );
		// Pintamos datos del pais
		if( !pLis->runline(400) )
			return error;
		// Controlamos el pie de pagina
		if( IsPageBreak(short(pLis->getVari(101))) )
			return ok;
	}
	// Sumamos totales
	GMedalCounter aMedalCounter(aVMedalStandings.getEntryPoint());
	// Asignamos datos totales
	char tmp[100];
	RWCString totalNocs=pLis->getData(301)+"%d";
	sprintf(tmp,totalNocs,aMedalCounter.getTotalCountries());
	pLis->setData(302,RWCString(tmp));
	pLis->setData(452,aMedalCounter.getMaleGolds());
	pLis->setData(453,aMedalCounter.getMaleSilvers());
	pLis->setData(454,aMedalCounter.getMaleBronzes());
	pLis->setData(455,aMedalCounter.getTotalMaleMedals());
	pLis->setData(456,aMedalCounter.getFemaleGolds());
	pLis->setData(457,aMedalCounter.getFemaleSilvers());
	pLis->setData(458,aMedalCounter.getFemaleBronzes());
	pLis->setData(459,aMedalCounter.getTotalFemaleMedals());
	pLis->setData(460,aMedalCounter.getMixGolds());
	pLis->setData(461,aMedalCounter.getMixSilvers());
	pLis->setData(462,aMedalCounter.getMixBronzes());
	pLis->setData(463,aMedalCounter.getTotalMixMedals());
	pLis->setData(464,aMedalCounter.getTotalGolds());
	pLis->setData(465,aMedalCounter.getTotalSilvers());
	pLis->setData(466,aMedalCounter.getTotalBronzes());
	pLis->setData(467,aMedalCounter.getTotalMedals());
	// Pintamos datos totales
	if( !pLis->runline(450) )
		return error;

	// Pintamos la leyenda
	pLegend->runLis();

	return exit;
}

RWSet CHRC95::fillColEventsMedals()
{
	RWSet setAux;
	GEvent     * pEvent     = 0;
	GMedallist * pMedallist = 0;
	RWSetIterator iterMedallist(GMemoryDataBase::getColMedallist());
	while( (pMedallist=(GMedallist *)iterMedallist()) != 0 )
	{
		pEvent = pMedallist->getEvent();
		if( pEvent )
			setAux.insert(pEvent);
	}

	return setAux;
}



bool CHRC95::otherHasEqualRank(GMedalsByNoc *pMedalsByNoc)
{
	VMedalStandings aVMedalStandingsAux;
	if(!aVMedalStandingsAux.getEntryPoint().entries())
		return false;
	int rc=END_REPORT;
	while( (rc=aVMedalStandingsAux++) != END_REPORT )
	{
		GData * pData = aVMedalStandingsAux.getData(rc);
		GMedalsByNoc * pMedalsByNocAux = (GMedalsByNoc *)pData;
		if (pMedalsByNocAux->getGroup() == pMedalsByNoc->getGroup())
			continue;
		if (pMedalsByNocAux->getRkTotal() == pMedalsByNoc->getRkTotal())
			return true;
	}
	return false;
	
}

RWDate CHRC95::OnGetEventDate() const
{
	return INVALID_RWDATE;
}

RWTime CHRC95::OnGetEventTime() const
{
	return INVALID_RWTIME;
}