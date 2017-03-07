/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : QCHJudge.cpp                                                                 
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
#include "QCHJudge.h"
#include "CHJudge.h"
#include <core/TH/GTHMemoryDataBase.h>


size_t QCHJudge::selectCollection(RWDBConnection& aConnection,RWCollection& target)
{
	RWDBTable judge			= DBApplication::getTable("CHT017_JUDGE");
	RWDBSelector select     = DBApplication::getSelector();
	
	// Query data
	select  << judge["REGISTER"]
			<< judge["IDFUNCTION"]
			;

	RWDBReader rdr = select.reader(aConnection);

	
	int fRegister;
	short fFunction;
	
	GFunction aFunction,*pFunction=0;
	GRegister aRegister,*pRegister=0;
	CHJudge *pJudge=0;
	
	while (rdr())
	{
		rdr >> fRegister
			>> fFunction			
			;

		pFunction=0;
		
 	    aFunction.setFunction( char(fFunction) );
	    pFunction=GTHMemoryDataBase::findFunction(aFunction);

		aRegister.setRegister(fRegister);
		pRegister=(GRegister *)GTHMemoryDataBase::findRegister(aRegister);

		if (!pRegister)
			continue;

		pJudge = new CHJudge();
		pJudge->setFunction(pFunction);
		pJudge->setRegister(pRegister);
		target.insert(pJudge);
	}

	return target.entries();
}
