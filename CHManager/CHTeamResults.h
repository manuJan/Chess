/*************************************************************************************
*	© Copyright MSL Software, S.L., 2001
*
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior wriCHen permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHTeamResults.h
*   Description	: 
*
*	Author		: Chess Team
*	Date created: 22-12-2005
* 	Project		:
*
***************************************************************************************/

#if !defined(AFX_CHTEAMRESULTS_H__59A174F4_684B_453C_B9DB_443BF5941C9F__INCLUDED_)
#define AFX_CHTEAMRESULTS_H__59A174F4_684B_453C_B9DB_443BF5941C9F__INCLUDED_

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
#include "CHStatusDlg.h"
#include "CHEvenControlOperations.h"

//////////////////////////////////////////////////////////////////////////////////////
// CH defines Manual Event Control 
//////////////////////////////////////////////////////////////////////////////////////

// Labels
#define LBL_STATUS_DLGT			 990
#define LBL_MATCH_CABT			1000
#define LBL_MATCHRESNAME1T		1001
#define LBL_MATCHRESNOC1T		1002	
#define LBL_MATCHRESNAME2T		1003
#define LBL_MATCHRESNOC2T		1004	
#define LBL_MATCH_RESULCH		1006
#define LBL_MATCH_TITLE			1007


// Fondos
#define IDBCK1T					1008
#define IDBCKCABGT				1009 
#define IDBBKYELLOWT			1010 
#define IDBCKBROWNT				1011 	
#define IDBBK2T					1012 	
#define IDBCK3T					1013 	
#define IDBCKBROWN2_DE			1014 	
#define IDBCKBROWN3_DE			1015 	
#define IDBCK4T					1016 
#define IDBCK5T					1017 
#define IDBCK6T					1018 
#define IDBCKBLACKT				1019 
#define IDBCK7T					1020 	
#define IDBCK17T				1021 
	
// Fonts					 
#define IDFNTBGT				1022 
#define IDFNTBOLDT				1023 	
#define IDFNTBIGT				1024 	
#define IDFNTBMGT				1025 
#define IDFNTXT					1026 
#define IDFNTBT					1027 
#define IDFNTBG1T				1028 
#define IDFNTBG2T				1029 
#define IDFNTNEWT				1030 
#define IDFNTGRID2T				1031 
#define FNTMED					1032


// Colores					 
#define IDCOL1T					1033 
#define COLORWHITET				1034 
#define IDBWHITET				1035 
#define BLUET					1036 
#define REDT					1037 
//#define IDCOL					1038 

// Frames					 
#define FRMMATCH_RESULT1T		1040 
#define FRMMATCH_RESULT2T		1041 	
								 
// Bitmap						
#define FLAG_HOMET				1050 
#define FLAG_AWAYT				1051 
#define BMP_CHECKT				1052
#define BMP_PREVIOUS_MA		    1053
#define BMP_NEXT_MA			    1054

// Edits
#define ED_MATCH1T				1060
#define ED_MATCH2T				1061

// BuCHons
#define BU_STATUST				1097
#define BU_FINISHT				1105

// Menus
#define	MENU_INCIDENCE1T		1110
#define	SUBMENU_INCIDENCE11T	1111
#define	SUBMENU_INCIDENCE12T	1112
#define	SUBMENU_INCIDENCE13T	1113
#define	SUBMENU_INCIDENCE14T	1114
#define	SUBMENU_INCIDENCE15T	1115
#define	SUBMENU_INCIDENCE16T	1116
#define	SUBMENU_INCIDENCE17T	1117
#define	MENU_INCIDENCE2T		1118
#define	SUBMENU_INCIDENCE21T	1119
#define	SUBMENU_INCIDENCE22T	1120
#define	SUBMENU_INCIDENCE23T	1121
#define	SUBMENU_INCIDENCE24T	1122
#define	SUBMENU_INCIDENCE25T	1123
#define	SUBMENU_INCIDENCE26T	1124
#define	SUBMENU_INCIDENCE27T	1125 

// Grids
#define GR_SUBMATCH				1130
// Grids
#define CH_OFFICIAL_T			1140

// Medidas de las celdas
#define INIXT			     10
#define INIYT				 55
#define NAME_WIDTHT			140
#define NOC_WIDTHT		     30
#define PLAYERS_WIDTHT	    170
#define SERVICE_WIDTHT		 30
#define AFTER_RESULT	    265 // NOC+PLAYERS+NAME


#define CELL_HEIGHCH         18 // Alto de cada celda
#define	WIDTH_SUMT			 18 // Ancho de los botones de suma y resta
#define WIDTH_SCH			 75 // Ancho de los botones de Start, Finish

#define GRID_WIDTH_3T         75
#define GRID_WIDTH_5T         45
#define GRID_WIDTH_7T         33


class CHTeamResults : public CDialog
{
// Construction
public:
	enum type  { eSplit=0   , eMatch=1};

	CHTeamResults(CWnd* pParent,CHMatch *pSelMatch);   // standard constructor
	
// Dialog Data

	//{{AFX_DATA(CHTeamResults)
	enum { IDD = IDD_TEAM_RESULTS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHTeamResults)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHTeamResults)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	LRESULT onClick(WPARAM wParam, LPARAM lParam);
	void onContexMenu(LPARAM lParam, size_t id);
	void onOK();
	void OnKeyDown(WPARAM wParam, LPARAM lParam);
	BOOL onPaintGrid(UINT idGrid,GridItem *gi);
	void onLButtonDown (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT onDblClick(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT onRButtonDown(WPARAM wParam, LPARAM lParam);
	

private:
	inline CHMemoryDataBase *mem() 
	{
		return (CHMemoryDataBase *) ((GManagerInterfaceApp*)AfxGetApp())->memG(); 
	}
	RWCString putStatus();
	void disableEnableControls(RWBoolean enable);
	void paintMatch();
	void paintMatchStatus();
	void saveAll();
	void onQualitativeMenu1(GQualitative *pQualitative);
	void onQualitativeMenu2(GQualitative *pQualitative);
	void paintResults();
	void paintMatchResultHome(short widthCell);
	void paintMatchResultAway(short widthCell);
	void clearResults(CHMatch *pMatchAux);
	void fillSubMatches();
	void createTypeResults();
	void createTypeResultsPress();

	void paintListScheduledMatches(GridItem *gi);
	void changeBackButton(short button);
	void paintQualitatives();
	void paintMatchResult();
	void paintScore();
	void changePress();
	
	// Menu Type Results
	void onCreateMenuResults(LPARAM lParam, CHMatch *pMatch);
	void onResultsMenu(LPARAM lparam);

	// Menu Type Colors
	void onCreateMenuColors(LPARAM lParam, CHMatchResult *pMatchResult);
	void onColorsMenu(LPARAM lparam);

	short getEventFromButton(short button);

	void finishMatch(CHMatch *pMatchAux);
	void nextMatch();
	CHMatch *getPreviousResult();
	CHMatch *getNextResult();
	void	paintAll();
	void	paintFlags();

public:
	CGraphicWnd *w;
	CHMatch *pMatch ;
	CHMatchResult	*pMatchResult1;
	CHMatchResult	*pMatchResult2;
	CHStatusManager *pStatusMngt;
	CBitmap			* m_pBmpFlag[4];
	CHEvenControlOperations    eventControlOp;
	short			posX;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHTEAMRESULTS_H__59A174F4_684B_453C_B9DB_443BF5941C9F__INCLUDED_)
