/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : UCHMember.h
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

#if !defined(AFX_UCHMEMBER_H__3585D853_8CCC_4D1E_8D37_7BF4BBF8B1E9__INCLUDED_)
#define AFX_UCHMEMBER_H__3585D853_8CCC_4D1E_8D37_7BF4BBF8B1E9__INCLUDED_

#ifndef _UCHMember_H
#define _UCHMember_H
#endif

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <CORE/G/UMember.h>

class UCHMember : public UMember  
{
public:
	UCHMember(RWDBConnection *pNewConnection);
	virtual ~UCHMember();

protected:
	void OnAssignAttributes(const GMember& aMember);
	void OnInsert(RWDBInserter& aInsert,const GMember& aMember);
	void OnUpdate(RWDBUpdater& aUpdate,RWDBTable& table,const GMember& aMember);
	void OnDelete(RWDBDeleter& aDelete,RWDBTable& table,const GMember& aMember);

private:
	short function,rating,kConst;
	RWDBNullIndicator nullRating,nullKConst;
};

#endif // !defined(AFX_UCHMEMBER_H__3585D853_8CCC_4D1E_8D37_7BF4BBF8B1E9__INCLUDED_)
