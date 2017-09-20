/*************************************************************************************
*			© Copyright MSL Software, S.L., 2012
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHODFZZScheduleDescription.cpp
*	Description	:
*
*	Author		: 
*	Date created: 19-11-2013
* 	Project		: Archery ODF
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#include "StdAfx.h"
#include "CHODFZZScheduleDescription.h"
#include "CHODFApp.h"
#include "CHODFModel.h"
#include "..\CHMngtModel\CHMatch.h"
#include "..\CHMngtModel\CHPhase.h"
#include "..\CHMngtModel\CHPool.h"

CHODFZZScheduleDescription::CHODFZZScheduleDescription(ODFBuildMessage * pBuild,XMLElement * pElement,ODFFile * pFile)
:ODFTHScheduleDescription(pBuild,pElement,pFile)
{
}

CHODFZZScheduleDescription::~CHODFZZScheduleDescription()
{
}

void CHODFZZScheduleDescription::createSchLines()
{
	if (m_pData && m_pData->isA()==__CHMATCH)
	{
		CHMatch *pMatch=(CHMatch *)m_pData;
		if (/*pMatch->getStatus()>=GMemoryDataBase::eSchedulled && */ pMatch->getMatchNumber()>0)
		{
			ODFZZSchLine * pLine = createSchLine(pMatch);
			if( pLine )
				m_vSchLines.insert(pLine);
		}
	}
	else
	{
		CHMatch *pMatch = 0;
		MSLSetIterator iter(GTHMemoryDataBase::getCol(__GTHMATCH));
		while( (pMatch=(CHMatch *)iter())!=0 )
		{
			//if( pMatch->getStatus()>=GMemoryDataBase::eSchedulled)
			//{
				ODFZZSchLine * pLine = createSchLine(pMatch);
				if( pLine )
					m_vSchLines.insert(pLine);
			//}
		}
	}
}

ODFZZSchLine * CHODFZZScheduleDescription::createSchLine(GData * pData)
{
	if( !pData || pData->isA()!=__GTHMATCH )
		return 0;

	GTHMatch * pMatch = (GTHMatch *)pData;
	if( !pMatch )
		return 0;

	if (pMatch->getSubMatch())
		return 0;

	if( !pData || pData->isA()!=__GTHMATCH )
		return 0;

	ODFZZSchLine * pLine = new ODFZZSchLine(pMatch,ODFOrder::eUpdate);
	pLine->setGenderCode(ODF2Model::getRSCCodeSex	(pMatch->getEvent()));
	pLine->setEventCode (ODF2Model::getRSCCodeEvent(pMatch->getEvent()));	
	if( pMatch->getIsPool() )
		pLine->setPhaseCode(ODF2THModel::getTHModel()->getRSCCodeMatchPhase(pMatch));
	else
		pLine->setPhaseCode(ODF2Model::getRSCCodePhase(pMatch->getPhase()));
	pLine->setUnitCode (ODF2THModel::getRSCCodeMatch(pMatch));
	pLine->setUnitSDate(pMatch->getStartDate());
	pLine->setUnitSTime(pMatch->getStartTime());
	pLine->setUnitMedal( ODF2THModel::getTHModel()->isMedalsMatch(pMatch));
	return pLine;
}

void CHODFZZScheduleDescription::fillLevelPhase(XMLElement * pEl_Event,ODFZZSchLine * pSchPh)
{
	if( !pEl_Event || !pSchPh )
		return;

	XMLElement *pEl_Phase=pEl_Event->setElement(m_pEntPhase);
	if( !pEl_Phase )
		return;

	pEl_Phase->setAttribute("Code",pSchPh->getPhaseCode());

	// Phase Description
	GLanguage *pLang=0;
	MSLSetIterator it(GMemoryDataBase::getCol(__GLANGUAGE));		
	while( (pLang=(GLanguage *)it())!=0 )
	{
		if( pLang->getActiveFlag() != 0 )
			fillPhaseDescriptionChess(pEl_Phase->setElement(m_pEntPhaseDescription), pSchPh->getData(), pLang->get());
	}

	//Pillamos las units
	MSLArray vSchUnit;
	fillSchUnits(pSchPh,vSchUnit);

	ODFZZSchLine * pSchUnit = 0;
	for( long i=0;i<vSchUnit.entries();i++ )
	{
		pSchUnit = (ODFZZSchLine *)vSchUnit[i];

		//UNIT LEVEL
		fillLevelUnit(pEl_Phase,pSchUnit);
	}
}

void CHODFZZScheduleDescription::fillPhaseDescriptionChess(XMLElement * pEl_PhaseDescription, GData * pData, MSLString lang)
{
	if( !pEl_PhaseDescription || !pData )
		return;

	if (pData->isA()==__CHPHASE)
	{
		CHPhase* pPhase = (CHPhase*)pData;

		pEl_PhaseDescription->setAttribute("Lang",lang);
		pEl_PhaseDescription->setAttribute("ILDescription",getPhaseILDescription(pPhase,lang));
		pEl_PhaseDescription->setAttribute("ISDescription",getPhaseIDescription(pPhase,lang));
		pEl_PhaseDescription->setAttribute("LDescription",getPhaseLDescription(pPhase,lang));
		pEl_PhaseDescription->setAttribute("SDescription",getPhaseSDescription(pPhase,lang));
	}
	if (pData->isA()==__CHPOOL)
	{
		CHPhase* pPhase = (CHPhase*) ((CHPool*)pData)->getPhase();

		pEl_PhaseDescription->setAttribute("Lang",lang);
		pEl_PhaseDescription->setAttribute("ILDescription",getPhaseILDescription(pPhase,lang));
		pEl_PhaseDescription->setAttribute("ISDescription",getPhaseIDescription(pPhase,lang));
		pEl_PhaseDescription->setAttribute("LDescription",getPhaseLDescription(pPhase,lang));
		pEl_PhaseDescription->setAttribute("SDescription",getPhaseSDescription(pPhase,lang));
	}
	if (pData->isA()==__CHMATCH)
	{
		CHMatch* pMatch = (CHMatch*)pData;

		pEl_PhaseDescription->setAttribute("Lang",lang);
		pEl_PhaseDescription->setAttribute("ILDescription",getPhaseMatchILDescription(pMatch,lang));
		pEl_PhaseDescription->setAttribute("ISDescription",getPhaseMatchIDescription(pMatch,lang));
		pEl_PhaseDescription->setAttribute("LDescription" ,getPhaseMatchLDescription(pMatch,lang));
		pEl_PhaseDescription->setAttribute("SDescription" ,getPhaseMatchSDescription(pMatch,lang));
	}
}

MSLWString CHODFZZScheduleDescription::getPhaseIDescription(GPhase * pPhase,MSLString lang)
{
	if( !pPhase )
		return L"";

	return ODFTHScheduleDescription::getPhaseIDescription(pPhase,lang);
}

MSLWString CHODFZZScheduleDescription::getPhaseLDescription(GPhase * pPhase,MSLString lang)
{
	GTHPhase * pTHPhase = (GTHPhase *)pPhase;
	CHEvent * pEvent = pTHPhase ? (CHEvent *)pTHPhase->getEvent() : 0;
	if( !pTHPhase || !pEvent )
		return L"";

	return ODFTHScheduleDescription::getPhaseLDescription(pPhase,lang);
}

MSLWString CHODFZZScheduleDescription::getPhaseSDescription(GPhase * pPhase,MSLString lang)
{
	GTHPhase * pTHPhase = (GTHPhase *)pPhase;
	CHEvent * pEvent = pTHPhase ? (CHEvent *)pTHPhase->getEvent() : 0;
	if( !pTHPhase || !pEvent )
		return L"";

	return ODFTHScheduleDescription::getPhaseSDescription(pPhase,lang);
}

MSLWString CHODFZZScheduleDescription::getPhaseMatchILDescription(CHMatch *pMatch, MSLString lang)
{
	MSLWString desc = getPhaseILDescription(pMatch->getPhase(), lang);
	desc += L", ";
	desc += pMatch->getRoundAsString(true,false);
	return desc;
}

MSLWString CHODFZZScheduleDescription::getPhaseMatchIDescription(CHMatch *pMatch, MSLString lang)
{
	MSLWString desc = getPhaseIDescription(pMatch->getPhase(), lang);
	desc += L", ";
	desc += pMatch->getRoundAsString(true,false);
	return desc;
}

MSLWString CHODFZZScheduleDescription::getPhaseMatchLDescription(CHMatch *pMatch, MSLString lang)
{
	MSLWString desc = getPhaseLDescription(pMatch->getPhase(), lang);
	desc += L", ";
	desc += pMatch->getRoundAsString(true,false);
	return desc;
}

MSLWString CHODFZZScheduleDescription::getPhaseMatchSDescription(CHMatch *pMatch, MSLString lang)
{
	MSLWString desc = getPhaseSDescription(pMatch->getPhase(), lang);
	desc += L", ";
	desc += pMatch->getRoundAsString(false,false);
	return desc;
}

MSLWString CHODFZZScheduleDescription::getUnitIDescription(GData * pSchLineData,MSLString lang)
{
	CHMatch * pMatch = pSchLineData && pSchLineData->isA()==__CHMATCH ? (CHMatch *)pSchLineData : 0;
	if( !pMatch )
		return L"";

	MSLWString desc = CHODFMODEL->getMatchSDescription(pMatch,lang,true);
	return desc;
}

MSLWString CHODFZZScheduleDescription::getUnitILDescription(GData * pSchLineData,MSLString lang)
{
	CHMatch * pMatch = pSchLineData && pSchLineData->isA()==__CHMATCH ? (CHMatch *)pSchLineData : 0;
	if( !pMatch )
		return L"";

	MSLWString desc = CHODFMODEL->getMatchLDescription(pMatch,lang,true);
	return desc;
}
