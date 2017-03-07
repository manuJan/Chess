/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHRC93.h
*   Description	: 
*
*	Author		: CH Team
*	Date created: 5-1-2006
* 	Project		:
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#if !defined(AFX_CHRC93_H__84457930_2E5B_463E_9760_DA8428FDFC7B__INCLUDED_)
#define AFX_CHRC93_H__84457930_2E5B_463E_9760_DA8428FDFC7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHVMNGTDLL_H
	#include "CHVMngtModelDll.h"
#endif // _CHVMNGTDLL_H

#include "CHReportTemplate.h"
#include <REPORTS/V/VMedalsByEvent.h>
#include <REPORTS/V/RLegend.h>
#include <SPORTS/CH/DATA/CHMember.h>
#include <SPORTS/CH/DATA/CHEvent.h>

class CHVMngtExport CHRC93 : public CHReportTemplate  
{
public:
	CHRC93(CReportManager & aReportManager,CReportConfig & aReportConfig);
	CHRC93(CReportManager & aReportManager,CReportConfig & aReportConfig,CHEvent * pSelEvent);
	virtual ~CHRC93();

	// Overloaded member function
	void OnBeginReport();
	ReportReturn OnBody();
	inline CLis *getLis() const
		{ return pLis; }

protected:
	unsigned short OnCallbackFn(struct USR_TAB * pTableInfo);

	CReportBase::ReportReturn paintLevel1(GMedallist * pMedallist);
	CReportBase::ReportReturn paintLevel2(CHMember * pMember);

	RWCString getNameOfSourceLis();
	void fillColEvents();

	RWDate OnGetEventDate() const;
	RWTime OnGetEventTime() const;

	void	paintLegends();
	RWDate	getFirstMedallist(CHEvent *pEvent);

private:
	CLis *pLis;
	VMedalsByEvent *pVMedalsByEvent; // Event->Medallist->Members

	RWBoolean firstMedalOfEvent;
	RWBoolean firstMedallist;
	CHEvent * pEvent;
	GMedallist * pLastMedallist;
	int membersIndex;
	int nTotalMedals;
	RWSet colEventsNoMedals;
	RWBoolean oneEvent;
};

#endif // !defined(AFX_CHRC93_H__84457930_2E5B_463E_9760_DA8428FDFC7B__INCLUDED_)
