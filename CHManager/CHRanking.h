/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHRanking.h
*	Description	: Interface for the CHRanking class.
*
*	Author		: CH Team
*	Date created: 20-12-2005
* 	Project		: CHManager
*	
* 	Modification history
*	By			: 
*	Date		: 
*	Changes		: 
*
***************************************************************************************/

#if !defined(AFX_CHRANKING_H__29D5871F_1112_4B9D_9D2D_C998B2BD8030__INCLUDED_)
#define AFX_CHRANKING_H__29D5871F_1112_4B9D_9D2D_C998B2BD8030__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Sports\CH\Data\CHMemoryDataBase.h>
////////////////////////////////////////////////////////////////////////////////////
// class CHTieRankingPoolResult
////////////////////////////////////////////////////////////////////////////////////

class CHTieRankingPoolResult : public CHPoolResult
{
public:
	CHTieRankingPoolResult();
	CHTieRankingPoolResult(CHPoolResult *pPR);
	CHTieRankingPoolResult(const CHTieRankingPoolResult & copy);
	virtual ~CHTieRankingPoolResult();

	CHTieRankingPoolResult &	operator  = (const CHTieRankingPoolResult & copy);
	RWBoolean					operator == (const CHTieRankingPoolResult & copy);
	RWBoolean					operator != (const CHTieRankingPoolResult & copy);

	void						setMatchesTie(const int aMatchesTie);
	void						setPointsTie(const float aPointsTie);
	

	int							getMatchesTie() const;
	float						getPointsTie() const;
	

private:
	int							matchesTie;
	float						pointsTie;
	
};

////////////////////////////////////////////////////////////////////////////////////
// class CHRanking
////////////////////////////////////////////////////////////////////////////////////

class CHRanking
{
public:
	CHRanking();
	virtual ~CHRanking();

	void						calculateMedals(CHMatch* pMatch,CHEvent* pEvent); 
	void						calculateRankings(CHMatch* pMatch);
	void						calculateRankingsMatch(CHMatch* pMatch);
	void						calculateRankingsEvent(CHEvent* pEvent);
	void						calculateRankingsPhase(CHPhase* pPhase);
	void						calculateRankingsPool(CHPool* pPool);
	void						assignPointsMatchResult(CHMatch* pMatch);
	void						reCalculateSpecialPointsPool(CHMatch* pMatch);

private:
	
	void						destroyAllMedals(CHEvent* pEvent);
	void						tieBreakPool(CHPool *pPool);
	void						calculateTieValues(CHTieRankingPoolResult* pTiePR);
	void						HomeWin_AwayLoss(CHMatchResult *pHome,CHMatchResult *pAway);
	void						HomeLoss_AwayWin(CHMatchResult *pHome,CHMatchResult *pAway);
	void						HomeAwayDraw(CHMatchResult *pHome,CHMatchResult *pAway);
	void						sendToDB(CHMatchResult * pMatchResult);
	void						setMedallist(CHMatch* pMatch, CHEventResult * pEventResult,short medal);
	CHTieRankingPoolResult *	findTie	(GSortedVector &vAuxTieValues,GInscription *pIns);
	CHMatchResult *				findRankMatchResult	(CHEvent * pEvent,RWCString phase,short ranking);
	CHEventResult *				findRankEventResult(CHEvent * pEvent,short ranking);
	CHMatchResult *				findLastMatchResult (CHRegister* pRegister,GSortedVector& vMatchResults);
	RWBoolean					usedToCalculate(CHEvent* pEvent,short type);
	void						calculateSpecialPointsPool(CHMatch* pMatch);
	void						calculatePoints(CHMatch *pMatch);
	void						calculatePoint(CHMatchResult *pMatchResult);
	void						calculateSolkoffs(CHMatch *pMatch);
	void						calculateSolkoff(CHMatchResult *pMatchResult);
	void						calculateMedianSolkoffs(CHMatch *pMatch);
	void						calculateMedianSolkoff(CHMatchResult *pMatchResult);
	void						calculateSonneBergers(CHMatch *pMatch);
	void						calculateSonneBerger(CHMatchResult *pMatchResult);
	void						calculateProgressiveScores(CHMatch *pMatch);
	void						calculateProgressiveScore(CHMatchResult *pMatchResult);
	void						calculateMatchesParameter(CHMatch* pMatch);
	void						calculateMatchParameter(CHMatchResult *pMatchResult);
	void						calculateFinalRatings(CHMatch* pMatch);
	void						calculateFinalRating(CHMatchResult *pMatchResult);
	float						getProbability(short difRatingAndAverage);
	RWDate						getDateMatch(CHMatch *pMatch);


private:
	RWSet						setTieBreakPoolResult;
	GSortedVector				vTieBreakPoolResult;
	CHMemoryDataBase *			m_pMem;
};

#endif // !defined(AFX_CHRANKING_H__29D5871F_1112_4B9D_9D2D_C998B2BD8030__INCLUDED_)
