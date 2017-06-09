/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHEventCriteriaGUIEx.h
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
class CHEvent;

class CHRankOrder :public GData
{
public:
	CHRankOrder(short pos,short type);
	virtual ~CHRankOrder();

	/**** Virtual methods inherited from GData **********************/
	MSLPack& pack  (MSLPack& pck) const;
	MSLPack& unpack(MSLPack& pck);

	void setKey();

public:

	short m_order;
	short m_rankType;
};

class CHEventCriteriaGUIEx : public MSLGUIEx
{
public:
	CHEventCriteriaGUIEx(long id);
	virtual ~CHEventCriteriaGUIEx();

	// Class Methods
	GMemoryDataBase * getMem						() const;
	RECT getRect									() const;
	MSLString getTypeCriteria						(short typeCrit);
	short getOrderCriteria							(short typeCrit);

	void setOrderCriteria							();

	bool onInit										();

protected:

	bool onGridPaint								(long id,gui_grid_cell* cell);
	void onLButDblClick								(long id,long x,long y);
	void onGridCursor								(long id,long x,long y); 
	bool onGridHand									(long id,long x,long y);

	// Virtual event functions
	void dblClickGridEventCriteria 					(int x, int y);
	void editOrder									(CHRankOrder* pRankOrder);

	//Grid 
	void createGridEventCriteria					();
	void fillGridEventCriteria						();
	bool paintGridEventCriteria						(gui_grid_cell* cell);

	// Other
	void createOtherControls						();

	/***** Virtual from MSLGUIEX ****/
	LRESULT wndProc									(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	/***** Controls *****/
	LRESULT onCreateControl							(WPARAM wParam=0, LPARAM lParam=0);
	LRESULT onDestroyControl						(WPARAM wParam=0, LPARAM lParam=0);
	LRESULT onFillControl							(WPARAM wParam=0, LPARAM lParam=0);
	LRESULT onRedrawControl							(WPARAM wParam=0, LPARAM lParam=0);
	LRESULT onHideControl							(WPARAM wParam=0, LPARAM lParam=0);
	LRESULT onShowControl							(WPARAM wParam=0, LPARAM lParam=0);
	LRESULT onEventSelected							(WPARAM wParam=0, LPARAM lParam=0);
	// Comms
	LRESULT onCommsPackTrn							(WPARAM wParam=0, LPARAM lParam=0);
	LRESULT onCommsData								(WPARAM wParam=0, LPARAM lParam=0);


	// Virtual Sort Functions
	mslToolsFcCompare getSortEventCriteria		() const;
	PFN_ORDER_FC getGridSortEventCriteria		() const;

protected:

	CHEvent* m_pEvent;
	MSLSet colTypes;

};
