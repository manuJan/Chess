/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:UCHRatingDif.h
*	Description	:
*
*	Author		:Chess Team
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
#include <OVR/CORE/G/UBase.h>
#include "CHRatingDif.h"

class UCHRatingDif : public UBase
{

public:
	UCHRatingDif()
		:UBase()
	{;}
	virtual ~UCHRatingDif()
	{;}

protected:
	bool insert (GData& aData);
	bool update (GData& aData);	
	bool delete_(GData& aData);

	void assignAtributes(CHRatingDif& aEnd);

private:
	short code,probability,difference;
	MSLDBNullIndicator nullprobability,nulldifference;

};

