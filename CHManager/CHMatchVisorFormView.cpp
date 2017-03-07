/*************************************************************************************
*			© Copyright MSL Software, S.L., 2001
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior LBitten permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHMatchVisorFormView.cpp
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
#include "stdafx.h"
#include "CHManager.h"
#include "CHMatchVisorFormView.h"
#include "CHProgression.h"
#include "CHManualEventControl.h"
#include "CHCnfgTeamSchedule.h"
#include "resource.h"
#include "CHDefines.h"

#include <GUI/FLAGS/Flags.h>

#include <GUI/TH/GTHScheduleFormView.h>

#include <Sports/CH/Data/CHClassIds.h>
#include <Sports/CH/Data/CHDiscipline.h>
#include <Sports/CH/Data/CHEvent.h>
#include <Sports/CH/Data/CHMatch.h>
#include <Sports/CH/Data/CHPhase.h>
#include <Sports/CH/Data/CHMember.h>
#include <Sports/CH/Data/CHMatchMember.h>
#include <Sports/CH/Data/CHPoolResult.h>
#include <Sports/CH/Data/CHSplitMatch.h>
#include <Sports/CH/Data/CHInscription.h>
#include <Sports/CH/Data/CHRegister.h>
#include <Sports/CH/Data/CHSession.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define COLORSTATUS_GREY		RGB(150,150,150)	// Gris Oscuro
#define COLORSTATUS_BLACK		RGB(0,0,0)			// Negro
#define COLORSTATUS_BLUE		RGB(0,0,255)		// Azul
#define COLORSTATUS_DARKBLUE	RGB(0,64,128)		// Azul Oscuro
#define COLORSTATUS_GREEN		RGB(0,192,0)		// Verde
#define COLORSTATUS_PINK		RGB(255,128,128)	// Rosa
#define COLORSTATUS_RED			RGB(255,0,0)		// Rojo
#define COLORSTATUS_BROWN		RGB(128,64,0)		// Marron
#define	COLORSTATUS_DEFAULT		RGB(0,0,0)			// Negro

const int COLORSETSTATUS_AVAILABLE=		21931;
const int COLORSETSTATUS_CONFIGURED=	21932;
const int COLORSETSTATUS_SCHEDULLED=	21933;
const int COLORSETSTATUS_STARTLIST=		21934;
const int COLORSETSTATUS_RUNNING=		21935;
const int COLORSETSTATUS_UNOFFICIAL=	21936;
const int COLORSETSTATUS_FINISHED=		21937;
const int COLORSETSTATUS_REVISION=		21938;

#define GRM_SES			"Session"
#define GRM_TIME		"Time"
#define GRM_COURT		"Table"
#define GRM_ROUND		"Round"
#define GRM_DES			"Description"
#define GRM_TES			"Home vs Away"
#define GRM_RES			"Result"
#define GRM_STA			"Status"

// Ordenacion del grid pulsando sobre la cabecera.
// Session(Fecha,Hora) - StartDate - Court - Round
static 
int pfnCompareSessionFirst(const void * lParam1, const void * lParam2, LPARAM lSortParam)
{
	CHMatch* pA  = (CHMatch*) lParam1;
	CHMatch* pB  = (CHMatch*) lParam2;

		// Si alguno de ellos no tienen la sesión asignada va para abajo.
	if (!pA->getSession() && pB->getSession())
		return 1;
	if (pA->getSession() && !pB->getSession())
		return -1;
	
	if( !pA->getSessionDate().isValid() && !pB->getSessionDate().isValid())
		return strcmp(pA->getKey(),pB->getKey());
	if( !pA->getSessionDate().isValid() )
		return 1;
	if( !pB->getSessionDate().isValid() )
		return -1;

	int order=strcmp(pA->getSessionDateAsString("%Y%m%d"),pB->getSessionDateAsString("%Y%m%d"));
	if (order) 
		return order;

	// Compare time
	if( !pA->getSessionTime().isValid() && !pB->getSessionTime().isValid() )
		return strcmp(pA->getKey(),pB->getKey());
	if( !pA->getSessionTime().isValid())
		return 1;
	if( !pB->getSessionTime().isValid() )
		return -1;
	
	order=strcmp(pA->getSessionTimeAsString("%H:%M"),pB->getSessionTimeAsString("%H:%M"));
	if (order)
		return order;

	if( !pA->getStartDate().isValid() && !pB->getStartDate().isValid())
		return strcmp(pA->getKey(),pB->getKey());
	if( !pA->getStartDate().isValid() )
		return 1;
	if( !pB->getStartDate().isValid() )
		return -1;
	
	order=strcmp(pA->getStartDateAsString("%Y%m%d"),pB->getStartDateAsString("%Y%m%d"));
	if (order) 
		return order;

	if (!pA->getCourt() && !pB->getCourt())
		return strcmp(pA->getKey(),pB->getKey());
	if (!pA->getCourt() && pB->getCourt())
		return 1;
	if (pA->getCourt() && !pB->getCourt())
		return -1;
	
	order = pA->getCourt()->getCourt() - pB->getCourt()->getCourt();
	if (order)
		return order;

	order = pA->getRound() - pB->getRound();
	if (order)
		return order;

	return strcmp(pA->getKey(),pB->getKey());
		
	UNREFERENCED_PARAMETER(lSortParam);
}

// Ordenacion del grid pulsando sobre la cabecera.
// Court - Round - startDate - StartTime
static 
int pfnCompareCourtFirst(const void * lParam1, const void * lParam2, LPARAM lSortParam)
{
	CHMatch* pA  = (CHMatch*) lParam1;
	CHMatch* pB  = (CHMatch*) lParam2;

	if (!pA->getCourt() && !pB->getCourt())
		return strcmp(pA->getKey(),pB->getKey());
	if (!pA->getCourt() && pB->getCourt())
		return 1;
	if (pA->getCourt() && !pB->getCourt())
		return -1;
	
	int order = pA->getCourt()->getCourt() - pB->getCourt()->getCourt();
	if (order)
		return order;

	order = pA->getRound() - pB->getRound();
	if (order)
		return order;

	if( !pA->getStartDate().isValid() && !pB->getStartDate().isValid())
		return strcmp(pA->getKey(),pB->getKey());
	if( !pA->getStartDate().isValid() )
		return 1;
	if( !pB->getStartDate().isValid() )
		return -1;

	order=strcmp(pA->getStartDateAsString("%Y%m%d"), pB->getStartDateAsString("%Y%m%d"));
	if (order) 
		return order;

	// Compare time
	if( !pA->getStartTime().isValid() && !pB->getStartTime().isValid() )
		return strcmp(pA->getKey(),pB->getKey());
	if( !pA->getStartTime().isValid())
		return 1;
	if( !pB->getStartTime().isValid() )
		return -1;

	order=strcmp(pA->getStartTimeAsString("%H:%M"),pB->getStartTimeAsString("%H:%M"));
	if (order)
		return order;

	return stricmp(pA->getKey(),pB->getKey());

	UNREFERENCED_PARAMETER(lSortParam);
}

// Ordenacion del grid pulsando sobre la cabecera.
// Match Number - 
static int pfnCompareMatchNumberFirst(const void * lParam1, const void * lParam2, LPARAM lSortParam)
{
	CHMatch* pA  = (CHMatch*) lParam1;
	CHMatch* pB  = (CHMatch*) lParam2;

	// Si alguno tiene Bout Number asignado ordena por ese número...
	if (pA->getMatchNumber() && !pB->getMatchNumber())
		return -1;
	if (!pA->getMatchNumber() && pB->getMatchNumber())
		return 1;

	int order=pA->getMatchNumber() - pB->getMatchNumber();
	if (order)
		return order;

	order=strcmp(pA->getEventKey(),pB->getEventKey());
	if(order)
		return order;

	return strcmp(pA->getKey(),pB->getKey());


	UNREFERENCED_PARAMETER(lSortParam);
}

int orderMatVisDayByDate(const GVectorElement** a, const GVectorElement** b)
{
	GDay *p1=(GDay *)(*a)->getElement();
	GDay *p2=(GDay *)(*b)->getElement();

	RWDate date1=p1->getDate();
	RWDate date2=p2->getDate();
	
	if( !date1.isValid() )	return 1;
	if( !date2.isValid() )	return -1;

	RWCString aDate = date1.asString("%Y%m%d");
	RWCString bDate = date2.asString("%Y%m%d");
	int dif = strcmp(aDate,bDate);
	if (dif)
		return dif;

	return strcmp(p1->getKey(),p2->getKey());
}

int orderMVCourts(const GVectorElement** a, const GVectorElement** b)
{
	CHCourt *p1=(CHCourt *)(*a)->getElement();
	CHCourt *p2=(CHCourt *)(*b)->getElement();
	
	return p1->getCourt() - p2->getCourt();
}

int orderSessionsByDateTime(const GVectorElement** a, const GVectorElement** b)
{
	CHSession *p1=(CHSession *)(*a)->getElement();
	CHSession *p2=(CHSession *)(*b)->getElement();

	RWTime time1=p1->getTime();
	RWTime time2=p2->getTime();
	RWDate date1=p1->getDate();
	RWDate date2=p2->getDate();

	int order;
  	if( date1.isValid() && date2.isValid() )	
	{
		order=strcmp(date1.asString("%Y%m%d"),date2.asString("%Y%m%d"));
		if(order)
			return order;

  		if(time1.isValid() && time2.isValid() )	
		{
			order = strcmp(time1.asString("%H%M"),time2.asString("%H%M"));
			if(order)
				return order;
		}
		else if( !time1.isValid() )	return  1;
		else if( !time2.isValid() )	return -1;
	}
	else if( !date1.isValid() )	return  1;
	else if( !date2.isValid() )	return -1;

	return  (int)strcmp( p1->getKey(),p2->getKey() );
}

int orderCollectableTimes(const GVectorElement** a, const GVectorElement** b)
{
	RWCollectableTime *p1=(RWCollectableTime *)(*a)->getElement();
	RWCollectableTime *p2=(RWCollectableTime *)(*b)->getElement();
	
	return strcmp(p1->asString("%H%M"), p2->asString("%H%M"));
}

int orderByMatchNumber(const GVectorElement** a, const GVectorElement** b)
{
	CHMatch * pMatchA=(CHMatch *)(*a)->getElement();
	CHMatch * pMatchB=(CHMatch *)(*b)->getElement();
	
	// Compare date
	if( pMatchA->getStartDateAsString("%Y%m%d")==NULLRWSTRING  &&
		pMatchB->getStartDateAsString("%Y%m%d")==NULLRWSTRING  )
	{
		return strcmp(pMatchA->getKey(),pMatchB->getKey());
	}

	if( pMatchA->getStartDateAsString("%Y%m%d")==NULLRWSTRING )
		return 1;
	if( pMatchB->getStartDateAsString("%Y%m%d")==NULLRWSTRING )
		return -1;

	int order=strcmp(pMatchA->getStartDateAsString("%Y%m%d"),
					 pMatchB->getStartDateAsString("%Y%m%d"));
	if( order ) 
		return order;

	// Tratamos de ordenar por sesion.
	order = 0;
	if (pMatchA->getSession())
	{
		if (pMatchB->getSession())
			order = pMatchA->getSessionSession() - pMatchB->getSessionSession();
		else
			order = -1;
	}
	else 
	{
		if (pMatchB->getSession())
			order = 1;
		else
			order = 0;
	}
	if (order)
		return order;

	// Compare time
	if( pMatchA->getStartTimeAsString()==NULLRWSTRING )
		return 1;
	if( pMatchB->getStartTimeAsString()==NULLRWSTRING )
		return -1;

	if( pMatchA->getStartTimeAsString()==NULLRWSTRING &&
		pMatchB->getStartTimeAsString()==NULLRWSTRING )
	{
		return strcmp(pMatchA->getKey(),pMatchB->getKey());
	}

	order=strcmp(pMatchA->getStartTimeAsString("%H:%M"),
				 pMatchB->getStartTimeAsString("%H:%M") );
	if( order ) 
		return order;

	// Tratamos de ordenar por Match Number.
	order = pMatchA->getMatchNumber() - pMatchB->getMatchNumber();
	if (order)
		return order;

	// Tratamos de ordenar por court.
	if (pMatchA->getCourt() && pMatchB->getCourt())
		return pMatchA->getCourtCode() - pMatchB->getCourtCode();

	// Tratamos de ordenar por key.
	return strcmp(pMatchA->getKey(),pMatchB->getKey());
}
IMPLEMENT_DYNCREATE(CHMatchVisorFormView, CFormView)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHMatchVisorFormView::CHMatchVisorFormView()
:showSpecial(false)
,orderGrid(pfnCompareSessionFirst)
{
}

CHMatchVisorFormView::~CHMatchVisorFormView()
{
	colDays.clearAndDestroy();
	colStartTimes.clearAndDestroy();
}

#ifdef _DEBUG
void CHMatchVisorFormView::AssertValid() const
{
	CFormView::AssertValid();
}

void CHMatchVisorFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

BEGIN_MESSAGE_MAP(CHMatchVisorFormView, CManagerFormView)
	//{{AFX_MSG_MAP(CHMatchVisorFormView)
	ON_MESSAGE(UM_CLICKHEADER,		onClickHeader)
	ON_MESSAGE(UM_CLICK,			onClick)
	ON_MESSAGE(UM_KEYDOWN, OnKeyDown)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CHMatchVisorFormView::init()
{
	HINSTANCE hInstOld = AfxGetResourceHandle();

	w->addFont(CH_FNT		, 5,13,0,0,0,0,_T("Tahoma"));
	w->addFont(CH_BOLD_FNT	, 5,13,1,0,0,0,_T("Tahoma"));
	w->addFont(CH_IDFNT,5,16,0,0,0,0,_T("Tahoma"));
	w->addBitmap(BM_UP,IDB_BMP_UP);
	w->addBitmap(BM_DOWN,IDB_BMP_DOWN);
	w->addBitmapT(BMP_FIND_MATCH_VI	, IDB_BMP_FIND);

	createChksForStatus();
	//Seleccion de filtros
	w->createLabel(CH_DAY  ,CRect(10 ,30 ,120 ,45 ),"Day",BORDER_NONE,JUST_LEFT,IDBCK,0,CH_BOLD_FNT);
	w->createCombo(CB_DAYS ,CRect(10 ,48 ,120 ,293 ) ,BORDER_SINGLE,17,IDBCK,0,CH_FNT);
	//Session
	w->createLabel(CH_SESSION ,CRect(140,30,218,45),"Session",BORDER_NONE,JUST_LEFT,IDBCK,0,CH_BOLD_FNT);	
	w->createCombo(CB_SESSION,CRect(140,48,218,241),BORDER_SINGLE,17,IDBCK,0,CH_FNT);
	
	w->createButton(BT_AVSESSION ,CRect(220,48,236,65),"",IDBCK,0,CH_FNT);
	w->changeBmp(BT_AVSESSION,BM_DOWN,JUST_CENTER);	
	w->createButton(BT_RESESSION ,CRect(236,48,252,65),"",IDBCK,0,CH_FNT);
	w->changeBmp(BT_RESESSION,BM_UP,JUST_CENTER);	
	//Start Time
	w->createLabel(CH_START_TIME ,CRect(272,30,340,45),"Start Time",BORDER_NONE,JUST_LEFT,IDBCK,0,CH_BOLD_FNT);	
	w->createCombo(CB_START_TIME,CRect(272,48,340,241),BORDER_SINGLE,17,IDBCK,0,CH_FNT);

	w->createButton(BT_AVSTART_TIME ,CRect(342,48,359,65),"",IDBCK,0,CH_FNT);
	w->changeBmp(BT_AVSTART_TIME,BM_DOWN,JUST_CENTER);	
	w->createButton(BT_RESTART_TIME ,CRect(359,48,376,65),"",IDBCK,0,CH_FNT);
	w->changeBmp(BT_RESTART_TIME,BM_UP,JUST_CENTER);	
	//Court
	w->createLabel(CH_COURT,CRect(396,30,469,45),"Court",BORDER_NONE,JUST_LEFT,IDBCK,0,CH_BOLD_FNT);	
	w->createCombo(CB_COURT,CRect(396,48,469,241),BORDER_SINGLE,17,IDBCK,0,CH_FNT);

	w->createButton(BT_AVCOURT ,CRect(469,48,486,65),"",IDBCK,0,CH_FNT);
	w->changeBmp(BT_AVCOURT,BM_DOWN,JUST_CENTER);	
	w->createButton(BT_RECOURT ,CRect(486,48,503,65),"",IDBCK,0,CH_FNT);
	w->changeBmp(BT_RECOURT,BM_UP,JUST_CENTER);	
	//Round
	w->createLabel(CH_ROUND,CRect(523,30,591,45),"Round",BORDER_NONE,JUST_LEFT,IDBCK,0,CH_BOLD_FNT);	
	w->createCombo(CB_ROUND,CRect(523,48,591,241),BORDER_SINGLE,17,IDBCK,0,CH_FNT);

	w->createButton(BT_AVROUND ,CRect(591 ,48,608 ,65),"",IDBCK,0,CH_FNT);
	w->changeBmp(BT_AVROUND,BM_DOWN,JUST_CENTER);	
	w->createButton(BT_REROUND ,CRect(608 ,48,625 ,65),"",IDBCK,0,CH_FNT);
	w->changeBmp(BT_REROUND,BM_UP,JUST_CENTER);
	// Grid de Partidos
	w->createGrid(LSTMATCHS,CRect(10,90,1000,640),BORDER_DOWN,35,IDBCK_GRID,IDCOL,IDFNT);
	w->addGridColumn(LSTMATCHS,GRM_SES,JUST_CENTER,85);
	w->addGridColumn(LSTMATCHS,GRM_TIME,JUST_CENTER,60);
	w->addGridColumn(LSTMATCHS,GRM_COURT,JUST_CENTER,45);
	w->addGridColumn(LSTMATCHS,GRM_ROUND,JUST_CENTER,45);
	w->addGridColumn(LSTMATCHS,GRM_DES,JUST_CENTER,240);
	w->addGridColumn(LSTMATCHS,GRM_TES,JUST_CENTER,330);
	w->addGridColumn(LSTMATCHS,GRM_RES,JUST_CENTER,103);
	w->addGridColumn(LSTMATCHS,GRM_STA,JUST_CENTER,75);
	
	
	w->gridLineColor(LSTMATCHS,GET_COLOR_DEFAULT_LINE,GET_COLOR_DEFAULT_LINE);
	//label set
//	w->createLabel(CH_SET1,CRect(576+13,70,576+13+124,90),"Set 1",BORDER_DOWN,JUST_CENTER,IDBCK_GRID,0,CH_BOLD_FNT);
//	w->createLabel(CH_SET2,CRect(576+13+124,70,576+13+124+124,90),"Set 2",BORDER_DOWN,JUST_CENTER,IDBCK_GRID,0,CH_BOLD_FNT);
//	w->createLabel(CH_SET3,CRect(576+13+124+124,70,576+13+124+124+83,90),"Tie Break",BORDER_DOWN,JUST_CENTER,IDBCK_GRID,0,CH_BOLD_FNT);

	w->createLabel(CH_NMATCHES  ,CRect(935 ,70 ,985 ,90 ),"",BORDER_DOWN,JUST_CENTER,IDBCK,0,CH_BOLD_FNT);
	//Entrada de datos manual
	w->createButton(BT_MANDE ,CRect(610,645,750,660),"Manual Event Control",IDBCK_BUT,IDCOL,IDFNT_BOLD);
	w->hide(BT_MANDE);
	//Configuracion y entrada de datos para equipos
	w->createButton(BT_MANDETEAM,CRect(760,645,900,660),"Team Event Control",IDBCK_BUT,IDCOL,IDFNT_BOLD);
	w->hide(BT_MANDETEAM);
	fillComboDays();
	fillGridMatches();
	paintTotalMatches();
	// Boton de Buscar un partido
	w->createButton(BUTTON_FIND_MATCH_DE_VI,CRect(640,30,685,65),"",IDBCK,IDCOL);
	w->changeBmp(BUTTON_FIND_MATCH_DE_VI, BMP_FIND_MATCH_VI, JUST_LEFT);
	w->setToolTip  (BUTTON_FIND_MATCH_DE_VI ,"Find and Select a Match");

	w->createLabel(LBL_FIND_MATCH_VI,CRect(685,30,725,48),"Match",BORDER_3DDOWN,JUST_CENTER,IDBCK,IDCOL,IDFNT);
	
	w->createEdit(ED_FIND_MATCH_VI,  CRect(685,48,725,65),"",BORDER_UP,JUST_CENTER,IDBCK_EDIT,IDCOL,CH_BOLD_FNT);
	w->doEditLimit(ED_FIND_MATCH_VI,5);

	
	AfxSetResourceHandle(hInstOld);
}

BOOL CHMatchVisorFormView::exit() 
{
	return true;
}

BOOL CHMatchVisorFormView::onPaintGrid(UINT idGrid,GridItem *gi)
{
	switch (idGrid)
	{
	case LSTMATCHS:
		paintListMatches(gi);
		break;
	}
	return true;
}

LRESULT CHMatchVisorFormView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if (message==UM_CLICK)
	{
		switch( wParam )
		{
			case CB_DAYS:
				fillComboSession();
				fillComboStartTime();
				fillComboCourt();
				fillComboRound();
				fillGridMatches();
				break; 
			case CB_SESSION:
				fillComboStartTime();
				fillGridMatches();
				break;
			case BT_AVSESSION:
				selectOnCombo(CB_SESSION,1);
				fillComboStartTime();
				fillGridMatches();
				break;
			case BT_RESESSION:
				selectOnCombo(CB_SESSION,-1);
				fillComboStartTime();
				fillGridMatches();
				break;
			case CB_START_TIME:
				fillGridMatches();
				break;
			case BT_AVSTART_TIME:
				selectOnCombo(CB_START_TIME,1);
				fillGridMatches();
				break;
			case BT_RESTART_TIME:
				selectOnCombo(CB_START_TIME,-1);
				fillGridMatches();
				break;
			case CB_COURT:
				fillComboRound();
				fillGridMatches();
				break;
			case BT_AVCOURT:
				selectOnCombo(CB_COURT,1);
				fillComboRound();
				fillGridMatches();
				break;
			case BT_RECOURT:
				selectOnCombo(CB_COURT,-1);
				fillComboRound();
				fillGridMatches();
				break;
			case CB_ROUND:
				fillGridMatches();
				break;
			case BT_AVROUND:
				selectOnCombo(CB_ROUND,1);
				fillGridMatches();
				break;
			case BT_REROUND:
				selectOnCombo(CB_ROUND,-1);
				fillGridMatches();
				break;
			case CH_STATUS + 0:
			case CH_STATUS + 1:
			case CH_STATUS + 2:
			case CH_STATUS + 3:
			case CH_STATUS + 4:
			case CH_STATUS + 5:
			case CH_STATUS + 6:
			case CH_STATUS + 7:
				fillGridMatches();
				break;
			case BT_MANDE:
				{//Entrada de datos manual para individuales
					CHMatch *pM=(CHMatch *)w->getSelectedLParam(LSTMATCHS);
					if (!pM)
						break;
					if (pM->areTeams())
						break;
					if(!registersInMatch(pM))
					{	::msg("Attention","Match without competitor/s available",ICO_X,MSG_OK);
						break;
					}
					if (pM && lockMatch(pM) && pM->getStatus()>=CHMemoryDataBase::eStartList)
					{//bloqueo y lanzo
						CHManualEventControl manualEventControl(this,pM);
						if (manualEventControl.DoModal())
						{
							unLockMatch();
							int y=w->findGridLParam(LSTMATCHS,LPARAM(pM));
							w->redrawLine(LSTMATCHS,y);
						}	
					}
				}
				break;
			case BT_MANDETEAM:
				{//Entrada de datos para equipos
					GSortedVector gsvMatches;
					gsvMatches.sort(orderByMatchNumber);
					for (int i=0; i<w->getGridNItems(LSTMATCHS); i++)
					{
						CHMatch * pMatch = (CHMatch * )w->getGridLParam(LSTMATCHS,i);
						if (pMatch->areTeams())
							gsvMatches.insert(pMatch);
					}
					if (!gsvMatches.entries())
						break;
					CHCnfgTeamSchedule dlgCnfgTeamSchedule(this,gsvMatches,gsvMatches.index((CHMatch * )w->getSelectedLParam(LSTMATCHS)));
					dlgCnfgTeamSchedule.DoModal();
					w->redraw(LSTMATCHS);
				}
				break;
			case LSTMATCHS:
					CHMatch *pM=(CHMatch *)w->getSelectedLParam(LSTMATCHS);
					if (!pM)
						break;
					w->enable(BT_MANDETEAM,false);
					w->enable(BT_MANDE,false);
					if (pM->getStatus()>=CHMemoryDataBase::eStartList)
					{
						if (!pM->areTeams())
							w->enable(BT_MANDE,true);
						else
							w->enable(BT_MANDETEAM,true);
					}
				break;
		}
	}

	long valor1=wParam;
	long valor2=lParam;
	if (message==UM_KEYDOWN)
	{
		if ((valor1==90)  && (valor2==3)) // Ctrl+Shift+"z"
		{
			showSpecial=!showSpecial;
			if (!showSpecial)
			{
				w->hide(BT_MANDE);
				w->hide(BT_MANDETEAM);
			}
			else 
			{
				w->show(BT_MANDE);
				w->show(BT_MANDETEAM);
			}
			w->enable(BT_MANDETEAM,false);
			w->enable(BT_MANDE,false);
		}
	}

	return CManagerFormView::WindowProc(message, wParam, lParam);
}

LRESULT CHMatchVisorFormView::onClickHeader(WPARAM wParam,LPARAM lParam)
{
	switch (wParam)
	{
		case LSTMATCHS:
		{
			switch (lParam)
			{
				case 0: // Session
				case 1: // Start Time
				{
					w->gridSort(wParam,pfnCompareSessionFirst);
					orderGrid=pfnCompareSessionFirst;
					break;
				}
				case 2: // Court
				case 3: // Round
				{
					w->gridSort(wParam,pfnCompareCourtFirst);
					orderGrid=pfnCompareCourtFirst;
					break;
				}
				case 4: //Match Number
					w->gridSort(wParam,pfnCompareMatchNumberFirst);
					orderGrid=pfnCompareMatchNumberFirst;
					break;
			}
			break;
		}
	}

	return 0;
}

void CHMatchVisorFormView::onClick(UINT idCtrl,LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch (idCtrl)
	{	
	case BUTTON_FIND_MATCH_DE_VI: // Busco partido y lo selecciono en grids 
		{
			CHMatch *pMatchFind=findmatchExist();
			if(pMatchFind)
			{
				w->selectItem(LSTMATCHS,LPARAM(pMatchFind),false);
			}
			break;
		}
	}
}

void CHMatchVisorFormView::trnNotification(CPackTransaction *pt)
{
	switch (pt->getTransactionID())
	{
		case TRN_SET_REGISTER:
		case TRN_SET_MEMBER:
		case TRN_REMOVE_MEMBER:
		case TRN_CHANGE_MATCH_MEMBERS:
			w->redraw(LSTMATCHS);
		break;
		//Sessiones
		case TRN_SET_SESSION:
		case TRN_REMOVE_SESSION:
		case TRN_CHANGE_SESSION:
			{
				GDay * pDay=getSelectedDay();
				if(!pDay)
					return;

				CPackTransactionITerator iterPack(*pt);
				CPackObject aPackObject;
				
				while(iterPack(aPackObject))
				{
					if (aPackObject.getId()==__CHSESSION)
					{
						CHSession aSession(aPackObject.getPack());
						if(aSession.getDateAsString("%Y%m%d")==pDay->getDateAsString("%Y%m%d"))
						{
							fillComboSession();
							break;
						}
					}
				}
			}
		break;
		//results y status
		case TRN_CHANGE_SPLITMATCHRES:		//splitMatch MR cambio resultado
		case TRN_CHANGE_MATCHRES:			//cambio de sets ganados...
		case TRN_CHANGE_SPLIT_MATCH:		//cambio status del set(SplitMatch)
		{
			CPackObject aPackObject=(* pt)[0];
			CHMatch *pM=0;
			if (aPackObject.getId() == __CHSPLITMATCHRESULT )
			{
				CHSplitMatchResult aSMR(aPackObject.getPack());
				CHSplitMatchResult *pSMR=(CHSplitMatchResult *)mem()->findSplitMatchResult(aSMR);
				if (pSMR)
					pM=(CHMatch *)pSMR->getMatch();
			}
			if (aPackObject.getId() == __CHSPLITMATCH )
			{
				CHSplitMatch aSM(aPackObject.getPack());
				CHSplitMatch *pSM=(CHSplitMatch *)mem()->findSplitMatch(aSM);
				if (pSM)
					pM=(CHMatch *)pSM->getMatch();
			}
			if (aPackObject.getId() == __CHMATCHRESULT )
			{
				CHMatchResult aMR(aPackObject.getPack());
				CHMatchResult *pMR=(CHMatchResult *)mem()->findMatchResult(aMR);
				if (pMR)
					pM=(CHMatch *)pMR->getMatch();
			}
			if (pM)
			{
				int y=w->findGridLParam(LSTMATCHS,LPARAM(pM));
				w->redrawItem(LSTMATCHS,6,y); //pinto results
			}
		}
		break;
		//Horario y Status del Match
		case TRN_CONFIGURE_MATCH:
		case TRN_DESCONFIGURE_MATCH:
		case TRN_CHANGE_MATCH: //Cambio en el horario y Status del Match
		case TRN_CHANGE_MATCH_STATUS:
		{
			RWBoolean sort=false;

			CPackTransactionITerator iterPack(*pt);
			CPackObject aPackObject;

			CHMatch *pMatch=0;
			while(iterPack(aPackObject))
			{
				if (aPackObject.getId()==__CHMATCH)
				{
					CHMatch aMatch(aPackObject.getPack());

					pMatch=(CHMatch *)mem()->findMatch(aMatch);
					if (pMatch)
					{
						int y=w->findGridLParam(LSTMATCHS,LPARAM(pMatch));

							 if(y>=0 && matchAccepted(&aMatch))
									sort=true;
						else if(y>=0 && !matchAccepted(&aMatch))
									w->gridDeleteItem(LSTMATCHS,y);
						else if(y==-1 && matchAccepted(&aMatch))
						{
									fillGridMatches();
									w->redraw(LSTMATCHS);
									break;
						}
					}
				}
			}

			if(sort)
				orderGridMatches();
			paintTotalMatches();
		}
		break;
	}
	CManagerFormView::trnNotification(pt);
}

void CHMatchVisorFormView::createChksForStatus()
{
	GStatus *pStatus=0;
	int numColorSet=0;
	int numColor=0;
	CString txt("");
	for (size_t i=0; i<8; i++)
	{
		switch (i)
		{
		case 0: 
			pStatus=mem()->findStatus(CHMemoryDataBase::eAvailable);break;
		case 1: 
			pStatus=mem()->findStatus(CHMemoryDataBase::eConfigured);break;
		case 2: 
			pStatus=mem()->findStatus(CHMemoryDataBase::eSchedulled);break;
		case 3: 
			pStatus=mem()->findStatus(CHMemoryDataBase::eStartList);break;
		case 4: 
			pStatus=mem()->findStatus(CHMemoryDataBase::eRunning);break;
		case 5: 
			pStatus=mem()->findStatus(CHMemoryDataBase::eUnofficial);break;
		case 6: 
			pStatus=mem()->findStatus(CHMemoryDataBase::eFinished);break;
		case 7: 
			pStatus=mem()->findStatus(CHMemoryDataBase::eProtested);break;
		}
		if (pStatus)
		{
			numColorSet=findColorSetStatus(pStatus->getStatus());
			numColor=findColorStatus(pStatus->getStatus());
			w->destroyColorSet(numColorSet);
			w->addColorSet(numColorSet,numColor,COLOR_DEFAULT_OFF,COLOR_DEFAULT_HITX,COLOR_DEFAULT_HIGH,COLOR_DEFAULT_L3D,COLOR_DEFAULT_N3D,COLOR_DEFAULT_D3D);
			txt=pStatus->getLDescription();
		}
		w->createCheck(CH_STATUS+i,CRect(50+(i*100), 5,145+(i*100),25),txt,BORDER_NONE,JUST_CENTER,IDBCK,numColorSet,IDFNT);
		w->changeCheck(CH_STATUS+i,(i==4)?true:false);
	}
}

GDay * CHMatchVisorFormView::getSelectedDay() const
{ 
	return (GDay*)w->getSelectedData(CB_DAYS);
}

CHSession * CHMatchVisorFormView::getSelectedSession() const
{ 
	return (CHSession*)w->getSelectedData(CB_SESSION);
}

RWCollectableTime * CHMatchVisorFormView::getSelectedStartTime() const
{ 
	return (RWCollectableTime*)w->getSelectedData(CB_START_TIME);
}

CHCourt * CHMatchVisorFormView::getSelectedCourt() const
{ 
	return (CHCourt*)w->getSelectedData(CB_COURT);
}

short CHMatchVisorFormView::getSelectedRound() const
{ 
	return (short)w->getSelectedData(CB_ROUND);
}

void CHMatchVisorFormView::selectOnCombo(int idCtrl,int steep)
{
	int nLine=w->getSelectedItem(idCtrl);
	if(nLine+steep>=0)
		w->selectItemLine(idCtrl,nLine+steep,false);
}

void CHMatchVisorFormView::fillComboDays()
{
	colDays.clearAndDestroy();

	RWSetIterator iter(mem()->getColMatchs());
	CHMatch * pMatch=0;
	while((pMatch=(CHMatch*)iter())!=0)
	{
		RWDate aDate=pMatch->getStartDate();
		insertDay(aDate);
	}

	w->addItem(CB_DAYS,-1,(" None"),0,LPARAM(0));
	
	GSortedVector vColDays(colDays,orderMatVisDayByDate);
	for(size_t i=0;i<vColDays.entries();i++)
	{
		GDay * pDay = (GDay *)vColDays[i]->getElement();
		if(pDay)
			w->addItem(CB_DAYS,-1,pDay->getDate().asString("%a %d %b %Y"),0,LPARAM(pDay));
	}

	RWDate aCurrentDate;
		
	if(w->selectItemTxt(CB_DAYS,aCurrentDate.asString("%a %d %b %Y"),false))
	{
		fillComboSession();
		fillComboStartTime();
		fillComboCourt();
		fillComboRound();
		fillGridMatches();	
	}
	else
		w->selectItem(CB_DAYS,LPARAM(0),false);	
}

void CHMatchVisorFormView::fillComboSession()
{
	CHSession * pSelSession = getSelectedSession();

	w->delAllItems(CB_SESSION);
	w->redraw(CB_SESSION);

	GDay * pDay				= getSelectedDay	();
	if(!pDay)
		return;

	w->addItem(CB_SESSION,-1," All",0,LPARAM(0));
	
	CHSession * pSession = 0;
	GSortedVector vSessionsAux(mem()->getColSessions(),orderSessionsByDateTime);
	for (size_t i=0; i<vSessionsAux.entries(); i++)
	{
		pSession = (CHSession *)vSessionsAux[i]->getElement();
		if( !pDay ||
			(pSession && pDay &&
			 pSession->getDateAsString("%Y%m%d")==pDay->getDateAsString("%Y%m%d")) )
		{
			char desc[50];
			sprintf(desc," (%d) - %s",pSession->getSession(),pSession->getTimeAsString("%H:%M"));
					
			w->addItem(CB_SESSION,-1,desc,0,LPARAM(pSession));
		}
	}

	if(pSelSession && pSelSession->getDateAsString("%Y%m%d")!=pDay->getDateAsString("%Y%m%d"))
		pSelSession=0;

	w->selectItem(CB_SESSION,LPARAM(pSelSession),false);
}

void CHMatchVisorFormView::fillComboStartTime()
{
	RWCString timeStr;
	RWCollectableTime * pTime = getSelectedStartTime();
	if(pTime )
		timeStr=pTime->asString("%H%M");

	w->delAllItems(CB_START_TIME);
	w->redraw(CB_START_TIME);

	colStartTimes.clearAndDestroy();

	GDay * pDay				= getSelectedDay	();
	if(!pDay)
		return;

	CHSession * pSelSession = getSelectedSession();

	RWCollectableTime * pSelTime=0;
	RWSetIterator iter(CHMemoryDataBase::getColMatchs());
	CHMatch * pMatch=0;
	while((pMatch=(CHMatch*)iter())!=0)
	{
		if(pMatch->getStartDateAsString("%Y%m%d")==pDay->getDateAsString("%Y%m%d"))
		{
			if(!pSelSession || pMatch->getSession()==pSelSession)
			{
				if(!findStartTime(pMatch->getStartTimeAsString("%H%M")))
				{
					RWCollectableTime * pTimeNew=new RWCollectableTime(pMatch->getStartTime());
					colStartTimes.insert(pTimeNew);
					if(pTimeNew->asString("%H%M")==timeStr)
						pSelTime=pTimeNew;
				}
			}
		}
	}

	w->addItem(CB_START_TIME,-1," All",0,LPARAM(0));
	
	GSortedVector vStartTimes(colStartTimes,orderCollectableTimes);
	for(size_t i=0;i<vStartTimes.entries();i++)
	{
		RWCollectableTime * pTime = (RWCollectableTime *)vStartTimes[i]->getElement();
		if(pDay)
			w->addItem(CB_START_TIME,-1,pTime->asString(" %H:%M"),0,LPARAM(pTime));
	}

	w->selectItem(CB_START_TIME,LPARAM(pSelTime),false);
}

RWBoolean CHMatchVisorFormView::findStartTime(RWCString aTime)
{
	RWSetIterator iter(colStartTimes);

	RWCollectableTime * pTime=0;
	while((pTime=(RWCollectableTime*)iter())!=0)
	{
		if(pTime->asString("%H%M")==aTime)
			return true;
	}
	return false;
}

void CHMatchVisorFormView::fillComboCourt()
{
	CHCourt * pSelCourt=getSelectedCourt();

	w->delAllItems(CB_COURT);
	w->redraw(CB_COURT);

	w->addItem(CB_COURT,-1," All",0,LPARAM(0));
	
	if(!getSelectedDay())
		return;
	
	CHCourt * pCourt = 0;
	GSortedVector vCourtAux(mem()->getColCourts(),orderMVCourts);
	for (size_t i=0; i<vCourtAux.entries(); i++)
	{
		pCourt = (CHCourt *)vCourtAux[i]->getElement();
							
		w->addItem(CB_COURT,-1,_T(" ") + pCourt->getLDescription(),0,LPARAM(pCourt));
	}

	w->selectItem(CB_COURT,LPARAM(pSelCourt),false);
}

void CHMatchVisorFormView::fillComboRound()
{
	short aSelRound=getSelectedRound();

	w->delAllItems(CB_ROUND);
	w->redraw(CB_ROUND);
	if(!getSelectedDay())
		return;
	w->addItem(CB_ROUND,-1," All",0,LPARAM(0));

	RWSetIterator iter(CHMemoryDataBase::getColPools());
	CHPool * pPool=0;
	short maxNRounds=0;
	while((pPool=(CHPool*)iter())!=0)
	{
		if (maxNRounds<pPool->getNumRounds())
			maxNRounds=pPool->getNumRounds();
	}

	for (size_t i=1; i<=size_t(maxNRounds) ; i++)
	{
		char desc[30];
		sprintf(desc," Round %d", i);
		w->addItem(CB_ROUND,-1,desc,0,LPARAM(i));
	}

	w->selectItem(CB_ROUND,LPARAM(aSelRound),false);
}

void CHMatchVisorFormView::insertDay(RWDate & aDate)
{
	if(aDate.isValid())
	{
		GDay aDay(aDate);
		if(!colDays.find(&aDay))
		{
			GDay *pNewDay=new GDay(aDate);
			colDays.insert(pNewDay);
		}
	}
}

RWBoolean CHMatchVisorFormView::matchAccepted(CHMatch * pMatch)
{
	if(!pMatch)
		return false;

	unsigned char stat=pMatch->getStatus();
	GDay *pDay=getSelectedDay();
	CHSession *pSession=getSelectedSession();
	RWCollectableTime * pTime=getSelectedStartTime();
	CHCourt *pCourt=(CHCourt *)getSelectedCourt();
	short round=getSelectedRound();

	RWBoolean insert = checkForStatus(stat);
	
	if (pDay && pDay->getDate()!=pMatch->getStartDate())
		insert=false;
	else if (pSession && pSession!=(CHSession *)pMatch->getSession())
		insert=false;
	else if(pTime && pMatch->getStartTimeAsString("%H%M")!=pTime->asString("%H%M"))
		insert=false;
	else if (pCourt && pCourt!=(CHCourt *)pMatch->getCourt())
		insert=false;
	else if (round && round!=pMatch->getRound())
		insert=false;

	if (pMatch->areTeamIndividual())
		insert=false;
	return insert;
}

void CHMatchVisorFormView::fillGridMatches()
{
	CHMatch * pMatchSel=(CHMatch *)w->getSelectedLParam(LSTMATCHS);

	GSortedVector vMatches(mem()->getColMatchs(),NULL);

	w->gridDeleteAllItems(LSTMATCHS);

	CHMatch *pMatch=0;
	for (size_t i=0; i<vMatches.entries(); i++)
	{
		pMatch=(CHMatch *)vMatches[i]->getElement();
		if (!pMatch)
			continue;

		if (matchAccepted(pMatch))
			w->addGridLine  (LSTMATCHS,LPARAM(pMatch),_T(""));
	}

	if(orderGrid)
		w->gridSort(LSTMATCHS,orderGrid);
	
	if(pMatchSel)
		w->selectLParam(LSTMATCHS,LPARAM(pMatchSel),true,true);

	paintTotalMatches();
}

void CHMatchVisorFormView::orderGridMatches()
{
	CHMatch * pMatchSel=(CHMatch *)w->getSelectedLParam(LSTMATCHS);

	w->getWnd(LSTMATCHS)->SetRedraw(FALSE);
	w->gridSort(LSTMATCHS,orderGrid);

	if(pMatchSel)
		w->selectLParam(LSTMATCHS,LPARAM(pMatchSel),true,true);

	w->getWnd(LSTMATCHS)->SetRedraw(TRUE);
	w->redraw(LSTMATCHS);
}

void CHMatchVisorFormView::paintTotalMatches()
{
	w->changeTxt(CH_NMATCHES,TOSTRING(w->getGridNItems(LSTMATCHS),"0"));
}

void CHMatchVisorFormView::paintListMatches(GridItem *gi)
{
	if (!gi) 
		return;
	
	CHMatch *pMatch=(CHMatch *)gi->lParam;
	if (!pMatch) 
		return;

	if (gi->sel)							//  SI ESTA SELECCIONADO
		w->paintGridSolid(RGB(118,237,148));
	else if (gi->y % 2)						// Fila Par
		w->paintGridSolid(0xFFFFFF);
	else									// Fila Impar
		w->paintGridSolid(0xF0C0C0);

	RWCString strIDColumn(w->getGridColumnTxt(LSTMATCHS,gi->x));
	if (strIDColumn!=GRM_RES)
	{
		paintListCourt(gi,strIDColumn,pMatch);
		paintListRound(gi,strIDColumn,pMatch);
		paintListDateAndTime(gi,strIDColumn,pMatch);
		paintListMatchDescription(gi,strIDColumn,pMatch);
		paintListStatus(gi,strIDColumn,pMatch);
		paintListSession(gi,strIDColumn,pMatch);
		paintListMatchResults(gi,strIDColumn,pMatch);
	}
	paintListResult(gi,strIDColumn,pMatch);
}

void CHMatchVisorFormView::paintListSession(GridItem *gi,RWCString strIDColumn,CHMatch *pMatch)
{
	if (strIDColumn == GRM_SES )		// Session
	{
		CHSession *pSession=(CHSession *)pMatch->getSession();

		if (!pSession)
			w->paintGridText(gi->rc.Width()/2,0,"*",w->getCurrentFont(LSTMATCHS),RGB(255,0,0),JUST_RIGHT);
		else
		{
			w->paintGridVal(4,11,pSession->getSession(),JUST_LEFT);
			w->paintGridText(20,2 ,pSession->getDateAsString("%d/%m/%Y"),JUST_LEFT);
			w->paintGridText(35,18,pSession->getTime().asString("%H:%M"),JUST_LEFT);
		}
	}
}

void CHMatchVisorFormView::paintListDateAndTime(GridItem *gi,RWCString strIDColumn,CHMatch *pMatch)
{
	if (strIDColumn == GRM_TIME )		// Date And Time
	{
		w->paintGridText(gi->rc.Width()/2,11,pMatch->getStartTimeAsString("%H:%M"),JUST_CENTER);

		bool error=false;
		if (!pMatch ||
			 pMatch->getStartTime() == INVALID_RWTIME )
			error =true;
		if (!error && 
			 pMatch->getSession())
		{
			CHSession *pSession=(CHSession *)pMatch->getSession();
			if (pSession->getDateAsString() == pMatch->getStartDateAsString())
			{
				int orderInicio=strcmp(pMatch->getStartTime().asString("%H:%M"),
									   pSession->getTime().asString("%H:%M") );

				if (orderInicio < 0)
					error=true;
			}
		}
		if (error)
			w->paintGridText((gi->rc.Width())/2,0,"*",w->getCurrentFont(LSTMATCHS),RGB(255,0,0),JUST_CENTER);
	}
}

void CHMatchVisorFormView::paintListCourt(GridItem *gi,RWCString strIDColumn,CHMatch *pMatch)
{
	if (strIDColumn == GRM_COURT )		// Court
	{
		if (pMatch->getCourt())
			w->paintGridText(gi->rc.Width()/2,11,pMatch->getCourtSDescription(),JUST_CENTER);
		else
			w->paintGridText(gi->rc.Width()/2,0,"*",w->getCurrentFont(LSTMATCHS),RGB(255,0,0),JUST_CENTER);
	}
}

void CHMatchVisorFormView::paintListRound(GridItem *gi,RWCString strIDColumn,CHMatch *pMatch)
{
	if (strIDColumn == GRM_ROUND )		// Round
	{
		if (!pMatch->getRound())
				w->paintGridText((gi->rc.Width())/2,0,"*",w->getCurrentFont(LSTMATCHS),RGB(255,0,0),JUST_CENTER);
		else
		{
			w->paintGridVal(gi->rc.Width()-20,11,pMatch->getRound(),JUST_LEFT);
		}
	}
}

void CHMatchVisorFormView::paintListMatchDescription(GridItem *gi,RWCString strIDColumn,CHMatch *pMatch)
{
	if (strIDColumn == GRM_DES )		// Descripcion
	{
		wchar_t txt[400];
		// Si no es una Pool
		if (!pMatch->getIsPool())
			swprintf(txt,_T("%s-%s %s %d"),pMatch->getEventSDescription()
										,pMatch->getPhaseSDescription()
										,((CHDiscipline &)mem()->getDiscipline()).getSMatchDescription()
										,pMatch->getCode());
		else
			swprintf(txt,_T("%s-%s %s %s %d")	,pMatch->getEventSDescription()
											,pMatch->getPhaseSDescription()
											,pMatch->getPoolDescription(pMatch->getPhase()->getPoolDescription())
											,((CHDiscipline &)mem()->getDiscipline()).getSMatchDescription()
											,pMatch->getCode());

		w->paintGridText(4,2,txt,JUST_LEFT);
		w->paintGridText(4,18,mem()->getRSC(pMatch),JUST_LEFT);
		w->paintGridText(gi->rc.Width()-2,18,"MN: " + TOSTRING(pMatch->getMatchNumber()),JUST_RIGHT);

	}
}

void CHMatchVisorFormView::paintListStatus(GridItem *gi,RWCString strIDColumn,CHMatch *pMatch)
{
	if (strIDColumn == GRM_STA )		// Status
	{
		COLORREF colorTxt=findColorStatus(pMatch->getStatus());
		w->paintGridText(gi->rc.Width()/2,11,pMatch->getStatusLDescription(),IDFNT,colorTxt,JUST_CENTER);
	}
}

void CHMatchVisorFormView::paintListMatchResults(GridItem *gi,RWCString strIDColumn,CHMatch *pMatch)
{
	UNREFERENCED_PARAMETER(gi);

	CHEvent *pEv=(CHEvent *)pMatch->getEvent();
	if (strIDColumn == GRM_TES )		// Match
	{
		CHMatchResult *pMRA=(CHMatchResult *)pMatch->getMatchResultHome();
		CHMatchResult *pMRB=(CHMatchResult *)pMatch->getMatchResultAway();
		if (pMRA && pMRB)
		{
			CBitmap aBitmapA; //HOME
			getFlag(pMRA->getGroup(),ICO,&aBitmapA);	
			w->paintGridUserBmp  (4,2,&aBitmapA,false);
			RWWString txt1=_T(""),txt2=_T("");
			if (pMRA->getRegister())
			{
				txt1=pMRA->getPrnLName();
				txt1+=_T(" (");
				txt1+=RWWString(pMRA->getGroup(),RWWString::ascii)+_T(")");
			}
			else if (pMRA->getBye())
				txt1=pMRA->getIDCompetitor()+_T(" (BYE)");
			else if (pMRA->getPoolPosition())
				txt1=pMRA->getIDCompetitor();
			w->paintGridText(22,1,txt1,JUST_LEFT);
			CBitmap aBMA;//en funcion de la seleccion cargo bitmap
			if (gi->sel)
				aBMA.LoadBitmap(pMRA->getColor()==CHMatchResult::eBlack?IDB_GR_BLACK:IDB_GR_WHITE);
			else if (gi->y % 2)
				aBMA.LoadBitmap(pMRA->getColor()==CHMatchResult::eBlack?IDB_WH_BLACK:IDB_WH_WHITE);
			else
				aBMA.LoadBitmap(pMRA->getColor()==CHMatchResult::eBlack?IDB_BL_BLACK:IDB_BL_WHITE);
			w->paintGridUserBmp  (300,1,&aBMA,false);

			CBitmap aBitmapB; //AWAY
			getFlag(pMRB->getGroup(),ICO,&aBitmapB);	
			w->paintGridUserBmp  (4,20,&aBitmapB,false);
			if (pMRB->getRegister())
			{
				txt2=pMRB->getPrnLName();
				txt2+=_T(" (");
				txt2+=RWWString(pMRB->getGroup(),RWWString::ascii)+_T(")");
			}
			else if (pMRB->getBye())
				txt2=pMRB->getIDCompetitor()+_T(" (BYE)");
			else if (pMRB->getPoolPosition())
				txt2=pMRB->getIDCompetitor();
			w->paintGridText(22,19,txt2,JUST_LEFT);
			CBitmap aBMB;//en funcion de la seleccion cargo bitmap
			if (gi->sel)
				aBMB.LoadBitmap(pMRB->getColor()==CHMatchResult::eBlack?IDB_GR_BLACK:IDB_GR_WHITE);
			else if (gi->y % 2)
				aBMB.LoadBitmap(pMRB->getColor()==CHMatchResult::eBlack?IDB_WH_BLACK:IDB_WH_WHITE);
			else
				aBMB.LoadBitmap(pMRB->getColor()==CHMatchResult::eBlack?IDB_BL_BLACK:IDB_BL_WHITE);
			w->paintGridUserBmp  (300,18,&aBMB,false);

			w->paintGridText(gi->rc.Width()-1,1 ,pMRA->isQualitative()?pMRA->getQualitativeSDescription():_T(""),IDFNT,COLORSTATUS_RED,JUST_RIGHT);
			w->paintGridText(gi->rc.Width()-1,19,pMRB->isQualitative()?pMRB->getQualitativeSDescription():_T(""),IDFNT,COLORSTATUS_RED,JUST_RIGHT);
		}
	}
}

void CHMatchVisorFormView::paintListResult(GridItem *gi,RWCString strIDColumn,CHMatch *pMatch)
{
	UNREFERENCED_PARAMETER(gi);

	if (strIDColumn == GRM_RES )		// Results
	{
		CHMatchResult *pMRA=(CHMatchResult *)pMatch->getMatchResultHome();
		CHMatchResult *pMRB=(CHMatchResult *)pMatch->getMatchResultAway();
		RWCString gameA=NULLRWSTRING;
		size_t pos=RW_NPOS;
		if (pMRA && pMatch->getStatus()>CHMemoryDataBase::eStartList)
		{
			gameA=pMRA->getPointsAsString();
			pos=gameA.index(pMRA->getPoints()>1?".5":"0.5");
			if (pos!=RW_NPOS)
			{
				gameA.remove(pos,pMRA->getPoints()>1?2:3);
				gameA+="½";
			}
		}
		COLORREF colorTxt=findColorStatus(pMatch->getStatus(),true);
		w->paintGridText(gi->rc.Width()/2,1,gameA,CH_IDFNT,colorTxt,JUST_CENTER);
		RWCString gameB=NULLRWSTRING;
		if (pMRB && pMatch->getStatus()>CHMemoryDataBase::eStartList)
		{
			gameB=pMRB->getPointsAsString();
			pos=gameB.index(pMRB->getPoints()>1?".5":"0.5");
			if (pos!=RW_NPOS)
			{
				gameB.remove(pos,pMRB->getPoints()>1?2:3);
				gameB+="½";
			}
		}
		w->paintGridText(gi->rc.Width()/2,19,gameB,CH_IDFNT,colorTxt,JUST_CENTER);
		int totWidth=17;
		if (!pMRA || !pMRB)
			return;
	}
}

int CHMatchVisorFormView::findColorStatusEnd(unsigned char status,RWBoolean useDefault/*=false*/)
{
	int ret=0;

	if(useDefault && status!=CHMemoryDataBase::eAvailable)
		ret=COLORSTATUS_DEFAULT;
	else
	{
		switch (status)
		{
			case CHMemoryDataBase::eAvailable:
				ret=COLORSTATUS_GREY;
				break;
			case CHMemoryDataBase::eConfigured:
				ret=COLORSTATUS_BLACK;
				break;
			case CHMemoryDataBase::eSchedulled:
				ret=COLORSTATUS_BLUE;
				break;
			case CHMemoryDataBase::eStartList:
				ret=COLORSTATUS_DARKBLUE;
				break;
			case CHMemoryDataBase::eRunning:
				ret=COLORSTATUS_RED;
				break;
			case CHMemoryDataBase::eUnofficial:
				ret=COLORSTATUS_PINK;
				break;
			case CHMemoryDataBase::eFinished:
				ret=COLORSTATUS_GREEN;
				break;
			case CHMemoryDataBase::eProtested:
				ret=COLORSTATUS_BROWN;
				break;
		}
	}
	return ret;
}

int CHMatchVisorFormView::findColorStatus(unsigned char status,RWBoolean useDefault/*=false*/)
{
	int ret=0;

	if(useDefault && status!=CHMemoryDataBase::eAvailable)
		ret=COLORSTATUS_DEFAULT;
	else
	{
		switch (status)
		{
			case CHMemoryDataBase::eAvailable:
				ret=COLORSTATUS_GREY;
				break;
			case CHMemoryDataBase::eConfigured:
				ret=COLORSTATUS_BLACK;
				break;
			case CHMemoryDataBase::eSchedulled:
				ret=COLORSTATUS_BLUE;
				break;
			case CHMemoryDataBase::eStartList:
				ret=COLORSTATUS_DARKBLUE;
				break;
			case CHMemoryDataBase::eRunning:
				ret=COLORSTATUS_GREEN;
				break;
			case CHMemoryDataBase::eUnofficial:
				ret=COLORSTATUS_PINK;
				break;
			case CHMemoryDataBase::eFinished:
				ret=COLORSTATUS_RED;
				break;
			case CHMemoryDataBase::eProtested:
				ret=COLORSTATUS_BROWN;
				break;
		}
	}
	return ret;
}

int CHMatchVisorFormView::findColorSetStatus(unsigned char status)
{
	int ret=0;

	switch (status)
	{
		case CHMemoryDataBase::eAvailable:
			ret=COLORSETSTATUS_AVAILABLE;
			break;
		case CHMemoryDataBase::eConfigured:
			ret=COLORSETSTATUS_CONFIGURED;
			break;
		case CHMemoryDataBase::eSchedulled:
			ret=COLORSETSTATUS_SCHEDULLED;
			break;
		case CHMemoryDataBase::eStartList:
			ret=COLORSETSTATUS_STARTLIST;
			break;
		case CHMemoryDataBase::eRunning:
			ret=COLORSETSTATUS_RUNNING;
			break;
		case CHMemoryDataBase::eUnofficial:
			ret=COLORSETSTATUS_UNOFFICIAL;
			break;
		case CHMemoryDataBase::eFinished:
			ret=COLORSETSTATUS_FINISHED;
			break;
		case CHMemoryDataBase::eProtested:
			ret=COLORSETSTATUS_REVISION;
			break;
	}
	return ret;
}

bool CHMatchVisorFormView::checkForStatus(unsigned char status)
{
	if (status == CHMemoryDataBase::eAvailable	&& w->getCheck(CH_STATUS + 0) ||
		status == CHMemoryDataBase::eConfigured	&& w->getCheck(CH_STATUS + 1) ||
		status == CHMemoryDataBase::eSchedulled	&& w->getCheck(CH_STATUS + 2) ||
		status == CHMemoryDataBase::eStartList	&& w->getCheck(CH_STATUS + 3) ||
		status == CHMemoryDataBase::eRunning	&& w->getCheck(CH_STATUS + 4) ||
		status == CHMemoryDataBase::eUnofficial	&& w->getCheck(CH_STATUS + 5) ||
		status == CHMemoryDataBase::eFinished	&& w->getCheck(CH_STATUS + 6) ||
		status == CHMemoryDataBase::eProtested	&& w->getCheck(CH_STATUS + 7) )
		return true;
	return false;
}

CHMatch * CHMatchVisorFormView::findmatchExist()
{
	short matchNumber=short(w->getTxtValue(ED_FIND_MATCH_VI));
	if(!matchNumber)
	{
		::msg("Error!!","Please, Enter a match number.",0,MSG_OK);
		return 0;
	}
	
	CHMatch *pMatchAux=0;
	for(int i=0;i<w->getGridNItems(LSTMATCHS);i++)
	{
		pMatchAux=(CHMatch*)w->getGridLParam(LSTMATCHS,i);
		if(pMatchAux && pMatchAux->getMatchNumber()==matchNumber)
		{
			return pMatchAux;
		}
	}
	
	::msg("Error!!","No match of selected has this match number.",0,MSG_OK);
	return 0;
}

void CHMatchVisorFormView::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	int focus=w->getFocus();
			
	if(focus==ED_FIND_MATCH_VI)
	{
		if ( wParam==13 ) // Enter
		{				
			this->SendMessage(UM_CLICK,BUTTON_FIND_MATCH_DE_VI,0);	
		}
	}
}

RWBoolean CHMatchVisorFormView::registersInMatch(CHMatch *pMatch)
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
bool CHMatchVisorFormView::lockMatch(CHMatch *pMatch)
{
	if (!pMatch)
		return false;

	RWCString lockStringMatch;
	char match[10];
	
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

void CHMatchVisorFormView::unLockMatch()
{
	APP::unlock(lastMatchLocked);
}