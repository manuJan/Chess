/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHSplitMatchResult.h                                                                 
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

#pragma once
#include "CHMemoryDataBaseDefs.h"
#include <OVR\core\TH\GTHSplitMatchResult.h>

class CHMngtModelExport CHSplitMatchResult : public GTHSplitMatchResult
{

	MSLDECLARE_ITEM(CHSplitMatchResult)

public:

	//Construction/Destruction
	CHSplitMatchResult();
	CHSplitMatchResult(GTHMatchResult* aMatchResult, short aSplit);
	CHSplitMatchResult(const CHSplitMatchResult & copy);
	virtual ~CHSplitMatchResult();
		
	CHSplitMatchResult *getSplitMatchResultVersus();
};
