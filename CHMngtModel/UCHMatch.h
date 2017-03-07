/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : UCHMatch.h
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:07-12-2005
*   Project     :CH Model
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///

#if !defined(AFX_UCHMATCH_H__91823F8A_4F93_4A2F_AC04_A63E8BE1F9EA__INCLUDED_)
#define AFX_UCHMATCH_H__91823F8A_4F93_4A2F_AC04_A63E8BE1F9EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Core\THSP\UTHSPMatch.h>

class UCHMatch : public UTHSPMatch  
{
public:
	UCHMatch(RWDBConnection *pNewConnection);
	virtual ~UCHMatch();

protected:
	void OnAssignAttributes(GTHMatch& aMatch);
	void OnInsert(RWDBInserter& aInserter,GTHMatch& aMatch);
	void OnUpdate(RWDBUpdater& aUpdater,RWDBTable& t008match,GTHMatch& aMatch);
	void OnDelete(const GTHMatch& aMatch);

private:
	short session;
	short court;
	short fSubMatch,fMatchType,fRound;
	RWCString rVenue;

	RWDBNullIndicator nullSession ;
	RWDBNullIndicator nullCourt;
	RWDBNullIndicator nullVenue;
	RWDBNullIndicator nullRound;
};

#endif // !defined(AFX_UCHMATCH_H__91823F8A_4F93_4A2F_AC04_A63E8BE1F9EA__INCLUDED_)
