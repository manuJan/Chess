/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHSplitMatchResult.cpp                                                                 
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


#include "stdCHMngt.h"
#include "CHSplitMatchResult.h"
#include "CHMatchResult.h"
#include <ovr/core/G/GBuffer.h>

MSLDEFINE_ITEM(CHSplitMatchResult, __CHSPLITMATCHRESULT)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHSplitMatchResult::CHSplitMatchResult()
:GTHSplitMatchResult()
{
}

CHSplitMatchResult::CHSplitMatchResult(GTHMatchResult* aMatchResult, short aSplit)
:GTHSplitMatchResult(aMatchResult, aSplit)
{
}

CHSplitMatchResult::CHSplitMatchResult(const CHSplitMatchResult & copy)
{
	operator=(copy);
}


CHSplitMatchResult::~CHSplitMatchResult()
{
}


CHSplitMatchResult *CHSplitMatchResult::getSplitMatchResultVersus()
{
	CHMatchResult *pMatchResultVersus=((CHMatchResult*)getMatchResult())->getMatchResultVersus();
	if(pMatchResultVersus)
		return (CHSplitMatchResult*)pMatchResultVersus->getSplitMatchResult(getSplit()-1);
	
	return 0;
}

