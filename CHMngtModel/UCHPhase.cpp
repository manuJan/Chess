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
UCHPhase::UCHPhase(RWDBConnection *pNewConnection)
:UGTHPhase(pNewConnection)
{
}

UCHPhase::~UCHPhase()
{
}

void UCHPhase::OnAssignAttributes(const GPhase& aPhase)
{
	UGTHPhase::OnAssignAttributes(aPhase);

	typePhase		= ((CHPhase&)aPhase).getTypePhase();
	idTeamMatchsCnfg= ((CHPhase&)aPhase).getIdTeamMatchsCnfg();
	
}

void UCHPhase::OnInsert(RWDBInserter& aInsert,const GPhase& aPhase)
{
	UGTHPhase::OnInsert(aInsert,aPhase);
	aInsert["TYPEPHASE"]		<< ((CHPhase &)aPhase).getTypePhase();
	aInsert["TEAM_MATCH_CNFG"]	<< ((CHPhase &)aPhase).getIdTeamMatchsCnfg();
	
}

void UCHPhase::OnUpdate(RWDBUpdater& aUpdate,RWDBTable& table,const GPhase& aPhase)
{
	UGTHPhase::OnUpdate(aUpdate,table,aPhase);
	aUpdate << table["TYPEPHASE"]			.assign( ((CHPhase &)aPhase).getTypePhase() );
	aUpdate << table["TEAM_MATCH_CNFG"]		.assign( ((CHPhase &)aPhase).getIdTeamMatchsCnfg() );
	
}

void UCHPhase::OnDelete(RWDBDeleter& aDelete,RWDBTable& table,const GPhase& aPhase)
{
	// Match Judge
	RWDBTable matchJudge			= DBApplication::getTable("CHT013_MATCH_JUDGE");
	RWDBDeleter deleterMatchJudge	= matchJudge.deleter();

	deleterMatchJudge.where( matchJudge["SEX"]		 == fSex	 &&
							 matchJudge["EVENT"] 	 == fEvent	 &&
							 matchJudge["PHASE"] 	 == fPhase );

	// Execute de deleter command
	RWDBResult aResult=deleterMatchJudge.execute( *pConnection );
	aResult.table();

	if( aResult.rowCount()==-1L )
		return ;

	// Split Match
	RWDBTable splitMatch			= DBApplication::getTable("CHT061_SPLIT_MATCH");
	RWDBDeleter deleterSplitMatch	= splitMatch.deleter();

	deleterSplitMatch.where( splitMatch["SEX"]		 == fSex	 &&
							 splitMatch["EVENT"] 	 == fEvent	 &&
							 splitMatch["PHASE"] 	 == fPhase );

	// Execute de deleter command
	aResult=deleterSplitMatch.execute( *pConnection );
	aResult.table();

	if( aResult.rowCount()==-1L )
		return ;

	UGTHPhase::OnDelete(aDelete,table,aPhase);
}