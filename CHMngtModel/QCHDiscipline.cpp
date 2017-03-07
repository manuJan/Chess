/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : QCHDiscipline.h                                                                 
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
#include "QCHDiscipline.h"
#include "CHDiscipline.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
QCHDiscipline::QCHDiscipline(RWDBConnection *pNewConnection)
:QDiscipline(pNewConnection)
{
}

QCHDiscipline::~QCHDiscipline()
{
}

size_t QCHDiscipline::selectObject(RWDBConnection & aConnection,GData & aData)
{
	QDiscipline::selectObject(aConnection,aData);
	CHDiscipline & aDiscipline = (CHDiscipline &)aData;

	RWDBTable definitionTable  = DBApplication::getTable("CHT000_DEFINITION");
	RWDBTable generalNames     = DBApplication::getTable("ZZT530_OVERALL_DESCRIPTION");
	RWDBTable languages        = DBApplication::getTable("ZZT000_LANGUAGE");

	RWDBSelector select        = DBApplication::getSelector();

	// Query data
	select	<< definitionTable["GROUPING"]
			<< definitionTable["WEIGHT"]
			<< definitionTable["HEIGHT"]
			<< definitionTable["LSCB_LENGTH"]
			<< definitionTable["SSCB_LENGTH"]
			<< definitionTable["STATUS"]
			<< definitionTable["PARALYMPIC"]
		    << definitionTable["RSC_MODE"]
		    << definitionTable["RSC_COMPOSITION"]
			<< definitionTable["AUTO_PROG"]
			;	

	unsigned char fStatus;
	RWCString fWeight, fHeight, frscComposition;
	RWDBDateTime fDate;
	RWDBNullIndicator nullLongScore, nullShortScore, nullDate, nullRscComposition;
	int fGrouping, fShortScore, fLongScore, frscMode;
	short fParalympic,autoProg;

	
	RWDBReader rdr = select.reader(aConnection);

	if( rdr() ) 
	{
		rdr >> fGrouping
			>> fWeight
			>> fHeight
			>> nullLongScore  >> fLongScore
			>> nullShortScore >> fShortScore
			>> fStatus
			>> fParalympic
			>> frscMode
			>> nullRscComposition >> frscComposition
			>> autoProg
			;

		if (nullLongScore)
			fLongScore=0;
		if (nullShortScore) 
			fShortScore=0;

		aDiscipline.setGbCriterium(fGrouping);
		aDiscipline.setWeightFormat(fWeight);
		aDiscipline.setHeightFormat(fHeight);
		aDiscipline.setScbLName(fLongScore);
		aDiscipline.setScbSName(fShortScore);
		aDiscipline.setStatus(fStatus);
		aDiscipline.setParalympic(fParalympic!=0);
		aDiscipline.setRSCMode(frscMode);
		aDiscipline.setRSCComposition(frscComposition);
		aDiscipline.setAutoProg(autoProg==1);
	}

	select.clear();

	select << languages   ["IDLANGUAGE"        ]
		   << generalNames["POOL_SDESCRIPTION" ]
		   << generalNames["POOL_LDESCRIPTION" ]
		   << generalNames["MATCH_SDESCRIPTION"]
		   << generalNames["MATCH_LDESCRIPTION"]
		   << generalNames["SPLIT_SDESCRIPTION"]
		   << generalNames["SPLIT_LDESCRIPTION"]
		   ;

	select.where(generalNames["IDLANGUAGE"] == languages["IDLANGUAGE"] &&
				 languages   ["FACTIVE"   ] == "Y"                     );

	RWCString flang;
	RWWString fPoolSDesc,fPoolLDesc,fMatchSDesc,fMatchLDesc,fSetSDesc,fSetLDesc;
	RWDBNullIndicator nullPoolSDesc,nullPoolLDesc,nullMatchSDesc,nullMatchLDesc, 
					  nullSetSDesc,nullSetLDesc;

	rdr = select.reader(aConnection);

	while( rdr() ) 
	{
		rdr  >> flang
			 >> nullPoolSDesc  >> fPoolSDesc
			 >> nullPoolLDesc  >> fPoolLDesc
			 >> nullMatchSDesc >> fMatchSDesc
			 >> nullMatchLDesc >> fMatchLDesc
			 >> nullSetSDesc   >> fSetSDesc
			 >> nullSetLDesc   >> fSetLDesc
			 ;

		if( nullPoolSDesc  ) 
			fPoolSDesc=NULLRWWSTRING;
		if( nullPoolLDesc  ) 
			fPoolLDesc=NULLRWWSTRING;
		if( nullMatchSDesc ) 
			fMatchSDesc=NULLRWWSTRING;
		if( nullMatchLDesc ) 
			fMatchLDesc=NULLRWWSTRING;
		if( nullSetSDesc   ) 
			fSetSDesc=NULLRWWSTRING;
		if( nullSetLDesc   ) 
			fSetLDesc=NULLRWWSTRING;

		aDiscipline.setPoolNames ( GNames(flang,fPoolSDesc ,fPoolLDesc ) );
		aDiscipline.setMatchNames( GNames(flang,fMatchSDesc,fMatchLDesc) );
	}

	return DBApplication::getStatus();
}