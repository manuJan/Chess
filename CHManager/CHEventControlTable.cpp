// CHEventControlTable.cpp : implementation file
//

#include "stdafx.h"
#include "chmanager.h"
#include "CHEventControlTable.h"
#include "CHEventControlFormView.h"
#include "CHDefines.h"
#include "CHMsgDefines.h"
#include "CHStatusDlg.h"
#include <Sports/CH/Data/CHStatisticDefines.h>
#include <CORE/TH/GTHHistoricBuffer.h>
#include <CORE/TH/GTHHistoric.h>
#include <GUI/FLAGS/flags.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHEventControlTable

CHEventControlTable::CHEventControlTable(CWnd * _pParent,CGraphicWnd * _w,CRect _rect,CHMatch* _pMatch, short _index)
:pParent(_pParent)
,w(_w)
,rect(_rect)
,pMatch(_pMatch)
,index(_index)
,pLastMovement(0)
,bKingMoved(false)
,wKingMoved(false)
,pBmpFlagWhite(0)
,pBmpFlagBlack(0)
,eventControlOp((CHMemoryDataBase*)mem())
{
	Create( NULL, _T("Nada"), WS_CHILD|WS_OVERLAPPED|WS_VISIBLE|WS_BORDER,_rect, _pParent, CH_WND_BOARD+_index, NULL);
	SetDlgCtrlID(CH_WND_BOARD+_index);

	for (short i=0;i<MAXSQUARES;i++)
		for (short j=0;j<MAXSQUARES;j++)
			m_Squares[i][j]=0;
	
	initBoard();
}

CHEventControlTable::~CHEventControlTable()
{
	deleteBoard();	
}



BEGIN_MESSAGE_MAP(CHEventControlTable, CWnd)
	//{{AFX_MSG_MAP(CHEventControlTable)
	ON_MESSAGE(UM_ECT_SHOW,onShow)
	ON_MESSAGE(UM_ECT_DESTROY,onDestroy)
	ON_MESSAGE(UM_ECT_UNDOMOVEMENT,onUndoMovement)
	ON_MESSAGE(UM_ECT_REDRAW,onRedraw)
	ON_MESSAGE(UM_PROCESS_MOVEMENT,onProcessMovement)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CHEventControlTable::DestroyWindow() 
{
	deleteBoard();
	return TRUE;
}

void CHEventControlTable::deleteBoard()
{
	for (short i=0;i<MAXSQUARES;i++)
	{
		for (short j=0;j<MAXSQUARES;j++)
		{
			if (m_Squares[i][j])
			{
				m_Squares[i][j]->DestroyWindow();
				delete m_Squares[i][j];
				m_Squares[i][j]=0;
			}
		}
	}

	if (pBmpFlagWhite)
	{
		delete pBmpFlagWhite;
		pBmpFlagWhite=0;
	}

	if (pBmpFlagBlack)
	{
		delete pBmpFlagBlack;
		pBmpFlagBlack=0;
	}
}

void CHEventControlTable::resetBoard()
{
	for (short i=0;i<MAXSQUARES;i++)
	{
		for (short j=0;j<MAXSQUARES;j++)
		{
			if (m_Squares[i][j])
				setPiece(EMPTY,i,j,NOTHING);				
			else 
				return;
		}
	}

	setPiece(BLACK,0,0,B_ROOK);
	setPiece(BLACK,0,1,B_KNIGHT);
	setPiece(BLACK,0,2,B_BISHOP);
	setPiece(BLACK,0,3,B_QUEEN);
	setPiece(BLACK,0,4,B_KING);
	setPiece(BLACK,0,5,B_BISHOP);
	setPiece(BLACK,0,6,B_KNIGHT);
	setPiece(BLACK,0,7,B_ROOK);

	setPiece(WHITE,7,0,W_ROOK);
	setPiece(WHITE,7,1,W_KNIGHT);
	setPiece(WHITE,7,2,W_BISHOP);
	setPiece(WHITE,7,3,W_QUEEN);
	setPiece(WHITE,7,4,W_KING);	
	setPiece(WHITE,7,5,W_BISHOP);
	setPiece(WHITE,7,6,W_KNIGHT);
	setPiece(WHITE,7,7,W_ROOK);

	setPiece(BLACK,1,0,B_PAWN);
	setPiece(BLACK,1,1,B_PAWN);
	setPiece(BLACK,1,2,B_PAWN);
	setPiece(BLACK,1,3,B_PAWN);
	setPiece(BLACK,1,4,B_PAWN);
	setPiece(BLACK,1,5,B_PAWN);
	setPiece(BLACK,1,6,B_PAWN);
	setPiece(BLACK,1,7,B_PAWN);
	
	setPiece(WHITE,6,0,W_PAWN);
	setPiece(WHITE,6,1,W_PAWN);
	setPiece(WHITE,6,2,W_PAWN);
	setPiece(WHITE,6,3,W_PAWN);
	setPiece(WHITE,6,4,W_PAWN);
	setPiece(WHITE,6,5,W_PAWN);
	setPiece(WHITE,6,6,W_PAWN);
	setPiece(WHITE,6,7,W_PAWN);	
}

int CHEventControlTable::getSBmp(int piece)
{
	switch (piece)
	{
		case B_ROOK:
			return BMP_B_ROOK_S;
		case W_ROOK:
			return BMP_W_ROOK_S;
		case B_BISHOP:
			return BMP_B_BISHOP_S;
		case W_BISHOP:
			return BMP_W_BISHOP_S;
		case B_KNIGHT:
			return BMP_B_KNIGHT_S;
		case W_KNIGHT:
			return BMP_W_KNIGHT_S;
		case B_QUEEN:
			return BMP_B_QUEEN_S;
		case W_QUEEN:
			return BMP_W_QUEEN_S;
		case B_KING:
			return BMP_B_KING_S;
		case W_KING:
			return BMP_W_KING_S;		
		default:
			return NOTHING;
	}
	return 0;
}

void CHEventControlTable::createGrid()
{
	w->destroyControl(CH_GRD_HIST+index);

	w->createGrid(CH_GRD_HIST+index,CRect(rect.right,rect.top+35,rect.right+120,rect.bottom),BORDER_DOWN,15,IDBCK_GRID,IDCOL,IDFNT,false);
	w->gridLineColor(CH_GRD_HIST+index,NULL_COLOR,RGB(255,255,255));
	w->delGridColumn(CH_GRD_HIST+index,0);
	w->addGridColumn(CH_GRD_HIST+index,"",JUST_LEFT,20);
	w->addGridColumn(CH_GRD_HIST+index,"",JUST_CENTER,50);
	w->addGridColumn(CH_GRD_HIST+index,"",JUST_CENTER,50);
	
	fillListHistoric();
}

int CHEventControlTable::getColor(int i,int j)
{
	if (m_Squares[i][j])
	{
		return m_Squares[i][j]->getColor();
	}
	return EMPTY;
}

int CHEventControlTable::getPiece(int i,int j)
{
	if (m_Squares[i][j])
	{
		return m_Squares[i][j]->getPiece();
	}
	return NOTHING;
}

CHEventControlSquare *CHEventControlTable::getSquare(int i,int j)
{
	return m_Squares[i][j];
}

void CHEventControlTable::setPiece(int color,int x,int y,int idPiece)
{
	if (m_Squares[x][y])
	{
		m_Squares[x][y]->setPiece(idPiece);
		m_Squares[x][y]->setColor(color);
	}
}

void CHEventControlTable::setWKingMoved(RWBoolean value)
{
	wKingMoved = value;	
}

void CHEventControlTable::setBKingMoved(RWBoolean value)
{
	bKingMoved = value;
}

void CHEventControlTable::initBoard()
{
	deleteBoard();

	// Tablero
	w->destroyControl(CH_GRD_BOARD+index);
	w->destroyControl(CH_FRM_GAME+index);

	w->destroyControl(CH_LBL_1+index);
	w->destroyControl(CH_LBL_2+index);
	w->destroyControl(CH_LBL_3+index);
	w->destroyControl(CH_LBL_4+index);
	w->destroyControl(CH_LBL_5+index);
	w->destroyControl(CH_LBL_6+index);
	w->destroyControl(CH_LBL_7+index);
	w->destroyControl(CH_LBL_8+index);

	w->destroyControl(CH_LBL_A+index);
	w->destroyControl(CH_LBL_B+index);
	w->destroyControl(CH_LBL_C+index);
	w->destroyControl(CH_LBL_D+index);
	w->destroyControl(CH_LBL_E+index);
	w->destroyControl(CH_LBL_F+index);
	w->destroyControl(CH_LBL_G+index);
	w->destroyControl(CH_LBL_H+index);

	w->destroyControl(CH_BMP_WHITE+index);
	w->destroyControl(CH_BMP_BLACK+index);

	w->destroyControl(CH_LBL_NAME_WHITE+index);
	w->destroyControl(CH_LBL_NAME_BLACK+index);

	w->destroyControl(CH_LBL_ROUND+index);
	w->destroyControl(CH_LBL_GAME+index);
	w->destroyControl(CH_LBL_EVENT+index);
	w->destroyControl(CH_LBL_GAME_RESULT+index);

	w->destroyControl(CH_LBL_WHITE+index);
	w->destroyControl(CH_LBL_BLACK+index);

	// Historico
	w->destroyControl(GRID_HIST);
	w->destroyControl(CH_GRD_HIST+index);
	w->destroyControl(CH_BUT_STATUS+index);
	w->destroyControl(CH_BUT_W_WINNER+index);	
	w->destroyControl(CH_BUT_B_WINNER+index);	
	w->destroyControl(CH_BUT_DRAW+index);	
	w->destroyControl(CH_BUT_EMPTY+index);		
	w->destroyControl(CH_BUT_W_WINNER_F+index);
	w->destroyControl(CH_BUT_B_WINNER_F+index);
	w->destroyControl(CH_BUT_DRAW_F+index);
	w->destroyControl(CH_LBL_NEXT_TURN+index);

	if (!pMatch)
		return;

	pBmpFlagWhite=new CBitmap();
	pBmpFlagBlack=new CBitmap();

	w->createGrid(CH_GRD_BOARD+index,rect,BORDER_DOWN,30,IDBCK_GRID,IDCOL,IDFNT,false);
	w->dragDropRegister  (CH_GRD_BOARD+index,"Board");
	w->dragDropAvailable (CH_GRD_BOARD+index,TRUE,TRUE);

	for (short i=0;i<MAXSQUARES;i++)
	{
		w->addGridColumn(CH_GRD_BOARD+index,"",JUST_CENTER,30);
		w->addGridLine(CH_GRD_BOARD+index,0,"");
	}

	w->createGrid(CH_GRD_HIST+index,CRect(rect.right,rect.top+35,rect.right+120,rect.bottom),BORDER_DOWN,15,IDBCK_GRID,IDCOL,IDFNT,false);
	w->gridLineColor(CH_GRD_HIST+index,NULL_COLOR,RGB(255,255,255));
	w->delGridColumn(CH_GRD_HIST+index,0);
	w->addGridColumn(CH_GRD_HIST+index,"",JUST_LEFT,20);
	w->addGridColumn(CH_GRD_HIST+index,"",JUST_CENTER,50);
	w->addGridColumn(CH_GRD_HIST+index,"",JUST_CENTER,50);

	w->createLabel(CH_LBL_8+index,CRect(rect.left-20,rect.top+ 13,rect.left,rect.top+ 23),"8",BORDER_NONE,JUST_CENTER,IDBCK,IDCOL,IDFNT_BOLD);
	w->createLabel(CH_LBL_7+index,CRect(rect.left-20,rect.top+ 43,rect.left,rect.top+ 53),"7",BORDER_NONE,JUST_CENTER,IDBCK,IDCOL,IDFNT_BOLD);
	w->createLabel(CH_LBL_6+index,CRect(rect.left-20,rect.top+ 73,rect.left,rect.top+ 83),"6",BORDER_NONE,JUST_CENTER,IDBCK,IDCOL,IDFNT_BOLD);
	w->createLabel(CH_LBL_5+index,CRect(rect.left-20,rect.top+103,rect.left,rect.top+113),"5",BORDER_NONE,JUST_CENTER,IDBCK,IDCOL,IDFNT_BOLD);
	w->createLabel(CH_LBL_4+index,CRect(rect.left-20,rect.top+133,rect.left,rect.top+143),"4",BORDER_NONE,JUST_CENTER,IDBCK,IDCOL,IDFNT_BOLD);
	w->createLabel(CH_LBL_3+index,CRect(rect.left-20,rect.top+163,rect.left,rect.top+173),"3",BORDER_NONE,JUST_CENTER,IDBCK,IDCOL,IDFNT_BOLD);
	w->createLabel(CH_LBL_2+index,CRect(rect.left-20,rect.top+193,rect.left,rect.top+203),"2",BORDER_NONE,JUST_CENTER,IDBCK,IDCOL,IDFNT_BOLD);
	w->createLabel(CH_LBL_1+index,CRect(rect.left-20,rect.top+223,rect.left,rect.top+233),"1",BORDER_NONE,JUST_CENTER,IDBCK,IDCOL,IDFNT_BOLD);

	w->createLabel(CH_LBL_A+index,CRect(rect.left+ 12,rect.top+243,rect.left+ 22,rect.top+253),"A",BORDER_NONE,JUST_CENTER,IDBCK,IDCOL,IDFNT_BOLD);
	w->createLabel(CH_LBL_B+index,CRect(rect.left+ 42,rect.top+243,rect.left+ 52,rect.top+253),"B",BORDER_NONE,JUST_CENTER,IDBCK,IDCOL,IDFNT_BOLD);
	w->createLabel(CH_LBL_C+index,CRect(rect.left+ 72,rect.top+243,rect.left+ 82,rect.top+253),"C",BORDER_NONE,JUST_CENTER,IDBCK,IDCOL,IDFNT_BOLD);
	w->createLabel(CH_LBL_D+index,CRect(rect.left+102,rect.top+243,rect.left+112,rect.top+253),"D",BORDER_NONE,JUST_CENTER,IDBCK,IDCOL,IDFNT_BOLD);
	w->createLabel(CH_LBL_E+index,CRect(rect.left+132,rect.top+243,rect.left+142,rect.top+253),"E",BORDER_NONE,JUST_CENTER,IDBCK,IDCOL,IDFNT_BOLD);
	w->createLabel(CH_LBL_F+index,CRect(rect.left+162,rect.top+243,rect.left+172,rect.top+253),"F",BORDER_NONE,JUST_CENTER,IDBCK,IDCOL,IDFNT_BOLD);
	w->createLabel(CH_LBL_G+index,CRect(rect.left+192,rect.top+243,rect.left+202,rect.top+253),"G",BORDER_NONE,JUST_CENTER,IDBCK,IDCOL,IDFNT_BOLD);
	w->createLabel(CH_LBL_H+index,CRect(rect.left+222,rect.top+243,rect.left+232,rect.top+253),"H",BORDER_NONE,JUST_CENTER,IDBCK,IDCOL,IDFNT_BOLD);
	
	for (i=0;i<MAXSQUARES;i++)
	{
		for (short j=0;j<MAXSQUARES;j++)
		{
			m_Squares[i][j] = new CHEventControlSquare(this,w,CRect(rect.left+j*30,rect.top+i*30,30,30),i,j);
			m_Squares[i][j]->initSquare();
		}
	}

	resetBoard();
	fillListHistoric();
	processMatch();
	paintWhite();
	paintBlack();
	paintMatch();	
}

void CHEventControlTable::fillListHistoric()
{
	w->gridDeleteAllItems(CH_GRD_HIST+index);

	if(pMatch)
	{
		for (size_t i=0; i<size_t(pMatch->getHistoricNumber()); i++)
			w->addGridLine(CH_GRD_HIST+index,LPARAM(i),_T(""));	
	}

	w->addGridLine(CH_GRD_HIST+index,LPARAM(-1),_T(""));	
	w->selectNLine(CH_GRD_HIST+index,w->getGridNItems(CH_GRD_HIST+index)-1,true,true);	
}

void CHEventControlTable::processMatch()
{
	if(!pMatch)
		return;

	CHMatchResult* pWhite = pMatch->getWhite();
	CHMatchResult* pBlack = pMatch->getBlack();

	bKingMoved=false;
	wKingMoved=false;

	eventControlOp.putScore(EV_EMPTY,pMatch);
	changeBackgroundPress(0);

	int oldi=0,oldj=0,newi=0,newj=0,eatedPiece=0;

	for (size_t i=0; i<size_t(pMatch->getHistoricNumber()); i++)
	{
		int idPlay		= pMatch->getPlay(i);
		int numPlayer	= pMatch->getDataValue(i,DATA_PLAYER);
		int numPlay		= pMatch->getDataValue(i,DATA_NUMPLAY);
		int numPiece	= pMatch->getDataValue(i,DATA_PIECE);
		int oldPosi		= pMatch->getDataValue(i,DATA_OLDPOSI);
		int	newPosi		= pMatch->getDataValue(i,DATA_NEWPOSI);
		int	result		= pMatch->getDataValue(i,DATA_RESULT);
		int	eatPiece	= pMatch->getDataValue(i,DATA_EATPIECE);
		
		if (idPlay==PLAY_MOVEMENT || 
			idPlay==PLAY_SHORT_CASTLING ||
			idPlay==PLAY_LONG_CASTLING )
		{
			oldi=0,oldj=0,newi=0,newj=0,eatedPiece=0;

			m_MoveManager.getRowCol(oldPosi,&oldi,&oldj);
			m_MoveManager.getRowCol(newPosi,&newi,&newj);

			movePiece(oldi,oldj,newi,newj,eatedPiece);
		}		
		
		if (idPlay==PLAY_SHORT_CASTLING)
		{
			if (numPlayer==EV_BLACK)
				movePiece(B_ROOK_ROWDRAG_SH_CAST,B_ROOK_COLDRAG_SH_CAST,B_ROOK_ROWDROP_SH_CAST,B_ROOK_COLDROP_SH_CAST,eatedPiece);
			else if (numPlayer==EV_WHITE)
				movePiece(W_ROOK_ROWDRAG_SH_CAST,W_ROOK_COLDRAG_SH_CAST,W_ROOK_ROWDROP_SH_CAST,W_ROOK_COLDROP_SH_CAST,eatedPiece);
		}
		if (idPlay==PLAY_LONG_CASTLING)
		{
			if (numPlayer==EV_BLACK)
				movePiece(B_ROOK_ROWDRAG_LG_CAST,B_ROOK_COLDRAG_LG_CAST,B_ROOK_ROWDROP_LG_CAST,B_ROOK_COLDROP_LG_CAST,eatedPiece);
			else if (numPlayer==EV_WHITE)
				movePiece(W_ROOK_ROWDRAG_LG_CAST,W_ROOK_COLDRAG_LG_CAST,W_ROOK_ROWDROP_LG_CAST,W_ROOK_COLDROP_LG_CAST,eatedPiece);
		}

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

	}

	// Si no hay ninguna Jugada pongo el primer split a Schedule
	if (!pMatch->getHistoricNumber())
	{
		CHStatusManager statusManager;

		if(pMatch->getStatus() == CHMemoryDataBase::eRunning)
			statusManager.run(*pMatch,CHMemoryDataBase::eStartList,false,false);
	}

	pParent->SendMessage(UM_ECT_TOOUTCOL,WPARAM(pWhite));
	pParent->SendMessage(UM_ECT_TOOUTCOL,WPARAM(pBlack));
	
	pParent->SendMessage(UM_ECT_TOSEND,WPARAM(TRN_SET_EC_HISTORIC));

//	m_MoveManager.setPlayerColor(pMatch->getTurn());
}

void CHEventControlTable::onClick(UINT idCtrl,LPARAM lParam)
{
	if (idCtrl==UINT(CH_GRD_HIST+index))
	{
		pParent->SendMessage(UM_ECT_SETMATCH,WPARAM(pMatch),LPARAM(this));	
	}
	else if (idCtrl==UINT(CH_BUT_STATUS+index))
	{
		changeStatus();
		pParent->SendMessage(UM_ECT_CHANGE_STATUS,WPARAM(pMatch),LPARAM(this));	
	}
	else if (idCtrl==UINT(CH_BUT_W_WINNER+index))
		pParent->SendMessage(UM_ECT_EVENT,EV_WHITE_WINNER,LPARAM(this));
	else if (idCtrl==UINT(CH_BUT_B_WINNER+index))
		pParent->SendMessage(UM_ECT_EVENT,EV_BLACK_WINNER,LPARAM(this));		
	else if (idCtrl==UINT(CH_BUT_DRAW+index))
		pParent->SendMessage(UM_ECT_EVENT,EV_DRAW,LPARAM(this));
	else if (idCtrl==UINT(CH_BUT_EMPTY+index))
		eventControlOp.putScore(EV_EMPTY,pMatch);		
	else if (idCtrl==UINT(CH_BUT_W_WINNER_F+index))
		pParent->SendMessage(UM_ECT_EVENT,EV_WHITE_WINNER_F,LPARAM(this));
	else if (idCtrl==UINT(CH_BUT_B_WINNER_F+index))
		pParent->SendMessage(UM_ECT_EVENT,EV_BLACK_WINNER_F,LPARAM(this));
	else if (idCtrl==UINT(CH_BUT_DRAW_F+index))
		pParent->SendMessage(UM_ECT_EVENT,EV_DRAW_F,LPARAM(this));	
}

BOOL CHEventControlTable::onPaintGrid(UINT idGrid,GridItem *gi)
{
	if (idGrid==UINT(CH_GRD_BOARD+index))
	{
		int row = gi->x;
		int col = gi->y;

		if (m_Squares[col][row])
		{
			if ( ((col+row) %2) !=0 )
			{
				// Celda Negra
				w->paintGridSolid(RGB(165,123,90));
			}
			else
			{
				// Celda Blanca
				w->paintGridSolid(RGB(231,206,165));								
			}
			m_Squares[col][row]->paint();
		}	
		return TRUE;
	}

	if (idGrid==UINT(CH_GRD_HIST+index) )
	{
		return paintGridHistoric(gi);
	}

	return FALSE;
}

BOOL CHEventControlTable::paintGridHistoric(GridItem *gi)
{
	if(!pMatch)
		return FALSE;

	if(gi->lParam==-1)
	{
		w->paintGridSolid((gi->sel)?0xF0C0C0:RGB(221,221,221));
		return true;
	}
	
	GTHHistoric aHist=pMatch->getHistoric(gi->lParam);

	int currentFont=IDFNT_BOLD;
	if(!aHist.getValid())
		currentFont=IDFNTS;

	long idPlay = aHist.getIdPlay();

	int numPlay = pMatch->getDataValue(gi->lParam,DATA_NUMPLAY);
	if(numPlay%2)
		w->paintGridSolid((gi->sel)?0xF0C0C0:0xFFFFFF);
	else 
		w->paintGridSolid((gi->sel)?0xF0C0C0:RGB(240,240,250));

	switch(gi->x)
	{
	case 0:
		{
			if (idPlay==PLAY_MOVEMENT || idPlay==PLAY_SHORT_CASTLING || idPlay==PLAY_LONG_CASTLING)
				w->paintGridVal(gi->rc.Width()/2,1,numPlay,IDFNT,RGB(0,0,0),JUST_CENTER);
			break;
		}
	case 1:
		{
			if (idPlay==PLAY_MOVEMENT)
			{
				if (aHist.getValueOfData(DATA_PLAYER)==EV_WHITE)
				{
					int Piece = aHist.getValueOfData(DATA_PIECE);
					if (getSBmp(Piece))
						w->paintGridBmp(0,1,getSBmp(Piece));
					w->paintGridText(gi->rc.Width()/2,1,eventControlOp.getPgnNotation(&aHist,false),IDFNT,RGB(0,0,0),JUST_CENTER);
				}
			}
			else if (idPlay==PLAY_SHORT_CASTLING)
			{
				if (aHist.getValueOfData(DATA_PLAYER)==EV_WHITE)
					w->paintGridText(gi->rc.Width()/2,1,SH_CASTLING_PGN_NOTATION,IDFNT,RGB(0,0,0),JUST_CENTER);
			}
			else if (idPlay==PLAY_LONG_CASTLING)
			{
				if (aHist.getValueOfData(DATA_PLAYER)==EV_WHITE)
					w->paintGridText(gi->rc.Width()/2,1,LG_CASTLING_PGN_NOTATION,IDFNT,RGB(0,0,0),JUST_CENTER);
			}
			else if (idPlay==PLAY_WHITE_WINNER)
				w->paintGridText(30,1,WHITE_WINNER_PGN_NOTATION,IDFNT,RGB(255,0,0),JUST_CENTER);
			else if (idPlay==PLAY_BLACK_WINNER)
				w->paintGridText(30,1,WHITE_BLACK_PGN_NOTATION,IDFNT,RGB(255,0,0),JUST_CENTER);
			else if (idPlay==PLAY_DRAW)
				w->paintGridText(30,1,DRAW_PGN_NOTATION,IDFNT,RGB(255,0,0),JUST_CENTER);
			else if (idPlay==PLAY_WHITE_WINNER_F)
				w->paintGridText(30,1,WHITE_WINNER_F_PGN_NOTATION,IDFNT,RGB(255,0,0),JUST_CENTER);
			else if (idPlay==PLAY_BLACK_WINNER_F)
				w->paintGridText(30,1,WHITE_BLACK_F_PGN_NOTATION,IDFNT,RGB(255,0,0),JUST_CENTER);
			else if (idPlay==PLAY_DRAW_F)
				w->paintGridText(30,1,DRAW_F_PGN_NOTATION,IDFNT,RGB(255,0,0),JUST_CENTER);
		}
		break;
	case 2:
		{
			if (idPlay==PLAY_MOVEMENT)
			{
				if (aHist.getValueOfData(DATA_PLAYER)==EV_BLACK)
				{
					int Piece = aHist.getValueOfData(DATA_PIECE);
					if (getSBmp(Piece))
						w->paintGridBmp(0,1,getSBmp(Piece));
					w->paintGridText(gi->rc.Width()/2,1,eventControlOp.getPgnNotation(&aHist,false),IDFNT,RGB(0,0,0),JUST_CENTER);			
				}
			}
			else if (idPlay==PLAY_SHORT_CASTLING)
			{
				if (aHist.getValueOfData(DATA_PLAYER)==EV_BLACK)
					w->paintGridText(gi->rc.Width()/2,1,SH_CASTLING_PGN_NOTATION,IDFNT,RGB(0,0,0),JUST_CENTER);
			}
			else if (idPlay==PLAY_LONG_CASTLING)
			{
				if (aHist.getValueOfData(DATA_PLAYER)==EV_BLACK)
					w->paintGridText(gi->rc.Width()/2,1,LG_CASTLING_PGN_NOTATION,IDFNT,RGB(0,0,0),JUST_CENTER);	
			}			
		}
		break;
	}
	return TRUE;	
}


LRESULT CHEventControlTable::onRedraw(WPARAM wParam,LPARAM lParam)
{
	if (pMatch)
	{
		RWCString result="Res: ";
		result+=pMatch->getResultWhiteBlackAsString();
		w->changeTxt(CH_LBL_GAME_RESULT+index,result);
		w->redraw(CH_LBL_GAME_RESULT+index);
		w->changeTxt(CH_BUT_STATUS+index,getStatus());
		w->redraw(CH_BUT_STATUS+index);

		w->redraw(CH_GRD_BOARD+index);

		// Buttons
		int resultCode = pMatch->getResultCode();
		changeBackgroundPress(resultCode);
		w->changeTxt(CH_LBL_NEXT_TURN+index,"Turn:");

		if (pMatch->getTurn()==CHMatchResult::eWhite)
		{
			w->changeBck(CH_LBL_NEXT_TURN+index,IDBCK_WHITE);			
			w->changeBmp(CH_LBL_NEXT_TURN+index,BMP_WHITE_EC,JUST_RIGHT);
		}
		else if (pMatch->getTurn()==CHMatchResult::eBlack)
		{
			w->changeBck(CH_LBL_NEXT_TURN+index,IDBCK_BLACK);
			w->changeBmp(CH_LBL_NEXT_TURN+index,BMP_BLACK_EC,JUST_RIGHT);
		}

		w->redraw(CH_LBL_NEXT_TURN+index);
	}
	return 0;
}

LRESULT CHEventControlTable::onShow(WPARAM wParam, LPARAM lParam)
// Update CHMatch object
{
	CHMatch * pNewMatch = (CHMatch*)wParam;
	pMatch=pNewMatch;
		
	if (pMatch)
	{
		ShowWindow(SW_SHOW);
		MoveWindow(rect);
	}
	else
	{
		ShowWindow(SW_HIDE);
		MoveWindow(CRect(0,0,0,0));
	}
	
	onDestroy(0,0);
	initBoard();
	Invalidate();
	return 0;
}

LRESULT CHEventControlTable::onDestroy(WPARAM wParam, LPARAM lParam)
// destroying the Squares
{
	
	for (short i=0;i<MAXSQUARES;i++)
	{
		for (short j=0;j<MAXSQUARES;j++)
		{

			if (m_Squares[i][j])
			{					
				m_Squares[i][j]->DestroyWindow();
				delete m_Squares[i][j];
				m_Squares[i][j]=0;
			}
		}
	}

	if (w)
	{
		w->destroyControl(CH_GRD_BOARD+index);
		w->destroyControl(CH_GRD_HIST+index);
	}
	
	
	return 0;

	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);
}

LRESULT CHEventControlTable::onUndoMovement(WPARAM wParam,LPARAM lParam)
{
	int posHist = int(wParam);

	if (!pMatch)
		return 0;

	resetBoard();
	processMatch();
	SendMessage(UM_ECT_REDRAW);	
	return 0;
}

BOOL CHEventControlTable::onGridDrag(WPARAM wParam, LPARAM lParam)
{
	if (wParam==UINT(CH_GRD_BOARD+index))
	{
		DragDropItem *ddi = (DragDropItem *)lParam;
		if (!ddi) 
			return FALSE;
		
		short x = ddi->xSource;
		short y = ddi->ySource;

		if (ddi->idTarget!=ddi->idSource)
			return FALSE;

		if (!m_Squares[y][x])
			return FALSE;

		if (m_Squares[y][x]->getPiece()==NOTHING)
			return FALSE;

		if (m_Squares[y][x]->getColor()!=pMatch->getTurn())
			return FALSE;

		if (eventControlOp.statusForbidden(pMatch,false))
			return FALSE;
		
		if (eventControlOp.playForbidden(pMatch,PLAY_MOVEMENT))
			return FALSE;

		return TRUE;	
	}
	
	return FALSE;	
}

BOOL CHEventControlTable::onGridDrop(WPARAM wParam, LPARAM lParam)
{
	if (wParam==UINT(CH_GRD_BOARD+index))
	{
		DragDropItem *dd = (DragDropItem *)lParam;

		// Cogemos la posición del grid en la que se suelta 
		// el elemento sobre el que hacemos drag drop
		int rowDrop = dd->yTarget;
		int colDrop = dd->xTarget;

		int rowDrag = dd->ySource;
		int colDrag = dd->xSource;

		CHEventControlSquare* pSquare = (CHEventControlSquare*)getSquare(rowDrag,colDrag);
		if (!pSquare)
			return FALSE;

		
		return processMovement(pSquare,rowDrag,colDrag,rowDrop,colDrop);
	}

	return FALSE;
}

RWBoolean CHEventControlTable::processMovement(CHEventControlSquare *pSquare,int rowDrag,int colDrag,int rowDrop,int colDrop)
{
	int eatedPiece=NOTHING;

	RWBoolean isShortCastling=false;
	RWBoolean isLongCastling=false;

	if ( pSquare->getPiece()==W_KING &&
		 rowDrag==W_ROWDRAG_SH_CAST && colDrag==W_COLDRAG_SH_CAST && !wKingMoved) 			
	{
		if (rowDrop==W_ROWDROP_SH_CAST && colDrop==W_COLDROP_SH_CAST)
			isShortCastling=true;
		else if (rowDrop==W_ROWDROP_LG_CAST && colDrop==W_COLDROP_LG_CAST) 
			isLongCastling=true;
	}
		
	if ( pSquare->getPiece()==B_KING &&
		 rowDrag==B_ROWDRAG_SH_CAST && colDrag==B_COLDRAG_SH_CAST && !bKingMoved)

	{
		if (rowDrop==B_ROWDROP_SH_CAST && colDrop==B_COLDROP_SH_CAST)
			isShortCastling=true;	
		else if (rowDrop==B_ROWDROP_LG_CAST && colDrop==B_COLDROP_LG_CAST )
			isLongCastling=true;
	}

	
	if (isValidMovement(rowDrag,colDrag,rowDrop,colDrop,pMatch->getTurn(),isShortCastling || isLongCastling))
	{
		// Procesar jugada
		TMOVEMENT aMovement;			
		aMovement.idPlay=EV_MOVE;
		aMovement.Piece=pSquare->getPiece();		
		aMovement.Color=pMatch->getTurn()?EV_BLACK:EV_WHITE;
		aMovement.oldPosi=m_MoveManager.getPosition(rowDrag,colDrag);
		aMovement.newPosi=m_MoveManager.getPosition(rowDrop,colDrop);
		aMovement.result=0;

		// Resultado Enroque Corto
		if (isShortCastling)
			aMovement.idPlay=EV_SHORT_CASTLING;
			
		// Resultado Enroque Largo
		if (isLongCastling)
			aMovement.idPlay=EV_LONG_CASTLING;
		
		aMovement.checkSameMov = checkSameKindPieceMovement(&aMovement,aMovement.Color);

		if ( isShortCastling || isLongCastling )
			generateRookCastlingMovement(&aMovement,isShortCastling,isLongCastling);

		int Piece = movePiece(rowDrag,colDrag,rowDrop,colDrop,eatedPiece);
		aMovement.Piece=Piece;		
		aMovement.eatedPiece=eatedPiece?EV_EAT:NOTHING;

		// Resultado Jaque
		if (m_MoveManager.isInCheck(aMovement.Color==EV_WHITE?BLACK:WHITE,this))
			aMovement.result=EV_CHECK;
		
		// Resultado Jaque Mate
		if (m_MoveManager.isInCheckMate(aMovement.Color==EV_WHITE?BLACK:WHITE,this))
			aMovement.result=EV_CHECKMATE;

		pLastMovement=&aMovement;

		w->setFocus(CH_GRD_HIST+index);
		w->selectNLine(CH_GRD_HIST+index,w->getGridNItems(CH_GRD_HIST+index)-1,true,true);	

		pParent->SendMessage(UM_ECT_EVENT,WPARAM(aMovement.idPlay),LPARAM(this));
		
		pLastMovement=0;
		fillListHistoric();

		return TRUE;	
	}
	
	return FALSE;
}

LRESULT CHEventControlTable::onProcessMovement(WPARAM wParam,LPARAM lParam)
{
	TMOVEMENT *pMovement = (TMOVEMENT*)lParam;

	if (pMovement->idPlay==EV_MOVE)
		pMovement->oldPosi = m_MoveManager.findPositionSource(this,pMovement);

	int colDrag=0,rowDrag=0,colDrop=0,rowDrop=0;

	m_MoveManager.getRowCol(pMovement->newPosi,&rowDrop, &colDrop);
	m_MoveManager.getRowCol(pMovement->oldPosi,&rowDrag, &colDrag);

	CHEventControlSquare* pSquare = (CHEventControlSquare*)getSquare(rowDrag,colDrag);
	if (!pSquare)
		return 0;

	processMovement(pSquare,rowDrag,colDrag,rowDrop,colDrop);

	return 0;
}

BOOL CHEventControlTable::infoCurrentPlayStart(long idPlay, RWOrdered m_datas)
{
	if (eventControlOp.statusForbidden(pMatch))
	{
		// YA tiene error el status Forbidden
		pParent->SendMessage(UM_ECT_CANCEL_EVENTS);
		return FALSE;
	}

	if (eventControlOp.playForbidden(pMatch,idPlay))
	{
		pParent->SendMessage(UM_ECT_CANCEL_EVENTS);
		return FALSE;
	}

	return FALSE;
}

void CHEventControlTable::infoHistoricEnd(int posHist, BOOL isDo,GTHEventControlFormView::action histAction)
{
	if (!pMatch)
		return;

	long idPlay =pMatch->getPlay(posHist);
	if( idPlay == NOT_FOUND)
		return;

	// Si es la primera jugada inicia el partido
	if (isDo)
		eventControlOp.processStartGame(pMatch,idPlay);		

	if (isDo)
	{
		switch (idPlay)
		{
			case PLAY_WHITE_WINNER:
				eventControlOp.putScore(EV_WHITE_WINNER,pMatch);
				break;
			case PLAY_BLACK_WINNER:
				eventControlOp.putScore(EV_BLACK_WINNER,pMatch);
				break;
			case PLAY_DRAW:
				eventControlOp.putScore(EV_DRAW,pMatch);
				break;
			case PLAY_WHITE_WINNER_F:
				eventControlOp.putScore(EV_WHITE_WINNER_F,pMatch);
				break;
			case PLAY_BLACK_WINNER_F:
				eventControlOp.putScore(EV_BLACK_WINNER_F,pMatch);
				break;
			case PLAY_DRAW_F:
				eventControlOp.putScore(EV_DRAW_F,pMatch);
				break;
		}
	}
	else
	{
		switch (idPlay)
		{
			case PLAY_WHITE_WINNER:			
			case PLAY_BLACK_WINNER:			
			case PLAY_DRAW:			
			case PLAY_WHITE_WINNER_F:			
			case PLAY_BLACK_WINNER_F:			
			case PLAY_DRAW_F:					
			{
				eventControlOp.putScore(EV_EMPTY,pMatch);
				eventControlOp.clearResults(pMatch);
				eventControlOp.startListMatch(pMatch,true);					
				break;
			}
		}
	}

	SendMessage(UM_ECT_REDRAW);		
}

void CHEventControlTable::paintMatch()
{
	if (pMatch)
	{
		w->createFrame(CH_FRM_GAME+index,CRect(rect.left-22,rect.top-30,rect.right+212,rect.bottom+40),BORDER_UP,IDCOL);

		// Match information
		w->createLabel(CH_LBL_EVENT+index		,CRect(rect.right	,rect.top-3,rect.right+70 ,rect.top+15),pMatch->getEventLDescription()	,BORDER_DOWN,JUST_LEFT,IDBCK,IDCOL,IDFNT_BOLD);
		w->createLabel(CH_LBL_GAME_RESULT+index ,CRect(rect.right+70,rect.top-3,rect.right+138,rect.top+15),"",BORDER_DOWN,JUST_LEFT,IDBCK,IDCOL,IDFNT_BOLD);

		char tmp[10];
		RWCString round = "Round: ";
		sprintf(tmp,"%d",pMatch->getRound());
		round+=tmp;
		w->createLabel(CH_LBL_ROUND+index,CRect(rect.right,rect.top+16,rect.right+70,rect.top+34),round,BORDER_DOWN,JUST_LEFT,IDBCK,IDCOL,IDFNT_BOLD);

		RWCString game = "Game: ";
		game+=pMatch->getMatchNumberAsString();
		w->createLabel	(CH_LBL_GAME+index		,CRect(rect.right+70,rect.top+16,rect.right+138,rect.top+34),game,BORDER_DOWN,JUST_LEFT,IDBCK,IDCOL,IDFNT_BOLD);
		
		w->createButton	(CH_BUT_STATUS		+index	,CRect(rect.right+140,rect.top+ 34,rect.right+210,rect.top+ 54), ""				,IDBCK_GREEN,IDCOL,IDFNT);
		w->createButton	(CH_BUT_W_WINNER	+index	,CRect(rect.right+140,rect.top+ 55,rect.right+210,rect.top+ 75), " 1 : 0 "		,IDBCK_BUT,IDCOL,IDFNT);
		w->createButton	(CH_BUT_B_WINNER	+index	,CRect(rect.right+140,rect.top+ 76,rect.right+210,rect.top+ 96), " 0 : 1 "		,IDBCK_BUT,IDCOL,IDFNT);
		w->createButton	(CH_BUT_DRAW		+index	,CRect(rect.right+140,rect.top+ 97,rect.right+210,rect.top+117), " 1/2 : 1/2 "	,IDBCK_BUT,IDCOL,IDFNT);
		w->createButton	(CH_BUT_EMPTY		+index	,CRect(rect.right+140,rect.top+118,rect.right+210,rect.top+138), " Empty "		,IDBCK_BUT,IDCOL,IDFNT);
		w->createButton	(CH_BUT_W_WINNER_F	+index	,CRect(rect.right+140,rect.top+139,rect.right+210,rect.top+159), " 1F : 0F "	,IDBCK_BUT,IDCOL,IDFNT);
		w->createButton	(CH_BUT_B_WINNER_F	+index	,CRect(rect.right+140,rect.top+160,rect.right+210,rect.top+180), " 0F : 1F "	,IDBCK_BUT,IDCOL,IDFNT);
		w->createButton	(CH_BUT_DRAW_F		+index	,CRect(rect.right+140,rect.top+181,rect.right+210,rect.top+201), " 0F : 0F "	,IDBCK_BUT,IDCOL,IDFNT);
		w->createLabel	(CH_LBL_NEXT_TURN	+index	,CRect(rect.right+140,rect.top+202,rect.right+210,rect.top+240),"",BORDER_DOWN,JUST_LEFT,IDBCK,IDCOL_ROJO1,IDFNT_BOLD);
		w->setToolTip	(CH_BUT_STATUS		+index ,"Game Status");

		SendMessage(UM_ECT_REDRAW);
	}
}

void CHEventControlTable::paintWhite()
{
	 // Team flags
	w->destroyControl(CH_BMP_WHITE+index);
	
	CHMatchResult* pWhite = pMatch->getWhite();
	GRegister *pRegister=pWhite->getRegister();
	if(pRegister)
	{
		getFlag(pWhite->getGroup(),SML,pBmpFlagWhite);			
	 	w->createUserBitmap(CH_BMP_WHITE+index,CRect(rect.right-30,rect.bottom+15,rect.right,rect.bottom+40),pBmpFlagWhite,TRUE,BORDER_NONE);
		
		RWCString nameNOC=NULLRWSTRING;
		nameNOC+=pRegister->getScbLName().toMultiByte();
		nameNOC+=" (";
		nameNOC+=pRegister->getGroup();
		nameNOC+=")";

		w->createLabel   (CH_LBL_NAME_WHITE+index,CRect(rect.left,rect.bottom+15,rect.right-30,rect.bottom+40),nameNOC,BORDER_NONE,JUST_CENTER,IDBCK,IDCOL,IDFNT_BOLD);		
	}
}
void CHEventControlTable::paintBlack()
{
	// Team flags
	w->destroyControl(CH_BMP_BLACK+index);
	
	CHMatchResult* pBlack = pMatch->getBlack();
	GRegister *pRegister=pBlack->getRegister();
	if(pRegister)
	{
		getFlag(pBlack->getGroup(),SML,pBmpFlagBlack);			
	 	w->createUserBitmap(CH_BMP_BLACK+index,CRect(rect.left,rect.top-25,rect.left+30,rect.top),pBmpFlagBlack,TRUE,BORDER_NONE);
		
		RWCString nameNOC=NULLRWSTRING;
		nameNOC+=pRegister->getScbLName().toMultiByte();
		nameNOC+=" (";
		nameNOC+=pRegister->getGroup();
		nameNOC+=")";

		w->createLabel (CH_LBL_NAME_BLACK+index,CRect(rect.left+60,rect.top-25,rect.right,rect.top),nameNOC ,BORDER_NONE,JUST_LEFT,IDBCK,IDCOL,IDFNT_BOLD);			
	}
}

int CHEventControlTable::generateRookCastlingMovement(TMOVEMENT* pMovement, RWBoolean isShort, RWBoolean isLong)
{
	TMOVEMENT aMovement;			
	aMovement.idPlay=isShort?PLAY_SHORT_CASTLING:PLAY_LONG_CASTLING;

	if (pMovement->Piece==B_KING)
	{
		aMovement.Piece=B_ROOK;
		aMovement.Color=EV_BLACK;
	}
	else if (pMovement->Piece==W_KING) 
	{
		aMovement.Piece=W_ROOK;
		aMovement.Color=EV_WHITE;
	}
	else
		return NOTHING;

	int colDrag=0;
	int rowDrag=0;
	int colDrop=0;
	int rowDrop=0;
	
	if (aMovement.Color==EV_BLACK)
	{
		if (isShort)
		{
			rowDrag=B_ROOK_ROWDRAG_SH_CAST;
			colDrag=B_ROOK_COLDRAG_SH_CAST;			
			rowDrop=B_ROOK_ROWDROP_SH_CAST;
			colDrop=B_ROOK_COLDROP_SH_CAST;			
		}
		else if (isLong)
		{
			rowDrag=B_ROOK_ROWDRAG_LG_CAST;
			colDrag=B_ROOK_COLDRAG_LG_CAST;			
			rowDrop=B_ROOK_ROWDROP_LG_CAST;	
			colDrop=B_ROOK_COLDROP_LG_CAST;					
		}
	}

	if (aMovement.Color==EV_WHITE)
	{
		if (isShort)
		{
			rowDrag=W_ROOK_ROWDRAG_SH_CAST;
			colDrag=W_ROOK_COLDRAG_SH_CAST;
			rowDrop=W_ROOK_ROWDROP_SH_CAST;
			colDrop=W_ROOK_COLDROP_SH_CAST;
		}
		else if (isLong)
		{
			rowDrag=W_ROOK_ROWDRAG_LG_CAST;
			colDrag=W_ROOK_COLDRAG_LG_CAST;
			rowDrop=W_ROOK_ROWDROP_LG_CAST;
			colDrop=W_ROOK_COLDROP_LG_CAST;					
		}
	}

	
	aMovement.eatedPiece=0;

	// Resultado Jaque
	if (m_MoveManager.isInCheck(aMovement.Color==EV_WHITE?BLACK:WHITE,this))
		aMovement.result=EV_CHECK;

	if (isValidMovement(rowDrag,colDrag,rowDrop,colDrop,pMatch->getTurn(),false))
	{
		int Piece = movePiece(rowDrag,colDrag,rowDrop,colDrop,aMovement.eatedPiece);
	}
	return aMovement.result;
}	

int CHEventControlTable::movePiece(int oldi, int oldj, int newi, int newj, int &eatedPiece)
{
	if (m_Squares[newi][newj]->getPiece()!=NOTHING)
		eatedPiece=m_Squares[newi][newj]->getPiece();

	m_Squares[newi][newj]->setPiece(m_Squares[oldi][oldj]->getPiece());
	m_Squares[newi][newj]->setColor(m_Squares[oldi][oldj]->getColor());
	m_Squares[oldi][oldj]->empty();

	w->redraw(CH_GRD_BOARD+index);

	if (m_Squares[newi][newj]->getPiece()==W_KING)
		setWKingMoved(true);

	if (m_Squares[newi][newj]->getPiece()==B_KING)
		setBKingMoved(true);

	return m_Squares[newi][newj]->getPiece();
}

BOOL CHEventControlTable::isValidMovement(int rowDrag, int colDrag, int rowDrop, int colDrop, int color, RWBoolean isCastling)
{
	TLISTMOVEMENTS *pMovs=NULL;
	int valid =0;
	
	TMOVEMENT mov;
	CHEventControlSquare* pSquare = (CHEventControlSquare*)getSquare(rowDrag,colDrag);
	if (!pSquare)
		return FALSE;

//	m_MoveManager.setPlayerColor(color);

	mov.oldPosi = rowDrag*8 + colDrag+1;
	mov.newPosi = rowDrop*8 + colDrop+1;

	mov.Piece= pSquare->getPiece();
	mov.Color = color;

	pMovs = m_MoveManager.generateMovements(mov.oldPosi,mov.Piece,this,isCastling,color);

	if ( m_MoveManager.isMovementInList(&mov,pMovs) )
		valid=1;
	else valid=0;
	
	m_MoveManager.deleteMovements(pMovs);

	if ( valid )
	{
		if ( m_MoveManager.isInCheck(color,this) && isCastling )
		{
			short error;
			valid=0;
			return valid;
		}

		int oldPiece=NOTHING;
		int oldColor=EMPTY;

		m_MoveManager.makeMovement(this,&mov,oldPiece,oldColor);
		
		if ( m_MoveManager.isInCheck(color,this) )
		{
			short error;
			valid=0;
		}

		
		m_MoveManager.unmakeMovement(this,&mov,oldPiece,oldColor);		
	}

	return valid;
}

TMOVEMENT *CHEventControlTable::getLastMovement()
{
	return pLastMovement;		
}
	
CHMatch* CHEventControlTable::getMatch()
{
	return pMatch;
}

RWCString CHEventControlTable::getPgnNotation()
{
	return eventControlOp.getPgnNotation(pMatch);
}

int CHEventControlTable::getIdGridHistoric()
{
	return CH_GRD_HIST+index;
}

BOOL CHEventControlTable::checkSameKindPieceMovement(TMOVEMENT* pMovement,short color)
{
	return m_MoveManager.checkSameKindPieceMovement(this,pMovement,color==EV_BLACK?BLACK:WHITE);
}

RWCString CHEventControlTable::getStatus()
{
	if(pMatch)
	{
		
		GStatus *pStatus=CHMemoryDataBase::findStatus(pMatch->getStatus());
		if(pStatus)
			return pStatus->getLDescription().toMultiByte();
		
	}
	return NULLRWSTRING;
}

void CHEventControlTable::changeStatus()
{
	if (pMatch)
	{
		CHStatusDlg aStatusDlg(this,pMatch);
		aStatusDlg.DoModal();
			
		if(aStatusDlg.hasChanges())
		{
			// Si el Status es igual a StartList tengo que inicializar el partido
			if(	aStatusDlg.getStartList() && 
				pMatch->getStatus()==CHMemoryDataBase::eStartList)
				eventControlOp.clearResults(pMatch);

			// Si el Status es igual a Protested tengo que desprogresar el partido
			if(	pMatch->getStatus()==CHMemoryDataBase::eFinished ||
				pMatch->getStatus()==CHMemoryDataBase::eProtested)
			{
				eventControlOp.finishMatch(pMatch);
				/*if(pMatch->getStatus()==CHMemoryDataBase::eFinished)
					 disableEnableControls(false);
				else disableEnableControls(true);*/
			}
										
			SendMessage(UM_ECT_REDRAW);
		}				
	}
}	

void CHEventControlTable::changeBackgroundPress(short idEvent)
{
	w->changeBck	(CH_BUT_W_WINNER+index,IDBCK_BUT	);		
	w->redraw		(CH_BUT_W_WINNER+index,false		);

	w->changeBck	(CH_BUT_B_WINNER+index,IDBCK_BUT	);		
	w->redraw		(CH_BUT_B_WINNER+index,false		);

	w->changeBck	(CH_BUT_DRAW+index,IDBCK_BUT		);	
	w->redraw		(CH_BUT_DRAW+index,false			);
	
	w->changeBck	(CH_BUT_EMPTY+index,IDBCK_BUT		);		
	w->redraw		(CH_BUT_EMPTY+index,false			);
	
	w->changeBck	(CH_BUT_W_WINNER_F+index,IDBCK_BUT	);			
	w->redraw		(CH_BUT_W_WINNER_F+index,false		);
	
	w->changeBck	(CH_BUT_B_WINNER_F+index,IDBCK_BUT	);			
	w->redraw		(CH_BUT_B_WINNER_F+index,false		);
	
	w->changeBck	(CH_BUT_DRAW_F+index,IDBCK_BUT		);		
	w->redraw		(CH_BUT_DRAW_F+index,FALSE			);
 
	switch (idEvent)
	{
	case EV_WHITE_WINNER:
		w->changeBck(CH_BUT_W_WINNER+index,IDBCK_RED);
		break;
	case EV_BLACK_WINNER:
		w->changeBck(CH_BUT_B_WINNER+index,IDBCK_RED);
		break;
	case EV_DRAW:
		w->changeBck(CH_BUT_DRAW+index,IDBCK_RED);
		break;
	case EV_WHITE_WINNER_F:
		w->changeBck(CH_BUT_W_WINNER_F+index,IDBCK_RED);
		break;
	case EV_BLACK_WINNER_F:
		w->changeBck(CH_BUT_B_WINNER_F+index,IDBCK_RED);
		break;
	case EV_DRAW_F:
		w->changeBck(CH_BUT_DRAW_F+index,IDBCK_RED);
		break;		
	}
}