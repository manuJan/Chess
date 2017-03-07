/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHRC51G.cpp
*   Description	: 
*
*	Author		: CH Team
*	Date created: 24-12-2005
* 	Project		:
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#include "stdVCH.h"
#include "CHRC51G.h"
#include "CHRPool.h"

#include <SPORTS/CH/DATA/CHMemoryDataBase.h>
#include <SPORTS/CH/DATA/CHEvent.h>
#include <SPORTS/CH/DATA/CHInscription.h>
#include <SPORTS/CH/DATA/CHMember.h>
#include <SPORTS/CH/DATA/CHRegister.h>
#include "CHRLegends.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHRC51G::CHRC51G(CReportManager& aReportManager,CReportConfig& aReportConfig, CHEvent* _pEvent)
:CHRC76(aReportManager,aReportConfig,_pEvent,CHRC76::eSchedule)
,pLegend(0)
{
}

CHRC51G::~CHRC51G()
{
	//if( pLegend )
	//	delete pLegend;
}

void CHRC51G::onLook()
{
}

void CHRC51G::OnBeginReport()
{
	CHRC76::OnBeginReport();

	// Iniciamos leyendas
	//pLegend = new CHRLegends (this, pReport);
//	pLegend->showLegend(CHRLegends::e76A);
}

CReportBase::ReportReturn CHRC51G::OnBody()
{	
	//pLegend->print();
	ReportReturn rc = CHRC76::OnBody();	
	return rc;
}

RWBoolean CHRC51G::pageBreak(short value)
{
	return IsPageBreak(short(value/*+pLegend->calculateHeight()*/));
}

RWDate CHRC51G::OnGetEventDate() const
{
	return INVALID_RWDATE;
}

RWTime CHRC51G::OnGetEventTime() const
{
	return INVALID_RWTIME;
}