/*************************************************************************************
*			© Copyright MSL Software, S.L., 2001
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:	CHTreatPhases.h
*	Description	:   Session proccess
*
*	Author		:	Fernando Garcia
*	Date created:   
* 	Project		:	Chess Manager
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#if !defined(AFX_CHTREATPHASES_H__65C7038E_6D75_4B2D_993A_9B3B8A0F6CA6__INCLUDED_)
#define AFX_CHTREATPHASES_H__65C7038E_6D75_4B2D_993A_9B3B8A0F6CA6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CHTreatPhases.h : header file
//

#include <GUI/TH/GTreatPhases.h>

class CHTreatPhases : public GTreatPhases
{
// Construction
public:
	CHTreatPhases(GTHMemoryDataBase * pMemory, GTHEvent * aEvent, GTHProgression* aTHProgression, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHTreatPhases)
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHTreatPhases)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	void init (BOOL isPool);
	void calculateNumMatches();

	// Generated message map functions
	//{{AFX_MSG(CHTreatPhases)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHTREATPHASES_H__65C7038E_6D75_4B2D_993A_9B3B8A0F6CA6__INCLUDED_)
