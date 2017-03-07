/*************************************************************************************
*	© Copyright MSL Software, S.L., 2001
*
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior wriCHen permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:UCHMatchMember.h
*	Description	:Updater Chess MatchMember
*
*	Author		:Chess Team
*	Date created:13-12-2005
* 	Project		:CH Model
*
***************************************************************************************/

#if !defined(AFX_UCHMATCHMEMBER_H__85EA4746_ACBA_4648_B3EA_21C6131DA949__INCLUDED_)
#define AFX_UCHMATCHMEMBER_H__85EA4746_ACBA_4648_B3EA_21C6131DA949__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <CORE/TH/UGTHMatchMember.h>

class UCHMatchMember : public UGTHMatchMember  
{
public:
	UCHMatchMember(RWDBConnection *pNewConnection)
	:UGTHMatchMember(pNewConnection) 
	,fSubMatch(0)
	{ ; } 
	virtual ~UCHMatchMember()
	{ ; }


protected:
	void OnAssignAttributes(GTHMatchMember& aMatchMember);
	void OnInsert(RWDBInserter& aInsert,GTHMatchMember& aMatchMember);
	void OnUpdate(RWDBUpdater& aUpdate,RWDBTable& table,GTHMatchMember& aMatchMember);
	void OnDelete(RWDBDeleter& aDelete,RWDBTable& table,GTHMatchMember& aMatchMember);
private:
	short fSubMatch;
	
};

#endif // !defined(AFX_UCHMATCHMEMBER_H__85EA4746_ACBA_4648_B3EA_21C6131DA949__INCLUDED_)
