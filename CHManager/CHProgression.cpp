/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHProgression.h
*   Description : 
*
*   Author      : Javier Juste
*   Date created: 2-FEb-2009
*   Project     : AR Manager
*
*   Modification history
*   By      :
*   Date    :
*   Changes :
*
*****************************************************************************************/

#include "StdAfx.h"
#include "CHProgression.h"
#include "CHStatusManager.h"
#include "CHManagerApp.h"

#include "..\CHMngtModel\CHMatch.h"
#include "..\CHMngtModel\CHMatchResult.h"
#include "..\CHMngtModel\CHInscription.h"
#include "..\CHMngtModel\CHMember.h"
#include "..\CHMngtModel\CHRegister.h"
#include "..\CHMngtModel\CHPool.h"

#include <OVR\GUI\GUITHManager\GTHRanking.h>

#define UMPIRE 2 //a pinrel

static
int orderMatchMemberByRating(const MSLItem** a, const MSLItem** b)
{	
	GTHMatchMember *pMMA = (GTHMatchMember *)(*a);
	GTHMatchMember *pMMB = (GTHMatchMember *)(*b);

	CHMember *pMemberA = (CHMember *)pMMA->getMember();
	CHMember *pMemberB = (CHMember *)pMMB->getMember();

	if (pMemberA && pMemberB)
	{
		int order =pMemberB->getRating() - pMemberA->getRating();
		if(order)
			return order;
		
		return strcmp(pMemberA->getKey(),pMemberB->getKey());
	}

	return strcmp(pMMA->getKey(),pMMB->getKey());
}

CHProgression::CHProgression(MSLGUIEx* pGUIEx)
:GTHProgression(pGUIEx)
{
}

CHProgression::~CHProgression(void)
{
}

void CHProgression::setData(GTHInscription* pInscription, GTHMatchResult* pMatchResult, bool bye, bool includeSubMacthes, bool progression/*=true*/)
{
	GTHProgression::setData(pInscription, pMatchResult,bye,includeSubMacthes,progression);

	// Inicializo los match members del partido padre
	if (!pMatchResult->getMatchSubCode())
		initAllMatchMember((CHMatchResult*)pMatchResult);
}

void CHProgression::initAllMatchMember(CHMatchResult * pMatchResult)
{
	CHEvent * pEvent = (CHEvent*)pMatchResult->getEvent();
	if(!pEvent)
		return;
		
	CHInscription * pInscription = (CHInscription*)pMatchResult->getInscription();
	MSLSortedVector vMembers;
	if(pInscription)
		pInscription->getMembersVector(vMembers);

	MSLSortedVector vMatchMembers;
	pMatchResult->getMatchMembersVector(vMatchMembers);

	GTHMatchMember * pMatchMember=0;
	for (int i=0 ; i<vMatchMembers.entries(); i++)
	{
		pMatchMember=(GTHMatchMember*)vMatchMembers[i];
		if(pInscription)
		{
			if(i<vMembers.entries())
			{
				CHMember * pMember = (CHMember*)vMembers[i];
				if(pMember && pMember->getType()==GRegister::individual)
					pMatchMember->setMember(pMember);
			}
			else
				pMatchMember->setMember(0);
		}
		else
			pMatchMember->setMember(0);

		APP::out(*pMatchMember);						
	}
}

void CHProgression::manageByes(CHMatch *pMatch)
{
	if(!pMatch)
		return;

	CHEvent* pEvent = (CHEvent*)pMatch->getEvent();
	if (!pEvent)
		return;	

	if(!pMatch->hasByes())
		return;

	CHMatchResult * pMR1 = (CHMatchResult*)pMatch->getHome();
	CHMatchResult * pMR2 = (CHMatchResult*)pMatch->getAway();	

	if(pMR1->getBye() && pMR2->getBye())
	{
		pMR1->setPoints(0);
		pMR2->setPoints(0);
	}
	else if(pMR1->getBye())
	{
		pMR1->setPoints(0);
		pMR2->setPoints(pEvent->getPointsBye());
	}
	else if(pMR2->getBye())
	{
		pMR1->setPoints(pEvent->getPointsBye());
		pMR2->setPoints(0);
	}

	CHSend.toServerDB(pMR1);
	CHSend.toServerDB(pMR2);
	
	CHStatusManager statusManager;
	statusManager.setStatus(pMatch,CHMemoryDataBase::eFinished);		
}

void CHProgression::setAutoSubMatchesAssign(CHMatch *pMatch)
{
	if(!pMatch)
		return;

	if (pMatch->getSubCode())
		return;

	CHEvent* pEvent = (CHEvent*)pMatch->getEvent();
	if (!pEvent)
		return;	

	if (!pEvent->getSubMatches())
		return;
	
	MSLSortedVector vSubMatches;
	pMatch->getSubMatchesVector(vSubMatches);

	CHMatchResult * pMR1 = (CHMatchResult*)pMatch->getHome();
	MSLSortedVector vMatchMembers1;
	pMR1->getMatchMembersVector(vMatchMembers1,orderMatchMemberByRating);

	CHMatchResult * pMR2 = (CHMatchResult*)pMatch->getAway();	
	MSLSortedVector vMatchMembers2;
	pMR2->getMatchMembersVector(vMatchMembers2,orderMatchMemberByRating);

	for (short i=0;i<vSubMatches.entries();i++)
	{
		CHMatch* pSubMatch = (CHMatch*)vSubMatches[i];

		CHMatchResult * pMRHome = (CHMatchResult*)pSubMatch->getHome();
		CHMatchResult * pMRAway = (CHMatchResult*)pSubMatch->getAway();
		
		GTHMatchMember * pMM1 = (GTHMatchMember * ) vMatchMembers1[i];
		GTHMatchMember * pMM2 = (GTHMatchMember * ) vMatchMembers2[i];

		if (pMRHome && pMM1 && pMM1->getRegister())
		{
			GTHMatchMember * pMMHome = (GTHMatchMember *)(pMRHome?pMRHome->getMatchMember(0):0);
			if (pMMHome)
			{
				pMMHome->setMember(pMM1->getMember());
				CHSend.toServerDB(pMMHome);		
			}
		}

		if (pMRAway && pMM2 && pMM2->getRegister())
		{
			GTHMatchMember * pMMAway = (GTHMatchMember *)(pMRAway?pMRAway->getMatchMember(0):0);
			if (pMMAway)
			{
				pMMAway->setMember(pMM2->getMember());
				CHSend.toServerDB(pMMAway);		
			}
		}
	}

	startListScheduleMatch(pMatch);
}

void CHProgression::removeAutoSubMatchesAssign (CHMatch *pMatch)
{
	if(!pMatch)
		return;

	if (pMatch->getSubCode())
		return;

	CHEvent* pEvent = (CHEvent*)pMatch->getEvent();
	if (!pEvent)
		return;	

	if (!pEvent->getSubMatches())
		return;
	
	MSLSortedVector vSubMatches;
	pMatch->getSubMatchesVector(vSubMatches);

	CHMatchResult * pMR1 = (CHMatchResult*)pMatch->getHome();	
	CHMatchResult * pMR2 = (CHMatchResult*)pMatch->getAway();	
	
	for (short i=0;i<vSubMatches.entries();i++)
	{
		CHMatch* pSubMatch = (CHMatch*)vSubMatches[i];

		CHMatchResult * pMRHome = (CHMatchResult*)pSubMatch->getHome();
		CHMatchResult * pMRAway = (CHMatchResult*)pSubMatch->getAway();
		if (pMRHome)
		{
			GTHMatchMember * pMMHome = (GTHMatchMember *)(pMRHome?pMRHome->getMatchMember(0):0);
			if (pMMHome)
			{
				pMMHome->setMember(0);
				CHSend.toServerDB(pMMHome);				
			}
		}

		if (pMRAway)
		{
			GTHMatchMember * pMMAway = (GTHMatchMember *)(pMRAway?pMRAway->getMatchMember(0):0);
			if (pMMAway)
			{
				pMMAway->setMember(0);
				CHSend.toServerDB(pMMAway);				
			}
		}
	}
	startListScheduleMatch(pMatch);
}

void CHProgression::changeSide(CHMatch *pMatch)
{
	if(!pMatch)
		return;

	CHMatchResult * pMR1 = (CHMatchResult*)pMatch->getHome();	
	CHMatchResult * pMR2 = (CHMatchResult*)pMatch->getAway();	

	if (pMR1 && pMR2 &&
		pMR1->getColor()==CHMatchResult::eWhite)
	{
		pMR1->setColor(CHMatchResult::eBlack);
		pMR2->setColor(CHMatchResult::eWhite);
	}
	else if (pMR1 && pMR2 &&
		pMR1->getColor()==CHMatchResult::eBlack)
	{
		pMR1->setColor(CHMatchResult::eWhite);
		pMR2->setColor(CHMatchResult::eBlack);
	}

	CHSend.toServerDB(pMR1);			
	CHSend.toServerDB(pMR2);			
}

void CHProgression::startListScheduleMatch(CHMatch *pMatch)
{
	CHStatusManager statusManager;

	MSLSortedVector vMatchJudges;
	pMatch->getMatchJudgesVector(vMatchJudges);
	
	MSLSortedVector vSubMatches;
	pMatch->getSubMatchesVector(vSubMatches);

	if (pMatch->getStatus()==CHMemoryDataBase::eStartList && vMatchJudges.entries()==0)
	{
		statusManager.setStatus(pMatch,CHMemoryDataBase::eSchedulled);
		for (short i=0;i<vSubMatches.entries();i++)
		{
			CHMatch * pSubMatch = (CHMatch *)vSubMatches[i];
			statusManager.setStatus(pSubMatch,CHMemoryDataBase::eSchedulled);	
		}
		return;
	}

	bool competitors = pMatch->hasCompetitors();
	if (pMatch->getStatus()==CHMemoryDataBase::eStartList && !competitors)
	{
		statusManager.setStatus(pMatch,CHMemoryDataBase::eSchedulled);		
		for (short i=0;i<vSubMatches.entries();i++)
		{
			CHMatch * pSubMatch = (CHMatch *)vSubMatches[i];
			statusManager.setStatus(pSubMatch,CHMemoryDataBase::eSchedulled);	
		}
		return;
	}

	bool teamCompetitors = pMatch->hasTeamCompetitors();
	bool teamSubMatchesCompetitors = true;
	
	if (vSubMatches.entries())
	{
		for (short i=0;i<vSubMatches.entries();i++)
		{
			CHMatch * pSubMatch = (CHMatch *)vSubMatches[i];
			teamSubMatchesCompetitors = pSubMatch->hasTeamCompetitors();
			if (!teamSubMatchesCompetitors)
				break;
		}
	}

	if (pMatch->getStatus()==CHMemoryDataBase::eStartList && ( !teamCompetitors || !teamSubMatchesCompetitors) )
	{
		statusManager.setStatus(pMatch,CHMemoryDataBase::eSchedulled);	
		for (short i=0;i<vSubMatches.entries();i++)
		{
			CHMatch * pSubMatch = (CHMatch *)vSubMatches[i];
			statusManager.setStatus(pSubMatch,CHMemoryDataBase::eSchedulled);	
		}
		return;
	}

	if (pMatch->getStatus()==CHMemoryDataBase::eSchedulled && teamCompetitors && teamSubMatchesCompetitors &&  vMatchJudges.entries()>0)
	{
		statusManager.setStatus(pMatch,CHMemoryDataBase::eStartList);		

		for (short i=0;i<vSubMatches.entries();i++)
		{
			CHMatch * pSubMatch = (CHMatch *)vSubMatches[i];
			statusManager.setStatus(pSubMatch,CHMemoryDataBase::eStartList);
		}
	}
}

void CHProgression::setMatchJudge(CHMatch * pMatch, GOfficial * pOfficial)
{
	CHRegister * pRegister    =(CHRegister*)(pOfficial? pOfficial->getRegister():0);
	if(pRegister)
	{
		if(createMatchJudge(pMatch, pRegister))
			APP::out(TRN_SET_MATCHJUDGE);
	}		
}

bool CHProgression::createMatchJudge(CHMatch * pMatch,CHRegister * pRegister)
{
	if(!pRegister)
		return false;

	GTHMatchJudge aMatchJudge;
	aMatchJudge.setMatch(pMatch);
	aMatchJudge.setRegister(pRegister);
	
	GFunction * pFunction = 0;
		
	pFunction=CHMemoryDataBase::findFunction(UMPIRE);
	if( pFunction )
		aMatchJudge.setFunction(pFunction);

	if(!CHMemoryDataBase::find(aMatchJudge))
	{
		GTHMatchJudge * pMatchJudge = (GTHMatchJudge *)getMem()->set(aMatchJudge);

		if(pMatchJudge )
		{
			APP::out(*pMatchJudge);
			return true;
		}
	}
	return false;
}

bool CHProgression::deleteMatchJudge(GTHMatchJudge * pMatchJudge)
{
	if(!pMatchJudge)
		return false;

	GTHMatchJudge * pDelJudge = (GTHMatchJudge *)getMem()->remove(*pMatchJudge);
	if(pDelJudge )
	{
		APP::out(*pDelJudge,false);
		APP::out(TRN_REMOVE_MATCHJUDGE);
		return true;
	}
	return false;
}

bool CHProgression::assignOfficialsToAllRoundGames	(CHMatch *pMatch)
{
	CHPool * pPool = (CHPool *) pMatch->getPool();
	MSLSortedVector vRoundMatches;
	if (pPool)
		pPool->getRoundMatchesVector(vRoundMatches, pMatch->getRound());

	MSLSortedVector vOfficials;
	pMatch->getMatchJudgesVector(vOfficials);

	for (short i=0;i<vRoundMatches.entries();i++)
	{
		CHMatch* pRoundMatch = (CHMatch* )vRoundMatches[i];
		if (pRoundMatch == pMatch)
			continue;

		for (short j=0;j<vOfficials.entries();j++)
		{
			GTHMatchJudge * pMJ = (GTHMatchJudge*)vOfficials[j];						
			if (pMJ->getRegister())
			{
				createMatchJudge(pRoundMatch, (CHRegister*)pMJ->getRegister());
				APP::out(TRN_SET_MATCHJUDGE);
			}
		}		

		startListScheduleMatch(pRoundMatch);
	}

	return true;
}
