/*************************************************************************************
*			© Copyright MSL Software, S.L., 2012
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHODFParamsExt.cpp
*	Description	:
*
*	Author		: 
*	Date created: 07-05-2012
* 	Project		: Basket ODF
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "StdAfx.h"
#include "CHODFParamsExt.h"
#include <OVR/GUI/ODF2/ODFMngr/ODFMessage.h>

#include "..\CHMngtModel\CHDefinition.h"
#include "..\CHMngtModel\CHMatch.h"

static
int orderMatchesByKey(const MSLItem** a, const MSLItem** b)
{
	GTHMatch* pA=(GTHMatch*)(*a);
	GTHMatch* pB=(GTHMatch*)(*b);

	return strcmp(pA->getKey(),pB->getKey());
}

static
int orderSessions(const MSLItem** a,const MSLItem** b)
{
	GSession *pA= ((GSession *) (*a));
	GSession *pB= ((GSession *) (*b));

	int order = pA->getDate().value()-pB->getDate().value();
	if (order)
		return order;

	order=strcmp(pA->getTimeAsString("%H%M"),pB->getTimeAsString("%H%M") );
	if (order)
		return order;

	order = pA->getSession()-pB->getSession();
	if (order)
		return order;

	return strcmp(pA->getKey(),pB->getKey());
}

static
int orderByODFEvents(const MSLItem** a, const MSLItem** b)
{
	GEvent *pEvA=(GEvent *)(*a);
	GEvent *pEvB=(GEvent *)(*b);

	//Sex
	int order=(int)strcmp(pEvA->getSex(),pEvB->getSex());
	if( order )
		return order;

	//Order
	order = pEvA->getOrder()-pEvB->getOrder();
	if( order )
		return order;

	//Key
	return strcmp(pEvA->getKey(),pEvB->getKey());
}


CHODFParamsExt::CHODFParamsExt(long id, CHODFGUI * pGUI)
:ODFTHParamsExt(id,pGUI)
,m_pGUI(pGUI)
{
}

CHODFParamsExt::~CHODFParamsExt()
{
}

void CHODFParamsExt::fillParamsCollection(bool gridCall,MSLSet & col,TypeParam type)
{
	MSLDate aSelDate(INVALID_DATE);
	GTHEvent * pSelEvent=0;
	if(gridCall)
	{
		aSelDate =getSelDate();
		pSelEvent=getSelEvent();
	}

	MSLSortedVector vMatches(GTHMemoryDataBase::getCol(__GTHMATCH),orderMatchesByKey);

	bool sameDay,sameEvent;
	GTHMatch * pMatch=0;
	for(int i=0 ; i<vMatches.entries() ; i++)
	{
		pMatch=(GTHMatch*)vMatches[i];
		if (pMatch->getSubMatch())
			continue;

		if(pMatch->getStatus()>= GTHMemoryDataBase::eSchedulled)
		{
			sameDay=false;
			sameEvent=false;

			if(!aSelDate.isValid()   || (aSelDate.isValid() && pMatch->getStartDate().value()==aSelDate.value()) )
				sameDay=true;

			if(!pSelEvent || (pSelEvent && pMatch->getEvent()==pSelEvent))
				sameEvent=true;

			if( type == eParamDay )
			{
				if( pMatch->getStartDate().isValid() && sameDay)
				{
					MSLDate * pDay=0;
					if(pDay && !col.find(pDay))
						col.insert(pDay);
				}
			}
			else if(sameDay && sameEvent)
			{
				if(type==eParamMatch)
					col.insert(pMatch);
				else if(type==eParamPhase)
					col.insert(pMatch->getPhase());
				else if(type==eParamPool && pMatch->getIsPool())
					col.insert(pMatch->getPool());
				else if(type==eParamEvent)
					col.insert(pMatch->getEvent());
			}
		}
	}
}


void CHODFParamsExt::fillVectorParams(ODFMessage * pMessage,MSLArray& vParams,bool gridCall)
{
	if( !pMessage )
		return;

	MSLString msgDocType = pMessage->getMessage();	

	if (msgDocType==DT_CONFIG)
	{
		//Events
		MSLSortedVector vSessions( GTHMemoryDataBase::getCol(__GSESSION), orderSessions);
		
		GSession * pSession = 0;
		for( long i=0;i<vSessions.entries();i++ )
		{
			pSession = (GSession*)vSessions[i];
			vParams.insert(pSession);
		}
	}
	if( msgDocType==DT_BRACKETS)
	{
		//EVENT
		MSLSortedVector vEv(GMemoryDataBase::getCol(__GEVENT),orderByODFEvents);
		GEvent * pEvent = 0;
		for( long i=0;i<vEv.entries();i++ )
		{
			pEvent = (GEvent *)vEv[i];

			MSLSortedVector vPhases;
			pEvent->getPhasesVector(vPhases);

			if( vPhases.entries()>1 && pEvent->isEnable() && (pEvent->hasMedal() || msgDocType==DT_BRACKETS))
				vParams.insert(pEvent);
		}
		return;
	}

	ODFTHParamsExt::fillVectorParams(pMessage,vParams,gridCall);
}

MSLWString CHODFParamsExt::getParamDescription(void * pParam)
{
	if( !pParam )
		return L"";

	GData * pData = (GData *)pParam;
	switch(pData->isA())
	{
		case __GSESSION:
		{
			MSLWString sessionDesc = ((GSession *)pData)->getLDescription();
			if (sessionDesc.length()==0)
			{
				sessionDesc = TOWSTRING(((GSession *)pData)->getAcumulated());
				sessionDesc += L".";
				sessionDesc += ((GSession *)pData)->getDateAsString();
				sessionDesc += L"-";
				sessionDesc += ((GSession *)pData)->getTimeAsString().toUnicode();
			}
			return sessionDesc;
		}
	}
	return ODFTHParamsExt::getParamDescription(pParam);
}

MSLWString CHODFParamsExt::getMatchDescription(GTHMatch * pMatch)
{
	CHDefinition &aDef = (CHDefinition &)CHMemoryDataBase::getDefinition();
	
	MSLWString desc = NULLWSTRING;
	if (!pMatch)
		return desc;
		
	GTHPhase *pPhase = pMatch->getPhase();

	desc = pMatch->getEventSDescription();
	desc += L"";	
	desc += L" ";
	
	if (pPhase)
		desc += pPhase->getLDescription();
	
	CHEvent * pEvent = (CHEvent * )pMatch->getEvent();
	if (pEvent && pEvent->isTeam())
	{
		if (pPhase->getIsPool())
		{
			desc += L" ";
			desc += ((CHMatch*) pMatch)->getRoundAsString(false,false);
			desc += L" ";
			desc += aDef.getSMatchDescription();
			desc += L" ";
			desc += TOWSTRING(pMatch->getCode());
			desc += L" ";
		}			
		else
		{
			desc += L" ";
			desc += aDef.getSMatchDescription();
			desc += L" ";
			desc += TOWSTRING(pMatch->getCode());
			desc += L" ";
		}		
	}
	else
	{
		if (pPhase->getIsPool())
		{
			desc += L" ";
			desc += ((CHMatch*)pMatch)->getRoundAsString(false,false);
			desc += L" ";
			desc += aDef.getSMatchDescription();
			desc += L" ";
			desc += TOWSTRING(pMatch->getMatchNumber());
			desc += L" ";
		}
		else 
		{
			desc += L" ";
			desc += aDef.getSMatchDescription();
			desc += L" ";
			desc += TOWSTRING(pMatch->getMatchNumber());
			desc += L" ";
		}
	}

	GTHMatchResult * pHome = (GTHMatchResult *)pMatch->getHome();
	GTHMatchResult * pAway = (GTHMatchResult *)pMatch->getAway();

	if( pHome  )
	{
		if (pHome->getInscription())
			desc += MSLWString(pHome->getGroup());		
		else if (pHome->getBye())
			desc += "BYE";
		else
			desc += "UKN";
	}

	if( pAway )
	{
		desc += L" - " ;
		if (pAway->getInscription())
			desc += MSLWString(pAway->getGroup());
		else if (pAway->getBye())
			desc += "BYE";
		else
			desc += "UKN";
	}

	return desc;
}