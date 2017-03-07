/*************************************************************************************
*	© Copyright MSL Software, S.L., 2001
*
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior wriCHen permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:UCHMatchMember.cpp
*	Description	:Updater Chess MatchMember
*
*	Author		:Chess Team
*	Date created:13-12-2005
* 	Project		:CH Model
*
***************************************************************************************/

#include "stdCHMngt.h"
#include "CHMatchMember.h"
#include "UCHMatchMember.h"
#include "CHMatch.h"

void UCHMatchMember::OnAssignAttributes(GTHMatchMember& aMatchMember)
{
	UGTHMatchMember::OnAssignAttributes(aMatchMember);

	CHMatch *pMatch=(CHMatch *)aMatchMember.getMatchResult()->getMatch();

	fSubMatch = pMatch->getSubMatch();
}

void UCHMatchMember::OnInsert(RWDBInserter& aInsert,GTHMatchMember& aMatchMember)
{
	UGTHMatchMember::OnInsert(aInsert,aMatchMember);
	aInsert["IDSUBMATCH"]		  << fSubMatch;
}

void UCHMatchMember::OnUpdate(RWDBUpdater& aUpdate,RWDBTable& table,GTHMatchMember& aMatchMember)
{
	UGTHMatchMember::OnUpdate(aUpdate,table,aMatchMember);
}

void UCHMatchMember::OnDelete(RWDBDeleter& aDelete,RWDBTable& table,GTHMatchMember& aMatchMember)
{
	UGTHMatchMember::OnDelete(aDelete,table,aMatchMember);
}


