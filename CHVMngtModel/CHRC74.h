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

#pragma once
#include "CHVMngtModelDefs.h"
#include "CHReportTemplate.h"

class CHPhase;
class CHMatch;
class CHRLegends;

class CHVMngtModelExport CHRC74 : public CHReportTemplate  
{
public:
	CHRC74(CReportManager& aReportManager, CReportConfig& aReportConfig, CHPhase * pSelPhase, short roundSel);
	virtual ~CHRC74();
	
protected:
	ReportReturn	OnBody					();

private:
	void			OnBeginReport			();
	MSLString		getNameOfSourceLis		();
	unsigned short  OnCallbackFn			( struct USR_TAB * pTableInfo );
	
	ReportReturn	paintLegends			();
	ReportReturn	paintTemplateHeader		();
	ReportReturn	paintTemplateResults	();
	ReportReturn	paintMembers			(CHMatch *pMatch);
		
	MSLWString		OnGetLine(const int lineNumber,const char *language) const;
	MSLDate			OnGetEventDate() const;
	MSLTime			OnGetEventTime() const;

	void			initLabels();
	void			setGlobalVaris();
	
	void			assignDataIndividual(CHMatch *pMatch);
	void			assignDataMember(CHMatch *pSubMatch);
	void			buildVector();
	bool			changeRound(CHMatch *pMatch);
	void			setDynamicLegends();

private:
	CLis * m_pLis;
	CHPhase * m_pPhase;
	short m_index;
	
	CHRLegends	* m_pLegends;
	MSLSortedVector m_vMatches;
	short m_round;
	bool m_firstPage;

			
};


