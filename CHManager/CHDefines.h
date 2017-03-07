/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:LBDefines.h
*	Description	:
*
*	Author		:
*	Date created:
* 	Project		:
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

const int UM_DV_GUI				=WM_USER+100;

const int UM_SELECT_EVENT		=UM_DV_GUI+1;

//Defines de Form's view para Reports
#define CH_MEDALLIST_FORMVIEW			0
#define CH_MAIN_FORM					1
#define CH_INSCRIPTIONS_FORMVIEW		2
#define CH_CNFGNON_ATHLETES_FORMVIEW	3
#define CH_PROGRESSION_FORMVIEW			4
#define CH_FINAL_CLASS_FORMVIEW			5
#define CH_SCHEDULE_FORMVIEW			6
#define CH_EVENTCONTROL_FORM			7
#define CH_WEATHER_FORM					8


//Defines Generales
#define IDCOLBLUE			6000
#define IDCOLRED			6001
#define IDFNT_SUB			6002
#define FONT_STATUS			6003
#define IDBCKBLUE			6004
#define IDBCKRED			6005
#define FONT_VERYBIG		6006
#define FONT_EC				6007
#define IDCOLBLACK			6008
#define IDBCKCLOCK			6009
#define IDCOLWHITE			6010
#define FONT_NAMES			6011
#define IDBCKSCORERED		6012
#define IDBCKSCOREBLUE		6013
#define IDCOLYELLOW			6014
#define FONT_HEADER			6015
#define IDBCKGREY			6016
#define FONT_MEDIUM_SIZE	6017
#define IDBCKORANGE			6018
#define IDCOLDARKBLUE		6019
#define FONT_TITLES			6020
#define IDBCKGRIDREF		6021
#define FONT_REFEREES		6022
#define IDCOLSMOOBLUE		6023
#define FONT1				6024
#define FONT2				6025
#define FONT3				6026

	
//Colors
#define SKYBLUE		RGB(221,232,255)
#define ORANGE		RGB(255,220,210)
#define BLUEM		RGB(176,187,225)
#define BLUE_GUAY	RGB(102,153,204)
#define NAVYBLUE	RGB(0,0,198)

#define								DISCIPLIENGUI	5400
#define DIS_LBL_TITTLE				DISCIPLIENGUI+1
#define DIS_LBL_LINE				DISCIPLIENGUI+2
#define DIS_LBL_PROGRESSION			DISCIPLIENGUI+3
#define DIS_RAD_MANUAL				DISCIPLIENGUI+4
#define DIS_RAD_AUTO				DISCIPLIENGUI+5


//LBCCnfgEventsFormView
#define								EVENTSGUI		5500
#define LBL_PHASE					EVENTSGUI+1
#define LBL_LINE1					EVENTSGUI+2
#define LSTPHASES					EVENTSGUI+3
#define BMP_EVCHECK					EVENTSGUI+4
#define BMP_UNCHECK					EVENTSGUI+5
#define BMP_BRONZE					EVENTSGUI+6
#define LBL_EVENTS					EVENTSGUI+7
#define LBL_LINEA					EVENTSGUI+8
#define LBL_SEX						EVENTSGUI+9
#define LBL_NINS					EVENTSGUI+10
#define LBL_PHASEACT				EVENTSGUI+11
#define LBL_STARTDATE				EVENTSGUI+12
#define FRM_EVINF					EVENTSGUI+13
#define LSTCBO_TYPE_EVENT			EVENTSGUI+14
#define LSTCBO_TYPE_MODE			EVENTSGUI+15
#define FONT_MED					EVENTSGUI+16
#define GREEN						EVENTSGUI+17
#define BUT_MODIFY_PHASE			EVENTSGUI+18
#define LSTCBO_TYPE_PHASE			EVENTSGUI+19
#define LSTCBO_TYPE_MATCH_WINNER	EVENTSGUI+20
#define BUTTBCK						EVENTSGUI+21
#define LBL_LINE2					EVENTSGUI+25
#define LBL_RANK					EVENTSGUI+28
#define LBL_RANK_LINE				EVENTSGUI+29
#define LSTRANK						EVENTSGUI+30
#define CMB_EVENT_CPY				EVENTSGUI+31
#define BUT_COPY					EVENTSGUI+32
#define LBL_RATING_DIF				EVENTSGUI+36
#define LBL_LINE_RAT				EVENTSGUI+34
#define LSTRATINGS					EVENTSGUI+35



//LBInscriptionFormView
#define								INSCRIPGUI		5590
#define BUT_ORDER_MEMBERS			INSCRIPGUI+1		


// LBProgressionFormView
#define								PROGGUI			5600
#define CH_BUT_CHANGE_TEAMS			PROGGUI+1
#define CH_BUT_SUMMARY				PROGGUI+2
#define CH_BUT_STANDINGS			PROGGUI+3
#define CH_BUT_LOG					PROGGUI+4		//DLG Grupos
#define IDFNT_D						PROGGUI+5		//DLG Grupos
#define BUT_UP						PROGGUI+6		//DLG Grupos
#define BUT_DOWN					PROGGUI+7		//DLG Grupos
#define IDFNTBG2					PROGGUI+8		//DLG Grupos
#define MENU_RESULTS				PROGGUI+9		//DLG Grupos
#define SUB_MENU_FINISH				PROGGUI+10		//DLG Grupos
#define SUB_MENU_1_0				PROGGUI+11		//DLG Grupos
#define SUB_MENU_1_2_1_2			PROGGUI+12		//DLG Grupos
#define SUB_MENU_0_1				PROGGUI+13		//DLG Grupos
#define SUB_MENU_0_0				PROGGUI+14		//DLG Grupos
#define SUB_MENU_1F_0F				PROGGUI+15		//DLG Grupos
#define SUB_MENU_0F_1F				PROGGUI+16		//DLG Grupos
#define SUB_MENU_0F_0F				PROGGUI+17		//DLG Grupos
#define	MENU_INCIDENCE				PROGGUI+18		//DLG Grupos
#define	SUBMENU_INCIDENCE1			PROGGUI+19		//DLG Grupos
#define	SUBMENU_INCIDENCE2			PROGGUI+20		//DLG Grupos
#define	SUBMENU_INCIDENCE3			PROGGUI+21		//DLG Grupos
#define	SUBMENU_INCIDENCE4			PROGGUI+22		//DLG Grupos
#define	SUBMENU_INCIDENCE5 			PROGGUI+23		//DLG Grupos
#define	SUBMENU_INCIDENCE6 			PROGGUI+24		//DLG Grupos
#define	SUBMENU_INCIDENCE7 			PROGGUI+25		//DLG Grupos
#define	CH_BMP_DRAW					PROGGUI+26		//DLG Grupos
#define	CH_BMP_REM					PROGGUI+27		//DLG Grupos
#define	CH_BUT_REM					PROGGUI+28		//DLG Grupos


//MAtch Visor
#define								VISOR			5700
#define BM_UP						VISOR+1
#define BM_DOWN						VISOR+2
#define CH_FNT						VISOR+3
#define CH_BOLD_FNT					VISOR+4
#define CH_IDFNT					VISOR+5

#define  LSTSTATUS					VISOR+6
#define  CH_STATUS					VISOR+7

#define  CH_DAY						VISOR+20
#define  CH_SESSION					VISOR+21	
#define  CH_START_TIME				VISOR+22	
#define  CH_COURT					VISOR+23	
#define  CH_ROUND					VISOR+24	

#define  CB_DAYS					VISOR+25
#define  CB_SESSION					VISOR+26
#define  CB_START_TIME				VISOR+27
#define  CB_COURT					VISOR+28	
#define  CB_ROUND					VISOR+29
#define  CH_SET1					VISOR+30
#define  CH_SET2					VISOR+31
#define  CH_SET3					VISOR+32

#define  LSTMATCHS					VISOR+33

#define  BT_AVSTART_TIME			VISOR+34
#define  BT_RESTART_TIME			VISOR+35
#define  BT_AVCOURT					VISOR+36
#define  BT_RECOURT					VISOR+37
#define  BT_AVSESSION				VISOR+38
#define  BT_RESESSION				VISOR+39
#define  BT_AVROUND					VISOR+40
#define  BT_REROUND					VISOR+41
#define  BT_MANDE					VISOR+42
#define  CH_NMATCHES				VISOR+43

#define  BMP_FIND_MATCH_VI			VISOR+45
#define  BUTTON_FIND_MATCH_DE_VI	VISOR+46
#define  LBL_FIND_MATCH_VI			VISOR+47
#define  ED_FIND_MATCH_VI			VISOR+48
#define  BT_MANDETEAM				VISOR+49


// LBFinalStandingsDlg
#define CH_LBL_STANDINGS			2550
#define CH_FRAME_STANDINGS			2551
#define CH_EXIT_STANDINGS			2552
#define CH_GRID_STANDINGS			2553
#define CH_BMP_GOLD					2554
#define CH_BMP_SILVER				2555
#define CH_BMP_BRONZE				2556
#define CH_CMB_MEDALS				2557
#define CH_QUALITATIVE				2558


// LBCompSummaryDlg
#define CH_LBL_SUMMARY				2607
#define CH_FRAME_SUMMARY			2608
#define CH_EXIT_SUMMARY				2609
#define CH_LBL_GROUP_SUMMARY		2610 // +10 Pooles
#define CH_LBL_NAME_SUMMARY			2620 // +10 Pooles
#define CH_LBL_MATCHES_SUMMARY		2630 // +10 Pooles
#define CH_LBL_GOALS_SUMMARY		2640 // +10 Pooles
#define CH_LBL_POINTS_SUMMARY		2650 // +10 Pooles
#define CH_LBL_PLAYED_SUMMARY		2660 // +10 Pooles
#define CH_LBL_WON_SUMMARY			2670 // +10 Pooles
#define CH_LBL_DRAWN_SUMMARY		2680 // +10 Pooles
#define CH_LBL_LOST_SUMMARY			2690 // +10 Pooles
#define CH_LBL_FOR_SUMMARY			2700 // +10 Pooles
#define CH_LBL_AGAINST_SUMMARY		2710 // +10 Pooles
#define CH_LBL_DIFF_SUMMARY			2720 // +10 Pooles
#define CH_GRID_SUMMARY				2730 // +10 Pooles
#define CH_LBL_RANK					2740 // +10 Pooles
#define CH_LBL_SETS_SUMMARY			2750 // +10 Pooles
#define CH_LBL_SET_FOR_SUMMARY		2760 // +10 Pooles
#define CH_LBL_SET_AGA_SUMMARY		2770 // +10 Pooles


// LBResultDlg
#define CH_LBL_MATCH_RESULT			3600
#define CH_FRM_RESULT				3601
#define CH_BUT_EXIT					3602
#define CH_FRM_HOME					3603
#define CH_BMP_HOME					3604
#define CH_LBL_HOME					3605 // +5 Periods
#define	CH_EDT_HOME					3611 // +5 Periods
#define CH_FRM_AWAY					3617
#define CH_BMP_AWAY					3618
#define CH_LBL_AWAY					3619 // +5 Periods
#define	CH_EDT_AWAY					3625 // +5 Periods
#define	CH_CMB_QCODE_HOME			3631
#define	CH_CMB_QCODE_AWAY			3632
#define	LBBCK1						3633
#define	LBFNTBIG					3634
#define	LBCOL						3635
#define	CH_BUT_OK					3636

#define	CB_COMBO					3700
#define	CH_VENUE					3701
#define	CH_VENUE_NAME				3702
#define	CH_BOX_VENUE				3703

// CHManualEventControl
// Buttons
#define BU_STATUS					4000
#define BU_FINISH					4001
#define BU_SAVE_ALL					4002
#define BU_ONE_ZERO					4003
#define BU_HALF_HALF				4004
#define BU_ZERO_ONE					4005
#define BU_EMPTY					4006
#define BU_ONE_ZERO_F				4007
#define BU_ZERO_ONE_F				4008
#define BU_ZERO_ZERO_F				4009
#define BU_NEXT 					4010
#define BU_PREVIOUS_M 				4011
#define BU_NEXT_M 					4012

#define LBL_EVENTS_DE				4013
#define LBL_LINEA_DE				4014
#define LBL_POINT					4015
#define FRM_TYPE_RESULTS			4016	

#define	MENU_COLORS					4017
#define	SUBMENU_WHITE				4018
#define	SUBMENU_BLACK				4019

#define	LBL_EVENTS_SUB				4020
#define	LBL_LINEA_SUB				4021

#define	BU_POOL_SELECT				4022
#define	BU_DATE_SELECT				4023
#define CH_OFFICIAL					4024

// LB Colors
#define COLOR_NEGRO					RGB(  0,  0,  0)
#define COLOR_NARANJA				RGB(255,128,  0)
#define COLOR_AZUL					RGB(  0,  0,255)
#define COLOR_AZUL1					RGB(  0, 64,128)
#define COLOR_AZUL2					RGB(  0,  0,255)
#define COLOR_AZUL3					RGB(  0,  0,200)
#define COLOR_AZUL4					RGB(200,200,250)
#define COLOR_AZUL5					RGB(223,239,255)
#define COLOR_VERDE1				RGB( 43,255,143)
#define COLOR_VERDE2				RGB(118,237,148)
#define COLOR_VERDE3				RGB(235,255,235)
#define COLOR_VERDE4				RGB(  0,128, 64)
#define COLOR_VERDE5				RGB(213,235,211)
#define COLOR_VERDE6				RGB(225,255,225)
#define COLOR_VERDE7				RGB(215,230,215)
#define COLOR_MARRON				RGB(128, 64,  0)
#define COLOR_ROSA					RGB(255,128,128)
#define COLOR_ROJO1					RGB(200,  0,  0)
#define COLOR_ROJO2					RGB(150,  0,  0)
#define COLOR_ROJO3					RGB(255,  0,  0)
#define COLOR_BLANCO				RGB(255,255,255)
#define COLOR_AMARILLO1				RGB(255,255,170)
#define COLOR_AMARILLO2				RGB(206,149, 53)
#define COLOR_GRIS					RGB(160,160,160)
 
// Chess Colors Ids
#define	IDCOL_NEGRO					5000
#define	IDCOL_NARANJA				5001
#define	IDCOL_AZUL					5002
#define	IDCOL_AZUL1					5003
#define	IDCOL_AZUL2					5004
#define	IDCOL_AZUL3					5005
#define	IDCOL_AZUL4					5006
#define	IDCOL_AZUL5					5007

#define	IDCOL_VERDE1				5008
#define	IDCOL_VERDE2				5009
#define	IDCOL_VERDE3				5010
#define	IDCOL_VERDE4				5011
#define	IDCOL_VERDE5				5012
#define	IDCOL_VERDE6				5013
#define	IDCOL_VERDE7				5014
#define	IDCOL_MARRON				5015
#define	IDCOL_ROSA					5016
#define	IDCOL_ROJO1					5017
#define	IDCOL_ROJO2					5018
#define	IDCOL_ROJO3					5019
#define	IDCOL_BLANCO				5020
#define	IDCOL_AMARILLO1				5021
#define	IDCOL_AMARILLO2				5022
#define	IDCOL_GRIS					5023
#define IDCOLHEAVRED				5024

// Chess BCK
#define	IDBCK_VERDE					5050
#define	IDBCK_AMARILLO				5051
#define	IDBCK_GREEN					5052
#define	IDBCK_RED					5053
#define	IDBCK_WHITE					5054
#define	IDBCK_BLACK					5055

// Bitmaps
#define BMP_WHITE					5060
#define BMP_BLACK					5061

#define BMP_WHITE_EC				5062
#define BMP_BLACK_EC				5063

// CHEventControlFormView			

#define	CH_GRD_BOARD				5100	// +50
#define	CH_WND_BOARD				5151	// +50
#define	CH_GRD_HIST					5201	// +50

#define	CH_LAUNCH_MATCHES			5251
#define	CH_SCROLL_BAR				5252

#define	BMP_W_PAWN					5253
#define	BMP_W_ROOK					5254
#define	BMP_W_BISHOP				5255
#define	BMP_W_KNIGHT				5256
#define	BMP_W_QUEEN					5257
#define	BMP_W_KING					5258
#define	BMP_B_PAWN					5259
#define	BMP_B_ROOK					5260
#define	BMP_B_BISHOP				5261
#define	BMP_B_KNIGHT				5262
#define	BMP_B_QUEEN					5263
#define	BMP_B_KING					5264

#define	BMP_W_ROOK_S				5266
#define	BMP_W_BISHOP_S				5267
#define	BMP_W_KNIGHT_S				5268
#define	BMP_W_QUEEN_S				5269
#define	BMP_W_KING_S				5270
#define	BMP_B_ROOK_S				5272
#define	BMP_B_BISHOP_S				5273
#define	BMP_B_KNIGHT_S				5274
#define	BMP_B_QUEEN_S				5275
#define	BMP_B_KING_S				5276

#define CH_LBL_1					5300
#define CH_LBL_2					5350
#define CH_LBL_3					5400
#define CH_LBL_4					5450
#define CH_LBL_5					5500
#define CH_LBL_6					5550
#define CH_LBL_7					5600
#define CH_LBL_8					5650

#define CH_LBL_A					5700
#define CH_LBL_B					5750
#define CH_LBL_C					5800
#define CH_LBL_D					5850
#define CH_LBL_E					5900
#define CH_LBL_F					5950
#define CH_LBL_G					6000
#define CH_LBL_H					6050

#define CH_BMP_WHITE				6100
#define CH_BMP_BLACK				6150

#define CH_LBL_NAME_WHITE			6200
#define CH_LBL_NAME_BLACK			6250

#define CH_LBL_NOC_WHITE			6300
#define CH_LBL_NOC_BLACK			6350

#define CH_LBL_ROUND				6400
#define CH_LBL_GAME					6450
#define CH_LBL_EVENT				6500

#define CH_LBL_WHITE				6550
#define CH_LBL_BLACK				6600

#define CH_FRM_GAME					6650

#define CH_BUT_STATUS				6700
#define CH_LBL_NEXT_TURN			6750

#define CH_BUT_W_WINNER				6800
#define CH_BUT_B_WINNER				6850
#define CH_BUT_DRAW					6900
#define CH_BUT_EMPTY				6950
#define CH_BUT_W_WINNER_F			7000
#define CH_BUT_B_WINNER_F			7050
#define CH_BUT_DRAW_F				7100
#define CH_LBL_GAME_RESULT			7150

#define CH_LBL_SAVE_PGN				7200
#define CH_LBL_LOAD_PGN				7201

// CHPgnMatchesDlg
#define CH_GRD_MATCHES				7300
#define CH_GRD_PGNMATCHES			7301
#define CH_BUT_CANCEL				7302