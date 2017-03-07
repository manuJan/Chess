/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : UCHMatchJudge.h                                                                 
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


#ifndef _UCHMatchJudge_H
#define _UCHMatchJudge_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <core/TH/GTHMatchJudge.h>
#include <core/TH/UGTHMatchJudge.h>

#include "CHMatchJudge.h"

#ifndef _CHMNGTMODELDLL_H
#   include "CHMngtModelDll.h" 
#endif // _CH_MNGTMODELDLL_H

class CHModelExport UCHMatchJudge : public UGTHMatchJudge
{

public:
	UCHMatchJudge(RWDBConnection *pNewConnection)
		:UGTHMatchJudge(pNewConnection)
		{;}
	virtual ~UCHMatchJudge(){}


private:
	
	void OnAssignAttributes(GTHMatchJudge& aMatchJudge);
	void OnInsert(RWDBInserter& aInserter,GTHMatchJudge& aMatchJudge);
	void OnUpdate(RWDBUpdater& aUpdater,RWDBTable& t013matchJudge,GTHMatchJudge& aMatchJudge);

};

#endif //!defined(AFX_UCHMatchJudge_H)