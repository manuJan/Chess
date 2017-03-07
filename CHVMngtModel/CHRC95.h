/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHRC95.h
*   Description	: 
*
*	Author		: CH Team
*	Date created: 5-1-2006
* 	Project		:
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#if !defined(AFX_CHRC95_H__3027FC19_C446_4909_A842_D2FB59314693__INCLUDED_)
#define AFX_CHRC95_H__3027FC19_C446_4909_A842_D2FB59314693__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHVMNGTDLL_H
	#include "CHVMngtModelDll.h"
#endif // _CHVMNGTDLL_H

#include "CHReportTemplate.h"
#include <Reports/V/VMedalStandings.h>
#include "CHRLegends.h"

class GMedalsByNoc;

class CHVMngtExport CHRC95 : public CHReportTemplate  
{
public:
	CHRC95(CReportManager & aReportManager,CReportConfig& aReportConfig);
	virtual ~CHRC95();

protected:
	virtual void OnBeginReport();
	virtual ReportReturn OnBody();
	virtual RWCString getNameOfSourceLis();
	//bool paintSexEventInfo();			// -- Pintamos sexo, y/o evento.
	// Devolver la coleccion de GEvent que se van a pintar en las leyendas
	RWSet		fillColEventsMedals();
	
private:
	bool		otherHasEqualRank(GMedalsByNoc *pMedalsByNoc);
	RWDate		OnGetEventDate() const;
	RWTime		OnGetEventTime() const;

protected:
	CLis *pLis;
	bool  okLis;
	VMedalStandings aVMedalStandings; // GMedalsByNoc

private:
	RWSet eventsMedals;
	CHRLegends    *pLegend; 
};

#endif // !defined(AFX_CHRC95_H__3027FC19_C446_4909_A842_D2FB59314693__INCLUDED_)
