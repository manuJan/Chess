/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHEntriesEventGUIEx.cpp
*   Description : 
*
*   Author      : Javier Juste
*   Date created: 2-FEb-2009
*   Project     : CH Manager
*
*   Modification history
*   By      :
*   Date    :
*   Changes :
*
*****************************************************************************************/

#include "StdAfx.h"
#include "CHManagerApp.h"
#include "CHEntriesEventGUIEx.h"
#include "..\CHMngtModel\CHEvent.h"
#include "..\CHMngtModel\CHInscription.h"
#include "..\CHMngtModel\CHRegister.h"

CHEntriesEventGUIEx::CHEntriesEventGUIEx(long id)
:GEntriesEventGUIEx(id)
{
}

CHEntriesEventGUIEx::~CHEntriesEventGUIEx()
{
}

void CHEntriesEventGUIEx::createGridEvent()
{
	GEntriesEventGUIEx::createGridEvent();

	m_gui.grid_setCellW(GR_EVENT,1,150);
	m_gui.grid_setCellW(GR_EVENT,2,75);
	m_gui.grid_setCellW(GR_EVENT,0,30);

	m_gui.grid_addColumn(GR_EVENT,"Rating"		,GUI_JUST_CENTER, 50  ,C_RATING	);
	m_gui.grid_addColumn(GR_EVENT,"Seed"		,GUI_JUST_CENTER, 50  ,C_SEED	);
	m_gui.grid_addColumn(GR_EVENT,"KConst"		,GUI_JUST_CENTER, 50  ,C_KCONST	);
	
	m_gui.grid_setCellTT(GR_EVENT,m_gui.grid_findCol(GR_EVENT,C_RATING	),-1,"Rating");
	m_gui.grid_setCellTT(GR_EVENT,m_gui.grid_findCol(GR_EVENT,C_SEED	),-1,"Seed");
	m_gui.grid_setCellTT(GR_EVENT,m_gui.grid_findCol(GR_EVENT,C_KCONST	),-1,"K. Const");
}
	
bool CHEntriesEventGUIEx::paintGridEvent(gui_grid_cell* cell)
{
	if(cell->y==-1 || !cell->lParamLine)
		return false;

	GEvent * pEvent=(GEvent*)cell->lParamLine;

	CHInscription * pInscription =  (CHInscription*)getInscription(m_pRegisterSel,pEvent);
	
	switch (cell->lParamColumn)
	{
		case C_RATING:
			if (pInscription)
				m_gui.paint_text( pInscription->getRatingAsString().toUnicode() );
			break;
		case C_SEED:
			if (pInscription)
				m_gui.paint_text( pInscription->getSeedAsString().toUnicode() );
			break;
		case C_KCONST:		
			if (pInscription)
				m_gui.paint_text( pInscription->getKConstAsString().toUnicode() );
			break;		
	}

	return GEntriesEventGUIEx::paintGridEvent(cell);
}

void CHEntriesEventGUIEx::onLButDblClick(long id,long x,long y)
{
	if (id==GR_EVENT)
		dblClickGridEntriesEvent(x,y);
}

void CHEntriesEventGUIEx::dblClickGridEntriesEvent(long x, long y)
{
	gui_grid_cell * pCell=m_gui.grid_getCell(GR_EVENT,x,y);
	if(!pCell)
		return;
	
	CHEvent* pEvent = (CHEvent*) pCell->lParamLine;
	if (!pEvent)
		return;

	CHInscription* pInscription = (CHInscription*)getInscription();
	if (!pInscription)
		return;

	int col=pCell->lParamColumn;
	
		 if (col==C_RATING)
			editRating((CHInscription*)getInscription(m_pRegisterSel,pEvent));
	else if (col==C_SEED)
			editSeed((CHInscription*)getInscription(m_pRegisterSel,pEvent));
	else if (col==C_KCONST)
			editKConst((CHInscription*)getInscription(m_pRegisterSel,pEvent));
}

void CHEntriesEventGUIEx::editRating(CHInscription* pInscription)
{
	MSLString oldRating = pInscription->getRatingAsString();
	MSLString sNewRating = m_gui.grid_showEdit(GR_EVENT, oldRating,9,"####",4);
	if (sNewRating!=oldRating)
	{
		pInscription->setRating(atoi(sNewRating));		
		CHSend.toServerDB(pInscription);
	}
}

void CHEntriesEventGUIEx::editSeed(CHInscription* pInscription)
{
	MSLString sOldSeed=pInscription->getSeedAsString();
	MSLString sNewSeed= m_gui.grid_showEdit(GR_EVENT, sOldSeed,9,"####",4);
	if (sOldSeed!=sNewSeed)
	{
		pInscription->setSeed(short(atoi(sNewSeed)));
		CHSend.toServerDB(pInscription);
	}
}

void CHEntriesEventGUIEx::editKConst(CHInscription* pInscription)
{
	MSLString sOldKConst=pInscription->getKConstAsString();
	MSLString sNewKConst = m_gui.grid_showEdit(GR_EVENT, sOldKConst,9,"####",4);
	if (sOldKConst!=sNewKConst)
	{
		pInscription->setKConst(short(atoi(sNewKConst)));
		CHSend.toServerDB(pInscription);
	}
}
