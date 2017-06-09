/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHRatingDiffGUIEx.h
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
#include <ovr\gui\mslgui\mslgui.h>

class GMemoryDataBase;

class CHRatingDiffGUIEx : public MSLGUIEx
{
public:
	CHRatingDiffGUIEx(long id);
	virtual ~CHRatingDiffGUIEx();

	// Class Methods
	GMemoryDataBase * getMem						() const;
	RECT getRect									() const;
	
	bool onInit										();

protected:

	bool onGridPaint								(long id,gui_grid_cell* cell);
	void onLButDblClick								(long id,long x,long y);
	void onGridCursor								(long id,long x,long y); 
	bool onGridHand									(long id,long x,long y);

	// Virtual event functions
	void dblClickGridRatingDif	 					(int x, int y);
	void editDifference								(CHRatingDif* pRatingDif);

	//Grid 
	void createGridRatingDif						();
	void fillGridRatingDif							();
	bool paintGridRatingDif						(gui_grid_cell* cell);
		
	/***** Virtual from MSLGUIEX ****/
	LRESULT wndProc									(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	/***** Controls *****/
	LRESULT onCreateControl							(WPARAM wParam=0, LPARAM lParam=0);
	LRESULT onDestroyControl						(WPARAM wParam=0, LPARAM lParam=0);
	LRESULT onFillControl							(WPARAM wParam=0, LPARAM lParam=0);
	LRESULT onRedrawControl							(WPARAM wParam=0, LPARAM lParam=0);
	LRESULT onHideControl							(WPARAM wParam=0, LPARAM lParam=0);
	LRESULT onShowControl							(WPARAM wParam=0, LPARAM lParam=0);
	
	// Comms
	LRESULT onCommsPackTrn							(WPARAM wParam=0, LPARAM lParam=0);
	LRESULT onCommsData								(WPARAM wParam=0, LPARAM lParam=0);
	
	// Virtual Sort Functions
	mslToolsFcCompare getSortRatingDif			() const;
	PFN_ORDER_FC getGridSortRatingDif			() const;
};
