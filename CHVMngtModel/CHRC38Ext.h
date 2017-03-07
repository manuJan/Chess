/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHRC38Ext.h
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:19-12-2005
*   Project     :CHV Model               
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///
#if !defined(AFX_CHRC38EXT_H__85F44C1B_CF7C_47DE_9DC5_8749F845CB86__INCLUDED_)
#define AFX_CHRC38EXT_H__85F44C1B_CF7C_47DE_9DC5_8749F845CB86__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <REPORTS/V/RC38Ext.h>
#include <REPORTS/V/RLegend.h>
class CHRegister;
class CHRC38Ext : public RC38Ext  
{
public:
	CHRC38Ext(CReportTemplate *pRepTem, CReport *pRep);
	virtual ~CHRC38Ext();

	bool run();
	short getHeight();
	
	void prepare();
	void setLegend(RLegend *value);

protected:
	unsigned short generalLineOfLegendCallBack (struct USR_TAB *pTabInf);
	
private:
	RWCString getEventOfRegister();
	static unsigned short specialLaneCallBack( struct USR_TAB * pTabInf );


private:
	CHRegister *pCHRegister;
	RLegend *pSpLegend;
};

#endif // !defined(AFX_CHRC38EXT_H__85F44C1B_CF7C_47DE_9DC5_8749F845CB86__INCLUDED_)
