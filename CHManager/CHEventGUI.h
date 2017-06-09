/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHEventGUI.h
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
#include <OVR\GUI\GUIMANAGER\GEventGUI.h>

class CHEventCriteriaGUIEx;
class CHPhaseGUIEx;
class CHRatingDiffGUIEx;

class CHEventGUI :	public GEventGUI
{
public:
	CHEventGUI(long id);
	virtual ~CHEventGUI();

protected:

	/***** Virtual from MSLAppModule ****/
	LRESULT wndProc			(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	/***** Extensions *****/
	MSLGUIEx * onNewGUIEx	(long id);

	LRESULT onCreateControl (WPARAM wParam=0, LPARAM lParam=0);
	LRESULT onDestroyControl(WPARAM wParam=0, LPARAM lParam=0);
	LRESULT onEventSelected (WPARAM wParam=0, LPARAM lParam=0);

protected:

	CHEventCriteriaGUIEx	* m_pEventCriteriaGUIEx;
	CHPhaseGUIEx			* m_pPhaseGUIEx;
	CHRatingDiffGUIEx		* m_pRatingDiffGUIEx;
};
