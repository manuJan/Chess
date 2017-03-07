/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHReportTemplate.h
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

#if !defined(AFX_CHREPORTTEMPLATE_H__D80C16F8_6A71_4863_A948_92A97CEDFAE7__INCLUDED_)
#define AFX_CHREPORTTEMPLATE_H__D80C16F8_6A71_4863_A948_92A97CEDFAE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHVMNGTMODELDLL_H
	#include "CHVMngtModelDll.h"
#endif // _CHVMNGTNODELDLL_H

#include <Reports\THV\THReportTemplate.h>

class CHMatch;
class CHEvent;
class CHPhase;
class CReportConfig;
class CHVMngtExport CHReportTemplate : public THReportTemplate  
{
public:
	CHReportTemplate(CReportManager& aReportManager,CReportConfig& aReportConfig,const GTHEvent *pEvent=0);
	CHReportTemplate(CReportManager& aReportManager,CReportConfig& aReportConfig,const GTHPhase *pPhase);
	CHReportTemplate(CReportManager& aReportManager,CReportConfig& aReportConfig,const GTHMatch *pMatch);
	CHReportTemplate(CReportManager& aReportManager,CReportConfig& aReportConfig,RWDate date);
	virtual ~CHReportTemplate();

	RWBoolean			prepareTemplate();
	virtual RWBoolean	pageBreak(short value);
	void				setVaris(CLis *pLis);

protected:
	// Overwrite from CReportBase
//	RWCString OnGetReportID() const;
	RWBoolean OnRun();

protected:
	// Overwrite from CReportTemplate
	//RWCString OnGetEventCode() const;
	//RWCString OnGetPhaseCode() const;
	RWCString	OnGetVenueCode() const;
	RWDate		OnGetEventDate() const;
	RWTime		OnGetEventTime() const;
	

protected:

	RWCString getDateWithoutZero(RWDate date,RWCString format);

	CReportConfig *getReportConfig();
	CLis *getLis() const;
	void setFontType(CLis *pRepLis, int fHead, RWCString init, RWCString end="");

protected:
//	const GTHEvent *pHeaderEvent;
//	const GTHPhase *pHeaderPhase;
//	const GTHMatch *pHeaderMatch;
	RWDate dateSel;
	int font;
};

#endif // !defined(AFX_CHREPORTTEMPLATE_H__D80C16F8_6A71_4863_A948_92A97CEDFAE7__INCLUDED_)
