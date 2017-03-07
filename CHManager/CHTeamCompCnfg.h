/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior wriCHen permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHTeamCompCnfg.h
*	Description	:
*
*	Author		:Chess Team
*	Date created:15-12-2005
* 	Project		:
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#if !defined(AFX_CHTEAMCOMPCNFG_H__1F04FF1E_7223_41FD_AAC3_E29FF3381A2A__INCLUDED_)
#define AFX_CHTEAMCOMPCNFG_H__1F04FF1E_7223_41FD_AAC3_E29FF3381A2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CHTeamCompCnfg.h : header file
//

#include "resource.h"
#include <Sports/CH/Data/CHTeamMatchsCnfg.h>

/////////////////////////////////////////////////////////////////////////////
// CHTeamCompCnfg dialog

class CHTeamCompCnfg : public CDialog
{
// Construction
public:
	CHTeamCompCnfg(CHTeamMatchsCnfg *pTMCnfg,CWnd* pParent = NULL,short id=0);   // standard constructor

	inline CHMemoryDataBase * mem()
	{ return (CHMemoryDataBase *)	((CCHManagerApp *)AfxGetApp())->memG(); }

	inline CHTeamMatchsCnfg* getTeamMatchsCnfg() const
	{ return pTeamMatchsCnfg; }

// Dialog Data
	//{{AFX_DATA(CHTeamCompCnfg)
	enum { IDD = IDD_DLG_TEAM_COMP_CONF };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHTeamCompCnfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	LRESULT OnEditChange(WPARAM wParam,LPARAM lParam);
	LRESULT OnClick(WPARAM wParam,LPARAM lParam);
	LRESULT OnDblClick(WPARAM wParam,LPARAM lParam);
	BOOL OnPaintGrid(UINT idGrid,GridItem *gi);

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHTeamCompCnfg)
	virtual BOOL OnInitDialog();
	afx_msg void    OnKeyDown (WPARAM wParam, LPARAM lParam);
	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void fillGridMatchs();
	void fillGricComboComp();
	void fillGricComboCompDbl();
	RWCString geCHxtCmbo(LPARAM lParam, WORD cmbo);
	void fillGridDescriptions();
	void fillGrdTeamCnfg();
	void paintLisCHeamMatchsCnfg(GridItem *gi);
	void enableRightPart(bool value);
	short getNewIdTeamMatchsCnfg();
	void inserCHeamMatchsCnfg(CHTeamMatchsCnfg *pInsTMCnfg);
	void removeTeamMatchsCnfg(CHTeamMatchsCnfg *pDelTMCnfg);
	int isPosibleDelete(short id);
	CHTeamMatchsCnfg *findTeamMatchsCnfg(short id);
	CHTeamMatchsCnfg *findTeamMatchsCnfg(CHTeamMatchsCnfg aTeamMatCnfg);

private:
	CGraphicWnd	* w;
	CHTeamMatchsCnfg *pTeamMatchsCnfg,*pTMCnfgEdit;
	CString teamMatchesType;
	CString teamCompA;
	CString teamCompZ;
	CString finalStr;
	CString NoneTxt;
	CString IndvTxt;
	CString DbleTxt;
	int matchSel;
	bool show;
	short idTeamCnfg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHTEAMCOMPCNFG_H__1F04FF1E_7223_41FD_AAC3_E29FF3381A2A__INCLUDED_)
