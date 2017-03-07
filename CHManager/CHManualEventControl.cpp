/*************************************************************************************
*	© Copyright MSL Software, S.L., 2001
*
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be consideRED_DE liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registeRED_DE trademark.	
*
*	File name	: CHManualEventControl.cpp
*   Description	: 
*
*	Author		: Chess Team
*	Date created: 21-12-2005
* 	Project		:
*
***************************************************************************************/

#include "stdafx.h"
#include "CHmanager.h"
#include "CHManualEventControl.h"
#include "CHRanking.h"
#include "CHDefines.h"
#include "CHProgression.h"
#include <GUI/FLAGS/flags.h>
#include <core/G/GMsgDefines.h>
#include <core/TH/GTHMsgDefines.h>
#include <sports/CH/data/CHMsgDefines.h>
#include <sports/CH/data/CHMatchMember.h>
#include <sports/CH/data/CHStatisticDefines.h>
#include "CHManualEventControl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define		IDBACKG			 1001


extern CCHManagerApp theApp;

CHManualEventControl::CHManualEventControl(CWnd* pParent /*=NULL*/,CHMatch *pSelMatch)
:CDialog(CHManualEventControl::IDD, pParent)
,pMatch(pSelMatch)
,pMatchResult1(0)
,pMatchResult2(0)
,eventControlOp((CHMemoryDataBase*)mem())
,posX(0)
,posY(0)
,poolMatches(true)
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

	//{{AFX_DATA_INIT(CHManualEventControl)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CHManualEventControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHManualEventControl)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHManualEventControl, CDialog)
	//{{AFX_MSG_MAP(CHManualEventControl)
	ON_MESSAGE(UM_CLICK,onClick)
	ON_MESSAGE(UM_CONTEX_MENU,onContexMenu)		
	ON_MESSAGE(UM_KEYDOWN, OnKeyDown)
	ON_MESSAGE(UM_PAINTGRID,onPaintGrid)
	ON_MESSAGE(UM_LBUTDOWN, onLButtonDown)
	ON_MESSAGE(UM_DBLCLICK, onDblClick)
		
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CHManualEventControl::OnInitDialog() 
{
	w = new CGraphicWnd(this);
	INITW(w);
	
	
	w->destroyBackground (IDBACKG);
	w->addBackgroundColor(IDBACKG,RGB(240,240,250));
	w->setBackground (COLOR_VERDE5);	
	w->addBackgroundColor(IDBBKYELLOW_DE,RGB(255,255,207));
	w->addBackgroundColor(IDBCK ,RGB(240,240,250));
	w->addBackgroundColor(IDBCK2,RGB(209,209,209));
	w->addBackgroundColor(IDB_CK1_M ,RGB(74,149,149));
	w->addBackgroundColor(IDB_CK2_M ,RGB(183,220,180));
		
	w->addColorSet		 (IDCOL,0                ,COLOR_DEFAULT_OFF,COLOR_DEFAULT_HITX,COLOR_DEFAULT_HIGH,COLOR_DEFAULT_L3D,0xFFFFFF,COLOR_DEFAULT_D3D);
	w->addColorSet       (BLUE_DE  ,RGB( 50, 50,200),COLOR_DEFAULT_OFF,COLOR_DEFAULT_HITX,COLOR_DEFAULT_HIGH,COLOR_DEFAULT_L3D,COLOR_DEFAULT_N3D,COLOR_DEFAULT_D3D);
	w->addColorSet       (RED_DE   ,RGB(250, 50, 50),COLOR_DEFAULT_OFF,COLOR_DEFAULT_HITX,COLOR_DEFAULT_HIGH,COLOR_DEFAULT_L3D,COLOR_DEFAULT_N3D,COLOR_DEFAULT_D3D);
	
	
	w->addFont           (IDFNTB_DE,5,13,1,0,0,0,_T("Tahoma"));	
	w->addFont           (IDFNTBG_DE,8,18,1,0,0,0,_T("Tahoma"));	
	w->addFont           (IDFNTBOLD_DE, 8,20,1,0,0,0,_T("Arial"));		
	w->addFont           (IDFNTBG1_DE,6,15,1,0,0,0,_T("Tahoma"));	
	w->addFont           (IDFNTBG2_DE,6,17,1,0,0,0,_T("Tahoma"));	
	w->addFont           (IDFNTGRID2_DE,5,14,1,0,0,0,_T("Arial"));	
	w->addFont           (IDFNTX_DE,5,13,0,0,1,0,_T("Tahoma"));
	w->addFont           (IDFNTNEW_DE,4,12,1,0,0,0,_T("Tahoma"));

	w->addFont           (IDFNTGRID_BIG,12,24,1,0,0,0,_T("Verdana"));	
	w->addFont           (IDFNTGRID2_MEDIUM,8,20,1,0,0,0,_T("Verdana"));	
		
	
	w->addBackgroundBitmap(IDBCKBROWN2_DE	,IDB_BACKBROWN2);
	w->addBackgroundBitmap(IDBCKBROWN3_DE	,IDB_BACKBROWN3);
	w->addBitmapT(BMP_CHECK_DE			,IDB_CH_CHECK);

	CString aux=_T("");
				
		
	// Match Results
	w->createLabel (LBL_MATCH_RESULT,CRect(INIX+SERVICE_WIDTH,INIY,INIX+SERVICE_WIDTH+PLAYERS_WIDTH,INIY+CELL_HEIGHT),"Match Results",BORDER_SINGLE,JUST_CENTER,IDBCKBROWN2_DE ,IDCOL,IDFNTBOLD_DE);

	// Match 
	w->createLabel (LBL_MATCH_CAB,CRect(INIX+SERVICE_WIDTH+PLAYERS_WIDTH,INIY,INIX+SERVICE_WIDTH+PLAYERS_WIDTH+WIDTH_CELL,INIY+CELL_HEIGHT),"Match",BORDER_SINGLE,JUST_CENTER,IDBCKBROWN2_DE ,BLUE_DE,IDFNTB_DE);
			
	// Frame Match Result 1
	w->createFrame(FRMMATCH_RESULT1,CRect(INIX+SERVICE_WIDTH, INIY+CELL_HEIGHT,INIX+SERVICE_WIDTH+PLAYERS_WIDTH, INIY+CELL_HEIGHT*3),BORDER_3DUP,IDCOL);
	
	// Frame Match Result 2
	w->createFrame(FRMMATCH_RESULT2,CRect(INIX+SERVICE_WIDTH, INIY+CELL_HEIGHT*3,INIX+SERVICE_WIDTH+PLAYERS_WIDTH, INIY+CELL_HEIGHT*5),BORDER_3DUP,IDCOL);

	// Labels que contendran el nombre del tio 
	if(pMatchResult1)
		paintMatchResultHome();
		
	if(pMatchResult2)
		paintMatchResultAway();
		

	// Label de informacion del status
	w->createButton(BU_STATUS,CRect(45,10,110,45), putStatus(),IDBCKBROWN2_DE,IDCOL,IDFNTB_DE);
	w->setToolTip(BU_FINISH ,"Match Status");

	w->createButton(BU_FINISH,CRect(140, 10,205,45),"FINISH",IDBCKBROWN2_DE,IDCOL,IDFNTBG_DE);

	w->setToolTip(BU_FINISH ,"Finish the Match");
	

	// Menu de eleccion de DSQ,RET,DNS u OK
	w->createMenu(MENU_INCIDENCE1,100,22,IDBCK,IDCOL,IDFNTB_DE,IDBCK2,IDCOL);
	w->createMenu(MENU_INCIDENCE2,100,22,IDBCK,IDCOL,IDFNTB_DE,IDBCK2,IDCOL);

	
	doEditFormat();

		
	// Boton de salvar información a capón
	w->addBitmapT(BMP_SAVE, IDB_SAVE);
	w->createButton(BU_SAVE_ALL,CRect(230,10,290,45), "Save",IDBCKBROWN2_DE,IDCOL,IDFNTB_DE);
	w->changeBmp(BU_SAVE_ALL, BMP_SAVE, JUST_LEFT);
	w->setToolTip(BU_SAVE_ALL ,"Save Match Information");

	w->setFocus(ED_MATCH1);

	createTypeResults();
	//createPressTypeResults();

	createGridBeforeAfter();
	fillGrid();

	paintMatchResult();
	changePress();

	// Habilito o desabilito controles dependiendo del status del partidoç
	if(pMatch->getStatus()==CHMemoryDataBase::eFinished)
		 disableEnableControls(false);
	else disableEnableControls(true);
	
	CDialog::OnInitDialog();
	
	return FALSE;  // return TRUE unless you set the focus to a control
              // EXCEPTION: OCX Property Pages should return FALSE
}

void CHManualEventControl::createTypeResults()
{
	
	w->createLabel (LBL_EVENTS_DE,    CRect(INIX+SERVICE_WIDTH,INIY+CELL_HEIGHT*5+35,INIX+SERVICE_WIDTH+550,INIY+CELL_HEIGHT*5+45),"Possibles Results",BORDER_NONE,JUST_LEFT,IDBCK,IDCOL,FONTMAX);
	w->createLabel (LBL_LINEA_DE,    CRect(INIX+SERVICE_WIDTH,INIY+CELL_HEIGHT*5+47,INIX+SERVICE_WIDTH+550,INIY+CELL_HEIGHT*5+50),"",BORDER_NONE,JUST_LEFT,IDBCK_BOX);
	// Frame Type Results
	w->createFrame(FRM_TYPE_RESULTS,CRect(INIX+SERVICE_WIDTH, INIY+CELL_HEIGHT*5+50,INIX+SERVICE_WIDTH+550, INIY+CELL_HEIGHT*5+170),BORDER_3DUP,IDCOL);
}	
void CHManualEventControl::createPressTypeResults()
{
		
	w->createPress(BU_ONE_ZERO,CRect(INIX+SERVICE_WIDTH+15,INIY+CELL_HEIGHT*5+60,INIX+SERVICE_WIDTH+130,INIY+CELL_HEIGHT*5+100), " 1 : 0 ",1000,FALSE,IDBCK_BUT,IDCOL,IDFNT_BIG);
	w->createPress(BU_HALF_HALF,CRect(INIX+SERVICE_WIDTH+150,INIY+CELL_HEIGHT*5+60,INIX+SERVICE_WIDTH+265,INIY+CELL_HEIGHT*5+100), " 1/2 : 1/2 ",1000,FALSE,IDBCK_BUT,IDCOL,IDFNTBG_DE);
	w->createPress(BU_ZERO_ONE,CRect(INIX+SERVICE_WIDTH+285,INIY+CELL_HEIGHT*5+60,INIX+SERVICE_WIDTH+400,INIY+CELL_HEIGHT*5+100), " 0 : 1 ",1000,FALSE,IDBCK_BUT,IDCOL,IDFNT_BIG);
	w->createPress(BU_EMPTY,CRect(INIX+SERVICE_WIDTH+420,INIY+CELL_HEIGHT*5+60,INIX+SERVICE_WIDTH+535,INIY+CELL_HEIGHT*5+100), " Empty ",1000,FALSE,IDBCK_BUT,IDCOL,IDFNT_BIG);

	w->createPress(BU_ONE_ZERO_F,CRect(INIX+SERVICE_WIDTH+15,INIY+CELL_HEIGHT*5+120,INIX+SERVICE_WIDTH+130,INIY+CELL_HEIGHT*5+160), " 1F : 0F ",1000,FALSE,IDBCK_BUT,IDCOL,IDFNT_BIG);
	w->createPress(BU_ZERO_ONE_F,CRect(INIX+SERVICE_WIDTH+150,INIY+CELL_HEIGHT*5+120,INIX+SERVICE_WIDTH+265,INIY+CELL_HEIGHT*5+160), " 0F : 1F ",1000,FALSE,IDBCK_BUT,IDCOL,IDFNT_BIG);
	w->createPress(BU_ZERO_ZERO_F,CRect(INIX+SERVICE_WIDTH+285,INIY+CELL_HEIGHT*5+120,INIX+SERVICE_WIDTH+400,INIY+CELL_HEIGHT*5+160), " 0F : 0F ",1000,FALSE,IDBCK_BUT,IDCOL,IDFNT_BIG);
	//w->createPress(BU_NEXT,CRect(INIX+SERVICE_WIDTH+420,INIY+CELL_HEIGHT*5+120,INIX+SERVICE_WIDTH+535,INIY+CELL_HEIGHT*5+160), " Next ",1000,FALSE,IDBCK_BUT,IDCOL,IDFNT_BIG);

}	
void CHManualEventControl::createGridBeforeAfter()
{
	w->createGrid   (LST_MATCHES, CRect(INIX+SERVICE_WIDTH+PLAYERS_WIDTH+WIDTH_CELL+20,20,INIX+SERVICE_WIDTH+PLAYERS_WIDTH+WIDTH_CELL+300,182),BORDER_SINGLE,54,IDBCK_GRID,IDCOL,IDFNT,false);
	w->gridLineColor(LST_MATCHES,GET_COLOR_DEFAULT_LINE,GET_COLOR_DEFAULT_LINE);
	w->addGridColumn(LST_MATCHES,"Game" ,JUST_CENTER, 40);
	w->addGridColumn(LST_MATCHES,"Games" ,JUST_CENTER, 240);

	w->addBitmapT(BMP_PREVIOUS_M, IDB_BMP_BEFORE);
	w->addBitmapT(BMP_POINT_M, IDB_BMP_POINT);
	w->addBitmapT(BMP_NEXT_M, IDB_BMP_NEXT);

	// Previous Match
	w->createButton(BU_PREVIOUS_M,CRect(INIX+SERVICE_WIDTH+PLAYERS_WIDTH+WIDTH_CELL+305,40,INIX+SERVICE_WIDTH+PLAYERS_WIDTH+WIDTH_CELL+337,70), "",IDBCK,IDCOL,IDFNTB_DE);
	w->changeBmp(BU_PREVIOUS_M, BMP_PREVIOUS_M, JUST_CENTER);
	w->setToolTip(BU_PREVIOUS_M ,"Previous Match");

	// Actual Match
	w->createLabel (LBL_POINT,CRect(INIX+SERVICE_WIDTH+PLAYERS_WIDTH+WIDTH_CELL+310,90,INIX+SERVICE_WIDTH+PLAYERS_WIDTH+WIDTH_CELL+330,120),"" ,BORDER_NONE,JUST_CENTER,IDBCK ,BLUE_DE,IDFNTGRID2_DE);
	w->changeBmp(LBL_POINT, BMP_POINT_M, JUST_CENTER);
	
	// Next Match
	w->createButton(BU_NEXT_M,CRect(INIX+SERVICE_WIDTH+PLAYERS_WIDTH+WIDTH_CELL+305,135,INIX+SERVICE_WIDTH+PLAYERS_WIDTH+WIDTH_CELL+337,165), "",IDBCK,IDCOL,IDFNTB_DE);
	w->changeBmp(BU_NEXT_M, BMP_NEXT_M, JUST_CENTER);
	w->setToolTip(BU_NEXT_M ,"Next Match");

	/*// Matches of Pool
	w->createPress(BU_POOL_SELECT,CRect(INIX+SERVICE_WIDTH+PLAYERS_WIDTH+WIDTH_CELL+20,5,INIX+SERVICE_WIDTH+PLAYERS_WIDTH+WIDTH_CELL+80,20), "Pool",1001,FALSE,IDBCKBROWN3_DE,IDCOL,IDFNT_MIN);
	w->setToolTip(BU_POOL_SELECT ,"Matches of Pool");

	// Matches of Pool
	w->createPress(BU_DATE_SELECT,CRect(INIX+SERVICE_WIDTH+PLAYERS_WIDTH+WIDTH_CELL+80,5,INIX+SERVICE_WIDTH+PLAYERS_WIDTH+WIDTH_CELL+140,20), "Date",1001,FALSE,IDBCK_BUT,IDCOL,IDFNT_MIN);
	w->setToolTip(BU_DATE_SELECT ,"Matches by Date");*/
	
	w->createCheck(CH_OFFICIAL,CRect(INIX+SERVICE_WIDTH+PLAYERS_WIDTH+WIDTH_CELL+200,5,INIX+SERVICE_WIDTH+PLAYERS_WIDTH+WIDTH_CELL+300,20),"Automatic Finish",JUST_RIGHT,FALSE,IDBCK,IDCOL,IDFNT);
	
	
}	

void CHManualEventControl::fillGrid()
{
	w->gridDeleteAllItems(LST_MATCHES);

	CHMatch *pMatchPrv=0,*pMatchNext=0;

	pMatchPrv=getPreviousResult();
	pMatchNext=getNextResult();
	
	w->addGridLine(LST_MATCHES,LPARAM(pMatchPrv),"");
	w->addGridLine(LST_MATCHES,LPARAM(pMatch),"");
	w->addGridLine(LST_MATCHES,LPARAM(pMatchNext),"");

	w->selectItem(LST_MATCHES,LPARAM(pMatch));
}
BOOL CHManualEventControl::onPaintGrid(UINT idGrid,GridItem *gi)
{
	if (!gi) return FALSE;

	switch(idGrid)
	{
		case LST_MATCHES:
		{
			if (gi->sel)	
				gi->cdc->FillSolidRect(gi->rc,GET_COLOR_DEFAULT_HIGH);
			else
			{
				if(gi->y%2)
					 gi->cdc->FillSolidRect(gi->rc,RGB(255,255,255));
				else gi->cdc->FillSolidRect(gi->rc,RGB(243,243,243));
			}

			CHMatch* pMatchAux=(CHMatch*) gi->lParam;
			if (!pMatchAux) 
			{
				if(gi->x==0)
					 w->paintGridText(gi->rc.Width()/2,20,"",JUST_CENTER);
				else eventControlOp.paintShadow(gi->cdc,gi->rc.Width()/2+30,15,"No Match",COLOR_GRIS,1,IDFNTBG2_DE,w,COLOR_NEGRO); 
					
				return TRUE;
			}
			

			switch(gi->x)
			{
				case 0: // Match Number
				{
					char tmp[10];
					eventControlOp.paintShadow(gi->cdc,gi->rc.Width()/2,15,itoa(pMatchAux->getIdParent(),tmp,10),COLOR_NARANJA,1,IDFNTBG2_DE,w,COLOR_NEGRO); 
					//w->paintGridText(gi->rc.Width()/2,25,itoa(pMatchAux->getCode(),tmp,10),JUST_CENTER);
				}
				break;
				case 1: // Competitors
				{
					
					eventControlOp.paintShadow(gi->cdc,gi->rc.left+15,15,pMatchAux->getRoundAsString(false,false),COLOR_NARANJA,1,IDFNTBG2_DE,w,COLOR_NEGRO); 
					
					CHMatchResult *pMatchResultAux1=pMatchAux->getMatchResultHome();
					CHMatchResult *pMatchResultAux2=pMatchAux->getMatchResultAway();
					// Match Result 1
					if(pMatchResultAux1 && pMatchResultAux1->getRegister())
					{
						eventControlOp.paintShadow(gi->cdc,gi->rc.Width()/2+30,1,pMatchResultAux1->getPrnLName().toAscii(),COLOR_NEGRO,1,IDFNTBG2_DE,w,COLOR_NEGRO); 
						if (pMatchAux->getStatus()>=CHMemoryDataBase::eRunning)
							eventControlOp.paintShadow(gi->cdc,gi->rc.Width()/2+120,1,pMatchResultAux1->getPointsAsString(),COLOR_NEGRO,1,IDFNTBG2_DE,w,COLOR_ROJO1); 

					}
					else
					{
						if (pMatchResultAux1->getBye())
							eventControlOp.paintShadow(gi->cdc,gi->rc.Width()/2+30,1,"-Bye-",COLOR_NEGRO,1,IDFNTBG2_DE,w,COLOR_ROJO1); 
						else
							eventControlOp.paintShadow(gi->cdc,gi->rc.Width()/2+30,1,"Not Assigned-Home",COLOR_NEGRO,1,IDFNTBG2_DE,w,COLOR_ROJO1); 
					}
					
					
					// Versus
					eventControlOp.paintShadow(gi->cdc,gi->rc.Width()/2+30,15,"vs",COLOR_NEGRO,1,IDFNTBG2_DE,w,COLOR_NEGRO); 
					
					// Match Result 2
					
					if(pMatchResultAux2 && pMatchResultAux2->getRegister())
					{
						eventControlOp.paintShadow(gi->cdc,gi->rc.Width()/2+30,30,pMatchResultAux2->getPrnLName().toAscii(),COLOR_NEGRO,1,IDFNTBG2_DE,w,COLOR_NEGRO); 
						if (pMatchAux->getStatus()>=CHMemoryDataBase::eRunning)
							eventControlOp.paintShadow(gi->cdc,gi->rc.Width()/2+120,30,pMatchResultAux2->getPointsAsString(),COLOR_NEGRO,1,IDFNTBG2_DE,w,COLOR_ROJO1); 
					}
					else
					{
						if (pMatchResultAux2->getBye())
							eventControlOp.paintShadow(gi->cdc,gi->rc.Width()/2+30,30,"-Bye-",COLOR_NEGRO,1,IDFNTBG2_DE,w,COLOR_ROJO1); 
						else
							eventControlOp.paintShadow(gi->cdc,gi->rc.Width()/2+30,30,"Not Assigned-Away",COLOR_NEGRO,1,IDFNTBG2_DE,w,COLOR_ROJO1); 
					}
					
				}
				break;
			}
			return TRUE;
		}
		break;
	}
	

	return FALSE;

}

LRESULT CHManualEventControl::onClick(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch(wParam)
	{
				
		case BU_FINISH:
		{	
			saveAll();
			//calculateAll();
			paintMatchResult();
		}
		break;
		case BU_SAVE_ALL:
		{
			saveAll(false);
		}
		break;
		
		case BU_STATUS:
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
					clearResults();

				// Si el Status es igual a Protested tengo que desprogresar el partido
				if(pMatch->getStatus()==CHMemoryDataBase::eFinished ||
				   pMatch->getStatus()==CHMemoryDataBase::eProtested)
				{
					
					eventControlOp.finishMatch(pMatch);
					if(pMatch->getStatus()==CHMemoryDataBase::eFinished)
						 disableEnableControls(false);
					else disableEnableControls(true);
				}
											
				paintMatchStatus();
				
			}
			break;
		}
				
		case LBL_MATCHRESNOC1:
		case LBL_MATCHRESNOC2:
		{
 			onContexMenu(lParam,wParam);
			break;
		}
		case MENU_INCIDENCE1:
			 onQualitativeMenu1((GQualitative*)lParam);
			 break;
		case MENU_INCIDENCE2:
			 onQualitativeMenu2((GQualitative*)lParam);
			 break;

		case BU_ONE_ZERO:
		case BU_HALF_HALF:
		case BU_ZERO_ONE:
		case BU_EMPTY:
		case BU_ONE_ZERO_F:
		case BU_ZERO_ONE_F:
		case BU_ZERO_ZERO_F:
		//case BU_NEXT:
			if(pMatchResult1 && pMatchResult2)
			{
				eventControlOp.putScore( getEventFromButton(short(wParam)),pMatch);
				if(w->getCheck(CH_OFFICIAL))
					finishMatch(pMatch);
				paintScore();
				changeBackButton(short(wParam));
				paintMatchStatus();
				if(w->getCheck(CH_OFFICIAL))
					SendMessage(UM_CLICK,BU_NEXT_M,0);
			}
			break;
		case BU_PREVIOUS_M:
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
		case BU_NEXT_M:
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
		case BU_COLOR_HOME:
		{
			pMatchResult1->setColor(!pMatchResult1->getColor());
			pMatchResult2->setColor(pMatchResult1->getColorVersus());
			theApp.queueOut(pMatchResult1);
			theApp.queueOut(pMatchResult2);
			theApp.out(TRN_CHANGE_MATCHRES);
			paintColors();
			break;
		}
		case BU_COLOR_AWAY:
		{
			pMatchResult2->setColor(!pMatchResult2->getColor());
			pMatchResult1->setColor(pMatchResult2->getColorVersus());
			theApp.queueOut(pMatchResult1);
			theApp.queueOut(pMatchResult2);
			theApp.out(TRN_CHANGE_MATCHRES);
			paintColors();
			break;
		}
		
		case BU_POOL_SELECT:
		case BU_DATE_SELECT:
			poolMatches=!poolMatches;
			changeSelectionMatches();	
			break;

		
	}
	return 0;
}

void CHManualEventControl::onLButtonDown (WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);
}
LRESULT CHManualEventControl::onDblClick(WPARAM wParam, LPARAM lParam)
{
	if (wParam==LST_MATCHES)
	{
		WORD y=HIWORD(lParam);
		WORD x=LOWORD(lParam);
		
		CHMatch* pMatchAux = 0;
		
		pMatchAux=(CHMatch*)w->getGridLParam(LST_MATCHES,y);
		
		if(!pMatchAux)
			return false;

		pMatch=pMatchAux;		
		pMatchResult1=pMatch->getMatchResultHome();
		pMatchResult2=pMatch->getMatchResultAway();
		paintAll();

		
				
	}
	return 0;
}
void CHManualEventControl::onContexMenu(LPARAM lParam, size_t id)
{
 	 
	GQualitative *pQualitative=0;
	RWBoolean incidence=false;
	if(pMatchResult1 && id==LBL_MATCHRESNOC1)
	{
		w->delMenuItems(MENU_INCIDENCE1);
		short i=1;
		RWSetIterator it(CHMemoryDataBase::getColQualitatives());
		while((pQualitative=(GQualitative*)it())!=0)
		{
			if(pMatchResult1->getQualitative()==pQualitative)
			{	w->addMenuItem(MENU_INCIDENCE1,SUBMENU_INCIDENCE11+i,0,pQualitative->getLDescription(),LPARAM(pQualitative),BMP_CHECK_DE);	
				incidence=true;
			}
			else w->addMenuItem(MENU_INCIDENCE1,SUBMENU_INCIDENCE11+i,0,pQualitative->getLDescription(),LPARAM(pQualitative));	
			i++;
		}
						
		w->showMenu(MENU_INCIDENCE1);
	}
	else if(pMatchResult2 && id==LBL_MATCHRESNOC2)
	{
		w->delMenuItems(MENU_INCIDENCE2);
		short i=1;
		RWSetIterator it(CHMemoryDataBase::getColQualitatives());
		while((pQualitative=(GQualitative*)it())!=0)
		{
			if(pMatchResult2->getQualitative()==pQualitative)
			{	 w->addMenuItem(MENU_INCIDENCE2,SUBMENU_INCIDENCE21+i,0,pQualitative->getLDescription(),LPARAM(pQualitative),BMP_CHECK_DE);	
				 incidence=true;
			}
			else w->addMenuItem(MENU_INCIDENCE2,SUBMENU_INCIDENCE21+i,0,pQualitative->getLDescription(),LPARAM(pQualitative));	
			i++;
		}
		
		w->showMenu(MENU_INCIDENCE2);
	}
	
	UNREFERENCED_PARAMETER(lParam);
}

void CHManualEventControl::onQualitativeMenu1(GQualitative *pQualitative)
{
	if(LPARAM(pQualitative)>1)
	{	
		if(pQualitative->getCode()!=OK)
		{
			w->changeBck(LBL_MATCHRESNAME1,IDBCKBROWN3_DE);
			w->changeBck(LBL_MATCHRESNOC1,IDBCKBROWN3_DE);
		}
		else
		{
			w->changeBck(LBL_MATCHRESNAME1,IDBCKBROWN2_DE);
			w->changeBck(LBL_MATCHRESNOC1,IDBCKBROWN2_DE);
		}
		pMatchResult1->setQualitative(pQualitative->getCode());
		
		theApp.queueOut(pMatchResult1);
		theApp.out(TRN_CHANGE_MATCHRES);
		
		if (::msg("Attention","Do you want to put incidence in the pool?",
			   ICO_Q,MSG_YESNO)==RET_YES)	
		{
			CHPoolResult * pPoolResult=(CHPoolResult*)pMatchResult1->getPoolResult();
			if(pPoolResult)
			{
				pPoolResult->setQualitative(pQualitative->getCode());
				//theApp.updatePoolResult(*pPoolResult);
				theApp.queueOut(pPoolResult);
				theApp.out(TRN_CHANGE_POOLRES);
			}

			CHEventResult *pEventResult=(CHEventResult*)CHMemoryDataBase::findEventResult(pMatchResult1->getInscription());
			if(pEventResult)
			{
				pEventResult->setQualitative(pQualitative->getCode());
				theApp.queueOut(pEventResult);
				theApp.out(TRN_CHANGE_EVENT_RESULT);
			}
		}
		calculateAll();
		
	}
	
	paintMatchResult();
	w->redraw(LBL_MATCHRESNAME1);
	w->redraw(LBL_MATCHRESNOC1);
}

void CHManualEventControl::onQualitativeMenu2(GQualitative *pQualitative)
{
	if(LPARAM(pQualitative)>1)
	{
		if(pQualitative->getCode()!=OK)
		{
			w->changeBck(LBL_MATCHRESNAME2,IDBCKBROWN3_DE);
			w->changeBck(LBL_MATCHRESNOC2,IDBCKBROWN3_DE);
		}
		else
		{
			w->changeBck(LBL_MATCHRESNAME2,IDBCKBROWN2_DE);
			w->changeBck(LBL_MATCHRESNOC2,IDBCKBROWN2_DE);
		}
		pMatchResult2->setQualitative(pQualitative->getCode());
		
		//theApp.updateMatchResult(*pMatchResult2);
		theApp.queueOut(pMatchResult2);
		theApp.out(TRN_CHANGE_MATCHRES);
		if (::msg("Attention","Do you want to put incidence in the pool?",
			   ICO_Q,MSG_YESNO)==RET_YES)	
		{
			CHPoolResult * pPoolResult=(CHPoolResult*)pMatchResult2->getPoolResult();
			if(pPoolResult)
			{
				pPoolResult->setQualitative(pQualitative->getCode());
				//theApp.updatePoolResult(*pPoolResult);
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
		calculateAll();
	}
	
	w->redraw(LBL_MATCHRESNAME2);
	w->redraw(LBL_MATCHRESNOC2);
}

BOOL CHManualEventControl::DestroyWindow() 
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

void CHManualEventControl::onOK() 
{
	CDialog::OnOK();
}

RWCString CHManualEventControl::putStatus()
{
	if(pMatch)
	{
		
		GStatus *pStatus=CHMemoryDataBase::findStatus(pMatch->getStatus());
		if(pStatus)
			return pStatus->getLDescription().toMultiByte();
		
	}
	return NULLRWSTRING;
}

void CHManualEventControl::disableEnableControls(RWBoolean enable)
{
	// Labels que contendran el nombre del tio 
	w->enable (LBL_MATCHRESNAME1,enable);
	w->enable (LBL_MATCHRESNOC1,enable);
		
	// Edit de Partido
	w->enable(ED_MATCH1,enable);
	w->enable(ED_MATCH2,enable);	
	
	w->enable (LBL_MATCHRESNAME2,enable);
	w->enable (LBL_MATCHRESNOC2,enable);
	// Edit de Partido
	
	w->enable(BU_FINISH,enable);
	for(size_t i=0;i<8;i++)
		w->enable(BU_ONE_ZERO+i,enable);
	w->enable(BU_COLOR_HOME,enable);
	w->enable(BU_COLOR_AWAY,enable);

}

void CHManualEventControl::paintMatchStatus()
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
				w->changeTxt(BU_STATUS, (CString)pStatus->getLDescription());
				break;
			}
		}
	}
	
	if(!active) 
		w->changeTxt(BU_STATUS, "");
}

void CHManualEventControl::saveAll(RWBoolean status)
{
	// Le pongo a Running para despues poderle pasar a Unofficial
	if(status)
	{
		pMatch->setStatus(CHMemoryDataBase::eRunning);
		pStatusMngt->run(*pMatch, CHMemoryDataBase::eUnofficial,false);
		paintMatchStatus();
		
		theApp.queueOut(pMatch);
		theApp.out(TRN_CHANGE_MATCH);
	}			
	
	// SAVE MATCH RESULTS
	if(pMatchResult1)
	{
		pMatchResult1->setPoints(float(atof(w->getTxt(ED_MATCH1))));
		theApp.queueOut(pMatchResult1);
	}
	if(pMatchResult2)
	{
		pMatchResult2->setPoints(float(atof(w->getTxt(ED_MATCH2))));
		theApp.queueOut(pMatchResult2);
	}
	if(pMatchResult1 || pMatchResult2)
		theApp.out(TRN_CHANGE_MATCHRES);
		
}

void CHManualEventControl::paintResults()
{
	// Puntos totales en el partido
	CString GAME=_T("");
	
	w->changeTxt(ED_MATCH1,pMatchResult1->getPointsAsString());
	w->changeTxt(ED_MATCH2,pMatchResult2->getPointsAsString());
	
}

void CHManualEventControl::paintMatchResultHome()
{
	// Team flags
	w->destroyControl(FLAG_HOME);
	// Button Color  
	w->destroyControl(BU_COLOR_HOME);
		
	GRegister *pRegister=pMatchResult1->getRegister();
	if(pRegister)
	{
		getFlag(pMatchResult1->getGroup(),SML,m_pBmpFlag[0]);			
	 	w->createUserBitmap(FLAG_HOME,CRect(INIX+SERVICE_WIDTH+NAME_WIDTH,INIY+CELL_HEIGHT,INIX+SERVICE_WIDTH+NAME_WIDTH+NOC_WIDTH,INIY+CELL_HEIGHT*2),m_pBmpFlag[0],TRUE,BORDER_NONE);
		w->createButton(BU_COLOR_HOME,CRect(INIX,75,INIX+25,107), "",IDBCK,IDCOL,IDFNTB_DE);
		if(pMatchResult1->getColor()==CHMatchResult::eWhite)
			 w->changeBmp(BU_COLOR_HOME, BMP_WHITE, JUST_CENTER);
		else w->changeBmp(BU_COLOR_HOME, BMP_BLACK, JUST_CENTER);
		w->setToolTip(BU_COLOR_HOME ,"Change Color");

		if(pMatchResult1->isQualitative())
		{
			w->createLabel (LBL_MATCHRESNAME1,CRect(INIX+SERVICE_WIDTH,INIY+CELL_HEIGHT,INIX+SERVICE_WIDTH+NAME_WIDTH,INIY+CELL_HEIGHT*3),pRegister->getScbLName() ,BORDER_SINGLE,JUST_CENTER,IDBCKBROWN3_DE ,BLUE_DE,IDFNTGRID2_DE);		
			w->createLabelEx (LBL_MATCHRESNOC1 ,CRect(INIX+SERVICE_WIDTH+NAME_WIDTH,INIY+CELL_HEIGHT*2,INIX+SERVICE_WIDTH+NAME_WIDTH+NOC_WIDTH,INIY+CELL_HEIGHT*3),pRegister->getGroup(),BORDER_SINGLE,JUST_CENTER,IDBCKBROWN3_DE ,BLUE_DE,IDFNTX_DE);		
		}
		else
		{	w->createLabel (LBL_MATCHRESNAME1,CRect(INIX+SERVICE_WIDTH,INIY+CELL_HEIGHT,INIX+SERVICE_WIDTH+NAME_WIDTH,INIY+CELL_HEIGHT*3),pRegister->getScbLName() ,BORDER_SINGLE,JUST_CENTER,IDBCKBROWN2_DE ,BLUE_DE,IDFNTGRID2_DE);
			w->createLabelEx (LBL_MATCHRESNOC1 ,CRect(INIX+SERVICE_WIDTH+NAME_WIDTH,INIY+CELL_HEIGHT*2,INIX+SERVICE_WIDTH+NAME_WIDTH+NOC_WIDTH,INIY+CELL_HEIGHT*3),pRegister->getGroup(),BORDER_SINGLE,JUST_CENTER,IDBCKBROWN2_DE ,BLUE_DE,IDFNTX_DE);
		}
	}
	
	// Edit de Partido
	w->createEdit(ED_MATCH1, CRect(INIX+SERVICE_WIDTH+PLAYERS_WIDTH,INIY+CELL_HEIGHT,INIX+SERVICE_WIDTH+PLAYERS_WIDTH+WIDTH_CELL, INIY+CELL_HEIGHT*3),"",BORDER_SINGLE,JUST_CENTER ,IDBBKYELLOW_DE,RED_DE,IDFNTBG1_DE);
	
}

void CHManualEventControl::paintMatchResultAway()
{
	// Team flags
	w->destroyControl(FLAG_AWAY);
	// Button Color  
	w->destroyControl(BU_COLOR_AWAY);
	
	GRegister *pRegister=pMatchResult2->getRegister();
	if(pRegister)
	{
		getFlag(pMatchResult2->getGroup(),SML,m_pBmpFlag[1]);			
	 	w->createUserBitmap(FLAG_AWAY,CRect(INIX+SERVICE_WIDTH+NAME_WIDTH,INIY+CELL_HEIGHT*3,INIX+SERVICE_WIDTH+NAME_WIDTH+NOC_WIDTH,INIY+CELL_HEIGHT*4),m_pBmpFlag[1],TRUE,BORDER_NONE);
		
		w->createButton(BU_COLOR_AWAY,CRect(INIX,113,INIX+25,143), "",IDBCK,IDCOL,IDFNTB_DE);
		if(pMatchResult2->getColor()==CHMatchResult::eWhite)
			 w->changeBmp(BU_COLOR_AWAY, BMP_WHITE, JUST_CENTER);
		else w->changeBmp(BU_COLOR_AWAY, BMP_BLACK, JUST_CENTER);
		w->setToolTip(BU_COLOR_AWAY ,"Change Color");
		
		if(pMatchResult2->isQualitative())
		{	w->createLabel (LBL_MATCHRESNAME2,CRect(INIX+SERVICE_WIDTH,INIY+CELL_HEIGHT*3,INIX+SERVICE_WIDTH+NAME_WIDTH,INIY+CELL_HEIGHT*5),pRegister->getScbLName() ,BORDER_SINGLE,JUST_CENTER,IDBCKBROWN3_DE ,BLUE_DE,IDFNTGRID2_DE);		
			w->createLabelEx (LBL_MATCHRESNOC2 ,CRect(INIX+SERVICE_WIDTH+NAME_WIDTH,INIY+CELL_HEIGHT*4,INIX+SERVICE_WIDTH+NAME_WIDTH+NOC_WIDTH,INIY+CELL_HEIGHT*5),pRegister->getGroup(),BORDER_SINGLE,JUST_CENTER,IDBCKBROWN3_DE ,BLUE_DE,IDFNTX_DE);		
		}
		else
		{	w->createLabel (LBL_MATCHRESNAME2,CRect(INIX+SERVICE_WIDTH,INIY+CELL_HEIGHT*3,INIX+SERVICE_WIDTH+NAME_WIDTH,INIY+CELL_HEIGHT*5),pRegister->getScbLName() ,BORDER_SINGLE,JUST_CENTER,IDBCKBROWN2_DE ,BLUE_DE,IDFNTGRID2_DE);		
			w->createLabelEx (LBL_MATCHRESNOC2 ,CRect(INIX+SERVICE_WIDTH+NAME_WIDTH,INIY+CELL_HEIGHT*4,INIX+SERVICE_WIDTH+NAME_WIDTH+NOC_WIDTH,INIY+CELL_HEIGHT*5),pRegister->getGroup(),BORDER_SINGLE,JUST_CENTER,IDBCKBROWN2_DE ,BLUE_DE,IDFNTX_DE);		
		}
	}
	
	// Edit de Partido
	w->createEdit(ED_MATCH2, CRect(INIX+SERVICE_WIDTH+PLAYERS_WIDTH,INIY+CELL_HEIGHT*3,INIX+SERVICE_WIDTH+PLAYERS_WIDTH+WIDTH_CELL, INIY+CELL_HEIGHT*5),"",BORDER_SINGLE,JUST_CENTER ,IDBBKYELLOW_DE,RED_DE,IDFNTBG1_DE);
		
}
void CHManualEventControl::doEditFormat()
{
	w->doEditFormat(ED_MATCH1,"#.#");
	w->doEditFormat(ED_MATCH2,"#.#");
	
}

void CHManualEventControl::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	
	if ( pMatch )
	{
		int focus=w->getFocus();
				
		if(focus>=ED_MATCH1 && focus<=ED_MATCH2)
		{
			/*if ( wParam==38 ) // ARROW_UP
			{				
				if(focus>=ED_MATCH2 && focus<=ED_TIE5_PLAY2)
					w->setFocus(focus-11);
			}
			if ( wParam==40 ) // ARROW_DOWN
			{				
				if(focus>=ED_MATCH1 && focus<=ED_TIE5_PLAY2)
					w->setFocus(focus+11);
			}
			if ( wParam==39 ) // ARROW_RIGHT
			{				
				if(focus>=ED_MATCH1 && focus<ED_TIE5_PLAY2)
					w->setFocus(focus+1);
			}
			if ( wParam==37 ) // ARROW_LEFT
			{				
				if(focus>ED_MATCH1 && focus<=ED_TIE5_PLAY2)
					w->setFocus(focus-1);
			}*/
		}
		
	}
	switch(wParam)
	{
		case 27:
			OnCancel();
			break;
			
	}
}

void CHManualEventControl::paintMatchResult()
{
	if(pMatchResult1) 
		w->changeTxt(ED_MATCH1,pMatchResult1->getPointsAsString());
	else
		w->changeTxt(ED_MATCH1,"");
			
	
	if(pMatchResult2)	
		w->changeTxt(ED_MATCH2,pMatchResult2->getPointsAsString());
	else
		w->changeTxt(ED_MATCH2,"");
	
	w->redraw(ED_MATCH1);
	w->redraw(ED_MATCH2);
}

void CHManualEventControl::clearResults()
{
	if(eventControlOp.clearResults(pMatch))
	{
		// Repaint all.
		paintAll();
		
	}
}

void CHManualEventControl::calculateAll()
{
	eventControlOp.calculatePointMatchResult(pMatch);
}

void CHManualEventControl::changeBackButton(short button)
{
	for(size_t i=0;i<8;i++)
	{
		w->changeBck(BU_ONE_ZERO+i,IDBCK_BUT);
		RWBoolean check =w->getCheck(BU_ONE_ZERO+i);
		
		w->changeCheck(BU_ONE_ZERO+i,false);
		check =w->getCheck(BU_ONE_ZERO+i);
		w->redraw(BU_ONE_ZERO+i,FALSE);
	}
 
	if(button)
	{
		w->changeBck(button,IDBCKBROWN3_DE);
		w->redraw(button,FALSE);
	}
}	

void CHManualEventControl::paintScore()
{
	paintMatchResult();
	paintQualitatives();
	
}
void CHManualEventControl::paintQualitatives()
{
	if(pMatchResult1 && pMatchResult1->isQualitative())
	{
		w->changeBck(LBL_MATCHRESNAME1,IDBCKBROWN3_DE);
		w->changeBck(LBL_MATCHRESNOC1,IDBCKBROWN3_DE);
			
	}
	else
	{
		w->changeBck(LBL_MATCHRESNAME1,IDBCKBROWN2_DE);
		w->changeBck(LBL_MATCHRESNOC1,IDBCKBROWN2_DE);
	}
	
	if(pMatchResult2 && pMatchResult2->isQualitative())
	{
		w->changeBck(LBL_MATCHRESNAME2,IDBCKBROWN3_DE);
		w->changeBck(LBL_MATCHRESNOC2,IDBCKBROWN3_DE);
	}
	else
	{
		w->changeBck(LBL_MATCHRESNAME2,IDBCKBROWN2_DE);
		w->changeBck(LBL_MATCHRESNOC2,IDBCKBROWN2_DE);
	}
	w->redraw(LBL_MATCHRESNAME1);
	w->redraw(LBL_MATCHRESNOC1);
	w->redraw(LBL_MATCHRESNAME2);
	w->redraw(LBL_MATCHRESNOC2);
}
void CHManualEventControl::changePress()
{
	short button=0;
	
	for(size_t i=0;i<8;i++)
		w->destroyControl(BU_ONE_ZERO+i);

	createPressTypeResults();

	if(pMatchResult1 && pMatchResult2)
	{
		if(pMatchResult1->isQualitative() && pMatchResult2->isQualitative())
			button=BU_ONE_ZERO;
		else if(pMatchResult1->isQualitative())
			button=BU_ZERO_ONE_F;
		else if(pMatchResult2->isQualitative())
			button=BU_ONE_ZERO_F;
		else if(pMatchResult1->getPoints()==0 && pMatchResult2->getPoints==0)
			button=BU_EMPTY;
		else if(pMatchResult1->getPoints()==0 && pMatchResult2->getPoints()==1)
			button=BU_ZERO_ONE;
		else if(pMatchResult1->getPoints()==0.5 && pMatchResult2->getPoints()==0.5)
			button=BU_HALF_HALF;
		else if(pMatchResult1->getPoints()==1 && pMatchResult2->getPoints()==0)
			button=BU_ONE_ZERO;
	}
	
	w->changeCheck(button,TRUE);
	changeBackButton(button);
		
	
}
CHMatch *CHManualEventControl::getPreviousResult()
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
			if( pMatchAux->isConfigured() &&
				pMatchAux->getIdParent()==(pMatch->getIdParent()-1))
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
CHMatch *CHManualEventControl::getNextResult()
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
			if(pMatchAux->isConfigured() &&
			   pMatchAux->getIdParent()==(pMatch->getIdParent()+1))
			{
				pMatchNext=pMatchAux;
				break;
			}
						
		}
	}
	return pMatchNext;

}
void CHManualEventControl::paintHome()
{
 // Team flags
	w->destroyControl(FLAG_HOME);
		
	if(pMatchResult1)
	{
		GRegister *pRegister=pMatchResult1->getRegister();
		if(pRegister)
		{
			getFlag(pMatchResult1->getGroup(),SML,m_pBmpFlag[2]);			
	 		w->createUserBitmap(FLAG_HOME,CRect(INIX+SERVICE_WIDTH+NAME_WIDTH,INIY+CELL_HEIGHT,INIX+SERVICE_WIDTH+NAME_WIDTH+NOC_WIDTH,INIY+CELL_HEIGHT*2),m_pBmpFlag[2],TRUE,BORDER_NONE);
			w->changeTxt (LBL_MATCHRESNAME1,pRegister->getScbLName());
			w->changeTxt (LBL_MATCHRESNOC1 ,pRegister->getGroup());		
					
		}
		else if (pMatchResult1->getBye())
		{
			w->changeTxt (LBL_MATCHRESNAME1,"-Bye-");
			w->changeTxt (LBL_MATCHRESNOC1 ,"");
		}
		else
		{
			w->changeTxt (LBL_MATCHRESNAME1,"Not Assigned");
			w->changeTxt (LBL_MATCHRESNOC1 ,"");
		}

		if(pMatchResult1->getColor()==CHMatchResult::eWhite)
			 w->changeBmp(BU_COLOR_HOME, BMP_WHITE, JUST_CENTER);
		else w->changeBmp(BU_COLOR_HOME, BMP_BLACK, JUST_CENTER);
	}
	else
	{
		w->changeTxt (LBL_MATCHRESNAME1,"");
		w->changeTxt (LBL_MATCHRESNOC1 ,"");
		//w->destroyControl(BU_COLOR_HOME);
	}
	

}
void CHManualEventControl::paintAway()
{
 // Team flags
	w->destroyControl(FLAG_AWAY);
		
		
	if(pMatchResult2)
	{
		GRegister *pRegister=pMatchResult2->getRegister();
		if(pRegister)
		{
			getFlag(pMatchResult2->getGroup(),SML,m_pBmpFlag[3]);			
	 		w->createUserBitmap(FLAG_AWAY,CRect(INIX+SERVICE_WIDTH+NAME_WIDTH,INIY+CELL_HEIGHT*3,INIX+SERVICE_WIDTH+NAME_WIDTH+NOC_WIDTH,INIY+CELL_HEIGHT*4),m_pBmpFlag[3],TRUE,BORDER_NONE);
						
			w->changeTxt (LBL_MATCHRESNAME2,pRegister->getScbLName());
			w->changeTxt (LBL_MATCHRESNOC2 ,pRegister->getGroup());		
					
		}
		else if (pMatchResult2->getBye())
		{
			w->changeTxt (LBL_MATCHRESNAME2,"-Bye-");
			w->changeTxt (LBL_MATCHRESNOC2 ,"");
		}
		else
		{
			w->changeTxt (LBL_MATCHRESNAME2,"Not Assigned");
			w->changeTxt (LBL_MATCHRESNOC2 ,"");		
		}

		if(pMatchResult2->getColor()==CHMatchResult::eWhite)
			 w->changeBmp(BU_COLOR_AWAY, BMP_WHITE, JUST_CENTER);
		else w->changeBmp(BU_COLOR_AWAY, BMP_BLACK, JUST_CENTER);
	}
	else
	{
		w->changeTxt (LBL_MATCHRESNAME2,"");
		w->changeTxt (LBL_MATCHRESNOC2 ,"");	
		//w->destroyControl(BU_COLOR_HOME);
	}
	
	
}
void CHManualEventControl::paintAll()
{
	fillGrid();
	
	paintHome();
		
	paintAway();
	
	paintMatchStatus();
		
	
	paintMatchResult();
	changePress();
	paintQualitatives();
	paintColors();

	if(pMatch->getStatus()==CHMemoryDataBase::eFinished)
		 disableEnableControls(false);
	else disableEnableControls(true);
	
}
void CHManualEventControl::paintColors()
{
	if(pMatchResult1)
	{
		w->enable(BU_COLOR_HOME,true);
		if(pMatchResult1->getColor()==CHMatchResult::eWhite)
			 w->changeBmp(BU_COLOR_HOME, BMP_WHITE, JUST_CENTER);
		else w->changeBmp(BU_COLOR_HOME, BMP_BLACK, JUST_CENTER);
	}
	else
	{
		w->enable(BU_COLOR_HOME,false);
	}
	
	
	if(pMatchResult2)
	{
		w->enable(BU_COLOR_AWAY,true);
		if(pMatchResult2->getColor()==CHMatchResult::eWhite)
			 w->changeBmp(BU_COLOR_AWAY, BMP_WHITE, JUST_CENTER);
		else w->changeBmp(BU_COLOR_AWAY, BMP_BLACK, JUST_CENTER);
	}
	else
	{
		w->enable(BU_COLOR_AWAY,false);
	}
}
void CHManualEventControl::changeSelectionMatches()
{
	
	if(poolMatches)
	{
		w->changeBck(BU_POOL_SELECT,IDBCKBROWN3_DE);
		w->changeBck(BU_DATE_SELECT,IDBCK_BUT);
		
		w->changeCheck(BU_POOL_SELECT,TRUE);
		w->changeCheck(BU_DATE_SELECT,FALSE);
	}
	else
	{
		w->changeBck(BU_POOL_SELECT,IDBCK_BUT);
		w->changeBck(BU_DATE_SELECT,IDBCKBROWN3_DE);
		
		w->changeCheck(BU_POOL_SELECT,FALSE);
		w->changeCheck(BU_DATE_SELECT,TRUE);
	}
	w->redraw(BU_POOL_SELECT,FALSE);
	w->redraw(BU_DATE_SELECT,FALSE);
}

void CHManualEventControl::finishMatch(CHMatch *pMatch)
{
	CHStatusManager statusManager;
	statusManager.run(*pMatch,CHMemoryDataBase::eFinished);

	eventControlOp.finishMatch(pMatch);
	if(pMatch->getStatus()==CHMemoryDataBase::eFinished)
		 disableEnableControls(false);
	else disableEnableControls(true);
}

short CHManualEventControl::getEventFromButton(short button)
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
