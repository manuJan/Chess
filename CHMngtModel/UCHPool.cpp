/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : UCHPool.cpp                                                                 
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
#include "UCHPool.h"

void UCHPool::OnInsert(RWDBInserter& aInserter,GTHPool& aPool)
{
	UTHSPPool::OnInsert(aInserter,aPool);

}

void UCHPool::OnUpdate(RWDBUpdater& aUpdater,RWDBTable& t005pool,GTHPool& aPool)
{
	UTHSPPool::OnUpdate(aUpdater,t005pool,aPool);

}

void UCHPool::OnDelete(const GTHPool& aPool)
{

	UTHSPPool::OnDelete(aPool);
}