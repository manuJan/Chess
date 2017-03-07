/*************************************************************************************
*			© Copyright MSL Software, S.L., 2001
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:	CHScheduleFormView.cpp
*	Description	:   Chess Schedule
*
*	Author		:	Chess Team
*	Date created:   27-12-2005
* 	Project		:	Chess Manager
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdafx.h"
#include "CHmanager.h"
#include "CHScheduleFormView.h"
#include "CHDefines.h"
#include "CHTreatSession.h"
#include "CHCnfgTeamSchedule.h"
#include "CHCnfgMatchJudgeDlg.h"
#include "CHTeamResults.h"
#include <Sports/CH/Data/CHMsgDefines.h>
#include <CORE/TH/GTHMsgDefines.h>
#include <GUI/TH/GUITHSports.h>
#include <GUI/Flags/Flags.h>
#include <Sports/CH/Data/CHMatchResult.h>
#include <Sports/CH/Data/CHMatchJudge.h>
#include <Sports/CH/Data/CHPhaseBase.h>
#include <Sports/CH/Data/CHDiscipline.h>
#include <Sports/CH/Reports/CHReportDefines.h>

#include <SPORTS/CH/REPORTS/CHRC08.h>
#include <SPORTS/CH/REPORTS/CHRC51.h>
#include <SPORTS/CH/REPORTS/CHRC58.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int BUT_CFGMATCH      =900;
const int ID_GREEN	        =901;
const int ID_RED			=902;
const int BUT_CFGSUBMATCH   =903;
const int BUT_CFGDATAENTRY	=904;
const int CMB_SELECT_STATUS =905;
const int CMB_SELECT_TABLE  =906;
const int IDFONT1		    =907;
const int CMB_SELECT_ROUND  =908;

#define MATCHES_UP_PHASE(a) (((a)->getPhaseCode()[size_t(0)]>='B' && (a)->getPhaseCode()[size_t(0)]<='E'))

IMPLEMENT_DYNCREATE(CHScheduleFormView, CFormView)

static int orderPhasesByEvents(const GVectorElement** a, const GVectorElement** b)
{
	CHPhase * pPhaseEvA = (CHPhase *)(*a)->getElement();
	CHPhase * pPhaseEvB = (CHPhase *)(*b)->getElement();

	CHEvent *pEventA=(CHEvent*)pPhaseEvA->getEvent();
	CHEvent *pEventB=(CHEvent*)pPhaseEvB->getEvent();

	int order = pEventA->getOrderEvent()-pEventB->getOrderEvent();
	if(order)
		return order;

	order = pPhaseEvA->getOrder() - pPhaseEvB->getOrder();
	if(order)
		return order;

	return stricmp(pPhaseEvA->getKey(),pPhaseEvB->getKey());
}

extern CCHManagerApp theApp;

//////////////////////////////////////////////////////////////////////
// Select Functions
 
//////////////////////////////////////////////////////////////////////
// Order Functions
int orderEvent(const GVectorElement** a, const GVectorElement** b)
{
	CHEvent* pEventA=(CHEvent*)(*a)->getElement();
	CHEvent* pEventB=(CHEvent*)(*b)->getElement();

	return strcmp(pEventA->getKey(),pEventB->getKey());
}
int orderByMatchNumbers(const GVectorElement** a, const GVectorElement** b)
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

int orderCourt(const GVectorElement** a, const GVectorElement** b)
{
	GCourt* pCourtA=(GCourt*)(*a)->getElement();
	GCourt* pCourtB=(GCourt*)(*b)->getElement();

	if(pCourtA->getCourt() && pCourtB->getCourt())
		 return pCourtA->getCourt() - pCourtB->getCourt();

	else return 0;
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction

CHScheduleFormView::CHScheduleFormView()
:GTHScheduleFormView()
,gsvAvailableDates()
,vAvailablesMatches()
,vAvailablesPooles()
,vAvailablesPoolesPhase()
,aReportEvents()
,subMenu(0)
,isConsolation(false)
{
	//{{AFX_DATA_INIT(CHScheduleFormView)
		
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CHScheduleFormView::~CHScheduleFormView()
{
	gsvAvailableDates.clearAndDestroy();
	vAvailablesMatches.clearAndDestroy();
	vAvailablesPooles.clearAndDestroy();
	vAvailablesPoolesPhase.clearAndDestroy();
	aReportEvents.clearAndDestroy();
}

void CHScheduleFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHScheduleFormView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHScheduleFormView, GTHScheduleFormView)
	//{{AFX_MSG_MAP(CHScheduleFormView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		ON_MESSAGE(UM_DELETE_SESSION	,onDeleteSession)
			
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CHScheduleFormView diagnostics

#ifdef _DEBUG
void CHScheduleFormView::AssertValid() const
{
	CFormView::AssertValid();
}

void CHScheduleFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

void CHScheduleFormView::init()
{
	GTHScheduleFormView::init();	 

	setSchMatchesOrderFunction(orderByMatchNumbers);

	w->addColorSet( ID_RED, RGB(150,0, 100),COLOR_DEFAULT_OFF, COLOR_DEFAULT_HITX, COLOR_DEFAULT_HIGH, COLOR_DEFAULT_L3D, COLOR_DEFAULT_N3D, COLOR_DEFAULT_D3D );
	w->addColorSet( ID_GREEN, RGB(0,150,100),COLOR_DEFAULT_OFF, COLOR_DEFAULT_HITX, COLOR_DEFAULT_HIGH, COLOR_DEFAULT_L3D, COLOR_DEFAULT_N3D, COLOR_DEFAULT_D3D );

	w->createLabelEx(BUT_CFGMATCH,CRect(600,600,725,620),"Match Configuration",BORDER_NONE,JUST_CENTER,-1,-1,IDFNT_BOLD,-1,-1,IDFNT_BOLD);
	w->enable(BUT_CFGMATCH,false);
	w->createLabelEx(BUT_CFGDATAENTRY,CRect(750,600,850,620),"Manual Data Entry",BORDER_NONE,JUST_CENTER,-1,-1,IDFNT_BOLD,-1,-1,IDFNT_BOLD);
	w->enable(BUT_CFGDATAENTRY,false);
	w->createLabelEx(BUT_CFGSUBMATCH,CRect(875,600,985,620),"Team Configuration",BORDER_NONE,JUST_CENTER,-1,-1,IDFNT_BOLD,-1,-1,IDFNT_BOLD);
	w->enable(BUT_CFGSUBMATCH,false);

	w->addGridColumn(LSTSESSION1,"Round",JUST_CENTER,40);
	
	w->chgGridColumnWidth(LSTSESSION1,2,35);  // Match MN
	w->chgGridColumnWidth(LSTSESSION1,3,165); // Match Description
	w->chgGridColumnWidth(LSTSESSION1,4,297); // Home vs Away
	
	w->changeTxt(LABELCOURT,"Table:");
	w->chgGridColumnTxt(LSTSESSION1,7,"Table");
	w->editGridAuto(LSTSESSION1,true);

	// No quiero el "All Venues", si llegase a ser multisede quitar la siguiente funcion y ya

	w->addFont (IDFONT1, 4,11,0,0,0,0,_T("Tahoma"));
	w->createCombo (CMB_SELECT_STATUS  ,CRect(792, 240,853  ,287),BORDER_SINGLE,15,IDBCK,IDCOL,IDFONT1);
	w->createCombo (CMB_SELECT_ROUND   ,CRect(953/*792*/, 240,993/*853*/  ,287),BORDER_SINGLE,15,IDBCK,IDCOL,IDFONT1);
	fillComboOwn();
	fillStatus();
	fillRound();
	fillReports();
}


void CHScheduleFormView::fillReports()
{	// Opciones del menu de Reports.
	APP::addReport(1,0,RC08_NAME,RC08,CH_SCHEDULE_FORMVIEW);
	APP::addReport(2,0,RC58_NAME,RC58,CH_SCHEDULE_FORMVIEW);
	// Submenu para C58
	GTHMatch *pMatch = 0;
	RWBoolean founded = false;
	RWDate date;
	GScheduleDay *tmp = 0;
	gsvAvailableDates.clearAndDestroy();
	// Fill AvailableDates SortedVector
	RWSetIterator iter(mem()->getColMatchs());
	while( (pMatch = (GTHMatch*)iter()) != 0 ) 
	{
		founded = false;
		if( pMatch->getStartDate() != INVALID_RWDATE )
		{
			date = pMatch->getStartDate();
			GScheduleDay *pDate= new GScheduleDay(date);
			for( size_t i=0; i < gsvAvailableDates.entries(); i++)
			{
				tmp = (GScheduleDay *)gsvAvailableDates[i]->getElement();
				if( pDate->getDate() == tmp->getDate() )
				{
					founded = true;
					break;
				}
			}
			if( !founded )
				gsvAvailableDates.insert(pDate);
			else 
				if( pDate )
					delete( pDate );
		}
	}

	for( size_t j=0; j<gsvAvailableDates.entries(); j++)
	{
		GScheduleDay *pDate=(GScheduleDay*)gsvAvailableDates[j]->getElement();
		if( pDate )
			APP::addReport(RC58+(j+1), 2,(CString)toUpper(pDate->getDate().asString("%a %d %b %Y")), RC58, CH_SCHEDULE_FORMVIEW, LPARAM(pDate), 0);
	}

	
	APP::addReport(3,0,RC51_NAME,RC51,CH_SCHEDULE_FORMVIEW);
	//Phases
	GSortedVector vPhases(CHMemoryDataBase::getColPhases(),orderPhasesByEvents);
	CHPhase * pPhase=0;
	
	for(size_t i=0 ; i<vPhases.entries() ; i++)
	{
		pPhase=(CHPhase*)vPhases[i]->getElement();
				
		RWCString phaseDesc=pPhase->getEventLDescription().toAscii() + " " + pPhase->getLDescription().toAscii();
		APP::addReport(RC51+i,3,phaseDesc,RC51,CH_SCHEDULE_FORMVIEW,LPARAM(pPhase),0);
				
	}
}

void CHScheduleFormView::DeassignEventData(GTHEvent* pEvent)
{
	if (pEvent)
	{
		pEvent->setStatus(GMemoryDataBase::eConfigured);
		saveEvent(pEvent,TRN_DESCONFIGURE_EVENT);
	}
}
	 
void CHScheduleFormView::onClick(UINT idCtrl,LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	
	if (w->getSelectedLParam(LSTSESSION1))
	{
		CHMatch * pMatch = (CHMatch * )w->getSelectedLParam(LSTSESSION1);	
		w->changeColor(BUT_CFGDATAENTRY,ID_GREEN);
		if (pMatch->getStatus() <= GMemoryDataBase::eFinished)
		{	w->changeColor(BUT_CFGMATCH,ID_GREEN);
			w->changeColor(BUT_CFGSUBMATCH,ID_GREEN);
		}
		else
		{
			w->changeColor(BUT_CFGMATCH,ID_RED);
			w->changeColor(BUT_CFGSUBMATCH,ID_RED);
		}

		w->enable(BUT_CFGMATCH,true);
		w->enable(BUT_CFGDATAENTRY,true);
		
		if(pMatch->areTeams())
			 w->enable(BUT_CFGSUBMATCH,true);
		else w->enable(BUT_CFGSUBMATCH,false);
	}
	else
	{
		w->enable(BUT_CFGMATCH,false);
		w->enable(BUT_CFGSUBMATCH,false);
		w->enable(BUT_CFGDATAENTRY,false);
	}

	switch (idCtrl)
	{
		case BUT_CFGSUBMATCH:
		{
			GSortedVector gsvMatches;
			gsvMatches.sort(orderByMatchNumbers);
			for (int i=0; i<w->getGridNItems(LSTSESSION1); i++)
			{
				CHMatch * pMatch = (CHMatch * )w->getGridLParam(LSTSESSION1,i);
				if (pMatch->areTeams())
					gsvMatches.insert(pMatch);
			}
			if (!gsvMatches.entries())
				break;
			CHCnfgTeamSchedule dlgCnfgTeamSchedule(this,gsvMatches,gsvMatches.index((CHMatch * )w->getSelectedLParam(LSTSESSION1)));
			dlgCnfgTeamSchedule.DoModal();
			w->redraw(LSTSESSION1);
		}
		break;
		case BUT_CFGMATCH:
		{
			CHMatch * pMatch = (CHMatch * )w->getSelectedLParam(LSTSESSION1);
			if (pMatch && /*!pMatch->areTeams() &&*/ lockMatch(pMatch))
			{
				CHCnfgMatchJudgeDlg dlgCnfgMatchDlg(this,pMatch);
				if (dlgCnfgMatchDlg.DoModal())
				{
					unLockMatch();
					w->redrawLine(LSTSESSION1,w->getSelectedLine(LSTSESSION1));
				}	
			}
		}
		break;

		case BUT_CFGDATAENTRY:
		{
			CHMatch * pMatch = (CHMatch * )w->getSelectedLParam(LSTSESSION1);
			if(!registersInMatch(pMatch))
			{	::msg("Attention","Match without competitor/s available",ICO_X,MSG_OK);
				return;
			}

			if( pMatch->getStatus() < CHMemoryDataBase::eSchedulled )
			{
				::msg("Warning!!","Match´s status is less than Schedulled",ICO_X,MSG_OK);
					return;
			}

			if (pMatch && lockMatch(pMatch))
			{
				if(pMatch->areTeams())
				{
					CHTeamResults teamResults(this,pMatch);
					if (teamResults.DoModal())
					{
						unLockMatch();
						w->redrawLine(LSTSESSION1,w->getSelectedLine(LSTSESSION1));
					}
				}
				else
				{			
					CHManualEventControl * pResultDlg = new CHManualEventControl(this,pMatch);
					if( pResultDlg )
					{
						pResultDlg->DoModal();
						unLockMatch();
						delete pResultDlg;

						w->redraw(LSTSESSION1);
						
					}
					return;
				}
			}
		}
		break;
		case CMB_SELECT_STATUS:
		case CMB_SELECT_TABLE:
		case CMB_SELECT_ROUND:
		{	
			fillSchedulledGrid();	
			
		}
		break;
		case BUTADDSESSION:
			{
				RWCString lockStringData;
				lockStringData = "SESSIONS";
				if(APP::lock(lockStringData))
				{	
					CHTreatSession dlgSessions(mem(),this);
					dlgSessions.DoModal();
					fillComboSessions(getDate());
					APP::unlock(lockStringData);
				}
				break;
			}
		default:
			GTHScheduleFormView::onClick(idCtrl,lParam);			
	}
}

void CHScheduleFormView::onDblClick(UINT idGrid,int x,int y,LPARAM lParam)
{
	w->redraw(LSTSESSION1,true);
	// Si modifica la fecha tengo que modificar el vector de dias

	switch(idGrid)
	{
	case LSTSESSION1:
		{		     
			switch(x)
			{
				case 3:
				{	
					CHMatch * pMatch = (CHMatch*)lParam;
					if(!pMatch || pMatch)
						return;
					if (lockMatch(pMatch) )
					{
					
					}
				}
				break;
				case 4:
				{
					CHMatch * pMatch = (CHMatch*)lParam;
					if(!pMatch )
						return;
					if(!registersInMatch(pMatch))
					{	::msg("Attention","Match without competitor/s available",ICO_X,MSG_OK);
						return;
					}
					if (lockMatch(pMatch) )
					{
						if(pMatch->areTeams())
						{
							
						}
						else
						{
						
						}
					}
				}
				break;
				case 5:
				{
					CHMatch * pMatch = (CHMatch*)lParam;
					if(!pMatch)
						return;
					if(pMatch->areTeams())
					{
						if (lockMatch(pMatch) )
						{
							
						
						}
					}
				}
				break;
				case 6: // Session
				case 7: // Court
					{	CHMatch * pMatch = (CHMatch*)lParam;
						if(!pMatch )
							return;
						if (pMatch->getStatus()==CHMemoryDataBase::eFinished)
							return;
						GTHScheduleFormView::onDblClick(idGrid,x,y,lParam);
						if (x==7)
						{
							//X05
							sendIDSNotify(N_SCHEDULE,pMatch,N_UPDATE);
							::Sleep(300L);
						}
						if(pMatch->areTeams())
						{
							CHMatch *pSubMatch=0;
							GSortedVector vSubMatch = pMatch->getSubMatches();
							for(size_t i=0;i<vSubMatch.entries();i++)
							{
								pSubMatch = (CHMatch *)vSubMatch[i]->getElement();
								if( pSubMatch )
								{
									if (x==6)
									{
										if(pMatch->getSession())
											pSubMatch->setSession(pMatch->getSession());
									}
									else if (x==7)
									{
										if(pMatch->getCourt())
											pSubMatch->setCourt(pMatch->getCourt());
									}
									outMatch(pSubMatch);
								}
							}								
						}
					}
					break;
				default:
						GTHScheduleFormView::onDblClick(idGrid,x,y,lParam);
						break;
			}		
		}
		break;
		default:
			GTHScheduleFormView::onDblClick(idGrid,x,y,lParam);
			break;
	} //end switch
}

BOOL CHScheduleFormView::onPaintGrid(UINT idGrid,GridItem *gi)
{
	if (idGrid==LSTAVAL)
	{
		return GTHScheduleFormView::onPaintGrid(idGrid,gi);
	}

	if (idGrid==LSTSESSION1)
	{
		if (gi->x==4)
		{
			if (!gi) return true;
	
			CHMatch *pMatch=(CHMatch *) gi->lParam;
			if (!pMatch) return true;
			if (pMatch->areTeams())
			{
				COLORREF color=GET_COLOR_DEFAULT_N3D;
				w->paintGridSolid((gi->sel)?GET_COLOR_DEFAULT_HIGH:color);
				// Match Competitors
				if (pMatch->getCompetitorsVector().entries()==2)
				{
					if (pMatch->getCompetitorsVector()[0]->getElement() &&
						pMatch->getCompetitorsVector()[1]->getElement())
					{
						CHMatchResult* pMatchRes1 = (CHMatchResult*)pMatch->getCompetitorsVector()[0]->getElement();
						CHMatchResult* pMatchRes2 = (CHMatchResult*)pMatch->getCompetitorsVector()[1]->getElement();
						
						if (pMatchRes1->getRegister())
						{
							CBitmap aBitmap;
							getFlag(pMatchRes1->getGroup(),ICO,&aBitmap);	
							w->paintGridUserBmp  (4,1,&aBitmap,false);
	
							// NOC Home
							w->paintGridText(1,12,pMatchRes1->getGroup(),IDFNT_MIN,gi->sel? GET_COLOR_DEFAULT_HITX : GET_COLOR_DEFAULT_ON);
						}
	
						COLORREF color;
						if (pMatchRes1->getBye() || pMatchRes2->getBye())
							color=RGB(250,0,0);
						else
							color=GET_COLOR_DEFAULT_ON;

						RWWString aux=_T(" - ");
						RWWString txt1=_T("");
						RWWString txt2=_T("");
						if (pMatchRes1->getRegister())
							txt1=pMatchRes1->getPrnSName();
						else if (pMatchRes1->getBye())
							txt1=pMatchRes1->getIDCompetitor()+_T(" (BYE)");
						else if (pMatchRes1->getPoolPosition())
							txt1=pMatchRes1->getIDCompetitor();
						if (pMatchRes2->getRegister())
							txt2=pMatchRes2->getPrnSName();
						else if (pMatchRes2->getBye())
							txt2=pMatchRes2->getIDCompetitor()+_T(" (BYE)");
						else if (pMatchRes2->getPoolPosition())
							txt2=pMatchRes2->getIDCompetitor();
						w->paintGridText(gi->rc.Width()/2,0,txt1+aux+txt2,IDFNT,gi->sel? GET_COLOR_DEFAULT_HITX : color,JUST_CENTER);

						if (pMatchRes2->getRegister())
						{
							CBitmap aBitmap;
							getFlag(pMatchRes2->getGroup(),ICO,&aBitmap);	
							w->paintGridUserBmp  (279,1,&aBitmap,false);
						
							// NOC Away
							w->paintGridText(276,12,pMatchRes2->getGroup(),IDFNT_MIN,gi->sel? GET_COLOR_DEFAULT_HITX : GET_COLOR_DEFAULT_ON);
						}
					}
				return true;
				}
			}
		}
		GTHScheduleFormView::onPaintGrid(idGrid,gi);
		paintGridSession(gi);
		return true;
	}
	return false;
}

void CHScheduleFormView::paintGridSession(GridItem *gi)
{
	if (!gi) 
		return;
	
	CHMatch *pMatch=(CHMatch *) gi->lParam;
	if (!pMatch) 
		return;

	// Text		
	switch (gi->x)
	{
		case 2: // Match
		{
			break;
		}
		case 4:// Match Competitors
		{
			break;
		}
		case 6: //Session
		{
			if (pMatch->getSessionSession()==0)
				w->paintGridText(10,0,"*",w->getCurrentFont(LSTSESSION1),RGB(255,0,0),JUST_LEFT);
			break;
		}
		case 7: //Court
		{
			if (pMatch->getCourtCode()==0)
				w->paintGridText(10,0,"*",w->getCurrentFont(LSTSESSION1),RGB(255,0,0),JUST_LEFT);
			break;
		}
		case 8: // Round
		{
			char txt[100];
			sprintf(txt,"%d", pMatch->getRound());
			w->paintGridText(20,0,txt,IDFNT_BOLD,IDCOL,JUST_CENTER);			
			break;
		}
	}
}

bool CHScheduleFormView::lockMatch(CHMatch *pMatch)
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

void CHScheduleFormView::unLockMatch()
{
	APP::unlock(lastMatchLocked);
}

//////////////////////////////////////////////////////////////////////
// Temporal Reports methods
//////////////////////////////////////////////////////////////////////

void CHScheduleFormView::onReportRequest(CReportItem *pItem)
{
	if (!pItem)
		return;
	switch (pItem->getNReport())
	{
		case RC08:
		{
			pItem->setResultCode(CHMemoryDataBase::getRSC((GData *)0));
			break;
		}
		case RC58:
		{
			GScheduleDay *pDate = (GScheduleDay *)pItem->getLParam1();
			if( pDate )
			{
				pItem->setResultCode(CHMemoryDataBase::getRSC((GData *)0));
				RWDate date=pDate->getDate();
				pItem->addParameters(date.asString("%Y%m%d"));
			}
		}
		break;
		case RC51:
		{
			CHPhase *pPhase = (CHPhase *)pItem->getLParam1();
			if( pPhase )
				pItem->setResultCode(((CHMemoryDataBase*)mem())->getRSC(pPhase));
		}
		break;
	}
}

bool CHScheduleFormView::onReportGeneration(CReportManager *pReportMngr,CReportConfig *pReportCfg,CReportItem *pItem)
{
	if (!pItem || !pReportCfg || !pReportMngr)
		return false;
	switch (pItem->getNReport())
	{
		case RC08:
		{
			CHRC08 rRC08(*pReportMngr,*pReportCfg);
			return rRC08.Run(); 
			break;
		}
	case RC58:
		{
			GScheduleDay *pDate = (GScheduleDay *)pItem->getLParam1();
			if( !pDate )
			{
				::msg("Day not Selected!!","Please select a Day",ICO_X,MSG_OK);
				return 0;
			}			

			CHRC58 aRC58(*pReportMngr,*pReportCfg,pDate->getDate());
			return aRC58.Run();
			break;
		}
	case RC51:
		{
			if( !pItem->getLParam1() )
			{
				AfxMessageBox(RWWString("Please select a Event-Phase",RWWString::multiByte));
				return false;
			}

			if (pItem->getNReport()==RC51)
			{
				CHRC51 aCHRC51(*pReportMngr,*pReportCfg,(CHPhase*)pItem->getLParam1());
				return aCHRC51.Run();
			}
			break;
		}
	}
	return false;
}

void CHScheduleFormView::propagateMatchDateTime(GTHMatch* pMatch)
{
	CHMatch *pMat=(CHMatch *)pMatch;
	CHMatch *pSubMatch=0;
	//si cambiamos la fecha, hora, sesion, mesa o sede manualmente
	//lo pasamos al resto de los enfrentamientos de equipos
	if (pMat->areTeams())
	{
		GSortedVector vSubMatch = pMat->getSubMatches();
		for(size_t i=0;i<vSubMatch.entries();i++)
		{
			pSubMatch = (CHMatch *)vSubMatch[i]->getElement();
			if( pSubMatch )
			{
				if (pSubMatch->getStartDate()!=pMat->getStartDate() ||
					pSubMatch->getStartTime()!=pMat->getStartTime() ||
					pSubMatch->getSession()!=pMat->getSession() ||
					pSubMatch->getCourt()!=pMat->getCourt() ||
					pSubMatch->getVenue()!=pMat->getVenue())
				assignScheduledData(pMat,pSubMatch);
			}
		}
	}
	GTHScheduleFormView::propagateMatchDateTime(pMatch);
}

bool CHScheduleFormView::canConfigureMatch(GTHMatch *pMatch)
{
	if (!GetSessionComboSelection())
	{
		::msg(_T("Warning"),_T("please set the match session in the sessions combo!"),ICO_W,MSG_OK);	
		return false;
	}

	if (!GetCourtComboSelection())
	{
		::msg(_T("Warning"),_T("please set the match table in the tables combo!"),ICO_W,MSG_OK);	
		return false;
	}

	return true;
}

bool CHScheduleFormView::canDesconfigureMatch(GTHMatch *pMatch)
{
	bool ret = GTHScheduleFormView::canDesconfigureMatch(pMatch);
	if (ret)
	{
		// Si no es un registro de equipo, OUT.
		if(!((CHMatch *)pMatch)->areTeams())
			return true;
		
		CHMatch *pSubMatch=0;

		GSortedVector vSubMatch = ((CHMatch *)pMatch)->getSubMatches();
		for(size_t i=0;i<vSubMatch.entries();i++)
		{
			pSubMatch = (CHMatch *)vSubMatch[i]->getElement();
			if ( pSubMatch && (pSubMatch->getStatus()>GTHMemoryDataBase::eSchedulled) ) 
			{
				if (::msg("Warning !!", "There is any match whose status is up to schedulled\ndo you like continue ?",0,MSG_YESNO)==RET_NO)
					return false;
				break;
			}
		}

		for(i=0;i<vSubMatch.entries();i++)
		{
			pSubMatch = (CHMatch *)vSubMatch[i]->getElement();
			if( pSubMatch )
			{
				deAssignScheduledData(pSubMatch);
			}
		}
	}
	return ret;
}

void CHScheduleFormView::deAssignScheduledData(CHMatch *pSubMatch)
{
	if(pSubMatch)
	{
		pSubMatch->setStartDate(INVALID_RWDATE);
		pSubMatch->setStartTime(INVALID_RWTIME);
		pSubMatch->setSession(0);
		pSubMatch->setCourt(0);
		pSubMatch->setStatus(GMemoryDataBase::eAvailable);
		outMatch(pSubMatch);
	}
}

void CHScheduleFormView::AssignUserData(GTHMatch *pMatch)
{
	CHMatch* pMatchAux=(CHMatch*)pMatch;
	
	// Procesamos Sub-Eventos de Equipos...
	if((CHMatch*)pMatchAux->areTeams())
	{
		CHMatch *pSubMatch=0;

		GSortedVector vSubMatch = pMatchAux->getSubMatches();
		for(size_t i=0;i<vSubMatch.entries();i++)
		{
			pSubMatch = (CHMatch *)vSubMatch[i]->getElement();
			if( pSubMatch )
			{
				assignScheduledData(pMatchAux,pSubMatch);
			}
		}
	}
}

void CHScheduleFormView::assignScheduledData(CHMatch *pMatch,CHMatch *pSubMatch)
{
	if(pMatch && pSubMatch)
	{
		pSubMatch->setStartDate(pMatch->getStartDate());
		pSubMatch->setStartTime(pMatch->getStartTime());
		if(pMatch->getSession())
			pSubMatch->setSession(pMatch->getSession());
		if(pMatch->getCourt())
			pSubMatch->setCourt(pMatch->getCourt());
		if(pMatch->getVenue())
			pSubMatch->setVenue(pMatch->getVenue());

		pSubMatch->setStatus(GMemoryDataBase::eSchedulled);
		outMatch(pSubMatch);
	}
}

bool CHScheduleFormView::canInsertAvailableMatch(GTHMatch* pMatch)
{
	CHMatch *pMatchS=(CHMatch*)pMatch;
	// Si no hay matchResults nos vamos.
	
	GTHMatchResult *pMatchRes1 = (GTHMatchResult*)pMatch->getCompetitorsVector()[0]->getElement();
	GTHMatchResult *pMatchRes2 = (GTHMatchResult*)pMatch->getCompetitorsVector()[1]->getElement();
	if (!pMatchRes1 || !pMatchRes2)
		return false;
	
	// Si es un sub-evento no nos vale.
	if (	((CHMatch *)pMatch)->getSubMatch()>0)
		return false;
	
	// Si status>=schedule no nos vale.
	if ( pMatch->getStatus() >= GTHMemoryDataBase::eSchedulled )
		return false;
	
	// Si el match es bye no nos vale.
	if ( ((CHMatch*)pMatch)->isBye())
		return false;

	return true;
}

bool CHScheduleFormView::canInsertSelectedMatch(GTHMatch* pMatch)
{
	if ( pMatch->getStartDate().isValid() &&
		 pMatch->getStartTime().isValid() &&
		 pMatch->getStatus() >= GTHMemoryDataBase::eSchedulled && 
		 (((CHMatch *)pMatch)->getSubMatch()==0) &&
		 !((CHMatch*)pMatch)->isBye())
	{
		return true;
	}
	return false;
}

bool CHScheduleFormView::canInsertScheduledMatch(GTHMatch* pMatch)
{
	if(	(pMatch->getStatus() >= GTHMemoryDataBase::eSchedulled ||
		pMatch->getStartDate().isValid()) && 
		(((CHMatch *)pMatch)->getSubMatch()==0) && 
		!((CHMatch*)pMatch)->isBye() && 
		correctStatus(pMatch) && correctTable(pMatch) && correctRound(pMatch))
	{
		return true;
	}
	return false;
}
RWBoolean CHScheduleFormView::correctStatus(GTHMatch* pMatch)
{
	GStatus *pStatus=(GStatus*)w->getSelectedData(CMB_SELECT_STATUS);
	if(!pStatus)
		return true;
	if(pMatch->getStatus()==pStatus->getStatus())
		return true;

	return false;
}
RWBoolean CHScheduleFormView::correctTable(GTHMatch* pMatch)
{
	GCourt *pCourt=(GCourt*)w->getSelectedData(CMB_SELECT_TABLE);
	if(!pCourt)
		return true;
	if(pMatch->getCourt() && ((CHMatch *)pMatch)->getCourtKey()==pCourt->getKey())
		return true;

	return false;
}

RWBoolean CHScheduleFormView::correctRound(GTHMatch* pMatch)
{
	int round = w->getSelectedData(CMB_SELECT_ROUND);
	if (round<1)
		return true;
	if (((CHMatch *)pMatch)->getRound()==round)
		return true;

	return false;

}

RWWString CHScheduleFormView::getAvailableMatchDescription(GTHMatch* pMatch)
{
	RWWString txt = NULLRWWSTRING;
	CString matchCode = _T("");	

	txt = getMatchDescription(pMatch);
	if (pMatch->getCompetitorsVector().entries()==2)
	{
		if (pMatch->getCompetitorsVector()[0]->getElement() &&
			pMatch->getCompetitorsVector()[1]->getElement())
		{
			GTHMatchResult* pMatchRes1 = (GTHMatchResult*)pMatch->getCompetitorsVector()[0]->getElement();
			GTHMatchResult* pMatchRes2 = (GTHMatchResult*)pMatch->getCompetitorsVector()[1]->getElement();
			if (pMatchRes1->getRegister() && pMatchRes2->getRegister())
			{
				txt += _T("  ");
				txt += getMatchResultDescription(pMatchRes1);
				txt += _T(" - ");
				txt += getMatchResultDescription(pMatchRes2);				
			}
		}
	}
	return txt;
}
RWWString CHScheduleFormView::getMatchDescription(GTHMatch* pMatch)
{
	RWCString txt = NULLRWSTRING;
	
	// Si es una Pool
	if (pMatch->getIsPool())
	{
		txt = pMatch->getEventSDescription().toMultiByte();
		txt = txt + pMatch->getPhaseSDescription().toMultiByte();
		txt=txt+" "+pMatch->getPoolDescription(((CHMatch *)pMatch)->getPhasePoolDescription()).toMultiByte();
		txt += " - ";
		txt += ((CHMatch*)pMatch)->getRoundAsString();
	}
	else 
	{
		txt = ((CHMatch *)pMatch)->getEventSDescription().toMultiByte();
		txt = txt + ((CHMatch *)pMatch)->getPhaseSDescription().toMultiByte();
		txt = txt + " ";				
		txt = txt + ((CHMatch *)pMatch)->getPoolDescription().toMultiByte();
		txt += " - ";
		txt += ((CHMatch*)pMatch)->getRoundAsString();
	}
	return (CString)txt;
}

void CHScheduleFormView::fillStatus()
{
	w->delAllItems(CMB_SELECT_STATUS);
			
	RWOrderedIterator ite2((RWSortedVector&)mem()->getColStatus());
	GStatus *pStatus=0;
	while( (pStatus=(GStatus *)ite2()) != 0)
	{
		// No meto los status menores a Schedule
		if(pStatus->getStatus()<GMemoryDataBase::eSchedulled)
			continue;
		CString status=_T("");
		status.Format(_T("%s"),pStatus->getLDescription());
		w->addItem(CMB_SELECT_STATUS,0,status,0,LPARAM(pStatus));
	}
	
	w->addItem(CMB_SELECT_STATUS,0,"All",0,0);
	w->selectItem (CMB_SELECT_STATUS,0);
}

void CHScheduleFormView::fillRound()
{
	w->delAllItems(CMB_SELECT_ROUND);
	size_t nRound=0;
	RWSetIterator iter(CHMemoryDataBase::getColPools());
	CHPool * pPool=0;
	while((pPool=(CHPool*)iter())!=0)
	{
		if (nRound<pPool->getNumRounds())
			nRound=pPool->getNumRounds();
	}
	for (size_t i=0; i<nRound; i++)
	{
		CString round;
		round.Format(_T("%d"),i+1);
		w->addItem(CMB_SELECT_ROUND,0,round,0,LPARAM(i+1));
	}
	w->addItem(CMB_SELECT_ROUND,0,"All",0,0);
	w->selectItem (CMB_SELECT_ROUND,0);
}

bool CHScheduleFormView::canChangeMatchSession(GTHMatch* pMatch,int column)
{
	// Si devuelvo true, 
	// me cambiara la sesion al editar una fecha o una hora de un match.
	return false;

	// default
	// return true;
	UNREFERENCED_PARAMETER(pMatch);
	UNREFERENCED_PARAMETER(column);
}

bool CHScheduleFormView::canChangeMatchNumber(GTHMatch* pMatch, int matchNumber)
{
	// default
	return true;
	UNREFERENCED_PARAMETER(pMatch);
	UNREFERENCED_PARAMETER(matchNumber);
}

bool CHScheduleFormView::canChangeCourt(GTHMatch* pMatch, GCourt* pNewCourt)
{
	// default
	return true;
	UNREFERENCED_PARAMETER(pMatch);
	UNREFERENCED_PARAMETER(pNewCourt);
}
bool CHScheduleFormView::canChangeSession(GTHMatch* pMatch, GTHSession* pNewSession)
{
	// default
	return true;
	UNREFERENCED_PARAMETER(pMatch);
	UNREFERENCED_PARAMETER(pNewSession);
}

LRESULT CHScheduleFormView::onDeleteSession(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	CHSession * pSession=(CHSession*)wParam;
	if(pSession)
	{
		BOOL changes=false;
		APP::out(TRN_CHANGE_MATCH);
		
		RWSetIterator iter(CHMemoryDataBase::getColMatchs());
		CHMatch * pMatch=0;
		while ((pMatch=(CHMatch *)iter())!=0)
		{
			if(pMatch->getSession()==pSession)
			{
				pMatch->setSession(0); //quito session 
				APP::out(*pMatch,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
				changes=true;
			}
		}
		APP::out();
	}
	return true;
}

RWBoolean CHScheduleFormView::matchHaveJudges(CHMatch *pMatch)
{
	GSortedVector & vJudges=pMatch->getJudgesVector();
	
	for(size_t i=0;i<vJudges.entries();i++)
	{
		CHMatchJudge * pMatchJudge=(CHMatchJudge*)vJudges[i]->getElement();
		if(pMatchJudge)
		{
			if(pMatchJudge->getRegister())
				return true;
		}
	}
	return false;
}

RWWString CHScheduleFormView::getCourtDescription(GCourt* pCourt)
{
	if (pCourt)
		return pCourt->getSDescription();
	return NULLRWWSTRING;
}

void CHScheduleFormView::outMatch(CHMatch *pMatchAux)
{
	APP::out(TRN_CHANGE_MATCH);
	APP::out(*pMatchAux,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);		
	APP::out();
}

RWBoolean CHScheduleFormView::registersInMatch(CHMatch *pMatch)
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

bool CHScheduleFormView::canChangeMatchDate(GTHMatch* pMatch, RWDate newDate)
{
	if ((pMatch->getStatus()<=GTHMemoryDataBase::eStartList) ||
		(pMatch->getStartDate().isValid() && newDate!=pMatch->getStartDate()))
		return true;//(pMatch->getStatus()<=GTHMemoryDataBase::eStartList);
	return false;
}

bool CHScheduleFormView::canChangeMatchTime(GTHMatch* pMatch, RWTime time)
{
	return ((pMatch->getStatus()<=GTHMemoryDataBase::eStartList) ||
			(pMatch->getStartTime().isValid() && time!=pMatch->getStartTime()));
	UNREFERENCED_PARAMETER(time);
}

RWSet* CHScheduleFormView::getFilterMatches(GScheduleDay* pDay/*=0*/, GVenue * pVenue/*=0*/, GCourt* pCourt/*=0*/, GTHSession * pSession/*=0*/)
{
	CHEvent * pPrevEventSel = (CHEvent*)pEventSel;
	
	RWSet * colMatches = GTHScheduleFormView::getFilterMatches(pDay,pVenue,0,pSession);
	pEventSel = pPrevEventSel;
	return colMatches;
}

void CHScheduleFormView::fillComboOwn()
{
	CSchComboBox* pComboVenues=(CSchComboBox*)GetComboVenues();
	
	pComboVenues->ResetContent();
		
	RWSet venues = mem()->getColVenues();
	GVenue *pVenue=0;
	RWSetIterator iterator(venues);
	size_t j=0;
	while( (pVenue=(GVenue*)iterator())!=0 )
	{
		pComboVenues->InsertString(j,getVenueDescription(pVenue));
		pComboVenues->SetItemData(j, LPARAM(pVenue));
		j++;
	}	
	
	if (mem()->getColVenues().entries()==1)
	{
		pComboVenues->SetCurSel(0);
		fillComboCourtsOwn((GVenue*)pComboVenues->GetItemData(0));
	}
	else
		pComboVenues->SetCurSel(j);
}

void CHScheduleFormView::fillComboCourtsOwn(GVenue* pVenue)
{
	CSchComboBox* pComboCourt=(CSchComboBox*)GetComboCourt();
	
	pComboCourt->ResetContent();

	GCourt * pCourt;
	size_t j=0, k=0;

	RWSet aCourts=CHMemoryDataBase::getColCourts();
	
	GSortedVector gsv=GSortedVector(aCourts,orderCourt);

	for ( j= 0; j < gsv.entries(); j++)
	{
		pCourt = (GCourt *)gsv[j]->getElement();
		if(pCourt->getVenue()==pVenue)	
		{
			pComboCourt->InsertString(k,getCourtDescription(pCourt));
			pComboCourt->SetItemData(k, LPARAM(pCourt));
			k++;
		}
	}
	pComboCourt->InsertString(k, _T("All Tables"));
	pComboCourt->SetItemData(k, LPARAM(0));
	pComboCourt->SetCurSel(k);
}
