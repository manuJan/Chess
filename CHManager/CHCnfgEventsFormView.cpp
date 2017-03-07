/*************************************************************************************
*			© Copyright MSL Software, S.L., 2001
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior wriCHen permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHCnfgEventsFormView.cpp
*   Description	: Chess Configuration of Events
*
*	Author		: Chess Team
*	Date created: 15-12-2005
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
#include "CHCnfgEventsFormView.h"
#include <Sports\CH\Data\CHEvent.h>
#include <Sports\CH\Data\CHInscription.h>
#include <Sports\CH\Data\QCHEvent.h>
#include "resource.h"
#include "CHDefines.h"
#include "CHEventCnfgGUIExtPhases.h"
#include "CHEventCnfgGUIExtRank.h"
#include "CHEventCnfgGUIExtRating.h"
#include "CHPhasesDlg.h"
#include "CHPasswordDlg.h"
#include "CHTeamCompCnfg.h"

#define MENU_TEAM_CONF		EVENTSGUI+33

const int SUBMENUADD	=	1;
const int SUBMENUDEL	=	2;

const int BCK_MENU			=	9002;
const int BCK_MENU_SEL		=	9003;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/// Function that makes a select of the inscription of an event
//selects
static RWBoolean inscriptionsEvent(const RWCollectable *col, const void *param)
{
	CHInscription * pInscription = (CHInscription*) col;
	CHEvent		  * pEvent		 = (CHEvent *)param;
	if(pInscription->getEvent() == pEvent)
		return true;
	return false;	
}
/////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CCHCnfgEventsFormView, CFormView)

CCHCnfgEventsFormView::CCHCnfgEventsFormView()
:GTHCnfgEventsFormView()
,m_pGUIExtPhases(0)
,m_pGUIExtRank(0)
,m_pGUIExtRating(0)
{
	//{{AFX_DATA_INIT(CCHCnfgEventsFormView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CCHCnfgEventsFormView::~CCHCnfgEventsFormView()
{
	if (m_pGUIExtPhases) 
		delete m_pGUIExtPhases;
	
	if(m_pGUIExtRank)
		delete m_pGUIExtRank;

	if(m_pGUIExtRating)
		delete m_pGUIExtRating;
	
}

void CCHCnfgEventsFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCHCnfgEventsFormView, GTHCnfgEventsFormView)
	//{{AFX_MSG_MAP(CCHCnfgEventsFormView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		ON_MESSAGE(UM_EDITCHANGE			, onEditChange)
		ON_MESSAGE(UM_RBUTDOWN,			onRButtonDown)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CCHCnfgEventsFormView::fillColInactiveEvents()
{
	RWDBConnection aConnection = DBApplication::getConnection();
	QCHEvent qInactiveEvents(&aConnection,QEvent::eInactive);
	qInactiveEvents.select(colInactiveEvents);
}

void CCHCnfgEventsFormView::fillComboTypeEvents()
{
	w->delAllItems(LSTCBO_TYPE_EVENT);

	for (short i=1;i<=CHEvent::eBlitz;i++)
	{
		w->addItem(LSTCBO_TYPE_EVENT,i,getTypeEvent(0,i),0,LPARAM(i+1));
	}
}
void CCHCnfgEventsFormView::fillComboTypeModes()
{
	w->delAllItems(LSTCBO_TYPE_MODE);

	for (short i=1;i<=CHEvent::eTeam;i++)
	{
		w->addItem(LSTCBO_TYPE_MODE,i,getTypeMode(0,i),0,LPARAM(i+1));
	}
}

void CCHCnfgEventsFormView::init()
{
	GTHCnfgEventsFormView::init();
	
	w->addBackgroundColor (BCK_MENU,RGB(221,219,221));	// Gris claro
	w->addBackgroundColor (BCK_MENU_SEL,COLOR_GRID_PAR);	// Gris claro

	w->addGridColumn( LSTEVENT, "TypeEvent", JUST_CENTER, 60 );
	w->addGridColumn( LSTEVENT, "Mode", JUST_CENTER, 60 );
	w->addGridColumn( LSTEVENT, "Insc.", JUST_CENTER, 40 );
	w->addGridColumn( LSTEVENT, "ConstRating", JUST_CENTER, 80);
	w->addGridColumn( LSTEVENT, "Bronzes", JUST_CENTER, 60 );
	w->addGridColumn( LSTEVENT, "Team Config", JUST_CENTER, 80 );
	w->addGridColumn( LSTEVENT, "Win points per Bye", JUST_CENTER, 100 );
			
	w->createGridCombo(LSTCBO_TYPE_EVENT,100,BORDER_DOWN,22,IDBCK,IDCOL,IDFNT);
	w->createGridCombo(LSTCBO_TYPE_MODE,100,BORDER_DOWN,22,IDBCK,IDCOL,IDFNT);
	fillComboTypeEvents();
	fillComboTypeModes();

	changeEventGridProperties();
	
	w->addBitmapT(BMP_EVCHECK,  IDB_CH_CHECK);
	w->addBitmapT(BMP_UNCHECK,IDB_CH_UNCHECK);

	// Bitmap Bronze
	w->addBitmapT(BMP_BRONZE,IDB_BRONZE);
	RWWString font =RWWString("Arial",RWWString::ascii);
	
	w->addFont    (FONT_MED	,6,16,1,0,0,0,font);
	w->addColorSet(GREEN,RGB(52,83,23),COLOR_DEFAULT_OFF,COLOR_DEFAULT_HITX,COLOR_DEFAULT_HIGH,COLOR_DEFAULT_L3D,COLOR_DEFAULT_N3D,COLOR_DEFAULT_D3D);

	// Events Information
	const int xIni = 600;
	const int xFin = 900;
	w->createFrame (FRM_EVINF,    CRect(xIni,450,xFin,570),BORDER_DOWN,IDCOL);
	w->createLabel (LBL_EVENTS,   CRect(xIni,435,xFin,445),"Event Information",BORDER_NONE,JUST_LEFT,IDBCK,IDCOL,FONTMAX);
	w->createLabel (LBL_LINEA,    CRect(xIni,447,xFin,450),"",BORDER_NONE,JUST_LEFT,IDBCK_BOX);
	w->createLabel (LBL_SEX,      CRect(xIni+5,456,xFin,476),"",BORDER_NONE,JUST_LEFT,IDBCK,GREEN,FONT_MED);
	w->createLabel (LBL_NINS,     CRect(xIni+5,486,xFin,506),"",BORDER_NONE,JUST_LEFT,IDBCK,GREEN,FONT_MED);
	w->createLabel (LBL_PHASEACT, CRect(xIni+5,516,xFin,536),"",BORDER_NONE,JUST_LEFT,IDBCK,GREEN,FONT_MED);
    w->createLabel (LBL_STARTDATE,CRect(xIni+5,546,xFin,566),"",BORDER_NONE,JUST_LEFT,IDBCK,GREEN,FONT_MED);
	
	w->createButton (BUT_MODIFY_PHASE,CRect(35,410,135,430),"Modify Phase",IDBCK_BUT,IDCOL,FONTMIN);
	
	w->hide(LBL_EVENTS);
	w->hide(LBL_LINEA);
	w->hide(LBL_SEX);
	w->hide(LBL_NINS);
	w->hide(LBL_PHASEACT);
	w->hide(LBL_STARTDATE);
	w->hide(FRM_EVINF);
	w->hide(BUT_MODIFY_PHASE);

	
	// Menu
	w->createMenu(MENU_TEAM_CONF,140,22,IDBCK_GRID,IDCOL,FONTMIN,BCK_MENU_SEL,IDCOL);

	if(!m_pGUIExtRating)
		m_pGUIExtRating = new CHEventCnfgGUIExtRating(this,w,35,420,200,430);
		
}

//////////////////////////////////////////////////////////////////////
// CCHCnfgDisciplineFormView diagnostics
//////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
void CCHCnfgEventsFormView::AssertValid() const
{
	CFormView::AssertValid();
}

void CCHCnfgEventsFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

//////////////////////////////////////////////////////////////////////
// Maping message methods
//////////////////////////////////////////////////////////////////////
LRESULT CCHCnfgEventsFormView::onCursorOverGrid(WPARAM wParam, LPARAM lParam)
{
	int col = LOWORD(lParam);

	if ((col == 3) || (col == 4) || (col == 5) || (col == 7) || (col == 8) || (col == 9))
		return TRUE;

	return GTHCnfgEventsFormView::onCursorOverGrid(wParam,lParam);
}

LRESULT CCHCnfgEventsFormView::onEditChange(WPARAM wParam, LPARAM lParam)
{
	
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);
	
	return 1;
}

BOOL CCHCnfgEventsFormView::onPaintGrid(UINT idGrid,GridItem *gi)
{
	if (!gi) return FALSE;

	switch (idGrid)
	{
		case LSTEVENT:
		{
			if (gi->x == 2)
				paintListEvents(gi);
			else
				GTHCnfgEventsFormView::onPaintGrid(idGrid,gi);
			break;
		}
		default:
			GTHCnfgEventsFormView::onPaintGrid(idGrid,gi);
			break;
	}
	if (m_pGUIExtPhases)
		m_pGUIExtPhases->onPaintGrid(idGrid,gi);

	if (m_pGUIExtRank)
		m_pGUIExtRank->onPaintGrid(idGrid,gi);

	if (m_pGUIExtRating)
		m_pGUIExtRating->onPaintGrid(idGrid,gi);
	
	
	return TRUE;
}

void CCHCnfgEventsFormView::paintListEvents (GridItem *gi)
{
	GTHCnfgEventsFormView::paintListEvents(gi);

	if (!gi) return;

	CHEvent *pEvent=(CHEvent *) gi->lParam;
	if (!pEvent) return;

	// Text		
	switch (gi->x)
	{
		case 2:
		{
			// Status
			GStatus* pStatus = (GStatus *)mem()->findStatus(pEvent->getStatus());
			if (pStatus)
			{
				COLORREF color =CHMemoryDataBase::findColorStatus(pStatus->getStatus());
				w->paintGridText(10,2,pStatus->getLDescription(),IDFNT,color,JUST_LEFT);
			}
			break;
		}
		case 4: // Type Event
			w->paintGridText(gi->rc.Width()/2,2,getTypeEvent(pEvent),JUST_CENTER);
			break;
		
		case 5: // Mode = Individual o Team
			w->paintGridText(gi->rc.Width()/2,2,getTypeMode(pEvent),JUST_CENTER);
			break;

		case 6: // Inscriptions
		{
			RWSet * colInscriptions = (RWSet *) CHMemoryDataBase::getColInscriptions().select
									  (inscriptionsEvent,pEvent);	
			char numberInscriptions[200];
			memset(numberInscriptions,0,sizeof(numberInscriptions));

			if (colInscriptions->entries() > 0)
				sprintf(numberInscriptions,"%d",colInscriptions->entries());

			w->paintGridText(gi->rc.Width()/2,2,numberInscriptions,JUST_CENTER);
			delete colInscriptions;
			break;
		}
		case 7: // Const Rating = K
		{
			w->paintGridText(gi->rc.Width()/2,2,pEvent->getConstRatingStr(),JUST_CENTER);
			break;
		}
		
		case 8: // Bronces
		{
			if (pEvent->getTwoBronces())
			{
				w->paintGridBmp (15,0,BMP_BRONZE);
				w->paintGridBmp (30,0,BMP_BRONZE);
			}
			else
				w->paintGridBmp (22,0,BMP_BRONZE);
			break;
		}
		case 9:
		{
			CString txt=_T("");
			if (pEvent->isTeam())
			{
				CHTeamMatchsCnfg *pTMCnfg=(CHTeamMatchsCnfg *)CHMemoryDataBase::findTeamMatchsCnfg(pEvent);
				if (pTMCnfg)
				{
					txt=pTMCnfg->getLDescription();
					w->paintGridText(gi->rc.Width()/2,0,txt,JUST_CENTER);
				}
			}
			else
			{
				w->paintGridText(gi->rc.Width()/2,0,"N/A",JUST_CENTER);
			}
			
			break;
		}
		case 10:
		{
			w->paintGridText(gi->rc.Width()/2,2,pEvent->getPointsByeStr(),JUST_CENTER);
			break;
		}		
	}
}

void CCHCnfgEventsFormView::onClick (UINT idCtrl,LPARAM lParam)	
{
	switch (idCtrl)
	{
		case LSTEVENT:
		{
			CHEvent *pEvent = (CHEvent *) lParam;
			if (pEvent)
			{
                // Sex
				w->changeTxt(LBL_SEX, pEvent->getLDescription());

                // Number of Inscriptions
				RWSet * colInscriptions = (RWSet *) CHMemoryDataBase::getColInscriptions().select
										  (inscriptionsEvent,pEvent);	
				char numberInscriptions[200];
				memset(numberInscriptions,0,sizeof(numberInscriptions));
				sprintf(numberInscriptions,"Number Of Inscriptions: %d",colInscriptions->entries());
				w->changeTxt(LBL_NINS,numberInscriptions);
				delete colInscriptions;

				RWWString txt = RWWString("Event not started yet",RWWString::ascii);
				CHPhase * pPhase = 0;
	
				for(size_t i=0 ; i<pEvent->getPhasesVector().entries() ; i++)
				{
					pPhase = (CHPhase *)pEvent->getPhasesVector()[i]->getElement();
					if( pPhase && pPhase->getStatus() <= GMemoryDataBase::eRunning )
					{
						txt = pPhase->getLDescription();
						break;
					}
				}
                
                // Actual Phase
				w->changeTxt(LBL_PHASEACT,RWWString("Actual Phase : ",RWWString::ascii) 
											+ txt);

                // Start Date
                if (pEvent->getStartDate().isValid())
    				w->changeTxt(LBL_STARTDATE,"Start Date:  "+pEvent->getStartDate().asString("%d-%m-%Y"));
                else
    				w->changeTxt(LBL_STARTDATE,"Start Date:  Not assigned yet");

                w->show(LBL_SEX);
				w->show(LBL_NINS);
				w->show(LBL_PHASEACT);
				w->show(LBL_STARTDATE);
				w->show(FRM_EVINF);
				w->show(LBL_EVENTS);
				w->show(LBL_LINEA);
				w->show(BUT_MODIFY_PHASE);
								

				selectEvent(pEvent);
			}
			else
			{
				w->changeTxt(LBL_SEX, "");
				w->changeTxt(LBL_NINS,"");
				w->changeTxt(LBL_PHASEACT,"");
				w->changeTxt(LBL_STARTDATE,"");

				w->hide(LBL_SEX);
				w->hide(LBL_NINS);
				w->hide(LBL_PHASEACT);
				w->hide(LBL_STARTDATE);
				w->hide(FRM_EVINF);
				w->hide(BUT_MODIFY_PHASE);
				w->show(LBL_EVENTS);
				w->show(LBL_LINEA);
								
			}
			break;
		}
		case BUT_MODIFY_PHASE:
		{
			CHPasswordDlg dlgPassword(this);
			dlgPassword.DoModal();
			if(dlgPassword.getPressed())
			{
				CHPhasesDlg dlgPhase(this,(CHPhase*) w->getSelectedLParam(LSTPHASES));
				dlgPhase.DoModal();
				w->redraw(LSTPHASES,FALSE);
			}
			break;	
		}
		case MENU_TEAM_CONF:
		{
			// Add Team Configuration
			if (lParam == SUBMENUADD)		
			{
				SendMessage(UM_DBLCLICK,LSTEVENT,9);
			}
			// Del Team Configuration
			if (lParam == SUBMENUDEL)		
			{
				CHEvent  * pEvent      = (CHEvent*)w->getGridLParam(LSTEVENT,w->getSelectedLine(LSTEVENT)); // Lines
				if(pEvent)
				{
					pEvent->setIdTeamMatchsCnfg(0);
					saveEvent(pEvent);
				}
			}
			w->redrawLine(LSTEVENT,w->getSelectedLine(LSTEVENT));
			break;
		}
	}
	GTHCnfgEventsFormView::onClick (idCtrl,lParam);

	if (m_pGUIExtRank)
			m_pGUIExtRank->onClick(idCtrl,0,0,lParam);

	if (m_pGUIExtRating)
			m_pGUIExtRating->onClick(idCtrl,0,0,lParam);
	
}


void CCHCnfgEventsFormView::onDblClick(UINT idGrid,int x,int y,LPARAM lParam)
{
	GTHCnfgEventsFormView::onDblClick(idGrid,x,y,lParam);

	if (idGrid==LSTEVENT)
	{

		CHEvent  * pEvent      = (CHEvent*)w->getGridLParam(idGrid,w->getSelectedLine(LSTEVENT)); // Lines
		if(pEvent && !pEvent->isEnable())
			return;


		switch (x)  // Columns
		{
			case 3: // Modality (Repaint grid Phases)
				{
					m_pGUIExtPhases->SendMessage(UM_SELECT_EVENT,0,(LPARAM)pEvent);
					break;
				}
			case 4: // Type Event
				{
					if(pEvent->getStatus()<CHMemoryDataBase::eSchedulled)
					{
						showComboTypeEvent(x,y,pEvent);
						w->redrawLine(LSTEVENT,y,y);
					}
					break;
				}
			case 5: // Type Mode
				{
					if(pEvent->getStatus()<CHMemoryDataBase::eSchedulled)
					{
						showComboTypeMode(x,y,pEvent);
						w->redrawLine(LSTEVENT,y,y);
					}
					break;
				}
			
			case 7: // Const Rating
			{
				
				RWCString temp = w->editGridCell(LSTEVENT,x,y,pEvent->getConstRatingStr());

				if (strcmp(pEvent->getConstRatingStr(),temp))
				{
					pEvent->setConstRating(short(atof(temp)));
					w->redrawLine(LSTEVENT,y);
					APP::out(TRN_EVENT_ENABLE_DISABLE);
					APP::out(*pEvent,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);		
					APP::out();
				}
				
			}
			break;
			case 8: // Two Bronces
			{
				CString txt = "";
				

				if (pEvent->isEnable() 
					&& pEvent->getStatus()<GMemoryDataBase::eSchedulled)
				{
					pEvent->setTwoBronces(!pEvent->getTwoBronces());
					w->redrawLine(LSTEVENT,y);
					APP::out(TRN_EVENT_ENABLE_DISABLE);
					APP::out(*pEvent,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);		
					APP::out();
				}
			}
			break;
			//Team configuration
			case 9:
			{
				if (pEvent->isTeam())
				{
					CHTeamMatchsCnfg *aux=new CHTeamMatchsCnfg();
					CHTeamCompCnfg cDlg(aux,this,pEvent->getIdTeamMatchsCnfg());
					int value=cDlg.DoModal();
					if (value==IDOK)
					{
						CHTeamMatchsCnfg *pTMCnfg=cDlg.getTeamMatchsCnfg();
						if (pEvent->getIdTeamMatchsCnfg()!=pTMCnfg->getId())
						{
							pEvent->setIdTeamMatchsCnfg(pTMCnfg->getId());
							saveEvent(pEvent);
						}
					}
					if (!mem()->findTeamMatchsCnfg(pEvent))
					{
						pEvent->setIdTeamMatchsCnfg(0);
						saveEvent(pEvent);
					}
					w->redrawLine(LSTEVENT,y);
				}
				else
				{
					::msg("Error¡¡","Not Applicable in individual events.",ICO_W,MSG_OK);
				}
				break;
			}
			case 10: // Points Bye
			{
				
				RWCString temp = w->editGridCell(LSTEVENT,x,y,pEvent->getPointsByeStr());

				if (strcmp(pEvent->getPointsByeStr(),temp))
				{
					pEvent->setPointsBye(atof(temp));
					w->redrawLine(LSTEVENT,y);
					APP::out(TRN_EVENT_ENABLE_DISABLE);
					APP::out(*pEvent,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);		
					APP::out();
				}
				
			}
		}
	}
	if(idGrid==LSTPHASES)
	{
		 if (m_pGUIExtPhases)
			m_pGUIExtPhases->onDblClick(idGrid,x,y,lParam);
			
	}	
		
	if(idGrid==LSTRANK)
	{
		if (m_pGUIExtRank)
			m_pGUIExtRank->onDblClick(idGrid,x,y,lParam);
	}

	if(idGrid==LSTRATINGS)
	{
		if (m_pGUIExtRating)
			m_pGUIExtRating->onDblClick(idGrid,x,y,lParam);
	}
	
}

LRESULT CCHCnfgEventsFormView::onRButtonDown(WPARAM wParam, LPARAM lParam)
{
 	CHEvent* pEventAux=(CHEvent*)w->getSelectedLParam(LSTEVENT);	// Bout seleccionado..

    int count = w->getSelectedCount(LSTEVENT);

    
	WORD x=LOWORD(lParam);	

	if (wParam==LSTEVENT)
	{
		switch (x)
		{		
			
			case 9: // Asignación de configuracion de teams
				assignTeamConf(pEventAux, count);
				break;
						
		}
	}

	return TRUE;	
}
// Asignación de configuracion de teams
void CCHCnfgEventsFormView::assignTeamConf(CHEvent* pEventAux,int nSelected)
{
	if (!pEventAux || nSelected!=1)
		return;

	if(!pEventAux->isTeam())
		return;

	// muestra el menu. Ir al onClick a recoger la seleccion...
	w->delMenuItems(MENU_TEAM_CONF);
	w->addMenuItem(MENU_TEAM_CONF,SUBMENUADD,0," Add Team Configuration ",SUBMENUADD);
	w->addMenuItem(MENU_TEAM_CONF,SUBMENUDEL,0," Delete Team Configuration ",SUBMENUDEL);
	w->showMenu(MENU_TEAM_CONF);	
}
void CCHCnfgEventsFormView::selectEvent(CHEvent *pEvent)
{ 
	if (!pEvent) return; 
	if (!m_pGUIExtPhases)
		m_pGUIExtPhases = new CHEventCnfgGUIExtPhases(this,w,35,260,200,270,pEvent);
	m_pGUIExtPhases->SendMessage(UM_SELECT_EVENT,0,(LPARAM)pEvent);
	

	if(!m_pGUIExtRank)
		m_pGUIExtRank = new CHEventCnfgGUIExtRank(this,w,600,260,900,270,pEvent);
	m_pGUIExtRank->SendMessage(UM_SELECT_EVENT,0,(LPARAM)pEvent);
}
void CCHCnfgEventsFormView::changeEventGridProperties()
{
	w->chgGridColumnWidth(LSTEVENT,0, 50);
	w->chgGridColumnWidth(LSTEVENT,1,135);
	w->chgGridColumnWidth(LSTEVENT,2, 70);
	//w->chgGridColumnWidth(LSTEVENT,3, 140);

		
	w->changeRect(LBLAUX15,CRect(30, 15,105,25));
	w->changeRect(LBLAUX14,CRect(30,27,970,30));
	w->changeRect(LSTEVENT,CRect(30,30,970,252));
	
}
RWBoolean CCHCnfgEventsFormView::canChangeModality(GTHEvent * pEvent)
{
	if (pEvent->getStatus() < CHMemoryDataBase::eSchedulled)
	{	
		//fillComboModalities((CHEvent*)pEvent);
		return TRUE;
	
	}
	return FALSE;
}

RWCString CCHCnfgEventsFormView::getTypeEvent(CHEvent *pEvent,short typeDisc)
{
	
	short type=0;
	if(pEvent)
		 type=pEvent->getTypeEvent();
	else type=typeDisc;

	switch(type)
	{
		case CHEvent::eNone:
			return "None";
			break;
		case CHEvent::eClassic:
			return "Classic";
			break;
		case CHEvent::eRapid:
			return "Rapid";
			break;
		case CHEvent::eBlitz:
			return "Blitz";
			break;
		default:
			return "Unknown";
			break;
	}
	return NULLRWSTRING;
}


void CCHCnfgEventsFormView::showComboTypeEvent(int x,int y,CHEvent *pEvent)
{
	w->selectItem(LSTCBO_TYPE_EVENT,(LPARAM)(pEvent->getTypeEvent()+1));
	
	short typeEvent=0;
	typeEvent=short(w->showGridCombo(LSTEVENT,LSTCBO_TYPE_EVENT,x,y));


	if(typeEvent && (typeEvent-1)!=pEvent->getTypeEvent())
	{
		pEvent->setTypeEvent(short(typeEvent-1));
		saveEvent(pEvent);
		
	}
}
RWCString CCHCnfgEventsFormView::getTypeMode(CHEvent *pEvent,short typeMode)
{
	
	short type=0;
	if(pEvent)
		 type=pEvent->getMode();
	else type=typeMode;

	switch(type)
	{
		case CHEvent::eNoneMode:
			return "None";
			break;
		case CHEvent::eIndividual:
			return "Individual";
			break;
		case CHEvent::eTeam:
			return "Team";
			break;
		default:
			return "Unknown";
			break;
	}
	return NULLRWSTRING;
}


void CCHCnfgEventsFormView::showComboTypeMode(int x,int y,CHEvent *pEvent)
{
	w->selectItem(LSTCBO_TYPE_MODE,(LPARAM)(pEvent->getMode()+1));
	
	short typeMode=0;
	typeMode=short(w->showGridCombo(LSTEVENT,LSTCBO_TYPE_MODE,x,y));


	if(typeMode && (typeMode-1)!=pEvent->getMode())
	{
		pEvent->setMode(short(typeMode-1));
		saveEvent(pEvent);
		
	}
}
void CCHCnfgEventsFormView::saveEvent(CHEvent *pEvent)
{
	APP::out(TRN_CH_EVENT_CHANGE);
	APP::out(*pEvent,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
	APP::out();		
}

