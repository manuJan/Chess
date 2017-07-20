/*************************************************************************************
*			© Copyright MSL Software, S.L., 2014
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHODF2Team.h
*	Description	:
*
*	Author		: 
*	Date created: 
* 	Project		: AR ODF
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include <OVR/GUI/ODF2/ODF2THBase/ODF2THZZTeam.h>

#pragma once

class CHODF2Team : public ODF2THZZTeam/*ODF2ZZTeam*/
{
public:
	CHODF2Team(ODF2BuildBase * pBuild,XMLElement * pElement,ODF2FileBase * pFile,GRegister * pRegister);
	virtual ~CHODF2Team();

protected:
	void fillEventEntry(XMLElement * pEl_RegEvent,GData * pCompetitor);
};

