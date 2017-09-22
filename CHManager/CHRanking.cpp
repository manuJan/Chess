/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHRanking.h
*   Description : 
*
*   Author      : Javier Juste
*   Date created: 22-FEb-2009
*   Project     : AR Manager
*
*   Modification history
*   By      :
*   Date    :
*   Changes :
*
*****************************************************************************************/

#include "StdAfx.h"
#include "CHRanking.h"
#include "CHManagerApp.h"
#include "..\CHMngtModel\CHEvent.h"
#include "..\CHMngtModel\CHPoolResult.h"
#include "..\CHMngtModel\CHEventResult.h"
#include "..\CHMngtModel\CHPhase.h"
#include "..\CHMngtModel\CHPool.h"
#include "..\CHMngtModel\CHMatch.h"
#include "..\CHMngtModel\CHInscription.h"
#include "..\CHMngtModel\CHStatisticDefines.h"

#include <ovr\core\th\gthmsgdefines.h>
#include <OVR\core\G\GScore.h>

static
bool poolResultsRanked(const MSLItem* p,const void *n)
{
	CHPoolResult* pPoolResult = (CHPoolResult *)p;	
	if (!pPoolResult)
		return false;

	//if (!pPoolResult->getRegister())
	//	return false;

	if (pPoolResult->getMatchesPlayed())
		return true;

	return false;
	UNREFERENCED_PARAMETER(n);
}

static
bool phaseResultsRanked(const MSLItem* p,const void *n)
{
	CHPoolResult* pPoolResult = (CHPoolResult *)p;	
	if (!pPoolResult)
		return false;

	if (!pPoolResult->getRegister())
		return false;

	if ( pPoolResult->getRank())
		 return true;

	return false;
	UNREFERENCED_PARAMETER(n);
}

static
bool validEventResults(const MSLItem* p,const void *n)
{
	CHEventResult* pEventResult = (CHEventResult *)p;	
	if (!pEventResult)
		return false;
		
	CHPoolResult* pPoolResult = pEventResult->getPoolResult();
	if (!pPoolResult)
		return false;

	return true;
	UNREFERENCED_PARAMETER(n);
}

static int orderPoints(GScore a, GScore b)
{
	float gA = float(a);
	float gB = float(b);

	float diff = gB-gA;
	if (diff<0)
		return -1;
	if (diff>0)
		return 1;

	return 0;	
}

static
int orderMatchResultsByPosition(CHMatchResult* pA, CHMatchResult* pB)
{
	int order=0;
	order = pA->getPosition()-pB->getPosition();
	if (order)
		return order;

	return strcmp(pA->getKey(),pB->getKey());
}

static
int orderMatchResultByPoints(CHMatchResult* pA, CHMatchResult* pB)
{
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
		return orderMatchResultsByPosition(pA,pB);
		
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

	GScore pointsA=pA->getPoints();
	GScore pointsB=pB->getPoints();
	
	int order = orderPoints(pointsA,pointsB);
	if (order)
		return order;

	return 0;
}

static
int orderEventResults(const MSLItem** a,const MSLItem** b)
{
	CHEventResult * pA=((CHEventResult *)(*a));
	CHEventResult * pB=((CHEventResult *)(*b));
	
	if (pA->getQualitativeCode()!=OK && 
		pB->getQualitativeCode()!=OK)
	{
		GQualitative * pQA = pA->getQualitative();
		GQualitative * pQB = pB->getQualitative();
		if (pQA && pQB)
			return pQA->getSort() - pQB->getSort();

		return strcmp(pA->getKey(),pB->getKey());
	}

	if (pA->getQualitativeCode()!=OK)
		return 1;

	if (pB->getQualitativeCode()!=OK)
		return -1;

	CHPoolResult * pPA = pA->getPoolResult();
	CHPoolResult * pPB = pB->getPoolResult();

	if (!pPA && !pPB)
		return strcmp(pA->getKey(),pB->getKey());
		
	if (!pPA)
		return 1;

	if (!pPB)
		return -1;

	// Orden de fase
	int order = pPB->getPhaseOrder() - pPA->getPhaseOrder();
	if (order)
		return order;

	if (pPA->getPhaseRank() && pPB->getPhaseRank())
	{
		int order=(pPA->getPhaseRank() - pPB->getPhaseRank()); 
		if (order)
			return order;
	}
	if (!pPA->getPhaseRank())
		return 1;

	if (!pPB->getPhaseRank())
		return -1;

	return strcmp(pA->getKey(),pB->getKey());
}

static
int compEventResults(const MSLItem** a,const MSLItem** b)
{
	CHEventResult * pA=((CHEventResult *)(*a));
	CHEventResult * pB=((CHEventResult *)(*b));
		
if (pA->getQualitativeCode()!=OK && 
		pB->getQualitativeCode()!=OK)
	{
		GQualitative * pQA = pA->getQualitative();
		GQualitative * pQB = pB->getQualitative();
		if (pQA && pQB)
			return pQA->getSort() - pQB->getSort();

		return strcmp(pA->getKey(),pB->getKey());
	}

	if (pA->getQualitativeCode()!=OK)
		return 1;

	if (pB->getQualitativeCode()!=OK)
		return -1;

	CHPoolResult * pPA = pA->getPoolResult();
	CHPoolResult * pPB = pB->getPoolResult();

	if (!pPA && !pPB)
		return strcmp(pA->getKey(),pB->getKey());
		
	if (!pPA)
		return 1;

	if (!pPB)
		return -1;

	// Orden de fase
	int order = pPB->getPhaseOrder() - pPA->getPhaseOrder();
	if (order)
		return order;

	if (pPA->getPhaseRank() && pPB->getPhaseRank())
	{
		int order=(pPA->getPhaseRank() - pPB->getPhaseRank()); 
		if (order)
			return order;
	}
	if (!pPA->getPhaseRank())
		return 1;

	if (!pPB->getPhaseRank())
		return -1;

	return 0;
}

static
int orderMatchResultByPoints(const MSLItem** a,const MSLItem** b)
{
	CHMatchResult * pA=((CHMatchResult *)(*a));
	CHMatchResult * pB=((CHMatchResult *)(*b));
	
	if (pA->getQualitativeCode()==DSQ && 
		pB->getQualitativeCode()==DSQ)
		return strcmp(pA->getKey(),pB->getKey());

	if (pA->getQualitativeCode()==FO && 
		pB->getQualitativeCode()==FO)
		return strcmp(pA->getKey(),pB->getKey());

	if (pA->getQualitativeCode()==DSQ ||
		pB->getQualitativeCode()==RET)
		return 1;

	if (pB->getQualitativeCode()==DSQ ||
		pA->getQualitativeCode()==RET)
		return -1;
	
	GScore pointsA=pA->getPoints();
	GScore pointsB=pB->getPoints();
	
	int order = orderPoints(pointsA,pointsB);
	if (order)
		return order;

	return strcmp(pA->getKey(),pB->getKey());
}

static
int orderMatchResultByTeamPointsEliminatory(const MSLItem** a,const MSLItem** b)
{
	CHMatchResult * pA=((CHMatchResult *)(*a));
	CHMatchResult * pB=((CHMatchResult *)(*b));
	
	if (pA->getQualitativeCode()==DSQ && 
		pB->getQualitativeCode()==DSQ)
		return strcmp(pA->getKey(),pB->getKey());

	if (pA->getQualitativeCode()==FO && 
		pB->getQualitativeCode()==FO)
		return strcmp(pA->getKey(),pB->getKey());

	if (pA->getQualitativeCode()==DSQ ||
		pB->getQualitativeCode()==RET)
		return 1;

	if (pB->getQualitativeCode()==DSQ ||
		pA->getQualitativeCode()==RET)
		return -1;
	
	GScore pointsA=pA->getPoints();
	GScore pointsB=pB->getPoints();
	
	int order = orderPoints(pointsA,pointsB);
	if (order)
		return order;

	// Miro el primer submatch  
	CHMatch* pMatch  = (CHMatch*)pA->getMatch();
	if (pMatch && !pMatch->getSubMatch())
	{
		MSLSortedVector vSubMatches;
		pMatch->getSubMatchesVector(vSubMatches);
		if (vSubMatches.entries())
		{
			CHMatch * pSubMatch = (CHMatch*) vSubMatches[0];
			if (pSubMatch)
			{
				CHMatchResult * pWhite = (CHMatchResult*) pSubMatch->getWhite();
				CHMatchResult * pBlack = (CHMatchResult*) pSubMatch->getBlack();

				GScore pointsA=pWhite->getPoints();
				GScore pointsB=pBlack->getPoints();

				if ( pWhite->getInscription() == pA->getInscription() &&
				     pBlack->getInscription() == pB->getInscription() )
				{
					int order = orderPoints(pointsA,pointsB);
					if (order)
						 return order;
				}
				if (pWhite->getInscription() == pB->getInscription() &&
				    pBlack->getInscription() == pA->getInscription() )
				{
					int order = orderPoints(pointsB,pointsA);
					if (order)
						 return order;
				}
			}
		}
	}

	return strcmp(pA->getKey(),pB->getKey());
}

int compMatchResultByPoints(const MSLItem** a,const MSLItem** b)
{
	CHMatchResult * pA=((CHMatchResult *)(*a));
	CHMatchResult * pB=((CHMatchResult *)(*b));
	
	if (pA->getQualitativeCode()==DSQ && 
		pB->getQualitativeCode()==DSQ)
		return strcmp(pA->getKey(),pB->getKey());

	if (pA->getQualitativeCode()==FO && 
		pB->getQualitativeCode()==FO)
		return strcmp(pA->getKey(),pB->getKey());

	if (pA->getQualitativeCode()==DSQ ||
		pB->getQualitativeCode()==RET)
		return 1;

	if (pB->getQualitativeCode()==DSQ ||
		pA->getQualitativeCode()==RET)
		return -1;
	
	GScore pointsA=pA->getPoints();
	GScore pointsB=pB->getPoints();
	
	int order = orderPoints(pointsA,pointsB);
	if (order)
		return order;

	return 0;
}

static
int compMatchResultByTeamPointsEliminatory(const MSLItem** a,const MSLItem** b)
{
	CHMatchResult * pA=((CHMatchResult *)(*a));
	CHMatchResult * pB=((CHMatchResult *)(*b));
	
	if (pA->getQualitativeCode()==DSQ && 
		pB->getQualitativeCode()==DSQ)
		return strcmp(pA->getKey(),pB->getKey());

	if (pA->getQualitativeCode()==FO && 
		pB->getQualitativeCode()==FO)
		return strcmp(pA->getKey(),pB->getKey());

	if (pA->getQualitativeCode()==DSQ ||
		pB->getQualitativeCode()==RET)
		return 1;

	if (pB->getQualitativeCode()==DSQ ||
		pA->getQualitativeCode()==RET)
		return -1;
	
	GScore pointsA=pA->getPoints();
	GScore pointsB=pB->getPoints();
	
	int order = orderPoints(pointsA,pointsB);
	if (order)
		return order;

	// Miro el primer submatch  
	CHMatch* pMatch  = (CHMatch*)pA->getMatch();
	if (pMatch && !pMatch->getSubMatch())
	{
		MSLSortedVector vSubMatches;
		pMatch->getSubMatchesVector(vSubMatches);
		if (vSubMatches.entries())
		{
			CHMatch * pSubMatch = (CHMatch*) vSubMatches[0];
			if (pSubMatch)
			{
				CHMatchResult * pWhite = (CHMatchResult*) pSubMatch->getWhite();
				CHMatchResult * pBlack = (CHMatchResult*) pSubMatch->getBlack();

				GScore pointsA=pWhite->getPoints();
				GScore pointsB=pBlack->getPoints();

				if ( pWhite->getInscription() == pA->getInscription() &&
				     pBlack->getInscription() == pB->getInscription() )
				{
					int order = orderPoints(pointsA,pointsB);
					if (order)
						 return order;
				}
				if (pWhite->getInscription() == pB->getInscription() &&
				    pBlack->getInscription() == pA->getInscription() )
				{
					int order = orderPoints(pointsB,pointsA);
					if (order)
						 return order;
				}
			}
		}
	}

	return 0;
}

static
int orderPoolResults(const MSLItem** a,const MSLItem** b)
{
	CHPoolResult * pA=((CHPoolResult *)(*a));
	CHPoolResult * pB=((CHPoolResult *)(*b));

	if (pA->getRegister() && !pB->getRegister())
		return -1;
	if (!pA->getRegister() && pB->getRegister())
		return 1;
	
	CHEvent *pEvent=(CHEvent*)pA->getEvent();

	for(short i=0;i<pEvent->getNumRankOrder();i++)
	{
		CHEvent::TypeRank typeRnk=pEvent->getRankOrder(i);
		switch(typeRnk)
		{
			case CHEvent::eQualitative:
			{
				// Qualitative
				if (pA->getQualitativeCode()!=OK && 
					pB->getQualitativeCode()!=OK)
				{
					GQualitative * pQA = pA->getQualitative();
					GQualitative * pQB = pB->getQualitative();
					if (pQA && pQB)
						return pQA->getSort() - pQB->getSort();
				}
				
				if (pA->getQualitativeCode()==DSQ)
					return 1;
				if (pA->getQualitativeCode()==RET)
					return 1;
				if (pA->getQualitativeCode()==FO)
					return 1;
				if (pB->getQualitativeCode()==DSQ)
					return -1;		
				if (pB->getQualitativeCode()==RET)
					return -1;		
				if (pB->getQualitativeCode()==FO)
					return -1;
				break;
			}
			case CHEvent::ePoints:
			{		
				GScore pointsA=pA->getPointsF();
				GScore pointsB=pB->getPointsF();
	
				int order = orderPoints(pointsA,pointsB);
				if (order)
					return order;
				break;
			}			
			case CHEvent::eMatchPoints:
			{		
				GScore pointsA=pA->getMatchPoints();
				GScore pointsB=pB->getMatchPoints();
	
				int order = orderPoints(pointsA,pointsB);
				if (order)
					return order;
				break;
			}
			case CHEvent::eMatchesWon:
			{
				CHPoolResult * pOrigPoolResA = (CHPoolResult *)CHMemoryDataBase::find(*pA);
				CHPoolResult * pOrigPoolResB = (CHPoolResult *)CHMemoryDataBase::find(*pB);

				int order = pOrigPoolResB->getMatchesWon() - pOrigPoolResA->getMatchesWon();
				if (order)
					return order;

				break;
			}
			case CHEvent::eTeamPointsWon:
			{
				CHPoolResult * pOrigPoolResA = (CHPoolResult *)CHMemoryDataBase::find(*pA);
				CHPoolResult * pOrigPoolResB = (CHPoolResult *)CHMemoryDataBase::find(*pB);

				int order = pOrigPoolResA->getAllRoundsPointsForWon() - pOrigPoolResB->getAllRoundsPointsForWon();
				if (order)
					return order;

				break;
			}
			case CHEvent::eAvgOppRating:
			{
				CHPoolResult * pOrigPoolResA = (CHPoolResult *)CHMemoryDataBase::find(*pA);
				CHPoolResult * pOrigPoolResB = (CHPoolResult *)CHMemoryDataBase::find(*pB);

				GScore pointsA = pOrigPoolResA->getOppAverageRating();
				GScore pointsB = pOrigPoolResB->getOppAverageRating();

				int order = orderPoints(pointsA,pointsB);
				if (order)
					return order;
				break;
			}
			case CHEvent::eRating:
			{
				CHPoolResult * pOrigPoolResA = (CHPoolResult *)CHMemoryDataBase::find(*pA);
				CHPoolResult * pOrigPoolResB = (CHPoolResult *)CHMemoryDataBase::find(*pB);

				int pointsA = pOrigPoolResA->getInscriptionRating();
				int pointsB = pOrigPoolResB->getInscriptionRating();

				int order=pointsB - pointsA;
				if(order)
					return order;

				break;
			}
			case CHEvent::eSolkoff:
			{
				CHPoolResult * pOrigPoolResA = (CHPoolResult *)CHMemoryDataBase::find(*pA);
				CHPoolResult * pOrigPoolResB = (CHPoolResult *)CHMemoryDataBase::find(*pB);

				GScore pointsA = pOrigPoolResA->getSolkOffF();
				GScore pointsB = pOrigPoolResB->getSolkOffF();

				int order = orderPoints(pointsA,pointsB);
				if (order)
					return order;
				break;			
			}
			case CHEvent::eSolkoffCutLowestAndHighest:
			{
				CHPoolResult * pOrigPoolResA = (CHPoolResult *)CHMemoryDataBase::find(*pA);
				CHPoolResult * pOrigPoolResB = (CHPoolResult *)CHMemoryDataBase::find(*pB);

				GScore pointsA = pOrigPoolResA->getMedianSolkOffF(0,1,1);
				GScore pointsB = pOrigPoolResB->getMedianSolkOffF(0,1,1);

				int order = orderPoints(pointsA,pointsB);
				if (order)
					return order;
				break;			
			}
			case CHEvent::eSolkoffCutLowest:
			{
				CHPoolResult * pOrigPoolResA = (CHPoolResult *)CHMemoryDataBase::find(*pA);
				CHPoolResult * pOrigPoolResB = (CHPoolResult *)CHMemoryDataBase::find(*pB);

				GScore pointsA = pOrigPoolResA->getMedianSolkOffF(0,0,1);
				GScore pointsB = pOrigPoolResB->getMedianSolkOffF(0,0,1);

				int order = orderPoints(pointsA,pointsB);
				if (order)
					return order;
				break;			
			}
			case CHEvent::eSonneBerger:
			{
				CHPoolResult * pOrigPoolResA = (CHPoolResult *)CHMemoryDataBase::find(*pA);
				CHPoolResult * pOrigPoolResB = (CHPoolResult *)CHMemoryDataBase::find(*pB);

				GScore pointsA = pOrigPoolResA->getSonneBergerF();
				GScore pointsB = pOrigPoolResB->getSonneBergerF();

				int order = orderPoints(pointsA,pointsB);
				if (order)
					return order;

				break;
			}
		}
	}

	return strcmp(pA->getKey(),pB->getKey());
}

static
int orderPoolResultsByTeamPointsEliminatory(const MSLItem** a,const MSLItem** b)
{
	CHPoolResult * pA=((CHPoolResult *)(*a));
	CHPoolResult * pB=((CHPoolResult *)(*b));
	
	// Qualitative
	if (pA->getQualitativeCode()!=OK && 
		pB->getQualitativeCode()!=OK)
	{
		GQualitative * pQA = pA->getQualitative();
		GQualitative * pQB = pB->getQualitative();
		if (pQA && pQB)
			return pQA->getSort() - pQB->getSort();
	}
				
	if (pA->getQualitativeCode()==DSQ)
		return 1;
	if (pA->getQualitativeCode()==RET)
		return 1;
	if (pA->getQualitativeCode()==FO)
		return 1;
	if (pB->getQualitativeCode()==DSQ)
		return -1;		
	if (pB->getQualitativeCode()==RET)
		return -1;		
	if (pB->getQualitativeCode()==FO)
		return -1;
	
	GScore pointsA=pA->getPointsF();
	GScore pointsB=pB->getPointsF();
	
	int order = orderPoints(pointsA,pointsB);
	if (order)
		return order;
				
	// Miro el ranking del matchResult ya calculado
	MSLSortedVector vMatchResultsA;
	pA->getMatchResultsVector(vMatchResultsA);
	CHMatchResult * pMatchResultA = (CHMatchResult * ) vMatchResultsA[0];

	MSLSortedVector vMatchResultsB;
	pB->getMatchResultsVector(vMatchResultsB);
	CHMatchResult * pMatchResultB = (CHMatchResult * ) vMatchResultsB[0];

	if (pMatchResultA && pMatchResultB)
	{
		if (pMatchResultA->getQualitativeCode()==FO && 
			pMatchResultB->getQualitativeCode()==FO)
			return strcmp(pMatchResultA->getKey(),pMatchResultB->getKey());

		if (pMatchResultA->getQualitativeCode()==FO)
			return 1;

		if (pMatchResultB->getQualitativeCode()==FO)
			return -1;
			
		if (pMatchResultA->getRankPo()==0)
			return 1;

		if (pMatchResultB->getRankPo()==0)
			return -1;

		int rank=pMatchResultA->getRankPo() - pMatchResultB->getRankPo();
		if(rank)
			return rank;
	}

	return strcmp(pA->getKey(),pB->getKey());
}

static
int orderPoolResults2Ties(const MSLItem** a,const MSLItem** b)
{
	CHPoolResult * pA=((CHPoolResult *)(*a));
	CHPoolResult * pB=((CHPoolResult *)(*b));
	
	if (pA->getRegister() && !pB->getRegister())
		return -1;
	if (!pA->getRegister() && pB->getRegister())
		return 1;

	CHEvent *pEvent=(CHEvent*)pA->getEvent();

	for(short i=0;i<pEvent->getNumRankOrder();i++)
	{
		CHEvent::TypeRank typeRnk=pEvent->getRankOrder(i);
		switch(typeRnk)
		{
			case CHEvent::eQualitative:
			{
				// Qualitative
				if (pA->getQualitativeCode()!=OK && 
					pB->getQualitativeCode()!=OK)
				{
					GQualitative * pQA = pA->getQualitative();
					GQualitative * pQB = pB->getQualitative();
					if (pQA && pQB)
						return pQA->getSort() - pQB->getSort();
				}
				
				if (pA->getQualitativeCode()==DSQ)
					return 1;
				if (pA->getQualitativeCode()==RET)
					return 1;
				if (pA->getQualitativeCode()==FO)
					return 1;
				if (pB->getQualitativeCode()==DSQ)
					return -1;		
				if (pB->getQualitativeCode()==RET)
					return -1;		
				if (pB->getQualitativeCode()==FO)
					return -1;
				break;
			}
			case CHEvent::ePoints:
			{		
				CHPoolResult * pOrigPoolResA = (CHPoolResult *)CHMemoryDataBase::find(*pA);
				CHPoolResult * pOrigPoolResB = (CHPoolResult *)CHMemoryDataBase::find(*pB);

				GScore pointsA=pOrigPoolResA->getPointsF();
				GScore pointsB=pOrigPoolResB->getPointsF();
	
				int order = orderPoints(pointsA,pointsB);
				if (order)
					return order;
				break;
			}			
			case CHEvent::eMatchPoints:
			{		
				GScore pointsA=pA->getMatchPoints();
				GScore pointsB=pB->getMatchPoints();
	
				int order = orderPoints(pointsA,pointsB);
				if (order)
					return order;
				break;
			}
			case CHEvent::eDirectEncounter:
			{
				CHPoolResult * pOrigPoolResA = (CHPoolResult *)CHMemoryDataBase::find(*pA);
				CHPoolResult * pOrigPoolResB = (CHPoolResult *)CHMemoryDataBase::find(*pB);

				// Busco el partido que les enfrentó
				CHPool * pPool = (CHPool * ) pA->getPool();
				CHMatch * pMatch = pPool->findMatch(pOrigPoolResA, pOrigPoolResB);
				if (pMatch)
				{
					CHMatchResult * pMR1 = pMatch->getWhite();
					CHMatchResult * pMR2 = pMatch->getBlack();

					if (pMR1->getPoolResult() == pA &&
						pMR2->getPoolResult() == pB )
					{
						int order = orderMatchResultByPoints(pMR1, pMR2);
						if (order)
							return order;
					}
					else if (pMR1->getPoolResult() == pB &&
						 	 pMR2->getPoolResult() == pA )
					{
						int order = orderMatchResultByPoints(pMR2, pMR1);
						if (order)
							return order;
					}
				}
			
				break;
			}
			case CHEvent::eMatchesWon:
			{
				CHPoolResult * pOrigPoolResA = (CHPoolResult *)CHMemoryDataBase::find(*pA);
				CHPoolResult * pOrigPoolResB = (CHPoolResult *)CHMemoryDataBase::find(*pB);

				int order = pOrigPoolResB->getMatchesWon() - pOrigPoolResA->getMatchesWon();
				if (order)
					return order;

				break;
			}
			case CHEvent::eTeamPointsWon:
			{
				CHPoolResult * pOrigPoolResA = (CHPoolResult *)CHMemoryDataBase::find(*pA);
				CHPoolResult * pOrigPoolResB = (CHPoolResult *)CHMemoryDataBase::find(*pB);

				int order = pOrigPoolResA->getAllRoundsPointsForWon() - pOrigPoolResB->getAllRoundsPointsForWon();
				if (order)
					return order;

				break;
			}
			case CHEvent::eAvgOppRating:
			{
				CHPoolResult * pOrigPoolResA = (CHPoolResult *)CHMemoryDataBase::find(*pA);
				CHPoolResult * pOrigPoolResB = (CHPoolResult *)CHMemoryDataBase::find(*pB);

				GScore pointsA = pOrigPoolResA->getOppAverageRating();
				GScore pointsB = pOrigPoolResB->getOppAverageRating();

				int order = orderPoints(pointsA,pointsB);
				if (order)
					return order;
				break;
			}
			case CHEvent::eRating:
			{
				CHPoolResult * pOrigPoolResA = (CHPoolResult *)CHMemoryDataBase::find(*pA);
				CHPoolResult * pOrigPoolResB = (CHPoolResult *)CHMemoryDataBase::find(*pB);

				int pointsA = pOrigPoolResA->getInscriptionRating();
				int pointsB = pOrigPoolResB->getInscriptionRating();

				int order=pointsB - pointsA;
				if(order)
					return order;

				break;
			}
			case CHEvent::eSolkoff:
			{
				CHPoolResult * pOrigPoolResA = (CHPoolResult *)CHMemoryDataBase::find(*pA);
				CHPoolResult * pOrigPoolResB = (CHPoolResult *)CHMemoryDataBase::find(*pB);

				GScore pointsA = pOrigPoolResA->getSolkOffF();
				GScore pointsB = pOrigPoolResB->getSolkOffF();

				int order = orderPoints(pointsA,pointsB);
				if (order)
					return order;
				break;			
			}
			case CHEvent::eSolkoffCutLowestAndHighest:
			{
				CHPoolResult * pOrigPoolResA = (CHPoolResult *)CHMemoryDataBase::find(*pA);
				CHPoolResult * pOrigPoolResB = (CHPoolResult *)CHMemoryDataBase::find(*pB);

				GScore pointsA = pOrigPoolResA->getMedianSolkOffF(0,1,1);
				GScore pointsB = pOrigPoolResB->getMedianSolkOffF(0,1,1);

				int order = orderPoints(pointsA,pointsB);
				if (order)
					return order;
				break;			
			}
			case CHEvent::eSolkoffCutLowest:
			{
				CHPoolResult * pOrigPoolResA = (CHPoolResult *)CHMemoryDataBase::find(*pA);
				CHPoolResult * pOrigPoolResB = (CHPoolResult *)CHMemoryDataBase::find(*pB);

				GScore pointsA = pOrigPoolResA->getMedianSolkOffF(0,0,1);
				GScore pointsB = pOrigPoolResB->getMedianSolkOffF(0,0,1);

				int order = orderPoints(pointsA,pointsB);
				if (order)
					return order;
				break;			
			}
			case CHEvent::eSonneBerger:
			{
				CHPoolResult * pOrigPoolResA = (CHPoolResult *)CHMemoryDataBase::find(*pA);
				CHPoolResult * pOrigPoolResB = (CHPoolResult *)CHMemoryDataBase::find(*pB);

				GScore pointsA = pOrigPoolResA->getSonneBergerF();
				GScore pointsB = pOrigPoolResB->getSonneBergerF();

				int order = orderPoints(pointsA,pointsB);
				if (order)
					return order;

				break;
			}
		}
	}

	return strcmp(pA->getKey(),pB->getKey());
}

static
int compPoolResults(const MSLItem** a,const MSLItem** b)
{
	CHPoolResult * pA=((CHPoolResult *)(*a));
	CHPoolResult * pB=((CHPoolResult *)(*b));
	
	if (pA->getRegister() && !pB->getRegister())
		return -1;
	if (!pA->getRegister() && pB->getRegister())
		return 1;

	CHEvent *pEvent=(CHEvent*)pA->getEvent();

	for(short i=0;i<pEvent->getNumRankOrder();i++)
	{
		CHEvent::TypeRank typeRnk=pEvent->getRankOrder(i);
		switch(typeRnk)
		{
			case CHEvent::eQualitative:
			{
				// Qualitative
				if (pA->getQualitativeCode()!=OK && 
					pB->getQualitativeCode()!=OK)
				{
					GQualitative * pQA = pA->getQualitative();
					GQualitative * pQB = pB->getQualitative();
					if (pQA && pQB)
						return pQA->getSort() - pQB->getSort();
				}
				
				if (pA->getQualitativeCode()==DSQ)
					return 1;
				if (pA->getQualitativeCode()==RET)
					return 1;
				if (pA->getQualitativeCode()==FO)
					return 1;
				if (pB->getQualitativeCode()==DSQ)
					return -1;		
				if (pB->getQualitativeCode()==RET)
					return -1;		
				if (pB->getQualitativeCode()==FO)
					return -1;
				break;
			}
			case CHEvent::ePoints:
			{		
				GScore pointsA=pA->getPointsF();
				GScore pointsB=pB->getPointsF();
	
				int order = orderPoints(pointsA,pointsB);
				if (order)
					return order;
				break;
			}			
			case CHEvent::eMatchPoints:
			{		
				GScore pointsA=pA->getMatchPoints();
				GScore pointsB=pB->getMatchPoints();
	
				int order = orderPoints(pointsA,pointsB);
				if (order)
					return order;
				break;
			}
			case CHEvent::eTeamPointsWon:
			{
				CHPoolResult * pOrigPoolResA = (CHPoolResult *)CHMemoryDataBase::find(*pA);
				CHPoolResult * pOrigPoolResB = (CHPoolResult *)CHMemoryDataBase::find(*pB);

				int order = pOrigPoolResA->getAllRoundsPointsForWon() - pOrigPoolResB->getAllRoundsPointsForWon();
				if (order)
					return order;

				break;
			}
			case CHEvent::eMatchesWon:
			{
				CHPoolResult * pOrigPoolResA = (CHPoolResult *)CHMemoryDataBase::find(*pA);
				CHPoolResult * pOrigPoolResB = (CHPoolResult *)CHMemoryDataBase::find(*pB);

				int order = pOrigPoolResB->getMatchesWon() - pOrigPoolResA->getMatchesWon();
				if (order)
					return order;

				break;
			}
			case CHEvent::eAvgOppRating:
			{
				CHPoolResult * pOrigPoolResA = (CHPoolResult *)CHMemoryDataBase::find(*pA);
				CHPoolResult * pOrigPoolResB = (CHPoolResult *)CHMemoryDataBase::find(*pB);

				GScore pointsA = pOrigPoolResA->getOppAverageRating();
				GScore pointsB = pOrigPoolResB->getOppAverageRating();

				int order = orderPoints(pointsA,pointsB);
				if (order)
					return order;
				break;
			}
			case CHEvent::eRating:
			{
				CHPoolResult * pOrigPoolResA = (CHPoolResult *)CHMemoryDataBase::find(*pA);
				CHPoolResult * pOrigPoolResB = (CHPoolResult *)CHMemoryDataBase::find(*pB);

				int pointsA = pOrigPoolResA->getInscriptionRating();
				int pointsB = pOrigPoolResB->getInscriptionRating();

				int order=pointsB - pointsA;
				if(order)
					return order;

				break;
			}
			case CHEvent::eSolkoff:
			{
				CHPoolResult * pOrigPoolResA = (CHPoolResult *)CHMemoryDataBase::find(*pA);
				CHPoolResult * pOrigPoolResB = (CHPoolResult *)CHMemoryDataBase::find(*pB);

				GScore pointsA = pOrigPoolResA->getSolkOffF();
				GScore pointsB = pOrigPoolResB->getSolkOffF();

				int order = orderPoints(pointsA,pointsB);
				if (order)
					return order;
				break;			
			}
			case CHEvent::eSolkoffCutLowestAndHighest:
			{
				CHPoolResult * pOrigPoolResA = (CHPoolResult *)CHMemoryDataBase::find(*pA);
				CHPoolResult * pOrigPoolResB = (CHPoolResult *)CHMemoryDataBase::find(*pB);

				GScore pointsA = pOrigPoolResA->getMedianSolkOffF(0,1,1);
				GScore pointsB = pOrigPoolResB->getMedianSolkOffF(0,1,1);

				int order = orderPoints(pointsA,pointsB);
				if (order)
					return order;
				break;			
			}
			case CHEvent::eSolkoffCutLowest:
			{
				CHPoolResult * pOrigPoolResA = (CHPoolResult *)CHMemoryDataBase::find(*pA);
				CHPoolResult * pOrigPoolResB = (CHPoolResult *)CHMemoryDataBase::find(*pB);

				GScore pointsA = pOrigPoolResA->getMedianSolkOffF(0,0,1);
				GScore pointsB = pOrigPoolResB->getMedianSolkOffF(0,0,1);

				int order = orderPoints(pointsA,pointsB);
				if (order)
					return order;
				break;			
			}
			case CHEvent::eSonneBerger:
			{
				CHPoolResult * pOrigPoolResA = (CHPoolResult *)CHMemoryDataBase::find(*pA);
				CHPoolResult * pOrigPoolResB = (CHPoolResult *)CHMemoryDataBase::find(*pB);

				GScore pointsA = pOrigPoolResA->getSonneBergerF();
				GScore pointsB = pOrigPoolResB->getSonneBergerF();

				int order = orderPoints(pointsA,pointsB);
				if (order)
					return order;

				break;
			}
		}
	}
	
	return 0;
}

static
	
int compPoolResultsByTeamPointsEliminatory(const MSLItem** a,const MSLItem** b)
{
	CHPoolResult * pA=((CHPoolResult *)(*a));
	CHPoolResult * pB=((CHPoolResult *)(*b));
	
	// Qualitative
	if (pA->getQualitativeCode()!=OK && 
		pB->getQualitativeCode()!=OK)
	{
		GQualitative * pQA = pA->getQualitative();
		GQualitative * pQB = pB->getQualitative();
		if (pQA && pQB)
			return pQA->getSort() - pQB->getSort();
	}
				
	if (pA->getQualitativeCode()==DSQ)
		return 1;
	if (pA->getQualitativeCode()==RET)
		return 1;
	if (pA->getQualitativeCode()==FO)
		return 1;
	if (pB->getQualitativeCode()==DSQ)
		return -1;		
	if (pB->getQualitativeCode()==RET)
		return -1;		
	if (pB->getQualitativeCode()==FO)
		return -1;
	
	GScore pointsA=pA->getPointsF();
	GScore pointsB=pB->getPointsF();
	
	int order = orderPoints(pointsA,pointsB);
	if (order)
		return order;
				
	// Miro el ranking del matchResult ya calculado
	MSLSortedVector vMatchResultsA;
	pA->getMatchResultsVector(vMatchResultsA);
	CHMatchResult * pMatchResultA = (CHMatchResult * ) vMatchResultsA[0];

	MSLSortedVector vMatchResultsB;
	pB->getMatchResultsVector(vMatchResultsB);
	CHMatchResult * pMatchResultB = (CHMatchResult * ) vMatchResultsB[0];

	if (pMatchResultA && pMatchResultB)
	{
		if (pMatchResultA->getQualitativeCode()==FO && 
			pMatchResultB->getQualitativeCode()==FO)
			return strcmp(pMatchResultA->getKey(),pMatchResultB->getKey());

		if (pMatchResultA->getQualitativeCode()==FO)
			return 1;

		if (pMatchResultB->getQualitativeCode()==FO)
			return -1;
			
		if (pMatchResultA->getRankPo()==0)
			return 1;

		if (pMatchResultB->getRankPo()==0)
			return -1;

		int rank=pMatchResultA->getRankPo() - pMatchResultB->getRankPo();
		if(rank)
			return rank;
	}

	return 0;
}

static
int compPoolResults2Ties(const MSLItem** a,const MSLItem** b)
{
	CHPoolResult * pA=((CHPoolResult *)(*a));
	CHPoolResult * pB=((CHPoolResult *)(*b));
	
	if (pA->getRegister() && !pB->getRegister())
		return -1;
	if (!pA->getRegister() && pB->getRegister())
		return 1;

	CHEvent *pEvent=(CHEvent*)pA->getEvent();

	for(short i=0;i<pEvent->getNumRankOrder();i++)
	{
		CHEvent::TypeRank typeRnk=pEvent->getRankOrder(i);
		switch(typeRnk)
		{
			case CHEvent::eQualitative:
			{
				// Qualitative
				if (pA->getQualitativeCode()!=OK && 
					pB->getQualitativeCode()!=OK)
				{
					GQualitative * pQA = pA->getQualitative();
					GQualitative * pQB = pB->getQualitative();
					if (pQA && pQB)
						return pQA->getSort() - pQB->getSort();
				}
				
				if (pA->getQualitativeCode()==DSQ)
					return 1;
				if (pA->getQualitativeCode()==RET)
					return 1;
				if (pA->getQualitativeCode()==FO)
					return 1;
				if (pB->getQualitativeCode()==DSQ)
					return -1;		
				if (pB->getQualitativeCode()==RET)
					return -1;		
				if (pB->getQualitativeCode()==FO)
					return -1;
				break;
			}
			case CHEvent::ePoints:
			{		
				GScore pointsA=pA->getPointsF();
				GScore pointsB=pB->getPointsF();
	
				int order = orderPoints(pointsA,pointsB);
				if (order)
					return order;
				break;
			}			
			case CHEvent::eMatchPoints:
			{		
				GScore pointsA=pA->getMatchPoints();
				GScore pointsB=pB->getMatchPoints();
	
				int order = orderPoints(pointsA,pointsB);
				if (order)
					return order;
				break;
			}
			case CHEvent::eDirectEncounter:
			{
				CHPoolResult * pOrigPoolResA = (CHPoolResult *)CHMemoryDataBase::find(*pA);
				CHPoolResult * pOrigPoolResB = (CHPoolResult *)CHMemoryDataBase::find(*pB);

				// Busco el partido que les enfrentó
				CHPool * pPool = (CHPool * ) pA->getPool();
				CHMatch * pMatch = pPool->findMatch(pOrigPoolResA, pOrigPoolResB);
				if (pMatch)
				{
					CHMatchResult * pMR1 = pMatch->getWhite();
					CHMatchResult * pMR2 = pMatch->getBlack();

					if (pMR1->getPoolResult() == pA &&
						pMR2->getPoolResult() == pB )
					{
						int order = orderMatchResultByPoints(pMR1, pMR2);
						if (order)
							return order;
					}
					else if (pMR1->getPoolResult() == pB &&
						 	 pMR2->getPoolResult() == pA )
					{
						int order = orderMatchResultByPoints(pMR2, pMR1);
						if (order)
							return order;
					}
				}
			
				break;
			}
			case CHEvent::eMatchesWon:
			{
				CHPoolResult * pOrigPoolResA = (CHPoolResult *)CHMemoryDataBase::find(*pA);
				CHPoolResult * pOrigPoolResB = (CHPoolResult *)CHMemoryDataBase::find(*pB);

				int order = pOrigPoolResB->getMatchesWon() - pOrigPoolResA->getMatchesWon();
				if (order)
					return order;

				break;
			}
			case CHEvent::eTeamPointsWon:
			{
				CHPoolResult * pOrigPoolResA = (CHPoolResult *)CHMemoryDataBase::find(*pA);
				CHPoolResult * pOrigPoolResB = (CHPoolResult *)CHMemoryDataBase::find(*pB);

				int order = pOrigPoolResA->getAllRoundsPointsForWon() - pOrigPoolResB->getAllRoundsPointsForWon();
				if (order)
					return order;

				break;
			}
			case CHEvent::eAvgOppRating:
			{
				CHPoolResult * pOrigPoolResA = (CHPoolResult *)CHMemoryDataBase::find(*pA);
				CHPoolResult * pOrigPoolResB = (CHPoolResult *)CHMemoryDataBase::find(*pB);

				GScore pointsA = pOrigPoolResA->getOppAverageRating();
				GScore pointsB = pOrigPoolResB->getOppAverageRating();

				int order = orderPoints(pointsA,pointsB);
				if (order)
					return order;
				break;
			}
			case CHEvent::eRating:
			{
				CHPoolResult * pOrigPoolResA = (CHPoolResult *)CHMemoryDataBase::find(*pA);
				CHPoolResult * pOrigPoolResB = (CHPoolResult *)CHMemoryDataBase::find(*pB);

				int pointsA = pOrigPoolResA->getInscriptionRating();
				int pointsB = pOrigPoolResB->getInscriptionRating();

				int order=pointsB - pointsA;
				if(order)
					return order;

				break;
			}
			case CHEvent::eSolkoff:
			{
				CHPoolResult * pOrigPoolResA = (CHPoolResult *)CHMemoryDataBase::find(*pA);
				CHPoolResult * pOrigPoolResB = (CHPoolResult *)CHMemoryDataBase::find(*pB);

				GScore pointsA = pOrigPoolResA->getSolkOffF();
				GScore pointsB = pOrigPoolResB->getSolkOffF();

				int order = orderPoints(pointsA,pointsB);
				if (order)
					return order;
				break;			
			}			
			case CHEvent::eSolkoffCutLowestAndHighest:
			{
				CHPoolResult * pOrigPoolResA = (CHPoolResult *)CHMemoryDataBase::find(*pA);
				CHPoolResult * pOrigPoolResB = (CHPoolResult *)CHMemoryDataBase::find(*pB);

				GScore pointsA = pOrigPoolResA->getMedianSolkOffF(0,1,1);
				GScore pointsB = pOrigPoolResB->getMedianSolkOffF(0,1,1);

				int order = orderPoints(pointsA,pointsB);
				if (order)
					return order;
				break;			
			}
			case CHEvent::eSolkoffCutLowest:
			{
				CHPoolResult * pOrigPoolResA = (CHPoolResult *)CHMemoryDataBase::find(*pA);
				CHPoolResult * pOrigPoolResB = (CHPoolResult *)CHMemoryDataBase::find(*pB);

				GScore pointsA = pOrigPoolResA->getMedianSolkOffF(0,0,1);
				GScore pointsB = pOrigPoolResB->getMedianSolkOffF(0,0,1);

				int order = orderPoints(pointsA,pointsB);
				if (order)
					return order;
				break;			
			}
			case CHEvent::eSonneBerger:
			{
				CHPoolResult * pOrigPoolResA = (CHPoolResult *)CHMemoryDataBase::find(*pA);
				CHPoolResult * pOrigPoolResB = (CHPoolResult *)CHMemoryDataBase::find(*pB);

				GScore pointsA = pOrigPoolResA->getSonneBergerF();
				GScore pointsB = pOrigPoolResB->getSonneBergerF();

				int order = orderPoints(pointsA,pointsB);
				if (order)
					return order;

				break;
			}
		}
	}

	return 0;
}

static
int orderPoolResultsPhase(const MSLItem** a,const MSLItem** b)
{
	CHPoolResult * pPA=((CHPoolResult *)(*a));
	CHPoolResult * pPB=((CHPoolResult *)(*b));

	if (pPA->getRegister() && !pPB->getRegister())
		return -1;
	if (!pPA->getRegister() && pPB->getRegister())
		return 1;

	CHEvent *pEvent=(CHEvent*)pPA->getEvent();

	int order = pPA->getPhaseOrder() - pPB->getPhaseOrder();
	if (order)
		return order;

	CHPhase* pPhase = (CHPhase* ) pPA->getPhase(); 
	
	if (pPA->getRankPo() && pPB->getRankPo())
	{
		order=(pPA->getRankPo() - pPB->getRankPo()); 
		if (order)
			return order;
	}

	for(short i=0;i<pEvent->getNumRankOrder();i++)
	{
		CHEvent::TypeRank typeRnk=pEvent->getRankOrder(i);
		switch(typeRnk)
		{
			case CHEvent::eQualitative:
			{
				// Qualitative
				if (pPA->getQualitativeCode()!=OK && 
					pPB->getQualitativeCode()!=OK)
				{
					GQualitative * pQA = pPA->getQualitative();
					GQualitative * pQB = pPB->getQualitative();
					if (pQA && pQB)
						return pQA->getSort() - pQB->getSort();
				}
				
				if (pPA->getQualitativeCode()==DSQ)
					return 1;
				if (pPA->getQualitativeCode()==RET)
					return 1;
				if (pPA->getQualitativeCode()==FO)
					return 1;
				if (pPB->getQualitativeCode()==DSQ)
					return -1;		
				if (pPB->getQualitativeCode()==RET)
					return -1;		
				if (pPB->getQualitativeCode()==FO)
					return -1;
				break;
			}
			case CHEvent::ePoints:
			{
				// Score
				GScore pointsA=pPA->getPoints();
				GScore pointsB=pPB->getPoints();
			
				int order = orderPoints(pointsA,pointsB);
				if (order)
					return order;
				break;				
			}			
		}
	}

	return strcmp(pPA->getKey(),pPB->getKey());
}

static
int compPoolResultsPhase(const MSLItem** a,const MSLItem** b)
{
	CHPoolResult * pPA=((CHPoolResult *)(*a));
	CHPoolResult * pPB=((CHPoolResult *)(*b));

	if (pPA->getRegister() && !pPB->getRegister())
		return -1;
	if (!pPA->getRegister() && pPB->getRegister())
		return 1;

	CHEvent *pEvent=(CHEvent*)pPA->getEvent();

	int order = pPA->getPhaseOrder() - pPB->getPhaseOrder();
	if (order)
		return order;

	CHPhase* pPhase = (CHPhase* ) pPA->getPhase(); 
	
	if (pPA->getRankPo() && pPB->getRankPo())
	{
		order=(pPA->getRankPo() - pPB->getRankPo()); 
		if (order)
			return order;
	}
	
	for(short i=0;i<pEvent->getNumRankOrder();i++)
	{
		CHEvent::TypeRank typeRnk=pEvent->getRankOrder(i);
		switch(typeRnk)
		{
			case CHEvent::eQualitative:
			{
				// Qualitative
				if (pPA->getQualitativeCode()!=OK && 
					pPB->getQualitativeCode()!=OK)
				{
					GQualitative * pQA = pPA->getQualitative();
					GQualitative * pQB = pPB->getQualitative();
					if (pQA && pQB)
						return pQA->getSort() - pQB->getSort();
				}
				
				if (pPA->getQualitativeCode()==DSQ)
					return 1;
				if (pPA->getQualitativeCode()==RET)
					return 1;
				if (pPA->getQualitativeCode()==FO)
					return 1;
				if (pPB->getQualitativeCode()==DSQ)
					return -1;		
				if (pPB->getQualitativeCode()==RET)
					return -1;		
				if (pPB->getQualitativeCode()==FO)
					return -1;
				break;
			}
			case CHEvent::ePoints:
			{
				// Score
				GScore pointsA=pPA->getPoints();
				GScore pointsB=pPB->getPoints();
			
				int order = orderPoints(pointsA,pointsB);
				if (order)
					return order;
				break;				
			}			
		}
	}
	return 0;
}

CHRanking::CHRanking(MSLGUIEx* pGUIEx)
:GTHRanking(pGUIEx)
,m_bLastRkCalculation(false)
,m_rankCH(0)
,m_rankPoCH(0)
,m_tiesCH(0)
{
}

CHRanking::~CHRanking()
{
}

void CHRanking::setRankings(GData  * pData, bool tie)
{
	if (pData && 
		pData->isA()==__CHEVENTRESULT)
	{
		setRankings((CHEventResult*)pData, tie);
		return;
	}
	return GTHRanking::setRankings(pData,tie);
}

void CHRanking::setRankings(CHEventResult  * pEventResult , bool tie)
{
	if(!pEventResult)
		return;

	CHEventResult* pRealEventResult = (CHEventResult*) getMem()->find(*pEventResult);
	if (!pRealEventResult)
		return;

	m_rankPo++;
	if (!tie)
		m_rank=m_rankPo;
					
	setEventRankings(pRealEventResult, m_rank, m_rankPo);	
}

void CHRanking::setEventRankings(CHEventResult* pEventResult, short rank, short rankPo)
{
	if (!pEventResult)
		return;

	CHPoolResult* pPoolResult = (CHPoolResult*)pEventResult->getPoolResult();
	if (pPoolResult->getPoolStatus()==CHMemoryDataBase::eFinished)
	{
		pEventResult->setRank( getEventRank(pEventResult, pPoolResult, rank) );
		pEventResult->setRankPo(rankPo);
	}
	else
	{
		pEventResult->setRank(0);
		pEventResult->setRankPo(0);
	}

	APP::out(*pEventResult);
}

short CHRanking::getEventRank(CHEventResult *pEventResult, CHPoolResult *pPoolResult, short rank)
{
	if (!pEventResult || !pPoolResult)
		return 0;

	GTHPool  * pPool = (GTHPool *)pPoolResult->getPool();
	CHPhase * pPhase= (CHPhase*)pPool->getPhase();

	if (!pPool || !pPhase)
		return 0;

	int winerRank = pPhase->getWinnerRank();
	if (winerRank==0)
	{
		CHEvent * pEvent = (CHEvent * ) pPhase->getEvent();
		if (pEvent->getPhases().entries()==1 && pPhase->getPhase()==SWISS_ROUND)
			winerRank=1;
	}
	
	int loserRank = pPhase->getLoserRank();

	if(pEventResult->getQualitativeCode()==DSQ) // no le doy ranking para la medalla
		return 0;
	
	else if(pPhase->getStatus()<CHMemoryDataBase::eUnofficial) //para desprogresion
		return 0;
	
	else if(pPhase->getIsPool()) //Phase de Pooles
	{
		return pPoolResult->getPhaseRank() ? pPoolResult->getPhaseRank() : rank;
	}
	else if(!pPhase->getIsPool()) //Phase Eliminatoria
	{
		if(pPoolResult->getRank()==1 && winerRank) 
			return short(winerRank);
		else if(pPoolResult->getRank()==2 && loserRank)
			return short(loserRank);		
	}
	
	return rank;
}


void CHRanking::setRankings(GTHMatchResult  * pMatchResult , bool tie)
{
	if (!m_bLastRkCalculation)
	{
		GTHRanking::setRankings(pMatchResult , tie);
		return;
	}

	if(!pMatchResult)
		return;

	CHMatchResult* pRealMatchResult = (CHMatchResult*) getMem()->find(*pMatchResult);
	if (!pRealMatchResult)
		return;

	m_rankPoCH++;

	if(!tie)
		m_rankCH=m_rankPoCH;

	setMatchRankings(pRealMatchResult, short(m_rankCH), short(m_rankPoCH));		
}

void CHRanking::onSetMatchRankings(GTHMatchResult * pMatchResult, short rank, short rankPo)
{
	if (pMatchResult->getQualitativeCode()==DSQ || 
		pMatchResult->getQualitativeCode()==RET ||
		pMatchResult->getQualitativeCode()==FO)
	{
		pMatchResult->setRank(0);
		pMatchResult->setRankPo(0);
	}

	UNREFERENCED_PARAMETER(rankPo);
	UNREFERENCED_PARAMETER(rank);
}

void CHRanking::onSetPoolRankings(GTHPoolResult	* pPoolResult , short rank, short rankPo)
{
	if (pPoolResult->getQualitativeCode()==DSQ ||
		pPoolResult->getQualitativeCode()==RET)
	{
		//pPoolResult->setRank(0);
		//pPoolResult->setRankPo(0);
	}

	UNREFERENCED_PARAMETER(rank);
	UNREFERENCED_PARAMETER(rankPo);
}


void CHRanking::onSetPhaseRankings(GTHPoolResult * pPoolResult , short rank, short rankPo)
{
	if (pPoolResult->getQualitativeCode()==DSQ ||
		pPoolResult->getQualitativeCode()==FO)
	{
		pPoolResult->setPhaseRank(0);
		pPoolResult->setPhaseRankPo(0);
	}

	UNREFERENCED_PARAMETER(rank);
	UNREFERENCED_PARAMETER(rankPo);
}

void CHRanking::getColResults(GData* pData, MSLSet& colResults)
{
	if (pData->isA()==__CHEVENT)
	{
		MSLSet colEventResults;
		((CHEvent*)pData)->getEventResults(colEventResults);
		colResults = colEventResults.select(getValidResultsFunction(pData), getParamRankings(pData));
		return;
	}
	
	GTHRanking::getColResults(pData,colResults);
}

mslToolsFcSelect CHRanking::getValidResultsFunction(GData* pData)
{
	if (pData &&
		pData->isA()==__CHEVENT)
		return validEventResults;

	return GTHRanking::getValidResultsFunction(pData);
}

mslToolsFcCompare CHRanking::getSortResults(GData* pData)
{
	if (pData && 
		pData->isA()==__CHEVENT)
		return orderEventResults;
	
	return GTHRanking::getSortResults(pData);
}

mslToolsFcCompare CHRanking::getSortResultsNoTies(GData* pData)
{
	if (pData && 
		pData->isA()==__CHEVENT)
		return orderEventResults;
	

	return GTHRanking::getSortResultsNoTies(pData);
}

mslToolsFcCompare CHRanking::getSortResults2Ties(GData* pData)
{
	if (pData && 
		pData->isA()==__CHEVENT)
		return orderEventResults;
		
	return GTHRanking::getSortResults2Ties(pData);
}

mslToolsFcCompare CHRanking::getSortResults3Ties(GData* pData)
{
	if (pData && 
		pData->isA()==__CHEVENT)
		return orderEventResults;

	return GTHRanking::getSortResults3Ties(pData);
}	

mslToolsFcCompare CHRanking::getSortResultsTotal(GData* pData)
{
	if (pData && 
		pData->isA()==__CHEVENT)
		return orderEventResults;

	return GTHRanking::getSortResultsTotal(pData);
}

mslToolsFcCompare CHRanking::getCompResults(GData* pData)
{
	if (pData && 
		pData->isA()==__CHEVENT)
		return compEventResults;

	return GTHRanking::getCompResults(pData);
}

mslToolsFcCompare CHRanking::getCompResultsNoTies(GData* pData)
{
	if (pData && 
		pData->isA()==__CHEVENT)
		return compEventResults;

	return GTHRanking::getCompResultsNoTies(pData);
}

mslToolsFcCompare CHRanking::getCompResults2Ties(GData* pData)
{
	if (pData && 
		pData->isA()==__CHEVENT)
		return compEventResults;

	return GTHRanking::getCompResults2Ties(pData);
}

mslToolsFcCompare CHRanking::getCompResults3Ties(GData* pData)
{
	if (pData && 
		pData->isA()==__CHEVENT)
		return compEventResults;

	return GTHRanking::getCompResults3Ties(pData);
}

mslToolsFcCompare CHRanking::getCompResultsTotal(GData* pData)
{
	if (pData && 
		pData->isA()==__CHEVENT)
		return compEventResults;


	return GTHRanking::getCompResultsTotal(pData);
}

mslToolsFcCompare CHRanking::getSortMatchResults(GTHMatch* pMatch)
{
	if ( ( (CHMatch*) pMatch)->isTeam() && pMatch->getPhaseCode()!=SWISS_ROUND)
		return orderMatchResultByTeamPointsEliminatory;

	return orderMatchResultByPoints;
}

mslToolsFcCompare CHRanking::getSortMatchResultsNoTies(GTHMatch* pMatch)
{
	if ( ( (CHMatch*) pMatch)->isTeam() && pMatch->getPhaseCode()!=SWISS_ROUND)
		return orderMatchResultByTeamPointsEliminatory;

	return orderMatchResultByPoints;
}

mslToolsFcCompare CHRanking::getSortMatchResults2Ties(GTHMatch* pMatch)
{
	if ( ( (CHMatch*) pMatch)->isTeam() && pMatch->getPhaseCode()!=SWISS_ROUND)
		return orderMatchResultByTeamPointsEliminatory;

	return orderMatchResultByPoints;
}

mslToolsFcCompare CHRanking::getSortMatchResults3Ties(GTHMatch* pMatch)
{
	if ( ( (CHMatch*) pMatch)->isTeam() && pMatch->getPhaseCode()!=SWISS_ROUND)
		return orderMatchResultByTeamPointsEliminatory;

	return orderMatchResultByPoints;
}

mslToolsFcCompare CHRanking::getSortMatchResultsTotal(GTHMatch* pMatch)
{
	if ( ( (CHMatch*) pMatch)->isTeam() && pMatch->getPhaseCode()!=SWISS_ROUND)
		return orderMatchResultByTeamPointsEliminatory;

	return orderMatchResultByPoints;
}

mslToolsFcCompare CHRanking::getCompMatchResults(GTHMatch* pMatch)
{	
	if ( ( (CHMatch*) pMatch)->isTeam() && pMatch->getPhaseCode()!=SWISS_ROUND)
		return compMatchResultByTeamPointsEliminatory;

	return compMatchResultByPoints;
}

mslToolsFcCompare CHRanking::getCompMatchResultsNoTies(GTHMatch* pMatch)
{
	if ( ( (CHMatch*) pMatch)->isTeam() && pMatch->getPhaseCode()!=SWISS_ROUND)
		return compMatchResultByTeamPointsEliminatory;
	
	return compMatchResultByPoints;
}

mslToolsFcCompare CHRanking::getCompMatchResults2Ties(GTHMatch* pMatch)
{
	if ( ( (CHMatch*) pMatch)->isTeam() && pMatch->getPhaseCode()!=SWISS_ROUND)
		return compMatchResultByTeamPointsEliminatory;

	return compMatchResultByPoints;
}

mslToolsFcCompare CHRanking::getCompMatchResults3Ties(GTHMatch* pMatch)
{
	if ( ( (CHMatch*) pMatch)->isTeam() && pMatch->getPhaseCode()!=SWISS_ROUND)
		return compMatchResultByTeamPointsEliminatory;

	return compMatchResultByPoints;
}

mslToolsFcCompare CHRanking::getCompMatchResultsTotal(GTHMatch* pMatch)
{
	if ( ( (CHMatch*) pMatch)->isTeam() && pMatch->getPhaseCode()!=SWISS_ROUND)
		return compMatchResultByTeamPointsEliminatory;

	return compMatchResultByPoints;
}

void CHRanking::postCalculateRankings(GData* pData, MSLSortedVector vResults)
{	
}

void CHRanking::resetMatchData(GTHMatch* pMatch, MSLSortedVector vMatchResults, bool send)
{
	for (long i=0;i<vMatchResults.entries();i++)
	{
		GTHMatchResult* pMatchResult = (GTHMatchResult*)vMatchResults[i];
		resetMatchResultData(pMatchResult, false);		
	}
	UNREFERENCED_PARAMETER(pMatch);	
	UNREFERENCED_PARAMETER(send);
}


bool CHRanking::preAcumulateMatchData(GTHMatchResult* pMatchResult)
{
	return true;
	UNREFERENCED_PARAMETER(pMatchResult);
}

// POOL RANKINGS
mslToolsFcCompare CHRanking::getSortPoolResults(GTHPool* pPool)
{
	if ( ( (CHPool*) pPool)->isTeam() && pPool->getPhaseCode()!=SWISS_ROUND)
		return orderPoolResultsByTeamPointsEliminatory;

	return orderPoolResults;
	UNREFERENCED_PARAMETER(pPool);
}

mslToolsFcCompare CHRanking::getSortPoolResultsNoTies(GTHPool* pPool)
{
	if ( ( (CHPool*) pPool)->isTeam() && pPool->getPhaseCode()!=SWISS_ROUND)
		return orderPoolResultsByTeamPointsEliminatory;

	return orderPoolResults;
	UNREFERENCED_PARAMETER(pPool);
}

mslToolsFcCompare CHRanking::getSortPoolResults2Ties(GTHPool* pPool)
{
	if ( ( (CHPool*) pPool)->isTeam() && pPool->getPhaseCode()!=SWISS_ROUND)
		return orderPoolResultsByTeamPointsEliminatory;

	return orderPoolResults2Ties;
	UNREFERENCED_PARAMETER(pPool);
}

mslToolsFcCompare CHRanking::getSortPoolResults3Ties(GTHPool* pPool)
{
	if ( ( (CHPool*) pPool)->isTeam() && pPool->getPhaseCode()!=SWISS_ROUND)
		return orderPoolResultsByTeamPointsEliminatory;

	return orderPoolResults;
	UNREFERENCED_PARAMETER(pPool);
}

mslToolsFcCompare CHRanking::getSortPoolResultsTotal(GTHPool* pPool)
{
	if ( ( (CHPool*) pPool)->isTeam() && pPool->getPhaseCode()!=SWISS_ROUND)
		return orderPoolResultsByTeamPointsEliminatory;

	return orderPoolResults;
	UNREFERENCED_PARAMETER(pPool);
}

mslToolsFcCompare CHRanking::getCompPoolResults(GTHPool* pPool)
{
	if ( ( (CHPool*) pPool)->isTeam() && pPool->getPhaseCode()!=SWISS_ROUND)
		return compPoolResultsByTeamPointsEliminatory;

	return compPoolResults;
	UNREFERENCED_PARAMETER(pPool);
}	

mslToolsFcCompare CHRanking::getCompPoolResultsNoTies(GTHPool* pPool)
{
	if ( ( (CHPool*) pPool)->isTeam() && pPool->getPhaseCode()!=SWISS_ROUND)
		return compPoolResultsByTeamPointsEliminatory;

	return compPoolResults;
	UNREFERENCED_PARAMETER(pPool);
}

mslToolsFcCompare CHRanking::getCompPoolResults2Ties(GTHPool* pPool)
{
	if ( ( (CHPool*) pPool)->isTeam() && pPool->getPhaseCode()!=SWISS_ROUND)
		return compPoolResultsByTeamPointsEliminatory;

	return compPoolResults2Ties;
	UNREFERENCED_PARAMETER(pPool);
}

mslToolsFcCompare CHRanking::getCompPoolResults3Ties(GTHPool* pPool)
{
	if ( ( (CHPool*) pPool)->isTeam() && pPool->getPhaseCode()!=SWISS_ROUND)
		return compPoolResultsByTeamPointsEliminatory;

	return compPoolResults;
	UNREFERENCED_PARAMETER(pPool);
}

mslToolsFcCompare CHRanking::getCompPoolResultsTotal(GTHPool* pPool)
{
	return compPoolResults;
	UNREFERENCED_PARAMETER(pPool);
}

mslToolsFcSelect  CHRanking::getValidPoolResultsFunction(GTHPool* pPool)
{
	return poolResultsRanked;
	UNREFERENCED_PARAMETER(pPool);
}	

// PHASE RANKING
mslToolsFcCompare CHRanking::getSortPoolResultsPhase(GTHPhase* pPhase)
{
	return orderPoolResultsPhase;
	UNREFERENCED_PARAMETER(pPhase);
}

mslToolsFcCompare CHRanking::getSortPoolResultsPhaseNoTies(GTHPhase* pPhase)
{
	return orderPoolResultsPhase;
	UNREFERENCED_PARAMETER(pPhase);
}

mslToolsFcCompare CHRanking::getSortPoolResultsPhase2Ties(GTHPhase* pPhase)
{
	return orderPoolResultsPhase;
	UNREFERENCED_PARAMETER(pPhase);
}

mslToolsFcCompare CHRanking::getSortPoolResultsPhase3Ties(GTHPhase* pPhase)
{
	return orderPoolResultsPhase;
	UNREFERENCED_PARAMETER(pPhase);
}

mslToolsFcCompare CHRanking::getSortPoolResultsPhaseTotal(GTHPhase* pPhase)
{
	return orderPoolResultsPhase;
	UNREFERENCED_PARAMETER(pPhase);
}

mslToolsFcCompare CHRanking::getCompPoolResultsPhase(GTHPhase* pPhase)
{
	return compPoolResultsPhase;
	UNREFERENCED_PARAMETER(pPhase);
}

mslToolsFcCompare CHRanking::getCompPoolResultsPhaseNoTies(GTHPhase* pPhase)
{
	return compPoolResultsPhase;
	UNREFERENCED_PARAMETER(pPhase);
}

mslToolsFcCompare CHRanking::getCompPoolResultsPhase2Ties(GTHPhase* pPhase)
{
	return compPoolResultsPhase;
	UNREFERENCED_PARAMETER(pPhase);
}

mslToolsFcCompare CHRanking::getCompPoolResultsPhase3Ties(GTHPhase* pPhase)
{
	return compPoolResultsPhase;
	UNREFERENCED_PARAMETER(pPhase);
}

mslToolsFcCompare CHRanking::getCompPoolResultsPhaseTotal(GTHPhase* pPhase)
{
	return compPoolResultsPhase;
	UNREFERENCED_PARAMETER(pPhase);
}

mslToolsFcSelect CHRanking::getValidPoolResultsPhaseFunction(GTHPhase* pPhase)
{
	return phaseResultsRanked;
	UNREFERENCED_PARAMETER(pPhase);
}

bool CHRanking::isValidData(GData* pData)
{
	if (pData && 
		pData->isA()==__CHEVENT)
		return true;

	return GTHRanking::isValidData(pData);
}

bool CHRanking::onPerfectTie(GData* pData, MSLSortedVector vTiesResults)
{
	bool ret = GTHRanking::onPerfectTie(pData,vTiesResults);

	if (pData->isA()!=__CHMATCH)
		return ret;

	return ret;
}

bool CHRanking::preAcumulateMatchData(MSLSortedVector vResults, GTHMatchResult* pMatchResult)
{
	return pMatchResult ? ( pMatchResult->getMatchStatus()==CHMemoryDataBase::eFinished ? true : false ) : false;
}

bool CHRanking::preAcumulatePoolData(MSLSortedVector vResults, GTHPoolResult* pPoolResult, GTHMatchResult* pMatchResult)
{
	GTHMatch * pMatch = pMatchResult->getMatch();
	if (pMatch->getSubCode())
		return false;

	if (pMatchResult->getMatchStatus()!=GTHMemoryDataBase::eFinished && 
		pMatchResult->getMatchStatus()!=GTHMemoryDataBase::eUnofficial)
		return false;

	CHPool* pPool = (CHPool*)pPoolResult->getPool();
		
	// Solo los match results con los equipos implicados en el empate
	for (short i=0;i<vResults.entries();i++)
	{
		CHPoolResult* pPResult = (CHPoolResult*)vResults[i];
		if (pPResult->getKey()==pPoolResult->getKey())
			continue;
		
		CHMatchResult* pMResult = (CHMatchResult*) pMatchResult->getOpponent();
		if (!pMResult)
			continue;

		if (pMResult->getRegCode()==pPResult->getRegCode())
			return true;
	}
	
	return false;
}

void CHRanking::userResetPoolResultData(GTHPoolResult* pPoolResult, bool send)
{
	((CHPoolResult*)pPoolResult)->clearData();
	UNREFERENCED_PARAMETER(send);
}

void CHRanking::userAcumulatePoolData(GTHPoolResult* pPoolResult, GTHMatchResult* pMatchResult)
{
	CHMatch* pMatch = (CHMatch*)pMatchResult->getMatch();

	if  ( pMatch && 
		( pMatch->getStatus() == CHMemoryDataBase::eFinished ||
		  pMatch->getStatus() == CHMemoryDataBase::eUnofficial ) )
	{
		((CHPoolResult*)pPoolResult)->setPointsF(((CHPoolResult*)pPoolResult)->getPointsF() + ((CHMatchResult*)pMatchResult)->getPoints());
		((CHPoolResult*)pPoolResult)->setMPlayed(((CHPoolResult*)pPoolResult)->getMPlayed() + 1 );
		
		if (!pMatch->isTeam())
		{
			if (((CHMatchResult*)pMatchResult)->getPoints()==WIN_POINTS)
				((CHPoolResult*)pPoolResult)->setMWon( ((CHPoolResult*)pPoolResult)->getMWon() + 1);
			if (((CHMatchResult*)pMatchResult)->getPoints()==DRAW_POINTS)
				((CHPoolResult*)pPoolResult)->setMDrawn( ((CHPoolResult*)pPoolResult)->getMDrawn() + 1);
			if (((CHMatchResult*)pMatchResult)->getPoints()==LOST_POINTS)
				((CHPoolResult*)pPoolResult)->setMLost( ((CHPoolResult*)pPoolResult)->getMLost() + 1);
		}
		else
		{
			MSLSortedVector vSubMatchesResult;
			pMatchResult->getSubMatchResultsVector(vSubMatchesResult);
			for (short i=0;i<vSubMatchesResult.entries();i++)
			{
				CHMatchResult * pSubMatchResult = (CHMatchResult*)vSubMatchesResult[i];
				if (pSubMatchResult->getMatchStatus() == CHMemoryDataBase::eFinished ||
					pSubMatchResult->getMatchStatus() == CHMemoryDataBase::eUnofficial ) 
				{
					CHMatch * pSubMatch=(CHMatch*)pSubMatchResult->getMatch();

					if (((CHMatchResult*)pSubMatchResult)->getPoints()==WIN_POINTS)
						((CHPoolResult*)pPoolResult)->setMWon( ((CHPoolResult*)pPoolResult)->getMWon() + 1);
					if (((CHMatchResult*)pSubMatchResult)->getPoints()==DRAW_POINTS)
						((CHPoolResult*)pPoolResult)->setMDrawn( ((CHPoolResult*)pPoolResult)->getMDrawn() + 1);
					if (((CHMatchResult*)pSubMatchResult)->getPoints()==LOST_POINTS && pSubMatch && pSubMatch->getResultCode()!=EV_EMPTY)
						((CHPoolResult*)pPoolResult)->setMLost( ((CHPoolResult*)pPoolResult)->getMLost() + 1);				
				}			
			}
		}

		APP::out(*pPoolResult);
	}
}

void CHRanking::calculateMedals(GTHPhase* pPhase)
{
	if(!pPhase)
		return;

	bool calculateMedals=false;
	if (pPhase->getEvent() && pPhase->getEvent()->getPhases().entries()==1)
		calculateMedals=true;

	int winerRank = pPhase->getWinnerRank();
	int loserRank = pPhase->getLoserRank();

	if( ( winerRank==1 || winerRank==2 || winerRank==3 ||
	      loserRank==1 || loserRank==2 || loserRank==3 ) || calculateMedals )
	{
		GTHEvent * pEvent =(GTHEvent*)pPhase->getEvent();

		//si hay medallistas primero me los cargo
		deleteMedallist(pEvent);

		//Creo los medallistas nuevos
		createMedallist(pEvent);
	}
}

void CHRanking::onMedallistCreated(GMedallist * pMedallist)
{
	if (!pMedallist)
		return;

	CHInscription * pInscription = (CHInscription*) CHMemoryDataBase::findInscription(pMedallist->getRegister(), pMedallist->getEvent());
	if (!pInscription)
		return;

	CHMatchResult* pMatchResult = pInscription->getLastMatchResult();
	if (!pMatchResult)
	{
		// Pongo la fecha de Hoy
		MSLDate today;
		pMedallist->setDate(today);
		return;
	}

	CHMatch *pMatch = (CHMatch*) pMatchResult->getMatch();
	if (pMatch)
		pMedallist->setDate(pMatch->getStartDate());
}

