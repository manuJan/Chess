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
#include "CHDiscipline.h"
#include "CHPoolResult.h"
#include "CHPool.h"
#include "CHRegister.h"
#include "CHClassIds.h"
#include "UCHPoolResult.h"
#include <core/G/GBuffer.h>
#include <core/G/GScore.h>

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

int orderMatchesByRoundMatch(const GVectorElement** a, const GVectorElement** b)
{
	CHMatch * pA=(CHMatch *)(*a)->getElement();
	CHMatch * pB=(CHMatch *)(*b)->getElement();

	int order=pA->getRound() - pB->getRound();
	if(order)
		return order;

	return pA->getCode() - pB->getCode();
}

static
RWBoolean matchResultsOfPoolResult(const RWCollectable * col, const void * param)
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

RWDEFINE_COLLECTABLE(CHPoolResult, __CHPOOLRESULT)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHPoolResult::CHPoolResult()
:GTHPoolResult()
,mPlayed(0)
,mWon(0)
,mLost(0)
,mDrawn(0)
,pointsF(0.0)
,mSolkoff(0.0)
,mMedianSolkoff(0.0)
,mSonneBerger(0.0)
,mProgressiveScore(0.0)
{
}

CHPoolResult::CHPoolResult(const CHPoolResult & copy)
{
	operator=(copy);
}

CHPoolResult::CHPoolResult(CPack& aPack)
{
	unpack(aPack);
}

CHPoolResult::~CHPoolResult() 
{
}


//////////////////////////////////////////////////////////////////////
// Operators
//////////////////////////////////////////////////////////////////////
CHPoolResult & CHPoolResult::operator =(const CHPoolResult & copy)
{
	if (this != &copy)
	{
		GTHPoolResult::operator =(copy);
		mPlayed				= copy.mPlayed;
		mWon				= copy.mWon;
		mLost				= copy.mLost;
		mDrawn				= copy.mDrawn;
		pointsF				= copy.pointsF;
		mSolkoff			= copy.mSolkoff;
		mMedianSolkoff		= copy.mMedianSolkoff;
		mSonneBerger		= copy.mSonneBerger;
		mProgressiveScore	= copy.mProgressiveScore;
	}
	return * this;
}

RWBoolean CHPoolResult::operator ==(const CHPoolResult & copy)
{
	if (this == &copy)
		return true;
	else
		return (GTHPoolResult::operator ==(copy)	&&
				mPlayed				== copy.mPlayed			&&
				mWon				== copy.mWon			&&
				mLost				== copy.mLost			&&
				mDrawn				== copy.mDrawn			&&
				pointsF				== copy.pointsF			&&
				mSolkoff			== copy.mSolkoff		&&
				mMedianSolkoff		== copy.mMedianSolkoff	&&
				mSonneBerger		== copy.mSonneBerger	&&
				mProgressiveScore	== copy.mProgressiveScore);
}

RWBoolean CHPoolResult::operator !=(const CHPoolResult & copy)
{
	return !operator==(copy);
}


//////////////////////////////////////////////////////////////////////
// From GData
//////////////////////////////////////////////////////////////////////
RWBoolean CHPoolResult::uSQL(RWDBConnection& pConnect,RWBoolean remove /*=false*/ )
{
	RWBoolean rc=false;

	UCHPoolResult upd(&pConnect);

	if( remove )  rc=upd.remove(*this);
	else          rc=upd.set   (*this);

	return rc;
}

CPack& CHPoolResult::pack(CPack& aPack)
{
	GTHPoolResult::pack(aPack);
	
	aPack << mPlayed;
	aPack << mWon;
	aPack << mLost;
	aPack << mDrawn;
	aPack << pointsF;
	aPack << mSolkoff;	
	aPack << mMedianSolkoff;
	aPack << mSonneBerger;
	aPack << mProgressiveScore;

	return aPack;
}

CPack& CHPoolResult::unpack(CPack& aPack)
{
	GTHPoolResult::unpack(aPack);

	aPack >> mPlayed;
	aPack >> mWon;
	aPack >> mLost;
	aPack >> mDrawn;
	aPack >> pointsF;
	aPack >> mSolkoff;	
	aPack >> mMedianSolkoff;
	aPack >> mSonneBerger;
	aPack >> mProgressiveScore;

	return aPack;
}

RWCString CHPoolResult::msl() const
{
	// Copio el points para que en el GTHPoolResult se envien los puntos
	/*short poolPoints=((CHPoolResult*)this)->getPoolPoints();
	
	((CHPoolResult*)this)->setPoints(poolPoints);*/

	RWCString str = GTHPoolResult::msl();

	GBuffer aBuffer;

	return str +  RWCString (aBuffer	<< mPlayed // getMatchesPlayed()
										<< mWon	//getMatchesWon()
										<< mLost //getMatchesLost()
										<< mDrawn //getMatchesDrawn()
										<< getPointsFStr() // getPoolPointsFStr()
										<< mSolkoff
										<< mSonneBerger
										<< mProgressiveScore
										<< getPointsForWon()
										<< endLine   );
}

RWCString CHPoolResult::mslDescription(const char *language) const
{
	return GTHPoolResult::mslDescription(language);
}

//Set's
void CHPoolResult::setMPlayed(const short value)
{
	mPlayed=value;
}
void CHPoolResult::setMWon(const short value)
{
	mWon=value;
}
void CHPoolResult::setMLost(const short value)
{
	mLost=value;
}
void CHPoolResult::setMDrawn(const short value)
{
	mDrawn=value;
}
void CHPoolResult::setPointsF(const float value)
{
	pointsF=value;
}

void CHPoolResult::setMSolkoff(const float value)
{
	mSolkoff=value;
}

void CHPoolResult::setMMedianSolkoff(const float value)
{
	mMedianSolkoff=value;
}

void CHPoolResult::setMSonneBerger(const float value)
{
	mSonneBerger=value;
}
void CHPoolResult::setMProgressiveScore(const float value)
{
	mProgressiveScore=value;
}
//Get´s
short CHPoolResult::getMPlayed() const
{
	return mPlayed;
}
short CHPoolResult::getMWon() const
{
	return mWon;
}
short CHPoolResult::getMLost() const
{
	return mLost;
}
short CHPoolResult::getMDrawn() const
{
	return mDrawn;
}
float CHPoolResult::getPointsF() const
{
	return pointsF;
}
float CHPoolResult::getMSolkoff() const
{
	return mSolkoff;
}
float CHPoolResult::getMMedianSolkoff() const
{
	return mMedianSolkoff;
}
float CHPoolResult::getMSonneBerger() const
{
	return mSonneBerger;
}
float CHPoolResult::getMProgressiveScore() const
{
	return mProgressiveScore;
}

RWCString CHPoolResult::getPointsFStr() const
{
	RWCString format="###";
	float points=getPointsF();

	if((points-int(points))>0)
	{
		format="###.#"; // Decimales
		
	}

	GScore auxPointsF = GScore(points);
	RWCString p=auxPointsF.asString(format);
	
	p=p.strip(RWCString::leading,' ');
	return p;
	
}
RWCString CHPoolResult::getMSolkOffStr() const
{
	RWCString format="###";
	float solkOff=getMSolkoff();

	if((solkOff-int(solkOff))>0)
	{
		format="###.#"; // Decimales
		
	}

	GScore auxSolkoffF = GScore(solkOff);
	RWCString p=auxSolkoffF.asString(format);
	
	p=p.strip(RWCString::leading,' ');
	return p;
	
}
RWCString CHPoolResult::getMMedianSolkOffStr() const
{
	RWCString format="###";
	float medianSolkOff=getMMedianSolkoff();

	if((medianSolkOff-int(medianSolkOff))>0)
	{
		format="###.#"; // Decimales
		
	}

	GScore auxMSolkoffF = GScore(medianSolkOff);
	RWCString p=auxMSolkoffF.asString(format);
	
	p=p.strip(RWCString::leading,' ');
	return p;
	
}

RWCString CHPoolResult::getMSonneBergerStr() const
{
	RWCString format="###";
	float sonneBerger=getMSonneBerger();

	if((sonneBerger-int(sonneBerger))>0)
	{
		format="###.##"; // Decimales
		
	}

	GScore auxSonneBergerF = GScore(sonneBerger);
	RWCString p=auxSonneBergerF.asString(format);
	
	p=p.strip(RWCString::leading,' ');
	return p;
	
}
RWCString CHPoolResult::getMProgressiveScoreStr() const
{
	RWCString format="###";
	float progressiveScore=getMProgressiveScore();

	if((progressiveScore-int(progressiveScore))>0)
	{
		format="###.#"; // Decimales
		
	}

	GScore auxProgressiveScoreF = GScore(progressiveScore);
	RWCString p=auxProgressiveScoreF.asString(format);
	
	p=p.strip(RWCString::leading,' ');
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
	GSortedVector & vMatches = pPool->getMatchsVector();
	for(size_t i=0 ; i<vMatches.entries() ; i++)
	{
		pMatch = (CHMatch *)vMatches[i]->getElement();
		if (pMatch->getRound()>maxRound)
			continue;
		// Con los subpartidos no tengo que calcular puntos, ni rankings de pool, etc
		if(pMatch->getSubMatch())
			continue;
		if( pMatch && pMatch->getStatus() >= CHMemoryDataBase::eUnofficial )
		{
			pHome = pMatch->getMatchResultHome();
			if( pHome && pHome->getInscription() == getInscription() )
				matchesPlayed++;

			pAway = pMatch->getMatchResultAway();
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
	GSortedVector & vMatches = pPool->getMatchsVector();
	for(size_t i=0 ; i<vMatches.entries() ; i++)
	{
		pMatch = (CHMatch *)vMatches[i]->getElement();
		if (pMatch->getRound()>maxRound)
			continue;
		// Con los subpartidos no tengo que calcular puntos, ni rankings de pool, etc
		if(pMatch->getSubMatch())
			continue;
		if( pMatch && pMatch->getStatus() >= CHMemoryDataBase::eUnofficial )
		{	
			pHome = pMatch->getMatchResultHome();
			pAway = pMatch->getMatchResultAway();

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
	GSortedVector & vMatches = pPool->getMatchsVector();
	for(size_t i=0 ; i<vMatches.entries() ; i++)
	{
		pMatch = (CHMatch *)vMatches[i]->getElement();
		if (pMatch->getRound()>maxRound)
			continue;
		// Con los subpartidos no tengo que calcular puntos, ni rankings de pool, etc
		if(pMatch->getSubMatch())
			continue;
		if( pMatch && pMatch->getStatus() >= CHMemoryDataBase::eUnofficial )
		{
			pHome = pMatch->getMatchResultHome();
			if( pHome && pHome->getInscription() == getInscription() &&
				pHome->getPoints() == LOST_POINTS )
				matchesLost++;

			pAway = pMatch->getMatchResultAway();
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
	GSortedVector & vMatches = pPool->getMatchsVector();
	for(size_t i=0 ; i<vMatches.entries() ; i++)
	{
		pMatch = (CHMatch *)vMatches[i]->getElement();
		if (pMatch->getRound()>maxRound)
			continue;
		// Con los subpartidos no tengo que calcular puntos, ni rankings de pool, etc
		if(pMatch->getSubMatch())
			continue;
		if( pMatch && pMatch->getStatus() >= CHMemoryDataBase::eUnofficial )
		{
			pHome = pMatch->getMatchResultHome();
			pAway = pMatch->getMatchResultAway();

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

float CHPoolResult::getPoolPointsF(short nRound/*=0*/,RWBoolean onlyRound) const
{//se hace el acumulado a maxRound
	CHPool * pPool = (CHPool *) getPool();
	if( !pPool )
		return 0;

	short maxRound=!nRound?pPool->getNumRounds():nRound;
	float points = 0.0;
	CHMatch * pMatch = 0;
	CHMatchResult * pHome = 0;
	CHMatchResult * pAway = 0;
	GSortedVector & vMatches = pPool->getMatchsVector();
	CompareFunction oldCompare = vMatches.getCompare();
	vMatches.sort(orderMatchesByRoundMatch);

	for(size_t i=0 ; i<vMatches.entries() ; i++)
	{
		pMatch = (CHMatch *)vMatches[i]->getElement();
		if ((pMatch->getRound()>maxRound && !onlyRound) || (onlyRound && nRound && pMatch->getRound()!=nRound))
			continue;
		
		if(pMatch->isTeam() && !pMatch->getSubMatch())
			continue;

		if( pMatch && pMatch->getStatus() >= CHMemoryDataBase::eUnofficial )
		{
			pHome = pMatch->getMatchResultHome();
			if( pHome && pHome->getInscription() == getInscription() )
				points += pHome->getPoints();

			pAway = pMatch->getMatchResultAway();
			if( pAway && pAway->getInscription() == getInscription() )
				points += pAway->getPoints();
		}
	}
	vMatches.sort(oldCompare);
	return points;
}
RWCString CHPoolResult::getPoolPointsFStr(short nRound/*=0*/,RWBoolean onlyRound) const
{
	RWCString format="###";
	float points=getPoolPointsF(nRound,onlyRound);

	if((points-int(points))>0)
	{
		format="###.#"; // Decimales
		
	}

	GScore pointsF = GScore(points);
	RWCString p=pointsF.asString(format);
	
	p=p.strip(RWCString::leading,' ');
	return p;
	
}

float CHPoolResult::getPointsSO(short nRound/*=0*/,RWBoolean onlyRound/*=false*/) const
{	
	CHPool * pPool = (CHPool *) getPool();
	if( !pPool )
		return 0;

	short maxRound=!nRound?pPool->getNumRounds():nRound;
	float points = 0.0;
	CHMatch * pMatch = 0;
	CHMatchResult * pHome = 0;
	CHMatchResult * pAway = 0;
	GSortedVector & vMatches = pPool->getMatchsVector();
	CompareFunction oldCompare = vMatches.getCompare();
	vMatches.sort(orderMatchesByRoundMatch);

	for(size_t i=0 ; i<vMatches.entries() ; i++)
	{
		pMatch = (CHMatch *)vMatches[i]->getElement();
		if ((pMatch->getRound()>maxRound && !onlyRound) || (onlyRound && nRound && pMatch->getRound()!=nRound))
			continue;
		
		if(pMatch->isTeam() && !pMatch->getSubMatch())
			continue;

		if( pMatch && pMatch->getStatus() >= CHMemoryDataBase::eUnofficial )
		{
			pHome = pMatch->getMatchResultHome();
			if( pHome && pHome->getInscription() == getInscription() )
				points += pHome->getPointsSO();

			pAway = pMatch->getMatchResultAway();
			if( pAway && pAway->getInscription() == getInscription() )
				points += pAway->getPointsSO();
		}
	}
	vMatches.sort(oldCompare);
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
	GSortedVector & vMatches = pPool->getMatchsVector();
	for(size_t i=0 ; i<vMatches.entries() ; i++)
	{
		pMatch = (CHMatch *)vMatches[i]->getElement();
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


RWCString CHPoolResult::getSolkOffFStr(short nRound/*=0*/) const
{
	RWCString format="###";
	float points=getSolkOffF(nRound);

	if((points-int(points))>0)
		format="###.#"; // Decimales

	GScore pointsF = GScore(points);
	RWCString p=pointsF.asString(format);

	p=p.strip(RWCString::leading,' ');
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
	GSortedVector & vMatches = pPool->getMatchsVector();
	GSortedVector vCompetitors;
	RWBoolean hasBye=false;
	for(size_t i=0 ; i<vMatches.entries() ; i++)
	{
		pMatch = (CHMatch *)vMatches[i]->getElement();
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
		vCompetitors.sort(orderPoolResultSO);
	
		for (size_t i=1;i<vCompetitors.entries()-1;i++)
		{
			CHPoolResult* pPoolResult = (CHPoolResult*)vCompetitors[i]->getElement();
			points += float(pPoolResult->getPointsSO(maxRound));
		}

		if (hasBye)
			points+=0.5*nRoundsPlayed;
	}

	return points;
}


RWCString CHPoolResult::getMedianSolkOffFStr(short nRound/*=0*/) const
{
	RWCString format="###";
	float points=getMedianSolkOffF(nRound);

	if((points-int(points))>0)
		format="###.#"; // Decimales

	GScore pointsF = GScore(points);
	RWCString p=pointsF.asString(format);

	p=p.strip(RWCString::leading,' ');
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
	GSortedVector & vMatches = pPool->getMatchsVector();
	for(size_t i=0 ; i<vMatches.entries() ; i++)
	{
		pMatch = (CHMatch *)vMatches[i]->getElement();
		if (pMatch->getRound()>maxRound)
			continue;
		
		if(pMatch->isTeam() && !pMatch->getSubMatch())
			continue;

		if( pMatch && pMatch->getStatus() >= CHMemoryDataBase::eUnofficial )
		{
			short winner=pMatch->getWinner();
			if (winner>=CHMatch::eWinnerWhite && winner<=CHMatch::eDraw)//ganadores
			{//si es distinto es el oponente
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

RWCString CHPoolResult::getSonneBergerFStr(short nRound/*=0*/) const
{
	RWCString format="###";
	float points=getSonneBergerF(nRound);

	if((points-int(points))>0)
		format="###.##"; // Decimales

	GScore pointsF = GScore(points);
	RWCString p=pointsF.asString(format);

	p=p.strip(RWCString::leading,' ');
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
	GSortedVector & vMatches = pPool->getMatchsVector();
	CHInscription *pInscription=(CHInscription*)getInscription();
	if(!pInscription)
		return 0.0;
	int count=0;
	for(size_t i=0 ; i<vMatches.entries() ; i++)
	{
		pMatch = (CHMatch *)vMatches[i]->getElement();
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

RWCString CHPoolResult::getProgressiveFStr(short nRound/*=0*/) const
{
	RWCString format="###";
	float points=getProgresiveF(nRound);

	if((points-int(points))>0)
		format="###.#"; // Decimales

	GScore pointsF = GScore(points);
	RWCString p=pointsF.asString(format);

	p=p.strip(RWCString::leading,' ');
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
	GSortedVector & vMatches = pPool->getMatchsVector();
	for(size_t i=0 ; i<vMatches.entries() ; i++)
	{
		pMatch = (CHMatch *)vMatches[i]->getElement();
		if (pMatch->getRound()>maxRound)
			continue;
		// Con los subpartidos no tengo que calcular puntos, ni rankings de pool, etc
		
		if( pMatch && pMatch->getStatus() >= CHMemoryDataBase::eUnofficial )
		{	
			pHome = pMatch->getMatchResultHome();
			
			if( pHome && pHome->getInscription() == getInscription())
				matchesWon+=pHome->getTeamMatchesWon();

			pAway = pMatch->getMatchResultAway();
			if( pAway && pAway->getInscription() == getInscription())
				matchesWon+=pAway->getTeamMatchesWon();
		}
	}

	return matchesWon;
}

RWCString CHPoolResult::getTeamMatchesWonStr(short nRound/*=0*/) const
{
	short points=getTeamMatchesWon(nRound);

	char tmp[10];
	sprintf(tmp,"%d",points);
	
	return RWCString(tmp);
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
	GSortedVector & vMatches = pPool->getMatchsVector();
	for(size_t i=0 ; i<vMatches.entries() ; i++)
	{
		pMatch = (CHMatch *)vMatches[i]->getElement();
		if (pMatch->getRound()>maxRound)
			continue;
		// Con el partido general no tengo que calcular puntos, ni rankings de pool, etc
		if(pMatch->isTeam() && !pMatch->getSubMatch())
			continue;
		
		if( pMatch && pMatch->getStatus() >= CHMemoryDataBase::eUnofficial )
		{	
			pHome = pMatch->getMatchResultHome();
			
			if( pHome && pHome->getInscriptionKey() == getInscriptionKey())
				PointsFR+=float(pHome->getPoints());

			pAway = pMatch->getMatchResultAway();
			if( pAway && pAway->getInscriptionKey() == getInscriptionKey())
				PointsFR+=float(pAway->getPoints());
		}
	}
	return PointsFR;
}

RWWString CHPoolResult::getGroup() const
{
	return RWWString(GTHPoolResult::getGroup(),RWWString::multiByte);
}

RWCString CHPoolResult::getIsoCountry() const
{
	return getRegister() ? getRegister()->getIsoCountry() : "";
}

RWWString CHPoolResult::getDescription(RWBoolean longDescription/*=true*/) const
{
	// Tiene registro : nombre del equipo
	CHRegister * pRegister = (CHRegister *) getRegister();
	if( pRegister )
		return longDescription?pRegister->getPrnSName():TOWSTRING(pRegister->getGroup());

	// Es una pool : numero de orden
	if( getIsPool() )
		return TOWSTRING(getOrder());

	// Best ranking position : 2º Rk 3 || 2º (A3,B3,C3)
	RWWString txt;
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
		GSortedVector & vPools = pPhaseSource->getPoolsVector();
		for(size_t i=0 ; i<vPools.entries() ; i++)
		{
			pPool = (CHPool *)vPools[i]->getElement();
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

	CHMatch * pMatchSource = (CHMatch *) pPoolSource->getMatchsVector()[0]->getElement();
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

RWWString CHPoolResult::getSourceCompetitor()
{
	RWWString idcompetitor(NULLRWWSTRING);
	
	GTHPhase * pPhaseSource=getPointerPhaseSource();
	CHPool * pPoolSource=(CHPool*)getPointerPoolSource();
	wchar_t aux[20];
	memset(aux,0,sizeof(aux));
	if(!pPhaseSource )
	{
		idcompetitor+=_itow(int(getOrder()),aux,10);
		idcompetitor+=_T(" ");
		if (getPool())
			idcompetitor+=((CHPool*)getPool())->getLDescription(GTHPhase::eText);			
	}		
	else if( pPhaseSource->getIsPool() && getRankingSource() )
	{
		idcompetitor+=_itow(int(getRankingSource()),aux,10);
		idcompetitor+=_T(".");
		if( pPoolSource )
			idcompetitor+=pPoolSource->getLDescription(GTHPhase::eText);						
	}				
	else if( !pPhaseSource->getIsPool() )
	{
		if(getRankingSource()==1)
			idcompetitor+=RWWString("Winner ",RWWString::ascii);
		if(getRankingSource()==2)
			idcompetitor+=RWWString("Loser ",RWWString::ascii);
		if (pPoolSource &&
			pPoolSource->getMatchsVector().entries())
		{
			CHMatch* pMatch = (CHMatch*)pPoolSource->getMatchsVector()[0]->getElement();
			if (pMatch)
				idcompetitor+=_itow(int(pMatch->getMatchNumber()),aux,10);
		}
	}

	return idcompetitor;
}

RWBoolean CHPoolResult::isQualitative() const
{
	if(getQualitative() && getQualitativeCode()!=OK)
		return true;

	return false;
}

bool CHPoolResult::hasAlreadyPlayed(CHPoolResult* _pPoolResult, short lastRound)
{
	RWSet* colMatchResults=(RWSet*)CHMemoryDataBase::getColMatchResults().select(matchResultsOfPoolResult,this);
	RWSetIterator it(*colMatchResults);
		
	CHMatchResult* pMatchResult=0;
	while( (pMatchResult=(CHMatchResult*)it()) != 0)
	{
		CHMatch* pMatch = (CHMatch*) pMatchResult->getMatch();

		if (lastRound==pMatch->getRound())
			continue;
		
		CHMatchResult* pWhite = pMatch->getMatchResultHome();
		CHMatchResult* pBlack = pMatch->getMatchResultAway();

		if (_pPoolResult->getRegister()==pWhite->getRegister() ||
			_pPoolResult->getRegister()==pBlack->getRegister())
		{
			delete colMatchResults;
			return true;
		}
	}
	
	delete colMatchResults;	
	return false;
}

bool CHPoolResult::isPlayingRound(CHMatch* _pMatch, short round)
{
	RWSet* colMatchResults=(RWSet*)CHMemoryDataBase::getColMatchResults().select(matchResultsOfPoolResult,this);
	RWSetIterator it(*colMatchResults);

	CHMatchResult* pMatchResult=0;
	while( (pMatchResult=(CHMatchResult*)it()) != 0)
	{
		CHMatch* pMatch = (CHMatch*) pMatchResult->getMatch();

		if (round==pMatch->getRound() &&
			pMatch!=_pMatch)
		{
			delete colMatchResults;	
			return true;
		}		
	}
	
	delete colMatchResults;	
	return false;
}

short CHPoolResult::getNumMatchesWithColor(CHMatchResult::side color, short lastRound)
{
	short num = 0;
	
	RWSet* colMatchResults=(RWSet*)CHMemoryDataBase::getColMatchResults().select(matchResultsOfPoolResult,this);
	RWSetIterator it(*colMatchResults);
		
	CHMatchResult* pMatchResult=0;
	while( (pMatchResult=(CHMatchResult*)it()) != 0)
	{
		CHMatch* pMatch = (CHMatch*) pMatchResult->getMatch();

		if (pMatch->getRound()>=lastRound)
			continue;

		if (pMatch->getSubMatch()!=0)
			continue;


		CHMatchResult* pWhite = pMatch->getMatchResultHome();
		CHMatchResult* pBlack = pMatch->getMatchResultAway();

		if (getRegister()==pWhite->getRegister() && 
			color == CHMatchResult::eWhite)
			num++;
		{
			if (getRegister()==pBlack->getRegister() && 
				color == CHMatchResult::eBlack)
				num++;
		}		
	}	
	
	delete colMatchResults;
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
		RWSet* colMatchResults=(RWSet*)CHMemoryDataBase::getColMatchResults().select(matchResultsOfPoolResult,this);
		RWSetIterator it(*colMatchResults);
		
		CHMatchResult* pMatchResult=0;
		while( (pMatchResult=(CHMatchResult*)it()) != 0)
		{	
			CHMatch* pMatch = (CHMatch*)pMatchResult->getMatch();

			if (pMatch->getRound()==round)
				continue;

			if (pMatch->getRound()==round-1)
			{
				CHMatchResult* pWhite = pMatch->getMatchResultHome();
				CHMatchResult* pBlack = pMatch->getMatchResultAway();

				if (pWhite->getRegister() == getRegister())
					return CHMatchResult::eBlack;
				if (pBlack->getRegister() == getRegister())
					return CHMatchResult::eWhite;
			}
		}
		delete colMatchResults;
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
		RWSet* colMatchResults=(RWSet*)CHMemoryDataBase::getColMatchResults().select(matchResultsOfPoolResult,this);
		RWSetIterator it(*colMatchResults);
		
		CHMatchResult* pMatchResult=0;
		while( (pMatchResult=(CHMatchResult*)it()) != 0)
		{	
			CHMatch* pMatch = (CHMatch*)pMatchResult->getMatch();

			if (pMatch->getRound()==round)
				continue;

			if (pMatch->getRound()==round-1)
			{
				CHMatchResult* pWhite = pMatch->getMatchResultHome();
				CHMatchResult* pBlack = pMatch->getMatchResultAway();

				if (pWhite->getRegister() == getRegister())
					return CHMatchResult::eBlackModerate;
				if (pBlack->getRegister() == getRegister())
					return CHMatchResult::eWhiteModerate;
			}
		}
		delete colMatchResults;
	}
	return CHMatchResult::eDraw;
}

bool CHPoolResult::hasAlreadyBye(short lastRound)
{
	RWSet* colMatchResults=(RWSet*)CHMemoryDataBase::getColMatchResults().select(matchResultsOfPoolResult,this);
	RWSetIterator it(*colMatchResults);
	
	CHMatchResult* pMatchResult=0;
	while( (pMatchResult=(CHMatchResult*)it()) != 0)
	{
		CHMatch* pMatch = (CHMatch*) pMatchResult->getMatch();
		if (pMatch->getRound()==lastRound)
			continue;
		if (pMatch->isBye())
		{
			delete colMatchResults;
			return true;
		}
	}
	delete colMatchResults;
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

	for(size_t i=0;i<pPool->getPoolResultsVector().entries();i++)
	{
		pPoolResult=(CHPoolResult*)pPool->getPoolResultsVector()[i]->getElement();
		if(pMatch)
			 totalPoints+=pPoolResult->getPoolPointsF(pMatch->getRound());
		else totalPoints+=pPoolResult->getPointsF();

	}
	totalPoints/=short(pPool->getPoolResultsVector().entries());

	return totalPoints;
}