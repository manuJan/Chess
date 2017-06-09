/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHPhaseGUIEx.h
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
#include <OVR/GUI/GUITHMANAGER/GTHPhaseGUIEx.h>

class CHPhaseGUIEx : public GTHPhaseGUIEx
{
public:
	CHPhaseGUIEx(long id, GEvent* pEvent, GPhaseGUIEx::TypeControl tCtrl,GPhaseGUIEx::TypeTitlePosition tPos,const wchar_t * title,const wchar_t * comboAdd/*=0*/, int phaseOrder/*=-1*/);
	virtual ~CHPhaseGUIEx();

protected:

	void createGridPhase				();
	bool paintGridPhase					(gui_grid_cell* cell);
	
};
