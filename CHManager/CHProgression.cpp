/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHProgression.cpp
*	Description	: Implementation for the CHProgression class.
*
*	Author		: Chess Team
*	Date created: 15-12-2005
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
#include "CHProgression.h"
#include "CHStatusManager.h"
#include "CHEvenControlOperations.h"
#include <CORE/G/GMsgDefines.h>
#include <CORE/TH/GTHMsgDefines.h>
#include <CORE/TH/GTHOrderFunctions.h>
#include <SPORTS/CH/DATA/CHMsgDefines.h>
#include <SPORTS/CH/DATA/CHSportDefines.h>
#include <SPORTS/CH/DATA/CHDiscipline.h>

#include <SPORTS/CH/DATA/CHPhase.h>
#include <SPORTS/CH/REPORTS\CHRoundDraw.h>

///////////////////////////////////////////////////////////////////////////
//Order Functions
///////////////////////////////////////////////////////////////////////////
static 
int orderByMemberFunction(const GVectorElement** a, const GVectorElement** b)
{
	CHMember *pA=(CHMember *)(*a)->getElement();
	CHMember *pB=(CHMember *)(*b)->getElement();

	if(!pA->getFunction() && pB->getFunction())
		return 1;

	if(pA->getFunction() && !pB->getFunction() ) 
		return -1;
	
	int rc=pA->getFunction() - pB->getFunction();
	if(rc)
		return rc;

	return _wcsicoll(pA->getPrnLName(), pB->getPrnLName());
}
///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
CHProgression::CHProgression(CHMemoryDataBase * pMem)
:GTHProgression(pMem)
{
	m_pMem = (CHMemoryDataBase *) pMem;
}

////////////////////////////////////////////////////////////////////////////////////
CHProgression::~CHProgression()
{

}

////////////////////////////////////////////////////////////////////////////////////
GTHPhase * CHProgression::getNewPhase()
{
	return new CHPhase();
}

////////////////////////////////////////////////////////////////////////////////////
GTHPool * CHProgression::getNewPool()
{
	return new CHPool();
}

////////////////////////////////////////////////////////////////////////////////////
GTHPoolResult * CHProgression::getNewPoolResult()
{
	return new CHPoolResult();
}

////////////////////////////////////////////////////////////////////////////////////
GTHMatch * CHProgression::getNewMatch()
{
	return new CHMatch();
}

////////////////////////////////////////////////////////////////////////////////////
GTHMatchResult * CHProgression::getNewMatchResult()
{
	return new CHMatchResult();
}

////////////////////////////////////////////////////////////////////////////////////
GTHSplitMatchResult * CHProgression::getNewSplitMatchResult()
{
	return new CHSplitMatchResult();
}

////////////////////////////////////////////////////////////////////////////////////
GTHMatchMember * CHProgression::getNewMatchMember()
{
	return new CHMatchMember();
}

////////////////////////////////////////////////////////////////////////////////////
GTHStatusManager * CHProgression::getNewStatusManager()
{
	return new CHStatusManager();
}

////////////////////////////////////////////////////////////////////////////////////
RWBoolean CHProgression::onCreatePoolResult(GTHPoolResult * pPoolResult,GTHModalityPhase * pModalityPhase)
{
	((CHPoolResult*)pPoolResult)->setQualitative(OK);
	return true;

	UNREFERENCED_PARAMETER(pModalityPhase);
}

RWBoolean CHProgression::onCreateMatchResult(GTHMatchResult * pMatchResult,GTHModalityPhase * pModalityPhase)
{
	((CHMatchResult*)pMatchResult)->setQualitative(OK);	
	((CHMatchResult*)pMatchResult)->setPoolPosition(0);
	if(pMatchResult->getPosition()==1)
		((CHMatchResult*)pMatchResult)->setColor(CHMatchResult::eWhite);
	if(pMatchResult->getPosition()==2)
		((CHMatchResult*)pMatchResult)->setColor(CHMatchResult::eBlack);

	
	return true;

	UNREFERENCED_PARAMETER(pModalityPhase);
}

//virtual
RWBoolean CHProgression::onCreateMatch(GTHMatch * pMatch,GTHModalityPhase * pModalityPhase)
{
	// Set match type...
	CHMatch *pCHMatch=(CHMatch *)pMatch;
	pCHMatch->setMatchType(short(pCHMatch->getEventMode()));

	APP::out(*pCHMatch,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
	
	if(((CHMatch*)pMatch)->areTeamIndividual())
	{
		createConfrontationMatches((CHMatch*)pMatch);
	}
	//el out con parametros lo hago yo.
	return false; 

	UNREFERENCED_PARAMETER(pModalityPhase);
}


RWBoolean CHProgression::onCreatePoolResult(GTHPoolResult * pPoolResult)
{
	((CHPoolResult*)pPoolResult)->setQualitative(OK);
	return true;
}

RWBoolean CHProgression::onCreateMatchResult(GTHMatchResult * pMatchResult)
{
	((CHMatchResult*)pMatchResult)->setQualitative(OK);
	((CHMatchResult*)pMatchResult)->setPoolPosition(0);
	if(pMatchResult->getPosition()==1)
		((CHMatchResult*)pMatchResult)->setColor(CHMatchResult::eWhite);
	if(pMatchResult->getPosition()==2)
		((CHMatchResult*)pMatchResult)->setColor(CHMatchResult::eBlack);
	return true;
}

//virtual
RWBoolean CHProgression::onCreateMatch(GTHMatch * pMatch)
{
	// Set match type...
	CHMatch *pCHMatch=(CHMatch *)pMatch;
	pCHMatch->setMatchType(short(pCHMatch->getEventMode()));

	CHPool* pPool = (CHPool*)pCHMatch->getPool();
	short code = (pCHMatch->getCode() - 10000) / 10;
	short round = ((code-1)/pPool->getNumMatches()) + 1;
	pCHMatch->setRound(round);
	
	//send to database..
	APP::out(*pCHMatch,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
		
	if(((CHMatch*)pMatch)->areTeams())
		createConfrontationMatches((CHMatch*)pMatch);
	
	//el out con parametros lo hago yo.
	return false; 
}


bool CHProgression::onChangeInscription(GTHInscription *pInscription, GTHMatchResult *pMatchResult)
{
	// Si es equipos y no tiene submatches no salimos
	// Esto se hace porque la GUITH envia este mensaje 2 veces uno el correcto y el otro de pega
	if (((CHMatchResult *)pMatchResult)->areTeams())
	{
		GSortedVector vMatches=((CHMatchResult *)pMatchResult)->getSubMatches();

		if(!vMatches.entries())
			return false;
	}

	bool changed=GTHProgression::onChangeInscription(pInscription,pMatchResult);
	if (!changed)
		return false;

	if (((CHMatchResult *)pMatchResult)->areTeams())
	{	// Asignamos/Deasignamos Inscripcion a los sub-Matches de Equipo en cuestion.
		GSortedVector vMatches=((CHMatchResult *)pMatchResult)->getSubMatches();
		CHMatch *pMatchAux=0;
		CHMatchResult *pSubMatchResult=0;
		short position=pMatchResult->getPosition();

		
		for(size_t i=0;i<vMatches.entries();i++)
		{
			pMatchAux = (CHMatch*)vMatches[i]->getElement();
			if(pMatchAux)
			{
				GSortedVector &vMatchResult=pMatchAux->getCompetitorsVector();
				pSubMatchResult=(CHMatchResult*)vMatchResult[position-1]->getElement();
				if (pSubMatchResult)
				{
					pSubMatchResult->setInscription(pInscription);
					int order = pMatchResult->getPoolResult()?pMatchResult->getPoolResult()->getOrder():0;
					pSubMatchResult->setPoolPosition(order);
					APP::out(*pSubMatchResult,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
				}
			}
		}
	}

	return true;
}

RWBoolean CHProgression::createConfrontationMatches(CHMatch* pMatch)
{
	// Enfrentamientos, buscamos la configuracion de los match de equipo,
	// en la phase, round y event. Si no se encuentra, no creamos sub-matches.
	CHPhase *pPhase=(CHPhase *)pMatch->getPhase();
	CHTeamMatchsCnfg *pTeamMatchsCnfg=CHMemoryDataBase::findTeamMatchsCnfg(pPhase);
	if (!pTeamMatchsCnfg)
		return false;

	// Creamos los submatch...
	for(short i=0;i<pTeamMatchsCnfg->getMatches();i++)
	{
		CHMatch aMatch;
		aMatch.setPool(pMatch->getPool());
		aMatch.setCode(short(pMatch->getCode()+i+1));
		aMatch.setSubMatch(short(i+1));
		aMatch.setNumCompetitors(pMatch->getNumCompetitors());
		aMatch.setStatus(GTHMemoryDataBase::eAvailable);
		aMatch.setMatchType(CHMatch::eTeamIndividual);
		aMatch.setRound(pMatch->getRound());
		
		CHMatch  * pMatchOut = (CHMatch *)((CHMemoryDataBase*)mem())->setMatch(aMatch);
		APP::out(*pMatchOut,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
		
		//creamos los match results
		createMatchResultsOfMatch(pMatchOut,pTeamMatchsCnfg);
	
	}
	return false; //el out con parametros lo hago yo.
}

//crea todos los CHMatchResult de un partido
void CHProgression::createMatchResultsOfMatch(CHMatch * pMatch,CHTeamMatchsCnfg *pTeamMatchsCnfg)
{
	for(short i=0 ; i<pMatch->getNumCompetitors() ; i++)
	{
		CHMatchResult *pMatchResult=createMatchResult(pMatch,i);

		// PARA EQUIPOS, MATCH MEMBERS, QUE SE SACAN DE LA CONFIGURACION DE EQUIPOS.
		createMatchMembers(pMatchResult,pTeamMatchsCnfg);		
	}
}

//creamos los CHMatchMembers de un matchResult.
void CHProgression::createMatchMembers(CHMatchResult * pMatchResult,CHTeamMatchsCnfg *pTeamMatchsCnfg)
{
	// Por defecto y para dobles.
	short nComp = short(pMatchResult->getTeamMembers());
	
	// Si equipos y hay configuracion...
	if (pTeamMatchsCnfg)
	{
		nComp = pTeamMatchsCnfg->getCompetitors();
		short nSubMatch = pMatchResult->getSubMatch();
		if (nSubMatch>0)
			nComp = pTeamMatchsCnfg->getMatchType(nSubMatch);
	}

	// Creamos los matchMembers.
	for (short n=0;n<nComp;n++)
	{
		CHMatchMember aMatchMember;
		
		aMatchMember.setMatchResult(pMatchResult);
		aMatchMember.setMatchMember(short(n+1));

		CHMatchMember *pMatchMemberOut=(CHMatchMember *)((CHMemoryDataBase*)mem())->setMatchMember(aMatchMember);
		if (pMatchMemberOut)
			APP::out(*pMatchMemberOut,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
	}
}

//crea los MatchResul de un partido
CHMatchResult * CHProgression::createMatchResult(CHMatch * pMatch,short position)
{
	CHMatchResult aMatchResult;

	aMatchResult.setMatch(pMatch);
	aMatchResult.setPosition(short(position+1));
	aMatchResult.setQualitative(OK);
	if(short(position+1)==1)
		aMatchResult.setColor(CHMatchResult::eWhite);
	if(short(position+1)==2)
		aMatchResult.setColor(CHMatchResult::eBlack);

	CHMatchResult  * pMatchResult = (CHMatchResult *)((CHMemoryDataBase*)mem())->setMatchResult(aMatchResult);
	APP::out(*pMatchResult,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);

	return pMatchResult;
}

RWBoolean CHProgression::deleteConfrontationMatches(CHMatch* pMatch)
{
	// Enfrentamientos, buscamos la configuracion de los match de equipo,
	// en la phase, round y event. Si no se encuentra, no creamos sub-matches.
	CHPhase *pPhase=(CHPhase *)pMatch->getPhase();
	CHTeamMatchsCnfg *pTeamMatchsCnfg=CHMemoryDataBase::findTeamMatchsCnfg(pPhase);
	if (!pTeamMatchsCnfg)
		return false;

	// Creamos los submatch...
	for(short i=0;i<pTeamMatchsCnfg->getMatches();i++)
	{
		CHMatch aMatch;

		aMatch.setPool(pMatch->getPool());
		aMatch.setCode(pMatch->getCode());
		aMatch.setSubMatch(short(i+1));
				
		CHMatch  * pMatchOut = (CHMatch *)((CHMemoryDataBase*)mem())->removeMatch(aMatch);
		APP::out(*pMatchOut,OP_DELETE,TO_VENUE|TO_DATABASE);
		
		//Borramos los match results
		deleteMatchResultsOfMatch(pMatchOut,pTeamMatchsCnfg);
	}
	return false; //el out con parametros lo hago yo.
}

//borra todos los CHMatchResult de un partido
void CHProgression::deleteMatchResultsOfMatch(CHMatch * pMatch,CHTeamMatchsCnfg *pTeamMatchsCnfg)
{
	for(short i=0 ; i<pMatch->getNumCompetitors() ; i++)
	{
		CHMatchResult *pMatchResult=deleteMatchResult(pMatch,i);
		
		// PARA EQUIPOS, MATCH MEMBERS, QUE SE SACAN DE LA CONFIGURACION DE EQUIPOS.
		deleteMatchMembers(pMatchResult,pTeamMatchsCnfg);
	}
}

//borra un CHMatchResult de un partido
CHMatchResult * CHProgression::deleteMatchResult(CHMatch * pMatch,short position)
{
	CHMatchResult aMatchResult;

	aMatchResult.setMatch(pMatch);
	aMatchResult.setPosition(short(position+1));
	CHMatchResult  * pMatchResult = (CHMatchResult *)((CHMemoryDataBase*)mem())->removeMatchResult(aMatchResult);
	APP::out(*pMatchResult,OP_DELETE,TO_VENUE|TO_DATABASE);
	
	return pMatchResult;
}

//Borra los MatchMembers de un MatchResul de un partido
void CHProgression::deleteMatchMembers(CHMatchResult * pMatchResult,CHTeamMatchsCnfg *pTeamMatchsCnfg)
{
	short nComp = pTeamMatchsCnfg->getCompetitors();
	short nSubMatch = pMatchResult->getSubMatch();
	if (nSubMatch>0)
		nComp = pTeamMatchsCnfg->getMatchType(nSubMatch);

	for (short n=0;n<nComp;n++)
	{
		CHMatchMember aMatchMember;
		
		aMatchMember.setMatchResult(pMatchResult);
		aMatchMember.setMatchMember(short(n+1));

		CHMatchMember *pMatchMemberOut=(CHMatchMember *)((CHMemoryDataBase*)mem())->removeMatchMember(aMatchMember);
		if (pMatchMemberOut)
			APP::out(*pMatchMemberOut,OP_DELETE,TO_VENUE|TO_DATABASE);
	}
}

short CHProgression::getMatchCode(GTHPhase * pPhase)
{
	/*short newMatch=GTHProgression::getMatchCode(pPhase);
	
	// Reducimos el match code.
	if (newMatch>cKindTeam)
	{
		newMatch=short(newMatch-cKindTeam);
		newMatch=short(newMatch/cStepTeam);
	}*/
	return 0;
}

short CHProgression::getYourMatchCode(GTHPool * pPool,short matchCode,bool addMatch)
{
	UNREFERENCED_PARAMETER(addMatch);
	UNREFERENCED_PARAMETER(pPool);

	// Se esta añadiendo un math, rectificamos..
	short newMatch=matchCode;
	if (matchCode>cKindTeam)
	{
		newMatch=short(newMatch-cKindTeam);
		newMatch=short(newMatch/cStepTeam+1);
	}
	newMatch =short(cKindTeam+newMatch*cStepTeam);

	return newMatch;
} 
////////////////////////////////////////////////////////////////////////////////////
void CHProgression::clearMatch(CHMatch * pMatch)
{
	APP::out(TRN_CHANGE_MATCH);
	APP::out(*pMatch,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
	APP::out();
}

////////////////////////////////////////////////////////////////////////////////////
void CHProgression::clearMatchResults(CHMatch * pMatch)
{
	APP::out(TRN_CHANGE_MATCHRES);

	CHMatchResult * pMatchResult = 0;
	GSortedVector & vMatchResult = pMatch->getCompetitorsVector();
	for(size_t i=0 ; i<vMatchResult.entries() ; i++)
	{
		pMatchResult = (CHMatchResult *)vMatchResult[i]->getElement();
		if( pMatchResult )
		{
			pMatchResult->setPoints(0);
			pMatchResult->setBye(false);
			pMatchResult->setRanking(0);
			pMatchResult->setRankingPosition(0);
			pMatchResult->setQualitative(OK);
			
			APP::out(*pMatchResult,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
		}
	}

	APP::out();
}

////////////////////////////////////////////////////////////////////////////////////
void CHProgression::setProgression(GTHPool * pPool)
{
	GTHProgression::setProgression(pPool);
}

////////////////////////////////////////////////////////////////////////////////////
void CHProgression::setProgression(GTHPhase * pPhase)
{
	GTHProgression::setProgression(pPhase);
}

void CHProgression::removeCompetitors(CHPhase* pPhase)
{
	CHPoolResult* pPoolResult=0;
	
	for (size_t i=0;i<pPhase->getPoolsVector().entries();i++)
	{
		CHPool* pPool = (CHPool*)pPhase->getPoolsVector()[i]->getElement();
		for (size_t j=0;j<pPool->getPoolResultsVector().entries();j++)
		{
			pPoolResult = (CHPoolResult*) pPool->getPoolResultsVector()[j]->getElement();
			if (pPoolResult->getInscription())
			{
				unprogressPoolResult(pPoolResult,false);
				APP::out(TRN_CHANGE_POOLRES);
				progressInscription(0,pPoolResult,false);						

				if (pPoolResult->getBye())
				{
					pPoolResult->setBye(false);
					APP::out(*pPoolResult,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
				}			
				APP::out();
			}
		}
	}
}	

bool CHProgression::unprogressUserMatch(GTHMatch *pMatch, bool cascade)
{
	
	CHEvenControlOperations eventControlOp((CHMemoryDataBase*)mem());
	if (!eventControlOp.clearResults((CHMatch*)pMatch))
		return true;
	return false;
}

RWBoolean CHProgression::isLastRound(CHMatch *pMatch)
{
	if(!pMatch)
		return true;

	CHPool *pPool=(CHPool*)pMatch->getPool();

	if(pMatch->getRound()==pPool->getNumRounds())
		return true;

	return false;
}

unsigned char CHProgression::nextRoundStatus(CHMatch *_pMatch)
{
	RWBoolean isFinished=false;
	RWBoolean isStartList=false;
	CHPool* pPool = (CHPool*)_pMatch->getPool();
	CHMatch* pMatch=0;

	for (size_t i=0;i<pPool->getMatchsVector().entries();i++)
	{
		pMatch = (CHMatch*) pPool->getMatchsVector()[i]->getElement();
		if (pMatch->getRound()==_pMatch->getRound()+1 && pMatch->getSubMatch()==0)
		{
			if (pMatch->getStatus()==CHMemoryDataBase::eRunning)
				return CHMemoryDataBase::eRunning;
			else if (pMatch->getStatus()==CHMemoryDataBase::eProtested)
				return CHMemoryDataBase::eProtested;
			else if (pMatch->getStatus()==CHMemoryDataBase::eFinished ||
					 pMatch->getStatus()==CHMemoryDataBase::eUnofficial)
			{
				isStartList=false;
				isFinished=true;
			}
			else
			{
				if (!isFinished)
					isStartList=true;
			}
		}
	}
	if (isFinished)
		return CHMemoryDataBase::eFinished;

	if (isStartList)
		return CHMemoryDataBase::eStartList;

	return CHMemoryDataBase::eStartList;
}

RWBoolean CHProgression::progressRound(CHMatch* pMatch, short round)
{
	if (!isFinishRound((CHPool*)pMatch->getPool(),round))
		return false;

	CHDiscipline aDiscipline = (CHDiscipline&) CHMemoryDataBase::getDiscipline();
	if (!aDiscipline.getAutoProg())
		return false;
	
	int doIt=RET_YES;
	doIt=::msg("Warning","Do you want to progress competitors to the next round manually?",ICO_W,MSG_YESNO);
	if (doIt==RET_YES)
		return false;
	
	RWSet colMatchResults;
	CHRoundDraw aRoundDraw(colMatchResults,(CHPool*)pMatch->getPool(),round+1);
	aRoundDraw.doDraw(CHRoundDraw::eMonrad);

	RWSetIterator it(colMatchResults);
	CHMatchResult *pMatchResult=0;
	APP::out(TRN_CHANGE_MATCHRES);
	while((pMatchResult=(CHMatchResult *)it())!=0)
	{
		onChangeInscription(pMatchResult->getInscription(),pMatchResult);
		APP::out(*pMatchResult,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
	}
	APP::out();
	return true;
}

RWBoolean CHProgression::isFinishRound(CHPool* pPool, short round)
{
	CHMatch* pMatch=0;
	for (size_t i=0;i<pPool->getMatchsVector().entries();i++)
	{
		pMatch = (CHMatch*) pPool->getMatchsVector()[i]->getElement();
		if (pMatch->getRound()==round &&
			pMatch->getStatus()!=CHMemoryDataBase::eFinished &&
			!pMatch->getSubMatch())
			return false;
	}
	return true;
}

void CHProgression::sendTransactionMatchProgress(CHMatch *pMatch)
{
	APP::out(TRN_PROGRESS_MATCH);
	APP::out(*pMatch,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
	APP::out();
}

GTHInscription*	CHProgression::getInscriptionSeed(GTHEvent * pEvent,short seed)
{
	RWSetIterator iter2(CHMemoryDataBase::getColInscriptions());
	CHInscription *pInscription = 0;
	while((pInscription = (CHInscription *)iter2() ) != 0)
	{
		if(pInscription->getEvent() == pEvent)
		{
			if(pInscription->getSeed() && pInscription->getSeed() == seed)
				return pInscription;			
		}
	}
	return 0;
}	

RWBoolean CHProgression::changeTeamsOrder(CHMatchResult* pHome, CHMatchResult* pAway)
{
	CHPoolResult * pPRHome = (CHPoolResult *)pHome->getPoolResult();
	CHPoolResult * pPRAway = (CHPoolResult *)pAway->getPoolResult();
	if( !pPRHome || !pPRAway )
		return false;

	// Copiamos los matchMembers
	RWOrdered sMembersHome, sMembersAway;
	copyMatchMembers(pHome,sMembersHome);
	copyMatchMembers(pAway,sMembersAway);

	// Cambiamos los matchResults
	changeMatchResult(pHome,pPRAway);
	changeMatchResult(pAway,pPRHome);

	// Cambiamos los matchMembers
	changeMatchMembers(pHome,sMembersAway);
	changeMatchMembers(pAway,sMembersHome);

	return true;
}

void CHProgression::copyMatchMembers(CHMatchResult * pMatchResult, RWOrdered & vector)
{
	CHMatchMember * pMatchMember = 0;
	for(size_t i=0 ; i<pMatchResult->getMembersVector().entries() ; i++)
	{
		pMatchMember = (CHMatchMember *)pMatchResult->getMembersVector()[i]->getElement();
		vector.insert(new CHMatchMember(*pMatchMember));
	}
}

void CHProgression::changeMatchResult(CHMatchResult * pMatchResult, CHPoolResult * pPoolResult)
{
	APP::out(TRN_CHANGE_MATCHRES);
		
	if(onChangeInscription(pPoolResult->getInscription(),pMatchResult) )
	{
		pMatchResult->setBye(false);
		pMatchResult->setPoolPosition(pPoolResult->getOrder());

		APP::out(*pMatchResult,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
		
	}
	APP::out();
}

////////////////////////////////////////////////////////////////////////////////////
void CHProgression::changeMatchMembers(CHMatchResult * pMatchResult, RWOrdered & vector)
{
	APP::out(TRN_CHANGE_MATCH_MEMBERS);

	CHMatchMember *pMatchMember=0,*pNewMatchMember=0;
	if( pMatchResult->getMembersVector().entries() < vector.entries() )
	{
		
		for(size_t i=pMatchResult->getMembersVector().entries() ; i<vector.entries() ; i++)
		{
			pMatchMember = new CHMatchMember();
			pMatchMember->setActive(false);
			pMatchMember->setMatchMember(short(i+1));
			pMatchMember->setMatchResult(pMatchResult);
			pNewMatchMember = (CHMatchMember *)mem()->setMatchMember(*pMatchMember);
			APP::out(*pNewMatchMember,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
		}		
	}

	for(size_t i=0 ; i<pMatchResult->getMembersVector().entries() ; i++)
	{
		pMatchMember = (CHMatchMember *)pMatchResult->getMembersVector()[i]->getElement();
		if( i<vector.entries() )
		{
			pNewMatchMember = (CHMatchMember *)vector[i];
			pMatchMember->setMember(pNewMatchMember->getMember());
			pMatchMember->setActive(pNewMatchMember->getActive());			
		}
		else
		{
			pMatchMember->setMember(0);
			pMatchMember->setActive(false);			
		}
		APP::out(*pMatchMember,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
	}
	vector.clearAndDestroy();

	APP::out();
}

RWBoolean CHProgression::checkMatchResult(CHMatchResult * pMatchResult,CHPoolResult * pPoolResult,RWBoolean showMsgs)
{
	CHMatch* pMatch = (CHMatch*) pMatchResult->getMatch();
	if (!pMatch)
		return false;
	
	CHMatchResult* pMROpponent=0;
	if ( ((CHMatchResult*)pMatchResult)->getColor()==CHMatchResult::eWhite)
		pMROpponent=pMatch->getBlack();
	else
		pMROpponent=pMatch->getWhite();

	if (int(pPoolResult)!=1 &&
		pPoolResult &&
		pPoolResult->getRegister() && pMROpponent->getRegister() &&
		pPoolResult->getRegister()==pMROpponent->getRegister())
	{
		if (showMsgs)
			::msg("Warning!!","This competitor is playing already this match ",ICO_W,MSG_OK);
		return false;
	}

	if (int(pPoolResult)!=1 &&
		pPoolResult &&
		pPoolResult->getRegister() && 
		((CHPoolResult*)pPoolResult)->isPlayingRound(pMatch,pMatch->getRound()))
	{
		if (showMsgs)
			::msg("Warning!!","This competitor is playing already in this round",ICO_W,MSG_OK);		
		return false;
	}

	if (int(pPoolResult)!=1 && 
		pPoolResult &&
		pPoolResult->getRegister() && pMROpponent->getRegister() &&
		pPoolResult->getRegister()!=pMROpponent->getRegister() &&
		((CHPoolResult*)pPoolResult)->hasAlreadyPlayed( (CHPoolResult*) pMROpponent->getPoolResult(),pMatch->getRound()))
	{
		if (showMsgs)
			::msg("Warning!!","This match exist already in this tournament ",ICO_W,MSG_OK);		
		return false;
	}

	if (int(pPoolResult)==1 &&
		pMROpponent &&
		pMROpponent->getPoolResult() &&
		((CHPoolResult*)pMROpponent->getPoolResult())->hasAlreadyBye(pMatch->getRound()))
	{
		if (showMsgs)
			::msg("Warning!!","This competitor has already play a bye game in this tournament ",ICO_W,MSG_OK);		
		return false;
	}

	if (!pMatch->isTeam() &&
		int(pPoolResult)!=1 && 
		pPoolResult &&
		!((CHPoolResult*)pPoolResult)->canPlayInColor( CHMatchResult::side(((CHMatchResult*)pMatchResult)->getColor()),pMatch->getRound()) )
	{
		if (showMsgs)
			::msg("Warning!!","This competitor cannot play in this color again ",ICO_W,MSG_OK);		
		return false;
	}
	
	return true;
}