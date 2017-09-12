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
#include "..\CHMngtModel\CHPool.h"
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

	// Assigno el tablero
	CHPool * pPool = (CHPool * ) pMatch->getPool();
	MSLSortedVector vRoundMatches;
	pPool->getRoundMatchesVector( vRoundMatches, ((CHMatch*)pMatch)->getRound());

	if (vRoundMatches.entries())
	{
		long index = vRoundMatches.index( pMatch );
		if (index>0)
		{
			CHMatch * pPrevMatch = (CHMatch*)vRoundMatches[index-1];
			if (pPrevMatch)
			{
				if (pPrevMatch->getCourt())
				{
					short courtCodeSubMatch = pPrevMatch->getCourtCode();
					if (pPrevMatch->isTeam())
					{
						MSLSet colSubMatches;
						pPrevMatch->getSubMatches(colSubMatches);	
						courtCodeSubMatch=courtCodeSubMatch+colSubMatches.entries();
					}
					else
						courtCodeSubMatch++;

					pMatch->setCourtCode(courtCodeSubMatch);
				}				
			}
		}
		else
		{
			pMatch->setCourtCode(1);
		}
	}
	
	APP::out(*pMatch);
	APP::out(TRN_SET_MATCH);

	if(!pMatch->getSubMatch()) //Fecha a los hijos
		onScheduleChangeSubMatch((CHMatch*)pMatch);	
}
	
void CHScheduleData::onMatchUndoScheduled(GTHMatch* pMatch)
{
	GTHScheduleData::onMatchUndoScheduled(pMatch);

	if(!pMatch->getSubMatch()) //Fecha a los hijos
	{
		onScheduleChangeSubMatch((CHMatch*)pMatch);
	}
}

bool CHScheduleData::onScheduleChangeSubMatch(CHMatch * pMatch)
{
	bool rtn=false;

	if(!pMatch || pMatch->getSubCode())
		return rtn;

	MSLSortedVector vSubMatches;
	pMatch->getSubMatchesVector(vSubMatches,orderMatchByDateTime);

	if(!vSubMatches.entries())
		return rtn;

	short courtCodeSubMatch = pMatch->getCourtCode();
	
	for (short i=0;i<vSubMatches.entries();i++)
	{
		CHMatch* pSubMatch=(CHMatch*)vSubMatches[i];
		
		if (pMatch->getStartDate().value()!=pSubMatch->getStartDate().value() )
		{
			pSubMatch->setStartDate(pMatch->getStartDate());
			pSubMatch->setStartTime(pMatch->getStartTime());									
			rtn=true;
		}
		
		if (pMatch->getStatus()!=pSubMatch->getStatus() )
		{
			pSubMatch->setStatus(pMatch->getStatus());
			rtn=true;
		}

		if (pMatch->getCourtCode()==0)
		{
			pSubMatch->setVenueCode(NULLSTRING);
			pSubMatch->setCourtCode(0);
			rtn=true;
		}
		else if (pSubMatch->getCourtCode()!=courtCodeSubMatch)
		{
			pSubMatch->setVenueCode(pMatch->getVenueCode());
			pSubMatch->setCourtCode(courtCodeSubMatch);
			rtn=true;
			courtCodeSubMatch++;
		}		

		if (rtn)
			APP::out(*pSubMatch);
	}

	if (rtn)
		APP::out(TRN_SET_MATCH);
	
	return rtn;
}
