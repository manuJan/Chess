/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : UCHSplitMatchResult.h                                                                 
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:13-12-2005
*   Project     :CH Model
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///


#ifndef _UCHSplitMatchResult_H
#define _UCHSplitMatchResult_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <core/TH/UGTHSplitMatchResult.h>
#include "CHSplitMatchResult.h"

#ifndef _CHMNGTMODELDLL_H
#   include "CHMngtModelDll.h" 
#endif // _CH_MNGTMODELDLL_H

class CHModelExport UCHSplitMatchResult : public UGTHSplitMatchResult
{
public:
	UCHSplitMatchResult(RWDBConnection *pNewConnection)
		:UGTHSplitMatchResult(pNewConnection)
		{;}
	virtual ~UCHSplitMatchResult(){}

protected:	
	void OnAssignAttributes(GTHSplitMatchResult& aSplitMatchResult);
	void OnInsert(RWDBInserter& aInserter, GTHSplitMatchResult& aSplitMatchResult);
	RWBoolean OnUpdate(RWDBUpdater& aUpdater,RWDBTable& xx006SplitMatchResult, GTHSplitMatchResult& aSplitMatchResult);
	void OnDelete(const GTHSplitMatchResult& aSplitMatchResult);
	
};

#endif //!defined(AFX_UCHSplitMatchResult_H)