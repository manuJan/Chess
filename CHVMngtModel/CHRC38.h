/*************************************************************************************
*			© Copyright MSL Software, S.L., 2000 - 2008
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHRC38.h
*	Description	: Report C38
*
*	Author		: Jose Matas
*	Date created: 21 Enero 2009
* 	Project		: BKVMngtModel
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#pragma once
#include "CHVMngtModelDefs.h"
#include <OVR\REPORTS\V\RC38.h>

class CHRLegends;
class CHRegister;

class CHVMngtModelExport CHRC38 : public RC38  
{
public:
	
	CHRC38(CReportManager& aReportManager,CReportConfig& aReportConfig,const char *pGroup);
	CHRC38(CReportManager& aReportManager,CReportConfig& aReportConfig);
	virtual ~CHRC38() {};
	bool isValid();
	
	MSLWString	getFunction();
	MSLWString	OnGetLine(const int lineNumber,const char *language) const;
	void		OnNextGroup();
	void		setDynamicLegends(CHRegister *pReg);
	VCheckList	*OnNewCheckList	();

protected:
	ReportReturn OnBody();
	void initLabels();
	
protected:
	
	// from RC38	
	bool		OnLoadLis		();
	void		OnLisLoaded		();
	bool		OnLoadLabels	();
	RLegend		*OnCreateLegend	();	
	bool		OnExtendedLis	();

private:
	CLis		*m_pLis;	
	CHRLegends  *m_pLegends;

};

