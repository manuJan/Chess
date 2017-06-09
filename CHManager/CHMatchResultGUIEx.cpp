#include "StdAfx.h"
/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHMatchResultGUIEx.cpp
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
#include "CHManagerApp.h"
#include "CHMatchResultGUIEx.h"
#include "CHProgression.h"

#include "..\CHMngtModel\CHPhase.h"
#include "..\CHMngtModel\CHMatchResult.h"
#include "..\CHMngtModel\CHRegister.h"
#include "..\CHMngtModel\CHPool.h"
#include "..\CHMngtModel\CHMatch.h"

#include <ovr\core\th\gthmsgdefines.h>

CHMatchResultGUIEx::CHMatchResultGUIEx(GTHProgression* pProgression, GTHProgressionData* pProgressionData, long id)
:GTHMatchResultGUIEx(pProgression,pProgressionData,id)
{
	
}

CHMatchResultGUIEx::~CHMatchResultGUIEx()
{
}

PFN_ORDER_FC CHMatchResultGUIEx::getGridSortMatchResults() const
{
	return grid_compare;
}

MSLGUIEx * CHMatchResultGUIEx::onNewGUIEx(long id)
{
	if (id==ARDRAWGUI_ID)
	{
	}

	return GTHMatchResultGUIEx::onNewGUIEx(id);
}

void CHMatchResultGUIEx::createGridMatchResults()
{
	GTHMatchResultGUIEx::createGridMatchResults();

	m_gui.grid_addColumn(GR_MATCHRESULTS,"", GUI_JUST_CENTER, 30, C_MR_RANK);
	m_gui.grid_addColumn(GR_MATCHRESULTS,"", GUI_JUST_CENTER, 30, C_MR_BIB	);	
}
	
bool CHMatchResultGUIEx::paintHeaderGrid(gui_grid_cell* cell)
{
	switch (cell->lParamColumn)
	{
		case C_MR_RANK:
			m_gui.paint_text(L"Rank");
			return true;
		case C_MR_BIB:
			m_gui.paint_text(L"Bib");
			return true;
	}

	return GTHMatchResultGUIEx::paintHeaderGrid(cell);
}

bool CHMatchResultGUIEx::paintGridMatchResults(gui_grid_cell* cell)
{
	if(cell->y==-1 || !cell->lParamLine)
		return paintHeaderGrid(cell);		
	
	CHMatchResult* pMatchResult = (CHMatchResult*) cell->lParamLine;
	if (!pMatchResult)
		return false;

	int col=cell->lParamColumn;

	switch (col)
	{
		case C_MR_RANK:
		{
			MSLString rank = getRank( pMatchResult );
			if (!rank.length())
				m_gui.paint_solid(GUI_RGB_LYELLOW);

			m_gui.paint_text( rank.toUnicode() );
			return true;
		}		
		case C_MR_BIB:
		{
			MSLString bib = getBib( pMatchResult );
			if (!bib.length())
				m_gui.paint_solid(GUI_RGB_LYELLOW);

			m_gui.paint_text( bib.toUnicode() );
			return true;
		}
	}

	return GTHMatchResultGUIEx::paintGridMatchResults(cell);
}

void CHMatchResultGUIEx::dblClickGridMatchResults(int x, int y)
{
	gui_grid_cell * pCell=m_gui.grid_getCell(GR_MATCHRESULTS,x,y);
	if(!pCell)
		return;
	
	CHMatchResult* pMatchResult = (CHMatchResult*) pCell->lParamLine;
	if (!pMatchResult)
		return;

	int col=pCell->lParamColumn;

	if (!canChangeMatchResult(pMatchResult,col))
		return;

	switch (col)
	{
		case C_MR_RANK:
			editRank(pMatchResult);
			return;
	
		case C_MR_BIB:
			editBib(pMatchResult);
			return;	
	}

	GTHMatchResultGUIEx::dblClickGridMatchResults(x,y);
}

void CHMatchResultGUIEx::onLButDown(long id,long x,long y)
{
	gui_grid_cell * pCell=m_gui.grid_getCell(GR_MATCHRESULTS,x,y);
	if(!pCell)
		return;
	
	if (y!=-1)
		return;

	int col=pCell->lParamColumn;

	switch (col)
	{	
	}

	GTHMatchResultGUIEx::onLButDown(id,x,y);
}

void CHMatchResultGUIEx::editBib(CHMatchResult *pMatchResult)
{
	if (!pMatchResult)
		return;

	CHRegister* pRegister = (CHRegister*)pMatchResult->getRegister();
	if (!pRegister)
		return;

	MSLString sOldBib = pRegister->getBib();
	MSLString sNewBib = m_gui.grid_showEdit(GR_MATCHRESULTS,sOldBib,getStyEdit(GR_MATCHRESULTS),0,4);

	if (strcmp(sNewBib,sOldBib))
	{
		pRegister->setBib(sNewBib);
		
		APP::out(*pRegister);
		APP::out(TRN_SET_REGISTER);
	}
}

void CHMatchResultGUIEx::editRank(CHMatchResult *pMatchResult)
{
	if (!pMatchResult)
		return;

	MSLString sOldRank = TOSTRING(pMatchResult->getRank(),"0");
	MSLString sNewRank = m_gui.grid_showEdit(GR_MATCHRESULTS,sOldRank,getStyEdit(GR_MATCHRESULTS),0,3);

	if (strcmp(sNewRank,sOldRank))
	{
		pMatchResult->setRank(short(atoi(sNewRank)));
		
		APP::out(*pMatchResult);
		APP::out(TRN_SET_MATCHRESULT);
	}
}


LRESULT CHMatchResultGUIEx::onLButDownToolBar(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	if (wParam==LX_PHASE_ARDRAW)
	{
		draw();
		return 0;
	}

	return GTHMatchResultGUIEx::onLButDownToolBar(wParam, lParam);
}
	
MSLWString CHMatchResultGUIEx::getBib(CHMatchResult *pMatchResult)
{
	return "";
}

MSLWString CHMatchResultGUIEx::getRank(CHMatchResult *pMatchResult)
{
	return pMatchResult ? TOWSTRING(pMatchResult->getRank()) : NULLWSTRING;
}

bool CHMatchResultGUIEx::canChangeMatchResult(CHMatchResult *pMatchResult, int col)
{
	return true;
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(pMatchResult);
}

void CHMatchResultGUIEx::draw()
{
	if (!m_pDataSel)
		return;

	unsigned char status = CHMemoryDataBase::eAvailable;

		 if (m_pDataSel->isA()==__CHPHASE)
			status = ((CHPhase*)m_pDataSel)->getStatus();
	else if (m_pDataSel->isA()==__CHPOOL)
			status = ((CHPool*)m_pDataSel)->getStatus();
	else if (m_pDataSel->isA()==__CHMATCH)
			status = ((CHMatch*)m_pDataSel)->getStatus();		
	else
		return;

	if (status==CHMemoryDataBase::eSchedulled ||
		status==CHMemoryDataBase::eStartList )
		onNewGUIEx(ARDRAWGUI_ID);
	else
		MSLMsgBox( m_gui.getHWndBase() ,"The status is incorrent for draw",GUI_ICO_ERROR, GUI_MB_OK, "GUITHManager Error");	
}

void CHMatchResultGUIEx::onCreateMatchResult(GTHMatchResult* pMatchResult)
{
	onFillControl();
	UNREFERENCED_PARAMETER(pMatchResult);
}