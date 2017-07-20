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
#include <ovr/core/G/DBApplication.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

size_t QCHTeamMatchsCnfg::selectCollection(MSLCollection& target)
{
	MSLString table=CHT_TEAM_MATCH_CNFG;
	MSLString tableName=CHT_TEAM_MATCH_CNFGL;

	MSLDBTable teamMatchCnfg	 = getTable(table);
	MSLDBTable teamMatchCnfgName = getTable(tableName);
	MSLDBTable languages	     = getTable("ZZT000_LANGUAGE");
	MSLDBSelector select		 = getSelector();

	select << teamMatchCnfg["TEAMCFG"]
		   << teamMatchCnfg["NCOMPETITORS"]
		   << teamMatchCnfg["NMATCHES"]
		   << teamMatchCnfg["NMATCHES_ELIM"]
		   << teamMatchCnfg["NMATCHESTYPE"]
		   << teamMatchCnfg["NMATCHESTYPE_ELIM"]
		   << teamMatchCnfg["COMPMATCHESDISTRIBUTION"]		   
		   << teamMatchCnfgName["IDLANGUAGE"]
		   << teamMatchCnfgName["SDESCRIPTION"]
		   << teamMatchCnfgName["LDESCRIPTION"]
		   << teamMatchCnfg["FAWAYC"]
		   ;

	select.where(  teamMatchCnfg["TEAMCFG"]    == teamMatchCnfgName["TEAMCFG"]
				&& teamMatchCnfgName["IDLANGUAGE"]  == languages["IDLANGUAGE"] 
				&& languages["FACTIVE"]      == "Y");
	
	MSLString fSex, fEvent, fRound, fPhase, fCompMatchesDistribution, fMatchesTypeElim,
		fMatchesType, fFAwayC;
	short fId, fnMatches,fnMatchesElim,fnComp;
	MSLDBNullIndicator nullRound, nullPhase, nullnComp, nullMatchesType,
		nullCompMatchesDistribution,nullMatchesTypeElim, nullnMatches,nullnMatchesElim, nullId, nullFAwayC;

	MSLString flanguage;
	MSLWString fsDescription,flDescription;
	MSLDBNullIndicator nullSDescription,nullLDescription;

	CHTeamMatchsCnfg aTeamMatCnfg, *pTeamMatCnfg=0;
	
	GDescription desc;

	MSLDBReader reader = select.reader();

	while (reader())
	{	
		reader >> fId	
			   >> nullnComp	>> fnComp
			   >> nullnMatches	>> fnMatches
			   >> nullnMatchesElim >> fnMatchesElim
			   >> nullMatchesType	>> fMatchesType
			   >> nullMatchesTypeElim	>> fMatchesTypeElim
			   >> nullCompMatchesDistribution	>> fCompMatchesDistribution			   
			   >> flanguage
			   >> nullSDescription >> fsDescription
			   >> nullLDescription >> flDescription
			   >> nullFAwayC	   >> fFAwayC
			   ;

		if( nullSDescription ) 
			fsDescription=NULLWSTRING;
		if( nullLDescription ) 
			flDescription=NULLWSTRING;
		
		desc.set(flanguage);
		desc.set(_LNAME,flDescription);
		desc.set(_SNAME,fsDescription);

		aTeamMatCnfg.setId(fId);
		pTeamMatCnfg=(CHTeamMatchsCnfg*) target.find(&aTeamMatCnfg);

		if (!pTeamMatCnfg)
		{
			pTeamMatCnfg=new CHTeamMatchsCnfg();
			pTeamMatCnfg->setId(fId);
			pTeamMatCnfg->setCompetitors(fnComp);
			pTeamMatCnfg->setMatches(fnMatches);
			pTeamMatCnfg->setMatchesElim(fnMatchesElim);
			pTeamMatCnfg->setMatchesType(fMatchesType);
			pTeamMatCnfg->setMatchesTypeElim(fMatchesTypeElim);
			pTeamMatCnfg->setCompMatchesDistribution(fCompMatchesDistribution);			
			pTeamMatCnfg->setFAwayC(fFAwayC);
			target.insert(pTeamMatCnfg);
		}

		pTeamMatCnfg->setDescriptions(desc);	
	}
	return target.entries();
}