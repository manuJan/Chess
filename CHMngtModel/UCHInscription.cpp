/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : UCHInscription.cpp
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
#include "UCHInscription.h"
#include "CHInscription.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void UCHInscription::OnAssignAttributes(const GInscription& aInscription)
{
	UGTHInscription::OnAssignAttributes(aInscription);

	nullSeed			  = ((seed = ((CHInscription&)aInscription).getSeed())== 0);
	nullRating			  = ((rating = ((CHInscription&)aInscription).getRating())== 0);
	nullKConst			  = ((kConst = ((CHInscription&)aInscription).getKConst())== 0);
	
}

void UCHInscription::OnInsert(MSLDBInserter& aInserter,MSLDBTable& table,const GInscription& aInscription)
{
	UGTHInscription::OnInsert(aInserter,table,aInscription);

	aInserter << table["SEED"]		.assign(seed,&nullSeed);
	aInserter << table["RATING"]	.assign(rating,&nullRating);
	aInserter << table["KCONST"]	.assign(kConst,&nullKConst);	
}

void UCHInscription::OnUpdate(MSLDBUpdater& aUpdate,MSLDBTable& table,const GInscription& aInscription)
{
	UGTHInscription::OnUpdate(aUpdate,table,aInscription);

	aUpdate << table["SEED"]		.assign(seed,&nullSeed);
	aUpdate << table["RATING"]		.assign(rating,&nullRating);
	aUpdate << table["KCONST"]		.assign(kConst,&nullKConst);
	
}

