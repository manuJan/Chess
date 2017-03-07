/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHMatchJudge.cpp                                                                 
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:13-12-2005
*   Project     :CH Model
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///


#include "stdCHMngt.h"
#include "CHMatchJudge.h"
#include "CHClassIds.h"
#include "UCHMatchJudge.h"
#include "CHJudge.h"
#include "CHMatch.h"

#include <core/G/GBuffer.h>

RWDEFINE_COLLECTABLE(CHMatchJudge, __CHMATCHJUDGE)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHMatchJudge::CHMatchJudge()
:GTHMatchJudge()
{
}

CHMatchJudge::CHMatchJudge(GTHMatch * pMatch,CHJudge *pJudge)
:GTHMatchJudge()
{
	setMatch(pMatch) ;
	setFunction(pJudge->getFunction()) ;
	setRegister(pJudge->getRegister()) ;
	setPosition(0);
	setKey();
}

CHMatchJudge::CHMatchJudge(const CHMatchJudge & copy)
{
	operator=(copy);
}

CHMatchJudge::CHMatchJudge(CPack& aPack)
{
	unpack(aPack);
}

CHMatchJudge::~CHMatchJudge()
{
}

//////////////////////////////////////////////////////////////////////
// Operators
//////////////////////////////////////////////////////////////////////
CHMatchJudge & CHMatchJudge::operator =(const CHMatchJudge & copy)
{
	if (this != &copy)
	{
		GTHMatchJudge::operator =(copy);

		
	}
	return * this;
}

RWBoolean CHMatchJudge::operator ==(const CHMatchJudge & copy)
{
	if (this == &copy)
		return true;
	else
		return (GTHMatchJudge::operator ==(copy));
}

RWBoolean CHMatchJudge::operator !=(const CHMatchJudge & copy)
{
	return !operator==(copy);
}


//////////////////////////////////////////////////////////////////////
// From GData
//////////////////////////////////////////////////////////////////////
RWBoolean CHMatchJudge::uSQL(RWDBConnection& pConnect,RWBoolean remove /*=false*/ )
{
	RWBoolean rc=false;

	UCHMatchJudge upd(&pConnect);

	if( remove )  rc=upd.remove(*this);
	else          rc=upd.set   (*this);

	return rc;
}

CPack& CHMatchJudge::pack(CPack& aPack)
{
	GTHMatchJudge::pack(aPack);
	
	return aPack;
}

CPack& CHMatchJudge::unpack(CPack& aPack)
{
	GTHMatchJudge::unpack(aPack);
		
	return aPack;
}


RWCString CHMatchJudge::msl() const
{
	RWCString str = GTHMatchJudge::msl();

	GBuffer aBuffer;

	return str +  RWCString (aBuffer 	<< endLine);
}

RWCString CHMatchJudge::mslDescription(const char *language) const
{
	return GTHMatchJudge::mslDescription(language);
}


//////////////////////////////////////////////////////////////////////
// Sets
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Gets
//////////////////////////////////////////////////////////////////////
short CHMatchJudge::getFunctionShort()
{
	short car=char((getFunction()->getFunction()-1)-'A');
	return car;
}