/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:	CHSubMatchConfigurationGUI.h
*	Description	:   Dlg configuracion de un partido
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

class CHUmpireGUIEx;
class CHMatch;
class CHMatchResult;
class CHMatchMember;
class CHRegister;
class CHMatchConfigToolBar;

class CHSubMatchConfigurationGUIEx : public GTHManagerGUI
{
public:
	CHSubMatchConfigurationGUIEx(long id, CHMatch * pMatch);
	virtual ~CHSubMatchConfigurationGUIEx();

	CHMemoryDataBase * getMem		() const;
	void setMatch(CHMatch * pMatch);

	/***** Virtual from MSLGUIEX ****/
	bool onInit									();
	bool onGridPaint							(long id,gui_grid_cell* cell);
	void onLButDblClick							(long id,long x,long y);
	void onClick								(long id,LPARAM lParam);
	bool onGridHand								(long id,long x,long y);
	void onLButDown								(long id,long x,long y);

	MSLGUIEx * onNewGUIEx						(long id);

protected:

	/***** Virtual from MSLGUIEX ****/
	LRESULT wndProc								(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT onLButDownToolBar					(WPARAM wParam=0, LPARAM lParam=0);

	/***** Controls *****/
	virtual LRESULT onCreateControl				(WPARAM wParam=0, LPARAM lParam=0);
	virtual LRESULT onFillControl				(WPARAM wParam=0, LPARAM lParam=0);
	virtual LRESULT onRedrawControl				(WPARAM wParam=0, LPARAM lParam=0);
	   	    
	virtual LRESULT onCommsPackTransaction		(WPARAM wParam,LPARAM lParam);
	virtual LRESULT onComms						(WPARAM wParam,LPARAM lParam);

	/***** Extensions *****/
	//virtual MSLGUIEx * onNewGUIEx				(long id);

private:

	void editStatus								(CHMatch * pMatch, long idGrid);
	void fillComboStatus						(CHMatch * pMatch);
	void paintFlagCompetitor					(CHMatchResult *pMatchResult, gui_grid_cell* cell);
	
	void createGridSubmatches					();
	void fillGridSubmatches						();
	bool paintGridSubmatches					(gui_grid_cell* cell);
	void dblClickGridSubmatches					(long x,long y);
	bool handGridSubmatches						(int x,int y);
	CHMatch *getSubmatchSelected				();
	CHMatch *selectFirstAvailableSubMatch		();

	void paintFlagCompetitor					(CHRegister *pRegister, gui_grid_cell* cell);
	void painSexRegister						(CHRegister * pRegister);
	void editMatchMember						(CHMatch * pMatch, int col,int y);
	void editSubMatchMember						(CHMatch * pMatch, int col,int y);
	void editSubMatchSide						(CHMatch * pMatch, int col,int y);
	void fillComboMembers						(GTHMatchMember * pMatchMember);

	void subMatchesAutoSet						();
	void subMatchesRemoveSet					();
	void changeSide								(CHMatch *pMatch);	 		
	long getResultCode							(long idCtrl);
	void setResults								(long resultCode);
	void finishMatch							(CHMatch* pMatch);
private:
	
	CHMatch * m_pMatch;
	CHMatchConfigToolBar* m_pMatchConfigToolBar;
	bool m_autoFinish;
};
