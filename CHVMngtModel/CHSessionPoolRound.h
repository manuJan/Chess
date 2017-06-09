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

#pragma once
#include "CHVMngtModelDefs.h"

class CHPool;

class CHSessionPoolRound : public GData  
{
public:
	CHSessionPoolRound(GSession *_pSession, CHPool *_pPool, short _round);
	virtual ~CHSessionPoolRound();
	    
	void setKey();
	void setNumMatches();

	short getNumMatches() const;

	MSLWString getEventDescription() const;
	MSLWString getFullEventDescription() const;
	MSLWString getSessionDescription() const;
	MSLString getSessionStartTime() const;
	MSLString getSessionStartDate(MSLString format="%d %b %Y") const;

	MSLDate	getStartDate() const;
	GSession *getSession() const;
	short getRound() const;

private:
	GSession *m_pSession;
	CHPool *m_pPool;
	short m_round;
	short m_numMatches;
};

