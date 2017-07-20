/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : ARManagerDefs.h
*   Description : 
*
*   Author      : J.Juste
*   Date created: 12-Ene-2008
*   Project     : AR Manager
*
*   Modification history
*   By      :
*   Date    :
*   Changes :
*
*****************************************************************************************/

#pragma once
#include <OVR\GUI\GUIMANAGER\GUIManagerDefs.h>
#include <OVR\GUI\GUITHMANAGER\GUITHManagerDefs.h>
#include <OVR\GUI\MSLFlags\MSLFlags.h>
#include <OVR\TOOLS\MSLTools\MSLToolsIncs.h>

/*********************************** USER MESSAGES **************************************/
#define UM_CHMANAGER								WM_USER+3000
#define UM_REGISTER_CREATED							UM_CHMANAGER+1
#define UM_CHANGE_UMPIRE							UM_CHMANAGER+2
#define UM_CHANGE_MATCH								UM_CHMANAGER+3
#define UM_GOTO_NEXT_MATCH							UM_CHMANAGER+4

/*********************************** GUI *************************************************/
#define CH_GUI										3000

/************************************* STYLES ********************************************/
#define CHM_ID_STY_EDIT_DATAENTRY					CH_GUI+1

/************************************* COLORS ********************************************/
#define COLOR_GREEN_ODD								RGB(80,248,185)
#define COLOR_GREEN_EVEN							RGB(190,252,228)
#define COLOR_GREEN_SELECTED						RGB(9,208,134)

#define COLOR_BLUE_ODD								RGB(153,217,234)
#define COLOR_BLUE_EVEN								RGB(103,200,224)
#define COLOR_BLUE_SELECTED							RGB(49,180,213)

#define COLOR_GREEN_HEADER							RGB(79,247,184)
#define COLOR_BLUE_HEADER							RGB(0,128,183)

/************************************* BITMAPS ********************************************/
#define BM_LOAD										CH_GUI+1
#define BM_SAVE										CH_GUI+2
#define BM_TARGET									CH_GUI+3

//////////////////////////////////// SPORT //////////////////////////////////////////////
/*********************************** ARSPORTGUI *****************************************/
#define CHSPORTGUI_ID								CH_GUI+10
	#define LB_AUTO_PROG							CHSPORTGUI_ID+1
	#define FRM_AUTO_PROG							CHSPORTGUI_ID+2
	#define CH_AUTO_PROG							CHSPORTGUI_ID+3

//////////////////////////////////// EVENTS //////////////////////////////////////////////
/*********************************** CHEnableEventGUIEx *********************************/

	#define C_EV_TYPE								C_ENABLE_EVENT+1
	#define C_EV_REG_TYPE							C_ENABLE_EVENT+2
	#define C_EV_INSCRIPTIONS						C_ENABLE_EVENT+3
	#define C_EV_CONST_RATING						C_ENABLE_EVENT+4
	#define C_EV_BYE_POINTS							C_ENABLE_EVENT+5
	#define C_EV_BRONZES							C_ENABLE_EVENT+6	
	#define C_EV_CODE_REPORTS						C_ENABLE_EVENT+7
	#define C_EV_TEAM_CFG							C_ENABLE_EVENT+8

	#define CB_TEAM_CFG								CH_GUI+20
	
/*********************************** CHEventCriteriaGUIEx *******************************/
#define CHEVENTCRITERIAGUIEX_ID						CH_GUI+110
	#define LB_CH_EVENT_CRITERIA					CHEVENTCRITERIAGUIEX_ID+1
	#define GR_CH_EVENT_CRITERIA					CHEVENTCRITERIAGUIEX_ID+2
		#define C_ORDER								GR_CH_EVENT_CRITERIA+1
		#define C_CRITERIUM							GR_CH_EVENT_CRITERIA+2

/*********************************** CHEventCriteriaGUIEx *******************************/
#define CHRATINGDIFGUIEX_ID							CH_GUI+115
	#define LB_CH_RATING_DIF						CHRATINGDIFGUIEX_ID+1
	#define GR_CH_RATING_DIF						CHRATINGDIFGUIEX_ID+2
		#define C_CODE								GR_CH_RATING_DIF+1
		#define C_PROBABILITY						GR_CH_RATING_DIF+2
		#define C_DIFFERENCE						GR_CH_RATING_DIF+3

/*********************************** CHPhaseGUIEx *******************************/
#define CHPHASEGUIEX_ID								GTHPHASEGUIEX_ID
	#define C_PHASE_TYPE							C_PHASE_STATUS+1

//////////////////////////////////// INSCRIPTIONS //////////////////////////////////////////////
/*********************************** AREntriesGUI *********************************/
	#define	CB_MASTER_TYPE							CH_GUI+120
	#define C_REG_MASTER_TYPE						C_NAME_REG_ENTRIES+1

/********************************* CHEntriesToolBar *******************************/
	#define LX_FIDE_LOAD							CH_GUI+125
	#define LX_SEED_CALCULATION						CH_GUI+126
	
/****************************** AREntriesEventGUIEx *******************************/

	#define C_RATING							C_INSC_EV_ENTRIES+1
	#define	C_SEED								C_INSC_EV_ENTRIES+2
	#define C_KCONST							C_INSC_EV_ENTRIES+3
	
/****************************** CHEntriesMemberGUIEx *******************************/

	#define C_MEMBER_RATING						C_DESC_MEMBER+1
	#define C_MEMBER_KCONST						C_DESC_MEMBER+2

/******************************* CHInitialLoadGUI ***************************************************/
#define CHINITIALLOADGUI_ID							CH_GUI+130	

/******************************** CHManagerPhaseGUI ********************************/
#define CHManagerPhaseGUI_ID					CH_GUI+130

/*********************************** CHMatchGUIEx **********************************/
#define CHMatchGUIEx_ID							CH_GUI+150
	#define	C_MT_ROUND								C_MT_AWAY_RESULT+1

/*********************************** CHMatchToolBar **********************************/
#define TB_CHMATCH_ID							CH_GUI+170
#define LX_PHASE_CHDRAW								TB_CHMATCH_ID+1
#define LX_MATCH_CONFIG								TB_CHMATCH_ID+2

/****************** CHMatchConfigurationGUI *********************************/
	#define CHMATCHCONFIGGUI_ID					CH_GUI+180
	#define	CB_MATCH_CNF				CHMATCHCONFIGGUI_ID+1
	#define LB_MATCH_TITLE				CHMATCHCONFIGGUI_ID+2
	#define GR_MATCH_CNF				CHMATCHCONFIGGUI_ID+3
		#define C_DATE_MATCH_CNF			GR_MATCH_CNF+1
		#define C_SESSI_MATCH_CNF			GR_MATCH_CNF+2		
		#define C_COURT_MATCH_CNF			GR_MATCH_CNF+3
		#define C_GAME_MATCH_CNF			GR_MATCH_CNF+4
		#define C_STATU_MATCH_CNF			GR_MATCH_CNF+5
	#define LB_MATCHRESULT_TITLE		CHMATCHCONFIGGUI_ID+4
	#define GR_MATCHRESULTS_CNF			CHMATCHCONFIGGUI_ID+5
		#define C_HOME_MATCHR_CNF			GR_MATCHRESULTS_CNF+1
		#define C_HOME_RESULT_CNF			GR_MATCHRESULTS_CNF+2
		#define C_AWAY_MATCHR_CNF			GR_MATCHRESULTS_CNF+3
		#define C_AWAY_RESULT_CNF			GR_MATCHRESULTS_CNF+4
	#define GR_MATCHMEMBERS_CNF			CHMATCHCONFIGGUI_ID+6
		#define C_HOME_MATCHM_CNF			GR_MATCHMEMBERS_CNF+1
		#define C_AWAY_MATCHM_CNF			GR_MATCHMEMBERS_CNF+2
	#define CB_MATCHMEMBERS_CNF			CHMATCHCONFIGGUI_ID+7
	#define LB_MATCHJUDGE_TITLE			CHMATCHCONFIGGUI_ID+8
	#define GR_MATCHJUDGE_CNF			CHMATCHCONFIGGUI_ID+9
		#define C_NAME_MATCHJ_CNF			GR_MATCHJUDGE_CNF+1
		#define C_FUNCT_MATCHJ_CNF			GR_MATCHJUDGE_CNF+2
	#define BT_UMPIRE					CHMATCHCONFIGGUI_ID+10
	#define LB_SUBMATCHES_TITLE			CHMATCHCONFIGGUI_ID+11
	#define GR_SUBMATCHES_CNF			CHMATCHCONFIGGUI_ID+12
		#define C_DATE_SUBMATCH_CNF			GR_SUBMATCHES_CNF+1
		#define C_SESSI_SUBMATCH_CNF		GR_SUBMATCHES_CNF+2		
		#define C_SUBMC_SUBMATCH_CNF		GR_SUBMATCHES_CNF+3
		#define C_COURT_SUBMATCH_CNF		GR_SUBMATCHES_CNF+4
		#define C_STATU_SUBMATCH_CNF		GR_SUBMATCHES_CNF+5
		#define C_HOME_SUBMATCH_CNF			GR_SUBMATCHES_CNF+6
		#define C_HOME_COL_SUBMATCH_CNF		GR_SUBMATCHES_CNF+7
		#define C_AWAY_SUBMATCH_CNF			GR_SUBMATCHES_CNF+8
		#define C_AWAY_COL_SUBMATCH_CNF		GR_SUBMATCHES_CNF+9	
		#define C_AWAY_COL_RESULT_CNF		GR_SUBMATCHES_CNF+10
	#define BT_GO_PREV					CHMATCHCONFIGGUI_ID+16
	#define BT_GO_NEXT					CHMATCHCONFIGGUI_ID+17

/****************** CHSubMatchConfigurationGUIEx *********************************/
	#define CHSUBMATCHCONFIGGUIEX_ID		CH_GUI+220
		#define CB_SUBMATCH_CNF					CHSUBMATCHCONFIGGUIEX_ID+1

/****************** CHMatchConfigurationToolbar **********************************/
	#define CHMATCHCONFIGURATION_TB			CH_GUI+221
		#define BT_AUTO_SET					CHMATCHCONFIGURATION_TB+1
		#define BT_REMOVE_SET				CHMATCHCONFIGURATION_TB+2
		#define BT_CHANGE_SIDE				CHMATCHCONFIGURATION_TB+3
		#define BT_PRESS_WINNER_WHITE		CHMATCHCONFIGURATION_TB+4
		#define BT_PRESS_TIED				CHMATCHCONFIGURATION_TB+5
		#define BT_PRESS_WINNER_BLACK		CHMATCHCONFIGURATION_TB+6
		#define BT_PRESS_WINNER_WHITE_F		CHMATCHCONFIGURATION_TB+7
		#define BT_PRESS_TIED_F				CHMATCHCONFIGURATION_TB+8
		#define BT_PRESS_WINNER_BLACK_F		CHMATCHCONFIGURATION_TB+9
		#define BT_PRESS_EMPTY				CHMATCHCONFIGURATION_TB+10
		#define BT_CHECK_AUTO_FINISH		CHMATCHCONFIGURATION_TB+11
		#define BT_FINISH					CHMATCHCONFIGURATION_TB+12


/************ TEChairUmpireGUIEx ***********************/
#define CHUMPIREGUIEX_ID					CH_GUI+200
	#define CK_ALL_OFFICIALS			CHUMPIREGUIEX_ID+1
	#define GR_CHAIR_UMPIRE				CHUMPIREGUIEX_ID+2
		#define C_NOC_CHAIRUMP				GR_CHAIR_UMPIRE+1
		#define C_NAME_CHAIRUMP				GR_CHAIR_UMPIRE+2
		#define C_FUNCTION_CHAIRUMP			GR_CHAIR_UMPIRE+3


/******************************* AREventControlGUIEx ****************************************/
#define AREVENTCONTROLGUIEX_ID					CH_GUI+220
	#define C_EC_RANK								AREVENTCONTROLGUIEX_ID+1
	#define C_EC_SCORE								AREVENTCONTROLGUIEX_ID+2
	#define C_EC_QUALITATIVE						AREVENTCONTROLGUIEX_ID+3
	#define C_EC_TENS								AREVENTCONTROLGUIEX_ID+4
	#define C_EC_INNER								AREVENTCONTROLGUIEX_ID+5
	#define C_EC_RECORD								AREVENTCONTROLGUIEX_ID+6
	#define C_EC_TIES								AREVENTCONTROLGUIEX_ID+7
	#define C_EC_END								AREVENTCONTROLGUIEX_ID+8
	#define C_EC_MTS								AREVENTCONTROLGUIEX_ID+9
	#define C_MR_ARROW								AREVENTCONTROLGUIEX_ID+10
	#define C_EC_PORT_DOS							AREVENTCONTROLGUIEX_ID+11
	#define C_EC_PORT_MTS							AREVENTCONTROLGUIEX_ID+12
	#define MN_DOUBT_ARROW							AREVENTCONTROLGUIEX_ID+13
		#define MN_OPT_DOUBT							MN_DOUBT_ARROW+1
		#define MN_OPT_CONFIRMED						MN_DOUBT_ARROW+2
		#define MN_OPT_ADD_EXTRA						MN_DOUBT_ARROW+3
		#define MN_OPT_REM_EXTRA						MN_DOUBT_ARROW+4
	#define PRG_DATA_ENTRY							AREVENTCONTROLGUIEX_ID+14
	
/******************************* AREventControlArrowsGUIEx ****************************************/
#define AREVENTCONTROLARROWSGUIEX_ID				CH_GUI+240
/******************************* AREventControlEndsGUIEx ******************************************/
#define AREVENTCONTROLENDSGUIEX_ID					CH_GUI+245
/******************************* AREventControlSplitsGUIEx ****************************************/
#define AREVENTCONTROLSPLITSGUIEX_ID				CH_GUI+250
/******************************* AREventControlSetsGUIEx ******************************************/
#define AREVENTCONTROLSETSGUIEX_ID					CH_GUI+255

/******************************* AREventControlToolBar ****************************************/
	#define RD_ARROW								CH_GUI+270
	#define RD_END									CH_GUI+271
	#define RD_SPLIT								CH_GUI+272
	#define RD_SET									CH_GUI+273
	#define BT_STATUS								CH_GUI+274
	#define BT_MATCH_OFFICIAL						CH_GUI+275
	#define BT_PHASE_OFFICIAL						CH_GUI+276
	#define CB_FIRST_TRGT							CH_GUI+277
	#define CB_LAST_TRGT							CH_GUI+278
	#define CB_SPLIT								CH_GUI+279
	#define BT_LOAD_RESULTS							CH_GUI+280
	#define BT_SAVE_RESULTS							CH_GUI+281
	#define BT_REMOVE_PHASE_RESULTS					CH_GUI+282
	#define BT_REMOVE_MATCH_RESULTS					CH_GUI+283
	#define BT_MEDALS_DISTANCE						CH_GUI+284
	#define BT_CALC_RECORDS							CH_GUI+285
	#define BT_CALC_RANKS							CH_GUI+286
	#define MN_LOAD_RESULTS							CH_GUI+287
	#define BT_MATCH_UNOFFICIAL						CH_GUI+288
	#define BT_PHASE_UNOFFICIAL						CH_GUI+289
	#define	BT_RANKING_TO_BIB						CH_GUI+290
	#define BT_TARGET_TO_BIB						CH_GUI+291
	#define BT_DATA_TEST							CH_GUI+292
		#define MN_LOAD_TOTALS							MN_LOAD_RESULTS+1
		#define MN_LOAD_END_BY_END						MN_LOAD_RESULTS+2
	#define BT_DISK_TOSS							CH_GUI+293

/******************************* ARDistanceGUIEx **************************************************/
#define ARDISTANCEGUIEX_ID							CH_GUI+290
	#define GR_DISTANCE								ARDISTANCEGUIEX_ID+1
		#define C_DISTANCE_DESC						GR_DISTANCE+1		
	#define CB_DISTANCE								ARDISTANCEGUIEX_ID+2
	#define LB_DISTANCE								ARDISTANCEGUIEX_ID+3

/***************************** ARInscriptionLineGUIEx ***********************************************/
#define ARINSCRIPTIONLINEGUIEX_ID					CH_GUI+300
	#define GR_INSCRIPTION_LINE						ARINSCRIPTIONLINEGUIEX_ID+1
		#define C_INS_LINE_CREATE						GR_INSCRIPTION_LINE+1
		#define C_INS_LINE_INSCRIPTED					GR_INSCRIPTION_LINE+2
		#define C_INS_LINE_DIVISION						GR_INSCRIPTION_LINE+3
		#define C_INS_LINE_SURNAME						GR_INSCRIPTION_LINE+4
		#define C_INS_LINE_NAME							GR_INSCRIPTION_LINE+5
		#define C_INS_LINE_FITA_CODE					GR_INSCRIPTION_LINE+6
		#define C_INS_LINE_NOC_CODE						GR_INSCRIPTION_LINE+7
		#define C_INS_LINE_BIRTHDAY						GR_INSCRIPTION_LINE+8		
	#define GR_LOADING_DATA							ARINSCRIPTIONLINEGUIEX_ID+2
		#define C_LOADING_DESC							GR_LOADING_DATA+1
		#define C_LOADING_CODE							GR_LOADING_DATA+2
		#define C_LOADING_STATUS						GR_LOADING_DATA+3
	#define PRG_LOADING_DATA						ARINSCRIPTIONLINEGUIEX_ID+3


/***************************** ARInscriptionLineToolBar ***********************************************/
#define TB_ARINSCRIPTIONLINE_ID						CH_GUI+310
#define TB_ARRECORDLINE_ID						CH_GUI+310
	#define LX_LOAD_ENTRIES								TB_ARINSCRIPTIONLINE_ID+1
	#define LX_SAVE_ENTRIES								TB_ARINSCRIPTIONLINE_ID+2
	#define LX_INITIAL_LOAD								TB_ARINSCRIPTIONLINE_ID+3	
	#define LX_EXIT										TB_ARINSCRIPTIONLINE_ID+4
	#define PR_ENABLE_ALL								TB_ARINSCRIPTIONLINE_ID+5
	#define PR_ENABLE_NOTINS							TB_ARINSCRIPTIONLINE_ID+6
	#define PR_DISABLE_ALL								TB_ARINSCRIPTIONLINE_ID+7
	#define LX_REMOVE_ALLRECORDS						TB_ARINSCRIPTIONLINE_ID+8
	


/***************************** ARRecordsLoadGUI ***************************************************/
#define ARRECORDSLOADGUI_ID							CH_GUI+321

/***************************** ARRecordLineGUIEx ***********************************************/
#define ARRECORDLINEGUIEX_ID						CH_GUI+330
	#define GR_RECORD_LINE							ARRECORDLINEGUIEX_ID+1

		#define C_REC_LINE_CREATE						GR_RECORD_LINE+1
		#define C_REC_LINE_CREATED						GR_RECORD_LINE+2
		#define C_REC_LINE_GENDER						GR_RECORD_LINE+3
		#define C_REC_LINE_EVENT						GR_RECORD_LINE+4
		#define C_REC_LINE_TYPE							GR_RECORD_LINE+5
		#define C_REC_LINE_AREA							GR_RECORD_LINE+6
		#define C_REC_LINE_FITA_NUMBER					GR_RECORD_LINE+7
		#define C_REC_LINE_NAME							GR_RECORD_LINE+8
		#define C_REC_LINE_SURNAME						GR_RECORD_LINE+9
		#define C_REC_LINE_NOC_CODE						GR_RECORD_LINE+10
		#define C_REC_LINE_DATE							GR_RECORD_LINE+11
		#define C_REC_LINE_MARK							GR_RECORD_LINE+12
		#define C_REC_LINE_LOCATION						GR_RECORD_LINE+13
		#define C_REC_LINE_COUNTRY						GR_RECORD_LINE+14

	#define GR_REC_LOADING_DATA						ARRECORDLINEGUIEX_ID+2

		#define C_REC_LOADING_DESC						GR_REC_LOADING_DATA+1
		#define C_REC_LOADING_CODE						GR_REC_LOADING_DATA+2
		#define C_REC_LOADING_STATUS					GR_REC_LOADING_DATA+3

	#define REC_PRG_LOADING_DATA					ARRECORDLINEGUIEX_ID+3

/********************************* ARMedalsEventGUI ********************************/
#define ARMEDALSEVENTGUI_ID							CH_GUI+350

/***************************** ARMedalsEventToolBar ********************************/
#define TB_ARMEDALSEVENT_ID							CH_GUI+351
	#define BT_SET_MEDALS								TB_ARMEDALSEVENT_ID+1
	#define BT_DEL_MEDALS								TB_ARMEDALSEVENT_ID+2
	
/************************** ARSplitMatchResultGUIEx ********************************/
#define ARSPLITMATCHRESULTGUIEX_ID					CH_GUI+355
	#define GR_SPLITMATCHRESULT							ARSPLITMATCHRESULTGUIEX_ID+1

		#define C_SPR_RK								GR_SPLITMATCHRESULT+1
		#define C_SPR_RK_PO								GR_SPLITMATCHRESULT+2
		#define C_SPR_FLAG								GR_SPLITMATCHRESULT+3
		#define C_SPR_NAME								GR_SPLITMATCHRESULT+4
		#define C_SPR_NOC								GR_SPLITMATCHRESULT+5
		#define C_SPR_RESULT							GR_SPLITMATCHRESULT+6
		#define C_SPR_MEDAL								GR_SPLITMATCHRESULT+7
	
/********************************* ARFieldGUI **************************************/
#define ARFIELDGUI_ID								CH_GUI+360
	#define GR_FIELD										ARFIELDGUI_ID+1
		#define	C_FIELD_DATE								GR_FIELD+1
		#define	C_FIELD_TIME								GR_FIELD+2
		#define	C_FIELD_TARGET								GR_FIELD+3

/********************************* ARFieldToolBar *********************************/
#define TB_ARFIELDGUI_ID							CH_GUI+365

/******************************* ARSplitPhaseGUIEx ************************************************/
#define C_SPLITPHASE_TYPE						C_SPLITPHASE_DESC+1
#define C_SPLITPHASE_DISTANCE					C_SPLITPHASE_DESC+2
#define C_SPLITPHASE_NUMENDS					C_SPLITPHASE_DESC+3
#define C_SPLITPHASE_NUMARROWS					C_SPLITPHASE_DESC+4
#define C_SPLITPHASE_STARTDATE					C_SPLITPHASE_DESC+5
#define C_SPLITPHASE_STARTTIME					C_SPLITPHASE_DESC+6

/******************************* ARRecordsGUI *****************************************************/
#define C_REC_INNERS							C_REC_EX+1

/********************************* CHTreeGUIEx ****************************************************/
#define MN_FITA_ITEM							MN_PRG_REMOVE_SUBMATCH+1
#define MN_OLYMPIC_ITEM							MN_PRG_REMOVE_SUBMATCH+2
#define MN_FIELD_ITEM							MN_PRG_REMOVE_SUBMATCH+3

#define MN_FITA_SS_ITEM							MN_PRG_REMOVE_SUBMATCH+4
#define MN_FITA_HMTOTAL_ITEM					MN_PRG_REMOVE_SUBMATCH+5
#define MN_OLY_SS_ITEM							MN_PRG_REMOVE_SUBMATCH+6
#define MN_OLY_HMTOTAL_ITEM						MN_PRG_REMOVE_SUBMATCH+7
#define MN_FLD_SS_ITEM							MN_PRG_REMOVE_SUBMATCH+6
#define MN_FLD_HMTOTAL_ITEM						MN_PRG_REMOVE_SUBMATCH+7

/***************************** WARNINGS && ERRORS ****************************************/
#define ARM_ID_ERROR_MATCH_TIED						10000
#define ARM_ID_ERROR_NEXT_PHASE_BYES				10001
#define ARM_ID_WARNING_GENERATE_MEMBERS				10002
#define ARM_ID_WARNING_REMOVEWORST					10003
#define ARM_ID_WARNING_CALCULATERANKS				10004
#define ARM_ID_WARNING_NEXTPHASEBYES				10005
#define ARM_ID_WARNING_NEXTPHASEOFFICIAL			10006
#define ARM_ID_WARNING_PORT_MTS_AREUSURE			10007
#define ARM_ID_WARNING_PORT_DOS_AREUSURE			10008
#define ARM_ID_ERROR_MTSEND							10009

struct drawInfo
{
	short firstTarget;
	short lastTarget;
	short compByTarget;
};


/************************************ Clases de Datos ************************************/
#define AREVENTCONTROLDATA							20000
#define AREVENTCONTROLSERIALDATA					20001



#define			__ARCOLUMNDATAENTRY					600
#define			__ARCOLUMNARROW						601
#define			__ARCOLUMNEND						602	