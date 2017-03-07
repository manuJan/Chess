/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHSessionPoolRound.h
*   Description	: 
*
*	Author		: CH Team
*	Date created:  2-1-2006
* 	Project		:
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#if !defined(AFX_CHSESSIONPOOLROUND_H__B757C17E_4F0E_466A_B1AC_139443D9F337__INCLUDED_)
#define AFX_CHSESSIONPOOLROUND_H__B757C17E_4F0E_466A_B1AC_139443D9F337__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHVMNGTDLL_H
	#include "CHVMngtModelDll.h"
#endif // _CHVMNGTDLL_H

#include <Core/G/GData.h>

class CHSession;
class CHPool;
class CHSessionPoolRound : public GData  
{
public:
	CHSessionPoolRound(CHSession *_pSession, CHPool *_pPool, short _round);
	virtual ~CHSessionPoolRound();

    CPack&		pack(CPack& aPack);
	CPack&		unpack(CPack& aPack);
	RWBoolean	uSQL(RWDBConnection& pConnect,RWBoolean remove=false);

	void setKey();
	void setNumMatches();

	short getNumMatches() const;

	RWCString getEventDescription() const;
	RWCString getFullEventDescription() const;
	RWCString getSessionDescription() const;
	RWCString getSessionStartTime() const;
	RWCString getSessionStartDate(RWCString format="%d %b %Y") const;

	RWDate	getStartDate() const;
	CHSession *getSession() const;
	short getRound() const;

private:
	CHSession *pSession;
	CHPool *pPool;
	short round;
	short numMatches;
};

#endif // !defined(AFX_CHSESSIONPOOLROUND_H__B757C17E_4F0E_466A_B1AC_139443D9F337__INCLUDED_)
