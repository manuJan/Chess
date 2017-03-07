/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHRC51G.h
*   Description	: 
*
*	Author		: CH Team
*	Date created: 24-12-2005
* 	Project		:
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#if !defined(AFX_CHRC51G_H__3E7C6FB3_8C2B_4779_94D5_3678EC8788C4__INCLUDED_)
#define AFX_CHRC51G_H__3E7C6FB3_8C2B_4779_94D5_3678EC8788C4__INCLUDED_

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
class CHVMngtExport CHRC51G : public CHRC76  
{
public:
	CHRC51G(CReportManager& aReportManager, CReportConfig& aReportConfig, CHEvent* _pEvent);
	virtual ~CHRC51G();

	void	onLook();
	void	OnBeginReport();
	CReportBase::ReportReturn OnBody();

	RWBoolean pageBreak(short value);

	RWDate		OnGetEventDate() const;
	RWTime		OnGetEventTime() const;

private:
	CHRLegends		*pLegend;
};

#endif // !defined(AFX_CHRC51G_H__3E7C6FB3_8C2B_4779_94D5_3678EC8788C4__INCLUDED_)
