/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHRC30.h
*	Description	:Export Dll
*
*	Author		:Chess Team
*	Date created:19-12-2005
* 	Project		: Number Entries By Noc Report
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#if !defined(AFX_CHRC30_H__C064208C_8766_4E49_95DF_C4D2F885CF30__INCLUDED_)
#define AFX_CHRC30_H__C064208C_8766_4E49_95DF_C4D2F885CF30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CHVMngtModelDll.h"

#include "CHReportTemplate.h"
#include <Reports/V/V03Inscription.h>
class CHRLegends;


class CHVMngtExport CHRC30 : public CHReportTemplate  
{
public:
	CHRC30(CReportManager& aReportManager,CReportConfig& aReportConfig);
	virtual ~CHRC30();

	
protected:
	// Overloaded member function
	ReportReturn OnBody();
	unsigned short OnCallbackFn( struct USR_TAB * pTableInfo );
	unsigned short tablaCabecera( struct USR_TAB * pTableInfo );
	unsigned short tablaGroups( struct USR_TAB * pTableInfo );
	unsigned short tablaTotals( struct USR_TAB * pTableInfo );

private:
	void OnBeginReport();
	CReportBase::ReportReturn paintHeader();
	CReportBase::ReportReturn paintLegend();
	CReportBase::ReportReturn paintGroup();
	CReportBase::ReportReturn paintTotals();
	void setDataGroup(GGroup* pGroup);
	void setDataTotals();
	void setVariables30();
	CReportBase::ReportReturn paintAsOf();

	int getEntriesByEvent();
	int getMenOfGroup();
	int getWomenOfGroup();
	void setMenOfGroup();
	void setWomenOfGroup();

	void insertRegister(CHRegister* pRegister);

	RWCString getEventsDescription();
	RWDate OnGetEventDate() const;
	RWTime OnGetEventTime() const;

	void setDynamicLegends();

private:
	V03Inscription aV03Inscription;
	V03Inscription aV03InscAux;
	CReportManager *pReportMng;
	GData *pData;
	CLis *pLis;
	GSortedVector vEvents;
	GGroup* pGroupSel;
	size_t index;
	RWOrdered vIndex;
	int totalMen;
	int totalWomen;
	int totalTotal;
	int totalGroups;
	RWSet colMenRegisters;
	RWSet colWomenRegisters;
	CHRLegends* pLegends;
};

#endif // !defined(AFX_CHRC30_H__C064208C_8766_4E49_95DF_C4D2F885CF30__INCLUDED_)
