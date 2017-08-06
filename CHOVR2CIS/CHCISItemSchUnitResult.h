/*************************************************************************************
*			© Copyright MSL Software, S.L., 2008
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHCISItemSchUnitResult.h
*	Description	:
*
*	Author		: BK Team
*	Date created: 28-03-2011
* 	Project		: BKOVR2CIS
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#pragma once

#include <ovr\gui\thovr2cis\GTHCISItemSchUnitResult.h>

class CHCISItemSchUnitResult : public GTHCISItemSchUnitResult
{

public:

	CHCISItemSchUnitResult(GData* pData);
	~CHCISItemSchUnitResult();
		
protected:

	/**** virtual Methods ***************************************/
	virtual MSLWString		getScore(const char* lang=0);	
	virtual MSLString		getRegKeyA();
	virtual MSLString		getRegKeyB();
	virtual MSLWString		getIDCompetitorSDesc(const char* lang);
	virtual MSLWString		getIDCompetitorLDesc(const char* lang);
};
