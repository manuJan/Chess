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

size_t QCHMasterType::selectCollection(MSLCollection& target)
{
	MSLDBTable MasterType		= getTable(CHT_MASTER_TYPE);
	MSLDBTable MasterTypeNames	= getTable(CHT_MASTER_TYPEL);
	MSLDBTable languages		= getTable(ZZT_LANGUAGE);
	MSLDBSelector select			= getSelector();

	select << MasterType["NORDER"]
		   << MasterTypeNames["MASTER_TYPE"]
		   << MasterTypeNames["IDLANGUAGE"]
		   << MasterTypeNames["SDESCRIPTION"]
		   << MasterTypeNames["LDESCRIPTION"]
		   ;

	select.where( MasterType["MASTER_TYPE"] == MasterTypeNames["MASTER_TYPE"]	&&
				  languages["IDLANGUAGE"]	== MasterTypeNames["IDLANGUAGE"]	&&
				  languages["FACTIVE"]		== "Y" );

	MSLDBReader rdr = select.reader();

	short fmasterType;
	short forder;
	MSLString flanguage;
	MSLWString fsDescription,flDescription;
	MSLDBNullIndicator nullSDescription,nullLDescription, nullorder;

	GDescription desc;
	CHMasterType aMasterType,*pMasterType=0;

	while( rdr() ) 
	{
		rdr >> nullorder >> forder
			>> fmasterType
			>> flanguage
			>> nullSDescription >> fsDescription
			>> nullLDescription >> flDescription
			;

		if( nullSDescription ) fsDescription = NULLWSTRING;
		if( nullLDescription ) flDescription = NULLWSTRING;
		if( nullorder		 ) forder = 0;

		if( nullSDescription  ) fsDescription  = NULLWSTRING;
		if( nullLDescription  ) flDescription  = NULLWSTRING;
		
		desc.set(flanguage);
		desc.set(_LNAME,flDescription);
		desc.set(_SNAME,fsDescription);

		aMasterType.setMasterType(fmasterType);

		pMasterType = (CHMasterType *)target.find(&aMasterType);
		if( !pMasterType ) 
		{
			pMasterType = new CHMasterType;
			pMasterType->setMasterType(fmasterType);
			pMasterType->setOrder(forder);
			target.insert(pMasterType);
		}

		pMasterType->setDescriptions(desc);	
	}

	return target.entries();
}
