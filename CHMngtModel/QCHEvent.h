/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : QCHEvent.h                                                                 
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

#if !defined(AFX_QCHEVENT_H__E2BA6CEE_47AF_43BD_9007_9DFBAEA2A309__INCLUDED_)
#define AFX_QCHEVENT_H__E2BA6CEE_47AF_43BD_9007_9DFBAEA2A309__INCLUDED_

#ifndef _QCHEvent_H
#define _QCHEvent_H
#endif

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHMNGTMODELDLL_H
#   include "CHMngtModelDll.h" 
#endif // _CH_MNGTMODELDLL_H

#include <CORE/TH/QGTHEvent.h>
#include "CHEvent.h"

class CHModelExport QCHEvent : public QGTHEvent  
{
public:
	QCHEvent(RWDBConnection *pNewConnection,QEvent::SelectionMode selection=QEvent::eActive);
	virtual ~QCHEvent();

protected:
	GEvent * OnNewEvent();
	void OnSelect(RWDBSelector& aSelect,RWDBTable& tEvent);
	void OnReader(RWDBReader& aReader,GEvent *pEvent);
};

#endif // !defined(AFX_QCHEVENT_H__E2BA6CEE_47AF_43BD_9007_9DFBAEA2A309__INCLUDED_)
