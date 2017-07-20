/*************************************************************************************
*			© Copyright MSL Software, S.L., 2015
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHODF2Brackets.h
*	Description	:
*
*	Author		: Antonio Balmaseda
*	Date created: 22-01-2015
* 	Project		: AR ODF
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#include "StdAfx.h"
#include "CHODF2Brackets.h"
#include "CHODFApp.h"
#include "CHODFModel.h"
#include "CHODF2Defines.h"

#include "..\CHMngtModel\CHMatch.h"
#include "..\CHMngtModel\CHPhase.h"
#include "..\CHMngtModel\CHMatchResult.h"
#include "..\CHMngtModel\CHPoolResult.h"
#include "..\CHMngtModel\CHInscription.h"

int ordMatches(const MSLItem** a,const MSLItem** b)
{
	CHMatch * pMatchA = (CHMatch *)(*a);
	CHMatch * pMatchB = (CHMatch *)(*b);

	int order=pMatchA->getPhaseOrder() - pMatchB->getPhaseOrder();
	if(order)
		return order;

	return (strcmp(pMatchA ->getKey(),pMatchB->getKey()));
}

CHODF2Brackets::CHODF2Brackets(ODF2BuildBase * pBuild,XMLElement * pElement,ODF2FileBase * pFile,GEvent * pEvent)
:ODF2THZZBrackets(pBuild,pElement,pFile,pEvent)
{
}

CHODF2Brackets::~CHODF2Brackets()
{
}

mslToolsFcCompare CHODF2Brackets::getSortUnits() const
{
	return ordMatches;
}

void CHODF2Brackets::fillBracketData(XMLElement *pEl_BracketItem,MSLItem * pData,short pos)
{
	GTHMatch * pMatch = pData && pData->isA()==__GTHMATCH ? (GTHMatch *)pData : 0;
	if( !pMatch )
		return;

	pEl_BracketItem->setAttribute("Code",getMatchNumber(pData));
	pEl_BracketItem->setAttribute("Order",short(pos+1));
	if(pMatch->getStartDate().isValid())
		pEl_BracketItem->setAttribute("Date",pMatch->getStartDateAsString("%Y-%m-%d"));
	pEl_BracketItem->setAttribute("Time",pMatch->getStartTimeAsString("%H:%M"));
	if( pMatch->getStatus() >= GMemoryDataBase::eUnofficial )
		pEl_BracketItem->setAttribute("Result",getResult(pMatch));
}

MSLString CHODF2Brackets::getMatchNumber(MSLItem * pData)
{
	GTHMatch * pMatch = pData && pData->isA()==__GTHMATCH ? (GTHMatch *)pData : 0;
	if( !pMatch )
		return "";

	return TOSTRING(pMatch->getMatchNumber(),"0");
}

//tipos diferentes de Brackets
short CHODF2Brackets::getTypeBrackets()
{
	if (!m_pData)
		return 0;

	CHEvent * pEvent = (CHEvent *)m_pData;

	MSLSortedVector vPhases;
	pEvent->getPhasesVector(vPhases);
	MSLSet sTypeBrackets;
	for (short i=0;i<vPhases.entries();i++)
	{
		CHPhase* pPhase = (CHPhase*)vPhases[i];
		if (!pPhase->getIsPool() && pPhase->getPhase()!=BRONZE_MEDAL)
		{
			MSLNumber aNumber(eFinals);
			if (!sTypeBrackets.find(&aNumber))
			{
				MSLNumber * pNum = new MSLNumber(eFinals);
				sTypeBrackets.insert(pNum);
			}
		}
		else if (pPhase->getPhase()==BRONZE_MEDAL)
		{
			MSLNumber aNumber(eBronze);
			if (!sTypeBrackets.find(&aNumber))
			{
				MSLNumber * pNum = new MSLNumber(eBronze);
				sTypeBrackets.insert(pNum);
			}
		}
	}

	short typeBrackets = short(sTypeBrackets.entries());
	sTypeBrackets.clearAndDestroy();
	return typeBrackets;
}

//Phases a insertar en el tipo de Bracket.
bool CHODF2Brackets::insertInVector(GPhase *pPhase, short typeBracket)
{
	if ( typeBracket == eFinals && ( pPhase->getPhase()==GOLD_MEDAL	      || 
									 pPhase->getPhase()==SEMIFINAL		) )
		return true;

	if ( typeBracket == eBronze  && ( pPhase->getPhase()==BRONZE_MEDAL ) )
		return true;
	
	return false;
}

MSLString CHODF2Brackets::getBracketCode(GEvent *pEvent, short typeBracket)
{
	UNREFERENCED_PARAMETER(pEvent);

	if (typeBracket==eFinals)
		return CH_BRACKET_FNL;
	if (typeBracket==eBronze)
		return CH_BRACKET_BRN;
		
	return NULLSTRING;
}

//Dentro del bracket los items que code se le va a dar.
MSLString  CHODF2Brackets::getBracketItemsCode(GPhase *pPhase)
{
	if(pPhase)
	{
		if  ( pPhase->getPhase()==GOLD_MEDAL  || pPhase->getPhase()==BRONZE_MEDAL )
			return CH_BRACKET_ITEM_FNL;
		else if(pPhase->getPhase()==SEMIFINAL )
			return CH_BRACKET_ITEM_SFL;		
	}
	
	return NULLSTRING;
}

//detro de cada BracketItems los partidos que hay que introducir.
void CHODF2Brackets::fillVectorEUnits(GPhase *pPhase,MSLSortedVector& vEUnits)
{
	GTHMatch * pMatch = 0;
	MSLSet colMatches;
	((GTHPhase *)pPhase)->getMatches(colMatches);
	MSLSortedVector vMatches(colMatches);
	for(int i=0 ; i<vMatches.entries() ; i++)
	{
		pMatch = (GTHMatch *)vMatches[i];
		if (pMatch->getSubMatch())
			continue;

		if( pMatch)
			vEUnits.insert(pMatch);
	}	
}

MSLString CHODF2Brackets::getResult(GTHMatch * pMatch)
{
	return ((CHMatch*)pMatch)->getResultAsString();
}

void CHODF2Brackets::fillVectorAthletes(MSLArray& vAthletes,MSLItem * pData)
{
	CHMatchResult* pMR = (CHMatchResult*) (pData && pData->isA()==__GTHMATCHRESULT?(GTHMatchResult*)pData:0);
	if(!pMR)
		return;

	CHEvent* pEvent=(CHEvent*) pMR->getEvent();
	if (!pEvent)
		return;

	if(pEvent->getRegType()==GRegister::individual)
		vAthletes.insert(pMR);
	else 
	{
		MSLSortedVector vMembers;
		CHODFMODEL->fillMembers(pMR,vMembers);
		for(short i=0 ; i<vMembers.entries() ; i++ )
		{
			GData* pData = (GData*) vMembers[i];
			vAthletes.insert(pData);
		}
	}	
}

void CHODF2Brackets::fillPreviousUnit(XMLElement *pEl_CompPlace,MSLItem * pData)
{
	if( !pEl_CompPlace || !pData )
		return;

	GTHMatchResult * pMR = pData && pData->isA()==__GTHMATCHRESULT ? (GTHMatchResult *)pData : 0;
	if( !pMR )
		return;

	GTHPoolResult * pPR = pMR->getPoolResult();
	GTHMatch * pMatchSrc = ODF2THModel::getTHModel()->getMatchSource(pMR);

	if (!pMatchSrc)
		return;

	ODF2THZZBrackets::fillPreviousUnit(pEl_CompPlace,pData);
}

void CHODF2Brackets::fillVectorExtBracketsAthletes(MSLArray & vExtBracketAths,MSLItem * pData)
{
	if( !pData )
		return;

	vExtBracketAths.insert(insertZZExtension(pData,"","","",""));
}

XMLElement * CHODF2Brackets::fillVectorExtBracketAth(MSLItem * pData,XMLElement * pElement)
{
	ODFZZExt * pExtension = pData && pData->isA()==__ODFEXTENSION ? (ODFZZExt *)pData : 0;
	if( !pExtension )
		return 0;

	XMLElement *pEl=0;
	CHMatchResult *pMR=0;
	CHInscription *pTeInsc=0;
	short currRank=0;
	MSLString qType="";
	bool sOut=false;

	if(((ODFZZExt *)pData)->getExtItem()->isA()==__CHMATCHRESULT)
	{
		pMR = (CHMatchResult *)((ODFZZExt *)pData)->getExtItem();
		if( !pMR )
			return 0;

		CHPhase* pPhase = (CHPhase*)pMR->getPhase();
		if (!pPhase)
			return 0;

		fillRankingRoundExtBracketAth(pElement,pMR);

		if (pMR->getMatchStatus()==CHMemoryDataBase::eFinished &&
			pMR->getOpponent() && !pMR->getOpponent()->getBye())
		{
			addExtension("ExtBracketAths","ExtBracketAth",pElement,RES,SCORE,"",pMR->getResult());

			if (pMR->getQualitativeCode()!=OK)
			{
				//RES/ARROWS
				addExtension("ExtBracketAths","ExtBracketAth",pElement,RES, IRM,"",pMR->getQualitativeSDescription("ENG").toAscii());
			}
		}		
	}
	else if(((ODFZZExt *)pData)->getExtItem()->isA()==__CHMEMBER)
	{
		CHMember *pMM = (CHMember *)((ODFZZExt *)pData)->getExtItem();
		if( !pMM )
			return 0;
	}

	return pEl;
}

bool CHODF2Brackets::fillRankingRoundExtBracketAth(XMLElement * pElement, CHMatchResult *pMR)
{
	CHPoolResult* pPoolResult = (CHPoolResult*) pMR->getPoolResult();
	if (!pPoolResult)
		return false;

	CHPhase* pPhase = (CHPhase*)pPoolResult->getPrevPhase();
	if (!pPhase)
		return false;

	if (!pPhase->isSwissRound())
		return false;

	//RR/RANK_RND
	addExtension("ExtBracketAths","ExtBracketAth",pElement,SR,RANK_SWISS_RND,"",TOSTRING(pMR->getSwissRoundRank()));
		
	//RR/SCORE
	addExtension("ExtBracketAths","ExtBracketAth",pElement,SR,SCORE,"",pMR->getSwissRoundScore());

	return true;
}

void CHODF2Brackets::fillVectorExtBracketsCompetitors(MSLArray & vExtBracketsCompetitors,MSLItem * pData)
{
	if( !pData )
		return;

	vExtBracketsCompetitors.insert(insertZZExtension(pData,"","","",""));
}

XMLElement * CHODF2Brackets::fillVectorExtBracketComp(MSLItem * pData,XMLElement * pElement)
{
	ODFZZExt * pExtension = pData && pData->isA()==__ODFEXTENSION ? (ODFZZExt *)pData : 0;
	if( !pExtension )
		return 0;

	XMLElement *pEl=0;
	CHMatchResult *pMR=0;
	CHInscription *pTeInsc=0;
	short currRank=0;
	MSLString qType="";
	bool sOut=false;

	if(((ODFZZExt *)pData)->getExtItem()->isA()==__CHMATCHRESULT)
	{
		pMR = (CHMatchResult *)((ODFZZExt *)pData)->getExtItem();
		if( !pMR )
			return 0;

		CHPhase* pPhase = (CHPhase*)pMR->getPhase();
		if (!pPhase)
			return 0;

		if (!pPhase->isTeamEvent())
			return 0;

		fillRankingRoundExtBracketComp(pElement,pMR);

		if (pMR->getMatchStatus()==CHMemoryDataBase::eFinished &&
			pMR->getOpponent() && !pMR->getOpponent()->getBye())
		{
			//RES/SET
			addExtension("ExtBracketComps","ExtBracketComp",pElement,RES,SCORE,"",pMR->getResult());

			if (pMR->getQualitativeCode()!=OK)
			{
				//RES/ARROWS
				addExtension("ExtBracketComps","ExtBracketComp",pElement,RES, IRM,"",pMR->getQualitativeSDescription("ENG").toAscii());
			}
		}		
	}
	
	return pEl;
}

bool CHODF2Brackets::fillRankingRoundExtBracketComp(XMLElement * pElement, CHMatchResult *pMR)
{
	CHPoolResult* pPoolResult = (CHPoolResult*) pMR->getPoolResult();
	if (!pPoolResult)
		return false;

	CHPhase* pPhase = (CHPhase*)pPoolResult->getPrevPhase();
	if (!pPhase)
		return false;

	if (!pPhase->isSwissRound())
		return false;

	//RR/RANK_RND
	addExtension("ExtBracketComps","ExtBracketComp",pElement,SR,RANK_SWISS_RND,"",TOSTRING(pMR->getSwissRoundRank()));
		
	//RR/SCORE
	addExtension("ExtBracketComps","ExtBracketComp",pElement,SR,SCORE,"",pMR->getSwissRoundScore());

	return true;
}