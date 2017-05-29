/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : UCHMember.cpp
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
#include "UCHMember.h"
#include "CHMember.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void UCHMember::OnAssignAttributes(const GMember& aMember)
{
	function		= ((CHMember &)aMember).getFunction();
	nullRating		= ((rating = ((CHMember&)aMember).getRating())== 0);
	nullKConst		= ((kConst = ((CHMember&)aMember).getKConst())== 0);
}

void UCHMember::OnInsert(MSLDBInserter& aInserter,MSLDBTable& table,const GMember& aMember)
{
	aInserter << table["IDFUNCTION"]	.assign(function);
	aInserter << table["RATING"]		.assign(rating,&nullRating);
	aInserter << table["KCONST"]		.assign(kConst,&nullKConst);

	UNREFERENCED_PARAMETER(aMember);
}

void UCHMember::OnUpdate(MSLDBUpdater & aUpdater ,MSLDBTable& table,const GMember& aMember)
{
	aUpdater << table["IDFUNCTION"].assign(function);
	aUpdater << table["RATING"].assign(rating,&nullRating);
	aUpdater << table["KCONST"].assign(kConst,&nullKConst);

	UNREFERENCED_PARAMETER(aMember);
}

