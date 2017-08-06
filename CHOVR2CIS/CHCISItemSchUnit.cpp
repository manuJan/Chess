/*************************************************************************************
*			© Copyright MSL Software, S.L., 2008
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHCISItemSchUnit.h
*	Description	:
*
*	Author		: BK Team
*	Date created: 23-03-2011
* 	Project		: BKOVR2CIS
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "StdAfx.h"
#include "CHCISItemSchUnit.h"
#include "CHCISProcess.h"

#include "..\CHMngtModel\CHMatch.h"
#include "..\CHMngtModel\CHMatchResult.h"

CHCISItemSchUnit::CHCISItemSchUnit(GData* pData)
:GTHCISItemSchUnit(pData)
{
}

CHCISItemSchUnit::~CHCISItemSchUnit()
{
}

MSLWString CHCISItemSchUnit::getLDescription(const char * lang/*=0*/)
{
	if (m_pData && m_pData->isA()==__CHMATCH)
	{
		CHMatch* pMatch = (CHMatch*)m_pData;
		return CHPROCESS->getMatchLDescription(pMatch,lang);
	}

	return L"";
	UNREFERENCED_PARAMETER(lang);
}

MSLWString CHCISItemSchUnit::getSDescription(const char * lang/*=0*/)
{
	if (m_pData && m_pData->isA()==__CHMATCH)
	{
		CHMatch* pMatch = (CHMatch*)m_pData;
		return CHPROCESS->getMatchSDescription(pMatch,lang);
	}
	return L"";
	UNREFERENCED_PARAMETER(lang);
}

MSLString CHCISItemSchUnit::getRegKeyA()
{
	if (m_pData && m_pData->isA()==__GTHMATCH)
	{
		CHMatch* pMatch = (CHMatch*)m_pData;
		if (pMatch->getIsPool())
			return NULLSTRING;
	}

	return GTHCISItemSchUnit::getRegKeyA();
}

MSLString CHCISItemSchUnit::getRegKeyB()
{
	if (m_pData && m_pData->isA()==__GTHMATCH)
	{
		CHMatch* pMatch = (CHMatch*)m_pData;
		if (pMatch->getIsPool())
			return NULLSTRING;
	}
	return GTHCISItemSchUnit::getRegKeyB();
}


MSLWString CHCISItemSchUnit::getScore(const char * lang/*=0*/)
{
	if (m_pData && m_pData->isA()==__GTHMATCH)
	{
		CHMatch* pMatch = (CHMatch*)m_pData;
		if (pMatch->getIsPool())
			return NULLSTRING;

		if (pMatch->getStatus()>=CHMemoryDataBase::eRunning)
			return pMatch->getResultAsString().toUnicode();
	}
	return L"";
	UNREFERENCED_PARAMETER(lang);
}

MSLWString CHCISItemSchUnit::getScoreA(const char * lang/*=0*/)
{
	if (m_pData && m_pData->isA()==__CHMATCH)
	{
		CHMatch* pMatch = (CHMatch*)m_pData;
		if (pMatch->getIsPool())
			return NULLSTRING;

		CHMatchResult* pMatchResult =0;
		pMatchResult = (CHMatchResult*) pMatch->getHome();		
		if (pMatch->getStatus()>=CHMemoryDataBase::eRunning)
		{
			if (pMatchResult)
				return pMatchResult->getResult().toUnicode();
		}
	}
	return L"";
	UNREFERENCED_PARAMETER(lang);
}

MSLWString CHCISItemSchUnit::getScoreB(const char * lang/*=0*/)
{
	if (m_pData && m_pData->isA()==__CHMATCH)
	{
		CHMatch* pMatch = (CHMatch*)m_pData;
		if (pMatch->getIsPool())
			return NULLSTRING;

		CHMatchResult* pMatchResult = (CHMatchResult* ) pMatch->getAway();		
		if (pMatch->getStatus()>=CHMemoryDataBase::eRunning)
			if (pMatchResult)
				return pMatchResult->getResult().toUnicode();
	}
	return L"";
	UNREFERENCED_PARAMETER(lang);	
}

int CHCISItemSchUnit::getTypeBracket()
{
	if( m_pData && m_pData->isA()==__GTHMATCH )
	{
		CHMatch* pMatch = (CHMatch*)m_pData;
		if (pMatch->getPhaseCode()==SEMIFINAL		|| 
			pMatch->getPhaseCode()==GOLD_MEDAL		)
			return 1;

		if (pMatch->getPhaseCode()==BRONZE_MEDAL)
			return 2;		
	}	
	return 0;
}

bool CHCISItemSchUnit::getPaintMatchBracket()
{
	if( m_pData && m_pData->isA()==__GTHMATCH )
	{
		CHMatch* pMatch = (CHMatch*)m_pData;
		CHMatchResult* pHome = (CHMatchResult* ) pMatch->getHome();
		CHMatchResult* pAway = (CHMatchResult* ) pMatch->getAway();

		if (pHome && pAway && pHome->getBye() && pAway->getBye())
			return false;
	}
	return true;
}

short CHCISItemSchUnit::getCourtCode()		
{
	if (m_pData && m_pData->isA()==__GTHMATCH)
	{
		CHMatch* pMatch = (CHMatch*)m_pData;
		if (!pMatch->getIsPool())
			return ((GTHMatch *)m_pData)->getCourtCode();
	}
	return 0;
}