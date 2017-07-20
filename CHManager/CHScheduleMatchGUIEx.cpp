/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHScheduleMatchGUIEx.cpp
*   Description : 
*
*   Author      : Javier Juste
*   Date created: 2-Feb-2010
*   Project     : AR Manager
*
*   Modification history
*   By      :
*   Date    :
*   Changes :
*
*****************************************************************************************/

#include "StdAfx.h"
#include "CHScheduleMatchGUIEx.h"

#include "..\CHMngtModel\CHMatch.h"
#include "..\CHMngtModel\CHMatchResult.h"

CHScheduleMatchGUIEx::CHScheduleMatchGUIEx(GTHScheduleData* pScheduleData, long id,bool filter/*=false*/)
:GTHScheduleMatchGUIEx(pScheduleData,id,filter)
{
}

CHScheduleMatchGUIEx::~CHScheduleMatchGUIEx(void)
{
}

MSLWString CHScheduleMatchGUIEx::getCompetitorsDescription	(GTHMatchResult *pMatchResult)
{
	if (pMatchResult->getRegister())
		return ((CHMatchResult*)pMatchResult)->getSName();
	
	return TOWSTRING(pMatchResult->getPoolPosition());
}

bool CHScheduleMatchGUIEx::canInsertScheduleMatch(GTHMatch *pMatch)
{
	if (pMatch->getSubCode())
		return false;

	return GTHScheduleMatchGUIEx::canInsertScheduleMatch(pMatch);
}