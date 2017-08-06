/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHManagerPhaseGUI.h
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
#include "CHManagerPhaseGUI.h"
#include "CHManagerPoolGUI.h"
#include <OVR/gui/GUITHMANAGER/GTHPhaseBaseGUIEx.h>

#include "..\CHMngtModel\CHEvent.h"
#include "..\CHMngtModel\CHPhase.h"
#include "..\CHMngtModel\CHPhaseBase.h"

CHManagerPhaseGUI::CHManagerPhaseGUI(GTHProgressionData* pProgressionData, GData* pData, long id)
:GTHManagerPhaseGUI(pProgressionData,pData,id)
{
}

CHManagerPhaseGUI::~CHManagerPhaseGUI()
{
}

MSLGUIEx * CHManagerPhaseGUI::onNewGUIEx	(long id, GData* pData, long idTrigger)
{
	switch(id)
	{
		case GTHMANAGERPOOLGUI_ID:
		{
			char tmp[10];
			sprintf_s(tmp,"%.2d",idTrigger);
			CHManagerPoolGUI * pTHManagerPoolGUI=new CHManagerPoolGUI(getProgressionData(), GTHMANAGERPOOLGUI_ID, pData, tmp, m_gui.getCheck(CH_PH_ISPOOL) );
			pTHManagerPoolGUI->init(m_gui.getHWnd(0),m_hWnd,RC(140,m_YPhase+85,415,m_YPhase+300));
			return pTHManagerPoolGUI;
		}
	}

	return GTHManagerPhaseGUI::onNewGUIEx(id, pData, idTrigger);
}

bool CHManagerPhaseGUI::hasSplits()
{
	return false;
}


void CHManagerPhaseGUI::onCreateUserControls()
{
	RECT rect = getRect();

	int X = rect.left;
	int Y = rect.top;
}

void CHManagerPhaseGUI::onInitControls()
{
	if (m_pDataSel && m_pDataSel->isA()==__CHEVENT)
	{
		CHEvent * pEvent = (CHEvent*)m_pDataSel;
		
		// No Submatches
		m_gui.setTxtN(ED_PH_SUBMATCHES_BYMATCH, pEvent->getTeamMatches());

		setSubMatchesMembers(pEvent->getCfgTeamMembers());
	}

	GTHManagerPhaseGUI::onInitControls();
}

void CHManagerPhaseGUI::onInitUserControls()
{
	CHPhase* pPhase = (CHPhase*)m_pDataSel;
	if (!m_pDataSel)
		return;		


}

LRESULT CHManagerPhaseGUI::onPhaseBaseSelected(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	if (!m_pDataSel ||
		 m_pDataSel->isA()!=__CHEVENT)
		return GTHManagerPhaseGUI::onPhaseBaseSelected(wParam, lParam);

	CHPhaseBase* pPhaseBase = (CHPhaseBase*)lParam;
	if (!pPhaseBase)
		return GTHManagerPhaseGUI::onPhaseBaseSelected(wParam, lParam);
	
	CHEvent * pEvent = (CHEvent*)m_pDataSel;
	
	if (pPhaseBase)
	{
		if (pPhaseBase->getCode()==SWISS_ROUND)
		{
			// No Submatches
			m_gui.setTxtN(ED_PH_SUBMATCHES_BYMATCH, pEvent->getTeamMatches());	
			setSubMatchesMembers(pEvent->getCfgTeamMembers());
		}
		else
		{
			// No Submatches
			m_gui.setTxtN(ED_PH_SUBMATCHES_BYMATCH, pEvent->getTeamMatchesElim());		
			setSubMatchesMembers(pEvent->getCfgTeamMembersElim());
		}
	}

	return GTHManagerPhaseGUI::onPhaseBaseSelected(wParam, lParam);
}

bool CHManagerPhaseGUI::guiCheckUserPhaseValues(bool messageBox)
{
	return true;
	
	UNREFERENCED_PARAMETER(messageBox);
}
	
void CHManagerPhaseGUI::setUserPhaseProperties(GTHPhase* pPhase)
{
	CHPhaseBase * pPhaseBase=0;
	if (m_pTHPhaseBaseGUIEx)
		pPhaseBase = (CHPhaseBase*)m_pTHPhaseBaseGUIEx->getSelectedPhaseBase();
	
	if (!pPhaseBase)
		return;	
}
