#if !defined(AFX_CHMASTERTYPEDLG_H__A0CC819B_59C9_42DF_B896_21C7569E0760__INCLUDED_)
#define AFX_CHMASTERTYPEDLG_H__A0CC819B_59C9_42DF_B896_21C7569E0760__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CHMasterTypeDlg.h : header file
//

#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CHMasterTypeDlg dialog
class CHMemoryDataBase;
class CHRegsiter;
class CHMasterTypeDlg : public CDialog
{
// Construction
public:
	CHMasterTypeDlg(CHMemoryDataBase* pMem,CHRegister *pRegister,CWnd* pParent = NULL);   // standard constructor

	inline CHMasterType * getMasterType() const
		{ return pMasterType; }
	inline RWBoolean getPressed() const
	{ return pressed; }

private:
	short fillMasterType(short type=0);		
	void  paintMasterType(GridItem* gi);
	bool  addMasterType();
	bool  delMasterType(CHMasterType *pMasterType);
	short getNextMasterTypeId();
	void  saveMasterType(CHMasterType* pMasterType);
	void  paintCartel();
	void  OnOK();

// Dialog Data
	//{{AFX_DATA(CHMasterTypeDlg)
	enum { IDD = IDD_MASTER_TYPE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHMasterTypeDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHMasterTypeDlg)
	virtual BOOL OnInitDialog();
	afx_msg LRESULT onClick(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT onDblClick(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT onPaintGrid(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT onClickHeader(WPARAM wParam,LPARAM lParam);
	afx_msg void    OnKeyDown (WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CGraphicWnd*	  w;
	CHMemoryDataBase* pMemory;
	CHMasterType*     pMasterType;
	RWBoolean		  pressed;
	CHRegister*       pRegisterSel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHMASTERTYPEDLG_H__A0CC819B_59C9_42DF_B896_21C7569E0760__INCLUDED_)
