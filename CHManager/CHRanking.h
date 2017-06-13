/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHRanking.h
*   Description : 
*
*   Author      : Javier Juste
*   Date created: 22-FEb-2009
*   Project     : AR Manager
*
*   Modification history
*   By      :
*   Date    :
*   Changes :
*
*****************************************************************************************/

#pragma once
#include "CHManagerDefs.h"
#include <OVR/gui/GUITHMANAGER/GTHRanking.h>

class CHPhase;
class CHEventResult;
class CHPoolResult;
class CHMatch;
class CHMatchResult;

class CHRanking : public GTHRanking
{
public:
	CHRanking(MSLGUIEx* pGUIEx);
	virtual ~CHRanking();

	void setRankings									(GData  * pData, bool tie);
	void setRankings									(CHEventResult		* pEventResult , bool tie);
		
	// Best NOC Players
	
	void setEventRankings								(CHEventResult	* pEventResult, short rank, short rankPo);
	void setRankings									(GTHMatchResult  * pMatchResult , bool tie);
	
	void onSetMatchRankings								(GTHMatchResult	* pMatchResult, short rank, short rankPo);
	void onSetPoolRankings								(GTHPoolResult	* pPoolResult , short rank, short rankPo);
	void onSetPhaseRankings								(GTHPoolResult	* pPoolResult , short rank, short rankPo);

	void postCalculateRankings							(GData* pData, MSLSortedVector vResults);
	void postCalculateMatchRankings						(CHMatch* pMatch, MSLSortedVector vResults);

	void getColResults									(GData* pData, MSLSet& colResults);
	short getEventRank									(CHEventResult *pEventResult, CHPoolResult *pPoolResult, short rank);

	// Data Rankings
	mslToolsFcSelect getValidResultsFunction			(GData* pData);

	mslToolsFcCompare getSortResults					(GData* pData);
	mslToolsFcCompare getSortResultsNoTies				(GData* pData);
	mslToolsFcCompare getSortResults2Ties				(GData* pData);
	mslToolsFcCompare getSortResults3Ties				(GData* pData);
	mslToolsFcCompare getSortResultsTotal				(GData* pData);

	mslToolsFcCompare getCompResults					(GData* pData);
	mslToolsFcCompare getCompResultsNoTies				(GData* pData);
	mslToolsFcCompare getCompResults2Ties				(GData* pData);
	mslToolsFcCompare getCompResults3Ties				(GData* pData);
	mslToolsFcCompare getCompResultsTotal				(GData* pData);

	// Match Rankings
	mslToolsFcCompare getSortMatchResults				(GTHMatch* pMatch);
	mslToolsFcCompare getSortMatchResultsNoTies			(GTHMatch* pMatch);
	mslToolsFcCompare getSortMatchResults2Ties			(GTHMatch* pMatch);
	mslToolsFcCompare getSortMatchResults3Ties			(GTHMatch* pMatch);
	mslToolsFcCompare getSortMatchResultsTotal			(GTHMatch* pMatch);
	mslToolsFcCompare getCompMatchResults				(GTHMatch* pMatch);
	mslToolsFcCompare getCompMatchResultsNoTies			(GTHMatch* pMatch);
	mslToolsFcCompare getCompMatchResults2Ties			(GTHMatch* pMatch);
	mslToolsFcCompare getCompMatchResults3Ties			(GTHMatch* pMatch);
	mslToolsFcCompare getCompMatchResultsTotal			(GTHMatch* pMatch);

	void resetMatchData									(GTHMatch* pMatch, MSLSortedVector vMatchResults, bool send);
	bool preAcumulateMatchData							(GTHMatchResult* pMatchResult);
	
	// Pool Rankings
	mslToolsFcCompare getSortPoolResults						(GTHPool* pPool);
	mslToolsFcCompare getSortPoolResultsNoTies					(GTHPool* pPool);
	mslToolsFcCompare getSortPoolResults2Ties					(GTHPool* pPool);
	mslToolsFcCompare getSortPoolResults3Ties					(GTHPool* pPool);
	mslToolsFcCompare getSortPoolResultsTotal					(GTHPool* pPool);
	mslToolsFcCompare getCompPoolResults						(GTHPool* pPool);
	mslToolsFcCompare getCompPoolResultsNoTies					(GTHPool* pPool);
	mslToolsFcCompare getCompPoolResults2Ties					(GTHPool* pPool);
	mslToolsFcCompare getCompPoolResults3Ties					(GTHPool* pPool);
	mslToolsFcCompare getCompPoolResultsTotal					(GTHPool* pPool);

	mslToolsFcSelect  getValidPoolResultsFunction				(GTHPool* pPool);

	bool preAcumulatePoolData									(MSLSortedVector vResults, GTHPoolResult* pPoolResult, GTHMatchResult* pMatchResult);
	void userResetPoolResultData								(GTHPoolResult* pPoolResult, bool send);
	void userAcumulatePoolData									(GTHPoolResult* pPoolResult, GTHMatchResult* pMatchResult);

	// Phase Rankings
	mslToolsFcCompare getSortPoolResultsPhase					(GTHPhase* pPhase);
	mslToolsFcCompare getSortPoolResultsPhaseNoTies				(GTHPhase* pPhase);
	mslToolsFcCompare getSortPoolResultsPhase2Ties				(GTHPhase* pPhase);
	mslToolsFcCompare getSortPoolResultsPhase3Ties				(GTHPhase* pPhase);
	mslToolsFcCompare getSortPoolResultsPhaseTotal				(GTHPhase* pPhase);
	mslToolsFcCompare getCompPoolResultsPhase					(GTHPhase* pPhase);
	mslToolsFcCompare getCompPoolResultsPhaseNoTies				(GTHPhase* pPhase);
	mslToolsFcCompare getCompPoolResultsPhase2Ties				(GTHPhase* pPhase);
	mslToolsFcCompare getCompPoolResultsPhase3Ties				(GTHPhase* pPhase);
	mslToolsFcCompare getCompPoolResultsPhaseTotal				(GTHPhase* pPhase);

	mslToolsFcSelect  getValidPoolResultsPhaseFunction			(GTHPhase* pPhase);

	bool preAcumulateMatchData									(MSLSortedVector vResults, GTHMatchResult* pMatchResult);
	bool onPerfectTie											(GData* pData, MSLSortedVector vTiesResults);
	bool isValidData											(GData* pData);

	// Ranking Round Tie
	int getNumByes												(CHPhase *pPhase);

	void onMedallistCreated										(GMedallist * pMedallist);

private:

	bool m_bLastRkCalculation;
	int  m_rankCH;
	int  m_rankPoCH;
	int  m_tiesCH;
};
