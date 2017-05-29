/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHRatingDif.h
*	Description	:
*
*	Author		:CH Team
*	Date created:26-01-2006
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

class CHMngtModelExport CHRatingDif : public GData  
{
	MSLDECLARE_ITEM(CHRatingDif)

public:
	// Constructors & Destructor
	CHRatingDif();
	CHRatingDif(const short id);
	CHRatingDif(const CHRatingDif & copy);	
	virtual ~CHRatingDif();

	/**** Virtual operators inherited from GData ********************/
	GData& operator= (const GData& copy);
	bool   operator==(const GData& copy);
	bool   operator!=(const GData& copy);

	/**** Virtual methods inherited from GData **********************/
	MSLPack& pack  (MSLPack& pck) const;
	MSLPack& unpack(MSLPack& pck);

	QBase* onQ() const;
	UBase* onU() const;

	// Key Method
	void setKey();

	// Set Methods
	void setCode(const short value);
	void setDifference(const short value);
	void setProbability(const short value);
	
	// Get Methods
	short getCode() const;
	short getDifference() const;
	short getProbability() const;
		
	// Help Methods
	float getProbabilityCode(bool positive=true);
	MSLString getProbabilityCodeStr();


private:
	short m_code;
	short m_difference;
	short m_probability;
};

