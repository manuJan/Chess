/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHAfterInitialLoadDlg.h
*	Description	:
*
*	Author		: Javier Juste
*	Date created: 27-Sep-2006
* 	Project		: Chess After Initial Load update data
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#if !defined(AFX_XXAFTERINITIALLOADDLG_H__26648979_4F2E_4B16_9188_8CE301F02251__INCLUDED_)
#define AFX_XXAFTERINITIALLOADDLG_H__26648979_4F2E_4B16_9188_8CE301F02251__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class GMemoryDataBase;
class MSLNetwork;
class CHInscription;

class CCHAfterInitialLoadDlg : public CDialog
{

public:
	CCHAfterInitialLoadDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCHAfterInitialLoadDlg)
	enum { IDD = IDD_AFTERINITIALLOAD_DIALOG };
	CProgressCtrl	m_progress;
	CString	m_Names;
	CString	m_Numbering;
	CString	m_EventResult;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCHAfterInitialLoadDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCHAfterInitialLoadDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdateBt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	GMemoryDataBase	* OnNewMemoryDB();

private:
	void			 initProgressControl();

	void			 processRegisters	();
	void			 processInscriptions();

	RWBoolean		 setNames			(GRegister * pRegister);
	RWBoolean		 setNumbering		(int numbering);
	RWBoolean		 setEventResult		(CHInscription * pInscription);
	void			 orderMembers		(CHInscription * pInscription);
	void			 getMembers			(CHInscription * pInscription,RWSet & sMembers);

protected:
	RWDBConnection	  aConnect;

	int				  nPosProgress;
	GMemoryDataBase	* m_pMem;
	MSLNetwork		* m_pOnline;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XXAFTERINITIALLOADDLG_H__26648979_4F2E_4B16_9188_8CE301F02251__INCLUDED_)
