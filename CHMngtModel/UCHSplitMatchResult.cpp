/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : UCHSplitMatchResult.cpp                                                                 
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:13-12-2005
*   Project     :CH Model
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///


#include "stdCHMngt.h"
#include "UCHSplitMatchResult.h"


void UCHSplitMatchResult::OnAssignAttributes(GTHSplitMatchResult& aSplitMatchResult)
{
	
	CHSplitMatchResult* pSplitMatchResult=(CHSplitMatchResult*)&aSplitMatchResult;
	UNREFERENCED_PARAMETER(pSplitMatchResult);
	
}

void UCHSplitMatchResult::OnInsert(RWDBInserter& aInserter, GTHSplitMatchResult& aSplitMatchResult)
{
	UNREFERENCED_PARAMETER(aInserter);	
	UNREFERENCED_PARAMETER(aSplitMatchResult);
}

RWBoolean UCHSplitMatchResult::OnUpdate(RWDBUpdater& aUpdater,RWDBTable& xx006SplitMatchResult, GTHSplitMatchResult& aSplitMatchResult)
{	
	return true;
	UNREFERENCED_PARAMETER(aUpdater);
	UNREFERENCED_PARAMETER(xx006SplitMatchResult);
	UNREFERENCED_PARAMETER(aSplitMatchResult);
}
void UCHSplitMatchResult::OnDelete(const GTHSplitMatchResult& aSplitMatchResult)
{
	UNREFERENCED_PARAMETER(aSplitMatchResult);
		
}