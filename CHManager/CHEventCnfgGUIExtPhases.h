/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHEventCnfgGUIExtPhases.h
*	Description	:
*
*	Author		:Chess Team
*	Date created:15-12-2005
* 	Project		:CH Manager
*	
***************************************************************************************/

#if !defined(AFX_CHEVENTCNFGGUIEXTPHASES_H__A82C6ECC_7ED9_47B4_A415_2F15B60FBB2F__INCLUDED_)
#define AFX_CHEVENTCNFGGUIEXTPHASES_H__A82C6ECC_7ED9_47B4_A415_2F15B60FBB2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class		CHPhase;

class CHEventCnfgGUIExtPhases : public CWnd
{
// Construction
public:
	CHEventCnfgGUIExtPhases(CWnd * pParent,CGraphicWnd * _w, int x1,int y1,int x2,int y2,CHEvent *pEvent);
	virtual ~CHEventCnfgGUIExtPhases();

	void		init						(int x1,int y1,int x2,int y2);
				
	void		onClick					(UINT idGrid,int x,int y,LPARAM lParam);		
	void		onDblClick					(UINT idGrid,int x,int y,LPARAM lParam);
	void		onLButtonDown				(UINT idGrid,int x,int y,LPARAM lParam);
				
	BOOL		onPaintGrid				(UINT idGrid,GridItem * gi);
				
	void		fillGridPhases();
	void		paintListPhases			(GridItem *gi);
	
	void		fillComboTypePhases();
	RWCString	getTypePhase(CHPhase *pPhase,short typePhase);
	void		showComboTypePhase(int x,int y,CHPhase *pPhase);
	void		selectPhase();

	void		changeOrderPhase(UINT idGrid,int x,int y,CHPhase *pPhase);
	void		savePhase(CHPhase *pPhase);

		
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHEventCnfgGUIExtPhases)
	//}}AFX_VIRTUAL

	
	//{{AFX_MSG(CHEventCnfgGUIExtPhases)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT onSelectEvent	(WPARAM wParam, LPARAM lParam);	//UM_SELECT_EVENT

private:
	RWCString		getTypeTie(CHPhase *pPhase,short typeTie=0);
	void			fillComboTypeTies();
	void			showComboTypeTie(int x,int y,CHPhase *pPhase);
	RWCString		getTypeMatchWinner(CHPhase *pPhase,short typeMatchWinner=0);
	void			fillComboTypeMatchWinner();
	void			showComboTypeMatchWinner(int x,int y,CHPhase *pPhase);
private:
	CHMemoryDataBase * mem();

	CGraphicWnd				*w;
	CWnd					*m_pParent;
	CHEvent					*m_pEvent;
	CHPhase					*m_pPhase;
	
	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHEVENTCNFGGUIEXTPHASES_H__A82C6ECC_7ED9_47B4_A415_2F15B60FBB2F__INCLUDED_)
