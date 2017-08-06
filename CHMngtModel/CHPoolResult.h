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


#pragma once
#include "CHMemoryDataBaseDefs.h"
#include <ovr/Core/TH/GTHPoolResult.h>
#include "CHMatchResult.h"
#include <ovr/core/G/GScore.h>

class CHPhase;

class CHMngtModelExport CHPoolResult : public GTHPoolResult
{
	MSLDECLARE_ITEM(CHPoolResult)

public:

	//Construction/Destruction
	CHPoolResult();
	CHPoolResult(const CHPoolResult & copy);	
	virtual ~CHPoolResult();
	
	/**** Virtual operators inherited from GData ********************/
	GData& operator= (const GData& copy);
	bool   operator==(const GData& copy);
	bool   operator!=(const GData& copy);

	/**** Virtual methods inherited from GData **********************/
	MSLPack& pack  (MSLPack& pck) const;
	MSLPack& unpack(MSLPack& pck);

	QBase* onQ() const;
	UBase* onU() const;

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
	MSLString getPointsFStr() const;
	float getMSolkoff() const;
	MSLString getMSolkOffStr() const;
	float getMMedianSolkoff() const;
	MSLString getMMedianSolkOffStr() const;
	float getMSonneBerger() const;
	MSLString getMSonneBergerStr() const;
	float getMProgressiveScore() const;
	MSLString getMProgressiveScoreStr() const;


	// Help Methods
	short			getMatchesPlayed(short nRound=0) const;
	short			getMatchesWon(short nRound=0) const;
	short			getMatchesLost(short nRound=0) const;
	short			getMatchesDrawn(short nRound=0) const;
	short			getPointsForWon(short nRound=0) const;
	short			getAllRoundsPointsForWon() const;
	float			getPoolPointsF(short nRound=0,bool onlyRound=false) const;
	MSLString		getPoolPointsFStr(short nRound=0,bool onlyRound=false) const;
	GScore			getSolkOffF(short nRound=0);
	MSLString		getSolkOffFStr(short nRound=0);
	GScore			getMedianSolkOffF(short nRound=0, short cutHighest=0, short cutLowest=1);
	MSLString		getMedianSolkOffFStr(short nRound=0, short cutHighest=0, short cutLowest=1);
	GScore			getSonneBergerF(short nRound=0);
	MSLString		getSonneBergerFStr(short nRound=0);
	float			getProgresiveF(short nRound=0) const;
	MSLString		getProgressiveFStr(short nRound=0) const;
	bool			isQualitative() const;
	short			getTeamMatchesWon(short nRound=0) const;
	MSLString		getTeamMatchesWonStr(short nRound=0) const;
	float			getPointsFR(short nRound=0) const;
	GScore			getPointsSO(short nRound=0,bool onlyRound=false);
	GScore			getMatchPoints(short nRound=0,bool onlyRound=false);
	MSLString		getMatchPointsStr(short nRound=0,bool onlyRound=false);
	MSLString		getDirectMatchPtsStr();
	
	MSLWString		getDescription(bool longDescription=true) const;
	MSLWString		getSourceCompetitor();

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
	GScore			getOppAverageRating(short discountHigh=1, short discountLower=1);
	bool			isTeamEvent();

	void			clearData();

	CHPhase*		getPrevPhase();

	void			getParentMatchResultsVector	(MSLSortedVector& vMatchResults, mslToolsFcCompare compare=0);

	// select function
	mslToolsFcSelect getSelectFn(const GData *pData);

private:
	short		m_mPlayed,
				m_mWon,
				m_mLost,
				m_mDrawn;
	float		m_pointsF,
				m_mSolkoff,
				m_mMedianSolkoff,
				m_mSonneBerger,
				m_mProgressiveScore;
};
