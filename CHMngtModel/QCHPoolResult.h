/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : QCHPoolResult.h                                                                 
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


#ifndef _QCHPoolResult_H
#define _QCHPoolResult_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <core/G/QBase.h>
#include <core/TH/QGTHPoolResult.h>

#include "CHPoolResult.h"


class CHModelExport QCHPoolResult : public QGTHPoolResult
{
public:
	QCHPoolResult(RWDBConnection *pNewConnection)
	:QGTHPoolResult(pNewConnection)
	{;}

	virtual ~QCHPoolResult() {;}

protected:
	void OnSelect(RWDBSelector& aSelect,RWDBTable& table);
	void OnReader(RWDBReader& aReader,GTHPoolResult *pPoolResult);
	GTHPoolResult * OnNewPoolResult();
};

#endif //!defined(AFX_QCHPoolResult_H)