/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:	CHUmpireGUIEx.h
*	Description	:   Asignacion de Chair Umpire al Match
*
*	Author		:	Fernando Hicar
*	Date created:   1-Abril-2009
* 	Project		:	Tennis Manager
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#pragma once
#include <ovr/gui/guithmanager/GTHManagerGUI.h>

class CHMatch;
class CHRegister;

class CHUmpireGUIEx : public GTHManagerGUI
{
public:
	CHUmpireGUIEx			(long id,CHMatch * pMatch);
	virtual ~CHUmpireGUIEx	();

	CHMemoryDataBase * getMem		() const;
	GOfficial * getOfficial			();
	MSLWString getNameRegister		(GRegister * pRegister) const;
	MSLWString getNameOfficial		(GOfficial * pOfficial) const;
	MSLWString getNameFunction		(GFunction * pFunction) const;

	/***** Virtual from MSLGUIEX ****/
	bool onInit									();
	bool onGridPaint							(long id,gui_grid_cell* cell);
	void onClick								(long id,LPARAM lParam);
	void onLButDblClick							(long id,long x,long y);
	void onLButDown								(long id,long x,long y);

protected:

	/***** Virtual from MSLGUIEX ****/
	//LRESULT wndProc								(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	/***** Controls *****/
	virtual LRESULT onCreateControl				(WPARAM wParam=0, LPARAM lParam=0);
	virtual LRESULT onFillControl				(WPARAM wParam=0, LPARAM lParam=0);
	virtual LRESULT onRedrawControl				(WPARAM wParam=0, LPARAM lParam=0);

	virtual LRESULT onCommsPackTransaction		(WPARAM wParam,LPARAM lParam);
	virtual LRESULT onComms						(WPARAM wParam,LPARAM lParam);

	/***** Grid Match Members*****/
	mslToolsFcCompare getOrderOfficial			() const;

	void createGridChairUmpire					();
	void fillGridChairUmpire					();
	bool paintGridChairUmpire					(gui_grid_cell* cell);
	void redrawGridChairUmpire					();
	bool handGridChairUmpire					(long x,long y);
	void clickGridChairUmpire					(long x,long y);
	void dblClickGridChairUmpire				(long x,long y);
	
private:
	void setMatchJudge							(GOfficial * pOfficial);
	bool createMatchJudge						(CHRegister * pRegister);
	bool deleteMatchJudge						(GTHMatchJudge * pMatchJudge);

private:
	CHMatch * m_pMatch;
	int		m_orderColOfficial;
};

