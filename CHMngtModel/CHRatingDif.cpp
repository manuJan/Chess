/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHRatingDif.cpp
*	Description	:
*
*	Author		:CH Team
*	Date created:26-01-2006
* 	Project		:Chess Management Model DLL
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdCHMngt.h"
#include "CHRatingDif.h"
#include "QCHRatingDif.h"
#include "UCHRatingDif.h"
#include <ovr/core/G/GScore.h>

MSLDEFINE_ITEM(CHRatingDif,__CHRATINGDIF)

/////////////////////////////////////////////////////////////////////
// Constructors & Destructor
//////////////////////////////////////////////////////////////////////

CHRatingDif::CHRatingDif()
:GData()
,m_code(0)
,m_difference(0)
,m_probability(0)
{

}
CHRatingDif::CHRatingDif(const short id)
:GData()
,m_code(id)
,m_difference()
,m_probability(0)
{
	setKey();
}

CHRatingDif::CHRatingDif(const CHRatingDif & copy)
{	
	operator=(copy);
}


CHRatingDif::~CHRatingDif()
{	
}

//////////////////////////////////////////////////////////////////////
// Overloaded Operators
//////////////////////////////////////////////////////////////////////

GData & CHRatingDif::operator = (const GData & copy)
{		
	if (this != &copy)
	{
		const CHRatingDif & aRatingDif=(const CHRatingDif&) copy;

		m_code			= aRatingDif.m_code;
		m_difference    = aRatingDif.m_difference;
		m_probability	= aRatingDif.m_probability;
	}
	return *this;
}

bool CHRatingDif::operator == (const GData & copy)
{
	if (this == &copy)
		return true;

	const CHRatingDif & aRatingDif=(const CHRatingDif&) copy;

	return ( m_code			== aRatingDif.m_code		&&
			 m_difference	== aRatingDif.m_difference	&&
			 m_probability	== aRatingDif.m_probability);
}

bool CHRatingDif::operator != (const GData & copy)
{
	return !operator==(copy);
}

//////////////////////////////////////////////////////////////////////
// SQL Method
//////////////////////////////////////////////////////////////////////


QBase* CHRatingDif::onQ() const
{
	return new QCHRatingDif();
}

UBase* CHRatingDif::onU() const
{
	return new UCHRatingDif();
}


//////////////////////////////////////////////////////////////////////
// Key Method
//////////////////////////////////////////////////////////////////////

void CHRatingDif::setKey()
{
	char tmp[4];
	sprintf_s(tmp,"%.3d",m_code);
	key=tmp;
}

//////////////////////////////////////////////////////////////////////
// Set Methods
//////////////////////////////////////////////////////////////////////

void CHRatingDif::setCode(const short value)
{
	m_code = value;
	setKey();
}

void CHRatingDif::setDifference(const short value)
{
	m_difference = value;
}

void CHRatingDif::setProbability(const short value)
{
	m_probability = value;
}

//////////////////////////////////////////////////////////////////////
// Get Methods
//////////////////////////////////////////////////////////////////////
short CHRatingDif::getCode() const
{ 
	return m_code; 
}

short CHRatingDif::getDifference() const
{
	return m_difference;
}

short CHRatingDif::getProbability() const
{
	return m_probability;
}
//////////////////////////////////////////////////////////////////////
// Help Methods
//////////////////////////////////////////////////////////////////////
float CHRatingDif::getProbabilityCode(bool positive/*=true*/)
{
	if(positive) 
		 return float(float(getProbability())/float(100));
	else return float(float(100-getProbability())/float(100));

}
MSLString CHRatingDif::getProbabilityCodeStr()
{
	GScore pointsSPos = GScore(getProbabilityCode(true));
	GScore pointsSNeg = GScore(getProbabilityCode(false));
	
	MSLString a=pointsSPos.asString("#.##")+" / "+pointsSNeg.asString("#.##");
	return a;
}

//////////////////////////////////////////////////////////////////////
// Packing Methods
//////////////////////////////////////////////////////////////////////

MSLPack & CHRatingDif::pack(MSLPack & aPack) const
{	
	aPack << m_code;
	aPack << m_difference;
	aPack << m_probability;

	return aPack;
}

MSLPack & CHRatingDif::unpack(MSLPack & aPack)
{
		
	aPack >> m_code;
	aPack >> m_difference;
	aPack >> m_probability;

	return aPack;
}



