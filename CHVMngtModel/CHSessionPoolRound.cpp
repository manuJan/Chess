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
#include "stdafx.h"
#include "CHSessionPoolRound.h"

#include "..\CHMngtModel\CHPhase.h"
#include "..\CHMngtModel\CHPool.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHSessionPoolRound::CHSessionPoolRound(GSession *_pSession, CHPool *_pPool, short _round)
:m_pSession(_pSession)
,m_pPool(_pPool)
,m_round(_round)
,m_numMatches(1)
{
	setKey();
}

CHSessionPoolRound::~CHSessionPoolRound()
{
}

void CHSessionPoolRound::setKey()
{
	char aux[3];
	if (m_pSession && m_pPool)
	{
		CHPhase * pPhase = (CHPhase * )m_pPool->getPhase();

		sprintf_s(aux,"%.2d",m_round);
		key=m_pSession->getKey()+TOSTRING(pPhase->getOrder())+m_pPool->getKey()+MSLString(aux);
	}
}

void CHSessionPoolRound::setNumMatches()
{
	m_numMatches++;
}

short CHSessionPoolRound::getNumMatches() const
{
	return m_numMatches;
}

MSLWString CHSessionPoolRound::getEventDescription() const
{
	MSLWString aux =  NULLWSTRING;
	aux = m_pPool->getEventLDescription();
	aux += " ";
	if ( m_pPool->getIsPool() )
		aux += m_pPool->getLDescription();
	else
		aux += m_pPool->getPhaseLDescription();
	return aux;
}

MSLWString CHSessionPoolRound::getFullEventDescription() const
{
	char aux[3];
	MSLWString full = NULLSTRING;
	full = m_pPool->getEventLDescription();
	//full += " ";
	//full += m_pPool->getPhaseLDescription();
	if (m_pPool->getIsPool())
	{
		full +=	m_pPool->getNumRounds()>1?" Round ":" ";
		if (m_pPool->getNumRounds()>1)
		{
			sprintf_s(aux,"%d",m_round);
			full += aux;
		}
		else
			full += m_pPool->getSDescription();
	}
	else
		full += " " + m_pPool->getPhaseLDescription();

	return full;
}

MSLWString CHSessionPoolRound::getSessionDescription() const
{
	return NULLSTRING;
}

MSLString CHSessionPoolRound::getSessionStartTime() const
{
	return m_pSession->getTimeAsString("%H:%M");
}

MSLString CHSessionPoolRound::getSessionStartDate(MSLString format/*="%d %b %Y"*/) const
{
	MSLString desc = m_pSession->getDateAsString(format);
	desc.toUpper();
	return desc;
}

MSLDate CHSessionPoolRound::getStartDate() const
{
	return m_pSession->getDate();
}

MSLTime	CHSessionPoolRound::getStartTime() const
{
	return m_pSession->getTime();
}

GSession *CHSessionPoolRound::getSession() const
{
	return m_pSession;
}

short CHSessionPoolRound::getRound() const
{
	return m_round;
}

CHPhase *CHSessionPoolRound::getPhase() const
{
	return m_pPool ? (CHPhase*)m_pPool->getPhase() : 0;
}