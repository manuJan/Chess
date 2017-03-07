/*************************************************************************************
*	© Copyright MSL Software, S.L., 2001
*
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior wriCHen permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:QCHMatchMember.h
*	Description	:Query Chess MatchMember
*
*	Author		:Chess Team
*	Date created:13-12-2005
* 	Project		:CH Model
*
***************************************************************************************/

#include "stdCHMngt.h"
#include "QCHMatchMember.h"


void QCHMatchMember::OnSelect(RWDBSelector& aSelect,RWDBTable& tMatchMember)
{
	QGTHMatchMember::OnSelect(aSelect,tMatchMember);
}

void QCHMatchMember::OnReader(RWDBReader& aReader,GTHMatchMember *pMatchMember)
{
	QGTHMatchMember::OnReader(aReader,pMatchMember);
}

