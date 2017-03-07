/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHRSCDoha.cpp
*	Description	:
*
*	Author		: J. M. Regalado
*	Date created: 11-sep-2006
* 	Project		: CHRSC MSL Dll
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdafx.h"
#include "CHRSCDoha.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
	UNREFERENCED_PARAMETER(hModule);
	UNREFERENCED_PARAMETER(lpReserved);
}

RSC_API void getRSC(const char * oris,RWCString& mslRSC,RWCString& mslParams)
{
	// MSL DDGEEEPUUUUU		->	DOHA DDGEEEPUU

	RWCString ORIS=oris;

	int len = mslRSC.length();
	if( len!=12 )
		return;
	
	RWCString rsc,disc,sex,event,phase,unit;
	// Discipline
	disc	= mslRSC(0,2);
	rsc		= disc;
	// Sex
	sex	= mslRSC[size_t(2)]; // 0,M,W,X
	// Event
	event = mslRSC(3,3);
	
	rsc += sex + event;
	// Phase
	phase = ( mslParams.length() && strcmp(oris,"C58") )?mslParams:mslRSC[size_t(6)];
	// Unit
	unit = "00";
	rsc += phase + unit;
	// Con params con Doha
	mslRSC		= rsc;
}

