/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHPhase.cpp
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:07-12-2005
*   Project     :CH Model
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///

#include "stdCHMngt.h"
#include "CHPhase.h"
#include "CHPhaseBase.h"
#include "CHEvent.h"
#include "CHPool.h"
#include "CHMatch.h"
#include "UCHPhase.h"
#include "QCHPhase.h"
#include "CHMemoryDataBase.h"


MSLDEFINE_ITEM(CHPhase, __CHPHASE);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHPhase::CHPhase()
:GTHPhase()
,m_typePhase(CHPhaseBase::eElim)
,m_idTeamMatchsCnfg(0)
{
}

CHPhase::CHPhase(const CHPhase& copy)
{
	operator=(copy);
}

CHPhase::~CHPhase()
{
}

GData & CHPhase::operator = (const GData & copy)
{
	if (this != &copy)
	{
		GTHPhase::operator=(copy);

		const CHPhase & aPhase=(const CHPhase &) copy;

		m_typePhase			= aPhase.m_typePhase;
		m_idTeamMatchsCnfg	= aPhase.m_idTeamMatchsCnfg;
	}
	return *this;
}

bool CHPhase::operator == (const GData & copy)
{
	if (this == &copy)
		return true;
	
	const CHPhase & aPhase=(const CHPhase &) copy;
	
	return (GTHPhase::operator==(copy)						&&
			m_typePhase			== aPhase.m_typePhase		&&
			m_idTeamMatchsCnfg	== aPhase.m_idTeamMatchsCnfg);
}

bool CHPhase::operator != (const GData & copy)
{
	return !operator==(copy);
}

QBase*	CHPhase::onQ() const
{
	return new QCHPhase();
}

UBase* CHPhase::onU() const
{
	return new UCHPhase();
}

MSLPack& CHPhase::pack(MSLPack& aPack) const
{
	GTHPhase::pack(aPack);
		
	aPack << m_typePhase;
	aPack << m_idTeamMatchsCnfg;
	
	return aPack;
}

MSLPack& CHPhase::unpack(MSLPack& aPack)
{
	GTHPhase::unpack(aPack);
	
	aPack >> m_typePhase;
	aPack >> m_idTeamMatchsCnfg;

	return aPack;
}
//////////////////////////////////////////////////////////////////////
//set
//////////////////////////////////////////////////////////////////////
void CHPhase::setTypePhase(const short value)
{
	m_typePhase=value;
}
void CHPhase::setIdTeamMatchsCnfg(const short value)
{
	m_idTeamMatchsCnfg=value;
}

//////////////////////////////////////////////////////////////////////
//get
//////////////////////////////////////////////////////////////////////
short CHPhase::getTypePhase() const
{
	return m_typePhase;
}
short CHPhase::getIdTeamMatchsCnfg() const
{
	return m_idTeamMatchsCnfg;
}

//////////////////////////////////////////////////////////////////////
//Help Methods
//////////////////////////////////////////////////////////////////////

bool CHPhase::hasCompetitors()
{
	if (getStatus()>=CHMemoryDataBase::eStartList)
		return true;

	CHPool* pPool = 0;
	CHMatch* pMatch = 0;

	MSLSortedVector vPools;
	getPoolesVector(vPools);

	for (short i=0;i<vPools.entries();i++)
	{
		pPool = (CHPool*)vPools[i];
		if (pPool->hasCompetitors())
			return true;

		MSLSortedVector vMatches;
		pPool->getMatchesVector(vMatches);
		
		for (short j=0;j<vMatches.entries();j++)
		{
			pMatch = (CHMatch*)vMatches[j];
			if (pMatch->hasCompetitors(true) || 
				pMatch->hasByes())
				return true;
		}
	}
	return false;
}
