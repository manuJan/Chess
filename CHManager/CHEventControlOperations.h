/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHEventControlOperations.h
*	Description	:
*
*	Author		:Chess Team
*	Date created:21/12/2005
* 	Project		:Chess Management
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/


#pragma once
#include "CHManagerDefs.h"

class CHMemoryDataBase;
class CHEvent;
class CHPoolResult;
class CHMatch;
class CHMatchResult;

/*class CHPgnMatch;

#define PAWN_PGN_NOTATION	""
#define KNIGHT_PGN_NOTATION	"N"
#define BISHOP_PGN_NOTATION	"B"
#define ROOK_PGN_NOTATION	"R"
#define QUEEN_PGN_NOTATION	"Q"
#define KING_PGN_NOTATION	"K"

#define EAT_PGN_NOTATION	"x"
#define CHECK_PGN_NOTATION	"+"
#define CHECKMATE_PGN_NOTATION	"#"
#define SH_CASTLING_PGN_NOTATION	"O-O"
#define LG_CASTLING_PGN_NOTATION	"O-O-O"

#define WHITE_WINNER_PGN_NOTATION	"1-0"
#define WHITE_BLACK_PGN_NOTATION	"0-1"
#define DRAW_PGN_NOTATION			"1/2-1/2"
#define WHITE_WINNER_F_PGN_NOTATION	"1F-0F"
#define WHITE_BLACK_F_PGN_NOTATION	"0F-1F"
#define DRAW_F_PGN_NOTATION			"0F-0F"*/

class CHEventControlOperations  
{
public:
	
	CHEventControlOperations(MSLGUIEx* pGUIEx);
	virtual ~CHEventControlOperations();
		
	// Locks Fucntion
		
public:
	
	void		calculatePointMatchResult(CHMatch *pMatch);
	void		finishMatch(CHMatch *pMatch, bool status=false);
	void		startListMatch(CHMatch *pMatch, bool status=false);
	void		setScore(long idEvent,CHMatch *pMatch);

	bool		clearResults(CHMatch *pMatch);
	void		recalculateTeam(CHMatch *pMatch);
		
	// EventControl 
	bool		statusForbidden	(CHMatch *pMatch, bool msg=true);
	bool		playForbidden	(CHMatch *pMatch, long idPlay);
	void		processStartGame(CHMatch *pMatch, long idPlay=0);


	// Pgn Files
	/*bool	  copyHistoricToMatch(CHPgnMatch* pPgnMatch, CWnd* pGUI);
	bool	  processResultsFromPgnFile(GSortedVector vMatchesInPlay,MSLString resultPath, GSortedVector &vPgnMatches);
	MSLString getPgnNotation(CHMatch* pMatch);
	MSLString getPgnNotation(GTHHistoric* pHistoric, RWBoolean withPiece=false);
	MSLString getPiecePgnNotation(short Piece);
	int		  getPgnNotationPiece(MSLString Piece, CHMatchResult::side color);
	bool	 isValidCol(MSLString col);
	int		  getCol(MSLString col);
	void	  emptyBlancks(MSLString &value);
	void	  processPlay(CHMatch* pMatch, MSLString playWhite, CHMatchResult::side color, int numPlay);*/

private:

	MSLGUIEx* m_pGUIEx;
};


