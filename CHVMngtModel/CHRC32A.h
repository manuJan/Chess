/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHRC32A.h
*	Description	: Export Dll
*
*	Author		: Chess Team
*	Date created: 19-12-2005
* 	Project		: Entry List By Noc Report
*	
* 	Modification history
*	By			:                    
*	Date		: 
*	Changes		: 
*
***************************************************************************************/

#if !defined(AFX_CHRC32A_H__9D90FFB4_D26F_4FE7_9F80_BB15740FEE3D__INCLUDED_)
#define AFX_CHRC32A_H__9D90FFB4_D26F_4FE7_9F80_BB15740FEE3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CHVMngtModelDll.h"

#include "CHReportTemplate.h"
#include "CHVEntriesByNoc.h"

class CHMember;
class CHInscription;
class CHRLegends;

class CHVMngtExport CHRC32A : public CHReportTemplate  
{
public:
	CHRC32A(CReportManager& aReportManager,CReportConfig& aReportConfig);
	virtual ~CHRC32A();
	
protected:
	// Overloaded member function
	ReportReturn	OnBody();
	unsigned short	OnCallbackFn( struct USR_TAB * pTableInfo );
	unsigned short	tHeader( struct USR_TAB * pTableInfo );
	unsigned short	tDetails( struct USR_TAB * pTableInfo );

private:
	void						OnBeginReport();
	CReportBase::ReportReturn	paintHeader();
	CReportBase::ReportReturn	paintDetails();
	
	CHMember					*findMember(CHEvent *pEvent, CHRegister *pRegister);
	GVectorElement				*isInscription(CHInscription* pInscription);
	void						insertInscription(CHInscription* pInscription);
	int							getVirtualRanking(GVectorElement* pAux);
	void						deleteInscriptionsVector();	

	CReportBase::ReportReturn	paintLegend();
	RWCString					assignAsterikEvent();
	RWDate						OnGetEventDate() const;
	RWTime						OnGetEventTime() const;
	void						setDynamicLegends();

private:
	CHVEntriesByNoc aVEntriesByNoc;
	CReportManager	*pReportMng;
	CLis			*pLis;
	GSortedVector	vEvents;
	CHRegister		*pRegisterSel;
	size_t			index;
	RWOrdered		vIndex;
	int				nRegisters;
	int				counterRegisters;
	RWBoolean		first;
	RWBoolean		breakPage;
	CHRLegends		*pLegends;
	
};

#endif // !defined(AFX_CHRC32A_H__9D90FFB4_D26F_4FE7_9F80_BB15740FEE3D__INCLUDED_)
