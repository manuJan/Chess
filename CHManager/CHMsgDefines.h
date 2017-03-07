/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHMsgDefines.h                                                                 
*   Description : Mensajes de comunicacion entre módulos del Handball Manager
*
*   Author      : Chess Team
*   Date created: 
*   Project     : 
*
*   Modification history
*   By      :      
*   Date    :      
*   Changes :      
*
**************************************************************************************///

#include <Core/G/GMsgDefines.h>

//Defines de Form's view para Reports

// EventControl Msgs
#define UM_ECT_CHANGE_GRIDPOSITION		WM_USER+7565
#define UM_ECT_SET_PUNTUATION			WM_USER+7566
#define UM_ECT_ORDERLIST				WM_USER+7568
#define UM_ECT_REMOVE_MATCH				WM_USER+7570
#define UM_ECT_DLGSTATUS				WM_USER+7571
#define UM_ECT_DLGRANKING				WM_USER+7572
#define UM_ECT_DLGREPORTS				WM_USER+7573
#define UM_ECT_START_END				WM_USER+7574
#define UM_ECT_VSCROLL_TOPOSITION		WM_USER+7576
#define UM_ECT_HSCROLL_TOPOSITION		WM_USER+7577
#define UM_ECT_AVRE_PAGE_SCROLL			WM_USER+7578
#define UM_ECT_DLGQUALITATIVE			WM_USER+7579

// Common Msgs
#define UM_ECT_INIT						WM_USER+7580
#define UM_ECT_SHOW						WM_USER+7581
#define UM_ECT_REDRAW					WM_USER+7582
#define UM_ECT_EVENT					WM_USER+7583
#define UM_ECT_ENABLE					WM_USER+7584
#define UM_ECT_DESTROY					WM_USER+7585
#define UM_ECT_SET_FOCUS				WM_USER+7586
#define UM_ECT_REDRAW_COMPETITOR		WM_USER+7587
#define UM_ECT_REDRAW_MATCH				WM_USER+7588
#define UM_SET_RESULTS					WM_USER+7589
#define UM_ECT_SHOW_MATCHES				WM_USER+7590
#define UM_ECT_SETMATCH					WM_USER+7591
#define UM_ECT_UNDOMOVEMENT				WM_USER+7592
#define UM_ECT_SETWINNER				WM_USER+7593
#define UM_ECT_CHANGE_STATUS			WM_USER+7594
#define UM_ECT_UNSETWINNER				WM_USER+7595
#define UM_ECT_CANCEL_EVENTS			WM_USER+7596
#define UM_ECT_TOOUTCOL					WM_USER+7597
#define UM_ECT_TOSEND					WM_USER+7598
#define UM_PROCESS_MOVEMENT				WM_USER+7599

// Event Control Edit
#define UM_ECT_EDIT_KEYDOWN				UM+100
#define UM_ECT_EDIT_CHANGE				UM+102

#define MAX_MULTI_EC					4
