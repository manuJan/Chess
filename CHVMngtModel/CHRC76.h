/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHRC76.h
*   Description	: 
*
*	Author		: CH Team
*	Date created: 22-12-2005
* 	Project		:
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#if !defined(AFX_CHRC76_H__F53270AC_1C4D_4596_BBE8_FE7DA27FAD83__INCLUDED_)
#define AFX_CHRC76_H__F53270AC_1C4D_4596_BBE8_FE7DA27FAD83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHVMNGTDLL_H
	#include "CHVMngtModelDll.h"
#endif // _CHVMNGTDLL_H

#include <Sports/CH/Data/CHRegister.h>
#include "CHReportTemplate.h"

class CHRLegends;
class CHRPool;
class CHVMngtExport CHRC76 : public CHReportTemplate  
{
public:

	enum typeReport{eSchedule=0,ePreliminarySummary=1,eFinalSummary=2};

	CHRC76(CReportManager& aReportManager, CReportConfig& aReportConfig, CHEvent* _pEvent, typeReport repType);
	virtual ~CHRC76();

protected:
	RWCString		getNameOfSourceLis();
	void			OnBeginReport();
	ReportReturn	OnBody();
	unsigned short	OnCallbackFn(struct USR_TAB * pTableInfo);
	
	void			loadDataPool();

	virtual void	onLook(){};

	RWDate		OnGetEventDate() const;
	RWTime		OnGetEventTime() const;
	RWCString	OnGetPhaseCode() const;
	
protected:
	CLis			*pLis;
	CReportManager	*pReportMng;
	CHEvent			*pEvent;
	
	GSortedVector	vCHRPool;
	CHRPool			*pCurrentCHRPool;

	int				nLines;
	short			index;
	short			indexRound;
	short			indexTwice;
	short			indexHeightTwice;
	int				nInitLine;
	int				nLastLine;
	
	RWBoolean		newPage;
	typeReport		repType;

	RWBoolean		jumpPooles;

	int				xPool;
	CHPhase			*pPhaseAnt;
};

#endif // !defined(AFX_CHRC76_H__F53270AC_1C4D_4596_BBE8_FE7DA27FAD83__INCLUDED_)
