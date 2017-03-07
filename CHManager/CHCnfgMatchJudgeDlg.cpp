/*************************************************************************************
*	© Copyright MSL Software, S.L., 2001
*
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHCnfgMatchJudgeDlg.cpp
*   Description	: 
*
*	Author		: Chess Team
*	Date created: 27-12-2005
* 	Project		:
*
***************************************************************************************/

#include "stdafx.h"
#include "CHmanager.h"
#include "CHCnfgMatchJudgeDlg.h"
#include <GUI/FLAGS/flags.h>
#include <core/G/GMsgDefines.h>
#include <core/TH/GTHMsgDefines.h>
#include <sports/CH/data/CHMsgDefines.h>
#include <sports/CH/data/CHMatchMember.h>
#include <sports/CH/data/CHSession.h>
#include <sports/CH/data/CHRegister.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define		LBL_OK			 1000
#define		LBL_EXIT		 1001
#define		LBL_TEAM_H		 1002
#define		LBL_TEAM_V		 1003
#define		LBL_HOME		 1004
#define		LBL_VISIT		 1005
#define		LBL_VS			 1006
#define		LBL_MATCH		 1007
#define		LBL_STATUS		 1008
#define		LBL_UMPIRE1		 1009
#define		LBL_UMPIRE2		 1010
#define		IDBACKG			 1011
#define     IDWHITE			 1012
#define     IDGREY			 1013
#define		IDCOLBLUE		 1014
#define		IDCOLRED		 1015
#define		IDCOLNAVY		 1016
#define		IDCOLYELLOW		 1017
#define		IDCOLGREEN		 1018
#define		IDCOLBLACK		 1019
#define		FNTDLG			 1020
#define		FNTMAX			 1021
#define		FNTMED			 1022
#define		FNTSUP			 1023
#define		FNTMIN			 1024
#define		FLAG_TEAM_H		 1025
#define		FLAG_TEAM_V		 1026
#define     FLAG_UMPIRE1	 1027
#define     FLAG_UMPIRE2	 1028
#define		BUT_UMPIRE1		 1029
#define		BUT_UMPIRE2		 1030
#define     LST_TEAM_HOME	 1031
#define     LST_TEAM_VISIT	 1032
#define     FR_HOME			 1033
#define     FR_VISIT		 1034
#define		LINEBCK			 1035
#define		FR_JUDGE		 1036
#define		LBL_TITLE		 1037
#define		LBL_RAYA1		 1038
#define		LBL_TITLE2		 1039
#define		LBL_RAYA2		 1040
#define		LBL_TITLE3		 1041
#define		LBL_RAYA3		 1042
#define		FR_HOMEAWAY	     1043
#define		IDBLUE			 1044
#define		IDYELLOW		 1045
#define		BU_CLEARTEAMH	 1046
#define		BU_CLEARTEAMV	 1047
#define		LBL_GROUP_TEAM_V 1048
#define		LBL_GROUP_TEAM_H 1049

CHCnfgMatchJudgeDlg::CHCnfgMatchJudgeDlg(CWnd* pParent /*=NULL*/,CHMatch *pSelMatch)
:CDialog(CHCnfgMatchJudgeDlg::IDD, pParent)
,pMatch(pSelMatch)
,pComboVenue(0)
,pComboCourt(0)
,pJudgesDlg(0)
{
	pBmpFlagH=new CBitmap();
	pBmpFlagV=new CBitmap();
	pBmpFlagJU =new CBitmap();
	pBmpFlagJS =new CBitmap();
	pStatusMngt = new CHStatusManager();
	
	//{{AFX_DATA_INIT(CHCnfgMatchJudgeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CHCnfgMatchJudgeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHCnfgMatchJudgeDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHCnfgMatchJudgeDlg, CDialog)
	//{{AFX_MSG_MAP(CHCnfgMatchJudgeDlg)
	ON_MESSAGE(UM_CLICK,onClick)
	ON_MESSAGE(UM_DBLCLICK,onDblClick)
	ON_MESSAGE(UM_CHNG_MATCHJUDGE,onChangeMatchJudge)
	ON_MESSAGE(UM_KEYDOWN, OnKeyDown)
//	ON_MESSAGE(TRN_MATCH_CHANGE_DLG,onChangeMatch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CHCnfgMatchJudgeDlg::OnInitDialog() 
{
	w = new CGraphicWnd(this);

	w->destroyBackground (IDBACKG);
	w->addBackgroundColor(IDBACKG,RGB(240,240,250));
	w->setBackground (IDBACKG);	
	
	w->addBackgroundColor(LINEBCK, RGB( 58,110,165));	
	w->addBackgroundColor(IDWHITE,RGB(255,255,255));
	w->addBackgroundColor(IDGREY,RGB(200,200,200));
	w->addBackgroundColor(IDBLUE,RGB(210,210,255));
	w->addBackgroundColor(IDYELLOW,RGB(255,255,240));
			
	w->addFont(FNTDLG, 6,15,1,0,1,0,_T("Arial"));
	w->addFont(FNTMAX, 9,20,1,1,0,0,_T("Arial"));
	w->addFont(FNTMED, 7,15,1,0,0,0,_T("Arial"));
	w->addFont(FNTSUP,  15,30,1,0,0,0,_T("Arial"));
	w->addFont(FNTMIN, 6,12,1,0,0,0,_T("Arial"));
	
	w->addColorSet(IDCOLBLUE,RGB(0,0,170),COLOR_DEFAULT_OFF ,COLOR_DEFAULT_HITX,COLOR_DEFAULT_HIGH,COLOR_DEFAULT_L3D,COLOR_DEFAULT_N3D,COLOR_DEFAULT_D3D );
	w->addColorSet(IDCOLRED,RGB(200,0,0),COLOR_DEFAULT_OFF,COLOR_DEFAULT_HITX,COLOR_DEFAULT_HIGH,COLOR_DEFAULT_L3D,COLOR_DEFAULT_N3D,COLOR_DEFAULT_D3D);
	w->addColorSet(IDCOLNAVY,RGB(0,0,100),COLOR_DEFAULT_OFF,COLOR_DEFAULT_HITX,COLOR_DEFAULT_HIGH,COLOR_DEFAULT_L3D,COLOR_DEFAULT_N3D,COLOR_DEFAULT_D3D);
	w->addColorSet(IDCOLBLACK,RGB(0,0,0),COLOR_DEFAULT_OFF,RGB(0,0,0),RGB(200,200,200),COLOR_DEFAULT_L3D,COLOR_DEFAULT_N3D,COLOR_DEFAULT_D3D);
	w->addColorSet(IDCOLGREEN,RGB(0,180,0),COLOR_DEFAULT_OFF,RGB(0,0,0),RGB(200,200,200),COLOR_DEFAULT_L3D,COLOR_DEFAULT_N3D,COLOR_DEFAULT_D3D);
	w->addColorSet(IDCOLYELLOW,RGB(250,180,37),COLOR_DEFAULT_OFF,RGB(0,0,0),RGB(200,200,200),COLOR_DEFAULT_L3D,COLOR_DEFAULT_N3D,COLOR_DEFAULT_D3D);

	w->createLabel( LBL_TITLE, CRect(10,5,620,20), "Match Configuration", BORDER_NONE, JUST_LEFT, IDBACKG, IDCOLNAVY, FNTMED );
	w->createLabel( LBL_RAYA1, CRect(10,22,620,25), "", BORDER_NONE, JUST_LEFT, LINEBCK);
	
	w->createLabelEx(LBL_OK ,CRect(570,240,620,255),"OK",BORDER_NONE,JUST_CENTER,IDBACKG,IDCOLBLUE,FNTDLG,IDBACKG,IDCOLRED);
	//w->createLabelEx(LBL_EXIT ,CRect(570,350,620,400),"Cancel",BORDER_NONE,JUST_CENTER,IDBACKG,IDCOLBLUE,FNTDLG,IDBACKG,IDCOLRED);

	showHeadCompetitors();
	showConfiguredMatch();

	CDialog::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
              // EXCEPTION: OCX Property Pages should return FALSE
}

void CHCnfgMatchJudgeDlg::showHeadCompetitors()
{
	if (!pMatch)
		return;

	w->createFrame(FR_HOMEAWAY,CRect( 10,15,620,105),BORDER_DOWN,0,0,IDBLUE);	

	CString match = _T("");
	match.Format(_T("%s%d") , pMatch->getEventSDescription(),pMatch->getMatchNumber());
	/*CString str =  _T("Match ");
	str += match;*/
	w->createLabel(LBL_MATCH,CRect(250,30,380,50),match,BORDER_NONE,JUST_CENTER,IDBLUE,IDCOLNAVY,FNTSUP);

	w->createLabel(LBL_HOME,CRect( 60, 30,115,60),"Home",BORDER_NONE,JUST_LEFT,IDBLUE,IDCOLBLUE,FNTMAX);
	w->createLabel(LBL_VISIT,CRect(390,30,455,60),"Away",BORDER_NONE,JUST_RIGHT,IDBLUE,IDCOLRED,FNTMAX);
	
	w->createLabel(LBL_VS,CRect(275,65,315,100),"vs",BORDER_NONE,JUST_RIGHT,IDBLUE,IDCOLBLACK,FNTMED);
	
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
		w->createUserBitmap(FLAG_TEAM_H ,CRect( 20, 65, 40,95),pBmpFlagH,TRUE,BORDER_DOWN);
		w->createLabel(LBL_GROUP_TEAM_H,CRect( 20,85,55,100),pRegister->getGroup(),BORDER_NONE,JUST_LEFT,IDBLUE,IDCOLBLUE,FNTMED);
		w->createLabel(LBL_TEAM_H,CRect( 60,65,250,95),pRegister->getPrnLName(),BORDER_DOWN,JUST_LEFT,IDBLUE,IDCOLBLUE,FNTMED);
				
	}

	if (pMResultVisit && pMResultVisit->getRegister())
	{
		CHRegister *pRegister = (CHRegister *)pMResultVisit->getRegister();
		GGroup *pGroupSel = CHMemoryDataBase::findGroup(pRegister->getGroup());
		getFlag(pGroupSel->getGroup(),SML,pBmpFlagV);	
		w->createUserBitmap(FLAG_TEAM_V ,CRect(365, 65, 395,95),pBmpFlagV,TRUE,BORDER_DOWN);
		w->createLabel(LBL_GROUP_TEAM_V,CRect(365,85,400,100),pRegister->getGroup(),BORDER_NONE,JUST_LEFT,IDBLUE,IDCOLBLUE,FNTMED);
		w->createLabel(LBL_TEAM_V,CRect(405,65,605,95),pRegister->getPrnLName(),BORDER_DOWN,JUST_LEFT,IDBLUE,IDCOLRED,FNTMED);
				
	}
	
}


void CHCnfgMatchJudgeDlg::showConfiguredMatch()
{
	if (pMatch->getStatus() >= GMemoryDataBase::eRunning)
		w->enable(LBL_STATUS,false);

	w->createLabel( LBL_TITLE3, CRect( 10,130,620,145), "Select Judge", BORDER_NONE, JUST_LEFT, IDBACKG, IDCOLNAVY, FNTMED );
	w->createLabel( LBL_RAYA3, CRect( 10,147,620,150), "", BORDER_NONE, JUST_LEFT, LINEBCK);
	w->createFrame(FR_JUDGE,CRect( 10,150,620,230),BORDER_DOWN,0,0,IDBLUE);	

	w->createButton(BUT_UMPIRE1,CRect( 60,160,170,180),"First Umpire",IDGREY,IDCOLNAVY,FNTDLG);
	
	w->createLabelEx(BU_CLEARTEAMH,CRect(240,175,280,190),"Clear",BORDER_NONE,JUST_RIGHT,IDBLUE,IDCOLBLUE,FNTDLG,IDBLUE,IDCOLRED);
	w->createButton(BUT_UMPIRE2,CRect(370,160,480,180),"Second Umpire",IDGREY,IDCOLNAVY,FNTDLG);
	w->createLabelEx(BU_CLEARTEAMV,CRect(550,175,590,190),"Clear",BORDER_NONE,JUST_RIGHT,IDBLUE,IDCOLBLUE,FNTDLG,IDBLUE,IDCOLRED);

	w->createLabelEx(LBL_STATUS,CRect(240,230,340,260),"",BORDER_NONE,JUST_CENTER,IDBACKG,IDCOLNAVY,FNTDLG,IDBACKG,IDCOLBLACK);
		
	paintStatus();
	w->createLabel(LBL_UMPIRE1 ,CRect( 60,190,280,220),"",BORDER_DOWN,JUST_LEFT,IDBACKG,IDCOLBLACK,FNTMED);	
	w->createLabel(LBL_UMPIRE2 ,CRect(370,190,590,220),"",BORDER_DOWN,JUST_LEFT,IDBACKG,IDCOLBLACK,FNTMED);	
	
	GSortedVector &vMatchJudges = pMatch->getJudgesVector();
	CHMatchJudge *pMatchJudge =0;
	for (size_t i= 0; i < vMatchJudges.entries() ;i++)
	{
		pMatchJudge = (CHMatchJudge *)vMatchJudges[i]->getElement();
		if( pMatchJudge )
			showJudge(pMatchJudge );
	}
}	


void CHCnfgMatchJudgeDlg::showJudge(CHMatchJudge *pMatchJudge)
{
	if (pMatchJudge) 
	{
		/*GFunction *pFunction = pMatchJudge->getFunction();
		if (pFunction)
		{
			switch(pFunction->getFunction())
			{
				case CHJudge::eUmpire:
				{*/
					if(pMatchJudge->getPositionCode()==1)
					{
						w->changeTxt(LBL_UMPIRE1 , pMatchJudge->getPrnLName());
//						CHRegister *pRegister = (CHRegister *)pMatchJudge->getRegister();
						GGroup *pGroupSel = CHMemoryDataBase::findGroup(pMatchJudge->getGroup());
						getFlag(pGroupSel->getGroup(),SML,pBmpFlagJU);	
						w->createUserBitmap(FLAG_UMPIRE1,CRect( 20,190, 40,210),pBmpFlagJU,TRUE,BORDER_DOWN);
						w->redraw(FLAG_UMPIRE1);
					}
					else 
					{
						w->changeTxt(LBL_UMPIRE2, pMatchJudge->getPrnLName());
//						CHRegister *pRegister = (CHRegister *)pMatchJudge->getRegister();
						GGroup *pGroupSel = CHMemoryDataBase::findGroup(pMatchJudge->getGroup());
						getFlag(pGroupSel->getGroup(),SML,pBmpFlagJS);			
						w->createUserBitmap(FLAG_UMPIRE2,CRect(330, 190,350,210),pBmpFlagJS,TRUE,BORDER_DOWN);
						w->redraw(FLAG_UMPIRE2);
					}
			/*	}
				break;
				
				default:
					break;
			}
		}*/
	}
}

void CHCnfgMatchJudgeDlg::paintStatus()
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
				w->changeColor(LBL_STATUS,IDCOLBLUE);
				break;
			case GMemoryDataBase::eSchedulled:
				w->changeColor(LBL_STATUS,IDCOLGREEN);
				break;
			case GMemoryDataBase::eRunning:
				w->changeColor(LBL_STATUS,IDCOLYELLOW);
				break;
			case GMemoryDataBase::eFinished:
				w->changeColor(LBL_STATUS,IDCOLRED);
				break;
			default:
				break;
		}
	}
}

LRESULT CHCnfgMatchJudgeDlg::onClick(WPARAM wParam, LPARAM lParam)
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
		case BUT_UMPIRE1:
		{
			pJudgesDlg = new CHJudgesDlg(pMatch ,CHJudge::eUmpire ,1,this );	
			pJudgesDlg->DoModal();
			delete pJudgesDlg;
			break;
		}
		case BUT_UMPIRE2:
		{
			pJudgesDlg = new CHJudgesDlg(pMatch ,CHJudge::eUmpire,2,this );	
			pJudgesDlg->DoModal();
			delete pJudgesDlg;
			break;
		}
		case BU_CLEARTEAMH:
		{
			removeMatchJudge(1);
			w->changeTxt(LBL_UMPIRE1,"");
			break;
		}
		case BU_CLEARTEAMV:
		{
			removeMatchJudge(2);
			w->redraw(LBL_UMPIRE2,TRUE);
			w->changeTxt(LBL_UMPIRE2,"");
			break;
		}
		
	}
	return 0;
}
void CHCnfgMatchJudgeDlg::removeMatchJudge(short numCode)
{
	GSortedVector &vJudges = pMatch->getJudgesVector();
	CHMatchJudge *pMatchJudge =0;
	
	for (size_t i=0; i < vJudges.entries() ; i++)
	{
		pMatchJudge = (CHMatchJudge *) vJudges[i]->getElement();
		if (pMatchJudge &&
			pMatchJudge->getPositionCode() == numCode)

		{
			pMatchJudge = (CHMatchJudge *)mem()->removeMatchJudge(*pMatchJudge);
			APP::out(TRN_REMOVE_MATCH_JUDGES);
			APP::out(*pMatchJudge,OP_DELETE,TO_VENUE|TO_DATABASE);		
			APP::out();
		}
	}
	
	removeTeamMatchJudges(numCode);

}
void CHCnfgMatchJudgeDlg::removeTeamMatchJudges(short numCode)
{
	if(pMatch->areTeams())
	{
		GSortedVector vMatches=pMatch->getSubMatches();
		CHMatch *pMatchAux=0;
		for(size_t i=0;i<vMatches.entries();i++)
		{
			pMatchAux = (CHMatch*)vMatches[i]->getElement();
			if(pMatchAux)
			{
				GSortedVector &vJudges = pMatchAux->getJudgesVector();
				CHMatchJudge *pMatchJudge =0;
				for (size_t i=0; i < vJudges.entries() ; i++)
				{
					pMatchJudge = (CHMatchJudge *) vJudges[i]->getElement();
					if (pMatchJudge &&
						pMatchJudge->getPositionCode() == numCode)

					{
						pMatchJudge = (CHMatchJudge *)mem()->removeMatchJudge(*pMatchJudge);
						APP::out(TRN_REMOVE_MATCH_JUDGES);
						APP::out(*pMatchJudge,OP_DELETE,TO_VENUE|TO_DATABASE);		
						APP::out();
					}
				}
			}
		}
	}
}
void CHCnfgMatchJudgeDlg::changeStatus()
{
	unsigned char newStatus;
	unsigned char status = pMatch->getStatus();
	switch(status)
	{
		case GMemoryDataBase::eStartList:
			newStatus = GMemoryDataBase::eSchedulled;
			pStatusMngt->run(*pMatch,newStatus);
			
			// Lo que quiero es tener los Splits inicializados como el partido pero
			// no necesito ninguna progapacion ya que ya lo ha hecho el match
			pStatusMngt->saveTeamSubMatchesStatus(pMatch,GMemoryDataBase::eSchedulled);
	
			break;
		case GMemoryDataBase::eSchedulled:
			if(registersInMatch())			
			{
				newStatus = GMemoryDataBase::eStartList;
				pStatusMngt->run(*pMatch,newStatus);
				// Lo que quiero es tener los Splits inicializados como el partido pero
				// no necesito ninguna progapacion ya que ya lo ha hecho el match
				pStatusMngt->saveTeamSubMatchesStatus(pMatch,GMemoryDataBase::eStartList);
				
			}
			else ::msg("Attention","Match without competitor/s available",ICO_X,MSG_OK);
			break;
		default:
			break;
	}
	paintStatus();
} 

LRESULT CHCnfgMatchJudgeDlg::onChangeMatchJudge(WPARAM wParam, LPARAM lParam)
{
	CHMatchJudge *pMatchJudge = (CHMatchJudge *)wParam;
	showJudge(pMatchJudge );
	return 0;
	UNREFERENCED_PARAMETER(lParam);
}

LRESULT CHCnfgMatchJudgeDlg::onSelectMatchMember(WPARAM wParam, LPARAM lParam)
{
	CHMatchMember *pMatchMember = (CHMatchMember *)wParam;
	if (pMatchMember) 
	{
		int y;
		if (pMatchMember->getMatchResult()->getPosition() == 1)
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

void CHCnfgMatchJudgeDlg::onDblClick(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
		case LST_TEAM_HOME:
		case LST_TEAM_VISIT:
		{
			//WORD hi=HIWORD(lParam);
			//CHMatchMember *pMatchMember =(CHMatchMember *) w->getGridLParam(wParam,hi);
			//CHMatchMemberDlg memberDlg(pMatchMember,this);
			//memberDlg.DoModal();
		}
		default:
			break;
	}
	UNREFERENCED_PARAMETER(lParam);
	UNREFERENCED_PARAMETER(wParam);

}

LRESULT CHCnfgMatchJudgeDlg::onChangeMatch(WPARAM wParam, LPARAM lParam)
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
		if (pJudgesDlg)
			pJudgesDlg->SendMessage(TRN_JUDGE_CHANGE_DLG,wParam,0);
		break;
	}
	}
	return true;
}

BOOL CHCnfgMatchJudgeDlg::DestroyWindow() 
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
	
	return CDialog::DestroyWindow();
}

void CHCnfgMatchJudgeDlg::onOK() 
{
/*	if (!pComboCourt && pComboVenue)
		::msg("Warning!!", "Court not selected.It wouldn't save selected venue!!",ICO_X,MSG_OK);			*/

	CDialog::OnOK();
}

void CHCnfgMatchJudgeDlg::outMatch(CHMatch *pMatch)
{
	APP::out(TRN_CHANGE_MATCH);
	APP::out(*pMatch,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);		
	APP::out();
}

RWBoolean CHCnfgMatchJudgeDlg::registersInMatch()
{
	GSortedVector &vMatchResult=pMatch->getCompetitorsVector();
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

void CHCnfgMatchJudgeDlg::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
		
	switch(wParam)
	{
		case 27:
			OnCancel();
			break;
			
	}
}
