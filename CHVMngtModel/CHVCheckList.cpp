/*************************************************************************************
*			© Copyright MSL Software, S.L., 2000 - 2008
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHVCheckList.h
*	Description	: Implementation for the CHVCheckList class.
*
*	Author		: Jose Matas
*	Date created: 21 Enero 2009
* 	Project		: BKVMngtModel
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdafx.h"
#include "CHVCheckList.h"
#include "CHGCheckList.h"

/////////////////////////////////////////////////////////////////////
CHVCheckList::CHVCheckList(const char *group,CheckMode _mode,const char* lang/*=0*/)
:VCheckList(group,_mode)
,m_mode(_mode)
,m_language(lang)
{

}

/////////////////////////////////////////////////////////////////////
CHVCheckList::~CHVCheckList()
{

}

/////////////////////////////////////////////////////////////////////
GCheckList * CHVCheckList::OnCreate(GRegister *pRegister)
{
	CHGCheckList *pCHGCheck = new CHGCheckList();
	if (pCHGCheck)
		pCHGCheck->setRegister((CHRegister *)pRegister,m_language);
	
	return (GCheckList*)pCHGCheck;
}

