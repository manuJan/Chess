/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : QCHEventResult.h                                                                 
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


#ifndef _QCHEventResult_H
#define _QCHEventResult_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <core/G/QBase.h>
#include <core/TH/QGTHEventResult.h>

#include "CHEventResult.h"


class CHModelExport QCHEventResult : public QGTHEventResult
{

public:

	QCHEventResult(RWDBConnection *pNewConnection)
	:QGTHEventResult(pNewConnection)
	{;}

	virtual ~QCHEventResult() {;}

protected:
	void OnSelect(RWDBSelector& aSelect,RWDBTable& tPool);
	void OnReader(RWDBReader& aReader,GTHEventResult *pEventResult);
	GTHEventResult * OnNewEventResult();

};

#endif //!defined(AFX_QCHEventResult_H)