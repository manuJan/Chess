/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : UCHPoolResult.cpp                                                                 
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:12-12-2005
*   Project     :CH Model
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///

#include "stdCHMngt.h"
#include "UCHPoolResult.h"

void UCHPoolResult::OnAssignAttributes(GTHPoolResult& aPoolResult)
{
	
	UGTHPoolResult::OnAssignAttributes(aPoolResult);
	CHPoolResult* pPoolResult=(CHPoolResult*)&aPoolResult;

	matchesPlayed=pPoolResult->getMPlayed();
	wonGames=pPoolResult->getMWon();
	lostGames=pPoolResult->getMLost();
	tieGames=pPoolResult->getMDrawn();
	pointsF=pPoolResult->getPointsF();
	solkoff=pPoolResult->getMSolkoff();
	mediansolkoff=pPoolResult->getMMedianSolkoff();
	sonneBerger=pPoolResult->getMSonneBerger();
	progressiveScore=pPoolResult->getMProgressiveScore();
	
	nullmatchesPlayed = (matchesPlayed!=0) ? false : true;
	nullwonGames = (wonGames!=0) ? false : true;
	nulllostGames = (lostGames!=0) ? false : true;
	nulltieGames = (tieGames!=0) ? false : true;
	nullpointsF = (pointsF!=0) ? false : true;
	nullsolkoff = (solkoff!=0) ? false : true;
	nullmediansolkoff = (mediansolkoff!=0) ? false : true;
	nullsonneBerger = (sonneBerger!=0) ? false : true;
	nullprogressiveScore = (progressiveScore!=0) ? false : true;
	
}

void UCHPoolResult::OnInsert(RWDBInserter& aInserter,GTHPoolResult& aPoolResult)
{
	UGTHPoolResult::OnInsert(aInserter,aPoolResult);

	aInserter["MATCHES_PLAYED"]		<< RWDBBoundExpr(&matchesPlayed,&nullmatchesPlayed);
	aInserter["WON_GAMES"]			<< RWDBBoundExpr(&wonGames,&nullwonGames);
	aInserter["LOST_GAMES"]			<< RWDBBoundExpr(&lostGames,&nulllostGames);
	aInserter["TIE_GAMES"]			<< RWDBBoundExpr(&tieGames,&nulltieGames);
	aInserter["POINTS_F"]			<< RWDBBoundExpr(&pointsF,&nullpointsF);
	aInserter["SOLKOFF"]			<< RWDBBoundExpr(&solkoff,&nullsolkoff);
	aInserter["MEDIAN_SOLKOFF"]		<< RWDBBoundExpr(&mediansolkoff,&nullmediansolkoff);
	aInserter["SONNEBERGER"]		<< RWDBBoundExpr(&sonneBerger,&nullsonneBerger);
	aInserter["PROGRESSIVE_SCORE"]	<< RWDBBoundExpr(&progressiveScore,&nullprogressiveScore);
	
}

void UCHPoolResult::OnUpdate(RWDBUpdater& aUpdater,RWDBTable& table,GTHPoolResult& aPoolResult)
{
	UGTHPoolResult::OnUpdate(aUpdater,table,aPoolResult);

	aUpdater << table["MATCHES_PLAYED"]		.assign(RWDBBoundExpr(&matchesPlayed,&nullmatchesPlayed));
	aUpdater << table["WON_GAMES"]			.assign(RWDBBoundExpr(&wonGames,&nullwonGames));
	aUpdater << table["LOST_GAMES"]			.assign(RWDBBoundExpr(&lostGames,&nulllostGames));
	aUpdater << table["TIE_GAMES"]			.assign(RWDBBoundExpr(&tieGames,&nulltieGames));
	aUpdater << table["POINTS_F"]			.assign(RWDBBoundExpr(&pointsF,&nullpointsF));
	aUpdater << table["SOLKOFF"]			.assign(RWDBBoundExpr(&solkoff,&nullsolkoff));
	aUpdater << table["MEDIAN_SOLKOFF"]		.assign(RWDBBoundExpr(&mediansolkoff,&nullmediansolkoff));
	aUpdater << table["SONNEBERGER"]		.assign(RWDBBoundExpr(&sonneBerger,&nullsonneBerger));
	aUpdater << table["PROGRESSIVE_SCORE"]	.assign(RWDBBoundExpr(&progressiveScore,&nullprogressiveScore));
	
}
