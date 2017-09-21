#include "StdAfx.h"
#include "CHODFModel.h"
#include "CHODF2Defines.h"

#include "..\CHMngtModel\CHMatchResult.h"
#include "..\CHMngtModel\CHMember.h"
#include "..\CHMngtModel\CHMatch.h"
#include "..\CHMngtModel\CHDefinition.h"
#include "..\CHMngtModel\CHInscription.h"
#include "..\CHMngtModel\CHRegister.h"

static
int orderMatchMembersByName(const MSLItem** a, const MSLItem** b)
{
	GTHMatchMember * pA=((GTHMatchMember *)(*a));
	GTHMatchMember * pB=((GTHMatchMember *)(*b));

	if (pA->getRegister() && pB->getRegister())
	{
		int rc = _wcsicoll(pA->getPrnLName(),pB->getPrnLName());
		//int rc=wcscmp(pA->getPrnLName(),pB->getPrnLName());
		if (rc)
			return rc; 
		
		return strcmp(pA->getKey(),pB->getKey());
	}
	
	int order = (pA->getRegister()) ? 1: -1;
	if (order)
		return order;

	return strcmp(pA->getKey(),pB->getKey());
}

static 
int orderMembersByName(const MSLItem** a, const MSLItem** b)
{
	CHMember *pA=(CHMember *)(*a);
	CHMember *pB=(CHMember *)(*b);

	int order = _wcsicoll(pA->getPrnLName(),pB->getPrnLName());
	if( order )
		return order;

	return strcmp(pA->getKey(),pB->getKey());
}

static
bool sessionMatches(const MSLItem* p,const void *n)
{
	GSession* pSession = (GSession*) n;
	CHMatch* pMatch = (CHMatch *)p;	

	if (!pSession)
		return true;

	if ( pSession->getKey() == pMatch->getSessionKey() )
		 return true;

	return false;
}

CHODFModel::CHODFModel(void)
:ODF2THModel()
{
}


CHODFModel::~CHODFModel(void)
{
}

CHMemoryDataBase * CHODFModel::getMem() const
{
	return (CHMemoryDataBase*)CHMemoryDataBase::getMem();
}

CHODFModel * CHODFModel::getCHModel()
{
	return (CHODFModel*)getTHModel();
}

GTHMatch * CHODFModel::findMatch(GTHPool * pPool, GTHPoolResult * pPoolResult, GTHPoolResult * pPoolResultOpp)
{
	GTHMatch * pMatch = 0;
	GTHMatchResult * pMatchResult1 = 0;
	GTHMatchResult * pMatchResult2 = 0;
	GTHPoolResult * pPoolResult1 = 0;
	GTHPoolResult * pPoolResult2 = 0;
	MSLSortedVector vMatches;
	pPool->getMatchesVector(vMatches);	
	for(int i=0 ; i<vMatches.entries() ; i++)
	{
		pMatch        = (GTHMatch       *)vMatches[i];
		
		pMatchResult1 = (GTHMatchResult *)(pMatch ? pMatch->getHome() : 0);
		pMatchResult2 = (GTHMatchResult *)(pMatch ? pMatch->getAway() : 0);
		
		pPoolResult1  = (GTHPoolResult  *)(pMatchResult1 ? pMatchResult1->getPoolResult() : 0);
		pPoolResult2  = (GTHPoolResult  *)(pMatchResult2 ? pMatchResult2->getPoolResult() : 0);

		if( ( pPoolResult1 == pPoolResult   && pPoolResult2 == pPoolResultOpp ) ||
				 ( pPoolResult1 == pPoolResultOpp && pPoolResult2 == pPoolResult   ) )
		{
			return pMatch;
		}	
	}
	
	return 0;
}

MSLString CHODFModel::getResult(GTHMatch * pMatch, GTHPoolResult * pPoolResult, GTHPoolResult * pPoolResultOpp)
{
	if (!pMatch)
		return NULLWSTRING;
	
	GTHPool* pPool = pMatch->getPool();
	if (!pPool)
		return NULLWSTRING;
		
	GTHMatchResult * pMatchResult1 = (GTHMatchResult *)(pMatch ? pMatch->getHome() : 0);
	GTHMatchResult * pMatchResult2 = (GTHMatchResult *)(pMatch ? pMatch->getAway() : 0);
	GTHPoolResult * pPoolResult1  = (GTHPoolResult  *)(pMatchResult1 ? pMatchResult1->getPoolResult() : 0);
	GTHPoolResult * pPoolResult2  = (GTHPoolResult  *)(pMatchResult2 ? pMatchResult2->getPoolResult() : 0);

	if( ( pPoolResult1 == pPoolResult   && pPoolResult2 == pPoolResultOpp ) ||
		( pPoolResult1 == pPoolResultOpp && pPoolResult2 == pPoolResult   ) )
	{
		if (pPoolResult->getRegCode()==pMatchResult1->getRegCode())
			return getMatchScore(pMatchResult1,pMatchResult2);							
		else if (pPoolResultOpp->getRegCode()==pMatchResult1->getRegCode())
			return getMatchScore(pMatchResult2,pMatchResult1);
		return getMatchScore(pMatchResult1,pMatchResult2);	
	}
	
	return L"-";
}

MSLString CHODFModel::getFunction(GData *pData)
{
	if (!pData)
		return "";
	
	switch (pData->isA())
	{
		case __GMEMBER:
		{
			CHMember *pMember= (CHMember *)pData;
			if (pMember->getType()==GRegister::individual)
				return "AA01";			
		}
		case __GREGISTER:
		{
			GRegister *pRegister = (GRegister *)pData;
			if (pRegister->getType()==GRegister::individual)
				return "AA01";
			if (pRegister->getType()==GRegister::teamOfficial)
				return "AOE1";
			if (pRegister->getType()==GRegister::official)
				return "AJU1";
			break;
		}
		case __GOFFICIAL:
		{
			GOfficial *pOfficial = (GOfficial *)pData;
			switch (pOfficial->getFunctionCode())
			{
				
			}
		}
	}
	return "";
}

bool CHODFModel::getIsCurrent(CHMatch * pMatch)
{
	if (!pMatch)
		return false;

	return (pMatch->getStatus()==CHMemoryDataBase::eRunning );
}

MSLWString CHODFModel::getMatchLDescription(CHMatch *pMatch, const char * lang, bool info)
{
	//Women Basketball, Pool A, Match 3, POL vs NZL
	CHDefinition &aDef = (CHDefinition &)CHMemoryDataBase::getDefinition();

	MSLWString desc = NULLWSTRING;
	if (!pMatch)
		return desc;
	
	desc = pMatch->getEventLDescription(lang);
	desc += L"";	
	desc += L" ";
	
	GTHPhase *pPhase = pMatch->getPhase();
	if (pPhase)
	{
		if (!pPhase->getIsPool())		
			desc += pPhase->getLDescription(lang);
	}

	CHEvent * pEvent = (CHEvent * )pMatch->getEvent();
	if (pEvent->isTeam())
	{
		if (pPhase->getIsPool())
		{
			desc += L" ";
			desc += pMatch->getRoundAsString(true,false);
			desc += L" ";
			desc += aDef.getSMatchDescription(lang);
			desc += L" ";
			if (pMatch->getMatchNumber())
				desc += TOWSTRING(pMatch->getMatchNumber());
			else
				desc += TOWSTRING(pMatch->getCode());
		}			
		else
		{
			desc += L" ";
			desc += aDef.getSMatchDescription(lang);
			desc += L" ";
			if (pMatch->getMatchNumber())
				desc += TOWSTRING(pMatch->getMatchNumber());
			else
				desc += TOWSTRING(pMatch->getCode());		
		}
	}
	else
	{
		if (pPhase->getIsPool())
		{
			desc += L" ";
			desc += pMatch->getRoundAsString(true,false);
			desc += L" ";
			desc += aDef.getSMatchDescription(lang);
			desc += L" ";
			if (pMatch->getMatchNumber())
				desc += TOWSTRING(pMatch->getMatchNumber());
			else
				desc += TOWSTRING(pMatch->getCode());
		}
		else 
		{
			desc += L" ";
			desc += aDef.getSMatchDescription(lang);
			desc += L" ";
			if (pMatch->getMatchNumber())
				desc += TOWSTRING(pMatch->getMatchNumber());
			else
				desc += TOWSTRING(pMatch->getCode());
		}
	}

	return desc;
}

MSLWString CHODFModel::getMatchSDescription(CHMatch *pMatch, const char * lang, bool info)
{
	//Women Basketball, Pool A, Match 3, POL vs NZL
	CHDefinition &aDef = (CHDefinition &)CHMemoryDataBase::getDefinition();

	MSLWString desc = NULLWSTRING;
	if (!pMatch)
		return desc;
	
	GTHPhase *pPhase = pMatch->getPhase();
	
	if (!info)
	{
		desc = pMatch->getEventSDescription(lang);
		desc += L"";	
		desc += L" ";
	}

	if (pPhase)
	{
		if (!pPhase->getIsPool())
			desc += pPhase->getLDescription(lang);
	}

	CHEvent * pEvent = (CHEvent * )pMatch->getEvent();
	if (pEvent->isTeam())
	{
		if(pMatch->getSubMatch())
		{
			desc += L" ";
			desc += aDef.getSMatchDescription(lang);
			desc += L" ";
			desc += TOWSTRING(pMatch->getSubCode());
		}
		else
		{
			if (pPhase->getIsPool())
			{
				desc += L" ";
				desc += pMatch->getRoundAsString(false,false);
				desc += L" ";
				desc += aDef.getSMatchDescription(lang);
				desc += L" ";
				desc += TOWSTRING(pMatch->getCode());
			}			
			else
			{
				desc += L" ";
				desc += aDef.getSMatchDescription(lang);
				desc += L" ";
				desc += TOWSTRING(pMatch->getCode());
			}
		}
	}
	else
	{
		if (pPhase->getIsPool())
		{
			desc += L" ";
			desc += pMatch->getRoundAsString(false,false);
			desc += L" ";
			desc += aDef.getSMatchDescription(lang);
			desc += L" ";
			desc += TOWSTRING(pMatch->getMatchNumber());
		}
		else 
		{
			desc += L" ";
			desc += aDef.getSMatchDescription(lang);
			desc += L" ";
			desc += TOWSTRING(pMatch->getMatchNumber());
		}
	}

	return desc;
}

MSLString CHODFModel::getMasterType(CHRegister* pRegister)
{
	if (!pRegister)
		return "";	

	return pRegister->getMasterTypeSDescription().toAscii();
}

MSLString CHODFModel::getColor(CHMatchResult * pMR)
{
	if (!pMR)
		return NULLSTRING;

	return pMR->getColor()==CHMatchResult::eWhite ? WHITE : BLACK;
}

bool CHODFModel::hasMatchesInSession(GSession *pSession, MSLSortedVector &vMatches)
{
	if (!pSession)
		return 0;

	MSLSet colMatches = (CHMemoryDataBase::getCol(__GTHMATCH)).select(sessionMatches, pSession );
	vMatches = MSLSortedVector(colMatches);
	
	return vMatches.entries() ? true : false;						
}	

CHEvent * CHODFModel::getEventSession(GSession* pSession)
{
	MSLSortedVector vMatches;
	if (hasMatchesInSession (pSession, vMatches))
	{
		MSLString eventCode = NULLSTRING;
		for (short i=0;i<vMatches.entries();i++)
		{
			CHMatch * pMatch = (CHMatch *)vMatches[i];
			if (eventCode==NULLSTRING)
			{
				eventCode = pMatch->getEventCode();
				continue;
			}
			if (eventCode!=pMatch->getEventCode())
				return 0;
		}
		return (CHEvent *) ((CHMatch*)vMatches[0])->getEvent();
	}

	return 0;
}

void CHODFModel::fillMembers(CHMatchResult* pMatchResult, MSLSortedVector &vMembers)
{
	CHEvent* pEvent = (CHEvent*)pMatchResult->getEvent();
	if (!pEvent)
		return;

	pMatchResult->getMatchMembersVector(vMembers);
	vMembers.setFcCompare(orderMatchMembersByName);
	vMembers.sort();	
}