/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHEntriesGUI.h
*   Description : 
*
*   Author      : Javier Juste
*   Date created: 2-FEb-2009
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
#include <OVR\GUI\GUIMANAGER\GEntriesGUI.h>

class CHEntriesGUI : public GEntriesGUI
{
public:
	CHEntriesGUI(long id);
	virtual ~CHEntriesGUI();

	bool onInit();

protected:

	/***** Extensions *****/
	virtual MSLGUIEx * onNewGUIEx			(long id);

	LRESULT wndProc							(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void onLButDblClick						(long id,long x,long y);
	bool onGridHand							(long id,long x,long y); 
	
	LRESULT onLButDownToolBar				(WPARAM wParam, LPARAM lParam);
	LRESULT onRegisterCreated				(WPARAM wParam, LPARAM lParam);

	/***** Grid Register *****/
	virtual void createGridRegister			();
	virtual bool paintGridRegister			(gui_grid_cell* cell);
	virtual void dblClickGridRegister		(long x,long y);
	virtual void editMasterType				(CHRegister *pRegister);
	
	void fillComboMasterType				();
	void onFideInitialLoad					();
	bool canDeleteInscription				(GInscription * pInscription);

	void calculateSeedsFromRating			(GEvent *pEvent, bool reset);
	void calculateTeamsRatings				(GEvent *pEvent, bool reset);
	short getKConst							(CHInscription *pInscription);
	short getKConst							(CHMember *pMemb);
	short getTeamRating						(CHInscription *pIns);
	
	// reports
	void onReportsAdd();
	void onReportRequest(MSLReportItem  *pReport);
	bool onReportGeneration(CReportManager *pReportMngr,CReportConfig *pReportCfg,MSLReportItem *pReport);
};
