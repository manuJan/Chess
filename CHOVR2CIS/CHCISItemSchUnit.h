/*************************************************************************************
*			© Copyright MSL Software, S.L., 2008
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHCISItemSchUnit.h
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

#include <ovr\GUI\thovr2cis\GTHCISItemSchUnit.h>

class CHCISItemSchUnit : public GTHCISItemSchUnit
{
public:

	CHCISItemSchUnit(GData* pData);
	~CHCISItemSchUnit();

	/**** virtual Methods ***************************************/
	virtual MSLWString		getLDescription(const char * lang=0);
	virtual MSLWString		getSDescription(const char * lang=0);
	virtual MSLString		getRegKeyA();
	virtual MSLString		getRegKeyB();
	virtual MSLWString		getScore(const char * lang=0);
	virtual MSLWString		getScoreA(const char * lang=0);
	virtual MSLWString		getScoreB(const char * lang=0);
	virtual short			getCourtCode();		

	virtual int				getTypeBracket();
	virtual bool			getPaintMatchBracket();
};
