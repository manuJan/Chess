/*************************************************************************************
*			© Copyright MSL Software, S.L., 2001
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:	CHTreatSession.cpp
*	Description	:   Session proccess
*
*	Author		:	Fernando Garcia
*	Date created:   27-Mayo-2002
* 	Project		:	Table Tennis Manager
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdafx.h"
#include "CHmanager.h"
#include "CHTreatSession.h"
#include "CHScheduleFormView.h"
#include <GUI/TH/GUITHSports.h>
#include <GUI/TH/GTHScheduleFormView.h>
#include <GUI/GS/GScheduleDay.h>
#include <CORE/TH/GTHMsgDefines.h>
#include <core/TH/GTHOrderFunctions.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CHTreatSession::CHTreatSession(CHMemoryDataBase * pMemory,CWnd* pParent /*=NULL*/)
: GTreatSessions(pMemory, pParent)
{
}

void CHTreatSession::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHTreatSession)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHTreatSession, GTreatSessions)
	//{{AFX_MSG_MAP(CHTreatSession)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

