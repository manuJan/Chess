/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : QCHRegister.cpp
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
#include "QCHRegister.h"
#include "CHRegister.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

QCHRegister::QCHRegister(RWDBConnection *pNewConnection)
:QRegister(pNewConnection)
{
}

QCHRegister::~QCHRegister()
{
}

GRegister *QCHRegister::OnNewRegister()
{ 
	return new CHRegister();
}

void QCHRegister::OnSelect(RWDBSelector& aSelect,RWDBTable& z010register)
{
	aSelect<< z010register["MASTER_TYPE"];
	
}

void QCHRegister::OnReader(RWDBReader& aReader,GRegister *pRegister)
{
	CHRegister * pCHRegister=(CHRegister*)pRegister;

	RWDBNullIndicator nullMasterType;
	
	short masterType;

	aReader >> nullMasterType >> masterType;
	
		
	if( nullMasterType)
		masterType=0;

	
	pCHRegister->setMasterType(masterType);
}

