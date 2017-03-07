/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : QCHRegister.h                                                                 
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:13-07-2005
*   Project     :CH Model
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///


#if !defined(AFX_QCHREGISTER_H__D4BEC758_9C87_4DBE_9D41_D2E209C037ED__INCLUDED_)
#define AFX_QCHREGISTER_H__D4BEC758_9C87_4DBE_9D41_D2E209C037ED__INCLUDED_

#ifndef _QCHRegister_H
#define _QCHRegister_H
#endif 

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHMNGTMODELDLL_H
#   include "CHMngtModelDll.h" 
#endif // _CH_MNGTMODELDLL_H

#include <CORE/G/QRegister.h>

class CHRegister;
class QCHRegister : public QRegister  
{
public:
	QCHRegister(RWDBConnection *pNewConnection);
	virtual ~QCHRegister();

private:
	void OnSelect(RWDBSelector& aSelect,RWDBTable& z010register);
	void OnReader(RWDBReader& aReader,GRegister *pRegister);

	GRegister *OnNewRegister();
};

#endif // !defined(AFX_QCHREGISTER_H__D4BEC758_9C87_4DBE_9D41_D2E209C037ED__INCLUDED_)
