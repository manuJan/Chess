/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: UCHDefinition.h
*	Description	:
*
*	Author		: Javier Juste
*	Date created: 03 Junio 2008
* 	Project		: Archery DLL
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#pragma once
#include <OVR/CORE/G/UDefinition.h>

class UCHDefinition : public UDefinition  
{
public:

	UCHDefinition():UDefinition()
	{;}

	~UCHDefinition() 
	{;}

protected:

	void OnUpdate(MSLDBUpdater & aUpdater ,MSLDBTable& table,const GDefinition& aDefinition);
};
