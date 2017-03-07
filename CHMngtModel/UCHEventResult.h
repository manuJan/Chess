/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : UCHEventResult.h                                                                 
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


#ifndef _UCHEventResult_H
#define _UCHEventResult_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <core/TH/UGTHEventResult.h>
#include "CHEventResult.h"

class UCHEventResult : public UGTHEventResult
{

public:

	UCHEventResult(RWDBConnection *pNewConnection)
		:UGTHEventResult(pNewConnection)
		{;}
	virtual ~UCHEventResult(){}


private:
	
	RWCString qualitative;
	short     rating;	
	
	RWDBNullIndicator nullqualitative,nullRating;
	
	void OnAssignAttributes(const GTHEventResult& aEventResult);
	void OnInsert(RWDBInserter& aInserter,const GTHEventResult& aEventResult);
	void OnUpdate(RWDBUpdater& aUpdater,RWDBTable& t015EvRes,const GTHEventResult& aEventResult);
};

#endif //!defined(AFX_UCHEventResult_H)