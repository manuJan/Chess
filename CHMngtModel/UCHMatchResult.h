/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : UCHMatchResult.h
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

#if !defined(AFX_UCHMATCHRESULT_H__4A4ECD3F_EB8A_401D_A6D4_A16FCC045809__INCLUDED_)
#define AFX_UCHMATCHRESULT_H__4A4ECD3F_EB8A_401D_A6D4_A16FCC045809__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Core/TH/UGTHMatchResult.h>

class UCHMatchResult : public UGTHMatchResult  
{
public:
	UCHMatchResult(RWDBConnection *pNewConnection);
	virtual ~UCHMatchResult();

protected:
	void OnAssignAttributes(GTHMatchResult& aMatchResult);
	void OnInsert(RWDBInserter& aInserter,GTHMatchResult& aMatchResult);
	void OnUpdate(RWDBUpdater& aUpdater,RWDBTable& t009matchResult,GTHMatchResult& aMatchResult);
	void OnDelete(const GTHMatchResult& aMatchResult);

private:
	float fPoints;
	short fSubMatch;	
};

#endif // !defined(AFX_UCHMATCHRESULT_H__4A4ECD3F_EB8A_401D_A6D4_A16FCC045809__INCLUDED_)
