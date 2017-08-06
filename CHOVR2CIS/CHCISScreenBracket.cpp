/*************************************************************************************
*			© Copyright MSL Software, S.L., 2008
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHCISScreenBracket.cpp
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
#include "CHCISScreenBracket.h"


CHCISScreenBracket::CHCISScreenBracket(MSLString eventKey)
:GTHCISScreenBracket(eventKey)
{
}

CHCISScreenBracket::CHCISScreenBracket(MSLString eventKey, MSLString name, MSLString designFile, GTHEvent* pEvent)
:GTHCISScreenBracket(eventKey,name,designFile,pEvent)
{
}

CHCISScreenBracket::~CHCISScreenBracket()
{
}

int	CHCISScreenBracket::getPhaseNumMatches(GTHPhase *pPhase, MSLSortedVector vSchUnits)
{
	return vSchUnits.entries();
	UNREFERENCED_PARAMETER(pPhase);
}

MSLString CHCISScreenBracket::getEliminatoryColumns()
{
	// Tamaño de las columnas en eliminatorias
	return "50C|15C|190L|0C|40C|15R|15C";
}

MSLString CHCISScreenBracket::getPreliminaryColumns	()
{
	// Tamaño de las columnas en preliminar
	return "50C|15C|190L|50C|40R|15C|15C";
}