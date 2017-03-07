/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHEventControlMoveManager.h
*	Description	:
*
*	Author		:Javier Juste 
*	Date created:  
* 	Project		:
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#if !defined(AFX_CHEVENTCONTROLMOVEMANAGER_H)
#define AFX_CHEVENTCONTROLMOVEMANAGER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAXSQUARES	8

#define BLACK		1
#define WHITE		0
#define EMPTY		-1
#define MAXFIGURES	6

#define NOTHING		0
#define B_PAWN		1
#define B_BISHOP	2
#define B_KNIGHT	3
#define B_ROOK		4
#define	B_QUEEN		5
#define B_KING		6

#define W_PAWN		7
#define	W_BISHOP	8
#define W_KNIGHT	9
#define W_ROOK		10
#define	W_QUEEN		11
#define W_KING		12

#define W_ROOK_ROWDRAG_SH_CAST	7
#define W_ROOK_COLDRAG_SH_CAST	7
#define W_ROOK_ROWDROP_SH_CAST	7
#define W_ROOK_COLDROP_SH_CAST	5

#define W_ROOK_ROWDRAG_LG_CAST	7
#define W_ROOK_COLDRAG_LG_CAST	0
#define W_ROOK_ROWDROP_LG_CAST	7
#define W_ROOK_COLDROP_LG_CAST	3

#define B_ROOK_ROWDRAG_SH_CAST	0
#define B_ROOK_COLDRAG_SH_CAST	7
#define B_ROOK_ROWDROP_SH_CAST	0
#define B_ROOK_COLDROP_SH_CAST	5

#define B_ROOK_ROWDRAG_LG_CAST	0
#define B_ROOK_COLDRAG_LG_CAST	0
#define B_ROOK_ROWDROP_LG_CAST	0
#define B_ROOK_COLDROP_LG_CAST	3

#define W_ROWDRAG_SH_CAST	7
#define W_COLDRAG_SH_CAST	4
#define W_ROWDROP_SH_CAST	7
#define W_COLDROP_SH_CAST	6

#define W_ROWDRAG_LG_CAST	7
#define W_COLDRAG_LG_CAST	4
#define W_ROWDROP_LG_CAST	7
#define W_COLDROP_LG_CAST	2

#define B_ROWDRAG_SH_CAST	0
#define B_COLDRAG_SH_CAST	4
#define B_ROWDROP_SH_CAST	0
#define B_COLDROP_SH_CAST	6

#define B_ROWDRAG_LG_CAST	0
#define B_COLDRAG_LG_CAST	4
#define B_ROWDROP_LG_CAST	0
#define B_COLDROP_LG_CAST	2

#define W_PGN_ROWDRAG_SH_CAST	1
#define W_PGN_COLDRAG_SH_CAST	5
#define W_PGN_ROWDROP_SH_CAST	1
#define W_PGN_COLDROP_SH_CAST	7

#define W_PGN_ROWDRAG_LG_CAST	1
#define W_PGN_COLDRAG_LG_CAST	5
#define W_PGN_ROWDROP_LG_CAST	1
#define W_PGN_COLDROP_LG_CAST	3

#define B_PGN_ROWDRAG_SH_CAST	8
#define B_PGN_COLDRAG_SH_CAST	5
#define B_PGN_ROWDROP_SH_CAST	8
#define B_PGN_COLDROP_SH_CAST	7

#define B_PGN_ROWDRAG_LG_CAST	8
#define B_PGN_COLDRAG_LG_CAST	5
#define B_PGN_ROWDROP_LG_CAST	8
#define B_PGN_COLDROP_LG_CAST	3


typedef struct _stMovement
{
	int idPlay;
	int Piece;
	int Color;
	int oldPosi;
	int newPosi;	
	int result;
	int eatedPiece;
	int checkSameMov;
}TMOVEMENT;

typedef struct _stListMovement
{
	TMOVEMENT mov;
	struct _stListMovement *psig;
}TLISTMOVEMENTS;


class CHEventControlTable;

class CHEventControlMoveManager  
{
public:
	CHEventControlMoveManager();
	virtual ~CHEventControlMoveManager();

	inline CHMemoryDataBase * mem()
	{	
		return (CHMemoryDataBase *)((GManagerInterfaceApp *) AfxGetApp())->memG();
	}
//	void setPlayerColor(int color);

	TLISTMOVEMENTS * generateMovements(CHEventControlTable* pBoard, int color);
	TLISTMOVEMENTS * generateMovements(int piece,CHEventControlTable* pBoard, short color);
	TLISTMOVEMENTS * generateMovements(short oldPosi,short piece,CHEventControlTable* pBoard,RWBoolean isCastling, short color);
	TLISTMOVEMENTS * generateAllMovs(CHEventControlTable* pBoard, int color);
	
	TLISTMOVEMENTS * generateRookMovement(CHEventControlTable* pBoard,int posi,int Piece, short color , int radio=8);
	TLISTMOVEMENTS * generateKnightMovement(CHEventControlTable* pBoard, int posi, int piece, short color);
	TLISTMOVEMENTS * generateBishopMovement(CHEventControlTable* pBoard, int posi,int piece, short color,int radio=8);
	TLISTMOVEMENTS * generateQueenMovement(CHEventControlTable* pBoard, int piece,short color);
	TLISTMOVEMENTS * generatePawnMovement(CHEventControlTable* pBoard, int posi, int piece, short color);
	TLISTMOVEMENTS * generateKingMovement(CHEventControlTable* pBoard, int piece, int color,RWBoolean isCastling);
	
	TLISTMOVEMENTS * generateKnightMovements(CHEventControlTable* pBoard, int piece, short color);	
	TLISTMOVEMENTS * generateRookMovements(CHEventControlTable* pBoard, int piece, short color);
	TLISTMOVEMENTS * generateBishopMovements(CHEventControlTable* pBoard, int piece, short color);
	TLISTMOVEMENTS * generatePawnMovements(CHEventControlTable* pBoard, int piece, short color);

	void unmakeMovement(CHEventControlTable* pBoard,TMOVEMENT *pMov, int oldPiece, int oldColor);
	void makeMovement(CHEventControlTable* pBoard,TMOVEMENT *pMov, int &oldPiece, int &oldColor);

	BOOL getRowCol(int posi,int *fila,int *columna);
	BOOL getPgnRowCol(int posi,int *fila,int *columna);
	int	 findPositionSource(CHEventControlTable* pBoard, TMOVEMENT* pMovement);

	BOOL checkSameKindPieceMovement(CHEventControlTable* pBoard, TMOVEMENT* pMovement, short color);

	BOOL isValidMovement(CHEventControlTable* pBoard, int row, int col, int color);
	BOOL isEmpty		(CHEventControlTable* pBoard, int row, int col);
	BOOL canEatPiece	(CHEventControlTable* pBoard, int row, int col, int color);
	BOOL isPieceColor	(CHEventControlTable* pBoard, int row, int col, int color);
	BOOL isMovementInList(int mov, TLISTMOVEMENTS * plist);
	BOOL isMovementInList(TMOVEMENT * pMov, TLISTMOVEMENTS * pList);
	BOOL isInCheck		(int color,CHEventControlTable* pBoard);
	BOOL isInCheckMate	(int color,CHEventControlTable* pBoard);

	TMOVEMENT* getMovementFromList(int mov,TLISTMOVEMENTS * pList, int col);
	
	BOOL isPiece(CHEventControlTable* pBoard,int Piece, int color, int col, int row);
	BOOL isKing(CHEventControlTable* pBoard,int color,int col, int row);
	BOOL isQueen(CHEventControlTable* pBoard,int color,int col,int row);
	BOOL isRook(CHEventControlTable* pBoard,int color,int col,int row);
	BOOL isBishop(CHEventControlTable* pBoard,int color,int col,int row);
	BOOL isKnight(CHEventControlTable* pBoard,int color,int col,int row);
	BOOL isPawn(CHEventControlTable* pBoard,int color,int col,int row);
	BOOL canMovePawn2(int color, int posi);

	int  insListMov(TLISTMOVEMENTS **ppListDest, TLISTMOVEMENTS * pListSrc);
	void deleteMovements(TLISTMOVEMENTS *pListMov);
	TLISTMOVEMENTS * removeHeadMov(TLISTMOVEMENTS * pLMovs, TMOVEMENT *pmov);
	TLISTMOVEMENTS * deleteEqualMovements(TLISTMOVEMENTS * pListMov, TLISTMOVEMENTS * pListMov2);
	int getPosition(int row, int col);
	
	TMOVEMENT * getAppMovement(RWCString pgnNotation);

private:
	//short m_colorPlayer;
};

#endif // !defined(AFX_CHEVENTCONTROLMOVEMANAGER_H__7993D84E_512E_4442_B8C8_F407530A71F4__INCLUDED_)
