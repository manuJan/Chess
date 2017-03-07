/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : QCHDiscipline.h                                                                 
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:05-12-2005
*   Project     :CH Model
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///

#ifndef _QCHDiscipline_H
#define _QCHDiscipline_H
#endif 

#if !defined(AFX_QCHDISCIPLINE_H__05C64AA3_7CB2_48A0_AEC4_2EA00FE3B60D__INCLUDED_)
#define AFX_QCHDISCIPLINE_H__05C64AA3_7CB2_48A0_AEC4_2EA00FE3B60D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHMNGTMODELDLL_H
#   include "CHMngtModelDll.h" 
#endif // _CH_MNGTMODELDLL_H

#include <CORE\G\QDiscipline.h>

class QCHDiscipline : public QDiscipline  
{
public:
	QCHDiscipline(RWDBConnection *pNewConnection);
	virtual ~QCHDiscipline();

protected:
	size_t selectObject(RWDBConnection & aConnection,GData & aData);
};

#endif // !defined(AFX_QCHDISCIPLINE_H__05C64AA3_7CB2_48A0_AEC4_2EA00FE3B60D__INCLUDED_)
