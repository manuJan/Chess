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
#pragma once

#include "CHVMngtModelDefs.h"
#include "CHReportTemplate.h"

class RCHSchedule;

class CHVMngtModelExport CHRC08 : public CHReportTemplate  
{
public:
	CHRC08(CReportManager& aReportManager,CReportConfig& aReportConfig);
	virtual ~CHRC08();

protected:
	// from CReportBase
	bool			OnRun();
	ReportReturn	body(const int nLin);
	unsigned short	OnCallbackFn(struct USR_TAB * pTableInfo);
	void			OnBeginReport();

private:
	RCHSchedule		*m_pSchedule;
	bool			m_bNewPage;
};

