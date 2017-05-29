/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : QCHMember.cpp
*   Description :                                                                      
*                                                                                      
*   Author      :Lawn Bowls Team
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
#include "QCHMember.h"
#include "CHMember.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void QCHMember::OnSelect(MSLDBSelector& aSelect,MSLDBTable& tMember)
{
	QMember::OnSelect(aSelect,tMember);

	aSelect	<< tMember["IDFUNCTION"];
	aSelect	<< tMember["RATING"];
	aSelect	<< tMember["KCONST"];
}

void QCHMember::OnReader(MSLDBReader& aReader,GMember *pMember)
{
	QMember::OnReader(aReader,pMember);

	short     function,rating,kConst;
	MSLDBNullIndicator nullFunction,nullRating,nullKConst;
	
	aReader >> nullFunction				  >> function
			>> nullRating				  >> rating
			>> nullKConst				  >> kConst;

	if (nullFunction)
		function=0;

	((CHMember*)pMember)->setFunction(function);

	if (nullRating)
		rating=0;
	
	((CHMember*)pMember)->setRating(rating);

	if (nullKConst)
		kConst=0;
	
	((CHMember*)pMember)->setKConst(kConst);
}