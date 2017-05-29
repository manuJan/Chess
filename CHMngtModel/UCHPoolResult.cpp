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
#include "CHPoolResult.h"

void UCHPoolResult::OnAssignAttributes(GTHPoolResult& aPoolResult)
{	
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

void UCHPoolResult::OnInsert(MSLDBInserter& aInserter,MSLDBTable& table,GTHPoolResult& aPoolResult)
{
	aInserter << table["MATCHES_PLAYED"]	.assign(matchesPlayed,&nullmatchesPlayed);
	aInserter << table["WON_GAMES"]			.assign(wonGames,&nullwonGames);
	aInserter << table["LOST_GAMES"]		.assign(lostGames,&nulllostGames);
	aInserter << table["TIE_GAMES"]			.assign(tieGames,&nulltieGames);
	aInserter << table["POINTS_F"]			.assign(pointsF,&nullpointsF);
	aInserter << table["SOLKOFF"]			.assign(solkoff,&nullsolkoff);
	aInserter << table["MEDIAN_SOLKOFF"]	.assign(mediansolkoff,&nullmediansolkoff);
	aInserter << table["SONNEBERGER"]		.assign(sonneBerger,&nullsonneBerger);
	aInserter << table["PROGRESSIVE_SCORE"]	.assign(progressiveScore,&nullprogressiveScore);	

	UNREFERENCED_PARAMETER(aPoolResult);
}

void UCHPoolResult::OnUpdate(MSLDBUpdater& aUpdater,MSLDBTable& table,GTHPoolResult& aPoolResult)
{
	aUpdater << table["MATCHES_PLAYED"]		.assign(matchesPlayed,&nullmatchesPlayed);
	aUpdater << table["WON_GAMES"]			.assign(wonGames,&nullwonGames);
	aUpdater << table["LOST_GAMES"]			.assign(lostGames,&nulllostGames);
	aUpdater << table["TIE_GAMES"]			.assign(tieGames,&nulltieGames);
	aUpdater << table["POINTS_F"]			.assign(pointsF,&nullpointsF);
	aUpdater << table["SOLKOFF"]			.assign(solkoff,&nullsolkoff);
	aUpdater << table["MEDIAN_SOLKOFF"]		.assign(mediansolkoff,&nullmediansolkoff);
	aUpdater << table["SONNEBERGER"]		.assign(sonneBerger,&nullsonneBerger);
	aUpdater << table["PROGRESSIVE_SCORE"]	.assign(progressiveScore,&nullprogressiveScore);	

	UNREFERENCED_PARAMETER(aPoolResult);
}
