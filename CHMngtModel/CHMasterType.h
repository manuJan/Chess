/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHMasterType.h
*	Description	:
*
*	Author		:CH Team
*	Date created:09-12-2005
* 	Project		:Chess Management Model DLL
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#if !defined(AFX_CHMasterType_H__EE4E4030_F708_4BC0_AAF6_E43CB04C85C2__INCLUDED_)
#define AFX_CHMasterType_H__EE4E4030_F708_4BC0_AAF6_E43CB04C85C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHMNGTMODELDLL_H
#   include "CHMngtModelDll.h" 
#endif // _CH_MNGTMODELDLL_H

class GData;

class CHModelExport CHMasterType : public GData  
{
	RWDECLARE_COLLECTABLE(CHMasterType)

public:
	// Constructors & Destructor
	CHMasterType();
	CHMasterType(const short id,GNames aNames);
	CHMasterType(const CHMasterType & copy);
	CHMasterType(CPack & aPack);
	virtual ~CHMasterType();

	// Overloaded Operators
	CHMasterType & operator  = (const CHMasterType & copy);
	RWBoolean operator == (const CHMasterType & copy);
	RWBoolean operator != (const CHMasterType & copy);

	// From GData
	// SQL Method
	RWBoolean uSQL(RWDBConnection & pConnect,RWBoolean remove=false);
	// Packing Methods
	CPack & pack  (CPack & aPack);
	CPack & unpack(CPack & aPack);	
	// Outputs Methods
	RWCString msl() const;
	//RWCString mslDescription(const char * language) const;

	// Key Method
	void setKey();
	// Set Methods
	void setMasterType(const short value);
	void setDescription(const GNames & description);
	void setOrder(const short value);

	// Get Methods
	short getMasterType() const;
	short getOrder() const;
	RWSet & getNames();	
	RWWString getLDescription(const char * language=DBApplication::getAppLanguage()) const;
	RWWString getSDescription(const char * language=DBApplication::getAppLanguage()) const;

	

	

private:
	// Private Methods
	void      copyMasterType   (const CHMasterType & copy);
	RWBoolean compareMasterType(const CHMasterType & copy);

private:
	short masterType;
	short order;
	RWSet masterTypeNames;
};

#endif // !defined(AFX_CHMasterType_H__EE4E4030_F708_4BC0_AAF6_E43CB04C85C2__INCLUDED_)
