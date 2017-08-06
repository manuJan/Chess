/*************************************************************************************
*	© Copyright MSL Software, S.L., 2008
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: ARRSCAtos.cpp
*	Description	: 
*
*	Author		:
*	Date created:20 Mar 2010
* 	Project		:RSC Atos
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdafx.h"
#include "CHRSCAtos.h"
#include "..\CHMngtModel\CHMatch.h"
#include "..\CHMngtModel\CHPool.h"

CHRSCATOS_API void getRSC(MSLString& msl,MSLString& params,const char * auxInfo,int typeTraslate/*=0*/,int typeClient/*=0*/)
{
	int len = msl.length();
	if( len==17 )
	{
		if (MSLString(auxInfo) == "C75" || MSLString(auxInfo) == "C74")
		{
			MSLString rsc=msl(0,2); //Discipline
			rsc+=getATOSSexCode(msl,params,auxInfo,typeClient);
			rsc+=getATOSEventCode(msl,params,auxInfo,typeClient);
			rsc+=getATOSPhaseCode(msl,params,auxInfo,typeClient);
			rsc+="00";
			msl=rsc;
		}
		else if(typeTraslate==RSC_ALL)
			msl=getATOSRSC(msl,params,auxInfo,typeClient);
		else if(typeTraslate==RSC_SEX)
			msl=getATOSSexCode(msl,params,auxInfo,typeClient);
		else if(typeTraslate==RSC_EVENT)
			msl=getATOSEventCode(msl,params,auxInfo,typeClient);
		else if(typeTraslate==RSC_PHASE)
			msl=getATOSPhaseCode(msl,params,auxInfo,typeClient);
		else if(typeTraslate==RSC_UNIT)
			msl=getATOSEventUnitCode(msl,params,auxInfo,typeClient);
	
		// RSC de Date (DD0000YDD)
		if( params.index("D_") != -1 )
		{
			// mslParams Date (D_YYYYMMDD) => (D_20101230)
			MSLString YYYYMMDD = params.after("D_");
			if( YYYYMMDD.length() == 8 )
			{
				MSLString rsc=msl(0,2); //Discipline
				rsc+=getATOSSexCode			(msl,params,auxInfo,typeClient);
				rsc+=getATOSEventCode		(msl,params,auxInfo,typeClient);
				rsc+="Y";				// Traducimos Phase(Y) con el caracter 'Y'
				rsc+=YYYYMMDD(6,2);		// Traducimos Unit(DD) con el dia
				msl=rsc;
			}
		}		
	}
}

CHMatch* findMatch(MSLString ge, MSLString ev, MSLString ph, short pool, short unit)
{
	//buscamos el match
	MSLSetIterator iter(CHMemoryDataBase::getCol(__CHMATCH));
	CHMatch *pMatch = 0;
	while( (pMatch = (CHMatch *)iter())!=0 )
	{
		if (pMatch->getEventSexCode()	== ge &&  
			pMatch->getEventCode()		== ev && 
			pMatch->getPhaseCode()		== ph && 
			pMatch->getPoolCode()		== pool && 
			pMatch->getCode()			== unit)
			return pMatch;			
	}
	return 0;
}

MSLString translatePhaseCode(CHMatch *pMatch)
{
	if (!pMatch )
		return NULLSTRING;

	if (pMatch->getPhaseCode() == SWISS_ROUND )
	{
		wchar_t txt[200];
		short round = pMatch->getRound();
		swprintf_s(txt,L"%c",(round-1)+'A');
		return txt;
	}
		
	if (pMatch->getPhaseCode() == SEMIFINAL)
		return ("2");		// Fase SEMIFINAL
	
	return ("1");			// Fase FINAL
}


MSLString getATOSRSC(MSLString msl,MSLString mslParams,const char* auxInfo,int typeClient)
{
	MSLString rsc=msl(0,2); //Discipline
	rsc+=getATOSSexCode			(msl,mslParams,auxInfo,typeClient);
	rsc+=getATOSEventCode		(msl,mslParams,auxInfo,typeClient);
	rsc+=getATOSPhaseCode		(msl,mslParams,auxInfo,typeClient);
	rsc+=getATOSEventUnitCode	(msl,mslParams,auxInfo,typeClient);
	return rsc;
}

MSLString getATOSSexCode(MSLString msl,MSLString mslParams,const char* auxInfo,int typeClient)
{
	UNREFERENCED_PARAMETER(mslParams);
	UNREFERENCED_PARAMETER(typeClient);
	UNREFERENCED_PARAMETER(auxInfo);

	MSLString mslSex=msl(2,1);
	return mslSex;
}

MSLString getATOSEventCode(MSLString msl,MSLString mslParams,const char* auxInfo,int typeClient)
{
	UNREFERENCED_PARAMETER(mslParams);
	UNREFERENCED_PARAMETER(typeClient);
	UNREFERENCED_PARAMETER(auxInfo);

	MSLString mslEvent=msl(3,3);
	return mslEvent;
}

MSLString getATOSPhaseCode(MSLString msl,MSLString mslParams,const char* auxInfo,int typeClient)
{
	UNREFERENCED_PARAMETER(typeClient);
	MSLString mslGender	=msl(2 ,1);
	MSLString mslEvent	=msl(3 ,3);
	MSLString mslPhase=msl(9,1);
	MSLString mslPool=msl(10,2);
	MSLString mslUnit	=msl(12,3);

	if ( mslPhase == SWISS_ROUND )	//Fase PRELIMINARY
	{
		CHMatch* pMatch = findMatch(mslGender,mslEvent,mslPhase,short(atoi(mslPool)),short(atoi(mslUnit)));
		if (pMatch)
			return translatePhaseCode(pMatch);

		return ATOS_SWISS_ROUND;
	}
	else if (mslPhase == SEMIFINAL )
		return ATOS_SF;
	else if (mslPhase == BRONZE_MEDAL )
		return ATOS_BM;
	else if (mslPhase == GOLD_MEDAL	)
		return ATOS_GM;
	
	return mslPhase;
	
	UNREFERENCED_PARAMETER(auxInfo);
}

MSLString getATOSEventUnitCode(MSLString msl,MSLString mslParams,const char* auxInfo,int typeClient)
{
	UNREFERENCED_PARAMETER(auxInfo);
	UNREFERENCED_PARAMETER(typeClient);

	MSLString key=msl(2,4); //Discipline+Sex+Event
	
	MSLString mslGender	=msl(2 ,1);
	MSLString mslSex  =msl(2, 1);
	MSLString mslEvent=msl(3 ,3);
	MSLString mslPhase=msl(9 ,1);
	MSLString mslPool=msl(10 ,2);	
	MSLString mslUnit =msl(12,3);
	MSLString mslUnit2 =msl(15,2);

	key+= mslPhase;
	key+= mslPool;
	key+= mslUnit2;
	key+= "00";

	MSLString strMsl(msl);
	if( MSLString(auxInfo)=="C67" )
	{
		int len = strMsl.length();
		if(len>=7)
			mslUnit = strMsl(len-2,2);
		return mslUnit;
	}

	CHEvent * pEvent=(CHEvent*)CHMemoryDataBase::findEvent(mslEvent,mslSex);
	MSLString matchCode;

	if(pEvent && (pEvent->isTeam()))
	{
		if(mslPhase=="B")		//Fase de Bronce Match=02
			matchCode="02";
		else if(mslPhase=="1")	//Fase de Oro	 Match=01
			matchCode="01";
		else if (mslPhase==SWISS_ROUND)
		{
			CHMatch* pMatch = findMatch(mslGender,mslEvent,mslPhase,short(atoi(mslPool)),short(atoi(mslUnit)));
			if (pMatch)
			{
				CHPool* pPool = (CHPool*) pMatch->getPool();
				short round = pMatch->getRound();
				short roundMatches = pPool ? pPool->getRoundMatches(round) : 0;
				short code = pMatch->getCode();				

				matchCode.format("%.2d",( code - ( (round-1)*roundMatches)));
			}
			else
				matchCode=mslUnit(1,2);
		}
		else
			matchCode=mslUnit(1,2);
	}
	else //Eventos normales //viene 3(getCode),2(getSubCode);
	{
		if(mslPhase=="B")		//Fase de Bronce Match=02
			matchCode="02";
		else if(mslPhase=="1")	//Fase de Oro	 Match=01
			matchCode="01";
		else if (mslPhase==SWISS_ROUND)
		{
			CHMatch* pMatch = findMatch(mslGender,mslEvent,mslPhase,short(atoi(mslPool)),short(atoi(mslUnit)));
			if (pMatch)
			{
				CHPool* pPool = (CHPool*) pMatch->getPool();
				short round = pMatch->getRound();
				short roundMatches = pPool ? pPool->getRoundMatches(round) : 0;
				short code = pMatch->getCode();				

				matchCode.format("%.2d",( code - ( (round-1)*roundMatches)));
			}
			else
				matchCode=mslUnit(1,2);
		}
		else
			matchCode=mslUnit(1,2);
	}
	
	return matchCode;

	/*CHMatch * pMatch=(CHMatch*)CHMemoryDataBase::getCol(__CHMATCH).find(&key);
	if(pMatch)
	{
		if (pMatch->getPhaseCode()==GOLD_MEDAL)
			return "01";

		if (pMatch->getPhaseCode()==BRONZE_MEDAL)
			return "02";
	}

	MSLString unit =mslUnit(3,2);
	return unit;*/
}

// Si pasara diferentes parametros
MSLString getParameterInBuffer(MSLString keyAux,short _index)
{
	MSLString params=keyAux;
	MSLString parameter = "";
	char szName[MAX_PATH];
	params.toUpper();
	strcpy_s(szName,params);
	int index=0;
	char *p=szName,*pp=NULL,*out=szName+strlen(szName);
	while( p<out )
	{
		pp=strchr(p,int('_'));
		if( pp && *pp )
			*pp=0;
		if(index==_index)		//RSC
			parameter = p;
		index++;
			p=pp?pp+1:out;
	}
	return parameter;		
}
