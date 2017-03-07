/*************************************************************************************
*	© Copyright MSL Software, S.L., 2001
*
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHCnfgEventsFormView.h
*   Description	: CH Configuration of Events
*
*	Author		: Chess Team
*	Date created: 15-12-2005
* 	Project		: CH Manager
*
***************************************************************************************/

#if !defined(AFX_CHCnfgEventsFormView_H__F0D4164E_AAFB_4508_85D2_A374C2AC55BC__INCLUDED_)
#define AFX_CHCnfgEventsFormView_H__F0D4164E_AAFB_4508_85D2_A374C2AC55BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include <GUI\TH\GTHCnfgEventsFormView.h>
#include "CHProgression.h"
#include <Sports\CH\Data\CHMemoryDataBase.h>

class	CHEventCnfgGUIExtPhases;
class	CHEventCnfgGUIExtRank;
class	CHEventCnfgGUIExtRating;

class CCHCnfgEventsFormView : public GTHCnfgEventsFormView
{
protected:
	CCHCnfgEventsFormView(); // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CCHCnfgEventsFormView)
	
	RWBoolean canChangeModality(GTHEvent * pGTHEvent);
	BOOL	  onPaintGrid(UINT idGrid,GridItem *gi);

// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCHCnfgEventsFormView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	void init();
	void fillColInactiveEvents();
	GTHProgression* getTHProgression()
		{ return new CHProgression(mem()); }

	void paintListEvents(GridItem *gi); //paint for user
	void onClick (UINT idCtrl,LPARAM lParam);
	void onDblClick(UINT idGrid,int x,int y,LPARAM lParam);
	LRESULT onRButtonDown(WPARAM wParam, LPARAM lParam);
	void changeEventGridProperties();

	inline CHMemoryDataBase *mem() 
	{return (CHMemoryDataBase *)	((CCHManagerApp*)AfxGetApp())->memG();}

	
// Implementation
protected:
	virtual ~CCHCnfgEventsFormView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
	void		fillComboTypeEvents();
	void		fillComboTypeModes();
	RWCString	getTypeEvent(CHEvent *pEvent,short typeEvent=0);
	void		showComboTypeEvent(int x,int y,CHEvent *pEvent);
	RWCString	getTypeMode(CHEvent *pEvent,short typeMode=0);
	void		showComboTypeMode(int x,int y,CHEvent *pEvent);
	void		assignTeamConf(CHEvent* pEventAux,int nSelected);

	void		saveEvent(CHEvent *pEvent);
	void		selectEvent(CHEvent *pEvent);
private:
// Generated message map functions
//{{AFX_MSG(CCHCnfgEventsFormView)
	afx_msg LRESULT onCursorOverGrid(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT onEditChange(WPARAM wParam,LPARAM lParam);
//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CHEventCnfgGUIExtPhases  *m_pGUIExtPhases;
	CHEventCnfgGUIExtRank	 *m_pGUIExtRank;
	CHEventCnfgGUIExtRating	 *m_pGUIExtRating;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHCnfgEventsFormView_H__F0D4164E_AAFB_4508_85D2_A374C2AC55BC__INCLUDED_)
