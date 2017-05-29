/************************************************************************************* 
*           � Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHMatch.cpp
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:07-12-2005
*   Project     :CH Model
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///

#include "stdCHMngt.h"
#include "CHMatch.h"
#include "CHMatchResult.h"
#include "CHPoolResult.h"
#include "UCHMatch.h"
#include "QCHMatch.h"
#include "CHMemoryDataBase.h"
#include "CHEvent.h"
#include "CHStatisticDefines.h"
#include "CHSportDefines.h"

#include <ovr\core\TH\GTHHistoric.h>

//////////////////////////////////////////////////////////////////////
// Order Functions
//////////////////////////////////////////////////////////////////////

static 
int orderByMatchNumber(const MSLItem** a, const MSLItem** b)
{
	CHMatch* pMatchA=(CHMatch*)(*a);
	CHMatch* pMatchB=(CHMatch*)(*b);

	
	if(pMatchA->hasByes())
		return 1;
	
	if(pMatchB->hasByes())
		return -1;

	int order=pMatchA->getMatchNumber() - pMatchB->getMatchNumber();
	if(order)
		return order;
	

	return strcmp(pMatchA->getKey(), pMatchB->getKey());
}

MSLDEFINE_ITEM(CHMatch, __CHMATCH);
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHMatch::CHMatch()
:GTHMatch()
,m_matchType(CHMatch::eNone)
,m_round(0)
{
}

CHMatch::CHMatch(const CHMatch &copy)
{
	operator =(copy);
}

CHMatch::CHMatch(const MSLBinary& aBinary)
:GTHMatch(aBinary)
,m_matchType(eNone)
,m_round(0)
{
}

CHMatch::CHMatch(GTHPool * poolMatch,short codeMatch, short codeSubMatch)
:GTHMatch(poolMatch,codeMatch,codeSubMatch)
,m_matchType(eNone)
,m_round(0)
{
}

CHMatch::~CHMatch()
{
}

//////////////////////////////////////////////////////////////////////
// Operators
//////////////////////////////////////////////////////////////////////
GData & CHMatch::operator  = (const GData& copy)
{
	if ( this != &copy )
	{
		GTHMatch::operator =(copy);

		CHMatch & aMatch = (CHMatch &)copy;

		m_matchType		= aMatch.m_matchType;		
		m_round			= aMatch.m_round;
	}
	
	return *this;
}

bool CHMatch::operator == (const GData& copy)
{
	if ( this == &copy )
		return true;
	
	CHMatch & aMatch = (CHMatch &)copy;

	return 	(	GTHMatch::operator ==(copy)				&&
				m_matchType		== aMatch.m_matchType	&&				
				m_round			== aMatch.m_round);
}

bool CHMatch::operator != (const GData& copy)
{
	return !operator==(copy);
}

MSLPack& CHMatch::pack(MSLPack& aPack) const
{
	GTHMatch::pack(aPack);

	aPack << m_matchType;
	aPack << m_round;
	
	return aPack;
}

MSLPack& CHMatch::unpack(MSLPack& aPack)
{
	GTHMatch::unpack(aPack);	
			
	aPack >> short(m_matchType);
	aPack >> m_round;
		
	return aPack;
}

UBase*  CHMatch::onU() const
{
	return new UCHMatch();
}

QBase*  CHMatch::onQ() const
{
	return new QCHMatch();	
}


//Sets

void CHMatch::setMatchType(const short value)
{ 
	m_matchType = (value);
}

void CHMatch::setRound(const short value)
{ 
	m_round = (value);
}

short CHMatch::getMatchType() const
{ 
	return m_matchType;
}
short CHMatch::getRound() const
{ 
	return m_round;
}

bool CHMatch::areTeams() const
{ 
	return (m_matchType==eTeam);
}

bool CHMatch::areTeamIndividual() const
{ 
	return (m_matchType==eTeamIndividual);
}

bool CHMatch::isEmpty()
{
	int k=0;
	MSLSortedVector vCompetitors;
	getMatchResultsVector(vCompetitors);

	while ( k < (int)vCompetitors.entries() )
	{
		GTHMatchResult *pMatchResult=(GTHMatchResult *)vCompetitors[k++];
		if (pMatchResult->getInscription())
			return false;
	}
	return true;
}

bool CHMatch::isConfigured()
{
	int k=0;

	MSLSortedVector vCompetitors;
	getMatchResultsVector(vCompetitors);

	while ( k < (int)vCompetitors.entries() )
	{
		GTHMatchResult *pMatchResult=(GTHMatchResult *)vCompetitors[k++];
		if (!pMatchResult->getInscription())
			return false;
	}
	return true;	
}

MSLString CHMatch::getResultWhiteBlackAsString() const
{
	if( getStatus() < CHMemoryDataBase::eRunning )
		return NULLSTRING;

	CHMatchResult * pWhite = 0;
	CHMatchResult * pBlack= 0;
	

	pWhite = getWhite();
	pBlack = getBlack();

	MSLString result=NULLSTRING;
	char sResult[200];
	MSLString qualita="";
	if(thereAreQualitative())
	{
		qualita=getResultWhiteBlackIncidence();
		return qualita;
	}
	memset(sResult,0,200);	
	
	// No hay qualitatives
	sprintf_s(sResult,"%s-%s",pWhite->getPointsAsString(),pBlack->getPointsAsString());
	return MSLString(sResult);
}

MSLString CHMatch::getResultAsString() const
{
	
	if( getStatus() < CHMemoryDataBase::eRunning )
		return NULLSTRING;

	CHMatchResult * pMatchResult1 = 0;
	CHMatchResult * pMatchResult2= 0;
	

	pMatchResult1 = (CHMatchResult *) getHome();
	pMatchResult2 = (CHMatchResult *) getAway();

	MSLString result=NULLSTRING;
	char sResult[200];
	MSLString qualita="";
	if(thereAreQualitative())
	{
		qualita=getResultIncidence();
		return qualita;
	}
	memset(sResult,0,200);	
	
	// No hay qualitatives
	sprintf_s(sResult,"%s-%s",pMatchResult1->getPointsAsString(),pMatchResult2->getPointsAsString());
	return MSLString(sResult);
		
}
bool CHMatch::thereAreQualitative() const
{
	
	MSLSortedVector vMatchResult;
	getMatchResultsVector(vMatchResult);

	CHMatchResult *pMatchResult=0;
	for(short i=0; i<vMatchResult.entries();i++)
	{
		pMatchResult=(CHMatchResult*)vMatchResult[i];
		if(pMatchResult)
		{
			if(pMatchResult->isQualitative())
				return true;
		}
	}

	return false;
}

MSLString CHMatch::getResultIncidence() const
{
	MSLSortedVector vMatchResult;
	getMatchResultsVector(vMatchResult);
	CHMatchResult *pMatchResult1=0;
	CHMatchResult *pMatchResult2=0;
	char qualitative[30];
	pMatchResult1=(CHMatchResult*)vMatchResult[0];
	pMatchResult2=(CHMatchResult*)vMatchResult[1];

	if(pMatchResult1->isQualitative() && pMatchResult2->isQualitative())
	{
		sprintf_s(qualitative,"%s%s-%s%s",pMatchResult1->getPointsAsString(),pMatchResult1->getQualitativeSDescription().toAscii(),pMatchResult2->getPointsAsString(),pMatchResult2->getQualitative()->getSDescription());
		
	}
	else if(pMatchResult1->isQualitative())
	{
		sprintf_s(qualitative,"%s%s-%s",pMatchResult1->getPointsAsString(),pMatchResult1->getQualitativeSDescription().toAscii(),pMatchResult2->getPointsAsString());
	}
	else if(pMatchResult2->isQualitative())
	{
		sprintf_s(qualitative,"%s-%s%s",pMatchResult1->getPointsAsString(),pMatchResult2->getPointsAsString(),pMatchResult2->getQualitativeSDescription().toAscii());
	}
	
	return MSLString(qualitative);
}

CHMatchResult * CHMatch::getWhite() const
{
	CHMatchResult* pHome= (CHMatchResult*) getHome();
	CHMatchResult* pAway= (CHMatchResult*) getAway();

	if (pHome && pHome->getColor()==CHMatchResult::eWhite)
		return pHome;

	if (pAway && pAway->getColor()==CHMatchResult::eWhite)
		return pAway;

	return pHome;
}

CHMatchResult * CHMatch::getBlack() const
{
	CHMatchResult* pHome= (CHMatchResult*) getHome();
	CHMatchResult* pAway= (CHMatchResult*) getAway();

	if (pHome && pHome->getColor()==CHMatchResult::eBlack)
		return pHome;

	if (pAway && pAway->getColor()==CHMatchResult::eBlack)
		return pAway;

	return pAway;
}


MSLString CHMatch::getResultWhiteBlackIncidence() const
{
	CHMatchResult *pWhite=getWhite();
	CHMatchResult *pBlack=getBlack();
	char qualitative[30];
	
	if(pWhite->isQualitative() && pBlack->isQualitative())
	{
		sprintf_s(qualitative,"%s%s-%s%s",pWhite->getPointsAsString(),pWhite->getQualitativeSDescription().toAscii(),pBlack->getPointsAsString(),pBlack->getQualitative()->getSDescription());		
	}
	else if(pWhite->isQualitative())
	{
		sprintf_s(qualitative,"%s%s-%s",pWhite->getPointsAsString(),pWhite->getQualitativeSDescription().toAscii(),pBlack->getPointsAsString());
	}
	else if(pBlack->isQualitative())
	{
		sprintf_s(qualitative,"%s-%s%s",pWhite->getPointsAsString(),pBlack->getPointsAsString(),pBlack->getQualitativeSDescription().toAscii());
	}
	
	return MSLString(qualitative);
}

short CHMatch::getTurn() const
{
	short turn=CHMatchResult::eWhite;
	
	if ( ((CHMatch*)this)->getHistoricNumber()>0)
	{
		GTHHistoric aHist=((CHMatch*)this)->getHistoric(((CHMatch*)this)->getHistoricNumber()-1);
		if (aHist.getValueOfData(DATA_PLAYER)==EV_WHITE)
			return CHMatchResult::eBlack;
		else if (aHist.getValueOfData(DATA_PLAYER)==EV_BLACK)
			return CHMatchResult::eWhite;
	}

	return turn;
}

short CHMatch::getNextPlayNumber() const
{
	if ( ((CHMatch*)this)->getHistoricNumber()>0)
	{
		GTHHistoric aHist=((CHMatch*)this)->getHistoric(((CHMatch*)this)->getHistoricNumber()-1);
		if (aHist.getValueOfData(DATA_PLAYER)==EV_WHITE)
			return short(aHist.getValueOfData(DATA_NUMPLAY));
		
		return short(aHist.getValueOfData(DATA_NUMPLAY)+1);		
	}
	return 1;
}

// Historico
size_t CHMatch::getHistoricDataSize()
{
	// Tenemos 8 datos distintos : 
	return defaultSize(8);
}

int	CHMatch::getResultCode() const
{
	if (getStatus()>=CHMemoryDataBase::eUnofficial)
	{
		CHMatchResult* pWhite = getWhite();
		CHMatchResult* pBlack = getBlack();

		float scoreWhite = pWhite->getPoints();
		float scoreBlack = pBlack->getPoints();

		MSLString qCodeWhite = pWhite->getQualitativeCode();
		MSLString qCodeBlack = pBlack->getQualitativeCode();

		if (scoreWhite>=1.0 &&
			scoreWhite>scoreBlack &&
			qCodeWhite==OK &&
			qCodeBlack==OK)
			return EV_WHITE_WINNER;

		else if (scoreBlack>=1.0 &&
				 scoreBlack>scoreWhite &&
				 qCodeWhite==OK &&
				 qCodeBlack==OK)
				 return EV_BLACK_WINNER;

		else if (scoreWhite>0 &&
				 scoreBlack>0 &&
				 scoreWhite==scoreBlack &&
				 qCodeWhite==OK &&
				 qCodeBlack==OK)
				 return EV_DRAW;

		else if (scoreWhite>=1.0 &&
				 scoreWhite>scoreBlack &&
				 qCodeWhite==OK &&
				 qCodeBlack!=OK)
				 return EV_WHITE_WINNER_F;

		else if (scoreBlack>=1.0 &&
				 scoreBlack>scoreWhite &&
				 qCodeWhite!=OK &&
				 qCodeBlack==OK)
				 return EV_BLACK_WINNER_F;

		else if (scoreWhite==scoreBlack &&
				 qCodeWhite!=OK &&
				 qCodeBlack!=OK)
				 return EV_DRAW_F;
	}
	return EV_EMPTY;
}

MSLString CHMatch::getTotalResult(bool onlyRound)
{
	CHMatchResult *pHome=(CHMatchResult *) getHome();
	CHMatchResult *pAway=(CHMatchResult *) getAway();
	
	char result[100]="";

	CHPoolResult *pPoolResultHome=(CHPoolResult*)pHome->getPoolResult();
	CHPoolResult *pPoolResultAway=(CHPoolResult*)pAway->getPoolResult();
	
		
	MSLString qualita="";
	if(!pPoolResultHome || !pPoolResultAway)
		return NULLSTRING;

	if(pPoolResultHome->isQualitative() && pPoolResultAway->isQualitative())
	{
		char qualitative[30];
		sprintf_s(qualitative,"%s-%s",pPoolResultHome->getQualitativeSDescription().toAscii(),pPoolResultAway->getQualitative()->getSDescription());
		return MSLString(qualitative);
	}

	if(pPoolResultHome->isQualitative())
	{
		char qualitative[30];
		sprintf_s(qualitative,"%s-%s",pPoolResultHome->getQualitativeSDescription().toAscii(),pPoolResultAway->getPoolPointsFStr(getRound()));
		return MSLString(qualitative);
	}

	if(pPoolResultAway->isQualitative())
	{
		char qualitative[30];
		sprintf_s(qualitative,"%s-%s",pPoolResultHome->getPoolPointsFStr(getRound()),pPoolResultAway->getQualitativeSDescription().toAscii());
		return MSLString(qualitative);
	}

	sprintf_s(result,"%s-%s",pPoolResultHome->getPoolPointsFStr(getRound(),onlyRound),pPoolResultAway->getPoolPointsFStr(getRound(),onlyRound));
	return MSLString(result);
}

MSLString CHMatch::getRoundAsString(bool lDesc/*=true*/,bool date/*=true*/)
{

	char tmp[20];
	MSLString m_roundDesc=NULLSTRING;
	if(lDesc)
		 sprintf_s(tmp,"Round %d", getRound());
	else sprintf_s(tmp,"R.%d", getRound());

	m_roundDesc=MSLString(tmp);
	if(date && getStartDate()!=INVALID_DATE)
		m_roundDesc+=", "+getStartDateAsString("%a %d %b %Y").toAscii();

	return m_roundDesc;
	
}
// From CHEvent
bool CHMatch::isTeam()
{
	CHEvent *pEvent=(CHEvent*)getEvent();
	if(pEvent)
		return pEvent->isTeam();

	return false;
}

MSLSortedVector CHMatch::getRoundMatches()
{
	CHMatch* pMatch=0;
	
	MSLSortedVector vMatchesRound;

	MSLSortedVector vMatches;
	if (getPool())
		getPool()->getMatchesVector(vMatches);

	for (short i=0;i<vMatches.entries();i++)
	{
		pMatch = (CHMatch*) vMatches[i];
		if(pMatch->getSubMatch())
			continue;

		if (pMatch->getRound()==getRound())
			vMatchesRound.insert(pMatch);
	}
	
	vMatchesRound.setFcCompare(orderByMatchNumber);
	vMatchesRound.sort();
	
	return vMatchesRound;

}
MSLString CHMatch::getRoundMatch()
{
	MSLString m_roundMatch=NULLSTRING;

	char tmp[10];

	sprintf_s(tmp,"%d.",getRound());

	CHMatch* pMatch=0;
	
	m_roundMatch=MSLString(tmp);
	MSLSortedVector vMatchesRound=getRoundMatches();
	
	for (short i=0;i<vMatchesRound.entries();i++)
	{
		pMatch = (CHMatch*) vMatchesRound[i];
		
		if (pMatch->getMatchNumber()==getMatchNumber())
			sprintf_s(tmp," %d",i+1);
	}

	m_roundMatch+=MSLString(tmp);
	return m_roundMatch;

}
bool CHMatch::getFinishedRound()
{		
	MSLSortedVector vMatchesRound=getRoundMatches();
	
	CHMatch *pMatch=0;
	for (short i=0;i<vMatchesRound.entries();i++)
	{
		pMatch = (CHMatch*) vMatchesRound[i];
		if(pMatch->getStatus()!=CHMemoryDataBase::eFinished)
			return false;

	}
	return true;
}

bool CHMatch::hasCompetitors(bool any/*=false*/)
{
	CHMatchResult* pMatchResult=0;
	MSLSortedVector vMatchResult;
	getMatchResultsVector(vMatchResult);

	for (short j=0; j<vMatchResult.entries(); j++)
	{
		pMatchResult=(CHMatchResult*)vMatchResult[j];
		if (!pMatchResult->getRegister() && !any)
			return false;
		else if (any && pMatchResult->getRegister())
			return true;
	}
	return (!any);
}

short CHMatch::getWinner() const
{
	CHMatchResult *pMR1 = (CHMatchResult *)getHome();
	CHMatchResult *pMR2 = (CHMatchResult *)getAway();

	if( pMR1->isQualitative() && pMR2->isQualitative() )
	{	
		// Sin puntuacion y con incicencias los dos no hay ganador
		if(pMR1->getPoints()==pMR2->getPoints())
			return eNoWinner;
		
		// Gana el que mas puntos tenga 
		return short(pMR1->getPoints()>pMR2->getPoints() ? short(1):short(2));
	}
	else if( pMR1->isQualitative() )
	{
		return eWinnerBlack;
	}
	else if( pMR2->isQualitative() )
	{
		return eWinnerWhite;
	}
	else if( pMR1->getPoints()>pMR2->getPoints() )
		return eWinnerWhite;
	else if( pMR2->getPoints()>pMR1->getPoints() )
		return eWinnerBlack;
	else if( pMR2->getPoints()==pMR1->getPoints() && getStatus()>=CHMemoryDataBase::eUnofficial)
		return eDraw; // Tablas
	
	return eNoWinner;	// no ganador
}