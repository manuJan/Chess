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

#pragma once
#include "CHVMngtModelDefs.h"

class CHReportTemplate;
class CHSessionPoolRound;
class VCHSchedule;

class RCHSchedule  
{
public:
	RCHSchedule(CHReportTemplate * pTpt,CReport * pRe);
	virtual ~RCHSchedule();

	bool loadLis();
	void initLabels();
	bool runLis();
	unsigned short entries(struct USR_TAB * pTableInfo);
	VCHSchedule *getView();
	void assignVari(const short nVble, const int value);
	int getVari(const short nVble) const;
	bool paintNote();

protected:
	unsigned short assignData(struct USR_TAB * pTableInfo);
	void setData(int Ccount);

private:
	CHReportTemplate	* m_pReportTemplate;
	CReport				* m_pReport;
	CLis				* m_pLis;

	CHSessionPoolRound	* m_pCurrent,*m_pLst;
	VCHSchedule			* m_pView;	
	int					m_index;

	double	 m_adjust;
	int		 m_nLines;
	int		 m_nDate;
};

