/*************************************************************************************
*			© Copyright MSL Software, S.L., 2008
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: ARCISScreenTeamResults.cpp
*	Description	:
*
*	Author		: CIS Team
*	Date created: 06-04-2011
* 	Project		: GTHOVR2CIS
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "StdAfx.h"
#include "CHCISApp.h"
#include "CHCISScreenResults.h"
#include "CHCISPaint.h"
#include "CHCISDefs.h"

#include "..\CHMngtModel\CHMatch.h"

CHCISScreenResults::CHCISScreenResults(MSLString key)
:GTHCISScreenTeamResults(key)
{

}	

CHCISScreenResults::CHCISScreenResults(MSLString key, MSLString name, MSLString designFile, GData* pData)
:GTHCISScreenTeamResults(key,name,designFile,pData)
{

}

CHCISScreenResults::~CHCISScreenResults()
{
}

void CHCISScreenResults::onRunNotTeamMatch()
{
	if (!m_pData || m_pData->isA()!=__GTHMATCH)
		return;

	CHMatch* pMatch = (CHMatch*)m_pData;
	
	// Results
	if (pMatch->getPhaseCode()==SWISS_ROUND)
		CHPAINT->paintRoundResults(isA(),LST_RESULTS,pMatch);
	else
		CHPAINT->paintMatchResults(isA(),LST_RESULTS,pMatch);
}
