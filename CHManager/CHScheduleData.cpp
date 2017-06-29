/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHScheduleData.h
*   Description : 
*
*   Author      : Javier Juste
*   Date created: 2-FEb-2009
*   Project     : AR Manager
*
*   Modification history
*   By      :
*   Date    :
*   Changes :
*
*****************************************************************************************/


#include "StdAfx.h"
#include "CHManagerApp.h"
#include "CHScheduleData.h"
#include "..\CHMngtModel\CHMatch.h"

#include <ovr\core\th\gthmsgdefines.h>
#include <ovr\gui\guithmanager\GTHAvailableMatchGUIEx.h>

int orderMatchByDateTime(const MSLItem** a, const MSLItem** b)
{
	CHMatch * pMatchA = (CHMatch *)(*a);
	CHMatch * pMatchB = (CHMatch *)(*b);
	
	if( !pMatchA->getStartDate().isValid() && pMatchB->getStartDate().isValid())
		return 1;
	if( !pMatchB->getStartDate().isValid() && pMatchA->getStartDate().isValid() )
		return -1;
	if( !pMatchB->getStartDate().isValid() && !pMatchA->getStartDate().isValid() )
		return strcmp(pMatchA->getKey(),pMatchB->getKey());

	// 1º - DATE
	int order = pMatchA->getStartDate().value()-pMatchB->getStartDate().value();
	if( order )
		return order;
		
	// Compare time
	if( pMatchA->getStartTimeAsString("%H:%M")==NULLSTRING &&
		pMatchB->getStartTimeAsString("%H:%M")==NULLSTRING )
		return strcmp(pMatchA->getKey(),pMatchB->getKey());

	if( pMatchA->getStartTimeAsString("%H:%M")==NULLSTRING )
		return 1;
	if( pMatchB->getStartTimeAsString("%H:%M")==NULLSTRING )
		return -1;

	order=strcmp(pMatchA->getStartTimeAsString("%H:%M"),
				 pMatchB->getStartTimeAsString("%H:%M") );

	if(order)
		return order;

	order = pMatchA->getCourtCode() - pMatchB->getCourtCode();
	if(order)
		return order;
		
	// 6º - KEY
	return strcmp(pMatchA->getKey(),pMatchB->getKey());
}

CHScheduleData::CHScheduleData(MSLGUIEx* pGUIEx)
:GTHScheduleData(pGUIEx)
{
}

CHScheduleData::~CHScheduleData(void)
{
}

void CHScheduleData::onMatchScheduled(GTHMatch* pMatch)
{	
	GTHScheduleData::onMatchScheduled(pMatch);

	if(pMatch->getSubMatch()) //Fecha al padre
		onScheduleChangeSubMatch((CHMatch*)pMatch);	
}
	
void CHScheduleData::onMatchUndoScheduled(GTHMatch* pMatch)
{
	GTHScheduleData::onMatchUndoScheduled(pMatch);

	if(pMatch->getSubMatch()) //Fecha al padre
	{
		onScheduleChangeSubMatch((CHMatch*)pMatch);
	}
}

bool CHScheduleData::onScheduleChangeSubMatch(CHMatch * pMatch)
{
	bool rtn=false;

	if(!pMatch)
		return rtn;

	CHMatch * pMatchParent=(CHMatch*)pMatch->getParent();
	if(!pMatchParent)
		return rtn;

	MSLSortedVector vSubMatches;
	pMatchParent->getSubMatchesVector(vSubMatches,orderMatchByDateTime);

	if(!vSubMatches.entries())
		return rtn;

	CHMatch* pSubMatch=(CHMatch*)vSubMatches[0];
	if(!pSubMatch)
		return rtn;

	if (pMatchParent->getStartDate().value()!=pSubMatch->getStartDate().value() )
	{
		pMatchParent->setStartDate(pSubMatch->getStartDate());
		pMatchParent->setStartTime(pSubMatch->getStartTime());
		APP::out(*pMatchParent);
		APP::out(TRN_SET_MATCH);
		rtn=true;
	}
	
	return rtn;
}
