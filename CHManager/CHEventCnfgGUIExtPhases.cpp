/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHEventCnfgGUIExtPhases.cpp
*	Description	:
*
*	Author		:Chess Team
*	Date created:15-12-2005
* 	Project		:CH Manager
*	
***************************************************************************************/

#include "stdafx.h"
#include "CHmanager.h"
#include "CHEventCnfgGUIExtPhases.h"
#include "CHDefines.h"
#include <Sports\CH\Data\CHPhase.h>
#include <Sports\CH\Data\CHPhaseBase.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static
int fnOrderPhases(const void *lParam1, const void *lParam2, LPARAM null)
{  	
	CHPhase *p1= (CHPhase *) lParam1;
	CHPhase *p2= (CHPhase *) lParam2;
	
	int order = p1->getOrder() -  p2->getOrder();
	if (!order)
		order = strcmp(p2->getKey(), p1->getKey());
	return order;	

	UNREFERENCED_PARAMETER(null);
}

/////////////////////////////////////////////////////////////////////////////
// Constructor
/////////////////////////////////////////////////////////////////////////////
CHEventCnfgGUIExtPhases::CHEventCnfgGUIExtPhases(CWnd * pParent,CGraphicWnd * _w, int x1,int y1,int x2,int y2,CHEvent *pEvent)
:CWnd()
,w(_w)
,m_pParent(pParent)
,m_pEvent(pEvent)
,m_pPhase(0)
{
	Create(NULL,NULL,WS_VISIBLE,CRect(0,0,1,1),pParent,0);
	init(x1,y1,x2,y2);
}

CHEventCnfgGUIExtPhases::~CHEventCnfgGUIExtPhases()
{
	w->destroyControl(LBL_PHASE);
	w->destroyControl(LBL_LINE1);
	w->destroyControl(LSTPHASES);
	
}

CHMemoryDataBase * CHEventCnfgGUIExtPhases::mem()
{ 
	return (CHMemoryDataBase *) ((CCHManagerApp*)AfxGetApp())->memG(); 
}

BEGIN_MESSAGE_MAP(CHEventCnfgGUIExtPhases, CWnd)
	//{{AFX_MSG_MAP(CHEventCnfgGUIExtPhases)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	ON_MESSAGE(UM_SELECT_EVENT,onSelectEvent)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CHEventCnfgGUIExtPhases::init(int x1,int y1,int x2,int y2)
{
	w->addBackgroundColor( BUTTBCK, RGB(239,239,239) ); // Buttons
	w->createLabel  (LBL_PHASE,CRect(x1,y1+15, x2,y1+25),"Phase/s",BORDER_NONE,JUST_LEFT,IDBCK,IDCOL,IDFNT_BOLD);
	w->createLabel  (LBL_LINE1,CRect(x1,y1+27,x1+540,y1+30),"",BORDER_NONE,JUST_LEFT,IDBCK_BOX);
	w->createGrid   (LSTPHASES,CRect(x1,y1+30,x1+540,y2+140),BORDER_DOWN,20,IDBCK_GRID,IDCOL,IDFNT);
	w->gridLineColor(LSTPHASES,GET_COLOR_DEFAULT_LINE,GET_COLOR_DEFAULT_LINE);
	w->addGridColumn(LSTPHASES,"Order",				JUST_CENTER ,30 );
	w->addGridColumn(LSTPHASES,"Phase Description",	JUST_LEFT	,110);
	w->addGridColumn(LSTPHASES,"Status",			JUST_CENTER ,70);
	w->addGridColumn(LSTPHASES,"Type Phase",		JUST_CENTER ,80);
	
	
	w->createGridCombo(LSTCBO_TYPE_PHASE,100,BORDER_DOWN,22,IDBCK,IDCOL,IDFNT);
	fillComboTypePhases();
	
}

LRESULT CHEventCnfgGUIExtPhases::onSelectEvent(WPARAM wParam, LPARAM lParam)	//UM_SELECT_EVENT
{
	m_pEvent = (CHEvent *) lParam;
	if (!m_pEvent)
		return 0;
	
	fillGridPhases();
	
	return 0;		
	UNREFERENCED_PARAMETER(wParam);
}

void CHEventCnfgGUIExtPhases::fillGridPhases()
{
	w->gridDeleteAllItems(LSTPHASES);
	GSortedVector vPhases = m_pEvent->getPhasesVector();
	CHPhase *pPhase =0;
	for(size_t i=0; i < vPhases.entries() ;i++)
	{
		pPhase = (CHPhase *)vPhases[i]->getElement();
		if (pPhase)
			w->addGridLine(LSTPHASES,LPARAM(pPhase),pPhase->getLDescription());
	}
	w->gridSort(LSTPHASES,fnOrderPhases);
}

BOOL CHEventCnfgGUIExtPhases::onPaintGrid(UINT idGrid,GridItem * gi)
{
	switch(idGrid)
	{
		case LSTPHASES:
			paintListPhases(gi);
		break;
				
	}
	return TRUE;
}

void CHEventCnfgGUIExtPhases::paintListPhases(GridItem *gi)
{
	char tmp[50]={0};
	//COLORREF selColor= RGB(58,110,165);
	//w->paintGridSolid(gi->sel ?  RGB(100,162,230) : RGB(255,255,255));
	//w->paintGridSolid(gi->sel ?  selColor : RGB(255,255,255));
	
	
	CHPhase *pPhase = (CHPhase *) gi->lParam;
	if (!pPhase) return; 
	switch (gi->x)
	{
		case 0://  order
			{
				sprintf(tmp,"%d",pPhase->getOrder());
				w->paintGridText(gi->rc.Width()/2,0,tmp,JUST_CENTER);		
				break;
			}
		case 1: // description
			{
				w->paintGridText(5,0,pPhase->getLDescription(),JUST_LEFT);		
				break;
			}
		case 2: // status
			{
				GStatus *pStatus = GMemoryDataBase::findStatus(pPhase->getStatus());
				if (pStatus)
					w->paintGridText(5,0,pStatus->getLDescription(),JUST_LEFT);		
				else
					w->paintGridText(gi->rc.Width()/2,0,"-",JUST_CENTER);		
				break;
			}
		case 3: // Type Phase
			w->paintGridText(gi->rc.Width()/2,1,getTypePhase(pPhase,0),JUST_CENTER);
			break;
		
		default:
				break;
	}
}


void CHEventCnfgGUIExtPhases::onClick(UINT idGrid,int x,int y,LPARAM lParam)
{
	UNREFERENCED_PARAMETER(idGrid);
	UNREFERENCED_PARAMETER(x);
	UNREFERENCED_PARAMETER(y);
	UNREFERENCED_PARAMETER(lParam);
}

void CHEventCnfgGUIExtPhases::selectPhase()
{
	
}

void CHEventCnfgGUIExtPhases::onLButtonDown(UINT idGrid,int x,int y,LPARAM lParam)
{
	switch(idGrid)
	{
		case LSTPHASES:
		{
			m_pPhase = (CHPhase *) lParam;
			selectPhase();
			
			break;
		}
	
	}
	
	UNREFERENCED_PARAMETER(x);
	UNREFERENCED_PARAMETER(y);
}

void CHEventCnfgGUIExtPhases::onDblClick(UINT idGrid,int x,int y,LPARAM lParam)
{
	switch(idGrid)
	{
		case LSTPHASES:
		{
			CHPhase *pPhase = (CHPhase *) lParam;
			
			switch (x)
			{
				case 0: // Order
					changeOrderPhase(idGrid,x,y,pPhase);
					break;
				case 3: // Type Phase
				{
					if(pPhase->getStatus()>=CHMemoryDataBase::eSchedulled)
						showComboTypePhase(x,y,pPhase);
					break;
				}
								
			}
			w->redraw(idGrid);
			break;
		}
		default:
			break;
	}

	
}

void CHEventCnfgGUIExtPhases::changeOrderPhase(UINT idGrid,int x,int y,CHPhase *pPhase)
{
	if (pPhase->getStatus() <= CHMemoryDataBase::eStartList)
	{
		char tmp[10]={0};
		RWCString sOldOrder = itoa(pPhase->getOrder(),tmp,10);
		RWCString sNewOrder=w->editGridCell(idGrid,x,y,sOldOrder,"##");
		if (sOldOrder!= sNewOrder)
		{
			int sIntNewOrder = atoi(sNewOrder);
			if (sIntNewOrder < 1)
				::msg("Warning!!","The order of phase must be more than 1",0,MSG_OK);
			else
			{
				pPhase->setOrder(short(sIntNewOrder));
				savePhase(pPhase);
				//Ponemos el codigo 
				
			}
		}
	}
	w->gridSort(LSTPHASES,fnOrderPhases);
	
}

void CHEventCnfgGUIExtPhases::savePhase(CHPhase *pPhase)
{
	APP::out(TRN_CHANGE_PHASE_ORDER);
	APP::out(*pPhase,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
	APP::out();		
}
RWCString CHEventCnfgGUIExtPhases::getTypePhase(CHPhase *pPhase,short typePhase)
{
	
	short type=0;
	if(pPhase)
		 type=pPhase->getTypePhase();
	else type=typePhase;

	switch(type)
	{
		case CHPhaseBase::eElim:
			return "Eliminatory";
			break;
		case CHPhaseBase::ePool:
			return "Pool";
			break;
		case CHPhaseBase::eSwiss:
			return "Swiss-System";
			break;
		case CHPhaseBase::eRepechage:
			return "Repechage";
			break;
		
		default:
			return "Unknown";
			break;
	}
	return NULLRWSTRING;
}
void CHEventCnfgGUIExtPhases::showComboTypePhase(int x,int y,CHPhase *pPhase)
{
	w->selectItem(LSTCBO_TYPE_PHASE,(LPARAM)(pPhase->getTypePhase()+1));
	
	short typePhase=0;
	typePhase=short(w->showGridCombo(LSTPHASES,LSTCBO_TYPE_PHASE,x,y));


	if(typePhase && (typePhase-1)!=pPhase->getTypePhase())
	{
		pPhase->setTypePhase(short(typePhase-1));
		savePhase(pPhase);
		
	}
}

void CHEventCnfgGUIExtPhases::fillComboTypePhases()
{
	w->delAllItems(LSTCBO_TYPE_PHASE);

	for (short i=1;i<=CHPhaseBase::eRepechage;i++)
	{
		w->addItem(LSTCBO_TYPE_PHASE,i,getTypePhase(0,i),0,LPARAM(i+1));
	}
}
