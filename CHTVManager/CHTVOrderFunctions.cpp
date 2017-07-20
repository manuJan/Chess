/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: WUTVOrderFunctions.cpp
*	Description	:
*
*	Author		: 
*	Date created: 11-Dec-2009
* 	Project		: WU TV
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdafx.h"
#include "CHTVOrderFunctions.h"
#include "CHTVGroupInfo.h"

#include "..\CHMngtModel\CHPhase.h"
#include "..\CHMngtModel\CHMatch.h"
#include "..\CHMngtModel\CHPoolResult.h"
#include "..\CHMngtModel\CHMatchResult.h"
#include "..\CHMngtModel\CHEventResult.h"

int fnOrderRegByTVLName(const MSLItem** a, const MSLItem** b)
{
	GRegister	* pA = (GRegister *)(*a),
				* pB = (GRegister *)(*b);
	
	int dif=_wcsicoll(pA->getTvLName(),pB->getTvLName());
	return (dif)? dif : (pA->getRegister() - pB->getRegister());
}

int fnOrderPhaseByDateTime(const MSLItem** a, const MSLItem** b)
{
	CHPhase * pA = (CHPhase *)(*a),
			* pB = (CHPhase *)(*b);

				// Comparo Por Dia
	int order=pA->getStartDate().value() - pB->getStartDate().value();
	if (order)
		return order;
				// Comparo Por Hora
	order=pA->getStartTime().value() - pB->getStartTime().value();
	if (order) 
		return order;

	return strcmp(pA->getKey(),pB->getKey());
}
int fnOrderMatchByDateTime(const MSLItem** a, const MSLItem** b)
{
	CHMatch * pA = (CHMatch *)((MSLItem*)*a),
			* pB = (CHMatch *)((MSLItem*)*b);

	if( !pA->getStartDate().isValid() && pB->getStartDate().isValid() )
		return 1;
	if( !pB->getStartDate().isValid() && pA->getStartDate().isValid() )
		return -1;

	int order = pA->getStartDate().value() - pB->getStartDate().value();
	if( order )
		return order;

	// Order by Start Time.
	if( !pA->getStartTime().isValid() && pB->getStartTime().isValid() )
		return 1;
	if( !pB->getStartTime().isValid() && pA->getStartTime().isValid() )
		return -1;

	order = pA->getStartTime().value() - pB->getStartTime().value();
	if (order)
		return order;
		
	return strcmp(pA->getKey(),pB->getKey());
}


int fnOrderMatchResultByColor(const MSLItem** a, const MSLItem** b)
{
	CHMatchResult	* pA = (CHMatchResult *)((MSLItem*)*a),
					* pB = (CHMatchResult *)((MSLItem*)*b);

	return pA->getColor() - pB->getColor();
}

int fnOrderMatchResultByPhaseAndMatch(const MSLItem** a, const MSLItem** b)
{
	CHMatchResult	* pA = (CHMatchResult *)((MSLItem*)*a),
					* pB = (CHMatchResult *)((MSLItem*)*b);

	CHPhase * pPhaseA = (CHPhase * ) pA->getPhase();
	CHPhase * pPhaseB = (CHPhase * ) pB->getPhase();

	if (pPhaseA && pPhaseB)
	{
		int order = pPhaseA->getOrder() - pPhaseB->getOrder();
		if( order )
			return order;
	}
	
	return strcmp(pA->getKey(),pB->getKey());
}

int fnOrderKey(const MSLItem** a, const MSLItem** b)
{
	GData	* pA = (GData *)((MSLItem*)*a),
			* pB = (GData *)((MSLItem*)*b);
	return strcmp(pA->getKey(),pB->getKey());
}

int fnOrderEventResultByRankPo(const MSLItem** a, const MSLItem** b)
{
	CHEventResult	* pA = (CHEventResult *)((MSLItem*)*a),
					* pB = (CHEventResult *)((MSLItem*)*b);

	int orderA, orderB, order;
	orderA = pA->getQualitativeCode() == OK ? (pA->getRank() ? 1:2):3;
	orderB = pB->getQualitativeCode() == OK ? (pB->getRank() ? 1:2):3;
	order = orderA-orderB;
	if( order )
		return order;
	if( orderA == 1 )
		order = pA->getRank() - pB->getRank();
	if( !order )
		order = pA->getRankPo() - pB->getRankPo();
	if( order )
		return order;
	return wcscmp(pA->getPrnLName(),pB->getPrnLName());
}

int fnOrderMatchByMatchNumber(const MSLItem** a, const MSLItem** b)
{
	CHMatch * pA = (CHMatch *)((MSLItem*)*a),
			* pB = (CHMatch *)((MSLItem*)*b);

	int order = 0;
	// GCourt
	GCourt *pCourtA=(GCourt *)pA->getCourt();
	GCourt *pCourtB=(GCourt *)pB->getCourt();
	if (pCourtA && pCourtB)
		order=pCourtA->getCourt() - pCourtB->getCourt();
	else if (!pCourtA && !pCourtB)
		order=0;
	else if (!pCourtA)
		order=1;
	else if (!pCourtB)
		order=-1;

	if (order)
		return order;

	// Comparo Por Dia
	order = pA->getStartDate().value() - pB->getStartDate().value();
	if (order)
		return order;

	// Comparo Por Hora
	order=strcmp(pA->getStartTimeAsString("%H%M"),
				 pB->getStartTimeAsString("%H%M") );
	if (order) 
		return order;

	return pA->getMatchNumber() - pB->getMatchNumber();
}

int fnOrderMatchByInvPhaseAndCode(const MSLItem** a, const MSLItem** b)
{
	CHMatch * pA = (CHMatch *)((MSLItem*)*a),
			* pB = (CHMatch *)((MSLItem*)*b);
	
	int order = pA->getPhaseOrder()-pB->getPhaseOrder();
	if( order )
		return order;
	return pA->getCode() - pB->getCode();
}

int fnOrderTatamisByCode(const MSLItem** a, const MSLItem** b)
{
	GCourt* pA = (GCourt*)(*a);
	GCourt* pB = (GCourt*)(*b);

	int rc = pA->getCourt() - pB->getCourt();
	if (!rc)
		rc=strcmp(pA->getKey(),pB->getKey());

	return rc;
}

int fnOrderMatchByTatamiAndStatus(const MSLItem** a, const MSLItem** b)
{
	CHMatch* pMatchA=(CHMatch *)((MSLItem*)*a);
	CHMatch* pMatchB=(CHMatch *)((MSLItem*)*b);
	
	int rc = pMatchA->getCourtCode() - pMatchB->getCourtCode();
	if (rc)	return rc;
	
	unsigned char stA = pMatchA->getStatus();
	unsigned char stB = pMatchB->getStatus();

	// Primero running
	if (stA == CHMemoryDataBase::eRunning)
		return -1;
	if (stB == CHMemoryDataBase::eRunning)
		return 1;
	
	// Después unofficial
	if (stA == CHMemoryDataBase::eUnofficial)
		return -1;
	if (stB == CHMemoryDataBase::eUnofficial)
		return 1;
	rc = stA - stB;
	if (rc) return rc;

	return fnOrderMatchByDateTime(a,b);
}

int fnOrderMatchJudgeByPosition(const MSLItem** a, const MSLItem** b)
{
	GTHMatchJudge	* pA = (GTHMatchJudge *)((MSLItem*)*a),
					* pB = (GTHMatchJudge *)((MSLItem*)*b);

	return strcmp(pA->getPositionKey(),pB->getPositionKey());
}

int fnOrderMatchResultByRanking(const MSLItem** a, const MSLItem** b)
{
	CHMatchResult * pA=((CHMatchResult *)(*a));
	CHMatchResult * pB=((CHMatchResult *)(*b));

	if (pA->getQualitativeCode()!=OK && 
		pB->getQualitativeCode()!=OK)
	{
		GQualitative * pQA = pA->getQualitative();
		GQualitative * pQB = pB->getQualitative();
		if (pQA && pQB)
			return pQA->getSort() - pQB->getSort();
	}

	if (pA->getQualitativeCode()!=OK)
		return 1;

	if (pB->getQualitativeCode()!=OK)
		return -1;
	
	if (pA->getRankPo()==0 && pB->getRankPo()==0)
	{
		return strcmp(pA->getKey(),pB->getKey());
	}

	if (pA->getRankPo()==0)
		return 1;

	if (pB->getRankPo()==0)
		return -1;

	int rank=pA->getRankPo() - pB->getRankPo();
	if(rank)
		return rank;

	return strcmp(pA->getKey(),pB->getKey());
}

int fnOrderMembersByName(const MSLItem** a, const MSLItem** b)
{
	GMember *pA=(GMember *)(*a);
	GMember *pB=(GMember *)(*b);

	int order = _wcsicoll(pA->getPrnLName(),pB->getPrnLName());
	if( order )
		return order;

	return strcmp(pA->getKey(),pB->getKey());
}

int fnOrderPhasesByPhaseOrder(const MSLItem** a,const MSLItem** b)
{
	CHPhase *pA=(CHPhase *)(*a);
	CHPhase *pB=(CHPhase *)(*b);

	int order = pA->getOrder() - pB->getOrder();
	if (order)	
		return order;

	return strcmp(pA->getKey(), pB->getKey());
}

int fnOrderPoolResultsByRankPo(const MSLItem** a, const MSLItem** b)
{
	CHPoolResult * pPoolResultA = (CHPoolResult *)(*a);
	CHPoolResult * pPoolResultB = (CHPoolResult *)(*b);
	
	int order = pPoolResultA->getPoolCode() - pPoolResultB->getPoolCode();
	if( order )
		return order;

	if( pPoolResultA->getRankPo() || pPoolResultB->getRankPo() )
	{
		if( !pPoolResultA->getRankPo() )
			return 1;
		if( !pPoolResultB->getRankPo() )
			return -1;
		int order = pPoolResultA->getRankPo() - pPoolResultB->getRankPo();
		if( order )
			return order;
	}

	return pPoolResultA->getOrder() - pPoolResultB->getOrder();
}

int fnOrderGroupInfoByRankPo(const MSLItem** a, const MSLItem** b)
{
	CHTVGroupInfo * pA = (CHTVGroupInfo *)(*a);
	CHTVGroupInfo * pB = (CHTVGroupInfo *)(*b);
	
	int order = strcmp( pB->m_group , pA->m_group);
	if( order )
		return order;


	if( pA->m_displayPos || pB->m_displayPos )
	{
		if( !pA->m_displayPos )
			return 1;
		
		if( !pB->m_displayPos )
			return -1;

		int order = pA->m_displayPos - pB->m_displayPos;
		if( order )
			return order;
	}

	if( pA->m_rank || pB->m_rank )
	{
		if( !pA->m_rank )
			return 1;
		
		if( !pB->m_rank )
			return -1;

		int order = pA->m_rank - pB->m_rank;
		if( order )
			return order;
	}

	return strcmp( pA->getKey() , pB->getKey());
}