/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHEnableEventGUIEx.h
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
#include <OVR\GUI\GUIMANAGER\GEnableEventGUIEx.h>

class CHEvent;
class GTHPhaseGUIEx;

class CHEnableEventGUIEx :	public GEnableEventGUIEx
{
public:
	CHEnableEventGUIEx(long id,GEnableEventGUIEx::TypeControl tCtrl);
	virtual ~CHEnableEventGUIEx();

protected:
		
	// virtual MSLGUIEx
	void onLButDblClick				(long id,long x,long y);

	// Grid Event
	void createGridEvent			();
	void fillGridEvent				();
	bool paintGridEvent				(gui_grid_cell* cell);
	void dblClickGridEvent			(long x, long y);
	void editConstRating			(CHEvent *pEvent);
	void editBronzes				(CHEvent *pEvent);
	void editByePoints				(CHEvent *pEvent);
	void editCodeForReports			(CHEvent *pEvent);
	
	// Other
	bool canChangeEvent				(CHEvent *pEvent, int col);
};
