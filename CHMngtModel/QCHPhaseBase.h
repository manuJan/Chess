/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : QCHPhaseBase.h                                                                 
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

#if !defined(AFX_QCHPHASEBASE_H__DD01EE36_BA4E_406B_A423_1C888719D597__INCLUDED_)
#define AFX_QCHPHASEBASE_H__DD01EE36_BA4E_406B_A423_1C888719D597__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <core/TH/QGTHPhaseGeneric.h>

class CHPhaseBase;

class QCHPhaseBase : public QGTHPhaseGeneric  
{
public:
	QCHPhaseBase(RWDBConnection *pNewConnection)
	:QGTHPhaseGeneric(pNewConnection)
	{;}

	virtual ~QCHPhaseBase() {;}

private:
	void OnSelect(RWDBSelector& aSelect,RWDBTable& z012phase,RWDBTable& z512phase);
	void OnReader(RWDBReader& aReader,GNamesEx& aDescription,GPhaseBase *pPhaseGeneric);
    
	
private:
	GPhaseBase *OnNewPhaseBase();

};

#endif // !defined(AFX_QCHPHASEBASE_H__DD01EE36_BA4E_406B_A423_1C888719D597__INCLUDED_)
