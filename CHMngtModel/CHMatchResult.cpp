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
#include "CHDiscipline.h"
#include "CHClassIDs.h"
#include "UCHMatchResult.h"
#include "CHEvent.h"
#include "CHPhase.h"
#include "CHInscription.h"
#include "CHRegister.h"
#include "CHMatch.h"
#include "CHMatchMember.h"
#include "CHStatisticDefines.h"
#include <core/G/GScore.h>

static
RWBoolean matchResultsOfPoolResult(const RWCollectable * col, const void * param)
{
	CHPoolResult * pPoolResult = (CHPoolResult *) param;
	CHMatchResult  * pMatchResult = (CHMatchResult*) col;
	
	if (pPoolResult &&
		pMatchResult &&
		pMatchResult->getSubMatch()==0 &&
		pMatchResult->getEvent() == pPoolResult->getEvent() &&
		pMatchResult->getRegister() &&
		pPoolResult->getRegister() &&
		pPoolResult->getRegister() == pMatchResult->getRegister())
		return true;

	return false;
}

RWDEFINE_COLLECTABLE(CHMatchResult, __CHMATCHRESULT)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHMatchResult::CHMatchResult()
:GTHMatchResult()
,points(0.0)
,color(eWhite)
,upFloater(false)
,downFloater(false)
{
}

CHMatchResult::CHMatchResult(CHMatch * match,short pos)
:GTHMatchResult(match,pos)
,points(0.0)
,color(eWhite)
,upFloater(false)
,downFloater(false)
{
}

CHMatchResult::CHMatchResult(const CHMatchResult & copy)
{
	operator =(copy);
}

CHMatchResult::CHMatchResult(CPack & aPack)
{
	unpack(aPack); 
}

CHMatchResult::~CHMatchResult()
{
}

CHMatchResult & CHMatchResult::operator =(const CHMatchResult & copy)
{
	if ( this != &copy )
	{
		GTHMatchResult::operator=(copy);	// Habrá que modificar
		points				= copy.points;
		color				= copy.color;
		upFloater			= copy.upFloater;
		downFloater			= copy.downFloater;
	}
	return *this;
}

RWBoolean CHMatchResult::operator ==(const CHMatchResult & copy)
{
	if ( this == &copy )
		return true;
	
	return (	GTHMatchResult::operator==(copy)					&&
				points				==	copy.points					&&
				color				==  copy.color					&&
				upFloater			==  copy.upFloater				&&
				downFloater			==  copy.downFloater);
}

RWBoolean CHMatchResult::operator !=(const CHMatchResult & copy)
{
	return !operator==(copy);
}

RWBoolean CHMatchResult::uSQL(RWDBConnection& pConnect,RWBoolean remove/*=false*/)
{
	RWBoolean rc=false;

	UCHMatchResult upd(&pConnect);
	if( remove )
		rc=upd.remove(*this);
	else
		rc=upd.set(*this);

	return rc;
}

RWCString CHMatchResult::msl() const
{
	GBuffer aBuffer;
	RWCString str = GTHMatchResult::msl();

	if(str==NULLRWSTRING)
		return str;
	return str + RWCString( aBuffer	<< getPointsAsString()
									<< getSubMatch()
									<< color
									<< upFloater
									<< downFloater
									<< endLine);
}

RWCString CHMatchResult::mslDescription(const char *language) const
{
	return GTHMatchResult::mslDescription(language);
}

CPack& CHMatchResult::pack(CPack &aPack)
{
 	GTHMatchResult::pack(aPack);

	aPack << points;
	aPack << color;
	aPack << upFloater;
	aPack << downFloater;

	return aPack;
}

CPack& CHMatchResult::unpack(CPack &aPack)
{
	GTHMatchResult::unpack(aPack);	

	aPack >> points;
	aPack >> color;
	aPack >> upFloater;
	aPack >> downFloater;

	return aPack;
}
//SETS
void CHMatchResult::setPoints(const float value)
{ 
	points = value;
}
void CHMatchResult::setColor(const short value)
{
	color = value;
}

void CHMatchResult::setUpFloater(const RWBoolean value)
{
	upFloater = value;
}

void CHMatchResult::setDownFloater(const RWBoolean value)
{
	downFloater = value;
}


// GETS
float CHMatchResult::getPoints() const
{ 
	return points;
}

RWCString CHMatchResult::getPointsAsString() const
{
	RWCString aux(NULLRWSTRING);
	char tmp[10];
 
	float points= getPoints();
	sprintf(tmp,"%.1f",points); //XXX.Y
	
	RWCString format="#";
	if((getPoints()-int(getPoints()))>0)
		format="#.#"; // Decimales
		
	
	GScore pointsS = GScore(getPoints());
	return pointsS.asString(format);
}

short CHMatchResult::getSubMatch() const
{
	return getMatch()?((CHMatch*)getMatch())->getSubMatch():0;
}
short CHMatchResult::getColor() const
{
	return color;
}
RWBoolean CHMatchResult::getUpFloater() const
{
	return upFloater;
}

RWBoolean CHMatchResult::getDownFloater() const
{
	return downFloater;
}

short CHMatchResult::getMatchNumber() const
{
	CHMatch * pMatch = (CHMatch*)getMatch();
	return pMatch?pMatch->getMatchNumber():short(0);
}
unsigned char CHMatchResult::getMatchStatus() const
{
	CHMatch * pMatch = (CHMatch*)getMatch();
	return pMatch?pMatch->getStatus():CHMemoryDataBase::eAvailable;
}
 
int CHMatchResult::getTeamMembers() const
{
	return ((CHEvent *)getEvent())->getTeamMembers();
}

GSortedVector CHMatchResult::getSubMatches()
{
	CHMatch *pMat=(CHMatch *)getMatch();
	return pMat->getSubMatches();
}

CHMatchResult*	CHMatchResult::getMatchResultVersus()
{
	if(isHome())
		 return ((CHMatch*)getMatch())->getMatchResultAway();
	else return ((CHMatch*)getMatch())->getMatchResultHome();
	
}

RWBoolean CHMatchResult::isHome() const
{
	return (getPosition()==1);
}

RWBoolean CHMatchResult::isQualitative() const
{
	if(getQualitative() && getQualitativeCode()!=OK)
		return true;

	return false;
}
GSortedVector &CHMatchResult::getInscriptionMembersVector() const
{
	return (GSortedVector &)(getInscription()->getMembersVector());
}

short CHMatchResult::getSeed()
{
	return getInscription()?((CHInscription*)getInscription())->getSeed():0;
}
	
RWCString CHMatchResult::getSeedAsString()
{
	return getInscription()?((CHInscription*)getInscription())->getSeedAsString():NULLRWSTRING;
}

int CHMatchResult::getColorRGB()
{
	int ret=0;
	
	switch (color)
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

RWBoolean CHMatchResult::areTeams() const
{
	return ((CHEvent *)getEvent())->isTeam();
}

short CHMatchResult::getColorVersus()
{
	short colorVersus=eNone;
	if(color==eWhite)
		colorVersus=eBlack;
	if(color==eBlack)
		colorVersus=eWhite;

	return colorVersus;

}

short CHMatchResult::getTeamMatchesWon()
{
	CHMatch *pTeamMatch=(CHMatch*)getMatch();
	GSortedVector vSubMatches=pTeamMatch->getSubMatches();
	CHMatch *pSubMatch=0;
	short matchesWon=0;
	for(size_t i=0;i<vSubMatches.entries();i++)
	{
		pSubMatch=(CHMatch*)vSubMatches[i]->getElement();
		if(isHome() && pSubMatch->getWinner()==CHMatch::eWinnerWhite)
			matchesWon++;
		if(!isHome() && pSubMatch->getWinner()==CHMatch::eWinnerBlack)
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

	if (pMatch->isBye())
		return 0.5;

	if (pMatch->getWinner()==((CHMatchResult*)this)->getPosition() &&
	   (pMatch->getResultCode()==EV_WHITE_WINNER_F || 
		pMatch->getResultCode()==EV_BLACK_WINNER_F) ) 
	{
		return 0.5;
	}
	return points;
}

// From CHMatchResult
CHMatchMember* CHMatchResult::getMatchMember()
{
	return (CHMatchMember*)getMembersVector()[0]->getElement();
	
}
RWWString CHMatchResult::getMatchMemberLDescription()
{
	GSortedVector vMatchMembers=getMembersVector();
	RWCString txt = NULLRWSTRING;
	CHMatchMember *pMatchMember=0;
	for(size_t i=0;i<vMatchMembers.entries();i++)
	{
		pMatchMember = (CHMatchMember*)vMatchMembers[i]->getElement();
		if(pMatchMember && pMatchMember->getRegister())
		{
			if(i!=0)
				 txt+="-"+pMatchMember->getPrnLName().toMultiByte();
			else txt+=pMatchMember->getPrnLName().toMultiByte();
		}
	}
			
	return RWWString(txt,RWWString::multiByte);
}
RWWString CHMatchResult::getMatchMemberSDescription()
{
	GSortedVector vMatchMembers=getMembersVector();
	RWCString txt = NULLRWSTRING;
	CHMatchMember *pMatchMember=0;
	for(size_t i=0;i<vMatchMembers.entries();i++)
	{
		pMatchMember = (CHMatchMember*)vMatchMembers[i]->getElement();
		if(pMatchMember && pMatchMember->getRegister())
		{
			if(i!=0)
				 txt+="-"+pMatchMember->getPrnSName().toMultiByte();
			else txt+=pMatchMember->getPrnSName().toMultiByte();
		}
	}
			
	return RWWString(txt,RWWString::multiByte);
}

RWCString CHMatchResult::getColorSDesc() const
{
	if (getColor()==eWhite)
		return "W";
	else if (getColor()==eBlack)
		return "B";
	return NULLRWSTRING;
}

RWCString CHMatchResult::getColorLDesc() const
{
	if (getColor()==eWhite)
		return "White";
	else if (getColor()==eBlack)
		return "Black";
	return NULLRWSTRING;
}

RWCString CHMatchResult::getColorVersusSDesc() const
{
	if (((CHMatchResult*)this)->getColorVersus()==eWhite)
		return "W";
	else if (((CHMatchResult*)this)->getColorVersus()==eBlack)
		return "B";
	return NULLRWSTRING;
}

RWCString CHMatchResult::getColorVersusLDesc() const
{
	if (((CHMatchResult*)this)->getColorVersus()==eWhite)
		return "White";
	else if (((CHMatchResult*)this)->getColorVersus()==eBlack)
		return "Black";
	return NULLRWSTRING;
}

void CHMatchResult::getPreviousMatchesVector(GSortedVector &vMatchResults,CHMatch* _pMatch)
{
	if (!getPoolResult())
		return;

	RWSet* colMatchResults=(RWSet*)CHMemoryDataBase::getColMatchResults().select(matchResultsOfPoolResult,getPoolResult());
	RWSetIterator it(*colMatchResults);
		
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

RWCString CHMatchResult::getPreviousMatchesAsString(CHMatch* pMatch)
{
	RWCString matches=NULLRWSTRING;
	GSortedVector vMatchResults;
	getPreviousMatchesVector(vMatchResults,pMatch);
	char tmp[100];
	for (size_t i=0;i<vMatchResults.entries();i++)
	{
		CHMatchResult* pMatchResult = (CHMatchResult*)vMatchResults[i]->getElement();
		if (pMatchResult->getRegister())
		{			
			matches+=pMatchResult->getColorSDesc();
			matches+=" - ";
			matches+=pMatchResult->getScbSName().toMultiByte();		
			matches+="\n";
		}
	}	

	return matches;
}