/*************************************************************************************
*			© Copyright MSL Software, S.L., 2001
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: GOApp.h
*	Description	:
*
*	Author		: GO Team
*	Date created: 09-06-2009
* 	Project		: Golf Manager
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#pragma once
#include <ovr/gui/guimanager/guimanagerapp.h>
#include <ovr/gui/guithmanager/guithmanager.h>

#include "..\CHMngtModel\CHMatchResult.h"

#include "CHSendingControl.h"

class CHManagerApp : public GUITHManagerApp
{
public:
	CHManagerApp();

	void onInit();
	void createStyles();

	GMemoryDataBase	*	onNewMemory();
	MSLAppModule*		onGetModule(long id) const;
	virtual MSLWString  onGetTitle() const;
	long				onGetAppType() const;	
	MSLWString			getMatchTitle(CHMatch * pMatch,bool lDesc=true);
	HBITMAP				getBmpColor(HINSTANCE hInst,CHMatchResult::side color);
	

public:
	static HINSTANCE m_hCHMyModule;

};

#define APP_CH CHManagerApp

extern CHSendingControl CHSend;

