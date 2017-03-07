/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : QCHEvent.cpp                                                                 
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
#include "QCHEvent.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
QCHEvent::QCHEvent(RWDBConnection *pNewConnection,QEvent::SelectionMode selection/*=QEvent::eActive*/)
:QGTHEvent(pNewConnection,selection)
{
}

QCHEvent::~QCHEvent()
{
}

GEvent* QCHEvent::OnNewEvent()
{
	return new CHEvent;
}

void QCHEvent::OnSelect(RWDBSelector& aSelect,RWDBTable& tEvent)
{
	QGTHEvent::OnSelect(aSelect,tEvent);

	aSelect << tEvent["ORDER_EVENT"]
			<< tEvent["MODE"]
			<< tEvent["TWO_BRONCES"]
			<< tEvent["TYPE_EVENT"]
			<< tEvent["REQRANKORDER"]
			<< tEvent["TEAMCFG"]
			<< tEvent["CONST_RATING"]
			<< tEvent["POINTS_BYE"]
			;
}

void QCHEvent::OnReader(RWDBReader& aReader,GEvent* pEvent)
{
	QGTHEvent::OnReader(aReader,pEvent);
	
	short fOrderEvent=0,
		  fTwoBronces=0,
		  fTypeEvent=-1,
		  fidTeamMatCnfg,
		  fMode=0;
	float constRating=0.0;
	float pointsBye=0.0;
	
	RWCString reqRankOrd(NULLRWSTRING);
	
	aReader	>> fOrderEvent
			>> fMode
			>> fTwoBronces
			>> fTypeEvent
			>> reqRankOrd
			>> fidTeamMatCnfg
			>> constRating
			>> pointsBye;
	
	CHEvent * pNewEvent = (CHEvent *)pEvent;

	pNewEvent->setOrderEvent(fOrderEvent);
	pNewEvent->setMode(fMode);
	pNewEvent->setTwoBronces(fTwoBronces);
	pNewEvent->setTypeEvent(fTypeEvent);
	pNewEvent->setReqRankOrder(reqRankOrd);
	pNewEvent->setIdTeamMatchsCnfg(fidTeamMatCnfg);
	pNewEvent->setConstRating(constRating);
	pNewEvent->setPointsBye(pointsBye);

}
