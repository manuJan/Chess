/************************************************************************************* 
*           � Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHPool.cpp                                                                 
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:12-12-2005
*   Project     :CH Model
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///


#include "stdCHMngt.h"
#include "CHPool.h"
#include "CHPoolResult.h"
#include "CHMatch.h"
#include "CHInscription.h"
#include "CHDefinition.h"
#include "CHMemoryDataBase.h"
#include <ovr/core/G/GBuffer.h>

MSLDEFINE_ITEM(CHPool, __CHPOOL)
	
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

static int orderMatches(const MSLItem** a, const MSLItem** b)
{
	CHMatch * pMatchA = (CHMatch *) (*a);
	CHMatch * pMatchB = (CHMatch *) (*b);
	
	// Order by m_round
	int order = pMatchA->getRound() - pMatchB->getRound();
	if( order )
		return order;

	if (!pMatchA->getMatchNumber() && !pMatchB->getMatchNumber())
	{
		// Order by Match Code
		order = pMatchA->getCode() - pMatchB->getCode();
		if( order )
			return order;
	
		// Order by key
		return strcmp(pMatchA->getKey(),pMatchB->getKey());
	}

	if (!pMatchA->getMatchNumber())
		return 1;

	if (!pMatchB->getMatchNumber())
		return -1;

	order = pMatchA->getMatchNumber() - pMatchB->getMatchNumber();
	if( order )
		return order;

	// Order by Match Code
	order = pMatchA->getCode() - pMatchB->getCode();
	if( order )
		return order;
	
	// Order by key
	return strcmp(pMatchA->getKey(),pMatchB->getKey());
}

CHPool::CHPool()
:GTHPool()
{
}

CHPool::CHPool(const CHPool & copy)
{
	operator=(copy);
}

CHPool::~CHPool()
{
}


//////////////////////////////////////////////////////////////////////
// Help Methods
//////////////////////////////////////////////////////////////////////

GTHPhase::DescriptionMode CHPool::getDescriptionMode() const
{
	return getPhase() ? getPhase()->getPoolDescription() : GTHPhase::eNumeric;
}

MSLWString CHPool::getOrderAsString(GTHPhase::DescriptionMode mode/*=GTHPhase::eNumeric*/) const
{
	wchar_t txt[200];

	if( mode == GTHPhase::eNumeric )
		swprintf_s(txt,_T("%d"),getOrder());
	else
	{
		swprintf_s(txt,_T("%c"),(getOrder()-1)+'A');
	}

	return txt;
}

MSLWString CHPool::getDescription(GTHPhase::DescriptionMode mode/*=DescriptionMode::eNumber*/,const char *language/*=getAppLanguage()*/) const
{
	MSLWString desc(NULLWSTRING);

	CHDefinition &aDefinition = (CHDefinition &)CHMemoryDataBase::getDefinition();	
	if( getPhase()->getIsPool() )
	{					
		desc=aDefinition.getSPoolDescription(language)+MSLWString(' ');
		if( mode==GTHPhase::eNumeric )
			desc+=TOWSTRING(getOrder());
		else
		{
			char car=char((getOrder()-1)+'A');
			desc+=MSLWString(car);
		}
	}
	else
	{
		desc=aDefinition.getSMatchDescription(language)+MSLWString(' ');
		desc+=TOWSTRING(getOrder());
	}

	return desc;

	
	UNREFERENCED_PARAMETER(language);
}

MSLWString CHPool::getSDescription(GTHPhase::DescriptionMode mode/*=GTHPhase::eNumeric*/,const char *language/*=getAppLanguage()*/) const
{
	UNREFERENCED_PARAMETER(language);
	MSLWString desc(NULLWSTRING);

	if( getPhase()->getIsPool() )
	{
		if( mode==GTHPhase::eNumeric )
			desc+=TOWSTRING(getOrder());
		else
		{
			char car=char((getOrder()-1)+'A');
			desc+=MSLWString(car);
		}
	}
	else
	{
		desc+=TOWSTRING(getOrder());
	}

	return desc;
}

MSLWString CHPool::getLDescription(GTHPhase::DescriptionMode mode/*=GTHPhase::eNumeric*/,const char *language/*=getAppLanguage()*/) const
{
	return getDescription(mode,language);
	
}

unsigned char CHPool::getRoundStatus(short nRound)
{
	size_t sAvailable=0, sConfigured=0, sSchedulled=0, sStartList=0, sRunning=0, sUnofficial=0, sFinished=0, sProtested=0;
	unsigned char actualStatus=CHMemoryDataBase::eAvailable;
	size_t totMatches=getRoundMatches(nRound);
	CHMatch* pMatch=0;
	MSLSortedVector vMatches;
	getMatchesVector(vMatches);
	for (short i=0;i<vMatches.entries();i++)
	{
		pMatch = (CHMatch*) vMatches[i];
		if (pMatch->getSubCode())
			continue;
		if (pMatch->getRound()==nRound)
		{
			switch(pMatch->getStatus())
			{
			case CHMemoryDataBase::eAvailable:
				sAvailable++;
				break;
			case CHMemoryDataBase::eConfigured:
				sConfigured++;
				break;
			case CHMemoryDataBase::eSchedulled:
				sSchedulled++;
				break;
			case CHMemoryDataBase::eStartList:
				sStartList++;
				break;
			case CHMemoryDataBase::eRunning:
				sRunning++;
				break;
			case CHMemoryDataBase::eUnofficial:
				sUnofficial++;
				break;
			case CHMemoryDataBase::eFinished:
				sFinished++;
				break;
			case CHMemoryDataBase::eProtested:
				sProtested++;
				break;
			}
		}
	}
	//miro los totales primero
	if (sAvailable==totMatches)
		return CHMemoryDataBase::eAvailable;
	if (sConfigured==totMatches)
		return CHMemoryDataBase::eConfigured;
	if (sSchedulled==totMatches)
		return CHMemoryDataBase::eSchedulled;
	if (sStartList==totMatches)
		return CHMemoryDataBase::eStartList;
	if (sRunning==totMatches)
		return CHMemoryDataBase::eRunning;
	if (sUnofficial==totMatches)
		return CHMemoryDataBase::eUnofficial;
	if (sFinished==totMatches)
		return CHMemoryDataBase::eFinished;
	if (sProtested==totMatches)
		return CHMemoryDataBase::eProtested;
	//miro los subtotales
	if ((sRunning<totMatches && sRunning>0) || (sUnofficial<totMatches && sUnofficial>0) ||
		(sFinished<totMatches && sFinished>0) || (sProtested<totMatches && sProtested>0))//estamos a running
		return CHMemoryDataBase::eRunning;
	if ((sStartList<totMatches && sStartList>0) && (sRunning==0) && (sUnofficial==0) &&
		(sFinished==0) && (sProtested==0))
		return CHMemoryDataBase::eStartList;
	if ((sSchedulled<totMatches && sSchedulled>0) && (sStartList==0) && (sRunning==0) &&
		(sUnofficial==0) &&	(sFinished==0) && (sProtested==0))
		return CHMemoryDataBase::eSchedulled;
	return actualStatus;
}

short CHPool::getNumRoundsPlayed()
{
	short nRounds=0;
	for (short i=1;i<=getNumRounds();i++)
	{
		if (getRoundStatus(i)==CHMemoryDataBase::eFinished)
			nRounds++;
		else
			return nRounds;
	}
	return nRounds;
}

short CHPool::getRoundMatches(short nRound)
{
	short count=0;
	CHMatch* pMatch=0;
	MSLSortedVector vMatches;
	getMatchesVector(vMatches);
	for (short i=0;i<vMatches.entries();i++)
	{
		pMatch = (CHMatch*) vMatches[i];
		if (pMatch->getRound()==nRound && pMatch->getSubMatch()==0)
			count++;
	}
	return count;
}

void CHPool::getRoundMatchesVector(MSLSortedVector &vRoundMatches, short nRound)
{
	CHMatch* pMatch=0;
	MSLSortedVector vMatches;
	getMatchesVector(vMatches);
	for (short i=0;i<vMatches.entries();i++)
	{
		pMatch = (CHMatch*) vMatches[i];
		if (pMatch->getRound()==nRound && pMatch->getSubMatch()==0)
			vRoundMatches.insert(pMatch);
	}
	vRoundMatches.setFcCompare(orderMatches);
	vRoundMatches.sort();
}

void CHPool::getFromRoundMatchesVector(MSLSortedVector &vRoundMatches, short nRound)
{
	CHMatch* pMatch=0;
	MSLSortedVector vMatches;
	getMatchesVector(vMatches);
	for (short i=0;i<vMatches.entries();i++)
	{
		pMatch = (CHMatch*) vMatches[i];
		if (pMatch->getRound()>=nRound && pMatch->getSubMatch()==0)
			vRoundMatches.insert(pMatch);
	}
}

bool CHPool::hasCompatibleColors(CHPoolResult* pPR1,CHPoolResult* pPR2, short round)
{
	if (pPR1 &&
		pPR1->getEvent() &&
		pPR1->isTeamEvent())
		return true;

	CHMatchResult::colorPreference color1 = pPR1->getColorPreference(round);
	CHMatchResult::colorPreference color2 = pPR2->getColorPreference(round);

	if (color1==CHMatchResult::eBlackAbsolut &&
		color2==CHMatchResult::eBlackAbsolut)
		return false;	

	if (color1==CHMatchResult::eWhiteAbsolut &&
		color2==CHMatchResult::eWhiteAbsolut)
		return false;

	return true;
}

bool CHPool::hasCompetitors()
{	
	CHPoolResult* pPoolResult=0;
	MSLSortedVector vPools;
	getPoolResultsVector(vPools);
	for (short j=0; j<vPools.entries(); j++)
	{
		pPoolResult=(CHPoolResult*)(vPools[j]);
		if (!pPoolResult->getRegister())
			return false;
	}
	return (true);
}

CHMatch * CHPool::findMatch(CHPoolResult * pPoolResult, CHPoolResult * pPoolResultOpp)
{
	MSLSortedVector vMatches;
	getMatchesVector(vMatches);

	for(int i=0 ; i<vMatches.entries() ; i++)
	{
		CHMatch *pMatch        = (CHMatch*)vMatches[i];
		
		CHMatchResult *pMatchResult1 = (CHMatchResult *)(pMatch ? pMatch->getHome() : 0);
		CHMatchResult *pMatchResult2 = (CHMatchResult *)(pMatch ? pMatch->getAway() : 0);
		
		CHPoolResult *pPoolResult1  = (CHPoolResult  *)(pMatchResult1 ? pMatchResult1->getPoolResult() : 0);
		CHPoolResult *pPoolResult2  = (CHPoolResult  *)(pMatchResult2 ? pMatchResult2->getPoolResult() : 0);

		if( ( pPoolResult1 == pPoolResult   && pPoolResult2 == pPoolResultOpp ) ||
			( pPoolResult1 == pPoolResultOpp && pPoolResult2 == pPoolResult   ) )
		{
			return pMatch;
		}	
	}
	return 0;
}

bool CHPool::isTeam()
{
	CHEvent *pEvent=(CHEvent*)getEvent();
	if(pEvent)
		return pEvent->isTeam();

	return false;
}

void CHPool::getSamePointsCompetitorsVector(MSLSortedVector &vector, CHPoolResult * pPoolResult)
{
	MSLSortedVector vCompetitors;
	getPoolResultsVector(vCompetitors);
	for (short i=0;i<vCompetitors.entries();i++)
	{
		CHPoolResult * pPR = (CHPoolResult *)vCompetitors[i];
		if (pPR==pPoolResult)
			continue;

		if (pPR->getPointsF() == pPoolResult->getPointsF())
			vector.insert(pPR);
	}
}

