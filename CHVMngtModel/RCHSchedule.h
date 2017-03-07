/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: RCHSchedule.h
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
#if !defined(AFX_RCHSCHEDULE_H__CC912396_E4E3_45A6_B7E2_4102F09A2049__INCLUDED_)
#define AFX_RCHSCHEDULE_H__CC912396_E4E3_45A6_B7E2_4102F09A2049__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHVMNGTDLL_H
	#include "CHVMngtModelDll.h"
#endif // _CHVMNGTDLL_H

class CHReportTemplate;
class CReport;
class CReportBase;
class CReportManager;
class CLis;
class CHSessionPoolRound;
class VCHSchedule;
class RCHSchedule  
{
public:
	RCHSchedule(CHReportTemplate * pTpt,CReport * pRe);
	virtual ~RCHSchedule();

	RWBoolean loadLis();
	RWBoolean runLis();
	unsigned short entries(struct USR_TAB * pTableInfo);
	VCHSchedule *getView();
	void assignVari(const short nVble, const int value);
	int getVari(const short nVble) const;
	RWBoolean paintNote();

protected:
	unsigned short assignData(struct USR_TAB * pTableInfo);
	void setData(int Ccount);

private:
	CHReportTemplate	* pReportTemplate;
	CReport				* pReport;
	CLis				* pLis;

	CHSessionPoolRound	* pCurrent,*pLst;
	VCHSchedule			* pView;

	double	 adjust;
	int		 nLines;
	int		 nDate;
};

#endif // !defined(AFX_RCHSCHEDULE_H__CC912396_E4E3_45A6_B7E2_4102F09A2049__INCLUDED_)
