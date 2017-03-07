/*************************************************************************************
*			© Copyright MSL Software, S.L., 2001
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:UCHSession.h
*	Description	:
*
*   Author      :Chess Team
*   Date created:12-12-2005
*   Project     :CH Model
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#if !defined(AFX_UCHSESSION_H__83A123AB_B920_4D7A_9578_31444B2030BA__INCLUDED_)
#define AFX_UCHSESSION_H__83A123AB_B920_4D7A_9578_31444B2030BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <core\TH\UGTHSession.h>

class UCHSession : public UGTHSession  
{
public:
		// CONSTRUCTORES Y DESTRUCTORES
	UCHSession(RWDBConnection *pNewConnection)
		:UGTHSession(pNewConnection)
	{ ; }

	virtual ~UCHSession()
	{ ; }

protected:
	void OnAssignAttributes(GTHSession &aSession);
	void OnInsert(RWDBInserter& aInserter,GTHSession& aSession);
	void OnUpdate(RWDBUpdater& aUpdater,RWDBTable& t011session,GTHSession& aSession);
	void OnDelete(const GTHSession &aSession);

private:
	RWCString fdescription;
	short acumSess;
	RWDBNullIndicator nullfdescription,nullAcumSess;
};

#endif // !defined(AFX_UCHSESSION_H__83A123AB_B920_4D7A_9578_31444B2030BA__INCLUDED_)
