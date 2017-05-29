/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHMasterType.cpp
*	Description	:
*
*	Author		:CH Team
*	Date created:09-12-2005
* 	Project		:Chess Management Model DLL
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdCHMngt.h"
#include "CHMasterType.h"
#include "QCHMasterType.h"
#include "UCHMasterType.h"

MSLDEFINE_ITEM(CHMasterType,__CHMASTERTYPE)

/////////////////////////////////////////////////////////////////////
// Constructors & Destructor
//////////////////////////////////////////////////////////////////////

CHMasterType::CHMasterType()
:GData()
,m_masterType(0)
,m_order(0)
{
	setKey();
}

CHMasterType::CHMasterType(const short id)
:GData()
,m_masterType(id)
{
	setKey();
}

CHMasterType::CHMasterType(const CHMasterType & copy)
{
	operator=(copy);
}


CHMasterType::~CHMasterType()
{
}

//////////////////////////////////////////////////////////////////////
// Overloaded Operators
//////////////////////////////////////////////////////////////////////

GData& CHMasterType::operator= (const GData& copy)
{
	if (this != &copy)
	{
		const CHMasterType & distance=(const CHMasterType &) copy;

		m_order		 = distance.m_order;
		m_masterType = distance.m_masterType; 
		m_Desc		 = distance.m_Desc;
	}
	return *this;
}

bool   CHMasterType::operator==(const GData& copy)
{
	if (this == &copy)
		return true;

	const CHMasterType & eventDiscipline=(const CHMasterType &) copy;

	return ( m_order	  == eventDiscipline.m_order		&&
			 m_masterType == eventDiscipline.m_masterType	&&
			 m_Desc		  == eventDiscipline.m_Desc);
}

bool CHMasterType::operator!=(const GData& copy)
{
	return !operator==(copy);
}

MSLPack& CHMasterType::pack(MSLPack& aPack) const
{
	aPack << m_order;
	aPack << m_masterType;
	aPack << m_Desc;
	
	return aPack;
}

MSLPack& CHMasterType::unpack(MSLPack& aPack)
{
	aPack >> m_order;
	aPack >> m_masterType;
	aPack >> m_Desc;
	
	return aPack;
}

//////////////////////////////////////////////////////////////////////
// Set Methods
//////////////////////////////////////////////////////////////////////

void CHMasterType::setMasterType(const short value)
{
	m_masterType = value;
	setKey();
}

void CHMasterType::setOrder(const short value)
{
	m_order = value;
}

QBase* CHMasterType::onQ() const
{
	return new QCHMasterType();
}

UBase* CHMasterType::onU() const
{
	return new UCHMasterType();
}

void CHMasterType::setKey()
{
	char tmp[10];
	sprintf_s(tmp,"%d",m_masterType);
	key=tmp;	
}

void CHMasterType::setDescriptions(GDescription & desc)
{
	m_Desc.set(desc);	
}

//////////////////////////////////////////////////////////////////////
// Get Methods
//////////////////////////////////////////////////////////////////////
short CHMasterType::getMasterType() const
{ 
	return m_masterType; 
}

short CHMasterType::getOrder() const
{
	return m_order;
}

GDescriptions& CHMasterType::getDescriptions() const
{
	return (GDescriptions&)m_Desc;
}

// Class Methods
MSLWString CHMasterType::getSDescription(const char *lang/*=0*/)  const
{
	return m_Desc.get(lang,_SNAME);	
}

MSLWString CHMasterType::getLDescription(const char *lang/*=0*/)  const
{
	return m_Desc.get(lang,_LNAME);	
}





