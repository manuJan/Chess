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
#include "CHEventResult.h"

void UCHEventResult::OnAssignAttributes(const GEventResult& aEventResult)
{	
	UEventResult::OnAssignAttributes(aEventResult);

	CHEventResult* pEventResult=(CHEventResult*)&aEventResult;
		
	rating=pEventResult->getRating();
	
	if(!rating)
		nullRating	= true;
		
}

void UCHEventResult::OnInsert(MSLDBInserter& aInserter,MSLDBTable& table,const GEventResult& aEventResult)
{
	UEventResult::OnInsert(aInserter,table,aEventResult);
		
	aInserter << table["RATING"].assign(rating,&nullRating); 	
}

void UCHEventResult::OnUpdate(MSLDBUpdater& aUpdater,MSLDBTable& t015EvRes,const GEventResult& aEventResult)
{
	UEventResult::OnUpdate(aUpdater,t015EvRes,aEventResult);
		
	aUpdater << t015EvRes["RATING"].assign(rating,&nullRating);
}
