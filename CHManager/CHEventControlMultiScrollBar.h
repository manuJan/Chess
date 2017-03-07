/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHEventControlMultiScrollBar.h
*	Description	:
*
*	Author		:Javier Juste 
*	Date created:  31-julio-2001
* 	Project		:
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#if !defined(AFX_CHEVENTCONTROLMULTISCROLLBAR_H)
#define AFX_CHEVENTCONTROLMULTISCROLLBAR_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CHScrollBar.h : header file

/////////////////////////////////////////////////////////////////////////////
// CHEventControlMultiScrollBar window

class CHEventControlMultiScrollBar : public CScrollBar
{
// Construction
public:
	CHEventControlMultiScrollBar(int entries,CRect _rect, CWnd* pWnd);

// Attributes
public:

// Operations
public:

	void setPosition(int position);
	void setEntries(int entries);
	int getPosition();
	int getEntries();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHEventControlMultiScrollBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHEventControlMultiScrollBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CHEventControlMultiScrollBar)
	afx_msg void VScroll(UINT nSBCode, UINT nPos);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	LRESULT onVScrollToPosition(WPARAM wParam, LPARAM lParam);	

private:
	int			position;
	int			entries;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHEVENTCONTROLMULTISCROLLBAR_H)
