/*************************************************************************************
*	© Copyright MSL Software, S.L., 2001
*
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHPgnMatchesDlg.h
*   Description	: 
*
*	Author		: Chess Team
*	Date created: 
* 	Project		:
*
***************************************************************************************/


#if !defined(AFX_CHPGNMATCHESDLG_H__C7D59247_7FFD_4184_9997_F596BB68B461__INCLUDED_)
#define AFX_CHPGNMATCHESDLG_H__C7D59247_7FFD_4184_9997_F596BB68B461__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CHPgnMatchesDlg.h : header file
//
#include "resource.h"
#include "CHEvenControlOperations.h"


class CHPgnMatch;
/////////////////////////////////////////////////////////////////////////////
// CHPgnMatchesDlg dialog

class CHPgnMatchesDlg : public CDialog
{
// Construction
public:
	CHPgnMatchesDlg(GSortedVector &_vMatchesInPlay, GSortedVector &_vPgnMatches , CWnd* pParent = NULL);   // standard constructor

	inline CHMemoryDataBase *mem() 
	{
		return (CHMemoryDataBase *) ((GManagerInterfaceApp*)AfxGetApp())->memG(); 
	}

// Dialog Data
	//{{AFX_DATA(CHPgnMatchesDlg)
	enum { IDD = IDD_PGN_MATCHES };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHPgnMatchesDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	void fillMatchesGrid();
	void fillPgnMatchesGrid();

	BOOL onPaintGrid(UINT idGrid,GridItem *gi);
	void paintListMatches(GridItem *gi);
	void paintListPgnMatches(GridItem *gi);

	BOOL onGridDrag(WPARAM wParam, LPARAM lParam);
	BOOL onGridDrop(WPARAM wParam, LPARAM lParam);
	void onClick(WPARAM wParam, LPARAM lParam);



	// Generated message map functions
	//{{AFX_MSG(CHPgnMatchesDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

	CGraphicWnd *w;

	GSortedVector *vMatchesInPlay;
	GSortedVector *vPgnMatches;

	CHEvenControlOperations    eventControlOp;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHPGNMATCHESDLG_H__C7D59247_7FFD_4184_9997_F596BB68B461__INCLUDED_)
