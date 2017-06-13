/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : QCHPoolResult.cpp                                                                 
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
#include "QCHPoolResult.h"
#include "CHPoolResult.h"


void QCHPoolResult::OnSelect(MSLDBSelector& aSelect,MSLDBTable& table)
{
	QGTHPoolResult::OnSelect(aSelect,table);
	
	aSelect << table["MATCHES_PLAYED"]
			<< table["WON_GAMES"]
			<< table["LOST_GAMES"]
			<< table["TIE_GAMES"]
			<< table["POINTS_F"]
			<< table["SOLKOFF"]
			<< table["MEDIAN_SOLKOFF"]
			<< table["SONNEBERGER"]
			<< table["PROGRESSIVE_SCORE"]
			;
}

void QCHPoolResult::OnReader(MSLDBReader& aReader,GTHPoolResult *pValue)
{
	QGTHPoolResult::OnReader(aReader,pValue);

	CHPoolResult* pVal = (CHPoolResult*)pValue;

	short matchesPlayed;
	short wonGames;
	short lostGames;
	short tieGames;
	double pointsF;
	double solkoff;
	double mediansolkoff;
	double sonneBerger;
	double progressiveScore;

	MSLDBNullIndicator nullmatchesPlayed;
	MSLDBNullIndicator nullwonGames;
	MSLDBNullIndicator nulllostGames;
	MSLDBNullIndicator nulltieGames;
	MSLDBNullIndicator nullpointsF;
	MSLDBNullIndicator nullsolkoff;
	MSLDBNullIndicator nullmediansolkoff;
	MSLDBNullIndicator nullsonneBerger;
	MSLDBNullIndicator nullprogressiveScore;
	

	aReader >> nullmatchesPlayed >> matchesPlayed
			>> nullwonGames >> wonGames
			>> nulllostGames >> lostGames
			>> nulltieGames >> tieGames
			>> nullpointsF >> pointsF
			>> nullsolkoff >> solkoff
			>> nullmediansolkoff >> mediansolkoff
			>> nullsonneBerger >> sonneBerger
			>> nullprogressiveScore >> progressiveScore
			;
	
	if ( nullmatchesPlayed ) matchesPlayed = 0;
	if ( nullwonGames ) wonGames = 0;
	if ( nulllostGames ) lostGames = 0;
	if ( nulltieGames ) tieGames = 0;
	if ( nullpointsF ) pointsF = 0.0;
	if ( nullsolkoff ) solkoff = 0.0;
	if ( nullmediansolkoff ) mediansolkoff = 0.0;
	if ( nullsonneBerger ) sonneBerger = 0.0;
	if ( nullprogressiveScore ) progressiveScore = 0.0;
	
	pVal->setMPlayed(matchesPlayed);
	pVal->setMWon(wonGames);
	pVal->setMLost(lostGames);
	pVal->setMDrawn(tieGames);
	pVal->setPointsF(pointsF);
	pVal->setMSolkoff(solkoff);
	pVal->setMMedianSolkoff(mediansolkoff);
	pVal->setMSonneBerger(sonneBerger);
	pVal->setMProgressiveScore(progressiveScore);
}

