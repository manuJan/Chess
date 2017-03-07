/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHVEntriesByNoc.h
*	Description	:Export Dll
*
*	Author		:Chess Team
*	Date created:19-12-2005
* 	Project		:Entries By Noc View
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#if !defined(AFX_CHVENTRIESBYNOC_H__766F4042_3DDF_477C_9DB3_9837DA97BB78__INCLUDED_)
#define AFX_CHVENTRIESBYNOC_H__766F4042_3DDF_477C_9DB3_9837DA97BB78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHVMNGTMODELDLL_H
	#include "CHVMngtModelDll.h"
#endif // _CHVMNGTNODELDLL_H

#include <Reports/V/ReportView.h>

class CHVMngtExport CHVEntriesByNoc : public CReportView  
{
public:
	CHVEntriesByNoc();
	virtual ~CHVEntriesByNoc()
		{;}

	RWCString getDescription() const;
	int getID() const;
	void rebuild();

private:
	void build();

protected:
	GVectorElement * insertRegister(GRegister *pRegister,const char *group);
	GVectorElement * insertGroup(const char *group);

};

#endif // !defined(AFX_CHVENTRIESBYNOC_H__766F4042_3DDF_477C_9DB3_9837DA97BB78__INCLUDED_)
