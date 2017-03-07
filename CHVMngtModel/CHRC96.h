
/*************************************************************************************
*			© Copyright MSL Software, S.L., 2001
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHRC96.h
*	Description	: Interface for the CHRC96 class.
*
*	Author		: Chess Team
*	Date created: 24-January-2006
* 	Project		: 
*	
* 	Modification history
*	By			: 
*	Date		: 
*	Changes		: 
*
***************************************************************************************/

#if !defined(AFX_CHRC96_H__D2E8BA39_EF36_42BF_B6FE_49AAE47ECE11__INCLUDED_)
#define AFX_CHRC96_H__D2E8BA39_EF36_42BF_B6FE_49AAE47ECE11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CHVMngtModelDll.h"
#include "CHRLegends.h"
#include "CHReportTemplate.h"  

class CHEvent;
class CHEventResult;
class GRegister;
class CHInscription;

class CHVMngtExport CHRC96 : public CHReportTemplate
{
public:
	CHRC96(CReportManager& aReportManager, CReportConfig& aReportCfg, CHEvent *pEvent);
	virtual ~CHRC96();

protected:
	// Overloaded member function
	ReportReturn	OnBody();
	ReportReturn	paintLegends();
	unsigned		short OnCallbackFn(struct USR_TAB * pTabInf);
	RWDate			OnGetEventDate() const;
	RWTime			OnGetEventTime() const;

private:
	void   OnBeginReport();
	CReportBase::ReportReturn paintRanking();

	RWBoolean	build_RankingVector();
	void		setDataEventResult(CHEventResult *pEventResult);
	void		setGlobalVaris();
	void		setDynamicLegends();

	unsigned short RankDetalCallBack( struct USR_TAB * pTabInf);

private:
	// Attributes
	CLis  *pMyLis;
	CHEvent	*pEventSel;
	CHEventResult *pEventResult;
	GSortedVector vResults;
	short rankAnt;
	size_t pos;
	CHRLegends		* pLegends;
	RWBoolean firstPage;
	
};

#endif // !defined(AFX_CHRC96_H__D2E8BA39_EF36_42BF_B6FE_49AAE47ECE11__INCLUDED_)
