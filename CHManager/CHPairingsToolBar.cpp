#include "StdAfx.h"
#include "CHManagerApp.h"
#include "CHPairingsToolBar.h"
#include "resource.h"

#include "..\CHMngtModel\CHMatch.h"
#include "..\CHMngtModel\CHPool.h"
#include "..\CHMngtModel\CHStatisticDefines.h"

CHPairingsToolBar::CHPairingsToolBar(long id, CHPool* pPool, short selRound)
:GToolBar(id)
,m_pPool(pPool)
,m_selRound(selRound)
{
}

CHPairingsToolBar::~CHPairingsToolBar(void)
{
}

/***** Virtual from MSLGUIEX ****/
LRESULT CHPairingsToolBar::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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

bool CHPairingsToolBar::onInit()
{
	doLabel(LB_ROUND,"Round : ",50,"Round");
	doCombo(CB_ROUND,100);

	doSeparator(7);

	doLabelEx(LX_LOAD_PAIRINGS,"Load Pairings",200,"Load Pairings");
	doLabelEx(LX_LOAD_RESULTS,"Load Results",200,"Load Results");

	fillComboRounds();

	m_gui.combo_selL(CB_ROUND, m_selRound);

	return true;
}

void CHPairingsToolBar::fillComboRounds()
{
	if (!m_pPool)
		return;

	short rounds = m_pPool->getNumRounds();
	for (short i=1;i<=rounds;i++)
	{
		m_gui.combo_add(CB_ROUND,"Round " + TOSTRING(i),i);
	}
}

/***** Virtual From GToolBar  *****/
HINSTANCE CHPairingsToolBar::getHInstance(int idCtrl,UINT idRes)
{
	if (idCtrl==BT_AUTO_SET || idCtrl==BT_REMOVE_SET || idCtrl==BT_CHANGE_SIDE)
		return CHManagerApp::m_hCHMyModule;

	return GUITHManagerApp::m_hGUITHMyModule;
	UNREFERENCED_PARAMETER(idCtrl);	
	UNREFERENCED_PARAMETER(idRes);	
}

void CHPairingsToolBar::onClick(long id,LPARAM lParam)
{
	SendMessage(getHWndMsgs(),UM_LBUTDOWN_TOOLBAR, id, lParam);
}

LRESULT CHPairingsToolBar::onRedrawControl(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	return 0;
	UNREFERENCED_PARAMETER(wParam);	
	UNREFERENCED_PARAMETER(lParam);	
}

LRESULT CHPairingsToolBar::onCommsPackTrn(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	if(!lParam)	
		return 0;

	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);
	return 1;
}

LRESULT CHPairingsToolBar::onCommsData(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	if(!lParam)	return 0;

	CommsMng * pCommsMng=(CommsMng *)lParam;
	GData * pData=pCommsMng->pData;
	if(!pData)
		return 0;

	return 0;
	UNREFERENCED_PARAMETER(wParam);	
}