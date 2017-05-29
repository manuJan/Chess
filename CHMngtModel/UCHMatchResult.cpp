/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : UCHMatchResult.cpp
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
#include "UCHMatchResult.h"
#include "CHMatchResult.h"
#include "CHMatch.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
void UCHMatchResult::OnAssignAttributes(GTHMatchResult& aMatchResult)
{
	CHMatchResult *pMatchResult=(CHMatchResult *)&aMatchResult;
			
	fPoints	= pMatchResult->getPoints();
}

void UCHMatchResult::OnInsert(MSLDBInserter& aInserter,MSLDBTable& table,const GTHMatchResult& aMatchResult)
{
	CHMatchResult *pMatchResult=(CHMatchResult *)&aMatchResult;

	aInserter << table["POINTS_F"]			.assign(fPoints);	
	aInserter << table["UPFLOATER"]			.assign(pMatchResult->getUpFloater());
	aInserter << table["DOWNFLOATER"]		.assign(pMatchResult->getDownFloater());
	aInserter << table["COLOR"]				.assign(pMatchResult->getColor());
}

void UCHMatchResult::OnUpdate(MSLDBUpdater & aUpdater ,MSLDBTable& table,const GTHMatchResult& aMatchResult)
{
	CHMatchResult *pMatchResult=(CHMatchResult *)&aMatchResult;

	aUpdater << table["POINTS_F"]		.assign(fPoints);	
	aUpdater << table["UPFLOATER"]		.assign(pMatchResult->getUpFloater());
	aUpdater << table["DOWNFLOATER"]	.assign(pMatchResult->getDownFloater());
	aUpdater << table["COLOR"]			.assign(pMatchResult->getColor());
}
