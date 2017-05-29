/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:QCHDefinition.cpp
*	Description	:
*
*	Author		: Javier Juste
*	Date created: 3 Junio 2008
* 	Project		: Archery DLL
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "StdCHMngt.h"
#include "CHDefinition.h"
#include "QCHDefinition.h"

void QCHDefinition::OnSelect(MSLDBSelector& aSelect,MSLDBTable& tDefinition)
{
	// Query data
	aSelect << tDefinition["AUTO_PROG"];
}

void QCHDefinition::OnReader(MSLDBReader& aReader  ,GDefinition *pDefinition)
{
	CHDefinition * aDefinition = (CHDefinition*)pDefinition;

	short fAutoProg;

	aReader >> fAutoProg;

	aDefinition->setAutoProg(fAutoProg!=0);	
}
