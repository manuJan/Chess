/*************************************************************************************
*			© Copyright MSL Software, S.L., 2001
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHStatusManager.h
*   Description	: CH Status Manager
*
*	Author		: Chess Team
*	Date created: 15-12-2005
* 	Project		: CH Manager
* 	Modification  history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#if !defined(AFX_CHSTATUSMANAGER_H__F6A88293_9F76_48E2_9273_B6C469F7FC27__INCLUDED_)
#define AFX_CHSTATUSMANAGER_H__F6A88293_9F76_48E2_9273_B6C469F7FC27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <GUI/TH/GTHStatusManager.h>
#include <SPORTS/CH/Data/CHClassIds.h>
#include <SPORTS/CH/Data/CHSplitMatch.h>
#include <SPORTS/CH/DATA/CHMemoryDataBase.h>

class CHStatusManager : public GTHStatusManager  
{
public:
	CHStatusManager();
	virtual ~CHStatusManager();

	void processUserNotification(GData *pData);
	void addObject(CHSplitMatch* pSplitMatch,unsigned char newStatus);
	void userPropagate(GTHMatch* pMatch,unsigned char newStatus);
	void runSplitMatch(CHSplitMatch & aSplitMatch,unsigned char newStatus=0,bool makeOut=true);
	void proccessSplitMatchForward(CHSplitMatch & aSplitMatch,unsigned char oldStatus,unsigned char newStatus);
	void proccessSplitMatchBack(CHSplitMatch & aSplitMatch,unsigned char oldStatus,unsigned char newStatus);
	void setStatusOnly(GData *pData,unsigned char newStatus);
	void setStatusBackPhase(CHPhase * pPhase);

	void proccessForward(GTHMatch&	aMatch,unsigned char oldStatus,unsigned char newStatus);
	void proccessBack	(GTHMatch&	aMatch,unsigned char oldStatus,unsigned char newStatus);
	void proccessForward(CHMatch *pMatch,unsigned char newStatus);
	void proccessBack	(CHMatch *pMatch,unsigned char newStatus);
	void checkAllStatus(GTHPhase* pPhase,unsigned char newStatus);
	void checkAllStatus(GTHPool* pPool,unsigned char newStatus);
	void checkAllStatus(CHMatch* pMatch,unsigned char newStatus);
	
	void proccessOutStatus();
	void sendColStatus();

	void saveTeamSubMatchesStatus(CHMatch* pMatch, unsigned char status);

protected:
	short isAEvent()
	{ return __CHEVENT;}
	short isAPhase()
	{ return __CHPHASE;}
	short isAPool()
	{ return __CHPOOL;}
	short isAMatch()
	{ return __CHMATCH;}

};

#endif // !defined(AFX_CHSTATUSMANAGER_H__F6A88293_9F76_48E2_9273_B6C469F7FC27__INCLUDED_)
