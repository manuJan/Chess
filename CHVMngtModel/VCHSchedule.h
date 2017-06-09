/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: VCHSchedule.h
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

class CHSessionPoolRound;

class VCHSchedule 
{
public:
	VCHSchedule();
	virtual ~VCHSchedule();
	int loadNextDate();

public:
	
	MSLDate getActualDate() const;
	void setDates();	
	CHSessionPoolRound * getData(short index);
	short getEntries();

private:

	bool build();

private:

	MSLSortedVector	m_vector;
	MSLSet			m_colDateSessionPoolRound;
	unsigned long	m_dates[50];
	short			m_ndate;
	int				m_count,m_countDate;
};


