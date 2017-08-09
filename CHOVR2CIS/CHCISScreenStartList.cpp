/*************************************************************************************
*			© Copyright MSL Software, S.L., 2008
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHCISScreenStartList.cpp
*	Description	:
*
*	Author		: AR Team
*	Date created: 06-04-2011
* 	Project		: AROVR2CIS
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/


#include "StdAfx.h"
#include "CHCISScreenStartList.h"
#include "CHCISPaint.h"
#include "CHCISDefs.h"
#include "..\CHMngtModel\CHMatch.h"

CHCISScreenStartList::CHCISScreenStartList(MSLString key)
:GTHCISScreenStartList(key)
{

}

CHCISScreenStartList::CHCISScreenStartList(MSLString key, MSLString name, MSLString designFile, GData* pData)
:GTHCISScreenStartList(key,name,designFile,pData)
{

}

CHCISScreenStartList::~CHCISScreenStartList(void)
{
}

void CHCISScreenStartList::onRunNotTeamMatch()
{
	if (!m_pData || m_pData->isA()!=__GTHMATCH)
		return;

	CHMatch* pMatch = (CHMatch*)m_pData;
	
	// Startlist
	if (pMatch->getPhaseCode()==SWISS_ROUND)
		CHPAINT->paintStartList(isA(),LST_STARTLIST,pMatch);
}