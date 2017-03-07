/*************************************************************************************
*			© Copyright MSL Software, S.L., 2001
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHMsgDefines.h
*   Description	: 
*
*	Author		: Chess Team
*	Date created: 07-12-2005
* 	Project		:
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

///////////////////////////////////////////////////////////////////////////////////////
//User Transactions
///////////////////////////////////////////////////////////////////////////////////////

#include <Core\TH\GTHMsgDefines.h>
#define TRN_CH_JUDGE_SET				1001 // Set Judges
#define TRN_CH_JUDGE_CHANGE				1000 // Update Judges
#define TRN_CH_JUDGE_REMOVE				1002 // Remove Judges

#define TRN_CH_EVENTRESULT_SET			1003 // Set EventResult
#define TRN_CH_EVENTRESULT_CHANGE		1004 // Update EventResult
#define TRN_CH_EVENTRESULT_REMOVE		1005 // Remove EventResult


//Progression
#define TRN_SET_MATCHRESULT				1009
#define TRN_SET_POOLRESULT				1010
#define TRN_SPLIT_STATUS_CHANGE			1011 
#define TRN_SPLIT_MATCHRESULT_CHANGE	1012 

#define TRN_CH_MATCHJUDGE_CHANGE		1013
#define TRN_CHANGE_PHASEBASE			1014

#define TRN_CH_EVENT_CHANGE				1015
#define TRN_CH_COURT_CHANGE				1016
#define TRN_CHANGE_POOLRESULT_CH		1017
#define TRN_PROGRESS_MATCH				1018


#define TRN_SET_SPLIT_MATCH				1024 // Set Split Match
#define TRN_CHANGE_SPLIT_MATCH			1025 // Update Split Match
#define TRN_REMOVE_SPLIT_MATCH			1026 // Remove Split Match

#define TRN_CH_INSERT_TEAMMATCHSCNFG	1030 // Team Matches Configuration
#define TRN_CH_REMOVE_TEAMMATCHSCNFG	1031 // Team Matches Configuration

#define TRN_CH_INSERT_MASTERTYPE		1040 // Master Type
#define TRN_CH_CHANGE_MASTERTYPE		1041 // Master Type
#define TRN_CH_REMOVE_MASTERTYPE		1042 // Master Type

#define TRN_JUDGE_CHANGE_DLG			1050 // Judge

#define TRN_SET_JUDGE					1151 //set judge
#define TRN_CHANGE_JUDGE				1152 //change judge
#define TRN_DELETE_JUDGE				1153 //delete judge

#define TRN_SET_RATING_DIF				1154 //set Rating Dif
#define TRN_CHANGE_RATING_DIF			1155 //change Rating Dif
#define TRN_DELETE_RATING_DIF			1156 //delete Rating Dif



