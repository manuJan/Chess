/**************************************************************************************** 
*           � Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHEntriesEventGUIEx.h
*   Description : 
*
*   Author      : Javier Juste
*   Date created: 
*   Project     : CH Manager
*
*   Modification history
*   By      :
*   Date    :
*   Changes :
*
*****************************************************************************************/

#pragma once
#include "CHManagerDefs.h"
#include <OVR\GUI\GUIMANAGER\GEntriesEventGUIEx.h>

class CHEntriesEventGUIEx :	public GEntriesEventGUIEx
{
public:
	CHEntriesEventGUIEx(long id);
	virtual ~CHEntriesEventGUIEx();

protected:

	// virtual MSLGUIEx
	void onLButDblClick						(long id,long x,long y);
	void dblClickGridEntriesEvent			(long x, long y);

	void createGridEvent					();
	bool paintGridEvent						(gui_grid_cell* cell);

	virtual void editRating					(CHInscription* pInscription);
	virtual void editSeed					(CHInscription* pInscription);
	virtual void editKConst					(CHInscription* pInscription);	
};
