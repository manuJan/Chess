/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHFinalStandingsDlg.h
*	Description	: Interface for the CHFinalStandingsDlg class.
*
*	Author		: Chess Team
*	Date created: 16-01-2006
* 	Project		: CHManager
*	
* 	Modification history
*	By			: 
*	Date		: 
*	Changes		: 
*
***************************************************************************************/

#if !defined(AFX_CHFINALSTANDINGSDLG_H__07E4018B_3991_42B5_8E78_3CDA155B1E19__INCLUDED_)
#define AFX_CHFINALSTANDINGSDLG_H__07E4018B_3991_42B5_8E78_3CDA155B1E19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

class CHFinalStandingsDlg : public CDialog
{
public:
	CHFinalStandingsDlg(CWnd * pParent,CHEvent * pSelEvent);
	virtual ~CHFinalStandingsDlg();

private:
	GMedallist *		isMedallist(CHEventResult * pEventResult);

	void				fillMedalsCombo();
	void				fillComboQualitative();
	void				fillEventResultsGrid();
	void				fillEventResultsVector();

	void				editRank			(RWBoolean rankPo,CHEventResult * pEventResult,int column,int line);
	void				editMedalDate		(CHEventResult * pEventResult,int column,int line);
	void				editQualitative		(CHEventResult * pEventResult,int column,int line);
	void				editInitialRating	(CHInscription * pInscription,int column,int line);
	void				editPointsPoolResult(CHEventResult * pEventResult,int column,int line);
	void				editFinalRating		(CHEventResult * pEventResult,int column,int line);

	void				saveEventResult		(CHEventResult * pEventResult);
	void				saveInscription		(CHInscription * pInscription);
	void				savePoolResult		(CHPoolResult * pPoolResult);
	void				saveMedallist		(GMedallist * pMedallist);
	void				destroyMedallist	(GMedallist * pMedallist);
	void				generateMedallist	(CHEventResult * pEventResult,int medal);

	//{{AFX_DATA(CHFinalStandingsDlg)
	enum { IDD = IDD_DLG_STANDINGS };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CHFinalStandingsDlg)
	BOOL				PreTranslateMessage(MSG * pMsg);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CHFinalStandingsDlg)
	afx_msg BOOL		OnInitDialog    ();
	afx_msg void		OnSize          (UINT nType, int cx, int cy);
	afx_msg void		OnDblClick      (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT		OnPaintGrid     (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT		OnCursorOverGrid(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	CGraphicWnd	*		w;
	CHEvent *			pEvent;
	GSortedVector		vEventResults;
	CHMemoryDataBase *	m_pMem;
};

#endif // !defined(AFX_CHFINALSTANDINGSDLG_H__07E4018B_3991_42B5_8E78_3CDA155B1E19__INCLUDED_)
