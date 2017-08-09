#pragma once
#include <OVR/GUI/THOVR2CIS/GTHCISDefs.h>

/////////////////////////////////////////////////////////////////////
///////////////  SCREEN DESIGNS  ////////////////////////////////////
/////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////
///////////////  LAYER LIST  /////////////////////
//////////////////////////////////////////////////

#define LST_STARTLIST						3000

#define COL_STL_GAME						0
#define COL_STL_SEED_WHITE					1
#define COL_STL_TITLE_WHITE					2
#define COL_STL_FLAG_WHITE					3
#define COL_STL_NAME_WHITE					4
#define COL_STL_NOC_WHITE					5
#define COL_STL_WHITE_POINTS				6
#define COL_STL_BLACK_POINTS				7
#define COL_STL_SEED_BLACK					8
#define COL_STL_TITLE_BLACK					9
#define COL_STL_FLAG_BLACK					10
#define COL_STL_NAME_BLACK					11
#define COL_STL_NOC_BLACK					12

#define LST_RESULTS							3001
#define COL_RES_GAME						0
#define COL_RES_SEED_WHITE					1
#define COL_RES_TITLE_WHITE					2
#define COL_RES_FLAG_WHITE					3
#define COL_RES_NAME_WHITE					4
#define COL_RES_NOC_WHITE					5
#define COL_RES_WHITE_POINTS				6
#define COL_RES_RESULT						7
#define COL_RES_BLACK_POINTS				8
#define COL_RES_SEED_BLACK					9
#define COL_RES_TITLE_BLACK					10
#define COL_RES_FLAG_BLACK					11
#define COL_RES_NAME_BLACK					12
#define COL_RES_NOC_BLACK					13
		
#define LST_TEAM_STARTLIST					3002

#define COL_TEAM_STL_GAME					0
#define COL_TEAM_STL_SEED_WHITE				1
#define COL_TEAM_STL_FLAG_WHITE				2
#define COL_TEAM_STL_NAME_WHITE				3
#define COL_TEAM_STL_NOC_WHITE				4
#define COL_TEAM_STL_WHITE_POINTS			5
#define COL_TEAM_STL_BLACK_POINTS			6
#define COL_TEAM_STL_SEED_BLACK				7
#define COL_TEAM_STL_FLAG_BLACK				8
#define COL_TEAM_STL_NAME_BLACK				9
#define COL_TEAM_STL_NOC_BLACK				10

#define LST_MATCH_HEADER_1					2003
#define COL_HEA_MN_LABEL					0
#define COL_HEA_MN							1

#define LST_MATCH_HEADER_2					2004
#define COL_HEA_FLAG_1						0
#define COL_HEA_NAME_1						1
#define COL_HEA_NOC_1						2
#define COL_HEA_NOC_2						4
#define COL_HEA_NAME_2						5
#define COL_HEA_FLAG_2						6

#define LST_MATCH_HEADER_3					2005
#define COL_HEA_COLOR_1						0
#define COL_HEA_MASTER_LABEL_1				2
#define COL_HEA_MASTER_1					3
#define COL_HEA_RATING_LABEL_1				4
#define COL_HEA_RATING_1					5
#define COL_HEA_RATING_LABEL_2				7
#define COL_HEA_RATING_2					8
#define COL_HEA_MASTER_LABEL_2				9
#define COL_HEA_MASTER_2					10
#define COL_HEA_COLOR_2						11

#define LST_MATCH_HEADER_TOTAL				2006
#define COL_HEA_WINNER_HOME					0
#define COL_HEA_TOTAL_HOME					2
#define COL_HEA_TOTAL						4
#define COL_HEA_TOTAL_AWAY					6
#define COL_HEA_WINNER_AWAY					8


#define LST_SUBMATCH_RESULTS				2007
#define COL_HEA_COLOR_HOME					0
#define COL_HEA_MASTER_HOME					1
#define COL_HEA_FLAG_HOME					2
#define COL_HEA_NAME_HOME					3
#define COL_HEA_NOC_HOME					4
#define COL_HEA_RESULT_HOME					5
#define COL_HEA_STATUS						6
#define COL_HEA_RESULT_AWAY					7
#define COL_HEA_FLAG_AWAY					8
#define COL_HEA_NAME_AWAY					9
#define COL_HEA_NOC_AWAY					10
#define COL_HEA_MASTER_AWAY					11
#define COL_HEA_COLOR_AWAY					12

#define LIST_CH_SUMMARY						1100
#define COL_CHPRS_RK						0
#define COL_CHPRS_FLAG						1
#define COL_CHPRS_NOC						2
#define COL_CHPRS_PLAYER					3
#define COL_CHPRS_PLAYED					4
#define COL_CHPRS_WON						5
#define COL_CHPRS_TIED						6
#define COL_CHPRS_LOST						7
#define COL_CHPRS_PTS						8
#define COL_CHPRS_MATCH_PTS					9
#define COL_CHPRS_SEPARATOR					10
#define COL_CHPRS_MATCHES					11

/////////////////////////////////////////////////
///////////////  REFERENCES TYPES  ///////////////
//////////////////////////////////////////////////

#define REF_TITLE_SDESC		"TITLE_SDESC"
#define REF_TITLE_LDESC		"TITLE_LDESC"
#define REF_SEED			"SEED"		
#define REF_TITLE			"TITLE"		
#define REF_PREV_PTS		"PREV_PTS"		
#define REF_RESULT			"RESULT"
#define REF_POINTS_F		"POINTS_F"
#define REF_MATCH_POINTS	"MATCH_POINTS"
#define REF_OPPRK_RESULT	"OPPRK_RESULT"