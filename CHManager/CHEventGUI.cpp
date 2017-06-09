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

#include "StdAfx.h"
#include "CHEventGUI.h"
#include "CHEnableEventGUIEx.h"
#include "CHEventCriteriaGUIEx.h"
#include "CHPhaseGUIEx.h"
#include "CHRatingDiffGUIEx.h"

CHEventGUI::CHEventGUI(long id)
:GEventGUI(id)
,m_pEventCriteriaGUIEx(0)
,m_pPhaseGUIEx(0)
,m_pRatingDiffGUIEx(0)
{
}

CHEventGUI::~CHEventGUI()
{
	if (m_pEventCriteriaGUIEx)
		delete m_pEventCriteriaGUIEx;

	if (m_pPhaseGUIEx)
		delete m_pPhaseGUIEx;

	if (m_pRatingDiffGUIEx)
		delete m_pRatingDiffGUIEx;
}

LRESULT CHEventGUI::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case UM_EVENT_SELECTED	:	onEventSelected (wParam, lParam); break;
	}

	return GEventGUI::wndProc(hWnd, message, wParam, lParam);
}

MSLGUIEx * CHEventGUI::onNewGUIEx	(long id)
{
	switch(id)
	{
		case GEVENTGUIEX_ID:
		{
			CHEnableEventGUIEx * pEnableEventGUIEx=new CHEnableEventGUIEx(GEVENTGUIEX_ID,GEventGUIEx::eGrid);
			pEnableEventGUIEx->init(m_gui.getHWnd(0),m_hWnd,RC(10,100,790,320));
			return pEnableEventGUIEx;			
		}
		case CHEVENTCRITERIAGUIEX_ID:
		{
			CHEventCriteriaGUIEx * pEventCriteriaGUIEx=new CHEventCriteriaGUIEx(CHEVENTCRITERIAGUIEX_ID);
			pEventCriteriaGUIEx->init(m_gui.getHWnd(0),m_hWnd,RC(795,100,980,340));
			return pEventCriteriaGUIEx;
		}
		case GTHPHASEGUIEX_ID:
		{
			CHPhaseGUIEx * pPhaseGUIEx = new CHPhaseGUIEx(GTHPHASEGUIEX_ID, 0, CHPhaseGUIEx::eGrid, CHPhaseGUIEx::eTop,L"Phases",L"",-1);
			pPhaseGUIEx->init(m_gui.getHWnd(0),m_hWnd,RC(10,365,730,500));
			return pPhaseGUIEx;			
		}
		case CHRATINGDIFGUIEX_ID:
		{
			CHRatingDiffGUIEx * pRatingDiffGUIEx=new CHRatingDiffGUIEx(CHRATINGDIFGUIEX_ID);
			pRatingDiffGUIEx->init(m_gui.getHWnd(0),m_hWnd,RC(730,365,980,825));
			return pRatingDiffGUIEx;	
		}
	}
	
	return GEventGUI::onNewGUIEx(id);
}

LRESULT CHEventGUI::onCreateControl (WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	if(!wParam || wParam==CHEVENTCRITERIAGUIEX_ID)
	{
		if(m_pEventCriteriaGUIEx)
		{
			delete m_pEventCriteriaGUIEx;
			m_pEventCriteriaGUIEx=0;
		}
		
		m_pEventCriteriaGUIEx=(CHEventCriteriaGUIEx*)onNewGUIEx(CHEVENTCRITERIAGUIEX_ID);
	}

	if(!wParam || wParam==GTHPHASEGUIEX_ID)
	{
		if(m_pPhaseGUIEx)
		{
			delete m_pPhaseGUIEx;
			m_pPhaseGUIEx=0;
		}
		
		m_pPhaseGUIEx=(CHPhaseGUIEx*)onNewGUIEx(GTHPHASEGUIEX_ID);	
	}

	if(!wParam || wParam==CHRATINGDIFGUIEX_ID)
	{
		if(m_pRatingDiffGUIEx)
		{
			delete m_pRatingDiffGUIEx;
			m_pRatingDiffGUIEx=0;
		}

		m_pRatingDiffGUIEx=(CHRatingDiffGUIEx*)onNewGUIEx(CHRATINGDIFGUIEX_ID);
	}

	return GEventGUI::onCreateControl(wParam, lParam);
}

LRESULT CHEventGUI::onDestroyControl(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	if(!wParam || wParam==CHEVENTCRITERIAGUIEX_ID)
	{
		if(m_pEventCriteriaGUIEx)
		{
			delete m_pEventCriteriaGUIEx;
			m_pEventCriteriaGUIEx=0;
		}
	}

	if(!wParam || wParam==GTHPHASEGUIEX_ID)
	{
		if(m_pPhaseGUIEx)
		{
			delete m_pPhaseGUIEx;
			m_pPhaseGUIEx=0;
		}
	}

	return GEventGUI::onDestroyControl(wParam, lParam);
}

LRESULT CHEventGUI::onEventSelected (WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	if (m_pEventCriteriaGUIEx)
		SendMessage(m_pEventCriteriaGUIEx->getHWnd(), UM_EVENT_SELECTED, wParam, lParam);

	if (m_pPhaseGUIEx)
		SendMessage(m_pPhaseGUIEx->getHWnd(), UM_EVENT_SELECTED, wParam, lParam);

	if (m_pRatingDiffGUIEx)
		SendMessage(m_pRatingDiffGUIEx->getHWnd(), UM_PHASE_SELECTED, 0, 0);

	return 0;
}

