/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : QCHPool.cpp                                                                 
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:12-12-2005
*   Project     :CH Model
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///


#include "stdCHMngt.h"
#include "QCHPool.h"
#include "CHPool.h"


void QCHPool::OnSelect(RWDBSelector& aSelect,RWDBTable& table)
{
	QGTHPool::OnSelect(aSelect,table);
}

void QCHPool::OnReader(RWDBReader& aReader,GTHPool *pValue)
{
	QGTHPool::OnReader(aReader,pValue);

}

GTHPool * QCHPool::OnNewPool()
{
	return new CHPool();
}