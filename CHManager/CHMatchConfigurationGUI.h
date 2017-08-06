/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:	CHMatchConfigurationGUI.h
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
class CHSubMatchConfigurationGUIEx;

class CHMatchConfigurationGUI : public GTHManagerGUI
{
public:
	CHMatchConfigurationGUI			(long id, GData* pDataSel, CHMatch * pMatch);
	virtual ~CHMatchConfigurationGUI();

	CHMemoryDataBase * getMem		() const;
	void setMatch(CHMatch * pMatch);

	/***** Virtual from MSLGUIEX ****/
	bool onInit									();
	bool onGridPaint							(long id,gui_grid_cell* cell);
	void onLButDblClick							(long id,long x,long y);
	void onClick								(long id,LPARAM lParam);
	bool onGridHand								(long id,long x,long y);

	MSLGUIEx * onNewGUIEx						(long id);

protected:

	/***** Virtual from MSLGUIEX ****/
	LRESULT wndProc								(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	/***** Controls *****/
	virtual LRESULT onCreateControl				(WPARAM wParam=0, LPARAM lParam=0);
	virtual LRESULT onFillControl				(WPARAM wParam=0, LPARAM lParam=0);
	virtual LRESULT onRedrawControl				(WPARAM wParam=0, LPARAM lParam=0);
	   	    LRESULT onChangeUmpire				(WPARAM wParam=0, LPARAM lParam=0);
			LRESULT onGotoNextMatch				(WPARAM wParam=0, LPARAM lParam=0);
			LRESULT onChangeMatch				(WPARAM wParam=0, LPARAM lParam=0);

	virtual LRESULT onCommsPackTransaction		(WPARAM wParam,LPARAM lParam);
	virtual LRESULT onComms						(WPARAM wParam,LPARAM lParam);

	/***** Extensions *****/
	//virtual MSLGUIEx * onNewGUIEx				(long id);

private:

	/***** Grid Match *****/
	void createGridMatch						();
	void fillGridMatch							();
	bool paintGridMatch							(gui_grid_cell* cell);
	void dblClickGridMatch						(long x,long y);
	bool handGridMatch							(int x,int y);
	void redrawGrid								(long idGrid);

	void editStatus								(CHMatch * pMatch, long idGrid);
	void fillComboStatus						(CHMatch * pMatch);
	
	/***** Grid Match Judge *****/
	void createGridMatchJudge					();
	void fillGridMatchJudge						();
	bool paintGridMatchJudge					(gui_grid_cell* cell);
	
	/***** Grid Match Results*****/
	void createGridMatchResults					();
	void fillGridMatchResults					();
	bool paintGridMatchResults					(gui_grid_cell* cell);
	void dblClickGridMatchResults				(long x,long y);

	void paintFlagCompetitor					(CHMatchResult *pMatchResult, gui_grid_cell* cell);
	void editTieResult							(int col);
	
	/***** Grid Match Members*****/
	void createGridMatchMembers					();
	void fillGridMatchMembers					();
	bool paintGridMatchMembers					(gui_grid_cell* cell);
	void dblClickGridMatchMembers				(long x,long y);
	bool handGridMatchMembers					(int x,int y);
		
	void paintFlagCompetitor					(CHRegister *pRegister, gui_grid_cell* cell);
	void painSexRegister						(CHRegister * pRegister);
	void editMatchMember						(CHMatch * pMatch, int col,int y);
	void editSubMatchMember						(CHMatch * pMatch, int col,int y);
	void editSubMatchSide						(CHMatch * pMatch, int col,int y);
	void fillComboMembers						(GTHMatchMember * pMatchMember);

	CHMatch* getPrevMatch						();
	CHMatch* getNextMatch						();

	bool goToNextMatch							();
	bool goToPrevMatch							();

	void getMatchesVectorSel					(MSLSortedVector &vMatches);

private:
	GData * m_pDataSel;
	CHMatch * m_pMatch;
	CHUmpireGUIEx * m_pDlgUmpire;

	CHMatchConfigToolBar* m_pMatchConfigToolBar;
	CHSubMatchConfigurationGUIEx *m_pSubMatchConfigurationGUIEx;
};
