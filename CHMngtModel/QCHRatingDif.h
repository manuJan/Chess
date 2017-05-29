/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:QCHRatingDif.h
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
#include <OVR/CORE/G/QBase.h>

class QCHRatingDif : public QBase  
{
public:
	QCHRatingDif()
		:QBase() 
	{;}
	virtual ~QCHRatingDif()
	{;}

protected:

	size_t selectCollection(MSLCollection& target);
};

