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

#if !defined(AFX_UCHCOURT_H__9D6124C7_88CA_4B7C_9C93_B322C4873D63__INCLUDED_)
#define AFX_UCHCOURT_H__9D6124C7_88CA_4B7C_9C93_B322C4873D63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <CORE/G/UCourt.h>

class UCHCourt : public UCourt  
{
public:
	UCHCourt(RWDBConnection *pNewConnection)
	:UCourt(pNewConnection) 
	{ ; } 
	virtual ~UCHCourt()
	{ ; }

protected:
	void OnAssignAttributes(const GCourt& aCourt);
	void OnInsert(RWDBInserter& aInsert,const GCourt& aCourt);
	RWBoolean OnUpdate(RWDBUpdater& aUpdate,RWDBTable& table,const GCourt& aCourt);
	void OnDelete(RWDBDeleter& aDelete,RWDBTable& table,const GCourt& aCourt);

private:
	short order;
	
};

#endif // !defined(AFX_UCHCOURT_H__9D6124C7_88CA_4B7C_9C93_B322C4873D63__INCLUDED_)
