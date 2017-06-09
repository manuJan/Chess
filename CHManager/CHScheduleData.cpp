/**************************************************************************************** 
*           � Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHScheduleData.h
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


#include "StdAfx.h"
#include "CHManagerApp.h"
#include "CHScheduleData.h"

#include <ovr\core\th\gthmsgdefines.h>
#include <ovr\gui\guithmanager\GTHAvailableMatchGUIEx.h>

CHScheduleData::CHScheduleData(MSLGUIEx* pGUIEx)
:GTHScheduleData(pGUIEx)
{
}

CHScheduleData::~CHScheduleData(void)
{
}

void CHScheduleData::onMatchScheduled(GTHMatch* pMatch)
{	
	GTHScheduleData::onMatchScheduled(pMatch);
}
	
void CHScheduleData::onMatchUndoScheduled(GTHMatch* pMatch)
{
	GTHScheduleData::onMatchUndoScheduled(pMatch);
}