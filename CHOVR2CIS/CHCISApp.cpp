/*************************************************************************************
*			© Copyright MSL Software, S.L., 2008
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHCISApp.cpp
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

#include "stdafx.h"
#include "CHCISApp.h"
#include "CHCISProcess.h"
#include "CHCISPaint.h"
#include "CHCISGUIEx.h"

CHCISApp * CHCISApp::chcisApp = 0;

CHCISApp::CHCISApp()
:GTHCISApp()
{
	chcisApp = this;
}

CHCISApp::~CHCISApp()
{
}

CHCISApp::typeScoreWnd CHCISApp::getTypeScoreWnd()
{
	return CHCISApp::eSplitResultsLeft;
}

CHCISApp::scheduleFilter CHCISApp::getScheduleFilter()
{
	return CHCISApp::eByVenue;
}

GCISGUIEx *CHCISApp::onNewCISGUIEx()
{
	return new CHCISGUIEx();
}

GMemoryDataBase *CHCISApp::onNewMemory()
{
	return new CHMemoryDataBase();
}

GCISProcess * CHCISApp::onNewCISProcess()
{
	return new CHCISProcess(); 
}

GCISPaint * CHCISApp::onNewCISPaint()
{
	return new CHCISPaint();
}

bool CHCISApp::isTeamSport()
{
	return false;
}

bool CHCISApp::coachesMatchMembers()
{
	return false;
}