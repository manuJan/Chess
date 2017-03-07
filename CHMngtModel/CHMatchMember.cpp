/*************************************************************************************
*	© Copyright MSL Software, S.L., 2001
*
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior wriCHen permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHMatchMember.cpp
*	Description	:Chess Match-Member
*
*	Author		:Chess Team
*	Date created:13-12-2005
* 	Project		:CH Model
*
***************************************************************************************/

#include "stdCHMngt.h"
#include "CHMatchMember.h"
#include "CHClassIDs.h"
#include "UCHMatchMember.h"
#include <CORE/G/GBuffer.h>
#include "CHRegister.h"
#include "CHMatchResult.h"

RWDEFINE_COLLECTABLE(CHMatchMember, __CHMATCHMEMBER);

CHMatchMember::CHMatchMember()
:GTHMatchMember()
{}

CHMatchMember::CHMatchMember(const CHMatchMember &copy)
{
	operator=(copy);
}

CHMatchMember::CHMatchMember(CPack &aPack)
{	
	unpack(aPack); 
}

CHMatchMember::~CHMatchMember()
{}

CHMatchMember &CHMatchMember::operator = (const CHMatchMember &copy)
{
	if ( this != &copy )
	{
		GTHMatchMember::operator = (copy);
	}
	return *this;
}

RWBoolean CHMatchMember::operator == (const CHMatchMember &copy)
{
	if ( this == &copy )
		return true;

	if( GTHMatchMember::operator	== (copy) )
	{
		return true;
	}

	return false;
}

RWBoolean CHMatchMember::operator != (const CHMatchMember &copy)
{
	return !operator==(copy);
}

RWBoolean CHMatchMember::uSQL(RWDBConnection& pConnect,RWBoolean remove/*=false*/)
{
	RWBoolean rc=false;

	UCHMatchMember upd(&pConnect);
	if(remove )
		rc=upd.remove(*this);
	else
		rc=upd.set(*this);
	
	return rc;
}

RWCString CHMatchMember::msl() const
{
	if (!getMatchResult())
		return "";

	CHMatch *pMatch=(CHMatch*)getMatchResult()->getMatch();
	if (!pMatch)
		return "";

	RWCString str=GTHMatchMember::msl();
	GBuffer aBuffer;
	if(str==NULLRWSTRING)
		return str;

	return  str + RWCString(aBuffer << pMatch->getSubMatch()
									<< endLine);
}

RWCString CHMatchMember::mslDescription(const char *language) const
{
	return  GTHMatchMember::mslDescription(language);
}

CPack& CHMatchMember::pack(CPack & aPack)
{
	GTHMatchMember::pack (aPack);

	return aPack;
}

CPack& CHMatchMember::unpack(CPack &aPack)
{
	GTHMatchMember::unpack (aPack);
	
	return aPack;
}

GSortedVector &CHMatchMember::getMembersVector() const
{
	return (GSortedVector &)(getMatchResult()->getInscription()->getMembersVector());
}

RWCString CHMatchMember::getMemberKey() const
{
	return getMember()?getMember()->getKey():"";
}
