/*************************************************************************************
*	© Copyright MSL Software, S.L., 2001
*
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHManualEventControl.h
*   Description	: 
*
*	Author		: Chess Team
*	Date created: 21-12-2005
* 	Project		:
*
***************************************************************************************/

#if !defined(AFX_CHMANUALEVENTCONTROL_H__59A174F4_684B_453C_B9DB_443BF5941C9F__INCLUDED_)
#define AFX_CHMANUALEVENTCONTROL_H__59A174F4_684B_453C_B9DB_443BF5941C9F__INCLUDED_

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

#define LBL_STATUS_DLG			 990
#define LBL_MATCH_CAB			1000
#define LBL_MATCHRESNAME1		1001
#define LBL_MATCHRESNOC1		1002	
#define LBL_MATCHRESNAME2		1003
#define LBL_MATCHRESNOC2		1004	
#define LBL_MATCH_RESULT		1006
#define BU_COLOR_HOME			1007
#define BU_COLOR_AWAY			1008


// Fondos
#define IDBBKYELLOW_DE			1010 
#define IDBCKBROWN2_DE			1014 	
#define IDBCKBROWN3_DE			1015 	
#define IDBCKBLACK_DE			1019 
#define IDB_CK1_M				1020
#define IDB_CK2_M				1021

// Fonts					 
#define IDFNTBG_DE				1022 
#define IDFNTBOLD_DE			1023 	
#define IDFNTX_DE				1026 
#define IDFNTB_DE				1027 
#define IDFNTBG1_DE				1028 
#define IDFNTNEW_DE				1030 
#define IDFNTGRID2_DE			1031 
#define IDFNTGRID_BIG			1032
#define IDFNTGRID2_MEDIUM		1033
#define IDFNTBG2_DE				1034



// Colores					 
#define BLUE_DE					1035 
#define RED_DE					1036 

// Frames					 
#define FRMMATCH_RESULT1		1040 
#define FRMMATCH_RESULT2		1041 

								 
// Bitmap						
#define FLAG_HOME				1050 
#define FLAG_AWAY				1051 
#define BMP_CHECK_DE		    1052
#define BMP_SAVE			    1053
#define BMP_PREVIOUS_M		    1054
#define BMP_POINT_M			    1055
#define BMP_NEXT_M			    1056


// Edits
#define ED_MATCH1				1060
#define ED_MATCH2				1071

// Menus
#define	MENU_INCIDENCE1			1130
#define	SUBMENU_INCIDENCE11		1131
#define	SUBMENU_INCIDENCE12		1132
#define	SUBMENU_INCIDENCE13		1133
#define	SUBMENU_INCIDENCE14		1134
#define	SUBMENU_INCIDENCE15		1135
#define	SUBMENU_INCIDENCE16		1136
#define	SUBMENU_INCIDENCE17		1137
#define	MENU_INCIDENCE2			1138
#define	SUBMENU_INCIDENCE21		1139
#define	SUBMENU_INCIDENCE22		1140
#define	SUBMENU_INCIDENCE23		1141
#define	SUBMENU_INCIDENCE24		1142
#define	SUBMENU_INCIDENCE25		1143
#define	SUBMENU_INCIDENCE26		1144
#define	SUBMENU_INCIDENCE27		1145 

// Grids
#define	LST_MATCHES				1150 



// Medidas de las celdas
#define INIX			     10
#define INIY				 55
#define NAME_WIDTH			140
#define NOC_WIDTH		     30
#define PLAYERS_WIDTH	    170
#define SERVICE_WIDTH		 30

#define CELL_WIDTH			 70 // Ancho de cada celda
#define CELL_HEIGHT          18 // Alto de cada celda
#define	WIDTH_SUM			 18 // Ancho de los botones de suma y resta
#define WIDTH_ST			 75 // Ancho de los botones de Start, Finish

#define INTERVAL_WIDTH	      15
#define TOTAL_WIDTH	         270
#define WIDTH_CELL	          80
#define WIDTH_BUTTON		  50	

#define BLUE_COLOR				RGB( 50, 50,200)
#define RED_COLOR				RGB(250, 50, 50)

class CHManualEventControl : public CDialog
{
// Construction
public:
	
	CHManualEventControl(CWnd* pParent,CHMatch *pSelMatch);   // standard constructor
	
// Dialog Data

	//{{AFX_DATA(CHManualEventControl)
	enum { IDD = IDD_MANUAL_EVENT_CONTROL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHManualEventControl)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHManualEventControl)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	LRESULT onClick(WPARAM wParam, LPARAM lParam);
	void onLButtonDown  (WPARAM wParam, LPARAM lParam);
	BOOL onPaintGrid(UINT idGrid,GridItem *gi);
	void onContexMenu(LPARAM lParam, size_t id);
	void onOK();
	void OnKeyDown(WPARAM wParam, LPARAM lParam);
	LRESULT onDblClick(WPARAM wParam, LPARAM lParam);
			
	
private:
	inline CHMemoryDataBase *mem() 
	{
		return (CHMemoryDataBase *) ((GManagerInterfaceApp*)AfxGetApp())->memG(); 
	}
	RWCString	putStatus();
	void		disableEnableControls(RWBoolean enable);
	void		paintMatchStatus();
	void		saveAll(RWBoolean status=true);
	void		onQualitativeMenu1(GQualitative *pQualitative);
	void		onQualitativeMenu2(GQualitative *pQualitative);
	void		paintResults();
	void		paintMatchResultHome();
	void		paintMatchResultAway();
	void		doEditFormat();
	void		paintMatchResult();
	void		clearResults();
	void		calculateAll();
	void		createTypeResults();	
	void		createPressTypeResults();
	void		createGridBeforeAfter();
	void		changeBackButton(short button);		
	void		fillGrid();
	void		paintScore();
	void		paintQualitatives();
	void		changePress();
	CHMatch *	getPreviousResult();
	CHMatch *	getNextResult();
	void		paintHome();
	void		paintAway();
	void		paintAll();
	void		paintColors();
	void		changeSelectionMatches();
	void		finishMatch(CHMatch *pMatch);

	short		getEventFromButton(short button);

public:
	CGraphicWnd *w;
	CHMatch *pMatch;
	CHMatchResult	*pMatchResult1;
	CHMatchResult	*pMatchResult2;
	CHStatusManager *pStatusMngt;
	short			posX, posY;
	CBitmap			* m_pBmpFlag[4];
	CHEvenControlOperations		eventControlOp;
	RWBoolean		poolMatches;
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHMANUALEVENTCONTROL_H__59A174F4_684B_453C_B9DB_443BF5941C9F__INCLUDED_)
