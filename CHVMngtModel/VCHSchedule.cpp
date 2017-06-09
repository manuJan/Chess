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
#include "stdafx.h"
#include "VCHSchedule.h"
#include "CHSessionPoolRound.h"

#include "..\CHMngtModel\CHPhase.h"
#include "..\CHMngtModel\CHMatch.h"

int orderSessionPoolRound(const MSLItem** a, const MSLItem** b)
{
	CHSessionPoolRound * pSesA=(CHSessionPoolRound *)(*a);
	CHSessionPoolRound * pSesB=(CHSessionPoolRound *)(*b);
	// Compare date
	if( pSesA->getSessionStartDate()==NULLSTRING  &&
		pSesB->getSessionStartDate()==NULLSTRING  )
	{
		return strcmp(pSesA->getKey(),pSesB->getKey());
	}

	if( pSesA->getSessionStartDate()==NULLSTRING )
		return 1;
	if( pSesB->getSessionStartDate()==NULLSTRING )
		return -1;

	int order=strcmp(pSesA->getSessionStartDate("%Y%m%d"),
					 pSesB->getSessionStartDate("%Y%m%d"));

	if( order ) 
		return order;
	// Compare time
	if( pSesA->getSessionStartTime()==NULLSTRING )
		return 1;
	if( pSesB->getSessionStartTime()==NULLSTRING )
		return -1;

	if( pSesA->getSessionStartTime()==NULLSTRING &&
		pSesB->getSessionStartTime()==NULLSTRING )
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
:m_count(0)
,m_countDate(0)
,m_ndate(0)
{
	build();
}

VCHSchedule::~VCHSchedule()
{
	m_colDateSessionPoolRound.clearAndDestroy();
}

CHSessionPoolRound * VCHSchedule::getData(short index)
{
	return (CHSessionPoolRound * ) m_vector[index];
}

short VCHSchedule::getEntries()
{
	return m_vector.entries();
}

bool VCHSchedule::build()
{
	// Vector de Session Pool Round
	m_colDateSessionPoolRound.clearAndDestroy();
	m_ndate=0;
	for(size_t i=0; i<50; i++)
		m_dates[i]=0;
	
	MSLSetIterator it(CHMemoryDataBase::getCol(__CHMATCH));

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
			GSession *pSession=(GSession *)pMatchAux->getSession();
			CHPool *pPool=pPhase->getIsPool()?(CHPool *)pMatchAux->getPool():(CHPool *)pPhase->getPool(0);
			if (!pPool || !pSession)
				continue;
			CHSessionPoolRound *pAuxSesP=new CHSessionPoolRound(pSession,pPool,pMatchAux->getRound());
			CHSessionPoolRound *pSesP=(CHSessionPoolRound *)m_colDateSessionPoolRound.find(pAuxSesP);
			if (!pSesP)
			{
				m_colDateSessionPoolRound.insert(pAuxSesP);
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
	MSLSortedVector vTmp(m_colDateSessionPoolRound,orderSessionPoolRound);
	MSLDate aDate=INVALID_DATE;
	short count=0;
	for(short i=0; i<vTmp.entries(); i++)
	{
		CHSessionPoolRound *pSesP=(CHSessionPoolRound *)vTmp[i];
		if (aDate!=pSesP->getStartDate())
		{
			m_dates[count++]=pSesP->getStartDate().value();
			aDate=pSesP->getStartDate();
		}
	}
}

int VCHSchedule::loadNextDate()
{
	m_vector.clear();
	MSLSortedVector vTmp(m_colDateSessionPoolRound,orderSessionPoolRound);
	MSLDate aDate=INVALID_DATE;
	for(short i=0; i<vTmp.entries(); i++)
	{
		CHSessionPoolRound *pSesP=(CHSessionPoolRound *)vTmp[i];
		aDate=MSLDate(m_dates[m_countDate]);
		if (pSesP->getStartDate()==aDate)
		{
			m_vector.insert(pSesP);
			m_count++;
		}
	}
	m_countDate++;
	vTmp.clear();
	if (m_vector.entries())
		return m_vector.entries();
	
	return -1;
}

MSLDate VCHSchedule::getActualDate() const
{
	return MSLDate(m_dates[m_countDate]);
}