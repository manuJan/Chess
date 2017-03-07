#if !defined(AFX_CHEVENTCONTROLTABLE_H__31CEED7F_B4E8_4E07_9E4E_972B0040A74C__INCLUDED_)
#define AFX_CHEVENTCONTROLTABLE_H__31CEED7F_B4E8_4E07_9E4E_972B0040A74C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CHEventControlTable.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHEventControlTable window


#include "CHManager.h"
#include "CHEventControlSquare.h"
#include "CHEventControlMoveManager.h"
#include "CHEvenControlOperations.h"

#include <GUI\TH\GTHEventControlFormView.h>

class CHEventControlTable : public CWnd
{
// Construction
public:
	CHEventControlTable(CWnd * _pParent,CGraphicWnd * _w,CRect _rect,CHMatch* _pMatch, short _index);

// Attributes
public:

	inline CHMemoryDataBase *mem() 
	{ return (CHMemoryDataBase *) ((CCHManagerApp*)AfxGetApp())->memG();}
// Operations
public:

	void onClick(UINT idCtrl,LPARAM lParam);
	BOOL onPaintGrid(UINT idGrid,GridItem *gi);
	BOOL onGridDrag(WPARAM wParam, LPARAM lParam);
	BOOL onGridDrop(WPARAM wParam, LPARAM lParam);

	BOOL paintGridHistoric(GridItem *gi);

	void createGrid();
	void paintWhite();
	void paintBlack();
	void paintMatch();

	void fillListHistoric();

public:

	// Form EventControl Form View
	BOOL infoCurrentPlayStart(long idPlay, RWOrdered m_datas);
	void infoHistoricEnd(int posHist, BOOL isDo,GTHEventControlFormView::action histAction);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHEventControlTable)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHEventControlTable();
	
	void	  initBoard();
	void	  resetBoard();
	void	  processMatch();
	RWBoolean processMovement(CHEventControlSquare *pSquare,int rowDrag,int colDrag,int rowDrop,int colDrop);
		
	void changeStatus();
	void changeBackgroundPress(short press);

	int getPiece(int i,int j);
	int getColor(int i,int j);

	CHEventControlSquare *getSquare(int i,int j);
	TMOVEMENT *getLastMovement();
	CHMatch* getMatch();
	RWCString getPgnNotation();

	void setPiece(int color,int x,int y,int idPiece);
	int movePiece(int oldi, int oldj, int newi, int newj, int &eat);
	
	int getIdGridHistoric();

	void setWKingMoved(RWBoolean wKingMoved);
	void setBKingMoved(RWBoolean bKingMoved);

	int getSBmp(int piece);
	RWCString getStatus();

	BOOL checkSameKindPieceMovement(TMOVEMENT* pMovement,short color);

	// Generated message map functions
protected:
	//{{AFX_MSG(CHEventControlTable)
	LRESULT onShow(WPARAM wParam,LPARAM lParam);
	LRESULT onDestroy(WPARAM wParam,LPARAM lParam);	
	LRESULT onUndoMovement(WPARAM wParam,LPARAM lParam);
	LRESULT onRedraw(WPARAM wParam,LPARAM lParam);
	LRESULT onProcessMovement(WPARAM wParam,LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHEventControlTable)
	public:
	virtual BOOL DestroyWindow();
	//}}AFX_VIRTUAL

	void deleteBoard();
	BOOL isValidMovement(int rowDrag, int colDrag, int rowDrop, int colDrop, int color, RWBoolean isCastling);
	int generateRookCastlingMovement(TMOVEMENT* pMovement, RWBoolean isShort, RWBoolean isLong);
	
private:

	CWnd * pParent;
	CGraphicWnd * w;
	CRect rect;
	CHMatch* pMatch;
	short index;

	CBitmap *pBmpFlagWhite;
	CBitmap *pBmpFlagBlack;

	CHEventControlSquare *m_Squares[MAXSQUARES][MAXSQUARES];

	CHEventControlMoveManager m_MoveManager;
	RWBoolean bKingMoved;
	RWBoolean wKingMoved;
	
	TMOVEMENT *pLastMovement;

	CHEvenControlOperations    eventControlOp;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHEVENTCONTROLTABLE_H__31CEED7F_B4E8_4E07_9E4E_972B0040A74C__INCLUDED_)
