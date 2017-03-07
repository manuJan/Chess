/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHRC32C.h
*	Description	:Export Dll
*
*	Author		:Lawn Bowl Team
*	Date created:20-12-2005
* 	Project		:Entry List By Event Report
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#if !defined(AFX_CHRC32C_H__89D1F96A_EDE8_4A86_993C_779697347397__INCLUDED_)
#define AFX_CHRC32C_H__89D1F96A_EDE8_4A86_993C_779697347397__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CHVMngtModelDll.h"
#include "CHReportTemplate.h"
#include <Reports/V/V04Inscription.h>


class CHInscription;
class CHEvent;

class CHVMngtExport CHRC32C : public CHReportTemplate  
{
public:
	CHRC32C(CReportManager& aReportManager,CReportConfig& aReportConfig);
	CHRC32C(CReportManager& aReportManager,CReportConfig& aReportConfig, CHEvent *pEventSel);
	virtual ~CHRC32C()
		{;}
	
protected:
	// Overloaded member function
	ReportReturn	OnBody();
	RWDate			OnGetEventDate() const;
	RWTime			OnGetEventTime() const;
	RWWString		OnGetLine(const int lineNumber,const char *language) const;

private:
	void			OnBeginReport();
	ReportReturn	paintHeader();
	void			setDataInscription(CHInscription* pInscription);
	ReportReturn	paintInscription();
	ReportReturn	paintTotalEntries();
	
private:
	V04Inscription	aV04Inscription;
	CReportManager	*pReportMng;
	CLis			*pLis;
	bool			isTeam;
	int				totalEntries;
	CHEvent			*pEvent;
	RWCString		lastEvent;
	RWBoolean		isFirstEvent;
};

#endif // !defined(AFX_CHRC32C_H__89D1F96A_EDE8_4A86_993C_779697347397__INCLUDED_)
