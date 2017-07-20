#ifndef _CHODF2DEFINES_H_
#define _CHODF2DEFINES_H_

#include <OVR/GUI/ODF2/ODFTHMngr/ODFTHManagerDefs.h>

#define DT_EVENT_DESCRIPTION		"DT_EVENT_DESCRIPTION"

/////////////////////////////////////////////
// PARTICIPANTS
/////////////////////////////////////////////
#define E2_ENTRY				"ENTRY"
	#define E2_RATING			"RATING"
	#define E2_SEED				"SEED"
	#define E2_KCONST			"KCONST"	
	#define E2_MASTER			"MASTER"
		
/////////////////////////////////////////////
// TEAMS
/////////////////////////////////////////////
//#define E2_GROUP					"GROUP"
//#define E2_ORDER					"ORDER"

/////////////////////////////////////////////
//RESULT
/////////////////////////////////////////////
#define UI										"UI"
#define MATCH									"MATCH"
#define UNIT_NUM								"UNIT_NUM"
#define TABLE									"TABLE"
#define STATUS									"STATUS"
#define WHITE									"WHITE"
#define BLACK									"BLACK"
#define WHITE_PTS								"WHITE_PTS"
#define BLACK_PTS								"BLACK_PTS"

#define EUE										"EUE"
#define	COLOR									"COLOR"

#define ER										"ER"

/////////////////////////////////////////////
// POOLSTANDINGS
/////////////////////////////////////////////
#define	IRM_POINTS			"IRM_POINTS"
#define ER							"ER"
#define MATCHES						"MATCHES"
	#define PLAYED							"PLAYED"	
	#define WON								"WON"
	#define LOST							"LOST"
	#define TIE								"TIE"	
	#define MATCH_POINTS					"MATCH_POINTS"

/////////////////////////////////////////////
// BRACKETS
/////////////////////////////////////////////

// CC @Bracket
#define CH_BRACKET_FNL						"FNL"			// Final
#define CH_BRACKET_BRN						"BRN"			// Bronze

// CC @BracketItems
#define CH_BRACKET_ITEM_QFL					"QFL"			// Quarterfinals (PH_QUARTERFINAL)
#define CH_BRACKET_ITEM_SFL					"SFL"			// Semi-finals (PH_SEMIFINAL, PH_CLAS_5_8, PH_CLAS_9_12)
#define CH_BRACKET_ITEM_FNL					"FNL"			// Finals (PH_GOLD_MEDAL, PH_BRONZE_MEDAL, PH_MATCH_5_6, PH_MATCH_7_8)

// CC @CompetitorPlace
#define CH_PLACE_BYE						"BYE"			// There is not competitor, the other team passes directly to the next round
#define CH_PLACE_UNK						"UNK"			// The competitor is not known yet

#define SR									"SR"
#define RANK_SWISS_RND						"RANK_SWISS_RND"
#define SCORE								"SCORE"
#define RES									"RES"
#define IRM									"IRM"


//////////////////////////////////////////////////////////
///////////// DT_CONFIG //////////////////////////////////
//////////////////////////////////////////////////////////
#define EC							"EC"
#define SESSION						"SESSION"
#define UNIT						"UNIT"

///////////////////////////////////////////////
// PLAY BY PLAY
//////////////////////////////////////////////
#define UAC					"UAC"
#define SERVICE_BREAK		"SERVICE_BREAK"	
#define	SET_SCORE_H			"SET_SCORE_H"
#define	SET_SCORE_A			"SET_SCORE_A"

#define A1					"A1"				//Ace - 1st Serve
#define A2					"A2"				//Ace - 2nd Serve
#define	DFAULT				"DF"				//Double Fault
#define	PR1					"PR1"				//Point to Receiver - 1st Serve
#define PR2					"PR2"				//Point to Receiver - 2nd Serve
#define PS1					"PS1"				//Point to Server - 1st Serve
#define	PS2					"PS2"				//Point to Server - 2nd Serve

#define START_LIST			"START_LIST"
#define INTERMEDIATE		"INTERMEDIATE"
#define OFFICIAL			"OFFICIAL"
#define UNOFFICIAL			"UNOFFICIAL"
#define LIVE				"LIVE"

#endif //_ARODF2DEFINES_H_
