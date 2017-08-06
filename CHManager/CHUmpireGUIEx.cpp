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
#include "CHProgression.h"
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
,m_orderColOfficial(C_FUNCTION_UMP)
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
	return (GOfficial*)((MSLGUI &)m_gui).grid_selGetLParam(GR_UMPIRES);
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
	if(id==GR_UMPIRES)
		return paintGridChairUmpire(cell);
	
	return false;
}

void CHUmpireGUIEx::onClick(long id,LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	if(id==CK_ALL_OFFICIALS)
		fillGridChairUmpire();
	if(id==BT_OK)
	{
		assignOfficialsAllRound();
		dlgClose(0);
	}

	GTHManagerGUI::onClick(id,lParam);
}

void CHUmpireGUIEx::onLButDown(long id,long x,long y)
{
	if(id==GR_UMPIRES)
		clickGridChairUmpire(x,y);
}

LRESULT CHUmpireGUIEx::onCreateControl (WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	UNREFERENCED_PARAMETER(lParam);

	if(!wParam || wParam==GR_UMPIRES)
		createGridChairUmpire();

	return 1;
}

LRESULT CHUmpireGUIEx::onFillControl(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	UNREFERENCED_PARAMETER(lParam);

	if(!wParam || wParam==GR_UMPIRES)
		fillGridChairUmpire();
		
	return 0;
}

LRESULT CHUmpireGUIEx::onRedrawControl(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	UNREFERENCED_PARAMETER(lParam);

	if(!wParam || wParam==GR_UMPIRES)
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
		case C_NOC_UMP:
			return orderOfficialByNoc;
		case C_NAME_UMP:
			return orderOfficialByName;
		case C_FUNCTION_UMP:
			return orderOfficialByFunction;
	}
			
	return orderOfficialByFunction;
}

void CHUmpireGUIEx::createGridChairUmpire()
{
	RECT aRc=getRect();

	m_gui.doCheck(CK_ASSIGN_ALL_ROUND,RC(aRc.left+10,aRc.top,aRc.right-140,aRc.top+20),L"Assign to all round games",false);
	m_gui.doCheck(CK_ALL_OFFICIALS,RC(aRc.right-120,aRc.top,aRc.right-20,aRc.top+20),L"Show All Officials",false);

	m_gui.doGrid(GR_UMPIRES,RC(aRc.left,aRc.top+20,aRc.right-20,aRc.bottom-30),GUI_ID_STY_BOR,GUI_ID_STY_SEL,20);

	m_gui.grid_addColumn(GR_UMPIRES,""		    ,GUI_JUST_CENTER, 20 ,C_SEL_UMP);
	m_gui.grid_addColumn(GR_UMPIRES,"NOC"	    ,GUI_JUST_CENTER, 40 ,C_NOC_UMP);
	m_gui.grid_addColumn(GR_UMPIRES,"Name"	    ,GUI_JUST_LEFT  ,210 ,C_NAME_UMP);
	m_gui.grid_addColumn(GR_UMPIRES,"Function",GUI_JUST_LEFT    ,113 ,C_FUNCTION_UMP);
	
	m_gui.grid_setLineColor(GR_UMPIRES,GUI_RGB_OFF,GUI_RGB_OFF); 

	m_gui.doBut(BT_OK, RC(aRc.left+100,aRc.bottom-25,aRc.right-100,aRc.bottom-5), "OK");
}

void CHUmpireGUIEx::fillGridChairUmpire()
{
	bool allOfficials=m_gui.getCheck(CK_ALL_OFFICIALS);
	GOfficial * pSelOfficial=getOfficial();

	m_gui.grid_reset(GR_UMPIRES);

	MSLSortedVector vOfficial(GMemoryDataBase::getCol(__GOFFICIAL),getOrderOfficial());

	m_gui.grid_add(GR_UMPIRES,(LPARAM)0,L"");

	GOfficial * pOfficial=0;
	for(long i=0 ; i<vOfficial.entries() ; i++)
	{
		pOfficial=(GOfficial *)vOfficial[i];
		if(allOfficials || 
		   (!allOfficials && pOfficial->getFunctionCode()==UMPIRE))
			m_gui.grid_add(GR_UMPIRES,(LPARAM)pOfficial,getNameOfficial(pOfficial));
	}

	if(pSelOfficial)
		m_gui.grid_selLParam(GR_UMPIRES,(LPARAM)pSelOfficial);
}

bool CHUmpireGUIEx::paintGridChairUmpire(gui_grid_cell* cell)
{
	if(cell->y==-1)
		return false;

	GOfficial * pOfficial=(GOfficial*)cell->lParamLine;
	GTHMatchJudge * pMatchJudge=0;
	if (pOfficial)
	{
		pMatchJudge=(GTHMatchJudge *)m_pMatch->findMatchJudge(pOfficial);
		if(!cell->bSelected && pMatchJudge && pOfficial)
			m_gui.paint_solid(RGB(255,255,183));
	}
			
	switch (cell->lParamColumn)
	{
	case C_SEL_UMP:
		{
			m_gui.paint_check(pMatchJudge!=0,true);
			break;			
		}
	case C_NOC_UMP:
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
	case C_NAME_UMP:
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
	case C_FUNCTION_UMP:
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
	gui_grid_cell * pCell=m_gui.grid_getCell(GR_UMPIRES,x,y);
	if(!pCell)
		return false;

	int col=pCell->lParamColumn;
	if((col==C_NOC_UMP || col==C_NAME_UMP || col==C_FUNCTION_UMP))
		return true;
	
	return false;
}

void CHUmpireGUIEx::clickGridChairUmpire(long x,long y)
{
	gui_grid_cell * pCell=m_gui.grid_getCell(GR_UMPIRES,x,y);
	if(!pCell)
		return;

	int col=pCell->lParamColumn;

	if(y==-1) //cabecera
	{
		m_orderColOfficial=col;
		fillGridChairUmpire();
		return;
	}

	if (col==C_SEL_UMP)
	{
		CHProgression aProgression(this);

		GOfficial * pOfficial = (GOfficial*)pCell->lParamLine;
		if (pOfficial)
		{	
			GTHMatchJudge * pMatchJudge = m_pMatch->findMatchJudge(pOfficial);
			if (pMatchJudge)
				aProgression.deleteMatchJudge(pMatchJudge);				
			else
				aProgression.setMatchJudge(m_pMatch,pOfficial);							
		}	
		
		sendMsg(UM_CHANGE_UMPIRE,0);
		
		aProgression.startListScheduleMatch(m_pMatch);

		sendMsg(UM_CHANGE_MATCH,0);
		redrawGridChairUmpire();
	}
}

/*void CHUmpireGUIEx::dblClickGridChairUmpire(long x,long y)
{
	UNREFERENCED_PARAMETER(x);
	if(y==-1) //cabecera
		return;

	setMatchJudge(getOfficial());

	CHProgression aProgression(this);
	aProgression.startListMatch(m_pMatch);

	//dlgClose(0);
}*/


//////////////////////////////////////

bool CHUmpireGUIEx::assignOfficialsAllRound()
{
	if (m_pMatch->getMatchJudges().entries()==0)
		return false;

	bool assign = m_gui.getCheck(CK_ASSIGN_ALL_ROUND);
	
	if (assign && MSLMsgBox( m_gui.getHWndBase() ,"Selected official will be assigned to all round games, continue?", GUI_ICO_WARNING, GUI_MB_YESNO, "assigment")==IDYES)
	{
		CHProgression aProgression(this);
		return aProgression.assignOfficialsToAllRoundGames(m_pMatch);
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