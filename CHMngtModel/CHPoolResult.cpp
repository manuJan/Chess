/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHPoolResult.cpp                                                                 
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
#include "CHPoolResult.h"
#include "CHEvent.h"
#include "CHPhase.h"
#include "CHPool.h"
#include "CHMatch.h"
#include "CHMatchResult.h"
#include "CHInscription.h"
#include "CHRegister.h"
#include "CHSportDefines.h"
#include "UCHPoolResult.h"
#include "QCHPoolResult.h"
#include <ovr/core/G/GBuffer.h>
#include <ovr/core/G/GScore.h>

int orderPoolResultSO(const MSLItem** a, const MSLItem** b)
{
	CHPoolResult * pPoolResultA = (CHPoolResult *) (*a);
	CHPoolResult * pPoolResultB = (CHPoolResult *) (*b);

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

int orderMatchesByRoundMatch(const MSLItem** a, const MSLItem** b)
{
	CHMatch * pA=(CHMatch *)(*a);
	CHMatch * pB=(CHMatch *)(*b);

	int order=pA->getRound() - pB->getRound();
	if(order)
		return order;

	return pA->getCode() - pB->getCode();
}

bool matchResultsOfPoolResult(const MSLItem * col, const void * param)
{
	CHPoolResult * pPoolResult = (CHPoolResult *) param;
	CHMatchResult  * pMatchResult = (CHMatchResult*) col;
	
	if (pMatchResult->getEvent() == pPoolResult->getEvent() &&
		pMatchResult->getRegister() &&
		pPoolResult &&
		pPoolResult->getRegister() &&
		pPoolResult->getRegister() == pMatchResult->getRegister())
		return true;

	return false;
}

MSLDEFINE_ITEM(CHPoolResult, __CHPOOLRESULT)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHPoolResult::CHPoolResult()
:GTHPoolResult()
,m_mPlayed(0)
,m_mWon(0)
,m_mLost(0)
,m_mDrawn(0)
,m_pointsF(0.0)
,m_mSolkoff(0.0)
,m_mMedianSolkoff(0.0)
,m_mSonneBerger(0.0)
,m_mProgressiveScore(0.0)
{
}

CHPoolResult::CHPoolResult(const CHPoolResult & copy)
{
	operator=(copy);
}

CHPoolResult::~CHPoolResult() 
{
}


//////////////////////////////////////////////////////////////////////
// Operators
//////////////////////////////////////////////////////////////////////
GData & CHPoolResult::operator =(const GData & copy)
{
	if (this != &copy)
	{
		GTHPoolResult::operator =(copy);

		CHPoolResult & aPoolResult = (CHPoolResult &)copy;

		m_mPlayed			= aPoolResult.m_mPlayed;
		m_mWon				= aPoolResult.m_mWon;
		m_mLost				= aPoolResult.m_mLost;
		m_mDrawn			= aPoolResult.m_mDrawn;
		m_pointsF			= aPoolResult.m_pointsF;
		m_mSolkoff			= aPoolResult.m_mSolkoff;
		m_mMedianSolkoff	= aPoolResult.m_mMedianSolkoff;
		m_mSonneBerger		= aPoolResult.m_mSonneBerger;
		m_mProgressiveScore	= aPoolResult.m_mProgressiveScore;
	}
	return * this;
}

bool CHPoolResult::operator ==(const GData & copy)
{
	if (this == &copy)
		return true;
	
	CHPoolResult & aPoolResult = (CHPoolResult &)copy;

	return (GTHPoolResult::operator ==(copy)						&&
			m_mPlayed			== aPoolResult.m_mPlayed			&&
			m_mWon				== aPoolResult.m_mWon				&&
			m_mLost				== aPoolResult.m_mLost				&&
			m_mDrawn			== aPoolResult.m_mDrawn				&&
			m_pointsF			== aPoolResult.m_pointsF			&&
			m_mSolkoff			== aPoolResult.m_mSolkoff			&&
			m_mMedianSolkoff	== aPoolResult.m_mMedianSolkoff		&&
			m_mSonneBerger		== aPoolResult.m_mSonneBerger		&&
			m_mProgressiveScore	== aPoolResult.m_mProgressiveScore);
}

bool CHPoolResult::operator !=(const GData & copy)
{
	return !operator==(copy);
}


//////////////////////////////////////////////////////////////////////
// From GData
//////////////////////////////////////////////////////////////////////

QBase* CHPoolResult::onQ() const
{
	return new QCHPoolResult();
}

UBase* 	CHPoolResult::onU() const
{
	return new UCHPoolResult();
}

MSLPack& CHPoolResult::pack(MSLPack& aPack) const
{
	GTHPoolResult::pack(aPack);
	
	aPack << m_mPlayed;
	aPack << m_mWon;
	aPack << m_mLost;
	aPack << m_mDrawn;
	aPack << m_pointsF;
	aPack << m_mSolkoff;	
	aPack << m_mMedianSolkoff;
	aPack << m_mSonneBerger;
	aPack << m_mProgressiveScore;

	return aPack;
}

MSLPack& CHPoolResult::unpack(MSLPack& aPack)
{
	GTHPoolResult::unpack(aPack);

	aPack >> m_mPlayed;
	aPack >> m_mWon;
	aPack >> m_mLost;
	aPack >> m_mDrawn;
	aPack >> m_pointsF;
	aPack >> m_mSolkoff;	
	aPack >> m_mMedianSolkoff;
	aPack >> m_mSonneBerger;
	aPack >> m_mProgressiveScore;

	return aPack;
}


//Set's
void CHPoolResult::setMPlayed(const short value)
{
	m_mPlayed=value;
}
void CHPoolResult::setMWon(const short value)
{
	m_mWon=value;
}
void CHPoolResult::setMLost(const short value)
{
	m_mLost=value;
}
void CHPoolResult::setMDrawn(const short value)
{
	m_mDrawn=value;
}
void CHPoolResult::setPointsF(const float value)
{
	m_pointsF=value;
}

void CHPoolResult::setMSolkoff(const float value)
{
	m_mSolkoff=value;
}

void CHPoolResult::setMMedianSolkoff(const float value)
{
	m_mMedianSolkoff=value;
}

void CHPoolResult::setMSonneBerger(const float value)
{
	m_mSonneBerger=value;
}
void CHPoolResult::setMProgressiveScore(const float value)
{
	m_mProgressiveScore=value;
}
//Get´s
short CHPoolResult::getMPlayed() const
{
	return m_mPlayed;
}
short CHPoolResult::getMWon() const
{
	return m_mWon;
}
short CHPoolResult::getMLost() const
{
	return m_mLost;
}
short CHPoolResult::getMDrawn() const
{
	return m_mDrawn;
}
float CHPoolResult::getPointsF() const
{
	return m_pointsF;
}
float CHPoolResult::getMSolkoff() const
{
	return m_mSolkoff;
}
float CHPoolResult::getMMedianSolkoff() const
{
	return m_mMedianSolkoff;
}
float CHPoolResult::getMSonneBerger() const
{
	return m_mSonneBerger;
}
float CHPoolResult::getMProgressiveScore() const
{
	return m_mProgressiveScore;
}

MSLString CHPoolResult::getPointsFStr() const
{
	MSLString format="###";
	float points=getPointsF();

	if((points-int(points))>0)
	{
		format="###.#"; // Decimales
		
	}

	GScore auxPointsF = GScore(points);
	MSLString p=auxPointsF.asString(format);
	
	p=p.strip(MSLString::leading,' ');
	return p;
	
}
MSLString CHPoolResult::getMSolkOffStr() const
{
	MSLString format="###";
	float solkOff=getMSolkoff();

	if((solkOff-int(solkOff))>0)
	{
		format="###.#"; // Decimales
		
	}

	GScore auxSolkoffF = GScore(solkOff);
	MSLString p=auxSolkoffF.asString(format);
	
	p=p.strip(MSLString::leading,' ');
	return p;
	
}
MSLString CHPoolResult::getMMedianSolkOffStr() const
{
	MSLString format="###";
	float medianSolkOff=getMMedianSolkoff();

	if((medianSolkOff-int(medianSolkOff))>0)
	{
		format="###.#"; // Decimales
		
	}

	GScore auxMSolkoffF = GScore(medianSolkOff);
	MSLString p=auxMSolkoffF.asString(format);
	
	p=p.strip(MSLString::leading,' ');
	return p;
	
}

MSLString CHPoolResult::getMSonneBergerStr() const
{
	MSLString format="###";
	float sonneBerger=getMSonneBerger();

	if((sonneBerger-int(sonneBerger))>0)
	{
		format="###.##"; // Decimales
		
	}

	GScore auxSonneBergerF = GScore(sonneBerger);
	MSLString p=auxSonneBergerF.asString(format);
	
	p=p.strip(MSLString::leading,' ');
	return p;
	
}
MSLString CHPoolResult::getMProgressiveScoreStr() const
{
	MSLString format="###";
	float progressiveScore=getMProgressiveScore();

	if((progressiveScore-int(progressiveScore))>0)
	{
		format="###.#"; // Decimales
		
	}

	GScore auxProgressiveScoreF = GScore(progressiveScore);
	MSLString p=auxProgressiveScoreF.asString(format);
	
	p=p.strip(MSLString::leading,' ');
	return p;
	
}
short CHPoolResult::getInscriptionSeed() const
{
	CHInscription *pInscription = (CHInscription *)getInscription();
	return (pInscription?pInscription->getSeed():0);
}

short CHPoolResult::getInscriptionRating() const
{
	CHInscription *pInscription = (CHInscription *)getInscription();
	return (pInscription?pInscription->getRating():0);
}

short CHPoolResult::getMasterTypeOrder() const
{
	CHInscription *pInscription = (CHInscription *)getInscription();
	return (pInscription?pInscription->getRegMasterTypeOrder():0);
}
//////////////////////////////////////////////////////////////////////
// Help Methods
//////////////////////////////////////////////////////////////////////
short CHPoolResult::getMatchesPlayed(short nRound/*=0*/) const
{//se hace el acumulado a maxRound
	CHPool * pPool = (CHPool *) getPool();
	if( !pPool )
		return 0;

	short maxRound=!nRound?pPool->getNumRounds():nRound;
	short matchesPlayed = 0;
	CHMatch * pMatch = 0;
	CHMatchResult * pHome = 0;
	CHMatchResult * pAway = 0;
	MSLSortedVector vMatches;
	pPool->getMatchesVector(vMatches);
	for(short i=0 ; i<vMatches.entries() ; i++)
	{
		pMatch = (CHMatch *)vMatches[i];
		if (pMatch->getRound()>maxRound)
			continue;
		// Con los subpartidos no tengo que calcular puntos, ni rankings de pool, etc
		if(pMatch->getSubMatch())
			continue;
		if( pMatch && pMatch->getStatus() >= CHMemoryDataBase::eUnofficial )
		{
			pHome = (CHMatchResult*)pMatch->getHome();
			if( pHome && pHome->getInscription() == getInscription() )
				matchesPlayed++;

			pAway = (CHMatchResult*)pMatch->getAway();
			if( pAway && pAway->getInscription() == getInscription() )
				matchesPlayed++;
		}
	}

	return matchesPlayed;
}

short CHPoolResult::getMatchesWon(short nRound/*=0*/) const
{//se hace el acumulado a maxRound
	CHPool * pPool = (CHPool *) getPool();
	if( !pPool )
		return 0;

	short maxRound=!nRound?pPool->getNumRounds():nRound;
	short matchesWon = 0;
	CHMatch * pMatch = 0;
	CHMatchResult * pHome = 0;
	CHMatchResult * pAway = 0;
	MSLSortedVector vMatches;
	pPool->getMatchesVector(vMatches);
	for(short i=0 ; i<vMatches.entries() ; i++)
	{
		pMatch = (CHMatch *)vMatches[i];
		if (pMatch->getRound()>maxRound)
			continue;
		// Con los subpartidos no tengo que calcular puntos, ni rankings de pool, etc
		if(pMatch->getSubMatch())
			continue;
		if( pMatch && pMatch->getStatus() >= CHMemoryDataBase::eUnofficial )
		{	
			pHome = (CHMatchResult*)pMatch->getHome();
			pAway = (CHMatchResult*)pMatch->getAway();

			if( ( pHome && 
				  pHome->getInscription() == getInscription() && 
				  ( pHome->getPoints() == WIN_POINTS ) ) )
			{
				matchesWon++;
			}
			
			if( ( pAway && pAway->getInscription() == getInscription() &&
				  ( pAway->getPoints() == WIN_POINTS ) ) )
			{
				matchesWon++;
			}
		}
	}

	return matchesWon;
}

short CHPoolResult::getMatchesLost(short nRound/*=0*/) const
{//se hace el acumulado a maxRound
	CHPool * pPool = (CHPool *) getPool();
	if( !pPool )
		return 0;

	short maxRound=!nRound?pPool->getNumRounds():nRound;
	short matchesLost = 0;
	CHMatch * pMatch = 0;
	CHMatchResult * pHome = 0;
	CHMatchResult * pAway = 0;
	MSLSortedVector vMatches;
	pPool->getMatchesVector(vMatches);
	for(short i=0 ; i<vMatches.entries() ; i++)
	{
		pMatch = (CHMatch *)vMatches[i];
		if (pMatch->getRound()>maxRound)
			continue;
		// Con los subpartidos no tengo que calcular puntos, ni rankings de pool, etc
		if(pMatch->getSubMatch())
			continue;
		if( pMatch && pMatch->getStatus() >= CHMemoryDataBase::eUnofficial )
		{
			pHome = (CHMatchResult*)pMatch->getHome();
			if( pHome && pHome->getInscription() == getInscription() &&
				pHome->getPoints() == LOST_POINTS )
				matchesLost++;

			pAway = (CHMatchResult*)pMatch->getAway();
			if( pAway && pAway->getInscription() == getInscription() &&
				pAway->getPoints() == LOST_POINTS )
				matchesLost++;
		}
	}

	return matchesLost;
}

short CHPoolResult::getMatchesDrawn(short nRound/*=0*/) const
{//se hace el acumulado a maxRound
	CHPool * pPool = (CHPool *) getPool();
	if( !pPool )
		return 0;

	short maxRound=!nRound?pPool->getNumRounds():nRound;
	short matchesDrawn = 0;
	CHMatch * pMatch = 0;
	CHMatchResult * pHome = 0;
	CHMatchResult * pAway = 0;
	MSLSortedVector vMatches;
	pPool->getMatchesVector(vMatches);
	for(short i=0 ; i<vMatches.entries() ; i++)
	{
		pMatch = (CHMatch *)vMatches[i];
		if (pMatch->getRound()>maxRound)
			continue;
		// Con los subpartidos no tengo que calcular puntos, ni rankings de pool, etc
		if(pMatch->getSubMatch())
			continue;
		if( pMatch && pMatch->getStatus() >= CHMemoryDataBase::eUnofficial )
		{
			pHome = (CHMatchResult *) pMatch->getHome();
			pAway = (CHMatchResult *) pMatch->getAway();

			if( pAway &&  
				( pHome && pHome->getInscription() == getInscription() ) &&
				( pHome->getPoints() == DRAW_POINTS || pAway->getBye() ) ) 
				matchesDrawn++;
						
			if( pHome && 
				( pAway && pAway->getInscription() == getInscription() ) &&
				( pAway->getPoints() == DRAW_POINTS || pHome->getBye() ) ) 
				matchesDrawn++;
		}
	}

	return matchesDrawn;
}
short CHPoolResult::getPointsForWon(short nRound/*=0*/) const
{
	//se hace el acumulado a maxRound
	CHPool * pPool = (CHPool *) getPool();
	if( !pPool )
		return 0;

	return getMatchesWon(nRound)*WIN_POINTS_MEMBER+getMatchesDrawn(nRound);
}

short CHPoolResult::getAllRoundsPointsForWon() const
{
	//se hace el acumulado a maxRound
	CHPool * pPool = (CHPool *) getPool();
	if( !pPool )
		return 0;

	return getMWon()*WIN_POINTS_MEMBER+getMDrawn();
}

float CHPoolResult::getPoolPointsF(short nRound/*=0*/,bool onlyRound) const
{//se hace el acumulado a maxRound
	CHPool * pPool = (CHPool *) getPool();
	if( !pPool )
		return 0;

	short maxRound=!nRound?pPool->getNumRounds():nRound;
	float points = 0.0;
	CHMatch * pMatch = 0;
	CHMatchResult * pHome = 0;
	CHMatchResult * pAway = 0;
	MSLSortedVector vMatches;
	pPool->getMatchesVector(vMatches);
	mslToolsFcCompare oldCompare = vMatches.getFcCompare();
	vMatches.setFcCompare(orderMatchesByRoundMatch);
	vMatches.sort();

	for(short i=0 ; i<vMatches.entries() ; i++)
	{
		pMatch = (CHMatch *)vMatches[i];
		if ((pMatch->getRound()>maxRound && !onlyRound) || (onlyRound && nRound && pMatch->getRound()!=nRound))
			continue;
		
		if(pMatch->isTeam() && !pMatch->getSubMatch())
			continue;

		if( pMatch && pMatch->getStatus() >= CHMemoryDataBase::eUnofficial )
		{
			pHome = (CHMatchResult*) pMatch->getHome();
			if( pHome && pHome->getInscription() == getInscription() )
				points += pHome->getPoints();

			pAway = (CHMatchResult*) pMatch->getAway();
			if( pAway && pAway->getInscription() == getInscription() )
				points += pAway->getPoints();
		}
	}
	vMatches.setFcCompare(oldCompare);
	vMatches.sort();
	return points;
}

MSLString CHPoolResult::getPoolPointsFStr(short nRound/*=0*/,bool onlyRound) const
{
	MSLString format="###";
	float points=getPoolPointsF(nRound,onlyRound);

	if((points-int(points))>0)
	{
		format="###.#"; // Decimales		
	}

	GScore m_pointsF = GScore(points);
	MSLString p=m_pointsF.asString(format);
	
	p=p.strip(MSLString::leading,' ');
	return p;
	
}

float CHPoolResult::getPointsSO(short nRound/*=0*/,bool onlyRound/*=false*/) const
{	
	CHPool * pPool = (CHPool *) getPool();
	if( !pPool )
		return 0;

	short maxRound=!nRound?pPool->getNumRounds():nRound;
	float points = 0.0;
	CHMatch * pMatch = 0;
	CHMatchResult * pHome = 0;
	CHMatchResult * pAway = 0;
	MSLSortedVector vMatches;
	pPool->getMatchesVector(vMatches);

	mslToolsFcCompare oldCompare = vMatches.getFcCompare();
	vMatches.setFcCompare(orderMatchesByRoundMatch);
	vMatches.sort();
		
	for(short i=0 ; i<vMatches.entries() ; i++)
	{
		pMatch = (CHMatch *)vMatches[i];
		if ((pMatch->getRound()>maxRound && !onlyRound) || (onlyRound && nRound && pMatch->getRound()!=nRound))
			continue;
		
		if(pMatch->isTeam() && !pMatch->getSubMatch())
			continue;

		if( pMatch && pMatch->getStatus() >= CHMemoryDataBase::eUnofficial )
		{
			pHome = (CHMatchResult*)pMatch->getHome();
			if( pHome && pHome->getInscription() == getInscription() )
				points += pHome->getPointsSO();

			pAway = (CHMatchResult*)pMatch->getAway();
			if( pAway && pAway->getInscription() == getInscription() )
				points += pAway->getPointsSO();
		}
	}
	vMatches.setFcCompare(oldCompare);
	vMatches.sort();
	return points;
}


float CHPoolResult::getSolkOffF(short nRound/*=0*/) const
{//se hace el acumulado a maxRound
	//todos los posibles oponentes
	CHPool * pPool = (CHPool *) getPool();
	if( !pPool )
		return 0;

	CHPhase *pPhase = (CHPhase *) pPool->getPhase();
	if (!pPhase)
		return 0;

	CHEvent *pEvent = (CHEvent *) pPhase->getEvent();
	if (!pEvent)
		return 0;

	short nRoundsPlayed = pPool->getNumRoundsPlayed(); 

	int count=0;
	short maxRound=!nRound?pPool->getNumRoundsPlayed():nRound;
	float points = 0.0;
	CHMatch * pMatch = 0;
	CHMatchResult * pMatRes = 0;
	CHMatchResult * pMatResOp = 0;
	CHPoolResult * pPRes = 0;
	CHPoolResult * pPResOp = 0;
	MSLSortedVector vMatches;
	pPool->getMatchesVector(vMatches);
	for(short i=0 ; i<vMatches.entries() ; i++)
	{
		pMatch = (CHMatch *)vMatches[i];
		if (pMatch->getRound()>maxRound)
			continue;
		
		if(pMatch->isTeam() && pMatch->getSubMatch())
			continue;

		if( pMatch && pMatch->getStatus() >= CHMemoryDataBase::eUnofficial )
		{//buscamos los puntos del oponente
			count++;
			pMatRes=(CHMatchResult *)(pMatch->getMatchResult(0));
			pPRes=(CHPoolResult *)(pMatRes->getPoolResult());
			pMatResOp=(CHMatchResult *)(pMatch->getMatchResult(1));
			pPResOp=(CHPoolResult *)(pMatResOp->getPoolResult());
			
			if ((pMatRes->getBye() && pMatResOp->getInscriptionKey()==getInscriptionKey()) ||
				(pMatResOp->getBye() && pMatRes->getInscriptionKey()==getInscriptionKey()))
			{
				//points+=((CHPoolResult*)this)->getAveragePointsAllCompetitors();
				points += 0.5*nRoundsPlayed*pEvent->getTeamMatches();
				continue;
			}
			if (pMatRes->getInscriptionKey()==getInscriptionKey())
				points += float(pPResOp->getPointsSO(maxRound));
			else if (pMatResOp->getInscriptionKey()==getInscriptionKey())
				points += float(pPRes->getPointsSO(maxRound));
		}
	}
	return points;
}


MSLString CHPoolResult::getSolkOffFStr(short nRound/*=0*/) const
{
	MSLString format="###";
	float points=getSolkOffF(nRound);

	if((points-int(points))>0)
		format="###.#"; // Decimales

	GScore m_pointsF = GScore(points);
	MSLString p=m_pointsF.asString(format);

	p=p.strip(MSLString::leading,' ');
	return p;
}

float CHPoolResult::getMedianSolkOffF(short nRound/*=0*/) const
{//se hace el acumulado a maxRound
	//todos los posibles oponentes
	CHPool * pPool = (CHPool *) getPool();
	if( !pPool )
		return 0;

	CHPhase *pPhase = (CHPhase *) pPool->getPhase();
	if (!pPhase)
		return 0;

	CHEvent *pEvent = (CHEvent *) pPhase->getEvent();
	if (!pEvent)
		return 0;

	short nRoundsPlayed = pPool->getNumRoundsPlayed(); 

	int count=0;
	short maxRound=!nRound?pPool->getNumRounds():nRound;
	float points = 0.0;
	CHMatch * pMatch = 0;
	CHMatchResult * pMatRes = 0;
	CHMatchResult * pMatResOp = 0;
	CHPoolResult * pPRes = 0;
	CHPoolResult * pPResOp = 0;
	MSLSortedVector vMatches;
	pPool->getMatchesVector(vMatches);

	MSLSortedVector vCompetitors;
	bool hasBye=false;
	for(short i=0 ; i<vMatches.entries() ; i++)
	{
		pMatch = (CHMatch *)vMatches[i];
		if (pMatch->getRound()>maxRound)
			continue;
		
		if(pMatch->isTeam() && pMatch->getSubMatch())
			continue;

		if( pMatch && pMatch->getStatus() >= CHMemoryDataBase::eUnofficial )
		{//buscamos los puntos del oponente
			count++;
			pMatRes=(CHMatchResult *)(pMatch->getMatchResult(0));
			pPRes=(CHPoolResult *)(pMatRes->getPoolResult());
			
			pMatResOp=(CHMatchResult *)(pMatch->getMatchResult(1));
			pPResOp=(CHPoolResult *)(pMatResOp->getPoolResult());
			
			if (pMatRes->getBye() && pMatResOp->getInscriptionKey()==getInscriptionKey())
			{	
				hasBye=true;
				continue;
			}

			if (pMatResOp->getBye() && pMatRes->getInscriptionKey()==getInscriptionKey())
			{
				hasBye=true;
				continue;
			}
			
			if (pMatRes->getInscriptionKey()==getInscriptionKey())
				vCompetitors.insert(pPResOp);
			else if (pMatResOp->getInscriptionKey()==getInscriptionKey())
				vCompetitors.insert(pPRes);
		}
	}

	if (vCompetitors.entries()>1)
	{
		vCompetitors.setFcCompare(orderPoolResultSO);
		vCompetitors.sort();
	
		for (short i=1;i<vCompetitors.entries()-1;i++)
		{
			CHPoolResult* pPoolResult = (CHPoolResult*)vCompetitors[i];
			points += float(pPoolResult->getPointsSO(maxRound));
		}

		if (hasBye)
			points+=0.5*nRoundsPlayed;
	}

	return points;
}


MSLString CHPoolResult::getMedianSolkOffFStr(short nRound/*=0*/) const
{
	MSLString format="###";
	float points=getMedianSolkOffF(nRound);

	if((points-int(points))>0)
		format="###.#"; // Decimales

	GScore m_pointsF = GScore(points);
	MSLString p=m_pointsF.asString(format);

	p=p.strip(MSLString::leading,' ');
	return p;
}

float CHPoolResult::getSonneBergerF(short nRound/*=0*/) const
{//se hace el acumulado a maxRound
	//solo contra los opnentes que ha jugado
	CHPool * pPool = (CHPool *) getPool();
	if( !pPool )
		return 0;

	short maxRound=!nRound?pPool->getNumRounds():nRound;
	float points = 0.0;
	CHMatch * pMatch = 0;
	CHMatchResult * pMatRes = 0;
	CHMatchResult * pMatResOp = 0;
	CHPoolResult * pPRes = 0;
	CHPoolResult * pPResOp = 0;
	MSLSortedVector vMatches;
	pPool->getMatchesVector(vMatches);
	for(short i=0 ; i<vMatches.entries() ; i++)
	{
		pMatch = (CHMatch *)vMatches[i];
		if (pMatch->getRound()>maxRound)
			continue;
		
		if(pMatch->isTeam() && !pMatch->getSubMatch())
			continue;

		if( pMatch && pMatch->getStatus() >= CHMemoryDataBase::eUnofficial )
		{
			short winner=pMatch->getWinner();
			if (winner>=CHMatch::eWinnerWhite && winner<=CHMatch::eDraw)//ganadores
			{
				//si es distinto es el oponente
				pMatRes=(CHMatchResult *)pMatch->getMatchResult(winner<CHMatch::eDraw?winner-1:0);
				pPRes=(CHPoolResult *)(pMatRes->getPoolResult());
				pMatResOp=(CHMatchResult *)pMatch->getMatchResult(!(winner<CHMatch::eDraw?winner-1:0));
				pPResOp=(CHPoolResult *)(pMatResOp->getPoolResult());
				//si soy ganador los puntos del contrario
				//si empato la mitad de los puntos del contrario
				//si pierdo no cuenta
				if (pMatRes->getInscriptionKey()==getInscriptionKey() && winner<CHMatch::eDraw)
				{
					if (pPResOp)
						points+=float(pPResOp->getPointsFR(maxRound));
				}
				else if (winner==CHMatch::eDraw &&
					(pMatRes->getInscriptionKey()==getInscriptionKey() ||
					pMatResOp->getInscriptionKey()==getInscriptionKey()))//empate
				{
					if (pMatRes->getInscriptionKey()==getInscriptionKey() && pPResOp)
					points+=float(pPResOp->getPointsFR(maxRound)/float(2.0));
					else if (pMatResOp->getInscriptionKey()==getInscriptionKey() && pPRes)
						points+=float(pPRes->getPointsFR(maxRound)/float(2.0));
				}
			}
		}
	}

	return points;
}

MSLString CHPoolResult::getSonneBergerFStr(short nRound/*=0*/) const
{
	MSLString format="###";
	float points=getSonneBergerF(nRound);

	if((points-int(points))>0)
		format="###.##"; // Decimales

	GScore m_pointsF = GScore(points);
	MSLString p=m_pointsF.asString(format);

	p=p.strip(MSLString::leading,' ');
	return p;
}
float CHPoolResult::getProgresiveF(short nRound/*=0*/) const
{//se hace el acumulado a maxRound
	//solo contra los opnentes que ha jugado
	CHPool * pPool = (CHPool *) getPool();
	if( !pPool )
		return 0;

	short maxRound=!nRound?pPool->getNumRounds():nRound;
	float pointsProgressiveScore=0.0;
	float pointsProgressiveScorePrv=0.0;
	CHMatch * pMatch = 0;
	CHMatchResult * pMatRes = 0;
	CHMatchResult * pMatResOp = 0;
	MSLSortedVector vMatches;
	pPool->getMatchesVector(vMatches);
	CHInscription *pInscription=(CHInscription*)getInscription();
	if(!pInscription)
		return 0.0;
	int count=0;
	for(short i=0 ; i<vMatches.entries() ; i++)
	{
		pMatch = (CHMatch *)vMatches[i];
		if (pMatch->getRound()>maxRound)
			continue;
		if(pMatch->isTeam() && !pMatch->getSubMatch())
			continue;
		if( pMatch && pMatch->getStatus() >= CHMemoryDataBase::eUnofficial )
		{
			count++;
			pMatRes=(CHMatchResult *)pMatch->getMatchResult(0);
			pMatResOp=(CHMatchResult *)pMatch->getMatchResult(1);
			// Si no es un partido en los que participa saltamos a otro
			if(getInscriptionKey()!=pMatRes->getInscriptionKey() && 
			   getInscriptionKey()!=pMatResOp->getInscriptionKey())
			   continue;

			if (pMatRes->getInscriptionKey()==getInscriptionKey())
			{
				pointsProgressiveScore+=float(pMatRes->getPoints())+float(pointsProgressiveScorePrv);
				pointsProgressiveScorePrv+=float(pMatRes->getPoints());
			}
			else if (pMatResOp->getInscriptionKey()==getInscriptionKey())
			{
				pointsProgressiveScore+=float(pMatResOp->getPoints())+float(pointsProgressiveScorePrv);
				pointsProgressiveScorePrv+=float(pMatResOp->getPoints());
			}
						
		}
	}

	return pointsProgressiveScore;
}

MSLString CHPoolResult::getProgressiveFStr(short nRound/*=0*/) const
{
	MSLString format="###";
	float points=getProgresiveF(nRound);

	if((points-int(points))>0)
		format="###.#"; // Decimales

	GScore m_pointsF = GScore(points);
	MSLString p=m_pointsF.asString(format);

	p=p.strip(MSLString::leading,' ');
	return p;
}

short CHPoolResult::getTeamMatchesWon(short nRound/*=0*/) const
{//se hace el acumulado a maxRound
	
	CHEvent *pEvent= (CHEvent*)getEvent();
	// Solo se calcula esto para el evento de equipos
	// Es el numero de partidos ganados por los miembros del equipo
	if(!pEvent->isTeam())
		return 0;

	CHPool * pPool = (CHPool *) getPool();
	if( !pPool )
		return 0;

	short maxRound=!nRound?pPool->getNumRounds():nRound;
	short matchesWon = 0;
	CHMatch * pMatch = 0;
	CHMatchResult * pHome = 0;
	CHMatchResult * pAway = 0;
	MSLSortedVector vMatches;
	pPool->getMatchesVector(vMatches);
	for(short i=0 ; i<vMatches.entries() ; i++)
	{
		pMatch = (CHMatch *)vMatches[i];
		if (pMatch->getRound()>maxRound)
			continue;
		// Con los subpartidos no tengo que calcular puntos, ni rankings de pool, etc
		
		if( pMatch && pMatch->getStatus() >= CHMemoryDataBase::eUnofficial )
		{	
			pHome = (CHMatchResult*)pMatch->getHome();
			
			if( pHome && pHome->getInscription() == getInscription())
				matchesWon+=pHome->getTeamMatchesWon();

			pHome = (CHMatchResult*)pMatch->getAway();
			if( pAway && pAway->getInscription() == getInscription())
				matchesWon+=pAway->getTeamMatchesWon();
		}
	}

	return matchesWon;
}

MSLString CHPoolResult::getTeamMatchesWonStr(short nRound/*=0*/) const
{
	short points=getTeamMatchesWon(nRound);

	char tmp[10];
	sprintf_s(tmp,"%d",points);
	
	return MSLString(tmp);
}

float CHPoolResult::getPointsFR(short nRound/*=0*/) const
{//se hace el acumulado a maxRound del poolresult
	// Es el numero de puntos ganados por los miembros del equipo
	CHPool * pPool = (CHPool *) getPool();
	if( !pPool )
		return 0;

	short maxRound=!nRound?pPool->getNumRounds():nRound;
	float PointsFR = 0.0;
	CHMatch * pMatch = 0;
	CHMatchResult * pHome = 0;
	CHMatchResult * pAway = 0;
	MSLSortedVector vMatches;
	pPool->getMatchesVector(vMatches);
	for(short i=0 ; i<vMatches.entries() ; i++)
	{
		pMatch = (CHMatch *)vMatches[i];
		if (pMatch->getRound()>maxRound)
			continue;
		// Con el partido general no tengo que calcular puntos, ni rankings de pool, etc
		if(pMatch->isTeam() && !pMatch->getSubMatch())
			continue;
		
		if( pMatch && pMatch->getStatus() >= CHMemoryDataBase::eUnofficial )
		{	
			pHome = (CHMatchResult*)pMatch->getHome();
			
			if( pHome && pHome->getInscriptionKey() == getInscriptionKey())
				PointsFR+=float(pHome->getPoints());

			pHome = (CHMatchResult*)pMatch->getAway();
			if( pAway && pAway->getInscriptionKey() == getInscriptionKey())
				PointsFR+=float(pAway->getPoints());
		}
	}
	return PointsFR;
}

MSLWString CHPoolResult::getDescription(bool longDescription/*=true*/) const
{
	// Tiene registro : nombre del equipo
	CHRegister * pRegister = (CHRegister *) getRegister();
	if( pRegister )
		return longDescription?pRegister->getPrnSName():pRegister->getGroup().toUnicode();

	// Es una pool : numero de orden
	if( getIsPool() )
		return TOWSTRING(getOrder());

	// Best ranking position : 2º Rk 3 || 2º (A3,B3,C3)
	MSLWString txt;
	if( getBest() )
	{
		if( !longDescription )
		{
			txt += TOWSTRING(getPositionSource());
			txt += _T("º Rk ");
			txt += TOWSTRING(getRankingSource());
			return txt;
		}

		CHPhase * pPhaseSource = (CHPhase *) getPointerPhaseSource();
		if( !pPhaseSource )
			return _T("");

		CHPool * pPool = 0;
		MSLSortedVector vPools;
		pPhaseSource->getPoolesVector(vPools);
		for(short i=0 ; i<vPools.entries() ; i++)
		{
			pPool = (CHPool *)vPools[i];
			if( !pPool )
				continue;

			txt += (i==0)?TOWSTRING(getPositionSource())+_T("º ("):_T(",");
			txt += pPool->getOrderAsString(pPool->getDescriptionMode());
			txt += TOWSTRING(getRankingSource());
		}

		txt += _T(")");
		return txt;
	}

	CHPool * pPoolSource = (CHPool *) getPointerPoolSource();
	if( !pPoolSource )
		return _T("");

	// La fase anterior es una Pool : B4
	if( pPoolSource->getIsPool() )
	{
		txt += pPoolSource->getOrderAsString(pPoolSource->getDescriptionMode());
		txt += TOWSTRING(getRankingSource());
		return txt;
	}

	// La fase anterior no es una Pool : 
	if( getRankingSource() == 1 ) txt = longDescription?_T("Winner "):_T("W ");
	if( getRankingSource() == 2 ) txt = longDescription?_T("Loser " ):_T("L ");



	CHMatch * pMatchSource = (CHMatch *) pPoolSource->getMatch(0);
	if( pMatchSource )
	{
		if( pMatchSource->getMatchNumber() )
		{
			txt += TOWSTRING(pMatchSource->getMatchNumber());
			return txt;
		}

		txt += pMatchSource->getPhaseSDescription();
		txt += _T(" ") + pPoolSource->getDescription(pPoolSource->getDescriptionMode());
	}

	return txt;

}

MSLWString CHPoolResult::getSourceCompetitor()
{
	MSLWString idcompetitor(NULLWSTRING);
	
	GTHPhase * pPhaseSource=getPointerPhaseSource();
	CHPool * pPoolSource=(CHPool*)getPointerPoolSource();
	wchar_t aux[20];
	memset(aux,0,sizeof(aux));
	if(!pPhaseSource )
	{
		idcompetitor+=TOWSTRING(getOrder());		
		idcompetitor+=_T(" ");
		if (getPool())
			idcompetitor+=((CHPool*)getPool())->getLDescription(GTHPhase::eText);			
	}		
	else if( pPhaseSource->getIsPool() && getRankingSource() )
	{
		idcompetitor+=TOWSTRING(getRankingSource());
		idcompetitor+=_T(".");
		if( pPoolSource )
			idcompetitor+=pPoolSource->getLDescription(GTHPhase::eText);						
	}				
	else if( !pPhaseSource->getIsPool() )
	{
		if(getRankingSource()==1)
			idcompetitor+="Winner ";
		if(getRankingSource()==2)
			idcompetitor+="Loser ";
		if (pPoolSource &&
			pPoolSource->getMatches().entries())
		{
			CHMatch* pMatch = (CHMatch*)pPoolSource->getMatch(0);
			if (pMatch)
				idcompetitor+=TOWSTRING(pMatch->getMatchNumber());
		}
	}

	return idcompetitor;
}

bool CHPoolResult::isQualitative() const
{
	if(getQualitative() && getQualitativeCode()!=OK)
		return true;

	return false;
}

bool CHPoolResult::hasAlreadyPlayed(CHPoolResult* _pPoolResult, short lastRound)
{
	MSLSet colMatchResults=CHMemoryDataBase::getCol(__CHMATCHRESULT).select(matchResultsOfPoolResult,this);
	MSLSetIterator it(colMatchResults);
		
	CHMatchResult* pMatchResult=0;
	while( (pMatchResult=(CHMatchResult*)it()) != 0)
	{
		CHMatch* pMatch = (CHMatch*) pMatchResult->getMatch();

		if (lastRound==pMatch->getRound())
			continue;
		
		CHMatchResult* pWhite = (CHMatchResult*) pMatch->getHome();
		CHMatchResult* pBlack = (CHMatchResult*) pMatch->getAway();

		if (_pPoolResult->getRegister()==pWhite->getRegister() ||
			_pPoolResult->getRegister()==pBlack->getRegister())
		{			
			return true;
		}
	}	
	
	return false;
}

bool CHPoolResult::isPlayingRound(CHMatch* _pMatch, short round)
{
	MSLSet colMatchResults=CHMemoryDataBase::getCol(__CHMATCHRESULT).select(matchResultsOfPoolResult,this);
	MSLSetIterator it(colMatchResults);

	CHMatchResult* pMatchResult=0;
	while( (pMatchResult=(CHMatchResult*)it()) != 0)
	{
		CHMatch* pMatch = (CHMatch*) pMatchResult->getMatch();

		if (round==pMatch->getRound() &&
			pMatch!=_pMatch)
			return true;				
	}
		
	return false;
}

short CHPoolResult::getNumMatchesWithColor(CHMatchResult::side color, short lastRound)
{
	short num = 0;
	
	MSLSet colMatchResults=CHMemoryDataBase::getCol(__CHMATCHRESULT).select(matchResultsOfPoolResult,this);
	MSLSetIterator it(colMatchResults);
		
	CHMatchResult* pMatchResult=0;
	while( (pMatchResult=(CHMatchResult*)it()) != 0)
	{
		CHMatch* pMatch = (CHMatch*) pMatchResult->getMatch();

		if (pMatch->getRound()>=lastRound)
			continue;

		if (pMatch->getSubMatch()!=0)
			continue;


		CHMatchResult* pWhite = (CHMatchResult*) pMatch->getHome();
		CHMatchResult* pBlack = (CHMatchResult*) pMatch->getAway();

		if (getRegister()==pWhite->getRegister() && 
			color == CHMatchResult::eWhite)
			num++;
		{
			if (getRegister()==pBlack->getRegister() && 
				color == CHMatchResult::eBlack)
				num++;
		}		
	}	
		
	return num;	
}

CHMatchResult::side CHPoolResult::getSidePreference(short round)
{
	short numWhite = getNumMatchesWithColor(CHMatchResult::eWhite,round);
	short numBlack = getNumMatchesWithColor(CHMatchResult::eBlack,round);

	if ( numWhite-numBlack > 1 )
		return CHMatchResult::eBlack;
	else if ( numBlack-numWhite > 1)
		return CHMatchResult::eWhite;	
	else if ( numWhite-numBlack == 1 )
		return CHMatchResult::eBlack;
	else if ( numBlack-numWhite == 1)
		return CHMatchResult::eWhite;
	else if (numBlack==numWhite)
	{
		MSLSet colMatchResults=CHMemoryDataBase::getCol(__CHMATCHRESULT).select(matchResultsOfPoolResult,this);
		MSLSetIterator it(colMatchResults);
		
		CHMatchResult* pMatchResult=0;
		while( (pMatchResult=(CHMatchResult*)it()) != 0)
		{	
			CHMatch* pMatch = (CHMatch*)pMatchResult->getMatch();

			if (pMatch->getRound()==round)
				continue;

			if (pMatch->getRound()==round-1)
			{
				CHMatchResult* pWhite = (CHMatchResult* ) pMatch->getHome();
				CHMatchResult* pBlack = (CHMatchResult* ) pMatch->getAway();

				if (pWhite->getRegister() == getRegister())
					return CHMatchResult::eBlack;
				if (pBlack->getRegister() == getRegister())
					return CHMatchResult::eWhite;
			}
		}		
	}
	return CHMatchResult::eNone;
}

CHMatchResult::colorPreference CHPoolResult::getColorPreference(short round)
{
	short numWhite = getNumMatchesWithColor(CHMatchResult::eWhite,round);
	short numBlack = getNumMatchesWithColor(CHMatchResult::eBlack,round);

	if ( numWhite-numBlack > 1 )
		return CHMatchResult::eBlackAbsolut;
	else if ( numBlack-numWhite > 1)
		return CHMatchResult::eWhiteAbsolut;	
	else if ( numWhite-numBlack == 1 )
		return CHMatchResult::eBlackStrong;
	else if ( numBlack-numWhite == 1)
		return CHMatchResult::eWhiteStrong;
	else if (numBlack==numWhite)
	{
		MSLSet colMatchResults=CHMemoryDataBase::getCol(__CHMATCHRESULT).select(matchResultsOfPoolResult,this);
		MSLSetIterator it(colMatchResults);
		
		CHMatchResult* pMatchResult=0;
		while( (pMatchResult=(CHMatchResult*)it()) != 0)
		{	
			CHMatch* pMatch = (CHMatch*)pMatchResult->getMatch();

			if (pMatch->getRound()==round)
				continue;

			if (pMatch->getRound()==round-1)
			{
				CHMatchResult* pWhite = (CHMatchResult*) pMatch->getHome();
				CHMatchResult* pBlack = (CHMatchResult*) pMatch->getAway();

				if (pWhite->getRegister() == getRegister())
					return CHMatchResult::eBlackModerate;
				if (pBlack->getRegister() == getRegister())
					return CHMatchResult::eWhiteModerate;
			}
		}		
	}
	return CHMatchResult::eDraw;
}

bool CHPoolResult::hasAlreadyBye(short lastRound)
{
	MSLSet colMatchResults=CHMemoryDataBase::getCol(__CHMATCHRESULT).select(matchResultsOfPoolResult,this);
	MSLSetIterator it(colMatchResults);
	
	CHMatchResult* pMatchResult=0;
	while( (pMatchResult=(CHMatchResult*)it()) != 0)
	{
		CHMatch* pMatch = (CHMatch*) pMatchResult->getMatch();
		if (pMatch->getRound()==lastRound)
			continue;
		if (pMatch->hasByes())
			return true;		
	}	
	return false;
}

bool CHPoolResult::canPlayInColor(CHMatchResult::side color, short round)
{
	CHMatchResult::colorPreference colorPref = getColorPreference(round);
	if (colorPref==CHMatchResult::eBlackAbsolut && color==CHMatchResult::eWhite)
		return false;
	if (colorPref==CHMatchResult::eWhiteAbsolut && color==CHMatchResult::eBlack)
		return false;

	return true;
}

float CHPoolResult::getAveragePointsAllCompetitors(CHMatch *pMatch)
{
	CHPool *pPool=(CHPool*)getPool();

	CHPoolResult *pPoolResult=0;
	float totalPoints=0.0;

	MSLSortedVector vPoolResults;
	pPool->getPoolResultsVector(vPoolResults);
	for(short i=0;i<vPoolResults.entries();i++)
	{
		pPoolResult=(CHPoolResult*)vPoolResults[i];
		if(pMatch)
			 totalPoints+=pPoolResult->getPoolPointsF(pMatch->getRound());
		else totalPoints+=pPoolResult->getPointsF();

	}
	if (vPoolResults.entries()>0)
		totalPoints/=short(vPoolResults.entries());

	return totalPoints;
}

bool CHPoolResult::isTeamEvent()
{
	return ((CHEvent*)getEvent()) ? ((CHEvent*)getEvent())->isTeam() : false;
}