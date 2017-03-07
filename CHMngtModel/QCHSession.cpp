/*************************************************************************************
*			© Copyright MSL Software, S.L., 2001
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:QCHSession.cpp
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
#include "CHSession.h"
#include "QCHSession.h"

// *****************************************************************************

void QCHSession::OnSelect(RWDBSelector& aSelect,RWDBTable& tSession)
{
	QGTHSession::OnSelect(aSelect,tSession);

	aSelect << tSession["NAME"];
	aSelect << tSession["ACUM_SESS"];
	aSelect << tSession["STATUS"];

}

// *****************************************************************************

void QCHSession::OnReader(RWDBReader& aReader,GTHSession *pSession)
{
	QGTHSession::OnReader(aReader,pSession);

	RWCString fdescription;
	short acumSess,fStatus;
	RWDBNullIndicator nullfdescription,nullAcumSess;

	aReader >> nullfdescription >> fdescription
			>> nullAcumSess		>> acumSess
			>> fStatus
			;

	if (nullfdescription)
		((CHSession *)pSession)->setDescription(NULLRWSTRING);
	else
		((CHSession *)pSession)->setDescription(fdescription);

	if (nullAcumSess)
		((CHSession *)pSession)->setAcumulatSess(0);
	else
		((CHSession *)pSession)->setAcumulatSess(acumSess);

	((CHSession *)pSession)->setStatus(unsigned char(fStatus));


}

GTHSession * QCHSession::OnNewSession()	
{
	return new CHSession; 
}
