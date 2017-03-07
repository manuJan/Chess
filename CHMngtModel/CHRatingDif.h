/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHRatingDif.h
*	Description	:
*
*	Author		:CH Team
*	Date created:26-01-2006
* 	Project		:Chess Management Model DLL
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#if !defined(AFX_CHRatingDif_H__EE4E4030_F708_4BC0_AAF6_E43CB04C85C2__INCLUDED_)
#define AFX_CHRatingDif_H__EE4E4030_F708_4BC0_AAF6_E43CB04C85C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHMNGTMODELDLL_H
#   include "CHMngtModelDll.h" 
#endif // _CH_MNGTMODELDLL_H

class GData;

class CHModelExport CHRatingDif : public GData  
{
	RWDECLARE_COLLECTABLE(CHRatingDif)

public:
	// Constructors & Destructor
	CHRatingDif();
	CHRatingDif(const short id);
	CHRatingDif(const CHRatingDif & copy);
	CHRatingDif(CPack & aPack);
	virtual ~CHRatingDif();

	// Overloaded Operators
	CHRatingDif & operator  = (const CHRatingDif & copy);
	RWBoolean operator == (const CHRatingDif & copy);
	RWBoolean operator != (const CHRatingDif & copy);

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
	void setCode(const short value);
	void setDifference(const short value);
	void setProbability(const short value);
	

	// Get Methods
	short getCode() const;
	short getDifference() const;
	short getProbability() const;
		
	// Help Methods
	float getProbabilityCode(RWBoolean positive=true);
	RWCString getProbabilityCodeStr();
private:
	// Private Methods
	void      copyRatingDif   (const CHRatingDif & copy);
	RWBoolean compareRatingDif(const CHRatingDif & copy);

private:
	short code;
	short difference;
	short probability;
	
	
};

#endif // !defined(AFX_CHRatingDif_H__EE4E4030_F708_4BC0_AAF6_E43CB04C85C2__INCLUDED_)
