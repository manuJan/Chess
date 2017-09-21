/*************************************************************************************
*			© Copyright MSL Software, S.L., 2014
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHODF2Results.cpp
*	Description	:
*
*	Author		: Fernando Hicar
*	Date created: 26-01-2015
* 	Project		: AR ODF
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#include "StdAfx.h"
#include "CHODF2Results.h"
#include "CHODF2Defines.h"
#include "CHODFApp.h"
#include "CHODFModel.h"

#include "..\CHMngtModel\CHMatch.h"
#include "..\CHMngtModel\CHMatchResult.h"
#include "..\CHMngtModel\CHMember.h"

static int orderMembers_result(const MSLItem** a, const MSLItem** b)
{
	CHMember * pA = (CHMember *)(*a);
	CHMember * pB = (CHMember *)(*b);

	int order=pA->getOrder()-pB->getOrder();
	if(order)
		return order;

	return strcmp(pA->getKey(),pB->getKey());
}

static
int orderMatchResultsByPosition(const MSLItem** a, const MSLItem** b)
{
	int order=0;

	CHMatchResult * pA=(CHMatchResult *)(*a);
	CHMatchResult * pB=(CHMatchResult *)(*b);
	
	order = pA->getPosition()-pB->getPosition();
	if (order)
		return order;

	return strcmp(pA->getKey(),pB->getKey());
}

static
int orderMatchResultByRankingPo(const MSLItem** a, const MSLItem** b)
{
	CHMatchResult * pA=((CHMatchResult *)(*a));
	CHMatchResult * pB=((CHMatchResult *)(*b));

	if (pA->getQualitativeCode()!=OK && 
		pB->getQualitativeCode()!=OK)
	{
		GQualitative * pQA = pA->getQualitative();
		GQualitative * pQB = pB->getQualitative();
		if (pQA && pQB)
			return pQA->getSort() - pQB->getSort();
	}
	if (pA->getQualitativeCode()!=OK)
		return 1;
	if (pB->getQualitativeCode()!=OK)
		return -1;		

	if (pA->getRankPo()==0 && 
		pB->getRankPo()==0)
		return orderMatchResultsByPosition(a,b);
		
	if (pA->getRank()==0)
		return 1;

	if (pB->getRank()==0)
		return -1;

	int rank=pA->getRank() - pB->getRank();
	if(rank)
		return rank;

	if (pA->getRankPo()==0)
		return 1;

	if (pB->getRankPo()==0)
		return -1;

	rank=pA->getRankPo() - pB->getRankPo();
	if(rank)
		return rank;

	return orderMatchResultsByPosition(a,b);
}


CHODF2Results::CHODF2Results(ODF2BuildBase * pBuild,XMLElement * pElement,ODF2FileBase * pFile,GData * pData)
	:ODF2THZZResults(pBuild,pElement,pFile,pData)
	,m_startOrder(1)
	,m_memberOrder(1)
{
	m_vCompetitors.setFcCompare(orderMatchResultsByPosition);
}

CHODF2Results::~CHODF2Results()
{
}

void CHODF2Results::fillUnitDateTime(XMLElement * pElement)
{
	if( !m_pData || !pElement )
		return;

	if( m_pData->isA()!=__CHMATCH )
		return;

	CHMatch * pMatch = (CHMatch *)m_pData;
	if (!pMatch)
		return;

	//StartDate & StartTime del partido 
	MSLDate startDate = pMatch->getStartDate();
	MSLTime startTime = pMatch->getStartTime();

	if( startDate.isValid() )
	{
		XMLElement *pEl_UnitDateTime = pElement->setElement(m_pEntUnitDateTime);
		if( !pEl_UnitDateTime )
			return;

		pEl_UnitDateTime->setAttribute("StartDate",getDateTime(startDate,startTime));
	}
}

void CHODF2Results::fillVectorExtendedInfo(MSLArray& vExInfos)
{	
	if( !m_pData )
		return;

	if( m_pData->isA()!=__CHMATCH )
		return;

	CHMatch * pMatch = (CHMatch *)m_pData;
	if (!pMatch)
		return;

	if (pMatch->getSubMatch())
		return;

	MSLSortedVector vSubMatches;
	pMatch->getSubMatchesVector(vSubMatches);

	CHMatch * pSubMatch=0;
	for( long i=0;i<vSubMatches.entries();i++ )
	{
		pSubMatch = (CHMatch *)vSubMatches[i];
		
		MSLString subMatchDesc = TOSTRING(pSubMatch->getSubCode());	
		if (pSubMatch->hasTeamCompetitors())
			vExInfos.insert(insertZZExtension(pSubMatch, UI, MATCH, TOSTRING(pSubMatch->getSubCode()), subMatchDesc));		
	}
}

void CHODF2Results::fillExtendedExtensions(MSLItem * pData,XMLElement *pEl_ExInfo)
{
	ODFZZExt* pExtension = (ODFZZExt*)pData;
	if (!pExtension)
		return;

	MSLItem * pItem=pExtension->getExtItem();

	if(pItem->isA()==__CHMATCH)
	{
		CHMatch* pMatch = (CHMatch*)pItem;
		if (!pMatch)
			return;

		if (!pMatch->getSubCode())
			return;

		if (pMatch->getCourtCode())
			addExtension("","Extension",pEl_ExInfo,"",TABLE,"",TOSTRING(pMatch->getCourtCode()));

		addExtension("","Extension",pEl_ExInfo,"",STATUS,"", CHODFMODEL->getODFResultStatus(pMatch,pMatch->getStatus(),DT_RESULT));

		if (pMatch->getWhite() && 
			pMatch->getWhite()->getInscription())
		{
			CHMatchResult * pWhite = (CHMatchResult *)pMatch->getWhite();
			MSLString whiteAcreditation = pWhite->getAcreditation_CH();
			if (whiteAcreditation!=NULLSTRING)
				addExtension("","Extension",pEl_ExInfo,"",WHITE,"",whiteAcreditation);

			if (pMatch->getStatus()==CHMemoryDataBase::eUnofficial ||
				pMatch->getStatus()==CHMemoryDataBase::eFinished)
				addExtension("","Extension",pEl_ExInfo,"",WHITE_PTS,"",pWhite->getPointsAsString());
		}
		if (pMatch->getBlack() && 
			pMatch->getBlack()->getInscription())
		{
			CHMatchResult * pBlack = (CHMatchResult *)pMatch->getBlack();
			MSLString blackAcreditation = pBlack->getAcreditation_CH();
			if (blackAcreditation!=NULLSTRING)
				addExtension("","Extension",pEl_ExInfo,"",BLACK,"",blackAcreditation);

			if (pMatch->getStatus()==CHMemoryDataBase::eUnofficial ||
				pMatch->getStatus()==CHMemoryDataBase::eFinished)
				addExtension("","Extension",pEl_ExInfo,"",BLACK_PTS,"",pBlack->getPointsAsString());
		}
	}
}

void CHODF2Results::fillSportXXVenueDescription(GVenue * pVenue,XMLElement * pEl_VenueDesc)
{
	if( m_pData->isA()!=__CHMATCH )
		return;

	CHMatch * pMatch=(CHMatch*)m_pData;
	
	pEl_VenueDesc->setAttribute("Location",CHODFMODEL->getCourtODFString(pMatch));
	//pEl_VenueDesc->setAttribute("LocationName",pMatch->getCourtLDescription());
}

void CHODF2Results::fillCompetitor(MSLItem * pCompetitor,XMLElement * pEl_Competitor)
{
	if( !pCompetitor || !pEl_Competitor )
		return;

	CHMatchResult * pMR=0;
	if(pCompetitor->isA()==__CHMATCHRESULT)
		pMR=(CHMatchResult*)pCompetitor;

	if (!pMR)
		return;

	fillDescription(pCompetitor,pEl_Competitor);

	fillEventUnitEntry(pCompetitor,pEl_Competitor);
		
	fillComposition(pCompetitor,pEl_Competitor);
}

void CHODF2Results::fillSportCompetitor(MSLItem * pCompetitor, XMLElement * pEl_Competitor)
{
	if( !pCompetitor || !pEl_Competitor )
		return;

	GTHMatchResult * pMR = (GTHMatchResult *)pCompetitor;
	GTHEvent * pEvent = (GTHEvent *)pMR->getEvent();
	if( !pEvent )
		return;

	pEl_Competitor->setAttribute("Code",pMR->getBye() ? "NOCOMP" : pMR->getAcreditation());
	pEl_Competitor->setAttribute("Type",pEvent->getRegType()==GRegister::individual?"A":"T"); 	//pEl_Competitor->setAttribute("Type",pEvent->getTeamMembers()?"T":"A");
		
	GRegister *pRegister=pMR->getRegister();
	if(pRegister)
		pEl_Competitor->setAttribute("Organisation",pRegister->getOrgID());

	CHMatchResult * pMatchResult=0;
	if(pCompetitor->isA()==__CHMATCHRESULT)
		pMatchResult=(CHMatchResult*)pCompetitor;
}

void CHODF2Results::fillAthlete(MSLItem * pAthlete,XMLElement * pEl_Athlete)
{
	fillSportAthlete(pAthlete,pEl_Athlete);

	fillDescription(pAthlete,pEl_Athlete);
	
	fillEventUnitEntry(pAthlete,pEl_Athlete);

	fillExtendedResults(pAthlete,pEl_Athlete);

	fillStats(pAthlete,pEl_Athlete);
}

void CHODF2Results::fillSportAthlete(MSLItem * pAthlete,XMLElement * pEl_Athlete)
{
	if( m_pData->isA()!=__CHMATCH )
		return;

	CHMatch * pMatch=(CHMatch*)m_pData;

	CHMatchResult * pMR = 0;
	
	//Doubles
	if( pAthlete->isA()==__CHMATCHRESULT )
	{
		pMR = (CHMatchResult *)pAthlete;

		pEl_Athlete->setAttribute("Code",pMR->getAcreditation());
		pEl_Athlete->setAttribute("Order", m_memberOrder++);

		return;
	}

	ODF2THZZResults::fillSportAthlete(pAthlete,pEl_Athlete);
}


void CHODF2Results::fillEventUnitEntry(MSLItem * pCompetitor,XMLElement * pEl_Competitor)
{
	CHMatchResult * pMR=0;
	if(pCompetitor->isA()==__CHMATCHRESULT)
		pMR=(CHMatchResult*)pCompetitor;

	if (!pMR)
		return;

	addExtension("","EventUnitEntry", pEl_Competitor, EUE, COLOR , 0, CHODFMODEL->getColor(pMR));	
}

//Results
void CHODF2Results::fillVectorResults(MSLArray& vResults,MSLItem * pData/*=0*/)
{
	if( m_pData->isA()!=__CHMATCH )
		return;

	CHMatch * pMatch=(CHMatch*)m_pData;
	if( !pMatch )
		return;

	MSLSortedVector vMatchResults;
	
	CHMatchResult * pHome = (CHMatchResult * ) pMatch->getHome();
	if (pHome && isSelectable(pHome,eCompetitor) )
	{
		m_vCompetitors.insert(pHome);
		vResults.insert(pHome);
	}
	CHMatchResult * pAway = (CHMatchResult * ) pMatch->getAway();
	if (pAway && isSelectable(pAway,eCompetitor) )
	{
		m_vCompetitors.insert(pAway);
		vResults.insert(pAway);			
	}
}

bool CHODF2Results::isSelectable(GData * pData, ODF2THZZResults::TypeSelection selection)
{
	if (pData->isA()==__GTHMATCHRESULT && selection==eCompetitor)
	{
		return ((GTHMatchResult*)pData)->getRegister()!=0 || ((GTHMatchResult*)pData)->getBye();
	}

	return ODF2THZZResults::isSelectable(pData, selection);
}

void CHODF2Results::fillSportResult(MSLItem * pResult,XMLElement * pEl_Result)
{
	if( !pResult || !pEl_Result )
		return;

	CHMatchResult * pMR = (CHMatchResult *)pResult;
	if (!pMR)
		return;

	CHMatchResult* pOpp = (CHMatchResult*) pMR->getOpponent();

	CHMatch* pMatch = (CHMatch*)pMR->getMatch();
	if (!pMatch)
		return;

	if (pMR->getQualitativeCode()==OK)
	{		
		bool paintRank = ( pMatch && pMatch->getStatus()==CHMemoryDataBase::eFinished);

		if (paintRank && pMR->getRank())
		{
			pEl_Result->setAttribute("Rank",pMR->getRank());			
			
			if (pMR->isRankEqual())
				pEl_Result->setAttribute("RankEqual","Y");
			else
				pEl_Result->setAttribute("RankEqual","N");

			pEl_Result->setAttribute("ResultType","POINTS");
		}				
	}
	else
	{
		pEl_Result->setAttribute("IRM", pMR->getQualitativeSDescription("ENG"));
		pEl_Result->setAttribute("ResultType","IRM");
	}
	

	if	(pMatch && 
		(pMatch->getStatus()==CHMemoryDataBase::eUnofficial ||
		 pMatch->getStatus()==CHMemoryDataBase::eFinished ) )
	{
		MSLString wlt = NULLSTRING;
		if ( pMR->getRank()==1 && pOpp && pOpp->getRank()==1 )
			wlt = "T";
		else if (pMR->getRank()==1)
			wlt = "W";
		else if (pMR->getRank()==2 || pMR->getBye() )
			wlt = "L"; 

		if (wlt.length())
			pEl_Result->setAttribute("WLT", wlt);

		pEl_Result->setAttribute("Result", pMR->getPointsAsString());
	}

	if (pMR->getType()==CHMatchResult::eHome)
	{
		pEl_Result->setAttribute("SortOrder",1);
		pEl_Result->setAttribute("StartOrder",1);
	}
	else
	{
		pEl_Result->setAttribute("SortOrder",2);
		pEl_Result->setAttribute("StartOrder",2);	
	}
		
	pEl_Result->setAttribute("StartSortOrder", getStartSortOrder(pMR));	
}

short CHODF2Results::getStartSortOrder(CHMatchResult *pMR)
{
	if (pMR->getColor()==CHMatchResult::eWhite)
		return 1;

	return 2;
}


void CHODF2Results::fillVectorComposition(MSLItem * pCompetitor,MSLArray& vComposition)
{
	if( !pCompetitor )
		return;

	CHMatchResult * pMR = (CHMatchResult *)pCompetitor;
	if (!pMR)
		return;

	CHEvent* pEvent=(CHEvent*) pMR->getEvent();
	if (!pEvent)
		return;

	if(pEvent->getRegType()==GRegister::individual)
		vComposition.insert(pMR);
	else 
	{
		MSLSortedVector vMembers;
		CHODFMODEL->fillMembers(pMR,vMembers);
		for(short i=0 ; i<vMembers.entries() ; i++ )
		{
			GData* pData = (GData*) vMembers[i];
			vComposition.insert(pData);
		}
		m_memberOrder=1;
	}	
}

