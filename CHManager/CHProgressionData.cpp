/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHProgressionData.cpp
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
#include "CHManagerApp.h"
#include "CHProgressionData.h"
#include "CHProgression.h"

#include "..\CHMngtModel\CHEvent.h"
#include "..\CHMngtModel\CHInscription.h"
#include "..\CHMngtModel\CHMatchResult.h"
#include "..\CHMngtModel\CHMatch.h"
#include "..\CHMngtModel\CHPool.h"
#include "..\CHMngtModel\CHPhase.h"
#include "..\CHMngtModel\CHPhaseBase.h"

#include <OVR\Core\TH\GTHMsgDefines.h>

static
bool eventInscriptions(const MSLItem* p,const void *n)
{
	CHEvent* pEvent = (CHEvent *)n;
	CHInscription* pInscription = (CHInscription *)p;	

	if ( pEvent && 
		 pInscription->getEventKey() == pEvent->getKey() )
		 return true;

	return false;
}

CHProgressionData::CHProgressionData(MSLGUIEx *pGUIEx)
:GTHProgressionData(pGUIEx)
{
}

CHProgressionData::~CHProgressionData()
{
}

bool CHProgressionData::preSelectModality(GTHEvent* pEvent, GTHModality* pModality)
{
	if (!pEvent || !pModality)
		return false;

	MSLSet colInscriptions = (CHMemoryDataBase::getCol(__CHINSCRIPTION)).select(eventInscriptions, pEvent);
	long entries = colInscriptions.entries();
	if (!entries)
	{
		MSLMsgBox( m_pGUIEx->getHWnd() ,"This event has no entries, the modality cannot be assigned",GUI_ICO_ERROR, GUI_MB_OK, "CHManager Error");
		return false;
	}

	return true;
}	

GTHPhase* CHProgressionData::createPhase(GTHEvent* pEvent, MSLString phaseCode, GTHModalityPhase* pModalityPhase)
{
	return GTHProgressionData::createPhase(pEvent,phaseCode,pModalityPhase);
}


void CHProgressionData::onCreatePhase(GTHPhase* pPhase, GTHModalityPhase* pModalityPhase)
{
	CHEvent* pEvent = (CHEvent*)pPhase->getEvent();
	if (!pEvent)
		return;
	
	if (pModalityPhase)
	{
		//((CHPhase*)pPhase)->setNumSubMatches(pModalityPhase->getNumSubMatchs());
		//((CHPhase*)pPhase)->setSubMatchesMembers(pModalityPhase->getSubMatchesMembers());

		/*((CHPhase*)pPhase)->setNumArrows		( ((ARModalityPhase*) pModalityPhase)->getNumArrows());
		((CHPhase*)pPhase)->setNumEnds			( ((ARModalityPhase*) pModalityPhase)->getNumEnds());
		((CHPhase*)pPhase)->setNumArrowsShootOff( ((ARModalityPhase*) pModalityPhase)->getNumArrowsShootOff());
		((CHPhase*)pPhase)->setNumEndsShootOff	( ((ARModalityPhase*) pModalityPhase)->getNumEndsShootOff());
		((CHPhase*)pPhase)->setSOSplit			( ((ARModalityPhase*) pModalityPhase)->getSOSplit());
		((CHPhase*)pPhase)->setClosestSplit		( ((ARModalityPhase*) pModalityPhase)->getClosestSplit());
		((CHPhase*)pPhase)->setScoringType		( ((ARModalityPhase*) pModalityPhase)->getScoringType());*/
	}
	else
	{	
		/*CHPhaseBase* pPhaseBase = (CHPhaseBase*) CHMemoryDataBase::findPhaseBase(pPhase->getPhase());
		if (!pPhaseBase)
			return;
		
		if (pEvent->getTeamMembers())
		{
			((CHPhase*)pPhase)->setNumSubMatches(pEvent->getTeamMatches());
			((CHPhase*)pPhase)->setSubMatchesMembers(pEvent->getCfgTeamMembers());			
		}*/		
	}
}

void CHProgressionData::onCreatePoolResult(GTHPoolResult*	pPoolResult, GTHModalityPool * pModalityPool)
{
	pPoolResult->setQualitative(OK);
	UNREFERENCED_PARAMETER(pModalityPool);
}

void CHProgressionData::onCreateMatch(GTHMatch* pMatch, GTHModalityPool * pModalityPool)
{
	CHPool* pPool = (CHPool*)pMatch->getPool();	
	short round = ((pMatch->getCode()-1)/pPool->getNumMatches()) + 1;
	((CHMatch*)pMatch)->setRound(round);
}

void CHProgressionData::onCreateMatchResult(GTHMatchResult* pMatchResult, GTHModalityPool * pModalityPool)
{
	((CHMatchResult*)pMatchResult)->setQualitative(OK);		
	if(pMatchResult->getPosition()==1)
		((CHMatchResult*)pMatchResult)->setColor(CHMatchResult::eWhite);
	if(pMatchResult->getPosition()==2)
		((CHMatchResult*)pMatchResult)->setColor(CHMatchResult::eBlack);

	UNREFERENCED_PARAMETER(pModalityPool);
}

bool CHProgressionData::onMatchResultCreated(GTHMatchResult* pMatchResult, GTHModalityPool* pModalityPool)
{
	bool rtn=GTHProgressionData::onMatchResultCreated(pMatchResult,pModalityPool);
	if(rtn)
	{
		CHEvent * pEvent=(CHEvent *)pMatchResult->getEvent();
		CHPhase * pPhase=(CHPhase *)pMatchResult->getPhase();

		int nMembers = 0;
		// Match members del equipo
		if (!pMatchResult->getMatchSubCode() && pEvent->getSubMatches())
		{
			nMembers = pEvent->getTeamMembers();
		}
		else
		{
			nMembers = pEvent->getSubMatches() ?
			           pPhase->getSubMatchMembers(pMatchResult->getMatchSubCode()) :
				       pEvent->getTeamMembers();
		}

		for (short n=0;n<nMembers;n++)
		{
			createMatchMember((CHMatchResult*)pMatchResult,short(n+1));
		}
	}
	return rtn;
}

GTHMatchMember * CHProgressionData::createMatchMember(CHMatchResult* pMatchResult, short matchMember)
{
	GTHMatchMember aMatchMember(pMatchResult,matchMember);
	
	//insertamos en el modelo
	GTHMatchMember * pMatchMember = (GTHMatchMember*)getMem()->set(aMatchMember);
	APP::out(*pMatchMember);

	return pMatchMember;
}


void CHProgressionData::calculatePoolPosition(GTHMatch* pMatch, short position, int &local, int &away, int &poolPos)
{
	if (pMatch->getPhaseCode()!=SWISS_ROUND)
	{
		GTHProgressionData::calculatePoolPosition(pMatch, position, local, away, poolPos);
		return;
	}

	poolPos=0;
	local=0;
	away=0;
}

int	CHProgressionData::calculateMatchesByPool(int nCompetitors)
{
	int numMatches=0;
	if(nCompetitors>0)
	{
		numMatches=nCompetitors/2;
		if (nCompetitors%2)
			numMatches++;
	}

	return numMatches;
}
