/*************************************************************************************
*	© Copyright MSL Software, S.L., 2001
*
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHCnfgTeamSchedule.h
*   Description	: 
*
*	Author		: Chess Team
*	Date created: 27-12-2005
* 	Project		:
*
***************************************************************************************/

#if !defined(AFX_CHCNFGTEAMSCHEDULE_H__59A174F4_684B_453C_B9DB_443BF5941C9F__INCLUDED_)
#define AFX_CHCNFGTEAMSCHEDULE_H__59A174F4_684B_453C_B9DB_443BF5941C9F__INCLUDED_

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
#include <sports/CH/data/CHMatchMember.h>
#include <sports/CH/data/CHSession.h>
#include "CHManualEventControl.h"
#include "CHEvenControlOperations.h"
class CHMember;

class CHCnfgTeamSchedule : public CDialog
{
// Construction
public:
	enum typeMatchResult { eHome=0, eAway=1 } ;

	CHCnfgTeamSchedule(CWnd* pParent,GSortedVector vMatches,int index);   // standard constructor
	
// Dialog Data

	//{{AFX_DATA(CHCnfgTeamSchedule)
	enum { IDD = IDD_CNFG_TEAM_SCHEDULE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHCnfgTeamSchedule)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHCnfgTeamSchedule)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	LRESULT onClick(WPARAM wParam, LPARAM lParam);
	void	onDblClick(WPARAM wParam, LPARAM lParam);
	LRESULT onGridDrag(WPARAM wParam,LPARAM lParam);	
	void	onGridDrop(WPARAM wParam,LPARAM lParam);	
	LRESULT onSelectMatchMember(WPARAM wParam, LPARAM lParam);
	LRESULT onChangeMatch(WPARAM wParam, LPARAM lParam);
	void	OnKeyDown(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT onRButtonDown(WPARAM wParam, LPARAM lParam);
	void paintHeadMatch();
	void showHeadMatch();
	void showSubMatches();
	void paintStatus();	
	void onOK();
	void changeStatus();

	void outMatch(CHMatch *pMatch);
	void fillSubMatches();
	void paintListScheduledMatches(GridItem *gi);
	BOOL onPaintGrid   (UINT idGrid,GridItem *gi);
	void onGridDropMemberToMatchMember(DragDropItem *dd, int lineDrop,short num);
	void onGridDropMatchMemberToMember(DragDropItem *dd,short num);
	void onGridDropMatchMemberToMatchMember(DragDropItem *dd, int lineDrop,short num);
	RWBoolean	inMatchMember(CHMember *pMember,short num);
	void		disableEnableControls(RWBoolean enable);

		

private:
	inline CHMemoryDataBase *mem() 
	{
		return (CHMemoryDataBase *) ((GManagerInterfaceApp*)AfxGetApp())->memG(); 
	}
	
	RWBoolean		registersInMatch(CHMatch *pMatchAux);
	void			editMatch (int col, int lin);
	void			showComboSessions(int x, int y);
	void			showComboCourts(int x, int y);
	void			setStartTimes();
	void			showTeamAssignation();
	void			fillMatchMembersTeam(short num);
	void			paintMatchMembers(GridItem *gi);
	void			fillMembersTeam(short num);
	void			paintMembers(GridItem *gi);
	void			setMatchMembers();
	void			setMatchNumberCode(short type,CHMatchResult *pMatchResult,CHTeamMatchsCnfg *pTeamMatchCnfg,short numMatch);
	CHMatchMember*  getTeamMatchMember(short homeAway,short number);
	bool			lockMatch(CHMatch *pMatch);
	void			unLockMatch();
	void			paintTeamResult();
	void			clearResults(CHMatch *pMatchAux);
	void			onColorsMenu(LPARAM lparam);
	void			onCreateMenuColors(LPARAM lParam, CHMatchResult *pMatchResult);

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
	RWCString			lastMatchLocked;
	CHEvenControlOperations    eventControlOp;
	short posX;
	GSortedVector vSortMatches;
	int matchSel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHCNFGTEAMSCHEDULE_H__59A174F4_684B_453C_B9DB_443BF5941C9F__INCLUDED_)
