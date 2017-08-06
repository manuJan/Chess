/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHMatchGUIEx.cpp
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
#include "CHProgression.h"
#include "CHMatchGUIEx.h"
#include "CHMatchToolBar.h"
#include "CHMatchConfigurationGUI.h"
#include "CHRankingsGUI.h"

#include "..\CHVMngtModel\CHRoundDraw.h"

#include "..\CHMngtModel\CHPoolResult.h"
#include "..\CHMngtModel\CHPhase.h"
#include "..\CHMngtModel\CHPool.h"
#include "..\CHMngtModel\CHMatch.h"
#include "..\CHMngtModel\CHInscription.h"
#include <ovr\core\th\gthmsgdefines.h>

static
int orderPoolResults(const MSLItem** a, const MSLItem** b)
{
	GTHPoolResult * pA=(GTHPoolResult *)(*a);
	GTHPoolResult * pB=(GTHPoolResult *)(*b);

	int order=_wcsicoll(pA->getPrnLName(),pB->getPrnLName());
	if(order)
		return order;

	order = pA->getOrder() - pB->getOrder();
	if (order)
		return order;

	return strcmp(pA->getKey(),pB->getKey());
}

CHMatchGUIEx::CHMatchGUIEx(GTHProgression* pProgression, GTHProgressionData* pProgressionData, GTHStatusManager* pStatusManager, long id)
:GTHMatchGUIEx(pProgression, pProgressionData, pStatusManager, id)
,m_pDlgMatchConfig(0)
,m_pDlgRankings(0)
{

}

CHMatchGUIEx::~CHMatchGUIEx(void)
{

}

/***** Virtual from MSLGUIEX ****/
LRESULT CHMatchGUIEx::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return GTHMatchGUIEx::wndProc(hWnd, message, wParam, lParam);
}

CHMatch * CHMatchGUIEx::getMatch() const
{
	return (CHMatch*)((MSLGUI&)m_gui).grid_selGetLParam(GR_MATCHES);
}

LRESULT CHMatchGUIEx::onLButDownToolBar(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	if (wParam==LX_PHASE_CHDRAW)
	{
		initialDraw();
		return 0;
	}
	if(wParam==LX_MATCH_CONFIG)
	{
		matchConfigurationDlg();
		return 0;
	}
	if(wParam==LX_RANKINGS)
	{
		rankingsDlg();
		return 0;
	}
	return GTHMatchGUIEx::onLButDownToolBar(wParam, lParam);
}

/***** Extensions *****/
MSLGUIEx * CHMatchGUIEx::onNewGUIEx(long id)
{
	switch (id)
	{
		case TB_MATCH_ID:
		{
			RECT rect = getRect();

			CHMatchToolBar * pMatchToolBar= new CHMatchToolBar(TB_MATCH_ID);
			pMatchToolBar->initToolBar(m_gui.getHWnd(0),m_hWnd,GToolBar::eTop,36,0,0,(rect.right-rect.left-16));
			return pMatchToolBar;	
		}		
	}

	return GTHMatchGUIEx::onNewGUIEx(id);
}

void CHMatchGUIEx::createGridMatches()
{
	GTHMatchGUIEx::createGridMatches();
	
	m_gui.grid_setCellW(GR_MATCHES,0,50);
	m_gui.grid_setCellW(GR_MATCHES,4,175);
	m_gui.grid_setCellW(GR_MATCHES,6,175);

	m_gui.grid_addColumn(GR_MATCHES,"", GUI_JUST_CENTER, 65, C_MT_ROUND	 );
		
	m_gui.grid_movColumn(GR_MATCHES,6,5);
	
}

bool CHMatchGUIEx::paintHeaderGrid(gui_grid_cell* cell)
{
	long cx=cell->paint.rc.right-cell->paint.rc.left;

	switch (cell->lParamColumn)
	{
		case C_MT_HOME:
		case C_MT_AWAY:
			{
				if (!cx)
					return true;
				break;
			}
		case C_MT_HOME_RESULT:
			if (cx>0)
				m_gui.paint_text("Res H.", GUI_ID_FNT, GUI_RGB_BLACK, GUI_JUST_CENTER); 
			return true;
		case C_MT_AWAY_RESULT:
			if (cx>0)
				m_gui.paint_text("Res A.", GUI_ID_FNT, GUI_RGB_BLACK, GUI_JUST_CENTER); 
			return true;		
		case C_MT_ROUND:
			if (cx>0)
				m_gui.paint_text("Round", GUI_ID_FNT, GUI_RGB_BLACK, GUI_JUST_CENTER); 
			return true;		
	}

	return GTHMatchGUIEx::paintHeaderGrid(cell);
}

bool CHMatchGUIEx::paintGridMatches(gui_grid_cell* cell)
{
	if(cell->y==-1 || !cell->lParamLine)
		return paintHeaderGrid(cell);		
	
	CHMatch* pMatch = (CHMatch*) cell->lParamLine;
	if (!pMatch)
		return false;

	bool isPool = pMatch->getIsPool();

	paintMatchSolid(pMatch);

	int col=cell->lParamColumn;

	switch (col)
	{
		case C_MT_ROUND:
		{
			m_gui.paint_text( pMatch->getRoundAsString(false,false).toUnicode(), GUI_ID_FNT, COLORREF(-1), GUI_JUST_CENTER);	
			return false;
		}

	}
	return GTHMatchGUIEx::paintGridMatches(cell);
}

MSLWString CHMatchGUIEx::getDescription(GTHMatchResult *pMatchResult)
{
	if (!pMatchResult)
		return NULLWSTRING;

	MSLWString idCompetitor;
	if(pMatchResult->getRegister())
		idCompetitor=((CHMatchResult*)pMatchResult)->getSName();
	else
		idCompetitor=pMatchResult->getIDCompetitor(false);

	CHInscription * pInsc=(CHInscription *)pMatchResult->getInscription();
	if(pInsc && pInsc->getSeed()!=0 )
		idCompetitor+= MSLWString(L" (" + TOWSTRING(pInsc->getSeed()) + L")");

	if (pMatchResult->getBye())
		idCompetitor+=_T("(BYE)");

	return idCompetitor;
}

void CHMatchGUIEx::dblClickGridMatches(int x, int y)
{
	gui_grid_cell * pCell=m_gui.grid_getCell(GR_MATCHES,x,y);
	if(!pCell)
		return;
	
	GTHMatch* pMatch = (GTHMatch*) pCell->lParamLine;
	if (!pMatch)
		return;

	int col=pCell->lParamColumn;

	if (!canChangeMatch(pMatch,col))
		return;

	switch (col)
	{
		case C_MT_STATUS:
			editStatus((CHMatch*)pMatch);
			return;		
	}


	GTHMatchGUIEx::dblClickGridMatches(x,y);
}

void CHMatchGUIEx::editStatus(CHMatch* pMatch)
{
	GTHMatchGUIEx::editStatus(pMatch);
}

bool CHMatchGUIEx::canChangeMatchResult(CHMatchResult* pMatchResult)
{
	return true;
	UNREFERENCED_PARAMETER(pMatchResult);
}

bool CHMatchGUIEx::typePool(GData* pData)
{
	if (!pData)
		return false;

	if (pData->isA()!=__CHPHASE && 
		pData->isA()!=__CHPOOL  &&
		pData->isA()!=__CHMATCH  )
	{
		return false;
	}

	if (pData->isA()==__CHPHASE )
		return ((CHPhase*)pData)->getIsPool();
	else if (pData->isA()==__CHPOOL )
		return ((CHPool*)pData)->getIsPool();
	else if (pData->isA()==__CHMATCH )
		return ((CHMatch*)pData)->getIsPool();

	return false;
}

void CHMatchGUIEx::initialDraw()
{
	if (!m_pDataSel || !m_pTHProgression)
		return;

	CHPhase* pPhase=0;
	if (m_pDataSel->isA()==__CHPHASE)
		pPhase = (CHPhase*)m_pDataSel;
	else if (m_pDataSel->isA()==__CHPOOL)
		pPhase = (CHPhase*) ((CHPool*)m_pDataSel)->getPhase();
	else if (m_pDataSel->isA()==__CHMATCH)
		pPhase = (CHPhase*) ((CHMatch*)m_pDataSel)->getPhase();
	else
		return;

	
	if (pPhase && 
	   (pPhase->getStatus() > CHMemoryDataBase::eSchedulled))
	{
		MSLMsgBox(m_hWnd, L"The status of the phase must be less than schedule",GUI_ICO_STOP,GUI_MB_OK,L"Draw");
		return;
	}

	if (pPhase->hasCompetitors())
	{
		MSLMsgBox(m_hWnd, L"This event has some competitors, remove all before",GUI_ICO_STOP,GUI_MB_OK,L"Draw");		
		return;
	}
	
	m_pTHProgression->doInitialDraw(pPhase,GTHProgression::eRandom);

	bool validDraw = false;
	MSLSortedVector vPools;
	pPhase->getPoolesVector(vPools);

	for (short i=0;i<vPools.entries();i++)
	{
		CHPool* pPool = (CHPool*)vPools[i];
	
		MSLSet colMatchResults;
		CHRoundDraw aRoundDraw(colMatchResults,pPool,1);
		validDraw = aRoundDraw.doDraw(CHRoundDraw::eMonrad);
		if (validDraw)
		{
			MSLSetIterator it(colMatchResults);
			CHMatchResult *pMatchResult=0;			
			while((pMatchResult=(CHMatchResult *)it())!=0)
			{
				m_pTHProgression->setData(pMatchResult->getInscription(),pMatchResult,false,true);				
				APP::out(*pMatchResult);
			}
			APP::out(TRN_SET_MATCHRESULT);
		}
	}

	// Manage Byes
	if (validDraw)
	{
		for (short i=0;i<vPools.entries();i++)
		{
			CHPool* pPool = (CHPool*)vPools[i];
			
			MSLSortedVector vMatches;
			pPool->getMatchesVector(vMatches);
			for (short j=0;j<vMatches.entries();j++)
			{
				CHMatch* pMatch = (CHMatch*)vMatches[j];
				((CHProgression*)m_pTHProgression)->manageByes(pMatch);					
			}
		}
	}
}

void CHMatchGUIEx::matchConfigurationDlg()
{
	CHMatch * pMatch=getMatch();
	if(!pMatch)
		return;

	if(APP::lock("Match Config "+ pMatch->getKey()))
	{
		m_pDlgMatchConfig = new CHMatchConfigurationGUI(CHMATCHCONFIGGUI_ID,m_pDataSel,pMatch);
		MSLWString title=L"Match Configuration " + ((CHManagerApp*)MSLAPP)->getMatchTitle(pMatch);
		MSLDialog(m_hWnd,*m_pDlgMatchConfig ,700,450,title,0,true,-1,GUI_RGB_WHITE,m_hWnd);
		APP::unlock("Match Config "+ pMatch->getKey());
		delete m_pDlgMatchConfig;
		m_pDlgMatchConfig=0;

		m_gui.redraw(GR_MATCHES);
	}
}

void CHMatchGUIEx::rankingsDlg()
{
	CHPool * pPool = 0;
	CHMatch * pMatch=getMatch();
	if(pMatch)
		pPool = (CHPool*)pMatch->getPool();
	else if (m_pDataSel)
	{
		if (m_pDataSel->isA()==__CHPHASE)
		{
			CHPool *pPool = (CHPool *) ((CHPhase*)m_pDataSel)->getPool(0);
		}
		else if (m_pDataSel->isA()==__CHPOOL)
		{
			pPool = (CHPool*)m_pDataSel;
		}
		else if (m_pDataSel->isA()==__CHMATCH)
		{
			pPool = (CHPool*) ((CHMatch*)m_pDataSel)->getPool();	
		}
	}

	if (!pPool)
		return;

	if(APP::lock("Rankings "+ pPool->getKey()))
	{
		m_pDlgRankings = new CHRankingsGUI(pPool,m_pTHProgression, m_pTHProgressionData, CHRANKINGSGUI_ID);
		MSLWString title=L"Rankings " + pPool->getLDescription();
		MSLDialog(m_hWnd,*m_pDlgRankings ,800,550,title,0,true,-1,GUI_RGB_WHITE,m_hWnd);
		APP::unlock("Rankings "+ pPool->getKey());
		delete m_pDlgRankings;
		m_pDlgRankings=0;
	}
}

mslToolsFcCompare CHMatchGUIEx::getSortPoolResults() const
{
	return orderPoolResults;
}

bool CHMatchGUIEx::validComboPoolResult(GTHPoolResult *pPoolResult, GTHMatchResult* pMatchResult)
{
	// Si ese pool result ya esta en la ronda o ha jugado contra ese match result devuelvo false
	CHMatch * pMatch = (CHMatch*)pMatchResult->getMatch();
	if (!pMatch)
		return false;

	if (pPoolResult->getBye())
		return true;

	CHPool * pPool = (CHPool * ) pMatch->getPool();
	MSLSortedVector vRoundMatches;
	pPool->getRoundMatchesVector(vRoundMatches,pMatch->getRound());
	for (short i=0;i<vRoundMatches.entries();i++)
	{
		CHMatch* pMatchF = (CHMatch*)vRoundMatches[i];
		if (pMatchF->getKey()==pMatch->getKey())
			continue;

		CHMatchResult * pHome = (CHMatchResult *)pMatchF->getHome();
		CHMatchResult * pAway = (CHMatchResult *)pMatchF->getAway();

		if (pHome->getInscriptionKey()==pPoolResult->getInscriptionKey())
			return false;

		if (pAway->getInscriptionKey()==pPoolResult->getInscriptionKey())
			return false;
	}

	CHMatchResult * pOpponent = (CHMatchResult * ) pMatchResult->getOpponent();
	if (pOpponent->getInscription())
	{
		MSLSortedVector vPoolMatches;
		pPool->getMatchesVector(vPoolMatches);
		for (short i=0;i<vPoolMatches.entries();i++)
		{
			CHMatch * pMatchF = (CHMatch*) vPoolMatches[i];
			if (pMatchF->getSubCode())
				continue;
			
			CHMatchResult * pHome = (CHMatchResult *)pMatchF->getHome();
			CHMatchResult * pAway = (CHMatchResult *)pMatchF->getAway();
			
			if (pHome->getInscriptionKey() == pOpponent->getInscriptionKey() &&
				pAway->getInscriptionKey() == pPoolResult->getInscriptionKey())
				return false;

			if (pAway->getInscriptionKey() == pOpponent->getInscriptionKey() &&
				pHome->getInscriptionKey() == pPoolResult->getInscriptionKey())
				return false;
		}
	}

	if (pOpponent->getInscription() && pOpponent->getInscriptionKey() == pPoolResult->getInscriptionKey())
		return false;

	return true;
}