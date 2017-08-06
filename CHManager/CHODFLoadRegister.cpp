/*************************************************************************************
*			© Copyright MSL Software, S.L., 2012
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: FEODFLoadRegister.cpp
*	Description	:
*
*	Author		: Fernando Martin
*	Date created: 23-Sep-2013
* 	Project		: FEManager
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#include "StdAfx.h"
#include "CHODFLoadRegister.h"
#include "CHMSLODFDataTransfer.h"

#include "..\CHMngtModel\CHMember.h"

CHODFLoadRegister::CHODFLoadRegister(GRegister* pRegister, MSLIPCDataTransferModule* module)
:ODFLoadRegister(pRegister, module)
{
}

CHODFLoadRegister::~CHODFLoadRegister()
{
}

void CHODFLoadRegister::endProcess(bool isTeam)
{
	if (isTeam)
		return;

	if (m_function=="AA01")
		m_pRegister->setType(GRegister::individual);
	else if (
		m_function.index("AO0") >= 0 ||
		m_function=="GEN_MGR"	||
		m_function=="TEM_LDR"	||
		m_function=="HED_COA"	||
		m_function=="AST_COA"	||
		m_function=="GOA_COA"	||
		m_function=="FIT_COA"	||
		m_function=="TEM_DOC"	||
		m_function=="PHY"		||
		m_function=="TEM_MSR"	||
		m_function=="VID_COA"	||
		m_function=="VID_COA"	)
		m_pRegister->setType(GRegister::teamOfficial);
	else
		m_pRegister->setType(GRegister::official);
}

void CHODFLoadRegister::onTeamOfficialFunction(GMember* pTeamOfficial, const char* function)
{
	CHMember* pTO = (CHMember*) pTeamOfficial;
	MSLString func = function;

}