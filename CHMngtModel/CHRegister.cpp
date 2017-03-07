/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : LRegister.cpp
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
#include "CHRegister.h"
#include "CHClassIds.h"
#include "UCHRegister.h"
#include "CHMasterType.h"
#include "CHMemoryDataBase.h"

#include <CORE/G/GBuffer.h>
#include <CORE/G/GClassIDs.h>
RWDEFINE_COLLECTABLE(CHRegister, __CHREGISTER);
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHRegister::CHRegister()
:GRegister()
,masterType(0)
{
}

CHRegister::CHRegister(const GRegister &copy)
:GRegister(copy)
,masterType(0)
{
}

CHRegister::CHRegister(const CHRegister &copy)
{
	operator=(copy);
}

CHRegister::CHRegister(CPack &iPack)
{
	unpack(iPack);
}

CHRegister::~CHRegister()
{
}
//operator
GRegister& CHRegister::operator =(const GRegister& copy)
{
	CHRegister& aCopy=(CHRegister&)copy;
	UNREFERENCED_PARAMETER(aCopy);
	if ( this != &copy )
	{
		GRegister::operator = (copy);
		masterType=aCopy.masterType;
	}	
	return *this;
}

RWBoolean CHRegister::operator ==(const GRegister& copy)
{
	CHRegister& aCopy=(CHRegister&)copy;
	UNREFERENCED_PARAMETER(aCopy);
	if ( this == &copy )
		return true;

	if( GRegister::operator ==(copy) )
	{
		return masterType==aCopy.masterType;
	}

	return false;
}

RWBoolean CHRegister::operator !=(const GRegister& copy)
{
	return !operator==(copy);
}

RWBoolean CHRegister::uSQL(RWDBConnection& pConnect,RWBoolean remove/*=false*/)
{
	RWBoolean rc=false;
	UCHRegister upd(&pConnect);
	if(remove )
		rc=upd.remove(*this);
	else
		rc=upd.set(*this);
	return rc;
}

RWCString CHRegister::msl() const
{
	RWCString str = GRegister::msl();
	if(!str.length() || str == NULLRWSTRING)
		return NULLRWSTRING;

	GBuffer aBuffer;
	aBuffer << str;
	aBuffer.Trim(); //quita el endLine del buffer
	return aBuffer  << masterType
					<< endLine;
}
//pack
CPack& CHRegister::pack(CPack & aPack)
{
	GRegister::pack (aPack);

	aPack << masterType;
	return aPack;
}

CPack& CHRegister::unpack(CPack &aPack)
{
	GRegister::unpack (aPack);

	aPack >> masterType;
	return aPack;
}
// set
void CHRegister::setMasterType(const short value)
{
	masterType = value;
}
// get
short CHRegister::getMasterType() const
{
	return masterType;
}

RWCString CHRegister::getMasterTypeAsString(bool longer/*=true*/) const
{
	CHMasterType *pMast=(CHMasterType *)CHMemoryDataBase::findMasterType(masterType);
	if (pMast && pMast->getMasterType()>0)
		return longer?pMast->getLDescription().toMultiByte():pMast->getSDescription().toMultiByte();
	return NULLRWSTRING;
}

short CHRegister::getMasterTypeOrder() const
{
	CHMasterType *pMast=(CHMasterType *)CHMemoryDataBase::findMasterType(masterType);
	return (pMast?pMast->getOrder():0);
}