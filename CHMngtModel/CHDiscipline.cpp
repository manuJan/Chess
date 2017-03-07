/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be consideHome liable for any mistake or omission in the edition of    
*   this document. MSL is a registeHome trademark.                                      
*                                                                                      
*   File name   : CHDiscipline.cpp                                                                 
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:05-12-2005
*   Project     :CH Model
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///

#include "stdCHMngt.h"
#include "CHDiscipline.h"
#include "CHClassIds.h"
#include "UCHDiscipline.h"
//#include "CHMemoryDataBase.h"
#include <Core\G\GMemoryDataBase.h>
#include <core/G/GScore.h>

RWDEFINE_COLLECTABLE(CHDiscipline,__CHDISCIPLINE)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHDiscipline::CHDiscipline()
:GTHDiscipline()
,autoProg(false)
{
}

CHDiscipline::CHDiscipline(const CHDiscipline & copy)
:GTHDiscipline(copy)
{
	operator=(copy);
}

CHDiscipline::CHDiscipline(CPack& aPack)
{
	unpack(aPack);
}

CHDiscipline::~CHDiscipline()
{
}
//////////////////////////////////////////////////////////////////////
// Operators
//////////////////////////////////////////////////////////////////////
CHDiscipline & CHDiscipline::operator =(const CHDiscipline & copy)
{
	if (this != &copy)
	{
		GTHDiscipline::operator =(copy);
		autoProg = copy.autoProg;
	}
	return * this;
}

RWBoolean CHDiscipline::operator==(const CHDiscipline & copy)
{
	if (this == &copy)
		return true;
	
	if( GTHDiscipline::operator == (copy)		    &&
		autoProg		 == copy.autoProg			)
	{
		return true;
	}

	return false;
}

RWBoolean CHDiscipline::operator !=(const CHDiscipline & copy)
{
	return !operator==(copy);
}
//////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////
RWBoolean CHDiscipline::uSQL(RWDBConnection & pConnect,RWBoolean remove/*=false*/)
{
	UCHDiscipline u(&pConnect);
	if( remove )
		return u.remove(*this);
	return u.set(*this);
}

RWCString CHDiscipline::msl() const
{
	RWCString str = GTHDiscipline::msl();
	if( str == NULLRWSTRING || !str.length() )
		return NULLRWSTRING;

	GBuffer aBuffer;
	aBuffer << str;
	aBuffer.Trim();
	aBuffer << endLine;

	return  aBuffer;
}

RWCString CHDiscipline::mslDescription(const char *language) const
{
	return GTHDiscipline::mslDescription(language);
}

CPack & CHDiscipline::pack(CPack & aPack)
{
	GTHDiscipline::pack(aPack);

	aPack << autoProg;

	return aPack;
}

CPack & CHDiscipline::unpack(CPack & aPack)
{
	GTHDiscipline::unpack(aPack);

	aPack >> autoProg;
	
	return aPack;
}

//sets
void CHDiscipline::setAutoProg(RWBoolean value)
{
	autoProg = value;
}

//gets
RWBoolean CHDiscipline::getAutoProg()
{
	return autoProg;
}

//Venue methods
GVenue *CHDiscipline::getVenue() const
{
	RWSetIterator it(CHMemoryDataBase::getColVenues());

	GVenue * pVenue=0;
	while ((pVenue = (GVenue *)it()) != 0)
	{
		if(pVenue)
			break;
	}
	return pVenue;	
}

RWCString CHDiscipline::getVenueCode() const
{
	GVenue * pVenue=getVenue();
	if (pVenue)
		return pVenue->getVenue();

	return NULLRWSTRING;
}

RWWString CHDiscipline::getVenueSDescription(const char *language/*=DBApplication::getAppLanguage()*/) const
{
	GVenue *pVenue=getVenue();
	if (pVenue)
		return pVenue->getSDescription(language);

	return NULLRWWSTRING;
}

RWWString CHDiscipline::getVenueLDescription(const char *language/*=DBApplication::getAppLanguage()*/) const
{
	GVenue * pVenue=getVenue();
	if (pVenue)
		return pVenue->getLDescription(language);

	return NULLRWWSTRING;
}

