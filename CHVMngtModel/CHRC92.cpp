/*************************************************************************************
*			© Copyright MSL Software, S.L., 2008
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: ARC92A.cpp
*	Description	:
*
*	Author		: M.
*	Date created: 19-10-2009
* 	Project		: AR(V) Dll
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdafx.h"
#include "CHRC92.h"

CHRC92::CHRC92(CReportManager& aRM,CReportConfig& aRC,const GEvent *pEvent)
:RC92(aRM,aRC,pEvent)
{
}

CHRC92::~CHRC92(void)
{
}

MSLDate CHRC92::OnGetEventDate() const
{
	GTHMatch * pMatch = 0;
	MSLSetIterator it(GTHMemoryDataBase::getCol(__GTHMATCH));
	while( (pMatch=(GTHMatch*)it())!=0 )
	{
		if( pMatch->getPhaseCode() == GOLD_MEDAL && pMatch->getEvent() == m_pHeaderEvent )
			return pMatch->getStartDate();
	}
	return INVALID_DATE;
}

MSLTime CHRC92::OnGetEventTime() const
{
	return INVALID_TIME;
}
