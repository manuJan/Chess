/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : QCHTeamMatchsCnfg.cpp
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
#include "QCHTeamMatchsCnfg.h"
#include "CHEvent.h"
#include "CHMemoryDataBase.h"
#include "CHTeamMatchsCnfg.h"
#include <Core/G/DBApplication.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

QCHTeamMatchsCnfg::QCHTeamMatchsCnfg(RWDBConnection *pNewConnection)
:QBase(pNewConnection)
{
}

QCHTeamMatchsCnfg::~QCHTeamMatchsCnfg()
{
}


size_t QCHTeamMatchsCnfg::selectCollection(RWDBConnection& aConnection,RWCollection& target)
{
	RWCString table="CHT068_TEAM_MATCH_CNFG";
	RWCString tableName="CHT568_TEAM_MATCH_CNFG";

	RWDBTable teamMatchCnfg	= DBApplication::getTable(table);
	RWDBTable teamMatchCnfgName	= DBApplication::getTable(tableName);
	RWDBTable languages			= DBApplication::getTable("ZZT000_LANGUAGE");
	RWDBSelector select	= DBApplication::getSelector();

	select << teamMatchCnfg["TEAMCFG"]
		   << teamMatchCnfg["NCOMPETITORS"]
		   << teamMatchCnfg["NMATCHES"]
		   << teamMatchCnfg["NMATCHESTYPE"]
		   << teamMatchCnfg["COMPMATCHESDISTRIBUTION"]
		   << teamMatchCnfgName["IDLANGUAGE"]
		   << teamMatchCnfgName["SDESCRIPTION"]
		   << teamMatchCnfgName["LDESCRIPTION"]
		   << teamMatchCnfg["FAWAYC"]
		   ;

	select.where(  teamMatchCnfg["TEAMCFG"]    == teamMatchCnfgName["TEAMCFG"]
				&& teamMatchCnfgName["IDLANGUAGE"]  == languages["IDLANGUAGE"] 
				&& languages["FACTIVE"]      == "Y");
	
	RWCString fSex, fEvent, fRound, fPhase, fCompMatchesDistribution,
		fMatchesType, fFAwayC;
	short fId, fnMatches, fnComp;
	RWDBNullIndicator nullRound, nullPhase, nullnComp, nullMatchesType,
		nullCompMatchesDistribution, nullnMatches, nullId, nullFAwayC;

	RWCString flanguage;
	RWWString fsDescription,flDescription;
	RWDBNullIndicator nullSDescription,nullLDescription;

	CHTeamMatchsCnfg *pTeamMatCnfg=0,aTeamMatCnfg;
	GNames aNames;

	RWDBReader reader = select.reader(aConnection);

	while (reader())
	{	
		reader >> fId	
			   >> nullnComp	>> fnComp
			   >> nullnMatches	>> fnMatches
			   >> nullMatchesType	>> fMatchesType
			   >> nullCompMatchesDistribution	>> fCompMatchesDistribution
			   >> flanguage
			   >> nullSDescription >> fsDescription
			   >> nullLDescription >> flDescription
			   >> nullFAwayC	   >> fFAwayC
			   ;

		if( nullSDescription ) 
			fsDescription=NULLRWWSTRING;
		if( nullLDescription ) 
			flDescription=NULLRWWSTRING;
		
		aNames.setCode(flanguage);
		aNames.setSName(fsDescription);
		aNames.setLName(flDescription);

		aTeamMatCnfg.setId(fId);
		pTeamMatCnfg=(CHTeamMatchsCnfg *)CHMemoryDataBase::findTeamMatchsCnfg(aTeamMatCnfg);
		if (!pTeamMatCnfg)
		{
			pTeamMatCnfg=new CHTeamMatchsCnfg();
			pTeamMatCnfg->setId(fId);
			pTeamMatCnfg->setCompetitors(fnComp);
			pTeamMatCnfg->setMatches(fnMatches);
			pTeamMatCnfg->setMatchesType(fMatchesType);
			pTeamMatCnfg->setCompMatchesDistribution(fCompMatchesDistribution);
			pTeamMatCnfg->setFAwayC(fFAwayC);
			target.insert(pTeamMatCnfg);
		}
		pTeamMatCnfg->setDescription(aNames);
	}
	return target.entries();
}