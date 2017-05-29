/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : QCHMatchResult.cpp
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:07-12-2005
*   Project     :CH Model
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///

#include "stdCHMngt.h"
#include "QCHMatchResult.h"
#include "CHMatchResult.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void QCHMatchResult::OnSelect(MSLDBSelector& aSelect,MSLDBTable& tMatchResult)
{
	aSelect << tMatchResult["POINTS_F"]
			<< tMatchResult["UPFLOATER"]
			<< tMatchResult["DOWNFLOATER"]
			<< tMatchResult["COLOR"]
			;
}

void QCHMatchResult::OnReader(MSLDBReader& aReader,GTHMatchResult *pMatchResult)
{
	float fPoints;
	short upFloater;
	short downFloater;
	short fColor;

	
	aReader	>> fPoints
			>> upFloater
			>> downFloater
			>> fColor
			;

	CHMatchResult* pCHMatchResult=(CHMatchResult* )pMatchResult;
	pCHMatchResult->setPoints(fPoints);
	pCHMatchResult->setUpFloater(upFloater==1);
	pCHMatchResult->setDownFloater(downFloater==1);
	pCHMatchResult->setColor(fColor);
}
