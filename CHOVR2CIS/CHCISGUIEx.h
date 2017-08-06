/*************************************************************************************
*			© Copyright MSL Software, S.L., 2008
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: BKCISApp.h
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

#pragma once
#include <OVR/GUI/THOVR2CIS/GTHCISGUIEx.h>

class CHCISGUIEx : public GTHCISGUIEx
{
public:
	CHCISGUIEx();
	virtual ~CHCISGUIEx();

	virtual bool processSportNotify(GData * pData, int idNotify, MSLString buffer);
	virtual bool forceNewSportData(GData * pNewData, GData * pOldData, long idTrn);
};
