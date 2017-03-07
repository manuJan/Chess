
/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : UCHMatchJudge.cpp                                                                 
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
#include "UCHMatchJudge.h"

void UCHMatchJudge::OnAssignAttributes(GTHMatchJudge& aMatchJudge)
{
	CHMatchJudge *pMatchJudge = (CHMatchJudge *)&aMatchJudge;

	UNREFERENCED_PARAMETER(pMatchJudge);
}

void UCHMatchJudge::OnInsert(RWDBInserter& aInserter,GTHMatchJudge& aMatchJudge)
{
	UNREFERENCED_PARAMETER(aInserter);
	UNREFERENCED_PARAMETER(aMatchJudge);
}

void UCHMatchJudge::OnUpdate(RWDBUpdater& aUpdater,RWDBTable& t013matchJudge,GTHMatchJudge& aMatchJudge)
{
	UNREFERENCED_PARAMETER(aUpdater);
	UNREFERENCED_PARAMETER(t013matchJudge);
	UNREFERENCED_PARAMETER(aMatchJudge);
}