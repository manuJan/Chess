/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHStatusDlg.h
*	Description	: Interface for the CHStatusDlg class.
*
*	Author		: CH Team
*	Date created: 21-12-2005
* 	Project		: CHManager
*	
* 	Modification history
*	By			: 
*	Date		: 
*	Changes		: 
*
***************************************************************************************/

#if !defined(AFX_CHSTATUSDLG_H__0243F2F2_BAB3_4EED_9F0C_2CA9C2F98D7D__INCLUDED_)
#define AFX_CHSTATUSDLG_H__0243F2F2_BAB3_4EED_9F0C_2CA9C2F98D7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include "CHStatusManager.h"

class CGraphicWnd;
class CHMatch;
class CHMemoryDataBase;

class CHStatusDlg : public CDialog  
{
public:
	CHStatusDlg(CWnd * pParent,CHMatch * _pMatch);
	inline unsigned char getStatus() const
	{	return status;	}
	
	bool hasChanges();
	inline unsigned char getStartList() const
	{	return startList;	}
	

private:
	CHMemoryDataBase * mem();

	//{{AFX_DATA(CHStatusDlg)
	enum { IDD = IDD_DLG_STATUS };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHStatusDlg)
	BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CHStatusDlg)
	afx_msg BOOL OnInitDialog();
	afx_msg BOOL OnDestroy();
	afx_msg void OnClick(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	void onOK() ;
	void saveMatch(CHMatch * pMatch);

private:
	CWnd		* pTheParent;
	CHMatch     * pMatch;
	CGraphicWnd	* w;
	unsigned char status;
	RWBoolean changed,startList;
	CHStatusManager *pStatusMngt;
	
};

#endif // !defined(AFX_CHSTATUSDLG_H__0243F2F2_BAB3_4EED_9F0C_2CA9C2F98D7D__INCLUDED_)
