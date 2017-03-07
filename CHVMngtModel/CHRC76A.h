/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHRC76A.h
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
#if !defined(AFX_CHRC76A_H__15736481_C19A_40D5_9996_8FCC76EB5833__INCLUDED_)
#define AFX_CHRC76A_H__15736481_C19A_40D5_9996_8FCC76EB5833__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHVMNGTDLL_H
	#include "CHVMngtModelDll.h"
#endif // _CHVMNGTDLL_H

#include <Sports/CH/Data/CHRegister.h>
#include "CHRC76.h"
#include "CHReportDefines.h"

class CHRLegends;
class CHRPool;
class CHVMngtExport CHRC76A : public CHRC76  
{
public:
	CHRC76A(CReportManager& aReportManager, CReportConfig& aReportConfig, CHEvent* _pEvent);
	virtual ~CHRC76A();

	void	onLook();
	void	OnBeginReport();
	CReportBase::ReportReturn OnBody();

	RWBoolean pageBreak(short value);

	RWDate		OnGetEventDate() const;
	RWTime		OnGetEventTime() const;


private:
	CHRLegends		*pLegend;
};

#endif // !defined(AFX_CHRC76A_H__15736481_C19A_40D5_9996_8FCC76EB5833__INCLUDED_)
