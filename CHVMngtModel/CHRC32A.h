/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHRC32C.h
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
class CHEvent;
class CHMember;
class CHRegister;

class CHVMngtModelExport CHRC32A : public CHReportTemplate
{
public:
	CHRC32A(CReportManager& aReportManager,CReportConfig& aReportConfig);
	virtual ~CHRC32A();

protected:
	// Overloaded from CReportBase
	void			OnBeginReport();
	unsigned short	OnCallbackFn(struct USR_TAB * pTableInfo);
	ReportReturn	OnBody();
	void			initVaris();
	void			initLabels();

private:
	void			loadData();
	void			centerReport();

	unsigned short	reportHeader_CallBack	( struct USR_TAB *pTabInf );
	unsigned short	reportBody_CallBack		( struct USR_TAB *pTabInf );
	int				getGroupSize			( MSLString group );

	int				loadEvents();
	MSLString		inscriptedMark(CHEvent * pEvent);
	CHMember *		findMember(CHEvent *pEvent, CHRegister *pRegister);

private:
	CLis			*m_pLis;
	MSLSortedVector	m_vData;
	short			m_index;
	CHRLegends		*m_pLegend;

	CHInscription	*m_pInscription;
	bool			m_paintGroup;	
	MSLSortedVector	m_vEvents;
	int				m_numEvents;
};
