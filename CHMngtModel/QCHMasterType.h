/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:QCHMasterType.h
*	Description	:
*
*	Author		:CH Team
*	Date created:09-12-2005
* 	Project		:Chess Management Model DLL
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#if !defined(AFX_QCHMasterType_H__BA4FBA08_3EB9_457A_8072_F24F2A98A6CC__INCLUDED_)
#define AFX_QCHMasterType_H__BA4FBA08_3EB9_457A_8072_F24F2A98A6CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <CORE/G/QBase.h>

class QCHMasterType : public QBase  
{
public:
	QCHMasterType(RWDBConnection *pNewConnection):QBase(pNewConnection) {;}
	virtual ~QCHMasterType() {;}

protected:
	size_t selectCollection(RWDBConnection& aConnection,RWCollection& target);
};

#endif // !defined(AFX_QCHMasterType_H__BA4FBA08_3EB9_457A_8072_F24F2A98A6CC__INCLUDED_)
