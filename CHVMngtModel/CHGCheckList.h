/*************************************************************************************
*			© Copyright MSL Software, S.L., 2000 - 2008
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHGCheckList.h
*	Description	: Interface for the CHGCheckList class.
*
*	Author		: Jose Matas
*	Date created: 21 Enero 2009
* 	Project		: BKVMngtModel
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#pragma once
#include "CHVMngtModelDefs.h"
#include <OVR\REPORTS\V\GCheckList.h>

class CHRegister;

class CHGCheckList : public GCheckList  
{
public:
	// Constructor/Destructor
	CHGCheckList();
	virtual ~CHGCheckList();

	void setRegister(CHRegister *pReg, const char * lang=0);

	// Get Methods
	MSLWString getMasterType() const;
	MSLWString getEvents() const;
	void setSortCad();

private:
	// Elementos que queramos recuperar del member
	MSLWString	m_masterType;
	MSLWString	m_events;	
};
