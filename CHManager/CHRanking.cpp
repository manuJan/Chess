/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHRanking.cpp
*	Description	: Implementation for the CHRanking class.
*
*	Author		: CH Team
*	Date created: 20-12-2005
* 	Project		: CHManager
*	
* 	Modification history
*	By			: 
*	Date		: 
*	Changes		: 
*
***************************************************************************************/

#include "stdafx.h"
#include "CHManager.h"
#include "CHRanking.h"
#include <CORE/G/GMsgDefines.h>
#include <Sports\CH\Data\CHDiscipline.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

////////////////////////////////////////////////////////////////////////////////////
static int orderPRByRanking(const GVectorElement** a, const GVectorElement** b)
{
	CHPoolResult * pPRA=(CHPoolResult *)(*a)->getElement();
	CHPoolResult * pPRB=(CHPoolResult *)(*b)->getElement();

	CHEvent *pEvent=(CHEvent*)pPRA->getEvent();

	int order=0;
	for(short i=0;i<pEvent->getNumRankOrder();i++)
	{
	
		CHEvent::TypeRank typeRnk=pEvent->getRankOrder(i);
		switch(typeRnk)
		{
			case CHEvent::eQualitative:
			{	
				// Qualitative
				if (pPRA->isQualitative() && pPRB->isQualitative())
				{
					GQualitative * pQA = pPRA->getQualitative();
					GQualitative * pQB = pPRB->getQualitative();
					if (pQA && pQB)
						return pQA->getSort() - pQB->getSort();
				}
				if (pPRA->isQualitative())
					return 1;
				if (pPRB->isQualitative())
					return -1;		
				break;
			}
			case CHEvent::ePoints:
			{
				// Points
				float orderF = pPRB->getPointsF() - pPRA->getPointsF();
				if (orderF>0)
					return 1;
				if (orderF<0)
					return -1;

				break;
			}
			case CHEvent::eSolkoff:
			{
				// Solkoff
				float orderF = pPRB->getMSolkoff() - pPRA->getMSolkoff();
				if (orderF>0)
					return 1;
				if (orderF<0)
					return -1;
				break;
			}
			case CHEvent::eMedianSolkoff:
			{
				// Solkoff
				float orderF = pPRB->getMMedianSolkoff() - pPRA->getMMedianSolkoff();
				if (orderF>0)
					return 1;
				if (orderF<0)
					return -1;
				break;
			}
			case CHEvent::eSonneBerger:
			{
				// SonneBerger
				float orderF = pPRB->getMSonneBerger() - pPRA->getMSonneBerger();
				if (orderF>0)
					return 1;
				if (orderF<0)
					return -1;
				break;
			}
			
			case CHEvent::eProgressiveScore:
			{
				// SonneBerger
				float orderF = pPRB->getMProgressiveScore() - pPRA->getMProgressiveScore();
				if (orderF>0)
					return 1;
				if (orderF<0)
					return -1;
				break;
			}
			case CHEvent::eRating:
			{
				// Rating de comienzo
				order = pPRB->getInscriptionRating() - pPRA->getInscriptionRating();
				if (order)
					return order;
				break;
			}

			case CHEvent::eTeamMatchesWon:
			{
				// Solo en equipos tengo que mirar los partidos ganados por los miembros
				if(pEvent->isTeam())
				{
					// Partidos ganados por miembros
					order = pPRB->getTeamMatchesWon() - pPRA->getTeamMatchesWon();
					if (order)
						return order;
				}
				break;
			}
			case CHEvent::eMatchesWon:
			{
				// Partidos ganados 
				order = pPRB->getMWon() - pPRA->getMWon();
				if (order)
					return order;
				
				break;
			}
			case CHEvent::eMatchesDrawm:
			{
				// Partidos empatados
				order = pPRB->getMDrawn() - pPRA->getMDrawn();
				if (order)
					return order;
				
				break;
			}
			case CHEvent::eTeamPointsWon:
			{
				// Puntos de encuentro
				order = pPRB->getPointsForWon() - pPRA->getPointsForWon();
				if (order)
					return order;
				
				break;
			}

			
		 	
		}

	}

	return strcmp(pPRA->getKey(),pPRB->getKey());
		
}


static int orderPoolResultSO(const GVectorElement** a, const GVectorElement** b)
{
	CHPoolResult * pPoolResultA = (CHPoolResult *) (*a)->getElement();
	CHPoolResult * pPoolResultB = (CHPoolResult *) (*b)->getElement();

	CHPool *pPoolA=(CHPool*)pPoolResultA->getPool();
	CHPool *pPoolB=(CHPool*)pPoolResultB->getPool();

	// Order by Pool
	int order = pPoolA->getOrder() - pPoolB->getOrder();
	if( order )
		return order;

	float ord = pPoolResultA->getPointsF() - pPoolResultB->getPointsF();
	if (ord<0.0)
		return 1;
	if (ord>0.0)
		return -1;

	ord = pPoolResultA->getPointsSO() - pPoolResultB->getPointsSO();
	if (ord<0.0)
		return 1;
	if (ord>0.0)
		return -1;


	// Si alguno de ellos no tienen la sesión asignada va para abajo.
	if (!pPoolResultA->getRankPo())
		return 1;
	if (!pPoolResultB->getRankPo())
		return -1;

	// Order by Rank Po
	order = pPoolResultA->getRankPo() - pPoolResultB->getRankPo();
	if( order )
		return order;

	// Si alguno de ellos no tienen la sesión asignada va para abajo.
	if (!pPoolResultA->getRank())
		return 1;
	if (!pPoolResultB->getRank())
		return -1;

	// Order by Rank 
	order = pPoolResultA->getRank() - pPoolResultB->getRank();
	if( order )
		return order;
	
	// Order by key
	return strcmp(pPoolResultA->getKey(),pPoolResultB->getKey());
}
////////////////////////////////////////////////////////////////////////////////////
static int orderPRByTieRankingOlympic(const GVectorElement** a, const GVectorElement** b)
{
	CHTieRankingPoolResult * pPRA=(CHTieRankingPoolResult *)(*a)->getElement();
	CHTieRankingPoolResult * pPRB=(CHTieRankingPoolResult *)(*b)->getElement();

	// Ranking Pool Result
	int order = orderPRByRanking(a,b);
	if (order)
		return order;
	
	// Tie Points 
	float orderF = pPRB->getPointsTie() - pPRA->getPointsTie();
	if (orderF>0)
		return 1;
	if (orderF<0)
		return -1;

	return strcmp(pPRA->getKey(),pPRB->getKey());
		
}

////////////////////////////////////////////////////////////////////////////////////
static int orderMRByPhaseOrder(const GVectorElement** a, const GVectorElement** b)
{
	CHMatchResult * pMRA=(CHMatchResult *)(*a)->getElement();
	CHMatchResult * pMRB=(CHMatchResult *)(*b)->getElement();

	CHPhase * pPhaseA=(CHPhase *)pMRA->getPhase();
	CHPhase * pPhaseB=(CHPhase *)pMRB->getPhase();

	return pPhaseA->getOrder() - pPhaseB->getOrder();
}

////////////////////////////////////////////////////////////////////////////////////
static int orderMRByRankingEvent(const GVectorElement** a, const GVectorElement** b)
{
	CHMatchResult * pMRA=(CHMatchResult *)(*a)->getElement();
	CHMatchResult * pMRB=(CHMatchResult *)(*b)->getElement();

	CHEventResult * pERA=(CHEventResult *)pMRA->getEventResult();
	CHEventResult * pERB=(CHEventResult *)pMRB->getEventResult();

	CHPoolResult * pPoolResultA=(CHPoolResult *)pMRA->getPoolResult();
	CHPoolResult * pPoolResultB=(CHPoolResult *)pMRB->getPoolResult();

	CHPhase * pPhaseA=(CHPhase *)pMRA->getPhase();
	CHPhase * pPhaseB=(CHPhase *)pMRB->getPhase();

	// Qualitative
	if (pERA && pERB && pERA->isQualitative() &&
		pERB->isQualitative()  )
	{
		GQualitative * pQA = CHMemoryDataBase::findQualitative(pERA->getQualitativeCode());
		GQualitative * pQB = CHMemoryDataBase::findQualitative(pERB->getQualitativeCode());
		if (pQA && pQB)
			return pQA->getSort() - pQB->getSort();
	}
	if (pERA && pERA->isQualitative())
		return 1;
	if (pERB && pERB->isQualitative())
		return -1;

	// Orden de loser-rank de la fase
	int order = pPhaseA->getLoserRank() - pPhaseB->getLoserRank();
	if (order)
		return order;

	// Ranking en la phase
	order = pPoolResultA->getPhaseRankPo() - pPoolResultB->getPhaseRankPo();
	if (order)
		return order;

	// Ranking en la pool
	order = pPoolResultA->getRankPo() - pPoolResultB->getRankPo();
	if (order)
		return order;

	// Key
	return stricmp(pMRA->getKey(),pMRB->getKey());
}

////////////////////////////////////////////////////////////////////////////////////
static int orderTieRankingPhase(const GVectorElement** a, const GVectorElement** b)
{
	CHTieRankingPoolResult * pPRA=(CHTieRankingPoolResult *)(*a)->getElement();
	CHTieRankingPoolResult * pPRB=(CHTieRankingPoolResult *)(*b)->getElement();

	// Qualitative
	if (pPRA->getQualitativeCode()!=OK && pPRA->getQualitativeCode()!=NULLRWSTRING &&
		pPRB->getQualitativeCode()!=OK && pPRB->getQualitativeCode()!=NULLRWSTRING  )
	{
		GQualitative * pQA = CHMemoryDataBase::findQualitative(pPRA->getQualitativeCode());
		GQualitative * pQB = CHMemoryDataBase::findQualitative(pPRB->getQualitativeCode());
		if (pQA && pQB && pPRA->isQualitative() && pPRB->isQualitative())
			return pQA->getSort() - pQB->getSort();
	}
	if (pPRA->isQualitative())
		return 1;
	if (pPRB->isQualitative())
		return -1;

	CHPhase *pPhaseA=(CHPhase*)pPRA->getPhase();
	CHPhase *pPhaseB=(CHPhase*)pPRB->getPhase();
	
	// Rank
	if(pPhaseA->getIsPool())
	{
		int order = pPRA->getRank() - pPRB->getRank();
		if (order)
			return order;	
	}
	
	
	// Solkoff
	float orderF = pPRB->getMSolkoff() - pPRA->getMSolkoff();
	if (orderF>0)
		return 1;
	if (orderF<0)
		return -1;

	// Key
	return stricmp(pPRA->getKey(),pPRB->getKey());
}

/////////////////////////////////////////////////////////////////////
static RWBoolean selectMatchResultsOfEvent(const RWCollectable *col, const void *param)
{
	CHEvent       * pEvent       = (CHEvent *)param;
	CHMatchResult * pMatchResult = (CHMatchResult *)col;	

	if( !pMatchResult->getSubMatch() && pMatchResult->getEvent() == pEvent && pMatchResult->getMatchStatus() >= CHMemoryDataBase::eUnofficial )
		return true;

	return false;	
}
RWBoolean matchResultsOfCompetition(const RWCollectable *col, const void *param)
{
	CHMatchResult * pMatchResult = (CHMatchResult *) param;
	if (!pMatchResult)
		return false;

	if (!pMatchResult->getInscription())
		return false;

	if(pMatchResult->getMatchStatus() < CHMemoryDataBase::eFinished)
		return false;
	

	CHMatchResult * pMatchResultCol = (CHMatchResult *) col;
	CHMatch *pMatch = (CHMatch*)pMatchResultCol->getMatch();
	
	// Los submatches no los quiero
	/*if(pMatch->getSubMatch())
		return false;*/
	
	return (pMatchResultCol->getEvent()->getEvent() == pMatchResult->getEvent()->getEvent() &&
	        pMatchResultCol->getEvent()->getSex()   == pMatchResult->getEvent()->getSex()   &&
			pMatchResultCol->getInscription() == pMatchResult->getInscription());
}
RWBoolean finalsMatchResultsOfCompetition(const RWCollectable *col, const void *param)
{
	CHMatch * pMatch = (CHMatch *) param;
	if (!pMatch)
		return false;

	
	if(pMatch->getStatus() < CHMemoryDataBase::eFinished)
		return false;
	

	CHMatchResult  *pMatchResultCol		= (CHMatchResult *) col;
	CHMatch			*pMatchCol			= (CHMatch*)pMatchResultCol->getMatch();
	
	// Los submatches no los quiero
	/*if(pMatch->getSubMatch())
		return false;*/
	
	return (pMatch->getEvent()->getEvent() == pMatchCol->getEvent()->getEvent()  &&
	        pMatch->getEvent()->getSex()   == pMatchCol->getEvent()->getSex()    &&
			pMatch->getPool()			   == pMatchCol->getPool()				&&
			pMatch->getPhase()			   == pMatchCol->getPhase()				&&
			pMatch->getRound()			   == pMatchCol->getRound());
}

int orderMatchResultByMatchCode(const GVectorElement** a, const GVectorElement** b)
{
	CHMatchResult * pA=((CHMatchResult *)(*a)->getElement());
	CHMatchResult * pB=((CHMatchResult *)(*b)->getElement());

	return pA->getMatch()->getCode()-pB->getMatch()->getCode();
}

////////////////////////////////////////////////////////////////////////////////////
// class CHTieRankingPoolResult
////////////////////////////////////////////////////////////////////////////////////

CHTieRankingPoolResult::CHTieRankingPoolResult()
:CHPoolResult()
,matchesTie(0)
,pointsTie(0.0)
{

}

CHTieRankingPoolResult::CHTieRankingPoolResult(CHPoolResult *pPR)
:CHPoolResult(*pPR)
,matchesTie(0)
,pointsTie(0.0)
{

}

CHTieRankingPoolResult::CHTieRankingPoolResult(const CHTieRankingPoolResult & copy)
{
	operator = (copy);
}

CHTieRankingPoolResult::~CHTieRankingPoolResult()
{

}

CHTieRankingPoolResult & CHTieRankingPoolResult::operator = (const CHTieRankingPoolResult & copy)
{
	if( this != &copy )
	{
		CHPoolResult::operator = (copy);

		matchesTie		= copy.matchesTie;
		pointsTie		= copy.pointsTie;
	}

	return *this;
}

RWBoolean CHTieRankingPoolResult::operator == (const CHTieRankingPoolResult & copy)
{
	if( this == &copy )
		return true;

	if( !CHPoolResult::operator == (copy) )
		return false;

	return	matchesTie		== copy.matchesTie		&&
			pointsTie		== copy.pointsTie		;
}

RWBoolean CHTieRankingPoolResult::operator != (const CHTieRankingPoolResult & copy)
{
	return !operator == (copy);
}

void CHTieRankingPoolResult::setMatchesTie(const int aMatchesTie)
{
	matchesTie = aMatchesTie;
}

void CHTieRankingPoolResult::setPointsTie(const float aPointsTie)
{
	pointsTie = aPointsTie;
}

int CHTieRankingPoolResult::getMatchesTie() const
{
	return matchesTie;
}

float CHTieRankingPoolResult::getPointsTie() const
{
	return pointsTie;
}

////////////////////////////////////////////////////////////////////////////////////
// class CHRanking
////////////////////////////////////////////////////////////////////////////////////

extern CCHManagerApp theApp;

CHRanking::CHRanking()
{
	m_pMem = (CHMemoryDataBase *) ((APP *)AfxGetApp())->memG();

}

////////////////////////////////////////////////////////////////////////////////////
CHRanking::~CHRanking()
{
	setTieBreakPoolResult.clearAndDestroy();
}

////////////////////////////////////////////////////////////////////////////////////
void CHRanking::calculateRankings(CHMatch* pMatch)
{
	// Asignamos puntos
	assignPointsMatchResult(pMatch);

	// Ranking de match
	calculateRankingsMatch(pMatch); 

	CHMatch *pOldMat = 0;//Debo calcular los puntos, rankings, etc del principal si ha terminado
	if(pMatch->getSubMatch())
	{
		CHMatch *pParMat = (CHMatch *)pMatch->getParentMatch();
		if (pParMat->getStatus()== CHMemoryDataBase::eFinished)
		{
			pOldMat = pMatch;
			pMatch	= pParMat;
			// Asignamos puntos
			assignPointsMatchResult(pMatch);
			// Ranking de match
			calculateRankingsMatch(pMatch); 
		}
	}
	// Con los subpartidos no tengo que calcular puntos, ni rankings de pool, etc
	if(!pMatch->getSubMatch())
	{
		// Matches played, matches won, matches drawn, matches lost
		calculateMatchesParameter(pMatch);

		// Points, Solkoff, Sonneberger, Progressive
		calculateSpecialPointsPool(pMatch);

		// Ranking de pool
		calculateRankingsPool((CHPool*)pMatch->getPool());

		// Ranking de fase
		calculateRankingsPhase((CHPhase*)pMatch->getPhase());

		// Ranking de evento
		calculateRankingsEvent((CHEvent*)pMatch->getEvent());
	}

	if (pOldMat)
		pMatch	= pOldMat;

	CHEvent *pEvent = (CHEvent*)pMatch->getEvent();
	if (!pEvent)
		return;
	if(pEvent->getStatus()>CHMemoryDataBase::eUnofficial)
		calculateFinalRatings(pMatch);

	

}

////////////////////////////////////////////////////////////////////////////////////
void CHRanking::assignPointsMatchResult(CHMatch* pMatch)
{
	CHMatchResult *pHome = pMatch->getMatchResultHome();
	CHMatchResult *pAway = pMatch->getMatchResultAway();
	if (!pHome || !pAway || pMatch->getStatus() < CHMemoryDataBase::eUnofficial)
		return;

	if (pHome->getPoints() > pAway->getPoints()) // Gana Home
		HomeWin_AwayLoss(pHome,pAway);
	else
	if (pHome->getPoints() < pAway->getPoints()) // Gana Away
		HomeLoss_AwayWin(pHome,pAway);
	else if(!pMatch->isBye())// Empate 
		HomeAwayDraw(pHome,pAway); // Empate
	
	
	sendToDB(pHome);
	sendToDB(pAway);
}

////////////////////////////////////////////////////////////////////////////////////
void CHRanking::HomeWin_AwayLoss(CHMatchResult *pHome,CHMatchResult *pAway)
{
	CHEvent* pEvent = (CHEvent*) pAway->getEvent();

	if (pAway->getBye())
		pHome->setPoints(pEvent->getPointsBye());
	else
		pHome->setPoints(WIN_POINTS);
	
	pAway->setPoints(LOST_POINTS);
}

////////////////////////////////////////////////////////////////////////////////////
void CHRanking::HomeLoss_AwayWin(CHMatchResult *pHome,CHMatchResult *pAway)
{
	CHEvent* pEvent = (CHEvent*) pAway->getEvent();

	pHome->setPoints(LOST_POINTS);

	if (pHome->getBye())
		pAway->setPoints(pEvent->getPointsBye());
	else
		pAway->setPoints(WIN_POINTS);
}

////////////////////////////////////////////////////////////////////////////////////
void CHRanking::HomeAwayDraw(CHMatchResult *pHome,CHMatchResult *pAway)
{
	pHome->setPoints(DRAW_POINTS);
	pAway->setPoints(DRAW_POINTS);
}

////////////////////////////////////////////////////////////////////////////////////
void CHRanking::calculateRankingsMatch(CHMatch* pMatch)
{
	CHMatchResult *pHome = pMatch->getMatchResultHome();
	CHMatchResult *pAway = pMatch->getMatchResultAway();
	if (!pHome || !pAway || pMatch->getStatus() < CHMemoryDataBase::eUnofficial)
		return;

	if (pHome->getQualitative() &&
		(pHome->getQualitativeCode() != NULLRWSTRING && pHome->getQualitativeCode() != OK))
	{
		pHome->setRanking(2);
		pHome->setRankingPosition(2);
		pAway->setRanking(1);
		pAway->setRankingPosition(1);
	}
	else
	if (pAway->getQualitative() &&
		(pAway->getQualitativeCode() != NULLRWSTRING  && pAway->getQualitativeCode() != OK))
	{
		pHome->setRanking(1);
		pHome->setRankingPosition(1);
		pAway->setRanking(2);
		pAway->setRankingPosition(2);
	}
	else
	if (pHome->getPoints() > pAway->getPoints())
	{
		pHome->setRanking(1);
		pHome->setRankingPosition(1);
		pAway->setRanking(2);
		pAway->setRankingPosition(2);
	}
	else
	if (pHome->getPoints() < pAway->getPoints())
	{
		pHome->setRanking(2);
		pHome->setRankingPosition(2);
		pAway->setRanking(1);
		pAway->setRankingPosition(1);
	}
	else // empate
	{
		pHome->setRanking(1);
		pHome->setRankingPosition(1);
		pAway->setRanking(1);
		pAway->setRankingPosition(2);
	}

	sendToDB(pHome);
	sendToDB(pAway);
}

////////////////////////////////////////////////////////////////////////////////////
void CHRanking::calculateRankingsPool(CHPool* pPool)
{
	short rank=1;
	short rankPo=1;
	CHPoolResult *pPR=0;
	CHEventResult *pER=0;
	CHTieRankingPoolResult *pTiePR=0;
	CHTieRankingPoolResult *pTiePRPrev=0;
	
	// Limpiamos los rankings
	APP::out(TRN_CHANGE_POOLRES);
	for(size_t i=0 ; i<pPool->getPoolResultsVector().entries() ; i++)
	{
		pPR = (CHPoolResult *)pPool->getPoolResultsVector()[i]->getElement();
		if(pPR->getRank()!=0 || pPR->getRankPo()!=0)
		{
			pPR->setRank(0); pPR->setRankPo(0);
			APP::out(*pPR,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
		}
	}
	

	// Crea un vector ordenado calculando los empates entre equipos
	tieBreakPool(pPool);

	CHEvent *pEvent=(CHEvent*)pPool->getEvent();

	for(i=0 ; i<vTieBreakPoolResult.entries() ; i++)
	{
		pTiePR = (CHTieRankingPoolResult *) vTieBreakPoolResult[i]->getElement();
		if (i==0) pTiePRPrev = pTiePR;
		if (!pTiePR )
			continue;

		pPR = (CHPoolResult *) m_pMem->findPoolResult(*pTiePR);
		if (!pPR)
			continue;

		pER = (CHEventResult *)pPR->getEventResult();
		if (!pER)
			continue;
	
		//////////////////////////
		// Ranking de Pool CHESS//
		//////////////////////////

		// 0) Incidencias
		// 1) Puntos totales
		// 2) Solkoff
		// 3) SonneBerger
		// 4) ProgressiveScore
		// 5) Rating
		// 6) Team Matches Won
		// 7) Matches Won
		// 8) Matches Drawn
		// 9) Points for Won Matches (Team)
				
		if((pEvent->findRankOrder(CHEvent::eQualitative) && pER->getQualitative())																	||	// 0
		   (pEvent->findRankOrder(CHEvent::ePoints) && pTiePRPrev->getPointsF() != pTiePR->getPointsF())											||	// 1
		   (pEvent->findRankOrder(CHEvent::eMedianSolkoff) && pTiePRPrev->getMMedianSolkoff() != pTiePR->getMMedianSolkoff())											||	// 2
		   (pEvent->findRankOrder(CHEvent::eSolkoff) && pTiePRPrev->getMSolkoff() != pTiePR->getMSolkoff())											||	// 5
		   (pEvent->findRankOrder(CHEvent::eSonneBerger) && pTiePRPrev->getMSonneBerger() != pTiePR->getMSonneBerger())								||	// 4
		   (pEvent->findRankOrder(CHEvent::eProgressiveScore) && pTiePRPrev->getMProgressiveScore() != pTiePR->getMProgressiveScore())				||	// 6
		   (pEvent->findRankOrder(CHEvent::eRating) && pTiePRPrev->getInscriptionSeed() != pTiePR->getInscriptionSeed())							||	// 7
		   (pEvent->isTeam() && pEvent->findRankOrder(CHEvent::eTeamMatchesWon) && pTiePRPrev->getTeamMatchesWon() != pTiePR->getTeamMatchesWon())	||  // 8
		   (pEvent->findRankOrder(CHEvent::eMatchesWon) && pTiePRPrev->getMWon() != pTiePR->getMWon())												||	// 9
		   (pEvent->findRankOrder(CHEvent::eMatchesDrawm) && pTiePRPrev->getMDrawn() != pTiePR->getMDrawn())										||  // 10
		   (pEvent->findRankOrder(CHEvent::eTeamPointsWon) && pTiePRPrev->getPointsForWon() != pTiePR->getPointsForWon()))								// 11)								
		   
		   
		{
			rank = short(i+1);
			rankPo = rank;
		}

		if(pPR->getQualitativeCode()!=OK)
		{
			pPR->setRank(0);
			pPR->setRankPo(0);
			APP::out(*pPR,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
		}
		else if(pPR->getRank()!=rank || pPR->getRankPo()!=short(i+1))
		{
			pPR->setRank(rank);
			pPR->setRankPo(short(i+1));
			APP::out(*pPR,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
		}

		pTiePRPrev = pTiePR;
	}

	APP::out();
}

////////////////////////////////////////////////////////////////////////////////////
void CHRanking::tieBreakPool(CHPool *pPool)
{
	vTieBreakPoolResult.clearAndDestroy();
	setTieBreakPoolResult.clearAndDestroy();

	GSortedVector vPoolResults = pPool->getPoolResultsVector();
	vPoolResults.sort(orderPRByRanking);

	CHPoolResult *pPR=0;
	CHTieRankingPoolResult *pTiePR=0;
	for(size_t i=0 ; i<vPoolResults.entries() ; i++)
	{
		pPR = (CHPoolResult *)vPoolResults[i]->getElement();
		if (!pPR)
			continue;

		pTiePR = new CHTieRankingPoolResult(pPR);
		if (!pTiePR)
			continue;

		calculateTieValues(pTiePR);
		setTieBreakPoolResult.insert(pTiePR);
	}

	vTieBreakPoolResult.setVector(setTieBreakPoolResult,orderPRByTieRankingOlympic);
}

////////////////////////////////////////////////////////////////////////////////////
void CHRanking::calculateTieValues(CHTieRankingPoolResult* pTiePR)
{
	CHPool *pPool = (CHPool *)pTiePR->getPool();
	if (!pPool)
		return;

	CHEvent *pEvent=(CHEvent*)pPool->getEvent();

	// Construimos un vector con los pool results empatados con pTiePR
	GSortedVector vAuxTieValues;
	GSortedVector vCopyPoolResults = pPool->getPoolResultsVector();
	vCopyPoolResults.sort(orderPRByRanking);	

		
	CHPoolResult *pPR=0;
	CHEventResult *pER=0;
	for(size_t i=0 ; i<vCopyPoolResults.entries() ; i++)
	{
		pPR = (CHPoolResult *)vCopyPoolResults[i]->getElement();
		if (!pPR)
			continue;

		pER = (CHEventResult *)pPR->getEventResult();
		if (!pER)
			continue;
		
		if((pEvent->findRankOrder(CHEvent::eQualitative) && !pER->getQualitative())								&&
		   (pEvent->findRankOrder(CHEvent::ePoints) && pTiePR->getPointsF() == pPR->getPointsF())				&&
		   //(pEvent->findRankOrder(CHEvent::eMatchesWon) && pTiePR->getMWon() == pPR->getMWon())					&&
		   (pEvent->findRankOrder(CHEvent::eTeamPointsWon) && pTiePR->getPointsForWon() == pPR->getPointsForWon()))
			vAuxTieValues.insert(pPR);

		
	}

	if (vAuxTieValues.entries() < 2)
		return;

	// Calculamos los puntos de los partidos de los pool results empatados
	CHMatch *pMatch=0;
	CHMatchResult *pHome=0;
	CHMatchResult *pAway=0;
	float points=0.0;
	CHTieRankingPoolResult *pTiePRFindHome=0;
	CHTieRankingPoolResult *pTiePRFindAway=0;
	for(size_t j=0 ; j<pPool->getMatchsVector().entries() ; j++)
	{
		pMatch = (CHMatch *)pPool->getMatchsVector()[j]->getElement();
		if (!pMatch)
			continue;

		pHome = pMatch->getMatchResultHome();
		pAway = pMatch->getMatchResultAway();
		if (!pHome || !pAway)
			continue;

		pTiePRFindHome = findTie(vAuxTieValues,pHome->getInscription());
		pTiePRFindAway = findTie(vAuxTieValues,pAway->getInscription());
		if (!pTiePRFindHome || !pTiePRFindAway)
			continue;

		if (pTiePR->getInscription() == pTiePRFindHome->getInscription())
		{
			points += pHome->getPoints();
			
		}

		if (pTiePR->getInscription() == pTiePRFindAway->getInscription())
		{
			points += pAway->getPoints();
			
		}
	}

	pTiePR->setPointsTie(points);
	
}

////////////////////////////////////////////////////////////////////////////////////
CHTieRankingPoolResult * CHRanking::findTie(GSortedVector &vAuxTieValues,GInscription *pIns)
{
	CHTieRankingPoolResult *pTiePR=0;
	for(size_t i=0 ; i<vAuxTieValues.entries() ; i++)
	{
		pTiePR = (CHTieRankingPoolResult *)vAuxTieValues[i]->getElement();
		if (pTiePR && pTiePR->getInscription() == pIns)
			return pTiePR;
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////
void CHRanking::calculateRankingsPhase(CHPhase *pPhase)
{
	if (!pPhase || pPhase->getStatus() < CHMemoryDataBase::eUnofficial)
		return;
	
	// Construimos un vector con todos los pool results de la phase
	size_t i=0, j=0;
	CHPool *pPool=0;
	CHPoolResult *pPR=0;
	GSortedVector vPoolResults;
	for(i=0 ; i<pPhase->getPoolsVector().entries() ; i++)
	{
		pPool = (CHPool *)pPhase->getPoolsVector()[i]->getElement();
		if (!pPool)
			continue;

		for(j=0 ; j<pPool->getPoolResultsVector().entries() ; j++)
		{
			pPR = (CHPoolResult *)pPool->getPoolResultsVector()[j]->getElement();
			if (!pPR)
				continue;
			vPoolResults.insert(pPR);
		}
	}

	// Calculamos los partidos, puntos y goles totales en la phase
	CHMatch *pMatch=0;
	RWSet setTieRankingPhase;
	CHMatchResult *pHome=0, *pAway=0;
	CHTieRankingPoolResult *pTiePR=0;
	GSortedVector vMatches = GSortedVector(m_pMem->getColMatchs(),0);
	for(i=0 ; i<vPoolResults.entries() ; i++)
	{
		pPR = (CHPoolResult *)vPoolResults[i]->getElement();
		if (!pPR)
			continue;

		pTiePR = new CHTieRankingPoolResult(pPR);
		if (!pTiePR)
			continue;

		for(j=0 ; j<vMatches.entries() ; j++)
		{
			pMatch = (CHMatch *)vMatches[j]->getElement();
			if (!pMatch || pMatch->getStatus() < CHMemoryDataBase::eUnofficial)
				continue;

			if (pPR->getPhase() != pMatch->getPhase())
				continue;

			pHome = pMatch->getMatchResultHome();
			if (pHome && pHome->getInscription() == pPR->getInscription())
			{
				pTiePR->setMatchesTie(pTiePR->getMatchesTie()+1);
				pTiePR->setPointsTie(pTiePR->getPointsTie()+pHome->getPoints());
				
			}

			pAway = pMatch->getMatchResultAway();
			if (pAway && pAway->getInscription() == pPR->getInscription())
			{
				pTiePR->setMatchesTie(pTiePR->getMatchesTie()+1);
				pTiePR->setPointsTie(pTiePR->getPointsTie()+pAway->getPoints());
				
			}
		}

		setTieRankingPhase.insert(pTiePR);
	}

	// Se ordenan por ranking de phase
	GSortedVector vTieRankingPhase = GSortedVector(setTieRankingPhase,orderTieRankingPhase);

	APP::out(TRN_CHANGE_POOLRES);

	short ranking=1;
	
	CHEventResult *pER=0;
	CHTieRankingPoolResult *pTiePRPrev=0;
	for(i=0 ; i<vTieRankingPhase.entries() ; i++)
	{
		pTiePR = (CHTieRankingPoolResult *) vTieRankingPhase[i]->getElement();
		if (i==0) pTiePRPrev = pTiePR;
		if (!pTiePR )
			continue;

		pPR = (CHPoolResult *) m_pMem->findPoolResult(*pTiePR);
		if (!pPR)
			continue;

		pER = (CHEventResult *)pPR->getEventResult();
		if (!pER)
			continue;
		
		//////////////////////
		// Ranking de Phase //
		//////////////////////

		// 0) Incidencias
		// 1) Solkoff
		// 2) SonneBerger
		// 3) Progressive Score
		// 4) Rating
		// 5) Ex aequo (empatados)

		if(pER->getQualitative()												||	// 0
		   pTiePRPrev->getMSolkoff() != pTiePR->getMSolkoff()					||	// 1
		   pTiePRPrev->getMSonneBerger() != pTiePR->getMSonneBerger()			||	// 2
		   pTiePRPrev->getMProgressiveScore() != pTiePR->getMProgressiveScore()	||	// 3
		   pTiePRPrev->getInscriptionRating() != pTiePR->getInscriptionRating())	// 4
		   
			ranking = short(i+1);

		if (pPR->getQualitativeCode()!=OK)
		{
			pPR->setPhaseRank(0);
			pPR->setPhaseRankPo(0);
			APP::out(*pPR,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);		
		}
		else if (pPR->getPhaseRank() != ranking || pPR->getPhaseRankPo() != short(i+1))
		{
			pPR->setPhaseRank(ranking);
			pPR->setPhaseRankPo(short(i+1));
			APP::out(*pPR,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
		}

		pTiePRPrev = pTiePR;
	}

	APP::out();
	setTieRankingPhase.clearAndDestroy();
}

////////////////////////////////////////////////////////////////////////////////////
void CHRanking::calculateRankingsEvent(CHEvent *pEvent)
{
	if (!pEvent)
		return;

	if (pEvent->getStatus()!=CHMemoryDataBase::eFinished)
		return;

	// Construimos un vector de match results ordenados por el orden de la phase
	RWSet *colMatchResults = (RWSet *)m_pMem->getColMatchResults().select(selectMatchResultsOfEvent,pEvent);
	GSortedVector vMatchResults = GSortedVector(*colMatchResults,orderMRByPhaseOrder);
	delete colMatchResults;	

	// Construimos un vector en el que guardamos el ultimo partido jugado por cada equipo
	CHInscription *pInscription=0;
	CHMatchResult *pMatchResult=0;
	GSortedVector vMResultsWithRankingPo;
	RWSetIterator it(m_pMem->getColInscriptions());
	while((pInscription=(CHInscription *)it())!=0)
	{
		if (pInscription->getEvent() == pEvent)
		{
			pMatchResult = findLastMatchResult((CHRegister*)pInscription->getRegister(),vMatchResults);
			if (pMatchResult)
				vMResultsWithRankingPo.insert(pMatchResult);
		}
	}
	
	//////////////////////
	// Ranking de Event //
	//////////////////////

	// 0) Incidencias
	// 1) Loser Rank de fases
	// 2) Ranking de phase
	// 3) Ranking de pool

	vMResultsWithRankingPo.sort(orderMRByRankingEvent);

	APP::out(TRN_CHANGE_EVENT_RESULT);

	CHEventResult *pEventResult=0;
	for(size_t i=0 ; i<vMResultsWithRankingPo.entries() ; i++)
	{
		pMatchResult = (CHMatchResult *)vMResultsWithRankingPo[i]->getElement();
		if (!pMatchResult)
			continue;

		pEventResult = (CHEventResult *)pMatchResult->getEventResult();
		if (!pEventResult)
			continue;

		if (pEventResult->getQualitativeCode()!=OK)
		{
			pEventResult->setRank(0);
			pEventResult->setRankPo(0);
			APP::out(*pEventResult,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);		
		}
		else if (pEventResult->getRank() != short(i+1))
		{
			pEventResult->setRank(short(i+1));
			pEventResult->setRankPo(short(i+1));
			APP::out(*pEventResult,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
		}
	}

	APP::out();
}

////////////////////////////////////////////////////////////////////////////////////
CHMatchResult* CHRanking::findLastMatchResult(CHRegister* pRegister,GSortedVector& vMatchResults)
{
	if (!pRegister)
		return 0;

	CHMatchResult* pMatchResult=0;
	for (size_t i=vMatchResults.entries() ; i>0 ; i--)
	{
		pMatchResult=(CHMatchResult *)vMatchResults[i-1]->getElement();
		if (pMatchResult && ((CHRegister*)pMatchResult->getRegister())==pRegister)
			return pMatchResult;
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////
void CHRanking::calculateMedals(CHMatch* pMatch, CHEvent* pEvent)
{
	// Finished y Revision
	if(pEvent->getStatus()>=CHMemoryDataBase::eFinished)
	{
		// Borramos los medallistas actuales
		destroyAllMedals(pEvent);

		// Buscamos el MatchResult de GOLD
		CHEventResult * pMRGold   = findRankEventResult(pEvent,1);
		if( pMRGold )
			setMedallist(pMatch,pMRGold,GMedallist::GOLD);

		// Buscamos el MatchResult de SILVER
		CHEventResult * pMRSilver = findRankEventResult(pEvent,2);
		if( pMRSilver )
			setMedallist(pMatch,pMRSilver,GMedallist::SILVER);

		// Buscamos el MatchResult de BRONZE
		CHEventResult * pMRBronze = findRankEventResult(pEvent,3);
		if( pMRBronze )
			setMedallist(pMatch,pMRBronze,GMedallist::BRONZE);
	}
}

////////////////////////////////////////////////////////////////////////////////////
void CHRanking::destroyAllMedals(CHEvent* pEvent)
{
	// Borramos los medallistas actuales
	APP::out(TRN_REMOVE_MEDALLIST);

	RWSet sTarget;
	m_pMem->getMedallist(sTarget,*pEvent);
	RWSetIterator it(sTarget);

	GMedallist *pMedallist=0;
	while((pMedallist=(GMedallist *)it())!=0)
	{
		APP::out(*pMedallist,OP_DELETE,TO_VENUE|TO_DATABASE);
		m_pMem->removeMedallist(*pMedallist);
	}

	APP::out();
}

////////////////////////////////////////////////////////////////////////////////////
CHMatchResult * CHRanking::findRankMatchResult(CHEvent * pEvent,RWCString phase,short ranking)
{
	CHPhase * pPhase = (CHPhase *)m_pMem->findPhase(pEvent,phase);
	if( !pPhase )
		return 0;

	CHPool * pPool = (CHPool *)pPhase->getPool(0);
	if( !pPool )
		return 0;

	CHMatch * pMatch = (CHMatch *)pPool->getMatch(0);
	if( !pMatch )
		return 0;

	CHMatchResult * pMatchResult = 0;
	for(size_t i=0 ; i<pMatch->getCompetitorsVector().entries() ; i++)
	{
		pMatchResult = (CHMatchResult *)pMatch->getCompetitorsVector()[i]->getElement();
		if( pMatchResult && pMatchResult->getRankingPosition() == ranking )
			return pMatchResult;
	}

	return 0;
}
////////////////////////////////////////////////////////////////////////////////////
CHEventResult * CHRanking::findRankEventResult(CHEvent * pEvent,short ranking)
{
	CHEventResult * pEventResult = 0;
	RWSetIterator it(m_pMem->getColEventResult());
	while( (pEventResult=(CHEventResult *)it()) != 0 )
	{
		if( pEvent == pEventResult->getEvent() )
		{
			if( pEventResult && pEventResult->getRankPo() == ranking )
				return pEventResult;
		}
	}

	return 0;
}


////////////////////////////////////////////////////////////////////////////////////
void CHRanking::setMedallist(CHMatch* pMatch, CHEventResult * pEventResult,short medal)
{
	GMedal * pMedal = m_pMem->findMedal(char(medal));
	if( !pMedal )
		return;

	GMedallist aMedallist(pEventResult->getEvent(),pEventResult->getRegister(),pMedal,"");
	if( pMatch &&
		pMatch->getStartDate().isValid())
		 aMedallist.setDate(pMatch->getStartDate());
	else if (pMatch) 
		aMedallist.setDate(getDateMatch(pMatch));
	
	GMedallist * pMedallist = m_pMem->setMedallist(aMedallist);
	if (pMedallist)
	{
		APP::out(TRN_NEW_MEDALS);
		APP::out(*pMedallist,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
		APP::out();
	}
}

////////////////////////////////////////////////////////////////////////////////////
void CHRanking::sendToDB(CHMatchResult * pMatchResult)
{
	APP::out(TRN_CHANGE_MATCHRES);
	APP::out(*pMatchResult,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
	APP::out();
}

void CHRanking::calculateMatchesParameter(CHMatch* pMatch)
{
	CHMatchResult *pMatchResult1=pMatch->getMatchResultHome();
	CHMatchResult *pMatchResult2=pMatch->getMatchResultAway();

	calculateMatchParameter(pMatchResult1);
	calculateMatchParameter(pMatchResult2);
}
void CHRanking::calculateMatchParameter(CHMatchResult *pMatchResult)
{
	CHPoolResult *pPoolResult=(CHPoolResult*)pMatchResult->getPoolResult();
	if(pPoolResult)
	{
		// Matches Played
		pPoolResult->setMPlayed(pPoolResult->getMatchesPlayed());
		// Matches Won
		pPoolResult->setMWon(pPoolResult->getMatchesWon());
		// Matches Drawn
		pPoolResult->setMDrawn(pPoolResult->getMatchesDrawn());
		// Matches Lost
		pPoolResult->setMLost(pPoolResult->getMatchesLost());
		
		theApp.queueOut(pPoolResult);
		theApp.out(TRN_CHANGE_POOLRES);
		
	}
}
void CHRanking::reCalculateSpecialPointsPool(CHMatch* pMatch)
{
	
	GSortedVector vMatchesRound=pMatch->getRoundMatches();

	CHMatch* pMatchAux=0;

	CHMatch* pMatchOld=pMatch;
	for (size_t i=0;i<vMatchesRound.entries();i++)
	{
		pMatchAux = (CHMatch*) vMatchesRound[i]->getElement();

		// El del partido current ya se ha calculado, ahora le toca al resto
		if(pMatchAux!=pMatch)
		{
			// Solkoff= Suma de los puntos de los oponentes 
			if(usedToCalculate((CHEvent*)pMatch->getEvent(),CHEvent::eSolkoff))
				calculateSolkoffs(pMatchAux);

			// MedianSolkoff= Suma de los puntos de los oponentes menos el primero y ultimo
			if(usedToCalculate((CHEvent*)pMatch->getEvent(),CHEvent::eMedianSolkoff))
				calculateMedianSolkoffs(pMatchAux);

			// SonneBerger= Suma de los oponentes contra los que ha ganado + 
			//              mitad de los puntos de los oponentes contra los que ha empatado
			if(usedToCalculate((CHEvent*)pMatch->getEvent(),CHEvent::eSonneBerger))
				calculateSonneBergers(pMatchAux);

			// ProgressiveScore= Suma de las puntuaciones progresivas obtenidas
			if(usedToCalculate((CHEvent*)pMatch->getEvent(),CHEvent::eProgressiveScore))
				calculateProgressiveScores(pMatchAux);
		}
	}
	pMatch=pMatchOld;
	
}
void CHRanking::calculateSpecialPointsPool(CHMatch* pMatch)
{
	// Points 
	if(usedToCalculate((CHEvent*)pMatch->getEvent(),CHEvent::ePoints))
		calculatePoints(pMatch);

	// Solkoff= Suma de los puntos de los oponentes 
	if(usedToCalculate((CHEvent*)pMatch->getEvent(),CHEvent::eSolkoff))
		calculateSolkoffs(pMatch);

	// Solkoff= Suma de los puntos de los oponentes menos el primero y ultimo
	if(usedToCalculate((CHEvent*)pMatch->getEvent(),CHEvent::eMedianSolkoff))
		calculateMedianSolkoffs(pMatch);


	// SonneBerger= Suma de los oponentes contra los que ha ganado + 
	//              mitad de los puntos de los oponentes contra los que ha empatado
	if(usedToCalculate((CHEvent*)pMatch->getEvent(),CHEvent::eSonneBerger))
		calculateSonneBergers(pMatch);

	// ProgressiveScore= Suma de las puntuaciones progresivas obtenidas
	if(usedToCalculate((CHEvent*)pMatch->getEvent(),CHEvent::eProgressiveScore))
		calculateProgressiveScores(pMatch);
}

void CHRanking::calculatePoints(CHMatch *pMatch)
{
	CHMatchResult *pMatchResult1=pMatch->getMatchResultHome();
	CHMatchResult *pMatchResult2=pMatch->getMatchResultAway();

	calculatePoint(pMatchResult1);
	calculatePoint(pMatchResult2);

}
void CHRanking::calculatePoint(CHMatchResult *pMatchResult)
{
	RWSet *colMatchResults = (RWSet *) CHMemoryDataBase::getColMatchResults().select
					(matchResultsOfCompetition,pMatchResult);

	GSortedVector vMatchResults(*colMatchResults,orderMatchResultByMatchCode);
	CHPoolResult *pPoolResultVersus=0;
	CHMatchResult *pSelMR=0,*pMatchResultVersus=0;
	
	float points=0.0;
	for( size_t i=0; i<vMatchResults.entries(); i++ )
	{
		pSelMR = (CHMatchResult *)vMatchResults[i]->getElement();
		
		CHMatch *pMatch=(CHMatch*)pSelMR->getMatch();
		if(pMatch->isTeam() && !pMatch->getSubMatch())
			continue;

		if(pSelMR)
			points+=pSelMR->getPoints();
		
	}
	CHPoolResult *pPoolResult=(CHPoolResult*)pMatchResult->getPoolResult();
	if(pPoolResult)
	{
		pPoolResult->setPointsF(points);
		theApp.queueOut(pPoolResult);
		theApp.out(TRN_CHANGE_POOLRES);
	}
		
	delete colMatchResults;

}
void CHRanking::calculateSolkoffs(CHMatch *pMatch)
{
	CHMatchResult *pMatchResult1=pMatch->getMatchResultHome();
	CHMatchResult *pMatchResult2=pMatch->getMatchResultAway();

	calculateSolkoff(pMatchResult1);
	calculateSolkoff(pMatchResult2);

}
void CHRanking::calculateMedianSolkoffs(CHMatch *pMatch)
{
	CHMatchResult *pMatchResult1=pMatch->getMatchResultHome();
	CHMatchResult *pMatchResult2=pMatch->getMatchResultAway();

	calculateMedianSolkoff(pMatchResult1);
	calculateMedianSolkoff(pMatchResult2);

}

void CHRanking::calculateSolkoff(CHMatchResult *pMatchResult)
{
	CHPool *pPool = (CHPool *) pMatchResult->getPool();
	if (!pPool)
		return;

	CHEvent* pEvent = (CHEvent*)pPool->getEvent();
	if (!pEvent)
		return;

	CHDiscipline &discipline = ((CHDiscipline &)CHMemoryDataBase::getDiscipline());
	short nRoundsPlayed = pPool->getNumRoundsPlayed(); 

	RWSet *colMatchResults = (RWSet *) CHMemoryDataBase::getColMatchResults().select
					(matchResultsOfCompetition,pMatchResult);

	GSortedVector vMatchResults(*colMatchResults,orderMatchResultByMatchCode);
	CHPoolResult *pPoolResultVersus=0,*pPoolResult=0;
	CHMatchResult *pSelMR=0,*pMatchResultVersus=0;
	float pointsSolkoff=0.0;
	for( size_t i=0; i<vMatchResults.entries(); i++ )
	{
		pSelMR = (CHMatchResult *)vMatchResults[i]->getElement();

		CHMatch *pMatch=(CHMatch*)pSelMR->getMatch();
		if(pMatch->isTeam() && pMatch->getSubMatch())
			continue;

		pPoolResult=(CHPoolResult*)pSelMR->getPoolResult();
		if(pSelMR && pSelMR->getMatchStatus()>=CHMemoryDataBase::eFinished)
		{
			pMatchResultVersus=pSelMR->getMatchResultVersus();
			pPoolResultVersus=(CHPoolResult*)pMatchResultVersus->getPoolResult();
			if(pPoolResultVersus)
				pointsSolkoff+=pPoolResultVersus->getPointsSO();				
			else if (pMatchResultVersus->getBye())
				pointsSolkoff+=0.5*pEvent->getTeamMatches()*nRoundsPlayed;
		}
	
	}
	pPoolResult=(CHPoolResult*)pMatchResult->getPoolResult();
	if(pPoolResult)
	{
		pPoolResult->setMSolkoff(pointsSolkoff);
		theApp.queueOut(pPoolResult);
		theApp.out(TRN_CHANGE_POOLRES);
		
	}
		
	delete colMatchResults;

}

void CHRanking::calculateMedianSolkoff(CHMatchResult *pMatchResult)
{
	CHPool *pPool = (CHPool *) pMatchResult->getPool();
	if (!pPool)
		return;


	CHEvent *pEvent = (CHEvent *) pPool->getEvent();
	if (!pEvent)
		return;


	CHDiscipline &discipline = ((CHDiscipline &)CHMemoryDataBase::getDiscipline());
	short nRoundsPlayed = pPool->getNumRoundsPlayed(); 

	RWSet *colMatchResults = (RWSet *) CHMemoryDataBase::getColMatchResults().select
					(matchResultsOfCompetition,pMatchResult);

	GSortedVector vMatchResults(*colMatchResults,orderMatchResultByMatchCode);
	CHPoolResult *pPoolResultVersus=0,*pPoolResult=0;
	CHMatchResult *pSelMR=0,*pMatchResultVersus=0;
	float pointsMedianSolkoff=0.0;
	RWBoolean hasBye=false;
	GSortedVector vPoolResults;
	for( size_t i=0; i<vMatchResults.entries(); i++ )
	{
		pSelMR = (CHMatchResult *)vMatchResults[i]->getElement();

		CHMatch *pMatch=(CHMatch*)pSelMR->getMatch();
		if(pMatch->isTeam() && pMatch->getSubMatch())
			continue;

		pPoolResult=(CHPoolResult*)pSelMR->getPoolResult();
		if(pSelMR && pSelMR->getMatchStatus()>=CHMemoryDataBase::eFinished)
		{
			pMatchResultVersus=pSelMR->getMatchResultVersus();
			pPoolResultVersus=(CHPoolResult*)pMatchResultVersus->getPoolResult();
			if(pPoolResultVersus)
				vPoolResults.insert(pPoolResultVersus);
			else if(pPoolResult && pMatchResultVersus->getBye())
				hasBye=true;
			
		}
	
	}

	pPoolResult=(CHPoolResult*)pMatchResult->getPoolResult();

	if (vPoolResults.entries()>1)
	{
		vPoolResults.sort(orderPoolResultSO);
	
		for (size_t i=1;i<vPoolResults.entries()-1;i++)
		{
			CHPoolResult* pPoolResult = (CHPoolResult*)vPoolResults[i]->getElement();
			pointsMedianSolkoff += float(pPoolResult->getPointsSO());
		}

		if (hasBye)
			pointsMedianSolkoff+=0.5*pEvent->getTeamMatches()*nRoundsPlayed;
	}

	if(pPoolResult)
	{
		pPoolResult->setMMedianSolkoff(pointsMedianSolkoff);
		theApp.queueOut(pPoolResult);
		theApp.out(TRN_CHANGE_POOLRES);
		
	}
		
	delete colMatchResults;

}

void CHRanking::calculateSonneBergers(CHMatch *pMatch)
{
	CHMatchResult *pMatchResult1=pMatch->getMatchResultHome();
	CHMatchResult *pMatchResult2=pMatch->getMatchResultAway();

	calculateSonneBerger(pMatchResult1);
	calculateSonneBerger(pMatchResult2);

}
void CHRanking::calculateSonneBerger(CHMatchResult *pMatchResult)
{
	RWSet *colMatchResults = (RWSet *) CHMemoryDataBase::getColMatchResults().select
					(matchResultsOfCompetition,pMatchResult);

	GSortedVector vMatchResults(*colMatchResults,orderMatchResultByMatchCode);
	CHPoolResult *pPoolResultVersus=0;
	CHMatchResult *pSelMR=0,*pMatchResultVersus=0;
	float pointsSonneBerger=0.0;
	for( size_t i=0; i<vMatchResults.entries(); i++ )
	{
		pSelMR = (CHMatchResult *)vMatchResults[i]->getElement();

		CHMatch *pMatch=(CHMatch*)pSelMR->getMatch();
		if(pMatch->isTeam() && !pMatch->getSubMatch())
			continue;
		if(pSelMR)
		{
			CHMatch *pMatchSel=(CHMatch*)pSelMR->getMatch();
			if(pMatchSel && pMatchSel->getStatus()>=CHMemoryDataBase::eFinished)
			{
				short winnerMatch=pMatchSel->getWinner();
				// Si es el ganador del partido le sumamos los puntos del contrario
				// Si ha habido tablas le sumamos los puntos del contrario dividido entre 2
				if((winnerMatch==CHMatch::eWinnerWhite && pSelMR==pMatchSel->getMatchResultHome())  ||
				   (winnerMatch==CHMatch::eWinnerBlack && pSelMR==pMatchSel->getMatchResultAway())	||
				   (winnerMatch==CHMatch::eDraw))
				{
					pMatchResultVersus=pSelMR->getMatchResultVersus();
					pPoolResultVersus=(CHPoolResult*)pMatchResultVersus->getPoolResult();
					if(pPoolResultVersus)
					{
						if(winnerMatch==CHMatch::eDraw)
							 pointsSonneBerger+=float(pPoolResultVersus->getPointsF()/float(2));
						else pointsSonneBerger+=pPoolResultVersus->getPointsF();
					}
				}
			}
			
		}
	
	}
	CHPoolResult *pPoolResult=(CHPoolResult*)pMatchResult->getPoolResult();
	if(pPoolResult)
	{
		pPoolResult->setMSonneBerger(pointsSonneBerger);
		theApp.queueOut(pPoolResult);
		theApp.out(TRN_CHANGE_POOLRES);
		
	}
		
	delete colMatchResults;

}
void CHRanking::calculateProgressiveScores(CHMatch *pMatch)
{
	CHMatchResult *pMatchResult1=pMatch->getMatchResultHome();
	CHMatchResult *pMatchResult2=pMatch->getMatchResultAway();

	calculateProgressiveScore(pMatchResult1);
	calculateProgressiveScore(pMatchResult2);

}
void CHRanking::calculateProgressiveScore(CHMatchResult *pMatchResult)
{
	RWSet *colMatchResults = (RWSet *) CHMemoryDataBase::getColMatchResults().select
					(matchResultsOfCompetition,pMatchResult);

	GSortedVector vMatchResults(*colMatchResults,orderMatchResultByMatchCode);
	CHPoolResult *pPoolResultVersus=0;
	CHMatchResult *pSelMR=0,*pMatchResultVersus=0;
	float pointsProgressiveScore=0.0;
	float pointsProgressiveScorePrv=0.0;
	for( size_t i=0; i<vMatchResults.entries(); i++ )
	{
		pSelMR = (CHMatchResult *)vMatchResults[i]->getElement();
		CHMatch *pMatch=(CHMatch*)pSelMR->getMatch();
		if(pMatch->isTeam() && !pMatch->getSubMatch())
			continue;
		if(pSelMR)
		{
			CHMatch *pMatchSel=(CHMatch*)pSelMR->getMatch();
			if(pMatchSel && pMatchSel->getStatus()>=CHMemoryDataBase::eFinished)
			{
				pointsProgressiveScore+=pSelMR->getPoints()+pointsProgressiveScorePrv;
				pointsProgressiveScorePrv+=pSelMR->getPoints();
				
				
			}
			
		}
	
	}
	CHPoolResult *pPoolResult=(CHPoolResult*)pMatchResult->getPoolResult();
	if(pPoolResult)
	{
		pPoolResult->setMProgressiveScore(pointsProgressiveScore);
		theApp.queueOut(pPoolResult);
		theApp.out(TRN_CHANGE_POOLRES);
		
	}
		
	delete colMatchResults;

}

RWBoolean CHRanking::usedToCalculate(CHEvent* pEvent, short type)
{
	for(short i=0;i<pEvent->getNumRankOrder();i++)
	{
	
		CHEvent::TypeRank typeRnk=pEvent->getRankOrder(i);
		switch(typeRnk)
		{
			case CHEvent::ePoints:
			case CHEvent::eSolkoff:
			case CHEvent::eMedianSolkoff:
			case CHEvent::eSonneBerger:
			case CHEvent::eProgressiveScore:
			{
				return true;
			}
				
		}

	}
	return false;

}
void CHRanking::calculateFinalRatings(CHMatch* pMatch)
{
	
	RWSet *colMatchResults = (RWSet *) CHMemoryDataBase::getColMatchResults().select
				(finalsMatchResultsOfCompetition,pMatch);

	
	GSortedVector vMatchResults(*colMatchResults,orderMatchResultByMatchCode);
		
	CHMatchResult *pSelMR=0;
		
	for( size_t i=0; i<vMatchResults.entries(); i++ )
	{
		pSelMR = (CHMatchResult *)vMatchResults[i]->getElement();
		calculateFinalRating(pSelMR);	
	}
	delete colMatchResults;
}
void CHRanking::calculateFinalRating(CHMatchResult *pMatchResult)
{
	CHInscription *pInscription=(CHInscription*)pMatchResult->getInscription();
	
	if(!pInscription || (pInscription && !pInscription->getRating()))
		return;


	RWSet *colMatchResults = (RWSet *) CHMemoryDataBase::getColMatchResults().select
				(matchResultsOfCompetition,pMatchResult);

	GSortedVector vMatchResults(*colMatchResults,orderMatchResultByMatchCode);
	
	// Rating Final = Rating Inicial + K*(W-We)
	// K= Constante depende del numero de partidos jugados
	// W= Puntos conseguidos en el torneo
	// ((Suma Ratings oponentes/Numero oponentes)=X)
	// Busco probabilidad de ganar a partir del numero X y obtenemos de las tablas CHRatingDif el numero Y
	// We = Y*numero de oponentes.
	CHPoolResult *pPoolResult=(CHPoolResult*)pMatchResult->getPoolResult();

	CHMatchResult *pSelMR=0,*pMatchResultVersus=0;
	short ratingsOpponents=0,nOponents=0;
	
	for( size_t i=0; i<vMatchResults.entries(); i++ )
	{
		pSelMR = (CHMatchResult *)vMatchResults[i]->getElement();
		CHMatch *pMatch=(CHMatch*)pSelMR->getMatch();
		if(pMatch->isTeam() && !pMatch->getSubMatch())
			continue;
		if(pSelMR)
		{
			CHMatch *pMatchSel=(CHMatch*)pSelMR->getMatch();
			if(pMatchSel && pMatchSel->getStatus()>=CHMemoryDataBase::eFinished)
			{
				pMatchResultVersus=pSelMR->getMatchResultVersus();
				CHInscription *pIncriptionAux=(CHInscription*)pMatchResultVersus->getInscription();
				if(pIncriptionAux)
				{
					ratingsOpponents+=pIncriptionAux->getRating();
					nOponents++;
				}
			}
		}
	}
	short averageRatings=0;
	if (nOponents)
		averageRatings=short(short(ratingsOpponents)/short(nOponents));
		
	short difRatingAndAverage=short(pInscription->getRating()-averageRatings);

	// Obtenemos con la diferencia de ratings la probabilidad de victoria de CHRankingDif
	float probability=getProbability(difRatingAndAverage);

	// Victorias esperadas
	float We=float(float(probability)*float(nOponents));

	if(pPoolResult)
	{
		// Victorias conseguidas
		float W=pPoolResult->getPointsF();
		
		// Rating Final = Rating Inicial + K*(W-We);
		short K=pInscription->getKConst(); 
		
		//int faltaBuscarComosePonelaK;
		short ratingFinal=short((pInscription->getRating())+short(K*(W-We)));

		CHEventResult *pEventResult=(CHEventResult*)CHMemoryDataBase::findEventResult(pInscription);
		if(pEventResult)
		{
			pEventResult->setRating(short(ratingFinal));
			theApp.queueOut(pEventResult);
			theApp.out(TRN_CHANGE_EVENT_RESULT);
		}
		
	}
		
	delete colMatchResults;
}

float CHRanking::getProbability(short difRatingAndAverage)
{
	// Obtengo a partir de la diferencia de ratings entre el del competidor - Media de ratings de oponentes
	// la probabilidad de ganar o perder, dependiendo de que la diferencia sea positiva o negativa
	RWSet& colRatingDifs=CHMemoryDataBase::getColRatingDifs();
	RWSetIterator it( colRatingDifs );
	CHRatingDif* pRatingDif=0;
	RWBoolean positive=false;
	if(difRatingAndAverage>0)
		positive=true;
	if(!positive)
		difRatingAndAverage=difRatingAndAverage*(-1);
	float probability=0.0;
	while( (pRatingDif=(CHRatingDif*)it())!=0 )
	{
		if(pRatingDif->getDifference()==difRatingAndAverage)
			return pRatingDif->getProbabilityCode(positive);

		if(pRatingDif->getDifference()>difRatingAndAverage)
			return probability;

		probability=pRatingDif->getProbabilityCode(positive);
	}

	return probability;
}
RWDate CHRanking::getDateMatch(CHMatch *pMatch)
{
	GSortedVector vMatchesRound=pMatch->getRoundMatches();
	CHMatch *pMatchAux=0;
	RWDate date;
	for(size_t i=0;i<vMatchesRound.entries();i++)
	{
		pMatchAux=(CHMatch*)vMatchesRound[i]->getElement();
		if(pMatchAux->getStartDate().isValid())
			return pMatchAux->getStartDate();
	}

	return date;
}