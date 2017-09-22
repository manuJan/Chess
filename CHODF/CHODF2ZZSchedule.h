/*************************************************************************************
*			© Copyright MSL Software, S.L., 2012
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHODF2ZZSchedule.h
*	Description	:
*
*	Author		: 
*	Date created: 18-12-2014
* 	Project		: AR ODF
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#pragma once
#include <OVR/GUI/ODF2/ODF2THBase/ODF2THZZSchedule.h>

class CHMatch;
class ODFZZSchLine;

class CHODF2ZZSchedule : public ODF2THZZSchedule
{
public:
	CHODF2ZZSchedule				(ODF2BuildBase * pBuild, XMLElement * pElement, ODF2FileBase * pFile, GData * pData);
	~CHODF2ZZSchedule				();

protected:
	void			createSchLines		();
	ODF2ZZSchLine * createSchLine		(GData * pData);

	void fillSportScheduleUnit(XMLElement *pEl_Unit,ODF2ZZSchLine * pSchUnit);
	
	MSLWString getItemNameDescription	(GData * pData,const char * language=0);
	MSLString isMedalsMatch				(CHMatch * pMatch);

	//StartList
	void fillVectorComposition			(MSLItem * pCompetitor,MSLArray& vComposition);
	mslToolsFcCompare getVectorCompositionCompare();
};

