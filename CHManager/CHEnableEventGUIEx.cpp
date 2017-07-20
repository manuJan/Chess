/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHEnableEventGUIEx.cpp
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
#include "CHManagerApp.h"
#include "CHEnableEventGUIEx.h"
#include <OVR/gui/GUITHMANAGER/GTHPhaseGUIEx.h>
#include "..\CHMngtModel\CHEvent.h"
#include <ovr/core/G/GScore.h>

int orderTeamMatchCfgs(const MSLItem** a, const MSLItem** b)
{
	CHTeamMatchsCnfg *pTeamMatchsCnfgA = (CHTeamMatchsCnfg *)(*a);
	CHTeamMatchsCnfg *pTeamMatchsCnfgB = (CHTeamMatchsCnfg *)(*b);
	
	return pTeamMatchsCnfgA->getId() - pTeamMatchsCnfgB->getId();
}


CHEnableEventGUIEx::CHEnableEventGUIEx(long id,GEnableEventGUIEx::TypeControl tCtrl)
:GEnableEventGUIEx(id,tCtrl)
{
}

CHEnableEventGUIEx::~CHEnableEventGUIEx()
{
}

void CHEnableEventGUIEx::createGridEvent()
{
	GEnableEventGUIEx::createGridEvent();

	m_gui.grid_setCellW(GR_EVENT,1,195);
	m_gui.grid_setCellW(GR_EVENT,2, 60);

	m_gui.grid_addColumn(GR_EVENT,"Event Type"	,GUI_JUST_CENTER	,65	,C_EV_TYPE			);
	m_gui.grid_addColumn(GR_EVENT,"Reg Type"	,GUI_JUST_CENTER	,57	,C_EV_REG_TYPE		);
	m_gui.grid_addColumn(GR_EVENT,"Insc."		,GUI_JUST_CENTER	,42	,C_EV_INSCRIPTIONS	);
	m_gui.grid_addColumn(GR_EVENT,"Const Rating",GUI_JUST_CENTER	,65	,C_EV_CONST_RATING	);
	m_gui.grid_addColumn(GR_EVENT,"Bye Pts"		,GUI_JUST_CENTER	,55	,C_EV_BYE_POINTS	);
	m_gui.grid_addColumn(GR_EVENT,"No. Bronzes"	,GUI_JUST_CENTER	,65	,C_EV_BRONZES		);
	m_gui.grid_addColumn(GR_EVENT,"Code Rep."	,GUI_JUST_CENTER	,65	,C_EV_CODE_REPORTS	);
	m_gui.grid_addColumn(GR_EVENT,"Team Cfg"	,GUI_JUST_CENTER	,65	,C_EV_TEAM_CFG		);
	
	//TT
	m_gui.grid_setCellTT(GR_EVENT,m_gui.grid_findCol(GR_EVENT,C_EV_TYPE			),-1,"Event type");
	m_gui.grid_setCellTT(GR_EVENT,m_gui.grid_findCol(GR_EVENT,C_EV_REG_TYPE		),-1,"Register type");
	m_gui.grid_setCellTT(GR_EVENT,m_gui.grid_findCol(GR_EVENT,C_EV_INSCRIPTIONS	),-1,"Number of inscripted");
	m_gui.grid_setCellTT(GR_EVENT,m_gui.grid_findCol(GR_EVENT,C_EV_CONST_RATING	),-1,"Const rating");
	m_gui.grid_setCellTT(GR_EVENT,m_gui.grid_findCol(GR_EVENT,C_EV_BYE_POINTS	),-1,"Winner by bye awarded points");
	m_gui.grid_setCellTT(GR_EVENT,m_gui.grid_findCol(GR_EVENT,C_EV_BRONZES		),-1,"Number of bronze medals");
	m_gui.grid_setCellTT(GR_EVENT,m_gui.grid_findCol(GR_EVENT,C_EV_CODE_REPORTS	),-1,"Code for printouts");
	m_gui.grid_setCellTT(GR_EVENT,m_gui.grid_findCol(GR_EVENT,C_EV_TEAM_CFG		),-1,"Team Configuration");

	// Combo TeamCfgs
	m_gui.doCombo(CB_TEAM_CFG, RC(0,0,0,0));
	fillComboTeamConfig();
}

void CHEnableEventGUIEx::fillComboTeamConfig()
{
	m_gui.combo_reset(CB_TEAM_CFG);
	
	MSLSortedVector vTeamCfgs(CHMemoryDataBase::getCol(__CHTEAMMATCHSCNFG), orderTeamMatchCfgs );
	for (short i=0; i<vTeamCfgs.entries(); i++)
	{
		CHTeamMatchsCnfg *pTeamMatchsCnfg = (CHTeamMatchsCnfg *) vTeamCfgs[i];
		if (pTeamMatchsCnfg)
			m_gui.combo_add(CB_TEAM_CFG, pTeamMatchsCnfg->getLDescription(), (LPARAM) pTeamMatchsCnfg);
	}
}

void CHEnableEventGUIEx::fillGridEvent()
{
	GEnableEventGUIEx::fillGridEvent();
}

bool CHEnableEventGUIEx::paintGridEvent(gui_grid_cell* cell)
{
	CHEvent * pEvent=(CHEvent*)cell->lParamLine;
	if (!pEvent)
		return false;
	
	switch (cell->lParamColumn)
	{
		case C_EV_TYPE:
			m_gui.paint_text(pEvent->getTypeEventAsString());
			break;
		case C_EV_REG_TYPE:
			m_gui.paint_text(pEvent->getRegTypeAsString());
			break;
		case C_EV_INSCRIPTIONS:
			m_gui.paint_text( TOWSTRING(pEvent->getInscriptions()));
			break;
		case C_EV_CONST_RATING:
			m_gui.paint_text( pEvent->getConstRatingStr().toUnicode());
			break;
		case C_EV_BYE_POINTS:
			m_gui.paint_text( pEvent->getPointsByeStr().toUnicode());
			break;
		case C_EV_BRONZES:			
			m_gui.paint_text( pEvent->getTwoBronces()?"2":"1");
			break;		
		case C_EV_CODE_REPORTS:
			m_gui.paint_text( pEvent->getCodeReports().toUnicode());
			break;		
		case C_EV_TEAM_CFG:
			m_gui.paint_text( pEvent->getTeamCfgSDescription());
			break;		
	}
	
	return GEnableEventGUIEx::paintGridEvent(cell);
}

void CHEnableEventGUIEx::onLButDblClick(long id,long x,long y)
{
	if(id==GR_EVENT)
		dblClickGridEvent(x,y);
}

void CHEnableEventGUIEx::dblClickGridEvent(long x, long y)
{
	gui_grid_cell * pCell=m_gui.grid_getCell(GR_EVENT,x,y);
	if(!pCell)
		return;
	
	CHEvent* pEvent = (CHEvent*) pCell->lParamLine;
	if (!pEvent)
		return;

	int col=pCell->lParamColumn;

	if (!canChangeEvent(pEvent, col))
		return;

		 if (col==C_EV_CONST_RATING)
			editConstRating(pEvent);
	else if (col==C_EV_BRONZES)
			editBronzes(pEvent);
	else if (col==C_EV_BYE_POINTS)
			editByePoints(pEvent);	
	else if (col==C_EV_CODE_REPORTS)
			editCodeForReports(pEvent);
	else if (col==C_EV_TEAM_CFG)
			editTeamCfg(pEvent);

	m_gui.redraw(GR_EVENT);
}

void CHEnableEventGUIEx::editConstRating(CHEvent *pEvent)
{
	if (!pEvent)
		return;

	MSLString sOldRating = pEvent->getConstRatingStr();
	MSLString sNewRating = m_gui.grid_showEdit(GR_EVENT,sOldRating,9,"#",1);
	GScore newRating = GScore(sNewRating);
	if (sNewRating!=sOldRating)
	{
		pEvent->setConstRating(newRating.getScore());
		CHSend.toServerDB(pEvent);
	}
}

void CHEnableEventGUIEx::editBronzes(CHEvent *pEvent)
{
	if (!pEvent)
		return;

	short oldValue = pEvent->getTwoBronces();
	pEvent->setTwoBronces( oldValue==1 ? 0 : 1);
	CHSend.toServerDB(pEvent);
}

void CHEnableEventGUIEx::editByePoints(CHEvent *pEvent)
{
	if (!pEvent)
		return;

	MSLString sOldPoints = pEvent->getPointsByeStr();
	MSLString sNewPoints = m_gui.grid_showEdit(GR_EVENT,sOldPoints,9,"#",1);
	GScore newPoints = GScore(sNewPoints);
	if (sNewPoints!=sOldPoints)
	{
		pEvent->setPointsBye(newPoints);
		CHSend.toServerDB(pEvent);
	}
}

void CHEnableEventGUIEx::editCodeForReports(CHEvent *pEvent)
{
	if (!pEvent)
		return;

	MSLString sOld = pEvent->getCodeReports();
	MSLString sNew = m_gui.grid_showEdit(GR_EVENT,sOld,9,0,10);	
	if (sNew!=sOld)
	{
		pEvent->setCodeReports(sNew);
		CHSend.toServerDB(pEvent);
	}
}

void CHEnableEventGUIEx::editTeamCfg(CHEvent *pEvent)
{
	CHTeamMatchsCnfg* pTeamMatchsCnfg=pEvent->getTeamMatchCfg();
	m_gui.combo_selL(CB_TEAM_CFG,(LPARAM)pTeamMatchsCnfg);

	CHTeamMatchsCnfg * pNewTeamMatchsCnfg = (CHTeamMatchsCnfg*) m_gui.grid_showCombo(GR_EVENT, CB_TEAM_CFG);
	if(pNewTeamMatchsCnfg!=pTeamMatchsCnfg && pNewTeamMatchsCnfg)
	{
		pEvent->setIdTeamMatchsCnfg(pNewTeamMatchsCnfg->getId());
		CHSend.toServerDB(pEvent);
	}

}

bool CHEnableEventGUIEx::canChangeEvent(CHEvent *pEvent, int col)
{
	if (pEvent && 
		pEvent->getStatus()>=CHMemoryDataBase::eRunning &&
		col == C_EV_TEAM_CFG)
	{
		MSLMsgBox(m_hWnd, L"The event is running, this value cannot be changed",GUI_ICO_STOP,GUI_MB_OK,L"Events");
		return false;
	}

	return true;
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(pEvent);
}
