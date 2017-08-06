/*************************************************************************************
*			© Copyright MSL Software, S.L., 2008
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHCISApp.h
*	Description	:
*
*	Author		: Javier Juste
*	Date created: 28-03-2011
* 	Project		: BKOVR2CIS
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#pragma once
#include <OVR/GUI/THOVR2CIS/GTHCISApp.h>

#define CHCISAPP CHCISApp::chcisApp

class CHCISApp : public GTHCISApp
{
public:
	CHCISApp();           // protected constructor used by dynamic creation
	virtual ~CHCISApp();

	bool isTeamSport();
	bool coachesMatchMembers();

protected:
	
	virtual typeScoreWnd	getTypeScoreWnd		();
	virtual scheduleFilter	getScheduleFilter	();
	virtual GCISGUIEx		* onNewCISGUIEx		();
	virtual GCISProcess		* onNewCISProcess	();
	virtual GMemoryDataBase * onNewMemory		();
	virtual GCISPaint		* onNewCISPaint		();

public:

	// Static variables
	static CHCISApp * chcisApp;
};