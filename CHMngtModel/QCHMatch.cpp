/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : QCHMatch.cpp
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
#include "QCHMatch.h"
#include "CHMatch.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void QCHMatch::OnSelect(MSLDBSelector& aSelect,MSLDBTable& tMatch)
{
	aSelect << tMatch["IDTYPE"]			
			<< tMatch["ROUND"];
}

void QCHMatch::OnReader(MSLDBReader& aReader,GTHMatch *pMatch)
{
	short fMatchType, fRound;
	

	MSLDBNullIndicator nullMatchType;
	MSLDBNullIndicator nullRound;


	aReader	>> nullMatchType		>> fMatchType
			>> nullRound			>> fRound
			;


	CHMatch *pNewMatch=(CHMatch *)pMatch;
	
	//matchType
	if (nullMatchType) 
		fMatchType=CHMatch::eNone;
	
	pNewMatch->setMatchType(fMatchType);
	
	pNewMatch->setRound(fRound);
}
