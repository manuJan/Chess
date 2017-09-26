/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:ARRC32C.h
*	Description	:
*				 
*	Author		: Javier Juste
*	Date created: 5-Mar-2009
* 	Project		: ARVMngtModel
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
class CHInscription;
class CHMember;
class CHEvent;

class CHVMngtModelExport CHRC32C : public CHReportTemplate  
{
public:
	CHRC32C(CReportManager& aReportManager,CReportConfig& aReportConfig,CHEvent* _pEvent);
	virtual ~CHRC32C();

protected:
	// Overloaded from CReportBase
	void			OnBeginReport();
	unsigned short	OnCallbackFn(struct USR_TAB * pTableInfo);
	ReportReturn	OnBody();
	
private:
	void			loadData();
	void			centerReport();
	void			initLabels();

	MSLDate			OnGetEventDate() const;
	MSLTime			OnGetEventTime() const;

	unsigned short	reportHeader_CallBack	( struct USR_TAB *pTabInf );
	unsigned short	reportBody_CallBack		( struct USR_TAB *pTabInf );

private:
	CLis			*m_pLis;
	MSLSortedVector	m_vData;
	short			m_index;
	CHRLegends		*m_pLegend;

	CHInscription	*m_pInscription;
	CHMember		*m_pMember;
	CHEvent			*m_pEvent;

	MSLString		m_lastCountry;

};

