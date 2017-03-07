/*************************************************************************************
*	© Copyright MSL Software, S.L., 2001
*
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHCnfgTeamMembersDlg.h
*   Description	: 
*
*	Author		: Chess Team
*	Date created: 27-12-2005
* 	Project		:
*
***************************************************************************************/
#if !defined(AFX_CCHCNFGTEAMMEMBERSDLG_H__72E77A20_0A85_43CF_81E5_E25E9879F996__INCLUDED_)
#define AFX_CCHCNFGTEAMMEMBERSDLG_H__72E77A20_0A85_43CF_81E5_E25E9879F996__INCLUDED_



#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CHCnfgTeamMembersDlg.h : header file
//

#include "Resource.h"
#include <SYS\GR\GraphicWnd.h>
#include <Core\G\GSortedVector.h>
#include <Sports\CH\Data\CHMemoryDataBase.h>
#include <Sports\CH\Data\CHRegister.h>
#include <Sports\CH\Data\CHMatchMember.h>
#include <Sports\CH\Data\CHMatch.h>
#include <Sports\CH\Data\CHMember.h>


/////////////////////////////////////////////////////////////////////////////
// CCHCnfgTeamMembersDlg dialog

class CCHCnfgTeamMembersDlg : public CDialog
{
// Construction
public:
	CCHCnfgTeamMembersDlg(CHMemoryDataBase * pMemory, CHMatch *pMatch, CHMatchMember *pMatchMember, CWnd* pParent = NULL);   // standard constructor
	void fillListMembers();
	void paintMenbers(GridItem *gi);
	const CHMember *getSelMember()
	{ return pSelMember; }

// Dialog Data
	//{{AFX_DATA(CCHCnfgTeamMembersDlg)
	enum { IDD = IDD_CNFG_TEAMMEMBERS_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCHCnfgTeamMembersDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL DestroyWindow();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCHCnfgTeamMembersDlg)
		// NOTE: the ClassWizard will add member functions here
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	bool isMatchMember(CHMatch *pMatch,CHMember *pMember);

private:
	CGraphicWnd			* w;
	CHMemoryDataBase	* mMem;
	CHMatchMember		* pInMatchMember;
	CHMatch				* pInMatch;
	CHMember			* pSelMember;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CCHCNFGTEAMMEMBERSDLG_H__72E77A20_0A85_43CF_81E5_E25E9879F996__INCLUDED_)
