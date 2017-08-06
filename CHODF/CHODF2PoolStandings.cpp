/*************************************************************************************
*			© Copyright MSL Software, S.L., 2015
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHODF2PoolStandings.cpp
*	Description	:
*
*	Author		: Antonio Balmaseda
*	Date created: 29-01-2015
* 	Project		: TE ODF
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#include "StdAfx.h"
#include "CHODF2PoolStandings.h"
#include "CHODF2Defines.h"
#include "CHODFModel.h"
#include "..\CHMngtModel\CHPoolResult.h"
#include "..\CHMngtModel\CHInscription.h"
#include "..\CHMngtModel\CHMember.h"
#include "..\CHMngtModel\CHMatch.h"

static int orderPoolResultsByRanking(const MSLItem** a, const MSLItem** b)
{
	GTHPoolResult * pPoolResultA = (GTHPoolResult *)(*a);
	GTHPoolResult * pPoolResultB = (GTHPoolResult *)(*b);

	int order = 0;
	if( pPoolResultA->getRankPo() || pPoolResultB->getRankPo() )
	{
		if( !pPoolResultA->getRankPo() ) return  1;
		if( !pPoolResultB->getRankPo() ) return -1;
		order = pPoolResultA->getRankPo() - pPoolResultB->getRankPo();
	}
	return order ? order : strcmp(pPoolResultA->getKey(),pPoolResultB->getKey());
}

CHODF2PoolStandings::CHODF2PoolStandings(ODF2BuildBase * pBuild,XMLElement * pElement,ODF2FileBase * pFile,GData * pData)
:ODF2THZZPoolStandings(pBuild,pElement,pFile,pData)
{
}

CHODF2PoolStandings::~CHODF2PoolStandings(void)
{
}

void CHODF2PoolStandings::fillSportXXDescription(GEvent * pEvent,XMLElement * pEl_SportDesc)
{	
}

void CHODF2PoolStandings::fillVectorResults(MSLArray & vResults,MSLItem * pData/*=0*/)
{
	GTHPool * pPool = pData && pData->isA()==__GTHPOOL ? (GTHPool *)pData : 0;
	if( !pPool )
		return;

	m_vPoolResults.clear();

	GTHPoolResult * pPoolResult = 0;
	pPool->getPoolResultsVector(m_vPoolResults,orderPoolResultsByRanking);
	for(int i=0 ; i<m_vPoolResults.entries() ; i++)
	{
		pPoolResult = (GTHPoolResult *)m_vPoolResults[i];
		if (pPoolResult->getBye())
			continue;

		if( isSelectable(pPoolResult) )
			vResults.insert(pPoolResult);
	}
}

void CHODF2PoolStandings::fillSportResult(MSLItem * pResult,XMLElement * pEl_Result,int order)
{
	ODF2THZZPoolStandings::fillSportResult(pResult,pEl_Result,order);

	if( !pResult || !pEl_Result )
		return;

	CHPoolResult * pPR = (CHPoolResult*)pResult;

	if(pPR->getQualitativeCode()==DSQ)
	{
		pEl_Result->setAttribute("ResultType","IRM_POINTS");
		pEl_Result->setAttribute("IRM",DSQ);
	}
}

void CHODF2PoolStandings::fillVectorComposition(MSLItem * pCompetitor,MSLSortedVector & vComposition)
{
	CHPoolResult *pPoolResult = (CHPoolResult*)pCompetitor;
	CHInscription *pInscription = pPoolResult?(CHInscription *)pPoolResult->getInscription():0; 
	if (!pInscription)
		return;
	
	if(pInscription->getType()==GRegister::individual)
	{
		vComposition.insert(pInscription);
	}
	else
	{
		MSLSortedVector vMembers;
		pInscription->getMembersVector(vMembers);

		CHMember * pMember=0;
		for(int i=0; i<vMembers.entries()  ;i++)
		{
			pMember=(CHMember*)vMembers[i];
			if(pMember->getType()==GRegister::individual)
				vComposition.insert(pMember);
		}
	}
}

void CHODF2PoolStandings::fillSportAthlete(MSLItem * pAthlete,XMLElement * pEl_Athlete)
{
	if(!pAthlete)
		return;

	if(pAthlete->isA()==__CHINSCRIPTION)
	{
		CHInscription * pInsc = (CHInscription*)pAthlete;
		pEl_Athlete->setAttribute("Code",pInsc->getAcreditation());
		pEl_Athlete->setAttribute("Order","1");
	}
	else if(pAthlete->isA()==__CHMEMBER)
	{
		CHMember *pMember = (CHMember*)pAthlete;

		pEl_Athlete->setAttribute("Code",pMember->getAcreditation());
		pEl_Athlete->setAttribute("Order",TOSTRING(pMember->getOrder()));
	}
}

void CHODF2PoolStandings::fillExtendedResults(MSLItem * pCompetitor,XMLElement * pEl_Competitor)
	/*fillExtendedResultsGames(GTHPoolResult* pPoolResult,XMLElement * pEl_Competitor)*/
{

	if(pEl_Competitor->getLabel()=="Competitor")
	{
		//CHPoolResult * pCHPoolResult=(CHPoolResult*) pPoolResult;
		CHPoolResult *pCHPoolResult = (CHPoolResult*)pCompetitor;
		
		// ER
		XMLElement * pExtendedResults = addExtension(	"ExtendedResults", "ExtendedResult",pEl_Competitor,	ER,MATCHES,"","" );

		// Extensions MATCHES

		// PLAYED
		addExtension(	"Extensions", "Extension",pExtendedResults,MATCHES,PLAYED,"",TOSTRING(pCHPoolResult->getMPlayed(),"0") );

		// WON
		addExtension(	"Extensions", "Extension",pExtendedResults,MATCHES,WON,"",TOSTRING(pCHPoolResult->getMWon(),"0") );

		// LOST
		addExtension(	"Extensions", "Extension", pExtendedResults,MATCHES,LOST,"",TOSTRING(pCHPoolResult->getMLost(),"0"));
		
		// TIE
		addExtension(	"Extensions", "Extension", pExtendedResults,MATCHES,TIE,"",TOSTRING(pCHPoolResult->getMDrawn(),"0") );

		// POINTS
		addExtension(	"Extensions", "Extension",pExtendedResults,MATCHES,POINTS,"",pCHPoolResult->getPointsFStr());

		// MATCH POINTS
		if (pCHPoolResult->isTeamEvent())
			addExtension(	"Extensions", "Extension",pExtendedResults,MATCHES,MATCH_POINTS,"",pCHPoolResult->getMatchPointsStr());
	}
}

void CHODF2PoolStandings::fillVectorOpponents(MSLItem * pCompetitor,MSLSortedVector & vOpponents)
{
	m_pPoolResultSel = pCompetitor && pCompetitor->isA()==__GTHPOOLRESULT ? (GTHPoolResult *)pCompetitor : 0;
	if( !m_pPoolResultSel )
		return;
	
	MSLSortedVector vMatchResults;
	m_pPoolResultSel->getMatchResultsVector(vMatchResults);

	CHMatchResult * pMatchResult = 0;
	CHMatchResult * pOppMatchResult = 0;
	GTHPoolResult * pOpponent = 0;
	for(int i=0 ; i<vMatchResults.entries() ; i++)
	{
		pMatchResult = (CHMatchResult *)vMatchResults[i];
		if (!pMatchResult)
			continue;

		pOppMatchResult = (CHMatchResult *)pMatchResult->getOpponent();
		if (!pOppMatchResult)
			continue;

		pOpponent = pOppMatchResult->getPoolResult();
		if (!pOpponent)
			continue;

		if( isSelectable(pOpponent) && pOpponent != m_pPoolResultSel )
		{
			vOpponents.insert(pOpponent);
		}
	}
	vOpponents.setFcCompare(orderPoolResultsByRanking);
}

void CHODF2PoolStandings::fillSportOpponent(MSLItem * pOpponent,XMLElement * pEl_Opponent)
{
	ODF2THZZPoolStandings::fillSportOpponent(pOpponent,pEl_Opponent);

	CHPoolResult * pPoolResultOpp = pOpponent && pOpponent->isA()==__GTHPOOLRESULT ? (CHPoolResult *)pOpponent : 0;
	if( !pPoolResultOpp || !m_pPoolResultSel )
		return;

	if (m_pMatchSel && m_pMatchSel->getStatus()==GTHMemoryDataBase::eFinished)
		pEl_Opponent->setAttribute("Result",CHODFMODEL->getResult(m_pMatchSel, m_pPoolResultSel, pPoolResultOpp));
}

bool CHODF2PoolStandings::isSelectable(GData * pData)
{
	if (!pData)
		return false;

	if (pData->isA()==__CHMATCH)
	{
		if(((CHMatch*)pData)->getSubMatch())
			return false;
	}

	return ODF2THZZPoolStandings::isSelectable(pData);
}

