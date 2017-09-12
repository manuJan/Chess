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

#include <ovr/gui/guithmanager/GTHPoolResultGUIEx.h>

class CHPool;
class CHPoolResult;

class CHRankingsGUI : public GTHPoolResultGUIEx
{
public:

	CHRankingsGUI(CHPool * pPool, GTHProgression* pProgression, GTHProgressionData* pProgressionData, long id);
	~CHRankingsGUI();

	LRESULT onFillControl			(WPARAM wParam=0, LPARAM lParam=0);

	virtual MSLGUIEx * onNewGUIEx	(long id);
	void onClick					(long id,LPARAM lParam);
	void createGridPoolResults		();
	bool paintHeaderGrid			(gui_grid_cell* cell);
	void createOtherControls		();
	void fillGridPoolResultsCH		();
	void onLButDblClick				(long id,long x,long y);
	void dblClickGridPoolResultsCH	(int x, int y);
	void editPoolRankingPositionCH	(GTHPoolResult *pPoolResult);
	void editPoolRankingCH			(GTHPoolResult *pPoolResult);
	void insertPoolResultCH			(GTHPoolResult* pPoolResult);
	bool paintGridPoolResults		(gui_grid_cell* cell);
	bool canChangePoolResult		(GTHPoolResult* pPoolResult, int col);

	mslToolsFcCompare getSortPoolResults() const;
	PFN_ORDER_FC getGridSortPoolResults() const;

	void recalculateAllRanks		(CHPoolResult *pPoolResult, short oldRank, short sNewRank);
private:

	CHPool * m_pPool;
};
