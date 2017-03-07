/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHDFProcessExt.h
*	Description	:
*
*	Author		: Chess Team
*	Date created: 17-may-2006
* 	Project		: Chess DataFeed
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#if !defined(AFX_CHDFPROCESSEXT_H__ACA2E03D_0C78_40DA_976E_A032C469EC37__INCLUDED_)
#define AFX_CHDFPROCESSEXT_H__ACA2E03D_0C78_40DA_976E_A032C469EC37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <GUI/DF/DFProcessExt.h>

class CHDFProcessExt : public DFProcessExt  
{
public:
	CHDFProcessExt(DFGUI * pGUI);
	virtual ~CHDFProcessExt();

	void processTransactions(CPackTransaction& pt);

private:
	void proccessRemoveEvent(CPackTransaction &packTransaction);
	void processRemoveRegister(CPackTransaction &packTransaction);
	void proccessRemoveInscription(CPackTransaction &packTransaction);
	void processSetModality(CPackTransaction &packTransaction);
	void removePhase(CPackTransaction &packTransaction);
	void proccessRemovePhase(CHPhase * pPhase);
	void proccessRemovePool(CPackTransaction &packTransaction);
	void proccessRemoveMatch(CPackTransaction &packTransaction);
	void proccessRemoveMatchResult(CPackTransaction &packTransaction);
	void proccessRemovePoolResult(CPackTransaction &packTransaction);

	void addRecord(RWClassID classID, GData * pData, short type);

private:
	CHMemoryDataBase * m_pCHMem;
};

#endif // !defined(AFX_CHDFPROCESSEXT_H__ACA2E03D_0C78_40DA_976E_A032C469EC37__INCLUDED_)
