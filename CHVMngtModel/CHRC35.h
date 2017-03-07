/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHRC35.h
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
#if !defined(AFX_CHRC35_H__B74C2CA5_80B6_4F88_A3B8_42330FB9AAF3__INCLUDED_)
#define AFX_CHRC35_H__B74C2CA5_80B6_4F88_A3B8_42330FB9AAF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHVMNGTDLL_H
	#include "CHVMngtModelDll.h"
#endif // _CHVMNGTDLL_H

#include "CHReportTemplate.h"

const int CH_COMPETITION_OFFICIALS_C35 = 809;

class CHROfficialsRole;
class GFunction;
class CHVMngtExport CHRC35 : public CHReportTemplate  
{
public:
	CHRC35(CReportManager& aReportManager,CReportConfig& aReportConfig);
	virtual ~CHRC35();

protected:
	void				OnBeginReport();
	ReportReturn		OnBody();
	unsigned short		OnCallbackFn(struct USR_TAB * pTabInf);

	RWDate OnGetEventDate() const;
	RWTime OnGetEventTime() const;


private:
	void				center();
	void				loadData();

//attributes
private:
	CLis				*pLis;
	int					index,	 //indice 	
						nLines;  //número de lineas 
	CHROfficialsRole	*pOfficialsRole;
	bool				first;	
	GSortedVector		vFunctions;
	GFunction			*pFunction;
	bool				full;
	int					part;
};

#endif // !defined(AFX_CHRC35_H__B74C2CA5_80B6_4F88_A3B8_42330FB9AAF3__INCLUDED_)
