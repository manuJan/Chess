/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHRC30.h
*	Description	:
*				 
*	Author		: Javier Juste
*	Date created: 5-Jul-2006
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

class CHVMngtModelExport CHRC30: public CHReportTemplate
{
public:
	CHRC30(CReportManager& aReportManager,CReportConfig& aReportConfig);
	virtual ~CHRC30();

protected:
	// Overloaded from CReportBase
	void			OnBeginReport();
	unsigned short	OnCallbackFn(struct USR_TAB * pTableInfo);
	ReportReturn	OnBody();

private:
	void			loadData();
	void			centerReport();
	void			initLabels();
	void			initVaris();
	int				getNumEvents();

	unsigned short	reportHeader_CallBack	( struct USR_TAB *pTabInf );
	unsigned short	reportBody_CallBack		( struct USR_TAB *pTabInf );
	unsigned short	reportTotals_CallBack	( struct USR_TAB *pTabInf );

private:
	CLis*			m_pLis;
	MSLSortedVector	m_vData;
	MSLSortedVector	m_vEvents;
	short			m_index;	
	GGroup			*m_pGroup;
	int				m_men;
	int				m_women;
	int				m_total;
	int				m_countries;
	int				m_t_men;
	int				m_t_women;
	int				m_t_total;
	int				m_numEvents;
	int				*m_division;
	int				*m_t_division;

	CHRLegends		*m_pLegend;
};

