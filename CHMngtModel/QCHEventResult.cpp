/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : QCHEventResult.cpp                                                                 
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
#include "QCHEventResult.h"
#include "CHEventResult.h"
//#include "CHMemoryDatabase.h"


void QCHEventResult::OnSelect(RWDBSelector& aSelect,RWDBTable& tPool)
{
	QGTHEventResult::OnSelect(aSelect,tPool);

	aSelect << tPool["QUALITATIVE"];
	aSelect << tPool["RATING"];
			
}

void QCHEventResult::OnReader(RWDBReader& aReader,GTHEventResult *pValue)
{
	QGTHEventResult::OnReader(aReader,pValue);

	CHEventResult* pVal = (CHEventResult*)pValue;

	RWCString qualitative;
	short     rating;
			

	RWDBNullIndicator nullqualitative,nullRating;
	
	
	aReader >> nullqualitative	>> qualitative
			>> nullRating		>> rating
			;
	
	
	if ( nullqualitative ) qualitative="";
		
	pVal->setQualitative(qualitative);

	if (nullRating)
		rating=0;
	
	pVal->setRating(rating);
	
}

GTHEventResult * QCHEventResult::OnNewEventResult()
{
	return new CHEventResult();
}