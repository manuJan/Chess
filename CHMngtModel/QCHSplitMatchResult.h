/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : QCHSplitMatchResult.h                                                                 
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


#ifndef _QCHSplitMatchResult_H
#define _QCHSplitMatchResult_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <core/G/QBase.h>
#include <core/TH/QGTHSplitMatchResult.h>

#include "CHSplitMatchResult.h"

#ifndef _CHMNGTMODELDLL_H
#   include "CHMngtModelDll.h" 
#endif // _CH_MNGTMODELDLL_H

class CHModelExport QCHSplitMatchResult : public QGTHSplitMatchResult
{

public:

	QCHSplitMatchResult(RWDBConnection *pNewConnection)
	:QGTHSplitMatchResult(pNewConnection)
	{;}

	virtual ~QCHSplitMatchResult() {;}

protected:
	void OnSelect(RWDBSelector& aSelect,RWDBTable& table);
	void OnReader(RWDBReader& aReader,GTHSplitMatchResult *pSplitMatchResult);
	GTHSplitMatchResult * OnNewSplitMatchResult();

};

#endif //!defined(AFX_QCHSplitMatchResult_H)