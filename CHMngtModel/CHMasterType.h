/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHMasterType.h
*	Description	:
*
*	Author		:CH Team
*	Date created:09-12-2005
* 	Project		:Chess Management Model DLL
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#pragma once
#include "CHMemoryDataBaseDefs.h"
#include <OVR/CORE/G/GData.h>

class CHMngtModelExport CHMasterType : public GData  
{
	MSLDECLARE_ITEM(CHMasterType)

public:
	// Constructors & Destructor
	CHMasterType();
	CHMasterType(const short id);
	CHMasterType(const CHMasterType & copy);	
	virtual ~CHMasterType();

	// Overloaded Operators
	/**** Virtual operators inherited from GData ********************/
	GData& operator= (const GData& copy);
	bool   operator==(const GData& copy);
	bool   operator!=(const GData& copy);
	
	/**** Virtual methods inherited from GData **********************/
	MSLPack& pack  (MSLPack& pck) const;
	MSLPack& unpack(MSLPack& pck);

	QBase*			onQ() const;
	UBase*			onU() const;
	void			setKey();

	// Set Methods
	void setMasterType(const short value);
	void setDescriptions(GDescription& desc);
	void setOrder(const short value);

	// Get Methods
	short getMasterType() const;
	short getOrder() const;
	GDescriptions&  getDescriptions () const;

	// Class Methods
	MSLWString getSDescription(const char *lang=0) const;
	MSLWString getLDescription(const char *lang=0) const;
	
private:
	short m_masterType;
	short m_order;
	GDescriptions	m_Desc;
};


