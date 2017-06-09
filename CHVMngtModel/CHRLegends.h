/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHRLegends.h
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

#include <OVR/Reports/V/RLegend.h>

class CHRLegends : public RLegend  
{
public:
	
	CHRLegends(CReportTemplate *pTpt, CReport *pRe, long id);
	virtual ~CHRLegends();

	void		setDynamic(const wchar_t *key);
	void		createDynamic();
	int			addReportNote(const wchar_t *title=0);

protected:
	bool		OnLoadLis();

private:
	void		printLegend(int start, int num_cols=1);
	int			getTypeBuffer(const wchar_t *pBuffer);
	void		loadData();

private:
	CLis*	m_pLis;

	int		m_idReport,
			m_idNote,
			m_idDynamic,
			m_idStatic;
};
