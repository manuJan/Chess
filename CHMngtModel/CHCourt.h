/*************************************************************************************
*	© Copyright MSL Software, S.L., 2001
*
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHCourt.h
*	Description	:Chess
*
*	Author		:Chess Team
*	Date created:12-12-2005
* 	Project		:CH Model
*
*
***************************************************************************************/

#pragma once
#include "CHMemoryDataBaseDefs.h"
#include <OVR/CORE/G/GCourt.h>

class CHMngtModelExport CHCourt : public GCourt  
{
	MSLDECLARE_ITEM(CHCourt)

public:
	// Constructors/Destructor
	CHCourt();
	CHCourt(const CHCourt &copy);	
	virtual ~CHCourt();

	/**** Virtual operators inherited from GData ********************/
	GData& operator= (const GData& copy);
	bool   operator==(const GData& copy);
	bool   operator!=(const GData& copy);
	
	/**** Virtual methods inherited from GData **********************/
	MSLPack& pack  (MSLPack& pck) const;
	MSLPack& unpack(MSLPack& pck);

	QBase*	onQ() const;
	UBase*	onU() const;
	
	//SETS
	void setOrder(const short value);
	
	//GETS
	short getOrder() const;

private:
	short m_order;		// Numero de Orden 
};


