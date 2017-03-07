/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : UCHMatch.cpp                                                                 
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:15-07-2005
*   Project     :CH Model               
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///

#include "stdCHMngt.h"
#include "UCHJudge.h"
#include "CHJudge.h"


RWBoolean UCHJudge::insert (RWDBConnection& aConnection,GData& aData)
{
	CHJudge &    aJudge 	= (CHJudge &)aData;
	RWDBTable    judge 	    = DBApplication::getTable("CHT017_JUDGE");
	RWDBInserter inserter   = judge.inserter();
	
	assignAtributes(&aJudge);

	inserter["REGISTER"]		<< fRegister;	
	inserter["IDFUNCTION"]		<< RWDBBoundExpr(&fFunction	,&nullFunction);
		
	
	RWDBResult aResult=inserter.execute(aConnection);
	aResult.table();
	
	return aResult.rowCount()>0L;
}

RWBoolean UCHJudge::update (RWDBConnection& aConnection,GData& aData)
{
	CHJudge &    aJudge 		= (CHJudge &)aData;
	RWDBTable    judge 	    = DBApplication::getTable("CHT017_JUDGE");
	RWDBUpdater updater    = judge.updater();

	assignAtributes(&aJudge);
	
	updater.where( judge["REGISTER"]   == fRegister &&
				   judge["IDFUNCTION"] == fFunction);
	
	updater << judge["IDFUNCTION"]	.assign(RWDBBoundExpr(&fFunction	,&nullFunction));
		
	RWDBResult aResult=updater.execute(aConnection);
	aResult.table();
	
	return aResult.rowCount()>0L;
}

RWBoolean UCHJudge::delete_(RWDBConnection& aConnection,GData& aData)
{
	CHJudge &    aJudge 	= (CHJudge &)aData;
	RWDBTable    judge 	    = DBApplication::getTable("CHT017_JUDGE");
	RWDBDeleter  deleter    = judge.deleter();

	assignAtributes(&aJudge);
	
	deleter.where( judge["REGISTER"]   == fRegister &&
				   judge["IDFUNCTION"] == fFunction);	
	
	RWDBResult aResult=deleter.execute(aConnection);
	aResult.table();
	
	return aResult.rowCount()!=-1L;
}


void UCHJudge::assignAtributes(CHJudge *pJudge)
{
	fFunction=0;
	GFunction * pFunction= pJudge->getFunction();
	nullFunction=(pFunction==NULL);
	if(pFunction)
	{
	   fFunction=pFunction->getFunction();
	}
	
	
	fRegister =atoi(pJudge->getRegisterKey());
}