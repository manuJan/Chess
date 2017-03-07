/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:UCHPhaseBase.cpp
*	Description	: 
*
*   Author      :Chess Team
*   Date created:07-12-2005
*   Project     :CH Model       
*	
* 	Modification history
*	By		:	
*	Date	:	
*	Changes	:	
*
***************************************************************************************/
#include "stdCHMngt.h"
#include "CHPhaseBase.h"
#include "UCHPhaseBase.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


RWBoolean UCHPhaseBase::insert(RWDBConnection& aConnection, GData& aData)
{
	CHPhaseBase &aPB	= (CHPhaseBase &) aData;

	RWDBTable ddTable		= DBApplication::getTable ("ZCH012_PHASE");
	RWDBTable ddTableNames	= DBApplication::getTable ("ZCH512_PHASE");

	RWDBInserter ins = ddTable.inserter();
	ins["PHASE"]			<< aPB.getCode();
	ins["NORDER"]			<< aPB.getOrder();
	ins["WINNER_RANK"]		<< aPB.getWinnerRank();
	ins["LOSER_RANK"]		<< aPB.getLoserRank();
	ins["TYPEPHASE"]		<< aPB.getTypePhase();
		

	RWDBResult aResult = ins.execute(aConnection);	
	aResult.table();

	if ( aResult.rowCount()>0L )
	{
		ins = ddTableNames.inserter();
	
		RWSet phaseNames = aPB.getNames();
		RWSetIterator iter(phaseNames);
		GNamesEx * pNames = 0;
		while( (pNames = (GNamesEx *)iter()) != 0 )
		{
			if( pNames )
			{
				ins["PHASE"]		<< aPB.getCode();
				ins["IDLANGUAGE"]	<< pNames->getCode();
				ins["LDESCRIPTION"]	<< pNames->getLName();
				ins["SDESCRIPTION"]	<< pNames->getSName();
								
				aResult = ins.execute(aConnection);
			}
		}
		
	}
	aResult.table();
	return aResult.rowCount()>0L;
}

RWBoolean UCHPhaseBase::update(RWDBConnection& aConnection, GData& aData)
{
	CHPhaseBase &aPB	= (CHPhaseBase &) aData;

	RWDBTable ddTable		= DBApplication::getTable ("ZCH012_PHASE");
	RWDBTable ddTableNames	= DBApplication::getTable ("ZCH512_PHASE");

	RWDBUpdater updater=ddTable.updater();
	updater.where( ddTable["PHASE"]==aPB.getCode() );
	updater << ddTable["NORDER"].assign( aPB.getOrder() );
	updater << ddTable["WINNER_RANK"].assign( aPB.getWinnerRank() );
	updater << ddTable["LOSER_RANK"].assign( aPB.getLoserRank() );
	updater << ddTable["TYPEPHASE"].assign( aPB.getTypePhase() );
	
	
	RWDBResult aResult=updater.execute(aConnection);
	aResult.table();

	
	RWDBUpdater upd = ddTableNames.updater();

	RWSet names = aPB.getNames();
	RWSetIterator iter(names);
	GNamesEx * pNames = 0;
	long contador = 0;
	while( (pNames = (GNamesEx *)iter()) != 0 )
	{
		if( pNames )
		{
			upd.where( ddTableNames["PHASE"] == aPB.getCode()		&&
					   ddTableNames["IDLANGUAGE"] == pNames->getCode() );

			upd	<< ddTableNames["LDESCRIPTION"]	.assign( pNames->getLName() );
			upd	<< ddTableNames["SDESCRIPTION"]	.assign( pNames->getSName() );
						
			RWDBResult aResult = upd.execute(aConnection);
			aResult.table();
			
			contador = contador + aResult.rowCount();
		}		
	}
		
	return contador>0L;
}

RWBoolean UCHPhaseBase::delete_(RWDBConnection& aConnection,GData& aData)
{
	CHPhaseBase &aPB	= (CHPhaseBase &) aData;

	RWDBTable ddTable		= DBApplication::getTable ("ZCH012_PHASE");
	RWDBTable ddTableNames	= DBApplication::getTable ("ZCH512_PHASE");

	RWDBDeleter del = ddTableNames.deleter().
					  where( ddTableNames["PHASE"] == aPB.getCode() );

	RWDBResult aResult = del.execute(aConnection);
	aResult.table();
	if( aResult.rowCount()>0L )
	{
		del = ddTable.deleter().
			where( ddTable["PHASE"] == aPB.getCode() );

		aResult = del.execute(aConnection);
		aResult.table();
	}
	return aResult.rowCount()>0L;
}
