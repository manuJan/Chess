/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : UCHTeamMatchsCnfg.cpp
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
#include "UCHTeamMatchsCnfg.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void UCHTeamMatchsCnfg::assignAtributes(CHTeamMatchsCnfg & aTeamMatCnfg)
{
	fCompMatchesDistribution = aTeamMatCnfg.getCompMatchesDistribution();
	nullCompMatchesDistribution=true;
	if (fCompMatchesDistribution!=NULLSTRING)
		nullCompMatchesDistribution=false;


	fMatchesTypeElim = aTeamMatCnfg.getMatchesTypeElim();
	nullMatchesTypeElim=true;
	if (fMatchesTypeElim!=NULLSTRING)
		nullMatchesTypeElim=false;


	fMatchesType = aTeamMatCnfg.getMatchesType();
	nullMatchesType=true;
	if (fMatchesType!=NULLSTRING)
		nullMatchesType=false;

	fId = aTeamMatCnfg.getId();
	nullId=true;
	if (fId!=0)
		nullId=false;

	fnMatches = aTeamMatCnfg.getMatches();
	nullnMatches=true;
	if (fnMatches!=0)
		nullnMatches=false;

	fnMatchesElim = aTeamMatCnfg.getMatchesElim();
	nullnMatchesElim=true;
	if (fnMatchesElim!=0)
		nullnMatchesElim=false;

	fnComp = aTeamMatCnfg.getCompetitors();
	nullnComp=true;
	if (fnComp!=0)
		nullnComp=false;
		
	fFAwayC = aTeamMatCnfg.getFAwayC();
	nullFAwayC=true;
	if (fFAwayC!=NULLSTRING)
		nullFAwayC=false;
}

bool UCHTeamMatchsCnfg::assignNames(CHTeamMatchsCnfg& aTeamMatchsCnfg,const char *language)
{
	GDescription &desc=aTeamMatchsCnfg.getDescriptions()[language];	

	flanguage		= language;
	flDescription	= desc[_LNAME];		nullLDescription	= (flDescription	== L"");
	fsDescription	= desc[_SNAME];		nullSDescription	= (fsDescription	== L"");
	
	return true;
}

bool UCHTeamMatchsCnfg::insert(GData& aData)
{
	MSLDBTable table = getTable(CHT_TEAM_MATCH_CNFG);	
	MSLDBTable teamMatchCnfgName	= getTable(CHT_TEAM_MATCH_CNFGL);
	MSLDBTable languages			= getTable(ZZT_LANGUAGE);

	CHTeamMatchsCnfg & aTeamMatCnfg=(CHTeamMatchsCnfg &)aData;
	assignAtributes(aTeamMatCnfg);

	MSLDBInserter inserter = table.inserter();

	inserter << table["TEAMCFG"]		.assign(fId);
	inserter << table["NCOMPETITORS"]	.assign(fnComp,&nullnComp);
	inserter << table["NMATCHES"]		.assign(fnMatches,&nullnMatches);
	inserter << table["NMATCHES_ELIM"]		.assign(fnMatchesElim,&nullnMatchesElim);
	inserter << table["NMATCHESTYPE"]	.assign(fMatchesType,&nullMatchesType);
	inserter << table["NMATCHESTYPE_ELIM"]	.assign(fMatchesTypeElim,&nullMatchesTypeElim);
	inserter << table["COMPMATCHESDISTRIBUTION"]	.assign(fCompMatchesDistribution,&nullCompMatchesDistribution);	
	inserter << table["FAWAYC"]			.assign(fFAwayC,&nullFAwayC);

	long count=inserter.execute();

	if( count>0L )
		count += OnInsertLang(teamMatchCnfgName,aTeamMatCnfg);

	return count>0L;
}

long UCHTeamMatchsCnfg::OnInsertLang(MSLDBTable& table, CHTeamMatchsCnfg& aTeamMatchsCnfg)
{
	long count=0L;
	GLanguage *pLang=0;		
	MSLSetIterator it(GMemoryDataBase::getCol(__GLANGUAGE));		
	while( (pLang=(GLanguage *)it())!=0 )
	{
		if( pLang->getNamesFlag() && assignNames(aTeamMatchsCnfg,pLang->get()) )
			count+=insertLang(table, aTeamMatchsCnfg);
	}
	return count;
}

long UCHTeamMatchsCnfg::insertLang(MSLDBTable& table, CHTeamMatchsCnfg& aTeamMatchsCnfg)
{
	MSLDBInserter inserterName=table.inserter();
	
	inserterName << table["TEAMCFG"]		.assign(fId);
	inserterName << table["IDLANGUAGE"]		.assign(flanguage);
	inserterName << table["SDESCRIPTION"]	.assign(fsDescription,&nullSDescription);
	inserterName << table["LDESCRIPTION"]	.assign(flDescription,&nullLDescription);
	
	return inserterName.execute();
	UNREFERENCED_PARAMETER(aTeamMatchsCnfg);
}


bool UCHTeamMatchsCnfg::update(GData& aData)
{
	MSLDBTable table				= getTable(CHT_TEAM_MATCH_CNFG);	
	MSLDBTable teamMatchCnfgName	= getTable(CHT_TEAM_MATCH_CNFGL);
	MSLDBTable languages			= getTable(ZZT_LANGUAGE);

	CHTeamMatchsCnfg & aTeamMatCnfg=(CHTeamMatchsCnfg &)aData;
	assignAtributes(aTeamMatCnfg);


	MSLDBUpdater updater=table.updater();
	updater.where(table["TEAMCFG"]   == fId);

	updater << table["NCOMPETITORS"]			.assign(fnComp,&nullnComp);
	updater << table["NMATCHES"]				.assign(fnMatches,&nullnMatches);
	updater << table["NMATCHES_ELIM"]				.assign(fnMatchesElim,&nullnMatchesElim);
	updater << table["NMATCHESTYPE"]			.assign(fMatchesType,&nullMatchesType);
	updater << table["NMATCHESTYPE_ELIM"]	.assign(fMatchesTypeElim,&nullMatchesTypeElim);
	updater << table["COMPMATCHESDISTRIBUTION"]	.assign(fCompMatchesDistribution,&nullCompMatchesDistribution);	
	updater << table["FAWAYC"]					.assign(fFAwayC,&nullFAwayC);

	long count=updater.execute();

	if( count>0L )
		count += OnUpdateLang(teamMatchCnfgName,aTeamMatCnfg);

	return count>0;	
}

long UCHTeamMatchsCnfg::updateLang(MSLDBTable& table, CHTeamMatchsCnfg& aTeamMatchsCnfg)
{
	MSLDBUpdater updaterName=table.updater();
	updaterName.where(	table["TEAMCFG"]	== fId		&&
						table["IDLANGUAGE"]	== flanguage);
	
	updaterName << table["SDESCRIPTION"]	.assign(fsDescription,&nullSDescription);
	updaterName << table["LDESCRIPTION"]	.assign(flDescription,&nullLDescription);

	return updaterName.execute();
	UNREFERENCED_PARAMETER(aTeamMatchsCnfg);
}

long UCHTeamMatchsCnfg::OnUpdateLang(MSLDBTable& table, CHTeamMatchsCnfg& aTeamMatchsCnfg)
{
	long count=0L,countLang=0L;
	GLanguage *pLang=0;		
	MSLSetIterator it(GMemoryDataBase::getCol(__GLANGUAGE));		
	while( (pLang=(GLanguage *)it())!=0 )
	{
		if( pLang->getNamesFlag() && assignNames(aTeamMatchsCnfg,pLang->get()) )
		{
			countLang=updateLang(table,aTeamMatchsCnfg);
			if( !countLang )
				countLang=insertLang(table,aTeamMatchsCnfg);
			count+=countLang;
		}
	}
	return count;
}

bool UCHTeamMatchsCnfg::delete_(GData& aData)
{
	CHTeamMatchsCnfg & aTeamMatCnfg=(CHTeamMatchsCnfg &)aData;
	
	MSLDBTable table        = getTable(CHT_TEAM_MATCH_CNFG);
	MSLDBTable namesTable   = getTable(CHT_TEAM_MATCH_CNFGL);

	MSLDBDeleter deleter=namesTable.deleter().
				where(namesTable["TEAMCFG"]==aTeamMatCnfg.getId());

	if (deleter.execute()<=0)
		return false;
	
	MSLDBDeleter deleter2=table.deleter().
	where(table["TEAMCFG"]==aTeamMatCnfg.getId());

	return deleter2.execute()!=-1L;
}






