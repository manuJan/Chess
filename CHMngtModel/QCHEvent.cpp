/************************************************************************************* 
*           � Copyright MSL Software, S.L., 1998                                       
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
#include "CHEvent.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void QCHEvent::OnSelect(MSLDBSelector& aSelect,MSLDBTable& tEvent)
{
	aSelect << tEvent["TWO_BRONCES"]
			<< tEvent["TYPE_EVENT"]
			<< tEvent["REQRANKORDER"]
			<< tEvent["TEAMCFG"]
			<< tEvent["CONST_RATING"]
			<< tEvent["POINTS_BYE"]
			<< tEvent["CODE_REPORTS"]
			;
}

void QCHEvent::OnReader(MSLDBReader& aReader,GEvent* pEvent)
{
	short fTwoBronces=0,
		  fTypeEvent=-1,
		  fidTeamMatCnfg;

	double constRating=0.0;
	double pointsBye=0.0;
	
	MSLDBNullIndicator nullCodeRep,nullReqRankOrd;

	MSLWString reqRankOrd(NULLWSTRING);
	MSLString codeReports(NULLSTRING);
	
	aReader	>> fTwoBronces
			>> fTypeEvent
			>> nullReqRankOrd >> reqRankOrd
			>> fidTeamMatCnfg
			>> constRating
			>> pointsBye
			>> nullCodeRep >> codeReports;
	
	CHEvent * pNewEvent = (CHEvent *)pEvent;

	if (nullReqRankOrd)
		reqRankOrd=NULLWSTRING;
	if (nullCodeRep)
		codeReports=NULLSTRING;

	pNewEvent->setTwoBronces(fTwoBronces);
	pNewEvent->setTypeEvent(fTypeEvent);
	pNewEvent->setReqRankOrder(reqRankOrd.toAscii());
	pNewEvent->setIdTeamMatchsCnfg(fidTeamMatCnfg);
	pNewEvent->setConstRating(constRating);
	pNewEvent->setPointsBye(pointsBye);
	pNewEvent->setCodeReports(codeReports);
}
