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

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
QCHMember::QCHMember(RWDBConnection *pNewConnection)
:QGTHMember(pNewConnection)
{
}

QCHMember::~QCHMember()
{
}

GMember * QCHMember::OnNewMember()
{
	return new CHMember();
}

void QCHMember::OnSelect(RWDBSelector& aSelect,RWDBTable& tMember)
{
	QGTHMember::OnSelect(aSelect,tMember);

	aSelect	<< tMember["IDFUNCTION"];
	aSelect	<< tMember["RATING"];
	aSelect	<< tMember["KCONST"];
}

void QCHMember::OnReader(RWDBReader& aReader,GMember *pMember)
{
	QGTHMember::OnReader(aReader,pMember);

	short     function,rating,kConst;
	RWDBNullIndicator nullFunction,nullRating,nullKConst;
	
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