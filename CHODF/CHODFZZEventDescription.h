/*************************************************************************************
*			© Copyright MSL Software, S.L., 2012
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHODFZZEventDescription.h
*	Description	:
*
*	Author		: 
*	Date created: 19-11-2013
* 	Project		: Archery ODF
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#pragma once
#include <OVR/GUI/ODF2/ODF2Base/ODFZZItem.h>

class CHODFZZEventDescription : public ODFZZItem
{
public:
	CHODFZZEventDescription(ODF2BuildBase * pBuild,XMLElement * pElement,ODF2FileBase * pFile);
	virtual ~CHODFZZEventDescription();

	bool run();
	void loadEntities();

protected:
	XMLEntity *		m_pEntDiscipline;
	XMLEntity *		m_pEntGender;
	XMLEntity *		m_pEntEvent;
	XMLEntity *		m_pEntEventDescription;
};

