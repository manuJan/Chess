/*************************************************************************************
*			© Copyright MSL Software, S.L., 2012
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHODFApp.h
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
#include "Resource.h"
#include <OVR/GUI/ODF2/ODFTHMngr/ODFTHManagerApp.h>

class CHODFApp : public ODFTHManagerApp
{
public:
	CHODFApp();
	
	GMemoryDataBase *	onNewMemory();
	HICON				onGetHIcon() const;
	MSLWString			onGetTitle() const;
	ODFGUI *			onNewODFGUI() const;
	ODF2Model *			onNewModel() const;
	
	virtual MSLString	getDisciplineCode();
};

#define APP_CH CHODFApp

