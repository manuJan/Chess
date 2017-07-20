/*************************************************************************************
*			© Copyright MSL Software, S.L., 2012
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHODFGUI.h
*	Description	:
*
*	Author		: 
*	Date created: 4-6-2012
* 	Project		: Archery ODF
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#pragma once
#include <OVR/GUI/ODF2/ODFTHMngr/ODFTHGUI.h>

class CHODFGUI : public ODFTHGUI
{
public:
	CHODFGUI(long id);
	virtual ~CHODFGUI();

	//virtual from ODFGUI
	MSLGUIEx * onNewODFEx(long id);
	ODFBuildMessage * onNewBuildMessage();
};
