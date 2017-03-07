/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHRLegends.cpp
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:15-12-2005
*   Project     :CHV Model               
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///
#include "stdVCH.h"
#include "CHRLegends.h"
#include <Sports/CH/Data/CHMemoryDataBase.h>
#include <Reports/V/OrderView.h>

static int orderEventsByOrder(const GVectorElement** a, const GVectorElement** b)
{
	CHEvent *pEvent1=(CHEvent *)(*a)->getElement();
	CHEvent *pEvent2=(CHEvent *)(*b)->getElement();

	int rc = pEvent1->getOrderEvent() - pEvent2->getOrderEvent();
	if( !rc )
		rc = strcmp(pEvent1->getKey(),pEvent2->getKey());
	return rc;
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHRLegends::CHRLegends(CReportTemplate *pRepTem, CReport *pRep,OrisCode id)
:RLegend(pRepTem, pRep)
,pLegendLis(0)
,orisCod(id)
,pEvent(0)
{
	loadLegendDescription(pRep);
}

CHRLegends::~CHRLegends()
{
}

//////////////////////////////////////////////////////////////////////
// dynamic assign
//////////////////////////////////////////////////////////////////////
	
void CHRLegends::setDynamic(const wchar_t *key)
{
	RLegend::setDynamic(key,idDynamic);
}

void CHRLegends::createDynamic()
{
	RLegend::createDynamic(idDynamic);
}

void CHRLegends::OnSettings(int id)
{
	
	UNREFERENCED_PARAMETER(id);
}
RWBoolean CHRLegends::OnLoadLis()
{
 	RWCString lang = DBApplication::getAppLanguage();
	RWCString lis = "CHLegends." + lang + ".lis";

	CLis& aLis=pReport->setLis(lis);
	pLegendLis=&aLis;

	if( !pLegendLis->isValid() )
	{
		CReportManager& aReportMng=pReport->getManager();
		AfxMessageBox(TOWSTRING(aReportMng.getLastError()+"\n"+lis));
		pLegendLis=0;
	}
	
	if( pLegendLis )
	{
		loadData();
		return true;
	}

	return false;
}
bool CHRLegends::loadLegendDescription(CReport *pRep)
{
	// Cargamos el lis
	RWCString lang=DBApplication::getAppLanguage();
	RWCString nameOfList=CHMemoryDataBase::getDiscipline().getCode()+"LegendsDescription."+lang+".lis";
	CLis& aLegDes=pRep->setLis(nameOfList);
	pLegendLis=&aLegDes;

	return pLegendLis->isValid();
}

bool CHRLegends::loadData()
{
	
	switch (orisCod)
	{
	case eC30:
		printLegendForC30();
		break;
	case eC32A:
		printLegendForC32A();
		break;
	case eC51:
		printC51Legend();
		break;
	case eC58:
		printC58Legend();
		break;
	case eC73:
		printLegendResults();
		break;
	case eC74:
		printC74Legend();
		break;
	case eC75:
		printC75Legend();
		break;
	case e76A:
		printC76ALegend();
		break;
	case e76B:
		printC76BLegend();
		break;
	case eC95:
		printC95Legend();
		break;
	case eC96:
		printC96Legend();
		break;
	default:	
		return false;
		break;
	}
	return true;
}

CLis * CHRLegends::getLegDes()
{
	return pLegendLis;
}

void CHRLegends::setEvent(CHEvent * _pEvent)
{ 
	pEvent=_pEvent; 
}

void CHRLegends::setMatch(CHMatch * _pMatch)
{ 
	pMatch=_pMatch; 
}

RWCString CHRLegends::giveMeData(int data)
{ 
	return pLegendLis->getData(short(data)); 
}

void CHRLegends::printLegend()
{
	//printTheActiveLegend();
}

void CHRLegends::printLegendForC30()
{
	idDynamic=addDynamicLegend(3);
	
	CHEvent *pEvent = 0;
	GSortedVector vEvents(CHMemoryDataBase::getColEvents(),orderEventsByOrder);
	for( size_t i=0; i<vEvents.entries(); i++ )
	{
		pEvent = (CHEvent *)vEvents[i]->getElement();
		////addlegend(pEvent->getSDescription().toAscii(),pEvent->getLDescription().toAscii() );
		addItem(pEvent->getSDescription()+_T("|")+pEvent->getLDescription());
	}
	
}
void CHRLegends::printLegendForC32A()
{
	
	idDynamic=addDynamicLegend(2);

	GSex *pSex = 0;
	GSortedVector vSexs = GSortedVector(CHMemoryDataBase::getColSex(),orderSex );
	for(size_t i=0; i<vSexs.entries(); i++ )
	{
		pSex = (GSex *) vSexs[i]->getElement();
		if( pSex->getSex()!="2" )
			addItem(pSex->getSDescription()+_T("|")+pSex->getLDescription());
				
	}

	CHEvent *pEvent = 0;
	GSortedVector vEvents(CHMemoryDataBase::getColEvents(),orderEventsByOrder);
	for( i=0; i<vEvents.entries(); i++ )
	{
		pEvent = (CHEvent *)vEvents[i]->getElement();
		addItem(pEvent->getSDescription()+_T("|")+pEvent->getLDescription() );

	}
}
void CHRLegends::printC51Legend()
{
	idDynamic=addDynamicLegend(2);

	CHMasterType *pMasterType = 0;
	RWSetIterator iter(CHMemoryDataBase::getColMasterTypes());
	
	while ((pMasterType=(CHMasterType*)iter())!=0)
	{
		if(pMasterType->getMasterType())
			addItem(pMasterType->getSDescription()+_T("|")+pMasterType->getLDescription());
	}
	
}
void CHRLegends::printC58Legend()
{
	idDynamic=addDynamicLegend(2);

	CHEvent *pEvent = 0;
	GSortedVector vEvents(CHMemoryDataBase::getColEvents(),orderEventsByOrder);
	for( int i=0; i<short(vEvents.entries()); i++ )
	{
		pEvent = (CHEvent *)vEvents[i]->getElement();
		addItem(pEvent->getSDescription()+_T("|")+pEvent->getLDescription() );

	}

	RWSetIterator iter(CHMemoryDataBase::getColPhaseNames());
	CHPhaseBase *pPhaseBase=0;
	while ((pPhaseBase=(CHPhaseBase*)iter())!=0)
		addItem(pPhaseBase->getSDescription()+_T("|")+pPhaseBase->getLDescription() );
	
}

void CHRLegends::printC74Legend()
{
	idDynamic=addDynamicLegend(2);

	CHMasterType *pMasterType = 0;
	RWSetIterator iter(CHMemoryDataBase::getColMasterTypes());
	
	while ((pMasterType=(CHMasterType*)iter())!=0)
	{
		if(pMasterType->getMasterType())
			addItem(pMasterType->getSDescription()+_T("|")+pMasterType->getLDescription());
	}
}
void CHRLegends::printC75Legend()
{
	
	if(pEvent && pEvent->getStatus()>CHMemoryDataBase::eUnofficial)
	{

		addStaticLegend(2);
		int start	= 100;
		RWCString d	= "";
		for(int i=start;d!="end";i++)
		{	
			d = pLegendLis->getData(short(i));
			if( d!="end" )
				addItem(TOWSTRING(d));
		}
	}
}

void CHRLegends::printLegendResults()
{
	//printTheActiveLegend();
}

void CHRLegends::printC76ALegend()
{
	
}
/////////////////////////////////////////////////////////////////////
void CHRLegends::printC76BLegend()
{

}


void CHRLegends::printC95Legend()
{
	addStaticLegend(2);
	int start	= 150;
	RWCString d	= "";
	for(int i=start;d!="end";i++)
	{	
		d = pLegendLis->getData(short(i));
		if( d!="end" )
			addItem(TOWSTRING(d));
	}
	
}

void CHRLegends::printC96Legend()
{
	
	idDynamic=addDynamicLegend(2);

	CHMasterType *pMasterType = 0;
	RWSetIterator iter(CHMemoryDataBase::getColMasterTypes());
	
	while ((pMasterType=(CHMasterType*)iter())!=0)
	{
		if(pMasterType->getMasterType())
			addItem(pMasterType->getSDescription()+_T("|")+pMasterType->getLDescription());
	}
	
}
