/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHRC58.h
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
#if !defined(AFX_CHRC58_H__C18E0B8A_7EB1_49B5_8FEF_86A49F32D814__INCLUDED_)
#define AFX_CHRC58_H__C18E0B8A_7EB1_49B5_8FEF_86A49F32D814__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHVMNGTDLL_H
	#include "CHVMngtModelDll.h"
#endif // _CHVMNGTDLL_H

#include "CHReportTemplate.h"
#include "CHReportDefines.h"
#include "CHRLegends.h"

class CHVMngtExport CHRC58 : public CHReportTemplate  
{
public:
	CHRC58(CReportManager& aReportManager,CReportConfig& aReportConfig,RWDate aDate);
	virtual ~CHRC58();

protected:
	// Overloaded member function
	ReportReturn OnBody();
	unsigned short OnCallbackFn( struct USR_TAB * pTableInfo );
	unsigned short tablaHeader( struct USR_TAB * pTableInfo );
	unsigned short tablaMatch( struct USR_TAB * pTableInfo );

private:
	void OnBeginReport();
	CReportBase::ReportReturn paintDateEvent();
	CReportBase::ReportReturn paintHeader();
	CReportBase::ReportReturn paintMatch();
	CReportBase::ReportReturn paintLegend();
		
	void		setDataMatch(CHMatch* pMatch);
	RWCString	getSessionDetailed();
	void		setDynamicLegends();
	
	
	GSortedVector	getMatchesSession(CHSession *pSession);
	void			buildVector();
	RWDate			OnGetEventDate() const;
	RWTime			OnGetEventTime() const;
	

private:
	
	CReportManager	*pReportMng;
	GData			*pData;
	CLis			*pLis;
	CHSession		*pSession;
	RWDate			date;
	CHRLegends		* pLegends;
	RWBoolean       paintSession;
	GSortedVector vMatches;
	size_t			posVector;
};

#endif // !defined(AFX_CHRC58_H__C18E0B8A_7EB1_49B5_8FEF_86A49F32D814__INCLUDED_)
