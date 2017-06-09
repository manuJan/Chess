/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHPairDraw.cpp
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
#include "CHPairDraw.h"
#include "..\CHMngtModel\CHMatch.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHPairDraw::CHPairDraw(CHGroupDraw *_pGroupDraw, CHMatch* _pMatch, short _order)
:pGroupDraw(_pGroupDraw)
,pMatch(_pMatch)
,order(order)
{
	setKey();
}

CHPairDraw::~CHPairDraw()
{

}

void CHPairDraw::setKey() 
{
	if (pMatch)
	{
		key=pMatch->getKey();
	}
	else
	{
		char tmp[100];
		sprintf_s(tmp,"%d",order);
		key=tmp;
	}
}

bool CHPairDraw::operator !=(const GData& copy)
{
	return !operator==(copy);
}

bool CHPairDraw::operator ==(const GData& copy)
{
	CHPairDraw & aCopy = (CHPairDraw & )copy;

	bool value= false;

	if ( pMatch		==	aCopy.pMatch	&&
		 order		==	aCopy.order	)
		 value= true;

	return value;
}

GData& CHPairDraw::operator =(const GData& copy)
{
	CHPairDraw & aCopy = (CHPairDraw & )copy;

	pMatch			=   aCopy.pMatch;
	order			=	aCopy.order;	

	return *this;
}

CHMatch* CHPairDraw::getMatch()
{
	return pMatch;
}

short CHPairDraw::getOrder()
{
	return order;
}

CHCompetitorDraw* CHPairDraw::getWhite()
{
	return pWhite;
}
	
CHCompetitorDraw* CHPairDraw::getBlack()
{
	return pBlack;
}

CHGroupDraw* CHPairDraw::getGroupDraw()
{
	return pGroupDraw;
}

void CHPairDraw::setMatch(CHMatch* value)
{
	pMatch = value;
	setKey();
}

void CHPairDraw::setOrder(short value)
{
	order = value;
	setKey();
}

void CHPairDraw::setWhite(CHCompetitorDraw* value)
{
	pWhite = value;
}

void CHPairDraw::setBlack(CHCompetitorDraw* value)
{
	pBlack = value;
}