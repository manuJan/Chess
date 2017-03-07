/*************************************************************************************
*	© Copyright MSL Software, S.L., 2001
*
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHJudgesDlg.h
*   Description	: 
*
*	Author		: Chess Team
*	Date created: 27-12-2005
* 	Project		:
*
***************************************************************************************/

#if !defined(AFX_CHJUDGESDLG_H__CH17AD74_3B9F_4BCE_A654_8CF563EC57CH__INCLUDED_)
#define AFX_CHJUDGESDLG_H__CH17AD74_3B9F_4BCE_A654_8CF563EC57CH__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <sports/CH/data/CHMemoryDataBase.h>
#include <sports/CH/data/CHMatch.h>
#include <sports/CH/data/CHMatchJudge.h>
#include <SYS\GR\GraphicWnd.h>
#include <GUI/FLAGS/flags.h>
#include "resource.h"

#define UM_CHNG_MATCHJUDGE		   WM_USER + 12000

class CHJudgesDlg : public CDialog
{
// Construction
public:
	CHJudgesDlg(CHMatch *pSelMatch,int function,short code,CWnd* pParent = NULL);   // standard constructor
	// Dialog Data
	//{{AFX_DATA(CHJudgesDlg)
	enum { IDD = IDD_JUDGES_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHJudgesDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CHJudgesDlg)
		afx_msg void onDblClick(WPARAM wParam, LPARAM lParam);
		virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void fillJudges();
	void paintJudges(GridItem *gi);
	LRESULT onClick(WPARAM wParam, LPARAM lParam);
	LRESULT onChangeJudge(WPARAM wParam, LPARAM lParam);
	BOOL onPaintGrid  (UINT idGrid,GridItem *gi);
	int bmpForReg(int typeSex);
	void setJudgeOfMatch(CHJudge *pJudge);
	void saveTeamSubMatchesJudge(CHJudge *pJudge);
	void setNewTeamMatchJudge(CHJudge *pJudge,CHMatch *pMatchAux);
	

private:
	inline CHMemoryDataBase *mem() 
	{
		return (CHMemoryDataBase *) ((GManagerInterfaceApp*)AfxGetApp())->memG(); 
	}
	void OnKeyDown(WPARAM wParam, LPARAM lParam);

public:
	CGraphicWnd *w;
	CHMatch	    *pMatch;
	GFunction   *pFunction;
	CWnd		*pDlgParent;
	short		numCode;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHJUDGESDLG_H__CH17AD74_3B9F_4BCE_A654_8CF563EC57CH__INCLUDED_)
