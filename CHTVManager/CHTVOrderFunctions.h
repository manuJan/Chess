/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: WUTVOrderFunctions.h
*	Description	:
*
*	Author		: 
*	Date created: 11-Dec-2009
* 	Project		: WU TV
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#pragma once
#include <OVR\TOOLS\MSLTOOLS\MSLSortedVector.h>

int fnOrderRegByTVLName				(const MSLItem** a, const MSLItem** b);
int fnOrderPhaseByDateTime			(const MSLItem** a, const MSLItem** b);
int fnOrderMatchByDateTime			(const MSLItem** a, const MSLItem** b);
int fnOrderMatchResultByColor		(const MSLItem** a, const MSLItem** b);
int fnOrderMatchResultByPhaseAndMatch(const MSLItem** a, const MSLItem** b);
int fnOrderKey						(const MSLItem** a, const MSLItem** b);
int fnOrderEventResultByRankPo		(const MSLItem** a, const MSLItem** b);
int fnOrderMatchByMatchNumber		(const MSLItem** a, const MSLItem** b);
int fnOrderMatchByInvPhaseAndCode	(const MSLItem** a, const MSLItem** b);
int fnOrderTatamisByCode			(const MSLItem** a, const MSLItem** b);
int fnOrderMatchByTatamiAndStatus	(const MSLItem** a, const MSLItem** b);
int fnOrderMatchJudgeByPosition		(const MSLItem** a, const MSLItem** b);
int fnOrderMatchResultByRanking		(const MSLItem** a, const MSLItem** b);
int fnOrderMembersByName			(const MSLItem** a, const MSLItem** b);
int fnOrderPhasesByPhaseOrder		(const MSLItem** a, const MSLItem** b);
int fnOrderPoolResultsByRankPo		(const MSLItem** a, const MSLItem** b);
int fnOrderGroupInfoByRankPo		(const MSLItem** a, const MSLItem** b);