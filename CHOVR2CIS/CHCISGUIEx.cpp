/*************************************************************************************
*			© Copyright MSL Software, S.L., 2008
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHCISGUIEx.h
*	Description	:
*
*	Author		: Javier Juste
*	Date created: 28-03-2011
* 	Project		: BKOVR2CIS
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "StdAfx.h"
#include "CHCISGUIEx.h"
#include "CHCISProcess.h"

#include "..\CHMngtModel\CHMatchResult.h"

CHCISGUIEx::CHCISGUIEx()
{
}

CHCISGUIEx::~CHCISGUIEx()
{
}

bool CHCISGUIEx::processSportNotify(GData * pData, int idNotify, MSLString buffer)
{
	if (!pData)
		return true;

	/*if (idNotify==N_RANKING_CIS)
	{
		if (pData->isA()==__BKPOOL)
			CHPROCESS->updateScreen(__CISTHSCREEN_POOLSUMMARY, ((BKPool*)pData)->getPhaseKey());
		if (pData->isA()==__CHPhase)
			CHPROCESS->updateScreen(__CISTHSCREEN_POOLSUMMARY, ((CHPhase*)pData)->getKey());
	}*/

	return true;
}

bool CHCISGUIEx::forceNewSportData(GData * pNewData, GData * pOldData, long idTrn)
{
	if (pNewData && pOldData && pNewData->isA()==__CHMATCHRESULT && pOldData->isA()==__CHMATCHRESULT)
	{
		if ( ((CHMatchResult*)pNewData)->getType()!=((CHMatchResult*)pOldData)->getType())
			return true;
	}

	return false;
}