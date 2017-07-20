/*************************************************************************************
*			© Copyright MSL Software, S.L., 2015
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHODF2Brackets.h
*	Description	:
*
*	Author		: Antonio Balmaseda
*	Date created: 22-01-2015
* 	Project		: AR ODF
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#pragma once

#include <OVR/GUI/ODF2/ODF2THBase/ODF2THZZBrackets.h>

class CHMatchResult;

class CHODF2Brackets : public ODF2THZZBrackets
{
public:
	enum TypeBrackets{eFinals=0,eBronze=1};

	CHODF2Brackets(ODF2BuildBase * pBuild,XMLElement * pElement,ODF2FileBase * pFile,GEvent * pEvent);
	virtual ~CHODF2Brackets();

	short getTypeBrackets();
	bool insertInVector(GPhase *pPhase, short typeBracket);
	MSLString getBracketCode(GEvent *pEvent, short typeBracket);
	MSLString  getBracketItemsCode(GPhase *pPhase);
	
	//BracketItems
	void fillVectorEUnits			(GPhase * pPhase,MSLSortedVector & vEUnits);
	mslToolsFcCompare getSortUnits	() const;

	//BracketItem
	void fillBracketData(XMLElement *pEl_BracketItem,MSLItem * pData,short pos);	
	MSLString getMatchNumber(MSLItem * pData);
	MSLString getResult(GTHMatch * pMatch);
	
	//PreviousUnit
	void fillPreviousUnit(XMLElement * pEl_CompPlace,MSLItem * pData);

	//ExtBracketsAthletes
	virtual void fillVectorAthletes(MSLArray& vAthletes,MSLItem * pData);
	virtual void fillVectorExtBracketsAthletes(MSLArray & vExtBracketAths,MSLItem * pData);
	XMLElement * fillVectorExtBracketAth(MSLItem * pData,XMLElement * pElement);
	bool fillRankingRoundExtBracketAth(XMLElement * pElement, CHMatchResult *pMR);

	//ExtBracketComps
	virtual void fillVectorExtBracketsCompetitors(MSLArray & vExtBracketsCompetitors,MSLItem * pData);
	virtual XMLElement * fillVectorExtBracketComp(MSLItem * pData,XMLElement * pElement);
	bool fillRankingRoundExtBracketComp(XMLElement * pElement, CHMatchResult *pMR);
	
};

