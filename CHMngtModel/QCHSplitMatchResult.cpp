/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : QCHSplitMatchResult.cpp                                                                 
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:13-12-2005
*   Project     :CH Model
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///


#include "stdCHMngt.h"
#include "QCHSplitMatchResult.h"
#include "CHSplitMatchResult.h"


void QCHSplitMatchResult::OnSelect(RWDBSelector& aSelect,RWDBTable& table)
{
	QGTHSplitMatchResult::OnSelect(aSelect,table);
	
}

void QCHSplitMatchResult::OnReader(RWDBReader& aReader,GTHSplitMatchResult *pValue)
{
	QGTHSplitMatchResult::OnReader(aReader,pValue);

	CHSplitMatchResult* pVal = (CHSplitMatchResult*)pValue;
	
	UNREFERENCED_PARAMETER(pVal);
		
}

GTHSplitMatchResult * QCHSplitMatchResult::OnNewSplitMatchResult()
{
	return new CHSplitMatchResult();
}