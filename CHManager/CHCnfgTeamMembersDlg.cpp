/*************************************************************************************
*	© Copyright MSL Software, S.L., 2001
*
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CCHCnfgTeamMembersDlg.cpp
*   Description	: 
*
*	Author		: Chess Team
*	Date created: 27-12-2005
* 	Project		:
*
***************************************************************************************/

#include "stdafx.h"
#include "CHmanager.h"
#include "CHCnfgTeamMembersDlg.h"
#include <Sports\CH\Data\CHMember.h>
#include <Sports\CH\Data\CHMatchResult.h>
#include <Core\G\GMsgDefines.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DBLUE			700
#define FONT			701
#define IDBCK3			705
#define TEAMMEMBERS     706
#define HEADER_NOC		707


RWBoolean matchMembers(const RWCollectable * col, const void * param)
{
	CHMatch * pMatch = (CHMatch*) param;
	CHMatchMember *pMatMem=(CHMatchMember *)col;
	CHMatch *pActMatch=(CHMatch *)pMatMem->getMatch();

	if (pActMatch->getKey()==pMatch->getKey() &&
		pActMatch->getSubMatch()==pMatch->getSubMatch())
	{
		return true;
	}
	return false;	
}

/////////////////////////////////////////////////////////////////////////////
// CCHCnfgTeamMembersDlg dialog


CCHCnfgTeamMembersDlg::CCHCnfgTeamMembersDlg(CHMemoryDataBase * pMemory, CHMatch *pMatch, CHMatchMember *pMatchMember, CWnd* pParent /*=NULL*/)
: CDialog(CCHCnfgTeamMembersDlg::IDD, pParent)
,w(0)
,mMem(pMemory)
,pInMatchMember(pMatchMember)
,pInMatch(pMatch)
,pSelMember(0)
{
	//{{AFX_DATA_INIT(CCHCnfgTeamMembersDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCHCnfgTeamMembersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCHCnfgTeamMembersDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCHCnfgTeamMembersDlg, CDialog)
	//{{AFX_MSG_MAP(CCHCnfgTeamMembersDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCHCnfgTeamMembersDlg message handlers

BOOL CCHCnfgTeamMembersDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	w = new CGraphicWnd(this);

	// BackGround Color
	w->addBackgroundColor	( IDBCK3, RGB(240,240,250));
	w->setBackground		( IDBCK3 );
	// Font Text
	w->addFont (FONT,6,14,1,0,0,0,_T("Tahoma"));
	// Color Text
	w->addColorSet( DBLUE, COLOR_DEFAULT_ON, COLOR_DEFAULT_OFF, COLOR_DEFAULT_HITX, COLOR_DEFAULT_HIGH, COLOR_DEFAULT_L3D, COLOR_DEFAULT_N3D, COLOR_DEFAULT_D3D );
	
	// Preparamos header.
	
	CString sHeader=_T(""); CString sType=_T("");
	CString sNOC=pInMatchMember->getTeamPrnLName();
	CHMatch *pMatch=(CHMatch *)pInMatchMember->getMatch();
	
	sType=_T("Singles");
	
	sHeader.Format(_T("%s Match %d Select Member %d for %s"),sType,pMatch->getSubMatch(),pInMatchMember->getMatchMember(),sNOC);
	
	// Grid to see
	w->createGrid	(TEAMMEMBERS,CRect(10,15,415,230),6,22,IDBCK3,DBLUE,FONT);
	w->gridLineColor(TEAMMEMBERS,RGB(192,192,192),RGB(192,192,192));
	w->addGridColumn(TEAMMEMBERS,"Order",JUST_CENTER,74);
	w->addGridColumn(TEAMMEMBERS,sHeader,JUST_CENTER,330);
	
	// Fill the Grid
	fillListMembers();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCHCnfgTeamMembersDlg::fillListMembers()
{
	w->gridDeleteAllItems(TEAMMEMBERS);
	if(!pInMatch || !pInMatchMember)
		return;

	/*
	CHMatchResult *pMatchResult=0;
	GSortedVector &vCompetitors=pInMatch->getCompetitorsVector();
	if(pInMatchMember->getMatchMember()>=short(vCompetitors.entries()))
		return;

	pMatchResult = (CHMatchResult*)vCompetitors[pInMatchMember->getMatchMember()-1]->getElement();
	if (!pMatchResult)
		return;

	CHMatchMember *pMatchMember=0;
	GSortedVector &vMatchMembers=pMatchResult->getMembersVector();

	for (size_t i=0; i<vMatchMembers.entries(); i++)
	{
		pMatchMember=(CHMatchMember *)vMatchMembers[i]->getElement();
		if (pMatchMember)
			w->addGridLine(TEAMMEMBERS,LPARAM(pMatchMember),"");
	}
	*/

	CHMember *pMember=0;
	GSortedVector &vMembers=pInMatchMember->getMembersVector();

	
	for (size_t i=0; i<vMembers.entries(); i++)
	{
		pMember=(CHMember *)vMembers[i]->getElement();
		if (pMember /*&& isMatchMember((CHMatch *)pInMatchMember->getMatch(),pMember)*/)
			w->addGridLine(TEAMMEMBERS,LPARAM(pMember),"");
	}
}

void CCHCnfgTeamMembersDlg::paintMenbers(GridItem *gi)
{
	if (!gi)
		return;

	if(gi->y%2)
		gi->cdc->FillSolidRect(CRect(gi->rc.left,gi->rc.top,gi->rc.right+45,gi->rc.bottom),(gi->sel)?0xF0C0C0:0xFFFFFF);
	else 
		gi->cdc->FillSolidRect(CRect(gi->rc.left,gi->rc.top,gi->rc.right+45,gi->rc.bottom),(gi->sel)?0xF0C0C0:RGB(238,238,238));

	CHMember *pMember=(CHMember *)gi->lParam;
	if (!pMember || !pMember->getRegister())
		return;

	//Text
	gi->cdc->SetBkMode(TRANSPARENT);

	char tmp[10];
	switch(gi->x)

	{
	case 0:		// Order
		w->paintGridText( 10, 3, itoa(pMember->getOrder(),tmp,10), JUST_LEFT);
		break;
	case 1:		// Nombre
		w->paintGridText( 20, 3, pMember->getPrnLName(), JUST_LEFT);
		break;
	}
}

BOOL CCHCnfgTeamMembersDlg::DestroyWindow()
{
	if (w)	
		delete w;

	return CDialog::DestroyWindow();
}

LRESULT CCHCnfgTeamMembersDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	if (message==UM_PAINTGRID)
	{
		switch (wParam)
		{
			case TEAMMEMBERS:
				paintMenbers((GridItem *) lParam);
				break;
		}
		return TRUE;
	}

	/*if ( message==UM_CLICK )
	{
		switch(wParam)
		{
			case TEAMMEMBERS:
				{	
					pSelMember=(CHMember *)w->getGridLParam(TEAMMEMBERS,w->getSelectedLine(TEAMMEMBERS)); 
					if (pInMatchMember && pSelMember)
						pInMatchMember->setMember(pSelMember);
					break;
				}
		}
		return TRUE;
	}*/
	if ( message==UM_DBLCLICK )
	{
		switch(wParam)
		{
			case TEAMMEMBERS:
				{	
					pSelMember=(CHMember *)w->getGridLParam(TEAMMEMBERS,w->getSelectedLine(TEAMMEMBERS)); 
					if (pInMatchMember && pSelMember)
					{
						pInMatchMember->setMember(pSelMember);
						OnCancel();
					}
					break;
				}
		}
		return TRUE;
	}
	if ( message==UM_KEYDOWN )
	{
		switch(wParam)
		{
			case 27:
				OnCancel();
				break;
				
		}
		return TRUE;
	}
	

	return CDialog::WindowProc(message, wParam, lParam);
}

bool CCHCnfgTeamMembersDlg::isMatchMember(CHMatch *pMatch,CHMember *pMember)
{
	RWSet * colMatchMembers=(RWSet *) CHMemoryDataBase::getColMatchMember().select
		(matchMembers,pMatch);

	CHMatchMember *pMatchMember=0;
	RWSetIterator ite(*colMatchMembers);
	while( (pMatchMember=(CHMatchMember *)ite()) != 0)
	{
//		CHMatch *pMat=(CHMatch *)pInMatchMember->getMatch();
//		CHMatch *pMatA=(CHMatch *)pMatchMember->getMatch();
		if (!pMatchMember->getMember())
			continue;
		if (pMatchMember->getRegister()==pMember->getRegister())
			return false;
	}
	return true;
}