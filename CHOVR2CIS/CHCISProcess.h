/*************************************************************************************
*			© Copyright MSL Software, S.L., 2008
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHCISProcess.h
*	Description	:
*
*	Author		: Javier Juste
*	Date created: 28-03-2011
* 	Project		: BKOVR2CIS
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#pragma once
#include <ovr\gui\thovr2cis\GTHCISProcess.h>

#define CHPROCESS CHCISProcess::chProcess

class CHMatchResult;
class CHPoolResult;
class CHRegister;

class CHCISProcess : public GTHCISProcess
{
public:
	CHCISProcess();
	virtual ~CHCISProcess();

	MSLWString CHCISProcess::getMatchSDescription(CHMatch *pMatch, const char * lang);
	MSLWString CHCISProcess::getMatchLDescription(CHMatch *pMatch, const char * lang);

	bool onCreateScreens(long idScreen);
	MSLString getScreenDesign(long idScreen, GData* pData=0);

protected:

	void fillColItems							(long idItem, MSLSet & col);

	GCISScreen	* onNewScreen					(long idScreen, MSLString key, MSLString name, MSLString designFile, GData * pData=0);
	GCISItem	* onNewItem						(GData * pData, long idItem);

	void setRefRegister							(GRegister * pRegister, MSLString lang, bool bInsert);
	void setRefSchUnitResult					(GCISItemSchUnitResult * pCISScheduleUnitResult, MSLString lang, bool bInsert);
	void setRefMatch							(GTHMatch* pMatch, MSLString lang, bool bInsert);
	void setRefMatchResult						(GTHMatchResult* pMatchResult , MSLString lang, bool bInsert);	
	void setRefPoolResult						(GTHPoolResult* pPoolResult , MSLString lang, bool bInsert);	
	
	MSLString getDataRef						(GData* pData, MSLString reference, MSLString lang, bool bInsert);	
	MSLString getDataRefMatch					(CHMatch* pMatch, MSLString reference, MSLString lang, bool bInsert);	
	MSLString getDataRefMatchResult				(CHMatchResult* pMatchResult, MSLString reference, MSLString lang, bool bInsert);	
	MSLString getDataRefPoolResult				(CHPoolResult* pPoolResult, MSLString reference, MSLString lang, bool bInsert);
	MSLString getDataRefScheduleUnitRes			(GCISItemSchUnitResult* pItemSchUnitResult, MSLString reference, MSLString lang, bool bInsert);
	
	MSLWString getDataRefW						(GData* pData, MSLString reference, MSLString lang, bool bInsert);
	MSLWString getDataRefWRegister				(CHRegister* pRegister, MSLString reference, MSLString lang, bool bInsert);	
	
	bool isTrnScheduleChange					(long idTrn);
	mslToolsFcCompare getOrderPoolResults		(long idScreen, GData* pData);
	mslToolsFcCompare getOrderReferees			(long idScreen, GData* pData);
	
	unsigned char getRoundStatus				(CHMatch * pMatch);
public:

	// Static variables
	static CHCISProcess * chProcess;
};
