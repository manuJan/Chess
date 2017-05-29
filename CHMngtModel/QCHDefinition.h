/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:QCHDefinition.h
*	Description	:
*
*	Author		: Javier Juste
*	Date created: 03 Junio 2008
* 	Project		: Chess DLL
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#pragma once
#include <OVR/CORE/TH/QGTHDefinition.h>

class QCHDefinition : public QGTHDefinition
{
public:	
	QCHDefinition()
		:QGTHDefinition()
	{;}
	virtual ~QCHDefinition()
	{;}

protected:

	void OnSelect(MSLDBSelector& aSelect,MSLDBTable& tDefinition);
	void OnReader(MSLDBReader& aReader  ,GDefinition *pDefinition);
};
