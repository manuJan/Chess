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
#include "UCHRatingDif.h"
#include "CHClassIDs.h"
#include <core/G/GScore.h>

RWDEFINE_COLLECTABLE(CHRatingDif,__CHRATINGDIF)

/////////////////////////////////////////////////////////////////////
// Constructors & Destructor
//////////////////////////////////////////////////////////////////////

CHRatingDif::CHRatingDif()
:GData()
,code(0)
,difference(0)
,probability(0)
{

}
CHRatingDif::CHRatingDif(const short id)
:GData()
,code(id)
,difference()
,probability(0)
{
	setKey();
}

CHRatingDif::CHRatingDif(const CHRatingDif & copy)
{
	copyRatingDif(copy);
	setKey();
}

CHRatingDif::CHRatingDif(CPack & aPack)
{
	unpack(aPack);
	setKey();
}

CHRatingDif::~CHRatingDif()
{
	
}

//////////////////////////////////////////////////////////////////////
// Overloaded Operators
//////////////////////////////////////////////////////////////////////

CHRatingDif & CHRatingDif::operator = (const CHRatingDif & copy)
{
	copyRatingDif(copy);
	return *this;
}

RWBoolean CHRatingDif::operator == (const CHRatingDif & copy)
{
	return compareRatingDif(copy);
}

RWBoolean CHRatingDif::operator != (const CHRatingDif & copy)
{
	return !compareRatingDif(copy);
}
void CHRatingDif::copyRatingDif(const CHRatingDif & copy)
{
	if( this == &copy )
		return;

	difference	= copy.difference;
	probability = copy.probability;
	
}

RWBoolean CHRatingDif::compareRatingDif(const CHRatingDif & copy)
{
	if( this == &copy )
		return true;

	if( code		!= copy.code		   ||
		difference	!= copy.difference     ||
		probability != copy.probability )
		return false;

	return true;
}
//////////////////////////////////////////////////////////////////////
// SQL Method
//////////////////////////////////////////////////////////////////////

RWBoolean CHRatingDif::uSQL(RWDBConnection & pConnect,RWBoolean remove/*=false*/)
{
	UCHRatingDif upd(&pConnect);
	return remove ? upd.remove(*this) : upd.set(*this);
}
//////////////////////////////////////////////////////////////////////
// Outputs Methods
//////////////////////////////////////////////////////////////////////

RWCString CHRatingDif::msl() const
{
	GBuffer aBuffer;
	
	char strCode[4];
	sprintf(strCode,"%.3d",code);

	return aBuffer << isA()
				   << getKey()
				   << strCode
				   << difference
				   << probability
				   << endLine;
}

//////////////////////////////////////////////////////////////////////
// Key Method
//////////////////////////////////////////////////////////////////////

void CHRatingDif::setKey()
{
	char tmp[4];
	sprintf(tmp,"%.3d",code);
	key=tmp;
}

//////////////////////////////////////////////////////////////////////
// Set Methods
//////////////////////////////////////////////////////////////////////

void CHRatingDif::setCode(const short value)
{
	code = value;
	setKey();
}

void CHRatingDif::setDifference(const short value)
{
	difference = value;
}
void CHRatingDif::setProbability(const short value)
{
	probability = value;
}

//////////////////////////////////////////////////////////////////////
// Get Methods
//////////////////////////////////////////////////////////////////////
short CHRatingDif::getCode() const
{ 
	return code; 
}

short CHRatingDif::getDifference() const
{
	return difference;
}

short CHRatingDif::getProbability() const
{
	return probability;
}
//////////////////////////////////////////////////////////////////////
// Help Methods
//////////////////////////////////////////////////////////////////////
float CHRatingDif::getProbabilityCode(RWBoolean positive/*=true*/)
{
	if(positive) 
		 return float(float(getProbability())/float(100));
	else return float(float(100-getProbability())/float(100));

}
RWCString CHRatingDif::getProbabilityCodeStr()
{
	GScore pointsSPos = GScore(getProbabilityCode(true));
	GScore pointsSNeg = GScore(getProbabilityCode(false));
	
	RWCString a=pointsSPos.asString("#.##")+" / "+pointsSNeg.asString("#.##");
	return a;
}

//////////////////////////////////////////////////////////////////////
// Packing Methods
//////////////////////////////////////////////////////////////////////

CPack & CHRatingDif::pack(CPack & aPack)
{
	
	aPack << code;
	aPack << difference;
	aPack << probability;

	return aPack;
}

CPack & CHRatingDif::unpack(CPack & aPack)
{
		
	aPack >> code;
	aPack >> difference;
	aPack >> probability;

	return aPack;
}



