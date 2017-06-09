/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHAvailableMatchGUIEx.h
*   Description : 
*
*   Author      : Javier Juste
*   Date created: 2-Feb-2010
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
#include <OVR/gui/GUITHMANAGER/GTHAvailableMatchGUIEx.h>


class CHAvailableMatchGUIEx : public GTHAvailableMatchGUIEx
{
public:
	CHAvailableMatchGUIEx(GTHScheduleData* pScheduleData, GTHProgressionData * pProgressionData, long id);
	virtual ~CHAvailableMatchGUIEx(void);

};
