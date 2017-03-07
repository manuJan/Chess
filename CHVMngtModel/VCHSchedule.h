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
#if !defined(AFX_VCHSCHEDULE_H__4D586759_9811_48A4_B9B4_EDB68CD395CB__INCLUDED_)
#define AFX_VCHSCHEDULE_H__4D586759_9811_48A4_B9B4_EDB68CD395CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class VCHSchedule : public CReportView  
{
public:
	VCHSchedule();
	virtual ~VCHSchedule();
	int loadNextDate();

public:
	RWCString getDescription() const;
	int getID() const;
	RWDate getActualDate() const;
	void setDates();

private:
	RWBoolean build();

private:
	RWSet			colDateSessionPoolRound;
	unsigned long	dates[50];
	short			ndate;
	int				count,countDate;
};

#endif // !defined(AFX_VCHSCHEDULE_H__4D586759_9811_48A4_B9B4_EDB68CD395CB__INCLUDED_)
