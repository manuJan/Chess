/*************************************************************************************
*			© Copyright MSL Software, S.L., 2001
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:	CHTreatSession.h
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

#if !defined(AFX_CHTREATSESSION_H)
#define AFX_CHTREATSESSION_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Sports/CH/data/CHMemoryDataBase.h>
#include <Sports/CH/data/CHSession.h>
#include "resource.h"
#include <SYS/GR/GraphicWnd.h>
#include <GUI/TH/GUITHSports.h>
#include <GUI/TH/GTreatSessions.H>
#include "CHScheduleFormView.h"


class CHTreatSession : public GTreatSessions
{
// Construction
public:
	CHTreatSession(CHMemoryDataBase * pMemory,CWnd* pParent = NULL);   // standard constructor
	
	
// Dialog Data
	//{{AFX_DATA(CHTreatSession)
	//}}AFX_DATA

// Implementation
protected:

	GTHSession* getNewSession()
	{ return new CHSession();}

	// Generated message map functions
	//{{AFX_MSG(CHTreatSession)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHTreatSession)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHTREATSESSION_H)
