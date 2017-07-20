/*************************************************************************************
*			© Copyright MSL Software, S.L., 2012
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHODFModel.h
*	Description	:
*
*	Author		: 
*	Date created: 
* 	Project		: ARODF
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#pragma once
#include <OVR/GUI/ODF2/ODF2THBase/ODF2THModel.h>

class CHMatch;
class CHRegister;
class CHEvent;
class CHMatchResult;

#define CHODFMODEL CHODFModel::getCHModel()

class CHODFModel : public ODF2THModel
{
public:
	CHODFModel();
	~CHODFModel();

	static CHODFModel * getCHModel		();

	CHMemoryDataBase * getMem() const;

	GTHMatch * findMatch			(GTHPool * pPool, GTHPoolResult * pPoolResult, GTHPoolResult * pPoolResultOpp);
	MSLString getResult				(GTHMatch * pMatch, GTHPoolResult * pPoolResult, GTHPoolResult * pPoolResultOpp);
	MSLString getFunction			(GData *pData);
	bool getIsCurrent				(CHMatch * pMatch);
	MSLWString getMatchLDescription	(CHMatch *pMatch, const char * lang, bool info);
	MSLWString getMatchSDescription	(CHMatch *pMatch, const char * lang, bool info);
	MSLString getMasterType			(CHRegister* pRegister);
	MSLString getColor				(CHMatchResult * pMR);
	bool hasMatchesInSession		(GSession* pSession, MSLSortedVector &vMatches);
	CHEvent * getEventSession		(GSession* pSession);
	void fillMembers				(CHMatchResult* pMatchResult, MSLSortedVector &vMembers);
};

