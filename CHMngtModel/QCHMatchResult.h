/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : QCHMatchResult.h
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

#if !defined(AFX_QCHMATCHRESULT_H__79C882F6_A108_4F3F_9406_045FC44AC0C2__INCLUDED_)
#define AFX_QCHMATCHRESULT_H__79C882F6_A108_4F3F_9406_045FC44AC0C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <CORE/TH/QGTHMatchResult.h>

class QCHMatchResult : public QGTHMatchResult  
{
public:
	QCHMatchResult(RWDBConnection *pNewConnection);
	virtual ~QCHMatchResult();

protected:
	void OnSelect(RWDBSelector& aSelect,RWDBTable& tMatchResult);
	void OnReader(RWDBReader& aReader,GTHMatchResult *pMatchResult);

	GTHMatchResult * OnNewMatchResult();
};

#endif // !defined(AFX_QCHMATCHRESULT_H__79C882F6_A108_4F3F_9406_045FC44AC0C2__INCLUDED_)
