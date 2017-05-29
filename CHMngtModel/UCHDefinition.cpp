/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:UARDefinition.h
*	Description	:
*
*	Author		: Javier Juste
*	Date created: 05 Junio 2008
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
#include "UCHDefinition.h"

void UCHDefinition::OnUpdate(MSLDBUpdater & aUpdater ,MSLDBTable& table,const GDefinition& aDefinition)
{
	CHDefinition & aCHDefinition = (CHDefinition &)aDefinition;

	aUpdater << table["AUTO_PROG"].assign( aCHDefinition.getAutoProg());
}
