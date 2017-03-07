/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHRC08.h
*   Description	: 
*
*	Author		: CH Team
*	Date created:  2-1-2006
* 	Project		:
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#if !defined(AFX_CHRC08_H__FF6C4287_B2E4_4FB1_AA33_40C6C07E8E48__INCLUDED_)
#define AFX_CHRC08_H__FF6C4287_B2E4_4FB1_AA33_40C6C07E8E48__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHVMNGTDLL_H
	#include "CHVMngtModelDll.h"
#endif // _CHVMNGTDLL_H

#include "CHReportTemplate.h"

class RCHSchedule;
class CHVMngtExport CHRC08 : public CHReportTemplate  
{
public:
	CHRC08(CReportManager& aReportManager,CReportConfig& aReportConfig);
	virtual ~CHRC08();

protected:
	// from CReportBase
	RWBoolean		OnRun();
	ReportReturn	body(const int nLin);
	ReportReturn	OnFootHeader(const RWBoolean bNPg=true);
//	ReportReturn	OnBody();
	unsigned short	OnCallbackFn(struct USR_TAB * pTableInfo);
	void			OnBeginReport();
//	void			properties();
//	ReportReturn	paintLegend();
	RWDate			OnGetEventDate() const;
	RWTime			OnGetEventTime() const;

private:
	RCHSchedule		*pSchedule;
//	CHRLegends		*pStaticLegend;
	RWBoolean		bNewPage;
};

#endif // !defined(AFX_CHRC08_H__FF6C4287_B2E4_4FB1_AA33_40C6C07E8E48__INCLUDED_)
