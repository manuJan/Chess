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
#include "CHRankingsGUI.h"
#include "CHManagerDefs.h"
#include "..\CHMngtModel\CHPool.h"
#include <ovr\gui\GUITHManager\GUITHManager.h>
#include <ovr\core\th\GTHMsgDefines.h>

#include "..\CHMngtModel\CHEvent.h"
#include "..\CHMngtModel\CHPool.h"
#include "..\CHMngtModel\CHPoolResult.h"

static int orderPoolResultsByRank(const MSLItem** a, const MSLItem** b)
{
	CHPoolResult * pPoolResultA = (CHPoolResult *) (*a);
	CHPoolResult * pPoolResultB = (CHPoolResult *) (*b);

	CHPool *pPoolA=(CHPool*)pPoolResultA->getPool();
	CHPool *pPoolB=(CHPool*)pPoolResultB->getPool();

	// Order by Pool
	int order = pPoolA->getOrder() - pPoolB->getOrder();
	if( order )
		return order;

	// Si alguno de ellos no tienen la sesión asignada va para abajo.
	if (!pPoolResultA->getRankPo())
		return 1;
	if (!pPoolResultB->getRankPo())
		return -1;

	// Order by Rank Po
	order = pPoolResultA->getRankPo() - pPoolResultB->getRankPo();
	if( order )
		return order;

	// Si alguno de ellos no tienen la sesión asignada va para abajo.
	if (!pPoolResultA->getRank())
		return 1;
	if (!pPoolResultB->getRank())
		return -1;

	// Order by Rank 
	order = pPoolResultA->getRank() - pPoolResultB->getRank();
	if( order )
		return order;
	
	// Order by key
	return strcmp(pPoolResultA->getKey(),pPoolResultB->getKey());
}

static 
int pfc_orderPoolResultsByRank(const void *lParam1, const void *lParam2, LPARAM null)
{
	GTHPoolResult *pPoolResultA= (GTHPoolResult *) lParam1;
	GTHPoolResult *pPoolResultB= (GTHPoolResult *) lParam2;

	int	order = pPoolResultA->getPoolCode()-pPoolResultB->getPoolCode();
	if (order)
		return order;

	// Si alguno de ellos no tienen la sesión asignada va para abajo.
	if (!pPoolResultA->getRankPo())
		return 1;
	if (!pPoolResultB->getRankPo())
		return -1;

	// Order by Rank Po
	order = pPoolResultA->getRankPo() - pPoolResultB->getRankPo();
	if( order )
		return order;

	// Si alguno de ellos no tienen la sesión asignada va para abajo.
	if (!pPoolResultA->getRank())
		return 1;
	if (!pPoolResultB->getRank())
		return -1;

	// Order by Rank 
	order = pPoolResultA->getRank() - pPoolResultB->getRank();
	if( order )
		return order;
	
	// Order by key
	return strcmp(pPoolResultA->getKey(),pPoolResultB->getKey());
	UNREFERENCED_PARAMETER(null);
}

CHRankingsGUI::CHRankingsGUI(CHPool * pPool, GTHProgression* pProgression, GTHProgressionData* pProgressionData, long id)
:GTHPoolResultGUIEx(pProgression, pProgressionData, id)
,m_pPool(pPool)
{
	setDataSel(pPool);
}

CHRankingsGUI::~CHRankingsGUI()
{	
}

// Virtual Sort Functions
mslToolsFcCompare CHRankingsGUI::getSortPoolResults() const
{
	return orderPoolResultsByRank;
}

PFN_ORDER_FC CHRankingsGUI::getGridSortPoolResults() const
{
	return pfc_orderPoolResultsByRank;
}

MSLGUIEx * CHRankingsGUI::onNewGUIEx(long id)
{
	switch(id)
	{
		case TB_POOLRESULT_ID:
		{
			return 0;	
		}
	}

	return 0;
}

LRESULT CHRankingsGUI::onFillControl(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	UNREFERENCED_PARAMETER(lParam);

	if(!wParam || wParam==GR_POOLRESULTS)
	{
		fillGridPoolResultsCH();
		return 1;
	}
	return 0;
}

bool CHRankingsGUI::onDrag(long id,gui_dd_item* dd)
{
	return (!dd || (id!=GR_POOLRESULTS && dd->idTarget!=GR_POOLRESULTS)) ? false : true;
}

void CHRankingsGUI::onDrop(long id,gui_dd_item* dd)
{
	UNREFERENCED_PARAMETER(id);
	if( dd->idSource == GR_POOLRESULTS && dd->idTarget == GR_POOLRESULTS )
	{
		int pos = dd->cellTarget->y;
		GData * pDataMember = (GData *)dd->cellSource->lParamLine;
		updateRanking(pDataMember,pos);
	}
}

void CHRankingsGUI::onClick(long id,LPARAM lParam)
{
	return GTHManagerGUI::onClick(id,lParam);
}

void CHRankingsGUI::createOtherControls()
{
	RECT aRect=getRect();
	short hCtrl=0;

	MSLWString poolResults = GUITHManagerApp::getOverallSPoolDescription();
	poolResults+=DESC(PROGRESSION_PRG_RESULTS);
	m_gui.doLbl(LB_POOLRESULTS,RC(aRect.left,aRect.top+hCtrl,aRect.right-16,aRect.top+16+hCtrl) ,poolResults,getStyTitle(LB_POOLRESULTS));	
}


void CHRankingsGUI::createGridPoolResults()
{
	RECT aRect=getRect();
	short hCtrl1=16;
	
	m_gui.doGrid(GR_POOLRESULTS,RC(aRect.left,aRect.top+hCtrl1,aRect.right-16,aRect.bottom),getStyGrid(GR_POOLRESULTS),getStyGridSel(GR_POOLRESULTS),30,getStyHeaderGrid(GR_POOLRESULTS));
	m_gui.grid_setLineColor(GR_POOLRESULTS,GUI_RGB_OFF,GUI_RGB_OFF); 
	
	m_gui.grid_addColumn(GR_POOLRESULTS,"",GUI_JUST_RIGHT , 35	,C_PR_RANK			);	
	m_gui.grid_addColumn(GR_POOLRESULTS,"Rk",GUI_JUST_RIGHT , 35	,C_PR_CH_RK		);	
	m_gui.grid_addColumn(GR_POOLRESULTS,"",GUI_JUST_LEFT  ,250	,C_PR_NAME			);
	m_gui.grid_addColumn(GR_POOLRESULTS,"",GUI_JUST_CENTER, 25			,C_PR_COUNTRY		);
	m_gui.grid_addColumn(GR_POOLRESULTS,"IRM",GUI_JUST_CENTER, 35		,C_PR_CH_QCODE		);	
	m_gui.grid_addColumn(GR_POOLRESULTS,"Points",GUI_JUST_CENTER, 45	,C_PR_CH_POINTS		);
		
	CHEvent * pEvent = (CHEvent*)m_pPool->getEvent();
	if (pEvent && 
		pEvent->findRankOrder( CHEvent::eMatchPoints) )
		m_gui.grid_addColumn(GR_POOLRESULTS,"Match Pts",GUI_JUST_CENTER, 55	,C_PR_CH_MATCHPOINTS);

	if (pEvent && 
		pEvent->findRankOrder( CHEvent::eDirectEncounter) )
		m_gui.grid_addColumn(GR_POOLRESULTS,"Direct Enc.",GUI_JUST_CENTER, 55, C_PR_CH_DIRECTMATCH);

	if (pEvent && 
		pEvent->findRankOrder( CHEvent::eSolkoffCutLowest) )
		m_gui.grid_addColumn(GR_POOLRESULTS,"Buchholz(Cut 1)",GUI_JUST_CENTER, 85, C_PR_CH_BUCHOLZCUT1);

	if (pEvent && 
		pEvent->findRankOrder( CHEvent::eSolkoff) )
		m_gui.grid_addColumn(GR_POOLRESULTS,"Buchholz",GUI_JUST_CENTER, 55, C_PR_CH_BUCHOLZ);

	if (pEvent && 
		pEvent->findRankOrder( CHEvent::eSolkoff) )
		m_gui.grid_addColumn(GR_POOLRESULTS,"Won games",GUI_JUST_CENTER, 65, C_PR_CH_WONGAMES);

	if (pEvent && 
		pEvent->findRankOrder( CHEvent::eSonneBerger) )
		m_gui.grid_addColumn(GR_POOLRESULTS,"Sonne-berger",GUI_JUST_CENTER, 75, C_PR_CH_SONNEBERGER);
	
	
	m_gui.grid_setCellTT(GR_POOLRESULTS,m_gui.grid_findCol(GR_POOLRESULTS,C_PR_RANK			),-1,DESC(PROGRESSION_PRG_COMPPOOLRK));	
	m_gui.grid_setCellTT(GR_POOLRESULTS,m_gui.grid_findCol(GR_POOLRESULTS,C_PR_CH_RK		),-1,DESC(PROGRESSION_PRG_COMPPOOLRK));	
	m_gui.grid_setCellTT(GR_POOLRESULTS,m_gui.grid_findCol(GR_POOLRESULTS,C_PR_NAME			),-1,DESC(PROGRESSION_PRG_COMPNAME));
	m_gui.grid_setCellTT(GR_POOLRESULTS,m_gui.grid_findCol(GR_POOLRESULTS,C_PR_COUNTRY		),-1,DESC(PROGRESSION_PRG_COMPCTRY));

	m_gui.setDragDrop(GR_POOLRESULTS,"Rankings "+m_pPool->getLDescription().toAscii());
	m_gui.setDragDropOn(GR_POOLRESULTS,true,true);

}

bool CHRankingsGUI::paintHeaderGrid(gui_grid_cell* cell)
{
	switch (cell->lParamColumn)
	{
		case C_PR_RANK:
		m_gui.paint_text("Rk Po", GUI_ID_FNT, GUI_RGB_BLACK, GUI_JUST_CENTER);
		return false;
	}
	return GTHPoolResultGUIEx::paintHeaderGrid(cell);
}

void CHRankingsGUI::fillGridPoolResultsCH()
{
	m_gui.grid_reset(GR_POOLRESULTS);
	
	if (!m_pDataSel)
		return;

	MSLSortedVector *gsvPoolResults=0;
	
	if (m_pDataSel->isA()==__GTHPHASE)
	{
		MSLSet colPoolResults;
		((GTHPhase*)m_pDataSel)->getPoolResults(colPoolResults);
		gsvPoolResults=new MSLSortedVector(colPoolResults,getSortPoolResults());
	}
	else if (m_pDataSel->isA()==__GTHPOOL)
		gsvPoolResults=new MSLSortedVector(((GTHPool*)m_pDataSel)->getPoolResults(),getSortPoolResults());
	else if (m_pDataSel->isA()==__GTHMATCH)
	{
		GTHPool* pPool = (GTHPool*) ((GTHMatch*)m_pDataSel)->getPool();
		if (pPool)
			gsvPoolResults=new MSLSortedVector(pPool->getPoolResults(),getSortPoolResults());
	}
	else 
		return;

	if (!gsvPoolResults)
		return;

	for (long i=0; i<gsvPoolResults->entries(); i++)
	{
		GTHPoolResult * pPoolResult = (GTHPoolResult *) (*gsvPoolResults)[i];
		insertPoolResultCH(pPoolResult);
	}

	delete gsvPoolResults;
}

void CHRankingsGUI::insertPoolResultCH(GTHPoolResult* pPoolResult)
{
	if (!pPoolResult)
		return;

	GTHPoolResult* pRealPoolResult = (GTHPoolResult*) GTHMemoryDataBase::find(*pPoolResult);
	if (!pRealPoolResult)
		return;

	if (pRealPoolResult->getBye())
		return;

	if (m_gui.grid_find(GR_POOLRESULTS,(LPARAM)pRealPoolResult)>=0)
		onRedrawControl();
	else 
		m_gui.grid_add(GR_POOLRESULTS,(LPARAM)pRealPoolResult);		

	m_gui.grid_sort(GR_POOLRESULTS,getGridSortPoolResults());
}

bool CHRankingsGUI::paintGridPoolResults(gui_grid_cell* cell)
{
	bool ret = GTHPoolResultGUIEx::paintGridPoolResults(cell);

	CHPoolResult * pPoolResult=(CHPoolResult*)cell->lParamLine;
	if (!pPoolResult)
		return false;
	
	switch (cell->lParamColumn)
	{
		case C_PR_CH_RK:
			m_gui.paint_text(TOWSTRING(pPoolResult->getRank()), GUI_ID_FNT, COLORREF(-1), GUI_JUST_CENTER);
			break;
		case C_PR_CH_POINTS:
			m_gui.paint_text(pPoolResult->getPointsFStr().toUnicode(), GUI_ID_FNT, COLORREF(-1), GUI_JUST_CENTER);
			break;
		case C_PR_CH_MATCHPOINTS:
			m_gui.paint_text(pPoolResult->getMatchPointsStr().toUnicode(), GUI_ID_FNT, COLORREF(-1), GUI_JUST_CENTER);
			break;
		case C_PR_CH_DIRECTMATCH:
			m_gui.paint_text(pPoolResult->getDirectMatchPtsStr().toUnicode(), GUI_ID_FNT, COLORREF(-1), GUI_JUST_CENTER);
			break;
		case C_PR_CH_BUCHOLZCUT1:
			m_gui.paint_text(pPoolResult->getMedianSolkOffFStr().toUnicode(), GUI_ID_FNT, COLORREF(-1), GUI_JUST_CENTER);
			break;
		case C_PR_CH_BUCHOLZ:
			m_gui.paint_text(pPoolResult->getSolkOffFStr().toUnicode(), GUI_ID_FNT, COLORREF(-1), GUI_JUST_CENTER);
			break;
		case C_PR_CH_WONGAMES:
			m_gui.paint_text( TOWSTRING(pPoolResult->getMatchesWon()), GUI_ID_FNT, COLORREF(-1), GUI_JUST_CENTER);
			break;
		case C_PR_CH_SONNEBERGER:
			m_gui.paint_text(pPoolResult->getSonneBergerFStr().toUnicode(), GUI_ID_FNT, COLORREF(-1), GUI_JUST_CENTER);
			break;
	}
	return ret;
}

bool CHRankingsGUI::canChangePoolResult(GTHPoolResult* pPoolResult, int col)
{
	return true;	
}

void CHRankingsGUI::onLButDblClick(long id,long x,long y)
{
	if(id==GR_POOLRESULTS)
		dblClickGridPoolResultsCH(x,y);
}

void CHRankingsGUI::dblClickGridPoolResultsCH(int x, int y)
{
	gui_grid_cell * pCell=m_gui.grid_getCell(GR_POOLRESULTS,x,y);
	if(!pCell)
		return;
	
	GTHPoolResult* pPoolResult = (GTHPoolResult*) pCell->lParamLine;
	if (!pPoolResult)
		return;

	int col=pCell->lParamColumn;

	if (!canChangePoolResult(pPoolResult, col))
		return;

	if (col==C_PR_RANK)
		editPoolRankingPositionCH(pPoolResult);	
	if (col==C_PR_CH_RK)
		editPoolRankingCH(pPoolResult);	
}


void CHRankingsGUI::editPoolRankingPositionCH(GTHPoolResult *pPoolResult)
{
	if (!pPoolResult)
		return;
	short oldRank = pPoolResult->getRankPo();

	MSLString sNewRank = m_gui.grid_showEdit(GR_POOLRESULTS,TOSTRING(pPoolResult->getRankPo()),3,"###",3);
	
	pPoolResult->setRankPo(short(atoi(sNewRank)));
	
	recalculateAllRanks((CHPoolResult*)pPoolResult, oldRank, short(atoi(sNewRank)));

	APP::out(*pPoolResult);	
	APP::out(TRN_SET_POOLRESULT);
	
	m_gui.grid_sort(GR_POOLRESULTS, pfc_orderPoolResultsByRank);

	SendMessage(getHWndMsgs(), UM_DATA_UPDATED, (WPARAM)GTHPOOLRESULTGUIEX_ID, (LPARAM)pPoolResult);	
}

void CHRankingsGUI::editPoolRankingCH(GTHPoolResult *pPoolResult)
{
	if (!pPoolResult)
		return;
	
	short oldRank = pPoolResult->getRank();

	MSLString sNewRank = m_gui.grid_showEdit(GR_POOLRESULTS,TOSTRING(pPoolResult->getRankPo()),3,"###",3);
	
	pPoolResult->setRank(short(atoi(sNewRank)));
		
	APP::out(*pPoolResult);	
	APP::out(TRN_SET_POOLRESULT);
	
	m_gui.grid_sort(GR_POOLRESULTS, pfc_orderPoolResultsByRank);

	SendMessage(getHWndMsgs(), UM_DATA_UPDATED, (WPARAM)GTHPOOLRESULTGUIEX_ID, (LPARAM)pPoolResult);	
}

void CHRankingsGUI::recalculateAllRanks(CHPoolResult *pPoolResult, short oldRank, short sNewRank)
{
	CHPool* pPool = (CHPool*) pPoolResult->getPool();
	MSLSortedVector vPoolResults;
	pPool->getPoolResultsVector(vPoolResults, orderPoolResultsByRank );
	int rankPo = 1;    
	for (short i = 0; i < vPoolResults.entries(); i++)
    {
        CHPoolResult * pPR = (CHPoolResult * )vPoolResults[i];
		rankPo = pPR->getRankPo();

        if (sNewRank < oldRank)
        {
            if (pPR == pPoolResult || rankPo < sNewRank)
				continue;
            
            if (rankPo >= sNewRank && rankPo < oldRank)
            {
				//pPR->setRank(rankPo+1);
				pPR->setRankPo(rankPo+1);
                APP::out(*pPR);	
            }
        }
        else 
        {
			if (pPR == pPoolResult || rankPo < oldRank)
				continue;

			if (rankPo > oldRank && rankPo <= sNewRank)
			{
				//pPR->setRank( rankPo-1);
				pPR->setRankPo( rankPo-1);
				APP::out(*pPR);					
			}
		}
    }

	APP::out(TRN_SET_POOLRESULT);
}

void CHRankingsGUI::updateRanking(GData* pDataMember/*=0*/,long pos/*=-1*/)
{
	if( pDataMember && pos != -1 )
	{
		m_gui.grid_delLParam(GR_POOLRESULTS,LPARAM(pDataMember));
		m_gui.grid_add      (GR_POOLRESULTS,LPARAM(pDataMember),"",false,pos);
	}
	CHPoolResult * pPResult = 0;
	for(short i=0 ; i<m_gui.grid_getNLines(GR_POOLRESULTS) ; i++)
	{
		CHPoolResult * pPResult = (CHPoolResult *)m_gui.grid_getLParam(GR_POOLRESULTS,i);
		if( pPResult && pPResult->getRankPo() != i+1 )
		{
			pPResult->setRankPo(i+1);
			APP::out(*pPResult);
		}
	}
	APP::out(TRN_SET_POOLRESULT);
	m_gui.grid_sort(GR_POOLRESULTS, pfc_orderPoolResultsByRank);
	SendMessage(getHWndMsgs(), UM_DATA_UPDATED, (WPARAM)GTHPOOLRESULTGUIEX_ID, (LPARAM)pPResult);	
}
