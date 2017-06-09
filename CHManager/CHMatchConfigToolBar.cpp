#include "StdAfx.h"
#include "CHManagerApp.h"
#include "CHMatchConfigToolBar.h"

CHMatchConfigToolBar::CHMatchConfigToolBar(long id)
:GToolBar(id)
{
}

CHMatchConfigToolBar::~CHMatchConfigToolBar(void)
{
}

/***** Virtual from MSLGUIEX ****/
LRESULT CHMatchConfigToolBar::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		// Comms
		case UM_COMMS_PACKTRANSACTION	:	return onCommsPackTrn		(wParam, lParam);
		case UM_COMMS_DATA				:	return onCommsData			(wParam, lParam);
	}
	return GToolBar::wndProc(hWnd,message,wParam,lParam);
}

bool CHMatchConfigToolBar::onInit()
{
	doJump(7);
	
	doLabelEx(BT_AUTO_SET, "Auto Set",70,"Auto match member assigment");
	doLabelEx(BT_REMOVE_SET, "Remove Set",70,"Remove match member assigment");
	doLabelEx(BT_CHANGE_SIDE, "Change Side",70,"Change side/color");

	doSeparator();
	
	return true;
}

/***** Virtual From GToolBar  *****/
HINSTANCE CHMatchConfigToolBar::getHInstance(int idCtrl,UINT idRes)
{
	return GUITHManagerApp::m_hGUITHMyModule;
	UNREFERENCED_PARAMETER(idCtrl);	
	UNREFERENCED_PARAMETER(idRes);	
}

void CHMatchConfigToolBar::onLButDown(long id,long x,long y)
{
	sendMsg(UM_LBUTDOWN_TOOLBAR,(LPARAM)id);
	UNREFERENCED_PARAMETER(x);	
	UNREFERENCED_PARAMETER(y);	
}

LRESULT CHMatchConfigToolBar::onRedrawControl(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	return 0;
	UNREFERENCED_PARAMETER(wParam);	
	UNREFERENCED_PARAMETER(lParam);	
}

LRESULT CHMatchConfigToolBar::onCommsPackTrn(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	if(!lParam)	
		return 0;

	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);
	return 1;
}

LRESULT CHMatchConfigToolBar::onCommsData(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	if(!lParam)	return 0;

	CommsMng * pCommsMng=(CommsMng *)lParam;
	GData * pData=pCommsMng->pData;
	if(!pData)
		return 0;

	return 0;
	UNREFERENCED_PARAMETER(wParam);	
}