/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHMember.cpp
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
#include "CHMember.h"
#include "UCHMember.h"
#include "QCHMember.h"
#include "CHRegister.h"

MSLDEFINE_ITEM(CHMember, __CHMEMBER);
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHMember::CHMember()
:GMember(0,0)
,m_function(eNone)
,m_rating(0)
,m_kConst(0)
{
}

CHMember::CHMember(GRegister * iRegister, GRegister * tRegister)
:GMember(iRegister,tRegister)
,m_function(eNone)
,m_rating(0)
,m_kConst(0)
{
}

CHMember::CHMember(const CHMember &copy)
:GMember(0,0)
{
	operator=(copy);
}

CHMember::~CHMember()
{

}

GData &CHMember::operator = (const GData &copy)
{
	if ( this != &copy )
	{
		const CHMember & aMember=(const CHMember &) copy;

		GMember::operator	= (copy);
		
		m_function			= aMember.m_function;
		m_rating			= aMember.m_rating;
		m_kConst			= aMember.m_kConst;
	}
	return *this;
}

bool CHMember::operator == (const GData &copy)
{
	if ( this == &copy )
		return true;
	
	const CHMember & aMember=(const CHMember &) copy;

	return	(GMember::operator	==(copy)				&&
			 m_function			== aMember.m_function	&&
			 m_rating			== aMember.m_rating		&&
			 m_kConst			== aMember.m_kConst);
}

bool CHMember::operator != (const GData &copy)
{
	return !operator==(copy);
}

QBase* CHMember::onQ() const
{
	return new QCHMember();
}

UBase* CHMember::onU() const
{
	return new UCHMember();
}	

MSLPack& CHMember::pack(MSLPack & aPack) const
{
	GMember::pack (aPack);

	aPack << m_function;
	aPack << m_rating;
	aPack << m_kConst;

	return aPack;
}

MSLPack& CHMember::unpack(MSLPack &aPack)
{
	GMember::unpack (aPack);

	aPack >> m_function;
	aPack >> m_rating;
	aPack >> m_kConst;

	return aPack;
}
//set
void CHMember::setFunction(const short value)
{
	m_function=value;
}
void CHMember::setRating(const short value)
{
	m_rating = value;
}
void CHMember::setKConst(const short value)
{
	m_kConst = value;
}
//get
short CHMember::getFunction() const
{
	return m_function;
}
short CHMember::getRating() const
{
	return m_rating;
}
short CHMember::getKConst() const
{
	return m_kConst;
}

MSLString CHMember::getRatingAsString() const
{ 
	MSLString aux="-";	
	if (m_rating)
		aux=TOSTRING(m_rating);
	return aux; 
}
MSLString CHMember::getKConstAsString() const
{ 
	MSLString aux="-";
	if (m_kConst)
		aux=TOSTRING(m_kConst);
	return aux; 
}

GFunction *CHMember::getCFunction() const
{
	return (!m_function?(GFunction *)0:((GFunction *)CHMemoryDataBase::findFunction(char(m_function))));
}

MSLWString CHMember::getFunctionLDescription() const
{
	GFunction *pFunc=(!m_function?(GFunction *)0:((GFunction *)CHMemoryDataBase::findFunction(char(m_function))));
	return !pFunc?_T("None"):pFunc->getLDescription();
}

CHEvent *CHMember::getEvent() const
{
	return (CHEvent *)(getInscription()->getEvent());
}

int CHMember::getRegisterCode() const
{
	return getRegister()?getRegister()->getRegister():0;
}
