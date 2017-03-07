/*************************************************************************************
*			© Copyright MSL Software, S.L., 2001
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHPhasesDlg.h
*   Description	: CH Phases Dialog
*
*	Author		: Chess Team
*	Date created: 15-12-2005
* 	Project		: CH Manager
* 	Modification  history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#if !defined(AFX_CHPhasesDlg_H__EFFF0380_3678_4DC8_85CA_A766E2C747FA__INCLUDED_)
#define AFX_CHPhasesDlg_H__EFFF0380_3678_4DC8_85CA_A766E2C747FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CHPhasesDlg.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CHPhasesDlg dialog
class CHPhaseBase;

class CHPhasesDlg : public CDialog
{
// Construction
public:
	CHPhasesDlg(CWnd* pParent = NULL, CHPhase* pPhase = NULL);   // standard constructor

	afx_msg LRESULT onDblClick(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT onPaintGrid(WPARAM wParam, LPARAM lParam);

	void fillListPhasesBase();
	void fillListPhases();
	void fillLanguagesList();
	void fillComboTypePhases();
	void fillComboStatus();
	void showComboTypePhase(int x,int y,CHPhaseBase *pPhaseBaseAux);
	void showComboTypePhase(int x,int y,CHPhase *pPhaseAux);
	void showComboStatus(int x,int y,CHPhase *pPhaseAux);
	void paintPhasesBase(GridItem* gi);
	void paintPhases(GridItem* gi);
	void paintListLanguages(GridItem *gi);
	
	inline CHMemoryDataBase * mem()
	{ return (CHMemoryDataBase *) ( (CCHManagerApp *)AfxGetApp() )->memG(); }


// Dialog Data
	//{{AFX_DATA(CHPhasesDlg)
	enum { IDD = IDD_PHASES_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHPhasesDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHPhasesDlg)
	virtual BOOL OnInitDialog();
	afx_msg void    OnKeyDown (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT onClick(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void		savePhaseBase(CHPhaseBase *pPhaseBaseAux);
	void		savePhase(CHPhase *pPhaseAux);
	void		createGrid();
	RWCString	getTypePhase(CHPhaseBase *pPhaseBaseAux=NULL, short typePhase=0);
	void		selecGrid();
	void		paintCartel();
	RWBoolean	saveCreateEvent();
private:
	CGraphicWnd*	w;
	CHPhase*		pPhase;
	CHPhaseBase*	pPhaseBase;
	GLanguage  *    pLanguage;
	RWBoolean		description;
	RWBoolean		allPhases;
	RWBoolean		phaseBase;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHPhasesDlg_H__EFFF0380_3678_4DC8_85CA_A766E2C747FA__INCLUDED_)
