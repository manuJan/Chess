/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHPool.h                                                                 
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
#include <OVR/CORE/TH/GTHPool.h>
#include <OVR/CORE/TH/GTHPhase.h>

class CHPoolResult;
class CHInscription;
class CHMatch;

class CHMngtModelExport CHPool : public GTHPool
{

	MSLDECLARE_ITEM(CHPool)

public:

	//Construction/Destruction
	CHPool();
	CHPool(const CHPool & copy);	
	virtual ~CHPool();
		
	// Help Methods
	GTHPhase::DescriptionMode	getDescriptionMode() const;
	MSLWString					getOrderAsString(GTHPhase::DescriptionMode mode=GTHPhase::eNumeric) const;

	MSLWString getDescription(GTHPhase::DescriptionMode mode= GTHPhase::eNumeric,const char *language=0) const;
	MSLWString getSDescription(GTHPhase::DescriptionMode mode= GTHPhase::eText,const char *language=0) const;
	MSLWString getLDescription(GTHPhase::DescriptionMode mode= GTHPhase::eText,const char *language=0) const;

	unsigned char getRoundStatus(short nRound);
	short getRoundMatches(short nRound);
	void getRoundMatchesVector(MSLSortedVector &vRoundMatches, short nRound);
	void getFromRoundMatchesVector(MSLSortedVector &vRoundMatches, short nRound);
	short getNumRoundsPlayed();

	bool	hasCompatibleColors(CHPoolResult* pPR1,CHPoolResult* pPR2, short round);
	bool	hasCompetitors();
	bool	isTeam();

	void	getSamePointsCompetitorsVector(MSLSortedVector &vector, CHPoolResult * pPoolResult);

	CHMatch * findMatch(CHPoolResult * pPR1, CHPoolResult * pPR2);
};
