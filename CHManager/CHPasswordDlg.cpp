/*************************************************************************************
*			© Copyright MSL Software, S.L., 2001
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHPasswordDlg.cpp
*   Description	: CH Password Dlg
*
*	Author		: Chess Team
*	Date created: 15-12-2005
* 	Project		: CH Manager
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/


#include "stdafx.h"
#include "CHmanager.h"
#include "CHPasswordDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDBBKCLEAR				1701
#define IDBBKBLUE				1702
#define IDBBKBROWN				1703
#define BUCH_OK					1704
#define BUCH_CANCEL				1705
#define CHL_VALUE				1706
#define ED_VALUE				1707
#define IDBBKYELLOW				1710
#define CHL_CARTEL_NAME			1711
#define FONTDCHG				1712
#define GRID_BREEDS				1713
#define BUCH_ADD				1714
#define BUCH_DEL				1715
#define FONTDLG					1716
#define IDB_CK1					1717
#define IDB_CK2					1718
#define IDB_CK3					1719
#define CHL_PASSWORD			1720
#define	ED_PASSWORD				1721
/////////////////////////////////////////////////////////////////////////////
// CHPasswordDlg dialog

CHPasswordDlg::CHPasswordDlg(CWnd* pParent /*=NULL*/)
:CDialog(CHPasswordDlg::IDD, pParent)
,pressed(false)
,w(0)
{
	//{{AFX_DATA_INIT(CHPasswordDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CHPasswordDlg::~CHPasswordDlg()
{
	
}
void CHPasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHPasswordDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHPasswordDlg, CDialog)
	//{{AFX_MSG_MAP(CHPasswordDlg)
		ON_MESSAGE(UM_CLICK, onClick)
		ON_WM_SIZE()
		ON_WM_CLOSE()
		ON_MESSAGE(UM_KEYDOWN, OnKeyDown)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHPasswordDlg message handlers

BOOL CHPasswordDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	w=new CGraphicWnd(this);

	if (!w)
		return FALSE;
	INITW(w);
	//w->addBackgroundColor(IDBBKCLEAR,RGB(240,240,250));
	w->addBackgroundColor(IDBBKBLUE ,RGB(194,206,245));
	w->addBackgroundColor(IDBBKBROWN,RGB(239,220,189));
	w->addBackgroundColor(IDBBKYELLOW,RGB(255,255,207));
	w->setBackground (IDBBKCLEAR);	
	w->addFont (FONTDLG,6,14,1,0,0,0,_T("Arial"));
	w->addFont (FONTDCHG,8,16,1,0,0,0,_T("Arial"));
		
	w->addBackgroundColor(IDB_CK1 ,RGB(74,149,149));
	w->addBackgroundColor(IDB_CK2 ,RGB(183,220,180));
	w->addBackgroundColor(IDB_CK3 ,RGB(239,235,222));
				
	w->createLabel(CHL_PASSWORD,CRect(30, 40,130,70),"Password",BORDER_UP,JUST_CENTER,IDB_CK1,IDCOL,IDFNT_BOLD);
	w->createEdit(ED_PASSWORD,  CRect(130,40,230,70),"",BORDER_UP,JUST_CENTER,IDB_CK2,IDCOL,IDFNT_BOLD);
	w->doEditFormat(ED_PASSWORD,"*");

	// BUCHON OK / CANCEL
	w->createButton (BUCH_OK,CRect(50, 90,120, 120),"OK",IDBBKBROWN,0,FONTDLG);
	w->createButton (BUCH_CANCEL,CRect( 140, 90, 210,120),"Cancel",IDBBKBROWN,0,FONTDLG);
	
	w->setFocus(ED_PASSWORD);
	
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
BOOL CHPasswordDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	if(w)	
		delete w;

	return CDialog::DestroyWindow();
}

LRESULT CHPasswordDlg::onClick(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (wParam)
	{
		case BUCH_OK:
		{
			OnOK();
			break;
		}
		case BUCH_CANCEL:
		{
			CDialog::OnCancel();
			break;
		}
				
	}
	return TRUE;
}

void CHPasswordDlg::OnOK()
{
	if(!strcmp(w->getTxt(ED_PASSWORD),"msl"))
	{	
		pressed=true;
		CDialog::OnOK();
	}
	else ::msg("Error","Incorrect Password");
}
void CHPasswordDlg::OnKeyDown (WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch(wParam)
	{
		case 27: // Escape
			OnCancel();
			break;
		case 13: // Enter
			OnOK();
			break;
		
	}
}