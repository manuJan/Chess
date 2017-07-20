/*************************************************************************************
*			© Copyright MSL Software, S.L., 2014
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHODF2Results.h
*	Description	:
*
*	Author		: Fernando Hicar
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
#include <OVR/GUI/ODF2/ODF2THBase/ODF2THZZResults.h>

class CHMatchResult;

class CHODF2Results : public ODF2THZZResults
{
public:
	CHODF2Results					(ODF2BuildBase * pBuild,XMLElement * pElement,ODF2FileBase * pFile,GData * pData);
	virtual ~CHODF2Results			();

	//Extended Infos
	void fillVectorExtendedInfo		(MSLArray& vExInfos);									//M
	void fillExtendedExtensions		(MSLItem * pData,XMLElement *pEl_ExInfo);				//M
	void fillUnitDateTime			(XMLElement * pElement);

	//Venue Description
	void fillSportXXVenueDescription(GVenue * pVenue,XMLElement * pEl_VenueDesc);			//M
	
	//Result
	void fillCompetitor				(MSLItem * pCompetitor	,XMLElement * pEl_Competitor);	//M	
	void fillSportCompetitor		(MSLItem * pCompetitor	,XMLElement * pEl_Competitor);	//M
	void fillAthlete				(MSLItem * pAthlete		,XMLElement * pEl_Athlete);
	void fillSportAthlete			(MSLItem * pAthlete		,XMLElement * pEl_Athlete);
	void fillEventUnitEntry			(MSLItem * pCompetitor	,XMLElement * pEl_Competitor);	//M
	void fillVectorResults			(MSLArray& vResults		,MSLItem * pData=0);
	void fillSportResult			(MSLItem * pResult		,XMLElement * pEl_Result);
	void fillVectorComposition		(MSLItem * pCompetitor	,MSLArray& vComposition);
	
	bool isSelectable				(GData * pData, ODF2THZZResults::TypeSelection selection);

private:

	short getStartSortOrder(CHMatchResult *pMR);

private:

	MSLSortedVector m_vCompetitors;
	short m_startOrder;
	short m_memberOrder;
};

