/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : UCHRegister.h
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

#if !defined(AFX_UCHREGISTER_H__97D444AB_57D2_47D0_B413_A5D69E738EDB__INCLUDED_)
#define AFX_UCHREGISTER_H__97D444AB_57D2_47D0_B413_A5D69E738EDB__INCLUDED_

#ifndef _UCHRegister_H
#define _UCHRegister_H
#endif

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <CORE/G/URegister.h>
class CHRegister;
class UCHRegister : public URegister  
{
public:
	UCHRegister(RWDBConnection *pNewConnection);
	virtual ~UCHRegister();

private:
	void OnAssignAttributes(GRegister& aRegister);
	void OnInsert(RWDBInserter& aInserter,GRegister& aRegister);
	void OnUpdate(RWDBUpdater& aUpdater,RWDBTable& z010register,GRegister& aRegister);

private:
	short masterType;
	
	RWDBNullIndicator nullMasterType;

};

#endif // !defined(AFX_UCHREGISTER_H__97D444AB_57D2_47D0_B413_A5D69E738EDB__INCLUDED_)
