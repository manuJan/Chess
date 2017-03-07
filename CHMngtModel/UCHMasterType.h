/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:UCHMasterType.h
*	Description	:
*
*	Author		:Chess Team
*	Date created:09-12-2005
* 	Project		:Ches Management Model DLL
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#if !defined(AFX_UCHMasterType_H__EC659569_DDDE_413E_AA76_54B9A464DF99__INCLUDED_)
#define AFX_UCHMasterType_H__EC659569_DDDE_413E_AA76_54B9A464DF99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <CORE/G/UBase.h>

class UCHMasterType : public UBase  
{
public:
	UCHMasterType(RWDBConnection *pNewConnection):UBase(pNewConnection) {;}
	virtual ~UCHMasterType() {;}
	
	void assignAtributes(CHMasterType& aMasterType);

protected:
	RWBoolean insert (RWDBConnection& aConnection,GData& aData);
	RWBoolean update (RWDBConnection& aConnection,GData& aData);
	RWBoolean delete_(RWDBConnection& aConnection,GData& aData);

private:
	short order;
	RWDBNullIndicator nullorder;

};

#endif // !defined(AFX_UCHMasterType_H__EC659569_DDDE_413E_AA76_54B9A464DF99__INCLUDED_)
