/*************************************************************************************
*			© Copyright MSL Software, S.L., 2001
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHPasswordDlg.h
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
#if !defined(AFX_CHPasswordDlg_H__B54082B6_402D_40E3_9527_0C5F294013C0__INCLUDED_)
#define AFX_CHPasswordDlg_H__B54082B6_402D_40E3_9527_0C5F294013C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CHPasswordDlg.h : header file
//

#include "resource.h"

class CHMemoryDataBase;
class CHEvent;

class CHPasswordDlg : public CDialog
{
// Construction
public:
	CHPasswordDlg(CWnd* pParent = NULL);// standard constructor
	virtual ~CHPasswordDlg();
	
	inline RWBoolean getPressed() const
	{ return pressed; }

private:
	
	void  OnOK();
	BOOL  DestroyWindow() ;
	
	
// Dialog Data
	//{{AFX_DATA(CHPasswordDlg)
	enum { IDD = IDD_PASSWORD };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHPasswordDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHPasswordDlg)
	virtual BOOL OnInitDialog();
	afx_msg LRESULT onClick(WPARAM wParam, LPARAM lParam);
	afx_msg void    OnKeyDown (WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	

private:
	CGraphicWnd* w;
	RWBoolean	  pressed;
	
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHPasswordDlg_H__B54082B6_402D_40E3_9527_0C5F294013C0__INCLUDED_)
