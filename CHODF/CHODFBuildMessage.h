/*************************************************************************************
*			© Copyright MSL Software, S.L., 2012
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHODFBuildMessage.h
*	Description	:
*
*	Author		: 
*	Date created: 7-5-2012
* 	Project		: Basket ODF
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#pragma once
#include <OVR/GUI/ODF2/ODFTHMngr/ODFTHBuildMessage.h>

class CHODFBuildMessage : public ODFTHBuildMessage
{
public:
	CHODFBuildMessage(ODFGUI * pGUI);
	virtual ~CHODFBuildMessage();

	//virtual from ODFTHBuildMessage
	bool getPIT	(ODFFile * pFile,XMLElement * pCompetitionElem);
	bool getRT	(ODFFile * pFile,XMLElement * pCompetitionElem);
	bool getODF2(ODF2FileBase * pFile,XMLElement * pCompetitionElem);

};

