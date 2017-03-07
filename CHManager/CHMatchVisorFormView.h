/*************************************************************************************
*			© Copyright MSL Software, S.L., 2001
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior LBitten permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHMatchVisorFormView.h
*	Description	:
*
*	Author		: CH Team
*	Date created: 27-12-2005
* 	Project		: CH Manager
*	
* 	Modification history
*	By		: 
*	Date	: 
*	Changes	: 
*
***************************************************************************************/
#if !defined(AFX_CHMATCHVISORFORMVIEW_H__CF70FCF0_6D95_4CFB_8B21_040879D17099__INCLUDED_)
#define AFX_CHMATCHVISORFORMVIEW_H__CF70FCF0_6D95_4CFB_8B21_040879D17099__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <GUI/GMI/GManagerInterface.h>

#include <Sports/CH/Data/CHMemoryDataBase.h>
#include <Reports/V/GDay.h>
#include <rw/colltime.h>

class CHMatch;
class CHMatchVisorFormView : public CManagerFormView  
{
public:
	virtual void init();
	virtual BOOL exit();
	DECLARE_DYNCREATE(CHMatchVisorFormView);

	void trnNotification(CPackTransaction *pt);

	CHMatchVisorFormView();
	virtual ~CHMatchVisorFormView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	//{{AFX_VIRTUAL(CHMatchVisorFormView)
	protected:
		LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CHMatchVisorFormView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	inline CHMemoryDataBase *mem()
		{ return (CHMemoryDataBase *)((GManagerInterfaceApp *)AfxGetApp())->memG(); }

protected:		// Functions
	BOOL onPaintGrid   (UINT idGrid,GridItem *gi);			

private:
		void createChksForStatus();

		GDay			  * getSelectedDay		() const;
		CHSession		  * getSelectedSession	() const;
		RWCollectableTime * getSelectedStartTime() const;
		CHCourt			  *	getSelectedCourt	() const;
		short				getSelectedRound	() const;

		void fillComboDays		();
		void fillComboSession	();
		void fillComboStartTime	();
		void fillComboCourt		();
		void fillComboRound		();

		void selectOnCombo(int idCtrl,int steep);
		
		void insertDay			(RWDate & aDate);
		void fillGridMatches	();
		void orderGridMatches	();
		void paintTotalMatches	();
		void paintListMatches	(GridItem *gi);
		int findColorStatus		(unsigned char status,RWBoolean useDefault=false);
		int	findColorStatusEnd	(unsigned char status,RWBoolean useDefault=false);
		int findColorSetStatus	(unsigned char status);
		RWBoolean findStartTime	(RWCString aTime);

		void paintListCourt				(GridItem *gi,RWCString strIDColumn,CHMatch *pMatch);
		void paintListRound				(GridItem *gi,RWCString strIDColumn,CHMatch *pMatch);
		void paintListDateAndTime		(GridItem *gi,RWCString strIDColumn,CHMatch *pMatch);
		void paintListMatchDescription	(GridItem *gi,RWCString strIDColumn,CHMatch *pMatch);
		void paintListStatus			(GridItem *gi,RWCString strIDColumn,CHMatch *pMatch);
		void paintListSession			(GridItem *gi,RWCString strIDColumn,CHMatch *pMatch);
		void paintListMatchResults		(GridItem *gi,RWCString strIDColumn,CHMatch *pMatch);
		void paintListResult			(GridItem *gi,RWCString strIDColumn,CHMatch *pMatch);
		bool checkForStatus				(unsigned char status);
		RWBoolean matchAccepted			(CHMatch * pMatch);
		CHMatch * findmatchExist();
		
		LRESULT onClickHeader(WPARAM wParam,LPARAM lParam);
		void	onClick(UINT idCtrl,LPARAM lParam);
		void	OnKeyDown(WPARAM wParam, LPARAM lParam);
		RWBoolean registersInMatch(CHMatch *pMatch);
		bool	lockMatch(CHMatch *pMatch);
		void	unLockMatch();
private:
		RWSet			colDays;
		RWSet			colStartTimes;
		bool			showSpecial;

		PFN_ORDER_FC	orderGrid;
		RWCString		lastMatchLocked;
};

#endif // !defined(AFX_CHMATCHVISORFORMVIEW_H__CF70FCF0_6D95_4CFB_8B21_040879D17099__INCLUDED_)
