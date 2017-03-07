/*************************************************************************************
*	© Copyright MSL Software, S.L., 2001
*
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHCnfgTeamSchedule.cpp
*   Description	: 
*
*	Author		: Chess Team
*	Date created: 27-12-2005
* 	Project		:
*
***************************************************************************************/

#include "stdafx.h"
#include "CHmanager.h"
#include "CHCnfgTeamSchedule.h"

#include <GUI/FLAGS/flags.h>
#include <core/G/GMsgDefines.h>
#include <core/TH/GTHMsgDefines.h>
#include <sports/CH/data/CHMsgDefines.h>
#include <sports/CH/data/CHMember.h>
#include <sports/CH/data/CHMatchMember.h>
#include <sports/CH/data/CHSession.h>
#include "CHCnfgTeamMembersDlg.h"
#include "CHCnfgMatchJudgeDlg.h"
#include "CHDefines.h"
#include <CORE/G/GTime.h>
#include "CHProgression.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define		BYE					 "BYE"

#define		LBL_OK				1000
#define		LBL_EXIT			1001
#define		LBL_TEAM_H			1002
#define		LBL_TEAM_V			1003
#define		LBL_HOME			1004
#define		LBL_VISIT			1005
#define		LBL_VS				1006
#define		LBL_MATCH			1007
#define		LBL_STATUS			1008
#define		LBL_UMPIRE1			1009
#define		LBL_UMPIRE2			1010
#define		IDBACKG				1011
#define     IDWHITE				1012
#define     IDGREY				1013
//#define		IDCOL_AZUL			1014
//#define		IDCOL_ROJO1			1015
#define		IDCOLNAVY			1016
//#define		IDCOL_AMARILLO1			1017
#define		IDCOLGREEN			1018
//#define		IDCOL_NEGRO			1019
#define		FNTDLG				1020
#define		FNTMAX				1021
#define		FNTMED				1022
#define		FNTSUP				1023
#define		FNTMIN				1024
#define		FLAG_TEAM_H			1025
#define		FLAG_TEAM_V			1026
#define     FLAG_UMPIRE1		1027
#define     FLAG_UMPIRE2		1028
#define		BUT_UMPIRE1			1029
#define		BUT_UMPIRE2			1030
#define     LST_TEAM_HOME		1031
#define     LST_TEAM_VISIT		1032
#define     FR_HOME				1033
#define     FR_VISIT			1034
#define		LINEBCK				1035
#define		FR_JUDGE			1036
#define		LBL_TITLE2			1039
#define		LBL_RAYA2			1040
#define		LBL_TITLE3			1041
#define		LBL_RAYA3			1042
#define		FR_HOMEAWAY			1043
#define		IDBLUE				1044
#define		IDYELLOW			1045
#define		BU_CLEARTEAMH		1046
#define		BU_CLEARTEAMV		1047
#define		LBL_GROUP_TEAM_V	1048
#define		LBL_GROUP_TEAM_H	1049
#define		LBL_DATE			1050
#define		LBL_DATES			1051
#define		LBL_TIME			1052
#define		LBL_TIMES			1053
#define		LBL_SESSION			1054
#define		LBL_SESSIONS		1055	
#define		LBL_TABLE			1056
#define		LBL_TABLES			1057
#define		LBL_STATUS1			1058
#define		LBL_STATUS1S		1059
#define		GR_SUBMATCH			1060
#define		FNTMAXIMIN			1061
#define		LBL_DESCMATCH		1062
#define		IDBLUE1				1063
#define		CBOSUBGRIDSESSION	1064
#define		CBOSUBGRIDCOURT		1065
#define		LBL_START_TIME		1066
#define		LBL_TIME_BEHIND		1067
#define		ED_START_TIME		1068
#define		ED_TIME_BEHIND		1069
#define     LBL_TIME_BEHIND_MM	1070
#define		BMPDOWN				1071
#define		BU_DOWN				1072
// TEAM COMPETITION SCHEDULE
#define		LBL_TEAM_COMP		1073
#define		LBL_LETTER11		1074
#define		LBL_LETTER12		1075
#define		LBL_LETTER13		1076
#define		LBL_LETTER14		1077
#define		LBL_LETTER15		1078
#define		LBL_LETTER21		1079
#define		LBL_LETTER22		1080
#define		LBL_LETTER23		1081
#define		LBL_LETTER24		1082
#define		LBL_LETTER25		1083
#define		GR_MEMBER1			1084
#define		GR_MEMBER2			1085
#define		GR_TEAM_MEMBER1		1086
#define		GR_TEAM_MEMBER2		1087
#define		FR_TEAM_MEMBER		1088
#define		BMP_MEMB_RIGHT1		1089
#define		BMP_MEMB_RIGHT2		1090
#define		BU_SETCOMPETITION	1091
#define		FNTGRMED			1092
#define		FNTGRMIN			1093
#define		LBL_TEAM_RESULT		1094
#define		LBL_TEAM_RESULT_TIT 1095
#define		FNTMED1				1096
#define		BMP_CHECKT			1097
#define		BU_AUTSETCOMPETIT	1098

extern CCHManagerApp theApp;

int orderCHSessions(const GVectorElement** a, const GVectorElement** b)
{
	CHSession* pSessionA=(CHSession*)(*a)->getElement();
	CHSession* pSessionB=(CHSession*)(*b)->getElement();

	return strcmp(pSessionA->getKey(),pSessionB->getKey());
}

int orderCourts(const GVectorElement** a, const GVectorElement** b)
{
	GCourt* pCourtA=(GCourt*)(*a)->getElement();
	GCourt* pCourtB=(GCourt*)(*b)->getElement();

	if(pCourtA->getCourt() && pCourtB->getCourt())
		 return pCourtA->getCourt() - pCourtB->getCourt();
	else return 0;
}

int orderRating(const GVectorElement** a, const GVectorElement** b)
{
	CHMember *pMemA=(CHMember *)(*a)->getElement();
	CHMember *pMemB=(CHMember *)(*b)->getElement();

	if (!pMemB->getRating() && pMemA->getRating())
		return -1;
	else if (!pMemA->getRating() && pMemB->getRating())
		return 1;
	else if (pMemB->getRating() && pMemA->getRating())
	{
		short order=pMemB->getRating()-pMemA->getRating();
		if (order>0)
			return 1;
		if (order<0)
			return -1;
	}
	return (pMemA->getOrder()-pMemB->getOrder());
}

CHCnfgTeamSchedule::CHCnfgTeamSchedule(CWnd* pParent /*=NULL*/,GSortedVector vMatches,int index)
:CDialog(CHCnfgTeamSchedule::IDD, pParent)
,pMatch(0)
,pComboVenue(0)
,pComboCourt(0)
,eventControlOp((CHMemoryDataBase*)mem())
,posX(0)
,vSortMatches(vMatches)
,matchSel(index!=-1?index:0)
{
	pBmpFlagH=new CBitmap();
	pBmpFlagV=new CBitmap();
	pBmpFlagJU =new CBitmap();
	pBmpFlagJS =new CBitmap();
	pStatusMngt = new CHStatusManager();

	//{{AFX_DATA_INIT(CHCnfgTeamSchedule)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CHCnfgTeamSchedule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHCnfgTeamSchedule)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHCnfgTeamSchedule, CDialog)
	//{{AFX_MSG_MAP(CHCnfgTeamSchedule)
	ON_MESSAGE(UM_CLICK,onClick)
	ON_MESSAGE(UM_DBLCLICK,onDblClick)
	ON_MESSAGE(UM_PAINTGRID,onPaintGrid)
	ON_MESSAGE(UM_DROP,	onGridDrop)
	ON_MESSAGE(UM_DRAG,	onGridDrag)
	ON_MESSAGE(UM_KEYDOWN, OnKeyDown)
	ON_MESSAGE(UM_RBUTDOWN, onRButtonDown)
	//	ON_MESSAGE(TRN_MATCH_CHANGE_DLG,onChangeMatch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CHCnfgTeamSchedule::OnInitDialog() 
{
	w = new CGraphicWnd(this);
	INITW(w);

	pMatch = (CHMatch *) vSortMatches[matchSel]->getElement();
	if(!lockMatch(pMatch))
		return FALSE;
	w->destroyBackground (IDBACKG);
	w->addBackgroundColor(IDBACKG,RGB(240,240,250));
	w->setBackground (IDBACKG);	

	w->addBackgroundColor(LINEBCK, RGB( 58,110,165));	
	w->addBackgroundColor(IDWHITE,RGB(255,255,255));
	w->addBackgroundColor(IDGREY,RGB(200,200,200));
	w->addBackgroundColor(IDBLUE,RGB(210,210,255));
	w->addBackgroundColor(IDBLUE1,RGB(168,193,238));
	w->addBackgroundColor(IDYELLOW,RGB(255,255,236));

	w->addFont(FNTDLG, 6,15,1,0,1,0,_T("Arial"));
	w->addFont(FNTMAX, 9,20,1,1,0,0,_T("Arial"));
	w->addFont(FNTMED, 7,15,1,0,0,0,_T("Arial"));
	w->addFont(FNTSUP,  15,30,1,0,0,0,_T("Arial"));
	w->addFont(FNTMIN, 6,12,1,0,0,0,_T("Arial"));
	w->addFont(FNTMAXIMIN, 7,13,1,0,0,0,_T("Arial"));
	w->addFont(FNTGRMED, 7,13,1,0,0,0,_T("Arial"));
	w->addFont(FNTGRMIN, 6,11,1,0,0,0,_T("Arial"));
	w->addFont(FNTMED1,  15,26,1,0,0,0,_T("Arial"));

	//w->addColorSet(IDCOL_AZUL,RGB(0,0,170),COLOR_DEFAULT_OFF ,COLOR_DEFAULT_HITX,COLOR_DEFAULT_HIGH,COLOR_DEFAULT_L3D,COLOR_DEFAULT_N3D,COLOR_DEFAULT_D3D );
	//w->addColorSet(IDCOL_ROJO1,RGB(200,0,0),COLOR_DEFAULT_OFF,COLOR_DEFAULT_HITX,COLOR_DEFAULT_HIGH,COLOR_DEFAULT_L3D,COLOR_DEFAULT_N3D,COLOR_DEFAULT_D3D);
	w->addColorSet(IDCOLNAVY,RGB(0,0,100),COLOR_DEFAULT_OFF,COLOR_DEFAULT_HITX,COLOR_DEFAULT_HIGH,COLOR_DEFAULT_L3D,COLOR_DEFAULT_N3D,COLOR_DEFAULT_D3D);
	//w->addColorSet(IDCOL_NEGRO,RGB(0,0,0),COLOR_DEFAULT_OFF,RGB(0,0,0),RGB(200,200,200),COLOR_DEFAULT_L3D,COLOR_DEFAULT_N3D,COLOR_DEFAULT_D3D);
	w->addColorSet(IDCOLGREEN,RGB(0,180,0),COLOR_DEFAULT_OFF,RGB(0,0,0),RGB(200,200,200),COLOR_DEFAULT_L3D,COLOR_DEFAULT_N3D,COLOR_DEFAULT_D3D);
	//w->addColorSet(IDCOL_AMARILLO1,RGB(250,180,37),COLOR_DEFAULT_OFF,RGB(0,0,0),RGB(200,200,200),COLOR_DEFAULT_L3D,COLOR_DEFAULT_N3D,COLOR_DEFAULT_D3D);

	w->addBitmapT(BMPDOWN,IDB_BMP_DOWN);
	w->addBitmapT(BMP_MEMB_RIGHT1,IDB_MEMB_RIGHT	);
	w->addBitmapT(BMP_MEMB_RIGHT2,IDB_MEMB_RIGHT	);

	w->createLabelEx(LBL_OK ,CRect(380,600,450,615),"OK",BORDER_NONE,JUST_CENTER,IDBACKG,IDCOL_AZUL,FNTDLG,IDBACKG,IDCOL_ROJO1);

	w->createLabel(LBL_TEAM_RESULT_TIT ,CRect(280, 160, 470,185),"Team Result",BORDER_SINGLE,JUST_CENTER,IDBLUE,IDCOLNAVY,FNTMAX);
	w->createLabel(LBL_TEAM_RESULT ,CRect(280, 190, 470,220),"",BORDER_NONE,JUST_CENTER,IDBACKG,IDCOL_ROJO1,FNTMED1);

	w->addBitmapT(BMP_PREVIOUS_M, IDB_BMP_BEFORE);
	w->addBitmapT(BMP_NEXT_M, IDB_BMP_NEXT);

	if (vSortMatches.entries()>1)
	{
		// Previous Match
		w->createButton(BU_PREVIOUS_M,CRect(750,160,776,185), "",IDBCK,IDCOL,FNTMED);
		w->changeBmp(BU_PREVIOUS_M, BMP_PREVIOUS_M, JUST_CENTER);
		w->setToolTip(BU_PREVIOUS_M ,"Previous Match");
		// Next Match
		w->createButton(BU_NEXT_M,CRect(750,190,776,215), "",IDBCK,IDCOL,FNTMED);
		w->changeBmp(BU_NEXT_M, BMP_NEXT_M, JUST_CENTER);
		w->setToolTip(BU_NEXT_M ,"Next Match");
	}
	paintTeamResult();

	showHeadMatch();
	showSubMatches();
	// Sessions Combo
	w->createGridCombo(CBOSUBGRIDSESSION,100,BORDER_DOWN,22,IDBACKG,IDCOL_AZUL,FNTMIN);
	// Courts Combo
	w->createGridCombo(CBOSUBGRIDCOURT,100,BORDER_DOWN,22,IDBACKG,IDCOL_AZUL,FNTMIN);

	showTeamAssignation();

	w->addBitmapT(BMP_CHECKT			,IDB_CH_CHECK);
	// Menu de visualizacion de possibles resultados
	w->createMenu(MENU_COLORS,70,22,IDBCK,IDCOL,FNTGRMED,IDBCK2,IDCOL);

	CDialog::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
              // EXCEPTION: OCX Property Pages should return FALSE
}

void CHCnfgTeamSchedule::paintHeadMatch()
{
	if (!pMatch)
		return;

	CString aux = _T("");
	aux.Format(_T("%s, %s, Match %d"),pMatch->getEventLDescription(),pMatch->getPhaseLDescription(),pMatch->getMatchNumber());
	w->changeTxt(LBL_DESCMATCH,aux);

	CString match = _T("");
	match.Format(_T("%s%d") , pMatch->getEventSDescription(),pMatch->getMatchNumber());
	w->changeTxt(LBL_MATCH,match);

	GSortedVector &vMatchResults = pMatch->getCompetitorsVector();
	if (vMatchResults.entries() != 2)
		return;

	CHMatchResult *pMResultHome = (CHMatchResult *)vMatchResults[0]->getElement();
	CHMatchResult *pMResultVisit = (CHMatchResult *)vMatchResults[1]->getElement();

	if (pMResultHome && pMResultHome->getRegister())
	{
		CHRegister *pRegister = (CHRegister *)pMResultHome->getRegister();
		GGroup *pGroupSel = CHMemoryDataBase::findGroup(pRegister->getGroup());
		getFlag(pGroupSel->getGroup(),SML,pBmpFlagH);			
		w->createUserBitmap(FLAG_TEAM_H ,CRect( 20, 75, 40,105),pBmpFlagH,TRUE,BORDER_DOWN);
		w->show(FLAG_TEAM_H);
		w->redraw(FLAG_TEAM_H);
		w->changeTxt(LBL_GROUP_TEAM_H,pRegister->getGroup());
		w->changeTxt(LBL_TEAM_H,pRegister->getPrnLName());
	}
	else
	{
		w->hide(FLAG_TEAM_H);
		w->changeTxt(LBL_GROUP_TEAM_H,"");
		w->changeTxt(LBL_TEAM_H,"");
	}

	if (pMResultVisit && pMResultVisit->getRegister())
	{
		CHRegister *pRegister = (CHRegister *)pMResultVisit->getRegister();
		GGroup *pGroupSel = CHMemoryDataBase::findGroup(pRegister->getGroup());
		getFlag(pGroupSel->getGroup(),SML,pBmpFlagV);	
		w->createUserBitmap(FLAG_TEAM_V ,CRect(465, 75, 495,105),pBmpFlagV,TRUE,BORDER_DOWN);
		w->show(FLAG_TEAM_V);
		w->redraw(FLAG_TEAM_V);
		w->changeTxt(LBL_GROUP_TEAM_V,pRegister->getGroup());
		w->changeTxt(LBL_TEAM_V,pRegister->getPrnLName());
	}
	else
	{
		w->hide(FLAG_TEAM_V);
		w->changeTxt(LBL_GROUP_TEAM_V,"");
		w->changeTxt(LBL_TEAM_V,"");
	}

	aux=_T("");
	aux = pMatch->getStartDate().isValid() ? pMatch->getStartDate().asString("%d/%m/%Y"):"-"; 
	// Date
	w->changeTxt(LBL_DATES,aux);
	aux = pMatch->getStartTime().isValid() ? pMatch->getStartTime().asString("%H:%M"):"-"; 
	// Time
	w->changeTxt(LBL_TIMES,aux);
	if(pMatch->getSession())
		aux.Format(_T("%d"),pMatch->getSessionSession());
	else aux = "-";
	// Session
	w->changeTxt(LBL_SESSIONS,aux);
	if(pMatch->getCourt())
		aux.Format(_T("%d"),pMatch->getCourtCode());
	else aux = "-";
	// Table
	w->changeTxt(LBL_TABLES,aux);
	GStatus* pStatus = (GStatus*)mem()->findStatus(pMatch->getStatus());
	if (pStatus)
		aux = pStatus->getLDescription();
	else aux = "-";
	// Status
	w->changeTxt(LBL_STATUS1S,aux);
}

void CHCnfgTeamSchedule::showHeadMatch()
{
	if (!pMatch)
		return;

	CString aux = _T("");

	aux.Format(_T("%s, %s, Match %d"),pMatch->getEventLDescription(),pMatch->getPhaseLDescription(),pMatch->getMatchNumber());

	w->createLabel(LBL_DESCMATCH,CRect(10,10,820,40),aux,BORDER_SINGLE,JUST_CENTER,IDBLUE1,IDCOLNAVY,FNTSUP);

	w->createFrame(FR_HOMEAWAY,CRect( 10,45,820,145),BORDER_DOWN,0,0,IDBLUE);	

	CString match = _T("");
	match.Format(_T("%s%d") , pMatch->getEventSDescription(),pMatch->getMatchNumber());
	/*CString str =  _T("Match ");
	str += match;*/
	w->createLabel(LBL_MATCH,CRect(350,50,480,70),match,BORDER_NONE,JUST_CENTER,IDBLUE,IDCOLNAVY,FNTSUP);

	w->createLabel(LBL_HOME,CRect( 60, 50,165,70),"Home",BORDER_NONE,JUST_LEFT,IDBLUE,IDCOL_AZUL,FNTMAX);
	w->createLabel(LBL_VISIT,CRect(490,50,555,70),"Away",BORDER_NONE,JUST_RIGHT,IDBLUE,IDCOL_ROJO1,FNTMAX);

	w->createLabel(LBL_VS,CRect(365,75,415,110),"vs",BORDER_NONE,JUST_RIGHT,IDBLUE,IDCOL_NEGRO,FNTMED);

	GSortedVector &vMatchResults = pMatch->getCompetitorsVector();
	if (vMatchResults.entries() != 2)
		return;

	CHMatchResult *pMResultHome = (CHMatchResult *)vMatchResults[0]->getElement();
	CHMatchResult *pMResultVisit = (CHMatchResult *)vMatchResults[1]->getElement();

	if (pMResultHome && pMResultHome->getRegister())
	{
		CHRegister *pRegister = (CHRegister *)pMResultHome->getRegister();
		GGroup *pGroupSel = CHMemoryDataBase::findGroup(pRegister->getGroup());
		getFlag(pGroupSel->getGroup(),SML,pBmpFlagH);			
		w->createUserBitmap(FLAG_TEAM_H ,CRect( 20, 75, 40,105),pBmpFlagH,TRUE,BORDER_DOWN);
		w->show(FLAG_TEAM_H);
		w->createLabel(LBL_GROUP_TEAM_H,CRect( 20,95,55,110),pRegister->getGroup(),BORDER_NONE,JUST_LEFT,IDBLUE,IDCOL_AZUL,FNTMED);
		w->createLabel(LBL_TEAM_H,CRect( 60,75,350,105),pRegister->getPrnLName(),BORDER_DOWN,JUST_LEFT,IDBACKG,IDCOL_AZUL,FNTMED);
				
	}

	if (pMResultVisit && pMResultVisit->getRegister())
	{
		CHRegister *pRegister = (CHRegister *)pMResultVisit->getRegister();
		GGroup *pGroupSel = CHMemoryDataBase::findGroup(pRegister->getGroup());
		getFlag(pGroupSel->getGroup(),SML,pBmpFlagV);	
		w->createUserBitmap(FLAG_TEAM_V ,CRect(465, 75, 495,105),pBmpFlagV,TRUE,BORDER_DOWN);
		w->show(FLAG_TEAM_V);
		w->createLabel(LBL_GROUP_TEAM_V,CRect(465,95,500,110),pRegister->getGroup(),BORDER_NONE,JUST_LEFT,IDBLUE,IDCOL_AZUL,FNTMED);
		w->createLabel(LBL_TEAM_V,CRect(505,75,795,105),pRegister->getPrnLName(),BORDER_DOWN,JUST_LEFT,IDBACKG,IDCOL_ROJO1,FNTMED);
	}
	else
	{
		w->show(FLAG_TEAM_V);
	}
	aux=_T("");
	aux = pMatch->getStartDate().isValid() ? pMatch->getStartDate().asString("%d/%m/%Y"):"-"; 
	// Label Date
	w->createLabel(LBL_DATE,CRect(20,120,70,135),"Date:",BORDER_NONE,JUST_LEFT,IDBLUE,IDCOL_NEGRO,FNTMED);
	// Date
	w->createLabel(LBL_DATES,CRect(75,120,150,135),aux,BORDER_NONE,JUST_LEFT,IDBLUE,IDCOLNAVY,FNTMED);

	aux = pMatch->getStartTime().isValid() ? pMatch->getStartTime().asString("%H:%M"):"-"; 
	// Label Time
	w->createLabel(LBL_TIME,CRect(175,120,225,135),"Time:",BORDER_NONE,JUST_LEFT,IDBLUE,IDCOL_NEGRO,FNTMED);
	// Time
	w->createLabel(LBL_TIMES,CRect(230,120,305,135),aux,BORDER_NONE,JUST_LEFT,IDBLUE,IDCOLNAVY,FNTMED);

	if(pMatch->getSession())
	{
		aux.Format(_T("%d"),pMatch->getSessionSession());
	}
	else aux = "-";
	// Label Session
	w->createLabel(LBL_SESSION,CRect(330,120,390,135),"Session:",BORDER_NONE,JUST_LEFT,IDBLUE,IDCOL_NEGRO,FNTMED);
	// Session
	w->createLabel(LBL_SESSIONS,CRect(395,120,455,135),aux,BORDER_NONE,JUST_LEFT,IDBLUE,IDCOLNAVY,FNTMED);

	if(pMatch->getSession())
	{
		aux.Format(_T("%d"),pMatch->getSessionSession());
	}
	else aux = "-";
	// Label Table
	w->createLabel(LBL_TABLE,CRect(480,120,530,135),"Table:",BORDER_NONE,JUST_LEFT,IDBLUE,IDCOL_NEGRO,FNTMED);
	// Table
	w->createLabel(LBL_TABLES,CRect(535,120,605,135),aux,BORDER_NONE,JUST_LEFT,IDBLUE,IDCOLNAVY,FNTMED);
	// Status
	GStatus* pStatus = (GStatus*)mem()->findStatus(pMatch->getStatus());
	if (pStatus)
	{
		aux = pStatus->getLDescription();
	}
	else aux = "-";
	// Label Status
	w->createLabel(LBL_STATUS1,CRect(630,120,680,135),"Status:",BORDER_NONE,JUST_LEFT,IDBLUE,IDCOL_NEGRO,FNTMED);
	// Status
	w->createLabel(LBL_STATUS1S,CRect(685,120,755,135),aux,BORDER_NONE,JUST_LEFT,IDBLUE,IDCOLNAVY,FNTMED);
}


void CHCnfgTeamSchedule::showSubMatches()
{
	// Label Start Time
	w->createLabel(LBL_START_TIME,CRect(10,150,85,170),"Time:",BORDER_NONE,JUST_LEFT,IDBACKG,IDCOL_NEGRO,FNTMIN);
	w->createEdit(ED_START_TIME,CRect(87,150,127,170),"",BORDER_DOWN,JUST_LEFT,IDYELLOW,IDCOLNAVY,FNTMIN);
	w->doEditFormat(ED_START_TIME,"##:##");
	w->createLabel(LBL_TIME_BEHIND,CRect(10,175,85,195),"Time Behind:",BORDER_NONE,JUST_LEFT,IDBACKG,IDCOL_NEGRO,FNTMIN);
	w->createLabel(LBL_TIME_BEHIND_MM,CRect(10,190,85,200),"(mm)",BORDER_NONE,JUST_CENTER,IDBACKG,IDCOL_NEGRO,FNTMIN);
	w->createEdit(ED_TIME_BEHIND,CRect(87,175,127,195),"",BORDER_DOWN,JUST_LEFT,IDYELLOW,IDCOLNAVY,FNTMIN);
	w->doEditFormat(ED_TIME_BEHIND,"###");
	//w->createBitmap (BMPDOWN,BMPDOWN,87,200,true,BORDER_NONE);
	w->createButton(BU_DOWN,CRect(90, 195, 120,220),"",IDBACKG,IDCOL_NEGRO,FNTMIN);
	w->changeBmp(BU_DOWN,BMPDOWN,JUST_CENTER);

	int finish=250+(pMatch->getSubMatches().entries()*25);
	w->createGrid(GR_SUBMATCH,CRect(5,225,815,finish),BORDER_DOWN,25,IDBACKG,IDCOL_NEGRO,FNTMAXIMIN);

	w->gridLineColor(GR_SUBMATCH,RGB(192,192,192),RGB(192,192,192));

	w->addGridColumn(GR_SUBMATCH,"Date",JUST_CENTER,75);
	w->addGridColumn(GR_SUBMATCH,"Time",JUST_CENTER,40);
	//w->addGridColumn(GR_SUBMATCH,"MN",JUST_CENTER,30);
	w->addGridColumn(GR_SUBMATCH,"SubMatch",JUST_CENTER,70);
	w->addGridColumn(GR_SUBMATCH,"Home",JUST_CENTER,191);
	w->addGridColumn(GR_SUBMATCH,"Away",JUST_CENTER,191);
	w->addGridColumn(GR_SUBMATCH,"Status",JUST_CENTER,70);
	w->addGridColumn(GR_SUBMATCH,"Session",JUST_CENTER,60);
	w->addGridColumn(GR_SUBMATCH,"Table",JUST_CENTER,60);
	w->addGridColumn(GR_SUBMATCH,"Result",JUST_CENTER,50);

	fillSubMatches();
}	

void CHCnfgTeamSchedule::fillSubMatches()
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
}

void CHCnfgTeamSchedule::showTeamAssignation()
{
	if(pMatch)
	{
		int init=250+(pMatch->getSubMatches().entries()*25);
		CHTeamMatchsCnfg * pTeamMatchCnfg=CHMemoryDataBase::findTeamMatchsCnfg(((CHPhase*)pMatch->getPhase()));
		if(pTeamMatchCnfg)
		{
			CString aux=_T("");
			aux=pTeamMatchCnfg->getLDescription();
			w->createLabel(LBL_TEAM_COMP,CRect(340,init+17,490,init+37),aux,BORDER_SINGLE,JUST_CENTER,IDBACKG,IDCOL_AZUL,FNTMED);
			char letra='A';
			w->createGrid(GR_MEMBER1,CRect(55,init+62,195,init+62+(35*pTeamMatchCnfg->getCompMember(0))),BORDER_DOWN,35,IDGREY,IDCOL_AZUL,FNTMED,false);
			w->addGridColumn(GR_MEMBER1,"", JUST_LEFT, 140);
			w->gridLineColor(GR_MEMBER1,RGB(192,192,192),RGB(192,192,192));
			for(short i=0;i<pTeamMatchCnfg->getCompMember(0);i++) //pTeamMatchCnfg->getCompetitors()
			{
				aux.Format(_T("%c"),letra);
				w->createLabel(LBL_LETTER11+i,CRect(10,init+62+(i*35),50,init+92+(i*35)),aux,BORDER_NONE,JUST_CENTER,IDBACKG,IDCOL_AZUL,FNTMAX);
				letra++;
			}
			letra=char(pTeamMatchCnfg->getFAwayC()(0));
			w->createGrid(GR_MEMBER2,CRect(635,init+62,775,init+62+(35*pTeamMatchCnfg->getCompMember(1))),BORDER_DOWN,35,IDGREY,IDCOL_AZUL,FNTMED,false);
			w->addGridColumn(GR_MEMBER2,"", JUST_LEFT, 140);
			w->gridLineColor(GR_MEMBER2,RGB(192,192,192),RGB(192,192,192));
			for(i=0;i<pTeamMatchCnfg->getCompMember(1);i++) //pTeamMatchCnfg->getCompetitors()
			{
				aux.Format(_T("%c"),letra);
				w->createLabel(LBL_LETTER21+i,CRect(780,init+62+(i*35),820,init+92+(i*35)),aux,BORDER_NONE,JUST_CENTER,IDBACKG,IDCOL_AZUL,FNTMAX);
				letra++;
			}
			CHMatchResult* pMatchRes1 = (CHMatchResult*)pMatch->getCompetitorsVector()[0]->getElement();
			CHMatchResult* pMatchRes2 = (CHMatchResult*)pMatch->getCompetitorsVector()[1]->getElement();
			// Team 1
			w->createGrid(GR_TEAM_MEMBER1,CRect(240,init+44,380,init+62+(20*(pMatchRes1->getInscription()?pMatchRes1->getInscriptionMembersVector().entries():pTeamMatchCnfg->getCompetitors()))),BORDER_DOWN,20,IDBLUE1,IDCOL_AZUL,FNTMED);
			w->addGridColumn(GR_TEAM_MEMBER1,"Members Team 1", JUST_LEFT, 140);
			w->gridLineColor(GR_TEAM_MEMBER1,RGB(192,192,192),RGB(192,192,192));
			// Team 2
			w->createGrid(GR_TEAM_MEMBER2,CRect(450,init+44,590,init+62+(20*(pMatchRes2->getInscription()?pMatchRes2->getInscriptionMembersVector().entries():pTeamMatchCnfg->getCompetitors()))),BORDER_DOWN,20,IDBLUE1,IDCOL_AZUL,FNTMED);
			w->addGridColumn(GR_TEAM_MEMBER2,"Members Team 2", JUST_LEFT, 140);
			w->gridLineColor(GR_TEAM_MEMBER2,RGB(192,192,192),RGB(192,192,192));

			w->createFrame(FR_TEAM_MEMBER,CRect( 5,init+12,825,init+97+(35*(pTeamMatchCnfg->getCompMember(1)))),BORDER_DOWN,0,0,IDBLUE);	
			// Match Members 1 y 2
			fillMatchMembersTeam(0);
			fillMatchMembersTeam(1);
			// Members 1 y 2
			fillMembersTeam(0);
			fillMembersTeam(1);
			// For Drag and Drop
			w->dragDropRegister  (GR_MEMBER1,"Members");
			w->dragDropAvailable (GR_MEMBER1,TRUE,TRUE);
			w->dragDropRegister  (GR_MEMBER2,"Members");
			w->dragDropAvailable (GR_MEMBER2,TRUE,TRUE);
			w->dragDropRegister  (GR_TEAM_MEMBER1,"Members");
			w->dragDropAvailable (GR_TEAM_MEMBER1,TRUE,TRUE);
			w->dragDropRegister  (GR_TEAM_MEMBER2,"Members");
			w->dragDropAvailable (GR_TEAM_MEMBER2,TRUE,TRUE);

			CBitmap *pBitArrow=w->getBmp(BMP_MEMB_RIGHT1);
			w->createUserBitmap(BMP_MEMB_RIGHT1,CRect(195,init+102,240,init+132),pBitArrow,TRUE,BORDER_NONE, 0,0);

			pBitArrow=w->getBmp(BMP_MEMB_RIGHT2);
			w->createUserBitmap(BMP_MEMB_RIGHT2,CRect(590,init+102,640,init+132),pBitArrow,TRUE,BORDER_NONE, 0,0);

			w->createButton(BU_SETCOMPETITION,CRect(397,init+102,430,init+122),"Set",IDBLUE1,IDCOL_ROJO1,FNTMED);
			w->setToolTip(BU_SETCOMPETITION ,"Set Match Members");

			w->createButton(BU_AUTSETCOMPETIT,CRect(385,init+142,442,init+162),"Auto Set",IDBLUE1,IDCOL_ROJO1,FNTMED);
			w->setToolTip(BU_AUTSETCOMPETIT ,"Auto Set Match Members");
		}
	}
}
LRESULT CHCnfgTeamSchedule::onGridDrag(WPARAM wParam, LPARAM lParam)
{
	DragDropItem *ddi = (DragDropItem *)lParam;
	if (!ddi) return false;
	
	return true;	
	UNREFERENCED_PARAMETER(wParam);
}

void CHCnfgTeamSchedule::onGridDrop(WPARAM wParam, LPARAM lParam)
{
	DragDropItem *dd = (DragDropItem *)lParam;
	// Cogemos la posición del grid en la que se suelta 
	// el elemento sobre el que hacemos drag drop
	int lineDrop = dd->yTarget;
	CString aux=_T("");

	if((dd->idSource == GR_TEAM_MEMBER1) && (dd->idTarget == GR_MEMBER1)) 
		onGridDropMemberToMatchMember(dd, lineDrop,0);
	else if((dd->idSource == GR_TEAM_MEMBER2) && (dd->idTarget == GR_MEMBER2))
		onGridDropMemberToMatchMember(dd, lineDrop,1);
	else if((dd->idSource == GR_MEMBER1) && (dd->idTarget == GR_TEAM_MEMBER1)) 
		onGridDropMatchMemberToMember(dd, 0);
	else if((dd->idSource == GR_MEMBER2) && (dd->idTarget == GR_TEAM_MEMBER2))
		onGridDropMatchMemberToMember(dd, 1);
	else if((dd->idSource == GR_MEMBER1) && (dd->idTarget == GR_MEMBER1))
		onGridDropMatchMemberToMatchMember(dd, lineDrop,0);
	else if((dd->idSource == GR_MEMBER2) && (dd->idTarget == GR_MEMBER2))
		onGridDropMatchMemberToMatchMember(dd, lineDrop,1);

	theApp.out(TRN_SET_MATCH_MEMBERS);
	UNREFERENCED_PARAMETER(wParam);
}

void CHCnfgTeamSchedule::onGridDropMemberToMatchMember(DragDropItem *dd, int lineDrop,short num)
{
	CString aux=_T("");
	CHMember *pMember = (CHMember *) dd->lParam;
	if (!pMember) 
		return;

	if (lineDrop >=0)
	{
		CHMatchMember *pMatchMember=(CHMatchMember*)w->getGridLParam(GR_MEMBER1+num,lineDrop);
		if(pMatchMember)
		{
			pMatchMember->setMember(pMember);
			theApp.queueOut(pMatchMember);
									
			fillMatchMembersTeam(num);
			fillMembersTeam(num);
			w->redraw(GR_TEAM_MEMBER1+num);
			w->redraw(GR_MEMBER1+num);
		}
	}
}
void CHCnfgTeamSchedule::onGridDropMatchMemberToMember(DragDropItem *dd, short num)
{
	CString aux=_T("");
	CHMatchMember *pMatchMember = (CHMatchMember *) dd->lParam;
	if (!pMatchMember) 
		return;

	pMatchMember->setMember(0);
	theApp.queueOut(pMatchMember);

	fillMatchMembersTeam(num);
	fillMembersTeam(num);
	w->redraw(GR_TEAM_MEMBER1+num);
	w->redraw(GR_MEMBER1+num);	
}
void CHCnfgTeamSchedule::onGridDropMatchMemberToMatchMember(DragDropItem *dd, int lineDrop,short num)
{
	CString aux=_T("");
	CHMatchMember *pMatchMember = (CHMatchMember *) dd->lParam;
	if (!pMatchMember) 
		return;

	if (lineDrop >=0)
	{
		CHMatchMember *pMatchMemberAux=(CHMatchMember*)w->getGridLParam(GR_MEMBER1+num,lineDrop);

		CHMember *pMemberInt=(CHMember*)pMatchMemberAux->getMember();
		if(pMatchMemberAux)
		{
			pMatchMemberAux->setMember(pMatchMember->getMember());
			theApp.queueOut(pMatchMemberAux);

			pMatchMember->setMember(pMemberInt);
			theApp.queueOut(pMatchMember);

			fillMatchMembersTeam(num);
			w->redraw(GR_MEMBER1+num);		
		}
	}
}

BOOL CHCnfgTeamSchedule::onPaintGrid   (UINT idGrid,GridItem *gi)
{
	if (idGrid==GR_SUBMATCH)
	{
		paintListScheduledMatches(gi);
		return true;
	}
	if (idGrid==GR_MEMBER1 || idGrid==GR_MEMBER2)
	{	
		paintMatchMembers(gi);
		return true;
	}
	if (idGrid==GR_TEAM_MEMBER1 || idGrid==GR_TEAM_MEMBER2)
	{	
		paintMembers(gi);
		return true;
	}

	return false;
}
void CHCnfgTeamSchedule::paintListScheduledMatches(GridItem *gi)
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
	/*if(gi->y%2)
		gi->cdc->FillSolidRect(CRect(gi->rc.left,gi->rc.top,gi->rc.right+45,gi->rc.bottom),(gi->sel)?RGB(105,105,105):RGB(140,140,255));
	else 
		gi->cdc->FillSolidRect(CRect(gi->rc.left,gi->rc.top,gi->rc.right+45,gi->rc.bottom),(gi->sel)?RGB(105,105,105):RGB(140,140,255));*/

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
				eventControlOp.paintShadow(gi->cdc,gi->rc.left+5,gi->rc.top+5,aStartDate.asString("%d/%m/%Y"),COLOR_MARRON,0,FNTGRMED,w,COLOR_NEGRO); 
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
				eventControlOp.paintShadow(gi->cdc,gi->rc.left+3,gi->rc.top+5,txt,COLOR_MARRON,0,FNTGRMED,w,COLOR_NEGRO); 
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
			eventControlOp.paintShadow(gi->cdc,gi->rc.left+10,gi->rc.top+5,matchNumber,COLOR_MARRON,0,FNTGRMED);
			//w->paintGridText(gi->rc.Width()/2,5,matchNumber,JUST_CENTER);
			break;			
		}	*/

	case 2:
		{
			char subMatch[4];
			sprintf(subMatch,"%d",pMatch->getSubMatch());
			// Match Description
			eventControlOp.paintShadow(gi->cdc,gi->rc.left+35,gi->rc.top+5,subMatch,COLOR_MARRON,1,FNTGRMED,w,COLOR_NEGRO); 
			//w->paintGridText(gi->rc.Width()/2,5,subMatch,JUST_CENTER);
			break;
		}
	case 3: // Home
		{
			CHMatchResult* pMatchRes1 = (CHMatchResult*)pMatch->getCompetitorsVector()[0]->getElement();
			if (pMatchRes1->getRegister())
			{
				CBitmap aBitmap;
				getFlag(pMatchRes1->getGroup(),ICO,&aBitmap);	
				w->paintGridUserBmp  (4,1,&aBitmap,false);
				// NOC Home
				eventControlOp.paintShadow(gi->cdc,gi->rc.left+3,gi->rc.top+12,pMatchRes1->getGroup(),COLOR_MARRON,0,FNTGRMED,w,COLOR_NEGRO); 
			}

			char text[50];
			COLORREF color;
			if (pMatch->hasByes())
				color=RGB(250,0,0);
			else
				color=COLOR_DEFAULT_ON;

			sprintf(text,"%s",	eventControlOp.getMatchResultDescription(pMatchRes1));
			eventControlOp.paintShadow(gi->cdc,gi->rc.left+39,gi->rc.top,text,COLOR_MARRON,0,FNTGRMED,w,COLOR_NEGRO); 

			sprintf(text,"%s",eventControlOp.getMatchMemberDescription(pMatchRes1));
			eventControlOp.paintShadow(gi->cdc,gi->rc.left+34,gi->rc.top+12,text,RGB(172,170,204),0,FNTGRMIN,w,COLOR_NEGRO); 
			
			if(pMatchRes1->getColor()==CHMatchResult::eWhite)
				 w->paintGridBmp (170,3,BMP_WHITE);
			else w->paintGridBmp(170,3,BMP_BLACK);
							
			break;
		}
	case 4: // Away
		{
			CHMatchResult* pMatchRes2 = (CHMatchResult*)pMatch->getCompetitorsVector()[1]->getElement();
						
			char text[50];
			COLORREF color;
			if (pMatch->hasByes())
				color=RGB(250,0,0);
			else
				color=COLOR_DEFAULT_ON;

			sprintf(text,"%s",eventControlOp.getMatchResultDescription(pMatchRes2));
			eventControlOp.paintShadow(gi->cdc,gi->rc.left+39,gi->rc.top,text,COLOR_MARRON,0,FNTGRMED,w,COLOR_NEGRO); 
			
			sprintf(text,"%s",eventControlOp.getMatchMemberDescription(pMatchRes2));
			eventControlOp.paintShadow(gi->cdc,gi->rc.left+34,gi->rc.top+12,text,RGB(172,170,204),0,FNTGRMIN,w,COLOR_NEGRO); 
			//w->paintGridText(gi->rc.Width()/2,0,text,FONTMIN,color,JUST_CENTER);

			if (pMatchRes2->getRegister())
			{
				CBitmap aBitmap;
				getFlag(pMatchRes2->getGroup(),ICO,&aBitmap);	
				w->paintGridUserBmp  (4,1,&aBitmap,false);
				// NOC Away
				//w->paintGridText(365,12,pMatchRes2->getGroup(),IDFONT,RGB(40,40,100),JUST_LEFT);
				eventControlOp.paintShadow(gi->cdc,gi->rc.left+3,gi->rc.top+12,pMatchRes2->getGroup(),COLOR_MARRON,0,FNTGRMED,w,COLOR_NEGRO); 
			}

			if(pMatchRes2->getColor()==CHMatchResult::eWhite)
				 w->paintGridBmp (170,3,BMP_WHITE);
			else w->paintGridBmp(170,3,BMP_BLACK);		
			break;
		}
	case 5: // Status
		{
			GStatus* pStatus = (GStatus*)mem()->findStatus(pMatch->getStatus());
			if (pStatus)
			{
				COLORREF color;
				if (pStatus->getStatus()<=CHMemoryDataBase::eSchedulled)
					color=RGB(0,125,0);		
				else
					color=RGB(250,0,0);

				eventControlOp.paintShadow(gi->cdc,gi->rc.left+5,gi->rc.top+5,pStatus->getLDescription().toMultiByte(),COLOR_MARRON,0,FNTGRMED,w,COLOR_NEGRO); 
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
				eventControlOp.paintShadow(gi->cdc,gi->rc.left+25,gi->rc.top+5,text,COLOR_MARRON,0,FNTGRMED,w,COLOR_NEGRO); 
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
				eventControlOp.paintShadow(gi->cdc,gi->rc.left+25,gi->rc.top+5,courtS.toAscii(),COLOR_MARRON,0,FNTGRMED,w,COLOR_NEGRO); 
				//w->paintGridText(gi->rc.Width()/2,5,getCourtDescription(pMatch->getCourt()),JUST_CENTER);
			}
			break;
		}
	case 8: // Result
		{
			gi->cdc->SetTextColor(COLOR_DEFAULT_ON);
			if(pMatch->getStatus()>CHMemoryDataBase::eStartList)
			{   // Match Description				
				eventControlOp.paintShadow(gi->cdc,gi->rc.left+27,gi->rc.top+5,pMatch->getResultAsString(),COLOR_MARRON,1,FNTGRMED,w,COLOR_NEGRO); 
			}
			else eventControlOp.paintShadow(gi->cdc,gi->rc.left+27,gi->rc.top+5,"-",COLOR_MARRON,1,FNTGRMED,w,COLOR_NEGRO); 
			break;
		}
	}
}
void CHCnfgTeamSchedule::paintMatchMembers(GridItem *gi)
// Paint the "Match Members Grid"
{
	if (!gi) 
		return;

	if (gi->sel)	
		gi->cdc->FillSolidRect(gi->rc,GET_COLOR_DEFAULT_HIGH);
	else
	{
		if(gi->y%2)
			 gi->cdc->FillSolidRect(gi->rc,RGB(255,255,255));
		else gi->cdc->FillSolidRect(gi->rc,RGB(243,243,243));
	}
	
	CHMatchMember * pMatchMember =(CHMatchMember*)gi->lParam;
	if(!pMatchMember)
		return;
	
	switch (gi->x)
	{
		case 0: // Name
		{	
			if(pMatchMember->getRegister())
				eventControlOp.paintShadow(gi->cdc,gi->rc.left+2,gi->rc.top+2,pMatchMember->getPrnSName().toMultiByte(),COLOR_MARRON,0,FNTGRMED,w,COLOR_NEGRO); 
			break;
		}	
	}
}

void CHCnfgTeamSchedule::paintMembers(GridItem *gi)
// Paint the "Members Grid"
{
	if (!gi) 
		return;
		
	if (gi->sel)	
		gi->cdc->FillSolidRect(gi->rc,GET_COLOR_DEFAULT_HIGH);
	else
	{
		if(gi->y%2)
			 gi->cdc->FillSolidRect(gi->rc,RGB(255,255,255));
		else gi->cdc->FillSolidRect(gi->rc,RGB(243,243,243));
	}

	CHMember * pMember =(CHMember*)gi->lParam;
	if(!pMember)
		return;

	switch (gi->x)
	{
		case 0: // Name
		{	
			if(pMember->getRegister())
				eventControlOp.paintShadow(gi->cdc,gi->rc.left+2,gi->rc.top+2,pMember->getPrnSName().toMultiByte(),COLOR_MARRON,0,FNTGRMED,w,COLOR_NEGRO); 
			break;
		}				
	}
}

void CHCnfgTeamSchedule::paintStatus()
{
	unsigned char status ;
	if (pMatch->getStatus())
	{
		status = pMatch->getStatus();
		GStatus *pStatus = GMemoryDataBase::findStatus(status);
		if (pStatus)
			w->changeTxt (LBL_STATUS,pStatus->getLDescription());
		switch (status)
		{
			case GMemoryDataBase::eStartList:
				w->changeColor(LBL_STATUS,IDCOL_AZUL);
				break;
			case GMemoryDataBase::eSchedulled:
				w->changeColor(LBL_STATUS,IDCOLGREEN);
				break;
			case GMemoryDataBase::eRunning:
				w->changeColor(LBL_STATUS,IDCOL_AMARILLO1);
				break;
			case GMemoryDataBase::eFinished:
				w->changeColor(LBL_STATUS,IDCOL_ROJO1);
				break;
			default:
				break;
		}
	}
}

LRESULT CHCnfgTeamSchedule::onClick(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch(wParam)
	{
		case LBL_OK:
			onOK();
			break;
		
		case LBL_STATUS:
			changeStatus();
			break;
		case BU_DOWN:
			setStartTimes();			
			break;
		case BU_SETCOMPETITION:
			setMatchMembers();
			theApp.out(TRN_SET_MATCH_MEMBERS);
			w->redraw(GR_SUBMATCH);
			break;
		case BU_AUTSETCOMPETIT://set automatico y aleatorio
			{//para esta competicion son en total tres partidos individuales
				int totald=-1;
				size_t nitems=w->getGridNItems(GR_MEMBER1)+w->getGridNItems(GR_MEMBER2);
				if (nitems%2)
					nitems++;
				for (size_t i=0;i<nitems;i++)
				{
					CHMatchMember *pMatMem=(CHMatchMember *)(w->getGridLParam(GR_MEMBER1+(i/(nitems/2)),(i%(nitems/2))));
					if (!pMatMem)
						continue;
					if (pMatMem->getMember())
						totald++;
				}
				if (totald>-1)
				{//dragdop de matchmember a member
				CHProgression progress(mem());
				short totd[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
				totald=nitems-1;
				while (totald>-1)
				{
					int a=progress.random(nitems);
					if (totd[a])
						continue;
					DragDropItem dd;
					int p=progress.random(w->getGridNItems(GR_MEMBER1+(a/(nitems/2))));
					dd.lParam=LPARAM(w->getGridLParam(GR_MEMBER1+(a/(nitems/2)),(a%(nitems/2))));
					onGridDropMatchMemberToMember(&dd, (a/(nitems/2)));
					totd[a]=1;
					totald--;
				};
				//simulo el pulsar set
				onClick(BU_SETCOMPETITION,0);
				theApp.out(TRN_SET_MATCH_MEMBERS);
				}
				else
				{//dragdop de member a matchmember
				GSortedVector &vMatchResults = pMatch->getCompetitorsVector();
				if (vMatchResults.entries() != 2)
					break;
				CHMatchResult *pMResultHome = (CHMatchResult *)vMatchResults[0]->getElement();
				CHMatchResult *pMResultVisit = (CHMatchResult *)vMatchResults[1]->getElement();
				GSortedVector vHomeMember;
				GSortedVector vAwayMember;
				if (pMResultHome->getInscription())
					vHomeMember=pMResultHome->getInscriptionMembersVector();
				if (pMResultVisit->getInscription())
					vAwayMember=pMResultVisit->getInscriptionMembersVector();
				vHomeMember.sort(orderRating);
				vAwayMember.sort(orderRating);
				GSortedVector vMatches=pMatch->getSubMatches();
				for(size_t i=0;i<vMatches.entries();i++)
				{
					if (i<vHomeMember.entries())
					{
						CHMember *pMemA=(CHMember *)vHomeMember[i]->getElement();
						DragDropItem dd;
						dd.lParam=LPARAM(pMemA);
						onGridDropMemberToMatchMember(&dd,i,0);
					}
					if (i<vAwayMember.entries())
					{
						CHMember *pMemB=(CHMember *)vAwayMember[i]->getElement();
						DragDropItem ee;
						ee.lParam=LPARAM(pMemB);
						onGridDropMemberToMatchMember(&ee,i,1);
					}
				}
				//simulo el pulsar set
				onClick(BU_SETCOMPETITION,0);
				theApp.out(TRN_SET_MATCH_MEMBERS);
				}
				w->redraw(GR_SUBMATCH);
			}
			break;
		case MENU_COLORS: // Menu de eleccíon de color de fichas
		 onColorsMenu(lParam);
		 break;

		case BU_PREVIOUS_M:
		case BU_NEXT_M:
			{
			unLockMatch();
			int lstMatch=matchSel;
			if (wParam==BU_PREVIOUS_M)
			{
			matchSel--;
			if (matchSel<0)
				matchSel=vSortMatches.entries()-1;
			}
			else if (wParam==BU_NEXT_M)
			{
			matchSel++;
			if (matchSel==int(vSortMatches.entries()))
				matchSel=0;
			}
			pMatch = (CHMatch *) vSortMatches[matchSel]->getElement();
			if (!lockMatch(pMatch))
			{
				matchSel=lstMatch;
				pMatch = (CHMatch *) vSortMatches[matchSel]->getElement();
				break;
			}
			//refresco para superior
			paintTeamResult();
			paintHeadMatch();
			//refresco enfrentamientos
			fillSubMatches();
			//refresco Match Members 1 y 2
			fillMatchMembersTeam(0);
			fillMatchMembersTeam(1);
			//refresco Members 1 y 2
			fillMembersTeam(0);
			fillMembersTeam(1);
			}
			break;
	}
	return 0;
}
LRESULT CHCnfgTeamSchedule::onRButtonDown(WPARAM wParam, LPARAM lParam)
{
		
	short x=short(lParam);

	switch(wParam)
	{		
		case GR_SUBMATCH:
		{
			posX=x;

			CHMatch *pMatch=(CHMatch*)w->getSelectedData(GR_SUBMATCH);
			if(!pMatch)
				return false;

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
			}	
			break;	
		}
	}
	return TRUE;
}
void CHCnfgTeamSchedule::onColorsMenu(LPARAM lparam)
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
void CHCnfgTeamSchedule::onCreateMenuColors(LPARAM lParam, CHMatchResult *pMatchResult)
{
 	if(!pMatchResult)
		return;
	
	RWCString colorts=NULLRWSTRING;
	w->delMenuItems(MENU_COLORS);
	

	if (pMatchResult->getMatchStatus()!=CHMemoryDataBase::eFinished)
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
void CHCnfgTeamSchedule::changeStatus()
{
	unsigned char newStatus;
	unsigned char status = pMatch->getStatus();
	switch(status)
	{
		case GMemoryDataBase::eStartList:
			newStatus = GMemoryDataBase::eSchedulled;
			pStatusMngt->run(*pMatch,newStatus);			
			break;
		case GMemoryDataBase::eSchedulled:
			if(registersInMatch(pMatch))			
			{
				newStatus = GMemoryDataBase::eStartList;
				pStatusMngt->run(*pMatch,newStatus);
				
			}
			else ::msg("Attention","Match without competitor/s available",ICO_X,MSG_OK);
			break;
		default:
			break;
	}
	paintStatus();
} 
LRESULT CHCnfgTeamSchedule::onSelectMatchMember(WPARAM wParam, LPARAM lParam)
{
	CHMatchMember *pMatchMember = (CHMatchMember *)wParam;
	if (pMatchMember) 
	{
		int y;
		if (pMatchMember->getMatchResultPosition() == 1)
		{
			y = w->findGridLParam (LST_TEAM_HOME,LPARAM(pMatchMember));	
			w->redrawLine (LST_TEAM_HOME,y);
		}
		else
		{
			y = w->findGridLParam (LST_TEAM_VISIT,LPARAM(pMatchMember));	
			w->redrawLine (LST_TEAM_VISIT,y);
		}
	}
	return 0;
	UNREFERENCED_PARAMETER(lParam);
}

void CHCnfgTeamSchedule::onDblClick(WPARAM wParam, LPARAM lParam) //UINT idGrid,int x,int y,LPARAM lParam)
{
	//UNREFERENCED_PARAMETER(lParam);
	
	int row=HIWORD(lParam);
	int column=LOWORD(lParam);

	switch (wParam)
	{
		case GR_SUBMATCH:
		{
			CHMatch * pSubMatch = (CHMatch*)w->getGridLParam(GR_SUBMATCH,row);
			if(!pSubMatch )
				return;
			switch (column)
			{
				case 0: // Date
				case 1: // Time 
					editMatch(column,row);
					break;
				case 2:
				{	CHMatch * pSubMatch = (CHMatch*)w->getGridLParam(GR_SUBMATCH,row);
					if(!pSubMatch )
						return;
					if (lockMatch(pSubMatch) )
					{
						CHCnfgMatchJudgeDlg dlgCnfgMatch(this,pSubMatch);
						if (dlgCnfgMatch.DoModal())
							unLockMatch();		
					}
				}
				break;
				case 5: // Status
				{
					if (pSubMatch->getStatus()<CHMemoryDataBase::eStartList)
					{
						msg("Warning!!","Match will be in Startlist Status.",ICO_X,MSG_OK);
						break;
					}
					CHStatusDlg aStatusDlg(this,pSubMatch);
					aStatusDlg.DoModal();
					
					if(aStatusDlg.hasChanges())
					{
						// Si el Status es igual a StartList tengo que inicializar el partido
						if(aStatusDlg.getStartList() && pSubMatch->getStatus()==CHMemoryDataBase::eStartList)
							clearResults(pSubMatch);

						// Si el Status es igual a Protested tengo que desprogresar el partido
						if(pSubMatch->getStatus()==CHMemoryDataBase::eFinished ||
						   pSubMatch->getStatus()==CHMemoryDataBase::eProtested)
						{
							eventControlOp.finishMatch(pSubMatch);
							if(pSubMatch->getStatus()==CHMemoryDataBase::eFinished)
								 disableEnableControls(false);
							else disableEnableControls(true);
						}
													
						//paintMatchStatus();
						w->redrawLine(GR_SUBMATCH,column);
					}
					break;
				}					
				case 6:
					showComboSessions(column,row);
					break;
				case 7:
					showComboCourts(column,row);
					break;
				case 8: // Result
				{
					/*if(!registersInMatch(pSubMatch))
					{	::msg("Attention","Match without competitor/s available",ICO_X,MSG_OK);
						return;
					}
					if (lockMatch(pSubMatch) )
					{
						CHManualEventControl manualEventControl(this,pSubMatch);
						if (manualEventControl.DoModal())
						{
							unLockMatch();
							w->redrawLine(LSTSESSION1,w->getSelectedLine(LSTSESSION1));
							paintTeamResult();
							
						}
					}*/
				}
				break;
			}
			w->redrawLine(GR_SUBMATCH,row,row);
		}
	}
}
void CHCnfgTeamSchedule::editMatch (int col, int lin)
{
	RWWString text=NULLRWWSTRING;
	if (w->getWnd(GR_SUBMATCH) && lin >= 0)
	{
		CHMatch *pMatchAux = (CHMatch *)w->getGridLParam(GR_SUBMATCH,lin);

		if(pMatchAux->getStatus()>CHMemoryDataBase::eStartList)
		{	::msg("Status superior to StartList!!", "I can´t change match data!!",ICO_X,MSG_OK);
			return;
		}

		switch (col)
		{
			case 0://Date
			{
				RWCString aux("");

				if(pMatchAux->getStartDate().isValid())
					aux = pMatchAux->getStartDate().asString("%d/%m/%Y");
				text = w->editGridCell(GR_SUBMATCH, col, lin, CString(aux), "##/##/####");
				
				if (pMatchAux->getStartDate() == RWDATE_DDMMYYYY(text))
					break;
				
				if(text != _T(""))
				{
					RWDate rwDate(RWDATE_DDMMYYYY(text));
					pMatchAux->setStartDate(rwDate);
				}
				else 
				{
					RWDate rwDate(INVALID_RWDATE);
					pMatchAux->setStartDate(rwDate);
				}
		
				if(text != RWWString(aux,RWWString::ascii))
				{
					if( pMatchAux->getStartDate().isValid() && 
						pMatchAux->getStartTime().isValid() &&
						pMatchAux->getStatus() < CHMemoryDataBase::eSchedulled)
					{
						pMatchAux->setStatus(CHMemoryDataBase::eSchedulled);
						
					
					}
					else
					{
						if((!pMatchAux->getStartDate().isValid() ||
							!pMatchAux->getStartTime().isValid()) &&
							pMatchAux->getStatus() == CHMemoryDataBase::eSchedulled)
						{
							pMatchAux->setStatus(CHMemoryDataBase::eAvailable);
							
						}
					}
					
					outMatch(pMatchAux);
				}				
				
				// reordenar el vector de matches
				w->redraw(GR_SUBMATCH);
	
			}
			break;
			case 1://Time
			{
				RWCString aux("");
				RWTime previous = pMatchAux->getStartTime();

				if(pMatchAux->getStartTime().isValid())
					aux = pMatchAux->getStartTime().asString("%H:%M");
				text = w->editGridCell(GR_SUBMATCH, col, lin, CString(aux), "##:##");
				
				if (previous == RWTIME_HHMMSS(text))
					break;

				if(text != _T(""))
				{
					RWTime rwTime(RWTIME_HHMMSS(text));
					pMatchAux->setStartTime(rwTime);
				}
				else 
				{
					RWTime rwTime(INVALID_RWTIME);
					pMatchAux->setStartTime(rwTime);
				}

				if(text != RWWString(aux,RWWString::ascii))
				{
					if( pMatchAux->getStartDate().isValid() && 
						pMatchAux->getStartTime().isValid() &&
						pMatchAux->getStatus() < GMemoryDataBase::eSchedulled)
					{
						pMatchAux->setStatus(CHMemoryDataBase::eSchedulled);
						
					}
					else
					{
						if( (!pMatchAux->getStartDate().isValid() || 
							 !pMatchAux->getStartTime().isValid()) &&
							pMatchAux->getStatus() == GMemoryDataBase::eSchedulled)
						{	
							pMatchAux->setStatus(CHMemoryDataBase::eAvailable);
							
						}
					}
					
					outMatch(pMatchAux);
					w->redraw(GR_SUBMATCH);
					
				}				
			}
			break;
			/*case 2:
			{
				CString aux("");
				short previous = pMatchAux->getMatchNumber();
	
				aux.Format("%d", pMatchAux->getMatchNumber());
				text = w->editGridCell(GR_SUBMATCH, col, lin, aux);
				if (previous == (short)atoi(text))
					break;
				if(text != "")
					pMatchAux->setMatchNumber((short)atoi(text));
				else pMatchAux->setMatchNumber(0);
				outMatch(pMatchAux);
				w->redraw(GR_SUBMATCH);
				break;
			}*/
			case 7:
			{
				break;
			}
		}
	}
}
void CHCnfgTeamSchedule::showComboSessions(int x, int y)
{
	CString sessionCode=_T("");
	CHSession* pSession=0;
	w->delAllItems (CBOSUBGRIDSESSION);
	
	CHMatch* pMatchAux = (CHMatch*)w->getGridLParam(GR_SUBMATCH,y);
	if(pMatchAux->getStatus()==CHMemoryDataBase::eFinished)
	{	::msg("Status Official!!", "I can´t change match data!!",ICO_X,MSG_OK);
		return;
	}
	GSortedVector gsv=GSortedVector(CHMemoryDataBase::getColSessions(),orderCHSessions);

	w->addItem(CBOSUBGRIDSESSION,0," NONE",0,0);

	for (size_t j= 0; j < gsv.entries(); j++)
	{
		pSession = (CHSession *)gsv[j]->getElement();
		if (pSession->getDate()==pMatchAux->getStartDate())
		{
			w->addItem(CBOSUBGRIDSESSION,0,eventControlOp.getSessionDescription(pSession),0,(LPARAM)pSession);
		}
	}
	// SELECTING ITEM
	if (pMatchAux->getSession())
	{
		pSession =(CHSession*) mem()->findSession(*pMatchAux->getSession());
		if (pSession)
		{
			w->selectItemTxt(CBOSUBGRIDSESSION,eventControlOp.getSessionDescription(pSession));												
		}
	}
	// SHOW COMBO
	pSession=(CHSession*)w->showGridCombo(GR_SUBMATCH,CBOSUBGRIDSESSION,x,y);
	if (pSession/* && canChangeSession(pMatch,pSession)*/)
	{
		pMatchAux->setSession(pSession);
		outMatch(pMatchAux);
	}
	else if (!pSession)
	{
		pMatchAux->setSession(0);
		outMatch(pMatchAux);
	}
}

void CHCnfgTeamSchedule::showComboCourts(int x, int y)
{
	w->delAllItems (CBOSUBGRIDCOURT);
	CHMatch* pMatchAux = (CHMatch*)w->getGridLParam(GR_SUBMATCH,y);
	if(pMatchAux->getStatus()==CHMemoryDataBase::eFinished)
	{	::msg("Status Official!!", "I can´t change match data!!",ICO_X,MSG_OK);
		return;
	}
	w->addItem(CBOSUBGRIDCOURT,0," NONE",0,0);			   

	RWSet aCourts=CHMemoryDataBase::getColCourts();
	GSortedVector gsv=GSortedVector(aCourts,orderCourts);
	GCourt * pCourt;
	for ( size_t j= 0; j < gsv.entries(); j++)
	{
		pCourt = (GCourt *)gsv[j]->getElement();
		if(pCourt->getVenue()==pMatchAux->getVenue())	
           w->addItem(CBOSUBGRIDCOURT,j+1,eventControlOp.getCourtDescription(pCourt),0,LPARAM(pCourt));
	}
	// SELECTING ITEM
	pCourt = pMatchAux->getCourt();
	if (pCourt)
	{
		w->selectItemTxt(CBOSUBGRIDCOURT,eventControlOp.getCourtDescription(pCourt));														
	}
	// SHOW COMBO
	pCourt=(GCourt*)w->showGridCombo(GR_SUBMATCH,CBOSUBGRIDCOURT,x,y);
	if (pCourt/* && canChangeCourt(pMatchAux,pCourt)*/)
	{
		pMatchAux->setCourt(pCourt);
		outMatch(pMatchAux);
	}	
	else if (!pCourt)
	{
		pMatchAux->setCourt(0);
		outMatch(pMatchAux);
	}
}

LRESULT CHCnfgTeamSchedule::onChangeMatch(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch (wParam)
	{
	case TRN_SET_REGISTER:
	case TRN_SET_MEMBER:
		w->redraw(LST_TEAM_HOME);
		w->redraw(LST_TEAM_VISIT);
		break;
	case TRN_CHANGE_MATCH_STATUS:
		paintStatus();
		break;
	case TRN_SET_JUDGE:
	case TRN_DELETE_JUDGE:
	case TRN_SET_NAREGISTER:
	{
		/*if (pJudgesDlg)
			pJudgesDlg->SendMessage(TRN_JUDGE_CHANGE_DLG,wParam,0);*/
		break;
	}
	}
	return true;
}

BOOL CHCnfgTeamSchedule::DestroyWindow() 
{
	if (w)
		delete w;		
	if (pBmpFlagH)
		delete pBmpFlagH;

	if (pBmpFlagV)
		delete pBmpFlagV;

	if (pBmpFlagJS)
		delete pBmpFlagJS;

	if (pBmpFlagJU)
		delete pBmpFlagJU;

	if (pStatusMngt)
		delete pStatusMngt;
	
	unLockMatch();
	return CDialog::DestroyWindow();
}

void CHCnfgTeamSchedule::onOK() 
{
/*	if (!pComboCourt && pComboVenue)
		::msg("Warning!!", "Court not selected.It wouldn't save selected venue!!",ICO_X,MSG_OK);			*/

	CDialog::OnOK();
}

void CHCnfgTeamSchedule::outMatch(CHMatch *pMatchAux)
{
	APP::out(TRN_CHANGE_MATCH);
	APP::out(*pMatchAux,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);		
	APP::out();
}

RWBoolean CHCnfgTeamSchedule::registersInMatch(CHMatch *pMatchAux)
{
	GSortedVector &vMatchResult=pMatchAux->getCompetitorsVector();
	CHMatchResult *pMatchResult=0;
	for(size_t i=0;i<vMatchResult.entries();i++)
	{
		pMatchResult=(CHMatchResult*)vMatchResult[i]->getElement();
		if(pMatchResult)
		{
			if(!pMatchResult->getRegister())
				return false;
		}
	}
	return true;
}

void CHCnfgTeamSchedule::setStartTimes()
{
	if (::msg("Attention¡¡","Do you want to set submatch start time´s?",ICO_X,MSG_YESNO) == RET_NO)
		return;
	if(w->getTxt(ED_START_TIME).isNull() || w->getTxt(ED_TIME_BEHIND).isNull())
		return;
//CString
	GTime time(w->getTxt(ED_START_TIME),"@@:&&");
	
	GTime timeBehind(w->getTxt(ED_TIME_BEHIND),"&&");
	
	
	GSortedVector vMatches=pMatch->getSubMatches();
	for(size_t i=0;i<vMatches.entries();i++)
	{
		CHMatch *pSubMatch=(CHMatch*)vMatches[i]->getElement();
		if(pSubMatch)
		{
			long timeL=0,timeBehindL=0;
			timeL=time.getTime();
			timeBehindL=timeBehind.getTime();
			long resta=3600;
			if(timeL==3600)
				resta=0;
			unsigned long time=(timeL+timeBehindL*i)/1000-resta;
			if(time==0)
				time=1;
			RWTime timeSet(time);
			pSubMatch->setStartTime(timeSet);
			outMatch(pSubMatch);		
		}
	}
	w->redraw(GR_SUBMATCH,FALSE);
}
void CHCnfgTeamSchedule::fillMatchMembersTeam(short num)
// Fill the "Match Members Team 1 Grid"
{
	w->gridDeleteAllItems(GR_MEMBER1+num);
	GSortedVector & vCompetitors=pMatch->getCompetitorsVector();

	/*if(vCompetitors.entries())
		vCompetitors.sort(orderPosition);*/

	CHTeamMatchsCnfg * pTeamMatchCnfg=CHMemoryDataBase::findTeamMatchsCnfg(((CHPhase*)pMatch->getPhase()));
	if(!pTeamMatchCnfg) return;
	if(short(vCompetitors.entries())>num)
	{
		CHMatchResult *pMatchResult=(CHMatchResult*)vCompetitors[num]->getElement();
		GSortedVector vMatchMembers=pMatchResult->getMembersVector();
		for(size_t i=0;i<size_t(pTeamMatchCnfg->getCompMember(num));i++) //vMatchMembers.entries()
		{
			CHMatchMember * pMatchMember=(CHMatchMember*)vMatchMembers[i]->getElement();
			if(!pMatchMember)
				continue;
				
			w->addGridLine(GR_MEMBER1+num,LPARAM(pMatchMember),"");
		}
	}
}
void CHCnfgTeamSchedule::fillMembersTeam(short num)
// Fill the "Members Team 1 Grid"
{
	w->gridDeleteAllItems(GR_TEAM_MEMBER1+num);
	
	GSortedVector & vCompetitors=pMatch->getCompetitorsVector();

	/*if(vCompetitors.entries())
		vCompetitors.sort(orderPosition);*/
	
	if(short(vCompetitors.entries())>num)
	{
		CHMatchResult *pMatchResult=(CHMatchResult*)vCompetitors[num]->getElement();
		if(pMatchResult)
		{
			if(pMatchResult->getInscription())
			{
				GSortedVector vMembers=pMatchResult->getInscriptionMembersVector();		
				for(size_t i=0;i<vMembers.entries();i++)
				{
					CHMember * pMember=(CHMember*)vMembers[i]->getElement();
					if(!pMember)
						continue;
						
					if(!inMatchMember(pMember,num))
						w->addGridLine(GR_TEAM_MEMBER1+num,LPARAM(pMember),"");
				}
			}
		}	
	}
}
RWBoolean CHCnfgTeamSchedule::inMatchMember(CHMember *pMember,short num)
{
	for(short i=0;i<w->getGridNItems(GR_MEMBER1+num);i++)
	{
		CHMatchMember *pMatchMember=(CHMatchMember*)w->getGridLParam(GR_MEMBER1+num,i);
		if(pMatchMember && pMatchMember->getMember())
		{
			if(pMatchMember->getMember()->getKey()==pMember->getKey())
				return true;
		}
	}
	return false;
}
void CHCnfgTeamSchedule::setMatchMembers()
{
	CHTeamMatchsCnfg * pTeamMatchCnfg=CHMemoryDataBase::findTeamMatchsCnfg(((CHPhase*)pMatch->getPhase()));
	
	/*if(((CHPhase*)pMatch->getPhase())->getIdTeamMatchsCnfg())
	{
		// Cojo el tipo de competicion que tiene asignado dicho partido
		CHTeamMatchsCnfg * pTeamMatchCnfg=CHMemoryDataBase::findTeamMatchsCnfg(((CHPhase*)pMatch->getPhase())->getIdTeamMatchsCnfg());
		if(!pTeamMatchCnfg)
		{
			pTeamMatchCnfg=CHMemoryDataBase::findTeamMatchsCnfg(((CHPhase*)pMatch->getEvent())->getIdTeamMatchsCnfg());	
		}*/
		if(pTeamMatchCnfg)
		{
			// Para cada partido le voy a asignar sus match members
			GSortedVector vMatches=pMatch->getSubMatches();
			CHMatch *pSubMatch=0;
			for(short i=1;i<=pTeamMatchCnfg->getMatches() && i<=short(vMatches.entries());i++)
			{
				pSubMatch=(CHMatch*)vMatches[i-1]->getElement();
				if(pSubMatch)
				{
					GSortedVector &vCompetitors=pSubMatch->getCompetitorsVector();
					CHMatchResult *pMatchResult=0;
					for(size_t j=0;j<vCompetitors.entries();j++)
					{
						pMatchResult = (CHMatchResult*)vCompetitors[j]->getElement();
						if(pMatchResult &&
						   pMatchResult->getInscription())
						{
							if(j==0)
							{
								setMatchNumberCode(eHome,pMatchResult,pTeamMatchCnfg,i);
							}
							else // Dobles
							{
								setMatchNumberCode(eAway,pMatchResult,pTeamMatchCnfg,i);
							}		
						}
					}
				}
			}
		}
	
	//}
}
void CHCnfgTeamSchedule::setMatchNumberCode(short type,CHMatchResult *pMatchResult,CHTeamMatchsCnfg *pTeamMatchCnfg,short numMatch)
{
	GSortedVector vMatchMembers=pMatchResult->getMembersVector();
	CHMatchMember *pMatchMember=0;

	for(size_t i=0;i<vMatchMembers.entries();i++)
	{
		pMatchMember = (CHMatchMember*)vMatchMembers[i]->getElement();
		if(pMatchMember)
		{
			short numMatchMember=pTeamMatchCnfg->getCompOrder(numMatch,type,short(i));
			if (numMatchMember!=-1)
			{
				CHMatchMember *pMatchMemberAux=getTeamMatchMember(short(type),numMatchMember);
				if (pMatchMemberAux)
				{
					if (pMatchMemberAux->getMember())
						pMatchMember->setMember(pMatchMemberAux->getMember());
					else
					{ //si no ponemos a nadie en ABXY podemos seleccionar a quien queramos dentro de los
					  //miembros que tengan. El orden es
					  //individual A, individual X, individual B, individual Y,
					  //los dos miembros del dobles de equipo AB,
					  //los dos miembros del dobles de equipo XY, etc...
						CCHCnfgTeamMembersDlg teamMembDlg((CHMemoryDataBase *)mem(),pMatch,pMatchMember);
						teamMembDlg.DoModal();
						if (!teamMembDlg.getSelMember())
							pMatchMember->setMember(0);
					}
					theApp.queueOut(pMatchMember);
				}
			}
			else
			{
				CCHCnfgTeamMembersDlg teamMembDlg((CHMemoryDataBase *)mem(),pMatch,pMatchMember);
				teamMembDlg.DoModal();
				if (!teamMembDlg.getSelMember())
					pMatchMember->setMember(0);
				theApp.queueOut(pMatchMember);
			}
		}
	}
//	theApp.out(TRN_SET_MATCH_MEMBERS);
}

CHMatchMember* CHCnfgTeamSchedule::getTeamMatchMember(short homeAway,short number)
{
	GSortedVector &vCompetitors=pMatch->getCompetitorsVector();
	CHMatchResult *pMatchResult=0;
	if(homeAway<short(vCompetitors.entries()))
	{
		pMatchResult = (CHMatchResult*)vCompetitors[homeAway]->getElement();
		if(pMatchResult)
		{
			GSortedVector vMatchMembers=pMatchResult->getMembersVector();
			CHMatchMember *pMatchMember=0;
			if(number<=short(vMatchMembers.entries()))
			{	pMatchMember=(CHMatchMember*)vMatchMembers[number-1]->getElement();
				return pMatchMember;
			}
		}
	}
	return 0;
}
bool CHCnfgTeamSchedule::lockMatch(CHMatch *pMatch)
{
	if (!pMatch)
		return false;

	RWCString lockStringMatch;
	char match[5];
	
	lockStringMatch += pMatch->getEventCode();
	lockStringMatch += "-" + pMatch->getPhaseCode();
	lockStringMatch += "-" + pMatch->getPoolCode();	
	sprintf(match,"%d",pMatch->getCode());
	lockStringMatch += match;

	unLockMatch();

	if(!APP::lock(lockStringMatch))
		return false;
	else
	{
		lastMatchLocked = lockStringMatch;
		return true;
	}

	return true;
}

void CHCnfgTeamSchedule::unLockMatch()
{
	APP::unlock(lastMatchLocked);
}

void CHCnfgTeamSchedule::paintTeamResult()
{
	RWCString result="";

	if(pMatch->getStatus()>CHMemoryDataBase::eStartList)
	{   // Match Description
		result=pMatch->getResultAsString();  
	}
	w->changeTxt(LBL_TEAM_RESULT ,result);
}

void CHCnfgTeamSchedule::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
		
	switch(wParam)
	{
		case 27:
			OnCancel();
			break;
	}
}
void CHCnfgTeamSchedule::clearResults(CHMatch *pMatchAux)
{
	if(eventControlOp.clearResults(pMatchAux))
	{
		eventControlOp.recalculateTeam(pMatchAux);
		w->redraw(GR_SUBMATCH,FALSE);
		paintTeamResult();
	}
}
void CHCnfgTeamSchedule::disableEnableControls(RWBoolean enable)
{
		
/*	w->enable (GR_SUBMATCH,enable);
	w->enable (GR_MEMBER1,enable);
	w->enable(GR_MEMBER2,enable);*/
}