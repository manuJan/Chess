/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHMatchResultGUIEx.h
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
#include <OVR/gui/GUITHMANAGER/GTHMatchResultGUIEx.h>

class CHMatchResult;

class CHMatchResultGUIEx :	public GTHMatchResultGUIEx
{
public:

	CHMatchResultGUIEx(GTHProgression* pProgression, GTHProgressionData* pProgressionData, long id);
	virtual ~CHMatchResultGUIEx();

	void createGridMatchResults				();
	bool paintHeaderGrid					(gui_grid_cell* cell);
	bool paintGridMatchResults				(gui_grid_cell* cell);

	void onLButDown							(long id,long x,long y);
	void dblClickGridMatchResults 			(int x, int y);	
	void editBib							(CHMatchResult *pMatchResult);
	void editRank							(CHMatchResult *pMatchResult);

	bool canChangeMatchResult				(CHMatchResult *pMatchResult, int col);		
	MSLWString getBib						(CHMatchResult *pMatchResult);
	MSLWString getRank						(CHMatchResult *pMatchResult);

	// Draw
	void draw();

	/***** Extensions *****/
	MSLGUIEx * onNewGUIEx					(long id);

	/***** Functions ******/	
	PFN_ORDER_FC getGridSortMatchResults	() const;

	LRESULT onLButDownToolBar				(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/);

	void onCreateMatchResult				(GTHMatchResult* pMatchResult);

protected:

	PFN_ORDER_FC grid_compare;
};
