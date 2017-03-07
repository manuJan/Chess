/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHEvenControlOperations.h
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

#if !defined(AFX_CHEVENCONTROLOPERATIONS_H__A20941A5_2C0D_4F06_A9CA_8B211BF04988__INCLUDED_)
#define AFX_CHEVENCONTROLOPERATIONS_H__A20941A5_2C0D_4F06_A9CA_8B211BF04988__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Sports\CH\Data\CHSession.h>
#include <Sports\CH\Data\CHMsgDefines.h>
#include <Core\TH\GTHMsgDefines.h>
#include <Core\G\GMsgDefines.h>


class CHMemoryDataBase;
class CHEvent;
class CHPoolResult;
class CHMatch;
class CHMatchResult;
class GScheduleDay;
class GMedallist;
class CHPgnMatch;

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
#define DRAW_F_PGN_NOTATION			"0F-0F"

class CHEvenControlOperations  
{
public:
	
	CHEvenControlOperations(CHMemoryDataBase * pMemory);
	virtual ~CHEvenControlOperations();

	
	// Locks Fucntion
	
	
public:
	
	void		calculatePointMatchResult(CHMatch *pMatch);
	void		paintShadow(CDC *pdc,int x,int y,const char *txt,COLORREF col,short align, int font,CGraphicWnd *w,int colorText);
	void		putScore(short idEvent,CHMatch *pMatch);
	void		finishMatch(CHMatch *pMatch,RWBoolean status=false);
	void		startListMatch(CHMatch *pMatch,RWBoolean status=false);

	RWBoolean	clearResults(CHMatch *pMatch);
	void		recalculateTeam(CHMatch *pMatch);
	void		manageByes(CHMatch *pMatch);
	
	// Descriptions 
	RWCString	getMatchResultDescription(CHMatchResult* pMatchResult);
	RWCString	getMatchMemberDescription(CHMatchResult *pMatchResult);
	CString		getSessionDescription(CHSession* pSession);
	CString		getCourtDescription(GCourt* pCourt);
			

	// EventControl 
	BOOL		statusForbidden	(CHMatch *pMatch,RWBoolean msg=true);
	BOOL		playForbidden	(CHMatch *pMatch, long idPlay);
	void		processStartGame(CHMatch *pMatch, long idPlay=0);


	// Pgn Files
	RWBoolean copyHistoricToMatch(CHPgnMatch* pPgnMatch, CWnd* pGUI);
	RWBoolean processResultsFromPgnFile(GSortedVector vMatchesInPlay,RWCString resultPath, GSortedVector &vPgnMatches);
	RWCString getPgnNotation(CHMatch* pMatch);
	RWCString getPgnNotation(GTHHistoric* pHistoric, RWBoolean withPiece/*=false*/);
	RWCString getPiecePgnNotation(short Piece);
	int		  getPgnNotationPiece(RWCString Piece, CHMatchResult::side color);
	RWBoolean isValidCol(RWCString col);
	int		  getCol(RWCString col);
	void	  emptyBlancks(RWCString &value);

	void processPlay(CWnd* pGUI, CHMatch* pMatch, RWCString playWhite, CHMatchResult::side color, int numPlay);

private:
	CHMemoryDataBase *  pMemory;
	
};

#endif // !defined(AFX_CHEVENCONTROLOPERATIONS_H__A20941A5_2C0D_4F06_A9CA_8B211BF04988__INCLUDED_)
