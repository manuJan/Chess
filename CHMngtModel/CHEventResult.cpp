/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be consideHome liable for any mistake or omission in the edition of    
*   this document. MSL is a registeHome trademark.                                      
*                                                                                      
*   File name   : CHEventResult.cpp                                                                 
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
#include "CHEventResult.h"
#include "CHPoolResult.h"
#include "CHSportDefines.h"
#include "QCHEventResult.h"
#include "UCHEventResult.h"
#include <ovr/core/G/GBuffer.h>

MSLDEFINE_ITEM(CHEventResult, __CHEVENTRESULT)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHEventResult::CHEventResult()
:GEventResult()
,m_rating(0)
{
	setQualitative(OK);
}

CHEventResult::CHEventResult(const CHEventResult & copy)
{
	operator=(copy);
}

CHEventResult::~CHEventResult()
{
}


//////////////////////////////////////////////////////////////////////
// Operators
//////////////////////////////////////////////////////////////////////
GData & CHEventResult::operator =(const GData & copy)
{
	if (this != &copy)
	{
		GEventResult::operator =(copy);
				
		const CHEventResult & aEventResult=(const CHEventResult &) copy;

		m_rating = aEventResult.m_rating;
	}
	return * this;
}

bool CHEventResult::operator ==(const GData & copy)
{
	if (this == &copy)
		return true;
	
	const CHEventResult & aEventResult=(const CHEventResult &) copy;

	return (GEventResult::operator ==(copy)		&& 
			m_rating == aEventResult.m_rating);
}

bool CHEventResult::operator !=(const GData & copy)
{
	return !operator==(copy);
}


//////////////////////////////////////////////////////////////////////
// From GData
//////////////////////////////////////////////////////////////////////

MSLPack& CHEventResult::pack(MSLPack& aPack) const
{
	GEventResult::pack(aPack);
		
	aPack << m_rating;
	
	return aPack;
}

MSLPack& CHEventResult::unpack(MSLPack& aPack)
{
	GEventResult::unpack(aPack);
		
	aPack >> m_rating;
	
	return aPack;
}

QBase* CHEventResult::onQ() const
{
	return new QCHEventResult();
}

UBase* CHEventResult::onU() const
{
	return new UCHEventResult();
}


//////////////////////////////////////////////////////////////////////
// Sets
//////////////////////////////////////////////////////////////////////

void CHEventResult::setRating(const short value)
{
	m_rating = value;
}

//////////////////////////////////////////////////////////////////////
// Gets
//////////////////////////////////////////////////////////////////////

short CHEventResult::getRating() const
{
	return m_rating;
}
MSLString CHEventResult::getRatingAsString() const
{ 
	MSLString aux="-";
	if (m_rating)
		aux=TOSTRING(m_rating);
	return aux; 
}

CHPoolResult * CHEventResult::getPoolResult()
{
	MSLSetIterator iter(CHMemoryDataBase::getCol(__CHPOOLRESULT));
	
	CHPoolResult *pPoolResult = 0;

	while ((pPoolResult = (CHPoolResult*) iter())!=0 )
	{
		if (pPoolResult->getInscription() == getInscription())
			return pPoolResult;
	}

	return NULL;
}
float CHEventResult::getPointsPoolResult()
{
	CHPoolResult *pPoolResult=getPoolResult();
	if(pPoolResult)
		return pPoolResult->getPointsF();
	
	return 0;
}

MSLString CHEventResult::getPointsPoolResultStr()
{
	CHPoolResult *pPoolResult=getPoolResult();
	if(pPoolResult)
		return pPoolResult->getPointsFStr();
	
	return NULLSTRING;
}