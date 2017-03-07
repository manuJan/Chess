/*************************************************************************************
*	© Copyright MSL Software, S.L., 2001
*
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHCourt.CPP
*	Description	:
*
*	Author		:Chess Team
*	Date created:12-12-2005
* 	Project		:CH Model
*
*
***************************************************************************************/

#include "stdCHMngt.h"
#include "CHCourt.h"
#include "UCHCourt.h"
#include "CHClassIDs.h"

RWDEFINE_COLLECTABLE(CHCourt, __CHCOURT);

//////////////////////////////////////////////////////////////////////
// Constructors/Destructor
//////////////////////////////////////////////////////////////////////
CHCourt::CHCourt()
:GCourt()
,order(0)
{
}
	
CHCourt::CHCourt(const CHCourt &copy)
:GCourt()
{
	operator=(copy);
}

CHCourt::CHCourt(CPack &iPack)
:GCourt()
{
	unpack(iPack);
}

CHCourt::~CHCourt()
{

}

//////////////////////////////////////////////////////////////////////
// Overloaded Operators
//////////////////////////////////////////////////////////////////////

CHCourt & CHCourt::operator=(const CHCourt & copy)
{
	if ( this != &copy )
	{
		GCourt::operator = (copy);
		order		 = copy.order;
	}	
	return *this;
}

RWBoolean CHCourt::operator==(const CHCourt & copy)
{
	if ( this == &copy )
		return true;

	if( GCourt::operator == (copy)		   &&
		order		 == copy.order )
	{
		return true;
	}

	return false;
}


RWBoolean CHCourt::operator!=(const CHCourt & copy)
{
	return !operator==(copy);
}

//////////////////////////////////////////////////////////////////////
//From GData
//////////////////////////////////////////////////////////////////////

RWBoolean CHCourt::uSQL(RWDBConnection& pConnect,RWBoolean remove/*=false*/)
{
	UCHCourt upd(&pConnect);
	if( remove )
		return upd.remove(*this);
	return upd.set(*this);	
}

RWCString CHCourt::msl() const
{
	RWCString str = GCourt::msl();
	if( !str.length() || str == NULLRWSTRING )
		return NULLRWSTRING;

	GBuffer aBuffer;
	return str + RWCString(aBuffer << order
								   << endLine);
}

RWCString CHCourt::mslDescription(const char *language) const
{
	return GCourt::mslDescription(language);
}

//////////////////////////////////////////////////////////////////////
//SETS
//////////////////////////////////////////////////////////////////////

void CHCourt::setOrder(const short value)
{ 
	order = value; 
}

//////////////////////////////////////////////////////////////////////
//GETS
//////////////////////////////////////////////////////////////////////

short CHCourt::getOrder() const
{ 
	return order; 
}

//////////////////////////////////////////////////////////////////////
// Packing Methods
//////////////////////////////////////////////////////////////////////

CPack& CHCourt::pack(CPack & aPack)
{
	GCourt::pack (aPack);

	aPack << order;
	
	return aPack;
}


CPack& CHCourt::unpack(CPack &aPack)
{
	GCourt::unpack (aPack);
	
	aPack >> order;
	
	return aPack;
}
