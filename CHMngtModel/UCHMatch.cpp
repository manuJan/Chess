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
UCHMatch::UCHMatch(RWDBConnection *pNewConnection)
:UTHSPMatch(pNewConnection)
,session(0)
,court(0)
,fSubMatch(0)
,fMatchType(-1)
,rVenue(NULLRWSTRING)
{
}

UCHMatch::~UCHMatch()
{
}

void UCHMatch::OnAssignAttributes(GTHMatch& aMatch)
{
	
	//UTHSPMatch::OnAssignAttributes(aMatch);
	CHMatch *pMatch=((CHMatch *)&aMatch);
			
	court=short(pMatch->getCourtCode());
	GSession *pSession=pMatch->getSession();
	if (pSession)
		session=pMatch->getSessionSession();
	else
		session=0;
	fSubMatch=pMatch->getSubMatch();
	fMatchType=pMatch->getMatchType();
	rVenue=pMatch->getVenueCode();
	fRound=pMatch->getRound();

	nullCourt=(court!=0)? false:true;
	nullSession=(session!=0)? false:true;
	nullVenue=(rVenue!=NULLRWSTRING)?false:true;
	nullRound=(fRound!=0)? false:true;
}

void UCHMatch::OnInsert(RWDBInserter& aInserter,GTHMatch& aMatch)
{
	aInserter["COURT"]		<< RWDBBoundExpr(&court				,&nullCourt);
	aInserter["IDSESSION"]	<< RWDBBoundExpr(&session			,&nullSession);
	aInserter["IDSUBMATCH"]	<< fSubMatch;
	aInserter["IDTYPE"]		<< fMatchType;
	aInserter["VENUE"]		<< RWDBBoundExpr(&rVenue			,&nullVenue);
	aInserter["ROUND"]		<< RWDBBoundExpr(&fRound			,&nullRound);
	
	UNREFERENCED_PARAMETER(aMatch);
}

void UCHMatch::OnUpdate(RWDBUpdater& aUpdater,RWDBTable& t008match,GTHMatch& aMatch)
{
	aUpdater << t008match["COURT"]		.assign(RWDBBoundExpr(&court			,&nullCourt));
	aUpdater << t008match["IDSESSION"]	.assign(RWDBBoundExpr(&session			,&nullSession));
	aUpdater << t008match["IDSUBMATCH"]	.assign(fSubMatch);
	aUpdater << t008match["IDTYPE"]		.assign(fMatchType);
	aUpdater << t008match["VENUE"]		.assign(RWDBBoundExpr(&rVenue			,&nullVenue));
	aUpdater << t008match["ROUND"]		.assign(RWDBBoundExpr(&fRound			,&nullRound));
	
	UNREFERENCED_PARAMETER(aMatch);
}

void UCHMatch::OnDelete(const GTHMatch& aMatch)
{
	// Match Judge
	RWDBTable matchJudge			= DBApplication::getTable("CHT013_MATCH_JUDGE");
	RWDBDeleter deleterMatchJudge	= matchJudge.deleter();

	deleterMatchJudge.where( matchJudge["SEX"]		  == fSex	 &&
							 matchJudge["EVENT"] 	  == fEvent	 &&
							 matchJudge["PHASE"] 	  == fPhase	 &&
							 matchJudge["POOL"]		  == fPool	 &&
							 matchJudge["IDMATCH"] 	  == fMatch);

	// Execute de deleter command
	RWDBResult aResult=deleterMatchJudge.execute( *pConnection );
	aResult.table();

	if( aResult.rowCount()==-1L )
		return ;

	UGTHMatch::OnDelete(aMatch);
}
