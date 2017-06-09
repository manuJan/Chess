/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: ARReportTemplate.h
*   Description	:
*
*	Author		: ARTeam
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

#include <OVR\Reports\THV\THReportTemplate.h>

class CHVMngtModelExport CHReportTemplate : public THReportTemplate  
{

public:

	CHReportTemplate(CReportManager& aReportManager,CReportConfig& aReportConfig,const GTHEvent *pEvent=0);
	CHReportTemplate(CReportManager& aReportManager,CReportConfig& aReportConfig,const GTHPhase *pPhase);
	CHReportTemplate(CReportManager& aReportManager,CReportConfig& aReportConfig,const GTHMatch *pMatch);
	CHReportTemplate(CReportManager& aReportManager,CReportConfig& aReportConfig,MSLDate date);
	virtual ~CHReportTemplate();
	
	// GENERAL
	void			centerData(CLis *pLis, struct USR_TAB *pTabInf		, int desplX=10, int desplY=10);
	void			alignData (CLis *pLis, int tab, int dato, int desplX, int desplY);
	
	virtual bool	pageBreak(short value);
	void			setVaris(CLis *pLis);

protected:
	
	// Overwrite from CReportTemplate	
	MSLDate		OnGetEventDate() const;
	MSLTime		OnGetEventTime() const;	

protected:

	void setFontType(CLis *pRepLis, int fHead, MSLString init, MSLString end="");

protected:
	
	MSLDate dateSel;
	int font;
};


