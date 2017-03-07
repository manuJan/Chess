/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
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
#include "CHClassIds.h"
#include "CHDiscipline.h"
#include "UCHPool.h"
#include <core/G/GBuffer.h>

RWDEFINE_COLLECTABLE(CHPool, __CHPOOL)


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHPool::CHPool()
:GTHPool()
{
}

CHPool::CHPool(const CHPool & copy)
{
	operator=(copy);
}

CHPool::CHPool(CPack& aPack)
{
	unpack(aPack);
}

CHPool::~CHPool()
{
}


//////////////////////////////////////////////////////////////////////
// Operators
//////////////////////////////////////////////////////////////////////
CHPool & CHPool::operator =(const CHPool & copy)
{
	if (this != &copy)
	{
		GTHPool::operator =(copy);
	}
	return * this;
}

RWBoolean CHPool::operator ==(const CHPool & copy)
{
	if (this == &copy)
		return true;
	else
		return (GTHPool::operator ==(copy));
}

RWBoolean CHPool::operator !=(const CHPool & copy)
{
	return !operator==(copy);
}


//////////////////////////////////////////////////////////////////////
// From GData
//////////////////////////////////////////////////////////////////////
RWBoolean CHPool::uSQL(RWDBConnection& pConnect,RWBoolean remove /*=false*/ )
{
	RWBoolean rc=false;

	UCHPool upd(&pConnect);

	if( remove )  rc=upd.remove(*this);
	else          rc=upd.set   (*this);

	return rc;
}

CPack& CHPool::pack(CPack& aPack)
{
	GTHPool::pack(aPack);
	

	return aPack;
}

CPack& CHPool::unpack(CPack& aPack)
{
	GTHPool::unpack(aPack);

	return aPack;
}

RWCString CHPool::msl() const
{
	RWCString str = GTHPool::msl();

	GBuffer aBuffer;

	return str +  RWCString (aBuffer << endLine );
}

RWCString CHPool::mslDescription(const char *language) const
{
	return GTHPool::mslDescription(language);
}

//////////////////////////////////////////////////////////////////////
// Help Methods
//////////////////////////////////////////////////////////////////////

GTHPhase::DescriptionMode CHPool::getDescriptionMode() const
{
	return getPhase() ? getPhase()->getPoolDescription() : GTHPhase::eNumeric;
}

RWWString CHPool::getOrderAsString(GTHPhase::DescriptionMode mode/*=GTHPhase::eNumeric*/) const
{
	wchar_t txt[200];

	if( mode == GTHPhase::eNumeric )
		swprintf(txt,_T("%d"),getOrder());
	else
	{
		swprintf(txt,_T("%c"),(getOrder()-1)+'A');
	}

	return txt;
}
RWWString CHPool::getDescription(GTHPhase::DescriptionMode mode/*=DescriptionMode::eNumber*/,const char *language/*=DBApplication::getAppLanguage()*/) const
{
	RWWString desc(NULLRWWSTRING);
	wchar_t tmp[20];

	if( getPhase()->getIsPool() )
	{
		desc=((CHDiscipline &)CHMemoryDataBase::getDiscipline()).getSPoolDescription(language)+RWWString(' ');
		if( mode==GTHPhase::eNumeric )
			desc+=_itow(getOrder(),tmp,10);
		else
		{
			char car=char((getOrder()-1)+'A');
			desc+=RWWString(car);
		}
	}
	else
	{
		desc=((CHDiscipline &)CHMemoryDataBase::getDiscipline()).getSMatchDescription(language)+RWWString(' ');
		desc+=_itow(getOrder(),tmp,10);
	}

	return desc;

	
	UNREFERENCED_PARAMETER(language);
}

RWWString CHPool::getSDescription(GTHPhase::DescriptionMode mode/*=GTHPhase::eNumeric*/,const char *language/*=DBApplication::getAppLanguage()*/) const
{
	UNREFERENCED_PARAMETER(language);
	RWWString desc(NULLRWWSTRING);
	wchar_t tmp[20];

	if( getPhase()->getIsPool() )
	{
		if( mode==GTHPhase::eNumeric )
			desc+=_itow(getOrder(),tmp,10);
		else
		{
			char car=char((getOrder()-1)+'A');
			desc+=RWWString(car);
		}
	}
	else
	{
		desc+=_itow(getOrder(),tmp,10);
	}

	return desc;
}

RWWString CHPool::getLDescription(GTHPhase::DescriptionMode mode/*=GTHPhase::eNumeric*/,const char *language/*=DBApplication::getAppLanguage()*/) const
{
	return getDescription(mode,language);
	
}

unsigned char CHPool::getRoundStatus(short nRound)
{
	size_t sAvailable=0, sConfigured=0, sSchedulled=0, sStartList=0, sRunning=0, sUnofficial=0, sFinished=0, sProtested=0;
	unsigned char actualStatus=CHMemoryDataBase::eAvailable;
	size_t totMatches=getRoundMatches(nRound);
	CHMatch* pMatch=0;
	for (size_t i=0;i<getMatchsVector().entries();i++)
	{
		pMatch = (CHMatch*) getMatchsVector()[i]->getElement();
		if (pMatch->areTeamIndividual())
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
	for (size_t i=1;i<=getNumRounds();i++)
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
	for (size_t i=0;i<getMatchsVector().entries();i++)
	{
		pMatch = (CHMatch*) getMatchsVector()[i]->getElement();
		if (pMatch->getRound()==nRound && pMatch->getSubMatch()==0)
			count++;
	}
	return count;
}

bool CHPool::hasCompatibleColors(CHPoolResult* pPR1,CHPoolResult* pPR2, short round)
{
	if (pPR1 &&
		pPR1->getEvent() &&
		pPR1->getEvent()->isTeam())
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

RWBoolean CHPool::hasCompetitors()
{	
	CHPoolResult* pPoolResult=0;
	for (size_t j=0; j<getPoolResultsVector().entries(); j++)
	{
		pPoolResult=(CHPoolResult*)(getPoolResultsVector()[j]->getElement());
		if (!pPoolResult->getRegister())
			return false;
	}
	return (true);
}