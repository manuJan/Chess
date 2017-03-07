/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHMemoryDataBase.cpp                                                                 
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
#include "CHMemoryDataBase.h"
#include "CHClassIds.h"
#include "CHInscription.h"
#include "CHEvent.h"
#include "CHPhase.h"
#include "CHMember.h"
#include "CHPoolResult.h"
#include "CHPool.h"
#include "CHMatch.h"
#include "CHMatchResult.h"
#include "CHSplitMatchResult.h"
#include "CHSplitMatch.h"
#include "CHEventResult.h"
#include "CHDiscipline.h"
#include "CHMatchJudge.h"
#include "CHMatchMember.h"
#include "CHJudge.h"
#include "CHSession.h"
#include "CHMember.h"
#include "CHRegister.h"

#include "QCHInscription.h"
#include "QCHEvent.h"
#include "QCHPhase.h"
#include "QCHMember.h"
#include "QCHPoolResult.h"
#include "QCHPool.h"
#include "QCHMatch.h"
#include "QCHMatchResult.h"
#include "QCHSplitMatchResult.h"
#include "QCHSplitMatch.h"
#include "QCHEventResult.h"
#include "QCHDiscipline.h"
#include "QCHJudge.h"
#include "QCHMatchJudge.h"
#include "QCHSession.h"
#include "QCHMatchMember.h"
#include "QCHPhaseBase.h"
#include "QCHCourt.h"
#include "QCHMasterType.h"
#include "QCHTeamMatchsCnfg.h"
#include "CHTeamMatchsCnfg.h"
#include "QCHRegister.h"
#include "QCHRatingDif.h"


// static data members
//////////////////////////////////////////////////////////////////////
RWSet CHMemoryDataBase::colTeamMatchsCnfg;		// CHTeamMatchsCnfg's collection
RWSet CHMemoryDataBase::colJudges;				// Colección de CHJudges
RWSet CHMemoryDataBase::colMasterTypes;			// Colección de CHMasterType
RWSet CHMemoryDataBase::colRatingDifs;			// Colección de CHRatingDif

extern "C" __declspec( dllexport ) GMemoryDataBase * fnGetMemory()
{
        return new CHMemoryDataBase();
}

extern "C" __declspec( dllexport ) long fnGetCollection(GMemoryDataBase *pMem,long id,RWSet &set)
{
        if (!pMem)
            return 0;

        CHMemoryDataBase *pMyMem=(CHMemoryDataBase *) pMem;

        switch (id)
        {
			//G Collections
        case 1: set=pMyMem->getColGroups();				return 1;
        case 2: set=pMyMem->getColCountries();			return 1;      
        case 3: set=pMyMem->getColSex();				return 1;
        case 4: set=pMyMem->getColVenues();				return 1;      
        case 5: set=pMyMem->getColRegisters();			return 1;
        case 6: set=pMyMem->getColEvents();				return 1;      
        case 7: set=pMyMem->getColPhases();				return 1;
        case 8: set=pMyMem->getColEventUnits();			return 1;      
        case 9: set=pMyMem->getColFunctions();			return 1;
        case 10: set=pMyMem->getColInscriptions();		return 1;      
        case 11: set=pMyMem->getColCategories();		return 1;
        case 12: set=pMyMem->getColRegisterTypes();		return 1;      
        case 13: set=pMyMem->getColMedal();				return 1;
        case 14: set=pMyMem->getColMedallist();			return 1;      
        case 15: set=pMyMem->getColPosition();			return 1;
        case 16: set=pMyMem->getColPhaseNames();		return 1;      
        case 17: set=pMyMem->getColEUnitNames();		return 1;
        case 18: set=pMyMem->getColCourts();			return 1;      

			//GTH Collections
        case 19: set=pMyMem->getColPools();				return 1;
        case 20: set=pMyMem->getColMatchs();			return 1;      
        case 21: set=pMyMem->getColPoolResults();		return 1;
        case 22: set=pMyMem->getColModality();			return 1;      
        case 23: set=pMyMem->getColModalityPhase();		return 1;
        case 24: set=pMyMem->getColProgMatchPosition(); return 1;      
        case 25: set=pMyMem->getColRounds();			return 1;
        case 26: set=pMyMem->getColRoundsGeneric();		return 1;      
        case 27: set=pMyMem->getColMatchResults();		return 1;
        case 28: set=pMyMem->getColProgPoolPosition();  return 1;      
        case 29: set=pMyMem->getColSplitMatchResult();  return 1;
        case 30: set=pMyMem->getColSplitPoolResult();	return 1;      
        case 31: set=pMyMem->getColSessions();			return 1;
        case 32: set=pMyMem->getColMatchMember();		return 1;      
        case 33: set=pMyMem->getColMatchJudge();		return 1;
        case 34: set=pMyMem->getColEventResult();		return 1;     
			
			//THSP Collections
        case 35: set=pMyMem->getColSplitPhase();		return 1;
        case 36: set=pMyMem->getColSplitMatch();		return 1;      
        case 37: set=pMyMem->getColModalitySplitPhase();return 1;

			//CH Collections
        case 38: set=pMyMem->getColJudges();			return 1;      
		case 39: set=pMyMem->getColMasterTypes();		return 1;      
		case 40: set=pMyMem->getColTeamMatchsCnfg();	return 1;      
		case 41: set=pMyMem->getColRatingDifs();		return 1;      
	
        }
        return 0;
}

static
int orderGreens(const GVectorElement** a, const GVectorElement** b)
{
	CHCourt* pCourtA=(CHCourt*)(*a)->getElement();
	CHCourt* pCourtB=(CHCourt*)(*b)->getElement();

	if(pCourtA->getCourt() && pCourtB->getCourt())
		 return pCourtA->getCourt() - pCourtB->getCourt();
	
	return strcmp(pCourtA->getKey(),pCourtB->getKey());
}


CHMemoryDataBase::CHMemoryDataBase()
:THSPMemoryDataBase()
{
}

CHMemoryDataBase::~CHMemoryDataBase()
{ 
	resetChild(); 
}


void CHMemoryDataBase::resetChild()
{
	THSPMemoryDataBase::resetChild();

	colTeamMatchsCnfg.clearAndDestroy();
	colJudges.clearAndDestroy();
	colMasterTypes.clearAndDestroy();
	colRatingDifs.clearAndDestroy();
		
}


GRegister * CHMemoryDataBase::setRegister(const GRegister& target)
{
	CHRegister & aRegister = (CHRegister &)target;
	CHRegister * pRegister = (CHRegister *)findRegister(aRegister);
	if( !pRegister )  
		pRegister = (CHRegister *)(getColRegisters().insert( new CHRegister(aRegister)));
		
	else 
	{
		if( pRegister != &aRegister )
			*pRegister = aRegister;
	}
	return pRegister;
}

GEventUnit *CHMemoryDataBase::setEventUnit(const GEventUnit& target)
{ 
	return 0;
	UNREFERENCED_PARAMETER(target); 
}


///////////////////////////////////////////////////////////////////////
/////////// SET'S
///////////////////////////////////////////////////////////////////////

GInscription * CHMemoryDataBase::setInscription(const GInscription& target)
{
	CHInscription & inscription = (CHInscription &) target;
	CHInscription * pInscription  = (CHInscription *) getColInscriptions().find (& inscription);
	if (! pInscription)
	{
		pInscription = new CHInscription(inscription);
		getColInscriptions().insert(pInscription); 
	}
	else // Update
		* pInscription = inscription;

	return pInscription;
}


GEvent * CHMemoryDataBase::setEvent(const GEvent& target)
{
	CHEvent & event = (CHEvent&) target; 
	CHEvent * pEvent = (CHEvent *) getColEvents().find (& event); 
	if (!pEvent)
	{
		pEvent = new CHEvent(event); // LLamo al cons. copia pCHa creCH el objeto
		getColEvents().insert(pEvent);
	}
	else 
		* pEvent = event;

	return pEvent;
}

GMember * CHMemoryDataBase::setMember(const GMember &target)
{
	CHMember &member = (CHMember &) target; 
	CHMember *pMember = (CHMember *)getColMember().find (& member);

	if(!pMember)
	{
		pMember = (CHMember *)getColMember().insert(new CHMember(member));
		// Lo insertamos en el vector de la inscripción
		((GTHInscription *)pMember->getInscription())->setMember(pMember);
	}
	else
	{
		*pMember = member;

		CHInscription * pInsc=(CHInscription*)pMember->getInscription();
		CompareFunction cmpFn=pInsc->getMembersVector().getCompare();
		pInsc->getMembersVector().sort(cmpFn);
	}

	return pMember;
}

CHJudge* CHMemoryDataBase::setJudge(const CHJudge& aJudge)
{
	CHJudge *pJudge = (CHJudge *)findJudge(aJudge);

	if (!pJudge)
		pJudge=(CHJudge*)colJudges.insert(new CHJudge(aJudge));
	else 
		*pJudge=aJudge;

	return pJudge;
}


GPhase * CHMemoryDataBase::setPhase(const GPhase& target)
{
	CHPhase & aPhase = (CHPhase&) target; 

	CHPhase * pPhase = (CHPhase *) getColPhases().find (& aPhase);
	if (!pPhase)
	{
		pPhase =(CHPhase*)getColPhases().insert(new CHPhase(aPhase));
		if (pPhase)
			pPhase->addToObjects();
	}
	else 
		* pPhase = aPhase;

	return pPhase;
}

GTHPool * CHMemoryDataBase::setPool (const GTHPool & target)
{
	CHPool & aPool = (CHPool &)target;

	CHPool * pPool= (CHPool *) getColPools().find(&aPool);
	if( !pPool )
	{
		pPool = (CHPool *)getColPools().insert( new CHPool(aPool) );
		if (pPool)
			pPool->addToObjects();
	}
	else
       *pPool=aPool;

	return pPool;
}

GTHPoolResult * CHMemoryDataBase::setPoolResult (const GTHPoolResult & target)
{
	CHPoolResult & aPoolResult = (CHPoolResult &)target;

	CHPoolResult * pPoolResult= (CHPoolResult *) getColPoolResults().find(&aPoolResult);

	if( !pPoolResult )
	{
		pPoolResult = (CHPoolResult *)getColPoolResults().insert( new CHPoolResult(aPoolResult) ); 
		if (pPoolResult)
			pPoolResult->addToObjects();
	}
	else
       *pPoolResult=aPoolResult;

	return pPoolResult;
}

GTHMatch * CHMemoryDataBase::setMatch (const GTHMatch & target)
{
	CHMatch & aMatch = (CHMatch &)target;

	CHMatch * pMatch= (CHMatch *) getColMatchs().find(&aMatch);
	if( !pMatch )
	{
		pMatch = (CHMatch *)getColMatchs().insert( new CHMatch(aMatch) ); 
		if (pMatch)
			pMatch->addToObjects();
	}
	else
        *pMatch=aMatch;

	return pMatch;
}

GTHMatchResult * CHMemoryDataBase::setMatchResult (const GTHMatchResult & target)
{
	CHMatchResult & aMatchResult = (CHMatchResult &)target;

	CHMatchResult * pMatchResult= (CHMatchResult *) getColMatchResults().find(&aMatchResult);
	
	if( !pMatchResult )
	{
		pMatchResult = (CHMatchResult *)getColMatchResults().insert( new CHMatchResult(aMatchResult)); 
		if (pMatchResult)
			pMatchResult->addToObjects();
	}
	else
        *pMatchResult=aMatchResult;

	return pMatchResult;
}

GTHSplitMatchResult * CHMemoryDataBase::setSplitMatchResult (const GTHSplitMatchResult & target)
{
	CHSplitMatchResult & aSplitMatchResult = (CHSplitMatchResult &)target;

	CHSplitMatchResult * pSplitMatchResult= (CHSplitMatchResult *) getColSplitMatchResult().find(&aSplitMatchResult);

	if( !pSplitMatchResult )
	{
		pSplitMatchResult = (CHSplitMatchResult *)getColSplitMatchResult().insert( new CHSplitMatchResult(aSplitMatchResult)); 
		if (pSplitMatchResult)
			pSplitMatchResult->addToObjects();
	}
	else
        *pSplitMatchResult=aSplitMatchResult;

	return pSplitMatchResult;
}

GTHSplitMatch * CHMemoryDataBase::setSplitMatch(const GTHSplitMatch &target)
{
	CHSplitMatch & aSplitMatch = (CHSplitMatch &)target;

	CHSplitMatch *pSplitMatch=(CHSplitMatch*)findSplitMatch(target);
	
	if (!pSplitMatch )	
	{
		pSplitMatch = (CHSplitMatch *) getColSplitMatch().insert(new CHSplitMatch(aSplitMatch) );
		if(pSplitMatch)
			pSplitMatch->addToObjects();
	}
	else
		*pSplitMatch = aSplitMatch;
	
	return pSplitMatch;
}


GTHEventResult * CHMemoryDataBase::setEventResult (const GTHEventResult	& target)
{
	CHEventResult & aEventResult = (CHEventResult&)target;

	CHEventResult * pEventResult= (CHEventResult *) getColEventResult().find(&aEventResult);

	if( !pEventResult )
		pEventResult = (CHEventResult *)getColEventResult().insert( new CHEventResult(aEventResult)); 
	else
        *pEventResult=aEventResult;

	return pEventResult;
}

GTHMatchJudge * CHMemoryDataBase::setMatchJudge       (const GTHMatchJudge & target)
{
	CHMatchJudge & aMatchJudge = (CHMatchJudge &)target;

	CHMatchJudge * pMatchJudge= (CHMatchJudge *) getColMatchJudge().find(&aMatchJudge);
	
	if( !pMatchJudge )
	{
		pMatchJudge= (CHMatchJudge *)getColMatchJudge().insert( new CHMatchJudge(aMatchJudge)); 
		if (pMatchJudge)
			pMatchJudge->addToObjects();
	}
	else
        *pMatchJudge=aMatchJudge;

	return pMatchJudge;
}


GTHSession * CHMemoryDataBase::setSession(const GTHSession& target)
{
	CHSession aSession=(CHSession&)target;
	CHSession* pSession=(CHSession*)findSession(aSession); 

	if( !pSession )  
		pSession=(CHSession *)getColSessions().insert( new CHSession(aSession) ); 
	else
       *pSession=aSession;

	return pSession;
}

/************************************************************/
GTHMatchMember * CHMemoryDataBase::setMatchMember(const GTHMatchMember & target)
{
	CHMatchMember & aMatchMember = (CHMatchMember &)target;
	CHMatchMember * pMatchMember = (CHMatchMember *)getColMatchMember().find(&aMatchMember);
	if( !pMatchMember )
	{
		pMatchMember = (CHMatchMember *)getColMatchMember().insert(new CHMatchMember(aMatchMember));
		//lo inserto en el vector de GTHMatchResult
		pMatchMember->addToObjects();
	}
	else if (pMatchMember != &aMatchMember)
        *pMatchMember = aMatchMember;
	return pMatchMember;
}

/************************************************************/
GCourt * CHMemoryDataBase::setCourt(const GCourt& target)
{
	CHCourt & aCourt = (CHCourt &)target;
	CHCourt * pCourt = (CHCourt*) getColCourts().find(&aCourt); 
	if( !pCourt )
		pCourt = (CHCourt *)getColCourts().insert( new CHCourt(aCourt) ); 
	else
	{
		if( pCourt != &aCourt )
			*pCourt = aCourt;
	}
	return pCourt;
}
CHMasterType* CHMemoryDataBase::setMasterType(const CHMasterType& aMasterType)
{
	CHMasterType *pMasterType = (CHMasterType *)findMasterType(aMasterType);

	if (!pMasterType)
		pMasterType=(CHMasterType*)colMasterTypes.insert(new CHMasterType(aMasterType));
	else 
		*pMasterType=aMasterType;

	return pMasterType;
}
CHTeamMatchsCnfg * CHMemoryDataBase::setTeamMatchsCnfg(const CHTeamMatchsCnfg& target)
{
	CHTeamMatchsCnfg *pTeamMatCnfg=(CHTeamMatchsCnfg *)getColTeamMatchsCnfg().find(&target);
	if (!pTeamMatCnfg)
		pTeamMatCnfg=(CHTeamMatchsCnfg *)(getColTeamMatchsCnfg().insert(new CHTeamMatchsCnfg(target)));
	else
	{
		if (pTeamMatCnfg != &target)
			*pTeamMatCnfg=target;
	}
	return pTeamMatCnfg;
}
CHRatingDif* CHMemoryDataBase::setRatingDif(const CHRatingDif& aRatingDif)
{
	CHRatingDif *pRatingDif = (CHRatingDif *)findRatingDif(aRatingDif);

	if (!pRatingDif)
		pRatingDif=(CHRatingDif*)colRatingDifs.insert(new CHRatingDif(aRatingDif));
	else 
		*pRatingDif=aRatingDif;

	return pRatingDif;
}
/////////////////////////////////////////////////////////////////////////////////
///////////// Remove's
/////////////////////////////////////////////////////////////////////////////////

CHJudge * CHMemoryDataBase::removeJudge(const CHJudge& aJudge)
{
	return (CHJudge*)colJudges.remove(&aJudge); 
}

GTHSplitMatchResult * CHMemoryDataBase::removeSplitMatchResult(const GTHSplitMatchResult & target)
{
	CHSplitMatchResult * pSplitMatchResult = (CHSplitMatchResult *)GTHMemoryDataBase::removeSplitMatchResult(target); 
	
	return pSplitMatchResult;
}

CHCourt *CHMemoryDataBase::removeCourt(const CHCourt& target)
{
	CHCourt *pCourt = (CHCourt *) &target;
	if( pCourt )
		pCourt = (CHCourt *)getColCourts().remove(&target);
	return pCourt;
}
CHMasterType *CHMemoryDataBase::removeMasterType(const CHMasterType& target)
{
	CHMasterType *pMasterType = (CHMasterType *) &target;
	if( pMasterType )
		pMasterType = (CHMasterType *)getColMasterTypes().remove(&target);
	return pMasterType;
}
CHTeamMatchsCnfg *CHMemoryDataBase::removeTeamMatchsCnfg(const CHTeamMatchsCnfg &target)
{
	CHTeamMatchsCnfg *pTeamMatCnfg=(CHTeamMatchsCnfg *)colTeamMatchsCnfg.remove(&target);
	return pTeamMatCnfg;
}
CHRatingDif *CHMemoryDataBase::removeRatingDif(const CHRatingDif& target)
{
	CHRatingDif *pRatingDif = (CHRatingDif *) &target;
	if( pRatingDif )
		pRatingDif = (CHRatingDif *)getColRatingDifs().remove(&target);
	return pRatingDif;
}
/////////////////////////////////////////////////////////////////////////////////
///////////// Query's
/////////////////////////////////////////////////////////////////////////////////

void CHMemoryDataBase::queryChildCollections(RWDBConnection& aConnection)
{
	THSPMemoryDataBase::queryChildCollections(aConnection);
	queryColTeamMatchsCnfg(aConnection,colTeamMatchsCnfg);
	queryColJudges(aConnection,colJudges);
	queryColMembers(aConnection,getColMember());	
	queryColMasterTypes(aConnection,getColMasterTypes());	
	queryColRatingDifs(aConnection,getColRatingDifs());	
}


GDiscipline * CHMemoryDataBase::queryDiscipline(RWDBConnection& aConnection)
{
	CHDiscipline * pDiscipline = new CHDiscipline();
	QCHDiscipline  qDiscipline(&aConnection);
	qDiscipline.select(*pDiscipline);
	return pDiscipline;
}

size_t CHMemoryDataBase::queryColEvents(RWDBConnection& aConnection,RWSet& target)
{
	QCHEvent qCHEvent(&aConnection);
	return qCHEvent.select(target);
}

size_t CHMemoryDataBase::queryColMembers(RWDBConnection& aConnection,RWSet& target)
{
	QCHMember qMember(&aConnection);
	return qMember.select(target);
}

size_t CHMemoryDataBase::queryColJudges(RWDBConnection& aConnection,RWSet& target)
{		
	QCHJudge queryJudge(&aConnection);
	return queryJudge.select(target);
}


size_t CHMemoryDataBase::queryColEventUnits(RWDBConnection& aConnection,RWSet& target)
{
	return 0;

	UNREFERENCED_PARAMETER(aConnection);
	UNREFERENCED_PARAMETER(target);
}

size_t CHMemoryDataBase::queryColEUnitNames(RWDBConnection& aConnection,RWSet& target)
{
	return 0;

	UNREFERENCED_PARAMETER(aConnection);
	UNREFERENCED_PARAMETER(target);
}

size_t CHMemoryDataBase::queryColInscriptions(RWDBConnection& aConnection,RWSet& target)
{
	QCHInscription qCHInscription(&aConnection);
	return qCHInscription.select(target);
}

size_t CHMemoryDataBase::queryColPhases(RWDBConnection& aConnection,RWSet& target)
{
	QCHPhase qCHPhase(&aConnection);
	return qCHPhase.select(target);
}


size_t CHMemoryDataBase::queryColPools(RWDBConnection& aConnection,RWSet& target)
{
	QCHPool qCHPool(&aConnection);
	return qCHPool.select(target);
}

size_t CHMemoryDataBase::queryColPoolResults(RWDBConnection& aConnection,RWSet& target)
{
	QCHPoolResult qCHColPoolResult(&aConnection);
	return qCHColPoolResult.select(target);
}

size_t CHMemoryDataBase::queryColMatchs(RWDBConnection& aConnection,RWSet& target)
{
	QCHMatch qCHMatch(&aConnection);
	return qCHMatch.select(target);
}

size_t CHMemoryDataBase::queryColMatchResults(RWDBConnection& aConnection,RWSet& target)
{
	QCHMatchResult qCHMatchResult(&aConnection);
	return qCHMatchResult.select(target);
}

size_t CHMemoryDataBase::queryColSplitMatches(RWDBConnection& aConnection,RWSet& target)
{
	QCHSplitMatch qCHSplitMatch(&aConnection);
	return qCHSplitMatch.select(target);
}
size_t CHMemoryDataBase::queryColSplitMatchResults(RWDBConnection& aConnection,RWSet& target)
{
	QCHSplitMatchResult qCHSplitMatchResult(&aConnection);
	return qCHSplitMatchResult.select(target);
}

size_t CHMemoryDataBase::queryColEventResults(RWDBConnection& aConnection,RWSet& target)
{
	QCHEventResult qCHEventResult(&aConnection);
	return qCHEventResult.select(target);
}

size_t CHMemoryDataBase::queryColMatchJudge(RWDBConnection& aConnection,RWSet& target)
{
	QCHMatchJudge qCHMatchJudge(&aConnection);
	return qCHMatchJudge.select(target);
}

size_t CHMemoryDataBase::queryColSessions(RWDBConnection& aConnection,RWSet& target)
{
	QCHSession querySession(&aConnection);
	return querySession.select(target);
}

size_t CHMemoryDataBase::queryColMatchMember(RWDBConnection& aConnection,RWSet& target)
{
	QCHMatchMember qCHMatchMember(&aConnection);
	return qCHMatchMember.select(target);
}
size_t CHMemoryDataBase::queryColPhaseNames(RWDBConnection& aConnection,RWSet& target)
{
	QCHPhaseBase qPhaseNames(&aConnection);
	return qPhaseNames.select(target);
}
size_t CHMemoryDataBase::queryColCourts(RWDBConnection& aConnection,RWSet& target)
{
	QCHCourt qCHCourt(&aConnection);
	return qCHCourt.select(target);
}
size_t CHMemoryDataBase::queryColMasterTypes(RWDBConnection& aConnection,RWSet& target)
{		
	QCHMasterType queryMasterType(&aConnection);
	return queryMasterType.select(target);
}
size_t CHMemoryDataBase::queryColRatingDifs(RWDBConnection& aConnection,RWSet& target)
{		
	QCHRatingDif queryRatingDif(&aConnection);
	return queryRatingDif.select(target);
}
size_t CHMemoryDataBase::queryColTeamMatchsCnfg(RWDBConnection& aConnection,RWSet& target)
{
	QCHTeamMatchsCnfg qTeamMatchsCnfg(&aConnection);
	return qTeamMatchsCnfg.select(target);
}
size_t CHMemoryDataBase::queryColRegisters(RWDBConnection& aConnection,RWSet& target)
{
	QCHRegister qCHRegister(&aConnection);
	return qCHRegister.select(target);
}
//////////////////////////////////////////////////////////////
/////////   PACK's Y UNPACK 's
//////////////////////////////////////////////////////////////

void CHMemoryDataBase::packChildCollections(CPack& aPack)
{
	THSPMemoryDataBase::packChildCollections(aPack);

	packCollection(aPack,colTeamMatchsCnfg);
	packCollection(aPack,colJudges);
	packCollection(aPack,colMasterTypes);
	packCollection(aPack,colRatingDifs);

}

GDiscipline * CHMemoryDataBase::unpackDiscipline(CPack& aPack)
{
	// La disciplina no se desempaqueta porque solo hay un registro, sólo se crea.
	return new CHDiscipline(aPack);
}


void CHMemoryDataBase::unpackColEvents(CPack& aPack,RWSet& target)
{
	size_t entries=0;
	aPack >> entries;
	for (size_t i=0; i < entries; i++)
		target.insert (new CHEvent(aPack));

}

void CHMemoryDataBase::unpackColInscriptions(CPack& aPack,RWSet& target)
{
	size_t entries=0;
	aPack >> entries;
	for (size_t i=0; i < entries; i++)
		target.insert(new CHInscription(aPack));
}


void CHMemoryDataBase::unpackColEventUnits(CPack& aPack,RWSet& target)
{
	UNREFERENCED_PARAMETER(target);

	size_t entries=0;
	aPack >> entries;
}

void CHMemoryDataBase::unpackColJudges(CPack& aPack,RWSet& target)
{
	size_t entries=0;

	// Colección de jueces.	
	aPack >> entries;
	for(size_t i=0;i<entries;i++)
		target.insert( new CHJudge(aPack) );
}


void CHMemoryDataBase::unpackChildCollections(CPack& aPack)
{
	THSPMemoryDataBase::unpackChildCollections(aPack);

	unpackColTeamMatchsCnfg(aPack,colTeamMatchsCnfg);
	unpackColJudges(aPack,colJudges);
	unpackColMasterTypes(aPack,colMasterTypes);
	unpackColRatingDifs(aPack,colRatingDifs);
		
}

void CHMemoryDataBase::unpackColPhases(CPack& aPack,RWSet& target)
{
	size_t nEntries=0;
	aPack >> nEntries;

	for (size_t i=0;i<nEntries;i++)
	{
		CHPhase * pPhase =(CHPhase *)target.insert (new CHPhase(aPack));
		if (pPhase) 
			pPhase->addToObjects();
	}
}


void CHMemoryDataBase::unpackColPools(CPack& aPack,RWSet& target)
{
	size_t nEntries = 0;
	aPack >> nEntries;

	for (size_t i=0;i<nEntries;i++)
	{
		CHPool * pPool=(CHPool *)target.insert (new CHPool(aPack));
		if (pPool) 
			pPool->addToObjects();
	}
}

void CHMemoryDataBase::unpackColPoolResults(CPack& aPack,RWSet& target)
{
	size_t nEntries=0;
	aPack >> nEntries;

	for (size_t i=0;i<nEntries;i++)
	{
		CHPoolResult * pPoolResult=(CHPoolResult *)target.insert (new CHPoolResult(aPack));
		if (pPoolResult) //lo inserto en el setPoolResult que hay en el GTHPool
			pPoolResult->addToObjects();
	}
}

void CHMemoryDataBase::unpackColMatchs(CPack& aPack,RWSet& target)
{
	size_t nEntries=0;
	aPack >> nEntries;

	for (size_t i=0;i<nEntries;i++)
	{
		CHMatch * pMatch = (CHMatch *)target.insert (new CHMatch(aPack));
		if (pMatch)  // lo inserto en el vector matchsVector que tiene el GTHPool
			pMatch->addToObjects();
	}
}

void CHMemoryDataBase::unpackColMatchResults(CPack& aPack,RWSet& target)
{
	size_t nEntries=0;
	aPack >> nEntries;

	for (size_t i=0;i<nEntries;i++)
	{
		CHMatchResult * pMatchResult = (CHMatchResult *)target.insert (new CHMatchResult(aPack));
		if (pMatchResult)  // lo inserto en el vector setMatchResult que tiene el GTHMatch
			pMatchResult->addToObjects();
	}
}

void CHMemoryDataBase::unpackColSplitMatchResults(CPack& aPack,RWSet& target)
{
	size_t nEntries=0;
	aPack >> nEntries;

	for (size_t i=0;i<nEntries;i++)
	{
		CHSplitMatchResult * pSplitMatchResult = (CHSplitMatchResult *)target.insert (new CHSplitMatchResult(aPack));
		if (pSplitMatchResult)  // lo inserto en el vector vectorSplits que tiene el GTHMatchResult
			pSplitMatchResult->addToObjects();
	}
}

void CHMemoryDataBase::unpackSplitMatches(CPack& aPack,RWSet& target)
{
	size_t nEntries=0;
	aPack >> nEntries;

	for (size_t i=0;i<nEntries;i++)
	{
		CHSplitMatch * pSplitMatch = (CHSplitMatch*)target.insert (new CHSplitMatch(aPack));
		if (pSplitMatch)  // lo inserto en el vector vectorSplits que tiene el GTHMatchResult
			pSplitMatch->addToObjects();
	}
}


void CHMemoryDataBase::unpackColEventResults(CPack& aPack,RWSet& target)
{
	size_t nEntries=0;
	aPack >> nEntries;

	for(size_t i=0;i<nEntries;i++)
		target.insert( new CHEventResult(aPack) );
}


void CHMemoryDataBase::unpackColMatchJudge(CPack& aPack,RWSet& target)
{
	size_t nEntries=0;
	aPack >> nEntries;

	for (size_t i=0;i<nEntries;i++)
	{
		CHMatchJudge * pMatchJudge = (CHMatchJudge *)target.insert (new CHMatchJudge(aPack));
		if (pMatchJudge)  
			pMatchJudge->addToObjects();
	}
}

void CHMemoryDataBase::unpackColSessions(CPack& aPack,RWSet& target)
{
	size_t nEntries=0;
	aPack >> nEntries;

	for(size_t i=0;i<nEntries;i++)
		target.insert (new CHSession(aPack));
}


void CHMemoryDataBase::unpackColMembers(CPack& aPack,RWSet& target)
{
	size_t nEntries=0;

	aPack >> nEntries;
	for (size_t i=0;i<nEntries;i++)
	{
		CHMember * pMember =(CHMember *)target.insert (new CHMember(aPack));
		if(pMember)
		{
			CHInscription * pInscription=(CHInscription *)pMember->getInscription();
			if(!pInscription->getMembersVector().find(pMember))
				pInscription->setMember(pMember);		
		}
	}
}

void CHMemoryDataBase::unpackColMatchMember(CPack& aPack,RWSet& target)
{
	size_t nEntries=0;
	aPack >> nEntries;

	for (size_t i=0;i<nEntries;i++)
	{
		CHMatchMember * pMatchMember = (CHMatchMember *)target.insert (new CHMatchMember(aPack));
		if (pMatchMember)  // lo inserto en el vector setMatchResult que tiene el GTHMatch
		{
			GTHMatchResult *pMatchResult = pMatchMember->getMatchResult();
			pMatchResult->setMatchMember(pMatchMember);
		}
	}
}

void CHMemoryDataBase::unpackColPhaseNames(CPack& aPack,RWSet& target)
{
	size_t nEntries=0;

	aPack >> nEntries;
	for(size_t i=0;i<nEntries;i++)
		target.insert( new CHPhaseBase(aPack) );
}

void CHMemoryDataBase::unpackColCourts(CPack& aPack,RWSet& target)
{
	size_t nEntries=0;
	aPack >> nEntries;

	for(size_t i=0;i<nEntries;i++)
		target.insert( new CHCourt(aPack) );
}
void CHMemoryDataBase::unpackColMasterTypes(CPack& aPack,RWSet& target)
{
	size_t entries=0;

	// Colección de master types	
	aPack >> entries;
	for(size_t i=0;i<entries;i++)
		target.insert( new CHMasterType(aPack) );
}
void CHMemoryDataBase::unpackColRatingDifs(CPack& aPack,RWSet& target)
{
	size_t entries=0;

	// Colección de rating difs
	aPack >> entries;
	for(size_t i=0;i<entries;i++)
		target.insert( new CHRatingDif(aPack) );
}
void CHMemoryDataBase::unpackColTeamMatchsCnfg(CPack& aPack,RWSet& target)
{
	size_t entries=0;
	
	CHTeamMatchsCnfg *pTeamMatCnfg=0;
	aPack >> entries;
	for (size_t i=0; i<entries; i++)
	{
		pTeamMatCnfg=(CHTeamMatchsCnfg *)target.insert(new CHTeamMatchsCnfg(aPack));
	}
}
void CHMemoryDataBase::unpackColRegisters(CPack& aPack,RWSet& target)
{
	size_t nEntries=0;
	aPack >> nEntries;
	for( size_t i=0; i<nEntries; i++ )
		target.insert( new CHRegister(aPack) );
}
////////////////////////////////////////////////////////////////////////////////
///////// Update Model   
////////////////////////////////////////////////////////////////////////////////
RWBoolean CHMemoryDataBase::updateModel(CPackObject& aPackObject)
{
	RWBoolean rc=false;

	unsigned int ObjectId = aPackObject.getId();

	CPackObject::actions OBjectAction = CPackObject::actions(aPackObject.getAction());

	switch( ObjectId )
	{
	case __CHDISCIPLINE: // Una disciplina ni se crea ni se borra, solo se modifica
		{ 
			CHDiscipline aDiscipline(aPackObject.getPack());
			(CHDiscipline&)getDiscipline() = aDiscipline;
			rc=true;
		}
		break;
	case __CHEVENT:
		if ( OBjectAction == CPackObject::eDeleteObject )
		{
			delete removeEvent (CHEvent(aPackObject.getPack()));
			rc=true;
		}
		if ( OBjectAction == CPackObject::eInsertOrUpdateObject)
		{
			setEvent (CHEvent(aPackObject.getPack()));
			rc=true;
		}
		break;
	case __CHINSCRIPTION:
		if ( OBjectAction == CPackObject::eDeleteObject )
		{
			delete removeInscription (CHInscription(aPackObject.getPack()));
			rc=true;
		}
		if ( OBjectAction == CPackObject::eInsertOrUpdateObject)
		{
			setInscription (CHInscription(aPackObject.getPack()));
			rc=true;
		}
		break;
	case __CHJUDGE:
		if( OBjectAction==CPackObject::eDeleteObject )
		{
			delete removeJudge( CHJudge(aPackObject.getPack()) );
			rc=true;
		}
		if( OBjectAction==CPackObject::eInsertOrUpdateObject )
		{
			setJudge( CHJudge(aPackObject.getPack()) );
			rc=true;
		}		
		break;
	case __CHPHASE:
		if ( OBjectAction == CPackObject::eDeleteObject )
		{
			delete removePhase (CHPhase(aPackObject.getPack()));
			rc=true;
		}
		if ( OBjectAction == CPackObject::eInsertOrUpdateObject)
		{
			setPhase (CHPhase(aPackObject.getPack()));
			rc=true;
		}
		break;
	case __CHPOOL:
		if ( OBjectAction == CPackObject::eDeleteObject )
		{
			delete removePool (CHPool(aPackObject.getPack()));
			rc=true;
		}
		if ( OBjectAction == CPackObject::eInsertOrUpdateObject)
		{
			setPool (CHPool(aPackObject.getPack()));
			rc=true;
		}
		break;
	case __CHPOOLRESULT:
		if ( OBjectAction == CPackObject::eDeleteObject )
		{
			delete removePoolResult (CHPoolResult(aPackObject.getPack()));
			rc=true;
		}
		if ( OBjectAction == CPackObject::eInsertOrUpdateObject)
		{
			setPoolResult (CHPoolResult(aPackObject.getPack()));
			rc=true;
		}
		break;
	case __CHMATCH:
		if ( OBjectAction == CPackObject::eDeleteObject )
		{
			delete removeMatch (CHMatch(aPackObject.getPack()));
			rc=true;
		}
		if ( OBjectAction == CPackObject::eInsertOrUpdateObject)
		{
			setMatch (CHMatch(aPackObject.getPack()));
			rc=true;
		}
		break;
	case __CHSPLITMATCH:
		if ( OBjectAction == CPackObject::eDeleteObject )
		{
			delete removeSplitMatch(CHSplitMatch(aPackObject.getPack()));
			rc=true;
		}
		if ( OBjectAction == CPackObject::eInsertOrUpdateObject)
		{
			setSplitMatch(CHSplitMatch(aPackObject.getPack()));				
			rc=true;		
		}
		break;
	case __CHMATCHRESULT:
		if ( OBjectAction == CPackObject::eDeleteObject )
		{
			delete removeMatchResult (CHMatchResult(aPackObject.getPack()));
			rc=true;
		}
		if ( OBjectAction == CPackObject::eInsertOrUpdateObject)
		{
			setMatchResult (CHMatchResult(aPackObject.getPack()));
			rc=true;
		}
		break;
	case __CHSPLITMATCHRESULT:
		if ( OBjectAction == CPackObject::eDeleteObject )
		{
			delete removeSplitMatchResult (CHSplitMatchResult(aPackObject.getPack()));
			rc=true;
		}
		if ( OBjectAction == CPackObject::eInsertOrUpdateObject)
		{
			setSplitMatchResult (CHSplitMatchResult(aPackObject.getPack()));
			rc=true;
		}
		break;
	case __CHEVENTRESULT:
		if ( OBjectAction == CPackObject::eDeleteObject )
		{
			delete removeEventResult(CHEventResult(aPackObject.getPack()));
			rc=true;
		}
		if ( OBjectAction == CPackObject::eInsertOrUpdateObject)
		{
			setEventResult(CHEventResult(aPackObject.getPack()));
			rc=true;
		}
		break;	
	case __CHMATCHJUDGE:
		if ( OBjectAction == CPackObject::eDeleteObject )
		{
			delete removeMatchJudge(CHMatchJudge(aPackObject.getPack()));
			rc=true;
		}
		if ( OBjectAction == CPackObject::eInsertOrUpdateObject)
		{
			setMatchJudge(CHMatchJudge(aPackObject.getPack()));
			rc=true;
		}
		break;
	case __CHSESSION:
		if( OBjectAction==CPackObject::eDeleteObject )
		{
			delete removeSession( CHSession(aPackObject.getPack()) );
			rc=true;
		}
		if( OBjectAction==CPackObject::eInsertOrUpdateObject )
		{
			setSession( CHSession(aPackObject.getPack()) );
			rc=true;
		}		
		break;
	case __CHMEMBER:
		if ( OBjectAction == CPackObject::eDeleteObject )
		{
			delete removeMember(CHMember(aPackObject.getPack()));
			rc=true;
		}
		if ( OBjectAction == CPackObject::eInsertOrUpdateObject)
		{
			setMember(CHMember(aPackObject.getPack()));
			rc=true;
		}
		break;	
	case __CHMATCHMEMBER:
		if( OBjectAction == CPackObject::eDeleteObject )
		{
			delete removeMatchMember( CHMatchMember(aPackObject.getPack()) );
			rc=true;
		}
		if( OBjectAction == CPackObject::eInsertOrUpdateObject )
		{
			setMatchMember( CHMatchMember(aPackObject.getPack()) );
			rc=true;
		}
		break;
	case __CHCOURT:
		if( OBjectAction==CPackObject::eDeleteObject )
		{
			delete removeCourt( CHCourt(aPackObject.getPack()) );
			rc=true;
		}
		if( OBjectAction==CPackObject::eInsertOrUpdateObject )
		{
			setCourt( CHCourt(aPackObject.getPack()) );
			rc=true;
		}
		break;
	case __CHMASTERTYPE:
		if( OBjectAction==CPackObject::eDeleteObject )
		{
			delete removeMasterType( CHMasterType(aPackObject.getPack()) );
			rc=true;
		}
		if( OBjectAction==CPackObject::eInsertOrUpdateObject )
		{
			setMasterType( CHMasterType(aPackObject.getPack()) );
			rc=true;
		}
		break;
	case __CHTEAMMATCHSCNFG:
		if ( OBjectAction==CPackObject::eDeleteObject )
		{
			delete removeTeamMatchsCnfg(CHTeamMatchsCnfg(aPackObject.getPack()));
			rc=true;
		}
		if ( OBjectAction==CPackObject::eInsertOrUpdateObject )
		{
			setTeamMatchsCnfg(CHTeamMatchsCnfg(aPackObject.getPack()));
			rc=true;
		}
		break;
	case __CHREGISTER:
		if( OBjectAction==CPackObject::eDeleteObject )
		{
			delete removeRegister( CHRegister(aPackObject.getPack()) );
			rc=true;
		}
		if( OBjectAction==CPackObject::eInsertOrUpdateObject )
		{
			setRegister( CHRegister(aPackObject.getPack()) );
			rc=true;
		}
		break;
	
	case __CHRATINGDIF:
		if( OBjectAction==CPackObject::eDeleteObject )
		{
			delete removeRatingDif( CHRatingDif(aPackObject.getPack()) );
			rc=true;
		}
		if( OBjectAction==CPackObject::eInsertOrUpdateObject )
		{
			setRatingDif( CHRatingDif(aPackObject.getPack()) );
			rc=true;
		}
		break;
	}
	if (!rc)
		rc = THSPMemoryDataBase::updateModel(aPackObject);
	return rc;

}

GData * CHMemoryDataBase::getObject(RWClassID aClassID,CPack &aPack)
{
	switch( aClassID )
	{
	case __CHEVENT:
		return new CHEvent(aPack);
		break;
	case __CHINSCRIPTION:
		return new CHInscription(aPack);
		break;
	case __CHJUDGE:
		return new CHJudge(aPack);
		break;
	case __CHPHASE:
		return new CHPhase(aPack);
		break;
	case __CHPOOL:
		return new CHPool(aPack);
		break;
	case __CHPOOLRESULT:
		return new CHPoolResult(aPack);
		break;
	case __CHMATCH:
		return new CHMatch(aPack);
		break;
	case __CHMATCHRESULT:
		return new CHMatchResult(aPack);
		break;
	case __CHSPLITMATCHRESULT:
		return new CHSplitMatchResult(aPack);
		break;
	case __CHMATCHJUDGE:
		return new CHMatchJudge(aPack);
		break;
	case __CHSESSION:
		return new CHSession(aPack);

	case __CHEVENTRESULT:
		return new CHEventResult(aPack);

	case __CHSPLITMATCH:
		return new CHSplitMatch(aPack);
		break;

	case __CHMEMBER:
		return new CHMember(aPack);
		break;
	case __CHMATCHMEMBER:
		return new CHMatchMember(aPack);
		break;
	case __CHCOURT:
		return new CHCourt(aPack);
		break;
	case __CHMASTERTYPE:
		return new CHMasterType(aPack);
		break;
	case __CHTEAMMATCHSCNFG:
		return new CHTeamMatchsCnfg(aPack);
		break;
	case __CHREGISTER:
		return new CHRegister(aPack);
		break;
	case __CHRATINGDIF:
		return new CHRatingDif(aPack);
		break;

	default:
		return THSPMemoryDataBase::getObject(aClassID,aPack);
	}
	return NULL;
}

void CHMemoryDataBase::unionChildCollections(RWHashTable& sSource)
{

	THSPMemoryDataBase::unionChildCollections(sSource);
	sSource+=colTeamMatchsCnfg;
	sSource+=colJudges;
	sSource+=colMasterTypes;
	sSource+=colRatingDifs;

}

CHJudge * CHMemoryDataBase::findJudge(const CHJudge& aJudge)
{
	return (CHJudge *)colJudges.find(&aJudge); 
}

CHJudge * CHMemoryDataBase::findJudge(GRegister* pRegister,GFunction * pFunction)
{
	CHJudge aJudge;
	aJudge.setFunction(pFunction);
	aJudge.setRegister(pRegister);
	
	RWSetIterator it(colJudges);
	CHJudge *pJud=0;
	while ((pJud=(CHJudge*)it())!=0)
		if (pJud &&	pJud->getKey()==aJudge.getKey())
			return (CHJudge*)pJud;
	return 0; 
}
CHMasterType * CHMemoryDataBase::findMasterType(const CHMasterType& aMasterType)
{
	return (CHMasterType *)colMasterTypes.find(&aMasterType); 
}

CHMasterType * CHMemoryDataBase::findMasterType(short masterType)
{
	CHMasterType aMasterType;
	aMasterType.setMasterType(masterType);
		
	RWSetIterator it(colMasterTypes);
	CHMasterType *pMaster=0;
	while ((pMaster=(CHMasterType*)it())!=0)
		if (pMaster &&	pMaster->getKey()==aMasterType.getKey())
			return (CHMasterType*)pMaster;
	return 0; 
}
CHRatingDif * CHMemoryDataBase::findRatingDif(const CHRatingDif& aRatingDif)
{
	return (CHRatingDif *)colRatingDifs.find(&aRatingDif); 
}

CHRatingDif * CHMemoryDataBase::findRatingDif(short ratingCode)
{
	CHRatingDif aRatingDif;
	aRatingDif.setCode(ratingCode);
		
	RWSetIterator it(colRatingDifs);
	CHRatingDif *pRatingDif=0;
	while ((pRatingDif=(CHRatingDif*)it())!=0)
		if (pRatingDif &&	pRatingDif->getKey()==aRatingDif.getKey())
			return (CHRatingDif*)pRatingDif;
	return 0; 
}
CHTeamMatchsCnfg *CHMemoryDataBase::findTeamMatchsCnfg(short id)
{
	CHTeamMatchsCnfg aTeamMatCnfg;
	aTeamMatCnfg.setId(id);
	return findTeamMatchsCnfg(aTeamMatCnfg);
}

CHTeamMatchsCnfg *CHMemoryDataBase::findTeamMatchsCnfg(CHEvent *pEvent)
{
	if (pEvent)
		return findTeamMatchsCnfg(pEvent->getIdTeamMatchsCnfg());

	return 0;
}

CHTeamMatchsCnfg *CHMemoryDataBase::findTeamMatchsCnfg(CHPhase *pPhase)
{
	CHTeamMatchsCnfg *pTeamMatchCfg=0;

	if (pPhase)
	{
		pTeamMatchCfg=findTeamMatchsCnfg(pPhase->getIdTeamMatchsCnfg());
		if (!pTeamMatchCfg)
			pTeamMatchCfg=findTeamMatchsCnfg((CHEvent *)pPhase->getEvent());
	}
	
	return pTeamMatchCfg;
}

CHTeamMatchsCnfg *CHMemoryDataBase::findTeamMatchsCnfg(CHTeamMatchsCnfg& aTeamMatchsCnfg)
{ 
	if (aTeamMatchsCnfg.getId()!=0)
		return (CHTeamMatchsCnfg *)colTeamMatchsCnfg.find(&aTeamMatchsCnfg);
	else
		return NULL;
}

CHMatch *CHMemoryDataBase::findMatchSource(CHMatchResult *pMR)
{
	CHMatch *pMatch=0;
	
	GTHPoolResult * pPoolResult = pMR->getPoolResult();
	if(!pPoolResult)
		return NULL;

	CHPhase *pPhaseSrc = findPhaseSource(pMR);
	if (!pPhaseSrc)
		return NULL;

	CHPool *pPoolSrc   = findPoolSource(pMR);
	if (!pPoolSrc)
		return NULL;

	if (pPoolSrc->getMatchsVector()[0])
		pMatch =  (CHMatch *)pPoolSrc->getMatchsVector()[0]->getElement();

	return pMatch;
}

CHPhase *CHMemoryDataBase::findPhaseSource(CHMatchResult *pMR)
{
	GTHPoolResult * pPoolResult = pMR->getPoolResult();
	if(!pPoolResult)
		return NULL;

	return (CHPhase *)pPoolResult->getPointerPhaseSource();
}

CHPool *CHMemoryDataBase::findPoolSource(CHMatchResult *pMR)
{
	GTHPoolResult * pPoolResult = pMR->getPoolResult();
	if(!pPoolResult)
		return NULL;

	return (CHPool *)pPoolResult->getPointerPoolSource();
}

int CHMemoryDataBase::findColorStatus(unsigned char status)
{
	int ret=0;

	switch (status)
	{
		case CHMemoryDataBase::eAvailable:
			ret=COLORSTATUS_AVAILABLE;
			break;
		case CHMemoryDataBase::eConfigured:
			ret=COLORSTATUS_CONFIGURED;
			break;
		case CHMemoryDataBase::eSchedulled:
			ret=COLORSTATUS_SCHEDULLED;
			break;
		case CHMemoryDataBase::eStartList:
			ret=COLORSTATUS_STARTLIST;
			break;
		case CHMemoryDataBase::eRunning:
			ret=COLORSTATUS_RUNNING;
			break;
		case CHMemoryDataBase::eUnofficial:
			ret=COLORSTATUS_UNOFFICIAL;
			break;
		case CHMemoryDataBase::eFinished:
			ret=COLORSTATUS_FINISHED;
			break;
		case CHMemoryDataBase::eProtested:
			ret=COLORSTATUS_REVISION;
			break;
	}
	return ret;
}

RWCString CHMemoryDataBase::getRSC(const GData *pData)
{
	return getRSC(pData);
}

RWCString CHMemoryDataBase::getRSC(GData * pData,RWBoolean withoutDiscipline/*=false*/,RWBoolean extraRSC/*=true*/,RWDate date/*=INVALID_RWDATE*/)
{
	// Estan en el documento COD00135_Approved_030207 (2004 Codes).doc
	RWCString strGender = extraRSC?	"0"		:"";
	RWCString strEvent  = extraRSC?	"000"	:"";
	RWCString strPhase  = extraRSC?	"0"		:"";
	RWCString strUnit   = extraRSC?	"00000"	:"";

	RWCString rsc = getDiscipline().getCode();

	if( !pData) // && date==INVALID_RWDATE )
		return rsc += "0000000000";

	/*if( date!=INVALID_RWDATE )
	{
		rsc += "0000Y";
		return rsc += date.asString("%d");
	}*/

	if( pData )
	{
		switch( pData->isA() )
		{
			case __CHEVENT:			// GEEE 
			{
				GTHEvent * pEvent = (GTHEvent *)pData;
				strGender = traslateCode(pEvent->getSex());
				strEvent  = traslateCode(pEvent);
			}
			break;

			case __CHPHASE:			// GEEEP
			{
				GTHPhase * pPhase = (GTHPhase *)pData;
				strGender = traslateCode(pPhase->getEventSexCode());
				strEvent  = traslateCode((GTHEvent*)pPhase->getEvent());
				strPhase  = traslateCode(pPhase);
			}
			break;

			case __CHMATCH:			// GEEEPUU
			{
				CHMatch *pMatch=(CHMatch*) pData;
				strGender = traslateCode(pMatch->getEventSexCode());
				strEvent  = traslateCode(pMatch->getEvent());
				strPhase  = traslateCode(pMatch->getPhase());
				strUnit  = traslateCode(pMatch);
			}
			break;
		}
	}

	return withoutDiscipline?(strGender+strEvent+strPhase+strUnit):(getDiscipline().getCode()+strGender+strEvent+strPhase+strUnit);
}


/************************************************************/
/*** TRASLATE METHODS ***************************************/
/************************************************************/

RWCString CHMemoryDataBase::traslateCode(RWCString sex)
{
	RWCString code = "";

	if( sex == MEN )
		code = "M";
	if( sex == WOMEN )
		code = "W";
	if( sex == MIXED )
		code = "X";

	return code;
}

/************************************************************/

RWCString CHMemoryDataBase::traslateCode(GTHEvent *pEvent)
{
	if (!pEvent)
		return NULLRWSTRING;
	return pEvent->getEvent();
}

/************************************************************/

RWCString CHMemoryDataBase::traslateCode(GTHPhase * pPhase)
{
	if (!pPhase)
		return NULLRWSTRING;
	return pPhase->getPhase();
}

/************************************************************/

RWCString CHMemoryDataBase::traslateCode(CHMatch * pMatch)
{
	if (!pMatch)
		return NULLRWSTRING;

	char tmp[5]={0};
	sprintf(tmp,"%.5d",pMatch->getCode());
	RWCString code=tmp;

	return code;
}
/************************************************************/
RWCString CHMemoryDataBase::traslateCode(CHPool * pPool)
{
	if (!pPool)
		return NULLRWSTRING;

	char tmp[5]={0};
	sprintf(tmp,"%.2d",pPool->getPool());
	RWCString code=tmp;

	return code;
}