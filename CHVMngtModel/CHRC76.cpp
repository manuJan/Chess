/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHRC76.cpp
*   Description	: 
*
*	Author		: CH Team
*	Date created: 22-12-2005
* 	Project		:
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#include "stdVCH.h"
#include "CHRPool.h"
#include "CHRC76.h"
 
#include <SPORTS/CH/DATA/CHMemoryDataBase.h>
#include <SPORTS/CH/DATA/CHEvent.h>
#include <SPORTS/CH/DATA/CHInscription.h>
#include <SPORTS/CH/DATA/CHMember.h>
#include <SPORTS/CH/DATA/CHRegister.h>

#include "CHRLegends.h"

static int orderCHRPoolByOrder(const GVectorElement** a, const GVectorElement** b)
{
	CHRPool* pCHRPoolA = (CHRPool *)(*a)->getElement();
	CHRPool* pCHRPoolB = (CHRPool *)(*b)->getElement();

	CHPool* pPoolA = pCHRPoolA->getPool();
	CHPool* pPoolB = pCHRPoolB->getPool();

	// Compare Match Number
    int	order = (pPoolA->getPhase()->getOrder() - pPoolB->getPhase()->getOrder());
	if (order)
		return order;

	// Compare Match Number
    order = (pPoolA->getOrder() - pPoolB->getOrder());
	if (order)
		return order;

	// .... y si no se puede comparar pues ... Compare keys
	return strcmp(pPoolA->getKey(),pPoolB->getKey());
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHRC76::CHRC76(CReportManager& aReportManager,CReportConfig& aReportConfig, CHEvent* _pEvent, typeReport _repType)
:CHReportTemplate(aReportManager,aReportConfig,_pEvent)
,pLis(0)
,pReportMng(&aReportManager)
,index(0)
,indexRound(0)
,indexTwice(0)
,indexHeightTwice(0)
,nLines(0)
,newPage(false)
,pEvent(_pEvent)
,repType(_repType)
,jumpPooles(false)
,pCurrentCHRPool(0)
,pPhaseAnt(0)
,nInitLine(0)
,nLastLine(0)
{
	loadDataPool();
}

CHRC76::~CHRC76()
{
	for (size_t i=0;i<vCHRPool.entries();i++)
	{
		CHRPool* pCHRPool = (CHRPool*)vCHRPool[i]->getElement();
		delete pCHRPool;
	}
}

RWCString CHRC76::getNameOfSourceLis()
{
	RWCString lang = DBApplication::getAppLanguage();
	return CHMemoryDataBase::getDiscipline().getCode()+"RC76"+lang+".lis";
}

void CHRC76::loadDataPool()
{
	if (!pEvent)
		return;

	CHRPool* pCHRPool=0;

	for (size_t i=0;i<pEvent->getPhasesVector().entries();i++)
	{
		CHPhase* pPhase = (CHPhase*)pEvent->getPhasesVector()[i]->getElement();
		if (pPhase->getIsPool())
		{
			for (size_t j=0;j<pPhase->getPoolsVector().entries();j++)
			{
				CHPool* pPool = (CHPool*) pPhase->getPoolsVector()[j]->getElement();
				if (pPool)
				{
					pCHRPool = new CHRPool(this,pReport,pPool,nLines,repType);
					vCHRPool.insert(pCHRPool);
				}
			}			
		}
	}		

	vCHRPool.sort(orderCHRPoolByOrder);
	if (vCHRPool.entries())
		pCurrentCHRPool=(CHRPool *)vCHRPool[0]->getElement();
}


void CHRC76::OnBeginReport()
{
	bOkLis=false;
	// Instanciamos una referencia al lis del report
	RWCString nameLis = getNameOfSourceLis();
	CLis& aLis = pReport->setLis(nameLis);
	pLis = &aLis;

	for (size_t i=0;i<vCHRPool.entries();i++)
	{
		CHRPool* pCHRPool = (CHRPool*)vCHRPool[i]->getElement();
		bOkLis=pCHRPool->OnBeginReport();
		if (!bOkLis)
			return;
	}
	bHeaderAsOf=true;
	pReport->setZeroAs("0");
	pReport->setCursor(0,0);
	pReportMng->setCtrlmargin(true);
}

CReportBase::ReportReturn CHRC76::OnBody()
{	
	xPool=0;
	// Competition Summary
	if (!newPage || jumpPooles)
	{
		for (size_t i=index;i<vCHRPool.entries();i++,index++)
		{
			pCurrentCHRPool = (CHRPool*)vCHRPool[i]->getElement();
			if (repType==CHRC76::eFinalSummary)
				indexRound=pCurrentCHRPool->getNumRounds()-1;
			for (size_t j=indexRound; j<size_t(pCurrentCHRPool->getNumRounds()); j++,indexRound++)
			{
				if (repType==CHRC76::eSchedule &&
					pCurrentCHRPool->getPool()->getRoundStatus(indexRound+1)<CHMemoryDataBase::eSchedulled)
					continue;
				if (repType==CHRC76::ePreliminarySummary &&
					pCurrentCHRPool->getPool()->getRoundStatus(indexRound+1)<CHMemoryDataBase::eRunning)
					continue;
				if (repType==CHRC76::eFinalSummary && pCurrentCHRPool->getPool()->getStatus()<CHMemoryDataBase::eRunning)
					continue;
				for (size_t k=indexTwice; k<size_t(pCurrentCHRPool->getTwice()); k++,indexTwice++)
				{
					for (size_t l=indexHeightTwice;l<size_t(pCurrentCHRPool->getHeightTwice()); l++,indexHeightTwice++)
					{
						if (pageBreak(short(pCurrentCHRPool->getHeight(l)/**(pCurrentCHRPool->getTwice()?2:1)*/)))
							return ok;

						if(pPhaseAnt!=pCurrentCHRPool->getPool()->getPhase() && pCurrentCHRPool->getNumRounds()==1)
						{
							pPhaseAnt=(CHPhase*)pCurrentCHRPool->getPool()->getPhase();
						}
						if( !pCurrentCHRPool->runLis(getCenter(), pReport->getYCoor()+(i*60), xPool,indexRound+1,k,l) )
							return error;
					}
					indexHeightTwice=0;
				}
				indexTwice=0;
			}
		}
	}
	return exit;	
}

unsigned short CHRC76::OnCallbackFn(struct USR_TAB * pTabInf)
{	
	if (pTabInf->Tb == 100 && pCurrentCHRPool)
		return pCurrentCHRPool->OnCallbackFn(pTabInf);

	return CHReportTemplate::OnCallbackFn(pTabInf);
}

RWDate CHRC76::OnGetEventDate() const
{
	return INVALID_RWDATE;
}

RWTime CHRC76::OnGetEventTime() const
{
	return INVALID_RWTIME;
}

RWCString CHRC76::OnGetPhaseCode() const
{
	return pCurrentCHRPool->getPool()->getPhaseCode();
}