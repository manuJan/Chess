/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:QCHRatingDif.cpp
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
#include "QCHRatingDif.h"

size_t QCHRatingDif::selectCollection(MSLCollection& target)
{
	MSLString table=CHT_RATING_DIF;

	MSLDBTable tRating	 = getTable(table);
	MSLDBSelector select = getSelector();
	
	select	<< tRating["CODE_RAT"]
			<< tRating["PROBABILITY"]
			<< tRating["DIFFERENCE"]
			;
	
	MSLDBReader rdr = select.reader();		

	// fetch 
	
	short fCode,fProbability,fDifference;
	MSLDBNullIndicator	nullProbability, nullDifference;
	
	CHRatingDif* pRatingDif=0;

	while( rdr() )
	{
		rdr >> fCode
			>> nullProbability	>> fProbability
			>> nullDifference	>> fDifference
			;

		
		if (nullProbability)
			fProbability=0;

		if (nullDifference)
			fDifference=0;

		CHRatingDif aRatingDif(fCode);

		pRatingDif=(CHRatingDif*)target.find(&aRatingDif);
		if (!pRatingDif)
		{
			pRatingDif=new CHRatingDif(fCode);
			pRatingDif->setCode(fCode);
			pRatingDif->setProbability(fProbability);
			pRatingDif->setDifference(fDifference);
			target.insert(pRatingDif);
		}

	}

	return target.entries();

}
