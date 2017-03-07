/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHSplitMatch.cpp                                                                 
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
#include "CHSplitMatch.h"
#include "CHClassIds.h"
#include "UCHSplitMatch.h"
#include <core/G/GBuffer.h>

RWDEFINE_COLLECTABLE(CHSplitMatch, __CHSPLITMATCH)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHSplitMatch::CHSplitMatch()
:GTHSplitMatch()
{

}

CHSplitMatch::CHSplitMatch(const CHSplitMatch & copy)
{
	operator=(copy);
}

CHSplitMatch::CHSplitMatch(CPack& aPack)
{
	unpack(aPack);
}

CHSplitMatch::~CHSplitMatch()
{
}


//////////////////////////////////////////////////////////////////////
// Operators
//////////////////////////////////////////////////////////////////////
CHSplitMatch & CHSplitMatch::operator =(const CHSplitMatch & copy)
{
	if (this != &copy)
	{
		GTHSplitMatch::operator =(copy);

	}
	return * this;
}

RWBoolean CHSplitMatch::operator ==(const CHSplitMatch & copy)
{
	if (this == &copy)
		return true;
	else
		return (GTHSplitMatch::operator ==(copy));
}

RWBoolean CHSplitMatch::operator !=(const CHSplitMatch & copy)
{
	return !operator==(copy);
}


//////////////////////////////////////////////////////////////////////
// From GData
//////////////////////////////////////////////////////////////////////
RWBoolean CHSplitMatch::uSQL(RWDBConnection& pConnect,RWBoolean remove /*=false*/ )
{
	RWBoolean rc=false;

	UCHSplitMatch upd(&pConnect);

	if( remove )  rc=upd.remove(*this);
	else          rc=upd.set   (*this);

	return rc;
}

CPack& CHSplitMatch::pack(CPack& aPack)
{
	GTHSplitMatch::pack(aPack);
		
	return aPack;
}

CPack& CHSplitMatch::unpack(CPack& aPack)
{
	GTHSplitMatch::unpack(aPack);
	
	return aPack;
}

RWCString CHSplitMatch::msl() const
{
	RWCString str = GTHSplitMatch::msl();

	GBuffer aBuffer;

	return str +  RWCString (aBuffer 	<< endLine
		);
}

RWCString CHSplitMatch::mslDescription(const char *language) const
{
	return GTHSplitMatch::mslDescription(language);
}


//////////////////////////////////////////////////////////////////////
// Sets
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Gets
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Help Methods
//////////////////////////////////////////////////////////////////////

