/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHInitialLoadGUI.h
*   Description : 
*
*   Author      : Javier Juste
*   Date created: 20-Feb-2010
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

class ARInscriptionLineGUIEx;

class CHInitialLoadGUI : public MSLGUIEx
{
public:
	CHInitialLoadGUI(long id);
	virtual ~CHInitialLoadGUI();

	RECT getRect() const;

protected:

	bool onExit();
	bool onInit();
	void createControls();
	void initControls();

	void onClick       (long id,LPARAM lParam);

	/***** Virtual from MSLGUIEX ****/
	LRESULT wndProc					(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	/***** Controls *****/
	LRESULT onCreateControl			(WPARAM wParam=0, LPARAM lParam=0);
	LRESULT onFillControl			(WPARAM wParam=0, LPARAM lParam=0);
	LRESULT onDestroyControl		(WPARAM wParam=0, LPARAM lParam=0);
	LRESULT onRedrawControl			(WPARAM wParam=0, LPARAM lParam=0);
	LRESULT onHideControl			(WPARAM wParam=0, LPARAM lParam=0);
	LRESULT onShowControl			(WPARAM wParam=0, LPARAM lParam=0);
	LRESULT onRegisterCreated		(WPARAM wParam=0, LPARAM lParam=0);
	LRESULT onLButDownToolBar		(WPARAM wParam=0, LPARAM lParam=0);
	LRESULT onCommsPackTransaction	(WPARAM wParam=0, LPARAM lParam=0);
	LRESULT onComms					(WPARAM wParam=0, LPARAM lParam=0);

	/***** Extensions *****/
	virtual MSLGUIEx * onNewGUIEx	(long id);

	void createInscriptions			();
	void loadEntries				();
	
protected:
	
	HWND m_hWndParent;
	
};
