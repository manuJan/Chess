/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHProgressionFormView.h
*   Description	:
*
*	Author		: CH Team
*	Date created: 15-Nov-2004
* 	Project		: CHManager
*	
* 	Modification history
*	By		: 
*	Date	: 
*	Changes	: 
*
***************************************************************************************/


#if !defined(AFX_CHPROGRESSIONFORMVIEW_H)
#define AFX_CHPROGRESSIONFORMVIEW_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <gui\th\GTHProgressionFormView.h>
#include "CHProgression.h"
#include "CHEvenControlOperations.h"

#include  <sports\CH\Data\CHMemoryDataBase.h>

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif



class CHProgressionFormView : public GTHProgressionFormView
{
protected:
	CHProgressionFormView();           // protected constructor used by dynamic creation
	virtual ~CHProgressionFormView();
	DECLARE_DYNCREATE(CHProgressionFormView)

	inline CHMemoryDataBase *mem() 
	{
		CCHManagerApp * pApp=(CCHManagerApp*)AfxGetApp();
		return (CHMemoryDataBase *)	pApp->memG();
	}


	GTHProgression* getTHProgression(){ return new CHProgression(mem());}

	void deleteMatch(GTHMatch * pDelMatch);
	void setDataOnMatchResult(GTHMatchResult * pMatchResult,GTHPoolResult * pPoolResult);	

public:

	void init();
	void onDblClick(UINT idGrid,int x,int y,LPARAM lParam);
	void onClick(UINT idCtrl,LPARAM lParam);
	LRESULT onCursorOverGrid(WPARAM wParam, LPARAM lParam);	
	
	void assignPhaseInfoDlg();	
	bool canInsertProgressMatch(GTHMatch * pMatch);

	BOOL onPaintGrid(UINT idGrid,GridItem *gi);

	void paintMyListMatches(UINT idGrid,GridItem *gi);
	void paintMyListPooles(UINT idGrid,GridItem *gi) ;
	void paintResult(GridItem * gi,CHMatchResult * pMatchResult);
	void paintListMatchesTeam(GridItem *gi);
	void paintMyMatchResult(GridItem *gi, GTHMatchResult *pMatchResult);

	RWCString getMyMatchResultDescription(GTHMatchResult *pMatchResult);

	void onReportRequest   (CReportItem    *pItem);
	bool onReportGeneration(CReportManager *pReportMngr,CReportConfig *pReportCfg,CReportItem *pItem);

	short getEventFromMenu(short menu);

protected:

	void changeUserTreeSelection();
	void setTreeDescription();

	void onClickButChangeTeams();
	void onClickButSummary();
	void onClickButDraw();
	void onClickButAssign();
	void onClickButRemove();
	
	bool canDeletePhase(GTHPhase* pPhase);
	bool canDeletePool(GTHPool* pPool);
	bool canDeleteMatch(GTHMatch* pMatch);
	bool canChangePoolResult(GTHPoolResult* pPoolResult, int row);
	
	bool checkDBThread();
	void fillComboCompetitor(int idGrid, GTHPool * pPool);

	// Generated message map functions
	//{{AFX_MSG(CHProgressionFormView)
		// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg LRESULT onRButtonDown(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	GTHPhase* insertPhase();
	GTHPool* insertPool(RWBoolean isRealPool=true);
private:
	bool lockMatch(CHMatch *pMatch);
	void unLockMatch();
	// Menu Results
	void onCreateMenuResults(LPARAM lParam, CHMatch *pMatch);
	void onResultsMenu(LPARAM lparam);

	// Menu Type Colors
	void onCreateMenuColors(LPARAM lParam, CHMatchResult *pMatchResult);
	void onColorsMenu(LPARAM lparam);
	
	// Update PoolResults
	void editRank(int idGrid,CHPoolResult * pPoolResult,int column,int line);
	void editSeed(int idGrid,CHPoolResult * pPoolResult,int column,int line);
	void editRating(int idGrid,CHPoolResult * pPoolResult,int column,int line);
	void onQualitativeMenu(GQualitative *pQualitative);
	void editMatches(int idGrid,CHPoolResult * pPoolResult,int column,int line);
	void editPoints(int idGrid,CHPoolResult * pPoolResult,int column,int line);
	void fillReports();
	void clearResults(CHMatch *pMatch);
	

private:
	RWCString		lastMatchLocked;
	short			posX;
	CHEvenControlOperations		eventControlOp;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHPROGRESSIONFORMVIEW_H)
