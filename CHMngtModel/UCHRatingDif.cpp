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

bool UCHRatingDif::insert(GData& aData)
{
	CHRatingDif& aRatingDif=(CHRatingDif&)aData;

	MSLDBTable ratingDifTable      = getTable(CHT_RATING_DIF);

	MSLDBInserter inserter = ratingDifTable.inserter();	

	assignAtributes(aRatingDif);

	inserter << ratingDifTable["CODE_RAT"]		.assign(aRatingDif.getCode());
	inserter << ratingDifTable["PROBABILITY"]	.assign(probability,&nullprobability);
	inserter << ratingDifTable["DIFFERENCE"]	.assign(difference,&nulldifference);

	long count=inserter.execute();
	return count>0L;
}

bool UCHRatingDif::update(GData& aData)
{
	CHRatingDif& aRatingDif=(CHRatingDif&)aData;

	MSLDBTable table = getTable(CHT_RATING_DIF);
	
	MSLDBUpdater updater = table.updater();	

	assignAtributes(aRatingDif);
	updater.where(table["CODE_RAT"]   == aRatingDif.getCode());

	updater << table["PROBABILITY"]	.assign(probability,&nullprobability);
	updater << table["DIFFERENCE"]	.assign(difference,&nulldifference);

	long count=updater.execute();
	return count>0L;
}

bool UCHRatingDif::delete_(GData& aData)
{
	CHRatingDif& aRatingDif=(CHRatingDif&)aData;

	MSLDBTable ratingDifTable      = getTable(CHT_RATING_DIF);
	
	MSLDBCriterion aWhere=	ratingDifTable["CODE_RAT"] == aRatingDif.getCode();

	MSLDBDeleter deleter = ratingDifTable.deleter();
	deleter.where( aWhere );

	return  deleter.execute()!=-1;	
}
