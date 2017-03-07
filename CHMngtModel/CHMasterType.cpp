/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHMasterType.cpp
*	Description	:
*
*	Author		:CH Team
*	Date created:09-12-2005
* 	Project		:Chess Management Model DLL
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdCHMngt.h"
#include "CHMasterType.h"
#include "UCHMasterType.h"
#include "CHClassIDs.h"

RWDEFINE_COLLECTABLE(CHMasterType,__CHMASTERTYPE)

/////////////////////////////////////////////////////////////////////
// Constructors & Destructor
//////////////////////////////////////////////////////////////////////

CHMasterType::CHMasterType()
:GData()
,masterType(0)
,order(0)
,masterTypeNames()
{

}
CHMasterType::CHMasterType(const short id,GNames aNames)
:GData()
,masterType(id)
,order(0)
,masterTypeNames()
{
	setDescription(aNames);
	setKey();
}

CHMasterType::CHMasterType(const CHMasterType & copy)
{
	copyMasterType(copy);
	setKey();
}

CHMasterType::CHMasterType(CPack & aPack)
{
	unpack(aPack);
	setKey();
}

CHMasterType::~CHMasterType()
{
	masterTypeNames.clearAndDestroy();
}

//////////////////////////////////////////////////////////////////////
// Overloaded Operators
//////////////////////////////////////////////////////////////////////

CHMasterType & CHMasterType::operator = (const CHMasterType & copy)
{
	copyMasterType(copy);
	return *this;
}

RWBoolean CHMasterType::operator == (const CHMasterType & copy)
{
	return compareMasterType(copy);
}

RWBoolean CHMasterType::operator != (const CHMasterType & copy)
{
	return !compareMasterType(copy);
}
void CHMasterType::copyMasterType(const CHMasterType & copy)
{
	if( this == &copy )
		return;

	masterType = copy.masterType;

	GNames * pNames = 0;
	masterTypeNames.clearAndDestroy();
	RWSetIterator it((RWSet &)copy.masterTypeNames);
	while( (pNames=(GNames *)it())!=0 )
		masterTypeNames.insert( new GNames(*pNames) );
}

RWBoolean CHMasterType::compareMasterType(const CHMasterType & copy)
{
	if( this == &copy )
		return true;

	if( masterType	!= copy.masterType     ||
		order		!= copy.order		   ||
        masterTypeNames != copy.masterTypeNames )
		return false;

	return true;
}
//////////////////////////////////////////////////////////////////////
// SQL Method
//////////////////////////////////////////////////////////////////////

RWBoolean CHMasterType::uSQL(RWDBConnection & pConnect,RWBoolean remove/*=false*/)
{
	UCHMasterType upd(&pConnect);
	return remove ? upd.remove(*this) : upd.set(*this);
}
//////////////////////////////////////////////////////////////////////
// Outputs Methods
//////////////////////////////////////////////////////////////////////

RWCString CHMasterType::msl() const
{
	GBuffer aBuffer;
	
	char strMasterType[4];
	sprintf(strMasterType,"%.3d",masterType);

	return aBuffer << isA()
				   << getKey()
				   << strMasterType
				   << order
				   << endLine;
}

//////////////////////////////////////////////////////////////////////
// Key Method
//////////////////////////////////////////////////////////////////////

void CHMasterType::setKey()
{
	char tmp[4];
	sprintf(tmp,"%.3d",masterType);
	key=tmp;
}

//////////////////////////////////////////////////////////////////////
// Set Methods
//////////////////////////////////////////////////////////////////////

void CHMasterType::setMasterType(const short value)
{
	masterType = value;
	setKey();
}

void CHMasterType::setOrder(const short value)
{
	order = value;
}

void CHMasterType::setDescription(const GNames & description)
{
	GNames * pNames = (GNames *)masterTypeNames.find(&description);
	if( pNames ) 
		*pNames=description;
	else 
		masterTypeNames.insert(new GNames(description));
}

//////////////////////////////////////////////////////////////////////
// Get Methods
//////////////////////////////////////////////////////////////////////
short CHMasterType::getMasterType() const
{ 
	return masterType; 
}

short CHMasterType::getOrder() const
{
	return order;
}

RWSet & CHMasterType::getNames()
{
	return masterTypeNames; 
}

RWWString CHMasterType::getSDescription(const char * language/*=DBApplication::getAppLanguage()*/) const
{
	GNames find;
	find.setCode(language);

	GNames * pNames = (GNames *)masterTypeNames.find(&find);
	if( !pNames ) 
		return NULLRWWSTRING;

	return pNames->getSName();
}

RWWString CHMasterType::getLDescription(const char * language/*=DBApplication::getAppLanguage()*/) const
{
	GNames find;
	find.setCode(language);

	GNames * pNames = (GNames *)masterTypeNames.find(&find);
	if( !pNames )
		return NULLRWWSTRING;

	return pNames->getLName();
}

//////////////////////////////////////////////////////////////////////
// Packing Methods
//////////////////////////////////////////////////////////////////////

CPack & CHMasterType::pack(CPack & aPack)
{
	size_t namesEntries = masterTypeNames.entries();

	aPack << masterType;
	aPack << order;
	aPack << namesEntries;

	GNames * pNames = 0;
	RWSetIterator it(masterTypeNames);
	while( (pNames=(GNames *)it())!=0 )
		pNames->pack(aPack);

	return aPack;
}

CPack & CHMasterType::unpack(CPack & aPack)
{
	size_t namesEntries = 0;
	
	aPack >> masterType;
	aPack >> order;
	aPack >> namesEntries;

	masterTypeNames.clearAndDestroy();
	for(size_t i=0 ; i<namesEntries ; i++)
		masterTypeNames.insert( new GNames(aPack) );

	return aPack;
}



