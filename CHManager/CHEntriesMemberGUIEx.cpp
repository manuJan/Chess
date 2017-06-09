/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHEntriesMemberGUIEx.cpp
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
#include "CHEntriesMemberGUIEx.h"
#include "..\CHMngtModel\CHMember.h"
#include "..\CHMngtModel\CHRegister.h"

CHEntriesMemberGUIEx::CHEntriesMemberGUIEx(long id)
:GEntriesMemberGUIEx(id)
{
}

CHEntriesMemberGUIEx::~CHEntriesMemberGUIEx(void)
{
}

void CHEntriesMemberGUIEx::createGridMember(int yPos/*=46*/)
{
	GEntriesMemberGUIEx::createGridMember(yPos);

	m_gui.grid_addColumn(GR_MEMBER_MEMBER,"Rating",GUI_JUST_CENTER  ,50 ,C_MEMBER_RATING);
	m_gui.grid_addColumn(GR_MEMBER_MEMBER,"KConst",GUI_JUST_CENTER	,50 ,C_MEMBER_KCONST);
}

bool CHEntriesMemberGUIEx::paintGridMember(gui_grid_cell* cell)
{
	if(cell->y==-1 || !cell->lParamLine)
		return false;

	CHMember * pMember=(CHMember*)cell->lParamLine;

	if(pMember->getType()!=CHRegister::individual && !cell->bSelected)
		m_gui.paint_solid(RGB(240,240,240));
	
	switch (cell->lParamColumn)
	{
		case C_MEMBER_RATING:
		{
			m_gui.paint_text(pMember->getRatingAsString().toUnicode());	
			break;
		}
		case C_MEMBER_KCONST:
		{
			m_gui.paint_text(pMember->getKConstAsString().toUnicode());	
			break;
		}
	}

	return GEntriesMemberGUIEx::paintGridMember(cell);
}

void CHEntriesMemberGUIEx::dblClickGridMemberMember(long x, long y)
{
	gui_grid_cell *pCell=m_gui.grid_getCell(GR_MEMBER_MEMBER,x,y);
	if(!pCell)
		return;

	CHMember * pMember=(CHMember*)pCell->lParamLine;
	if (!pMember)
		return;

	int col=pCell->lParamColumn;

	if (col==C_MEMBER_RATING)
	{
		editRating(pMember);
		return;
	}
	if (col==C_MEMBER_KCONST)
	{
		editKConst(pMember);
		return;
	}

	GEntriesMemberGUIEx::clickGridMember(x,y);
}

void CHEntriesMemberGUIEx::editRating(CHMember *pMember)
{
	MSLString oldRating = pMember->getRatingAsString();
	MSLString sNewRating = m_gui.grid_showEdit(GR_MEMBER_MEMBER, oldRating,9,"####",4);
	if (sNewRating!=oldRating)
	{
		pMember->setRating(atoi(sNewRating));		
		CHSend.toServerDB(pMember);
	}
}

void CHEntriesMemberGUIEx::editKConst(CHMember *pMember)
{
	MSLString sOldKConst=pMember->getKConstAsString();
	MSLString sNewKConst = m_gui.grid_showEdit(GR_MEMBER_MEMBER, sOldKConst,9,"####",4);
	if (sOldKConst!=sNewKConst)
	{
		pMember->setKConst(short(atoi(sNewKConst)));
		CHSend.toServerDB(pMember);
	}
}

int CHEntriesMemberGUIEx::getTeamMembers()
{
	return 99;
}
