/*************************************************************************************
*			© Copyright MSL Software, S.L., 2001
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHPhasesDlg.cpp
*   Description	: CH Phases Dialog
*
*	Author		: Chess Team
*	Date created: 15-12-2005
* 	Project		: CH Manager
* 	Modification  history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdafx.h"
#include "CHmanager.h"
#include "CHPhasesDlg.h"
#include <Sports\CH\Data\CHMsgDefines.h>
#include <Sports\CH\Data\CHPhaseBase.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int	LSTPHASES					= 2500;
const int	CHLLANG						= 2501;
const int	CHL_LINE2					= 2502;
const int	GRIDLANG					= 2503;
const int   BCK_BLUE					= 2504;
const int   BUCH_OK						= 2505;
const int   BUCH_CANCEL					= 2506;
const int   IDBBKBROWN					= 2507;
const int   FONTDLG						= 2508;
const int	BMP_BACK					= 2509;
const int	BMP_VALIDATE				= 2510;
const int	CHLEX_NORMAL_DESC			= 2511;
const int	FR_OK_CANCEL				= 2512;
const int	BLUE						= 2513;
const int	RED							= 2514;
const int	FONTMIN_A 					= 2515;
const int	LSTCBO_TYPE_PHASE			= 2518;
const int	CHLEX_ALL_ONEPHASE			= 2520;
const int	FR_CHL_EX					= 2521;
const int	CHLEX_PHASE_BASE			= 2522;
const int	LSTCBO_STATUS				= 2523;
const int	FONTMIN						= 2524;
const int	CHL_CARTEL					= 2529;
const int	FONTMAX						= 2530;
const int	BMP_CHECK_PH				= 2531;
const int	BMP_UNCHECK_PH				= 2532;

static 
int ECOrderPhaseCode(const void * lParam1, const void * lParam2, LPARAM lSortParam)
{
	CHPhaseBase* pPhaseBase1 = (CHPhaseBase*) lParam1;
	CHPhaseBase* pPhaseBase2 = (CHPhaseBase*) lParam2;

	return strcmp(pPhaseBase1->getCode(),pPhaseBase2->getCode());
	
	UNREFERENCED_PARAMETER(lSortParam);
}
static 
int ECOrderEventPhaseOrder(const void * lParam1, const void * lParam2, LPARAM lSortParam)
{
	CHPhase* pPhase1 = (CHPhase*) lParam1;
	CHPhase* pPhase2 = (CHPhase*) lParam2;

	CHEvent *pEvent1=(CHEvent*)pPhase1->getEvent();
	CHEvent *pEvent2=(CHEvent*)pPhase2->getEvent();

	int order = 0;
	order = strcmp(pEvent1->getKey(),pEvent2->getKey());
	if(order)
		return order;

	order = pPhase1->getOrder() - pPhase2->getOrder();
	if(order)
		return order;

	return strcmp(pPhase1->getKey(),pPhase2->getKey());
	
	UNREFERENCED_PARAMETER(lSortParam);
}
/////////////////////////////////////////////////////////////////////////////
// CHPhasesDlg dialog


CHPhasesDlg::CHPhasesDlg(CWnd* pParent /*=NULL*/,CHPhase* pPh /*= NULL*/)
	: CDialog(CHPhasesDlg::IDD, pParent)
	,pPhase(pPh)
	,pPhaseBase(0)
	,pLanguage(0)
	,description(true)
	,phaseBase(true)

{
	if(pPhase)
	{
		pPhaseBase=(CHPhaseBase*)CHMemoryDataBase::findPhaseBase(pPhase->getPhase());
		allPhases=false;
	}
	else allPhases=true;
	
	
	//{{AFX_DATA_INIT(CHPhasesDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CHPhasesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHPhasesDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHPhasesDlg, CDialog)
	//{{AFX_MSG_MAP(CHPhasesDlg)
	ON_MESSAGE(UM_DBLCLICK, onDblClick)
	ON_MESSAGE(UM_PAINTGRID, onPaintGrid)	
	ON_MESSAGE(UM_KEYDOWN, OnKeyDown)
	ON_MESSAGE(UM_CLICK, onClick)
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHPhasesDlg message handlers

BOOL CHPhasesDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	if (w)
		delete w;

	return CDialog::DestroyWindow();
}

BOOL CHPhasesDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	w = new CGraphicWnd(this);
	INITW(w);  
	SetWindowPos(0,0,105,1024,650,0);

	w->addBitmapT(BMP_BACK,IDB_BMP_BACK);
	w->addBitmapT(BMP_VALIDATE,IDB_BMP_VALIDATE);
	
	w->addBackgroundColor(BCK_BLUE,RGB( 0,64,128) );	// Morado para líneas
	w->addBackgroundColor(IDBBKBROWN,RGB(239,220,189));

	RWWString font =RWWString("Tahoma",RWWString::ascii);
	w->addFont (FONTDLG,6,14,1,0,0,0,_T("Arial"));
	w->addFont(FONTMIN_A	,5,13,1,0,0,0,font);
	w->addFont(FONTMIN	,5,11,1,0,0,0,font);
	w->addFont (FONTMAX,10,20,1,0,0,0,_T("Arial"));
	
	w->addColorSet       (BLUE,RGB( 50, 50,200),COLOR_DEFAULT_OFF,COLOR_DEFAULT_HITX,COLOR_DEFAULT_HIGH,COLOR_DEFAULT_L3D,COLOR_DEFAULT_N3D,COLOR_DEFAULT_D3D);
	w->addColorSet       (RED ,RGB(250, 50, 50),COLOR_DEFAULT_OFF,COLOR_DEFAULT_HITX,COLOR_DEFAULT_HIGH,COLOR_DEFAULT_L3D,COLOR_DEFAULT_N3D,COLOR_DEFAULT_D3D);

	// Languages Grid
	w->createLabel( CHLLANG, CRect(50,510,200,530), "Languages", BORDER_NONE, JUST_LEFT, IDBCK, IDCOL, IDFNT_BOLD );
	w->createLabel( CHL_LINE2, CRect(50,532,200,535), "", BORDER_NONE, JUST_LEFT, BCK_BLUE);
	w->createGrid ( GRIDLANG, CRect(50,540,200,620), BORDER_DOWN, 22, IDBCK_GRID, IDCOL, IDFNT );
	w->addGridColumn( GRIDLANG, "Language",JUST_CENTER ,150);
	pLanguage = (GLanguage *)mem()->getDiscipline().getLanguagesCol()[0];
	fillLanguagesList();
	
	
	w->createLabel( CHL_CARTEL  , CRect(10,10,300,45), "", BORDER_NONE, JUST_LEFT, IDBCK, IDCOL, FONTMAX );
	paintCartel();

	createGrid();
	
	w->createFrame (FR_CHL_EX      ,CRect(245,  515,355,615),BORDER_DOWN,IDCOL);	
	w->createLabelEx(CHLEX_NORMAL_DESC	 ,CRect(250,520,350,540),"Descriptions",BORDER_NONE,JUST_CENTER,IDBCK,BLUE,FONTMIN_A,IDBCK,RED,FONTMIN_A);

	w->createLabelEx(CHLEX_ALL_ONEPHASE	 ,CRect(250,555,350,575),"",BORDER_NONE,JUST_CENTER,IDBCK,BLUE,FONTMIN_A,IDBCK,RED,FONTMIN_A);
	if(allPhases)
		 w->changeTxt(CHLEX_ALL_ONEPHASE,"All Phases");
	else w->changeTxt(CHLEX_ALL_ONEPHASE,"Selected Phase");

	w->createLabelEx(CHLEX_PHASE_BASE	 ,CRect(250,590,350,610),"Phase Base",BORDER_NONE,JUST_CENTER,IDBCK,BLUE,FONTMIN_A,IDBCK,RED,FONTMIN_A);
		
	w->createGridCombo(LSTCBO_TYPE_PHASE,100,BORDER_DOWN,22,IDBCK,IDCOL,IDFNT);
	
			
	w->createGridCombo(LSTCBO_STATUS,101,BORDER_DOWN,22,IDBCK,IDCOL,IDFNT);
	
	fillComboTypePhases();
	
	fillComboStatus();
	// BUCHON OK / CANCEL
	w->createFrame (FR_OK_CANCEL      ,CRect(745,  580,975, 620),BORDER_DOWN,IDCOL);	
	w->createButton (BUCH_OK,CRect( 750, 585,850, 615),"OK",IDBBKBROWN,0,FONTDLG);
	w->changeBmp(BUCH_OK,BMP_VALIDATE);
	w->createButton (BUCH_CANCEL,CRect( 870, 585, 970, 615),"Cancel",IDBBKBROWN,0,FONTDLG);
	w->changeBmp(BUCH_CANCEL,BMP_BACK);

	w->addBitmapT(BMP_CHECK_PH			,IDB_CH_CHECK);
	w->addBitmapT(BMP_UNCHECK_PH		,IDB_CH_UNCHECK);
	

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CHPhasesDlg::fillListPhasesBase()
{
	w->gridDeleteAllItems(LSTPHASES);

	// Si está seleccionada la fase solo muestro dicha fase
	if(pPhaseBase && !allPhases)
	{
		w->addGridLine(LSTPHASES,LPARAM(pPhaseBase),"");
		return;
	}

	CHPhaseBase * pPhaseBaseAux = 0;
	RWSetIterator it(mem()->getColPhaseNames());
	while( (pPhaseBaseAux = (CHPhaseBase *)it()) != 0 )
	{
		w->addGridLine(LSTPHASES,LPARAM(pPhaseBaseAux),"");
	}
	w->gridSort(LSTPHASES,ECOrderPhaseCode);
	
}
void CHPhasesDlg::fillListPhases()
{
	w->gridDeleteAllItems(LSTPHASES);

	// Si está seleccionada la fase solo muestro dicha fase
	if(pPhase && !allPhases)
	{
		w->addGridLine(LSTPHASES,LPARAM(pPhase),"");
		return;
	}

	CHPhase * pPhaseAux = 0;
	RWSetIterator it(mem()->getColPhases());
	while( (pPhaseAux = (CHPhase *)it()) != 0 )
	{
		w->addGridLine(LSTPHASES,LPARAM(pPhaseAux),"");
	}
	
	w->gridSort(LSTPHASES,ECOrderEventPhaseOrder);
}

void CHPhasesDlg::fillLanguagesList()
{
	w->gridDeleteAllItems(GRIDLANG);

	RWSortedVector &colLanguages = mem()->getDiscipline().getLanguagesCol();

	GLanguage *pLang=0;
	for (size_t i =0; i < colLanguages.entries() ; i++)
	{
		pLang = (GLanguage *)colLanguages[i];
		if (pLang && pLang->getActiveFlag())
			w->addGridLine(GRIDLANG,LPARAM(pLang),pLang->getLName());

		if(pLang==pLanguage)
			w->selectItem(GRIDLANG,LPARAM(pLang));
	}
}

void CHPhasesDlg::fillComboTypePhases()
{
	w->delAllItems(LSTCBO_TYPE_PHASE);

	for (short i=1;i<=CHPhaseBase::eRepechage;i++)
	{
		w->addItem(LSTCBO_TYPE_PHASE,i,getTypePhase(0,i),0,LPARAM(i+1));
	}
}

void CHPhasesDlg::fillComboStatus()
{
	w->delAllItems(LSTCBO_STATUS);

	RWOrderedIterator ite2((RWSortedVector&)mem()->getColStatus());
	GStatus *pStatus=0;
	short i=0;
	while( (pStatus=(GStatus *)ite2()) != 0)
	{
		w->addItem(LSTCBO_STATUS,i,pStatus->getLDescription(),0,pStatus->getStatus());
		i++;
	}
}


LRESULT CHPhasesDlg::onDblClick(WPARAM wParam, LPARAM lParam)
{
	if (wParam==LSTPHASES)
	{
		WORD y=HIWORD(lParam);
		WORD x=LOWORD(lParam);
		
		CHPhaseBase* pPhaseBaseAux = 0;
		CHPhase* pPhaseAux = 0;
		
		if(phaseBase)
			 pPhaseBaseAux=(CHPhaseBase*)w->getGridLParam(LSTPHASES,y);
		else pPhaseAux=(CHPhase*)w->getGridLParam(LSTPHASES,y);
		
		if (!pPhaseBaseAux && !pPhaseAux)
			return 0;

		switch (x)  // Columns
		{
			case 1: // LDescription
			{
				if(phaseBase)
				{
					if(description)
					{
						RWCString temp="";
						temp = w->editGridCell(LSTPHASES,x,y,pPhaseBaseAux->getLDescription(pLanguage->getCode()).toAscii(),0,0,false,-1,-1,-1,-1,35);

						if (strcmp(pPhaseBaseAux->getLDescription(pLanguage->getCode()).toAscii(),temp))
						{
							GNamesEx names(pLanguage->getCode(), pPhaseBaseAux->getSDescription(pLanguage->getCode()),RWWString(temp,RWWString::multiByte), NULLRWWSTRING, NULLRWWSTRING);
							pPhaseBaseAux->setDescription(names);
							savePhaseBase(pPhaseBaseAux);
							w->redrawLine(LSTPHASES,y,y);
						}
					}
					else
					{
						showComboTypePhase(x,y,pPhaseBaseAux);
						w->redrawLine(LSTPHASES,y,y);
					}
				}

				break;
			}									
		case 2: // SDescription - Order - Order
			{
				if(phaseBase)
				{
					if(description)
					{
						RWCString temp="";
						temp = w->editGridCell(LSTPHASES,x,y,pPhaseBaseAux->getSDescription(pLanguage->getCode()).toAscii(),0,0,false,-1,-1,-1,-1,20);

						if (strcmp(pPhaseBaseAux->getSDescription(pLanguage->getCode()).toAscii(),temp))
						{
							GNamesEx names(pLanguage->getCode(), RWWString(temp,RWWString::multiByte),pPhaseBaseAux->getLDescription(pLanguage->getCode()), NULLRWWSTRING, NULLRWWSTRING);
							pPhaseBaseAux->setDescription(names);
							savePhaseBase(pPhaseBaseAux);
							w->redrawLine(LSTPHASES,y,y);
						}
					}
					else
					{
						char tmp[10]={0};
						RWCString sOldOrder = itoa(pPhaseBaseAux->getOrder(),tmp,10);
						RWCString sNewOrder=w->editGridCell(LSTPHASES,x,y,sOldOrder,"##");
						if (sOldOrder!= sNewOrder)
						{
							int sIntNewOrder = atoi(sNewOrder);
							if (sIntNewOrder < 1)
								::msg("Warning!!","The order of phase must be more than 1",0,MSG_OK);
							else
							{
								pPhaseBaseAux->setOrder(short(sIntNewOrder));
								savePhaseBase(pPhaseBaseAux);
							}
						}
						w->redrawLine(LSTPHASES,y,y);
											
					}
				}
				else
				{
					char tmp[10]={0};
					RWCString sOldOrder = itoa(pPhaseAux->getOrder(),tmp,10);
					RWCString sNewOrder=w->editGridCell(LSTPHASES,x,y,sOldOrder,"##");
					if (sOldOrder!= sNewOrder)
					{
						int sIntNewOrder = atoi(sNewOrder);
						if (sIntNewOrder < 1)
							::msg("Warning!!","The order of phase must be more than 1",0,MSG_OK);
						else
						{
							pPhaseAux->setOrder(short(sIntNewOrder));
							savePhase(pPhaseAux);
							
							
						}
					}
					w->redrawLine(LSTPHASES,y,y);
				}

				break;
			}					
		case 3: // Winner Rank - Status 
			{
				if(phaseBase)
				{
					if(!description)
					{
						char tmp[10]={0};
						RWCString sOldWinner = itoa(pPhaseBaseAux->getWinnerRank(),tmp,10);
						RWCString sNewWinner=w->editGridCell(LSTPHASES,x,y,sOldWinner,"###");
						if (sOldWinner!= sNewWinner)
						{
							int sIntNewWinner = atoi(sNewWinner);
							pPhaseBaseAux->setWinnerRank(short(sIntNewWinner));
							savePhaseBase(pPhaseBaseAux);
							
						}
						w->redrawLine(LSTPHASES,y,y);
					}
					
				}
				else
				{
					showComboStatus(x,y,pPhaseAux);
					w->redrawLine(LSTPHASES,y,y);
				}
				break;
			}									
		case 4: // Loser Rank - Type Phase
			{
				if(phaseBase)
				{
					if(!description)
					{
						char tmp[10]={0};
						RWCString sOldLoser = itoa(pPhaseBaseAux->getLoserRank(),tmp,10);
						RWCString sNewLoser =w->editGridCell(LSTPHASES,x,y,sOldLoser,"###");
						if (sOldLoser!= sNewLoser)
						{
							int sIntNewLoser = atoi(sNewLoser);
							pPhaseBaseAux->setLoserRank(short(sIntNewLoser));
							savePhaseBase(pPhaseBaseAux);
							
						}
						w->redrawLine(LSTPHASES,y,y);
					}
				}
				else
				{
					showComboTypePhase(x,y,pPhaseAux);
					w->redrawLine(LSTPHASES,y,y);
				}

				break;
			}
		
		case 5: // Winner Rank 
			{
				if(!phaseBase)
				{
					
					char tmp[10]={0};
					RWCString sOldWinner = itoa(pPhaseAux->getWinnerRank(),tmp,10);
					RWCString sNewWinner=w->editGridCell(LSTPHASES,x,y,sOldWinner,"###");
					if (sOldWinner!= sNewWinner)
					{
						int sIntNewWinner = atoi(sNewWinner);
						pPhaseAux->setWinnerRank(short(sIntNewWinner));
						savePhase(pPhaseAux);
						
					}
					w->redrawLine(LSTPHASES,y,y);
					
				}
								
				break;
			}									
		case 6: // Loser Rank
			{
				if(!phaseBase)
				{
					
					char tmp[10]={0};
					RWCString sOldLoser = itoa(pPhaseAux->getLoserRank(),tmp,10);
					RWCString sNewLoser =w->editGridCell(LSTPHASES,x,y,sOldLoser,"###");
					if (sOldLoser!= sNewLoser)
					{
						int sIntNewLoser = atoi(sNewLoser);
						pPhaseAux->setLoserRank(short(sIntNewLoser));
						savePhase(pPhaseAux);
						
					}
					w->redrawLine(LSTPHASES,y,y);
					
				}
				
				break;
			}
		
		}		
		
	}
	return 0;
}
void CHPhasesDlg::showComboTypePhase(int x,int y,CHPhaseBase *pPhaseBaseAux)
{
	w->selectItem(LSTCBO_TYPE_PHASE,(LPARAM)(pPhaseBaseAux->getTypePhase()+1));
	
	short typePhase=0;
	typePhase=short(w->showGridCombo(LSTPHASES,LSTCBO_TYPE_PHASE,x,y));

	if(typePhase && (typePhase-1)!=pPhaseBaseAux->getTypePhase())

	{
		pPhaseBaseAux->setTypePhase(short(typePhase-1));
		savePhaseBase(pPhaseBaseAux);
				
	}
}

void CHPhasesDlg::showComboTypePhase(int x,int y,CHPhase *pPhaseAux)
{
	w->selectItem(LSTCBO_TYPE_PHASE,(LPARAM)(pPhaseAux->getTypePhase()+1));
	
	short typePhase=0;
	typePhase=short(w->showGridCombo(LSTPHASES,LSTCBO_TYPE_PHASE,x,y));

	if(typePhase && (typePhase-1)!=pPhaseAux->getTypePhase())

	{
		pPhaseAux->setTypePhase(short(typePhase-1));
		savePhase(pPhaseAux);
				
	}
}

void CHPhasesDlg::showComboStatus(int x,int y,CHPhase *pPhaseAux)
{
	w->selectItem(LSTCBO_STATUS,(LPARAM)(pPhaseAux->getStatus()));
	
	unsigned char status=0;
	status=unsigned char(w->showGridCombo(LSTPHASES,LSTCBO_STATUS,x,y));


	if(status && status!=pPhaseAux->getStatus())
	{
		pPhaseAux->setStatus(status);
		savePhase(pPhaseAux);
		
	}
}

LRESULT CHPhasesDlg::onPaintGrid(WPARAM wParam, LPARAM lParam)
{
	if (wParam==LSTPHASES)
	{
		if(phaseBase)
			 paintPhasesBase((GridItem*)lParam);
		else paintPhases((GridItem*)lParam);
		return TRUE;
	}
	if (wParam==GRIDLANG)
	{
		paintListLanguages((GridItem*)lParam);
		return TRUE;
	}
	
	return FALSE;
}

void CHPhasesDlg::paintPhasesBase(GridItem* gi)
{	
	if (!gi)
		return;
	
	CHPhaseBase* pPhaseBaseAux=(CHPhaseBase*) gi->lParam;
	if (!pPhaseBaseAux) return;

	gi->cdc->SetTextColor(RGB(0,0,0));	//Negro

	if (gi->sel)	
		gi->cdc->FillSolidRect(gi->rc,GET_COLOR_DEFAULT_HIGH);
	else
	{
		if(gi->y%2)
			 gi->cdc->FillSolidRect(gi->rc,RGB(255,255,255));
		else gi->cdc->FillSolidRect(gi->rc,RGB(243,243,243));
	}
	
	char tmp[10];
	switch(gi->x)
	{
		
		case 0:	
		{
			// Phase
			w->paintGridText(gi->rc.Width()/2,1,pPhaseBaseAux->getCode(),JUST_CENTER);
			break;
		}
		case 1:
		{
			if(description)
				// Long Description
				w->paintGridText(gi->rc.Width()/2,1,pPhaseBaseAux->getLDescription(pLanguage->getCode()),JUST_CENTER);
			else 
				// Type
				w->paintGridText(gi->rc.Width()/2,1,getTypePhase(pPhaseBaseAux),JUST_CENTER);
			break;		
		}
		case 2:
		{
			if(description)
				// Short Description
				w->paintGridText(gi->rc.Width()/2,1,pPhaseBaseAux->getSDescription(pLanguage->getCode()),JUST_CENTER);
			else 
				// Order
				w->paintGridText(gi->rc.Width()/2,1,itoa(pPhaseBaseAux->getOrder(),tmp,10),JUST_CENTER);
			break;		
		}
		case 3:
		{
			// Winner Rank
			w->paintGridText(gi->rc.Width()/2,0,itoa(pPhaseBaseAux->getWinnerRank(),tmp,10));
			break;		
		}
		case 4:
		{
			// Loser Rank
			w->paintGridText(gi->rc.Width()/2,1,itoa(pPhaseBaseAux->getLoserRank(),tmp,10),JUST_CENTER);
			break;		
		}
		
		
	}
}
void CHPhasesDlg::paintPhases(GridItem* gi)
{	
	if (!gi)
		return;
	
	CHPhase* pPhaseAux=(CHPhase*) gi->lParam;
	if (!pPhaseAux) return;

	gi->cdc->SetTextColor(RGB(0,0,0));	//Negro

	if (gi->sel)	
		gi->cdc->FillSolidRect(gi->rc,GET_COLOR_DEFAULT_HIGH);
	else
	{
		if(gi->y%2)
			 gi->cdc->FillSolidRect(gi->rc,RGB(255,255,255));
		else gi->cdc->FillSolidRect(gi->rc,RGB(243,243,243));
	}
	
	char tmp[10];
	switch(gi->x)
	{
		case 0:	// Event
		{
			RWCString event=NULLRWSTRING;
			event=pPhaseAux->getEventSDescription().toAscii()+" - "+pPhaseAux->getEventCode();
			// Event
			w->paintGridText(5,1,event,JUST_LEFT);
			break;
		}
		case 1:	// Phase
		{
			RWCString phase=NULLRWSTRING;
			phase=pPhaseAux->getSDescription().toAscii()+" - "+pPhaseAux->getPhase();

			// Phase
			w->paintGridText(5,1,phase,JUST_LEFT);
			break;
		}
		case 2:	// Order
		{
			char tmp[10];

			w->paintGridText(gi->rc.Width()/2,1,itoa(pPhaseAux->getOrder(),tmp,10),JUST_CENTER);
			break;
		}
		case 3:	// Status
		{
			GStatus* pStatus = CHMemoryDataBase::findStatus(pPhaseAux->getStatus());
			if (pStatus)
				w->paintGridText(gi->rc.Width()/2,1, pStatus->getLDescription(),JUST_CENTER);	
			break;
		}
		case 4:	// TypePhase
		{
			w->paintGridText(gi->rc.Width()/2,1,getTypePhase(0,pPhaseAux->getTypePhase()),JUST_CENTER);
			break;
		}
		case 5:
		{
			// Winner Rank
			w->paintGridText(gi->rc.Width()/2,0,itoa(pPhaseAux->getWinnerRank(),tmp,10));
			break;		
		}
		case 6:
		{
			// Loser Rank
			w->paintGridText(gi->rc.Width()/2,1,itoa(pPhaseAux->getLoserRank(),tmp,10),JUST_CENTER);
			break;		
		}
								
	}
}

void CHPhasesDlg::paintListLanguages(GridItem *gi)
{
	if (!gi)
		return;
	
	GLanguage *pLanguageAux =(GLanguage *) gi->lParam;
	if (!pLanguageAux) return;

	w->paintGridSolid(gi->sel ?  RGB( 0,64,128)  : RGB(255,255,255));
	if (gi->x == 0)
		w->paintGridText(10,0,CString(pLanguageAux->getSName()),JUST_LEFT);
}
LRESULT CHPhasesDlg::onClick(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
		case GRIDLANG:
		{
			pLanguage = (GLanguage *) lParam;
			if (pLanguage)
				fillListPhasesBase();
			break;
		}
		case BUCH_CANCEL:
		{
			OnCancel();
			break;
		}
		case CHLEX_NORMAL_DESC:
		{
			if(phaseBase)
			{
				description=!description;
				w->changeTxt(CHLEX_NORMAL_DESC,(description? "Descriptions":"Data"));
				createGrid();
				paintCartel();
			}
			break;

		}
		case CHLEX_ALL_ONEPHASE:
		{
			if(pPhaseBase)
			{
				allPhases=!allPhases;
				w->changeTxt(CHLEX_ALL_ONEPHASE,(allPhases? "All Phases":"Selected Phase"));
				if(phaseBase)
					 fillListPhasesBase(); 
				else fillListPhases();
			}
			break;
		}
		case CHLEX_PHASE_BASE:
		{
			phaseBase=!phaseBase;
			w->changeTxt(CHLEX_PHASE_BASE,(phaseBase? "Phase Base":"Competition Phase"));
			createGrid();
			paintCartel();
			break;
		}
	}
	return TRUE;
}
void CHPhasesDlg::OnKeyDown (WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch(wParam)
	{
		case 27:
			OnCancel();
			break;
		
	}
}
void CHPhasesDlg::savePhaseBase(CHPhaseBase *pPhaseBaseAux)
{
	APP::out(TRN_CHANGE_PHASEBASE);
	APP::out(*pPhaseBaseAux,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);		
	APP::out();
}
void CHPhasesDlg::savePhase(CHPhase *pPhaseAux)
{
	APP::out(TRN_CHANGE_PHASE);
	APP::out(*pPhaseAux,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);		
	APP::out();
}
void CHPhasesDlg::createGrid()
{
	w->destroyControl(LSTPHASES);

	w->createGrid   (LSTPHASES, CRect(10,50,995,500),BORDER_SINGLE,22,IDBCK_GRID,IDCOL,IDFNT);
	w->gridLineColor(LSTPHASES,GET_COLOR_DEFAULT_LINE,GET_COLOR_DEFAULT_LINE);
		
	
	if(phaseBase && description)
	{	
		w->addGridColumn(LSTPHASES,"Phase" ,JUST_CENTER, 55);
		w->addGridColumn(LSTPHASES,"LDescription"    ,JUST_CENTER, 155);
		w->addGridColumn(LSTPHASES,"SDescription"    ,JUST_CENTER, 155);
			
	}
	else if(phaseBase)
	{
		w->addGridColumn(LSTPHASES,"Phase" ,JUST_CENTER, 55);
		w->addGridColumn(LSTPHASES,"TypePhase"			,JUST_CENTER, 120);
		w->addGridColumn(LSTPHASES,"Order"				,JUST_CENTER, 80);
		w->addGridColumn(LSTPHASES,"Winner Rank"		,JUST_CENTER, 100);
		w->addGridColumn(LSTPHASES,"Loser Rank"			,JUST_CENTER, 100);
		
	}
	else
	{
		w->addGridColumn(LSTPHASES,"Event"	 ,JUST_CENTER, 120);
		w->addGridColumn(LSTPHASES,"Phase"	 ,JUST_CENTER, 120);
		w->addGridColumn(LSTPHASES,"Order"	 ,JUST_CENTER, 50);
		w->addGridColumn(LSTPHASES,"Status"	 ,JUST_CENTER, 100);
		w->addGridColumn(LSTPHASES,"TypePhase",JUST_CENTER,120);
		w->addGridColumn(LSTPHASES,"Winner Rank"		,JUST_CENTER, 80);
		w->addGridColumn(LSTPHASES,"Loser Rank"			,JUST_CENTER, 80);
		
	}

	selecGrid();
}
RWCString CHPhasesDlg::getTypePhase(CHPhaseBase *pPhaseBaseAux,short typePhase)
{
	short type=0;
	if(pPhaseBaseAux)
		 type=pPhaseBaseAux->getTypePhase();
	else type=typePhase;
	switch(type)
	{
		case CHPhaseBase::eElim:
			return "Eliminatory";
			break;
		case CHPhaseBase::ePool:
			return "Pool";
			break;
		case CHPhaseBase::eSwiss:
			return "Swiss-System";
			break;
		case CHPhaseBase::eRepechage:
			return "Repechage";
			break;
		default:
			return "Unknown";
			break;
	}
	return NULLRWSTRING;
}

void CHPhasesDlg::selecGrid()
{
	if(phaseBase)
	{
		w->show(CHLLANG);
		w->show(CHL_LINE2);
		w->show(GRIDLANG);
		fillListPhasesBase(); 
	}
	else 
	{
		w->hide(CHLLANG);
		w->hide(CHL_LINE2);
		w->hide(GRIDLANG);
		fillListPhases();
	}
}
void CHPhasesDlg::paintCartel()
{
	if(phaseBase)
	{
		if(description)
			 w->changeTxt(CHL_CARTEL,"PHASE BASE - DESCRIPTION");
		else w->changeTxt(CHL_CARTEL,"PHASE BASE - DATA");
	}
	else
		w->changeTxt(CHL_CARTEL,"PHASE COMPETITION");

}
