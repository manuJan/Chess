/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : QCHMatch.cpp
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
#include "QCHMatch.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
QCHMatch::QCHMatch(RWDBConnection *pNewConnection)
:QGTHMatch(pNewConnection) 
{
}

QCHMatch::~QCHMatch()
{
}

GTHMatch * QCHMatch::OnNewMatch(const RWDBBlob& aBlob)
{ 
	return new CHMatch(aBlob); 
}

void QCHMatch::OnSelect(RWDBSelector& aSelect,RWDBTable& tMatch)
{
	aSelect << tMatch["COURT"]
			<< tMatch["IDSESSION"]
			<< tMatch["IDSUBMATCH"]
			<< tMatch["IDTYPE"]
			<< tMatch["VENUE"]
			<< tMatch["ROUND"];
}

void QCHMatch::OnReader(RWDBReader& aReader,GTHMatch *pMatch)
{
	short court;
	short session;
	short fSubMatch, fMatchType, fRound;
	RWCString rVenue;

	RWDBNullIndicator nullCourt;
	RWDBNullIndicator nullSession;
	RWDBNullIndicator nullSubMatch;
	RWDBNullIndicator nullMatchType;
	RWDBNullIndicator nullVenue;
	RWDBNullIndicator nullRound;


	aReader	>> nullCourt			>> court
			>> nullSession			>> session
			>> nullSubMatch			>> fSubMatch
			>> nullMatchType		>> fMatchType
			>> nullVenue			>> rVenue
			>> nullRound			>> fRound
			;


	CHMatch *pNewMatch=(CHMatch *)pMatch;
	
	//venue
	GVenue *pVenue=0;
	pVenue=(GVenue *)GTHMemoryDataBase::findVenue(rVenue);
	if (nullVenue || !pVenue)
		pNewMatch->setVenue(0);
	else
		pNewMatch->setVenue(pVenue);

	//court
	if (nullCourt)
		pNewMatch->setCourt(0);
	else
	{
		GCourt *pCourt = 0;
		
		pCourt = GMemoryDataBase::findCourt(pNewMatch->getVenueCode(),court );
		if (pCourt)
			pNewMatch->setCourt(pCourt); 
	}

	//session
	GSession *pSession=0;

	RWDate date=pNewMatch->getStartDate();
	if (date.isValid())
		pSession= (GSession *)GTHMemoryDataBase::findSession(date, char(session));
	if (nullSession || !pSession)
		pNewMatch->setSession(0);
	else
		pNewMatch->setSession((GTHSession *)pSession);

	//subMatch
	if (nullSubMatch) fSubMatch=0;
	pNewMatch->setSubMatch(fSubMatch);

	//matchType
	if (nullMatchType) fMatchType=CHMatch::eNone;
	pNewMatch->setMatchType(fMatchType);

	

	pNewMatch->setRound(fRound);
}
