/*************************************************************************************
*	© Copyright MSL Software, S.L., 2001
*
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHJudgesDlg.cpp
*   Description	: 
*
*	Author		: Chess Team
*	Date created: 27-12-2005
* 	Project		:
*
***************************************************************************************/

#include "stdafx.h"
#include "CHmanager.h"
#include "CHJudgesDlg.h"
#include "CHCnfgMatchJudgeDlg.h"
#include <sports/CH/data/CHRegister.h>
#include <sports/CH/data/CHMatchJudge.h>
#include <sports/CH/data/CHMsgDefines.h>
#include <core/TH/GTHMsgDefines.h>
#include <GUI/GS/ResGUISports.h>
#include <GUI/GS/GUISports.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDCOLTEXT  1100
#define IDBACKG	   1101
#define LSTJUDGES  1102
#define FNTDLG	   1103
#define LBL_EXIT   1104
#define IDCOLBLUE  1105
#define IDCOLRED   1106
#define FNTDLG2   1107

int orderJudgeByName(const GVectorElement** a, const GVectorElement** b)
{
	CHJudge *pJudgeA = (CHJudge *)(*a)->getElement();
	CHJudge *pJudgeB = (CHJudge *)(*b)->getElement();
	
	CHRegister *pRegisterA = (CHRegister *)pJudgeA->getRegister();
	CHRegister *pRegisterB = (CHRegister *)pJudgeB->getRegister();

	int rc=wcscmp(pRegisterA->getPrnLName(),pRegisterB->getPrnLName());
	if (rc)
		return rc; 
	else
		return strcmp(pRegisterA->getKey(),pRegisterB->getKey());
}


CHJudgesDlg::CHJudgesDlg(CHMatch *pSelMatch, int function,short code, CWnd* pParent /*=NULL*/)
: CDialog(CHJudgesDlg::IDD, pParent)
,pMatch(pSelMatch)
,pDlgParent(pParent)
,numCode(code)
{
	//{{AFX_DATA_INIT(CHJudgesDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	pFunction = CHMemoryDataBase::findFunction(unsigned char(function));
}

void CHJudgesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHJudgesDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHJudgesDlg, CDialog)
	//{{AFX_MSG_MAP(CHJudgesDlg)
		ON_MESSAGE(UM_DBLCLICK, onDblClick)
		ON_MESSAGE(UM_PAINTGRID,onPaintGrid)
		ON_MESSAGE(UM_CLICK,onClick)
		ON_MESSAGE(TRN_JUDGE_CHANGE_DLG,onChangeJudge)
		ON_MESSAGE(UM_KEYDOWN, OnKeyDown)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CHJudgesDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	w = new CGraphicWnd(this);

	//Recursos de la Dll
	HINSTANCE hInstOld = AfxGetResourceHandle();
	
	AfxSetResourceHandle(getGUIModuleHandle());

	w->destroyBackground (IDBACKG);
	w->addBackgroundColor(IDBACKG,RGB(240,240,250));
	w->setBackground (IDBACKG);	
	
	w->addColorSet(IDCOLTEXT,RGB(0,0,170),COLOR_DEFAULT_OFF ,COLOR_DEFAULT_HITX,COLOR_DEFAULT_HIGH,COLOR_DEFAULT_L3D,COLOR_DEFAULT_N3D,COLOR_DEFAULT_D3D );
	w->addColorSet(IDCOLBLUE,RGB(0,0,170),COLOR_DEFAULT_OFF ,COLOR_DEFAULT_HITX,COLOR_DEFAULT_HIGH,COLOR_DEFAULT_L3D,COLOR_DEFAULT_N3D,COLOR_DEFAULT_D3D );
	w->addColorSet(IDCOLRED,RGB(200,0,0),COLOR_DEFAULT_OFF,COLOR_DEFAULT_HITX,COLOR_DEFAULT_HIGH,COLOR_DEFAULT_L3D,COLOR_DEFAULT_N3D,COLOR_DEFAULT_D3D);

	w->addFont(FNTDLG, 6,15,1,0,0,0,_T("Arial"));
	w->addFont(FNTDLG2, 6,15,1,0,1,0,_T("Arial"));

	w->createGrid(LSTJUDGES,CRect(10,10,300,400),BORDER_DOWN,20,IDBACKG,IDCOLTEXT,FNTDLG,FALSE,0);
	w->gridLineColor(LSTJUDGES,RGB(207,207,207),RGB(207,207,207));
	w->addGridColumn(LSTJUDGES,"Judges",JUST_CENTER,290);

	w->createLabelEx(LBL_EXIT,CRect(120,410,180,430),"Cancel",BORDER_NONE,JUST_CENTER,IDBACKG,IDCOLBLUE,FNTDLG2,IDBACKG,IDCOLRED);

	w->addBitmapT(BMPMAN  ,IDB_GNRAL_MAN);
	w->addBitmapT(BMPWOMAN,IDB_GNRAL_WOMAN);
	
	AfxSetResourceHandle(hInstOld);
	
	fillJudges();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CHJudgesDlg::fillJudges()
{
	GSortedVector vAllJudges=GSortedVector(CHMemoryDataBase::getColJudges(),orderJudgeByName);
	GSortedVector vJudges;

	CHJudge *pJudge=0;
	w->gridDeleteAllItems(LSTJUDGES);
	for (size_t i=0;i<vAllJudges.entries();i++)
	{
		pJudge=(CHJudge *)vAllJudges[i]->getElement();
		CHRegister *pRegister = (CHRegister *)pJudge->getRegister();
		if (!vJudges.find(pRegister))
		{
			vJudges.insert(pRegister);
			CHMatchJudge aMatchJudge(pMatch,pJudge);
			aMatchJudge.setFunction(pFunction);
			aMatchJudge.setMatch(pMatch);
			if (!CHMemoryDataBase::findMatchJudge(aMatchJudge))
				w->addGridLine(LSTJUDGES,LPARAM(pJudge),"");
		}
	}
	vJudges.clearAndDestroy();
	vAllJudges.clearAndDestroy();
}

BOOL CHJudgesDlg::onPaintGrid (UINT idGrid,GridItem *gi)
{
	switch(idGrid)
	{
		case LSTJUDGES:
			 paintJudges(gi);
			 break;
		default:
			break;
	}
	return TRUE;
}

void CHJudgesDlg::paintJudges(GridItem *gi)
{
	if (!gi)
		return;
	
	gi->cdc->FillSolidRect(gi->rc,(gi->sel)?RGB(170,170,170):0xFFFFFF);

	CHJudge *pJudge = (CHJudge *) gi->lParam;
	if (!pJudge)
		return;

	switch(gi->x)
	{
		case 0:
		{
			CHRegister *pRegister = (CHRegister *) pJudge->getRegister();
			CDC cdc;
			CBitmap aBitmap;
			getFlag(pRegister->getGroup(),ICO,&aBitmap);	
			cdc.CreateCompatibleDC(NULL);
			cdc.SelectObject(&aBitmap);
			gi->cdc->BitBlt(gi->rc.left+4,gi->rc.top+1,16,11,&cdc,0,0,SRCCOPY);
			
			if (pRegister->getTypeSex() == 0)
				gi->cdc->SetTextColor(RGB(0,0,130));
			else	
				gi->cdc->SetTextColor(RGB(130,0,0));

			RWCString text = pRegister->getPrnLName().toMultiByte();
			gi->cdc->ExtTextOut(gi->rc.left+55,gi->rc.top+5,ETO_CLIPPED,gi->rc,CString(text),0);
			int ico=bmpForReg(pRegister->getTypeSex());
			if (ico) 
				w->paintGridBmp (23,0,ico);
			break;
		}
		default:
			break;
	}
}

int CHJudgesDlg::bmpForReg(int typeSex)
{
	if (typeSex == GSex::sMan)	    return BMPMAN;
	if (typeSex == GSex::sWoman)	return BMPWOMAN;
	
	return 0;
}

LRESULT CHJudgesDlg::onClick(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
		case LBL_EXIT:
			CDialog::OnCancel();
			break;
		default:
			break;
	}
	return 0;
	UNREFERENCED_PARAMETER(lParam);
}

void CHJudgesDlg::onDblClick(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
		case LSTJUDGES:
		{
			WORD hi=HIWORD(lParam);
			CHJudge *pJudge =(CHJudge *) w->getGridLParam(LSTJUDGES,hi);
			if (pJudge)
			{
				setJudgeOfMatch(pJudge);
				saveTeamSubMatchesJudge(pJudge);
			}
			CDialog::OnCancel();
			break;
		}
		default:
			break;
	}
}

void CHJudgesDlg::setJudgeOfMatch(CHJudge *pJudge)
{
	GSortedVector &vJudges = pMatch->getJudgesVector();
	CHMatchJudge *pMatchJudge =0;
	for (size_t i=0; i < vJudges.entries() ; i++)
	{
		pMatchJudge = (CHMatchJudge *) vJudges[i]->getElement();
		if (pMatchJudge &&
			pMatchJudge->getFunction() == pFunction && 
			pMatchJudge->getMatch() == pMatch &&
			pMatchJudge->getPositionCode() == numCode)

		{
			pMatchJudge = (CHMatchJudge *)mem()->removeMatchJudge(*pMatchJudge);
			APP::out(TRN_REMOVE_MATCH_JUDGES);
			APP::out(*pMatchJudge,OP_DELETE,TO_VENUE|TO_DATABASE);		
			APP::out();
		}
	}

	CHMatchJudge aMatchJudge(pMatch,pJudge);
	aMatchJudge.setFunction(pFunction);
	aMatchJudge.setMatch(pMatch);
	GPosition* pPosition=mem()->findPosition(char(numCode));
	if(pPosition)
		aMatchJudge.setPosition(pPosition);
	pMatchJudge = (CHMatchJudge *)mem()->setMatchJudge( aMatchJudge);
	
	pDlgParent->SendMessage(UM_CHNG_MATCHJUDGE,WPARAM(pMatchJudge) );	
	
	APP::out(TRN_SET_MATCH_JUDGES);
	APP::out(*pMatchJudge,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);		
	APP::out();
	
}

void CHJudgesDlg::saveTeamSubMatchesJudge(CHJudge *pJudge)
{
	if(pMatch->areTeams())
	{
		GSortedVector vMatches=pMatch->getSubMatches();
		CHMatch *pMatchAux=0;
		for(size_t i=0;i<vMatches.entries();i++)
		{
			pMatchAux = (CHMatch*)vMatches[i]->getElement();
			if(pMatchAux)
				setNewTeamMatchJudge(pJudge,pMatchAux);
		
		}
	}
}
	
void CHJudgesDlg::setNewTeamMatchJudge(CHJudge *pJudge,CHMatch *pMatchAux)
{
	GSortedVector &vJudges = pMatchAux->getJudgesVector();
	CHMatchJudge *pMatchJudge =0;
	for (size_t i=0; i < vJudges.entries() ; i++)
	{
		pMatchJudge = (CHMatchJudge *) vJudges[i]->getElement();
		if (pMatchJudge &&
			pMatchJudge->getFunction() == pFunction && 
			pMatchJudge->getMatch() == pMatchAux &&
			pMatchJudge->getPositionCode() == numCode)

		{
			pMatchJudge = (CHMatchJudge *)mem()->removeMatchJudge(*pMatchJudge);
			APP::out(TRN_REMOVE_MATCH_JUDGES);
			APP::out(*pMatchJudge,OP_DELETE,TO_VENUE|TO_DATABASE);		
			APP::out();
		}
	}

	CHMatchJudge aMatchJudge(pMatchAux,pJudge);
	aMatchJudge.setFunction(pFunction);
	aMatchJudge.setMatch(pMatchAux);
	GPosition* pPosition=mem()->findPosition(char(numCode));
	if(pPosition)
		aMatchJudge.setPosition(pPosition);
	pMatchJudge = (CHMatchJudge *)mem()->setMatchJudge( aMatchJudge);
	
	//pDlgParent->SendMessage(UM_CHNG_MATCHJUDGE,WPARAM(pMatchJudge) );	
	
	APP::out(TRN_SET_MATCH_JUDGES);
	APP::out(*pMatchJudge,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);		
	APP::out();
	
}

LRESULT CHJudgesDlg::onChangeJudge(WPARAM wParam, LPARAM lParam)	
{
	UNREFERENCED_PARAMETER(lParam);

	switch (wParam)
	{
		case TRN_SET_JUDGE:
		case TRN_DELETE_JUDGE:
		case TRN_SET_NAREGISTER:
			fillJudges();
			break;
	}
	return true;
}

BOOL CHJudgesDlg::DestroyWindow() 
{
	if (w)
		delete w;

	return CDialog::DestroyWindow();
}

void CHJudgesDlg::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
		
	switch(wParam)
	{
		case 27:
			OnCancel();
			break;
			
	}
}
