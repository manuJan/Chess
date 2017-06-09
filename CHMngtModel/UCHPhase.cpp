/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : UCHPhase.cpp
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
#include "UCHPhase.h"
#include "CHPhase.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void UCHPhase::OnAssignAttributes(const GPhase& aPhase)
{
	UGTHPhase::OnAssignAttributes(aPhase);

	typePhase		= ((CHPhase&)aPhase).getTypePhase();
	idTeamMatchsCnfg= ((CHPhase&)aPhase).getIdTeamMatchsCnfg();
	
}

void UCHPhase::OnInsert(MSLDBInserter& aInserter,MSLDBTable& table,const GPhase& aPhase)
{
	UGTHPhase::OnInsert(aInserter, table,aPhase);

	aInserter << table["TYPEPHASE"]			.assign(typePhase);
	aInserter << table["TEAM_MATCH_CNFG"]	.assign(idTeamMatchsCnfg);

	UNREFERENCED_PARAMETER(aPhase);
}

void UCHPhase::OnUpdate(MSLDBUpdater & aUpdater ,MSLDBTable& table,const GPhase& aPhase)
{
	UGTHPhase::OnUpdate(aUpdater, table, aPhase);

	aUpdater << table["TYPEPHASE"]			.assign( typePhase );
	aUpdater << table["TEAM_MATCH_CNFG"]	.assign( idTeamMatchsCnfg );

	UNREFERENCED_PARAMETER(aPhase);
}

