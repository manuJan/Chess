/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHTVGUI.h
*	Description	:
*
*	Author		: 
*	Date created: 11-Dec-2009
* 	Project		: CH TV
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#pragma once
#include <ovr/gui/mslapp/mslappModuleTv.h>
#include "CHTVTools.h"

class CHTVGUI: public MSLAppModuleTV
{
public:
	CHTVGUI(long id);
	virtual ~CHTVGUI();

	// Required files & fields
	virtual void  callForRequiredFiles	();
	virtual void  callForPaths			();		
	virtual void  callForContent		(long level,MSLString name,DWORD dataParent);
	virtual bool  callForIsRequired		(long level,MSLString name,DWORD dataParent);

	virtual void onComms				(MSLTransaction &pt);
	virtual void onComms				(long idTrn,bool bInsert,GData *pData,long index);

	// WU
	bool validateDate(MSLDate aDate);
	bool validateSession(const short acc);

protected:
	virtual bool onInit					();

private:
	bool preprocessNotifies				(MSLTransaction &pt);
	
	bool preprocessTrnOfficials			(MSLTransaction &pt);
	bool preprocessTrnDataEntry			(MSLTransaction &pt);
	bool preprocessTrnProgression		(MSLTransaction &pt);
	bool preprocessTrnMedals			(MSLTransaction &pt);
	bool preprocessTrnRankings			(MSLTransaction &pt);
	void updateModel					(MSLTransaction &pt);

private:
	CHMemoryDataBase*	m_pMem;
	CHTVTools			m_tools;
};
