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

#pragma once
#include "CHVMngtModelDefs.h"
#include "CHReportTemplate.h"

class CHRLegends;
class CHPhase;
class CHPoolResult;
class CHMatch;

class CHVMngtModelExport CHRC75 : public CHReportTemplate  
{
public:
	CHRC75(CReportManager& aReportManager, CReportConfig& aReportConfig, CHPhase * pSelPhase, short roundSel);
	virtual ~CHRC75();
	
protected:
	ReportReturn	OnBody					();

private:
	void			OnBeginReport			();
	MSLString		getNameOfSourceLis		();
	unsigned short  OnCallbackFn( struct USR_TAB * pTableInfo );
	void			initLabels();

	ReportReturn	paintLegends			();
	ReportReturn	paintTemplateHeader		();
	ReportReturn	paintTemplateResults	();
			
	MSLDate			OnGetEventDate() const;
	MSLTime			OnGetEventTime() const;
	MSLWString		OnGetLine(const int lineNumber,const char *language) const;

	void			setGlobalVaris();
	
	void			assignDataIndividual(CHPoolResult *pPoolResult);
	void			buildVector();
	bool			changeRound(CHMatch *pMatch);
	

private:
	CLis * m_pLis;
	CHPhase * m_pPhase;
	short m_index;
	
	CHRLegends		* m_pLegends;
	MSLSortedVector m_vPoolResults;
	short m_round;
	bool m_firstPage;			
};
