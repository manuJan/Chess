// CHEventControlMoveManager.cpp: implementation of the CHEventControlMoveManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "chmanager.h"
#include "CHEventControlMoveManager.h"
#include "CHEventControlSquare.h"
#include "CHEventControlTable.h"
#include <Sports\CH\Data\CHStatisticDefines.h>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHEventControlMoveManager::CHEventControlMoveManager()
//:m_colorPlayer(WHITE)
{

}

CHEventControlMoveManager::~CHEventControlMoveManager()
{

}

/*void CHEventControlMoveManager::setPlayerColor(int color)
{
	m_colorPlayer = color;
}*/

TLISTMOVEMENTS * CHEventControlMoveManager::generateMovements(short oldPosi,short piece,CHEventControlTable* pBoard,RWBoolean isCastling, short color)
{
	TLISTMOVEMENTS *pMovs=0;

	switch( piece )
	{
	case W_ROOK:
	case B_ROOK:
		pMovs = generateRookMovement(pBoard,oldPosi,piece,color);
		break;
	case W_KNIGHT:
	case B_KNIGHT:
		pMovs = generateKnightMovement(pBoard,oldPosi,piece,color);
		break;
	case W_BISHOP:
	case B_BISHOP:
		pMovs = generateBishopMovement(pBoard,oldPosi,piece,color);
		break;
	case W_QUEEN:
	case B_QUEEN:
		pMovs = generateQueenMovement(pBoard,piece,color);
		break;
	case W_KING:
	case B_KING:
		pMovs = generateKingMovement(pBoard,piece,color,isCastling);
		break;
	case W_PAWN:
	case B_PAWN:
		pMovs = generatePawnMovement(pBoard,oldPosi,piece,color);
		break;

	}

	return pMovs;
}

/*
generar todos los movimientos de la piezas de un color determinado
y retorna un puntero a la lista de movimientos generados
*/
TLISTMOVEMENTS * CHEventControlMoveManager::generateMovements(CHEventControlTable* pBoard, int color)
{
	TLISTMOVEMENTS *pTMovs=NULL;
	TLISTMOVEMENTS *pMovs[MAXFIGURES];

	if (color==BLACK)
		pMovs[0]=generateMovements(B_PAWN,pBoard,color);
	else
		pMovs[0]=generateMovements(W_PAWN,pBoard,color);

	insListMov(&pTMovs,pMovs[0]);

	if (color==BLACK)
		pMovs[1]=generateMovements(B_KNIGHT,pBoard,color);
	else
		pMovs[1]=generateMovements(W_KNIGHT,pBoard,color);

	insListMov(&pTMovs,pMovs[1]);

	if (color==BLACK)
		pMovs[2]=generateMovements(B_BISHOP,pBoard,color);
	else
		pMovs[2]=generateMovements(W_BISHOP,pBoard,color);

	insListMov(&pTMovs,pMovs[2]);

	if (color==BLACK)
		pMovs[3]=generateMovements(B_QUEEN,pBoard,color);
	else
		pMovs[3]=generateMovements(W_QUEEN,pBoard,color);

	insListMov(&pTMovs,pMovs[3]);

	if (color==BLACK)
		pMovs[4]=generateMovements(B_ROOK,pBoard,color);
	else
		pMovs[4]=generateMovements(W_ROOK,pBoard,color);

	insListMov(&pTMovs,pMovs[4]);
	
	return pTMovs;

}

int CHEventControlMoveManager::insListMov(TLISTMOVEMENTS **ppListDest, TLISTMOVEMENTS * pListSrc)
{
	TLISTMOVEMENTS *pTmp;


	pTmp = *ppListDest;
	if ( *ppListDest == NULL )
		*ppListDest = pListSrc;
	else
	{
		while ( (*ppListDest)->psig != NULL )
			*ppListDest = (*ppListDest)->psig;


		(*ppListDest)->psig = pListSrc;

		*ppListDest = pTmp;
	}

	return 0;
}

/*
genera los posibles movimientos de una pieza en un tablero determinado
retorna un puntero a una lista de movimientos
*/
TLISTMOVEMENTS * CHEventControlMoveManager::generateMovements(int piece, CHEventControlTable* pBoard, short color)
{ 

	TLISTMOVEMENTS *pMov=NULL;

	switch( piece )
	{
		case W_ROOK:
		case B_ROOK:
			pMov = generateRookMovements(pBoard,piece,color);
			break;
		case W_KNIGHT:
		case B_KNIGHT:
			pMov = generateKnightMovements(pBoard,piece,color);
			break;
		case W_BISHOP:
		case B_BISHOP:
			pMov = generateBishopMovements(pBoard,piece,color);
			break ;
		case W_QUEEN:
		case B_QUEEN:
			pMov = generateQueenMovement(pBoard,piece,color);
			break;
		case W_KING:
		case B_KING:
			pMov = generateKingMovement(pBoard,piece,color,false);
			break;
		case W_PAWN:
		case B_PAWN:
			pMov = generatePawnMovements(pBoard,piece,color);
			break;

	}



	return pMov;
}


TLISTMOVEMENTS * CHEventControlMoveManager::generateQueenMovement(CHEventControlTable* pBoard, int Piece, short color)
{
	TLISTMOVEMENTS * pMovQueen=NULL;
	TLISTMOVEMENTS * pMov=NULL;
	int i;
	
	for (i=0;i<MAXSQUARES;i++)
	{
		for (short j=0;j<MAXSQUARES;j++)
		{
			if ((isQueen(pBoard,color,i,j)))
			{
				pMov = generateRookMovement(pBoard,getPosition(i,j),Piece,color);
				insListMov(&pMovQueen,pMov);
				pMov=NULL;
 				pMov = generateBishopMovement(pBoard,getPosition(i,j),Piece,color);
				insListMov(&pMovQueen,pMov);				
			}		
		}
	}
	return pMovQueen;
}

TLISTMOVEMENTS * CHEventControlMoveManager::generateRookMovement(CHEventControlTable* pBoard,int posi,int Piece, short color, int radio/*=8*/)
{
	TLISTMOVEMENTS *pMovRook=NULL;
	TLISTMOVEMENTS *pMov=NULL;
	TLISTMOVEMENTS *pTmp=NULL;
	int i,j;

	int relativMovs[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
	
	/*	
		significado de las posiciones relativas en de relativMovs
		son la posiciones relativas que puede hacer la Torre
		
	
		x3x
		2T0
		x1x

		T	=> Torre
		0	=> relativMovs[0][0]=0	relativMovs[0][1]=1
		1	=> relativMovs[1][0]=1	relativMovs[1][1]=0
		
	*/

	int filaNew,columNew,newPosi;
	int fila,colum;
	
	getRowCol(posi,&fila,&colum);
	
	for(i=0;i<radio;i++)
	{
		for(j=0;j<4;j++)
		{
			
			filaNew = fila + relativMovs[j][0];
			columNew = colum + relativMovs[j][1];
			
			if ( isValidMovement(pBoard, filaNew, columNew, color) )
			{
				newPosi = getPosition( filaNew,columNew);
				if ( relativMovs[j][0] <= 1000 )
				{
					pTmp= new TLISTMOVEMENTS;
					pTmp->mov.Piece=Piece;
					pTmp->mov.Color=color;
					pTmp->mov.oldPosi=posi;
					pTmp->mov.newPosi=newPosi;
					pTmp->psig=NULL;

					if ( pMov == NULL )
						pMovRook = pMov = pTmp;
					else 
					{
						pMov->psig=pTmp;
						pMov=pTmp;
					}
				}
				if ( canEatPiece(pBoard,filaNew,columNew,color))
				{
					relativMovs[j][0]=1000;	// no sigue sumando
					relativMovs[j][1]=1000;
				}				
			}

			if ( !isEmpty(pBoard,filaNew,columNew) )
			{
				relativMovs[j][0]=1000;	// no sigue sumando
				relativMovs[j][1]=1000;
			}


			if ( relativMovs[j][0] != 0 )
				{
					// incremento la posición relativa por las columnas
					if ( relativMovs[j][0] < 0 )
						relativMovs[j][0]--;
					else 
						relativMovs[j][0]++;
				}

			if ( relativMovs[j][1] != 0)
			{
				// incremento la posición relativa por las filas
				if ( relativMovs[j][1] < 0 )
					relativMovs[j][1]--;
				else 
					relativMovs[j][1]++;
			}		
		}
	}

	return pMovRook;
}

TLISTMOVEMENTS * CHEventControlMoveManager::generateBishopMovement(CHEventControlTable* pBoard, int posi,int piece, short color,int radio)
{

	TLISTMOVEMENTS *pMovBishop=NULL;
	TLISTMOVEMENTS *pMov=NULL;
	TLISTMOVEMENTS *pTmp=NULL;
	int i,j;
	int relativMovs[4][2]={{-1,1},{1,1},
							{1,-1},{-1,-1}};

		/*	
		significado de las posiciones relativas en de relativMovs
		son la posiciones relativas que puede hacer la Torre
		
	
		3x0
		xAx
		2x1

		A	=> Alfil
		0	=> relativMovs[0][0]=-1	relativMovs[0][1]=1
		1	=> relativMovs[1][0]=1	relativMovs[1][1]=1
		
	*/



	int filaNew,columNew,newPosi;
	int fila,colum;
	
	getRowCol(posi,&fila,&colum);
	
	for(i=0;i<radio;i++)
	{
		for(j=0;j<4;j++)
		{
			
			filaNew = fila + relativMovs[j][0];
			columNew = colum + relativMovs[j][1];
			
			if (isValidMovement(pBoard,filaNew,columNew,color))
			{
				newPosi = getPosition( filaNew,columNew);
				if ( relativMovs[j][0] <= 1000 )
				{
					pTmp= new TLISTMOVEMENTS;
					pTmp->mov.Piece=piece;
					pTmp->mov.Color=color;
					pTmp->mov.oldPosi=posi;
					pTmp->mov.newPosi=newPosi;
					pTmp->psig=NULL;

					if ( pMov == NULL )
						pMovBishop= pMov = pTmp;
					else 
					{
						pMov->psig=pTmp;
						pMov=pTmp;
					}


				}
				if ( canEatPiece(pBoard,filaNew,columNew,color))
				{
					relativMovs[j][0]=1000;	// no sigue sumando
					relativMovs[j][1]=1000;
				}

				
			}

			if ( !isEmpty(pBoard,filaNew,columNew))
			{
				relativMovs[j][0]=1000;	// no sigue sumando
				relativMovs[j][1]=1000;
			}

			if ( relativMovs[j][0] != 0 )
				{
					if ( relativMovs[j][0] < 0 )
						relativMovs[j][0]--;
					else relativMovs[j][0]++;
				}

			if ( relativMovs[j][1] != 0)
				{
					if ( relativMovs[j][1] < 0 )
						relativMovs[j][1]--;
					else relativMovs[j][1]++;
				}

			
		}

		

	}

	return pMovBishop;
}

/*
retorna una lista de los posibles movimientos que puede realizar un caballo en una posición.
*/
TLISTMOVEMENTS *CHEventControlMoveManager::generateKnightMovement(CHEventControlTable* pBoard, int posi, int piece, short color)
{
	
	TLISTMOVEMENTS *pMovCaballo=NULL;
	TLISTMOVEMENTS *pMov,*pTmp;

	int relativMovs[8][2]={	{-2,1},{-1,2},
							{1,2},{2,1},
							{2,-1},{+1,-2},
							{-1,-2},{-2,-1}};


	/*	
		significado de las posiciones relativas en de relativMovs
		son la posiciones relativas que puede hacer el caballo
		
		
		x7x0x		0	=> relativMovs[0][0]=-2	relativMovs[0][1]=1
		6xxx1
		xxCxx
		5xxx2
		x4x3x
		
			
	*/

	int fila,colum;
	int filaNew,columNew;
	int i;

	fila = (int ) ( posi / MAXSQUARES );
	colum = (int ) (posi % MAXSQUARES ) - 1;

	
	//para todos los movimientos relativos
	for( i=0;i<MAXSQUARES;i++)
	{
		// obtengo la posición global en tablero de la posición relativa
		filaNew = fila + relativMovs[i][0];
		columNew = colum + relativMovs[i][1];
		if ( isValidMovement(pBoard, filaNew,columNew,color ))
		{
			if ( pMovCaballo==NULL )
			{
				pMovCaballo	= new TLISTMOVEMENTS;
				pMov = pMovCaballo;
			}
			else
			{
				pTmp = new TLISTMOVEMENTS;
				pMov->psig=pTmp;
				pMov = pTmp;
			}

			pMov->mov.oldPosi = posi;
			pMov->mov.newPosi = (filaNew*8 + columNew+1);
			pMov->mov.Color = color;
			pMov->mov.Piece=piece;
			pMov->psig=NULL;			
		}				
	}							
							
	
	return pMovCaballo;
}

TLISTMOVEMENTS *CHEventControlMoveManager::generatePawnMovement(CHEventControlTable* pBoard, int posi, int Piece, short color)
{
	int newPosi;
	TLISTMOVEMENTS *pList=NULL;
	TLISTMOVEMENTS *pListTmp=NULL;
	TLISTMOVEMENTS *pListTmp2=NULL;
	int sumar;
	int newFila,newColumna;

	if ( color == BLACK )
	{
		sumar=1;	// las negras se supone que están en la parte superior del tablero
	}
	else
	{
		sumar=-1;	// blancas se suponen en la parte inferior del tablero.
	}

	// movimiento de un hacia delante del peón, 1 casilla hacia delante
	newPosi = posi + sumar * MAXSQUARES;// según el valor de sumar se suma o se resta.

	int row,col;
	getRowCol(newPosi,&row,&col);

	if ( !isPieceColor(pBoard, row, col, BLACK ) &&
		 !isPieceColor(pBoard, row, col, WHITE ) )
	{
		pListTmp = new TLISTMOVEMENTS;
		pListTmp->mov.Piece=Piece;
		pListTmp->mov.Color=color;
		pListTmp->mov.oldPosi= posi;
		pListTmp->mov.newPosi=newPosi;
		pListTmp->psig= NULL;
	}

	pList = pListTmp;

	// movimiento de un hacia delante del peón, 2 casillas hacia delante ( ANCHOTABLERO*2)
	newPosi = posi + ( sumar * MAXSQUARES*2);
	getRowCol(newPosi,&row,&col);

	if ( pList && 
		!isPieceColor(pBoard, row, col, BLACK ) && 
		!isPieceColor(pBoard, row, col, WHITE ) &&
		canMovePawn2(color,posi) )
		 
	{
		
		pListTmp = new TLISTMOVEMENTS;		
		pListTmp->mov.Piece = Piece;
		pListTmp->mov.Color = color;
		pListTmp->mov.oldPosi=posi;
		pListTmp->mov.newPosi=newPosi;
		pListTmp->psig=NULL;
		insListMov(&pList,pListTmp);
					
	}

	// miramos si puede comersa alguna
	getRowCol(posi,&newFila,&newColumna);
	// obtengo en newFila y newColumna la posición en diagonal con respecto al peón.
	newFila+=sumar;// adelanto una fila con respecto a la posicion del peón.
	newColumna-=sumar;// columna hacia la izquierda
	newPosi = getPosition(newFila,newColumna);
	getRowCol(newPosi,&row,&col);

	if ( isPieceColor(pBoard,row,col,color))
	{
		pListTmp= new TLISTMOVEMENTS;
		pListTmp->mov.Piece = Piece;
		pListTmp->mov.Color = color;
		pListTmp->mov.oldPosi=posi;
		pListTmp->mov.newPosi=newPosi;
		pListTmp->psig=NULL;

		insListMov(&pList,pListTmp);

	}
	getRowCol(posi,&newFila,&newColumna);
	newFila+=sumar;
	newColumna+=sumar;// columna hacia la derecha
	newPosi = getPosition(newFila,newColumna);
	if ( isPieceColor(pBoard,newFila,newColumna,color))
	{
		pListTmp= new TLISTMOVEMENTS;
		pListTmp->mov.Piece = Piece;
		pListTmp->mov.Color = color;
		pListTmp->mov.oldPosi=posi;
		pListTmp->mov.newPosi=newPosi;
		pListTmp->psig=NULL;
		insListMov(&pList,pListTmp);

	}
	
	return pList;
}

BOOL CHEventControlMoveManager::canMovePawn2(int color, int posi)
{
	int row,col;

	if ( posi < 0 )
		return FALSE;

	getRowCol(posi,&row,&col);

	if ( color == BLACK )
	{
		if ( row==1)
			return TRUE;
		else return FALSE;

	}
	else
	{
		if ( row == 6 )
			return TRUE;
		else return FALSE;
	}
	
		
	return FALSE;
}

BOOL CHEventControlMoveManager::checkSameKindPieceMovement(CHEventControlTable* pBoard, TMOVEMENT* pMovement, short color)
{
	if (!pBoard || !pMovement)
		return TRUE;

	int newRow=0,newCol=0,oldRow=0,oldCol=0;
	getRowCol(pMovement->newPosi,&newRow,&newCol);
	getRowCol(pMovement->oldPosi,&oldRow,&oldCol);

	TLISTMOVEMENTS *pAllMovs=NULL;
	TLISTMOVEMENTS *pMovs=NULL;
	TMOVEMENT mov;
	

	for (short i=0;i<MAXSQUARES;i++)
	{
		for (short j=0;j<MAXSQUARES;j++)
		{
			if (i!=oldRow || j!=oldCol)
			{
				if (isPiece(pBoard,pMovement->Piece,pMovement->Color,i,j))
				{
					mov.oldPosi = getPosition(i,j);
					mov.newPosi = pMovement->newPosi;
					mov.Piece= pMovement->Piece;
					mov.Color = color;

					pMovs = generateMovements(mov.oldPosi,mov.Piece,pBoard,false,color);

					if ( isMovementInList(&mov,pMovs) )
					{
						deleteMovements(pMovs);
						return TRUE;					
					}
					deleteMovements(pMovs);
				}
			}
		}
	}	
	return FALSE;
}

TLISTMOVEMENTS * CHEventControlMoveManager::generatePawnMovements(CHEventControlTable* pBoard, int piece, short color)
{
	int i;
	TLISTMOVEMENTS *pMovPawns,*pPawn;
	int pawn;

	pMovPawns=NULL;

	// busco los peones en tablero
	for (i=0;i<MAXSQUARES;i++)
	{
		for (short j=0;j<MAXSQUARES;j++)
		{
			if ( (isPawn(pBoard, color, i,j ) ) )
			{
				//genero movimientos del peón en la posicion i
				pPawn = generatePawnMovement(pBoard,getPosition(i,j),piece,color);
				// inserto los movimientos generados en la lista de los demás movientos de los
				// demás peones.
				insListMov(&pMovPawns,pPawn);

			}			
		}		
	}

	return pMovPawns;
}


TLISTMOVEMENTS * CHEventControlMoveManager::generateRookMovements(CHEventControlTable* pBoard, int piece, short color)
{
	TLISTMOVEMENTS *pMovRook=NULL;
	TLISTMOVEMENTS *pMov=NULL;
 
	int i;
	
	// bucle para buscar las torres
	for (i=0;i<MAXSQUARES;i++)
	{
		for (short j=0;j<MAXSQUARES;j++)
		{
			if ( isRook(pBoard,color,i,j) )
			{
				// genero movimiento de la torre en una posición dada por i
				pMov = generateRookMovement(pBoard,getPosition(i,j),piece,color);
				//inserto los movimientos generados en la lista de movimientos
				// generada por la otra torre.
				insListMov(&pMovRook,pMov);
			}			
		}
	}

	return pMovRook;
}

TLISTMOVEMENTS * CHEventControlMoveManager::generateBishopMovements(CHEventControlTable* pBoard, int piece, short color)
{
	TLISTMOVEMENTS *pMovBishop=NULL;
	TLISTMOVEMENTS *pMov=NULL;
 
		// bucle para buscar las torres
	for (short i=0;i<MAXSQUARES;i++)
	{
		for (short j=0;j<MAXSQUARES;j++)
		{
			if ( isBishop(pBoard,color,i,j) )
			{
				// genero movimiento de la torre en una posición dada por i
				pMov = generateBishopMovement(pBoard,getPosition(i,j),piece,color);
				//inserto los movimientos generados en la lista de movimientos
				// generada por la otra torre.
				insListMov(&pMovBishop,pMov);
			}			
		}
	}

	return pMovBishop;
}

TLISTMOVEMENTS * CHEventControlMoveManager::generateKnightMovements(CHEventControlTable* pBoard, int piece, short color)
{
	TLISTMOVEMENTS *pMovKnight=NULL;
	TLISTMOVEMENTS *pMov=NULL;
 
		// bucle para buscar las torres
	for (short i=0;i<MAXSQUARES;i++)
	{
		for (short j=0;j<MAXSQUARES;j++)
		{
			if ( isKnight(pBoard,color,i,j) )
			{
				// genero movimiento de la torre en una posición dada por i
				pMov = generateKnightMovement(pBoard,getPosition(i,j),piece,color);
				//inserto los movimientos generados en la lista de movimientos
				// generada por la otra torre.
				insListMov(&pMovKnight,pMov);
			}			
		}
	}

	return pMovKnight;
}

TLISTMOVEMENTS * CHEventControlMoveManager::generateKingMovement(CHEventControlTable* pBoard, int piece, int color, RWBoolean isCastling)
{
	TLISTMOVEMENTS * pMovKing=NULL;
	TLISTMOVEMENTS * pMov=NULL;
	TLISTMOVEMENTS * pMovOther=NULL;

	int i;
	
	for (i=0;i<MAXSQUARES;i++)
	{
		for (short j=0;j<MAXSQUARES;j++)
		{
			if ( isKing(pBoard,color,i,j))
			{
				pMov = generateRookMovement(pBoard,getPosition(i,j),piece,isCastling?2:1);
				insListMov(&pMovKing,pMov);
				pMov=NULL;
				pMov = generateBishopMovement(pBoard,getPosition(i,j),piece,1);
				insListMov(&pMovKing,pMov);
				
				////////////////////////
				pMovOther=generateMovements(pBoard,!color);
				
				pMovKing = deleteEqualMovements(pMovKing,pMovOther);
				deleteMovements(pMovOther);
				//deleteMovements(pMovKing);
			}
		}		
	}
	return pMovKing;

}

BOOL CHEventControlMoveManager::getRowCol(int posi,int *fila,int *columna)
{
	*fila = (int ) ( posi / MAXSQUARES );

	if ( !(posi % 8))
	{
		*columna = MAXSQUARES - 1;
		*fila = (int ) ( ( posi / MAXSQUARES ) -1 );
	}
	else
		*columna = (int ) ( (posi % MAXSQUARES) - 1 );

	return TRUE;
}

BOOL CHEventControlMoveManager::getPgnRowCol(int posi,int *fila,int *columna)
{
	int col=0,row=0;
	getRowCol(posi,&row,&col);

	* columna = col;
	* fila= MAXSQUARES - row ;
	return TRUE;
}

/*
retorna la posición según fila y columna.
*/

int CHEventControlMoveManager::getPosition(int row, int col)
{
	int posi;

	if ( (row < 0) || ( row >= 8) ||
		 (col <0)||(col >= 8))
		 return -1;
	
	posi = row*8 + col+1;
	return posi;
}

BOOL CHEventControlMoveManager::isValidMovement(CHEventControlTable* pBoard, int row, int col, int color)
{	
	if (row<0 || col<0 || 
		row>=MAXSQUARES || col>=MAXSQUARES)
		return FALSE;

	if ( isEmpty(pBoard,row,col) || canEatPiece(pBoard,row,col,color) )
		 return TRUE;

	return FALSE;
}

BOOL CHEventControlMoveManager::isEmpty(CHEventControlTable* pBoard, int row, int col)
{
	if (!pBoard)
		return FALSE;

	if (row<0 || col<0 || 
		row>=MAXSQUARES || col>=MAXSQUARES)
		return FALSE;

	CHEventControlSquare* pSquare = (CHEventControlSquare*)	pBoard->getSquare(row,col);
	if (pSquare &&
		pSquare->getPiece()==NOTHING)
		return TRUE;

	return FALSE;
}

BOOL CHEventControlMoveManager::canEatPiece(CHEventControlTable* pBoard, int row, int col, int color)
{
	if ( color == BLACK )
	{
		if ( isPieceColor(pBoard,row,col,color) )
			return TRUE;
		else 
			return FALSE;
	}
	else
	{
		if ( isPieceColor(pBoard,row,col,color) )
			return TRUE;
		else 
			return FALSE;
	}

	return FALSE;
}

BOOL CHEventControlMoveManager::isPieceColor(CHEventControlTable* pBoard, int row, int col, int color)
{
	if (row<0 || col<0 || 
		row>=MAXSQUARES || col>=MAXSQUARES)
		return FALSE;

	CHEventControlSquare* pSquare = (CHEventControlSquare*)	pBoard->getSquare(row,col);
	if (!pSquare)
		return FALSE;

	if ( color == BLACK )
	{
		if (pSquare->getPiece() && pSquare->getColor()==WHITE)
			return TRUE;
	}
	else
	{
		if (pSquare->getPiece() && pSquare->getColor()==BLACK)
			return TRUE;
	}

	return FALSE;
}

BOOL CHEventControlMoveManager::isMovementInList(int mov, TLISTMOVEMENTS * plist)
{
	BOOL follow=true;
	while( (plist != NULL) && follow)
	{

		if ( plist->mov.newPosi == mov )
			follow=false;
		plist = plist->psig;
	}

	return !follow;
}

TMOVEMENT* CHEventControlMoveManager::getMovementFromList(int mov,TLISTMOVEMENTS * plist, int col)
{
	BOOL follow=true;
	int column=0,row=0;

	while( (plist != NULL) && follow)
	{
		getRowCol(plist->mov.oldPosi,&row,&column);

		if ( plist->mov.newPosi == mov && (col==-1 || column == col) )
		{
			follow=false;
			return &plist->mov;
		}

		plist = plist->psig;
	}

	return 0;
}

BOOL CHEventControlMoveManager::isMovementInList(TMOVEMENT * pMov, TLISTMOVEMENTS * pList)
{
	BOOL follow=true;

	while( (pList != NULL) && follow )
	{
		if ( pList->mov.newPosi==pMov->newPosi)
			follow=false;
		pList=pList->psig;
	}

	return !follow;

}

/*
borra completamente una lista de movimientos
*/
void CHEventControlMoveManager::deleteMovements(TLISTMOVEMENTS * pListMov)
{
	TLISTMOVEMENTS *pTmp;

	while( pListMov != NULL )
	{
		pTmp = pListMov->psig;
		delete pListMov;
		pListMov = pTmp;
	}
}

// borra los movimientos que son iguales
TLISTMOVEMENTS * CHEventControlMoveManager::deleteEqualMovements(TLISTMOVEMENTS * pListMov, TLISTMOVEMENTS * pListMov2)
{
	TLISTMOVEMENTS *pList,*pPosterior,*pAnterior;
	TLISTMOVEMENTS *pListReturn=NULL;

	pListReturn = pList = pListMov;

	pAnterior=NULL;
	while( pList != NULL )
	{
		
		if ( isMovementInList(&(pList->mov),pListMov2) )
		{
			pPosterior = pList->psig;
			delete pList;
			pList=0;
			
			if ( pAnterior == NULL )
				pListReturn = pPosterior;
			else pAnterior->psig=pPosterior;

			pList=pPosterior;
		}
		else 
		{
			pAnterior = pList;
			pList=pList->psig;
		}
	}

	return pListReturn;
}


void CHEventControlMoveManager::makeMovement(CHEventControlTable* pBoard,TMOVEMENT * pMov, int &oldPiece, int &oldColor)
{
	int row,col;

	getRowCol(pMov->newPosi,&row,&col);
	oldPiece = pBoard->getPiece(row,col);
	oldColor = pBoard->getColor(row,col);
	pBoard->setPiece(pMov->Color,row,col,pMov->Piece);

	getRowCol(pMov->oldPosi,&row,&col);
	pBoard->setPiece(EMPTY,row,col,NOTHING);
}

void CHEventControlMoveManager::unmakeMovement(CHEventControlTable* pBoard, TMOVEMENT * pMov, int oldPiece, int oldColor)
{
	int row,col;
	getRowCol(pMov->newPosi,&row,&col);
	pBoard->setPiece(oldColor,row,col,oldPiece);
	
	getRowCol(pMov->oldPosi,&row,&col);
	pBoard->setPiece(pMov->Color,row,col,pMov->Piece);	
}

BOOL CHEventControlMoveManager::isInCheckMate(int color,CHEventControlTable* pBoard)
{
	TLISTMOVEMENTS *pMovs;
	TMOVEMENT movement;
	int follow=TRUE;
	int oldPiece=NOTHING;
	int oldColor=EMPTY;

	pMovs = generateAllMovs(pBoard,color);

	while ( pMovs != NULL && follow )
	{
		pMovs= removeHeadMov(pMovs,&movement);
		makeMovement( pBoard,&movement,oldPiece,oldColor);
		if ( !isInCheck( color,pBoard) )
			follow=FALSE;
		unmakeMovement(pBoard,&movement,oldPiece,oldColor);
	}

	deleteMovements( pMovs );

	return follow;
}

TLISTMOVEMENTS * CHEventControlMoveManager::generateAllMovs(CHEventControlTable* pBoard, int color)
{
	TLISTMOVEMENTS *pMovWhite,*pMovWhiteKing;
	TLISTMOVEMENTS *pMovBlack,*pMovBlackKing;
	TLISTMOVEMENTS *pMovTmp=NULL;
	TLISTMOVEMENTS *pKingValids=NULL;
	TLISTMOVEMENTS *pListReturn=NULL;

	pMovWhite=pMovWhiteKing=NULL;
	pMovBlack=pMovBlackKing=NULL;


	//m_colorPlayer = color;
	pMovWhiteKing= generateKingMovement(pBoard,W_KING,WHITE,false);
	pMovBlackKing= generateKingMovement(pBoard,B_KING,BLACK,false);

	//m_colorPlayer = BLACK;
	pMovBlack = generateMovements(pBoard,BLACK);

	//m_colorPlayer = WHITE;
	pMovWhite= generateMovements(pBoard,WHITE);

	if ( color == BLACK )
	{
		pMovTmp = pMovWhiteKing;
		insListMov(&pMovTmp,pMovWhite);
		pKingValids = deleteEqualMovements(pMovBlackKing,pMovTmp);
		insListMov(&pMovBlack,pKingValids);
		pListReturn = pMovBlack;
		deleteMovements(pMovTmp);
	}
	else
	{

		pMovTmp = pMovBlackKing;
		insListMov(&pMovTmp,pMovBlack);
		pKingValids = deleteEqualMovements(pMovWhiteKing,pMovTmp);
		insListMov(&pMovWhite,pKingValids);
		pListReturn = pMovWhite;
		deleteMovements(pMovTmp);
	}
	
	return pListReturn;
}

int	CHEventControlMoveManager::findPositionSource(CHEventControlTable* pBoard, TMOVEMENT* pMovement)
{
	int colSource = pMovement->oldPosi;
	TLISTMOVEMENTS *pMovs = generateMovements(pMovement->Piece,pBoard,pMovement->Color==EV_WHITE?WHITE:BLACK);
	TMOVEMENT* pMov = getMovementFromList(pMovement->newPosi,pMovs,colSource);

	int oldPosi = pMov?pMov->oldPosi:0;
	deleteMovements(pMovs);	
	return oldPosi;
}


BOOL CHEventControlMoveManager::isInCheck(int color,CHEventControlTable* pBoard)
{
	TLISTMOVEMENTS *pMovs;
	TLISTMOVEMENTS *pMovsKing;
	int posKing,i;
	int follow=1;
	BOOL check=false;

	CHEventControlSquare* pSquare=0;

	for (i=0;i<MAXSQUARES && follow;i++)
	{
		for (short j=0;j<MAXSQUARES && follow;j++)
		{
			if (color==BLACK && pBoard->getPiece(i,j)==B_KING)
			{
				pSquare = pBoard->getSquare(j,i);
				follow=false;
				posKing = getPosition(i,j);
			}
			else if (color==WHITE && pBoard->getPiece(i,j)==W_KING)
			{
				pSquare = pBoard->getSquare(j,i);
				follow=false;
				posKing = getPosition(i,j);
			}
		}
	}

	if ( color == BLACK )
		pMovsKing = generateKingMovement(pBoard,B_KING,color,false);
	else 
		pMovsKing = generateKingMovement(pBoard,W_KING,color,false);

	//m_colorPlayer = !color;
	pMovs = generateMovements(pBoard,!color);
	//m_colorPlayer = color;

	if ( isMovementInList( posKing,pMovs ))
		check=true;
	else 
		check=false;

	deleteMovements( pMovs );
	deleteMovements( pMovsKing );

	return check;
}

BOOL CHEventControlMoveManager::isKing(CHEventControlTable* pBoard,int color,int col, int row)
{
	BOOL ret=false;
	if ( color == BLACK )
	{
		if ( pBoard->getPiece(col,row) == B_KING)
			ret = true;
		else 
			ret=false;
	}
	else
	{
		if ( pBoard->getPiece(col,row) == W_KING)
			ret = true;
		else 
			ret=false;
	}

	return ret;

}

BOOL CHEventControlMoveManager::isRook(CHEventControlTable* pBoard,int color,int col,int row)
{
	BOOL ret=false;
	if ( color == BLACK )
	{
		if ( pBoard->getPiece(col,row) == B_ROOK)
			ret = true;
		else 
			ret=false;
	}
	else
	{
		if ( pBoard->getPiece(col,row) == W_ROOK)
			ret = true;
		else 
			ret=false;
	}

	return ret;
}

BOOL CHEventControlMoveManager::isQueen(CHEventControlTable* pBoard,int color,int col,int row)
{

	BOOL ret=false;
	if ( color == BLACK )
	{
		if ( pBoard->getPiece(col,row) == B_QUEEN)
			ret = true;
		else 
			ret=false;
	}
	else
	{
		if ( pBoard->getPiece(col,row) == W_QUEEN)
			ret = true;
		else 
			ret=false;
	}

	return ret;

}

BOOL CHEventControlMoveManager::isPiece(CHEventControlTable* pBoard,int Piece, int color, int col, int row)
{
	BOOL ret=false;
	
	if ( pBoard->getPiece(col,row) == Piece)
		ret = true;
	else 
		ret=false;
	
	return ret;

}

BOOL CHEventControlMoveManager::isBishop(CHEventControlTable* pBoard,int color,int col,int row)
{
	BOOL ret=false;
	if ( color == BLACK )
	{
		if ( pBoard->getPiece(col,row) == B_BISHOP)
			ret = true;
		else 
			ret=false;
	}
	else
	{
		if ( pBoard->getPiece(col,row) == W_BISHOP)
			ret = true;
		else 
			ret=false;
	}

	return ret;

}

BOOL CHEventControlMoveManager::isKnight(CHEventControlTable* pBoard,int color,int col,int row)
{
	BOOL ret=false;
	if ( color == BLACK )
	{
		if ( pBoard->getPiece(col,row) == B_KNIGHT)
			ret = true;
		else 
			ret=false;
	}
	else
	{
		if ( pBoard->getPiece(col,row) == W_KNIGHT)
			ret = true;
		else 
			ret=false;
	}

	return ret;

}


BOOL CHEventControlMoveManager::isPawn(CHEventControlTable* pBoard,int color,int col,int row)
{
	BOOL ret=false;
	if ( color == BLACK )
	{
		if ( pBoard->getPiece(col,row) == B_PAWN)
			ret = true;
		else 
			ret=false;
	}
	else
	{
		if ( pBoard->getPiece(col,row) == W_PAWN)
			ret = true;
		else 
			ret=false;
	}

	return ret;
}


TLISTMOVEMENTS  *CHEventControlMoveManager::removeHeadMov(TLISTMOVEMENTS * pLMovs, TMOVEMENT *pmov)
{
	TLISTMOVEMENTS  *pTmp;

	pTmp = pLMovs->psig;
	
	memcpy(pmov,pLMovs,sizeof(TMOVEMENT));

	delete pLMovs;

	return pTmp;
}

