/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHRatingDiffGUIEx.cpp
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
#include "CHRatingDiffGUIEx.h"

static
int fnOrderRatingDif(const void *lParam1, const void *lParam2, LPARAM null)
{  	
	CHRatingDif *p1= (CHRatingDif *) lParam1;
	CHRatingDif *p2= (CHRatingDif *) lParam2;
	
	int order = p1->getCode() -  p2->getCode();
	if (order)
		return order;

	return strcmp(p1->getKey(), p2->getKey());
	
	UNREFERENCED_PARAMETER(null);
}

CHRatingDiffGUIEx::CHRatingDiffGUIEx(long id)
:MSLGUIEx(id)
{
}
	
CHRatingDiffGUIEx::~CHRatingDiffGUIEx()
{
}

GMemoryDataBase * CHRatingDiffGUIEx::getMem() const
{
	return CHMemoryDataBase::getMem();
}
	
RECT CHRatingDiffGUIEx::getRect() const
{
	RECT aRect;
	GetClientRect(m_hWnd,&aRect);
	return aRect;
}

LRESULT CHRatingDiffGUIEx::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		// Comms
		case UM_COMMS_PACKTRANSACTION:	return onCommsPackTrn		(wParam, lParam);
		case UM_COMMS_DATA			 :	return onCommsData			(wParam, lParam);
	}
	return MSLGUIEx::wndProc(hWnd,message,wParam,lParam);
}

bool CHRatingDiffGUIEx::onInit()
{
	onCreateControl	();
	onFillControl	();
	return true;
}

void CHRatingDiffGUIEx::createGridRatingDif()
{
	RECT aRect=getRect();
	m_gui.doLbl(LB_CH_RATING_DIF, RC(aRect.left,aRect.top,aRect.right,aRect.top+16) ,"Rating Difference", GUIM_ID_STY_TITLE);	

	m_gui.doGrid(GR_CH_RATING_DIF,RC(aRect.left,aRect.top+18,aRect.right-20,aRect.bottom));
	m_gui.grid_setLineColor(GR_CH_RATING_DIF,GUI_RGB_OFF,GUI_RGB_OFF);
	
	m_gui.grid_addColumn(GR_CH_RATING_DIF,"Code",GUI_JUST_CENTER		, 50	,C_CODE);
	m_gui.grid_addColumn(GR_CH_RATING_DIF,"Probability",GUI_JUST_CENTER	,100	,C_PROBABILITY);	
	m_gui.grid_addColumn(GR_CH_RATING_DIF,"Difference",GUI_JUST_CENTER	, 75	,C_DIFFERENCE);	
}

void CHRatingDiffGUIEx::fillGridRatingDif()
{
	m_gui.grid_reset(GR_CH_RATING_DIF);
		
	CHRatingDif *pRatingDif=0;
	MSLSetIterator it(CHMemoryDataBase::getCol(__CHRATINGDIF));
	while( (pRatingDif=(CHRatingDif *)it() ) != 0) 
		m_gui.grid_add(GR_CH_RATING_DIF, (LPARAM)pRatingDif, TOSTRING(pRatingDif->getCode()));
	
	m_gui.grid_sort(GR_CH_RATING_DIF, getGridSortRatingDif());
}

bool CHRatingDiffGUIEx::onGridPaint(long id,gui_grid_cell* cell)
{
	if(id==GR_CH_RATING_DIF)
		return paintGridRatingDif(cell);
	
	return false;
}

bool CHRatingDiffGUIEx::paintGridRatingDif(gui_grid_cell* cell)
{
	if(cell->y==-1 || !cell->lParamLine)
		return false;		
	
	CHRatingDif *pRatingDif = (CHRatingDif*)cell->lParamLine;
	
	switch (cell->lParamColumn)
	{
		case C_CODE:
			m_gui.paint_text( TOWSTRING (pRatingDif->getCode(),L"0") );
			break;
		case C_PROBABILITY:
			m_gui.paint_text( pRatingDif->getProbabilityCodeStr().toUnicode() );
			break;
		case C_DIFFERENCE:
			m_gui.paint_text( pRatingDif->getDifferenceStr().toUnicode() );
			break;
	}
	return true;
}

void CHRatingDiffGUIEx::onLButDblClick(long id,long x,long y)
{
	if(id==GR_CH_RATING_DIF)
		dblClickGridRatingDif(x,y);
}

void CHRatingDiffGUIEx::onGridCursor(long id,long x,long y)
{
	UNREFERENCED_PARAMETER(id);
	UNREFERENCED_PARAMETER(x);
	UNREFERENCED_PARAMETER(y);
}

bool CHRatingDiffGUIEx::onGridHand(long id,long x,long y)
{
	return false;
	UNREFERENCED_PARAMETER(id);
	UNREFERENCED_PARAMETER(x);
	UNREFERENCED_PARAMETER(y);
}

void CHRatingDiffGUIEx::dblClickGridRatingDif(int x, int y)
{	
	gui_grid_cell * pCell=m_gui.grid_getCell(GR_CH_RATING_DIF,x,y);
	if(!pCell)
		return;
	
	CHRatingDif* pRatingDif = (CHRatingDif*)pCell->lParamLine;

	int col=pCell->lParamColumn;

	switch (col)
	{
		case C_DIFFERENCE:	
		{
			editDifference(pRatingDif);			
			break;
		}
	}

}

void CHRatingDiffGUIEx::editDifference(CHRatingDif* pRatingDif)
{	
	short oldDiff = pRatingDif->getDifference();
	MSLString format="####";
	if(oldDiff<0)
		format="-####";

	MSLString sNewDiff = m_gui.grid_showEdit(GR_CH_RATING_DIF, TOSTRING(oldDiff), 9,format,4);
	if (oldDiff!=atoi(sNewDiff))
	{
		pRatingDif->setDifference(short(atoi(sNewDiff)));
		CHSend.toServerDB(pRatingDif);
	}
}

mslToolsFcCompare CHRatingDiffGUIEx::getSortRatingDif() const
{
	return 0;
}

PFN_ORDER_FC CHRatingDiffGUIEx::getGridSortRatingDif() const
{
	return fnOrderRatingDif;
}

LRESULT CHRatingDiffGUIEx::onCreateControl(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	if(!wParam || wParam==GR_CH_RATING_DIF)
		createGridRatingDif();
		
	return 0;
	UNREFERENCED_PARAMETER(lParam);
}

LRESULT CHRatingDiffGUIEx::onDestroyControl(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	if(!wParam || wParam==GR_CH_RATING_DIF)
	{
		m_gui.delCtrl(GR_CH_RATING_DIF);
		return 1;
	}

	if(!wParam)
	{
		m_gui.delCtrl(GR_CH_RATING_DIF);		
		return 1;	
	}

	return 0;
	UNREFERENCED_PARAMETER(lParam);
}

LRESULT CHRatingDiffGUIEx::onFillControl(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	UNREFERENCED_PARAMETER(lParam);

	if(!wParam || wParam==GR_CH_RATING_DIF)
	{
		fillGridRatingDif();
		return 1;
	}
	return 0;
}	

LRESULT CHRatingDiffGUIEx::onRedrawControl(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	if(!wParam || wParam==GR_CH_RATING_DIF )
	{
		m_gui.redraw(GR_CH_EVENT_CRITERIA);
		m_gui.grid_sort(GR_CH_EVENT_CRITERIA, getGridSortRatingDif());
		return 1;
	}

	return 0;
	UNREFERENCED_PARAMETER(lParam);
}

LRESULT CHRatingDiffGUIEx::onHideControl(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	if(!wParam || wParam==GR_CH_RATING_DIF )
	{
		m_gui.setVisible(GR_CH_RATING_DIF,false);
		m_gui.redraw(GR_CH_RATING_DIF);		
	}

	if (!wParam || wParam==LB_CH_RATING_DIF)
	{
		m_gui.setVisible(LB_CH_RATING_DIF,false);
		m_gui.redraw(LB_CH_RATING_DIF);		
	}

	return 1;	
	UNREFERENCED_PARAMETER(lParam);
}

LRESULT CHRatingDiffGUIEx::onShowControl(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	if(!wParam || wParam==GR_CH_RATING_DIF )
	{
		m_gui.setVisible(GR_CH_RATING_DIF,true);
		m_gui.setFocus(GR_CH_RATING_DIF);
		m_gui.redraw(GR_CH_RATING_DIF);		
	}
	
	if (!wParam || wParam==LB_CH_RATING_DIF)
	{
		m_gui.setVisible(LB_CH_RATING_DIF,true);
		m_gui.redraw(LB_CH_RATING_DIF);		
	}

	return 0;
	UNREFERENCED_PARAMETER(lParam);
}

LRESULT CHRatingDiffGUIEx::onCommsPackTrn(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	return 0;
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);
}

LRESULT CHRatingDiffGUIEx::onCommsData(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	return 0;
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);
}		
