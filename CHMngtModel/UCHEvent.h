/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : UCHEvent.h                                                                 
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

#if !defined(AFX_UCHEVENT_H__553EB4A9_2FC0_447B_AAAB_BC9F3F3FCBE6__INCLUDED_)
#define AFX_UCHEVENT_H__553EB4A9_2FC0_447B_AAAB_BC9F3F3FCBE6__INCLUDED_

#ifndef _UCHEvent_H
#define _UCHEvent_H
#endif 

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHMNGTMODELDLL_H
#   include "CHMngtModelDll.h" 
#endif // _CH_MNGTMODELDLL_H

#include <CORE/TH/UGTHEvent.h>

class UCHEvent : public UGTHEvent  
{
public:
	UCHEvent(RWDBConnection *pNewConnection);
	virtual ~UCHEvent();

protected:
	void OnAssignAttributes(const GEvent & aEvent);
	void OnInsert(RWDBInserter & aInsert,const GEvent & aEvent);
	void OnUpdate(RWDBUpdater & aUpdate,RWDBTable & table,const GEvent & aEvent);
	void OnDelete(RWDBUpdater & aUpdate,RWDBTable & table,const GEvent & aEvent);

private:
	short	fOrderEvent,
			fTwoBronces,
			fTypeEvent,
			fMode;
	RWCString reqRankOrd;
	RWDBNullIndicator nullReqRankOrd;
	float	fConstRating;
	float	fPointsBye;
		
};

#endif // !defined(AFX_UCHEVENT_H__553EB4A9_2FC0_447B_AAAB_BC9F3F3FCBE6__INCLUDED_)
