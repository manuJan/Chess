/*************************************************************************************
*	© Copyright MSL Software, S.L., 2008
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: HBRSCAtos.h
*	Description	: 
*
*	Author		:M.
*	Date created:10 Feb 2010
* 	Project		:RSC Atos
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the HBRSCATOS_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// HBRSCATOS_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#ifdef CHRSCATOS_EXPORTS
#define CHRSCATOS_API extern "C" __declspec( dllexport )
#else
#define CHRSCATOS_API extern "C" __declspec( dllexport )
#endif

MSLString getParameterInBuffer(MSLString keyAux,short _index);

CHRSCATOS_API void getRSC(MSLString& msl,MSLString& mslParams,const char * auxInfo,int typeTraslate,int typeClient);
//ARRSCATOS_API MSLString getMSLKey(const char* rsc,long isA);

MSLString getATOSRSC			(MSLString msl,MSLString mslParams,const char* auxInfo,int typeClient);
MSLString getATOSSexCode		(MSLString msl,MSLString mslParams,const char* auxInfo,int typeClient);
MSLString getATOSEventCode		(MSLString msl,MSLString mslParams,const char* auxInfo,int typeClient);
MSLString getATOSPhaseCode		(MSLString msl,MSLString mslParams,const char* auxInfo,int typeClient);
MSLString getATOSEventUnitCode	(MSLString msl,MSLString mslParams,const char* auxInfo,int typeClient);
MSLString getATOSTypeRecordCode	(MSLString msl,MSLString mslParams,const char* auxInfo,int typeClient);

#define ATOS_SWISS_ROUND		"9"
#define ATOS_SF					"2"
#define ATOS_BM					"1"
#define ATOS_GM					"1"
