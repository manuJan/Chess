/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:	CHUmpireGUIEx.cpp
*	Description	:   Asignacion de Chair Umpire al Match
*
*	Author		:	Fernando Hicar
*	Date created:   1-Abril-2009
* 	Project		:	Tennis Manager
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "StdAfx.h"
#include "CHUmpireGUIEx.h"
#include "CHManagerApp.h"
#include "CHManagerDefs.h"
#include <OVR/CORE/TH/GTHMsgDefines.h>
#include "..\CHMngtModel\CHMatch.h"
#include "..\CHMngtModel\CHRegister.h"

#define UMPIRE 2 //a pinrel

/// Order Functions //////////////////////////////////////
static 
int orderOfficialByName(const MSLItem** a, const MSLItem** b)
{
	GOfficial * pA = (GOfficial *)(*a);
	GOfficial * pB = (GOfficial *)(*b);

	int order=_wcsicoll(pA->getPrnLName(),pB->getPrnLName());
	if(order)
		return order;

	return strcmp(pA->getKey(),pB->getKey());
}

static 
int orderOfficialByFunction(const MSLItem** a, const MSLItem** b)
{
	GOfficial * pA = (GOfficial*)(*a);
	GOfficial * pB = (GOfficial *)(*b);

	int order=strcmp(pA->getFunctionKey(),pB->getFunctionKey());
	if(order)
		return order;

	return orderOfficialByName(a,b);
}

static
int orderOfficialByNoc(const MSLItem** a, const MSLItem** b)
{
	GOfficial * pA = (GOfficial *)(*a);
	GOfficial * pB = (GOfficial *)(*b);

	int order=strcmp(pA->getGroup(),pB->getGroup());
	if(order)
		return order;

	return orderOfficialByName(a,b);
}

/// Order Functions //////////////////////////////////////


CHUmpireGUIEx::CHUmpireGUIEx(long id,CHMatch * pMatch)
:GTHManagerGUI(id)
,m_pMatch(pMatch)
,m_orderColOfficial(C_FUNCTION_CHAIRUMP)
{
}

CHUmpireGUIEx::~CHUmpireGUIEx()
{
}

CHMemoryDataBase * CHUmpireGUIEx::getMem() const
{
	return (CHMemoryDataBase*)GMemoryDataBase::getMem();
}

GOfficial * CHUmpireGUIEx::getOfficial()
{
	return (GOfficial*)((MSLGUI &)m_gui).grid_selGetLParam(GR_CHAIR_UMPIRE);
}

MSLWString CHUmpireGUIEx::getNameRegister(GRegister * pRegister) const
{
	return pRegister ? pRegister->getPrnLName():_T("");
}

MSLWString CHUmpireGUIEx::getNameOfficial(GOfficial * pOfficial) const
{
	return pOfficial ? getNameRegister(pOfficial->getRegister()):_T("None");
}

MSLWString CHUmpireGUIEx::getNameFunction(GFunction * pFunction) const
{
	return pFunction ? pFunction->getLDescription():_T("None");
}

bool CHUmpireGUIEx::onInit()
{	
	onCreateControl	();
	onFillControl	();
	
	return true;
}

bool CHUmpireGUIEx::onGridPaint(long id,gui_grid_cell* cell)
{
	if(id==GR_CHAIR_UMPIRE)
		return paintGridChairUmpire(cell);
	
	return false;
}

void CHUmpireGUIEx::onClick(long id,LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	if(id==CK_ALL_OFFICIALS)
		fillGridChairUmpire();

	GTHManagerGUI::onClick(id,lParam);
}

void CHUmpireGUIEx::onLButDblClick(long id,long x,long y)
{
	 if(id==GR_CHAIR_UMPIRE)
		dblClickGridChairUmpire(x,y);
}	

void CHUmpireGUIEx::onLButDown(long id,long x,long y)
{
	if(id==GR_CHAIR_UMPIRE)
		clickGridChairUmpire(x,y);
}

LRESULT CHUmpireGUIEx::onCreateControl (WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	UNREFERENCED_PARAMETER(lParam);

	if(!wParam || wParam==GR_CHAIR_UMPIRE)
		createGridChairUmpire();

	return 1;
}

LRESULT CHUmpireGUIEx::onFillControl(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	UNREFERENCED_PARAMETER(lParam);

	if(!wParam || wParam==GR_CHAIR_UMPIRE)
		fillGridChairUmpire();
		
	return 0;
}

LRESULT CHUmpireGUIEx::onRedrawControl(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	UNREFERENCED_PARAMETER(lParam);

	if(!wParam || wParam==GR_CHAIR_UMPIRE)
		redrawGridChairUmpire();
		
	return 0;
}

//LRESULT CHUmpireGUIEx::onCommsPackTransaction(WPARAM wParam,LPARAM lParam)
//{
//}

//LRESULT CHUmpireGUIEx::onComms(WPARAM wParam,LPARAM lParam)
//{
//}

/***** Grid Officials ****/
mslToolsFcCompare CHUmpireGUIEx::getOrderOfficial() const
{
	switch(m_orderColOfficial)
	{
		case C_NOC_CHAIRUMP:
			return orderOfficialByNoc;
		case C_NAME_CHAIRUMP:
			return orderOfficialByName;
		case C_FUNCTION_CHAIRUMP:
			return orderOfficialByFunction;
	}
			
	return orderOfficialByFunction;
}

void CHUmpireGUIEx::createGridChairUmpire()
{
	RECT aRc=getRect();

	m_gui.doCheck(CK_ALL_OFFICIALS,RC(aRc.right-120,aRc.top,aRc.right-20,aRc.top+20),L"Show All Officials",false);

	m_gui.doGrid(GR_CHAIR_UMPIRE,RC(aRc.left,aRc.top+20,aRc.right-20,aRc.bottom),GUI_ID_STY_BOR,GUI_ID_STY_SEL,20);
	m_gui.grid_addColumn(GR_CHAIR_UMPIRE,"NOC"	    ,GUI_JUST_CENTER, 40 ,C_NOC_CHAIRUMP);
	m_gui.grid_addColumn(GR_CHAIR_UMPIRE,"Name"	    ,GUI_JUST_LEFT  ,230 ,C_NAME_CHAIRUMP);
	m_gui.grid_addColumn(GR_CHAIR_UMPIRE,"Function",GUI_JUST_LEFT   ,113 ,C_FUNCTION_CHAIRUMP);
	
	m_gui.grid_setLineColor(GR_CHAIR_UMPIRE,GUI_RGB_OFF,GUI_RGB_OFF); 
}

void CHUmpireGUIEx::fillGridChairUmpire()
{
	bool allOfficials=m_gui.getCheck(CK_ALL_OFFICIALS);
	GOfficial * pSelOfficial=getOfficial();

	m_gui.grid_reset(GR_CHAIR_UMPIRE);

	MSLSortedVector vOfficial(GMemoryDataBase::getCol(__GOFFICIAL),getOrderOfficial());

	m_gui.grid_add(GR_CHAIR_UMPIRE,(LPARAM)0,L"");

	GOfficial * pOfficial=0;
	for(long i=0 ; i<vOfficial.entries() ; i++)
	{
		pOfficial=(GOfficial *)vOfficial[i];
		if(allOfficials || 
		   (!allOfficials && pOfficial->getFunctionCode()==UMPIRE))
			m_gui.grid_add(GR_CHAIR_UMPIRE,(LPARAM)pOfficial,getNameOfficial(pOfficial));
	}

	if(pSelOfficial)
		m_gui.grid_selLParam(GR_CHAIR_UMPIRE,(LPARAM)pSelOfficial);
}

bool CHUmpireGUIEx::paintGridChairUmpire(gui_grid_cell* cell)
{
	if(cell->y==-1)
		return false;

	GOfficial * pOfficial=(GOfficial*)cell->lParamLine;

	GTHMatchJudge * pMatchJudge=(GTHMatchJudge *)m_pMatch->getMatchJudge(0);
	if(!cell->bSelected && pMatchJudge && pOfficial && 
	    pMatchJudge->getRegister()==pOfficial->getRegister())
			m_gui.paint_solid(RGB(255,255,183));
			
	switch (cell->lParamColumn)
	{
	case C_NOC_CHAIRUMP:
		{
			if(pOfficial)
			{
				RECT aRect(cell->paint.rc);
				int w=aRect.right-aRect.left;

				HBITMAP hBmp=flag_getSize(pOfficial->getGroup(),19,9); 
				if (hBmp)
				{
					m_gui.paint_userBmp(hBmp,w/2-10,1,false);
					::DeleteObject(hBmp);
				}
				m_gui.paint_textAt(MSLWString(pOfficial->getGroup()),w/2-10,9,GUI_ID_FNT_MIN);
			}
		}
		break;
	case C_NAME_CHAIRUMP:
		{
			if(pOfficial)
			{
				GRegister * pRegister=pOfficial->getRegister();
				HBITMAP hBmp=((CHManagerApp*)MSLAPP)->getBmpSex(GUIManagerApp::m_hGUIMyModule,pOfficial->getSex(),pRegister->getType());
				if (hBmp)
				{
					m_gui.paint_userBmp(hBmp,1,2,true);
					::DeleteObject(hBmp);
				}
			}
			m_gui.paint_textAt(getNameOfficial(pOfficial),20,3);
		}
		break;
	case C_FUNCTION_CHAIRUMP:
		m_gui.paint_textAt(getNameFunction(pOfficial?pOfficial->getFunction():0),1,3);
		break;
	}
	return true;
}

void CHUmpireGUIEx::redrawGridChairUmpire()
{
	m_gui.redraw(GR_OFFICIAL);
}

bool CHUmpireGUIEx::handGridChairUmpire(long x,long y)
{
	gui_grid_cell * pCell=m_gui.grid_getCell(GR_CHAIR_UMPIRE,x,y);
	if(!pCell)
		return false;

	int col=pCell->lParamColumn;
	if((col==C_NOC_CHAIRUMP || col==C_NAME_CHAIRUMP || col==C_FUNCTION_CHAIRUMP))
		return true;
	
	return false;
}

void CHUmpireGUIEx::clickGridChairUmpire(long x,long y)
{
	gui_grid_cell * pCell=m_gui.grid_getCell(GR_CHAIR_UMPIRE,x,y);
	if(!pCell)
		return;

	int col=pCell->lParamColumn;

	if(y==-1) //cabecera
	{
		m_orderColOfficial=col;
		fillGridChairUmpire();
		return;
	}
}

void CHUmpireGUIEx::dblClickGridChairUmpire(long x,long y)
{
	UNREFERENCED_PARAMETER(x);
	if(y==-1) //cabecera
		return;

	setMatchJudge(getOfficial());

	dlgClose(0);
}


//////////////////////////////////////
void CHUmpireGUIEx::setMatchJudge(GOfficial * pOfficial)
{
	CHRegister * pRegister    =(CHRegister*)(pOfficial? pOfficial->getRegister():0);
	GTHMatchJudge * pMatchJudge=(GTHMatchJudge *)m_pMatch->getMatchJudge(0);

		 if(!pRegister && pMatchJudge)
		 {
			if(deleteMatchJudge(pMatchJudge))
				APP::out(TRN_REMOVE_MATCHJUDGE);
		 }
	else if(pRegister && !pMatchJudge)
	{
			if(createMatchJudge(pRegister))
				APP::out(TRN_SET_MATCHJUDGE);
	}
	else if(pRegister && pMatchJudge)
	{
		if(pMatchJudge->getRegister()!=pRegister)
		{
			bool rtnDel=deleteMatchJudge(pMatchJudge);
			bool rtnIns=createMatchJudge(pRegister);
			if(rtnDel || rtnIns)
				APP::out(TRN_SET_MATCHJUDGE);
		}
	}

	sendMsg(UM_CHANGE_UMPIRE,0);
}

bool CHUmpireGUIEx::createMatchJudge(CHRegister * pRegister)
{
	if(!pRegister)
		return false;

	GTHMatchJudge aMatchJudge;
	aMatchJudge.setMatch(m_pMatch);
	aMatchJudge.setRegister(pRegister);
	
	GFunction * pFunction = 0;
		
	pFunction=CHMemoryDataBase::findFunction(UMPIRE);
	if( pFunction )
		aMatchJudge.setFunction(pFunction);

	if(!CHMemoryDataBase::find(aMatchJudge))
	{
		GTHMatchJudge * pMatchJudge = (GTHMatchJudge *)getMem()->set(aMatchJudge);

		if(pMatchJudge )
		{
			APP::out(*pMatchJudge);
			return true;
		}
	}
	return false;
}

bool CHUmpireGUIEx::deleteMatchJudge(GTHMatchJudge * pMatchJudge)
{
	if(!pMatchJudge)
		return false;

	GTHMatchJudge * pDelJudge = (GTHMatchJudge *)getMem()->remove(*pMatchJudge);
	if(pDelJudge )
	{
		APP::out(*pDelJudge,false);
		
		return true;
	}
	return false;
}

LRESULT CHUmpireGUIEx::onCommsPackTransaction(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	MSLTransaction * pt=(MSLTransaction*)lParam;

	if(!pt)
		return 0;

	switch(pt->getTrnId())
	{
	case TRN_SET_REGISTER:
		redrawGridChairUmpire();
	case TRN_SET_OFFICIAL:
	case TRN_REMOVE_OFFICIAL:
		fillGridChairUmpire();
		break;
	}
	
	return 1;
}

LRESULT CHUmpireGUIEx::onComms(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	/*if(!lParam)	return 0;

	CommsMng * pCommsMng=(CommsMng *)lParam;
	GData * pData=pCommsMng->pData;
	if(!pData)
		return 0;*/

	return 1;
}