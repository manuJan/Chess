/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : UCHSplitMatch.cpp                                                                 
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
#include "UCHSplitMatch.h"


void UCHSplitMatch::OnAssignAttributes(GTHSplitMatch& aSplitMatch)
{
	CHSplitMatch* pSplitMatch=(CHSplitMatch*)&aSplitMatch;

	UNREFERENCED_PARAMETER(pSplitMatch);

	
}

void UCHSplitMatch::OnInsert(RWDBInserter& aInserter,GTHSplitMatch& aSplitMatch)
{
	
	UNREFERENCED_PARAMETER(aInserter);
	UNREFERENCED_PARAMETER(aSplitMatch);
}

void UCHSplitMatch::OnUpdate(RWDBUpdater& aUpdater,RWDBTable& table,GTHSplitMatch& aSplitMatch)
{
	
	UNREFERENCED_PARAMETER(aUpdater);
	UNREFERENCED_PARAMETER(table);
	UNREFERENCED_PARAMETER(aSplitMatch);
}