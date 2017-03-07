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
UCHMatchResult::UCHMatchResult(RWDBConnection *pNewConnection)
:UGTHMatchResult(pNewConnection)
,fPoints(0)
,fSubMatch(0)
{
}

UCHMatchResult::~UCHMatchResult()
{
}

void UCHMatchResult::OnAssignAttributes(GTHMatchResult& aMatchResult)
{
	CHMatchResult *pMatchResult=(CHMatchResult *)&aMatchResult;
			
	fPoints					= pMatchResult->getPoints();
	fSubMatch				= pMatchResult->getSubMatch();
}

void UCHMatchResult::OnInsert(RWDBInserter& aInserter,GTHMatchResult& aMatchResult)
{
	CHMatchResult *pMatchResult=(CHMatchResult *)&aMatchResult;

	aInserter["POINTS"]				<< fPoints;
	aInserter["IDSUBMATCH"]			<< fSubMatch;
	aInserter["UPFLOATER"]			<< pMatchResult->getUpFloater();
	aInserter["DOWNFLOATER"]		<< pMatchResult->getDownFloater();
	aInserter["COLOR"]				<< pMatchResult->getColor();
}

void UCHMatchResult::OnUpdate(RWDBUpdater& aUpdater,RWDBTable& t009matchResult,GTHMatchResult& aMatchResult)
{
	CHMatchResult *pMatchResult=(CHMatchResult *)&aMatchResult;

	aUpdater << t009matchResult["POINTS"]			.assign(fPoints);
	aUpdater << t009matchResult["IDSUBMATCH"]		.assign(fSubMatch);
	aUpdater << t009matchResult["UPFLOATER"]		.assign(pMatchResult->getUpFloater());
	aUpdater << t009matchResult["DOWNFLOATER"]		.assign(pMatchResult->getDownFloater());
	aUpdater << t009matchResult["COLOR"]			.assign(pMatchResult->getColor());
}

void UCHMatchResult::OnDelete(const GTHMatchResult& aMatchResult)
{
	UNREFERENCED_PARAMETER(aMatchResult);
}