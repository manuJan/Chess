/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHInitialLoadGUI.cpp
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

#include "StdAfx.h"
#include "CHInitialLoadGUI.h"

CHInitialLoadGUI::CHInitialLoadGUI(long id)
:MSLGUIEx(id)
{
}

CHInitialLoadGUI::~CHInitialLoadGUI()
{	
}

/**** Class Methods *****/
RECT CHInitialLoadGUI::getRect() const
{
	RECT aRect;
	GetClientRect(m_hWnd,&aRect);
	return aRect;
}

bool CHInitialLoadGUI::onExit()
{
	return true;
}
	
bool CHInitialLoadGUI::onInit()
{
	onCreateControl();
	onFillControl();
	return true;
}

/***** Virtual from MSLGUIEX ****/
LRESULT CHInitialLoadGUI::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case UM_REGISTER_CREATED: return onRegisterCreated(wParam, lParam);
		case UM_LBUTDOWN_TOOLBAR: return onLButDownToolBar(wParam, lParam);
	}

	return MSLGUIEx::wndProc(hWnd,message,wParam,lParam);
}

/***** Extensions *****/
MSLGUIEx * CHInitialLoadGUI::onNewGUIEx(long id)
{
	switch(id)
	{
		case ARINSCRIPTIONLINEGUIEX_ID:
		{
			RECT aRect=getRect();			
		}
	}

	return 0;
}

LRESULT CHInitialLoadGUI::onCreateControl(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	if(!wParam || wParam==ARINSCRIPTIONLINEGUIEX_ID)
	{		
	}
	UNREFERENCED_PARAMETER(lParam);
	return 0;
}

LRESULT CHInitialLoadGUI::onFillControl(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	return 0;
}

LRESULT CHInitialLoadGUI::onDestroyControl(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	if(!wParam || wParam==ARINSCRIPTIONLINEGUIEX_ID)
	{
	}
	return 0;
	UNREFERENCED_PARAMETER(lParam);
}

LRESULT CHInitialLoadGUI::onRedrawControl(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	return 0;
}

LRESULT CHInitialLoadGUI::onRegisterCreated(WPARAM wParam, LPARAM lParam)
{
	SendMessage(getHWndMsgs(), UM_REGISTER_CREATED, wParam, lParam);
	return 0;
}

LRESULT CHInitialLoadGUI::onLButDownToolBar(WPARAM wParam, LPARAM lParam)
{
	if (wParam==LX_EXIT)
		dlgClose(IDCANCEL);

	return 0;
	UNREFERENCED_PARAMETER(lParam);
}

LRESULT CHInitialLoadGUI::onCommsPackTransaction(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	return 0;
}

LRESULT CHInitialLoadGUI::onComms(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	return 0;
}


void CHInitialLoadGUI::onClick(long id,LPARAM lParam)
{		
	MSLGUIEx::onClick(id,lParam);
}

void CHInitialLoadGUI::createInscriptions()
{
	
}

void CHInitialLoadGUI::loadEntries()
{
	
}
