/*************************************************************************************
*			© Copyright MSL Software, S.L., 2015
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: ARODF2Config.h
*	Description	:
*
*	Author		: Antonio Balmaseda
*	Date created: 29-01-2015
* 	Project		: AR ODF
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#include "StdAfx.h"
#include "ARODF2Config.h"
#include "ARODFApp.h"
#include "ARODF2Defines.h"
#include "ARODFModel.h"

static
int orderMatchesByDate(const MSLItem** a, const MSLItem** b)
{
	ARMatch *pMatchA=(ARMatch *)(*a);
	ARMatch *pMatchB=(ARMatch *)(*b);

	if(!pMatchA->getStartDate().isValid())
		return 1;

	if(!pMatchB->getStartDate().isValid())
		return -1;

	int rc= pMatchA->getStartDate().value()-pMatchB->getStartDate().value();
	if(rc)
		return rc;

	return strcmp(pMatchA->getKey(),pMatchB->getKey());
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

ARODF2Config::ARODF2Config(ODF2BuildBase * pBuild,XMLElement * pElement,ODF2FileBase * pFile,GData * pData/*=0*/)
:ODF2ZZConfig(pBuild,pElement,pFile,pData)
,m_pSession((GSession*)pData)
{
}

ARODF2Config::~ARODF2Config(void)
{
}

void ARODF2Config::fillVectorConfigs(MSLArray& vConfigs)
{
	if (m_pSession)
	{
		vConfigs.insert(m_pSession);
	}
	else
	{
		MSLSortedVector vMatches;
		MSLSortedVector vSessions(ARMemoryDataBase::getCol(__GSESSION),orderSessions);
		GSession * pSession=0;
		for(int i=0 ; i<vSessions.entries() ; i++)
		{
			pSession=(GSession*)vSessions[i];
			if ( ARODFMODEL->hasMatchesInSession(pSession,vMatches))
				vConfigs.insert(pSession);
		}
	}
}

void ARODF2Config::fillSportConfig(MSLItem * pDataCfg,XMLElement * pEl_Config)
{

	if(pDataCfg->isA()==__GSESSION)
	{
		pEl_Config->setAttribute("Gender","0");
		pEl_Config->setAttribute("Event" , ARODFMODEL->getRSCCodeEvent( ARODFMODEL->getEventSession((GSession*)pDataCfg) ) );
		pEl_Config->setAttribute("Phase" , ARODFMODEL->getRSC((GSession*)pDataCfg,0,RSC_PHASE));
		pEl_Config->setAttribute("Unit"  , ARODFMODEL->getRSC((GSession*)pDataCfg,0,RSC_MATCH));
	}
}

void ARODF2Config::fillExtendedConfig(MSLItem * pDataCfg, XMLElement * pEl_Config)
{
	if( !pEl_Config || !pDataCfg )
		return;

	if(pDataCfg->isA()==__GSESSION)
	{
		GSession * pSession=(GSession*)pDataCfg;

		XMLElement * pEl_ExtConfig1 = addExtension("", "ExtendedConfig", pEl_Config, EC, SESSION, "1","" );
		if( pEl_ExtConfig1 )
			addSessionUnits(pEl_ExtConfig1,pSession);
	}
}

void ARODF2Config::addSessionUnits(XMLElement *pEl, GSession* pSession)
{
	ARMatch *pMatch=0;
	MSLSortedVector vMatches;
	if (ARODFMODEL->hasMatchesInSession (pSession, vMatches))
	{
		for (short i=0;i<vMatches.entries();i++)
		{
			pMatch = (ARMatch *)vMatches[i];
			if(pMatch->getSessionKey()==pSession->getKey())
			{
				addExtension("", "ExtendedConfigItem", pEl, "", UNIT, "", ODF2Model::getRSC(pMatch));
			}
		}
	}
}
