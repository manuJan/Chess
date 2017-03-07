/*************************************************************************************
*			© Copyright MSL Software, S.L., 2001
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHStatisticDefines.h
*	Description	:General Defines Of Chess Statistics
*
*	Author		:CH Team
*	Date created:
* 	Project		:Chess DLL
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

// ------ Datas ---------
#define DATA_PLAYER							1
#define DATA_NUMPLAY						2
#define DATA_PIECE							3
#define DATA_OLDPOSI						4
#define DATA_NEWPOSI						5
#define DATA_RESULT							6
#define DATA_EATPIECE						7
#define DATA_GENERAL_PURPOSE				8

// ------ Jugadas -------
#define PLAY_MOVEMENT						1
#define PLAY_SHORT_CASTLING					2
#define PLAY_LONG_CASTLING					3
#define PLAY_WHITE_WINNER					4
#define PLAY_BLACK_WINNER					5
#define PLAY_DRAW							6
#define PLAY_WHITE_WINNER_F					7
#define PLAY_BLACK_WINNER_F					8
#define PLAY_DRAW_F							9

//------------- EVENTS ----------------------//
#define EV_MOVE								1
#define EV_EAT								2
#define EV_SHORT_CASTLING					3
#define EV_LONG_CASTLING					4
#define EV_CHECK							5
#define EV_CHECKMATE						6
#define EV_PAWN								7
#define EV_KNIGHT							8
#define EV_BISHOP							9
#define EV_ROOK								10
#define EV_QUEEN							11
#define EV_KING								12
#define EV_PROMOTE							13
#define EV_WHITE							14
#define EV_BLACK							15
#define EV_WHITE_WINNER						16
#define EV_BLACK_WINNER						17
#define EV_DRAW								18
#define EV_WHITE_WINNER_F					19
#define EV_BLACK_WINNER_F					20
#define EV_DRAW_F							21
#define EV_EMPTY							22
