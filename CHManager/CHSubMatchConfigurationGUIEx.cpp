/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:	CHSubMatchConfigurationGUIEx.cpp
*	Description	:   Dlg configuracion de un partido
*
*	Author		:	Fernando Hicar
*	Date created:   1-Abril-2009
* 	Project		:	Tennis UDP
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "StdAfx.h"
#include "CHSubMatchConfigurationGUIEx.h"
#include "CHManagerApp.h"
#include "CHManagerDefs.h"
#include <OVR/CORE/TH/GTHMsgDefines.h>
#include "CHUmpireGUIEx.h"
#include "CHStatusManager.h"
#include "CHProgression.h"
#include "CHMatchConfigToolBar.h"
#include "CHEventControlOperations.h"

#include "..\CHMngtModel\CHPhase.h"
#include "..\CHMngtModel\CHPool.h"
#include "..\CHMngtModel\CHMatch.h"
#include "..\CHMngtModel\CHMatchResult.h"
#include "..\CHMngtModel\CHRegister.h"
#include "..\CHMngtModel\CHMember.h"
#include "..\CHMngtModel\CHInscription.h"
#include "..\CHMngtModel\CHStatisticDefines.h"

CHSubMatchConfigurationGUIEx::CHSubMatchConfigurationGUIEx(long id, CHMatch * pMatch)
:GTHManagerGUI(id)
,m_pMatch(pMatch)
,m_pMatchConfigToolBar(0)
,m_autoFinish(true)
{
}

CHSubMatchConfigurationGUIEx::~CHSubMatchConfigurationGUIEx()
{	
}

CHMemoryDataBase * CHSubMatchConfigurationGUIEx::getMem() const
{
	return (CHMemoryDataBase*)GMemoryDataBase::getMem();
}

void CHSubMatchConfigurationGUIEx::setMatch(CHMatch * pMatch)
{
	m_pMatch = pMatch;

	if (m_pMatchConfigToolBar)
	{
		delete m_pMatchConfigToolBar;
		m_pMatchConfigToolBar=0;
	}
	
	onCreateControl(CHMATCHCONFIGURATION_TB);
}

bool CHSubMatchConfigurationGUIEx::onInit()
{	
	onCreateControl	();
	onFillControl	();
	
	return true;
}

bool CHSubMatchConfigurationGUIEx::onGridPaint(long id,gui_grid_cell* cell)
{
	if(id==GR_SUBMATCHES_CNF)
		return paintGridSubmatches(cell);

	return false;
}

void CHSubMatchConfigurationGUIEx::onLButDblClick(long id,long x,long y)
{
	 if(id==GR_SUBMATCHES_CNF)
		dblClickGridSubmatches(x,y);
}

void CHSubMatchConfigurationGUIEx::onClick(long id,LPARAM lParam)
{

	GTHManagerGUI::onClick(id,lParam);
}

bool CHSubMatchConfigurationGUIEx::onGridHand(long id,long x,long y)
{
	return false;
}

void CHSubMatchConfigurationGUIEx::onLButDown(long id,long x,long y)
{
	gui_grid_cell * pCell=m_gui.grid_getCell(GR_SUBMATCHES_CNF,x,y);
	if(!pCell)
		return;

	CHMatch* pMatch = (CHMatch*)pCell->lParamLine;
	if (m_pMatchConfigToolBar)
	{
		delete m_pMatchConfigToolBar;
		m_pMatchConfigToolBar=0;
	}

	onCreateControl(CHMATCHCONFIGURATION_TB);
}

/***** Virtual from MSLGUIEX ****/
LRESULT CHSubMatchConfigurationGUIEx::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case UM_CHANGE_MATCH	: return onChangeMatch(wParam, lParam);
		case UM_LBUTDOWN_TOOLBAR: return onLButDownToolBar(wParam, lParam);
	}

	return GTHManagerGUI::wndProc(hWnd,message,wParam,lParam);
}

LRESULT CHSubMatchConfigurationGUIEx::onLButDownToolBar(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	switch(wParam)
	{
		case BT_AUTO_SET:
			subMatchesAutoSet();
			break;

		case BT_REMOVE_SET:
			subMatchesRemoveSet();
			break;

		case BT_CHANGE_SIDE:
		{
			CHMatch* pMatch = getSubmatchSelected();
			changeSide(pMatch);
			break;
		}
		case BT_PRESS_WINNER_WHITE:
		case BT_PRESS_TIED:			
		case BT_PRESS_WINNER_BLACK:
		case BT_PRESS_WINNER_WHITE_F:
		case BT_PRESS_TIED_F:
		case BT_PRESS_WINNER_BLACK_F:
		case BT_PRESS_EMPTY:
			setResults ( getResultCode(wParam));
			break;
		case BT_CHECK_AUTO_FINISH:
			m_autoFinish=!m_autoFinish;
			break;
		case BT_FINISH:
			CHMatch* pMatch = getSubmatchSelected();
			finishMatch(pMatch);
			break;

	}

	return 0;
	UNREFERENCED_PARAMETER(lParam);
}

LRESULT CHSubMatchConfigurationGUIEx::onChangeMatch(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	redrawGridSubmatches();
	return 0;
}

long CHSubMatchConfigurationGUIEx::getResultCode(long idCtrl)
{
	switch (idCtrl)
	{
		case BT_PRESS_WINNER_WHITE:
			return EV_WHITE_WINNER;

		case BT_PRESS_TIED:			
			return EV_DRAW;

		case BT_PRESS_WINNER_BLACK:
			return EV_BLACK_WINNER;

		case BT_PRESS_WINNER_WHITE_F:
			return EV_WHITE_WINNER_F;

		case BT_PRESS_TIED_F:
			return EV_DRAW_F;

		case BT_PRESS_WINNER_BLACK_F:
			return EV_BLACK_WINNER_F;

		case BT_PRESS_EMPTY:
			return EV_EMPTY;
	}
	return EV_EMPTY;
}

LRESULT CHSubMatchConfigurationGUIEx::onCreateControl (WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	UNREFERENCED_PARAMETER(lParam);

	if(!wParam || wParam==GR_SUBMATCHES_CNF)
		createGridSubmatches();

	if(!wParam || wParam==CHMATCHCONFIGURATION_TB)
	{
		if (m_pMatchConfigToolBar)
		{
			delete m_pMatchConfigToolBar;
			m_pMatchConfigToolBar=0;
		}

		m_pMatchConfigToolBar = (CHMatchConfigToolBar*) onNewGUIEx(CHMATCHCONFIGURATION_TB);
	}

	return 1;
}

LRESULT CHSubMatchConfigurationGUIEx::onFillControl(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	UNREFERENCED_PARAMETER(lParam);

	if(!wParam || wParam==GR_SUBMATCHES_CNF)
		fillGridSubmatches();

	return 0;
}

LRESULT CHSubMatchConfigurationGUIEx::onRedrawControl(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	UNREFERENCED_PARAMETER(lParam);

	if(!wParam || wParam==GR_SUBMATCHES_CNF)
		m_gui.redraw(GR_SUBMATCHES_CNF);
	return 0;
}


/***** Extensions *****/
MSLGUIEx * CHSubMatchConfigurationGUIEx::onNewGUIEx(long id)
{
	switch(id)
	{
		case CHMATCHCONFIGURATION_TB:
		{
			RECT rect = getRect();

			CHMatch* pMatch = getSubmatchSelected();
			if (!pMatch)
				pMatch=m_pMatch;

			CHMatchConfigToolBar * pMatchConfigToolBar= new CHMatchConfigToolBar(CHMATCHCONFIGURATION_TB, pMatch, m_autoFinish);
			pMatchConfigToolBar->initToolBar(m_gui.getHWnd(0),m_hWnd,GToolBar::eTop,34,0,0,rect.right-rect.left-16);
			return pMatchConfigToolBar;	
		}		
	}
	return 0;
}

void CHSubMatchConfigurationGUIEx::editStatus(CHMatch *pMatch, long idGrid)
{
	if(!pMatch)
		return;

	if(pMatch->getStatus() < CHMemoryDataBase::eSchedulled)
	{
		MSLMsgBox(m_hWnd, L"You can't change the status here.\nThe match is not in Schedule",GUI_ICO_WARNING,GUI_MB_OK,_T("Match Status"));
		return;
	}

	fillComboStatus(pMatch);

	unsigned char nOld=pMatch->getStatus();
	m_gui.combo_selL(idGrid,(LPARAM)nOld);	

	int nNew=m_gui.grid_showCombo(idGrid,CB_SUBMATCH_CNF);
	if(nNew!=-1)
	{
		CHStatusManager aStManager;
		aStManager.setStatus(pMatch ,(unsigned char)nNew,false);
		m_gui.redraw(idGrid);
		
		PostMessage(getHWndMsgs(),UM_REDRAW_CONTROL,0,0);
		SendMessage(getHWndMsgs(),UM_CHANGE_MATCH,0,0);
	}
}

void CHSubMatchConfigurationGUIEx::fillComboStatus(CHMatch * pMatch)
{
	m_gui.combo_reset(CB_SUBMATCH_CNF);

	if(pMatch->getStatus()==CHMemoryDataBase::eSchedulled)
	{
		GStatus * pStatus=CHMemoryDataBase::findStatus(CHMemoryDataBase::eStartList);
		if(pStatus)
			m_gui.combo_add(CB_SUBMATCH_CNF,pStatus->getLDescription(),CHMemoryDataBase::eStartList);
	}
	else if(pMatch->getStatus()==CHMemoryDataBase::eStartList)
	{
		GStatus * pStatus=CHMemoryDataBase::findStatus(CHMemoryDataBase::eSchedulled);
		if(pStatus)
			m_gui.combo_add(CB_SUBMATCH_CNF,pStatus->getLDescription(),CHMemoryDataBase::eSchedulled);
	}
	else if(pMatch->getStatus()==CHMemoryDataBase::eFinished)
	{
		GStatus * pStatus=CHMemoryDataBase::findStatus(CHMemoryDataBase::eStartList);
		if(pStatus)
			m_gui.combo_add(CB_SUBMATCH_CNF,pStatus->getLDescription(),CHMemoryDataBase::eStartList);
	}
	else if(pMatch->getStatus()==CHMemoryDataBase::eUnofficial)
	{
		GStatus * pStatus=CHMemoryDataBase::findStatus(CHMemoryDataBase::eFinished);
		if(pStatus)
			m_gui.combo_add(CB_SUBMATCH_CNF,pStatus->getLDescription(),CHMemoryDataBase::eFinished);
	}
}


void CHSubMatchConfigurationGUIEx::paintFlagCompetitor(CHMatchResult *pMatchResult, gui_grid_cell* cell)
{
	UNREFERENCED_PARAMETER(cell);

	if (!pMatchResult)
		return;

	HBITMAP hBmp=flag_getSize(pMatchResult->getGroup(),30,20); 
	if (hBmp)
	{
		m_gui.paint_userBmp(hBmp,2,2,false);
		::DeleteObject(hBmp);
	}	
	m_gui.paint_textAt(MSLWString(pMatchResult->getGroup()),5,20,GUI_ID_FNT_B,GUI_RGB_BLACK);
}

void CHSubMatchConfigurationGUIEx::paintFlagCompetitor(CHRegister *pRegister, gui_grid_cell* cell)
{
	UNREFERENCED_PARAMETER(cell);

	if (!pRegister)
		return;

	HBITMAP hBmp=flag_getSize(pRegister->getGroup(),20,10); 
	if (hBmp)
	{
		m_gui.paint_userBmp(hBmp,2,2,false);
		::DeleteObject(hBmp);
	}	
	m_gui.paint_textAt(MSLWString(pRegister->getGroup()),3,11,GUI_ID_FNT_MIN,GUI_RGB_BLACK);
}

void CHSubMatchConfigurationGUIEx::painSexRegister(CHRegister * pRegister)
{
	if(!pRegister)
		return;

	HBITMAP hBmp=((CHManagerApp*)MSLAPP)->getBmpSex(GUIManagerApp::m_hGUIMyModule,pRegister->getSex(),pRegister->getType());
	if (hBmp)
	{
		m_gui.paint_userBmp(hBmp,23,3,true);
		::DeleteObject(hBmp);
	}
}

/***** Grid Sub Match *****/
void CHSubMatchConfigurationGUIEx::createGridSubmatches()
{
	if (!m_pMatch)
		return;

	RECT aRc=getRect();

	int Y=aRc.top+35;
	m_gui.doLbl(LB_SUBMATCHES_TITLE,RC(aRc.left,Y,aRc.right-16,Y+16),"Sub-matches",GUIM_ID_STY_TITLE);

	Y+=18;

	m_gui.doGrid(GR_SUBMATCHES_CNF,RC(aRc.left,Y,aRc.right-16,Y+120),GUI_ID_STY_BOR,GUI_ID_STY_SEL,25);

	m_gui.grid_addColumn(GR_SUBMATCHES_CNF,"Date"	  ,GUI_JUST_CENTER,80 ,C_DATE_SUBMATCH_CNF);
	m_gui.grid_addColumn(GR_SUBMATCHES_CNF,"Time"	  ,GUI_JUST_CENTER,50 ,C_SESSI_SUBMATCH_CNF);
	m_gui.grid_addColumn(GR_SUBMATCHES_CNF,"Submatch" ,GUI_JUST_CENTER,50 ,C_SUBMC_SUBMATCH_CNF);
	m_gui.grid_addColumn(GR_SUBMATCHES_CNF,"Table"	  ,GUI_JUST_CENTER,50 ,C_COURT_SUBMATCH_CNF);
	m_gui.grid_addColumn(GR_SUBMATCHES_CNF,"Status"	  ,GUI_JUST_CENTER,90 ,C_STATU_SUBMATCH_CNF);	
	m_gui.grid_addColumn(GR_SUBMATCHES_CNF,"Home"	  ,GUI_JUST_CENTER,125,C_HOME_SUBMATCH_CNF);
	m_gui.grid_addColumn(GR_SUBMATCHES_CNF,"C.H"	  ,GUI_JUST_CENTER,35 ,C_HOME_COL_SUBMATCH_CNF);
	m_gui.grid_addColumn(GR_SUBMATCHES_CNF,"Away"	  ,GUI_JUST_CENTER,125,C_AWAY_SUBMATCH_CNF);
	m_gui.grid_addColumn(GR_SUBMATCHES_CNF,"C.A"	  ,GUI_JUST_CENTER,35 ,C_AWAY_COL_SUBMATCH_CNF);
	m_gui.grid_addColumn(GR_SUBMATCHES_CNF,"Res"	  ,GUI_JUST_CENTER,30 ,C_AWAY_COL_RESULT_CNF);	

	m_gui.grid_setLineColor(GR_SUBMATCHES_CNF,GUI_RGB_OFF,GUI_RGB_OFF); 	
	m_gui.doCombo(CB_SUBMATCH_CNF,RC(0,0,0,0));
	m_gui.doCombo(CB_MATCHMEMBERS_CNF,RC(0,0,0,0));
}

void CHSubMatchConfigurationGUIEx::fillGridSubmatches()
{
	m_gui.grid_reset(GR_SUBMATCHES_CNF);
	if(m_pMatch)
	{
		CHEvent * pEvent = (CHEvent * )m_pMatch->getEvent();

		MSLSortedVector vSubmatches;
		if (pEvent && pEvent->getSubMatches())
		{
			if (!m_pMatch->getSubCode())
				m_pMatch->getSubMatchesVector(vSubmatches);
			else
				vSubmatches.insert(m_pMatch);
		}
		else
		{
			vSubmatches.insert(m_pMatch);
		}
		
		for (short i=0;i<vSubmatches.entries();i++)
		{
			CHMatch* pMatch = (CHMatch*)vSubmatches[i];
			m_gui.grid_add(GR_SUBMATCHES_CNF,(LPARAM)pMatch);			

			m_gui.grid_setCellSym(GR_SUBMATCHES_CNF,m_gui.grid_findCol(GR_SUBMATCHES_CNF,C_STATU_SUBMATCH_CNF),i);
			m_gui.grid_setCellSym(GR_SUBMATCHES_CNF,m_gui.grid_findCol(GR_SUBMATCHES_CNF,C_HOME_SUBMATCH_CNF),i);
			m_gui.grid_setCellSym(GR_SUBMATCHES_CNF,m_gui.grid_findCol(GR_SUBMATCHES_CNF,C_AWAY_SUBMATCH_CNF),i);
		}
	}

	selectFirstAvailableSubMatch();
}

bool CHSubMatchConfigurationGUIEx::paintGridSubmatches(gui_grid_cell* cell)
{
	if(cell->y==-1 || !cell->lParamLine)
		return false;
	

	CHMatch * pMatch=(CHMatch*)cell->lParamLine;
	
	switch (cell->lParamColumn)
	{
	case C_DATE_SUBMATCH_CNF:
		cell->txt=pMatch->getStartDateAsString("%d/%m/%Y");
		break;
	case C_SESSI_SUBMATCH_CNF:
		cell->txt=MSLWString(pMatch->getStartTimeAsString("%H:%M"));
		break;	
	case C_SUBMC_SUBMATCH_CNF:
		cell->txt=TOWSTRING(pMatch->getSubCode());
		break;
	case C_COURT_SUBMATCH_CNF:
		cell->txt=pMatch->getCourtLDescription();
		break;
	case C_STATU_SUBMATCH_CNF:
		cell->txt=pMatch->getStatusLDescription();
		break;	
	case C_HOME_SUBMATCH_CNF:
		{
			CHMatchResult * pWhite = (CHMatchResult *) pMatch->getWhite();
			if (pMatch->getSubCode())
			{
				GTHMatchMember *pMM = pWhite ? pWhite->getMatchMember(0) : 0;
				if (pMM && 
					pMM->getRegister())
				{
					paintFlagCompetitor((CHRegister*)pMM->getRegister(),cell);
					painSexRegister((CHRegister*)pMM->getRegister());
					m_gui.paint_textAt(pMM->getPrnSName(),40,4,GUI_ID_FNT);
				}
			}
			else
			{
				if (pWhite && 
					pWhite->getRegister())
				{
					paintFlagCompetitor((CHRegister*)pWhite->getRegister(),cell);
					painSexRegister((CHRegister*)pWhite->getRegister());
					m_gui.paint_textAt(pWhite->getPrnSName(),40,4,GUI_ID_FNT);
				}			
			}
			break;
		}
	case C_HOME_COL_SUBMATCH_CNF:
		{
			CHMatchResult * pWhite = (CHMatchResult *) pMatch->getWhite();
			if (pWhite)			
			{
				CHMatchResult::side color = CHMatchResult::side(pWhite->getColor());
				HBITMAP hBmp=((CHManagerApp*)MSLAPP)->getBmpColor(CHManagerApp::m_hCHMyModule,color);
				if (hBmp)
				{
					m_gui.paint_userBmp(hBmp,10,3,true);
					::DeleteObject(hBmp);				
				}
			}
			break;
		}
	case C_AWAY_SUBMATCH_CNF:
		{
			CHMatchResult * pBlack = (CHMatchResult *) pMatch->getBlack();
			if (pMatch->getSubCode())
			{
				GTHMatchMember *pMM = pBlack ? pBlack->getMatchMember(0) : 0;
				if (pMM && pMM->getRegister())
				{
					paintFlagCompetitor((CHRegister*)pMM->getRegister(),cell);
					painSexRegister((CHRegister*)pMM->getRegister());
					m_gui.paint_textAt(pMM->getPrnSName(),40,4,GUI_ID_FNT);
				}
			}
			else
			{
				if (pBlack && pBlack->getRegister())
				{
					paintFlagCompetitor((CHRegister*)pBlack->getRegister(),cell);
					painSexRegister((CHRegister*)pBlack->getRegister());
					m_gui.paint_textAt(pBlack->getPrnSName(),40,4,GUI_ID_FNT);
				}
			}
			break;
		}
	case C_AWAY_COL_SUBMATCH_CNF:
		{
			CHMatchResult * pBlack = (CHMatchResult *) pMatch->getBlack();
			if (pBlack)			
			{
				CHMatchResult::side color = CHMatchResult::side(pBlack->getColor());
				HBITMAP hBmp=((CHManagerApp*)MSLAPP)->getBmpColor(CHManagerApp::m_hCHMyModule,color);
				if (hBmp)
				{
					m_gui.paint_userBmp(hBmp,10,3,true);
					::DeleteObject(hBmp);				
				}
			}
			break;
		}
		case C_AWAY_COL_RESULT_CNF:
		{
			cell->txt=pMatch->getResultAsString().toUnicode();
			break;
		}
	}
	
	
	return false;
}

void CHSubMatchConfigurationGUIEx::dblClickGridSubmatches(long x,long y)
{
	gui_grid_cell * pCell=m_gui.grid_getCell(GR_SUBMATCHES_CNF,x,y);
	if(!pCell)
		return;

	int col=pCell->lParamColumn;

	CHMatch* pMatch = (CHMatch*) pCell->lParamLine;

	if(col==C_STATU_SUBMATCH_CNF)
		editStatus(pMatch, GR_SUBMATCHES_CNF );
	else if(col==C_HOME_SUBMATCH_CNF)
		editSubMatchMember(pMatch, C_HOME_SUBMATCH_CNF,y);
	else if(col==C_AWAY_SUBMATCH_CNF)
		editSubMatchMember(pMatch, C_AWAY_SUBMATCH_CNF,y);
	else if(col==C_HOME_COL_SUBMATCH_CNF ||
			col==C_AWAY_COL_SUBMATCH_CNF)
		editSubMatchSide(pMatch, C_HOME_COL_SUBMATCH_CNF,y);

}

void CHSubMatchConfigurationGUIEx::redrawGridSubmatches	()
{
	m_gui.redraw(GR_SUBMATCHES_CNF);
}

bool CHSubMatchConfigurationGUIEx::handGridSubmatches(int x,int y)
{
	gui_grid_cell * pCell=m_gui.grid_getCell(GR_SUBMATCHES_CNF,x,y);
	if(!pCell)
		return false;

	if(pCell->lParamColumn==C_STATU_SUBMATCH_CNF)
		return true;

	return false;
}

void CHSubMatchConfigurationGUIEx::editSubMatchMember(CHMatch *pMatch, int col, int y)
{
	if(!pMatch)
		return;

	if(pMatch && pMatch->getStatus()>=CHMemoryDataBase::eRunning)
	{
		MSLMsgBox(m_hWnd, L"You can't change members.\nThe Match is started",GUI_ICO_WARNING,GUI_MB_OK,_T("Match Type Result"));
		return;
	}

	GTHMatchMember * pMM=0;
	if(col==C_HOME_SUBMATCH_CNF)
	{
		CHMatchResult * pMRH=(CHMatchResult *)pMatch->getHome();
		pMM=(GTHMatchMember *)(pMRH?pMRH->getMatchMember(0):0);
	}
	else if(col==C_AWAY_SUBMATCH_CNF)
	{
		CHMatchResult * pMRA=(CHMatchResult *)pMatch->getAway();
		pMM=(GTHMatchMember *)(pMRA?pMRA->getMatchMember(0):0);
	}

	if(!pMM)
		return;

	fillComboMembers(pMM);

	CHMember * pOldMember= (CHMember*)pMM->getMember();
	m_gui.combo_selL(CB_MATCHMEMBERS_CNF,(LPARAM)pOldMember);	

	CHMember * pNewMember=(CHMember *)m_gui.grid_showCombo(GR_SUBMATCHES_CNF,CB_MATCHMEMBERS_CNF);
	if(long(pNewMember)!=-1 && pOldMember!=pNewMember)
	{
		pMM->setMember(pNewMember);
		//redrawGrid(GR_MATCHMEMBERS_CNF);

		SendMessage(getHWndMsgs(),UM_CHANGE_MATCH,0,0);

		APP::out(*pMM);
		APP::out(TRN_SET_MATCHMEMBER); //TRN_CHANGE_MATCH_MEMBERS
	}
}

void CHSubMatchConfigurationGUIEx::editSubMatchSide(CHMatch * pMatch, int col,int y)
{
	changeSide(pMatch);
}

CHMatch *CHSubMatchConfigurationGUIEx::getSubmatchSelected()
{
	return (CHMatch *) m_gui.grid_selGetLParam(GR_SUBMATCHES_CNF);
}


void CHSubMatchConfigurationGUIEx::fillComboMembers(GTHMatchMember * pMatchMember)
{
	m_gui.combo_reset(CB_MATCHMEMBERS_CNF);

	if(!pMatchMember)
		return;

	CHInscription * pInscription=(CHInscription*)pMatchMember->getMatchResult()->getInscription();
	if(!pInscription)
		return;

	m_gui.combo_add(CB_MATCHMEMBERS_CNF,L"None",(LPARAM)0);

	MSLSortedVector vMembers;
	pInscription->getMembersVector(vMembers);

	CHMember * pMember=0;
	for(int i=0 ; i<vMembers.entries();i++)
	{
		pMember=(CHMember*)vMembers[i];
		if(pMember->getType()==GRegister::individual)
			m_gui.combo_add(CB_MATCHMEMBERS_CNF,pMember->getPrnLName(),(LPARAM)pMember);
	}
}

LRESULT CHSubMatchConfigurationGUIEx::onCommsPackTransaction(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	MSLTransaction * pt=(MSLTransaction*)lParam;

	if(!pt)
		return 0;

	switch(pt->getTrnId())
	{
		case TRN_SET_REGISTER:	  //nombres
			m_gui.redraw(GR_MATCHJUDGE_CNF);
			m_gui.redraw(GR_MATCHRESULTS_CNF);
			m_gui.redraw(GR_MATCHMEMBERS_CNF);
			break;
		case TRN_SET_MATCHMEMBER: //cambio matchMembers (TEAM)
			m_gui.redraw(GR_MATCHMEMBERS_CNF);
			break;
		case TRN_SET_MATCHRESULT: //cambio mathcResult
			m_gui.redraw(GR_MATCHRESULTS_CNF);
			break;
		case TRN_SET_MATCH:		 //cambio matchMembers (TEAM)
		case TRN_CHANGE_MATCH_STATUS:
		case TRN_SET_EC_HISTORIC:
			m_gui.redraw(GR_MATCH_CNF);
			break;
	}

	return 1;
}

LRESULT CHSubMatchConfigurationGUIEx::onComms(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	/*if(!lParam)	return 0;

	CommsMng * pCommsMng=(CommsMng *)lParam;
	GData * pData=pCommsMng->pData;
	if(!pData)
		return 0;*/

	return 1;
}

void CHSubMatchConfigurationGUIEx::subMatchesAutoSet()
{
	CHProgression aProgression(this);
	aProgression.setAutoSubMatchesAssign(m_pMatch);

	m_gui.redraw(GR_SUBMATCHES_CNF);

	SendMessage(getHWndMsgs(),UM_CHANGE_MATCH,0,0);
}

void CHSubMatchConfigurationGUIEx::subMatchesRemoveSet()
{
	CHProgression aProgression(this);
	aProgression.removeAutoSubMatchesAssign(m_pMatch);

	m_gui.redraw(GR_SUBMATCHES_CNF);

	SendMessage(getHWndMsgs(),UM_CHANGE_MATCH,0,0);
}

void CHSubMatchConfigurationGUIEx::changeSide(CHMatch *pMatch)
{
	CHProgression aProgression(this);
	aProgression.changeSide(pMatch);

	m_gui.redraw(GR_SUBMATCHES_CNF);
}

void CHSubMatchConfigurationGUIEx::finishMatch(CHMatch* pMatch)
{
	if (!pMatch)
	{
		MSLMsgBox(m_hWnd, L"Please select a match",GUI_ICO_STOP,GUI_MB_OK,L"CHManager");
		return;
	}

	CHEventControlOperations eventControlOp(this);
	eventControlOp.finishMatch(pMatch,true);
}

void CHSubMatchConfigurationGUIEx::setResults(long resultCode)
{
	CHMatch* pMatch = getSubmatchSelected();
	if (!pMatch)
		selectFirstAvailableSubMatch();
	
	pMatch = getSubmatchSelected();
	if (!pMatch)
	{
		sendMsg(UM_GOTO_NEXT_MATCH,0);	
		pMatch = getSubmatchSelected();
	}
	if (!pMatch)
	{
		MSLMsgBox(m_hWnd, L"No more available matches",GUI_ICO_STOP,GUI_MB_OK,L"CHManager");
		return;
	}
	
	CHEventControlOperations eventControlOp(this);
	eventControlOp.setScore( resultCode, pMatch);

	if( m_autoFinish )
		finishMatch(pMatch);

	m_gui.redraw(GR_SUBMATCHES_CNF);
				
	if( m_autoFinish )
	{
		pMatch = selectFirstAvailableSubMatch();
		if (!pMatch)
			sendMsg(UM_GOTO_NEXT_MATCH,0);
	}
}

CHMatch* CHSubMatchConfigurationGUIEx::selectFirstAvailableSubMatch()
{
	long nLines = m_gui.grid_getNLines(GR_SUBMATCHES_CNF);
	for (long i=0;i<nLines;i++)
	{
		CHMatch* pMatch = (CHMatch* ) m_gui.grid_getLParam(GR_SUBMATCHES_CNF,i);
		if (pMatch && pMatch->getStatus()!=CHMemoryDataBase::eFinished)
		{
			m_gui.grid_selLParam(GR_SUBMATCHES_CNF,LPARAM(pMatch),true,true,false);

			if (m_pMatchConfigToolBar)
			{
				delete m_pMatchConfigToolBar;
				m_pMatchConfigToolBar=0;
			}

			onCreateControl(CHMATCHCONFIGURATION_TB);			
			return pMatch;
		}
	}
	
	return 0;
}