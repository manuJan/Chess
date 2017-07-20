/*************************************************************************************
*			© Copyright MSL Software, S.L., 2014
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHODF2Ranking.h
*	Description	:
*
*	Author		: 
*	Date created: 26-01-2015
* 	Project		: AR ODF
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#pragma once
#include <OVR/GUI/ODF2/ODF2Base/ODF2ZZRanking.h>

class CHODF2Ranking : public ODF2ZZRanking
{
public:
	CHODF2Ranking(ODF2BuildBase * pBuild,XMLElement * pElement,ODF2FileBase * pFile,GData * pData);
	virtual ~CHODF2Ranking();

	//Result
	void fillSportAthlete(MSLItem * pAthlete,XMLElement * pEl_Athlete);
	void fillDescription(MSLItem * pCompetitor,XMLElement *pEl_Competitor);
	void fillVectorComposition(MSLItem * pCompetitor,MSLArray& vComposition);
};

