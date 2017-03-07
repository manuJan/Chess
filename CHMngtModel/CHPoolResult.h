/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHPoolResult.h                                                                 
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


#ifndef _CHPoolResult_H
#define _CHPoolResult_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef _CHMNGTMODELDLL_H
#   include "CHMngtModelDll.h" 
#endif // _CH_MNGTMODELDLL_H

#include <core/TH/GTHPoolResult.h>

#include "CHSportDefines.h"
#include "CHPhase.h"


class CHModelExport CHPoolResult : public GTHPoolResult
{
	RWDECLARE_COLLECTABLE(CHPoolResult)

public:

	//Construction/Destruction
	CHPoolResult();
	CHPoolResult(const CHPoolResult & copy);
	CHPoolResult(CPack& aPack);
	virtual ~CHPoolResult();


	//Operators
	RWBoolean		operator !=(const CHPoolResult & copy);
	RWBoolean		operator ==(const CHPoolResult & copy);
	CHPoolResult&	operator =(const CHPoolResult & copy);


	//From GData
	RWBoolean		uSQL(RWDBConnection& pConnect,RWBoolean remove=false);
	CPack&			pack(CPack &iPack);
	CPack&			unpack(CPack &iPack);
	RWCString		msl() const;
	RWCString		mslDescription(const char *language) const;

	// set
	void setMPlayed(const short value);
	void setMWon(const short value);
	void setMLost(const short value);
	void setMDrawn(const short value);
	void setPointsF(const float value);
	void setMSolkoff(const float value);
	void setMMedianSolkoff(const float value);
	void setMSonneBerger(const float value);
	void setMProgressiveScore(const float value);
	

	// get
	short getMPlayed() const;
	short getMWon() const;
	short getMLost() const;
	short getMDrawn() const;
	float getPointsF() const;
	RWCString getPointsFStr() const;
	float getMSolkoff() const;
	RWCString getMSolkOffStr() const;
	float getMMedianSolkoff() const;
	RWCString getMMedianSolkOffStr() const;
	float getMSonneBerger() const;
	RWCString getMSonneBergerStr() const;
	float getMProgressiveScore() const;
	RWCString getMProgressiveScoreStr() const;


	// Help Methods
	short			getMatchesPlayed(short nRound=0) const;
	short			getMatchesWon(short nRound=0) const;
	short			getMatchesLost(short nRound=0) const;
	short			getMatchesDrawn(short nRound=0) const;
	short			getPointsForWon(short nRound=0) const;
	short			getAllRoundsPointsForWon() const;
	float			getPoolPointsF(short nRound=0,RWBoolean onlyRound=false) const;
	RWCString		getPoolPointsFStr(short nRound=0,RWBoolean onlyRound=false) const;
	float			getSolkOffF(short nRound=0) const;
	RWCString		getSolkOffFStr(short nRound=0) const;
	float			getMedianSolkOffF(short nRound=0) const;
	RWCString		getMedianSolkOffFStr(short nRound=0) const;
	float			getSonneBergerF(short nRound=0) const;
	RWCString		getSonneBergerFStr(short nRound=0) const;
	float			getProgresiveF(short nRound=0) const;
	RWCString		getProgressiveFStr(short nRound=0) const;
	RWBoolean		isQualitative() const;
	short			getTeamMatchesWon(short nRound=0) const;
	RWCString		getTeamMatchesWonStr(short nRound=0) const;
	float			getPointsFR(short nRound=0) const;
	float			getPointsSO(short nRound=0,RWBoolean onlyRound=false) const;
	
	RWWString		getGroup() const;
	RWCString		getIsoCountry() const;
	RWWString		getDescription(RWBoolean longDescription=true) const;
	RWWString		getSourceCompetitor();

	// From CHInscription
	short			getInscriptionSeed() const;
	short			getInscriptionRating() const;
	short			getMasterTypeOrder() const;


	CHMatchResult::colorPreference	getColorPreference(short round);
	CHMatchResult::side				getSidePreference(short round);

	short			getNumMatchesWithColor(CHMatchResult::side color, short lastRound);
	bool			hasAlreadyPlayed(CHPoolResult* _pPoolResult, short lastRound);
	bool			hasAlreadyBye(short lastRound);
	bool			isPlayingRound(CHMatch* _pMatch, short round);
	bool			canPlayInColor(CHMatchResult::side color, short round);
	float			getAveragePointsAllCompetitors(CHMatch *pMatch=0);

private:
	short	mPlayed,
			mWon,
			mLost,
			mDrawn;
	float   pointsF,
			mSolkoff,
			mMedianSolkoff,
			mSonneBerger,
			mProgressiveScore;

};

#endif //!defined(AFX_CHPoolResult_H)