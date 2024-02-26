/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:	CHMatchConfigurationGUI.cpp
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
#include "CHMatchConfigurationGUI.h"
#include "CHManagerApp.h"
#include "CHManagerDefs.h"
#include <OVR/CORE/TH/GTHMsgDefines.h>
#include "CHUmpireGUIEx.h"
#include "CHStatusManager.h"
#include "CHProgression.h"
#include "CHMatchConfigToolBar.h"
#include "CHSubMatchConfigurationGUIEx.h"

#include "..\CHMngtModel\CHPhase.h"
#include "..\CHMngtModel\CHPool.h"
#include "..\CHMngtModel\CHMatch.h"
#include "..\CHMngtModel\CHMatchResult.h"
#include "..\CHMngtModel\CHRegister.h"
#include "..\CHMngtModel\CHMember.h"
#include "..\CHMngtModel\CHInscription.h"

bool selectMatches(const MSLItem * col, const void * param)
{
	CHMatch * pMatch= (CHMatch*) col;
	
	if (pMatch->getSubCode())
		return false;

	return true;
}

static
int orderMatches(const MSLItem** a, const MSLItem** b)
{
	GTHMatch * pA=(GTHMatch *)(*a);
	GTHMatch * pB=(GTHMatch *)(*b);

	int order = pA->getCode() - pB->getCode();
	if (order)
		return order;

	order = pA->getSubCode() - pB->getSubCode();
	if (order)
		return order;

	return strcmp(pA->getKey(),pB->getKey());
}

CHMatchConfigurationGUI::CHMatchConfigurationGUI(long id, GData* pDataSel, CHMatch * pMatch)
:GTHManagerGUI(id)
,m_pMatch(pMatch)
,m_pDlgUmpire(0)
,m_pDataSel(pDataSel)
,m_pSubMatchConfigurationGUIEx(0)
{
}

CHMatchConfigurationGUI::~CHMatchConfigurationGUI()
{	
}

CHMemoryDataBase * CHMatchConfigurationGUI::getMem() const
{
	return (CHMemoryDataBase*)GMemoryDataBase::getMem();
}

void CHMatchConfigurationGUI::setMatch(CHMatch * pMatch)
{
	m_pMatch = pMatch;
}

bool CHMatchConfigurationGUI::onInit()
{	
	onCreateControl	();
	onFillControl	();
	
	return true;
}

bool CHMatchConfigurationGUI::onGridPaint(long id,gui_grid_cell* cell)
{
	if(id==GR_MATCH_CNF)
		return paintGridMatch(cell);
	else if(id==GR_MATCHRESULTS_CNF)
		return paintGridMatchResults(cell);
	else if(id==GR_MATCHMEMBERS_CNF)
		return paintGridMatchMembers(cell);
	else if(id==GR_MATCHJUDGE_CNF)
		return paintGridMatchJudge(cell);

	return false;
}

void CHMatchConfigurationGUI::onLButDblClick(long id,long x,long y)
{
	 if(id==GR_MATCH_CNF)
		dblClickGridMatch(x,y);
	 else if(id==GR_MATCHRESULTS_CNF)
		dblClickGridMatchResults(x,y);
	 else if(id==GR_MATCHMEMBERS_CNF)
		 dblClickGridMatchMembers(x,y);
}

void CHMatchConfigurationGUI::onClick(long id,LPARAM lParam)
{
	if(id==BT_UMPIRE && m_pMatch)
	{
		m_pDlgUmpire= new CHUmpireGUIEx(CHUMPIREGUIEX_ID,m_pMatch);
		MSLDialog(m_hWnd,*m_pDlgUmpire,406,300,L"Umpire Selection",0,true,-1,GUI_RGB_WHITE,m_hWnd);
		delete m_pDlgUmpire;
		m_pDlgUmpire=0;
	}
	if (id==BT_GO_PREV)
	{
		bool ok = goToPrevMatch();

		
	}
	if (id==BT_GO_NEXT)
	{
		bool ok = goToNextMatch();		
	}

	GTHManagerGUI::onClick(id,lParam);
}

bool CHMatchConfigurationGUI::onGridHand(long id,long x,long y)
{
	if(id==GR_MATCH_CNF)
		return handGridMatch(x,y);
	else if(id==GR_MATCHMEMBERS_CNF)
		return handGridMatchMembers(x,y);
	
	return false;
}

/***** Virtual from MSLGUIEX ****/
LRESULT CHMatchConfigurationGUI::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case UM_GOTO_NEXT_MATCH: return onGotoNextMatch		(wParam, lParam);
		case UM_CHANGE_UMPIRE: return onChangeUmpire		(wParam, lParam);
		case UM_CHANGE_MATCH: return onChangeMatch			(wParam, lParam);
	}

	return GTHManagerGUI::wndProc(hWnd,message,wParam,lParam);
}

LRESULT CHMatchConfigurationGUI::onCreateControl (WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	UNREFERENCED_PARAMETER(lParam);

	if(!wParam || wParam==GR_MATCH_CNF)
		createGridMatch();
	if(!wParam || wParam==GR_MATCHJUDGE_CNF)
		createGridMatchJudge();
	if(!wParam || wParam==GR_MATCHRESULTS_CNF)
		createGridMatchResults();
	if(!wParam || wParam==GR_MATCHMEMBERS_CNF)
		createGridMatchMembers();
	if(!wParam || wParam==CHSUBMATCHCONFIGGUIEX_ID)
	{
		if(m_pSubMatchConfigurationGUIEx)
			delete m_pSubMatchConfigurationGUIEx;

		m_pSubMatchConfigurationGUIEx=(CHSubMatchConfigurationGUIEx*)onNewGUIEx(CHSUBMATCHCONFIGGUIEX_ID);		 
	}

	return 1;
}

LRESULT CHMatchConfigurationGUI::onFillControl(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	UNREFERENCED_PARAMETER(lParam);

	if(!wParam || wParam==GR_MATCH_CNF)
		fillGridMatch();
	if(!wParam || wParam==GR_MATCHRESULTS_CNF)
		fillGridMatchResults();
	if(!wParam || wParam==GR_MATCHMEMBERS_CNF)
		fillGridMatchMembers();
	if(!wParam || wParam==GR_MATCHJUDGE_CNF)
		fillGridMatchJudge();
	if(!wParam || wParam==CHSUBMATCHCONFIGGUIEX_ID)
	{
		if (m_pSubMatchConfigurationGUIEx)
			SendMessage(m_pSubMatchConfigurationGUIEx->getHWnd(),UM_FILL_CONTROL,wParam,lParam);	
	}

	
	return 0;
}

LRESULT CHMatchConfigurationGUI::onRedrawControl(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	UNREFERENCED_PARAMETER(lParam);

	if(!wParam || wParam==GR_MATCH_CNF)
		redrawGrid(GR_MATCH_CNF);
	if(!wParam || wParam==GR_MATCHRESULTS_CNF)
		redrawGrid(GR_MATCHRESULTS_CNF);
	if(!wParam || wParam==GR_MATCHMEMBERS_CNF)
		redrawGrid(GR_MATCHMEMBERS_CNF);
	if(!wParam || wParam==GR_MATCHJUDGE_CNF)
		redrawGrid(GR_MATCHJUDGE_CNF);
	if(!wParam || wParam==CHSUBMATCHCONFIGGUIEX_ID)
	{
		if (m_pSubMatchConfigurationGUIEx)
			SendMessage(m_pSubMatchConfigurationGUIEx->getHWnd(),UM_REDRAW_CONTROL,wParam,lParam);	
	}
	return 0;
}

LRESULT CHMatchConfigurationGUI::onChangeMatch(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	redrawGrid(GR_MATCH_CNF);

	if (m_pSubMatchConfigurationGUIEx)
		SendMessage(m_pSubMatchConfigurationGUIEx->getHWnd(),UM_CHANGE_MATCH,wParam,lParam);	
		
	return 0;
}

LRESULT CHMatchConfigurationGUI::onChangeUmpire(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);
	fillGridMatchJudge();
	SendMessage(getHWndMsgs(),UM_CHANGE_MATCH,0,0);
	return 1;
}

LRESULT CHMatchConfigurationGUI::onGotoNextMatch(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	bool ok = goToNextMatch();
	return ok?0:1;
}


/***** Extensions *****/
MSLGUIEx * CHMatchConfigurationGUI::onNewGUIEx(long id)
{
	switch(id)
	{
		case CHSUBMATCHCONFIGGUIEX_ID:
		{
			RECT aRc=getRect();

			CHSubMatchConfigurationGUIEx * pSubMatchConfigGUIEx= new CHSubMatchConfigurationGUIEx(CHSUBMATCHCONFIGGUIEX_ID,m_pMatch);
			pSubMatchConfigGUIEx->init(m_gui.getHWnd(0),m_hWnd,RC(aRc.left+10,240,aRc.right,440));			
			return pSubMatchConfigGUIEx;
		}
	}
	return 0;
}

/***** Grid Match *****/
void CHMatchConfigurationGUI::createGridMatch()
{
	RECT aRc=getRect();

	int Y=aRc.top+5;
	m_gui.doLbl(LB_MATCH_TITLE,RC(aRc.left+10,Y,aRc.left+460,Y+16),"Match",GUIM_ID_STY_TITLE);

	Y+=18;

	m_gui.doGrid(GR_MATCH_CNF,RC(aRc.left+10,Y,aRc.left+460,Y+70),GUI_ID_STY_BOR,GUI_ID_STY_SEL,50,1L,20);

	m_gui.grid_addColumn(GR_MATCH_CNF,"Date"	  ,GUI_JUST_CENTER,80 ,C_DATE_MATCH_CNF);
	m_gui.grid_addColumn(GR_MATCH_CNF,"Session"   ,GUI_JUST_CENTER,50 ,C_SESSI_MATCH_CNF);	
	m_gui.grid_addColumn(GR_MATCH_CNF,"Round"	  ,GUI_JUST_CENTER,60 ,C_COURT_MATCH_CNF);
	m_gui.grid_addColumn(GR_MATCH_CNF,"Game"	  ,GUI_JUST_CENTER,160 ,C_GAME_MATCH_CNF);
	m_gui.grid_addColumn(GR_MATCH_CNF,"Status"	  ,GUI_JUST_CENTER,100 ,C_STATU_MATCH_CNF);	

	m_gui.grid_setLineColor(GR_MATCH_CNF,GUI_RGB_OFF,GUI_RGB_OFF); 
	m_gui.doCombo(CB_MATCH_CNF,RC(0,0,0,0));

	m_gui.doBut(BT_GO_PREV,RC(aRc.left+10,Y+75,aRc.left+230,Y+94),"<---- Go To Prev Match ");	
	m_gui.doBut(BT_GO_NEXT,RC(aRc.left+235,Y+75,aRc.left+460,Y+94),"Go To Next Match ---->");	
}

void CHMatchConfigurationGUI::fillGridMatch()
{
	m_gui.grid_reset(GR_MATCH_CNF);
	if(m_pMatch)
		m_gui.grid_add(GR_MATCH_CNF,(LPARAM)m_pMatch);

	m_gui.grid_setCellSym(GR_MATCH_CNF,m_gui.grid_findCol(GR_MATCH_CNF,C_STATU_MATCH_CNF),0);	
}

bool CHMatchConfigurationGUI::paintGridMatch(gui_grid_cell* cell)
{
	if(cell->y==-1 || !cell->lParamLine)
		return false;

	//m_gui.paint_solid(RGB(255,255,255));

	CHMatch * pMatch=(CHMatch*)cell->lParamLine;
	
	switch (cell->lParamColumn)
	{
	case C_DATE_MATCH_CNF:
		m_gui.paint_text(pMatch->getStartDateAsString("%d/%m/%Y"),GUI_ID_FNT_MED_B);
		break;
	case C_SESSI_MATCH_CNF:
		m_gui.paint_text(pMatch->getSessionTimeAsString("%H:%M").toUnicode(),GUI_ID_FNT_MED_B);
		break;	
	case C_COURT_MATCH_CNF:
		m_gui.paint_text(pMatch->getRoundAsString(false,false),GUI_ID_FNT_MED_B);
		break;
	case C_GAME_MATCH_CNF:
		m_gui.paint_text(((CHManagerApp*)MSLAPP)->getMatchTitle(pMatch),GUI_ID_FNT_MED_B);
		break;
	case C_STATU_MATCH_CNF:
		m_gui.paint_text(pMatch->getStatusLDescription(),GUI_ID_FNT_MED_B);
		break;	}
	
	return false;
}

void CHMatchConfigurationGUI::redrawGrid(long idGrid)
{
	m_gui.redraw(idGrid);
}

void CHMatchConfigurationGUI::dblClickGridMatch(long x,long y)
{
	gui_grid_cell * pCell=m_gui.grid_getCell(GR_MATCH_CNF,x,y);
	if(!pCell)
		return;

	int col=pCell->lParamColumn;

	CHMatch * pMatch = (CHMatch * )pCell->lParamLine;

	if(col==C_STATU_MATCH_CNF)
		editStatus(pMatch, GR_MATCH_CNF);
}

bool CHMatchConfigurationGUI::handGridMatch(int x,int y)
{
	gui_grid_cell * pCell=m_gui.grid_getCell(GR_MATCH_CNF,x,y);
	if(!pCell)
		return false;

	if(pCell->lParamColumn==C_STATU_MATCH_CNF)
			return true;

	return false;
}

void CHMatchConfigurationGUI::editStatus(CHMatch *pMatch, long idGrid)
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

	int nNew=m_gui.grid_showCombo(idGrid,CB_MATCH_CNF);
	if(nNew!=-1)
	{
		CHStatusManager aStManager;
		aStManager.setStatus(pMatch ,(unsigned char)nNew,false);
		redrawGrid(idGrid);
		
		PostMessage(getHWndMsgs(),UM_REDRAW_CONTROL,0,0);
		SendMessage(getHWndMsgs(),UM_CHANGE_MATCH,0,0);
	}
}

void CHMatchConfigurationGUI::fillComboStatus(CHMatch * pMatch)
{
	m_gui.combo_reset(CB_MATCH_CNF);

/*	if(pMatch->getStatus()==CHMemoryDataBase::eSchedulled)
	{
		GStatus * pStatus=CHMemoryDataBase::findStatus(CHMemoryDataBase::eStartList);
		if(pStatus)
			m_gui.combo_add(CB_MATCH_CNF,pStatus->getLDescription(),CHMemoryDataBase::eStartList);
	}
	else if(pMatch->getStatus()==CHMemoryDataBase::eStartList)
	{
		GStatus * pStatus=CHMemoryDataBase::findStatus(CHMemoryDataBase::eSchedulled);
		if(pStatus)
			m_gui.combo_add(CB_MATCH_CNF,pStatus->getLDescription(),CHMemoryDataBase::eSchedulled);
	}*/

	GStatus * pStatus=CHMemoryDataBase::findStatus(CHMemoryDataBase::eSchedulled);
	if(pStatus)
		m_gui.combo_add(CB_MATCH_CNF,pStatus->getLDescription(),CHMemoryDataBase::eSchedulled);

	pStatus=CHMemoryDataBase::findStatus(CHMemoryDataBase::eStartList);
	if(pStatus)
		m_gui.combo_add(CB_MATCH_CNF,pStatus->getLDescription(),CHMemoryDataBase::eStartList);

	pStatus=CHMemoryDataBase::findStatus(CHMemoryDataBase::eRunning);
	if(pStatus)
		m_gui.combo_add(CB_MATCH_CNF,pStatus->getLDescription(),CHMemoryDataBase::eRunning);

	pStatus=CHMemoryDataBase::findStatus(CHMemoryDataBase::eUnofficial);
	if(pStatus)
		m_gui.combo_add(CB_MATCH_CNF,pStatus->getLDescription(),CHMemoryDataBase::eUnofficial);

	pStatus=CHMemoryDataBase::findStatus(CHMemoryDataBase::eFinished);
	if(pStatus)
		m_gui.combo_add(CB_MATCH_CNF,pStatus->getLDescription(),CHMemoryDataBase::eFinished);
}

/***** Grid Match Judge*****/
void CHMatchConfigurationGUI::createGridMatchJudge()
{
	RECT aRc=getRect();

	int Y=aRc.top+5;
	

	m_gui.doLbl(LB_MATCHJUDGE_TITLE,RC(aRc.left+465,Y,aRc.right-16,Y+16),"Umpires",GUIM_ID_STY_TITLE);
	Y+=18;

	m_gui.doGrid(GR_MATCHJUDGE_CNF,RC(aRc.left+465,Y,aRc.right-16,Y+70),GUI_ID_STY_BOR,GUI_ID_STY_SEL,25,GUI_ID_STY_UP,20);

	m_gui.grid_addColumn(GR_MATCHJUDGE_CNF,"Name",GUI_JUST_LEFT       ,140,C_NAME_MATCHJ_CNF);
	m_gui.grid_addColumn(GR_MATCHJUDGE_CNF,"Function",GUI_JUST_CENTER , 70,C_FUNCT_MATCHJ_CNF);
	
	m_gui.grid_setLineColor(GR_MATCHJUDGE_CNF,GUI_RGB_OFF,GUI_RGB_OFF); 

	m_gui.doBut(BT_UMPIRE,RC(aRc.left+465,Y+75,aRc.right-16,Y+94),"Umpire Selection");	
}

void CHMatchConfigurationGUI::fillGridMatchJudge()
{
	m_gui.grid_reset(GR_MATCHJUDGE_CNF);
	if(m_pMatch)
	{
		MSLSortedVector vMatchJudges;
		m_pMatch->getMatchJudgesVector(vMatchJudges);
		GTHMatchJudge * pMatchJudge=0;
		for(int i=0 ; i<vMatchJudges.entries();i++)
		{
			pMatchJudge=(GTHMatchJudge*)vMatchJudges[i];
			m_gui.grid_add(GR_MATCHJUDGE_CNF,(LPARAM)pMatchJudge);
		}
	}
}

bool CHMatchConfigurationGUI::paintGridMatchJudge(gui_grid_cell* cell)
{
	if(cell->y==-1 || !cell->lParamLine)
		return false;

	//m_gui.paint_solid(RGB(255,255,255));

	GTHMatchJudge * pMatchJudge=(GTHMatchJudge*)cell->lParamLine;
		
	switch (cell->lParamColumn)
	{
	case C_NAME_MATCHJ_CNF:
		paintFlagCompetitor((CHRegister*)pMatchJudge->getRegister(),cell);
		painSexRegister((CHRegister*)pMatchJudge->getRegister());
		m_gui.paint_textAt(pMatchJudge->getPrnLName(),40,4,GUI_ID_FNT);
	break;
	case C_FUNCT_MATCHJ_CNF:
		m_gui.paint_textAt(pMatchJudge->getFunctionLDescription(),2,3,GUI_ID_FNT);
	break;
	}
	
	return false;
}

/***** Grid Match Results*****/
void CHMatchConfigurationGUI::createGridMatchResults()
{
	RECT aRc=getRect();

	int Y=aRc.top;
	Y+=135;

	m_gui.doLbl(LB_MATCHRESULT_TITLE,RC(aRc.left+10,Y,aRc.right-16,Y+16),"Match Players",GUIM_ID_STY_TITLE);
	Y+=18;

	m_gui.doGrid(GR_MATCHRESULTS_CNF,RC(aRc.left+10,Y,aRc.right-16,Y+33),GUI_ID_STY_BOR,GUI_ID_STY_SEL,33,GUI_ID_STY_UP,0);

	int w=((aRc.right-16)-(aRc.left+10))/2;

	bool isTeam=false;
	if(m_pMatch && ((CHEvent*)m_pMatch->getEvent())->isTeam())
	{ 
		isTeam=true;
		w=w-15; 
	}

	m_gui.grid_addColumn(GR_MATCHRESULTS_CNF,"HOME",GUI_JUST_LEFT  ,w,C_HOME_MATCHR_CNF);
	if(isTeam)
		m_gui.grid_addColumn(GR_MATCHRESULTS_CNF,"Result",GUI_JUST_LEFT,15,C_HOME_RESULT_CNF);
	m_gui.grid_addColumn(GR_MATCHRESULTS_CNF,"AWAY",GUI_JUST_LEFT  ,w,C_AWAY_MATCHR_CNF);
	if(isTeam)
		m_gui.grid_addColumn(GR_MATCHRESULTS_CNF,"Result",GUI_JUST_LEFT,15,C_AWAY_RESULT_CNF);
	m_gui.grid_setLineColor(GR_MATCHRESULTS_CNF,GUI_RGB_OFF,GUI_RGB_OFF); 
}

void CHMatchConfigurationGUI::fillGridMatchResults()
{
	m_gui.grid_reset(GR_MATCHRESULTS_CNF);
	if(m_pMatch)
		m_gui.grid_add(GR_MATCHRESULTS_CNF,(LPARAM)m_pMatch);
}

bool CHMatchConfigurationGUI::paintGridMatchResults(gui_grid_cell* cell)
{
	if(cell->y==-1 || !cell->lParamLine)
		return false;

	m_gui.paint_solid(RGB(255,255,255));

	CHMatch * pMatch=(CHMatch*)cell->lParamLine;
	
	switch (cell->lParamColumn)
	{
	case C_HOME_MATCHR_CNF:
		{
			CHMatchResult * pMRH=(CHMatchResult *)pMatch->getHome();
			paintFlagCompetitor(pMRH,cell);
			m_gui.paint_textAt(pMRH->getPrnLName(),40,4,GUI_ID_FNT_BIG,GUI_RGB_BLACK);
		}
	break;
	case C_HOME_RESULT_CNF:
		{
			if(((CHEvent*)pMatch->getEvent())->isTeam())
			{
				CHMatchResult * pMRH=(CHMatchResult *)pMatch->getHome();
				
				/*if(pMatch->getSubMatch())
					m_gui.paint_val(pMRH->getPoints(),GUI_ID_FNT_MED,GUI_RGB_BLACK,GUI_JUST_CENTER);
				else
					m_gui.paint_val(pMRH->getWinningSets(),GUI_ID_FNT_MED,GUI_RGB_BLACK,GUI_JUST_CENTER);*/
			}
		}
	break;
	case C_AWAY_MATCHR_CNF:
		{
			CHMatchResult * pMRA=(CHMatchResult *)pMatch->getAway();
			paintFlagCompetitor(pMRA,cell);
			m_gui.paint_textAt(pMRA->getPrnLName(),40,3,GUI_ID_FNT_BIG,GUI_RGB_BLACK);
		}
	break;
	case C_AWAY_RESULT_CNF:
		{
			if(((CHEvent*)pMatch->getEvent())->isTeam())
			{
				CHMatchResult * pMRA=(CHMatchResult *)pMatch->getAway();
				/*if(pMatch->getSubMatch())
					m_gui.paint_val(pMRA->getPoints(),GUI_ID_FNT_MED,GUI_RGB_BLACK,GUI_JUST_CENTER);
				else
					m_gui.paint_val(pMRA->getWinningSets(),GUI_ID_FNT_MED,GUI_RGB_BLACK,GUI_JUST_CENTER);*/
			}
		}
		break;
	}
	
	return true;
}

void CHMatchConfigurationGUI::paintFlagCompetitor(CHMatchResult *pMatchResult, gui_grid_cell* cell)
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

void CHMatchConfigurationGUI::dblClickGridMatchResults(long x,long y)
{
	gui_grid_cell * pCell=m_gui.grid_getCell(GR_MATCHRESULTS_CNF,x,y);
	if(!pCell)
		return;

}

/***** Grid Match Members*****/
void CHMatchConfigurationGUI::createGridMatchMembers()
{
	RECT aRc=getRect();

	int Y=aRc.top;
	Y+=187;

	m_gui.doGrid(GR_MATCHMEMBERS_CNF,RC(aRc.left+10,Y,aRc.right-16,Y+47),GUI_ID_STY_BOR,GUI_ID_STY_SEL,23,GUI_ID_STY_UP,0);

	int w=((aRc.right-16)-(aRc.left+10))/2;
	m_gui.grid_addColumn(GR_MATCHMEMBERS_CNF,"HOME",GUI_JUST_LEFT,w,C_HOME_MATCHM_CNF);
	m_gui.grid_addColumn(GR_MATCHMEMBERS_CNF,"AWAY",GUI_JUST_LEFT  ,w,C_AWAY_MATCHM_CNF);
	
	m_gui.grid_setLineColor(GR_MATCHMEMBERS_CNF,GUI_RGB_OFF,GUI_RGB_OFF); 

	m_gui.doCombo(CB_MATCHMEMBERS_CNF,RC(0,0,0,0));
}

void CHMatchConfigurationGUI::fillGridMatchMembers()
{
	m_gui.grid_reset(GR_MATCHMEMBERS_CNF);
	if(m_pMatch)
	{
		CHMatchResult * pMRH=(CHMatchResult*)m_pMatch->getHome();
		CHMatchResult * pMRA=(CHMatchResult*)m_pMatch->getAway();

		int nLines=0;
		if(pMRH->getMatchMembers().entries()>pMRA->getMatchMembers().entries())
			nLines=pMRH->getMatchMembers().entries();
		else
			nLines=pMRA->getMatchMembers().entries();

		for(int i=0 ; i<nLines ; i++)
		{
			m_gui.grid_add(GR_MATCHMEMBERS_CNF,(LPARAM)m_pMatch);
			m_gui.grid_setCellSym(GR_MATCHMEMBERS_CNF,m_gui.grid_findCol(GR_MATCHMEMBERS_CNF,C_HOME_MATCHM_CNF),i);
			m_gui.grid_setCellSym(GR_MATCHMEMBERS_CNF,m_gui.grid_findCol(GR_MATCHMEMBERS_CNF,C_AWAY_MATCHM_CNF),i);
		}
	}
}

bool CHMatchConfigurationGUI::paintGridMatchMembers(gui_grid_cell* cell)
{
	if(cell->y==-1 || !cell->lParamLine)
		return false;

	//m_gui.paint_solid(RGB(255,255,255));

	CHMatch * pMatch=(CHMatch*)cell->lParamLine;
	
	switch (cell->lParamColumn)
		{
	case C_HOME_MATCHM_CNF:
		{
			CHMatchResult * pMRH=(CHMatchResult *)pMatch->getHome();
			GTHMatchMember * pMMH=pMRH?(GTHMatchMember *)pMRH->getMatchMember(cell->y):0;
			if(pMMH)
			{
				paintFlagCompetitor((CHRegister*)pMMH->getRegister(),cell);
				painSexRegister((CHRegister*)pMMH->getRegister());
				MSLWString desc = pMMH->getPrnLName();
				desc += pMMH->getMember() ? L" ("+((CHMember*)pMMH->getMember())->getRatingAsString().toUnicode()+L")" : NULLWSTRING;
				m_gui.paint_textAt(desc,40,4,GUI_ID_FNT);
			}
		}
	break;
	case C_AWAY_MATCHM_CNF:
		{
			CHMatchResult * pMRA=(CHMatchResult *)pMatch->getAway();
			GTHMatchMember * pMMA=pMRA?(GTHMatchMember *)pMRA->getMatchMember(cell->y):0;
			if(pMMA)
			{
				paintFlagCompetitor((CHRegister*)pMMA->getRegister(),cell);
				painSexRegister((CHRegister*)pMMA->getRegister());
				MSLWString desc = pMMA->getPrnLName();
				desc += pMMA->getMember() ? L" ("+((CHMember*)pMMA->getMember())->getRatingAsString().toUnicode()+L")" : NULLWSTRING;
				m_gui.paint_textAt(desc,40,4,GUI_ID_FNT);
			}
		}
	break;
	}
	
	return false;
}

void CHMatchConfigurationGUI::paintFlagCompetitor(CHRegister *pRegister, gui_grid_cell* cell)
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

void CHMatchConfigurationGUI::painSexRegister(CHRegister * pRegister)
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

void CHMatchConfigurationGUI::dblClickGridMatchMembers(long x,long y)
{
	gui_grid_cell * pCell=m_gui.grid_getCell(GR_MATCHMEMBERS_CNF,x,y);
	if(!pCell)
		return;

	int col=pCell->lParamColumn;
	
	CHMatch * pMatch = (CHMatch * )pCell->lParamLine;

	if(col==C_HOME_MATCHM_CNF)
		editMatchMember(pMatch, C_HOME_MATCHM_CNF,y);
	else if(col==C_AWAY_MATCHM_CNF)
		editMatchMember(pMatch, C_AWAY_MATCHM_CNF,y);
}

bool CHMatchConfigurationGUI::handGridMatchMembers(int x,int y)
{
	gui_grid_cell * pCell=m_gui.grid_getCell(GR_MATCHMEMBERS_CNF,x,y);
	if(!pCell)
		return false;

	return true;
}


void CHMatchConfigurationGUI::editMatchMember(CHMatch * pMatch, int col,int y)
{
	if(!pMatch)
		return;

	if(pMatch && pMatch->getStatus()>=CHMemoryDataBase::eRunning)
	{
/*		MSLMsgBox(m_hWnd, L"You can't change members.\nThe Match is started",GUI_ICO_WARNING,GUI_MB_OK,_T("Match Type Result"));
		return;*/

		long value = MSLMsgBox(m_hWnd, L"The match has started, do you want to change members?",GUI_ICO_QUESTION,GUI_MB_OKCANCEL,_T("Match Type Result"));
		if (value == IDCANCEL)
			return;

		value = MSLMsgBox(m_hWnd, L"Really, do you want to change members?",GUI_ICO_QUESTION,GUI_MB_OKCANCEL,_T("Match Type Result"));
		if (value == IDCANCEL)
			return;
	}

	GTHMatchMember * pMM=0;
	if(col==C_HOME_MATCHM_CNF)
	{
		CHMatchResult * pMRH=(CHMatchResult *)pMatch->getHome();
		pMM=(GTHMatchMember *)(pMRH?pMRH->getMatchMember(y):0);
	}
	else if(col==C_AWAY_MATCHM_CNF)
	{
		CHMatchResult * pMRA=(CHMatchResult *)pMatch->getAway();
		pMM=(GTHMatchMember *)(pMRA?pMRA->getMatchMember(y):0);
	}

	if(!pMM)
		return;

	fillComboMembers(pMM);

	CHMember * pOldMember= (CHMember*)pMM->getMember();
	m_gui.combo_selL(CB_MATCHMEMBERS_CNF,(LPARAM)pOldMember);	

	CHMember * pNewMember=(CHMember *)m_gui.grid_showCombo(GR_MATCHMEMBERS_CNF,CB_MATCHMEMBERS_CNF);
	if(long(pNewMember)!=-1 && pOldMember!=pNewMember)
	{
		pMM->setMember(pNewMember);
		redrawGrid(GR_MATCHMEMBERS_CNF);

		SendMessage(getHWndMsgs(),UM_CHANGE_MATCH,0,0);

		APP::out(*pMM);
		APP::out(TRN_SET_MATCHMEMBER); //TRN_CHANGE_MATCH_MEMBERS
	}
}

void CHMatchConfigurationGUI::editSubMatchMember(CHMatch *pMatch, int col, int y)
{
	if(!pMatch)
		return;

	if(pMatch && pMatch->getStatus()>=CHMemoryDataBase::eRunning)
	{
/*		MSLMsgBox(m_hWnd, L"You can't change members.\nThe Match is started",GUI_ICO_WARNING,GUI_MB_OK,_T("Match Type Result"));
		return;*/

		long value = MSLMsgBox(m_hWnd, L"The match has started, do you want to change members?",GUI_ICO_QUESTION,GUI_MB_OKCANCEL,_T("Match Type Result"));
		if (value == IDCANCEL)
			return;

		value = MSLMsgBox(m_hWnd, L"Really, do you want to change members?",GUI_ICO_QUESTION,GUI_MB_OKCANCEL,_T("Match Type Result"));
		if (value == IDCANCEL)
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
		redrawGrid(GR_MATCHMEMBERS_CNF);

		SendMessage(getHWndMsgs(),UM_CHANGE_MATCH,0,0);

		APP::out(*pMM);
		APP::out(TRN_SET_MATCHMEMBER); //TRN_CHANGE_MATCH_MEMBERS
	}
}

void CHMatchConfigurationGUI::fillComboMembers(GTHMatchMember * pMatchMember)
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

LRESULT CHMatchConfigurationGUI::onCommsPackTransaction(WPARAM wParam, LPARAM lParam)
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

	if(m_pDlgUmpire)
		SendMessage(m_pDlgUmpire->getHWnd(),UM_COMMS_PACKTRANSACTION,wParam,lParam);
	
	return 1;
}

LRESULT CHMatchConfigurationGUI::onComms(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	/*if(!lParam)	return 0;

	CommsMng * pCommsMng=(CommsMng *)lParam;
	GData * pData=pCommsMng->pData;
	if(!pData)
		return 0;*/

	if(m_pDlgUmpire)
		SendMessage(m_pDlgUmpire->getHWnd(),UM_COMMS_DATA,wParam,lParam);

	return 1;
}

bool CHMatchConfigurationGUI::goToNextMatch()
{
	CHMatch * pMatch = (CHMatch *)getNextMatch();
	if (pMatch)
	{
		setMatch(pMatch);
		if (m_pSubMatchConfigurationGUIEx)
			m_pSubMatchConfigurationGUIEx->setMatch(pMatch);
		
		onFillControl();
		
		return true;
	}
	return false;
}

bool CHMatchConfigurationGUI::goToPrevMatch()
{
	CHMatch * pMatch = (CHMatch *)getPrevMatch();
	if (pMatch)
	{
		setMatch(pMatch);			
		if (m_pSubMatchConfigurationGUIEx)
			m_pSubMatchConfigurationGUIEx->setMatch(pMatch);
		onFillControl();
		return true;
	}

	return false;
}


CHMatch* CHMatchConfigurationGUI::getPrevMatch()
{
	MSLSortedVector vMatches;
	getMatchesVectorSel(vMatches);

	long indexCurrent = vMatches.index(m_pMatch);
	if (indexCurrent>0)
		return (CHMatch*)vMatches[indexCurrent-1];

	return 0;
}

CHMatch* CHMatchConfigurationGUI::getNextMatch()
{
	MSLSortedVector vMatches;
	getMatchesVectorSel(vMatches);

	long indexCurrent = vMatches.index(m_pMatch);
	if (indexCurrent<vMatches.entries())
		return (CHMatch*)vMatches[indexCurrent+1];

	return 0;
}

void CHMatchConfigurationGUI::getMatchesVectorSel(MSLSortedVector &vMatches)
{
	if (!m_pDataSel)
		return;

	MSLSet colMatches;
	if (m_pDataSel->isA()==__CHPHASE)
	{
		CHPhase * pPhase = (CHPhase *)m_pDataSel;
		pPhase->getMatches(colMatches);
		
		vMatches = MSLSortedVector(colMatches.select(selectMatches,0), orderMatches);
	}
	else if (m_pDataSel->isA()==__CHPOOL)
	{
		CHPool * pPool = (CHPool *)m_pDataSel;
		colMatches=pPool->getMatches();		

		vMatches = MSLSortedVector(colMatches.select(selectMatches,0), orderMatches);
	}	
}