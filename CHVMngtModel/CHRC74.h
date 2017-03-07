/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHRC74.h
*	Description	: Results
*
*	Author		:CH Team
*	Date created:20-01-2006
* 	Project		:CHVMngtModel
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#if !defined(AFX_CHRC74_H__2FF39B88_82CE_466F_B9B9_BCB172107525__INCLUDED_)
#define AFX_CHRC74_H__2FF39B88_82CE_466F_B9B9_BCB172107525__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CHVMngtModelDll.h"

#include <Reports\V\ReportConfig.h>
#include "CHReportTemplate.h"
#include "CHRLegends.h"

class CHVMngtExport CHRC74 : public CHReportTemplate  
{
public:
	CHRC74(CReportManager& aReportManager,CReportConfig& aReportConfig,CHPhase * pSelPhase,short roundSel);
	virtual ~CHRC74();
	
protected:
	ReportReturn	OnBody					();

private:
	void			OnBeginReport			();
	RWCString		getNameOfSourceLis		();
	unsigned short  OnCallbackFn( struct USR_TAB * pTableInfo );
	
	ReportReturn	paintLegends			();
	ReportReturn	paintTemplateHeader		();
	ReportReturn	paintTemplateResults	();
	ReportReturn	paintMembers			(CHMatch *pMatch);
	
	
	
	
	RWDate			OnGetEventDate() const;
	RWTime			OnGetEventTime() const;
	RWWString		OnGetLine(const int lineNumber,const char *language) const;

	void			setGlobalVaris();
	
	void			assignDataIndividual(CHMatch *pMatch);
	void			assignDataMember(CHMatch *pSubMatch);
	void			buildVector();
	RWBoolean		changeRound(CHMatch *pMatch);
	void			setDynamicLegends();

private:
	CLis * pLis;
	CHPhase * pPhase;
	size_t index;
	
	CHRLegends		* pLegends;
	GSortedVector vMatches;
	short round;
	RWBoolean firstPage;

			
};

#endif // !defined(AFX_CHRC74_H__2FF39B88_82CE_466F_B9B9_BCB172107525__INCLUDED_)
