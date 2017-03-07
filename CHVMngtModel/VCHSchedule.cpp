/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: VCHSchedule.cpp
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
#include "VCHSchedule.h"
#include "CHViewsIDs.h"
#include "CHSessionPoolRound.h"
#include <Sports/CH/Data/CHMemoryDataBase.h>
#include <Sports/CH/Data/CHPhase.h>
#include <Sports/CH/Data/CHMatch.h>

int orderSessionPoolRound(const GVectorElement** a, const GVectorElement** b)
{
	CHSessionPoolRound * pSesA=(CHSessionPoolRound *)(*a)->getElement();
	CHSessionPoolRound * pSesB=(CHSessionPoolRound *)(*b)->getElement();
	// Compare date
	if( pSesA->getSessionStartDate()==NULLRWSTRING  &&
		pSesB->getSessionStartDate()==NULLRWSTRING  )
	{
		return strcmp(pSesA->getKey(),pSesB->getKey());
	}

	if( pSesA->getSessionStartDate()==NULLRWSTRING )
		return 1;
	if( pSesB->getSessionStartDate()==NULLRWSTRING )
		return -1;

	int order=strcmp(pSesA->getSessionStartDate("%Y%m%d"),
					 pSesB->getSessionStartDate("%Y%m%d"));

	if( order ) 
		return order;
	// Compare time
	if( pSesA->getSessionStartTime()==NULLRWSTRING )
		return 1;
	if( pSesB->getSessionStartTime()==NULLRWSTRING )
		return -1;

	if( pSesA->getSessionStartTime()==NULLRWSTRING &&
		pSesB->getSessionStartTime()==NULLRWSTRING )
	{
		return strcmp(pSesA->getKey(),pSesB->getKey());
	}

	order=strcmp(pSesA->getSessionStartTime(),
				 pSesB->getSessionStartTime() );
	if (order)
		return order;
	return pSesA->getRound() - pSesB->getRound();
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
VCHSchedule::VCHSchedule()
:CReportView(CHVDSCHEDULE_DEEP)
,count(0)
,countDate(0)
,ndate(0)
{
	build();
}

VCHSchedule::~VCHSchedule()
{
	colDateSessionPoolRound.clearAndDestroy();
}

RWCString VCHSchedule::getDescription() const
{
	return CHVDSCHEDULE_DESC;
}

int VCHSchedule::getID() const
{
	return CHVDSCHEDULE;
}

RWBoolean VCHSchedule::build()
{
	// Vector de Session Pool Round
	colDateSessionPoolRound.clearAndDestroy();
	ndate=0;
	for(size_t i=0; i<50; i++)
		dates[i]=0;
	
	RWSetIterator it(CHMemoryDataBase::getColMatchs());

	CHMatch *pMatchAux=0;
	while((pMatchAux=(CHMatch*)it())!=0)
	{
		if(!pMatchAux)
			continue;
		if (pMatchAux->getSubMatch()!=0)
			continue;
		if(pMatchAux->getStartDate().isValid() &&
		   pMatchAux->getSession())
		{
			CHPhase *pPhase=(CHPhase *)pMatchAux->getPhase();
			CHSession *pSession=(CHSession *)pMatchAux->getSession();
			CHPool *pPool=pPhase->getIsPool()?(CHPool *)pMatchAux->getPool():(CHPool *)pPhase->getPool(0);
			if (!pPool || !pSession)
				continue;
			CHSessionPoolRound *pAuxSesP=new CHSessionPoolRound(pSession,pPool,pMatchAux->getRound());
			CHSessionPoolRound *pSesP=(CHSessionPoolRound *)colDateSessionPoolRound.find(pAuxSesP);
			if (!pSesP)
			{
				colDateSessionPoolRound.insert(pAuxSesP);
			}
			else
				pSesP->setNumMatches();
		}
	}
	setDates();
	return true;
}

void VCHSchedule::setDates()
{
	GSortedVector vTmp(colDateSessionPoolRound,orderSessionPoolRound);
	RWDate aDate=INVALID_RWDATE;
	short count=0;
	for(size_t i=0; i<vTmp.entries(); i++)
	{
		CHSessionPoolRound *pSesP=(CHSessionPoolRound *)vTmp[i]->getElement();
		if (aDate!=pSesP->getStartDate())
		{
			dates[count++]=pSesP->getStartDate().julian();
			aDate=pSesP->getStartDate();
		}
	}
}

int VCHSchedule::loadNextDate()
{
	m_Vector.clearAndDestroy();
	GSortedVector vTmp(colDateSessionPoolRound,orderSessionPoolRound);
	RWDate aDate=INVALID_RWDATE;
	for(size_t i=0; i<vTmp.entries(); i++)
	{
		CHSessionPoolRound *pSesP=(CHSessionPoolRound *)vTmp[i]->getElement();
		aDate=RWDate(dates[countDate]);
		if (pSesP->getStartDate()==aDate)
		{
			m_Vector.insert(pSesP);
			count++;
		}
	}
	countDate++;
	vTmp.clearAndDestroy();
	if (m_Vector.entries())
	{
		vIndex.clearAndDestroy();
		vIndex.insert( new RWCollectableInt(-1) );

		return m_Vector.entries();
	}
	return -1;
}

RWDate VCHSchedule::getActualDate() const
{
	return RWDate(dates[countDate]);
}