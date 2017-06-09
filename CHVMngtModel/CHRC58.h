/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHRC58.h
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

class CHMatch;
class CHRLegends;

class CHVMngtModelExport CHRC58 : public CHReportTemplate  
{
public:
	CHRC58(CReportManager& aReportManager, CReportConfig& aReportConfig, MSLDate aDate);
	virtual ~CHRC58();

protected:
	// Overloaded member function
	ReportReturn OnBody();
	unsigned short OnCallbackFn( struct USR_TAB * pTableInfo );
	unsigned short tablaHeader( struct USR_TAB * pTableInfo );
	unsigned short tablaMatch( struct USR_TAB * pTableInfo );

private:
	void OnBeginReport();
	CReportBase::ReportReturn paintDateEvent();
	CReportBase::ReportReturn paintHeader();
	CReportBase::ReportReturn paintMatch();
	CReportBase::ReportReturn paintLegend();
	void centerReport();
	void initLabels();

	void		setDataMatch(CHMatch* pMatch);
	MSLWString	getSessionDetailed();
	void		setDynamicLegends();
	
	
	MSLSortedVector	getMatchesSession(GSession *pSession);
	void			buildVector();
	MSLDate			OnGetEventDate() const;
	MSLTime			OnGetEventTime() const;
	

private:
	
	CReportManager	*m_pReportMng;
	GData			*m_pData;
	CLis			*m_pLis;
	GSession		*m_pSession;
	MSLDate			m_date;
	CHRLegends		* m_pLegends;
	bool       m_paintSession;
	MSLSortedVector m_vMatches;
	short			m_posVector;
};


