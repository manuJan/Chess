/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : LRegister.cpp
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
#include "CHRegister.h"
#include "QCHRegister.h"
#include "UCHRegister.h"
#include "CHMasterType.h"
#include "CHMemoryDataBase.h"

#include <ovr/core/G/GBuffer.h>


MSLDEFINE_ITEM(CHRegister, __CHREGISTER);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHRegister::CHRegister()
:GRegister()
,m_masterType(0)
{
}

CHRegister::CHRegister(const CHRegister &copy)
{
	operator=(copy);
}

CHRegister::~CHRegister()
{
}
//operator
GData& CHRegister::operator =(const GData& copy)
{
	CHRegister& aCopy=(CHRegister&)copy;
	
	if ( this != &copy )
	{
		GRegister::operator = (copy);
	
		m_masterType=aCopy.m_masterType;
	}	

	return *this;
}

bool CHRegister::operator ==(const GData& copy)
{
	CHRegister& aCopy=(CHRegister&)copy;

	if ( this == &copy )
		return true;

	if( GRegister::operator ==(copy) )
		return m_masterType==aCopy.m_masterType;

	return false;
}

bool CHRegister::operator !=(const GData& copy)
{
	return !operator==(copy);
}

QBase* CHRegister::onQ() const
{
	return new QCHRegister();
}

UBase* CHRegister::onU() const
{
	return new UCHRegister();
}

//pack
MSLPack& CHRegister::pack(MSLPack & aPack) const
{
	GRegister::pack (aPack);

	aPack << m_masterType;

	return aPack;
}

MSLPack& CHRegister::unpack(MSLPack &aPack)
{
	GRegister::unpack (aPack);

	aPack >> m_masterType;

	return aPack;
}
// set
void CHRegister::setMasterType(const short value)
{
	m_masterType = value;
}
// get
short CHRegister::getMasterType() const
{
	return m_masterType;
}

MSLString CHRegister::getMasterTypeAsString(bool longer/*=true*/) const
{
	CHMasterType *pMast=(CHMasterType *)CHMemoryDataBase::findMasterType(m_masterType);
	if (pMast && pMast->getMasterType()>0)
		return longer ? pMast->getLDescription().toAscii() : pMast->getSDescription().toAscii();

	return NULLSTRING;
}

short CHRegister::getMasterTypeOrder() const
{
	CHMasterType *pMast=(CHMasterType *)CHMemoryDataBase::findMasterType(m_masterType);
	return (pMast?pMast->getOrder():0);
}