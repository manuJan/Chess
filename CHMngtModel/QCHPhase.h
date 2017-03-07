/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : QCHPhase.h
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

#if !defined(AFX_QCHPHASE_H__AC4514A0_F4B4_4E71_92CA_204FA4611C71__INCLUDED_)
#define AFX_QCHPHASE_H__AC4514A0_F4B4_4E71_92CA_204FA4611C71__INCLUDED_

#ifndef _QCHPhase_H
#define _QCHPhase_H
#endif 

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Core/TH/QGTHPhase.h>

class QCHPhase : public QGTHPhase  
{
public:
	QCHPhase(RWDBConnection *pNewConnection);
	virtual ~QCHPhase();

protected:
	void OnSelect(RWDBSelector& aSelect,RWDBTable& tPhase);
	void OnReader(RWDBReader& aReader,GPhase *pPhase);

	GPhase * OnNewPhase();
};

#endif // !defined(AFX_QCHPHASE_H__AC4514A0_F4B4_4E71_92CA_204FA4611C71__INCLUDED_)
