/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior wriCHen permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHTeamCompCnfg.cpp
*	Description	:
*
*	Author		:Chess Team
*	Date created:15-12-2005
* 	Project		:
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdafx.h"
#include "CHmanager.h"
#include "CHTeamCompCnfg.h"
#include "CHDefines.h"

#include <Gui/GS/guisports.h>
#include <Gui/TH/guithsports.h>
#include <REPORTS/V/orderView.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define LBL_MATCHS	10
#define EDT_MATCHS			(LBL_MATCHS+1)
#define LBL_COMP			(EDT_MATCHS+1)
#define EDT_COMP			(LBL_COMP+1)
#define LBL_MATCH_CNFG		(EDT_COMP+1)
#define LBL_LANE			(LBL_MATCH_CNFG+1)
#define GRD_MATCH_CNFG		(LBL_LANE+1)
#define LBL_DESCRIPTION		(GRD_MATCH_CNFG+1)
#define GRD_DESCRIPTION		(LBL_DESCRIPTION+1)
#define CBO_DESCRIPTION		(GRD_DESCRIPTION+1)
#define LBL_SAVE			(CBO_DESCRIPTION+1)
#define LBL_CANCEL			(LBL_SAVE+1)
#define LBL_EXIT			(LBL_CANCEL+1)
#define CBOGRDTYPEMATCH		(LBL_EXIT+1)
#define CBOGRDTEAMA			(CBOGRDTYPEMATCH+1)
#define CBOGRDTEAMZ			(CBOGRDTEAMA+1)
#define CBOGRDTEAMDBLA		(CBOGRDTEAMZ+1)
#define CBOGRDTEAMDBLZ		(CBOGRDTEAMDBLA+1)
#define LBLTEAMCNFGEDIT		(CBOGRDTEAMDBLZ+1)
#define LBLTEAMCNFGDELETE	(LBLTEAMCNFGEDIT+1)
#define LBLTEAMCNFGCHANGE	(LBLTEAMCNFGDELETE+1)
#define LSTTEAMCNFG			2040



int orderId(const GVectorElement** a, const GVectorElement** b)
{
	CHTeamMatchsCnfg *pA=(CHTeamMatchsCnfg *)(*a)->getElement();
	CHTeamMatchsCnfg *pB=(CHTeamMatchsCnfg *)(*b)->getElement();

	return pA->getId()-pB->getId();
}
/////////////////////////////////////////////////////////////////////////////
// CHTeamCompCnfg dialog

CHTeamCompCnfg::CHTeamCompCnfg(CHTeamMatchsCnfg *pTMCnfg,CWnd* pParent /*=NULL*/,short id/*=0*/)
:CDialog(CHTeamCompCnfg::IDD, pParent)
,pTeamMatchsCnfg(pTMCnfg)
,finalStr(_T("|"))
,NoneTxt("None")
,IndvTxt("Individual")
,DbleTxt("Doubles")
,matchSel(0)
,pTMCnfgEdit(0)
,show(true)
,idTeamCnfg(id)
{
	//{{AFX_DATA_INIT(CHTeamCompCnfg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CHTeamCompCnfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHTeamCompCnfg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHTeamCompCnfg, CDialog)
	//{{AFX_MSG_MAP(CHTeamCompCnfg)
	ON_MESSAGE(UM_EDITCHANGE,OnEditChange)
	ON_MESSAGE(UM_CLICK, OnClick)
	ON_MESSAGE(UM_DBLCLICK, OnDblClick)
	ON_MESSAGE(UM_PAINTGRID, OnPaintGrid)
	ON_MESSAGE(UM_KEYDOWN, OnKeyDown)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHTeamCompCnfg message handlers

BOOL CHTeamCompCnfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	w=new CGraphicWnd(this);
	INITW(w);
	// Fonts
	w->addFont(FONT1, 6,16,0,0,0,0,_T("Tahoma"));
	w->addFont(FNTB, 7,15,1,0,0,0,_T("Tahoma"));
	w->addFont(FONT2,7,15,0,0,1,0,_T("Tahoma"));
	w->addFont(FONT3, 6,16,0,0,0,0,_T("Tahoma"));
	
	// Colores
	w->addColorSet       (IDCOLBLUE  ,RGB( 50, 50,200),COLOR_DEFAULT_OFF,COLOR_DEFAULT_HITX,COLOR_DEFAULT_HIGH,COLOR_DEFAULT_L3D,COLOR_DEFAULT_N3D,COLOR_DEFAULT_D3D);
	w->addColorSet       (IDCOLRED   ,RGB(250, 50, 50),COLOR_DEFAULT_OFF,COLOR_DEFAULT_HITX,COLOR_DEFAULT_HIGH,COLOR_DEFAULT_L3D,COLOR_DEFAULT_N3D,COLOR_DEFAULT_D3D);

	// Colores
	w->addColorSet		 (IDCOL,0,0x808080,COLOR_DEFAULT_HITX,COLOR_DEFAULT_HIGH,0x608080,COLOR_DEFAULT_N3D,0x608080);
	w->addColorSet       (2,RGB( 50,50,200) ,COLOR_DEFAULT_OFF,COLOR_DEFAULT_HITX,COLOR_DEFAULT_HIGH,COLOR_DEFAULT_L3D,COLOR_DEFAULT_N3D,COLOR_DEFAULT_D3D);
	w->addColorSet       (3,RGB(250,50, 50) ,COLOR_DEFAULT_OFF,COLOR_DEFAULT_HITX,COLOR_DEFAULT_HIGH,COLOR_DEFAULT_L3D,COLOR_DEFAULT_N3D,COLOR_DEFAULT_D3D);
	w->addBackgroundColor (2,RGB(58,110,165 )); // Azul para cajas
	w->addBackgroundColor (3,RGB(250,250,230)); // Amarillo para edits		
	w->addBackgroundColor (4,RGB(250,250,255)); // labels info
	w->addBackgroundColor (5,RGB(250,125,125)); // Rojo
	w->addBackgroundColor (6,RGB(125,255,125)); // Verde	
	w->addBackgroundColor (EDTBCKG   ,RGB(255,255,255));

	
	w->addBackgroundColor(IDBDLG ,RGB(240,240,250));
	//w->setBackground     (IDBDLG);

	w->createGrid(LSTTEAMCNFG,CRect(6,10,316,308),BORDER_DOWN,20,IDBCK_GRID,IDCOL,FONT1);
	w->addGridColumn(LSTTEAMCNFG,"Type",JUST_CENTER,310);
	fillGrdTeamCnfg();
	w->createLabelEx(LBLTEAMCNFGEDIT  ,CRect(6,315,131,330)  ,"New Team Confg."  ,BORDER_NONE,JUST_LEFT,IDBCK,IDCOLBLUE,FONT2,IDBCK,IDCOLRED);
	w->createLabelEx(LBLTEAMCNFGDELETE,CRect(136,315,276,330),"Delete Team Confg.",BORDER_NONE,JUST_LEFT,IDBCK,IDCOLBLUE,FONT2,IDBCK,IDCOLRED);
	w->createLabelEx(LBLTEAMCNFGCHANGE,CRect(281,315,421,330),"Change Team Confg.",BORDER_NONE,JUST_LEFT,IDBCK,IDCOLBLUE,FONT2,IDBCK,IDCOLRED);

	CString matches,comp;
	matches.Format(_T("%d"),pTeamMatchsCnfg->getMatches());
	comp.Format(_T("%d"),pTeamMatchsCnfg->getCompetitors());
	w->createLabel(LBL_MATCHS,CRect(320,13,419,27), "Match's number: ",BORDER_NONE,JUST_LEFT,IDBCK,0,FONT1);
	w->createEdit(EDT_MATCHS,CRect(424,12,454,27),matches,BORDER_SINGLE,JUST_CENTER,3,IDCOL,FONT1);
	w->createLabel(LBL_COMP,CRect(559,13,694,27),"Competitor's number: ",BORDER_NONE,JUST_LEFT,IDBCK,0,FONT1);
	w->createEdit(EDT_COMP,CRect(699,12,729,27),comp,BORDER_SINGLE,JUST_CENTER,3,IDCOL,FONT1);
	w->createLabel(LBL_MATCH_CNFG,CRect(320,35,614,55),"Match Configuration",BORDER_NONE,JUST_LEFT,IDBCK,IDCOLRED,FNTB);
	w->createLabel (LBL_LANE, CRect(320,56,614,59),"",BORDER_NONE,JUST_LEFT,2);
	w->createGrid(GRD_MATCH_CNFG,CRect(320,60,614,200),BORDER_DOWN,22,IDBCK_GRID,IDCOL,FONT2);
	w->addGridColumn(GRD_MATCH_CNFG,"Match Type",JUST_CENTER,112);
	w->addGridColumn(GRD_MATCH_CNFG,"1st Comp.",JUST_CENTER,90);
	w->addGridColumn(GRD_MATCH_CNFG,"2nd Comp.",JUST_CENTER,90);
	w->createLabel(LBL_DESCRIPTION,CRect(320,208,394,223),"Description: ",BORDER_NONE,JUST_LEFT,IDBCK,0,FONT1);
	w->createGrid(GRD_DESCRIPTION,CRect(320,225,614,290),BORDER_DOWN,22,IDBCK_GRID,IDCOL,FONT1);
	w->addGridColumn(GRD_DESCRIPTION,"Lang.",JUST_CENTER,44);
	w->addGridColumn(GRD_DESCRIPTION,"Description",JUST_CENTER,250);
	fillGridDescriptions();

	w->createLabelEx(LBL_SAVE,CRect(640,300,705,315),"SAVE",BORDER_NONE,JUST_CENTER,IDBCK,IDCOLBLUE,FONT2,IDBCK,IDCOLRED);
	w->createLabelEx(LBL_CANCEL,CRect(640,319,705,334),"CANCEL",BORDER_NONE,JUST_CENTER,IDBCK,IDCOLBLUE,FONT2,IDBCK,IDCOLRED);
	w->createLabelEx(LBL_EXIT,CRect(640,338,705,353),"EXIT",BORDER_NONE,JUST_CENTER,IDBCK,IDCOLBLUE,FONT2,IDBCK,IDCOLRED);

	w->createGridCombo(CBOGRDTYPEMATCH,112,BORDER_DOWN,22,EDTBCKG,IDCOL,FONT3);
	w->addItem(CBOGRDTYPEMATCH,0,NoneTxt,0,0);
	w->addItem(CBOGRDTYPEMATCH,1,IndvTxt,0,1);
	w->addItem(CBOGRDTYPEMATCH,2,DbleTxt,0,2);

	w->createGridCombo(CBOGRDTEAMA,90,BORDER_DOWN,22,IDBCK_GRID,IDCOL,FONT3);
	w->createGridCombo(CBOGRDTEAMZ,90,BORDER_DOWN,22,IDBCK_GRID,IDCOL,FONT3);
	w->addItem(CBOGRDTEAMA,0,NoneTxt,0,0);
	w->addItem(CBOGRDTEAMZ,0,NoneTxt,0,0);

	w->createGridCombo(CBOGRDTEAMDBLA,90,BORDER_DOWN,22,IDBCK_GRID,IDCOL,FONT3);
	w->createGridCombo(CBOGRDTEAMDBLZ,90,BORDER_DOWN,22,IDBCK_GRID,IDCOL,FONT3);
	w->addItem(CBOGRDTEAMDBLA,0,NoneTxt,0,0);
	w->addItem(CBOGRDTEAMDBLZ,0,NoneTxt,0,0);

	enableRightPart(false);

	if(idTeamCnfg)
	{
		CHTeamMatchsCnfg *pTMCnfg=(CHTeamMatchsCnfg*)CHMemoryDataBase::findTeamMatchsCnfg(idTeamCnfg);
		if(pTMCnfg)
		{
			w->selectItem(LSTTEAMCNFG,LPARAM(pTMCnfg));
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CHTeamCompCnfg::OnEditChange(WPARAM wParam,LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	short count=0;
	if (wParam==EDT_MATCHS)
	{
		if (show)
		{
			for (short i=0; i<pTeamMatchsCnfg->getMatches();i++)
				w->redrawLine(GRD_MATCH_CNFG,i);
			return 0;
		}
		count=short(atoi(w->getTxt(EDT_MATCHS)));
		if (count!=pTeamMatchsCnfg->getMatches())
			pTeamMatchsCnfg->setMatches(count);
		if (count!=0)
		{
			show=false;
			fillGridMatchs();
		}
		else
		{
			w->gridDeleteAllItems(GRD_MATCH_CNFG);
			pTeamMatchsCnfg->setMatchesType("");
			pTeamMatchsCnfg->setCompMatchesDistribution("");
		}
	}
	if (wParam==EDT_COMP)
	{
		if (show)
		{
			for (short i=0; i<pTeamMatchsCnfg->getMatches();i++)
				w->redrawLine(GRD_MATCH_CNFG,i);
			return 0;
		}
		
		count=short(atoi(w->getTxt(EDT_COMP)));
		if(!count)
			return 0;

		if (count>5 || count<=1)
		{
			::msg("Warning","Only 2-5 competitors.",ICO_W,MSG_OK);
			return 0;
		}
		if (count!=pTeamMatchsCnfg->getCompetitors())
			pTeamMatchsCnfg->setCompetitors(count);
		if (count!=0)
		{
			fillGricComboCompDbl();
			fillGricComboComp();
			RWCString matches=NULLRWSTRING;
			for (short i=0; i<pTeamMatchsCnfg->getMatches();i++)
				matches+="|    ";
			pTeamMatchsCnfg->setCompMatchesDistribution(matches);
		}
		else
		{ //para el equipo A y el equipo Z
			w->delAllItems(CBOGRDTEAMA);
			w->delAllItems(CBOGRDTEAMZ);
			w->addItem(CBOGRDTEAMA,0,NoneTxt,0,0);
			w->addItem(CBOGRDTEAMZ,0,NoneTxt,0,0);
			w->selectItemTxt(CBOGRDTEAMA,"None");
			w->selectItemTxt(CBOGRDTEAMZ,"None");
			for (short i=0; i<pTeamMatchsCnfg->getMatches();i++)
				w->redrawLine(GRD_MATCH_CNFG,i);
		}
	}
	return 0;
}

void CHTeamCompCnfg::fillGricComboComp()
{
	w->delAllItems(CBOGRDTEAMA);
	w->delAllItems(CBOGRDTEAMZ);
	w->addItem(CBOGRDTEAMA,0,NoneTxt,0,0);
	w->addItem(CBOGRDTEAMZ,0,NoneTxt,0,0);

	char varA='A', varZ='W';
	for (short i=0; i<pTeamMatchsCnfg->getCompetitors();i++)
	{
		CString txtA=varA;
		CString txtZ=varZ;
		w->addItem(CBOGRDTEAMA,i+1,txtA,0,i+1);
		w->addItem(CBOGRDTEAMZ,i+1,txtZ,0,i+1);
		varA++;
		varZ++;
	}

	CString tA="None", tZ="None";
	w->selectItemTxt(CBOGRDTEAMA,tA);
	w->selectItemTxt(CBOGRDTEAMZ,tZ);

	for (i=0; i<pTeamMatchsCnfg->getMatches();i++)
		w->redrawLine(GRD_MATCH_CNFG,i);
}

void CHTeamCompCnfg::fillGricComboCompDbl()
{
	w->delAllItems(CBOGRDTEAMDBLA);
	w->delAllItems(CBOGRDTEAMDBLZ);
	w->addItem(CBOGRDTEAMDBLA,0,NoneTxt,0,0);
	w->addItem(CBOGRDTEAMDBLZ,0,NoneTxt,0,0);

	char varA1='A', varA2='A', varZ1='W', varZ2='W';
	int count=1;
	for (short i=0; i<pTeamMatchsCnfg->getCompetitors();i++)
	{
		for (short j=short(i+1); j<pTeamMatchsCnfg->getCompetitors();j++)
		{
			CString txtA=varA1;
			txtA+=char(varA2+j);
			CString txtZ=varZ1;
			txtZ+=char(varZ2+j);
			w->addItem(CBOGRDTEAMDBLA,count,txtA,0,count);
			w->addItem(CBOGRDTEAMDBLZ,count,txtZ,0,count);
			count++;
		}
		varA1++;
		varZ1++;
	}
}

void CHTeamCompCnfg::fillGridMatchs()
{
	RWCString team=NULLRWSTRING;
	RWCString matches=NULLRWSTRING;

	if (show)
	{
		CString auxm;
		auxm.Format(_T("%d"),pTeamMatchsCnfg->getMatches());
		w->changeTxt(EDT_MATCHS,auxm,false);
	}

	w->gridDeleteAllItems(GRD_MATCH_CNFG);
	for (short i=0; i<pTeamMatchsCnfg->getMatches();i++)
	{
		w->addGridLine(GRD_MATCH_CNFG,i,"");
		if (!show)
		{
			team+="| ";
			matches+="|    ";
		}
	}
	if (!show)
	{
		pTeamMatchsCnfg->setMatchesType(team);
		pTeamMatchsCnfg->setCompMatchesDistribution(matches);
		pTeamMatchsCnfg->setCompetitors(0);
	}
	CString auxc;
	auxc.Format(_T("%d"),pTeamMatchsCnfg->getCompetitors());
	w->changeTxt(EDT_COMP,auxc,false);
}

LRESULT CHTeamCompCnfg::OnClick(WPARAM wParam,LPARAM lParam)
{
	if (wParam==LSTTEAMCNFG)
	{
		pTeamMatchsCnfg=(CHTeamMatchsCnfg *)lParam;
		show=true;
		fillGridMatchs();
		fillGridDescriptions();
		enableRightPart(false);
	}
	if (wParam==LBLTEAMCNFGEDIT)
	{
		w->unselect(LSTTEAMCNFG);

		show=false;
		enableRightPart(true);
		pTMCnfgEdit=new CHTeamMatchsCnfg(*(findTeamMatchsCnfg(short(0))));
		pTMCnfgEdit->setId(getNewIdTeamMatchsCnfg());
		pTeamMatchsCnfg=pTMCnfgEdit;
		fillGridMatchs();
		fillGridDescriptions();
	}
	if (wParam==LBLTEAMCNFGDELETE)
	{
		int val=0;
		if (pTeamMatchsCnfg->getId()==0 || (val=isPosibleDelete(pTeamMatchsCnfg->getId()))!=0)
		{
			CString warning="Warning";
			CString txt="Select other configuration to delete";
			if (val==1)
				txt="There are events with this configuration";
			else if (val==2)
				txt="There are phases with this configuration";
			else if (val==3)
				txt="There are events and phases with this configuration";
			::msg(warning,txt,ICO_W,MSG_OK);
			return 0;
		}
		removeTeamMatchsCnfg(pTeamMatchsCnfg);
		pTeamMatchsCnfg=findTeamMatchsCnfg(short(0));
		fillGridMatchs();
		fillGrdTeamCnfg();
		fillGridDescriptions();
	}
	if (wParam==LBLTEAMCNFGCHANGE && pTeamMatchsCnfg->getId()!=0)
	{
//		w->selectItem(LSTTEAMCNFG,LPARAM(pTeamMatchsCnfg));
		show=false;
		enableRightPart(true);
		w->enable(LBL_EXIT,false);
		pTMCnfgEdit=new CHTeamMatchsCnfg(*(findTeamMatchsCnfg(*pTeamMatchsCnfg)));
		pTeamMatchsCnfg=pTMCnfgEdit;
		fillGrdTeamCnfg();
		fillGridDescriptions();
		fillGricComboCompDbl();
		fillGricComboComp();
	}
	if (wParam==LBL_CANCEL)
	{
		enableRightPart(false);
		w->enable(LBL_EXIT,true);
		delete pTMCnfgEdit;
		pTeamMatchsCnfg=findTeamMatchsCnfg(short(0));
		show=true;
		fillGridMatchs();
		fillGridDescriptions();
	}
	if (wParam==LBL_SAVE)
	{
		inserCHeamMatchsCnfg(pTMCnfgEdit);
		fillGrdTeamCnfg();
		enableRightPart(false);	
		w->enable(LBL_EXIT,true);
		delete pTMCnfgEdit;
		pTeamMatchsCnfg=findTeamMatchsCnfg(short(0));
		show=true;
		fillGridMatchs();
		fillGridDescriptions();
	}
	if (wParam==LBL_EXIT)
	{ //salvamos poniendo como key la mayor que haya
		CHTeamMatchsCnfg *pTMCaux=/*(CHTeamMatchsCnfg *)mem()->*/findTeamMatchsCnfg(*pTeamMatchsCnfg);
//		short a=pTMCaux->getMatch(1);
//		short b=pTMCaux->getMatchComp(2,0,0);
		if (pTMCaux)
			CDialog::OnOK();
		else
			CDialog::OnCancel();
	}
	return 0;
}

void CHTeamCompCnfg::enableRightPart(bool value)
{
	w->enable(GRD_MATCH_CNFG,value);
	w->enable(GRD_DESCRIPTION,value);
	w->enable(EDT_MATCHS,value);
	w->enable(EDT_COMP,value);
	w->enable(LBL_SAVE,value);
	w->enable(LBL_CANCEL,value);

	w->enable(LSTTEAMCNFG,(value==true?false:true));
	w->enable(LBLTEAMCNFGEDIT,(value==true?false:true));
	w->enable(LBLTEAMCNFGDELETE,(value==true?false:true));
	w->enable(LBLTEAMCNFGCHANGE,(value==true?false:true));
}

LRESULT CHTeamCompCnfg::OnDblClick(WPARAM wParam,LPARAM lParam)
{
	WORD y=HIWORD(lParam);
	WORD x=LOWORD(lParam);
	if (wParam==GRD_MATCH_CNFG)
	{
		switch (x) // Columnas del grid
		{ 
			case 0: //type match
			{
				int change=0;
				matchSel=y;
				RWCString text="None";
				if (!pTeamMatchsCnfg->getMatches())
					break;
				LPARAM lPar=w->showGridCombo(GRD_MATCH_CNFG,CBOGRDTYPEMATCH,x,y/*val-'0'*/);
				int val='0'+lPar;
				if (int(pTeamMatchsCnfg->getMatchesType().length())>=((y+1)*2))
				{
					RWCString aux=pTeamMatchsCnfg->getMatchesType();
					if (aux((y*2)+1)!=val)
						change=1;
					aux.replace((y*2)+1,1,char(val));
					
					if (val=='1')
						text="Individual";
					if (val=='2')
						text="Doubles";
					pTeamMatchsCnfg->setMatchesType(aux);
				}
				if (change /*(val=='0' || val=='2')*/ && 
					(int(pTeamMatchsCnfg->getCompMatchesDistribution().length())>=((y+1)*5)))
				{
					RWCString aux=pTeamMatchsCnfg->getCompMatchesDistribution();
					aux.replace((y*5)+1,1,' ');
					aux.replace((y*5)+2,1,' ');
					aux.replace((y*5)+3,1,' ');
					aux.replace((y*5)+4,1,' ');
					pTeamMatchsCnfg->setCompMatchesDistribution(aux);
				}
				w->selectItemTxt(CBOGRDTYPEMATCH, text);
				w->redrawLine(GRD_MATCH_CNFG,y);
			}
			break;
			case 1: //team A
			{
				if (!pTeamMatchsCnfg->getCompetitors())
					break;
				int valMT='0';
				if (int(pTeamMatchsCnfg->getMatchesType().length())>=((y+1)*2))
				{
					valMT=pTeamMatchsCnfg->getMatchesType()((y*2)+1);
					if (/*val=='2' ||*/ valMT==' ' || valMT=='0')
						return 0;
				}
				if (valMT=='1')
				{ //individual
					LPARAM lPar=w->showGridCombo(GRD_MATCH_CNFG,CBOGRDTEAMA,x,y/*val-'A'*/);
					CString txtA=_T('A');
					int val='A'+(lPar-1);
					if (int(pTeamMatchsCnfg->getCompMatchesDistribution().length())>=((y+1)*5))
					{
						RWCString aux=pTeamMatchsCnfg->getCompMatchesDistribution();
						if (lPar!=0)
						{
							aux.replace((y*5)+1,1,char(val));
							txtA=char(val);
						}
						else
						{
							aux.replace((y*5)+1,1,' ');
							txtA="None";
						}
						pTeamMatchsCnfg->setCompMatchesDistribution(aux);
					}
					w->selectItemTxt(CBOGRDTEAMA,txtA);
				}
				else if (valMT=='2')
				{ //dobles
					LPARAM lPar=w->showGridCombo(GRD_MATCH_CNFG,CBOGRDTEAMDBLA,x,y);
					RWCString txtA=geCHxtCmbo(lPar,x);
					if (int(pTeamMatchsCnfg->getCompMatchesDistribution().length())>=((y+1)*5))
					{
						RWCString aux=pTeamMatchsCnfg->getCompMatchesDistribution();
						if (lPar!=0)
						{
							aux.replace((y*5)+1,1,txtA(0));
							aux.replace((y*5)+2,1,txtA(1));
						}
						else
						{
							aux.replace((y*5)+1,1,' ');
							aux.replace((y*5)+2,1,' ');
							txtA="None";
						}
						pTeamMatchsCnfg->setCompMatchesDistribution(aux);
					}
					w->selectItemTxt(CBOGRDTEAMDBLA,txtA);
				}
				w->redrawLine(GRD_MATCH_CNFG,y);
			}
			break;
			case 2: //team B
			{
				if (!pTeamMatchsCnfg->getCompetitors())
					break;
				int valMT='0';
				if (int(pTeamMatchsCnfg->getMatchesType().length())>=((y+1)*2))
				{
					valMT=pTeamMatchsCnfg->getMatchesType()((y*2)+1);
					if (/*val=='2' ||*/ valMT==' ' || valMT=='0')
						return 0;
				}
				if (valMT=='1')
				{ //individual
					LPARAM lPar=w->showGridCombo(GRD_MATCH_CNFG,CBOGRDTEAMZ,x,y);
					CString txtZ=_T('W');
					int val='W'+(lPar-1);
					if (int(pTeamMatchsCnfg->getCompMatchesDistribution().length())>=((y+1)*5))
					{
						RWCString aux=pTeamMatchsCnfg->getCompMatchesDistribution();
						if (lPar!=0)
						{
							aux.replace((y*5)+3,1,char(val));
							txtZ=char(val);
						}
						else
						{
							aux.replace((y*5)+3,1,' ');
							txtZ="None";
						}
						pTeamMatchsCnfg->setCompMatchesDistribution(aux);
					}
					w->selectItemTxt(CBOGRDTEAMZ,txtZ);
				}
				else if (valMT=='2')
				{ //dobles
					LPARAM lPar=w->showGridCombo(GRD_MATCH_CNFG,CBOGRDTEAMDBLZ,x,y);
					RWCString txtZ=geCHxtCmbo(lPar,x);
					if (int(pTeamMatchsCnfg->getCompMatchesDistribution().length())>=((y+1)*5))
					{
						RWCString aux=pTeamMatchsCnfg->getCompMatchesDistribution();
						if (lPar!=0)
						{
							aux.replace((y*5)+3,1,txtZ(0));
							aux.replace((y*5)+4,1,txtZ(1));
						}
						else
						{
							aux.replace((y*5)+3,1,' ');
							aux.replace((y*5)+4,1,' ');
							txtZ="None";
						}
						pTeamMatchsCnfg->setCompMatchesDistribution(aux);
					}
					w->selectItemTxt(CBOGRDTEAMDBLZ,txtZ);
				}
				w->redrawLine(GRD_MATCH_CNFG,y);
			}
			break;
		}
	}
	if (wParam==GRD_DESCRIPTION)
	{
		GNames *names=(GNames *)w->getGridLParam(GRD_DESCRIPTION,y);//lParam;
		switch (x) // Columnas del grid
		{
		case 1: //Long description
			{
				RWWString tmp=names->getLName();
				RWWString txt=w->editGridCell(GRD_DESCRIPTION,x,y,tmp);
				if (txt.length()>35)
					AfxMessageBox(_T("The size of the string is than 35 "));
				else
				{
					names->setLName(txt);
					names->setSName(txt);
					pTeamMatchsCnfg->setDescription(*names);
				}
				w->redrawLine(GRD_DESCRIPTION,y);
			}
			break;
		}
	}
	if (wParam==LSTTEAMCNFG)
	{
		CHTeamMatchsCnfg *pTeamMatchCnfg=(CHTeamMatchsCnfg *)w->getGridLParam(LSTTEAMCNFG,y);
		
		if(!pTeamMatchCnfg)
			return 0;
		switch (x) // Columnas del grid
		{
		case 0: //Long description
			{
				SendMessage(UM_CLICK,LBL_EXIT,0);
			}
			break;
		}
	}
	

	return 0;
}

BOOL CHTeamCompCnfg::OnPaintGrid(UINT idGrid,GridItem *gi)
{
	if (!gi) return false;

	int y=gi->y;
	int x=gi->x;

	/*gi->cdc->FillSolidRect(gi->rc,(gi->sel)?0x808080:RGB(255,255,255));
	gi->cdc->SetTextColor(COLOR_DEFAULT_ON);*/

	switch (idGrid )
	{
	case GRD_MATCH_CNFG:
		{
			switch (x)
			{
			case 0:
				{
				CString text="None";
				int val='0';
				if (int(pTeamMatchsCnfg->getMatchesType().length())>=((y+1)*2))
				{
					val=pTeamMatchsCnfg->getMatchesType()((y*2)+1);
					if (val=='1')
						text="Individual";
					if (val=='2')
						text="Doubles";
				}
				w->paintGridText(gi->rc.Width()/2,0,text,JUST_CENTER);
				return true;
				}
				break;
			case 1:
				{
					CString txtA=_T("A");
					int val=' ';
					if (int(pTeamMatchsCnfg->getCompMatchesDistribution().length())>=((y+1)*5))
					{
						if (pTeamMatchsCnfg->getMatchesType()((y*2)+1)=='1')
						{ //indivudial
							val=pTeamMatchsCnfg->getCompMatchesDistribution()((y*5)+1);
							if (val>='A' && val<='Z')
								txtA=char(val);
						}
						else if (pTeamMatchsCnfg->getMatchesType()((y*2)+1)=='2')
						{ //doubles
							RWCString aux=pTeamMatchsCnfg->getCompMatchesDistribution()((y*5)+1,2);
							val='2';
							if (aux!="  ")
								txtA=aux;
							else
								txtA="None";
						}
					}
					if (!pTeamMatchsCnfg->getCompetitors() || val==' ' ||
						(int(pTeamMatchsCnfg->getMatchesType().length())>=((y+1)*2) &&
						 (pTeamMatchsCnfg->getMatchesType()((y*2)+1)=='0')))
						txtA="None";
					w->paintGridText(gi->rc.Width()/2,0,txtA,JUST_CENTER);
						return true;
				}
				break;
			case 2:
				{
					CString txtZ=_T("Z");
					int val=' ';
					if (int(pTeamMatchsCnfg->getCompMatchesDistribution().length())>=((y+1)*5))
					{
						if (pTeamMatchsCnfg->getMatchesType()((y*2)+1)=='1')
						{ //indivudial
							val=pTeamMatchsCnfg->getCompMatchesDistribution()((y*5)+3);
							if (val>='A' && val<='Z')
								txtZ=char(val);
						}
						else if (pTeamMatchsCnfg->getMatchesType()((y*2)+1)=='2')
						{ //doubles
							RWCString aux=pTeamMatchsCnfg->getCompMatchesDistribution()((y*5)+3,2);
							txtZ=aux;
							val='2';
							if (aux!="  ")
								txtZ=aux;
							else
								txtZ="None";
						}
					}
					if (!pTeamMatchsCnfg->getCompetitors() || val==' ' ||
						(int(pTeamMatchsCnfg->getMatchesType().length())>=((y+1)*2) &&
						(pTeamMatchsCnfg->getMatchesType()((y*2)+1)=='0')))
						txtZ="None";
					w->paintGridText(gi->rc.Width()/2,0,txtZ,JUST_CENTER);
						return true;
				}
				break;
			}
		}
		break;
	case GRD_DESCRIPTION:
		{
			GNames *name=(GNames *)gi->lParam;
			switch (x)
			{
			case 0: //languge
				{
					w->paintGridText(gi->rc.Width()/2,0,name->getCode(),JUST_CENTER);
					return true;
				}
				break;
			case 1: //description
				{
					w->paintGridText(gi->rc.Width()/2,0,name->getLName(),JUST_CENTER);
					return true;
				}
				break;
			}
		}
		break;
	case LSTTEAMCNFG:
		{
		paintLisCHeamMatchsCnfg(gi);
		return TRUE;
		}
		break;
	}
	return false;
}

RWCString CHTeamCompCnfg::geCHxtCmbo(LPARAM lParam, WORD cmbo)
{ //busco la pareja de dobles
	RWCString aux=NULLRWSTRING;
	char varA1='A', varA2='A', varZ1='W', varZ2='W';
	int count=1;
	for (short i=0; i<pTeamMatchsCnfg->getCompetitors();i++)
	{
		for (short j=short(i+1); j<pTeamMatchsCnfg->getCompetitors();j++)
		{
			RWCString txtA=varA1;
			txtA+=char(varA2+j);
			RWCString txtZ=varZ1;
			txtZ+=char(varZ2+j);
			if (count==lParam && cmbo==1)
				return txtA;
			if (count==lParam && cmbo==2)
				return txtZ;
			count++;
		}
		varA1++;
		varZ1++;
	}
	return aux;
}

void CHTeamCompCnfg::fillGridDescriptions()
{
	RWSet sVector=pTeamMatchsCnfg->getNames();
	RWSetIterator it(sVector);
	GNames *name=0;
	w->gridDeleteAllItems(GRD_DESCRIPTION);
	while( (name=(GNames *)it()) != 0)
	{
		w->addGridLine(GRD_DESCRIPTION,LPARAM(name),"");
	}
}

void CHTeamCompCnfg::fillGrdTeamCnfg()
{
	w->gridDeleteAllItems(LSTTEAMCNFG);
	CHTeamMatchsCnfg *pTMCnfg=0;
	GSortedVector vVector(CHMemoryDataBase::getColTeamMatchsCnfg(),orderId);
	for (size_t i=0; i<vVector.entries(); i++)
	{
		pTMCnfg=(CHTeamMatchsCnfg *)vVector[i]->getElement();
		if (pTMCnfg->getId()==0)
			continue;
		w->addGridLine(LSTTEAMCNFG,LPARAM(pTMCnfg),"");
	}
}

void CHTeamCompCnfg::paintLisCHeamMatchsCnfg(GridItem *gi)
{
	if (!gi) return;
		
	CHTeamMatchsCnfg *pTMCnfg=(CHTeamMatchsCnfg *) gi->lParam;

	/*gi->cdc->FillSolidRect(gi->rc,(gi->sel)?0x808080:RGB(255,255,255));
	gi->cdc->SetTextColor(COLOR_DEFAULT_ON);*/

	CString txt=_T("");

	switch (gi->x) // Columnas del grid
	{ 
		case 0: // Type
			txt=pTMCnfg->getLDescription();
			w->paintGridText(gi->rc.Width()/2,0,txt,JUST_CENTER);
			break;
	}
}

short CHTeamCompCnfg::getNewIdTeamMatchsCnfg()
{
	CHTeamMatchsCnfg *pTMCnfgAux=0;
	short id=0;
	RWSetIterator it(CHMemoryDataBase::getColTeamMatchsCnfg());
	while( (pTMCnfgAux=(CHTeamMatchsCnfg*)it()) != 0)
	{
		if (pTMCnfgAux->getId()>=id)
			id=pTMCnfgAux->getId();
	}
	id++;
	return id;
}

void CHTeamCompCnfg::inserCHeamMatchsCnfg(CHTeamMatchsCnfg *pInsTMCnfg)
{
	CHTeamMatchsCnfg *pInsTeamMatchsCnfg=((CHMemoryDataBase*)mem())->setTeamMatchsCnfg(*pInsTMCnfg);
	APP::out(TRN_CH_INSERT_TEAMMATCHSCNFG);
	APP::out(*pInsTeamMatchsCnfg,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
	APP::out();
}

void CHTeamCompCnfg::removeTeamMatchsCnfg(CHTeamMatchsCnfg *pDelTMCnfg)
{
	CHTeamMatchsCnfg *pDelTeamMatchsCnfg=((CHMemoryDataBase*)mem())->removeTeamMatchsCnfg(*pDelTMCnfg);
	APP::out(TRN_CH_REMOVE_TEAMMATCHSCNFG);
	APP::out(*pDelTeamMatchsCnfg,OP_DELETE,TO_VENUE|TO_DATABASE);
	APP::out();
}

int CHTeamCompCnfg::isPosibleDelete(short id)
{
	GSortedVector vEv(CHMemoryDataBase::getColEvents(),orderEvents);
	GSortedVector vPh(CHMemoryDataBase::getColPhases(),orderPhases);

	int total=0;
	int ev=1;
	int ph=2;
	for (size_t i=0; i<vEv.entries(); i++)
	{
		CHEvent *pEv=(CHEvent *)vEv[i]->getElement();
		if (pEv->isEnable() && id==pEv->getIdTeamMatchsCnfg())
		{
			if (!total || total==ph)
				total+=ev;
		}
	}
	for (i=0; i<vPh.entries(); i++)
	{
		CHPhase *pPh=(CHPhase *)vPh[i]->getElement();
		if (id==pPh->getIdTeamMatchsCnfg())
		{
			if (!total || total==ev)
				total+=ph;
		}
	}

	return total;
}

CHTeamMatchsCnfg *CHTeamCompCnfg::findTeamMatchsCnfg(short id)
{
	CHTeamMatchsCnfg aTeamMatCnfg;
	aTeamMatCnfg.setId(id);
	return (CHTeamMatchsCnfg *)(mem()->getColTeamMatchsCnfg().find(&aTeamMatCnfg));
}

CHTeamMatchsCnfg *CHTeamCompCnfg::findTeamMatchsCnfg(CHTeamMatchsCnfg aTeamMatCnfg)
{
	return (CHTeamMatchsCnfg *)(mem()->getColTeamMatchsCnfg().find(&aTeamMatCnfg));
}

void CHTeamCompCnfg::OnKeyDown (WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch(wParam)
	{
		case 27:
			OnCancel();
			break;
		
	}
}