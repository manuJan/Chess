/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : QCHPool.h                                                                 
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


#ifndef _QCHPool_H
#define _QCHPool_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <core/G/QBase.h>
#include <core/TH/QGTHPool.h>

#include "CHPool.h"


class CHModelExport QCHPool : public QGTHPool
{

public:

	QCHPool(RWDBConnection *pNewConnection)
	:QGTHPool(pNewConnection)
	{;}

	virtual ~QCHPool() {;}

protected:
	void OnSelect(RWDBSelector& aSelect,RWDBTable& table);
	void OnReader(RWDBReader& aReader,GTHPool *pPool);
	GTHPool * OnNewPool();

};

#endif //!defined(AFX_QCHPool_H)