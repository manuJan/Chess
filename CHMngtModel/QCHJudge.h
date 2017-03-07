/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : QCHJudge.h                                                                 
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

#if !defined(AFX_QCHJUDGE_H__223957E1_AB36_4755_BBA4_049AA649640C__INCLUDED_)
#define AFX_QCHJUDGE_H__223957E1_AB36_4755_BBA4_049AA649640C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <CORE/G/QBase.h>

class QCHJudge : public QBase  
{
public:
	QCHJudge(RWDBConnection *pNewConnection)
		:QBase(pNewConnection) 
	{ ; }
	virtual ~QCHJudge() 
	{ ; }

protected:
	size_t selectCollection(RWDBConnection &aConnection, RWCollection &target);

};

#endif // !defined(AFX_QCHJUDGE_H__223957E1_AB36_4755_BBA4_049AA649640C__INCLUDED_)
