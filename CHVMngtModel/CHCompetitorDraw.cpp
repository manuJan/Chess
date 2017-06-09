/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHCompetitorDraw.cpp
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:23-12-2005
*   Project     :CHV Model               
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///

#include "stdafx.h"
#include "CHCompetitorDraw.h"
#include "..\CHMngtModel\CHPoolResult.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


static
bool matchResultsOfPoolResult(const MSLItem * col, const void * param)
{
	CHPoolResult * pPoolResult = (CHPoolResult *) param;
	CHMatchResult  * pMatchResult = (CHMatchResult*) col;
	
	if (pMatchResult->getEvent() == pPoolResult->getEvent() &&
		pMatchResult->getRegister() &&
		pPoolResult->getRegister() &&
		pPoolResult->getRegister() == pMatchResult->getRegister())
		return true;

	return false;
}


CHCompetitorDraw::CHCompetitorDraw(CHPoolResult* _pPoolResult, short _order, short _round)
:pPoolResult(_pPoolResult)
,order(_order)
,round(_round)
,alreadyPaired(false)
,floatingDown(false)
,floatingUp(false)
{
	setKey();
}

CHCompetitorDraw::~CHCompetitorDraw()
{

}

void CHCompetitorDraw::setKey() 
{
	if (pPoolResult)
	{
		key=pPoolResult->getKey();
	}
}

bool CHCompetitorDraw::operator !=(const GData& copy)
{
	return !operator==(copy);
}

bool CHCompetitorDraw::operator ==(const GData& copy)
{
	CHCompetitorDraw& aCopy = (CHCompetitorDraw&) copy;

	bool value= false;

	if ( pPoolResult==	aCopy.pPoolResult	&&
		 order		==	aCopy.order	)
		 value= true;

	return value;
}

GData& CHCompetitorDraw::operator =(const GData& copy)
{
	CHCompetitorDraw& aCopy = (CHCompetitorDraw&) copy;

	pPoolResult		=   aCopy.pPoolResult;
	order			=	aCopy.order;	

	return *this;
}

CHPoolResult* CHCompetitorDraw::getPoolResult()
{
	return pPoolResult;
}

short CHCompetitorDraw::getOrder()
{	
	return order;
}

short CHCompetitorDraw::getPoolResultCode()
{
	return pPoolResult?pPoolResult->getOrder():0;
}

bool CHCompetitorDraw::getPoolResultBye()
{
	return pPoolResult?pPoolResult->getBye():false;
}

CHInscription* CHCompetitorDraw::getPoolResultInscription()
{
	return pPoolResult?(CHInscription*)pPoolResult->getInscription():0;
}

bool CHCompetitorDraw::getAlreadyPaired()
{
	return alreadyPaired;
}

bool CHCompetitorDraw::getFloatingDown()
{
	return floatingDown;
}

bool CHCompetitorDraw::getFloatingUp()
{
	return floatingUp;
}
	
void CHCompetitorDraw::setAlreadyPaired(bool value)
{
	alreadyPaired=value;
}

void CHCompetitorDraw::setFloatingDown(bool value)
{
	floatingDown = value;
}

void CHCompetitorDraw::setFloatingUp(bool value)
{
	floatingUp = value;
}

void CHCompetitorDraw::setOrder(short value)
{
	order = value;
}

bool CHCompetitorDraw::hasSameColorTwoLast()
{
	return false;
}

bool CHCompetitorDraw::hasAlreadyBye(short round)
{
	if (pPoolResult)
		return pPoolResult->hasAlreadyBye(round);
	return false;
}
	
bool CHCompetitorDraw::hasAlreadyNotOpponent()
{
	return false;
}
	


short CHCompetitorDraw::getColorDiference(CHPoolResult* pPoolResult)
{
	return 0;
}


CHMatchResult::colorPreference CHCompetitorDraw::getColorPreference(short round)
{
	if (pPoolResult)
		return pPoolResult->getColorPreference(round);
	return CHMatchResult::eDraw;
}

CHMatchResult::side  CHCompetitorDraw::getSidePreference(short round)
{
	if (pPoolResult)
		return pPoolResult->getSidePreference(round);
	return CHMatchResult::eNone;
}
