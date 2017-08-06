/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:ARMemoryDataBase.h
*	Description	:
*
*	Author		: Javier Juste
*	Date created: 9 Junio 2008
* 	Project		: Archery DLL
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#pragma once

#include <OVR/CORE/TH/GTHMemoryDataBase.h>
#include <OVR/CORE/G/GMsgDefines.h>

#include "CHMasterType.h"
#include "CHTeamMatchsCnfg.h"
#include "CHRatingDif.h"

typedef MSLString (*PFN_RSC_FIELD)(const char * rsc,int typeTraslate);

class CHMatch;

class CHMngtModelExport CHMemoryDataBase : public GTHMemoryDataBase  
{
public:

	//Construction/Destruction
	CHMemoryDataBase();
	virtual ~CHMemoryDataBase();

	//
	// Init / Reset
	//
	void onInit ();
	
	//
	// Objects
	//
	GData *onNew (long isA);

	// find functions (by Key)/////////////////////////
    static CHMasterType  * findMasterType			(short masterType);
	static CHTeamMatchsCnfg * findTeamMatchsCnfg	(short id);
	static CHRatingDif * findRatingDif				(short ratingCode);
			
	// collections(vectors)
	static void filterCol(MSLSet &colData, GData *pFilterData);
	static void getVector(MSLSet colData, MSLSortedVector &vector, GData *pFilterData=0); // DE UNA COL
	static void getVector(long isA, MSLSortedVector &vector, GData *pFilterData=0); // TODOS
	
	static int  findColorStatus(unsigned char status);

	virtual MSLString	getRSC				(const GData *pData);
	
	// RSC
	static MSLString	getRSCCH			(const GData * pData);
	static MSLString	getRSC_Unit			(const CHMatch *pMatch);
	
	static MSLString	getRSC_Client		(HMODULE hModule, const GData * pData, int typeTraslate, int typeClient=0);
	static MSLString	getRSCField_Client	(HMODULE hModule, MSLString rsc, int typeTraslate, int typeClient=0); 
		
};

