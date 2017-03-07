/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : QCHInscription.h
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

#if !defined(AFX_QCHINSCRIPTION_H__B1CE7FF3_29EA_4435_98FC_89E91C35D5F1__INCLUDED_)
#define AFX_QCHINSCRIPTION_H__B1CE7FF3_29EA_4435_98FC_89E91C35D5F1__INCLUDED_

#ifndef _QCHInscription_H
#define _QCHInscription_H
#endif

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHMNGTMODELDLL_H
#   include "CHMngtModelDll.h" 
#endif // _CH_MNGTMODELDLL_H

#include <Core/TH/QGTHInscription.h>
#include "CHInscription.h"

class QCHInscription : public QGTHInscription  
{
public:
	QCHInscription(RWDBConnection *pNewConnection);
	virtual ~QCHInscription();

protected:
	void OnSelect(RWDBSelector& aSelect,RWDBTable& tInscription);
	void OnReader(RWDBReader& aReader,GInscription *pInscription);
	
	GInscription * OnNewInscription();
};

#endif // !defined(AFX_QCHINSCRIPTION_H__B1CE7FF3_29EA_4435_98FC_89E91C35D5F1__INCLUDED_)
