#include "StdAfx.h"
#include "CHManagerApp.h"
#include "CHMatchConfigToolBar.h"
#include "resource.h"

#include "..\CHMngtModel\CHMatch.h"
#include "..\CHMngtModel\CHStatisticDefines.h"

CHMatchConfigToolBar::CHMatchConfigToolBar(long id, CHMatch* pMatch, bool autoFinish)
:GToolBar(id)
,m_autoFinish(autoFinish)
,m_pMatch(pMatch)
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
		case UM_REDRAW_CONTROL			:	return onRedrawControl		(wParam, lParam);
		// Comms
		case UM_COMMS_PACKTRANSACTION	:	return onCommsPackTrn		(wParam, lParam);
		case UM_COMMS_DATA				:	return onCommsData			(wParam, lParam);
	}
	return GToolBar::wndProc(hWnd,message,wParam,lParam);
}

bool CHMatchConfigToolBar::onInit()
{
	doJump(7);
	
	bool enable = m_pMatch ? m_pMatch->hasCompetitors() && m_pMatch->getStatus()>=CHMemoryDataBase::eSchedulled : false;

	doLabelEx(BT_AUTO_SET, "Auto Set",70,"Auto match member assigment",IDB_BMP_AUTOSET);	
	doLabelEx(BT_REMOVE_SET, "Remove Set",70,"Remove match member assigment",IDB_BMP_REMOVESET);
	doLabelEx(BT_CHANGE_SIDE, "Change Side",70,"Change side/color",IDB_BMP_CHANGESIDE);

	doSeparator();

	int resultCode = m_pMatch ? m_pMatch->getResultCode() : 0;

	doPress(BT_PRESS_WINNER_WHITE		, "1:0", 35, 1, resultCode == EV_WHITE_WINNER , "Winner white");	
	doPress(BT_PRESS_TIED				, "½:½", 40, 1, resultCode == EV_DRAW , "Tied");
	doPress(BT_PRESS_WINNER_BLACK		, "0:1", 35, 1, resultCode == EV_BLACK_WINNER , "Winner black");
	doPress(BT_PRESS_WINNER_WHITE_F		, "1:0F", 35, 1, resultCode == EV_WHITE_WINNER_F, "Winner white by forfait");
	doPress(BT_PRESS_TIED_F				, "½F:½F", 40, 1, resultCode == EV_DRAW_F , "Tied by forfait");
	doPress(BT_PRESS_WINNER_BLACK_F		, "0F:1", 35, 1, resultCode == EV_BLACK_WINNER_F , "Winner black by forfait");
	doPress(BT_PRESS_EMPTY				, "Empty", 40, 1, false, "Remove results");

	m_gui.setEnable(BT_PRESS_WINNER_WHITE		,enable);
	m_gui.setEnable(BT_PRESS_TIED				,enable);
	m_gui.setEnable(BT_PRESS_WINNER_BLACK		,enable);
	m_gui.setEnable(BT_PRESS_WINNER_WHITE_F		,enable);
	m_gui.setEnable(BT_PRESS_TIED_F				,enable);
	m_gui.setEnable(BT_PRESS_WINNER_BLACK_F		,enable);
	m_gui.setEnable(BT_PRESS_EMPTY				,enable);

	doSeparator();

	doCheck(BT_CHECK_AUTO_FINISH, "Auto Finish", 70, m_autoFinish, "Auto finish match we input result");
	doLabelEx(BT_FINISH, "Finish",50,"Finish match");				
	
	m_gui.setEnable(BT_CHECK_AUTO_FINISH	,enable);
	m_gui.setEnable(BT_FINISH				,enable);

	return true;
}

/***** Virtual From GToolBar  *****/
HINSTANCE CHMatchConfigToolBar::getHInstance(int idCtrl,UINT idRes)
{
	if (idCtrl==BT_AUTO_SET || idCtrl==BT_REMOVE_SET || idCtrl==BT_CHANGE_SIDE)
		return CHManagerApp::m_hCHMyModule;

	return GUITHManagerApp::m_hGUITHMyModule;
	UNREFERENCED_PARAMETER(idCtrl);	
	UNREFERENCED_PARAMETER(idRes);	
}

void CHMatchConfigToolBar::onClick(long id,LPARAM lParam)
{
	SendMessage(getHWndMsgs(),UM_LBUTDOWN_TOOLBAR, id, lParam);
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