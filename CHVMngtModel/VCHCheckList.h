/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : VCHCheckList.h
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:19-12-2005
*   Project     :CHV Model               
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///
#if !defined(AFX_VCHCHECKLIST_H__342BF61B_AF74_4829_805E_395767B7C2AC__INCLUDED_)
#define AFX_VCHCHECKLIST_H__342BF61B_AF74_4829_805E_395767B7C2AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHVMNGT_DLL
	#include "CHVMngtModelDll.h"
#endif // _CHVMNGT_DLL

#include <REPORTS/V/VCheckList.h>
class CHInscription;
class VCHCheckList : public VCheckList  
{
public:
	VCHCheckList(const char *group,VCheckList::CheckMode mode);
	virtual ~VCHCheckList();

	GCheckList * OnCreate(GRegister *pRegister);
	GCheckList * OnCreate(GRegister *pRegister,GInscription *pInscription);
};

#endif // !defined(AFX_VCHCHECKLIST_H__342BF61B_AF74_4829_805E_395767B7C2AC__INCLUDED_)
