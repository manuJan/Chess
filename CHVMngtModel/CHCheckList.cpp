/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHCheckList.cpp
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
#include "CHCheckList.h"
#include <Sports/CH/Data/CHInscription.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHCheckList::CHCheckList()
:GCheckList()
{
}

CHCheckList::CHCheckList(GRegister * pReg,RWBoolean bEx/*=false*/)
:GCheckList()
{
	setRegister(pRegister);
	bExtended=bEx;
}

CHCheckList::~CHCheckList()
{
}

void CHCheckList::insertInscription(CHInscription *pInscription)
{
	CHInscription *pInsc=0;
	pInsc=(CHInscription *)vInscriptions.find(pInscription);
	if (pInsc!=pInscription)
		vInscriptions.insert(pInscription);
}

GSortedVector& CHCheckList::getVectorInsc()
{
	return vInscriptions;
}