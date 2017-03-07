/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:UCHMasterType.cpp
*	Description	:
*
*	Author		:Chess Team
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

void UCHMasterType::assignAtributes(CHMasterType& aMasterType)
{
	order = aMasterType.getOrder();
	nullorder=true;
	if (order!=0)
		nullorder=false;
}

RWBoolean UCHMasterType::insert(RWDBConnection& aConnection,GData& aData)
{
	CHMasterType& aMasterType=(CHMasterType&)aData;

	RWDBTable masterTypeTable      = DBApplication::getTable("CHT064_MASTER_TYPE");
	RWDBTable masterTypeNamesTable = DBApplication::getTable("CHT564_MASTER_TYPE");

	RWDBInserter inserter = masterTypeTable.inserter();	

	inserter["MASTER_TYPE"] << aMasterType.getMasterType();
	inserter["NORDER"]		<< RWDBBoundExpr(&order,&nullorder);

	RWDBResult aResult = inserter.execute(aConnection);
	aResult.table();

	if( aResult.rowCount()>0L )
	{	
		inserter = masterTypeNamesTable.inserter();

		GNames * pNames = 0;
		RWSetIterator iter(aMasterType.getNames());
		while((pNames=(GNames *)iter())!=0)
		{
			if( pNames )
			{
				inserter["MASTER_TYPE"]		<< aMasterType.getMasterType();
				inserter["IDLANGUAGE"]		<< pNames->getCode();
				inserter["LDESCRIPTION"]    << pNames->getLName();
				inserter["SDESCRIPTION"]    << pNames->getSName();

				aResult = inserter.execute(aConnection);
			}
		}
	}

	aResult.table();
	return aResult.rowCount()>0L;
}

RWBoolean UCHMasterType::update(RWDBConnection& aConnection,GData& aData)
{
	CHMasterType& aMasterType=(CHMasterType&)aData;

	RWDBTable table = DBApplication::getTable("CHT064_MASTER_TYPE");
	RWDBTable masterTypeNamesTable = DBApplication::getTable("CHT564_MASTER_TYPE");

	RWDBUpdater updater = table.updater();	

	assignAtributes(aMasterType);
	updater.where(table["MASTER_TYPE"]   == aMasterType.getMasterType());

	updater << table["NORDER"].assign(RWDBBoundExpr(&order,&nullorder));

	RWDBResult aResult=updater.execute(aConnection);
	aResult.table();

	if (aResult.rowCount()>0L)
	{
		updater = masterTypeNamesTable.updater();
		GNames * pNames = 0;
		RWSetIterator iter(aMasterType.getNames());
		while((pNames=(GNames *)iter())!=0)
		{
			if( pNames )
			{
				updater.where(  masterTypeNamesTable["MASTER_TYPE"]  == aMasterType.getMasterType() &&
								masterTypeNamesTable["IDLANGUAGE"]	 == pNames->getCode() );

				updater << masterTypeNamesTable["LDESCRIPTION"].assign( pNames->getLName() );
				updater << masterTypeNamesTable["SDESCRIPTION"].assign( pNames->getSName() );

				RWDBResult aResult = updater.execute(aConnection);
				aResult.table();				
			}
		}
	}

	return aResult.rowCount()>0L;
}

RWBoolean UCHMasterType::delete_(RWDBConnection& aConnection,GData& aData)
{
	CHMasterType& aMasterType=(CHMasterType&)aData;

	RWDBTable masterTypeTable      = DBApplication::getTable("CHT064_MASTER_TYPE");
	RWDBTable masterTypeNamesTable = DBApplication::getTable("CHT564_MASTER_TYPE");

	RWDBDeleter deleter = masterTypeNamesTable.deleter();
	deleter.where( masterTypeNamesTable["MASTER_TYPE"] == aMasterType.getMasterType() );

	RWDBResult aResult = deleter.execute(aConnection);
	aResult.table();

	if( aResult.rowCount()>0L )
	{
		deleter = masterTypeTable.deleter();
		deleter.where( masterTypeTable["MASTER_TYPE"] == aMasterType.getMasterType() );

		aResult = deleter.execute(aConnection);
		aResult.table();
	}

	return aResult.rowCount()!=-1L;
}
