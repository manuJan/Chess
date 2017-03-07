/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:QCHMasterType.cpp
*	Description	:
*
*	Author		:Chess Team
*	Date created:09-12-2005
* 	Project		:Chess Management Model DLL
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdCHMngt.h"
#include "CHMasterType.h"
#include "QCHMasterType.h"

size_t QCHMasterType::selectCollection(RWDBConnection& aConnection,RWCollection& target)
{
	RWDBTable MasterType		= DBApplication::getTable("CHT064_MASTER_TYPE"   );
	RWDBTable MasterTypeNames	= DBApplication::getTable("CHT564_MASTER_TYPE"   );
	RWDBTable languages			= DBApplication::getTable("ZZT000_LANGUAGE");
	RWDBSelector select			= DBApplication::getSelector();

	select << MasterType["NORDER"]
		   << MasterTypeNames["MASTER_TYPE"]
		   << MasterTypeNames["IDLANGUAGE"]
		   << MasterTypeNames["SDESCRIPTION"]
		   << MasterTypeNames["LDESCRIPTION"]
		   ;

	select.where( MasterType["MASTER_TYPE"] == MasterTypeNames["MASTER_TYPE"]	&&
				  languages["IDLANGUAGE"]	== MasterTypeNames["IDLANGUAGE"]	&&
				  languages["FACTIVE"]		== "Y" );

	RWDBReader rdr = select.reader(aConnection);

	short fmasterType;
	short forder;
	RWCString flanguage;
	RWWString fsDescription,flDescription;
	RWDBNullIndicator nullSDescription,nullLDescription, nullorder;

	GNames aNames;
	while( rdr() ) 
	{
		rdr >> nullorder >> forder
			>> fmasterType
			>> flanguage
			>> nullSDescription >> fsDescription
			>> nullLDescription >> flDescription
			;

		if( nullSDescription ) fsDescription = NULLRWWSTRING;
		if( nullLDescription ) flDescription = NULLRWWSTRING;
		if( nullorder		 ) forder = 0;

		aNames.setCode (flanguage    );
		aNames.setSName(fsDescription);
		aNames.setLName(flDescription);

		CHMasterType * pMasterType = new CHMasterType();
		if( pMasterType )
		{
			pMasterType->setMasterType(fmasterType);
			pMasterType->setOrder(forder);
			pMasterType->setDescription(aNames);
			target.insert(pMasterType);
		}
	}

	return target.entries();
}
