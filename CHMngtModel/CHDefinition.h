/*************************************************************************************
*			� Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHDefinition.h
*	Description	:
*
*	Author		:Javier Juste
*	Date created:02 Junio 2008
* 	Project		:Chess DLL
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#pragma once
#include "CHMemoryDataBaseDefs.h"
#include <OVR/CORE/TH/GTHDefinition.h>


class CHMngtModelExport CHDefinition : public GTHDefinition
{
	MSLDECLARE_ITEM(CHDefinition)

public:	

	// Constructors/Destructor
	CHDefinition();
	CHDefinition(const CHDefinition & copy);
	virtual ~CHDefinition();

	/**** Virtual operators inherited from GData ********************/
	GData& operator= (const GData& copy);
	bool   operator==(const GData& copy);
	bool   operator!=(const GData& copy);
	
	/**** Virtual methods inherited from GData **********************/
	MSLPack& pack  (MSLPack& pck) const;
	MSLPack& unpack(MSLPack& pck);

	QBase*  onQ() const;
	UBase*  onU() const;
	
	//SETS
	void setAutoProg(const bool value);

	//GETS
	bool getAutoProg() const;

private:
	
	bool m_autoProg;
	
};
