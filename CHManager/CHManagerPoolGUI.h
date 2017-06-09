/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHManagerPoolGUI.h
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
#include <OVR/gui/GUITHMANAGER/GTHManagerPoolGUI.h>

class CHManagerPoolGUI : public GTHManagerPoolGUI
{
public:
	
	CHManagerPoolGUI();
	CHManagerPoolGUI(GTHProgressionData* pProgressionData, long id, GData* pData, MSLString idTrigger, bool isPool);
	~CHManagerPoolGUI();
			
	void onInitOtherControls();		
};
