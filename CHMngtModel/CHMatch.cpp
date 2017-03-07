/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
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
#include "UCHMatch.h"
#include "CHClassIDs.h"
#include "CHMemoryDataBase.h"
#include "CHStatisticDefines.h"
#include "CHSession.h"

#include <core\TH\GTHHistoric.h>

//////////////////////////////////////////////////////////////////////
// Order Functions
//////////////////////////////////////////////////////////////////////
static int orderMatchBySubMatches(const GVectorElement** a, const GVectorElement** b)
{
	CHMatch* pMatchA=(CHMatch*)(*a)->getElement();
	CHMatch* pMatchB=(CHMatch*)(*b)->getElement();

	return pMatchA->getSubMatch() - pMatchB->getSubMatch();

}
static int orderByMatchNumber(const GVectorElement** a, const GVectorElement** b)
{
	CHMatch* pMatchA=(CHMatch*)(*a)->getElement();
	CHMatch* pMatchB=(CHMatch*)(*b)->getElement();

	
	if(pMatchA->isBye())
		return 1;
	
	if(pMatchB->isBye())
		return -1;

	int order=pMatchA->getMatchNumber() - pMatchB->getMatchNumber();
	if(order)
		return order;
	

	return strcmp(pMatchA->getKey(), pMatchB->getKey());

}

static RWBoolean subMatchOfParentMatch   (const RWCollectable * col, const void * param)
{
	CHMatch* pMatch = (CHMatch*)param;
	CHMatch* pMatchAux = (CHMatch*)  col;
	if ( pMatch->getPool()->getKey() == pMatchAux->getPool()->getKey() &&
		 pMatch->getIdParent() == pMatchAux->getIdParent() &&
		 pMatchAux->getSubMatch())
		 return true;
	return false;
}

RWDEFINE_COLLECTABLE(CHMatch, __CHMATCH);
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHMatch::CHMatch()
:THSPMatch()
,pSession(0)
,pCourt(0) 
,pVenue(0)
,subMatch(0)
,matchType(CHMatch::eNone)
,round(0)
{
}

CHMatch::CHMatch(const CHMatch &copy)
{
	operator =(copy);
}

CHMatch::CHMatch(CPack &aPack)
{
	unpack(aPack);
}

CHMatch::CHMatch(const RWDBBlob& aBlob)
:THSPMatch(aBlob)
,pSession(0)
,pCourt(0)
,pVenue(0)
,subMatch(0)
,matchType(eNone)
,round(0)
{
}

CHMatch::CHMatch(CHPool *poolMatch,short codeMatch)
:THSPMatch(poolMatch,codeMatch)
,pSession(0)
,pCourt(0)
,pVenue(0)
,subMatch(0)
,matchType(eNone)
,round(0)
{
}

CHMatch::~CHMatch()
{
}

//////////////////////////////////////////////////////////////////////
// Operators
//////////////////////////////////////////////////////////////////////
CHMatch & CHMatch::operator  = (const CHMatch& copy)
{
	if ( this != &copy )
	{
		THSPMatch::operator =(copy);
		pSession	    = copy.pSession;
		pCourt		    = copy.pCourt;
		subMatch		= copy.subMatch;
		matchType		= copy.matchType;
		pVenue			= copy.pVenue;
		round			= copy.round;
	}
	
	return *this;
}

RWBoolean CHMatch::operator == (const CHMatch& copy)
{
	if ( this == &copy )
		return true;
	
	return 	(	THSPMatch::operator ==(copy)			&&
				pSession	    == copy.pSession		&&
				pCourt		    == copy.pCourt			&&	
				subMatch		== copy.subMatch		&&
				matchType		== copy.matchType		&&
				pVenue			== copy.pVenue			&&
				round			== copy.round);
}

RWBoolean CHMatch::operator != (const CHMatch& copy)
{
	return !operator==(copy);
}

RWBoolean CHMatch::uSQL(RWDBConnection& pConnect,RWBoolean remove/*=false*/)
{
	RWBoolean rc=false;

	UCHMatch upd(&pConnect);
	if( remove )
		rc=upd.remove(*this);
	else
		rc=upd.set(*this);

	return rc;

}

RWCString CHMatch::msl() const
{
	GBuffer aBuffer;
	RWCString str = THSPMatch::msl();

	if(str==NULLRWSTRING)
		return str;

	short numSession = 0;
	RWCString court("");
	RWCString venue=NULLRWSTRING;
	if(pSession)
	{
		//char aux[10];
		//sprintf(aux,"%c",pSession->getSession());
		numSession=short(pSession->getSession());
	}
	if (pCourt)
	{
		char aux[10];
		sprintf(aux,"%d",pCourt->getCourt());
		court=RWCString(aux);
	}

	if (pVenue)
	{
		venue = pVenue->getVenue();
	}

	return str + RWCString( aBuffer	<< numSession
									<< court
									<< subMatch
									<< matchType
									<< venue
									<< round
									<< endLine );
}

RWCString CHMatch::mslDescription(const char *language) const
{
	return THSPMatch::mslDescription(language);
}

CPack& CHMatch::pack(CPack& aPack)
{
	short idCourt = 0;

	if (pCourt)
		idCourt = pCourt->getCourt();

	THSPMatch::pack(aPack);

	aPack << pSession;
	aPack << idCourt;
	aPack << subMatch;
	aPack << matchType;
	aPack << pVenue;
	aPack << round;
	return aPack;
}

CPack& CHMatch::unpack(CPack& aPack)
{
	long lMatchDuration=0L;
	short idCourt = 0;

	THSPMatch::unpack(aPack);	

	aPack >> ((GTHSession **) &pSession);
	aPack >> idCourt;
	aPack >> subMatch;
	aPack >> short(matchType);
	aPack >> ((GVenue **) &pVenue);
	aPack >> round;

	if (CHMatch::getVenue())
		 pCourt = GTHMemoryDataBase::findCourt(CHMatch::getVenue()->getVenue(),idCourt);
	else pCourt = 0;

	return aPack;
}
//Sets
void CHMatch::setSession(GTHSession *value)
{ 
	pSession = (CHSession *)value;
}

void CHMatch::setCourt(GCourt *value)
{ 
	pCourt = value;
}

void CHMatch::setVenue(GVenue *value)
{
	pVenue = value;
}

void CHMatch::setSubMatch(const short value )
{ 
	subMatch = value;
}

void CHMatch::setMatchType(const short value)
{ 
	matchType = (value);
}

void CHMatch::setRound(const short value)
{ 
	round = (value);
}


//Gets
GTHSession* CHMatch::getSession() const
{ 
	return (GTHSession *)pSession;
}
GCourt* CHMatch::getCourt() const
{ 
	return pCourt;
}
short CHMatch::getSubMatch() const 
{ 
	return subMatch;
}
short CHMatch::getMatchType() const
{ 
	return matchType;
}
short CHMatch::getRound() const
{ 
	return round;
}

RWCString CHMatch::getMatchNumberAsString() const
{
	RWCString aux(NULLRWSTRING);
	char tmp[10];

	short matchNumber= getMatchNumber();
	aux=itoa(matchNumber,tmp,10);

	return aux;
}

RWBoolean CHMatch::areTeams() const
{ 
	return (matchType==eTeam);
}

RWBoolean CHMatch::areTeamIndividual() const
{ 
	return (matchType==eTeamIndividual);
}

int CHMatch::getEventMode() const
{
	return ((CHEvent *)getEvent())->getMode();
}

//methods from Phase
GTHPhase::DescriptionMode CHMatch::getPhasePoolDescription() const
{
	return getPhase()->getPoolDescription();
}

//methods from Session
char CHMatch::getSessionSession()const
{
	//return getSession()?getSession()->getSession():char(0);
	if (pSession)
		return pSession->getSession();
	else
		return char(0);
}
// methods for parentMatch
CHMatch* CHMatch::getParentMatch() const
{
	CHMatch aMatch,*pMatch=0;
	aMatch.setPool(getPool());
	aMatch.setCode(short(getCode()-getSubMatch()));
	pMatch=(CHMatch*)GTHMemoryDataBase::findMatch(aMatch);
	return pMatch;
	
}

short CHMatch::getParentMatchNumber() const
{
	if (areTeamIndividual())
		return getParentMatch()->getMatchNumber();
	return 0;
}

GSortedVector CHMatch::getSubMatches()
{
	GSortedVector vSubMatches;
	RWSet* colSubMatches=0;
	if(areTeams() && !this->getSubMatch())
	{
		colSubMatches = (RWSet *) CHMemoryDataBase::getColMatchs().select(subMatchOfParentMatch,this);
		vSubMatches = GSortedVector(*colSubMatches,orderMatchBySubMatches);
	}
	delete colSubMatches;
	return vSubMatches;
}

short CHMatch::getIdParent() const
{ 
	if (getCode()>cKindTeam)
		return short((getCode()-cKindTeam)/cStepTeam); 
	
	return (getCode()); 
}

RWCString CHMatch::getIdParentAsString() const
{
	RWCString aux(NULLRWSTRING);
	char tmp[10];

	short idParent= getIdParent();
	aux=itoa(idParent,tmp,10);

	return aux;
}

//methods for matchResults
CHMatchResult * CHMatch::getMatchResultHome() const
{
	if( getCompetitorsVector().entries() < 2 )
		return 0;

	CHMatchResult * pMR1 = (CHMatchResult*)getCompetitorsVector()[0]->getElement();
	CHMatchResult * pMR2 = (CHMatchResult*)getCompetitorsVector()[1]->getElement();
	
	
	if( !pMR1 || !pMR2) // || !pMR1->getInscription() || !pMR2->getInscription() )
		return 0;

	if( pMR1->getPosition() == 1 )
		return pMR1;
	else
		return pMR2;
}

CHMatchResult * CHMatch::getMatchResultAway() const
{
	if( getCompetitorsVector().entries() < 2 )
		return 0;

	CHMatchResult * pMR1 = (CHMatchResult*)getCompetitorsVector()[0]->getElement();
	CHMatchResult * pMR2 = (CHMatchResult*)getCompetitorsVector()[1]->getElement();
	if( !pMR1 || !pMR2 ) // || !pMR1->getInscription() || !pMR2->getInscription() )
		return 0;

	if( pMR1->getPosition() == 2 )
		return pMR1;
	else
		return pMR2;
}

CHMatchResult * CHMatch::getWhite() const
{	
	if( getCompetitorsVector().entries() < 2 )
		return 0;

	CHMatchResult * pMR1 = (CHMatchResult*)getCompetitorsVector()[0]->getElement();
	CHMatchResult * pMR2 = (CHMatchResult*)getCompetitorsVector()[1]->getElement();

	if( pMR1->getColor() == CHMatchResult::eWhite )
		return pMR1;
	else
		return pMR2;
}
	
CHMatchResult * CHMatch::getBlack() const
{
	if( getCompetitorsVector().entries() < 2 )
		return 0;

	CHMatchResult * pMR1 = (CHMatchResult*)getCompetitorsVector()[0]->getElement();
	CHMatchResult * pMR2 = (CHMatchResult*)getCompetitorsVector()[1]->getElement();

	if( pMR1->getColor() == CHMatchResult::eBlack )
		return pMR1;
	else
		return pMR2;
}

//methods from Venue
GVenue * CHMatch::getVenue() const
{ 
	return pVenue;
}

RWCString CHMatch::getVenueCode() const
{
	if (pVenue)
		return (pVenue->getVenue());
	else
		return NULLRWSTRING;
}
//methods from Court
int CHMatch::getCourtCode() const
{
	//return getCourt()?getCourt()->getCourt():0;
	if (pCourt)
		return pCourt->getCourt();
	else
		return 0;
			
}

bool CHMatch::isBye()
{
	int k=0;
	while (k<(int)getCompetitorsVector().entries())
	{
		GTHMatchResult *pMatchResult=(GTHMatchResult *)getCompetitorsVector()[k++]->getElement();
		if (pMatchResult->getBye())
			return true;
	}
	return false;
}

RWBoolean CHMatch::isEmpty()
{
	int k=0;
	while (k<(int)getCompetitorsVector().entries())
	{
		GTHMatchResult *pMatchResult=(GTHMatchResult *)getCompetitorsVector()[k++]->getElement();
		if (pMatchResult->getInscription())
			return false;
	}
	return true;
}

RWBoolean CHMatch::isConfigured()
{
	int k=0;
	while (k<(int)getCompetitorsVector().entries())
	{
		GTHMatchResult *pMatchResult=(GTHMatchResult *)getCompetitorsVector()[k++]->getElement();
		if (!pMatchResult->getInscription())
			return false;
	}
	return true;	
}

RWCString CHMatch::getResultWhiteBlackAsString() const
{
	if( getStatus() < CHMemoryDataBase::eRunning )
		return NULLRWSTRING;

	CHMatchResult * pWhite = 0;
	CHMatchResult * pBlack= 0;
	

	pWhite = getWhite();
	pBlack = getBlack();

	RWCString result=NULLRWSTRING;
	char sResult[200];
	RWCString qualita="";
	if(thereAreQualitative())
	{
		qualita=getResultWhiteBlackIncidence();
		return qualita;
	}
	memset(sResult,0,200);	
	
	// No hay qualitatives
	sprintf(sResult,"%s-%s",pWhite->getPointsAsString(),pBlack->getPointsAsString());
	return RWCString(sResult);
}

RWCString CHMatch::getResultAsString() const
{
	
	if( getStatus() < CHMemoryDataBase::eRunning )
		return NULLRWSTRING;

	CHMatchResult * pMatchResult1 = 0;
	CHMatchResult * pMatchResult2= 0;
	

	pMatchResult1 = getMatchResultHome();
	pMatchResult2 = getMatchResultAway();

	RWCString result=NULLRWSTRING;
	char sResult[200];
	RWCString qualita="";
	if(thereAreQualitative())
	{
		qualita=getResultIncidence();
		return qualita;
	}
	memset(sResult,0,200);	
	
	// No hay qualitatives
	sprintf(sResult,"%s-%s",pMatchResult1->getPointsAsString(),pMatchResult2->getPointsAsString());
	return RWCString(sResult);
		
}
RWBoolean CHMatch::thereAreQualitative() const
{
	
	GSortedVector & vMatchResult=getCompetitorsVector();
	CHMatchResult *pMatchResult=0;
	for(size_t i=0; i<vMatchResult.entries();i++)
	{
		pMatchResult=(CHMatchResult*)vMatchResult[i]->getElement();
		if(pMatchResult)
		{
			if(pMatchResult->isQualitative())
				return true;
		}
	}

	return false;
}

RWCString CHMatch::getResultIncidence() const
{
	GSortedVector & vMatchResult=getCompetitorsVector();
	CHMatchResult *pMatchResult1=0;
	CHMatchResult *pMatchResult2=0;
	char qualitative[30];
	pMatchResult1=(CHMatchResult*)vMatchResult[0]->getElement();
	pMatchResult2=(CHMatchResult*)vMatchResult[1]->getElement();

	if(pMatchResult1->isQualitative() && pMatchResult2->isQualitative())
	{
		sprintf(qualitative,"%s%s-%s%s",pMatchResult1->getPointsAsString(),pMatchResult1->getQualitativeSDescription().toAscii(),pMatchResult2->getPointsAsString(),pMatchResult2->getQualitative()->getSDescription());
		
	}
	else if(pMatchResult1->isQualitative())
	{
		sprintf(qualitative,"%s%s-%s",pMatchResult1->getPointsAsString(),pMatchResult1->getQualitativeSDescription().toAscii(),pMatchResult2->getPointsAsString());
	}
	else if(pMatchResult2->isQualitative())
	{
		sprintf(qualitative,"%s-%s%s",pMatchResult1->getPointsAsString(),pMatchResult2->getPointsAsString(),pMatchResult2->getQualitativeSDescription().toAscii());
	}
	
	return RWCString(qualitative);
}

RWCString CHMatch::getResultWhiteBlackIncidence() const
{
	CHMatchResult *pWhite=getWhite();
	CHMatchResult *pBlack=getBlack();
	char qualitative[30];
	
	if(pWhite->isQualitative() && pBlack->isQualitative())
	{
		sprintf(qualitative,"%s%s-%s%s",pWhite->getPointsAsString(),pWhite->getQualitativeSDescription().toAscii(),pBlack->getPointsAsString(),pBlack->getQualitative()->getSDescription());
		
	}
	else if(pWhite->isQualitative())
	{
		sprintf(qualitative,"%s%s-%s",pWhite->getPointsAsString(),pWhite->getQualitativeSDescription().toAscii(),pBlack->getPointsAsString());
	}
	else if(pBlack->isQualitative())
	{
		sprintf(qualitative,"%s-%s%s",pWhite->getPointsAsString(),pBlack->getPointsAsString(),pBlack->getQualitativeSDescription().toAscii());
	}
	
	return RWCString(qualitative);
}

short CHMatch::getWinner() const
{
	CHMatchResult *pMR1 = (CHMatchResult *)getMatchResult(0);
	CHMatchResult *pMR2 = (CHMatchResult *)getMatchResult(1);

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

short CHMatch::getTurn() const
{
	int turn=CHMatchResult::eWhite;
	
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
			return aHist.getValueOfData(DATA_NUMPLAY);
		
		return aHist.getValueOfData(DATA_NUMPLAY)+1;		
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

		RWCString qCodeWhite = pWhite->getQualitativeCode();
		RWCString qCodeBlack = pBlack->getQualitativeCode();

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

RWCString CHMatch::getTotalResult(RWBoolean onlyRound)
{
	CHMatchResult *pHome=getMatchResultHome();
	CHMatchResult *pAway=getMatchResultAway();
	
	char result[100]="";

	CHPoolResult *pPoolResultHome=(CHPoolResult*)pHome->getPoolResult();
	CHPoolResult *pPoolResultAway=(CHPoolResult*)pAway->getPoolResult();
	
		
	RWCString qualita="";
	if(!pPoolResultHome || !pPoolResultAway)
		return NULLRWSTRING;

	if(pPoolResultHome->isQualitative() && pPoolResultAway->isQualitative())
	{
		char qualitative[30];
		sprintf(qualitative,"%s-%s",pPoolResultHome->getQualitativeSDescription().toAscii(),pPoolResultAway->getQualitative()->getSDescription());
		return RWCString(qualitative);
	}

	if(pPoolResultHome->isQualitative())
	{
		char qualitative[30];
		sprintf(qualitative,"%s-%s",pPoolResultHome->getQualitativeSDescription().toAscii(),pPoolResultAway->getPoolPointsFStr(getRound()));
		return RWCString(qualitative);
	}

	if(pPoolResultAway->isQualitative())
	{
		char qualitative[30];
		sprintf(qualitative,"%s-%s",pPoolResultHome->getPoolPointsFStr(getRound()),pPoolResultAway->getQualitativeSDescription().toAscii());
		return RWCString(qualitative);
	}

	sprintf(result,"%s-%s",pPoolResultHome->getPoolPointsFStr(getRound(),onlyRound),pPoolResultAway->getPoolPointsFStr(getRound(),onlyRound));
	return RWCString(result);
}

RWCString CHMatch::getRoundAsString(RWBoolean lDesc/*=true*/,RWBoolean date/*=true*/)
{

	char tmp[20];
	RWCString roundDesc=NULLRWSTRING;
	if(lDesc)
		 sprintf(tmp,"Round %d", getRound());
	else sprintf(tmp,"R.%d", getRound());

	roundDesc=RWCString(tmp);
	if(date && getStartDate()!=INVALID_RWDATE)
		roundDesc+=", "+getStartDateAsString("%a %d %b %Y");

	return roundDesc;
	
}
// From CHEvent
RWBoolean CHMatch::isTeam()
{
	CHEvent *pEvent=(CHEvent*)getEvent();
	if(pEvent)
		return pEvent->isTeam();

	return false;
}

GSortedVector CHMatch::getRoundMatches()
{
	CHMatch* pMatch=0;
	
	GSortedVector vMatchesRound;
	for (size_t i=0;i<getPool()->getMatchsVector().entries();i++)
	{
		pMatch = (CHMatch*) getPool()->getMatchsVector()[i]->getElement();
		if(pMatch->getSubMatch())
			continue;

		if (pMatch->getRound()==getRound())
			vMatchesRound.insert(pMatch);
	}
	
	vMatchesRound.sort(orderByMatchNumber);
	
	return vMatchesRound;

}
RWCString CHMatch::getRoundMatch()
{
	RWCString roundMatch=NULLRWSTRING;

	char tmp[10];

	sprintf(tmp,"%d.",getRound());

	CHMatch* pMatch=0;
	
	roundMatch=RWCString(tmp);
	GSortedVector vMatchesRound=getRoundMatches();
	
	for (size_t i=0;i<vMatchesRound.entries();i++)
	{
		pMatch = (CHMatch*) vMatchesRound[i]->getElement();
		
		if (pMatch->getMatchNumber()==getMatchNumber())
			sprintf(tmp," %d",i+1);
	}
	roundMatch+=RWCString(tmp);

	return roundMatch;

}
RWBoolean CHMatch::getFinishedRound()
{		
	GSortedVector vMatchesRound=getRoundMatches();
	
	CHMatch *pMatch=0;
	for (size_t i=0;i<vMatchesRound.entries();i++)
	{
		pMatch = (CHMatch*) vMatchesRound[i]->getElement();
		if(pMatch->getStatus()!=CHMemoryDataBase::eFinished)
			return false;

	}
	return true;
}

RWBoolean CHMatch::hasCompetitors(bool any/*=false*/)
{
	CHMatchResult* pMatchResult=0;
	for (size_t j=0; j<getCompetitorsVector().entries(); j++)
	{
		pMatchResult=(CHMatchResult*)(getCompetitorsVector()[j]->getElement());
		if (!pMatchResult->getRegister() && !any)
			return false;
		else if (any && pMatchResult->getRegister())
			return true;
	}
	return (!any);
}