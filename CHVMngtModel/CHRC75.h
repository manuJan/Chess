/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHRC75.h
*	Description	: Results
*
*	Author		:CH Team
*	Date created:24-01-2006
* 	Project		:CHVMngtModel
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#if !defined(AFX_CHRC75_H__2FF39B88_82CE_466F_B9B9_BCB172107525__INCLUDED_)
#define AFX_CHRC75_H__2FF39B88_82CE_466F_B9B9_BCB172107525__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CHVMngtModelDll.h"

#include <Reports\V\ReportConfig.h>
#include "CHReportTemplate.h"
#include "CHRLegends.h"

class CHVMngtExport CHRC75 : public CHReportTemplate  
{
public:
	CHRC75(CReportManager& aReportManager,CReportConfig& aReportConfig,CHPhase * pSelPhase,short roundSel);
	virtual ~CHRC75();
	
protected:
	ReportReturn	OnBody					();

private:
	void			OnBeginReport			();
	RWCString		getNameOfSourceLis		();
	unsigned short  OnCallbackFn( struct USR_TAB * pTableInfo );
	
	ReportReturn	paintLegends			();
	ReportReturn	paintTemplateHeader		();
	ReportReturn	paintTemplateResults	();
		
	
	
	RWDate			OnGetEventDate() const;
	RWTime			OnGetEventTime() const;
	RWWString		OnGetLine(const int lineNumber,const char *language) const;

	void			setGlobalVaris();
	
	void			assignDataIndividual(CHPoolResult *pPoolResult);
	void			buildVector();
	RWBoolean		changeRound(CHMatch *pMatch);
	

private:
	CLis * pLis;
	CHPhase * pPhase;
	size_t index;
	
	CHRLegends		* pLegends;
	GSortedVector vPoolResults;
	short round;
	RWBoolean firstPage;

			
};

#endif // !defined(AFX_CHRC75_H__2FF39B88_82CE_466F_B9B9_BCB172107525__INCLUDED_)
