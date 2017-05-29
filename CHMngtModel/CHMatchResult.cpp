/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHMatchResult.cpp
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:07-12-2005
*   Project     :CH Model
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///
#include "stdCHMngt.h"
#include "CHMatchResult.h"
#include "CHMatch.h"
#include "CHPoolResult.h"
#include "UCHMatchResult.h"
#include "QCHMatchResult.h"
#include "CHEvent.h"
#include "CHPhase.h"
#include "CHInscription.h"
#include "CHRegister.h"
#include "CHMatch.h"
#include "CHStatisticDefines.h"
#include "CHSportDefines.h"
#include <ovr/core/G/GScore.h>

static
bool matchResultsOfPoolResult(const MSLItem * col, const void * param)
{
	CHPoolResult * pPoolResult = (CHPoolResult *) param;
	CHMatchResult  * pMatchResult = (CHMatchResult*) col;
	
	if (pPoolResult &&
		pMatchResult &&
		pMatchResult->getMatchSubCode()==0 &&
		pMatchResult->getEvent() == pPoolResult->getEvent() &&
		pMatchResult->getRegister() &&
		pPoolResult->getRegister() &&
		pPoolResult->getRegister() == pMatchResult->getRegister())
		return true;

	return false;
}

MSLDEFINE_ITEM(CHMatchResult, __CHMATCHRESULT)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHMatchResult::CHMatchResult()
:GTHMatchResult()
,m_points(0.0)
,m_color(eWhite)
,m_upFloater(false)
,m_downFloater(false)
{
}

CHMatchResult::CHMatchResult(CHMatch * match,short pos)
:GTHMatchResult(match,pos)
,m_points(0.0)
,m_color(eWhite)
,m_upFloater(false)
,m_downFloater(false)
{
}

CHMatchResult::CHMatchResult(const CHMatchResult & copy)
{
	operator =(copy);
}

CHMatchResult::~CHMatchResult()
{
}

GData & CHMatchResult::operator =(const GData & copy)
{
	if ( this != &copy )
	{
		CHMatchResult & aMatchResult = (CHMatchResult &)copy;

		GTHMatchResult::operator=(copy);	// Habrá que modificar
	
		m_points			= aMatchResult.m_points;
		m_color				= aMatchResult.m_color;
		m_upFloater			= aMatchResult.m_upFloater;
		m_downFloater		= aMatchResult.m_downFloater;
	}
	return *this;
}

bool CHMatchResult::operator ==(const GData & copy)
{
	if ( this == &copy )
		return true;
	
	CHMatchResult & aMatchResult = (CHMatchResult &)copy;
	
	return (	GTHMatchResult::operator==(copy)					&&
				m_points			==	aMatchResult.m_points		&&
				m_color				==  aMatchResult.m_color		&&
				m_upFloater			==  aMatchResult.m_upFloater	&&
				m_downFloater		==  aMatchResult.m_downFloater);
}

bool CHMatchResult::operator !=(const GData & copy)
{
	return !operator==(copy);
}

UBase*  CHMatchResult::onU() const
{
	return new UCHMatchResult();
}

QBase*  CHMatchResult::onQ() const
{
	return new QCHMatchResult();	
}

MSLPack& CHMatchResult::pack(MSLPack &aPack) const
{
 	GTHMatchResult::pack(aPack);

	aPack << m_points;
	aPack << m_color;
	aPack << m_upFloater;
	aPack << m_downFloater;

	return aPack;
}

MSLPack& CHMatchResult::unpack(MSLPack &aPack)
{
	GTHMatchResult::unpack(aPack);	

	aPack >> m_points;
	aPack >> m_color;
	aPack >> m_upFloater;
	aPack >> m_downFloater;

	return aPack;
}
//SETS
void CHMatchResult::setPoints(const float value)
{ 
	m_points = value;
}

void CHMatchResult::setColor(const short value)
{
	m_color = value;
}

void CHMatchResult::setUpFloater(const bool value)
{
	m_upFloater = value;
}

void CHMatchResult::setDownFloater(const bool value)
{
	m_downFloater = value;
}


// GETS
float CHMatchResult::getPoints() const
{ 
	return m_points;
}

MSLString CHMatchResult::getPointsAsString() const
{
	MSLString aux(NULLSTRING);
	char tmp[10];
 
	float m_points= getPoints();
	sprintf_s(tmp,"%.1f",m_points); //XXX.Y
	
	MSLString format="#";
	if((getPoints()-int(getPoints()))>0)
		format="#.#"; // Decimales
		
	
	GScore m_pointsS = GScore(getPoints());
	return m_pointsS.asString(format);
}

short CHMatchResult::getColor() const
{
	return m_color;
}

bool CHMatchResult::getUpFloater() const
{
	return m_upFloater;
}

bool CHMatchResult::getDownFloater() const
{
	return m_downFloater;
}


int CHMatchResult::getTeamMembers() const
{
	return ((CHEvent *)getEvent())->getTeamMembers();
}

CHMatchResult*	CHMatchResult::getMatchResultVersus()
{
	if(getType()==CHMatchResult::eHome)
		return (CHMatchResult*)getMatch()->getAway();
	
	return (CHMatchResult*)getMatch()->getHome();
}

bool CHMatchResult::isQualitative() const
{
	if(getQualitative() && getQualitativeCode()!=OK)
		return true;

	return false;
}

short CHMatchResult::getSeed()
{
	return getInscription()?((CHInscription*)getInscription())->getSeed():0;
}
	
MSLString CHMatchResult::getSeedAsString()
{
	return getInscription()?((CHInscription*)getInscription())->getSeedAsString():NULLSTRING;
}

int CHMatchResult::getColorRGB()
{
	int ret=0;
	
	switch (m_color)
	{
		case eWhite:
			ret=COLOR_BLANCO;
			break;
		case eBlack:
			ret=COLOR_NEGRO;
			break;
		
	}
	return ret;
}

bool CHMatchResult::areTeams() const
{
	return ((CHEvent *)getEvent())->isTeam();
}

short CHMatchResult::getColorVersus()
{
	short m_colorVersus=eNone;
	if(m_color==eWhite)
		m_colorVersus=eBlack;
	if(m_color==eBlack)
		m_colorVersus=eWhite;

	return m_colorVersus;

}

short CHMatchResult::getTeamMatchesWon()
{
	CHMatch *pTeamMatch=(CHMatch*)getMatch();
	MSLSet colSubMatches;
	pTeamMatch->getSubMatches(colSubMatches);	
	short matchesWon=0;
	MSLSetIterator iter(colSubMatches);
	CHMatch *pSubMatch=0;
	while ((pSubMatch= (CHMatch*) iter())!=0 )
	{

		if( getType()==CHMatchResult::eHome && 
			pSubMatch->getWinner()==CHMatch::eWinnerWhite)
			matchesWon++;
		if( getType()==CHMatchResult::eAway && 
			pSubMatch->getWinner()==CHMatch::eWinnerBlack)
			matchesWon++;
	}
	return matchesWon;
}

float CHMatchResult::getPointsSO()
{
	CHMatch* pMatch = (CHMatch*)getMatch();
	if (!pMatch)
		return 0.0;

	CHEvent* pEvent = (CHEvent*)pMatch->getEvent();
	if (!pEvent)
		return 0.0;

	if (pMatch->hasByes())
		return 0.5;

	if (pMatch->getWinner()==((CHMatchResult*)this)->getPosition() &&
	   (pMatch->getResultCode()==EV_WHITE_WINNER_F || 
		pMatch->getResultCode()==EV_BLACK_WINNER_F) ) 
	{
		return 0.5;
	}
	return m_points;
}

// From CHMatchResult

MSLString CHMatchResult::getColorSDesc() const
{
	if (getColor()==eWhite)
		return "W";
	else if (getColor()==eBlack)
		return "B";
	return NULLSTRING;
}

MSLString CHMatchResult::getColorLDesc() const
{
	if (getColor()==eWhite)
		return "White";
	else if (getColor()==eBlack)
		return "Black";
	return NULLSTRING;
}

MSLString CHMatchResult::getColorVersusSDesc() const
{
	if (((CHMatchResult*)this)->getColorVersus()==eWhite)
		return "W";
	else if (((CHMatchResult*)this)->getColorVersus()==eBlack)
		return "B";
	return NULLSTRING;
}

MSLString CHMatchResult::getColorVersusLDesc() const
{
	if (((CHMatchResult*)this)->getColorVersus()==eWhite)
		return "White";
	else if (((CHMatchResult*)this)->getColorVersus()==eBlack)
		return "Black";
	return NULLSTRING;
}

void CHMatchResult::getPreviousMatchesVector(MSLSortedVector &vMatchResults,CHMatch* _pMatch)
{
	if (!getPoolResult())
		return;

	MSLSet colMatchResults=CHMemoryDataBase::getCol(__CHMATCHRESULT).select(matchResultsOfPoolResult,getPoolResult());
	MSLSetIterator it(colMatchResults);
		
	CHMatchResult* pMatchResult=0;
	while( (pMatchResult=(CHMatchResult*)it()) != 0)
	{
		CHMatch* pMatch = (CHMatch*) pMatchResult->getMatch();

		if ( !_pMatch || _pMatch==pMatch || pMatch->getRound()>=_pMatch->getRound())
			continue;

		if (pMatchResult->getMatchResultVersus())
			vMatchResults.insert(pMatchResult->getMatchResultVersus());
	}
}

MSLString CHMatchResult::getPreviousMatchesAsString(CHMatch* pMatch)
{
	MSLString matches=NULLSTRING;
	MSLSortedVector vMatchResults;
	getPreviousMatchesVector(vMatchResults,pMatch);
	for (short i=0;i<vMatchResults.entries();i++)
	{
		CHMatchResult* pMatchResult = (CHMatchResult*)vMatchResults[i];
		if (pMatchResult->getRegister())
		{			
			matches+=pMatchResult->getColorSDesc();
			matches+=" - ";
			matches+=pMatchResult->getScbSName().toAscii();		
			matches+="\n";
		}
	}	

	return matches;
}