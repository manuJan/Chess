// CHEventControlFormView.cpp: implementation of the CHEventControlFormView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CHEventControlFormView.h"
#include "CHEventControlTable.h"
#include "CHEventControlMultiScrollBar.h"
#include "CHDefines.h"
#include "CHMsgDefines.h"
#include "CHReadFile.h"
#include "CHPgnMatchesDlg.h"
#include "Resource.h"

#include <core\TH\GTHHistoric.h>

#include <SPORTS/CH/REPORTS/CHPgnMatch.h>
#include <SPORTS/CH/REPORTS/CHReportDefines.h>
#include <SPORTS/CH/REPORTS/CHRC74.h>
#include <SPORTS/CH/REPORTS/CHRC75.h>

static
int orderMatchRoundDateTime(const GVectorElement** a, const GVectorElement** b)
{
	CHMatch *pA=(CHMatch *)(*a)->getElement();
	CHMatch *pB=(CHMatch *)(*b)->getElement();

	int order=pA->getRound()-pB->getRound();
	if (order)
		return order;

	order = strcmp(	pA->getStartDateAsString("%Y%m%d"),pB->getStartDateAsString("%Y%m%d"));
	if( order )
		return order;
	
	// Order by Match Start Time.
	order = strcmp(pA->getStartTimeAsString("%H:%M"),pB->getStartTimeAsString("%H:%M"));
	if (order)
		return order;
	
	order=pA->getMatchNumber()-pB->getMatchNumber();
	if (order)
		return order;

	return strcmp(pA->getKey(),pB->getKey());
}
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
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CHEventControlFormView, CFormView)

CHEventControlFormView::CHEventControlFormView()
:vMatchesInPlay(orderMatchRoundDateTime)
,pSelMatch(0)
,m_pMultiScrollBar(0)
,eventControlOp((CHMemoryDataBase*)mem())
{

}

CHEventControlFormView::~CHEventControlFormView()
{
	if (m_pMultiScrollBar)
	{
		m_pMultiScrollBar->DestroyWindow();
		delete m_pMultiScrollBar;
		m_pMultiScrollBar=0;
	}
}	

BEGIN_MESSAGE_MAP(CHEventControlFormView, GTHEventControlFormView)
	//{{AFX_MSG_MAP(CHEventControlFormView)
		ON_MESSAGE(UM_ECT_SHOW_MATCHES,onShowMatches)
		ON_MESSAGE(UM_DRAG,	onGridDrag)
		ON_MESSAGE(UM_DROP,	onGridDrop)	
		ON_MESSAGE(UM_ECT_EVENT,onEvent)
		ON_MESSAGE(UM_ECT_SETMATCH,onSetMatch)
		ON_MESSAGE(UM_ECT_CHANGE_STATUS,onChangeStatus)
		ON_MESSAGE(UM_ECT_CANCEL_EVENTS,onCancelEvents)
		ON_MESSAGE(UM_ECT_TOOUTCOL,onOutCol)
		ON_MESSAGE(UM_ECT_TOSEND,onSend)
		ON_MESSAGE(UM_PROCESS_MOVEMENT,onProcessMovement)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CHEventControlFormView::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	CHEventControlTable* pBoard=0;
	POSITION pos;
	CString buffer;		
	if (!obListBoards.IsEmpty())
	{
		for( pos = obListBoards.GetStartPosition(); pos != NULL; )
		{
			obListBoards.GetNextAssoc( pos, buffer, (CObject*&)pBoard);
			if (pBoard)
				pBoard->DestroyWindow();							
		}
	}
	obListBoards.RemoveAll();

	if (m_pMultiScrollBar)
	{
		m_pMultiScrollBar->DestroyWindow();
		delete m_pMultiScrollBar;
		m_pMultiScrollBar=0;
	}

	return GTHEventControlFormView::DestroyWindow();
}

//Plays and Data
	
BOOL CHEventControlFormView::infoCurrentPlayStart(long idPlay, RWOrdered m_datas)
{
	CHMatch* pMatch = (CHMatch*)getCurrentMatch();
	if (pMatch)
	{
		CHEventControlTable* pBoard = findBoard(pMatch);
		if (pBoard)
		{
			return pBoard->infoCurrentPlayStart(idPlay,m_datas);
		}
	}

	return FALSE;
}

void CHEventControlFormView::infoHistoricEnd(int posHist, BOOL isDo,action histAction)
{
	CHMatch* pMatch = (CHMatch*)getCurrentMatch();
	if (pMatch)
	{
		CHEventControlTable* pBoard = findBoard(pMatch);
		if (pBoard)
		{
			pBoard->infoHistoricEnd(posHist,isDo,histAction);				
		}
	}			
}

BOOL CHEventControlFormView::infoCurrentPlayEnd(long idPlay,RWOrdered m_datas)
{
	CHMatch* pMatch = (CHMatch*)getCurrentMatch();
	if (!pMatch)
		return FALSE;

	CHMatchResult* pWhite = pMatch->getWhite();
	CHMatchResult* pBlack = pMatch->getBlack();
	if (!pWhite && !pBlack)
		return FALSE;

	// Poner resultado al partido 
	if (idPlay == PLAY_WHITE_WINNER)
	{
		pWhite->setPoints(WIN_POINTS);
		pBlack->setPoints(LOST_POINTS);
	}
	else if (idPlay == PLAY_BLACK_WINNER)				
	{
		pWhite->setPoints(LOST_POINTS);
		pBlack->setPoints(WIN_POINTS);		
	}
	else if (idPlay == PLAY_DRAW)		
	{
		pWhite->setPoints(DRAW_POINTS);
		pBlack->setPoints(DRAW_POINTS);		
	}
	else if (idPlay == PLAY_WHITE_WINNER_F)
	{
		pWhite->setPoints(WIN_POINTS);
		pBlack->setPoints(LOST_POINTS);
	}	
	else if (idPlay == PLAY_BLACK_WINNER_F)					
	{
		pWhite->setPoints(LOST_POINTS);
		pBlack->setPoints(WIN_POINTS);		
	}
	else if (idPlay == PLAY_DRAW_F)					
	{
		pWhite->setPoints(LOST_POINTS);		
		pBlack->setPoints(LOST_POINTS);
	}

	toOutCol(pWhite);
	toOutCol(pBlack);
	
	send(TRN_SET_EC_HISTORIC);

	return TRUE;
}

void CHEventControlFormView::infoHistoricRecalculation(int posHist,action typeAction)
{
	if (typeAction==eDelete)
	{
		CHMatch* pMatch = (CHMatch*)getCurrentMatch();
		if (pMatch)
		{
			CHEventControlTable* pBoard = findBoard(pMatch);
			if (pBoard)
			{
				pBoard->SendMessage(UM_ECT_UNDOMOVEMENT,(WPARAM)posHist,(LPARAM)pMatch);				
			}
		}	
	}
}

void CHEventControlFormView::infoPlayEnd()
{

}

long CHEventControlFormView::requestData(long idData,long idEvent,LPARAM lParam)
{
	switch (idData)
	{
	case DATA_PLAYER:
		return getDataPlayer(idEvent,lParam);
		break;
	case DATA_PIECE:
		return getDataPiece(idEvent,lParam);
		break;
	case DATA_NUMPLAY:
		return getDataNumPlay(idEvent,lParam);
		break;
	case DATA_OLDPOSI:
		return getDataOldPosi(idEvent,lParam);
		break;
	case DATA_NEWPOSI:
		return getDataNewPosi(idEvent,lParam);
		break;
	case DATA_RESULT:
		return getDataResult(idEvent,lParam);
		break;
	case DATA_EATPIECE:
		return getDataEatPiece(idEvent,lParam);
		break;
	case DATA_GENERAL_PURPOSE:
		return getDataGeneralPurpose(idEvent,lParam);
	}

	return PROCESS_CANCELED;
}

long CHEventControlFormView::getDataPlayer(long idEvent, LPARAM lParam)
{
	CHEventControlTable* pBoard = (CHEventControlTable*)lParam;
	if (!pBoard)
		return 0;

	TMOVEMENT* pMovement = pBoard->getLastMovement();
	if (pMovement)
		return pMovement->Color;		
	
	return PROCESS_CANCELED;
}

long CHEventControlFormView::getDataPiece(long idEvent, LPARAM lParam)
{
	CHEventControlTable* pBoard = (CHEventControlTable*)lParam;
	if (!pBoard)
		return 0;

	TMOVEMENT* pMovement = pBoard->getLastMovement();
	if (pMovement)
	{
		return pMovement->Piece;
	}
	return PROCESS_CANCELED;
}

long CHEventControlFormView::getDataNumPlay(long idEvent, LPARAM lParam)
{
	CHEventControlTable* pBoard = (CHEventControlTable*)lParam;
	if (!pBoard)
		return 0;

	CHMatch* pMatch = pBoard->getMatch();
	if (pMatch)
	{
		return pMatch->getNextPlayNumber();
	}
	
	return PROCESS_CANCELED;
}

long CHEventControlFormView::getDataOldPosi(long idEvent, LPARAM lParam)
{
	CHEventControlTable* pBoard = (CHEventControlTable*)lParam;
	if (!pBoard)
		return 0;

	TMOVEMENT* pMovement = pBoard->getLastMovement();
	if (pMovement)
	{
		return pMovement->oldPosi;
	}
	
	return PROCESS_CANCELED;
}

long CHEventControlFormView::getDataNewPosi(long idEvent, LPARAM lParam)
{
	CHEventControlTable* pBoard = (CHEventControlTable*)lParam;
	if (!pBoard)
		return 0;

	TMOVEMENT* pMovement = pBoard->getLastMovement();
	if (pMovement)
	{
		return pMovement->newPosi;
	}
	
	return PROCESS_CANCELED;
}

long CHEventControlFormView::getDataResult(long idEvent, LPARAM lParam)
{
	CHEventControlTable* pBoard = (CHEventControlTable*)lParam;
	if (!pBoard)
		return 0;

	TMOVEMENT* pMovement = pBoard->getLastMovement();
	if (pMovement)
	{
		return pMovement->result;
	}
	return PROCESS_CANCELED;
}

long CHEventControlFormView::getDataEatPiece(long idEvent, LPARAM lParam)
{
	CHEventControlTable* pBoard = (CHEventControlTable*)lParam;
	if (!pBoard)
		return 0;

	TMOVEMENT* pMovement = pBoard->getLastMovement();
	if (pMovement)
	{
		return pMovement->eatedPiece;
	}

	return PROCESS_CANCELED;
}

long CHEventControlFormView::getDataGeneralPurpose(long idEvent, LPARAM lParam)
{
	CHEventControlTable* pBoard = (CHEventControlTable*)lParam;
	if (!pBoard)
		return 0;

	TMOVEMENT* pMovement = pBoard->getLastMovement();
	if (pMovement)
		return pMovement->checkSameMov;

	return 0;
}

GData* CHEventControlFormView::requestStatistic(long idPlay,const GTHECStatistic &st,int posHist,RWBoolean isDo/*=TRUE*/)
{

	return 0;
}

void CHEventControlFormView::init()
{
	GTHEventControlFormView::init();

	w->hide(6);
	w->hide(LBL_PLAY);
	w->hide(CONFIGURATOR);
	w->hide(7);
	w->destroyControl(LBL_POOL );
	w->destroyControl(LBL_MATCH);
	w->destroyControl(           1);
	w->destroyControl(LBL_STATUS  );
	w->destroyControl(           2);
	w->destroyControl(           3);
	w->destroyControl(LBL_EVPH    );
	w->destroyControl(           4);
	w->destroyControl(LBL_SDST    );
	w->destroyControl(LBL_POOL    );
	w->destroyControl(LBL_MATCH   );
	w->destroyControl(           5);

	for (short k=0; k<8; k++)
	{		
		w->hide(LED_EVENT+k);
		w->hide(LBL_EVENT+k);
		w->hide(LBL_AUX+k);
	}

	//Launch
	w->createLabelEx(CH_LAUNCH_MATCHES,CRect(10, 62,100,77),"Launch Matches...",BORDER_NONE,JUST_LEFT,IDBCK,BLUE,IDFNTX,IDBCK,RED,IDFNTX);
	w->enable(CH_LAUNCH_MATCHES,false);

	w->addBitmapT(BMP_W_PAWN	,IDB_WPAWN);
	w->addBitmapT(BMP_W_ROOK	,IDB_WROOK);
	w->addBitmapT(BMP_W_BISHOP	,IDB_WBISHOP);
	w->addBitmapT(BMP_W_KNIGHT	,IDB_WKNIGHT);
	w->addBitmapT(BMP_W_QUEEN	,IDB_WQUEEN);
	w->addBitmapT(BMP_W_KING	,IDB_WKING);

	w->addBitmapT(BMP_B_PAWN	,IDB_BPAWN);
	w->addBitmapT(BMP_B_ROOK	,IDB_BROOK);
	w->addBitmapT(BMP_B_BISHOP	,IDB_BBISHOP);
	w->addBitmapT(BMP_B_KNIGHT	,IDB_BKNIGHT);
	w->addBitmapT(BMP_B_QUEEN	,IDB_BQUEEN);
	w->addBitmapT(BMP_B_KING	,IDB_BKING);

	w->addBitmapT(BMP_W_ROOK_S	,IDB_WROOK_S);
	w->addBitmapT(BMP_W_BISHOP_S,IDB_WBISHOP_S);
	w->addBitmapT(BMP_W_KNIGHT_S,IDB_WKNIGHT_S);
	w->addBitmapT(BMP_W_QUEEN_S ,IDB_WQUEEN_S);
	w->addBitmapT(BMP_W_KING_S	,IDB_WKING_S);

	w->addBitmapT(BMP_B_ROOK_S	,IDB_BROOK_S);
	w->addBitmapT(BMP_B_BISHOP_S,IDB_BBISHOP_S);
	w->addBitmapT(BMP_B_KNIGHT_S,IDB_BKNIGHT_S);
	w->addBitmapT(BMP_B_QUEEN_S ,IDB_BQUEEN_S);
	w->addBitmapT(BMP_B_KING_S	,IDB_BKING_S);

	//fillReports();
}

void CHEventControlFormView::fillReports()
{	
	// Opciones del menu de Reports.
	APP::addReport(1,0,RC74_NAME,RC74,CH_EVENTCONTROL_FORM);
	APP::addReport(2,0,RC75_NAME,RC75,CH_EVENTCONTROL_FORM);
		
	
	//Phases
	GSortedVector vPhases(CHMemoryDataBase::getColPhases(),orderPhasesByEvents);
	CHPhase * pPhase=0;
	short nRoundC74=3000,nRoundC75=6000;
	char tmp[50];
	for(size_t i=0 ; i<vPhases.entries() ; i++)
	{
		pPhase=(CHPhase*)vPhases[i]->getElement();
				
		RWCString phaseDesc=pPhase->getEventLDescription().toAscii() + " " + pPhase->getLDescription().toAscii();
		APP::addReport(RC74+i,1,phaseDesc,RC74,CH_EVENTCONTROL_FORM,LPARAM(pPhase),0);
		APP::addReport(RC75+i,2,phaseDesc,RC75,CH_EVENTCONTROL_FORM,LPARAM(pPhase),0);
		
		for(size_t j=0;short(j)<pPhase->getNumRounds();j++)
		{
			sprintf(tmp,"Round %d",j+1);
			APP::addReport(RC74+nRoundC74,RC74+i,tmp,RC74,CH_EVENTCONTROL_FORM,LPARAM(pPhase),LPARAM(j+1));
			APP::addReport(RC75+nRoundC75,RC75+i,tmp,RC75,CH_EVENTCONTROL_FORM,LPARAM(pPhase),LPARAM(j+1));
			nRoundC74++;
			nRoundC75++;
		}
		APP::addReport(RC74+nRoundC74,RC74+i,"All Rounds",RC74,CH_EVENTCONTROL_FORM,LPARAM(pPhase),LPARAM(ALL_ROUNDS));
		nRoundC74++;
	}
}

BOOL CHEventControlFormView::exit() 
{
	return true;
}

void CHEventControlFormView::showAreaSelectMatch(BOOL show)
{
	GTHEventControlFormView::showAreaSelectMatch(show);

	// For Multiselection
	w->multipleSelection(GRID_MATCH,true);
	w->changeCellHeight(GRID_MATCH,66);

	w->changeRect(LBL_SELECT_EVENT,CRect(5,515,55,534));
	w->changeRect(CMB_SELECT_EVENT,CRect(55,515,195,635));		

	w->changeRect(LBL_SELECT_PHASE,CRect(5,545,55,565));
	w->changeRect(CMB_SELECT_PHASE,CRect(55,545,195,645));		

	w->changeRect(5,CRect(5,58,245,61));
	
	if (show)
	{
		w->destroyControl(CH_LBL_SAVE_PGN);
		w->destroyControl(CH_LBL_LOAD_PGN);	
	}
	else
	{
		w->createLabelEx(CH_LBL_SAVE_PGN,CRect(960,20,1010,40),"Save Pgn",BORDER_NONE,JUST_CENTER,IDBCK,BLUE,IDFNTX,IDBCK,RED,IDFNTX);
		w->createLabelEx(CH_LBL_LOAD_PGN,CRect(960,40,1010,60),"Load Pgn",BORDER_NONE,JUST_CENTER,IDBCK,BLUE,IDFNTX,IDBCK,RED,IDFNTX);
	}
}

void CHEventControlFormView::showAreaHistoric(BOOL show)
{
	GTHEventControlFormView::showAreaHistoric(show);

	w->hide(LBL_INFO_GRID);
	w->hide(LBL_INFO_MODE);
	w->hide(CHK_DEL_HISTORIC);

	if (!show)
	{
		// Me cargo los dos
		w->destroyControl(getIdGridHistoric());
		//w->hide(getIdGridHistoric());		
	}
	else
	{
		// Creo de nuevo el mio
		//w->show();
		createGrid(getIdGridHistoric());
	}

	//w->destroyControl();
	
	UNREFERENCED_PARAMETER(show);
}

bool CHEventControlFormView::matchView(GTHMatch * pMatch)
{
	if ( ((CHMatch*)pMatch)->hasCompetitors() && ((CHMatch*)pMatch)->getStatus()>=CHMemoryDataBase::eSchedulled)
		return true;
	return false;
}

void CHEventControlFormView::onClick(UINT idCtrl,LPARAM lParam)
{
	switch (idCtrl)
	{
		case GRID_MATCH://Launch Matches
		{
			pSelMatch = (CHMatch *)lParam;
			w->enable(CH_LAUNCH_MATCHES,true);
		}
		break;
		case CH_LAUNCH_MATCHES://Launch Matches
		{
			if (launchMatches())
			{
				showDataEntryArea(true);
				w->changeRect(5,CRect(5,78,245,81));
			}
		}
		break;
		case CHANGE_MATCH:
		{
			pSelMatch = 0;
			destroyControls();

			showDataEntryArea(false);
			GTHEventControlFormView::onClick(idCtrl, lParam);
		}
		break;
		case CH_LBL_SAVE_PGN:
		{
			savePgn();
		}
		break;
		case CH_LBL_LOAD_PGN:
		{
			loadPgn();
		}
		break;
	}

	CHEventControlTable* pBoard=0;
	POSITION pos;
	CString buffer;		
	BOOL ret=false;
	if (!obListBoards.IsEmpty())
	{
		for( pos = obListBoards.GetStartPosition(); pos != NULL; )
		{
			obListBoards.GetNextAssoc( pos, buffer, (CObject*&)pBoard);
			pBoard->onClick(idCtrl,lParam);
		}
	}


	GTHEventControlFormView::onClick(idCtrl, lParam);
}
void CHEventControlFormView::onDblClick(UINT idGrid,int x,int y,LPARAM lParam)
{	
	switch (idGrid)
	{
		case GRID_MATCH://Launch Matches
		{
			if (launchMatches())
			{
				showDataEntryArea(true);	
				w->changeRect(5,CRect(5,78,245,81));						
			}
			break;
		}
	}
	GTHEventControlFormView::onDblClick(idGrid, x, y, lParam);
}

BOOL CHEventControlFormView::onPaintGrid(UINT idGrid,GridItem *gi)
{
	GTHEventControlFormView::onPaintGrid(idGrid,gi);

	CHEventControlTable* pBoard=0;
	POSITION pos;
	CString buffer;		
	BOOL ret=false;
	if (!obListBoards.IsEmpty())
	{
		for( pos = obListBoards.GetStartPosition(); pos != NULL; )
		{
			obListBoards.GetNextAssoc( pos, buffer, (CObject*&)pBoard);
			if (pBoard->onPaintGrid(idGrid,gi))
				return TRUE;
		}
	}
	return FALSE;
}

LRESULT CHEventControlFormView::onGridDrag(WPARAM wParam, LPARAM lParam)
{
	CHEventControlTable* pBoard=0;
	POSITION pos;
	CString buffer;		
	BOOL ret=false;
	if (!obListBoards.IsEmpty())
	{
		for( pos = obListBoards.GetStartPosition(); pos != NULL; )
		{
			obListBoards.GetNextAssoc( pos, buffer, (CObject*&)pBoard);
			if (pBoard->onGridDrag(wParam,lParam))
				return 1;
		}
	}

	return 0;
}

void CHEventControlFormView::onGridDrop(WPARAM wParam, LPARAM lParam)
{
	CHEventControlTable* pBoard=0;
	POSITION pos;
	CString buffer;		
	BOOL ret=false;
	if (!obListBoards.IsEmpty())
	{
		for( pos = obListBoards.GetStartPosition(); pos != NULL; )
		{
			obListBoards.GetNextAssoc( pos, buffer, (CObject*&)pBoard);
			if (pBoard->onGridDrop(wParam,lParam))
				return;
		}
	}	
}

LRESULT	CHEventControlFormView::onSetMatch(WPARAM wParam, LPARAM lParam)
{
	CHMatch* pMatch = (CHMatch*)wParam;
	if (pMatch)
	{
		setCurrentMatch(pMatch,false);
	}

	return 0;
}

LRESULT	CHEventControlFormView::onCancelEvents	(WPARAM wParam, LPARAM lParam)
{
	cancelEvents();
	return 0;
}

LRESULT	CHEventControlFormView::onEvent(WPARAM wParam, LPARAM lParam)
{	
	CHEventControlTable* pBoard = (CHEventControlTable*)lParam;
	if (!pBoard)
		return 0;

	CHMatch* pMatch = pBoard->getMatch();
	if (!pMatch)
		return 0;

	long idEvent = long(wParam);

	setCurrentMatch(pMatch);

	if (pBoard)
	{
		switch (idEvent)
		{
			case EV_MOVE:
			case EV_SHORT_CASTLING:
			case EV_LONG_CASTLING:
			{
				if (pBoard->getLastMovement())
				{
					processData(DATA_PLAYER,wParam,lParam);
					processData(DATA_NUMPLAY,wParam,lParam);
					processData(DATA_PIECE,wParam,lParam);
					processData(DATA_OLDPOSI,wParam,lParam);
					processData(DATA_NEWPOSI,wParam,lParam);
					processData(DATA_RESULT,wParam,lParam);
					processData(DATA_EATPIECE,wParam,lParam);
					processData(DATA_GENERAL_PURPOSE,wParam,lParam);
				}
			}
			break;			
		}


		processEvent(wParam,lParam);
		pBoard->SendMessage(UM_ECT_REDRAW);
	}
	return 0;
}

LRESULT CHEventControlFormView::onShowMatches(WPARAM wParam, LPARAM lParam)
{
	showMatchesInPlay();
	return 0;
	UNREFERENCED_PARAMETER(lParam);
	UNREFERENCED_PARAMETER(wParam);
}

LRESULT	CHEventControlFormView::onProcessMovement(WPARAM wParam, LPARAM lParam)
{
	CHMatch* pMatch = (CHMatch*)wParam;
	TMOVEMENT *pMovement = (TMOVEMENT*)lParam;

	CHEventControlTable *pBoard = findBoard(pMatch);
	if (pBoard)
	{
		pBoard->SendMessage(UM_PROCESS_MOVEMENT,wParam,lParam);
	}

	return 0;
}

LRESULT CHEventControlFormView::onChangeStatus(WPARAM wParam, LPARAM lParam)
{
	CHMatch* pMatch = (CHMatch*)wParam;
	return 0;
}

LRESULT	CHEventControlFormView::onOutCol(WPARAM wParam, LPARAM lParam)
{
	toOutCol((GData*)wParam);
	return 0;
}
	

LRESULT	CHEventControlFormView::onSend(WPARAM wParam, LPARAM lParam)
{
	send(wParam);
	return 0;
}


void CHEventControlFormView::showDataEntryArea(BOOL show)
{
	if (show)
	{
		w->hide(CH_LAUNCH_MATCHES);
	}
	else
	{
		w->show(CH_LAUNCH_MATCHES);
		w->enable(CH_LAUNCH_MATCHES,false);
		
	}
}

void CHEventControlFormView::destroyControls()
{
	for (size_t i=0;i<vMatchesInPlay.entries();i++)
		hideGUI(int(i));

	if (m_pMultiScrollBar)
	{
		m_pMultiScrollBar->DestroyWindow();
		delete m_pMultiScrollBar;
		m_pMultiScrollBar=0;
	}
}

BOOL CHEventControlFormView::launchMatches()
{
	int entries = fillMatchesInPlayVector();

	if (!entries)
	{
		::msg("Data Entry","Select a Match First!!!",ICO_W,MSG_OK);	
		return 0;
	}

	//Visualizo el primero del vector
	if(vMatchesInPlay.entries())
	{
		pSelMatch = (CHMatch *)vMatchesInPlay[0]->getElement();
		GTHEventControlFormView::onDblClick(GRID_MATCH, 0, 0, LPARAM(pSelMatch));
	}

	showMatchesInPlay();
	
	return entries>0;
}

void CHEventControlFormView::showMatchesInPlay()
{
	int multiScrollPos = getMultiScrollBarPosition();

	if (vMatchesInPlay.entries()>MAX_MULTI_EC)
	{
		if (!m_pMultiScrollBar)
		{
			m_pMultiScrollBar = new CHEventControlMultiScrollBar(vMatchesInPlay.entries()/2,CRect(833,20,849,638),w->getBase());
			m_pMultiScrollBar->ShowWindow(TRUE);
		}
		else
		{
			int oldPosition = m_pMultiScrollBar->getPosition();
			m_pMultiScrollBar->setEntries(vMatchesInPlay.entries()/2);
			m_pMultiScrollBar->ShowWindow(TRUE);
			m_pMultiScrollBar->SetScrollRange(0,vMatchesInPlay.entries()/2);
			if (oldPosition>int(vMatchesInPlay.entries()/2))
				m_pMultiScrollBar->SetScrollPos(0);
		}
	}
	else
	{
		if (m_pMultiScrollBar)
		{
			m_pMultiScrollBar->DestroyWindow();
			delete m_pMultiScrollBar;
			m_pMultiScrollBar=0;
		}
	}

	CHMatch *pMatch = 0;
	short index=0;
	for (size_t i=multiScrollPos*2;i<size_t(MAX_MULTI_EC+multiScrollPos*2);i++)
	{
		if (vMatchesInPlay[i])
		{
			pMatch = (CHMatch *)vMatchesInPlay[i]->getElement();
			createGUI(pMatch,index);
		}
		else
		{
			hideGUI(index);
		}
		index++;
	}
}

int CHEventControlFormView::fillMatchesInPlayVector()
{
	vMatchesInPlay.clearAndDestroy();

	CHMatch *pMatch = 0;
	int count = w->getSelectedCount(GRID_MATCH);
	if (count)
	{
		int nSelected=0;
		while((pMatch = (CHMatch*)w->getSelectedLParam(GRID_MATCH,nSelected))!=0)
		{
			insertMatchInPlay(pMatch);
			nSelected++;
		}
	}				
	return count;
}

RWBoolean CHEventControlFormView::insertMatchInPlay(CHMatch* pMatch)
{
	if (!pMatch)
		return false;

	if (!vMatchesInPlay.find(pMatch))
	{
		vMatchesInPlay.insert(pMatch,orderMatchRoundDateTime);
		return true;
	}
	return false;
}

RWBoolean CHEventControlFormView::removeMatchInPlay(CHMatch* pMatch)
{
	if (vMatchesInPlay.find(pMatch))
	{
		vMatchesInPlay.remove(pMatch);
		return true;
	}
	return false;
}

int CHEventControlFormView::getMultiScrollBarPosition()
{
	if (m_pMultiScrollBar)
		return m_pMultiScrollBar->getPosition();

	return 0;
}

void CHEventControlFormView::createGUI(CHMatch *pMatch, int index)
// Creating all the form views and the Scroll
{
	CRect rect; 
	
	if (index<2)
		rect = CRect(30+index*473,50,270+index*473,290);		
	else
		rect = CRect(30+(index-2)*473,360,270+(index-2)*473,600);		
		
	///////////////////// NAMES FORM VIEW ///////////////////////////////////
	CHEventControlTable* pBoard=0;
	
	char key[10];
	sprintf(key,"%d", CH_WND_BOARD+index);
	obListBoards.Lookup(CString(key), (CObject*&) pBoard);

	if (!pBoard)
	{
		pBoard = new CHEventControlTable(this,w,rect,pMatch,index);
		obListBoards.SetAt((CString)key,pBoard);		
	}
	
	if (pBoard)
		pBoard->SendMessage(UM_ECT_SHOW,(WPARAM)pMatch);	
}

void CHEventControlFormView::hideGUI(int index)
{
	char key[10];
	
	// NAMES FORM VIEW
	CHEventControlTable* pBoard=0;
	sprintf(key,"%d", CH_WND_BOARD+index);
	obListBoards.Lookup(CString(key), (CObject*&) pBoard);

	if (pBoard)
	{
		pBoard->ShowWindow(SW_HIDE);
		pBoard->SendMessage(UM_ECT_SHOW,0);
	}
}

CHEventControlTable	*CHEventControlFormView::findBoard(GTHMatch* pMatch)
{
	CHEventControlTable* pBoard=0;
	POSITION pos;
	CString buffer;		
	if (!obListBoards.IsEmpty())
	{
		for( pos = obListBoards.GetStartPosition(); pos != NULL; )
		{
			obListBoards.GetNextAssoc( pos, buffer, (CObject*&)pBoard);
			if (pBoard &&
				pBoard->getMatch()==pMatch)
				return pBoard;
		}
	}
	return 0;
}

int	CHEventControlFormView::getIdGridHistoric()
{
	if (getCurrentMatch())
	{
		CHEventControlTable* pBoard = findBoard(getCurrentMatch());
		if (pBoard)
			return pBoard->getIdGridHistoric();
	}
	return GRID_HIST;
}

void CHEventControlFormView::createGrid(int idGrid)
{
	if (idGrid!=GRID_HIST)
	{
		CHEventControlTable* pBoard = findBoard(getCurrentMatch());
		if (pBoard)
			pBoard->createGrid();			
	}
}

void CHEventControlFormView::savePgn()
{
	wchar_t directory[MAX_PATH]={0};
	GetCurrentDirectory(MAX_PATH,directory);

	CString defExt(_T("*.txt\0"));
	static TCHAR BASED_CODE szFilter[] = _T("Pgn files (*.pgn)|*.pgn|Application extension (*.pgn)|*.pgn|All Files (*.*)|*.*||"); 
	CFileDialog fdlg(FALSE, defExt, NULL,
					 OFN_HIDEREADONLY|OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST,
					 szFilter, AfxGetMainWnd());	

	RWCString resultFile=NULLRWSTRING;
	RWCString resultPath=NULLRWSTRING;
	
	if (fdlg.DoModal()==IDOK)
	{
		resultPath=RWWString(fdlg.GetPathName()).toAscii();

		CHReadFile aReadFile;
		aReadFile.setFileName(resultPath);
		RWCString file="";
		POSITION pos;
		CString buffer;		
		CHEventControlTable* pBoard=0;

		if (!obListBoards.IsEmpty())
		{
			for( pos = obListBoards.GetStartPosition(); pos != NULL; )
			{
				obListBoards.GetNextAssoc( pos, buffer, (CObject*&)pBoard);
				if (pBoard)
				{
					file+=pBoard->getPgnNotation();
				}
			}
			aReadFile.saveFile(file);	
		}
		SetCurrentDirectory(directory);
	}
}

void CHEventControlFormView::loadPgn()
{
	wchar_t directory[MAX_PATH]={0};
	GetCurrentDirectory(MAX_PATH,directory);

	CString defExt(_T("*.pgn\0"));
	static TCHAR BASED_CODE szFilter[] = _T("Result files (*.pgn)|*.pgn|Application extension (*.pgn)|*.pgn|All Files (*.*)|*.*||"); 
	CFileDialog fdlg(TRUE, defExt, NULL,
					 OFN_HIDEREADONLY|OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST,
					 szFilter, AfxGetMainWnd());	
	RWCString resultFile=NULLRWSTRING;
	RWCString resultPath=NULLRWSTRING;
	GSortedVector vPgnMatches;
	if (fdlg.DoModal()==IDOK)
	{
		resultPath=RWWString(fdlg.GetPathName()).toAscii();
		eventControlOp.processResultsFromPgnFile(vMatchesInPlay,resultPath,vPgnMatches);

		CHPgnMatchesDlg aPgnMatchesDlg(vMatchesInPlay,vPgnMatches);
		if (aPgnMatchesDlg.DoModal()==IDOK)
		{
			for (size_t i=0;i<vPgnMatches.entries();i++)
			{
				CHPgnMatch* pPgnMatch = (CHPgnMatch*)vPgnMatches[i]->getElement();
				if (pPgnMatch->getMatch())
				{
					if (eventControlOp.copyHistoricToMatch(pPgnMatch,this))
						toOutCol(pPgnMatch->getMatch());
				}
			}
		}

		for (size_t i=0;i<vPgnMatches.entries();i++)
		{
			CHPgnMatch* pPgnMatch = (CHPgnMatch*)vPgnMatches[i]->getElement();
			delete pPgnMatch;
		}

		vPgnMatches.clearAndDestroy();

		SendMessage(UM_ECT_REDRAW);
	}

	send(TRN_SET_EC_HISTORIC);

	SetCurrentDirectory(directory);

}

//////////////////////////////////////////////////////////////////////
// Temporal Reports methods
//////////////////////////////////////////////////////////////////////

void CHEventControlFormView::onReportRequest(CReportItem *pItem)
{
	if (!pItem)
		return;
	switch (pItem->getNReport())
	{
		case RC74:
		{
			CHPhase *pPhase = (CHPhase *)pItem->getLParam1();
			if( pPhase )
				pItem->setResultCode(((CHMemoryDataBase*)mem())->getRSC(pPhase));
			
			short round = (short)pItem->getLParam2();

			char tmp[10];
			if(round && round!=ALL_ROUNDS)
				pItem->setParameters(itoa(round,tmp,10));
		}
		break;
		case RC75:
		{
			CHPhase *pPhase = (CHPhase *)pItem->getLParam1();
			if( pPhase )
				pItem->setResultCode(((CHMemoryDataBase*)mem())->getRSC(pPhase));

			short round = (short)pItem->getLParam2();

			char tmp[10];
			if(round && round!=ALL_ROUNDS)
				pItem->setParameters(itoa(round,tmp,10));
		}
		break;
		
	}
}

bool CHEventControlFormView::onReportGeneration(CReportManager *pReportMngr,CReportConfig *pReportCfg,CReportItem *pItem)
{
	if (!pItem || !pReportCfg || !pReportMngr)
		return false;
	switch (pItem->getNReport())
	{
	
		case RC74:
		{
			if( !pItem->getLParam1() )
			{
				AfxMessageBox(RWWString("Please select a Event-Phase",RWWString::multiByte));
				return false;
			}
			if( !pItem->getLParam2() )
			{
				AfxMessageBox(RWWString("Please select a Round or All Rounds",RWWString::multiByte));
				return false;
			}

			if (pItem->getNReport()==RC74)
			{
				CHRC74 aCHRC74(*pReportMngr,*pReportCfg,(CHPhase*)pItem->getLParam1(),short(pItem->getLParam2()));
				return aCHRC74.Run();
			}
			break;
		}
		case RC75:
		{
			if( !pItem->getLParam1() )
			{
				AfxMessageBox(RWWString("Please select a Event-Phase",RWWString::multiByte));
				return false;
			}
			if( !pItem->getLParam2() )
			{
				AfxMessageBox(RWWString("Please select a Round",RWWString::multiByte));
				return false;
			}

			if (pItem->getNReport()==RC75)
			{
				CHRC75 aCHRC75(*pReportMngr,*pReportCfg,(CHPhase*)pItem->getLParam1(),short(pItem->getLParam2()));
				return aCHRC75.Run();
			}
			break;
		}
	}
	return false;
}
