/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : QCHInscription.cpp
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
#include "QCHInscription.h"
#include "CHInscription.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void QCHInscription::OnSelect(MSLDBSelector& aSelect,MSLDBTable& tInscription)
{
	QGTHInscription::OnSelect(aSelect,tInscription);

	aSelect	<< tInscription["SEED"];
	aSelect	<< tInscription["RATING"];
	aSelect	<< tInscription["KCONST"];
}

void QCHInscription::OnReader(MSLDBReader& aReader,GInscription *pInscription)
{
	QGTHInscription::OnReader(aReader,pInscription);

	short     seed,rating,kConst;
	MSLDBNullIndicator nullSeed,nullRating,nullKConst;
	
		
	aReader >> nullSeed					  >> seed
			>> nullRating				  >> rating
			>> nullKConst				  >> kConst;
	

	if (nullSeed)
		seed=0;
	
	((CHInscription*)pInscription)->setSeed(seed);

	if (nullRating)
		rating=0;
	
	((CHInscription*)pInscription)->setRating(rating);

	if (nullKConst)
		kConst=0;
	
	((CHInscription*)pInscription)->setKConst(kConst);
	
}