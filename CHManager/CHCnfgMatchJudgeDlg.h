/*************************************************************************************
*	© Copyright MSL Software, S.L., 2001
*
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHCnfgMatchJudgeDlg.h
*   Description	: 
*
*	Author		: Chess Team
*	Date created: 27-12-2005
* 	Project		:
*
***************************************************************************************/

#if !defined(AFX_CHCnfgMatchJudgeDlg_H__59A174F4_684B_453C_B9DB_443BF5941C9F__INCLUDED_)
#define AFX_CHCnfgMatchJudgeDlg_H__59A174F4_684B_453C_B9DB_443BF5941C9F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include "CHStatusManager.h"
#include <sports/CH/data/CHMemoryDataBase.h>
#include <sports/CH/data/CHMatch.h>
#include <sports/CH/data/CHMatchResult.h>
#include <sports/CH/data/CHMatchJudge.h>
#include <sports/CH/data/CHMsgDefines.h>
#include "CHJudgesDlg.h"

class CHCnfgMatchJudgeDlg : public CDialog
{
// Construction
public:
	CHCnfgMatchJudgeDlg(CWnd* pParent,CHMatch *pSelMatch);   // standard constructor
	
// Dialog Data

	//{{AFX_DATA(CHCnfgMatchJudgeDlg)
	enum { IDD = IDD_CNFG_MATCH_JUDGES_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHCnfgMatchJudgeDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHCnfgMatchJudgeDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	LRESULT onClick(WPARAM wParam, LPARAM lParam);
	void onDblClick(WPARAM wParam, LPARAM lParam);
	LRESULT onChangeMatchJudge(WPARAM wParam, LPARAM lParam);
	LRESULT onSelectMatchMember(WPARAM wParam, LPARAM lParam);
	LRESULT onChangeMatch(WPARAM wParam, LPARAM lParam);
	void showJudge(CHMatchJudge *pMatchJudge);
	void showHeadCompetitors();
	void showConfiguredMatch();
	void paintStatus();	
	void onOK();
	void OnKeyDown(WPARAM wParam, LPARAM lParam);
	void changeStatus();

	void outMatch(CHMatch *pMatch);

private:
	inline CHMemoryDataBase *mem() 
	{
		return (CHMemoryDataBase *) ((GManagerInterfaceApp*)AfxGetApp())->memG(); 
	}
	
	RWBoolean registersInMatch();
	void      removeMatchJudge(short numCode);
	void	  removeTeamMatchJudges(short numCode);
public:
	CGraphicWnd *w;
	CHMatch *pMatch ;
	CBitmap *pBmpFlagH;
	CBitmap *pBmpFlagV;
	CBitmap *pBmpFlagJS;
	CBitmap *pBmpFlagJU;
	GVenue *pComboVenue;
	GCourt *pComboCourt;	
	CHStatusManager *pStatusMngt;
	CHJudgesDlg *pJudgesDlg;	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHCnfgMatchJudgeDlg_H__59A174F4_684B_453C_B9DB_443BF5941C9F__INCLUDED_)
