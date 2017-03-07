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
UCHTeamMatchsCnfg::UCHTeamMatchsCnfg(RWDBConnection *pNewConnection)
:UBase(pNewConnection)
{
}

UCHTeamMatchsCnfg::~UCHTeamMatchsCnfg()
{
}

void UCHTeamMatchsCnfg::assignAtributes(CHTeamMatchsCnfg & aTeamMatCnfg)
{
	fCompMatchesDistribution = aTeamMatCnfg.getCompMatchesDistribution();
	nullCompMatchesDistribution=true;
	if (fCompMatchesDistribution!=NULLRWSTRING)
		nullCompMatchesDistribution=false;

	fMatchesType = aTeamMatCnfg.getMatchesType();
	nullMatchesType=true;
	if (fMatchesType!=NULLRWSTRING)
		nullMatchesType=false;

	fId = aTeamMatCnfg.getId();
	nullId=true;
	if (fId!=0)
		nullId=false;

	fnMatches = aTeamMatCnfg.getMatches();
	nullnMatches=true;
	if (fnMatches!=0)
		nullnMatches=false;

	fnComp = aTeamMatCnfg.getCompetitors();
	nullnComp=true;
	if (fnComp!=0)
		nullnComp=false;
	flanguage=DBApplication::getAppLanguage();
	fsDescription=aTeamMatCnfg.getSDescription();
	nullSDescription=true;
	if (fsDescription!=NULLRWWSTRING)
		nullSDescription=false;
	flDescription=aTeamMatCnfg.getLDescription();
	nullLDescription=true;
	if (fsDescription!=NULLRWWSTRING)
		nullLDescription=false;

	fFAwayC = aTeamMatCnfg.getFAwayC();
	nullFAwayC=true;
	if (fFAwayC!=NULLRWSTRING)
		nullFAwayC=false;
}

RWBoolean UCHTeamMatchsCnfg::delete_(RWDBConnection& aConnection,GData& aData)
{
	CHTeamMatchsCnfg & aTeamMatCnfg=(CHTeamMatchsCnfg &)aData;
	assignAtributes(aTeamMatCnfg);

	RWDBTable table = DBApplication::getTable("CHT068_TEAM_MATCH_CNFG");
	RWCString tableName="CHT568_TEAM_MATCH_CNFG";
	RWDBTable teamMatchCnfgName	= DBApplication::getTable(tableName);
	RWDBTable languages			= DBApplication::getTable("ZZT000_LANGUAGE");

	RWDBDeleter deleter=teamMatchCnfgName.deleter();
	
	deleter.where(teamMatchCnfgName["TEAMCFG"] == fId);

	RWDBResult aResult=deleter.execute(aConnection);
	aResult.table();
	if (aResult.rowCount()>0L)
	{
		deleter = table.deleter();

		deleter.where(table["TEAMCFG"]		== fId );
		aResult=deleter.execute(aConnection);
		aResult.table();
	}

	return aResult.rowCount()>0L;
}

RWBoolean UCHTeamMatchsCnfg::insert(RWDBConnection& aConnection,GData& aData)
{
	RWDBTable table = DBApplication::getTable("CHT068_TEAM_MATCH_CNFG");
	RWCString tableName="CHT568_TEAM_MATCH_CNFG";
	RWDBTable teamMatchCnfgName	= DBApplication::getTable(tableName);
	RWDBTable languages			= DBApplication::getTable("ZZT000_LANGUAGE");

	CHTeamMatchsCnfg & aTeamMatCnfg=(CHTeamMatchsCnfg &)aData;
	assignAtributes(aTeamMatCnfg);

	RWDBInserter inserter = table.inserter();

	inserter["TEAMCFG"]				<< fId;
	inserter["NCOMPETITORS"]	<< RWDBBoundExpr(&fnComp,&nullnComp);
	inserter["NMATCHES"]		<< RWDBBoundExpr(&fnMatches,&nullnMatches);
	inserter["NMATCHESTYPE"]	<< RWDBBoundExpr(&fMatchesType,&nullMatchesType);
	inserter["COMPMATCHESDISTRIBUTION"]	<< RWDBBoundExpr(&fCompMatchesDistribution,&nullCompMatchesDistribution);
	inserter["FAWAYC"]			<< RWDBBoundExpr(&fFAwayC,&nullFAwayC);

	RWDBResult aResult = inserter.execute(aConnection);
	aResult.table();

	if (aResult.rowCount()>0L)
	{
		inserter=teamMatchCnfgName.inserter();
		RWSet sVector=aTeamMatCnfg.getNames();
		RWSetIterator it(sVector);
		GNames *name=0;
		while( (name=(GNames *)it()) != 0)
		{
			assignAtributesNames(name);

			inserter["TEAMCFG"]	<<	fId;
			inserter["IDLANGUAGE"]	<<	flanguage;
			inserter["SDESCRIPTION"]	<<	RWDBBoundExpr(&fsDescription,&nullSDescription);
			inserter["LDESCRIPTION"]	<<	RWDBBoundExpr(&flDescription,&nullLDescription);

			aResult =  inserter.execute(aConnection);
			aResult.table();
		}
	}

	return aResult.rowCount()!=-1L;
}

RWBoolean UCHTeamMatchsCnfg::update(RWDBConnection& aConnection,GData& aData)
{
	RWDBTable table = DBApplication::getTable("CHT068_TEAM_MATCH_CNFG");
	RWCString tableName="CHT568_TEAM_MATCH_CNFG";
	RWDBTable teamMatchCnfgName	= DBApplication::getTable(tableName);
	RWDBTable languages			= DBApplication::getTable("ZZT000_LANGUAGE");

	RWDBUpdater updater = table.updater();	

	CHTeamMatchsCnfg & aTeamMatCnfg=(CHTeamMatchsCnfg &)aData;
	assignAtributes(aTeamMatCnfg);

	updater.where(table["TEAMCFG"]   == fId);

	updater << table["NCOMPETITORS"]		.assign(RWDBBoundExpr(&fnComp,&nullnComp));
	updater << table["NMATCHES"]		.assign(RWDBBoundExpr(&fnMatches,&nullnMatches));
	updater << table["NMATCHESTYPE"]		.assign(RWDBBoundExpr(&fMatchesType,&nullMatchesType));
	updater << table["COMPMATCHESDISTRIBUTION"]		.assign(RWDBBoundExpr(&fCompMatchesDistribution,&nullCompMatchesDistribution));
	updater << table["FAWAYC"]			.assign(RWDBBoundExpr(&fFAwayC,&nullFAwayC));

	RWDBResult aResult=updater.execute(aConnection);
	aResult.table();

	if (aResult.rowCount()>0L)
	{
		updater = teamMatchCnfgName.updater();
		RWSet sVector=aTeamMatCnfg.getNames();
		RWSetIterator it(sVector);
		GNames *name=0;
		while( (name=(GNames *)it()) != 0)
		{
			assignAtributesNames(name);
			updater.where(  teamMatchCnfgName["TEAMCFG"]    == fId
					&& teamMatchCnfgName["IDLANGUAGE"]  == flanguage 
					);

			updater << teamMatchCnfgName["SDESCRIPTION"].assign(RWDBBoundExpr(&fsDescription,&nullSDescription));
			updater << teamMatchCnfgName["LDESCRIPTION"].assign(RWDBBoundExpr(&flDescription,&nullLDescription));

			aResult=updater.execute(aConnection);
			aResult.table();
		}
	}

	return aResult.rowCount()>0L;
}

void UCHTeamMatchsCnfg::assignAtributesNames(GNames *names)
{
	flanguage=names->getCode();
	fsDescription=names->getSName();
	nullSDescription=true;
	if (fsDescription!=NULLRWWSTRING)
		nullSDescription=false;
	flDescription=names->getLName();
	nullLDescription=true;
	if (fsDescription!=NULLRWWSTRING)
		nullLDescription=false;
}