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


#ifndef _CHSplitMatchResult_H
#define _CHSplitMatchResult_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef _CHMNGTMODELDLL_H
#   include "CHMngtModelDll.h" 
#endif // _CH_MNGTMODELDLL_H

#include <core/TH/GTHSplitMatchResult.h>
#include "CHSplitMatch.h"


class CHModelExport CHSplitMatchResult : public GTHSplitMatchResult
{

	RWDECLARE_COLLECTABLE(CHSplitMatchResult)

public:

	//Construction/Destruction
	CHSplitMatchResult();
	CHSplitMatchResult(GTHMatchResult* aMatchResult, short aSplit);
	CHSplitMatchResult(const CHSplitMatchResult & copy);
	CHSplitMatchResult(CPack& aPack);
	virtual ~CHSplitMatchResult();


	//Operators
	RWBoolean			operator !=(const CHSplitMatchResult & copy);
	RWBoolean			operator ==(const CHSplitMatchResult & copy);
	CHSplitMatchResult& operator =(const CHSplitMatchResult & copy);


	//From GData
	RWBoolean			uSQL(RWDBConnection& pConnect,RWBoolean remove=false);
	CPack&				pack(CPack &iPack);
	CPack&				unpack(CPack &iPack);
	RWCString			msl() const;
	RWCString			mslDescription(const char *language) const;
	
	
	CHSplitMatch *		getSplitMatch() const;
	unsigned char		getSplitMatchStatus()const;
	CHSplitMatchResult *getSplitMatchResultVersus();


};
CHModelExport CPack& operator << (CPack& aPack, CHSplitMatchResult * pSplitMatchResult);
CHModelExport CPack& operator >> (CPack& aPack, CHSplitMatchResult ** pSplitMatchResult);

#endif //!defined(AFX_CHSplitMatchResult_H)
