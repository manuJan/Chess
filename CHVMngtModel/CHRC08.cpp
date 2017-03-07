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
#include "stdVCH.h"
#include "CHRC08.h"
#include "RCHSchedule.h"
#include "VCHSchedule.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHRC08::CHRC08(CReportManager& aReportManager,CReportConfig& aReportConfig)
:CHReportTemplate(aReportManager,aReportConfig)
,bNewPage(true)
{
	pSchedule=new RCHSchedule(this,pReport);
}

CHRC08::~CHRC08()
{
	if (pSchedule)		delete pSchedule;
}

void CHRC08::OnBeginReport()
{
	bOkLis=pSchedule->loadLis();
	bHeaderAsOf=true;
//	properties();
	prepareTemplate();
	
}

unsigned short CHRC08::OnCallbackFn(struct USR_TAB * pTableInfo)
{
	if (pTableInfo->Tb>=101 && pTableInfo->Tb<=103)
		return pSchedule->entries(pTableInfo);
	return PRNALL;
}

RWBoolean CHRC08::OnRun()
{
	CReportBase::ReportReturn rc=ok;
	int nLin=0;
	
	do
	{
		nLin = pSchedule->getView()->loadNextDate();
		if( nLin==-1 )
			break;
		pSchedule->assignVari(10,nLin);

		if( IsPageBreak(short(((nLin+2)*80)+150)) )
		{
			bNewPage = true;
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
	pSchedule->assignVari( 4, bNewPage?true:false);
	pSchedule->assignVari(2023, bNewPage?pLis->getVari(2022):pReport->getYCoor());
	bNewPage = false;
	if( pSchedule->runLis() )
		return ok;
	return error;
}

CReportBase::ReportReturn CHRC08::OnFootHeader(const RWBoolean bNPg/*=true*/)
{
	if (!bNPg)
	{
//		pSchedule->paintNote();
//		paintLegend();
	}
	return CReportTemplate::OnFootHeader(bNPg);
}

RWDate CHRC08::OnGetEventDate() const
{
	return INVALID_RWDATE;
}

RWTime CHRC08::OnGetEventTime() const
{
	return INVALID_RWTIME;
}