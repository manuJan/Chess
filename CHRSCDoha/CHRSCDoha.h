/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHRSCDoha.h
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

#ifdef RSC_EXPORTS
#define RSC_API extern "C" __declspec( dllexport )
#else
#define RSC_API extern "C" __declspec( dllimport )
#endif


RSC_API void getRSC(const char * oris,RWCString& mslRSC,RWCString& mslParams);

