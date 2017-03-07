// CHEventControlSquare.cpp : implementation file
//

#include "stdafx.h"
#include "chmanager.h"
#include "CHEventControlSquare.h"
#include "CHEventControlTable.h"
#include "CHDefines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHEventControlSquare

CHEventControlSquare::CHEventControlSquare(CWnd * _pParent,CGraphicWnd * _w,CRect _rect,short _X, short _Y)
:pParent(_pParent)
,w(_w)
,rect(_rect)
,X(_X)
,Y(_Y)
{
	initSquare();
}

CHEventControlSquare::~CHEventControlSquare()
{
}


BEGIN_MESSAGE_MAP(CHEventControlSquare, CWnd)
	//{{AFX_MSG_MAP(CHEventControlSquare)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CHEventControlSquare::setPiece(int iPiece)
{
	m_Piece=iPiece;
}
	
void CHEventControlSquare::setFocus()
{
	m_focus=true;
}

void CHEventControlSquare::lostFocus()
{
	m_focus=false;
}

void CHEventControlSquare::setColor(int color)
{
	m_PieceColor=color;
}

int CHEventControlSquare::getPiece()
{
	return m_Piece;
}

int CHEventControlSquare::getColor()
{	
	return m_PieceColor;
}

bool CHEventControlSquare::isFocus()
{
	return m_focus;
}

/////////////////////////////////////////////////////////////////////////////
// CHEventControlSquare message handlers
void CHEventControlSquare::initSquare()
{
	setPiece(NOTHING);

}

void CHEventControlSquare::updateSquare()
{
	
}

void CHEventControlSquare::paint()
{
	if (getBmp())
		w->paintGridBmp(5,5,getBmp());
}

int CHEventControlSquare::getBmp()
{
	switch (m_Piece)
	{
		case B_PAWN:
			return BMP_B_PAWN;
		case W_PAWN:
			return BMP_W_PAWN;
		case B_ROOK:
			return BMP_B_ROOK;
		case W_ROOK:
			return BMP_W_ROOK;
		case B_BISHOP:
			return BMP_B_BISHOP;
		case W_BISHOP:
			return BMP_W_BISHOP;
		case B_KNIGHT:
			return BMP_B_KNIGHT;
		case W_KNIGHT:
			return BMP_W_KNIGHT;
		case B_QUEEN:
			return BMP_B_QUEEN;
		case W_QUEEN:
			return BMP_W_QUEEN;
		case B_KING:
			return BMP_B_KING;
		case W_KING:
			return BMP_W_KING;		
		default:
			return NOTHING;
	}
	return 0;
}

void CHEventControlSquare::empty()
{
	m_focus=false;
	m_Piece=NOTHING;
	m_PieceColor=EMPTY;
}

