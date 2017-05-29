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
#include "CHMemoryDataBaseDefs.h"

void UCHMasterType::assignAttributes(CHMasterType& aMasterType)
{
	masterType = aMasterType.getMasterType();
	order = aMasterType.getOrder();
	nullorder=true;

	if (order!=0)
		nullorder=false;
}

bool UCHMasterType::insert(GData& aData)
{
	CHMasterType& aMasterType=(CHMasterType&)aData;

	MSLDBTable masterTypeTable      = getTable(CHT_MASTER_TYPE);
	MSLDBTable masterTypeNamesTable = getTable(CHT_MASTER_TYPEL);

	MSLDBInserter inserter = masterTypeTable.inserter();	

	inserter << masterTypeTable["MASTER_TYPE"]	.assign(aMasterType.getMasterType());
	inserter << masterTypeTable["NORDER"]		.assign(order,&nullorder);

	long count=inserter.execute();
	if( count>0L )
		count += OnInsertLang(masterTypeNamesTable,aMasterType);

	return count>0L;
}

long UCHMasterType::OnInsertLang(MSLDBTable& table,const CHMasterType& aMasterType)
{
	long count=0L;
	GLanguage *pLang=0;		
	MSLSetIterator it(GMemoryDataBase::getCol(__GLANGUAGE));		
	while( (pLang=(GLanguage *)it())!=0 )
	{
		if( pLang->getActiveFlag()!=0 && assignNames(aMasterType,pLang->get()) )
			count+=insertLang(table);
	}
	return count;
}

long UCHMasterType::insertLang(MSLDBTable& table)
{
	MSLDBInserter inserterName=table.inserter();
	inserterName << table["MASTER_TYPE"]	.assign(masterType);
	inserterName << table["IDLANGUAGE"]		.assign(lang);
	inserterName << table["SDESCRIPTION"]	.assign(fsDescription,&nullSDescription);
	inserterName << table["LDESCRIPTION"]	.assign(flDescription,&nullLDescription);
	return inserterName.execute();
}

bool UCHMasterType::assignNames(const CHMasterType& aMasterType, const char *language)
{
	GDescription &desc=aMasterType.getDescriptions()[language];	

	lang		= language;
	flDescription	= desc[_LNAME];		nullLDescription	= (flDescription	== L"");
	fsDescription	= desc[_SNAME];		nullSDescription	= (fsDescription	== L"");
	
	return true;
}

bool UCHMasterType::update(GData& aData)
{
	CHMasterType& aMasterType=(CHMasterType&)aData;

	MSLDBTable table = getTable(CHT_MASTER_TYPE);
	MSLDBTable masterTypeNamesTable = getTable(CHT_MASTER_TYPEL);

	MSLDBUpdater updater = table.updater();	

	assignAttributes(aMasterType);

	updater.where(table["MASTER_TYPE"]   == aMasterType.getMasterType());

	updater << table["NORDER"].assign(order,&nullorder);

	long count=updater.execute();

	if( count>0L )
		count += OnUpdateLang(masterTypeNamesTable,aMasterType);

	return count>0;	
}

long UCHMasterType::updateLang(MSLDBTable& table)
{
	MSLDBUpdater updaterName=table.updater();
	updaterName.where(	table["MASTER_TYPE"]	== masterType			&&
						table["IDLANGUAGE"]		== lang);
	
	updaterName << table["SDESCRIPTION"]	.assign(fsDescription,&nullSDescription);
	updaterName << table["LDESCRIPTION"]	.assign(flDescription,&nullLDescription);

	return updaterName.execute();
}

long UCHMasterType::OnUpdateLang(MSLDBTable& table,const CHMasterType& aMasterType)
{
	long count=0L,countLang=0L;
	GLanguage *pLang=0;		
	MSLSetIterator it(GMemoryDataBase::getCol(__GLANGUAGE));		
	while( (pLang=(GLanguage *)it())!=0 )
	{
		if( pLang->getActiveFlag()!=0 && assignNames(aMasterType, pLang->get()) )
		{
			countLang=updateLang(table);
			if( !countLang )
				countLang=insertLang(table);
			count+=countLang;
		}
	}
	return count;
}

bool UCHMasterType::delete_(GData& aData)
{
	CHMasterType& aMasterType=(CHMasterType&)aData;

	assignAttributes(aMasterType);

	MSLDBTable tableNames	= getTable(CHT_MASTER_TYPEL);
	OnDeleteLang(tableNames, aMasterType);
		
	MSLDBTable table	= getTable(CHT_MASTER_TYPE);
	MSLDBCriterion aWhere =	table["MASTER_TYPE"]==masterType;

	MSLDBDeleter deleter=table.deleter();
	deleter.where(aWhere);
		
	return deleter.execute()!=-1;
}

void UCHMasterType::OnDeleteLang(MSLDBTable& table,const CHMasterType& aMasterType)
{
	GLanguage *pLang=0;		
	MSLSetIterator it(GMemoryDataBase::getCol(__GLANGUAGE));		
	while( (pLang=(GLanguage *)it())!=0 )
	{
		if( assignNames(aMasterType,pLang->get()) )
		{
			deleteLang(table);
		}
	}
}

void UCHMasterType::deleteLang(MSLDBTable& table)
{
	MSLDBDeleter deleterName=table.deleter();
	deleterName.where(	table["MASTER_TYPE"]	== masterType &&
						table["IDLANGUAGE"]		== lang);

	deleterName.execute();
}


	