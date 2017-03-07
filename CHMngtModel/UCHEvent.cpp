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
UCHEvent::UCHEvent(RWDBConnection *pNewConnection)
:UGTHEvent(pNewConnection)
{
}

UCHEvent::~UCHEvent()
{
}

void UCHEvent::OnAssignAttributes(const GEvent& aEvent)
{
	CHEvent *pEvent = (CHEvent*)&aEvent;

	fOrderEvent		= pEvent->getOrderEvent();
	fMode			= pEvent->getMode();
	fTwoBronces		= pEvent->getTwoBronces();
	fTypeEvent		= pEvent->getTypeEvent();
	
	reqRankOrd		= pEvent->getReqRankOrder();
	nullReqRankOrd	= (reqRankOrd != "");

	fConstRating	= pEvent->getConstRating();
	fPointsBye		= pEvent->getPointsBye();
			
}

void UCHEvent::OnInsert(RWDBInserter& aInserter,const GEvent& aEvent)
{
	UGTHEvent::OnInsert(aInserter,aEvent);

	CHEvent* pEvent=(CHEvent*)&aEvent;

	aInserter["ORDER_EVENT"]	<< fOrderEvent;
	aInserter["MODE"]			<< fMode;
	aInserter["TWO_BRONCES"]	<< fTwoBronces;
	aInserter["TYPE_EVENT"]		<< fTypeEvent;
	aInserter["REQRANKORDER"]	<< reqRankOrd;
	aInserter["TEAMCFG"]		<< pEvent->getIdTeamMatchsCnfg();
	aInserter["CONST_RATING"]	<< fConstRating;
	aInserter["POINTS_BYE"]		<< fPointsBye;
	
}

void UCHEvent::OnUpdate(RWDBUpdater& aUpdater,RWDBTable& table,const GEvent& aEvent)
{
	UGTHEvent::OnUpdate(aUpdater,table,aEvent);

	CHEvent* pEvent=(CHEvent*)&aEvent;

	aUpdater << table["ORDER_EVENT"]	.assign(fOrderEvent);
	aUpdater << table["MODE"]			.assign(fMode);
	aUpdater << table["TWO_BRONCES"]	.assign(fTwoBronces);
	aUpdater << table["TYPE_EVENT"]		.assign(fTypeEvent);
	aUpdater << table["REQRANKORDER"]	.assign(reqRankOrd);
	aUpdater << table["TEAMCFG"]		.assign(pEvent->getIdTeamMatchsCnfg());
	aUpdater << table["CONST_RATING"]	.assign(fConstRating);
	aUpdater << table["POINTS_BYE"]		.assign(fPointsBye);
		
}

void UCHEvent::OnDelete(RWDBUpdater& aUpdate,RWDBTable& table,const GEvent& aEvent)
{
	UGTHEvent::OnDelete(aUpdate, table, aEvent);
}