/*************************************************************************************
*	© Copyright MSL Software, S.L., 2001
*
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior wriCHen permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHTeamResults.cpp
*   Description	: 
*
*	Author		: Chess Team
*	Date created: 22-12-2005
* 	Project		:
*
***************************************************************************************/

#include "stdafx.h"
#include "CHmanager.h"
#include "CHTeamResults.h"
#include "CHRanking.h"
#include "CHProgression.h"
#include "CHDefines.h"
#include <GUI/FLAGS/flags.h>
#include <core/G/GMsgDefines.h>
#include <core/TH/GTHMsgDefines.h>
#include <sports/CH/data/CHMsgDefines.h>
#include <sports/CH/data/CHMatchMember.h>
#include <sports/CH/data/CHStatisticDefines.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define		LBL_OKT			 1000
#define		IDBACKGT		 1001

extern CCHManagerApp theApp;

CHTeamResults::CHTeamResults(CWnd* pParent /*=NULL*/,CHMatch *pSelMatch)
:CDialog(CHTeamResults::IDD, pParent)
,pMatch(pSelMatch)
,pMatchResult1(0)
,pMatchResult2(0)
,eventControlOp((CHMemoryDataBase*)mem())
,posX(0)
{
 	pStatusMngt = new CHStatusManager();
	if(pMatch)
	{
		GSortedVector & vCompetitors =pMatch->getCompetitorsVector();
		
		if(vCompetitors.entries()==2)
		{
		    pMatchResult1=(CHMatchResult*)vCompetitors[0]->getElement();
			pMatchResult2=(CHMatchResult*)vCompetitors[1]->getElement();
		}
		
	}
	m_pBmpFlag[0]=new CBitmap();
    m_pBmpFlag[1]=new CBitmap();
	m_pBmpFlag[2]=new CBitmap();
    m_pBmpFlag[3]=new CBitmap();

	//{{AFX_DATA_INIT(CHTeamResults)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CHTeamResults::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHTeamResults)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHTeamResults, CDialog)
	//{{AFX_MSG_MAP(CHTeamResults)
	ON_MESSAGE(UM_CLICK,onClick)
	ON_MESSAGE(UM_CONTEX_MENU,onContexMenu)		
	ON_MESSAGE(UM_KEYDOWN, OnKeyDown)
	ON_MESSAGE(UM_PAINTGRID,onPaintGrid)
	ON_MESSAGE(UM_LBUTDOWN, onLButtonDown)
	ON_MESSAGE(UM_DBLCLICK, onDblClick)
	ON_MESSAGE(UM_RBUTDOWN, onRButtonDown)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CHTeamResults::OnInitDialog() 
{
	w = new CGraphicWnd(this);
	INITW(w);

	//w->destroyBackground (IDBACKGT);
	//w->addBackgroundColor(IDBACKGT,RGB(240,240,250));
	//w->setBackground (IDBACKGT);	
	w->addBackgroundColor(IDBBKYELLOWT,RGB(255,255,207));
	//w->addBackgroundColor(IDBCK ,RGB(240,240,250));
	w->addBackgroundColor(IDBCK2,RGB(209,209,209));
	w->addBackgroundColor(IDBCK7T,RGB(167,167,165));
	
	w->addColorSet		 (IDCOL,0                ,COLOR_DEFAULT_OFF,COLOR_DEFAULT_HITX,COLOR_DEFAULT_HIGH,COLOR_DEFAULT_L3D,0xFFFFFF,COLOR_DEFAULT_D3D);
	w->addColorSet       (BLUET  ,RGB( 50, 50,200),COLOR_DEFAULT_OFF,COLOR_DEFAULT_HITX,COLOR_DEFAULT_HIGH,COLOR_DEFAULT_L3D,COLOR_DEFAULT_N3D,COLOR_DEFAULT_D3D);
	w->addColorSet       (REDT   ,RGB(250, 50, 50),COLOR_DEFAULT_OFF,COLOR_DEFAULT_HITX,COLOR_DEFAULT_HIGH,COLOR_DEFAULT_L3D,COLOR_DEFAULT_N3D,COLOR_DEFAULT_D3D);
	
	w->addFont           (IDFNTBT,5,13,1,0,0,0,_T("Tahoma"));	
	w->addFont           (IDFNTBGT,8,18,1,0,0,0,_T("Tahoma"));	
	w->addFont           (IDFNTBOLDT, 8,20,1,0,0,0,_T("Arial"));		
	w->addFont           (IDFNTBG1T,6,15,1,0,0,0,_T("Tahoma"));	
	w->addFont           (IDFNTBG2T,5,14,1,0,0,0,_T("Tahoma"));	
	w->addFont           (IDFNTGRID2T,5,14,1,0,0,0,_T("Arial"));	
	w->addFont           (IDFNTXT,5,13,0,0,1,0,_T("Tahoma"));
	w->addFont           (IDFNTNEWT,4,12,1,0,0,0,_T("Tahoma"));	
	w->addFont			 (FNTMED, 7,15,1,0,0,0,_T("Arial"));
//	w->addBackgroundBitmap(IDBCKCABGT,IDB_BACKGROUND_YELLOW);
		
	//w->addBitmapT(BMP_CHECKT			,IDB_CHECK);

	w->addBackgroundBitmap(IDBCKBROWN2_DE	,IDB_BACKBROWN2);
	w->addBackgroundBitmap(IDBCKBROWN3_DE	,IDB_BACKBROWN3);
	w->addBitmapT(BMP_CHECKT			,IDB_CH_CHECK);

	CString aux=_T("");
		
	short widthCell=80;
	// Match Results
	w->createLabel (LBL_MATCH_RESULCH,CRect(INIXT+SERVICE_WIDTHT,INIYT,INIXT+SERVICE_WIDTHT+PLAYERS_WIDTHT,INIYT+CELL_HEIGHCH),"Match Results",BORDER_SINGLE,JUST_CENTER,IDBCKBROWN2_DE ,IDCOL,IDFNTBOLDT);

	// Match 
	w->createLabel (LBL_MATCH_CABT,CRect(INIXT+SERVICE_WIDTHT+PLAYERS_WIDTHT,INIYT,INIXT+SERVICE_WIDTHT+PLAYERS_WIDTHT+widthCell,INIYT+CELL_HEIGHCH),"Result",BORDER_SINGLE,JUST_CENTER,IDBCKBROWN2_DE ,BLUET,IDFNTBT);
	
		
	// Frame Match Result 1
	w->createFrame(FRMMATCH_RESULT1T,CRect(INIXT+SERVICE_WIDTHT, INIYT+CELL_HEIGHCH,INIXT+SERVICE_WIDTHT+PLAYERS_WIDTHT, INIYT+CELL_HEIGHCH*3),BORDER_3DUP,IDCOL);
	
	// Frame Match Result 2
	w->createFrame(FRMMATCH_RESULT2T,CRect(INIXT+SERVICE_WIDTHT, INIYT+CELL_HEIGHCH*3,INIXT+SERVICE_WIDTHT+PLAYERS_WIDTHT, INIYT+CELL_HEIGHCH*5),BORDER_3DUP,IDCOL);

	// Labels que contendran el nombre del tio 
	
	if(pMatchResult1)
		paintMatchResultHome(widthCell);
		
	if(pMatchResult2)
		paintMatchResultAway(widthCell);
		
	
	// Label de informacion del status
	w->createButton(BU_STATUST,CRect(70,10,135,45), putStatus(),IDBCKBROWN3_DE,IDCOL,IDFNTBT);
	w->createButton(BU_FINISHT,CRect(190, 10,255,45),"FINISH",IDBCKBROWN3_DE,IDCOL,IDFNTBGT);

	paintResults();

	// Menu de eleccion de DSQ,RET,DNS u OK
	w->createMenu(MENU_INCIDENCE1T,100,22,IDBCK,IDCOL,IDFNTBT,IDBCK2,IDCOL);
	w->createMenu(MENU_INCIDENCE2T,100,22,IDBCK,IDCOL,IDFNTBT,IDBCK2,IDCOL);

	// Habilito o desabilito controles dependiendo del status del partidoç
	if(pMatch->getStatus()==CHMemoryDataBase::eFinished)
		 disableEnableControls(false);
	else disableEnableControls(true);
	
	w->createLabel (LBL_EVENTS_SUB,    CRect(15,165,215,182),"Sub Matches",BORDER_NONE,JUST_LEFT,IDBCK,IDCOL,FONTMAX);
	w->createLabel (LBL_LINEA_SUB,    CRect(15,182,855,185),"",BORDER_NONE,JUST_LEFT,IDBCK_BOX);

	w->createLabel (LBL_MATCH_TITLE,    CRect(155,165,855,182),"",BORDER_NONE,JUST_LEFT,IDBCK,IDCOL,IDFNTBGT);

	paintMatch();
	w->createGrid(GR_SUBMATCH,CRect(15,185,855,360),BORDER_DOWN,37,IDBCK_GRID,IDCOL,IDFNT);
	
	w->gridLineColor(GR_SUBMATCH,RGB(192,192,192),RGB(192,192,192));

	w->addGridColumn(GR_SUBMATCH,"Date",JUST_CENTER,85);
	w->addGridColumn(GR_SUBMATCH,"Time",JUST_CENTER,50);
	w->addGridColumn(GR_SUBMATCH,"SubMatch",JUST_CENTER,70);
	w->addGridColumn(GR_SUBMATCH,"Home",JUST_CENTER,191);
	w->addGridColumn(GR_SUBMATCH,"Away",JUST_CENTER,191);
	w->addGridColumn(GR_SUBMATCH,"Status",JUST_CENTER,71);
	w->addGridColumn(GR_SUBMATCH,"Session",JUST_CENTER,60);
	w->addGridColumn(GR_SUBMATCH,"Table",JUST_CENTER,60);
	w->addGridColumn(GR_SUBMATCH,"Result",JUST_CENTER,60);
	
	fillSubMatches();

	createTypeResults();
	createTypeResultsPress();

	// Menu de visualizacion de menu con posibles resultados
	w->createMenu(MENU_RESULTS,70,22,IDBCK,IDCOL,IDFNTBG2T,IDBCK2,IDCOL);

	// Menu de visualizacion de menu de posibles colores
	w->createMenu(MENU_COLORS,70,22,IDBCK,IDCOL,IDFNTBG2T,IDBCK2,IDCOL);
	
	
	w->createCheck(CH_OFFICIAL_T,CRect(INIXT+SERVICE_WIDTHT+AFTER_RESULT+170,8,INIXT+SERVICE_WIDTHT+AFTER_RESULT+270,25),"Automatic Finish",JUST_RIGHT,FALSE,IDBCK,IDCOL,IDFNT);

	w->addBitmapT(BMP_PREVIOUS_MA, IDB_BMP_BEFORE);
	w->addBitmapT(BMP_NEXT_MA, IDB_BMP_NEXT);

	// Previous Match
	w->createButton(BU_PREVIOUS_M,CRect(INIXT,INIYT+CELL_HEIGHCH,INIXT+29,INIYT+CELL_HEIGHCH*3-3), "",IDBCK,IDCOL,FNTMED);
	w->changeBmp(BU_PREVIOUS_M, BMP_PREVIOUS_MA, JUST_CENTER);
	w->setToolTip(BU_PREVIOUS_M ,"Previous Match");
	// Next Match
	w->createButton(BU_NEXT_M,CRect(INIXT,INIYT+CELL_HEIGHCH*3+3,INIXT+29,INIYT+CELL_HEIGHCH*5), "",IDBCK,IDCOL,FNTMED);
	w->changeBmp(BU_NEXT_M, BMP_NEXT_MA, JUST_CENTER);
	w->setToolTip(BU_NEXT_M ,"Next Match");

	CDialog::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
              // EXCEPTION: OCX Property Pages should return FALSE
}

void CHTeamResults::fillSubMatches()
{
	w->gridDeleteAllItems(GR_SUBMATCH);

	GSortedVector vMatches=pMatch->getSubMatches();
	for(size_t i=0;i<vMatches.entries();i++)
	{
		CHMatch *pSubMatch=(CHMatch*)vMatches[i]->getElement();
		if(pSubMatch)
		{
			w->addGridLine(GR_SUBMATCH, LPARAM(pSubMatch), "");
		}
	}
	w->selectNLine(GR_SUBMATCH,0);

}
void CHTeamResults::createTypeResults()
{
	
	w->createLabel (LBL_EVENTS_DE,    CRect(INIXT+SERVICE_WIDTHT+AFTER_RESULT,10,INIXT+SERVICE_WIDTHT+AFTER_RESULT+170,27),"Possibles Results",BORDER_NONE,JUST_LEFT,IDBCK,IDCOL,FONTMAX);
	w->createLabel (LBL_LINEA_DE,    CRect(INIXT+SERVICE_WIDTHT+AFTER_RESULT,27,INIXT+SERVICE_WIDTHT+AFTER_RESULT+550,30),"",BORDER_NONE,JUST_LEFT,IDBCK_BOX);
	// Frame Type Results
	w->createFrame(FRM_TYPE_RESULTS,CRect(INIXT+SERVICE_WIDTHT+AFTER_RESULT, 30,INIXT+SERVICE_WIDTHT+AFTER_RESULT+550, 150),BORDER_3DUP,IDCOL);
	
}
void CHTeamResults::createTypeResultsPress()
{
	
	w->createPress(BU_ONE_ZERO,CRect(INIXT+SERVICE_WIDTHT+AFTER_RESULT+15,40,INIXT+SERVICE_WIDTHT+AFTER_RESULT+130,80), " 1 : 0 ",1000,FALSE,IDBCK_BUT,IDCOL,IDFNT_BIG);
	w->createPress(BU_HALF_HALF,CRect(INIXT+SERVICE_WIDTHT+AFTER_RESULT+150,40,INIXT+SERVICE_WIDTHT+AFTER_RESULT+265,80), " 1/2 : 1/2 ",1000,FALSE,IDBCK_BUT,IDCOL,IDFNTBGT);
	w->createPress(BU_ZERO_ONE,CRect(INIXT+SERVICE_WIDTHT+AFTER_RESULT+285,40,INIXT+SERVICE_WIDTHT+AFTER_RESULT+400,80), " 0 : 1 ",1000,FALSE,IDBCK_BUT,IDCOL,IDFNT_BIG);
	w->createPress(BU_EMPTY,CRect(INIXT+SERVICE_WIDTHT+AFTER_RESULT+420,40,INIXT+SERVICE_WIDTHT+AFTER_RESULT+535,80), " Empty ",1000,FALSE,IDBCK_BUT,IDCOL,IDFNT_BIG);

	w->createPress(BU_ONE_ZERO_F,CRect(INIXT+SERVICE_WIDTHT+AFTER_RESULT+15,100,INIXT+SERVICE_WIDTHT+AFTER_RESULT+130,140), " 1F : 0F ",1000,FALSE,IDBCK_BUT,IDCOL,IDFNT_BIG);
	w->createPress(BU_ZERO_ONE_F,CRect(INIXT+SERVICE_WIDTHT+AFTER_RESULT+150,100,INIXT+SERVICE_WIDTHT+AFTER_RESULT+265,140), " 0F : 1F ",1000,FALSE,IDBCK_BUT,IDCOL,IDFNT_BIG);
	w->createPress(BU_ZERO_ZERO_F,CRect(INIXT+SERVICE_WIDTHT+AFTER_RESULT+285,100,INIXT+SERVICE_WIDTHT+AFTER_RESULT+400,140), " 0F : 0F ",1000,FALSE,IDBCK_BUT,IDCOL,IDFNT_BIG);
	
}
LRESULT CHTeamResults::onClick(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch(wParam)
	{
		case LBL_OKT:
			onOK();
			break;
		
		case BU_FINISHT:
			saveAll();
		break;

		case BU_STATUST:
		{
		if (pMatch->getStatus()<CHMemoryDataBase::eSchedulled)
			{
				msg("Warning!!","Match will be greater than Schedulled.",ICO_X,MSG_OK);
				break;
			}
			CHStatusDlg aStatusDlg(this,pMatch);
			aStatusDlg.DoModal();
			
			if(aStatusDlg.hasChanges())
			{
				// Si el Status es igual a StartList tengo que inicializar el partido
				if(aStatusDlg.getStartList() && pMatch->getStatus()==CHMemoryDataBase::eStartList)
					clearResults(pMatch);

				// Si el Status es igual a Protested tengo que desprogresar el partido
				if(pMatch->getStatus()==CHMemoryDataBase::eFinished ||
				   pMatch->getStatus()==CHMemoryDataBase::eProtested)
				{
					eventControlOp.finishMatch(pMatch);
					if(pMatch->getStatus()==CHMemoryDataBase::eFinished)
						 disableEnableControls(false);
					else disableEnableControls(true);
				}
				w->redraw(GR_SUBMATCH);							
				paintMatchStatus();
				paintResults();				
			}
			break;
		}
		case LBL_MATCHRESNOC1T:
		case LBL_MATCHRESNOC2T:
		{
			onContexMenu(lParam,wParam);
			break;
		}
		case MENU_INCIDENCE1T:
			 onQualitativeMenu1((GQualitative*)lParam);
			 break;
		case MENU_INCIDENCE2T:
			 onQualitativeMenu2((GQualitative*)lParam);
			 break;

		case BU_ONE_ZERO:
		case BU_HALF_HALF:
		case BU_ZERO_ONE:
		case BU_EMPTY:
		case BU_ONE_ZERO_F:
		case BU_ZERO_ONE_F:
		case BU_ZERO_ZERO_F:
		{	
			CHMatch *pMatchSel=(CHMatch*)w->getSelectedData(GR_SUBMATCH);
			if(!pMatchSel)
			{
				msg("Warning!!","Please select a Match.",ICO_X,MSG_OK);
				return false;
			}

			eventControlOp.putScore(getEventFromButton(short(wParam)),pMatchSel);
			if(w->getCheck(CH_OFFICIAL_T))
				finishMatch(pMatchSel);
			paintScore();
			changeBackButton(short(wParam));
			w->redraw(GR_SUBMATCH,FALSE);
			//SendMessage(UM_CLICK,BU_FINISH,0);
			if(w->getCheck(CH_OFFICIAL_T))
				nextMatch();
						
		}
		break;
		case MENU_RESULTS: // Menu de tipos de resultados de un partido
			onResultsMenu(lParam);
		 break;
		case MENU_COLORS: // Menu de eleccíon de color de fichas
			onColorsMenu(lParam);
		 break;
		case BU_PREVIOUS_M: // Previous Match
			{
				CHMatch *pMatchPrv=getPreviousResult();
				if(pMatchPrv)
				{
					pMatch=pMatchPrv;		
					pMatchResult1=pMatch->getMatchResultHome();
					pMatchResult2=pMatch->getMatchResultAway();
					paintAll();
				
				}
				break;
			}
		case BU_NEXT_M:		// Next Match
			{
				CHMatch *pMatchNext=getNextResult();
				if(pMatchNext)
				{
					pMatch=pMatchNext;
					pMatchResult1=pMatch->getMatchResultHome();
					pMatchResult2=pMatch->getMatchResultAway();
					paintAll();

				}
				break;
			}
			
	}
	return 0;
}

LRESULT CHTeamResults::onRButtonDown(WPARAM wParam, LPARAM lParam)
{
		
	short x=short(lParam);

	switch(wParam)
	{
		
		case GR_SUBMATCH:
		{
			CHMatch *pMatch=(CHMatch*)w->getSelectedData(GR_SUBMATCH);
			if(!pMatch)
				return false;
		
			posX=x;
			switch (x) // Columnas del grid
			{ 
				
				case 3:// Home
				case 4:// Away
				{
					CHMatchResult *pMatchResult=0;
					if(x==3) // Home
						 pMatchResult=(CHMatchResult*)pMatch->getMatchResultHome();
					else pMatchResult=(CHMatchResult*)pMatch->getMatchResultAway();
					onCreateMenuColors(lParam,pMatchResult);	
					
				}
				break;
				case 8:// Result 
				{
					onCreateMenuResults(lParam,pMatch);	
				}
				break;
			
			}
			
			break;	
		}
	
	}
	return TRUE;
}
void CHTeamResults::onCreateMenuResults(LPARAM lParam, CHMatch *pMatch)
{
 	if(!pMatch)
		return;
	
	RWCString results=NULLRWSTRING;
	w->delMenuItems(MENU_RESULTS);
	

	if (pMatch->getMatchResultHome() && pMatch->getMatchResultAway())
	{
		if(pMatch->getStatus()>=CHMemoryDataBase::eUnofficial)
			// Finish Match
		w->addMenuItem(MENU_RESULTS,SUB_MENU_FINISH,0,"Finish Match",LPARAM(1));	
		// 1:0
		w->addMenuItem(MENU_RESULTS,SUB_MENU_1_0,0,"1 : 0",LPARAM(2));	
		// 1/2:1/2
		w->addMenuItem(MENU_RESULTS,SUB_MENU_1_2_1_2,0,"1/2 : 1/2",LPARAM(3));	
		// 0:1
		w->addMenuItem(MENU_RESULTS,SUB_MENU_0_1,0,"0 : 1",LPARAM(4));	
		// Empty
		w->addMenuItem(MENU_RESULTS,SUB_MENU_0_0,0,"0 : 0",LPARAM(5));	
		// 1F : 0F
		w->addMenuItem(MENU_RESULTS,SUB_MENU_1F_0F,0,"1F : 0F",LPARAM(6));	
		// 0F : 1F
		w->addMenuItem(MENU_RESULTS,SUB_MENU_0F_1F,0,"0F : 1F",LPARAM(7));	
		// 0F : 0F
		w->addMenuItem(MENU_RESULTS,SUB_MENU_0F_0F,0,"0F : 0F",LPARAM(8));	

		w->showMenu(MENU_RESULTS);
				
	}
		
	UNREFERENCED_PARAMETER(lParam);
}
void CHTeamResults::onResultsMenu(LPARAM lparam)
{
	CHMatch *pMatch=(CHMatch*)w->getSelectedData(GR_SUBMATCH);
	if(!pMatch)
		return;
		
	if(lparam>0)
	{	
		if(lparam==1)
		{
			CHEvenControlOperations aEventControlOp(mem());
			aEventControlOp.finishMatch(pMatch,true);
		}
		else
		{
			CHEvenControlOperations aEventControlOp(mem());
			aEventControlOp.putScore(getEventFromButton(BU_ONE_ZERO+(lparam-2)),pMatch);
			paintScore();
		}
		w->redrawLine(GR_SUBMATCH,w->getSelectedLine(GR_SUBMATCH));
				
	}
}
void CHTeamResults::onColorsMenu(LPARAM lparam)
{
	CHMatch *pMatch=(CHMatch*)w->getSelectedData(GR_SUBMATCH);
	if(!pMatch)
		return;
		
	if(lparam>0)
	{	
		CHMatchResult *pMatchResult=0,*pMatchResultVersus=0;
		if(posX==3)
			 pMatchResult=(CHMatchResult*)pMatch->getMatchResultHome();
		else pMatchResult=(CHMatchResult*)pMatch->getMatchResultAway();
		
		pMatchResultVersus=pMatchResult->getMatchResultVersus();
		// Si se cambia de color
		if(pMatchResult->getColor()!=(lparam-1))
		{
			pMatchResult->setColor(short(lparam-1));
			// White
			if(lparam==1)
				pMatchResultVersus->setColor(short(lparam)); // Le pongo negras
			// Negro
			if(lparam==2)
				pMatchResultVersus->setColor(short(lparam-2)); // Le pongo blancas
		}
		
		theApp.queueOut(pMatchResult);
		theApp.queueOut(pMatchResultVersus);
		theApp.out(TRN_CHANGE_MATCHRES);
		
		w->redrawLine(GR_SUBMATCH,w->getSelectedLine(GR_SUBMATCH));
				
	}
}
void CHTeamResults::onCreateMenuColors(LPARAM lParam, CHMatchResult *pMatchResult)
{
 	if(!pMatchResult)
		return;
	
	RWCString colorts=NULLRWSTRING;
	w->delMenuItems(MENU_COLORS);
	

	if (pMatch->getStatus()!=CHMemoryDataBase::eFinished)
	{
		// White
		if(pMatchResult->getColor()==CHMatchResult::eWhite)
			 w->addMenuItem(MENU_COLORS,SUBMENU_WHITE,0,"White",LPARAM(1),BMP_CHECKT);
		else w->addMenuItem(MENU_COLORS,SUBMENU_WHITE,0,"White",LPARAM(1));
		// Black
		if(pMatchResult->getColor()==CHMatchResult::eBlack)
			 w->addMenuItem(MENU_COLORS,SUBMENU_BLACK,0,"Black",LPARAM(2),BMP_CHECKT);
		else w->addMenuItem(MENU_COLORS,SUBMENU_BLACK,0,"Black",LPARAM(2));
		
		w->showMenu(MENU_COLORS);
				
	}
		
	UNREFERENCED_PARAMETER(lParam);
}

void CHTeamResults::onContexMenu(LPARAM lParam, size_t id)
{
	GQualitative *pQualitative=0;
	RWBoolean incidence=false;
	if(id==LBL_MATCHRESNOC1T)
	{
		w->delMenuItems(MENU_INCIDENCE1T);
		short i=1;
		RWSetIterator it(CHMemoryDataBase::getColQualitatives());
		while((pQualitative=(GQualitative*)it())!=0)
		{
			if(pMatchResult1->getQualitative()==pQualitative)
			{	w->addMenuItem(MENU_INCIDENCE1T,SUBMENU_INCIDENCE11T+i,0,pQualitative->getLDescription(),LPARAM(pQualitative),BMP_CHECKT);	
				incidence=true;
			}
			else w->addMenuItem(MENU_INCIDENCE1T,SUBMENU_INCIDENCE11T+i,0,pQualitative->getLDescription(),LPARAM(pQualitative));	
			i++;
		}
						
		w->showMenu(MENU_INCIDENCE1T);
	}
	else if(id==LBL_MATCHRESNOC2T)
	{
		w->delMenuItems(MENU_INCIDENCE2T);
		short i=1;
		RWSetIterator it(CHMemoryDataBase::getColQualitatives());
		while((pQualitative=(GQualitative*)it())!=0)
		{
			if(pMatchResult2->getQualitative()==pQualitative)
			{	 w->addMenuItem(MENU_INCIDENCE2T,SUBMENU_INCIDENCE21T+i,0,pQualitative->getLDescription(),LPARAM(pQualitative),BMP_CHECKT);	
				 incidence=true;
			}
			else w->addMenuItem(MENU_INCIDENCE2T,SUBMENU_INCIDENCE21T+i,0,pQualitative->getLDescription(),LPARAM(pQualitative));	
			i++;
		}
		
		w->showMenu(MENU_INCIDENCE2T);
	}
	
	UNREFERENCED_PARAMETER(lParam);
}
void CHTeamResults::onQualitativeMenu1(GQualitative *pQualitative)
{
	if(LPARAM(pQualitative)>1)
	{	
		if(pQualitative->getCode()!=OK)
		{
			w->changeBck(LBL_MATCHRESNAME1T,IDBCKBROWN3_DE);
			w->changeBck(LBL_MATCHRESNOC1T,IDBCKBROWN3_DE);
		}
		else
		{
			w->changeBck(LBL_MATCHRESNAME1T,IDBCKBROWN2_DE);
			w->changeBck(LBL_MATCHRESNOC1T,IDBCKBROWN2_DE);
		}
		pMatchResult1->setQualitative(pQualitative->getCode());
		theApp.queueOut(pMatchResult1);
		theApp.out(TRN_CHANGE_MATCHRES);
		CHPoolResult * pPoolResult=(CHPoolResult*)pMatchResult1->getPoolResult();
		if(pPoolResult)
		{
			pPoolResult->setQualitative(pQualitative->getCode());
			theApp.queueOut(pPoolResult);
			theApp.out(TRN_CHANGE_POOLRES);
		}
	}
	
	w->redraw(LBL_MATCHRESNAME1T);
	w->redraw(LBL_MATCHRESNOC1T);
		
}
void CHTeamResults::onQualitativeMenu2(GQualitative *pQualitative)
{
	if(LPARAM(pQualitative)>1)
	{
		if(pQualitative->getCode()!=OK)
		{
			w->changeBck(LBL_MATCHRESNAME2T,IDBCKBROWN3_DE);
			w->changeBck(LBL_MATCHRESNOC2T,IDBCKBROWN3_DE);
		}
		else
		{
			w->changeBck(LBL_MATCHRESNAME2T,IDBCKBROWN2_DE);
			w->changeBck(LBL_MATCHRESNOC2T,IDBCKBROWN2_DE);
		}
		pMatchResult2->setQualitative(pQualitative->getCode());
		theApp.queueOut(pMatchResult2);
		theApp.out(TRN_CHANGE_MATCHRES);
		CHPoolResult * pPoolResult=(CHPoolResult*)pMatchResult2->getPoolResult();
		if(pPoolResult)
		{
			pPoolResult->setQualitative(pQualitative->getCode());
			theApp.queueOut(pPoolResult);
			theApp.out(TRN_CHANGE_POOLRES);
		}
		CHEventResult *pEventResult=(CHEventResult*)CHMemoryDataBase::findEventResult(pPoolResult->getInscription());
		if(pEventResult)
		{
			pEventResult->setQualitative(pQualitative->getCode());
			theApp.queueOut(pEventResult);
			theApp.out(TRN_CHANGE_EVENT_RESULT);
		}
	}

	w->redraw(LBL_MATCHRESNAME2T);
	w->redraw(LBL_MATCHRESNOC2T);	
}

BOOL CHTeamResults::DestroyWindow() 
{
	if (w)
		delete w;		

	if (pStatusMngt)
		delete pStatusMngt;
	
	for (int i=0; i<4; i++)
	{
		if (m_pBmpFlag[i])
		{
			m_pBmpFlag[i]->DeleteObject();
			delete m_pBmpFlag[i];
		}
	}
	
	return CDialog::DestroyWindow();
}

void CHTeamResults::onOK() 
{
	CDialog::OnOK();
}

RWCString CHTeamResults::putStatus()
{
	if(pMatch)
	{
		GStatus *pStatus=CHMemoryDataBase::findStatus(pMatch->getStatus());
		if(pStatus)
			return pStatus->getLDescription().toMultiByte();
		
	}
	return NULLRWSTRING;
}

void CHTeamResults::disableEnableControls(RWBoolean enable)
{
	// Labels que contendran el nombre del tio 
	
	w->enable (LBL_MATCHRESNAME1T,enable);
	w->enable (LBL_MATCHRESNOC1T,enable);
		
	// Edit de Partido
	w->enable(ED_MATCH1T,enable);
		
	w->enable (LBL_MATCHRESNAME2T,enable);
	w->enable (LBL_MATCHRESNOC2T,enable);
	// Edit de Partido
	w->enable(ED_MATCH2T,enable);
		
	w->enable(BU_FINISHT,enable);
	for(size_t i=0;i<8;i++)
		w->enable(BU_ONE_ZERO+i,enable);

}
void CHTeamResults::paintMatch()
{
	RWCString match=NULLRWSTRING;

	if(pMatch)
	{
		// Name Register 1
		if(pMatchResult1->getRegister())
			 match+=pMatchResult1->getScbLName().toAscii();
		else match+="None";
		
		match+=" - ";
		// Name Register 2
		if(pMatchResult2->getRegister())
			 match+=pMatchResult2->getScbLName().toAscii();
		else match+="None";

		match+="     ";

		//Round
		match+=pMatch->getRoundAsString(true,false);

		match+="     ";

		// Date
		if(pMatch->getStartDate().isValid())
			match+=pMatch->getStartDate().asString("%d/%m/%Y");
		// Time
		if(pMatch->getStartDate().isValid())
		{
			match+="  ";
			match+=pMatch->getStartTime().asString("%H:%M");
		}
		
	}
	w->changeTxt(LBL_MATCH_TITLE,match);
}
void CHTeamResults::paintMatchStatus()
{
	GStatus *pStatus=0;
	int active=0;
	RWOrderedIterator ite2((RWSortedVector&)mem()->getColStatus());
	while( (pStatus=(GStatus *)ite2()) != 0)
	{
		if (pStatus->getStatus()>=CHMemoryDataBase::eSchedulled)
		{
			if (pMatch->getStatus()==pStatus->getStatus())
				active=1;
			else
				active=0;

			if(active)	
			{
				w->changeTxt(BU_STATUST, (CString)pStatus->getLDescription());
				break;
			}
		}
	}
	
	if(!active) 
		w->changeTxt(BU_STATUST, "");
	
}

void CHTeamResults::saveAll()
{
	// Le pongo a Running para despues poderle pasar a Unofficial
	pMatch->setStatus(CHMemoryDataBase::eRunning);
	pStatusMngt->run(*pMatch, unsigned char(CHMemoryDataBase::eUnofficial),false);
	pMatch->setStatus(CHMemoryDataBase::eUnofficial);
	paintMatchStatus();
			
	// SAVE MATCH RESULTS
	pMatchResult1->setPoints(float(atof(w->getTxt(ED_MATCH1T))));
	theApp.queueOut(pMatchResult1);
	pMatchResult2->setPoints(float(atof(w->getTxt(ED_MATCH2T))));
	theApp.queueOut(pMatchResult2);
	theApp.out(TRN_CHANGE_MATCHRES);
	
}

void CHTeamResults::paintResults()
{
	// Puntos totales en el partido
	
	w->changeTxt(ED_MATCH1T,pMatchResult1->getPointsAsString());
	
	w->changeTxt(ED_MATCH2T,pMatchResult2->getPointsAsString());
}

void CHTeamResults::paintMatchResultHome(short widthCell)
{
	 // Team flags
	w->destroyControl(FLAG_HOMET);
		
	GRegister *pRegister=pMatchResult1->getRegister();
	if(pRegister)
	{
		getFlag(pMatchResult1->getGroup(),SML,m_pBmpFlag[0]);			
	 	w->createUserBitmap(FLAG_HOMET,CRect(INIXT+SERVICE_WIDTHT+NAME_WIDTHT,INIYT+CELL_HEIGHCH,INIXT+SERVICE_WIDTHT+NAME_WIDTHT+NOC_WIDTHT,INIYT+CELL_HEIGHCH*2),m_pBmpFlag[0],TRUE,BORDER_NONE);
		if(pMatchResult1->isQualitative())
		{	w->createLabel (LBL_MATCHRESNAME1T,CRect(INIXT+SERVICE_WIDTHT,INIYT+CELL_HEIGHCH,INIXT+SERVICE_WIDTHT+NAME_WIDTHT,INIYT+CELL_HEIGHCH*3),pRegister->getScbLName() ,BORDER_SINGLE,JUST_CENTER,IDBCKBROWN3_DE ,BLUET,IDFNTGRID2T);		
			w->createLabelEx (LBL_MATCHRESNOC1T ,CRect(INIXT+SERVICE_WIDTHT+NAME_WIDTHT,INIYT+CELL_HEIGHCH*2,INIXT+SERVICE_WIDTHT+NAME_WIDTHT+NOC_WIDTHT,INIYT+CELL_HEIGHCH*3),pRegister->getGroup(),BORDER_SINGLE,JUST_CENTER,IDBCKBROWN3_DE ,BLUET,IDFNTXT);
		}

		else
		{	w->createLabel (LBL_MATCHRESNAME1T,CRect(INIXT+SERVICE_WIDTHT,INIYT+CELL_HEIGHCH,INIXT+SERVICE_WIDTHT+NAME_WIDTHT,INIYT+CELL_HEIGHCH*3),pRegister->getScbLName() ,BORDER_SINGLE,JUST_CENTER,IDBCKBROWN2_DE ,BLUET,IDFNTGRID2T);		
			w->createLabelEx (LBL_MATCHRESNOC1T ,CRect(INIXT+SERVICE_WIDTHT+NAME_WIDTHT,INIYT+CELL_HEIGHCH*2,INIXT+SERVICE_WIDTHT+NAME_WIDTHT+NOC_WIDTHT,INIYT+CELL_HEIGHCH*3),pRegister->getGroup(),BORDER_SINGLE,JUST_CENTER,IDBCKBROWN2_DE,BLUET,IDFNTXT);
		}
	}
	
	// Edit de Partido
	w->createEdit(ED_MATCH1T, CRect(INIXT+SERVICE_WIDTHT+PLAYERS_WIDTHT,INIYT+CELL_HEIGHCH,INIXT+SERVICE_WIDTHT+PLAYERS_WIDTHT+widthCell, INIYT+CELL_HEIGHCH*3),"",BORDER_SINGLE,JUST_CENTER ,IDBBKYELLOWT,REDT,IDFNTBG1T);
	
}
void CHTeamResults::paintMatchResultAway(short widthCell)
{
	// Team flags
	w->destroyControl(FLAG_AWAYT);
	
	GRegister *pRegister=pMatchResult2->getRegister();
	if(pRegister)
	{
		getFlag(pMatchResult2->getGroup(),SML,m_pBmpFlag[1]);			
	 	w->createUserBitmap(FLAG_AWAYT,CRect(INIXT+SERVICE_WIDTHT+NAME_WIDTHT,INIYT+CELL_HEIGHCH*3,INIXT+SERVICE_WIDTHT+NAME_WIDTHT+NOC_WIDTHT,INIYT+CELL_HEIGHCH*4),m_pBmpFlag[1],TRUE,BORDER_NONE);
		
		if(pMatchResult2->isQualitative())
		{	w->createLabel (LBL_MATCHRESNAME2T,CRect(INIXT+SERVICE_WIDTHT,INIYT+CELL_HEIGHCH*3,INIXT+SERVICE_WIDTHT+NAME_WIDTHT,INIYT+CELL_HEIGHCH*5),pRegister->getScbLName() ,BORDER_SINGLE,JUST_CENTER,IDBCKBROWN3_DE ,BLUET,IDFNTGRID2T);		
			w->createLabelEx (LBL_MATCHRESNOC2T ,CRect(INIXT+SERVICE_WIDTHT+NAME_WIDTHT,INIYT+CELL_HEIGHCH*4,INIXT+SERVICE_WIDTHT+NAME_WIDTHT+NOC_WIDTHT,INIYT+CELL_HEIGHCH*5),pRegister->getGroup(),BORDER_SINGLE,JUST_CENTER,IDBCKBROWN3_DE ,BLUET,IDFNTXT);		
		}
		else
		{	w->createLabel (LBL_MATCHRESNAME2T,CRect(INIXT+SERVICE_WIDTHT,INIYT+CELL_HEIGHCH*3,INIXT+SERVICE_WIDTHT+NAME_WIDTHT,INIYT+CELL_HEIGHCH*5),pRegister->getScbLName() ,BORDER_SINGLE,JUST_CENTER,IDBCKBROWN2_DE ,BLUET,IDFNTGRID2T);		
			w->createLabelEx (LBL_MATCHRESNOC2T ,CRect(INIXT+SERVICE_WIDTHT+NAME_WIDTHT,INIYT+CELL_HEIGHCH*4,INIXT+SERVICE_WIDTHT+NAME_WIDTHT+NOC_WIDTHT,INIYT+CELL_HEIGHCH*5),pRegister->getGroup(),BORDER_SINGLE,JUST_CENTER,IDBCKBROWN2_DE ,BLUET,IDFNTXT);		
		}
	}
	
	// Edit de Partido
	w->createEdit(ED_MATCH2T, CRect(INIXT+SERVICE_WIDTHT+PLAYERS_WIDTHT,INIYT+CELL_HEIGHCH*3,INIXT+SERVICE_WIDTHT+PLAYERS_WIDTHT+widthCell, INIYT+CELL_HEIGHCH*5),"",BORDER_SINGLE,JUST_CENTER ,IDBBKYELLOWT,REDT,IDFNTBG1T);
	
}
void CHTeamResults::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	
	if ( pMatch )
	{
		int focus=w->getFocus();
				
		if(focus==ED_MATCH1T || focus==ED_MATCH2T)
		{
			if ( wParam==38/*ARROW_UP*/)
			{				
				if(focus==ED_MATCH2T)
					w->setFocus(--focus);
			}
			if ( wParam==40/*ARROW_DOWN*/)
			{				
				if(focus==ED_MATCH1T)
					w->setFocus(++focus);
			}
		}
	}
	
	switch(wParam)
	{
		case 33: // Av Pag
		case 34: // Re Pag
		case 40: // Up
		case 38: // Down
		{	
			int focus=w->getFocus();
			switch(focus)
			{
			
				case GR_SUBMATCH:
				{	
					CHMatch *pMatchAux=(CHMatch*)w->getSelectedLParam(GR_SUBMATCH);
					if (!pMatchAux) 
						return;
					changePress();
					
					break;
				}
				
			}
			break;		
		}
		case 27:
			OnCancel();
			break;
			
	}
}

void CHTeamResults::clearResults(CHMatch *pMatchAux)
{
	if(eventControlOp.clearResults(pMatchAux))
	{
		// Repaint all.
		paintMatchStatus();

		paintMatchResult();
		changePress();
		paintQualitatives();
		
		if(pMatchAux->getSubMatch())
			eventControlOp.recalculateTeam(pMatchAux);
		w->redraw(GR_SUBMATCH,FALSE);
	}
			
}
void CHTeamResults::onLButtonDown (WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
		case GR_SUBMATCH:
		{
			changePress();
			
		}
		break;
	}

	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);
}
LRESULT CHTeamResults::onDblClick(WPARAM wParam, LPARAM lParam)
{
	if (wParam==GR_SUBMATCH)
	{
		WORD y=HIWORD(lParam);
		WORD x=LOWORD(lParam);
		
		CHMatch *pMatchSel=(CHMatch*)w->getSelectedData(GR_SUBMATCH);
		if(!pMatchSel)
			return 0;
		
		switch (x)  // Columns
		{
			case 3: // Home Match Result 
				
				break;
			case 5: // Status
			{
				if (pMatchSel->getStatus()<CHMemoryDataBase::eStartList)
				{
					msg("Warning!!","Match will be in Startlist Status.",ICO_X,MSG_OK);
					break;
				}
				CHStatusDlg aStatusDlg(this,pMatchSel);
				aStatusDlg.DoModal();
				
				if(aStatusDlg.hasChanges())
				{
					// Si el Status es igual a StartList tengo que inicializar el partido
					if(aStatusDlg.getStartList() && pMatchSel->getStatus()==CHMemoryDataBase::eStartList)
					{
						clearResults(pMatchSel);
						paintResults();
					}

					// Si el Status es igual a Protested tengo que desprogresar el partido
					if(pMatchSel->getStatus()==CHMemoryDataBase::eFinished ||
					   pMatchSel->getStatus()==CHMemoryDataBase::eProtested)
					{
						
						eventControlOp.finishMatch(pMatchSel);
						if(pMatchSel->getStatus()==CHMemoryDataBase::eFinished)
							 disableEnableControls(false);
						else
						{
							if (pMatchSel->areTeamIndividual())
							{
								CHMatch *pMat=pMatchSel->getParentMatch();
								pStatusMngt->run(*pMat, CHMemoryDataBase::eProtested);
							}
							disableEnableControls(true);
						}
					}
					else if(pMatchSel->getStatus()==CHMemoryDataBase::eRunning)
					{
					}
					paintResults();
					paintMatchStatus();
					w->redrawLine(GR_SUBMATCH,y);
				}

				break;
			}									
			
		}		
		
	}
	return 0;
}
BOOL CHTeamResults::onPaintGrid   (UINT idGrid,GridItem *gi)
{
	if (idGrid==GR_SUBMATCH)
	{
		paintListScheduledMatches(gi);
		return true;
	}
	
	return false;
}
void CHTeamResults::paintListScheduledMatches(GridItem *gi)
{
	if (!gi) return;
	
	CHMatch *pMatch=(CHMatch *) gi->lParam;
	if (!pMatch) return;

	COLORREF color=RGB(250,250,240);


	//gi->cdc->FillSolidRect(gi->rc,(gi->sel)?0x808080:color);
	gi->cdc->SetTextColor(COLOR_DEFAULT_ON);

	RWCString txt = NULLRWSTRING;
	CString matchCode = _T("");	
	CString matchNumber = _T("");	
	CString subMatch = _T("");	
	// Text		
	
	if (gi->sel)	
		gi->cdc->FillSolidRect(gi->rc,GET_COLOR_DEFAULT_HIGH);
	else
	{
		if(gi->y%2)
			 gi->cdc->FillSolidRect(gi->rc,RGB(255,255,255));
		else gi->cdc->FillSolidRect(gi->rc,RGB(243,243,243));
	}

	switch (gi->x)
	{
	case 0:
		{
			// Start Date
			RWDate aStartDate = pMatch->getStartDate();
			if (aStartDate.isValid())
				eventControlOp.paintShadow(gi->cdc,gi->rc.left+5,gi->rc.top+12,aStartDate.asString("%d/%m/%Y"),COLOR_MARRON,0,IDFNTBG2T ,w,COLOR_NEGRO); 
			//	w->paintGridText(gi->rc.Width()/2,5,aStartDate.asString("%d/%m/%Y"),JUST_CENTER);

			break;
		}
	case 1:
		{	
			// Start Time
			RWTime aStartTime = pMatch->getStartTime();
			if (aStartTime.isValid())
			{
				txt = pMatch->getStartTime().asString("%H:%M");
				eventControlOp.paintShadow(gi->cdc,gi->rc.left+8,gi->rc.top+12,txt,COLOR_MARRON,0,IDFNTBG2T ,w,COLOR_NEGRO); 
				//w->paintGridText(gi->rc.Width()/2,5,txt,JUST_CENTER);
			}
			break;
		}
/*	case 2:
		{
			// Match Number
			matchNumber.Format("-");
			if (pMatch->getMatchNumber())
				matchNumber.Format("%d", pMatch->getMatchNumber());
			eventControlOp.paintShadow(gi->cdc,gi->rc.left+10,gi->rc.top+5,matchNumber,COLOR_MARRON,0,IDFNTBG2T ,w,COLOR_NEGRO); 
			//w->paintGridText(gi->rc.Width()/2,5,matchNumber,JUST_CENTER);
			break;			
		}	*/

	case 2:
		{
			char subMatch[4];
			sprintf(subMatch,"%d",pMatch->getSubMatch());
			// Match Description
			eventControlOp.paintShadow(gi->cdc,gi->rc.left+35,gi->rc.top+12,subMatch,COLOR_MARRON,1,IDFNTBG2T ,w,COLOR_NEGRO); 
			//w->paintGridText(gi->rc.Width()/2,5,subMatch,JUST_CENTER);
			break;
		}
	case 3:
		{
			// Match Competitors
		
			CHMatchResult* pMatchRes1 = (CHMatchResult*)pMatch->getCompetitorsVector()[0]->getElement();
			
			if (pMatchRes1->getRegister())
			{
				CBitmap aBitmap;
				getFlag(pMatchRes1->getGroup(),SML,&aBitmap);	
				w->paintGridUserBmp  (4,1,&aBitmap,false);

				// NOC Home
				eventControlOp.paintShadow(gi->cdc,gi->rc.left+10,gi->rc.top+20,pMatchRes1->getGroup(),COLOR_MARRON,0,IDFNTBG2T ,w,COLOR_NEGRO); 
			}

			char text[50];
			COLORREF color;
			if (pMatch->hasByes())
				color=RGB(250,0,0);
			else
				color=COLOR_DEFAULT_ON;

			sprintf(text,"%s",	eventControlOp.getMatchResultDescription(pMatchRes1));
			eventControlOp.paintShadow(gi->cdc,gi->rc.left+40,gi->rc.top+4,text,COLOR_MARRON,0,IDFNTBG2T ,w,COLOR_NEGRO); 
			
			sprintf(text,"%s",eventControlOp.getMatchMemberDescription(pMatchRes1));
			eventControlOp.paintShadow(gi->cdc,gi->rc.left+42,gi->rc.top+18,text,RGB(172,170,204),0,IDFNTGRID2T ,w,COLOR_NEGRO); 
						
			if(pMatchRes1->getColor()==CHMatchResult::eWhite)
				 w->paintGridBmp (170,10,BMP_WHITE);
			else w->paintGridBmp(170,10,BMP_BLACK);
			break;
		}
	case 4:
		{
			// Match Competitors
			
				
			CHMatchResult* pMatchRes2 = (CHMatchResult*)pMatch->getCompetitorsVector()[1]->getElement();
			
			if (pMatchRes2->getRegister())
			{
				CBitmap aBitmap;
				getFlag(pMatchRes2->getGroup(),SML,&aBitmap);	
				w->paintGridUserBmp  (4,1,&aBitmap,false);

				// NOC Home
				eventControlOp.paintShadow(gi->cdc,gi->rc.left+10,gi->rc.top+20,pMatchRes2->getGroup(),COLOR_MARRON,0,IDFNTBG2T ,w,COLOR_NEGRO); 
			}

			char text[50];
			COLORREF color;
			if (pMatch->hasByes())
				color=RGB(250,0,0);
			else
				color=COLOR_DEFAULT_ON;

			sprintf(text,"%s",	eventControlOp.getMatchResultDescription(pMatchRes2));
			eventControlOp.paintShadow(gi->cdc,gi->rc.left+40,gi->rc.top+4,text,COLOR_MARRON,0,IDFNTBG2T ,w,COLOR_NEGRO); 
			
			sprintf(text,"%s",eventControlOp.getMatchMemberDescription(pMatchRes2));
			eventControlOp.paintShadow(gi->cdc,gi->rc.left+42,gi->rc.top+18,text,RGB(172,170,204),0,IDFNTGRID2T ,w,COLOR_NEGRO); 
			if(pMatchRes2->getColor()==CHMatchResult::eWhite)
				 w->paintGridBmp (170,10,BMP_WHITE);
			else w->paintGridBmp(170,10,BMP_BLACK);
			break;
		}
	case 5:
		{
			// Status
			GStatus* pStatus = (GStatus*)mem()->findStatus(pMatch->getStatus());
			if (pStatus)
			{
				COLORREF color;
				if (pStatus->getStatus()<=CHMemoryDataBase::eSchedulled)
					color=RGB(0,125,0);		
				else
					color=RGB(250,0,0);

				eventControlOp.paintShadow(gi->cdc,gi->rc.left+5,gi->rc.top+12,pStatus->getLDescription().toMultiByte(),COLOR_MARRON,0,IDFNTBG2T ,w,COLOR_NEGRO); 
				//w->paintGridText(gi->rc.Width()/2,5,pStatus->getLDescription(),FONTMIN,color,JUST_CENTER);
			}
			break;			
		}
	case 6:
		{	// Session
			CHSession * pSession = (CHSession*)pMatch->getSession();
			
			if (pSession)
			{
				char text[10];
				sprintf(text,"%s",eventControlOp.getSessionDescription(pSession));
				eventControlOp.paintShadow(gi->cdc,gi->rc.left+25,gi->rc.top+12,text,COLOR_MARRON,0,IDFNTBG2T ,w,COLOR_NEGRO); 
				//w->paintGridText(gi->rc.Width()/2,5,getSessionDescription(pSession),JUST_CENTER);
			}
			
			break;
		}
	case 7:
		{   // Court 
			if (pMatch->getCourt())
			{
				CString court(eventControlOp.getCourtDescription(pMatch->getCourt()));
				RWWString courtS=court;
				eventControlOp.paintShadow(gi->cdc,gi->rc.left+25,gi->rc.top+12,courtS.toAscii(),COLOR_MARRON,0,IDFNTBG2T ,w,COLOR_NEGRO); 
				//w->paintGridText(gi->rc.Width()/2,5,getCourtDescription(pMatch->getCourt()),JUST_CENTER);
			}
			break;
		}
	case 8: // Result
		{
			gi->cdc->SetTextColor(COLOR_DEFAULT_ON);
			if(pMatch->getStatus()>CHMemoryDataBase::eStartList)
			{   // Match Description
				
				 eventControlOp.paintShadow(gi->cdc,gi->rc.left+27,gi->rc.top+12,pMatch->getResultAsString(),COLOR_MARRON,1,IDFNTBG2T ,w,COLOR_NEGRO); 
			}
			else eventControlOp.paintShadow(gi->cdc,gi->rc.left+27,gi->rc.top+12,"-",COLOR_MARRON,1,IDFNTBG2T ,w,COLOR_NEGRO); 
			break;
		}
	}
}

void CHTeamResults::paintScore()
{
	paintMatchResult();
	paintQualitatives();
	
}
void CHTeamResults::paintMatchResult()
{
	if(pMatchResult1) 
		w->changeTxt(ED_MATCH1T,pMatchResult1->getPointsAsString());
	else
		w->changeTxt(ED_MATCH1T,"");
			
	
	w->changeTxt (LBL_MATCHRESNAME1T,pMatchResult1->getScbLName() );
	w->changeTxt (LBL_MATCHRESNOC1T ,pMatchResult1->getGroup() );

	if(pMatchResult2)	
		w->changeTxt(ED_MATCH2T,pMatchResult2->getPointsAsString());
	else
		w->changeTxt(ED_MATCH2T,"");
	
	w->changeTxt (LBL_MATCHRESNAME2T,pMatchResult2->getScbLName() );
	w->changeTxt (LBL_MATCHRESNOC2T ,pMatchResult2->getGroup() );

	w->redraw(ED_MATCH1T);
	w->redraw(ED_MATCH2T);
}
void CHTeamResults::paintFlags()
{
	w->destroyControl(FLAG_HOMET);
		
	GRegister *pRegister=pMatchResult1->getRegister();
	if(pRegister)
	{
		getFlag(pMatchResult1->getGroup(),SML,m_pBmpFlag[0]);			
	 	w->createUserBitmap(FLAG_HOMET,CRect(INIXT+SERVICE_WIDTHT+NAME_WIDTHT,INIYT+CELL_HEIGHCH,INIXT+SERVICE_WIDTHT+NAME_WIDTHT+NOC_WIDTHT,INIYT+CELL_HEIGHCH*2),m_pBmpFlag[0],TRUE,BORDER_NONE);
	}

	// Team flags
	w->destroyControl(FLAG_AWAYT);
	
	pRegister=pMatchResult2->getRegister();
	if(pRegister)
	{
		getFlag(pMatchResult2->getGroup(),SML,m_pBmpFlag[1]);			
	 	w->createUserBitmap(FLAG_AWAYT,CRect(INIXT+SERVICE_WIDTHT+NAME_WIDTHT,INIYT+CELL_HEIGHCH*3,INIXT+SERVICE_WIDTHT+NAME_WIDTHT+NOC_WIDTHT,INIYT+CELL_HEIGHCH*4),m_pBmpFlag[1],TRUE,BORDER_NONE);
	}
}
void CHTeamResults::paintQualitatives()
{
	
	if(pMatchResult1 && pMatchResult1->isQualitative())
	{
		w->changeBck(LBL_MATCHRESNAME1T,IDBCKBROWN3_DE);
		w->changeBck(LBL_MATCHRESNOC1T,IDBCKBROWN3_DE);
			
	}
	else
	{
		w->changeBck(LBL_MATCHRESNAME1T,IDBCKBROWN2_DE);
		w->changeBck(LBL_MATCHRESNOC1T,IDBCKBROWN2_DE);
	}
	
	if(pMatchResult2 && pMatchResult2->isQualitative())
	{
		w->changeBck(LBL_MATCHRESNAME2T,IDBCKBROWN3_DE);
		w->changeBck(LBL_MATCHRESNOC2T,IDBCKBROWN3_DE);
	}
	else
	{
		w->changeBck(LBL_MATCHRESNAME2T,IDBCKBROWN2_DE);
		w->changeBck(LBL_MATCHRESNOC2T,IDBCKBROWN2_DE);
	}
	w->redraw(LBL_MATCHRESNAME1T);
	w->redraw(LBL_MATCHRESNOC1T);
	w->redraw(LBL_MATCHRESNAME2T);
	w->redraw(LBL_MATCHRESNOC2T);
}
void CHTeamResults::changeBackButton(short button)
{
	for(size_t i=0;i<8;i++)
	{
		w->changeBck(BU_ONE_ZERO+i,IDBCK_BUT);
		w->changeCheck(BU_ONE_ZERO+i,FALSE);
		w->redraw(BU_ONE_ZERO+i,FALSE);
	}
 
	if(button)
	{
		w->changeBck(button,IDBCKBROWN3_DE);
		w->redraw(button,FALSE);
	}
}	
void CHTeamResults::changePress()
{
	short button=0;
	
	CHMatch *pMatchSel=(CHMatch*)w->getSelectedData(GR_SUBMATCH);
	if(!pMatchSel)
		return;

	CHMatchResult *pMatchResultSel1=pMatchSel->getMatchResultHome();
	CHMatchResult *pMatchResultSel2=pMatchSel->getMatchResultAway();
	
	for(size_t i=0;i<8;i++)
		w->destroyControl(BU_ONE_ZERO+i);

	createTypeResultsPress();

	if(pMatchResultSel1 && pMatchResultSel2)
	{
		if(pMatchResultSel1->isQualitative() && pMatchResultSel2->isQualitative())
			button=BU_ONE_ZERO;
		else if(pMatchResultSel1->isQualitative())
			button=BU_ZERO_ONE_F;
		else if(pMatchResultSel2->isQualitative())
			button=BU_ONE_ZERO_F;
		else if(pMatchResultSel1->getPoints()==0 && pMatchResultSel2->getPoints==0)
			button=BU_EMPTY;
		else if(pMatchResultSel1->getPoints()==0 && pMatchResultSel2->getPoints()==1)
			button=BU_ZERO_ONE;
		else if(pMatchResultSel1->getPoints()==0.5 && pMatchResultSel2->getPoints()==0.5)
			button=BU_HALF_HALF;
		else if(pMatchResultSel1->getPoints()==1 && pMatchResultSel2->getPoints()==0)
			button=BU_ONE_ZERO;
	}
	
	w->changeCheck(button,TRUE);
	changeBackButton(button);
	
	if(pMatchSel->getStatus()==CHMemoryDataBase::eFinished)
		 disableEnableControls(false);
	else disableEnableControls(true);
}

short CHTeamResults::getEventFromButton(short button)
{
	switch (button)
	{
		case BU_ONE_ZERO:	
			return EV_WHITE_WINNER;
		case BU_HALF_HALF:
			return EV_DRAW;
		case BU_ZERO_ONE:
			return EV_BLACK_WINNER;		
		case BU_ONE_ZERO_F:
			return EV_WHITE_WINNER_F;
		case BU_ZERO_ONE_F:
			return EV_BLACK_WINNER_F;
		case BU_ZERO_ZERO_F:
			return EV_DRAW_F;
		case BU_EMPTY:
			return EV_EMPTY;
	}
	return 0;
}

void CHTeamResults::nextMatch()
{
	int line=w->getSelectedLine(GR_SUBMATCH);
	int nItems=w->getGridNItems(GR_SUBMATCH);
	if(line<=nItems)
	{
		w->selectNLine(GR_SUBMATCH,++line);
		changePress();
	
	}
}
void CHTeamResults::finishMatch(CHMatch *pMatchAux)
{
	CHStatusManager statusManager;
 	statusManager.run(*pMatchAux,CHMemoryDataBase::eFinished);

	eventControlOp.finishMatch(pMatchAux);
	if(pMatchAux->getStatus()==CHMemoryDataBase::eFinished)
		 disableEnableControls(false);
	else disableEnableControls(true);
	paintMatchStatus();
	CHMatch *pParentMatch=pMatchAux->getParentMatch();
	if(!pParentMatch)
		return;
	if(pParentMatch->getStatus()>=CHMemoryDataBase::eFinished)
		eventControlOp.finishMatch(pParentMatch,true);
		
}
CHMatch *CHTeamResults::getPreviousResult()
{
	CHMatch *pMatchPrv=0;
	CHPool *pPool=(CHPool*)pMatch->getPool();
	if(pMatch->getIdParent()>1)
	{
		CHMatch *pMatchAux=0;
		for(size_t i=0;i<pPool->getMatchsVector().entries();i++)
		{
			pMatchAux=(CHMatch*)pPool->getMatchsVector()[i]->getElement();
			// Encontrado
			if(pMatchAux->getIdParent()==(pMatch->getIdParent()-1))
			{
				pMatchPrv=pMatchAux;
				break;
			}
			if(pMatchAux->getIdParent()>pMatch->getIdParent())
				break;
				
			
		}
	}
	return pMatchPrv;

}
CHMatch *CHTeamResults::getNextResult()
{
	CHMatch *pMatchNext=0;
	CHPool *pPool=(CHPool*)pMatch->getPool();
	if(pMatch->getIdParent()<short(pPool->getMatchsVector().entries()))
	{
		CHMatch *pMatchAux=0;
		for(size_t i=0;i<pPool->getMatchsVector().entries();i++)
		{
			pMatchAux=(CHMatch*)pPool->getMatchsVector()[i]->getElement();
			// Encontrado
			short idParentAux=pMatchAux->getIdParent();
			short idParent=pMatch->getIdParent();
			if(pMatchAux->getIdParent()==(pMatch->getIdParent()+1))
			{
				pMatchNext=pMatchAux;
				break;
			}
						
		}
	}
	return pMatchNext;

}
void CHTeamResults::paintAll()
{
	fillSubMatches();
	
	paintMatch();
	paintMatchStatus();
	
	paintMatchResult();
	paintFlags();
	changePress();
	paintQualitatives();
	
	if(pMatch->getStatus()==CHMemoryDataBase::eFinished)
		 disableEnableControls(false);
	else disableEnableControls(true);
	
}