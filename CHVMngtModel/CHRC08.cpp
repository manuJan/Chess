/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHRC08.cpp
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
#include "stdafx.h"
#include "CHRC08.h"
#include "RCHSchedule.h"
#include "VCHSchedule.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHRC08::CHRC08(CReportManager& aReportManager,CReportConfig& aReportConfig)
:CHReportTemplate(aReportManager,aReportConfig)
,m_bNewPage(true)
{
	m_pSchedule=new RCHSchedule(this,m_pReport);
}

CHRC08::~CHRC08()
{
	if (m_pSchedule)		
		delete m_pSchedule;
}

void CHRC08::OnBeginReport()
{
	m_bOkLis=m_pSchedule->loadLis();
	m_bHeaderAsOf=true;
}

unsigned short CHRC08::OnCallbackFn(struct USR_TAB * pTableInfo)
{
	if (pTableInfo->Tb>=101 && pTableInfo->Tb<=103)
		return m_pSchedule->entries(pTableInfo);

	return PRNALL;
}

bool CHRC08::OnRun()
{
	CReportBase::ReportReturn rc=ok;
	int nLin=0;
	
	do
	{
		nLin = m_pSchedule->getView()->loadNextDate();
		if( nLin==-1 )
			break;
		m_pSchedule->assignVari(10,nLin);

		if( IsPageBreak(short(((nLin+2)*80)+150)) )
		{
			m_bNewPage = true;
			rc=OnFootHeader(true);
		}

		if( rc!=error )
			rc=body(nLin);
	}
	while( rc<exit );

	if( rc!=error )
		rc=OnFootHeader(false);
	
	if ( rc==error ) 
		return false;
	return true;
}

CReportBase::ReportReturn CHRC08::body(const int nLin)
{
	
	if( nLin==-1 )
		return error;
	//pinto as of
	m_pSchedule->assignVari( 4, m_bNewPage?true:false);
	m_pSchedule->assignVari(2023, m_bNewPage ? 10 : m_pReport->getYCoor());
	m_bNewPage = false;
	if( m_pSchedule->runLis() )
		return ok;
	return error;
}

MSLDate CHRC08::OnGetEventDate() const
{
	return INVALID_DATE;
}

MSLTime CHRC08::OnGetEventTime() const
{
	return INVALID_TIME;
}