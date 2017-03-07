/*************************************************************************************
*			© Copyright MSL Software, S.L., 2001
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHSession.cpp
*	Description	:
*
*   Author      :Chess Team
*   Date created:12-12-2005
*   Project     :CH Model
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdCHMngt.h"
#include "CHClassIDs.h"
#include "CHSession.h"

#include "UCHSession.h"


RWDEFINE_COLLECTABLE(CHSession, __CHSESSION)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHSession::CHSession()
:GTHSession()
,description(NULLRWSTRING)
,acumulatSess(0)
,status(0)
{ 
}

CHSession::CHSession(const CHSession &copy)
{ 
	operator = (copy); 
}

CHSession::CHSession(CPack &iPack)
{ 
	unpack(iPack); 
}

CHSession::~CHSession()
{
}


//////////////////////////////////////////////////////////////////////
// Operators
//////////////////////////////////////////////////////////////////////
CHSession &CHSession::operator = (const CHSession &copy)
{
	if( this!=&copy )
	{
		GTHSession::operator = (copy);
		description		= copy.description;
		acumulatSess	= copy.acumulatSess;
		status			= copy.status;
	}

	return *this;
}

RWBoolean CHSession::operator == (const CHSession &copy)
{
	if( this==&copy )
		return true;

	return ( GTHSession::operator ==(copy)			&&
			 description    == copy.description		&&
			 acumulatSess	== copy.acumulatSess	&&
			 status			== copy.status		   );
}

RWBoolean CHSession::operator != (const CHSession &copy)
{
	return !operator == (copy);
}


//////////////////////////////////////////////////////////////////////
// From GData
//////////////////////////////////////////////////////////////////////
RWCString CHSession::msl() const
{
	RWCString str = GTHSession::msl();
	if(!str.length() || str == NULLRWSTRING)
		return NULLRWSTRING;

	GBuffer aBuffer;
	aBuffer << str;
	aBuffer.Trim();	//quita el endLine del buffer,q lo mete la GTHSession.

	return aBuffer	<< description
					<< acumulatSess
					<< status
					<< endLine;
}

RWBoolean CHSession::uSQL(RWDBConnection& pConnect,RWBoolean remove/*=false*/)
{
	RWBoolean rc=false;

	UCHSession upd(&pConnect);
	if(remove )
		rc=upd.remove(*this);
	else
		rc=upd.set(*this);
	
	return rc;
}

CPack& CHSession::pack(CPack & aPack)
{
	GTHSession::pack (aPack);

	aPack << description;
	aPack << acumulatSess;
	aPack << status;
	
	return aPack;
}

CPack& CHSession::unpack(CPack &aPack)
{
	GTHSession::unpack (aPack);

	aPack >> description;
	aPack >> acumulatSess;
	aPack >> status;
	
	return aPack;
}


//////////////////////////////////////////////////////////////////////
// Sets
//////////////////////////////////////////////////////////////////////
void CHSession::setDescription(const RWCString value)
{ 
	description = value;	
}

void CHSession::setAcumulatSess(const short value)
{ 
	acumulatSess=value;	
}
void CHSession::setStatus(const unsigned char value)
{
	status=value; 
}


//////////////////////////////////////////////////////////////////////
// Gets
//////////////////////////////////////////////////////////////////////
RWCString CHSession::getDescription() const
{ 
	return description;	
}

short CHSession::getAcumulatSess() const
{ 
	return acumulatSess;	
}
unsigned char CHSession::getStatus() const
{
	return status; 
}

RWWString CHSession::getStatusSDescription(const char *language/*=DBApplication::getAppLanguage()*/) const
{
	GStatus * pStatus= GTHMemoryDataBase::findStatus(status);
	return pStatus ? pStatus->getSDescription(language):_T("");

}

RWWString CHSession::getStatusLDescription(const char *language/*=DBApplication::getAppLanguage()*/) const
{
	GStatus * pStatus= GTHMemoryDataBase::findStatus(status);
	return pStatus ? pStatus->getLDescription(language):_T("");
}