/*************************************************************************************
*			© Copyright MSL Software, S.L., 2001
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:UCHSession.cpp
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

#include "stdCHMngt.h"
#include "UCHSession.h"
#include "CHSession.h"

// *****************************************************************************

void UCHSession::OnAssignAttributes(GTHSession &aSession)
{
	UGTHSession::OnAssignAttributes(aSession);

	nullfdescription = true;
	if( ((CHSession &)aSession).getDescription() != NULLRWSTRING )
	{
		fdescription    = ((CHSession &)aSession).getDescription();
		nullfdescription = false;
	}

	nullAcumSess=true;
	if( ((CHSession &)aSession).getAcumulatSess() != 0)
	{
		acumSess    = ((CHSession &)aSession).getAcumulatSess();
		nullAcumSess = false;
	}
}

// *****************************************************************************

void UCHSession::OnInsert(RWDBInserter& aInsert,GTHSession &aSession)
{
	UGTHSession::OnInsert(aInsert,aSession);

	CHSession *pSession=(CHSession*)&aSession;

	aInsert["NAME"]		<< RWDBBoundExpr(&fdescription,&nullfdescription);
	aInsert["ACUM_SESS"]<< RWDBBoundExpr(&acumSess,&nullAcumSess);
	aInsert["STATUS"]<< pSession->getStatus();
}

// *****************************************************************************
void UCHSession::OnUpdate(RWDBUpdater& aUpdater,RWDBTable& t011session,GTHSession& aSession)
{
	UGTHSession::OnUpdate(aUpdater,t011session,aSession);

	CHSession *pSession=(CHSession*)&aSession;

	aUpdater << t011session["NAME"].assign(RWDBBoundExpr(&fdescription,&nullfdescription));
	aUpdater << t011session["ACUM_SESS"].assign(RWDBBoundExpr(&acumSess,&nullAcumSess));
	aUpdater << t011session["STATUS"].assign(pSession->getStatus());
}

// *****************************************************************************

void UCHSession::OnDelete(const GTHSession &aSession)
{
	UGTHSession::OnDelete(aSession);
}
