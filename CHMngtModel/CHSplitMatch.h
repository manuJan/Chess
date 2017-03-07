/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHSplitMatch.h                                                                 
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


#ifndef _CHSplitMatch_H
#define _CHSplitMatch_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef _CHMNGTMODELDLL_H
#   include "CHMngtModelDll.h" 
#endif // _CH_MNGTMODELDLL_H

#include <core/THSP/GTHSplitMatch.h>


class CHModelExport CHSplitMatch : public GTHSplitMatch
{
	RWDECLARE_COLLECTABLE(CHSplitMatch)

	
public:

	//Construction/Destruction
	CHSplitMatch();
	CHSplitMatch(const CHSplitMatch & copy);
	CHSplitMatch(CPack& aPack);
	virtual ~CHSplitMatch();


	//Operators
	RWBoolean		operator !=(const CHSplitMatch & copy);
	RWBoolean		operator ==(const CHSplitMatch & copy);
	CHSplitMatch&	operator =(const CHSplitMatch & copy);


	//From GData
	RWBoolean		uSQL(RWDBConnection& pConnect,RWBoolean remove=false);
	CPack&			pack(CPack &iPack);
	CPack&			unpack(CPack &iPack);
	RWCString		msl() const;
	RWCString		mslDescription(const char *language) const;


};

#endif //!defined(AFX_CHSplitMatch_H)