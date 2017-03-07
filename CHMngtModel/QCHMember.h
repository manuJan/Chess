/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : QCHMember.h
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

#if !defined(AFX_QCHMEMBER_H__EECB0D35_7602_45A2_863B_EA68FF9740BB__INCLUDED_)
#define AFX_QCHMEMBER_H__EECB0D35_7602_45A2_863B_EA68FF9740BB__INCLUDED_

#ifndef _QCHMember_H
#define _QCHMember_H
#endif

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHMNGTMODELDLL_H
#   include "CHMngtModelDll.h" 
#endif // _CH_MNGTMODELDLL_H

#include <CORE/TH/QGTHMember.h>
#include "CHMember.h"

class QCHMember : public QGTHMember  
{
public:
	QCHMember(RWDBConnection *pNewConnection);
	virtual ~QCHMember();

protected:
	void OnSelect(RWDBSelector& aSelect,RWDBTable& tMember);
	void OnReader(RWDBReader& aReader,GMember *pMember);

	GMember * OnNewMember();
};

#endif // !defined(AFX_QCHMEMBER_H__EECB0D35_7602_45A2_863B_EA68FF9740BB__INCLUDED_)
