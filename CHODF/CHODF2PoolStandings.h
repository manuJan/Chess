/*************************************************************************************
*			© Copyright MSL Software, S.L., 2015
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHODF2PoolStandings.h
*	Description	:
*
*	Author		: Antonio Balmaseda
*	Date created: 29-01-2015
* 	Project		: TE ODF
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#pragma once

#include <OVR/GUI/ODF2/ODF2THBase/ODF2THZZPoolStandings.h>

class CHODF2PoolStandings : public ODF2THZZPoolStandings
{
public:
	CHODF2PoolStandings(ODF2BuildBase * pBuild,XMLElement * pElement,ODF2FileBase * pFile,GData * pData);
	virtual ~CHODF2PoolStandings(void);

	void fillSportXXDescription(GEvent * pEvent,XMLElement * pEl_SportDesc);
	void fillVectorResults(MSLArray & vResults,MSLItem * pData=0);
	void fillSportResult(MSLItem * pResult,XMLElement * pEl_Result,int order);
	void fillVectorComposition(MSLItem * pCompetitor,MSLSortedVector & vComposition);
	void fillSportAthlete(MSLItem * pAthlete,XMLElement * pEl_Athlete);
	void fillExtendedResults(MSLItem * pCompetitor,XMLElement * pEl_Competitor);
	void fillVectorOpponents(MSLItem * pCompetitor,MSLSortedVector & vOpponents);
	void fillSportOpponent(MSLItem * pOpponent,XMLElement * pEl_Opponent);
	bool isSelectable(GData * pData);
};

