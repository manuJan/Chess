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

#pragma once
#include "CHVMngtModelDefs.h"

class CHGroupDraw;
class CHCompetitorDraw;
class CHPairDraw;
class CHPool;
class CHMatch;
class CHMatchResult;

class CHVMngtModelExport CHRoundDraw  
{
public:

	enum TypeDraw {eMonrad=1, eNordishRating=2, eNordishELO=3, eRoundRobin=4, eSortedMonrad=5};

	CHRoundDraw(MSLSet& colMatchResults, CHPool* _pPool, short _round);
	virtual ~CHRoundDraw();

	bool				doDraw(TypeDraw drawType);

	// Vector Functions
	MSLSortedVector&	getGroupsDrawVector();
	MSLItem*			setGroupsDraw(CHGroupDraw* pGroupDraw);
	void				removeGroupsDraw(CHGroupDraw& aGroupDraw);
	CHGroupDraw*		getGroupsDraw(int index);

	// Vector Functions
	MSLSortedVector&	getGroupsDrawProcessedVector();
	MSLItem*			setGroupsDrawProcessed(CHGroupDraw* pGroupDraw);
	void				removeGroupsDrawProcessed(CHGroupDraw& aGroupDraw);
	CHGroupDraw*		getGroupsDrawProcessed(int index);

	// Vector Functions
	MSLSortedVector&	getRoundMatchesVector();
	MSLItem*			setRoundMatch(CHMatch* pMatch);
	void				removeRoundMatch(CHMatch& aMatch);
	CHMatch*			getMatch(int index);	

	// Vector Functions
	MSLSortedVector&	getAllRoundPairsVector();
	MSLItem*			setAllRoundPair(CHPairDraw* pPairDraw);
	void				removeAllRoundPair(CHPairDraw& aPairDraw);
	short				removePairs(CHGroupDraw *pGroupDraw);
	CHPairDraw*			getPair(int index);	
	bool				trasposeGroup(CHGroupDraw *pGroupDraw);
	bool				changeGroup(CHGroupDraw *pGroupDraw);
		
	short				processGroupPairing(CHGroupDraw* pGroupDraw, MSLSet &colUnpairedCompetitors);
	CHCompetitorDraw*	processCompetitor(CHGroupDraw* pGroupDraw,CHCompetitorDraw* pCompetitorDraw,short &matchOrder, short &groupMatches, short P);
	short				processNotFoundOpponent(CHCompetitorDraw* pCompetitorDraw,CHGroupDraw *pGroupDraw,short &matchOrder, short &groupMatches, short P);
	CHPairDraw*			processPair(CHGroupDraw* pGroupDraw,CHCompetitorDraw* pCompetitorDraw,CHCompetitorDraw* pCompetitorDrawOpp,short matchOrder);

	void				changeCompetitorGroup(CHGroupDraw* pGroupDrawSource,CHCompetitorDraw* pCompetitorDraw,CHGroupDraw* pGroupDrawTarget,bool floatingUp, bool floatingDown);

protected:
	void				rebuildVector();
	void				destroyVector();
	
	void				fillMatchesVector();
	CHMatch*			fillMatch(CHCompetitorDraw* pCompetitorDraw, CHCompetitorDraw* pCompetitorDrawOpp, CHPairDraw* pPairDraw);
	void				unfillMatch(CHMatch* pMatch);
	short				undoGroup(CHGroupDraw* pGroupDraw);
	short				undoPreviousGroup_C12(CHGroupDraw* pGroupDraw,CHCompetitorDraw* pCompetitorDraw);
	short				undoPreviousGroup_C13(CHGroupDraw* pGroupDraw);
	void				mergeGroups(CHGroupDraw* pGroupDrawSource,CHGroupDraw* pGroupDrawTarget,bool floatingUp,bool floatingDown);

	void				assignMatchResult(CHMatchResult* pMatchResult,CHCompetitorDraw* pCompetitorDraw);
	void				unassignMatchResult(CHMatchResult* pMatchResult);

	int					randNum(int n);
	bool				hasBye();

private:

	CHPool* pPool;
	short round;
	
	MSLSortedVector vGroupDraw;	
	MSLSortedVector vGroupDrawProcessed;	
	
	MSLSortedVector vRoundMatches;
	MSLSortedVector vRoundPairs;
		
	TypeDraw typeDraw;
	MSLSet* colMatchResults;


};

