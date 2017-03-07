/*************************************************************************************
*			© Copyright MSL Software, S.L., 2001
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:	CHScheduleFormView.h
*	Description	:   Table Tennis Schedule
*
*	Author		:	Fernando Garcia
*	Date created:   27-Mayo-2002
* 	Project		:	Table Tennis Manager
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#if !defined(AFX_CHSCHEDULEFORMVIEW_H__4F0774B7_7635_4C04_8DC7_5DB67DF03706__INCLUDED_)
#define AFX_CHSCHEDULEFORMVIEW_H__4F0774B7_7635_4C04_8DC7_5DB67DF03706__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include <GUI/TH/GTHScheduleFormView.h>
#include <sports/CH/data/CHMemoryDataBase.h>
#include <SPORTS/CH/Data/CHInscription.h>
#include "CHStatusManager.h"


class CHScheduleFormView : public GTHScheduleFormView
{
protected:
	CHScheduleFormView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CHScheduleFormView)

	RWWString getAvailableMatchDescription(GTHMatch* pMatch);
	RWWString getMatchDescription(GTHMatch* pMatch);
	
	bool	canChangeMatchSession(GTHMatch* pMatch,int column);
	bool	canChangeMatchNumber(GTHMatch* pMatch, int matchNumber);
	bool	canChangeCourt(GTHMatch* pMatch, GCourt* pNewCourt);
	bool	canChangeSession(GTHMatch* pMatch, GTHSession* pNewSession);
	bool	canConfigureMatch(GTHMatch *pMatch);
	bool	canDesconfigureMatch(GTHMatch *pMatch);
	void	deAssignScheduledData(CHMatch *pSubMatch);
	void	DeassignEventData(GTHEvent* pEvent);

	BOOL	updateAllBefore() {return false;} 
	RWWString getCourtDescription(GCourt* pCourt);
	bool	canChangeMatchDate(GTHMatch* pMatch, RWDate newDate);
	bool	canChangeMatchTime(GTHMatch* pMatch, RWTime time);
	RWSet* getFilterMatches(GScheduleDay* pDay = 0, GVenue * pVenue = 0, GCourt* pCourt = 0, GTHSession * pSession = 0);
	RWCString getComposeDescription(CHMatch *pMatch);

	// V i r t u a l    m e t h o d s   R e p o r t s
	void onReportRequest(CReportItem    *pItem);
	bool onReportGeneration(CReportManager *pReportMngr,CReportConfig *pReportCfg,CReportItem *pItem);
	void propagateMatchDateTime(GTHMatch* pMatch);

public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHScheduleFormView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	//void trnNotification(CPackTransaction *pt);
	void init();

	GTHStatusManager* onCreateStatusManager()
	{ return new CHStatusManager();}

	void fillReports();
	void onClick(UINT idCtrl,LPARAM lParam);
	void onDblClick(UINT idGrid,int x,int y,LPARAM lParam);
	void paintGridSession(GridItem *gi);
	BOOL onPaintGrid(UINT idGrid,GridItem *gi);

	// Virtual and asociated filtering methods
	bool canInsertAvailableMatch(GTHMatch* pMatch);
	bool canInsertSelectedMatch(GTHMatch* pMatch);
	bool canInsertScheduledMatch(GTHMatch* pMatch);
      	  
private:
	inline CHMemoryDataBase *mem() 
	{ return (CHMemoryDataBase *) ((CCHManagerApp*)AfxGetApp())->memG();}
   
	bool lockMatch(CHMatch *pMatch);
	void unLockMatch();
	void AssignUserData(GTHMatch *pMatch);
	LRESULT   onDeleteSession(WPARAM wParam, LPARAM lParam);
	RWBoolean matchHaveJudges(CHMatch *pMatch);
	RWBoolean thereAreQualitative(CHMatch *pMatch);
	RWCString getResultIncidence(CHMatch *pMatch);
	void assignScheduledData(CHMatch *pMatch,CHMatch *pSubMatch);
	void outMatch(CHMatch *pMatchAux);
	void fillStatus();
	RWBoolean correctStatus(GTHMatch* pMatch);
	RWBoolean correctTable(GTHMatch* pMatch);
	RWBoolean correctRound(GTHMatch* pMatch);
	RWBoolean registersInMatch(CHMatch *pMatch);
	void fillComboOwn();
	void fillComboCourtsOwn(GVenue* pVenue);
	void fillRound();

// Implementation
protected:
	virtual ~CHScheduleFormView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CHScheduleFormView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	RWCString		lastMatchLocked;
	GSortedVector	gsvAvailableDates;
	GSortedVector	vAvailablesMatches;
	GSortedVector	aReportEvents;
	GSortedVector	vAvailablesPooles;
	GSortedVector	vAvailablesPoolesPhase;
	int             subMenu;
	bool			isConsolation;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHSCHEDULEFORMVIEW_H__4F0774B7_7635_4C04_8DC7_5DB67DF03706__INCLUDED_)
