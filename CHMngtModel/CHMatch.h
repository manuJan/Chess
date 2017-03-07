/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHMatch.h
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:07-12-2005
*   Project     :CH Model
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///

#if !defined(AFX_CHMATCH_H__14EDC82E_5189_42B6_A693_CD2BF3E63065__INCLUDED_)
#define AFX_CHMATCH_H__14EDC82E_5189_42B6_A693_CD2BF3E63065__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHMNGTMODELDLL_H
#   include "CHMngtModelDll.h" 
#endif // _CH_MNGTMODELDLL_H

#include <Core\THSP\THSPMatch.h>
#include <Core\G\GCourt.h>
#include <Core\G\GVenue.h>
#include "CHEvent.h"

//constantes para asignar el identificador del partido
static const cKindTeam= 10000;
static const cStepTeam= 10;

//constantes para qualitatives
static const char *WALKOVER="w";
static const char *DISQUALIFIED="d";
static const char *RETIRED="r";

class CHSession;
class CHMatchResult;
//class CHSplitMatch;
//class CHMatchJudge;
class CHPool;
//class GTHMatchMember;
class CHModelExport CHMatch : public THSPMatch  
{
	RWDECLARE_COLLECTABLE(CHMatch)
public:
	enum type { eNone=CHEvent::eNone,eIndividual=1,eTeam=CHEvent::eTeam,
				eTeamIndividual=CHEvent::eTeam+1};
	
	enum typeWinner { eNoWinner=0,eWinnerWhite=1,eWinnerBlack=2,eDraw=3};

	CHMatch();
	CHMatch(const CHMatch &copy);
	CHMatch(CPack &aPack);
	CHMatch(const RWDBBlob& aBlob);
	CHMatch(CHPool *poolMatch,short codeMatch);
	virtual ~CHMatch();

	CHMatch & operator  = (const CHMatch& copy);
	RWBoolean operator == (const CHMatch& copy);
	RWBoolean operator != (const CHMatch& copy);

	RWBoolean uSQL(RWDBConnection& pConnect,RWBoolean remove=false);
	RWCString msl() const;
	RWCString mslDescription(const char *language) const;
	CPack& pack(CPack& aPack);
	CPack& unpack(CPack& aPack);

	// Sets
	void setSession(GTHSession *value);
	void setCourt(GCourt *value);
	void setSubMatch(const short value );
	void setMatchType(const short value);
	void setRound(const short value);
	void setVenue(GVenue *value);

	//Gets
	GTHSession * getSession() const;
	GCourt * getCourt() const;
	short getSubMatch() const ;
	short getMatchType() const;
	short getRound() const;

	RWCString getMatchNumberAsString() const;
	RWBoolean areTeams() const;
	RWBoolean areTeamIndividual() const;
	RWBoolean thereAreQualitative() const;
	int		  getResultCode() const;
	RWCString getResultAsString() const;
	RWCString getResultWhiteBlackAsString() const;
	RWCString getResultIncidence() const;
	RWCString getResultWhiteBlackIncidence() const;

	//methods from Phase
	GTHPhase::DescriptionMode getPhasePoolDescription() const;

	//methods from Session
	char getSessionSession()const;

	//methods from parentMatch
	short getIdParent() const;
	RWCString getIdParentAsString() const;
	CHMatch * getParentMatch() const;
	short getParentMatchNumber() const;
	GSortedVector getSubMatches();

	//methods for matchResults
	CHMatchResult * getMatchResultHome() const;
	CHMatchResult * getMatchResultAway() const;

	//methods for matchResults
	CHMatchResult * getWhite() const;
	CHMatchResult * getBlack() const;

	//methods from Venue
	GVenue * getVenue() const;
	RWCString getVenueCode() const;

	//methods from Court
	int getCourtCode() const;
	int getEventMode() const;

	short	getWinner() const;
	bool	isBye();
	RWBoolean isEmpty();
	RWBoolean isConfigured();
	short	getTurn() const;
	short	getNextPlayNumber() const;
	size_t	getHistoricDataSize();
	RWCString		getTotalResult(RWBoolean onlyRound=false);
	RWCString		getRoundMatch();
	GSortedVector	getRoundMatches();
	RWBoolean		getFinishedRound();
	
	RWCString getRoundAsString(RWBoolean lDesc=true,RWBoolean date=true);

	// From CHEvent
	RWBoolean isTeam();

	RWBoolean hasCompetitors(RWBoolean any=false);

private:
	CHSession *pSession;
	GVenue *pVenue;
	GCourt *pCourt ;
	short subMatch;
	short matchType;
	short round;
};

#endif // !defined(AFX_CHMATCH_H__14EDC82E_5189_42B6_A693_CD2BF3E63065__INCLUDED_)
