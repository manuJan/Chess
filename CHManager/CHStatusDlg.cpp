/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHStatusDlg.cpp
*	Description	: Implementation for the CHStatusDlg class.
*
*	Author		: CH Team
*	Date created: 21-12-2005
* 	Project		: CHManager
*	
* 	Modification history
*	By			: 
*	Date		: 
*	Changes		: 
*
***************************************************************************************/

#include "stdafx.h"
#include "CHManager.h"
#include "CHDefines.h"
#include "CHStatusDlg.h"
#include <SYS/GR/GraphicWnd.h>
#include <SPORTS/CH/DATA/CHMatch.h>
#include <SPORTS/CH/DATA/CHMemoryDataBase.h>
#include <SPORTS/CH/DATA/CHSportDefines.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CHStatusDlg (6200-6249)
#define	ECT_BUT_RUNNING				6200			
#define	ECT_BUT_UNOFFICIAL			6201
#define	ECT_BUT_OFFICIAL			6202
#define	ECT_BUT_SUSPEND				6203
#define	ECT_BUT_REVISION			6204
#define	ECT_BUT_STARTLIST			6205
#define	ECT_BUT_SCHEDULLED			6206


#define IDFNTBB						5442
#define IDFNTBBG					5443


////////////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CHStatusDlg, CDialog)
	//{{AFX_MSG_MAP(CHStatusDlg)
	ON_MESSAGE(UM_CLICK,OnClick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////////////////
CHStatusDlg::CHStatusDlg(CWnd * pParent,CHMatch * pSelMatch)
:CDialog(CHStatusDlg::IDD, pParent)
,pTheParent(pParent)
,pMatch(pSelMatch)
,status(pSelMatch->getStatus())
,changed(false)
,startList(true)
{
	pStatusMngt = new CHStatusManager();
}

////////////////////////////////////////////////////////////////////////////////////
CHMemoryDataBase * CHStatusDlg::mem()
{
	return (CHMemoryDataBase *) ((APP *)AfxGetApp())->memG();
}

////////////////////////////////////////////////////////////////////////////////////
BOOL CHStatusDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetWindowPos(&CWnd::wndTop,435,220,150,202,SWP_DRAWFRAME);

	w = new CGraphicWnd(this);
	INITW(w);
	

	w->addFont           (IDFNTBB,5,13,1,0,0,0,_T("Tahoma"));	
	w->addFont           (IDFNTBBG,8,18,1,0,0,0,_T("Tahoma"));

	GStatus * pStatus = mem()->findStatus(CHMemoryDataBase::eSchedulled);
	if( pStatus )
		w->createLabelEx(ECT_BUT_SCHEDULLED  , CRect(5, 5,140, 30), pStatus->getLDescription(), BORDER_UP, JUST_CENTER, IDBCK_BUT, IDCOL_AZUL, IDFNTBB, IDBCK_RED, IDCOL_AZUL5, IDFNTBBG);

	pStatus = mem()->findStatus(CHMemoryDataBase::eStartList);
	if( pStatus )
		w->createLabelEx(ECT_BUT_STARTLIST   , CRect(5, 32,140, 57), pStatus->getLDescription(), BORDER_UP, JUST_CENTER, IDBCK_BUT, IDCOL_AZUL, IDFNTBB, IDBCK_RED, IDCOL_AZUL5, IDFNTBBG);

	pStatus = mem()->findStatus(CHMemoryDataBase::eRunning);
	if( pStatus )
		w->createLabelEx(ECT_BUT_RUNNING   , CRect(5, 59,140, 84), pStatus->getLDescription(), BORDER_UP, JUST_CENTER, IDBCK_BUT, IDCOL_AZUL, IDFNTBB, IDBCK_RED, IDCOL_AZUL5, IDFNTBBG);

	pStatus = mem()->findStatus(CHMemoryDataBase::eSuspend);
	if( pStatus )
		w->createLabelEx(ECT_BUT_SUSPEND, CRect(5, 86,140, 111), pStatus->getLDescription(), BORDER_UP, JUST_CENTER, IDBCK_BUT, IDCOL_AZUL, IDFNTBB, IDBCK_RED, IDCOL_AZUL5, IDFNTBBG);

	pStatus = mem()->findStatus(CHMemoryDataBase::eUnofficial);
	if( pStatus )
		w->createLabelEx(ECT_BUT_UNOFFICIAL  , CRect(5, 113,140,138), pStatus->getLDescription(), BORDER_UP, JUST_CENTER, IDBCK_BUT, IDCOL_AZUL, IDFNTBB, IDBCK_RED, IDCOL_AZUL5, IDFNTBBG);

	pStatus = mem()->findStatus(CHMemoryDataBase::eFinished);
	if( pStatus )
		w->createLabelEx(ECT_BUT_OFFICIAL  , CRect(5,140,140,165), pStatus->getLDescription(), BORDER_UP, JUST_CENTER, IDBCK_BUT, IDCOL_AZUL, IDFNTBB, IDBCK_RED, IDCOL_AZUL5, IDFNTBBG);

	pStatus = mem()->findStatus(CHMemoryDataBase::eProtested);
	if( pStatus )
		w->createLabelEx(ECT_BUT_REVISION  , CRect(5,167,140,192), pStatus->getLDescription(), BORDER_UP, JUST_CENTER, IDBCK_BUT, IDCOL_AZUL, IDFNTBB, IDBCK_RED, IDCOL_AZUL5, IDFNTBBG);

	w->enable(ECT_BUT_SCHEDULLED ,(status==CHMemoryDataBase::eStartList && status!=CHMemoryDataBase::eSchedulled));
	w->enable(ECT_BUT_STARTLIST ,(status!=CHMemoryDataBase::eFinished && status!=CHMemoryDataBase::eStartList));
	w->enable(ECT_BUT_RUNNING   ,(status==CHMemoryDataBase::eSuspend ||  status==CHMemoryDataBase::eStartList) &&(status!=CHMemoryDataBase::eRunning   ));
	w->enable(ECT_BUT_SUSPEND   ,(status==CHMemoryDataBase::eRunning   )&&(status!=CHMemoryDataBase::eSuspend   ));
	w->enable(ECT_BUT_UNOFFICIAL,(status>=CHMemoryDataBase::eRunning   )&&(status< CHMemoryDataBase::eSuspend));
	w->enable(ECT_BUT_OFFICIAL  ,(status>CHMemoryDataBase::eSuspend   )&&(status!=CHMemoryDataBase::eFinished  ));
	w->enable(ECT_BUT_REVISION  ,(status>=CHMemoryDataBase::eUnofficial)&&(status!=CHMemoryDataBase::eProtested ));

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////
void CHStatusDlg::OnClick(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch( wParam )
	{
		case ECT_BUT_SCHEDULLED	:
			 status = CHMemoryDataBase::eSchedulled;
			 onOK();
			 break;
		case ECT_BUT_STARTLIST:
			 status = CHMemoryDataBase::eStartList;
			 onOK();
			 break;
		case ECT_BUT_RUNNING :
			 status = CHMemoryDataBase::eRunning;
			 onOK();
			 break;
		case ECT_BUT_SUSPEND :
			 status = CHMemoryDataBase::eSuspend;
			 onOK();
			 break;
		case ECT_BUT_UNOFFICIAL :
			 status = CHMemoryDataBase::eUnofficial;
			 onOK();
			 break;
		case ECT_BUT_OFFICIAL :
			 status = CHMemoryDataBase::eFinished;
			 onOK();
			 break;
		case ECT_BUT_REVISION :
			 status = CHMemoryDataBase::eProtested;
			 onOK();
			 break;
	}
}

////////////////////////////////////////////////////////////////////////////////////
BOOL CHStatusDlg::PreTranslateMessage(MSG * pMsg)
{
	if( pMsg->message == WM_KEYDOWN )
	{
		int m_lastChar = pMsg->wParam;
		switch( m_lastChar )
		{
		case VK_ESCAPE:
			 changed=false; 
			 OnCancel();
			 return 1;
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

////////////////////////////////////////////////////////////////////////////////////
BOOL CHStatusDlg::OnDestroy()
{
	if( w ) delete w;
	if (pStatusMngt)
		delete pStatusMngt;

	return CDialog::DestroyWindow();
}
void CHStatusDlg::onOK() 
{
	changed=true;
		
	if (status && (status!=pMatch->getStatus()))
	{
		// Si permito cambiar el status esté como esté y pasarlo a Running
		// para evitar que se equivoquen y se ponga en Unofficial (u otros) 
		// y no se pueda volver al status correcto
		if( status==CHMemoryDataBase::eRunning)
			pStatusMngt->run(*pMatch, unsigned char(status));
		else 
		{
			if(status==CHMemoryDataBase::eStartList && pMatch->getStatus()==CHMemoryDataBase::eSchedulled)
				startList=false;
			pStatusMngt->run(*pMatch, unsigned char(status));
			//ponemos todos los enfrentamientos de equipos a startlist si estaba en schedule
			//o de schedule a startlist
			if((status==CHMemoryDataBase::eStartList && pMatch->getStatus()==CHMemoryDataBase::eStartList) ||
				(status==CHMemoryDataBase::eSchedulled && pMatch->getStatus()==CHMemoryDataBase::eSchedulled))
				pStatusMngt->saveTeamSubMatchesStatus(pMatch,status);
		}
	}
	CDialog::OnOK();
}
bool CHStatusDlg::hasChanges()
{
	return changed;
}
void CHStatusDlg::saveMatch(CHMatch * pMatch)
{
	if (pMatch)
	{		
		APP::out(TRN_CHANGE_MATCH);
		APP::out(*pMatch,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
		APP::out();
	}
}

