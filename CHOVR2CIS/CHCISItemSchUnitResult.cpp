/*************************************************************************************
*			© Copyright MSL Software, S.L., 2008
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHCISItemSchUnitResult.h
*	Description	:
*
*	Author		: BK Team
*	Date created: 28-03-2011
* 	Project		: BKOVR2CIS
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#include "StdAfx.h"
#include "CHCISItemSchUnitResult.h"

#include "..\CHMngtModel\CHMatch.h"
#include "..\CHMngtModel\CHMatchResult.h"

CHCISItemSchUnitResult::CHCISItemSchUnitResult(GData* pData)
:GTHCISItemSchUnitResult(pData)
{
}

CHCISItemSchUnitResult::~CHCISItemSchUnitResult()
{
}

MSLWString CHCISItemSchUnitResult::getScore(const char * lang/*=0*/)
{
	if( m_pData && m_pData->isA()==__CHMATCHRESULT )
	{
		CHMatch* pMatch = (CHMatch*) ((CHMatchResult *)m_pData)->getMatch();
		return ((CHMatchResult *)m_pData)->getResult().toUnicode();
	}

	return L"";
	UNREFERENCED_PARAMETER(lang);
}

MSLString CHCISItemSchUnitResult::getRegKeyA()
{
	if( m_pData && m_pData->isA()==__CHMATCHRESULT )
	{
		CHMatch* pMatch = (CHMatch*) ((CHMatchResult *)m_pData)->getMatch();
		if (pMatch->getPhaseCode()==SWISS_ROUND)
			return NULLSTRING;
	}

	return GTHCISItemSchUnitResult::getRegKeyA();
}

MSLString CHCISItemSchUnitResult::getRegKeyB()
{
	if( m_pData && m_pData->isA()==__CHMATCHRESULT )
	{
		CHMatch* pMatch = (CHMatch*) ((CHMatchResult *)m_pData)->getMatch();
		if (pMatch->getPhaseCode()==SWISS_ROUND)
			return NULLSTRING;
	}

	return GTHCISItemSchUnitResult::getRegKeyB();
}

MSLWString CHCISItemSchUnitResult::getIDCompetitorSDesc(const char* lang)
{
	if( m_pData && m_pData->isA()==__CHMATCHRESULT )
	{
		CHMatch* pMatch = (CHMatch*) ((CHMatchResult *)m_pData)->getMatch();
		if (pMatch->getPhaseCode()==SWISS_ROUND)
			return NULLSTRING;
	}

	return GTHCISItemSchUnitResult::getIDCompetitorSDesc(lang);
}

MSLWString CHCISItemSchUnitResult::getIDCompetitorLDesc(const char* lang)
{	
	return GTHCISItemSchUnitResult::getIDCompetitorLDesc(lang);
}