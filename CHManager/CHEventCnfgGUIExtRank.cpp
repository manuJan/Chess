/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHEventCnfgGUIExtRank.cpp
*	Description	:
*
*	Author		:Chess Team
*	Date created:15-12-2005
* 	Project		:CH Manager
*	
***************************************************************************************/
#include "stdafx.h"
#include "CHmanager.h"
#include "CHEventCnfgGUIExtRank.h"
#include "CHDefines.h"
#include <REPORTS/V/orderview.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////
//Class CHRankOrder para el grid
//////////////////////////////////////////////////////
CHRankOrder::CHRankOrder(short pos,short type)
	:order(pos)
	,rankType(type)
{
	setKey();
}
CHRankOrder::~CHRankOrder()
{
}
void CHRankOrder::setKey()
{
	char tmp[3];
	sprintf(tmp,"%.2d",rankType);
	key=tmp;
}
CPack& CHRankOrder::pack(CPack& aPack)
{
	UNREFERENCED_PARAMETER(aPack);
	return aPack;
}
CPack& CHRankOrder::unpack(CPack& aPack)
{
	UNREFERENCED_PARAMETER(aPack);
	return aPack;
}

RWBoolean CHRankOrder::uSQL(RWDBConnection& pConnect,RWBoolean remove/*=false*/)
{
	UNREFERENCED_PARAMETER(pConnect);
	UNREFERENCED_PARAMETER(remove);
	return false;
}
//////////////////////////////////////////////////////


//////////////////////////////////////////////////////
// CHEventCnfgGUIExtRank
//////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CHEventCnfgGUIExtRank, CWnd)
	//{{AFX_MSG_MAP(CHEventCnfgGUIExtRank)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	ON_MESSAGE(UM_SELECT_EVENT,onSelectEvent)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHEventCnfgGUIExtRank

static
int fnRankOrder(const void *lParam1, const void *lParam2, LPARAM null)
{
	UNREFERENCED_PARAMETER(null);

	CHRankOrder *p1= (CHRankOrder *) lParam1;
	CHRankOrder *p2= (CHRankOrder *) lParam2;

	if(!p1->order && p2->order)
		return 1;

	if(p1->order && !p2->order)
		return -1;
		
	int ord = p1->order -  p2->order;
	if(ord)
		return ord;
	
	return p1->rankType - p2->rankType;
}

CHEventCnfgGUIExtRank::CHEventCnfgGUIExtRank(CWnd * pParent,CGraphicWnd * _w, int x1,int y1,int x2,int y2,CHEvent *pEvent)
	:CWnd()
	,w(_w)
	,m_pParent(pParent)
	,m_pEvent(pEvent)
{
	Create(NULL,NULL,WS_VISIBLE,CRect(0,0,1,1),pParent,0);
	init(x1,y1,x2,y2);
}

CHEventCnfgGUIExtRank::~CHEventCnfgGUIExtRank()
{
	colRanks.clearAndDestroy();
}

CCHManagerApp * CHEventCnfgGUIExtRank::getApp() 
{
	return ((CCHManagerApp*)AfxGetApp());
}

CHMemoryDataBase * CHEventCnfgGUIExtRank::mem()
{ 
	return (CHMemoryDataBase *) getApp()->memG(); 
}

/////////////////////////////////////////////////////////////////////////////
// CHEventCnfgGUIExtRank message handlers
void CHEventCnfgGUIExtRank::init(int x1,int y1,int x2,int y2)
{
	w->createLabel  (LBL_RANK     ,CRect(x1,y1+15, x2,y1+25),"Rank Sorting",BORDER_NONE,JUST_LEFT,IDBCK,IDCOL,IDFNT_BOLD);
	w->createLabel  (LBL_RANK_LINE,CRect(x1,y1+27,x2,y1+30),"",BORDER_NONE,JUST_LEFT,IDBCK_BOX);

	w->createGrid   (LSTRANK     ,CRect(x1,y1+30,x2,y2+140),BORDER_DOWN,16,IDBCK_GRID,IDCOL,IDFNT);
	w->gridLineColor(LSTRANK	 ,GET_COLOR_DEFAULT_LINE,GET_COLOR_DEFAULT_LINE);
	w->addGridColumn(LSTRANK,"Order",	JUST_CENTER ,50 );
	w->addGridColumn(LSTRANK,"Ranking",	JUST_LEFT   ,250);

	w->createCombo (CMB_EVENT_CPY ,CRect(x1, y2+140,x1+180,y2+250),BORDER_SINGLE,17,IDBCK,IDCOL,IDFNT);
	w->createButton (BUT_COPY,CRect(x1+185,y2+140,x1+265,y2+160),"Copy to Event",IDBCK_BUT,IDCOL,IDFNT);
	fillComboEvents();
}


LRESULT CHEventCnfgGUIExtRank::onSelectEvent(WPARAM wParam, LPARAM lParam)	//UM_SELECT_EVENT
{
	UNREFERENCED_PARAMETER(wParam);

	m_pEvent = (CHEvent *) lParam;
		
	fillGridRank();
	fillComboEvents();
	
	return 0;		
}

BOOL CHEventCnfgGUIExtRank::onPaintGrid(UINT idGrid,GridItem * gi)
{
	switch(idGrid)
	{
		case LSTRANK:
			paintListRank(gi);
		break;
				
	}
	return TRUE;
}

void CHEventCnfgGUIExtRank::onDblClick(UINT idGrid,int x,int y,LPARAM lParam)
{
	switch(idGrid)
	{
		case LSTRANK:
		{
			CHRankOrder *pRankOrder = (CHRankOrder *) lParam;
			if(x==0)
			{
				editRankOrder(idGrid,x,y,pRankOrder);
				w->redraw(idGrid);
			}
		break;
		}
	}
}

void CHEventCnfgGUIExtRank::onClick(UINT idGrid,int x,int y,LPARAM lParam)
{
	UNREFERENCED_PARAMETER(x);
	UNREFERENCED_PARAMETER(y);
	UNREFERENCED_PARAMETER(lParam);
	
	switch (idGrid)
	{
		case BUT_COPY:
			copyOrderRank();
			break;
	}
}

void CHEventCnfgGUIExtRank::copyOrderRank()
{
	CHEvent * pTargetEvent=(CHEvent*)w->getSelectedData(CMB_EVENT_CPY);

	if(pTargetEvent)
	{
		pTargetEvent->setReqRankOrder(m_pEvent->getReqRankOrder());
		getApp()->queueOut(pTargetEvent);
	}
	else //Copiar a todos los eventos
	{
		GSortedVector vEvents(CHMemoryDataBase::getColEvents(),orderEvents);
		
		CHEvent * pEvent=0;
		for(size_t i=0 ; i<vEvents.entries() ;i++)
		{
			pEvent=(CHEvent*)vEvents[i]->getElement();
	
			if(pEvent!=m_pEvent)
			{
				pEvent->setReqRankOrder(m_pEvent->getReqRankOrder()) ;
				getApp()->queueOut(pEvent);
			}
		}
	}

	//To DB & NET
	getApp()->out(TRN_CH_EVENT_CHANGE);
}

void CHEventCnfgGUIExtRank::editRankOrder(UINT idGrid,int x,int y,CHRankOrder * pRankOrder)
{
	if(!pRankOrder)
		return;

	RWCString oldOrder=TOSTRING(pRankOrder->order);

	RWCString newOrder = w->editGridCell(idGrid,x,y,oldOrder,"##",0,true,JUST_CENTER);

	if (newOrder != oldOrder)
	{
		pRankOrder->order=short(atoi(newOrder));
		w->gridSort(LSTRANK,fnRankOrder);

		//establecer el orden de los rankings en el Evento
		setOrderRankInEvent();
	}
}

void CHEventCnfgGUIExtRank::setOrderRankInEvent()
{
	if (!m_pEvent)
		return;

	RWCString orderRankingEvent;
	int nLines=w->getGridNItems(LSTRANK);

	CHRankOrder * pRankOrder =0;
	for(size_t i=0 ; i<size_t(nLines) ; i++)
	{
		pRankOrder = (CHRankOrder *)w->getGridLParam(LSTRANK,i);
		if(pRankOrder->order)
		{
			char tmp[3];
			sprintf(tmp,"%.2d",pRankOrder->rankType);

			orderRankingEvent+=tmp;
		}
	}

	m_pEvent->setReqRankOrder(orderRankingEvent);
	
	//To DB & NET
	getApp()->queueOut(m_pEvent);
	getApp()->out(TRN_CH_EVENT_CHANGE);
}

void CHEventCnfgGUIExtRank::fillComboEvents()
{
	w->delAllItems(CMB_EVENT_CPY);
	w->redraw(CMB_EVENT_CPY);

	if(!m_pEvent)
		return;

	if (!m_pEvent->isEnable())
		return;

	w->addItem(CMB_EVENT_CPY,-1," All",0,LPARAM(0));

	GSortedVector vEvents(CHMemoryDataBase::getColEvents(),orderEvents);

	CHEvent * pEvent=0;
	for(size_t i=0 ; i<vEvents.entries() ;i++)
	{
		pEvent=(CHEvent*)vEvents[i]->getElement();
		if(pEvent!=m_pEvent)
			w->addItem(CMB_EVENT_CPY,-1,_T(" ") + pEvent->getLDescription(),0,LPARAM(pEvent));
	}
}


void CHEventCnfgGUIExtRank::fillGridRank()
{
	w->gridDeleteAllItems(LSTRANK);	
	colRanks.clearAndDestroy();
	
	if(!m_pEvent)
		return;

	w->enable(CMB_EVENT_CPY,m_pEvent->isEnable());
	w->enable(BUT_COPY,m_pEvent->isEnable());

	if (!m_pEvent->isEnable())
		return;

	short nRanks=m_pEvent->getNumRankOrder();
	for(size_t i=0 ; i<size_t(nRanks) ; i++)
	{
		short rankType=short(m_pEvent->getRankOrder(short(i)));
		if(rankType!=CHEvent::eEmpty)
			colRanks.insert(new CHRankOrder(short(i+1),rankType));
	}

	for(i=CHEvent::eQualitative ;i <=CHEvent::eTeamPointsWon ; i++)
	{
		CHRankOrder aRankOrder(0,short(i));

		if(!colRanks.find(&aRankOrder))
			colRanks.insert(new CHRankOrder(0,short(i)));
	}

	RWSetIterator iter(colRanks);

	CHRankOrder * pRankOrder=0;
	while((pRankOrder=(CHRankOrder *)iter())!=0)
	{
		w->addGridLine(LSTRANK,LPARAM(pRankOrder),"");
	}

	w->gridSort(LSTRANK,fnRankOrder);
}

void CHEventCnfgGUIExtRank::paintListRank(GridItem *gi)
{
//	char tmp[50]={0};
//	COLORREF selColor= RGB(58,110,165);
	//w->paintGridSolid(gi->sel ?  RGB(100,162,230) : RGB(255,255,255));
	//w->paintGridSolid(gi->sel ?  selColor : RGB(255,255,255));
	
	CHRankOrder * pRankOrder = (CHRankOrder *) gi->lParam;

	if (!pRankOrder ) return; 
	switch (gi->x)
	{
	case 0://  order
		if(pRankOrder->order)
			w->paintGridVal(gi->rc.Width()/2,0,pRankOrder->order,JUST_CENTER);		
	break;
	
	case 1: // Type Rank
		w->paintGridText(3,0,getRankDescription(pRankOrder->rankType),JUST_LEFT);
	break;
	}
}

RWCString CHEventCnfgGUIExtRank::getRankDescription(short rankType)
{
	
	switch(rankType)
	{
		case CHEvent::eEmpty:
			return "---";
		case CHEvent::eQualitative:
			return "Qualitative";
		case CHEvent::ePoints:
			return "Points";
		case CHEvent::eSolkoff:
			return "Solkoff";
		case CHEvent::eMedianSolkoff:
			return "Median Solkoff";
		case CHEvent::eSonneBerger:
			return "SonneBerger";
		case CHEvent::eProgressiveScore:
			return "Progressive Score";
		case CHEvent::eRating:
			return "Start Rating";
		case CHEvent::eTeamMatchesWon:
			return "Matches Won (Members)";
		case CHEvent::eMatchesWon:
			return "Matches Won";
		case CHEvent::eMatchesDrawm:
			return "Matches Drawn";
		case CHEvent::eTeamPointsWon:
			return "Points for Won Matches (Team)";
						
	}

	return "";
}