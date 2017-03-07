/*************************************************************************************
*			© Copyright MSL Software, S.L., 2001
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHCnfgDisciplineFormView.h
*   Description	: CH Configuration of Discipline
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
#if !defined(AFX_CCHCnfgDisciplineFormView_H__EC533014_34E5_48C4_B41E_5C31F7D03516__INCLUDED_)
#define AFX_CCHCnfgDisciplineFormView_H__EC533014_34E5_48C4_B41E_5C31F7D03516__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CCHCnfgDisciplineFormView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCHCnfgDisciplineFormView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include <GUI/GS/GCnfgDisciplineFormView.h>
#include <Sports/CH/Data/CHDiscipline.h>
#include <Sports/CH/Data/CHMemoryDataBase.h>


class CCHCnfgDisciplineFormView : public GCnfgDisciplineFormView
{
protected:
	CCHCnfgDisciplineFormView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CCHCnfgDisciplineFormView)

// Form Data
public:
	//{{AFX_DATA(CCHCnfgDisciplineFormView)
//	enum { IDD = _UNKNOWN_RESOURCE_ID_ };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	void init();
	BOOL exit();

    GDiscipline* getCopyDiscipline();
	void saveDiscipline();
	
	inline CHMemoryDataBase * mem()
	{	return (CHMemoryDataBase *)((GManagerInterfaceApp *) AfxGetApp())->memG(); }
		

private:
		
	CHDiscipline *pDiscipline;
	bool fChange;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCHCnfgDisciplineFormView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCHCnfgDisciplineFormView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CCHCnfgDisciplineFormView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void fillCHControls();
	RWBoolean compareChange();
	void setValuesToCopy();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHCNFGDISCIPLINEFORMVIEW_H__EC533014_34E5_48C4_B41E_5C31F7D03516__INCLUDED_)
