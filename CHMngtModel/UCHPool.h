/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : UCHPool.h                                                                 
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


#ifndef _UCHPool_H
#define _UCHPool_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <core/THSP/UTHSPPool.h>

class UCHPool : public UTHSPPool
{

public:

	UCHPool(RWDBConnection *pNewConnection)
		:UTHSPPool(pNewConnection)
		{;}
	virtual ~UCHPool(){}


private:
	
	void OnInsert(RWDBInserter& aInserter,GTHPool& aPool);
	void OnUpdate(RWDBUpdater& aUpdater,RWDBTable& t005pool,GTHPool& aPool);
	void OnDelete(const GTHPool& aPool);

};

#endif //!defined(AFX_UCHPool_H)