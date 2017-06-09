/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHManagerPhaseGUI.h
*   Description : 
*
*   Author      : Javier Juste
*   Date created: 2-FEb-2009
*   Project     : AR Manager
*
*   Modification history
*   By      :
*   Date    :
*   Changes :
*
*****************************************************************************************/

#pragma once
#include "CHManagerDefs.h"
#include <OVR/gui/GUITHMANAGER/GTHManagerPhaseGUI.h>


class CHManagerPhaseGUI : public GTHManagerPhaseGUI
{
public:
	CHManagerPhaseGUI(GTHProgressionData* pProgressionData, GData* pData, long id);
	virtual ~CHManagerPhaseGUI();

	MSLGUIEx * onNewGUIEx	(long id, GData* pData, long idTrigger);
		
protected:

	void onCreateUserControls					();
	void onInitControls							();
	void onInitUserControls						();
	
	bool guiCheckUserPhaseValues		(bool messageBox);
	void setUserPhaseProperties			(GTHPhase* pPhase);

	LRESULT onPhaseBaseSelected(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/);
};
