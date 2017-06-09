/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHTreeGUIEx.h
*   Description : 
*
*   Author      : Javier Juste
*   Date created: 2-FEb-2009
*   Project     : AR Manager
*
*   Modification history
*   By      :
*   Date    :
*   Changes :
*
*****************************************************************************************/

#include "StdAfx.h"
#include "CHTreeGUIEx.h"
#include "..\CHMngtModel\CHEvent.h"

CHTreeGUIEx::CHTreeGUIEx(long id, bool allEvents/*=false*/)
:GTHTreeGUIEx(id,allEvents)
{
}

CHTreeGUIEx::~CHTreeGUIEx(void)
{
}

MSLWString CHTreeGUIEx::getEventDescription(GTHEvent* pEvent)
{
	MSLWString eventDesc = pEvent ? pEvent->getSDescription() : NULLWSTRING;	
	eventDesc+=L" (";
	eventDesc+=TOWSTRING(((CHEvent*)pEvent)->getInscriptions(),L"0");
	eventDesc+=L")";
	return eventDesc;
}

