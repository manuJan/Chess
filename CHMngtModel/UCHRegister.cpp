/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : UCHMatch.cpp
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

#include "stdCHMngt.h"
#include "UCHRegister.h"
#include "CHRegister.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void UCHRegister::OnAssignAttributes(GRegister& aRegister)
{
	CHRegister & aCHRegister = (CHRegister&)aRegister;

	masterType		= aCHRegister.getMasterTypeCode();
	nullMasterType	= (masterType==0);
}

void UCHRegister::OnInsert(MSLDBInserter& aInserter,MSLDBTable& table,GRegister& aRegister)
{
	UNREFERENCED_PARAMETER(aRegister);

	aInserter << table["MASTER_TYPE"].assign( masterType,&nullMasterType);	
}

void UCHRegister::OnUpdate(MSLDBUpdater& aUpdater,MSLDBTable& z010register,GRegister& aRegister)
{
	UNREFERENCED_PARAMETER(aRegister);

	aUpdater << z010register["MASTER_TYPE"].assign( masterType,&nullMasterType);	
}

