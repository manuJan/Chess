/*************************************************************************************
*			© Copyright MSL Software, S.L., 2009
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHMsgGnralGUI.cpp
*	Description	:
*
*	Author		: 
*	Date created: 11-1-2010
* 	Project		: AR Manager
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "StdAfx.h"
#include "CHMsgGnralGUI.h"

CHMsgGnralGUI::CHMsgGnralGUI(long id)
:GMsgGnralGUI(id)
{
}

CHMsgGnralGUI::~CHMsgGnralGUI(void)
{
}

CHMemoryDataBase * CHMsgGnralGUI::getMem() const
{
	return (CHMemoryDataBase*) CHMemoryDataBase::getMem();
}

MSLString CHMsgGnralGUI::getHeaderRSC(GData * pData)
{
	if( !pData )
		return "";

	MSLString rsc("");
	if( pData->isA()==__GEVENT )
		rsc = GET_RSC(pData);
	return rsc;
}