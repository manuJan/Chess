/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : VCHCheckList.cpp
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
#include "stdVCH.h"
#include "VCHCheckList.h"

#include "CHCheckList.h"
#include <SPORTS/CH/Data/CHRegister.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
VCHCheckList::VCHCheckList(const char *group,VCheckList::CheckMode mode)
:VCheckList(group,mode)
{
}

VCHCheckList::~VCHCheckList()
{

}

GCheckList * VCHCheckList::OnCreate(GRegister *pRegister)
{
	if (pRegister->getType()==GRegister::individual &&
		(!pRegister->getFlagRecord() ||
		  pRegister->getFlagCompetitor()))
	{
		CHCheckList* p = new CHCheckList(pRegister,true);
		return p;
	}

	return 0;
}

GCheckList * VCHCheckList::OnCreate(GRegister *pRegister,GInscription *pInscription)
{
	if (pRegister->getType()==GRegister::individual && 
		(!pRegister->getFlagRecord() ||
		 pRegister->getFlagCompetitor()))
	{
		CHCheckList* p = new CHCheckList(pRegister,true);
		return p;
	}

	return 0;
	UNREFERENCED_PARAMETER(pInscription);
}
