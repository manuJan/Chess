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
#include "CHClassIDs.h"
#include "UCHMember.h"
#include "CHRegister.h"
#include <Core/G/GFunction.h>

RWDEFINE_COLLECTABLE(CHMember, __CHMEMBER);
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHMember::CHMember()
:GMember(0,0)
,function(eNone)
,rating(0)
,kConst(0)
{
}

CHMember::CHMember(CHRegister* pRegister,CHInscription* pInscription)
:GMember((GRegister*)pRegister,(GInscription*)pInscription)
,function(eNone)
,rating(0)
,kConst(0)
{
}

CHMember::CHMember(const CHMember &copy)
:GMember(0,0)
{
	operator=(copy);
}

CHMember::CHMember(CPack &iPack)
:GMember(0,0)
{
	unpack(iPack);
}

CHMember::~CHMember()
{

}

CHMember &CHMember::operator = (const CHMember &copy)
{
	if ( this != &copy )
	{
		GMember::operator	= (copy);
		function			= copy.function;
		rating				= copy.rating;
		kConst				= copy.kConst;
	}
	return *this;
}

RWBoolean CHMember::operator == (const CHMember &copy)
{
	if ( this == &copy )
		return true;
	else
		return	(GMember::operator	==(copy)			&&
				 function			== copy.function	&&
				 rating				== copy.rating		&&
				 kConst				== copy.kConst);
}

RWBoolean CHMember::operator != (const CHMember &copy)
{
	return !operator==(copy);
}

RWBoolean CHMember::uSQL(RWDBConnection& pConnect,RWBoolean remove/*=false*/)
{
	RWBoolean rc=false;

	UCHMember upd(&pConnect);
	if(remove )
		rc=upd.remove(*this);
	else
		rc=upd.set(*this);
	
	return rc;
}

RWCString CHMember::msl() const
{
	RWCString str = GMember::msl();
	if(!str.length() || str == NULLRWSTRING)
		return NULLRWSTRING;

	GBuffer aBuffer;
	

	aBuffer	<<	function
			<<  rating
			<<	endLine ;

	return str + RWCString(aBuffer);

}

CPack& CHMember::pack(CPack & aPack)
{
	GMember::pack (aPack);

	aPack << function;
	aPack << rating;
	aPack << kConst;

	return aPack;
}

CPack& CHMember::unpack(CPack &aPack)
{
	GMember::unpack (aPack);

	aPack >> function;
	aPack >> rating;
	aPack >> kConst;

	return aPack;
}
//set
void CHMember::setFunction(const short value)
{
	function=value;
}
void CHMember::setRating(const short value)
{
	rating = value;
}
void CHMember::setKConst(const short value)
{
	kConst = value;
}
//get
short CHMember::getFunction() const
{
	return function;
}
short CHMember::getRating() const
{
	return rating;
}
short CHMember::getKConst() const
{
	return kConst;
}

RWCString CHMember::getRatingAsString() const
{ 
	RWCString aux="-";
	char tmp[10];
	
	if (rating)
		aux=itoa(rating,tmp,10);
	return aux; 
}
RWCString CHMember::getKConstAsString() const
{ 
	RWCString aux="-";
	char tmp[10];
	
	if (kConst)
		aux=itoa(kConst,tmp,10);
	return aux; 
}

GFunction *CHMember::getCFunction() const
{
	return (!function?(GFunction *)0:((GFunction *)CHMemoryDataBase::findFunction(char(function))));
}

RWWString CHMember::getFunctionLDescription() const
{
	GFunction *pFunc=(!function?(GFunction *)0:((GFunction *)CHMemoryDataBase::findFunction(char(function))));
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

RWCString CHMember::getRegisterBirthDate(const char *format/*="%x"*/) const
{
	return getRegister()?getRegister()->getBirthDate(format):"";
}