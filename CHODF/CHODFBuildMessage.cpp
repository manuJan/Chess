/*************************************************************************************
*			© Copyright MSL Software, S.L., 2012
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHODFBuildMessage.cpp
*	Description	:
*
*	Author		: 
*	Date created: 7-5-2012
* 	Project		: Basket ODF
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#include "StdAfx.h"
#include "CHODFBuildMessage.h"
#include "CHODF2Defines.h"
#include "CHODFZZEventDescription.h"
#include "CHODFZZScheduleDescription.h"
#include "CHODF2Participant.h"
#include "CHODF2ZZSchedule.h"
#include "CHODF2Team.h"
#include "CHODF2Results.h"
#include "CHODF2PoolStandings.h"
#include "CHODF2Brackets.h"
#include "CHODF2Ranking.h"
#include "..\CHMngtModel\CHMatch.h"
/*
#include "ARODF2Config.h"
*/

CHODFBuildMessage::CHODFBuildMessage(ODFGUI * pGUI)
:ODFTHBuildMessage(pGUI)
{
}


CHODFBuildMessage::~CHODFBuildMessage()
{
}

bool CHODFBuildMessage::getPIT(ODFFile * pFile,XMLElement * pCompetitionElem)
{
	if( !pFile || !pCompetitionElem )
		return false;

	GData * pData = (GData *)pFile->getOrderParam();
	MSLString msg = pFile->getDocType();
	MSLString subtype = pFile->getDocSubType();

	if( msg==DT_EVENT_DESCRIPTION )
	{
		CHODFZZEventDescription aZZEventDesc(this,pCompetitionElem,pFile);
		return aZZEventDesc.run();
	}
	if( msg==DT_SCHEDULE_DESCRIPTION && pData==0 )
	{
		CHODFZZScheduleDescription aZZScheduleDesc(this,pCompetitionElem,pFile);
		return aZZScheduleDesc.run();
	}

	return ODFTHBuildMessage::getPIT(pFile,pCompetitionElem);
}
	

bool CHODFBuildMessage::getRT(ODFFile * pFile,XMLElement * pCompetitionElem)
{
	if( !pFile || !pCompetitionElem )
		return false;

	GData * pData = (GData *)pFile->getOrderParam();
	MSLString msg = pFile->getDocType();
	MSLString subtype = pFile->getDocSubType();

	return ODFTHBuildMessage::getRT(pFile,pCompetitionElem);
}

bool CHODFBuildMessage::getODF2(ODF2FileBase * pFile,XMLElement * pCompetitionElem)
{
	if( !pFile || !pCompetitionElem )
		return false;

	GData * pData = (GData *)pFile->getOrderParam();

	MSLString msg = pFile->getDocType();
	if( msg==DT_PARTIC || msg==DT_PARTIC_UPDATE )
	{
		CHODF2Participant aPartic(this,pCompetitionElem,pFile,(GRegister *)pData);
		return aPartic.run();
	}

	else if( msg==DT_SCHEDULE|| msg==DT_SCHEDULE_UPDATE)
	{
		CHODF2ZZSchedule aSch(this,pCompetitionElem,pFile,pData);
		return aSch.run();
	}

	else if( msg==DT_PARTIC_TEAMS || msg==DT_PARTIC_TEAMS_UPDATE )
	{
		CHODF2Team aPartic(this,pCompetitionElem,pFile,(GRegister *)pData);
		return aPartic.run();
	}
		
	else if( msg==DT_RESULT && pData )
	{
		if (!pData || pData->isA()!=__CHMATCH)
			return false;

		CHMatch* pMatch = (CHMatch*)pData;
		if (pMatch->getSubMatch())
			return false;

		CHODF2Results aRS(this,pCompetitionElem,pFile,pData);
		return aRS.run();
	}
	else if (msg==DT_POOL_STANDING && pData)
	{
		CHODF2PoolStandings aPS(this,pCompetitionElem,pFile,pData);
		return aPS.run();
	}
	else if( msg==DT_BRACKETS && pData )
	{
		CHODF2Brackets aBrackets(this,pCompetitionElem,pFile,(GEvent *)pData);
		return aBrackets.run();
	}
	else if (msg==DT_RANKING && pData)
	{
		CHODF2Ranking aRK(this,pCompetitionElem,pFile,pData);
		return aRK.run();
	}
	/*else if (msg==DT_CONFIG)
	{
		ARODF2Config aCF(this,pCompetitionElem,pFile,pData);
		return aCF.run();
	}*/
		
	return ODFBuildMessage::getODF2(pFile,pCompetitionElem);
}
