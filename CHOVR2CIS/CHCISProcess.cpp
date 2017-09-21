/*************************************************************************************
*			© Copyright MSL Software, S.L., 2008
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHCISProcess.cpp
*	Description	:
*
*	Author		: Javier Juste
*	Date created: 28-03-2011
* 	Project		: BKOVR2CIS
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdafx.h"
#include "CHCISDefs.h"
#include "CHCISProcess.h"
#include "CHCISItemSchUnit.h"
#include "CHCISItemSchUnitResult.h"
#include "CHCISScreenBracket.h"
#include "CHCISScreenStartList.h"
#include "CHCISScreenResults.h"
#include "CHCISScreenPoolSummary.h"

#include <ovr\core\th\GTHMsgDefines.h>

#include "..\CHMngtModel\CHPhase.h"
#include "..\CHMngtModel\CHPool.h"
#include "..\CHMngtModel\CHMatch.h"
#include "..\CHMngtModel\CHDefinition.h"
#include "..\CHMngtModel\CHPoolResult.h"
#include "..\CHMngtModel\CHMatchResult.h"
#include "..\CHMngtModel\CHRegister.h"
	

#define __CISCHSCREEN_ROUND_STARTLIST_DESIGN					"CH.ROUND_STARTLIST"
#define __CISCHSCREEN_TEAM_ROUND_STARTLIST_DESIGN				"CH.TEAM_ROUND_STARTLIST"
#define __CISCHSCREEN_MATCH_STARTLIST_DESIGN					"CH.MATCH_STARTLIST"			
#define __CISCHSCREEN_TEAM_MATCH_STARTLIST_DESIGN				"CH.TEAM_MATCH_STARTLIST"
#define __CISCHSCREEN_ROUND_RESULTS_DESIGN						"CH.ROUND_RESULTS"
#define __CISCHSCREEN_TEAM_ROUND_RESULTS_DESIGN					"CH.ROUND_TEAM_RESULTS"
#define __CISCHSCREEN_MATCH_RESULTS_DESIGN						"CH.MATCH_RESULTS"	
#define __CISCHSCREEN_TEAM_MATCH_RESULTS_DESIGN					"CH.TEAM_MATCH_RESULTS"
#define __CISCHSCREEN_BRACKET_DESIGN							"CH.BRACKETS"

CHCISProcess * CHCISProcess::chProcess = 0;

static 
int orderPoolResultsByRank(const MSLItem **a, const MSLItem **b)
{
	CHPoolResult *pPRA = (CHPoolResult *) (*a);
	CHPoolResult *pPRB = (CHPoolResult *) (*b);

	if(pPRA->getQualitativeCode()!=OK)
		return 1;

	if(pPRB->getQualitativeCode()!=OK)
		return -1;

	if(!pPRA->getRankPo() && pPRB->getRankPo())
		return 1;

	if(pPRA->getRankPo() && !pPRB->getRankPo())
		return -1;

	int order = pPRA->getRankPo() - pPRB->getRankPo();
	if (order)
		return order;

	order=pPRA->getOrder()-pPRB->getOrder();
	if (order)
		return order;

	return strcmp(pPRA->getKey(), pPRB->getKey());
}

static 
int orderRefereesByPosition(const MSLItem** a, const MSLItem** b)
{
	GTHMatchJudge * pMatchJudgeA = (GTHMatchJudge *) (*a);
	GTHMatchJudge * pMatchJudgeB = (GTHMatchJudge *) (*b);

	int order = pMatchJudgeA->getFunctionCode() - pMatchJudgeB->getFunctionCode();
	if (order)
		return order;

	order = pMatchJudgeA->getPositionCode() - pMatchJudgeB->getPositionCode();
	if (order)
		return order;
		
	return wcscmp(pMatchJudgeA->getPrnSName(),pMatchJudgeB->getPrnSName());
}

CHCISProcess::CHCISProcess()
:GTHCISProcess()
{
	chProcess = this;
}

CHCISProcess::~CHCISProcess()
{
}

bool CHCISProcess::onCreateScreens(long idScreen)
{
	if (idScreen==__CISTHSCREEN_PLAYER_RESULTS)
		return false;

	return GTHCISProcess::onCreateScreens(idScreen);
}

MSLString CHCISProcess::getScreenDesign(long idScreen, GData* pData/*=0*/)
{
		switch (idScreen)
	{
		case __CISTHSCREEN_STARTLIST			:	
			
			if (pData && pData->isA()==__CHMATCH)
			{
				CHMatch* pMatch = (CHMatch*)pData;
				if (pMatch->getIsPool())
					return __CISCHSCREEN_ROUND_STARTLIST_DESIGN;		
				else if (!pMatch->isTeam())
					return __CISCHSCREEN_MATCH_STARTLIST_DESIGN;		
				else
					return __CISCHSCREEN_TEAM_MATCH_STARTLIST_DESIGN;							
			}	
		
		case __CISTHSCREEN_TEAM_RESULTS			:	
		{
			if (pData && pData->isA()==__CHMATCH)
			{
				CHMatch* pMatch = (CHMatch*)pData;
				if (pMatch->getIsPool())
					return __CISCHSCREEN_ROUND_RESULTS_DESIGN;		
				else if (!pMatch->isTeam())
					return __CISCHSCREEN_MATCH_RESULTS_DESIGN;		
				else
					return __CISCHSCREEN_TEAM_MATCH_RESULTS_DESIGN;							
			}
		}
	}
	return GTHCISProcess::getScreenDesign(idScreen, pData);
}

GCISScreen	* CHCISProcess::onNewScreen(long idScreen, MSLString key, MSLString name, MSLString designFile, GData * pData/*=0*/)
{
	switch( idScreen )
	{
		case __CISTHSCREEN_STARTLIST:
		{
			if (pData && pData->isA()==__GTHMATCH)
			{
				return new CHCISScreenStartList(key,name,designFile,pData);			
			}
			break;
		}

		case __CISTHSCREEN_TEAM_RESULTS:
		{
			if (pData && pData->isA()==__GTHMATCH)
			{
				return new CHCISScreenResults(key,name,designFile,pData);
			}
			break;
		}
		case __CISTHSCREEN_BRACKET:
		{
			if (pData && pData->isA()==__GTHEVENT)
				return new CHCISScreenBracket(key,name,designFile,(GTHEvent*)pData);						
			break;
		}
		case __CISTHSCREEN_POOLSUMMARY:
		{
			if (pData && pData->isA()==__GTHPHASE)
				return new CHCISScreenPoolSummary(key,name,designFile,(GTHPhase*)pData);		
		}
	}
	
	return GTHCISProcess::onNewScreen(idScreen,key,name,designFile,pData);
}

void CHCISProcess::fillColItems(long idItem, MSLSet & col)
{
	switch (idItem)
	{
		case __CISITEM_SCHEDULE_UNIT:
		{
			MSLSetIterator iter(CHMemoryDataBase::getCol(__CHPOOL));
			CHPool * pPool = 0;
			while( (pPool = (CHPool *)iter())!=0 )
			{
				if (pPool->getPhaseCode()==SWISS_ROUND)
				{
					short nRounds = pPool->getNumRounds();
					for (short i=1;i<=nRounds;i++)
					{
						MSLSortedVector vRoundMatches;
						pPool->getRoundMatchesVector(vRoundMatches,i);
						if (vRoundMatches.entries())
						{														
							col.insert(vRoundMatches[vRoundMatches.entries()-1]);
						}
					}
				}
				else
				{
					MSLSortedVector vMatches;
					pPool->getMatchesVector(vMatches);
					for (short i=0;i<vMatches.entries();i++)
					{
						CHMatch* pMatch = (CHMatch*)vMatches[i];
						if (pMatch->getSubCode())
							continue;

						col.insert(pMatch);
					}
				}
			}
			
			break;
		}
		case __CISITEM_SCHEDULE_UNIT_RES:
		{
			MSLSetIterator it(GTHMemoryDataBase::getCol(__GTHMATCHRESULT));
			GTHMatchResult * pMatchResult = 0;
			while( (pMatchResult = (GTHMatchResult *)it())!=0 )
			{
				if (pMatchResult->getPhaseCode()!=SWISS_ROUND)
					col.insert(pMatchResult);
			}
			break;
		}		
	}

	GCISProcess::fillColItems(idItem,col);
}

GCISItem * CHCISProcess::onNewItem(GData * pData, long idItem)
{
	switch (idItem)
	{
		case __CISITEM_SCHEDULE_UNIT:
		{
			if (pData && pData->isA()==__CHMATCH)
			{
				CHMatch * pMatch = (CHMatch *)pData;
				if (pMatch->getSubCode()!=0)
					return 0;

				CHPool* pPool = (CHPool* ) pMatch->getPool();
				if (pPool->getPhaseCode()==SWISS_ROUND)
				{
					MSLSortedVector vRoundMatches;						
					pPool->getRoundMatchesVector(vRoundMatches,pMatch->getRound());
					if (!vRoundMatches.entries())
						return 0;

					CHMatch * pRoundMatch = (CHMatch * ) vRoundMatches[vRoundMatches.entries()-1];
					if (!pRoundMatch || pRoundMatch->getKey()!=pMatch->getKey())
						return 0;
				}

				CHCISItemSchUnit* pCISSchUnitItem = new CHCISItemSchUnit(pData);
				return pCISSchUnitItem;
			}
		}
		case __CISITEM_SCHEDULE_UNIT_RES:
		{
			if (pData && pData->isA()==__CHMATCHRESULT)
			{
				CHMatchResult * pMatchResult = (CHMatchResult *)pData;
				if (pMatchResult->getMatchSubCode()!=0)
					return 0;				

				CHMatch * pMatch = (CHMatch*) pMatchResult->getMatch();
				if (!pMatch)
					return 0;

				CHPool* pPool = (CHPool* ) pMatchResult->getPool();
				if (pPool->getPhaseCode()==SWISS_ROUND)
				{
					return 0;
				}

				CHCISItemSchUnitResult* pCISSchUnitResultItem = new CHCISItemSchUnitResult(pData);
				return pCISSchUnitResultItem;
			}
		}		
	}
	return GTHCISProcess::onNewItem(pData, idItem);
}

void CHCISProcess::setRefRegister(GRegister * pRegister, MSLString lang, bool bInsert)
{
	GTHCISProcess::setRefRegister(pRegister, lang, bInsert);

	setRef(pRegister, REF_TITLE_SDESC, getDataRefW(pRegister,REF_TITLE_SDESC,lang,bInsert), lang, bInsert);
	setRef(pRegister, REF_TITLE_LDESC, getDataRefW(pRegister,REF_TITLE_LDESC,lang,bInsert), lang, bInsert);

}

void CHCISProcess::setRefSchUnitResult(GCISItemSchUnitResult * pCISScheduleUnitResult, MSLString lang, bool bInsert)
{
	GTHCISProcess::setRefSchUnitResult(pCISScheduleUnitResult, lang, bInsert);
}

void CHCISProcess::setRefMatch(GTHMatch* pMatch, MSLString lang, bool bInsert)
{
	setRef(pMatch, REF_START_DATE		, pMatch->getStartDateAsString("%#d %b %Y",lang),lang,bInsert);
	setRef(pMatch, REF_START_DATE_SDESC	, msl_toUpper(pMatch->getStartDateAsString("%#d %b",lang)),lang,bInsert);
	setRef(pMatch, REF_START_TIME		, pMatch->getStartTimeAsString("%#H:%M"),lang,bInsert);
	setRef(pMatch, REF_END_DATE			, pMatch->getEndDateAsString("%#d %b %Y",lang),lang,bInsert);	
	setRef(pMatch, REF_END_TIME			, pMatch->getEndTimeAsString("%#H:%M"),lang,bInsert);	
	setRef(pMatch, REF_VENUE			, pMatch->getVenueKey(),lang,bInsert); 
	setRef(pMatch, REF_COURT			, pMatch->getCourtKey(),lang,bInsert); 
	setRef(pMatch, REF_MATCH_NUMBER		, pMatch->getMatchNumber(),lang,bInsert);
	setRef(pMatch, REF_STATUS			, getRoundStatus((CHMatch*)pMatch),lang,bInsert);
	setRef(pMatch, REF_RESULT, getDataRef(pMatch, REF_RESULT, lang, bInsert),lang, bInsert);	
}

void CHCISProcess::setRefMatchResult(GTHMatchResult* pMatchResult , MSLString lang, bool bInsert)
{
	GTHCISProcess::setRefMatchResult(pMatchResult, lang, bInsert);

	setRef(pMatchResult, REF_SEED			, getDataRef(pMatchResult, REF_SEED		,lang, bInsert),lang, bInsert);
	setRef(pMatchResult, REF_TITLE			, getDataRef(pMatchResult, REF_TITLE	,lang, bInsert),lang, bInsert);
	setRef(pMatchResult, REF_PREV_PTS		, getDataRef(pMatchResult, REF_PREV_PTS	,lang, bInsert),lang, bInsert);
	setRef(pMatchResult, REF_OPPRK_RESULT	, getDataRef(pMatchResult, REF_OPPRK_RESULT	,lang, bInsert),lang, bInsert);
	setRef(pMatchResult, REF_POINTS_F		, getDataRef(pMatchResult, REF_POINTS_F ,lang, bInsert),lang, bInsert);

}

void CHCISProcess::setRefPoolResult(GTHPoolResult* pPoolResult, MSLString lang, bool bInsert)
{
	GTHCISProcess::setRefPoolResult(pPoolResult, lang, bInsert);

	setRef(pPoolResult, REF_MATCHESPLAYED	, getDataRef(pPoolResult, REF_MATCHESPLAYED, lang, bInsert), lang, bInsert);
	setRef(pPoolResult, REF_MATCHESWON		, getDataRef(pPoolResult, REF_MATCHESWON, lang, bInsert), lang, bInsert);
	setRef(pPoolResult, REF_MATCHESTIES		, getDataRef(pPoolResult, REF_MATCHESTIES, lang, bInsert), lang, bInsert);
	setRef(pPoolResult, REF_MATCHESLOST		, getDataRef(pPoolResult, REF_MATCHESLOST, lang, bInsert), lang, bInsert);
	setRef(pPoolResult, REF_POINTS_F		, getDataRef(pPoolResult, REF_POINTS_F, lang, bInsert), lang, bInsert);
	setRef(pPoolResult, REF_MATCH_POINTS	, getDataRef(pPoolResult, REF_MATCH_POINTS, lang, bInsert), lang, bInsert);
}


MSLString CHCISProcess::getDataRef(GData* pData, MSLString reference, MSLString lang, bool bInsert)
{
	if (!pData)
		return NULLWSTRING;

	if (pData->isA()==__CHMATCH)
		return getDataRefMatch((CHMatch*)pData, reference,lang,bInsert);
	
	if (pData->isA()==__CHMATCHRESULT)
		return getDataRefMatchResult((CHMatchResult*)pData, reference,lang,bInsert);

	if (pData->isA()==__CHPOOLRESULT)
		return getDataRefPoolResult((CHPoolResult*)pData, reference,lang,bInsert);		   	
	
	if (pData->isA()==__CISITEM_SCHEDULE_UNIT_RES)
		return getDataRefScheduleUnitRes((GCISItemSchUnitResult*)pData, reference,lang,bInsert);

	return NULLSTRING;
}

MSLWString CHCISProcess::getDataRefW(GData* pData, MSLString reference, MSLString lang, bool bInsert)
{
	if (!pData)
		return NULLWSTRING;
		
	if (pData->isA()==__CHREGISTER)
		return getDataRefWRegister((CHRegister*)pData, reference,lang,bInsert);

	return NULLWSTRING;
	UNREFERENCED_PARAMETER(bInsert);
}

MSLWString CHCISProcess::getDataRefWRegister(CHRegister* pRegister, MSLString reference, MSLString lang, bool bInsert)
{
	if (reference==REF_TITLE_SDESC)
		return pRegister->getMasterTypeSDescription();
	if (reference==REF_TITLE_LDESC)
		return pRegister->getMasterTypeLDescription();
	return NULLWSTRING;
}

MSLString CHCISProcess::getDataRefMatch(CHMatch* pMatch, MSLString reference, MSLString lang, bool bInsert)
{
	if (reference==REF_RESULT)
		return pMatch->getResultAsString();

	return NULLSTRING;
	UNREFERENCED_PARAMETER(bInsert);
}

MSLString CHCISProcess::getDataRefMatchResult(CHMatchResult* pMatchResult, MSLString reference, MSLString lang, bool bInsert)
{
	if (reference==REF_SEED)
		return pMatchResult->getSeedAsString();
	if (reference==REF_PREV_PTS)
	{
		CHPoolResult * pPR = (CHPoolResult * ) pMatchResult->getPoolResult();
		return pPR ? pPR->getPoolPointsFStr(pMatchResult->getMatchRound()) : "";
	}
	if (reference==REF_OPPRK_RESULT)
	{
		MSLString desc="";
		CHMatchResult * pOpponent = (CHMatchResult * )pMatchResult->getOpponent();
		if (pOpponent && pOpponent->getPoolResult())
		{
			CHPoolResult * pPR = (CHPoolResult*) pOpponent->getPoolResult();
			desc = "(" + TOSTRING(pPR->getRank(),"") + ") ";
		}
				
		desc += pMatchResult->getPointsAsString();
		desc += "-";
		desc += pOpponent->getPointsAsString();
		return desc;
	}
	if (reference==REF_POINTS_F)
	{
		return pMatchResult->getPointsAsString();
	}

	return NULLSTRING;
	UNREFERENCED_PARAMETER(bInsert);
}

MSLString CHCISProcess::getDataRefScheduleUnitRes(GCISItemSchUnitResult* pItemSchUnitResult, MSLString reference, MSLString lang, bool bInsert)
{
	return NULLSTRING;
	UNREFERENCED_PARAMETER(bInsert);
}

MSLString CHCISProcess::getDataRefPoolResult(CHPoolResult* pPoolResult, MSLString reference, MSLString lang, bool bInsert)
{
	if (reference==REF_MATCHESPLAYED)
		return TOSTRING(pPoolResult->getMPlayed(),"0");
	if (reference==REF_MATCHESWON)
		return TOSTRING(pPoolResult->getMWon(),"0");	
	if (reference==REF_MATCHESTIES)
		return TOSTRING(pPoolResult->getMDrawn(),"0");	
	if (reference==REF_MATCHESLOST)
		return TOSTRING(pPoolResult->getMLost(),"0");	
	if (reference==REF_POINTS_F)
		return pPoolResult->getPointsFStr();
	if (reference==REF_MATCH_POINTS)
		return pPoolResult->getMatchPointsStr();

	return NULLSTRING;
	UNREFERENCED_PARAMETER(bInsert);
}

MSLWString CHCISProcess::getMatchSDescription(CHMatch *pMatch, const char * lang)
{
	CHDefinition &aDef = (CHDefinition &)CHMemoryDataBase::getDefinition();
	MSLWString desc = NULLWSTRING;	
	CHEvent * pEvent = (CHEvent * )pMatch->getEvent();
	if (pEvent)
	{
		desc += pEvent->getLDescription(lang);
	}

	CHPhase *pPhase = (CHPhase *) pMatch->getPhase();
	if (pPhase)
	{		
		if (!pPhase->getIsPool())
		{
			desc += L", ";
			desc += pPhase->getLDescription(lang);
		}
	}
	if (pEvent->isTeam())
	{
		if (pPhase->getIsPool())
		{
			desc += L", ";
			desc += pMatch->getRoundAsString(true,false);
		}			
		else
		{
			desc += L" ";
			desc += aDef.getSMatchDescription(lang);
			desc += L" ";
			desc += TOWSTRING(pMatch->getCode());
		}		
	}
	else
	{
		if (pPhase->getIsPool())
		{
			desc += L", ";
			desc += pMatch->getRoundAsString(true,false);
		}
		else 
		{
			desc += L" ";
			desc += aDef.getSMatchDescription(lang);
			desc += L" ";
			desc += TOWSTRING(pMatch->getMatchNumber());
		}
	}

	return desc;
}

MSLWString CHCISProcess::getMatchLDescription(CHMatch *pMatch, const char * lang)
{
	CHDefinition &aDef = (CHDefinition &)CHMemoryDataBase::getDefinition();
	MSLWString desc = NULLWSTRING;	
	CHEvent * pEvent = (CHEvent * )pMatch->getEvent();
	if (pEvent)
	{
		desc += pEvent->getLDescription(lang);
	}

	CHPhase *pPhase = (CHPhase *) pMatch->getPhase();
	if (pPhase)
	{
		desc += L", ";
		if (!pPhase->getIsPool())
			desc += pPhase->getLDescription(lang);
	}
	if (pEvent->isTeam())
	{
		if (pPhase->getIsPool())
		{
			desc += L", ";
			desc += pMatch->getRoundAsString(true,false);
		}			
		else
		{
			desc += L" ";
			desc += aDef.getSMatchDescription(lang);
			desc += L" ";
			desc += TOWSTRING(pMatch->getCode());
		}		
	}
	else
	{
		if (pPhase->getIsPool())
		{
			desc += L", ";
			desc += pMatch->getRoundAsString(true,false);
		}
		else 
		{
			desc += L" ";
			desc += aDef.getSMatchDescription(lang);
			desc += L" ";
			desc += TOWSTRING(pMatch->getMatchNumber());
		}
	}

	return desc;
}

bool CHCISProcess::isTrnScheduleChange(long idTrn)
{
	return (idTrn==TRN_CHANGE_MATCH_STATUS);
}


mslToolsFcCompare CHCISProcess::getOrderPoolResults(long idScreen, GData* pData)
{
	return orderPoolResultsByRank;
	UNREFERENCED_PARAMETER(idScreen);
	UNREFERENCED_PARAMETER(pData);
}

mslToolsFcCompare CHCISProcess::getOrderReferees(long idScreen, GData* pData)
{
	return orderRefereesByPosition;
	UNREFERENCED_PARAMETER(idScreen);
	UNREFERENCED_PARAMETER(pData);
}

unsigned char CHCISProcess::getRoundStatus(CHMatch * pMatch)
{
	unsigned char status = GMemoryDataBase::eSchedulled;
	if( pMatch && pMatch->getRound()>0 )
	{
		MSLSortedVector vRdMatches = pMatch->getRoundMatches();
		CHMatch * pM = 0;
		unsigned char statusHigh = GMemoryDataBase::eSchedulled, statusLow = GMemoryDataBase::eProtested;
		for(int i=0;i<int(vRdMatches.entries());i++)
		{
			pM = (CHMatch*)vRdMatches[i];
			if( pM )
			{
				if( pM->getStatus()>statusHigh)
					statusHigh = pM->getStatus();
				else if( pM->getStatus()<statusLow )
					statusLow = pM->getStatus();
			}
		}
		if( statusLow==GMemoryDataBase::eRunning || statusLow==statusHigh )
			return statusLow;
		else if( statusHigh==GMemoryDataBase::eProtested )
			return statusHigh;
		else
			return statusLow;
	}
	return status;
}