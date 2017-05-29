/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : UCHMatch.cpp
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
#include "UCHMatch.h"
#include "CHMatch.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void UCHMatch::OnAssignAttributes(GTHMatch& aMatch)
{
	CHMatch *pMatch=((CHMatch *)&aMatch);
			
	fMatchType=pMatch->getMatchType();
	fRound=pMatch->getRound();

	nullRound=(fRound!=0)? false:true;
}

void UCHMatch::OnInsert(MSLDBInserter& aInserter,MSLDBTable& table,const GTHMatch& aMatch)
{
	aInserter << table["IDTYPE"]	.assign(fMatchType);
	aInserter << table["ROUND"]		.assign(fRound,&nullRound);
	
	UNREFERENCED_PARAMETER(aMatch);
}

void UCHMatch::OnUpdate(MSLDBUpdater & aUpdater ,MSLDBTable& table,const GTHMatch& aMatch)
{
	aUpdater << table["IDTYPE"]		.assign(fMatchType);
	aUpdater << table["ROUND"]		.assign(fRound,&nullRound);
	
	UNREFERENCED_PARAMETER(aMatch);
}

