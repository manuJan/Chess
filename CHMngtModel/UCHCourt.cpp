/*************************************************************************************
*	© Copyright MSL Software, S.L., 2001
*
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:UCHCourt.cpp
*	Description	:Updater Chess
*
*	Author		:Chess Team
*	Date created:12-12-2005
* 	Project		:CH Model
*
***************************************************************************************/

#include "stdCHMngt.h"
#include "CHCourt.h"
#include "UCHCourt.h"

void UCHCourt::OnAssignAttributes(const GCourt& aCourt)
{
	order	= ((CHCourt&)aCourt).getOrder();
}

void UCHCourt::OnInsert(RWDBInserter& aInsert,const GCourt& aCourt)
{
	aInsert["NORDER"]	<< RWDBBoundExpr(&order);
	
	UNREFERENCED_PARAMETER(aCourt);
}

RWBoolean UCHCourt::OnUpdate(RWDBUpdater& aUpdate,RWDBTable& table,const GCourt& aCourt)
{
	aUpdate << table["NORDER"]	.assign(order);
	
	UNREFERENCED_PARAMETER(aCourt);
	return true; 
}

void UCHCourt::OnDelete(RWDBDeleter& aDelete,RWDBTable& table,const GCourt& aCourt)
{
	UNREFERENCED_PARAMETER(aDelete);
	UNREFERENCED_PARAMETER(table);
	UNREFERENCED_PARAMETER(aCourt);
}

