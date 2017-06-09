#include "StdAfx.h"
#include "CHManagerApp.h"
#include "CHMatchToolBar.h"
#include "resource.h"

#include "..\CHMngtModel\CHPhase.h"
#include "..\CHMngtModel\CHPool.h"
#include "..\CHMngtModel\CHPoolResult.h"
#include "..\CHMngtModel\CHMatch.h"

CHMatchToolBar::CHMatchToolBar(long id)
:GTHMatchToolBar(id)
{
}

CHMatchToolBar::~CHMatchToolBar(void)
{
}

bool CHMatchToolBar::onInit()
{
	bool ret = GTHMatchToolBar::onInit();

	doLabelEx(LX_PHASE_CHDRAW,"",30,"Initial Draw", IDB_BMP_DRAW );
	doLabelEx(LX_MATCH_CONFIG,"",70,"Match Configuration" ,IDB_BMP_MATCHCONFIG);

	m_gui.setEnable(LX_PHASE_CHDRAW, false);	

	m_gui.setVisible(LX_INSERT_MATCHRESULT,true); 
	m_gui.setVisible(LX_REMOVE_MATCHRESULT,true); 
	
	return ret;
}

HINSTANCE CHMatchToolBar::getHInstance(int idCtrl,UINT idRes)
{
	if (idCtrl==LX_PHASE_CHDRAW || idCtrl==LX_MATCH_CONFIG)
		return CHManagerApp::m_hCHMyModule;

	return GTHMatchToolBar::getHInstance(idCtrl,idRes);
}

LRESULT CHMatchToolBar::onDataSelected(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	GData* pDataSel = (GData*)lParam;
	if (!pDataSel)
		return 0;

	CHPhase* pPhase=0;	

	if ( pDataSel->isA()==__GTHPHASE)
		pPhase = (CHPhase*)pDataSel;
	else if ( pDataSel->isA()==__GTHPOOL )
		pPhase = (CHPhase*) ((CHPool*)pDataSel)->getPhase();
	else if ( pDataSel->isA()==__GTHPOOLRESULT )
		pPhase = (CHPhase*) ((CHPoolResult*)pDataSel)->getPhase();
	else if ( pDataSel->isA()==__GTHMATCH )
		pPhase = (CHPhase*) ((CHMatch*)pDataSel)->getPhase();

	if (pPhase && pPhase->getIsPool() )
		m_gui.setEnable(LX_PHASE_CHDRAW, false);
	else
		m_gui.setEnable(LX_PHASE_CHDRAW, false);
	
	return GTHMatchToolBar::onDataSelected(wParam,lParam);
}



bool CHMatchToolBar::preDoCtrl(int id)
{
	if (id==PR_POOLTABLE_VIEW)
		return true;

	if (id==PR_MAINMATCH_VIEW)
		return true;

	if (id==PR_SUBMATCHES_VIEW)
		return true;

	return true;
}

bool CHMatchToolBar::preDoSeparator(int id)
{
	if (id==SP_MATCH_VIEW)
		return false;

	return true;
}

void CHMatchToolBar::onClick(long id,LPARAM lParam)
{
	switch (id)
	{
		case LX_PHASE_CHDRAW:
		case LX_MATCH_CONFIG:
		{
			SendMessage(getHWndMsgs(),UM_LBUTDOWN_TOOLBAR,id,lParam);
			return;
		}
	}
	return GTHMatchToolBar::onClick(id, lParam);
}