/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHROfficialsRole.h
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
#if !defined(AFX_CHROFFICIALSROLE_H__8E4DA978_2C1E_41F0_978F_C1F1E8E0D4D5__INCLUDED_)
#define AFX_CHROFFICIALSROLE_H__8E4DA978_2C1E_41F0_978F_C1F1E8E0D4D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHVMNGT_DLL
	#include "CHVMngtModelDll.h"
#endif // _CHVMNGT_DLL

#include "CHReportTemplate.h"

class GFunction;
class CHRegister;
class CHROfficialsRole  
{
public:
	CHROfficialsRole(CHReportTemplate* _pReportTemplate,CReport* _pReport);
	virtual ~CHROfficialsRole();

	bool				runlis();
	int					getHeight();
	int					getWidth();
	void				setCorY(const short value);
	void				setCorX(const short value);
	void				loadData(GFunction* _pFunction,bool beginPage=false,bool full=true,int part=0);
	bool				isFinish();
	unsigned short		OnCallbackFn(struct USR_TAB * pTabInf);

protected:
	unsigned short		tableCallBack(struct USR_TAB * pTabInf);

private:
	RWBoolean			loadlis();	
	void				assignData();
	void				center();

private:
	CHReportTemplate	* pReportTemplate;
	CReport				* pReport;
	GFunction			* pFunction;
	CLis				* pLis;
	int					index;
	short				corx;
	short				cory;
	RWBoolean			ok;
	CHRegister			* pJudge;
	GSortedVector		vJudges;
	bool				first;
	bool				roleAssigned;
	bool				finish;
};

#endif // !defined(AFX_CHROFFICIALSROLE_H__8E4DA978_2C1E_41F0_978F_C1F1E8E0D4D5__INCLUDED_)
