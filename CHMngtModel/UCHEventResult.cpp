/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : UCHEventResult.cpp                                                                 
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
#include "UCHEventResult.h"
//#include "CHMemoryDataBase.h"


void UCHEventResult::OnAssignAttributes(const GTHEventResult& aEventResult)
{
	
	UGTHEventResult::OnAssignAttributes(aEventResult);
	CHEventResult* pEventResult=(CHEventResult*)&aEventResult;

	qualitative=		pEventResult->getQualitativeCode();
	
	nullqualitative	=	(qualitative =="") ? true:false;

	rating=pEventResult->getRating();
	
	if(!rating)
		nullRating	= true;
		
}

void UCHEventResult::OnInsert(RWDBInserter& aInserter,const GTHEventResult& aEventResult)
{
	UGTHEventResult::OnInsert(aInserter,aEventResult);

	aInserter["QUALITATIVE"]	<< RWDBBoundExpr(&qualitative,&nullqualitative);
	aInserter["RATING"]			<< RWDBBoundExpr(&rating,&nullRating);
	
}

void UCHEventResult::OnUpdate(RWDBUpdater& aUpdater,RWDBTable& t015EvRes,const GTHEventResult& aEventResult)
{
	UGTHEventResult::OnUpdate(aUpdater,t015EvRes,aEventResult);

	aUpdater << t015EvRes["QUALITATIVE"]		.assign(RWDBBoundExpr(&qualitative,&nullqualitative));
	aUpdater << t015EvRes["RATING"]		.assign(RWDBBoundExpr(&rating,&nullRating));
}
