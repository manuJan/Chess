/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:UCHRatingDif.cpp
*	Description	:
*
*	Author		:Chess Team
*	Date created:26-01-2006
* 	Project		:Chess Management Model DLL
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdCHMngt.h"
#include "CHRatingDif.h"
#include "UCHRatingDif.h"

void UCHRatingDif::assignAtributes(CHRatingDif& aRatingDif)
{
	code = aRatingDif.getCode();
	
	probability = aRatingDif.getProbability();

	nullprobability=true;
	if (probability!=0)
		nullprobability=false;

	difference = aRatingDif.getDifference();

	nulldifference=true;
	if (difference!=0)
		nulldifference=false;
}

RWBoolean UCHRatingDif::insert(RWDBConnection& aConnection,GData& aData)
{
	CHRatingDif& aRatingDif=(CHRatingDif&)aData;

	RWDBTable ratingDifTable      = DBApplication::getTable("CHT062_RATING_DIF");

	RWDBInserter inserter = ratingDifTable.inserter();	

	assignAtributes(aRatingDif);

	inserter["CODE_RAT"]		<< aRatingDif.getCode();
	inserter["PROBABILITY"]	<< RWDBBoundExpr(&probability,&nullprobability);
	inserter["DIFFERENCE"]	<< RWDBBoundExpr(&difference,&nulldifference);

	RWDBResult aResult = inserter.execute(aConnection);
	aResult.table();

	return aResult.rowCount()>0L;
}

RWBoolean UCHRatingDif::update(RWDBConnection& aConnection,GData& aData)
{
	CHRatingDif& aRatingDif=(CHRatingDif&)aData;

	RWDBTable table = DBApplication::getTable("CHT062_RATING_DIF");
	
	RWDBUpdater updater = table.updater();	

	assignAtributes(aRatingDif);
	updater.where(table["CODE_RAT"]   == aRatingDif.getCode());

	updater << table["PROBABILITY"].assign(RWDBBoundExpr(&probability,&nullprobability));
	updater << table["DIFFERENCE"].assign(RWDBBoundExpr(&difference,&nulldifference));

	RWDBResult aResult=updater.execute(aConnection);
	aResult.table();
	

	return aResult.rowCount()>0L;
}

RWBoolean UCHRatingDif::delete_(RWDBConnection& aConnection,GData& aData)
{
	CHRatingDif& aRatingDif=(CHRatingDif&)aData;

	RWDBTable ratingDifTable      = DBApplication::getTable("CHT062_RATING_DIF");
	
	RWDBDeleter deleter = ratingDifTable.deleter();
	deleter.where( ratingDifTable["CODE_RAT"] == aRatingDif.getCode() );

	RWDBResult aResult = deleter.execute(aConnection);
	aResult.table();

	if( aResult.rowCount()>0L )
	{
		deleter = ratingDifTable.deleter();
		deleter.where( ratingDifTable["CODE_RAT"] == aRatingDif.getCode() );

		aResult = deleter.execute(aConnection);
		aResult.table();
	}

	return aResult.rowCount()!=-1L;
}
