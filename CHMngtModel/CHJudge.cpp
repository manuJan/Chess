/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHJudge.cpp                                                                 
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
#include "CHJudge.h"
#include "CHClassIds.h"
#include "UCHJudge.h"
#include <core/G/GBuffer.h>

RWDEFINE_COLLECTABLE(CHJudge, __CHJUDGE)

inline
void CHJudge::setKey()
{
	if( getRegister() )
		key = getRegister()->getKey();

	if( getFunction() )
		key += getFunction()->getKey();
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHJudge::CHJudge()
:GJudge()
{
}

CHJudge::CHJudge(GRegister* pRegister,GFunction * pFunction)
:GJudge()
{
	setRegister(pRegister);
	setFunction(pFunction);
	setKey();
}

CHJudge::CHJudge(GRegister* pRegister)
:GJudge()
{
	setRegister(pRegister);
	setFunction(NULL);
}

CHJudge::CHJudge(const CHJudge & copy)
:GJudge(copy)
{
	operator=(copy);
}

CHJudge::CHJudge(CPack& aPack)
{
	unpack(aPack);
}

CHJudge::~CHJudge()
{
}

//////////////////////////////////////////////////////////////////////
// Operators
//////////////////////////////////////////////////////////////////////
CHJudge & CHJudge::operator =(const CHJudge & copy)
{
	if (this != &copy)
	{
		GJudge::operator =(copy);
		setKey();
	}
	return * this;
}

RWBoolean CHJudge::operator ==(const CHJudge & copy)
{
	if (this == &copy)
		return true;
	else
		return (GJudge::operator ==(copy));
}

RWBoolean CHJudge::operator !=(const CHJudge & copy)
{
	return !operator==(copy);
}


//////////////////////////////////////////////////////////////////////
// From GData
//////////////////////////////////////////////////////////////////////
RWBoolean CHJudge::uSQL(RWDBConnection& pConnect,RWBoolean remove /*=false*/ )
{
	RWBoolean rc=false;

	UCHJudge upd(&pConnect);

	if( remove )  rc=upd.remove(*this);
	else          rc=upd.set   (*this);

	return rc;
}

CPack& CHJudge::pack(CPack& aPack)
{
	GJudge::pack(aPack);
	
	return aPack;
}

CPack& CHJudge::unpack(CPack& aPack)
{
	GJudge::unpack(aPack);
		
	setKey();

	return aPack;
}

RWCString CHJudge::msl() const
{
	RWCString str = GJudge::msl();

	GBuffer aBuffer;

	return str +  RWCString (aBuffer	<< endLine
									 );
}

RWCString CHJudge::mslDescription(const char *language) const
{
	return GJudge::mslDescription(language);
}


//////////////////////////////////////////////////////////////////////
// Sets
//////////////////////////////////////////////////////////////////////

void CHJudge::setFunction(GFunction *value)
{
	GJudge::setFunction(value);
	setKey();
}

//////////////////////////////////////////////////////////////////////
// Gets
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//From GFunction
//////////////////////////////////////////////////////////////////////
const char CHJudge::getFunctionCode() const
{
	return getFunction()->getFunction();
}


//////////////////////////////////////////////////////////////////////
// From GRegister
//////////////////////////////////////////////////////////////////////
RWWString CHJudge::getGroupLDescription(const char *language)
{
	if(getRegister())
		return getRegister()->getGroupLDescription(language);

	return NULLRWWSTRING;
}
GRegister::TypeRegister CHJudge::getType()
{
	if(getRegister())
		return getRegister()->getType();

	return GRegister::individual;
}

