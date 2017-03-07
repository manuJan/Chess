/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHSessionPoolRound.cpp
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
#include "stdVCH.h"
#include "CHSessionPoolRound.h"

#include <Sports/CH/Data/CHSession.h>
#include <Sports/CH/Data/CHPool.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHSessionPoolRound::CHSessionPoolRound(CHSession *_pSession, CHPool *_pPool, short _round)
:pSession(_pSession)
,pPool(_pPool)
,round(_round)
,numMatches(1)
{
	setKey();
}

CHSessionPoolRound::~CHSessionPoolRound()
{
}

CPack& CHSessionPoolRound::pack(CPack& aPack)
{
	return aPack;
}

CPack& CHSessionPoolRound::unpack(CPack& aPack)
{
	return aPack;
}

RWBoolean CHSessionPoolRound::uSQL(RWDBConnection& pConnect,RWBoolean remove/*=false*/)
{
	return false;
	UNREFERENCED_PARAMETER(pConnect);
	UNREFERENCED_PARAMETER(remove);
}

void CHSessionPoolRound::setKey()
{
	char aux[3];
	if (pSession && pPool)
	{
		sprintf(aux,"%.2d",round);
		key=pSession->getKey()+pPool->getKey()+RWCString(aux);
	}
}

void CHSessionPoolRound::setNumMatches()
{
	numMatches++;
}

short CHSessionPoolRound::getNumMatches() const
{
	return numMatches;
}

RWCString CHSessionPoolRound::getEventDescription() const
{
	RWCString aux =  NULLRWSTRING;
	aux = pPool->getEventLDescription().toMultiByte();
	aux += " ";
	if ( pPool->getIsPool() )
		aux += pPool->getLDescription().toMultiByte();
	else
		aux += pPool->getPhaseLDescription().toMultiByte();
	return aux;
}

RWCString CHSessionPoolRound::getFullEventDescription() const
{
	char aux[3];
	RWCString full = NULLRWSTRING;
	full = pPool->getEventLDescription().toMultiByte();
	full += " ";
	full += pPool->getPhaseLDescription().toMultiByte();
	if (pPool->getIsPool())
	{
		full +=	pPool->getNumRounds()>1?" Round ":" ";
		if (pPool->getNumRounds()>1)
		{
			sprintf(aux,"%d",round);
			full += RWCString(aux);
		}
		else
			full += pPool->getSDescription().toMultiByte();
	}

	return full;
}

RWCString CHSessionPoolRound::getSessionDescription() const
{
	return NULLRWSTRING;
}

RWCString CHSessionPoolRound::getSessionStartTime() const
{
	return pSession->getTimeAsString("%H:%M");
}

RWCString CHSessionPoolRound::getSessionStartDate(RWCString format/*="%d %b %Y"*/) const
{
	return toUpper(pSession->getDateAsString(format));
}

RWDate CHSessionPoolRound::getStartDate() const
{
	return pSession->getDate();
}

CHSession *CHSessionPoolRound::getSession() const
{
	return pSession;
}

short CHSessionPoolRound::getRound() const
{
	return round;
}