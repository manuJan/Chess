#include "StdAfx.h"
#include "CHODF2ZZSchedule.h"
#include "CHODFApp.h"
#include "CHODFModel.h"
#include "..\CHMngtModel\CHMember.h"
#include "..\CHMngtModel\CHPhase.h"
#include "..\CHMngtModel\CHMatch.h"
#include "..\CHMngtModel\CHPool.h"
#include "..\CHMngtModel\CHRegister.h"

static int orderCHMembers(const MSLItem** a, const MSLItem** b)
{
	CHMember * pMemberA = (CHMember *)(*a);
	CHMember * pMemberB = (CHMember *)(*b);
	
	GRegister * pRegisterA = pMemberA->getRegister();
	GRegister * pRegisterB = pMemberB->getRegister();

	int order = _wcsicoll(pRegisterA->getPrnLName(),pRegisterB->getPrnLName());
	return order ? order : strcmp(pMemberA->getKey(), pMemberB->getKey());
}


CHODF2ZZSchedule::CHODF2ZZSchedule(ODF2BuildBase * pBuild,XMLElement * pElement,ODF2FileBase * pFile,GData * pData)
	:ODF2THZZSchedule(pBuild,pElement,pFile,pData)
{
}

CHODF2ZZSchedule::~CHODF2ZZSchedule()
{
}

ODF2ZZSchLine * CHODF2ZZSchedule::createSchLine(GData * pData)
{
	if( !pData || !m_pFile )
		return 0;

	if( pData->isA()!=__GTHMATCH )
		return 0;

	GTHMatch * pMatch = (GTHMatch * )pData;
	if (pMatch->getSubMatch())
		return 0;

	ODF2OrderBase::TypeAction action = m_pFile->getAction();
	ODF2ZZSchLine * pLine = new ODF2ZZSchLine(pMatch,action);

	pLine->setPhaseType("3");	//Competition
	pLine->setUnitCode  (ODF2THModel::getRSC(pMatch));
	pLine->setUnitNumber(TOSTRING(pMatch->getMatchNumber()));
	pLine->setUnitStatus(pMatch->getStatus()); 
	pLine->setUnitSDate (pMatch->getStartDate());
	pLine->setUnitSTime (pMatch->getStartTime());
	pLine->setUnitEDate (pMatch->getEndDate());
	pLine->setUnitETime (pMatch->getEndTime());
	pLine->setUnitEstEDate(true);
	pLine->setUnitMedal(ODF2THModel::getTHModel()->isMedalsMatch(pMatch));
	pLine->setUnitVenue(pMatch->getVenueCode());
	pLine->setUnitLocation(CHODFMODEL->getCourtODFString((CHMatch *)pMatch));//GMemoryDataBase::getMainLocationCourtCode(pMatch->getVenueCode()));
	pLine->setSessionCode(pMatch->getSessionLDescription().toAscii());

	return pLine;
/*	return ODF2THZZSchedule::createSchLine(pData);*/
}

MSLWString CHODF2ZZSchedule::getItemNameDescription(GData * pData,const char * language/*=0*/)
{
	CHMatch * pMatch = pData && pData->isA()==__GTHMATCH ? (CHMatch *)pData : 0;
	if( !pMatch )
		return L"";

	CHPhase * pPhase = (CHPhase *)pMatch->getPhase();
	CHPool * pPool = (CHPool *)pMatch->getPool();
	if( !pPhase || !pPool )
		return L"";

	MSLWString description = pMatch->getEventLDescription(language);
	description += L" " + pMatch->getPhaseLDescription(language);
	if( pPool->getIsPool() && pPool->getPhasePoolsNumber() > 1 )
		description += L" " + pMatch->getPoolDescription(pPhase->getPoolDescription(),language);
	//description += L" " + ((GTHDefinition &)GTHMemoryDataBase::getDefinition()).getSMatchDescription(language);
	//description += L" " + TOWSTRING(pMatch->getMatchNumber());
	return description;
}

void CHODF2ZZSchedule::fillVectorComposition(MSLItem * pCompetitor,MSLArray& vComposition)
{
	if( !pCompetitor )
		return;

	GTHMatchResult * pMatchResult = (GTHMatchResult *)pCompetitor;
	if (!pMatchResult)
		return;

	CHMatch * pMatch=(CHMatch*)pMatchResult->getMatch();
	if (pMatch->isTeam())
	{
		m_memberOrder = 0;

		CHRegister * pRegister=(CHRegister*)pMatchResult->getRegister();
		if(pRegister)
		{
			MSLSortedVector vMembers;
			pRegister->getMembersVector(vMembers); //la ordenacion me vale la genérica.
			for (long i=0;i<vMembers.entries();i++)
			{
				CHMember* pMember = (CHMember*)vMembers[i];
				if (isSelectable(pMember,eMember))
					vComposition.insert(pMember);
			}
		}
	}
	else
		ODF2THZZSchedule::fillVectorComposition(pCompetitor,vComposition);
}

mslToolsFcCompare CHODF2ZZSchedule::getVectorCompositionCompare()
{
	return orderCHMembers;
}

MSLString CHODF2ZZSchedule::isMedalsMatch(CHMatch * pMatch)
{
	if( !pMatch )
		return ME_NO;

	CHPhase * pPhase = (CHPhase *)pMatch->getPhase();
	if( !pPhase )
		return ME_NO;

	short wr = pPhase->getWinnerRank();
	short lr = pPhase->getLoserRank();

	if (wr==1 || wr==2 || lr==1 || lr==2)
		return ME_YES_GOLD;
	if (wr==3 || lr==3)
		return ME_YES_BRONZE;

	return ME_NO;
}

