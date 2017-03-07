/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : UCHSplitMatch.h                                                                 
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


#ifndef _UCHSplitMatch_H
#define _UCHSplitMatch_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <core/THSP/UGTHSplitMatch.h>
#include "CHSplitMatch.h"

#ifndef _CHMNGTMODELDLL_H
#   include "CHMngtModelDll.h" 
#endif // _CH_MNGTMODELDLL_H

class CHModelExport UCHSplitMatch : public UGTHSplitMatch
{

public:

	UCHSplitMatch(RWDBConnection *pNewConnection)
		:UGTHSplitMatch(pNewConnection)
		{;}
	virtual ~UCHSplitMatch(){}


private:
	
	void OnAssignAttributes(GTHSplitMatch& aSplitMatch);
	void OnInsert(RWDBInserter& aInserter,GTHSplitMatch& aSplitMatch);
	void OnUpdate(RWDBUpdater& aUpdater,RWDBTable& table,GTHSplitMatch& aSplitMatch);

};

#endif //!defined(AFX_UCHSplitMatch_H)