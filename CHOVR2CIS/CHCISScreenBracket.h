/*************************************************************************************
*			© Copyright MSL Software, S.L., 2008
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHCISScreenBracket.h
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

#pragma once
#include <OVR/GUI/THOVR2CIS/GTHCISScreenBracket.h>

class CHCISScreenBracket : public GTHCISScreenBracket
{
public:

	CHCISScreenBracket(MSLString key);
	CHCISScreenBracket(MSLString key, MSLString name, MSLString designFile, GTHEvent * pEvent=0);
	virtual ~CHCISScreenBracket();

	virtual int	getPhaseNumMatches(GTHPhase *pPhase, MSLSortedVector vSchUnits); 

	virtual MSLString getPreliminaryColumns();
	virtual MSLString getEliminatoryColumns();
};
