/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : UCHPhase.h
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

#if !defined(AFX_UCHPHASE_H__9C008000_6870_4A13_9885_F5C3E375938F__INCLUDED_)
#define AFX_UCHPHASE_H__9C008000_6870_4A13_9885_F5C3E375938F__INCLUDED_

#ifndef _UCHPhase_H
#define _UCHPhase_H
#endif

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Core/TH/UGTHPhase.h>

class UCHPhase : public UGTHPhase  
{
public:
	UCHPhase(RWDBConnection *pNewConnection);
	virtual ~UCHPhase();

protected:
	void OnAssignAttributes(const GPhase& aPhase);
	void OnInsert(RWDBInserter& aInsert,const GPhase& aPhase);
	void OnUpdate(RWDBUpdater& aUpdate,RWDBTable& table,const GPhase& aPhase);
	void OnDelete(RWDBDeleter& aDelete,RWDBTable& table,const GPhase& aPhase);

	short typePhase,idTeamMatchsCnfg;
};

#endif // !defined(AFX_UCHPHASE_H__9C008000_6870_4A13_9885_F5C3E375938F__INCLUDED_)
