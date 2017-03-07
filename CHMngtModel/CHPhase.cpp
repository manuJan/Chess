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
#include "CHEvent.h"
#include "UCHPhase.h"
#include "CHClassIDs.h"
#include "CHMemoryDataBase.h"


RWDEFINE_COLLECTABLE(CHPhase, __CHPHASE);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHPhase::CHPhase()
:THSPPhase()
,typePhase(CHPhaseBase::eElim)
,idTeamMatchsCnfg(0)
{
}

CHPhase::CHPhase(const CHPhase& copy)
{
	operator=(copy);
}

CHPhase::CHPhase(CPack &aPack)
{
	unpack(aPack);
}

CHPhase::~CHPhase()
{
}

CHPhase & CHPhase::operator = (const CHPhase & copy)
{
	if (this != &copy)
	{
		THSPPhase::operator=(copy);
		typePhase			= copy.typePhase;
		idTeamMatchsCnfg	= copy.idTeamMatchsCnfg;
	}
	return *this;
}

RWBoolean CHPhase::operator == (const CHPhase & copy)
{
	if (this == &copy)
		return true;
	
	else 
		return (THSPPhase::operator==(copy)					&&
				typePhase			== copy.typePhase		&&
				idTeamMatchsCnfg	== copy.idTeamMatchsCnfg);
}

RWBoolean CHPhase::operator != (const CHPhase & copy)
{
	return !operator==(copy);
}

RWBoolean CHPhase::uSQL(RWDBConnection& pConnect,RWBoolean remove/*=false*/)
{
	RWBoolean rc=false;

	UCHPhase upd(&pConnect);
	if( remove )
		rc=upd.remove(*this);
	else
		rc=upd.set(*this);
	return rc;
}

RWCString CHPhase::msl() const
{
	RWCString str=THSPPhase::msl();
	GBuffer aBuffer;
	if(str==NULLRWSTRING)
		return str;

	return str + RWCString (aBuffer << getOrder()
									<< typePhase
									<< idTeamMatchsCnfg
									<< endLine);
}

RWCString CHPhase::mslDescription(const char *language) const
{
	return THSPPhase::mslDescription(language);
}

CPack& CHPhase::pack(CPack& aPack)
{
	THSPPhase::pack(aPack);
		
	aPack << typePhase;
	aPack << idTeamMatchsCnfg;
	
	return aPack;
}

CPack& CHPhase::unpack(CPack& aPack)
{
	THSPPhase::unpack(aPack);
	
	aPack >> typePhase;
	aPack >> idTeamMatchsCnfg;

	return aPack;
}
//////////////////////////////////////////////////////////////////////
//set
//////////////////////////////////////////////////////////////////////
void CHPhase::setTypePhase(const short value)
{
	typePhase=value;
}
void CHPhase::setIdTeamMatchsCnfg(const short value)
{
	idTeamMatchsCnfg=value;
}

//////////////////////////////////////////////////////////////////////
//get
//////////////////////////////////////////////////////////////////////
short CHPhase::getTypePhase() const
{
	return typePhase;
}
short CHPhase::getIdTeamMatchsCnfg() const
{
	return idTeamMatchsCnfg;
}

//////////////////////////////////////////////////////////////////////
//Help Methods
//////////////////////////////////////////////////////////////////////
short CHPhase::getNumRounds()
{
	CHPool * pPool=(CHPool*)getPool(0);
	if(pPool)
		return pPool->getNumRounds();

	return 0;

}

RWBoolean CHPhase::hasCompetitors()
{
	if (getStatus()>=CHMemoryDataBase::eStartList)
		return true;

	CHPool* pPool = 0;
	CHMatch* pMatch = 0;
	for (size_t i=0;i<getPoolsVector().entries();i++)
	{
		pPool = (CHPool*)getPoolsVector()[i]->getElement();
		if (pPool->hasCompetitors())
			return true;

		for (size_t j=0;j<pPool->getMatchsVector().entries();j++)
		{
			pMatch = (CHMatch*)pPool->getMatchsVector()[j]->getElement();
			if (pMatch->hasCompetitors(true) || 
				pMatch->isBye())
				return true;
		}
	}
	return false;
}
