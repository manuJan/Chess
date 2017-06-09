/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHProgressionGUI.h
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
#include <OVR/gui/GUITHMANAGER/GTHProgressionGUI.h>

class CHProgressionGUI : public GTHProgressionGUI
{
public:
	CHProgressionGUI(long id);
	virtual ~CHProgressionGUI();

	bool onInit();

protected:

	/***** Extensions *****/
	virtual MSLGUIEx * onNewGUIEx		(long id, WPARAM wParam=0, LPARAM lParam=0);

	/**** Data Classes ****/
	virtual void * onNewDataObject		(long id);

	virtual LRESULT onChangeStatus		(WPARAM wParam=0, LPARAM lParam=0);

	// reports
	void onReportsAdd();
	void onReportRequest				(MSLReportItem  *pReport);
	bool onReportGeneration				(CReportManager *pReportMngr,CReportConfig *pReportCfg,MSLReportItem *pReport);

	LRESULT onLButDownToolBar			(WPARAM wParam=0, LPARAM lParam=0);
	virtual bool checkInitialDraw		(GTHPhase* pPhase);
	void guiInitialAssign				();
};
