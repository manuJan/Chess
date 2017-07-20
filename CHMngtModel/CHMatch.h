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

#pragma once
#include "CHMemoryDataBaseDefs.h"
#include <OVR/CORE/TH/GTHMatch.h>
#include "CHEvent.h"

//constantes para asignar el identificador del partido
static const int cKindTeam= 10000;
static const int cStepTeam= 10;

//constantes para qualitatives
static const char *WALKOVER="w";
static const char *DISQUALIFIED="d";
static const char *RETIRED="r";

class CHMatchResult;
class CHInscription;

class CHMngtModelExport CHMatch : public GTHMatch  
{

	MSLDECLARE_ITEM(CHMatch)

public:

	enum type { eNone=CHEvent::eNone,eIndividual=1,eTeam=2, eTeamIndividual=3};
	
	enum typeWinner { eNoWinner=0, eWinnerWhite=1, eWinnerBlack=2, eDraw=3};

	CHMatch();
	CHMatch(const CHMatch &copy);
	CHMatch(GTHPool * poolMatch,short codeMatch,short codeSubMatch);	
	CHMatch(const MSLBinary& aBinary);
	virtual ~CHMatch();

	/**** Virtual operators inherited from GData ********************/
	GData& operator= (const GData& copy);
	bool   operator==(const GData& copy);
	bool   operator!=(const GData& copy);

	/**** Virtual methods inherited from GData **********************/
	MSLPack& pack  (MSLPack& pck) const;
	MSLPack& unpack(MSLPack& pck);

	QBase*			onQ() const;
	UBase*			onU() const;

	// Sets
	void setMatchType(const short value);
	void setRound(const short value);
	
	//Gets
	short getMatchType() const;
	short getRound() const;

	bool areTeams() const;
	bool areTeamIndividual() const;
	bool thereAreQualitative() const;
	int	  getResultCode() const;
	MSLString getResultAsString() const;
	MSLString getResultWhiteBlackAsString() const;
	MSLString getResultIncidence() const;
	MSLString getResultWhiteBlackIncidence() const;
		
	//methods for matchResults
	CHMatchResult * getWhite() const;
	CHMatchResult * getBlack() const;
	
	CHInscription * getWhiteInscription() const;
	CHInscription * getBlackInscription() const;
	
	bool	isEmpty();
	bool	isConfigured();
	short	getTurn() const;
	short	getNextPlayNumber() const;
	
	//virtual methods GTHMatch	
	size_t getHistoricDataSize();

	MSLString		getTotalResult(bool onlyRound=false);
	MSLString		getRoundMatch();
	MSLSortedVector	getRoundMatches();
	bool			getFinishedRound();	
	MSLString		getRoundAsString(bool lDesc=true,bool date=true);
	MSLString		getEventCodeReports();

	// From CHEvent
	bool isTeam();

	bool hasCompetitors(bool any=false);
	bool hasTeamCompetitors(bool any=false);

	short getWinner() const;

	CHMatchResult*	findMatchResult(GRegister * pRegister) const;
	CHMatchResult*	findMatchResult(CHInscription *pInscription) const;
	CHMatchResult*	findMatchResultByProgression(CHMatchResult * pMatchResult) const;

	// select function
	mslToolsFcSelect getSelectFn(const GData *pData);

private:
	
	short m_matchType;
	short m_round;
};
