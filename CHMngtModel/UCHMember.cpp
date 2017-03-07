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
UCHMember::UCHMember(RWDBConnection *pNewConnection)
:UMember(pNewConnection)
{
}

UCHMember::~UCHMember()
{
}

void UCHMember::OnAssignAttributes(const GMember& aMember)
{
	UMember::OnAssignAttributes(aMember);

	function		= ((CHMember &)aMember).getFunction();
	nullRating		= ((rating = ((CHMember&)aMember).getRating())== 0);
	nullKConst		= ((kConst = ((CHMember&)aMember).getKConst())== 0);
}
void UCHMember::OnInsert(RWDBInserter& aInsert,const GMember& aMember)
{
	UMember::OnInsert(aInsert,aMember);

	aInsert["IDFUNCTION"]	<< function;
	aInsert["RATING"]		<< RWDBBoundExpr(&rating,&nullRating);
	aInsert["KCONST"]		<< RWDBBoundExpr(&kConst,&nullKConst);
}

void UCHMember::OnUpdate(RWDBUpdater& aUpdate,RWDBTable& table,const GMember& aMember)
{
	UMember::OnUpdate(aUpdate,table,aMember);

	aUpdate << table["IDFUNCTION"].assign(function);
	aUpdate << table["RATING"].assign(RWDBBoundExpr(&rating,&nullRating));
	aUpdate << table["KCONST"].assign(RWDBBoundExpr(&kConst,&nullKConst));
}

void UCHMember::OnDelete(RWDBDeleter& aDelete,RWDBTable& table,const GMember& aMember)
{
	UMember::OnDelete(aDelete,table,aMember);
}