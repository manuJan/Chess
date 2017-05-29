/*************************************************************************************
*	© Copyright MSL Software, S.L., 2001
*
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:UCHCourt.h
*	Description	:Updater Court
*
*	Author		:Chess Team
*	Date created:12-12-2005
* 	Project		:CH Model
*
***************************************************************************************/

#pragma once
#include <OVR/CORE/G/UCourt.h>

class UCHCourt : public UCourt  
{
public:
	UCHCourt()
	:UCourt() 
	{ ; } 

	virtual ~UCHCourt()
	{ ; }

protected:

	void OnAssignAttributes(const GCourt& aCourt);
	void OnInsert(MSLDBInserter& aInserter,MSLDBTable& table,const GCourt& aCourt);
	void OnUpdate(MSLDBUpdater & aUpdater ,MSLDBTable& table,const GCourt& aCourt);
	void OnDelete(const GCourt& aCourt);

private:
	short order;
	
};
