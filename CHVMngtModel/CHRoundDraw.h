/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHRoundDraw.h
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:23-12-2005
*   Project     :CHV Model               
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///

#if !defined(AFX_CHDRAW_H__C7F1B058_DDF1_46D6_B3B2_919290464370__INCLUDED_)
#define AFX_CHDRAW_H__C7F1B058_DDF1_46D6_B3B2_919290464370__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHVMNGTMODELDLL_H
	#include "CHVMngtModelDll.h"
#endif // _CHVMNGTNODELDLL_H

class CHGroupDraw;
class CHCompetitorDraw;
class CHPairDraw;

class CHVMngtExport CHRoundDraw  
{
public:

	enum TypeDraw {eMonrad=1, eNordishRating=2, eNordishELO=3, eRoundRobin=4, eSortedMonrad=5};

	CHRoundDraw(RWSet& colMatchResults, CHPool* _pPool, short _round);
	virtual ~CHRoundDraw();

	RWBoolean			doDraw(TypeDraw drawType);

	// Vector Functions
	GSortedVector&		getGroupsDrawVector();
	GVectorElement*		setGroupsDraw(CHGroupDraw* pGroupDraw);
	void				removeGroupsDraw(CHGroupDraw& aGroupDraw);
	CHGroupDraw*		getGroupsDraw(int index);

	// Vector Functions
	GSortedVector&		getGroupsDrawProcessedVector();
	GVectorElement*		setGroupsDrawProcessed(CHGroupDraw* pGroupDraw);
	void				removeGroupsDrawProcessed(CHGroupDraw& aGroupDraw);
	CHGroupDraw*		getGroupsDrawProcessed(int index);

	// Vector Functions
	GSortedVector&		getRoundMatchesVector();
	GVectorElement*		setRoundMatch(CHMatch* pMatch);
	void				removeRoundMatch(CHMatch& aMatch);
	CHMatch*			getMatch(int index);	

	// Vector Functions
	GSortedVector&		getAllRoundPairsVector();
	GVectorElement*		setAllRoundPair(CHPairDraw* pPairDraw);
	void				removeAllRoundPair(CHPairDraw& aPairDraw);
	short				removePairs(CHGroupDraw *pGroupDraw);
	CHPairDraw*			getPair(int index);	
	RWBoolean			trasposeGroup(CHGroupDraw *pGroupDraw);
	RWBoolean			changeGroup(CHGroupDraw *pGroupDraw);
		
	short				processGroupPairing(CHGroupDraw* pGroupDraw,RWSet &colUnpairedCompetitors);
	CHCompetitorDraw*	processCompetitor(CHGroupDraw* pGroupDraw,CHCompetitorDraw* pCompetitorDraw,short &matchOrder, short &groupMatches, short P);
	short				processNotFoundOpponent(CHCompetitorDraw* pCompetitorDraw,CHGroupDraw *pGroupDraw,short &matchOrder, short &groupMatches, short P);
	CHPairDraw*			processPair(CHGroupDraw* pGroupDraw,CHCompetitorDraw* pCompetitorDraw,CHCompetitorDraw* pCompetitorDrawOpp,short matchOrder);

	void				changeCompetitorGroup(CHGroupDraw* pGroupDrawSource,CHCompetitorDraw* pCompetitorDraw,CHGroupDraw* pGroupDrawTarget,RWBoolean floatingUp,RWBoolean floatingDown);

protected:
	void				rebuildVector();
	void				destroyVector();
	
	void				fillMatchesVector();
	CHMatch*			fillMatch(CHCompetitorDraw* pCompetitorDraw, CHCompetitorDraw* pCompetitorDrawOpp, CHPairDraw* pPairDraw);
	void				unfillMatch(CHMatch* pMatch);
	short				undoGroup(CHGroupDraw* pGroupDraw);
	short				undoPreviousGroup_C12(CHGroupDraw* pGroupDraw,CHCompetitorDraw* pCompetitorDraw);
	short				undoPreviousGroup_C13(CHGroupDraw* pGroupDraw);
	void				mergeGroups(CHGroupDraw* pGroupDrawSource,CHGroupDraw* pGroupDrawTarget,RWBoolean floatingUp,RWBoolean floatingDown);

	void				assignMatchResult(CHMatchResult* pMatchResult,CHCompetitorDraw* pCompetitorDraw);
	void				unassignMatchResult(CHMatchResult* pMatchResult);

	int					randNum(int n);
	RWBoolean			hasBye();

private:

	CHPool* pPool;
	short round;
	
	GSortedVector vGroupDraw;	
	GSortedVector vGroupDrawProcessed;	
	
	GSortedVector vRoundMatches;
	GSortedVector vRoundPairs;
		
	TypeDraw typeDraw;
	RWSet* colMatchResults;


};

#endif // !defined(AFX_CHDRAW_H__C7F1B058_DDF1_46D6_B3B2_919290464370__INCLUDED_)
