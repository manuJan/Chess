/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : UCHEvent.cpp                                                                 
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
#include "UCHEvent.h"
#include "CHEvent.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void UCHEvent::OnAssignAttributes(const GEvent& aEvent)
{
	CHEvent *pEvent = (CHEvent*)&aEvent;

	fTwoBronces		= pEvent->getTwoBronces();
	fTypeEvent		= pEvent->getTypeEvent();
	
	reqRankOrd		= pEvent->getReqRankOrder();
	nullReqRankOrd	= (reqRankOrd != "");

	fConstRating	= pEvent->getConstRating();
	fPointsBye		= pEvent->getPointsBye();
			
}

void UCHEvent::OnInsert(MSLDBInserter& aInserter,MSLDBTable& table,const GEvent& aEvent)
{
	UGTHEvent::OnInsert(aInserter,table,aEvent);

	CHEvent* pEvent=(CHEvent*)&aEvent;

	aInserter << table["TWO_BRONCES"]	.assign(fTwoBronces);
	aInserter << table["TYPE_EVENT"]	.assign(fTypeEvent);
	aInserter << table["REQRANKORDER"]	.assign(reqRankOrd);
	aInserter << table["TEAMCFG"]		.assign(pEvent->getIdTeamMatchsCnfg());
	aInserter << table["CONST_RATING"]	.assign(fConstRating);
	aInserter << table["POINTS_BYE"]	.assign(fPointsBye);
	
}

void UCHEvent::OnUpdate(MSLDBUpdater& aUpdater,MSLDBTable& table,const GEvent& aEvent)
{
	UGTHEvent::OnUpdate(aUpdater,table,aEvent);

	CHEvent* pEvent=(CHEvent*)&aEvent;
		
	aUpdater << table["TWO_BRONCES"]	.assign(fTwoBronces);
	aUpdater << table["TYPE_EVENT"]		.assign(fTypeEvent);
	aUpdater << table["REQRANKORDER"]	.assign(reqRankOrd);
	aUpdater << table["TEAMCFG"]		.assign(pEvent->getIdTeamMatchsCnfg());
	aUpdater << table["CONST_RATING"]	.assign(fConstRating);
	aUpdater << table["POINTS_BYE"]		.assign(fPointsBye);
}

