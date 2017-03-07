/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : UCHDiscipline.cpp                                                                 
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:05-12-2005
*   Project     :CH Model
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///

#include "stdCHMngt.h"
#include "UCHDiscipline.h"
#include "CHDiscipline.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
UCHDiscipline::UCHDiscipline(RWDBConnection *pNewConnection)
:UBase(pNewConnection)
{
}

UCHDiscipline::~UCHDiscipline()
{
}

void UCHDiscipline::assignAtributes(CHDiscipline& discipline)
{
	UNREFERENCED_PARAMETER(discipline);
	// Testing null indicators
	fShortScore = discipline.getScbSName();
	nullShortScore = (fShortScore == 0);

	fLongScore = discipline.getScbLName();
	nullLongScore = (fLongScore == 0);

	nullRscComposition = true;
	fRscComposition = discipline.getRSCComposition();
	if( fRscComposition!=NULLRWSTRING )
		nullRscComposition=false;

	autoProg=discipline.getAutoProg();
}

RWBoolean UCHDiscipline::update(RWDBConnection & aConnection,GData & aData)
{
	CHDiscipline & aDiscipline = (CHDiscipline &)aData;

	RWDBTable definitionTable  = DBApplication::getTable("CHT000_DEFINITION");

	RWDBUpdater	updater        = definitionTable.updater();

	assignAtributes(aDiscipline);

	updater.where( definitionTable["DISCIPLINE"]==aDiscipline.getCode() );

	updater << definitionTable["CHAMP"]			 .assign( aDiscipline.getChampionship().getChampionshipCode() )
		    << definitionTable["GROUPING"]		 .assign( aDiscipline.getGbCriterium() )
		    << definitionTable["WEIGHT"]		 .assign( aDiscipline.getWeightFormat() )
			<< definitionTable["HEIGHT"]		 .assign( aDiscipline.getHeightFormat() )
			<< definitionTable["LSCB_LENGTH"]	 .assign( RWDBBoundExpr(&fLongScore,&nullLongScore) )
			<< definitionTable["SSCB_LENGTH"]	 .assign( RWDBBoundExpr(&fShortScore,&nullShortScore) )
			<< definitionTable["STATUS"]		 .assign( aDiscipline.getStatus() )
			<< definitionTable["RSC_MODE"]		 .assign( aDiscipline.getRSCMode())
			<< definitionTable["RSC_COMPOSITION"].assign( RWDBBoundExpr(&fRscComposition,&nullRscComposition) )
			<< definitionTable["AUTO_PROG"]		 .assign( aDiscipline.getAutoProg() )
			;	

	RWDBResult aResult = updater.execute(aConnection); 
	aResult.table();

	return aResult.rowCount()>0L;
}