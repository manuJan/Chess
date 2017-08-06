/*************************************************************************************
*			© Copyright MSL Software, S.L., 2009
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHMsgGnralGUI.h
*	Description	:
*
*	Author		: 
*	Date created: 11-1-2010
* 	Project		: AR Manager
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#pragma once
#include <OVR/GUI/GUIManager/GMsgGnralGUI.h>

class CHMemoryDataBase;

class CHMsgGnralGUI : public GMsgGnralGUI
{
public:
	CHMsgGnralGUI(long id);
	virtual ~CHMsgGnralGUI();

	CHMemoryDataBase * getMem() const;

	//Virtual from GMsgGnralGUI
	//void		fillEventsCombo		();
	//void		fillPhasesCombo		();
	MSLString	getHeaderRSC		(GData * pData);
};
