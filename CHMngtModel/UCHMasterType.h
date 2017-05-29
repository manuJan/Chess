/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:UCHMasterType.h
*	Description	:
*
*	Author		:Chess Team
*	Date created:09-12-2005
* 	Project		:Ches Management Model DLL
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#pragma once
#include <OVR/CORE/G/UBase.h>
#include "CHMasterType.h"

class UCHMasterType : public UBase
{

public:
	UCHMasterType()
		:UBase()
	{;}
	virtual ~UCHMasterType()
	{;}

protected:
	bool insert (GData& aData);
	bool update (GData& aData);	
	bool delete_(GData& aData);

	long insertLang(MSLDBTable& table);
	long updateLang(MSLDBTable& table);
	void deleteLang(MSLDBTable& table);

	long OnInsertLang(MSLDBTable& table,const CHMasterType& aMasterType);
	long OnUpdateLang(MSLDBTable& table,const CHMasterType& aMasterType);
	void OnDeleteLang(MSLDBTable& table,const CHMasterType& aMasterType);

	void assignAttributes(CHMasterType& aEnd);
	bool assignNames(const CHMasterType& aMasterType,const char *language);

private:

	short order;
	MSLDBNullIndicator nullorder;

	MSLDBNullIndicator nullLDescription,nullSDescription;
	MSLString lang;	
	MSLWString flDescription,fsDescription;
	short masterType;

};

