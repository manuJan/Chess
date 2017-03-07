/*************************************************************************************
*			© Copyright MSL Software, S.L., 2001
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHStatusManager.cpp
*   Description	: CH Status Manager
*
*	Author		: Chess Team
*	Date created: 15-12-2005
* 	Project		: CH Manager
* 	Modification  history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/


#include "stdafx.h"
#include "CHManager.h"
#include "CHStatusManager.h"
#include <Sports\CH\Data\CHMatch.h>
#include <Sports\CH\Data\CHPhase.h>
#include <Sports\CH\Data\CHEvent.h>
#include <Sports\CH\Data\CHMatchResult.h>
#include <Sports\CH\Data\CHEventResult.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHStatusManager::CHStatusManager()
:GTHStatusManager(false)
{
}

CHStatusManager::~CHStatusManager()
{
}


void CHStatusManager::userPropagate(GTHMatch* pMatch,unsigned char newStatus)
{
	GStatus* pStatus = CHMemoryDataBase::findStatus(newStatus);
	if (pStatus && pStatus->getStatus()>CHMemoryDataBase::eStartList)
		return;

	CHMatch* pSelMatch = (CHMatch*)pMatch;
	CHSplitMatch* pSplitMatch=0;
	for (size_t i=0;i<pSelMatch->getSplitsMatch().entries();i++)
	{
		pSplitMatch = (CHSplitMatch*) pSelMatch->getSplitsMatch()[i]->getElement();
		runSplitMatch(*pSplitMatch,newStatus);
	}
}

void CHStatusManager::runSplitMatch(CHSplitMatch & aSplitMatch,unsigned char newStatus/*=0*/,bool makeOut /*=true */)
{
	unsigned char oldStatus=0;

	oldStatus=aSplitMatch.getStatus();
	if (newStatus>oldStatus)
		proccessSplitMatchForward(aSplitMatch,oldStatus,newStatus);	
	else
		proccessSplitMatchBack(aSplitMatch,oldStatus,newStatus);

	bool oldDoOut=doOut;
	doOut=makeOut;

	proccessOutStatus();
	
	doOut=oldDoOut;
}

void CHStatusManager::proccessSplitMatchForward(CHSplitMatch & aSplitMatch,unsigned char oldStatus,unsigned char newStatus)
{
	GStatus *pStatus=getNewStatus(oldStatus,newStatus);
	if( !pStatus || oldStatus==pStatus->getStatus() )
		return;

	newStatus=pStatus->getStatus();
	CHSplitMatch *pSplitMatch=(CHSplitMatch *)CHMemoryDataBase::findSplitMatch(aSplitMatch);
	addObject(pSplitMatch,newStatus);
}

void CHStatusManager::proccessSplitMatchBack(CHSplitMatch & aSplitMatch,unsigned char oldStatus,unsigned char newStatus)
{
	unsigned char sAvailable = unsigned char(CHMemoryDataBase::eAvailable);
	unsigned char sSchedulled= unsigned char(CHMemoryDataBase::eSchedulled);
	unsigned char sStartList = unsigned char(CHMemoryDataBase::eStartList);
	unsigned char sRunning = unsigned char(CHMemoryDataBase::eRunning);
	unsigned char sOfficial  = unsigned char(CHMemoryDataBase::eFinished);

	GStatus *pStatus=getNewStatus(oldStatus,newStatus);
	if( !pStatus || oldStatus==pStatus->getStatus() 
		|| (newStatus!=sAvailable && newStatus!=sSchedulled && newStatus!=sStartList && newStatus!=sOfficial && newStatus!=sRunning))
		return;
	
	newStatus=pStatus->getStatus();
	CHSplitMatch *pSplitMatch=(CHSplitMatch*) THSPMemoryDataBase::findSplitMatch(aSplitMatch);
	addObject(pSplitMatch,newStatus);
}
	

void CHStatusManager::addObject(CHSplitMatch* pSplitMatch,unsigned char newStatus)
{
	if( pSplitMatch && pSplitMatch->getStatus()!=newStatus )
	{
		pSplitMatch->setStatus(newStatus);
		insertObject(pSplitMatch);
	}
}

void CHStatusManager::processUserNotification(GData *pData)
{
	if(pData->isA() == __CHSPLITMATCH)
	{
		CHSplitMatch *pSplitMatch = (CHSplitMatch*)pData;
		GNotify aNotify = THSPMemoryDataBase::changeStatus(*pSplitMatch);
		APP::out(aNotify);
	}	
}

void CHStatusManager::setStatusOnly(GData *pData,unsigned char newStatus)
{
	if(pData->isA() == __CHSPLITMATCH)
		addObject((CHSplitMatch*)pData,newStatus);
	
	proccessOutStatus();
}

bool notDsq (CHMatch * pMatch)
{
	for (size_t i=0; i<pMatch->getCompetitorsVector().entries(); i++)
	{
		CHMatchResult* pMatchResult=(CHMatchResult*)pMatch->getCompetitorsVector()[i]->getElement();
		if (pMatchResult)
		{
			CHEventResult * pEventResult=(CHEventResult *)CHMemoryDataBase::findEventResult(pMatchResult->getInscription());
			if (pEventResult && pEventResult->getQualitativeCode()==DSQ)	
				return false;
		}
	}

	return true;
}

void CHStatusManager::setStatusBackPhase(CHPhase * pPhase)
{
	// extraemos el mayor status de los partidos existentes y ese ponemos como el nuevo status de la phase
	// siempre y cuando sea menor que el que había.
	

	GTHPhase *pCurrentPhase;
	GTHPool *pCurrentPool=0;
	unsigned char poolStatus=0;	

	//if (pPhase->getPoolsVector().entries())
	//	poolStatus=((GTHPool*)(pPhase->getPoolsVector()[0]->getElement()))->getStatus();

	
	for (size_t i=0;i<pPhase->getPoolsVector().entries();i++)
	{	
		pCurrentPool=(GTHPool*)pPhase->getPoolsVector()[i]->getElement();
		if (pCurrentPool->getStatus()>poolStatus)
		{
			//no contamos los partidos bye ni los descalificados por peso...
			CHMatch *pMatch = (CHMatch *)pCurrentPool->getMatchsVector()[0]->getElement();
			if (pMatch && (notDsq(pMatch)))
				poolStatus=pCurrentPool->getStatus();

		}
	}

	if (poolStatus<pPhase->getStatus() && (poolStatus!=0))	
	{
			pPhase->setStatus(poolStatus);
			insertObject(pPhase);
	}
	else
	{
		//si el mayor status es official la phase debe estar runing, porque alguna de las phase no lo esta?
		if (poolStatus==CHMemoryDataBase::eFinished)
		{
			pPhase->setStatus(CHMemoryDataBase::eRunning);
			insertObject(pPhase);
		}
	}
		//hacemos lo mismo con el evento le ponemos el status mayor de los de sus fases
	CHEvent * pEvent=(CHEvent*)pPhase->getEvent();
	if (pEvent && pEvent->getPhasesVector().entries())
		poolStatus=((CHPhase*)(pEvent->getPhasesVector()[0]->getElement()))->getStatus();
		

	for (i=0;i<pEvent->getPhasesVector().entries();i++)
	{
		pCurrentPhase=(CHPhase*)pEvent->getPhasesVector()[i]->getElement();
		if (pCurrentPhase && pCurrentPhase->getStatus()>poolStatus)		
		{
			
			poolStatus=pCurrentPhase->getStatus();
		}
	}
		

	if (poolStatus<pEvent->getStatus() && (poolStatus!=0)) 
	{		
		if( pEvent->getStatus()!=poolStatus )
		{
			pEvent->setStatus(poolStatus);
			insertObject(pEvent);
		}
		
	}
	else
	{
		//si el mayor status es official la phase debe estar running, porque alguna de las phase no lo esta?
		if (poolStatus==CHMemoryDataBase::eFinished)
		{
			pEvent->setStatus(CHMemoryDataBase::eRunning);
			insertObject(pEvent);
		}
	}

	proccessOutStatus();
}


void CHStatusManager::proccessOutStatus()
{
	
	if(doOut)
		GTHStatusManager::proccessOutStatus();
}


void CHStatusManager::sendColStatus()
{
	doOut=true;
	proccessOutStatus();
	doOut=false;
}

void CHStatusManager::proccessForward(GTHMatch&	aMatch,unsigned char oldStatus,unsigned char newStatus)
{
	GStatus *pStatus=getNewStatus(oldStatus,newStatus);
	if( !pStatus || 
		oldStatus==pStatus->getStatus() )
		return;

	newStatus=pStatus->getStatus();
	CHMatch *pMatch=(CHMatch *)GTHMemoryDataBase::findMatch(aMatch);
	CHMatch *pParentMatch=0;
	CHEvent *pEvent=(CHEvent *)pMatch->getEvent();
	CHPhase *pPhase=(CHPhase *)pMatch->getPhase();
	CHPool *pPool=(CHPool *)pMatch->getPool();
	bool progressParentMatch=false;
	GTHStatusManager::addObject(pMatch,newStatus);

	unsigned char sSchedulled= unsigned char(GTHMemoryDataBase::eSchedulled);
	unsigned char sStartList = unsigned char(GTHMemoryDataBase::eStartList);
	unsigned char sRunning   = unsigned char(GTHMemoryDataBase::eRunning);
	unsigned char sOfficial  = unsigned char(GTHMemoryDataBase::eFinished);
	unsigned char sProtested = unsigned char(GTHMemoryDataBase::eProtested);
	unsigned char sSuspend = unsigned char(CHMemoryDataBase::eSuspend);

	if (pEvent->isTeam() &&
		pMatch->getSubMatch()!=0)
	{
		progressParentMatch=true;
		pParentMatch=(CHMatch *)pMatch->getParentMatch();
	}
	
/*	if( newStatus==sSchedulled )
	{
		propagate(pMatch,newStatus);
		propagate(pMatch->getPool(),newStatus);		
		propagate(pMatch->getPhase(),newStatus);		
	}*/
	
	if( newStatus==sSchedulled ||
		newStatus==sStartList ||
		newStatus==sRunning )
	{
		if (pPool->getStatus()<newStatus)
			propagate(pMatch,newStatus);
		if (pPhase->getStatus()<newStatus)
		{
			propagate(pMatch->getPool(),newStatus);		
			propagate(pMatch->getPhase(),newStatus);		
		}
		if( progressParentMatch==true )
		{	//solo para equipos, tenemos que dar status al parent match
			proccessForward(pParentMatch,newStatus);
		}
	}
	
	if( newStatus==sOfficial)
	{
		if( progressParentMatch==true )
		{	//solo para equipos, tenemos que dar status al parent match
			proccessForward(pParentMatch,newStatus);
		}

		checkAllStatus(pMatch,newStatus);
		checkAllStatus(pMatch->getPool(),newStatus);
		checkAllStatus(pMatch->getPhase(),newStatus);		
	}

	if( newStatus==sProtested )
	{
		GTHPool *pPool=pMatch->getPool();
		if (pPool && pPool->getStatus()==sOfficial)
		{
			// propago a la pool
			propagate(pMatch,newStatus);
			if (pPhase && 
				pPhase->getStatus()==sOfficial)
			{
				propagate(pPool,newStatus);	
				GTHEvent *pEvent=(pPhase)?(GTHEvent *)pPhase->getEvent():0;
				if( pEvent && 
					pEvent->getStatus()==sOfficial )
					propagate(pPhase,newStatus);
			}
		}
	}

	if (newStatus==sSuspend)
	{
	}
}

void CHStatusManager::proccessBack	(GTHMatch&	aMatch,unsigned char oldStatus,unsigned char newStatus)
{
	unsigned char sAvailable = unsigned char(GTHMemoryDataBase::eAvailable);
	unsigned char sSchedulled= unsigned char(GTHMemoryDataBase::eSchedulled);
	unsigned char sStartList = unsigned char(GTHMemoryDataBase::eStartList);
	// ¿? unsigned char sRunning   = unsigned char(GTHMemoryDataBase::eRunning);
	unsigned char sOfficial  = unsigned char(GTHMemoryDataBase::eFinished);
	unsigned char sUnOfficial= unsigned char(GTHMemoryDataBase::eUnofficial);

	GStatus *pStatus=getNewStatus(oldStatus,newStatus);
	if( !pStatus || 
		oldStatus==pStatus->getStatus())
		return;

	newStatus=pStatus->getStatus();
	CHMatch *pMatch=(CHMatch *)GTHMemoryDataBase::findMatch(aMatch);
	CHMatch *pParentMatch=0;
	CHEvent *pEvent=(CHEvent *)pMatch->getEvent();
	bool progressParentMatch=false;
	GTHStatusManager::addObject(pMatch,newStatus);

	if (pEvent->isTeam() && 
		pMatch->getSubMatch()!=0)
	{
		progressParentMatch=true;
		pParentMatch=(CHMatch *)pMatch->getParentMatch();
	}

	if( newStatus==sAvailable || 
		newStatus==sSchedulled || 
		newStatus==sStartList || 
		newStatus==sOfficial || 
		newStatus==sUnOfficial)
	{
		checkAllStatus(pMatch,newStatus);
		checkAllStatus(pMatch->getPool(),newStatus);
		checkAllStatus(pMatch->getPhase(),newStatus);
		if(	(newStatus==sStartList || newStatus==sOfficial || newStatus==sUnOfficial) &&
			(progressParentMatch==true) )
		{	//solo para equipos, tenemos que dar status al parent match
			proccessBack(pParentMatch,newStatus);
		}
	}	
}

void CHStatusManager::proccessForward(CHMatch *pMatch,unsigned char newStatus)
{
	unsigned char sSchedulled= unsigned char(GTHMemoryDataBase::eSchedulled);
	unsigned char sStartList = unsigned char(GTHMemoryDataBase::eStartList);
	unsigned char sRunning   = unsigned char(GTHMemoryDataBase::eRunning);
	unsigned char sOfficial  = unsigned char(GTHMemoryDataBase::eFinished);
	unsigned char sProtested = unsigned char(GTHMemoryDataBase::eProtested);
	unsigned char sSuspend	 = unsigned char(CHMemoryDataBase::eSuspend);
	size_t statusRun=0,statusOff=0;
	size_t numMatches=pMatch->getSubMatches().entries();
	short realNumMatchesWin=0;
	CHMatchResult *pMatRes=0;
/*	if (pMatch->getWinner()!=0)
	{
		pMatRes=(CHMatchResult *)pMatch->getCompetitorsVector()[pMatch->getWinner()-1]->getElement();
		realNumMatchesWin=pMatRes->getPoints();
	}*/
	for (size_t i=0; i<numMatches; i++)
	{
		CHMatch *pMat=(CHMatch *)pMatch->getSubMatches()[i]->getElement();
		if (newStatus==sRunning && pMat->getStatus()==sRunning) //==sStartList)
			statusRun++;
		if (newStatus==sOfficial && pMat->getStatus()==sOfficial)
			statusOff++;
	}
	if (statusRun && newStatus==sRunning)
		GTHStatusManager::addObject(pMatch,newStatus);
	if (statusOff==numMatches && newStatus==sOfficial) /*statusOff==numMatches*/
		GTHStatusManager::addObject(pMatch,newStatus);

	UNREFERENCED_PARAMETER(sSchedulled);
	UNREFERENCED_PARAMETER(sStartList);
	UNREFERENCED_PARAMETER(sProtested);
	UNREFERENCED_PARAMETER(sSuspend);
}

void CHStatusManager::proccessBack	(CHMatch *pMatch,unsigned char newStatus)
{
	unsigned char sSchedulled= unsigned char(GTHMemoryDataBase::eSchedulled);
	unsigned char sStartList = unsigned char(GTHMemoryDataBase::eStartList);
	unsigned char sRunning   = unsigned char(GTHMemoryDataBase::eRunning);
	unsigned char sOfficial  = unsigned char(GTHMemoryDataBase::eFinished);
	unsigned char sUnOfficial= unsigned char(GTHMemoryDataBase::eUnofficial);
	unsigned char sProtested = unsigned char(GTHMemoryDataBase::eProtested);
	unsigned char sSuspend	 = unsigned char(CHMemoryDataBase::eSuspend);
	size_t statusSC=0,statusSL=0,statusRun=0,statusOff=0,statusUnOff=0,statusSusp=0;

	if (newStatus==pMatch->getStatus())
		return;
	size_t numMatches=pMatch->getSubMatches().entries();
	for (size_t i=0; i<numMatches; i++)
	{
		CHMatch *pMat=(CHMatch *)pMatch->getSubMatches()[i]->getElement();
		if (pMat->getStatus()==sUnOfficial)
			statusUnOff++;
		if (pMat->getStatus()==sOfficial)
			statusOff++;
		if (pMat->getStatus()==sRunning)
			statusRun++;
		if (pMat->getStatus()==sStartList)
			statusSL++;
		if (pMat->getStatus()==sSchedulled)
			statusSC++;
		if (pMat->getStatus()==sSuspend)
			statusSusp++;
	}
	if ((newStatus==sStartList && statusSL==numMatches) || 
		(newStatus==sOfficial && statusOff==numMatches) ||
		(newStatus==sUnOfficial && (statusOff+statusUnOff)==numMatches) || 
		(newStatus==sRunning && (statusSL+statusRun+statusOff+statusUnOff)==numMatches))
		{
			GTHStatusManager::addObject(pMatch,newStatus);
			GTHPool *pPool=pMatch->getPool();
			if (pPool && pPool->getStatus()!=sOfficial)
			{
				GTHPhase *pPhase=pMatch->getPhase();
				// propago a la pool
				propagate(pMatch,newStatus);
				if (pPhase && 
					pPhase->getStatus()!=sOfficial)
				{
					propagate(pPool,newStatus);	
					GTHEvent *pEvent=(pPhase)?(GTHEvent *)pPhase->getEvent():0;
					if( pEvent && 
						pEvent->getStatus()!=sOfficial )
						propagate(pPhase,newStatus);
				}
			}
		}
	UNREFERENCED_PARAMETER(sProtested);
}

void CHStatusManager::checkAllStatus(GTHPhase* pPhase,unsigned char newStatus)
{
	GTHStatusManager::checkAllStatus(pPhase,newStatus);
}

void CHStatusManager::checkAllStatus(GTHPool* pPool,unsigned char newStatus)
{
//	GTHStatusManager::checkAllStatus(pPool,newStatus);

	bool bOK=true;

	CHEvent *pEvent=(CHEvent *)pPool->getEvent();
	CHPhase *pPhase=(CHPhase *)pPool->getPhase();
	CHPool *pP=0;
	CHMatch *pCurrentMatch=0;
	unsigned char poolStatus=0;
	unsigned char matchStatus=0;
	
	for (size_t i=0;i<pPool->getMatchsVector().entries();i++)
	{	
		pCurrentMatch=(CHMatch*)pPool->getMatchsVector()[i]->getElement();
		if (pEvent->isTeam() && pCurrentMatch->getSubMatch()!=0)
			continue;
	
		matchStatus=pCurrentMatch->getStatus();
		if(matchStatus!=newStatus )
		{
			bOK=false;
			break;
		}
	}

	//hay que verificar si están todas las pooles finalizadas para propagate
	for (i=0; i<pPhase->getPoolsVector().entries(); i++)
	{
		pP=(CHPool *)pPhase->getPoolsVector()[i]->getElement();
		poolStatus=pP->getStatus();
		if (poolStatus!=newStatus)
		{
			bOK=false;
			break;
		}
	}

	if( bOK )
		propagate(pPool,newStatus);
}

void CHStatusManager::checkAllStatus(CHMatch* pMatch,unsigned char newStatus)
{
	bool bOK=true;

	CHEvent *pEvent=(CHEvent *)pMatch->getEvent();
	CHPool *pPool=(CHPool *)pMatch->getPool();
	CHMatch *pCurrentMatch=0;
	unsigned char matchStatus=0;	
	
	for (size_t i=0;i<pPool->getMatchsVector().entries();i++)
	{	
		pCurrentMatch=(CHMatch*)pPool->getMatchsVector()[i]->getElement();
		if (pEvent->isTeam() && pCurrentMatch->getSubMatch()!=0)
			continue;

		matchStatus=pCurrentMatch->getStatus();
		if(matchStatus!=newStatus )
		{
			bOK=false;
			break;
		}
	}

	if( bOK )
		propagate(pMatch,newStatus);
}

void CHStatusManager::saveTeamSubMatchesStatus(CHMatch* pMatch, unsigned char status)
{
	if(((CHEvent*)pMatch->getEvent())->isTeam())
	{
		GSortedVector vMatches=pMatch->getSubMatches();
		CHMatch *pMatchAux=0;
		for(size_t i=0;i<vMatches.entries();i++)
		{
			pMatchAux = (CHMatch*)vMatches[i]->getElement();
			if(pMatchAux)
			{
				run(*pMatchAux,status);
			}

		}
	}
}
