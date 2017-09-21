/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHEventCriteriaGUIEx.cpp
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
#include "CHEventCriteriaGUIEx.h"
#include "..\CHMngtModel\CHEvent.h"

static 
int pfn_orderEventCriteria(const void *lParam1, const void *lParam2, LPARAM null)
{
	CHRankOrder *p1= (CHRankOrder *) lParam1;
	CHRankOrder *p2= (CHRankOrder *) lParam2;

	if(!p1->m_order && p2->m_order)
		return 1;

	if(p1->m_order && !p2->m_order)
		return -1;
		
	int ord = p1->m_order -  p2->m_order;
	if(ord)
		return ord;
	
	return p1->m_rankType - p2->m_rankType;
	UNREFERENCED_PARAMETER(null);
}


CHRankOrder::CHRankOrder(short pos,short type)
:m_order(pos)
,m_rankType(type)
{
	setKey();
}
CHRankOrder::~CHRankOrder()
{
}
void CHRankOrder::setKey()
{
	char tmp[3];
	sprintf_s(tmp,"%.2d",m_rankType);
	key=tmp;
}

MSLPack& CHRankOrder::pack(MSLPack& pck) const
{
	return pck;
}

MSLPack& CHRankOrder::unpack(MSLPack& pck)
{
	return pck;
}

CHEventCriteriaGUIEx::CHEventCriteriaGUIEx(long id)
:MSLGUIEx(id)
,m_pEvent(0)
{
}
	
CHEventCriteriaGUIEx::~CHEventCriteriaGUIEx()
{
	colTypes.clearAndDestroy();
}

GMemoryDataBase * CHEventCriteriaGUIEx::getMem() const
{
	return CHMemoryDataBase::getMem();
}
	
RECT CHEventCriteriaGUIEx::getRect() const
{
	RECT aRect;
	GetClientRect(m_hWnd,&aRect);
	return aRect;
}

void CHEventCriteriaGUIEx::setOrderCriteria()
{
	if (!m_pEvent)
		return;

	MSLString orderRankingEvent;
	int nLines=m_gui.grid_getNLines(GR_CH_EVENT_CRITERIA);

	CHRankOrder * pRankOrder =0;
	for(short i=0 ; i<short(nLines) ; i++)
	{
		pRankOrder = (CHRankOrder *)m_gui.grid_getLParam(GR_CH_EVENT_CRITERIA,i);
		if(pRankOrder->m_order)
		{
			char tmp[3];
			sprintf_s(tmp,"%.2d",pRankOrder->m_rankType);

			orderRankingEvent+=tmp;
		}
	}

	m_pEvent->setReqRankOrder(orderRankingEvent);

	CHSend.toServerDB(m_pEvent);
}

LRESULT CHEventCriteriaGUIEx::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case UM_EVENT_SELECTED		 :	return onEventSelected		(wParam, lParam);
		// Comms
		case UM_COMMS_PACKTRANSACTION:	return onCommsPackTrn		(wParam, lParam);
		case UM_COMMS_DATA			 :	return onCommsData			(wParam, lParam);

	}

	return MSLGUIEx::wndProc(hWnd,message,wParam,lParam);
}


bool CHEventCriteriaGUIEx::onInit()
{
	onCreateControl	();
	onFillControl	();
	return true;
}

void CHEventCriteriaGUIEx::createGridEventCriteria()
{
	RECT aRect=getRect();
	m_gui.doGrid(GR_CH_EVENT_CRITERIA,RC(aRect.left,aRect.top+18,aRect.right,aRect.bottom));
	m_gui.grid_setLineColor(GR_CH_EVENT_CRITERIA,GUI_RGB_OFF,GUI_RGB_OFF);
	
	m_gui.grid_addColumn(GR_CH_EVENT_CRITERIA,"Order",GUI_JUST_CENTER	, 50	,C_ORDER);
	m_gui.grid_addColumn(GR_CH_EVENT_CRITERIA,"Criteria",GUI_JUST_LEFT	, 130	,C_CRITERIUM);	
}

void CHEventCriteriaGUIEx::createOtherControls()
{
	RECT aRect=getRect();
	m_gui.doLbl(LB_CH_EVENT_CRITERIA, RC(aRect.left,aRect.top,aRect.right,aRect.top+16) ,"Event Ranking Criteria", GUIM_ID_STY_TITLE);	
}

void CHEventCriteriaGUIEx::fillGridEventCriteria()
{
	if (!m_pEvent)
		return;

	m_gui.grid_reset(GR_CH_EVENT_CRITERIA);
	colTypes.clearAndDestroy();

	short nRanks=m_pEvent->getNumRankOrder();
	for(short i=0 ; i<(nRanks) ; i++)
	{
		short rankType=short(m_pEvent->getRankOrder(short(i)));
		if(rankType!=CHEvent::eEmpty)
			colTypes.insert(new CHRankOrder(short(i+1),rankType));
	}

	for(short i=CHEvent::eQualitative ;i <=CHEvent::eAvgOppRating ; i++)
	{
		CHRankOrder aRankOrder(0,short(i));

		if(!colTypes.find(&aRankOrder))
			colTypes.insert(new CHRankOrder(0,short(i)));
	}

	CHRankOrder *pRankOrder;
	MSLSetIterator it(colTypes);
	while( (pRankOrder=(CHRankOrder *)it() ) != 0) 
		m_gui.grid_add(GR_CH_EVENT_CRITERIA, (LPARAM)pRankOrder, getTypeCriteria(pRankOrder->m_rankType));
	
	m_gui.grid_sort(GR_CH_EVENT_CRITERIA, getGridSortEventCriteria(), (LPARAM)m_pEvent);
}

bool CHEventCriteriaGUIEx::onGridPaint(long id,gui_grid_cell* cell)
{
	if(id==GR_CH_EVENT_CRITERIA)
		return paintGridEventCriteria(cell);
	
	return false;
}

bool CHEventCriteriaGUIEx::paintGridEventCriteria(gui_grid_cell* cell)
{
	if(cell->y==-1 || !cell->lParamLine)
		return false;		
	
	CHRankOrder *pRankOrder = (CHRankOrder*)cell->lParamLine;
	
	switch (cell->lParamColumn)
	{
		case C_ORDER:
			m_gui.paint_text( TOWSTRING (pRankOrder->m_order) );
			break;
		case C_CRITERIUM:
			m_gui.paint_text( getTypeCriteria(pRankOrder->m_rankType).toUnicode());
			break;
	}
	return true;
}

void CHEventCriteriaGUIEx::onLButDblClick(long id,long x,long y)
{
	if(id==GR_CH_EVENT_CRITERIA)
		dblClickGridEventCriteria(x,y);
}

void CHEventCriteriaGUIEx::onGridCursor(long id,long x,long y)
{
	UNREFERENCED_PARAMETER(id);
	UNREFERENCED_PARAMETER(x);
	UNREFERENCED_PARAMETER(y);
}

bool CHEventCriteriaGUIEx::onGridHand(long id,long x,long y)
{
	return false;
	UNREFERENCED_PARAMETER(id);
	UNREFERENCED_PARAMETER(x);
	UNREFERENCED_PARAMETER(y);
}

void CHEventCriteriaGUIEx::dblClickGridEventCriteria(int x, int y)
{	
	gui_grid_cell * pCell=m_gui.grid_getCell(GR_CH_EVENT_CRITERIA,x,y);
	if(!pCell)
		return;
	
	CHRankOrder* pRankOrder = (CHRankOrder*)pCell->lParamLine;

	int col=pCell->lParamColumn;

	switch (col)
	{
		case C_ORDER:	
		{
			editOrder(pRankOrder);
			m_gui.grid_sort(GR_CH_EVENT_CRITERIA,getGridSortEventCriteria(),(LPARAM)m_pEvent);
			break;
		}
	}

}

void CHEventCriteriaGUIEx::editOrder(CHRankOrder* pRankOrder)
{
	if (!m_pEvent)
		return;

	short oldOrder = pRankOrder->m_order;
	MSLString sNewOrder = m_gui.grid_showEdit(GR_CH_EVENT_CRITERIA, TOSTRING(oldOrder), 9,"#",1);
	if (oldOrder!=atoi(sNewOrder))
	{
		pRankOrder->m_order = short(atoi(sNewOrder));
		setOrderCriteria();
	}
}

mslToolsFcCompare CHEventCriteriaGUIEx::getSortEventCriteria() const
{
	return 0;
}

PFN_ORDER_FC CHEventCriteriaGUIEx::getGridSortEventCriteria() const
{
	return pfn_orderEventCriteria;
}

LRESULT CHEventCriteriaGUIEx::onCreateControl(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	if(!wParam || wParam==GR_CH_EVENT_CRITERIA)
		createGridEventCriteria();
	
	if(!wParam)
		createOtherControls();

	return 0;
	UNREFERENCED_PARAMETER(lParam);
}

LRESULT CHEventCriteriaGUIEx::onDestroyControl(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	if(!wParam || wParam==GR_CH_EVENT_CRITERIA)
	{
		m_gui.delCtrl(GR_CH_EVENT_CRITERIA);
		return 1;
	}

	if(!wParam)
	{
		m_gui.delCtrl(LB_CH_EVENT_CRITERIA);		
		return 1;	
	}

	return 0;
	UNREFERENCED_PARAMETER(lParam);
}

LRESULT CHEventCriteriaGUIEx::onFillControl(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	UNREFERENCED_PARAMETER(lParam);

	if(!wParam || wParam==GR_CH_EVENT_CRITERIA)
	{
		fillGridEventCriteria();
		return 1;
	}
	return 0;
}	

LRESULT CHEventCriteriaGUIEx::onRedrawControl(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	if(!wParam || wParam==GR_CH_EVENT_CRITERIA )
	{
		m_gui.redraw(GR_CH_EVENT_CRITERIA);
		m_gui.grid_sort(GR_CH_EVENT_CRITERIA, getGridSortEventCriteria());
		return 1;
	}

	return 0;
	UNREFERENCED_PARAMETER(lParam);
}

LRESULT CHEventCriteriaGUIEx::onHideControl(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	if(!wParam || wParam==GR_CH_EVENT_CRITERIA )
	{
		m_gui.setVisible(GR_CH_EVENT_CRITERIA,false);
		m_gui.redraw(GR_CH_EVENT_CRITERIA);		
	}

	if (!wParam || wParam==LB_CH_EVENT_CRITERIA)
	{
		m_gui.setVisible(LB_CH_EVENT_CRITERIA,false);
		m_gui.redraw(LB_CH_EVENT_CRITERIA);		
	}

	return 1;	
	UNREFERENCED_PARAMETER(lParam);
}

LRESULT CHEventCriteriaGUIEx::onShowControl(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	if(!wParam || wParam==GR_CH_EVENT_CRITERIA )
	{
		m_gui.setVisible(GR_CH_EVENT_CRITERIA,true);
		m_gui.setFocus(GR_CH_EVENT_CRITERIA);
		m_gui.redraw(GR_CH_EVENT_CRITERIA);		
	}
	
	if (!wParam || wParam==LB_CH_EVENT_CRITERIA)
	{
		m_gui.setVisible(LB_CH_EVENT_CRITERIA,true);
		m_gui.redraw(LB_CH_EVENT_CRITERIA);		
	}

	return 0;
	UNREFERENCED_PARAMETER(lParam);
}

LRESULT CHEventCriteriaGUIEx::onEventSelected(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	m_pEvent = (CHEvent*)lParam;
	onFillControl();
	return 0;
	UNREFERENCED_PARAMETER(wParam);
}

LRESULT CHEventCriteriaGUIEx::onCommsPackTrn(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	return 0;
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);
}

LRESULT CHEventCriteriaGUIEx::onCommsData(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	return 0;
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);
}		

short CHEventCriteriaGUIEx:: getOrderCriteria(short typeCrit)
{
	if (!m_pEvent)
		return 0;

	return short(m_pEvent->getRankPosition(CHEvent::TypeRank(typeCrit)));
}

MSLString CHEventCriteriaGUIEx::getTypeCriteria(short typeCrit)
{
	switch(typeCrit)
	{
		case CHEvent::eQualitative:
			return "Qualitative";
		case CHEvent::ePoints:
			return "Points";
		case CHEvent::eMatchPoints:
			return "Match Points";
		case CHEvent::eDirectEncounter:
			return "Direct Encounter";
		case CHEvent::eKoyaTieBreak:
			return "Koya Tie Break";
		case CHEvent::eSolkoff:
			return "Buchholz";
		case CHEvent::eSonneBerger:
			return "Sonneberger";
		case CHEvent::eSolkoffCutLowest:
			return "Buchholz Cut Lowest";
		case CHEvent::eSolkoffCutLowestAndHighest:
			return "Buchholz Cut Lowest & Highest";
		case CHEvent::eProgressiveScore:
			return "Progressive score";
		case CHEvent::eRating:
			return "Rating";
		case CHEvent::eTeamMatchesWon:
			return "Team matches won";
		case CHEvent::eMatchesWon:
			return "Matches won";
		case CHEvent::eMatchesDrawm:
			return "Matches drawn";
		case CHEvent::eTeamPointsWon:
			return "Team points won";
		case CHEvent::eAvgOppRating:
			return "Avg. Opp Rating";
	}
	return "";
}