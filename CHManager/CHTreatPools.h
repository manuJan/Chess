/*************************************************************************************
*			© Copyright MSL Software, S.L., 2001
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:	CHTreatPools.h
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

#if !defined(AFX_CHTREATPOOLS_H__8C548507_9B8A_4CD4_9EBC_355DCEB85C8E__INCLUDED_)
#define AFX_CHTREATPOOLS_H__8C548507_9B8A_4CD4_9EBC_355DCEB85C8E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CHTreatPools.h : header file
//

#include <GUI/TH/GTreatPools.h>

/////////////////////////////////////////////////////////////////////////////
// CHTreatPools dialog

class CHTreatPools : public GTreatPools
{
// Construction
public:
	CHTreatPools(GTHMemoryDataBase * pMemory, GTHPhase * aPhase, GTHProgression* aTHProgression,RWBoolean isRealPool, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHTreatPools)
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHTreatPools)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	void calculateNumMatches();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHTreatPools)
	BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHTREATPOOLS_H__8C548507_9B8A_4CD4_9EBC_355DCEB85C8E__INCLUDED_)
