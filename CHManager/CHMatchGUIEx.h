/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHMatchGUIEx.h
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
#include <OVR/gui/GUITHMANAGER/GTHMatchGUIEx.h>

class CHMatchResult;
class CHMatch;
class CHMatchConfigurationGUI;

class CHMatchGUIEx : public GTHMatchGUIEx
{
public:
	CHMatchGUIEx(GTHProgression* pProgression, GTHProgressionData* pProgressionData, GTHStatusManager* pStatusManager, long id);
	virtual ~CHMatchGUIEx();

protected:

	LRESULT wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	LRESULT onLButDownToolBar			(WPARAM wParam=0, LPARAM lParam=0);

	/***** Extensions *****/
	MSLGUIEx * onNewGUIEx				(long id);

	CHMatch * getMatch					() const;

	void createGridMatches				();
	bool paintHeaderGrid				(gui_grid_cell* cell);
	bool paintGridMatches				(gui_grid_cell* cell);
	MSLWString getDescription			(GTHMatchResult *pMatchResult);

	void dblClickGridMatches			(int x, int y);	
	void editStatus						(CHMatch* pMatch);

	bool canChangeMatchResult			(CHMatchResult* pMatchResult);
	bool typePool						(GData* pData);	

	void initialDraw					();
	void matchConfigurationDlg			();

	bool validComboPoolResult			(GTHPoolResult *pPoolResult, GTHMatchResult* pMatchResult);

private:

	CHMatchConfigurationGUI * m_pDlgMatchConfig;
};
