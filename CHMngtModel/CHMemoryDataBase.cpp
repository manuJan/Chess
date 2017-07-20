/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHMemoryDataBase.cpp                                                                 
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:12-12-2005
*   Project     :CH Model       
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///

#include "stdCHMngt.h"
#include "CHMemoryDataBase.h"
#include "CHMemoryDataBaseDefs.h"
#include "CHDefinition.h"
#include "CHEvent.h"
#include "CHPhase.h"
#include "CHPhaseBase.h"
#include "CHPool.h"
#include "CHMatch.h"
#include "CHRegister.h"
#include "CHInscription.h"
#include "CHMember.h"
#include "CHPoolResult.h"
#include "CHMatchResult.h"
#include "CHSplitMatchResult.h"
#include "CHEventResult.h"


CHMemoryDataBase::CHMemoryDataBase()
:GTHMemoryDataBase()
{
}

CHMemoryDataBase::~CHMemoryDataBase()
{ 	
}


void CHMemoryDataBase::onInit ()
{
	GTHMemoryDataBase::onInit();

	addCol(__CHMASTERTYPE);
	addCol(__CHTEAMMATCHSCNFG);	
	addCol(__CHRATINGDIF);
	
}

GData *CHMemoryDataBase::onNew(long isA)
{
	switch ( isA )
	{
	case __CHDEFINITION: 
		return new CHDefinition();
	case __CHEVENT:
		return new CHEvent();
	case __CHPHASE:
		return new CHPhase();
	case __CHPHASEBASE:
		return new CHPhaseBase();
	case __CHPOOL:
		return new CHPool();
	case __CHMATCH:
		return new CHMatch();
	case __CHREGISTER:
		return new CHRegister();
	case __CHINSCRIPTION:
		return new CHInscription();
	case __CHMEMBER:
		return new CHMember();
	case __CHPOOLRESULT:
		return new CHPoolResult();
	case __CHMATCHRESULT:
		return new CHMatchResult();
	case __CHSPLITMATCHRESULT:
		return new CHSplitMatchResult();
	case __CHEVENTRESULT:
		return new CHEventResult();	
	case __CHMASTERTYPE: 
		return new CHMasterType();	
	case __CHTEAMMATCHSCNFG:
		return new CHTeamMatchsCnfg();	
	case __CHRATINGDIF:
		return new CHRatingDif();
	}
	return GTHMemoryDataBase::onNew(isA);
}


//////////////////////////////////////////////////////////////////////
// find functions (by Key)
//////////////////////////////////////////////////////////////////////

CHMasterType  * CHMemoryDataBase::findMasterType(short masterType)
{
	CHMasterType aMasterType(masterType);
	return (CHMasterType *)find(aMasterType);
}

CHTeamMatchsCnfg * CHMemoryDataBase::findTeamMatchsCnfg	(short id)
{
	CHTeamMatchsCnfg aTeamMatchsCnfg(id);
	return (CHTeamMatchsCnfg*)find(aTeamMatchsCnfg);
}

CHRatingDif * CHMemoryDataBase::findRatingDif(short ratingCode)
{
	CHRatingDif aRatingDif(ratingCode);
	return (CHRatingDif*)find(aRatingDif);
}	


//////////////////////////////////////////////////////////////////////
// collections(vectors)
//////////////////////////////////////////////////////////////////////

void CHMemoryDataBase::filterCol(MSLSet &colData, GData *pFilterData)
{
	if( !colData.entries() || !pFilterData )
		return;

	mslToolsFcSelect pFn=0;

	MSLSetIterator it(colData);
	GData * pData = (GData*)it(); // el primero
	switch( pData->isA() )
	{
	case __CHPHASE:			pFn = ((CHPhase*)pData)->getSelectFn(pFilterData); break;
	case __CHMATCH:			pFn = ((CHMatch*)pData)->getSelectFn(pFilterData); break;
	case __CHINSCRIPTION:	pFn = ((CHInscription*)pData)->getSelectFn(pFilterData); break;
	case __CHMATCHRESULT:	pFn = ((CHMatchResult*)pData)->getSelectFn(pFilterData); break;
	case __CHEVENTRESULT:	pFn = ((CHEventResult*)pData)->getSelectFn(pFilterData); break;
	case __CHPOOLRESULT:	pFn = ((CHPoolResult*)pData)->getSelectFn(pFilterData); break;
	}
	
	// select
	if( pFn )
		colData = colData.select(pFn, (void*)pFilterData);
}

void CHMemoryDataBase::getVector(MSLSet colData, MSLSortedVector &vector, GData *pFilterData/*=0*/)
{
	filterCol(colData,pFilterData);
	vector = colData.asSortedVector();
}

void CHMemoryDataBase::getVector(long isA, MSLSortedVector &vector, GData *pFilterData/*=0*/)
{
	MSLSet colData = getCol(isA);
	getVector(colData, vector, pFilterData);
}



MSLString CHMemoryDataBase::getRSC(const GData *pData)
{
	MSLString rsc = getRSCCH(pData);
	return rsc;
}

MSLString CHMemoryDataBase::getRSCCH(const GData * pData)
{
		// RSC format: DDSEEEPUUUUU

	MSLString sRsc		 = getDefinition().getCode();
	MSLString strGender  = "0"		;
	MSLString strEvent   = "000000"	;
	MSLString strPhase   = "0"		;
	MSLString strPool	 = "00"		;
	MSLString strUnit	 = "00000"	;
	char aux[10]={0};

	if( pData )
	{
		switch( pData->isA() )
		{
			case __GSEX:
			{
				GSex *pSex = (GSex *)pData;
				if( pSex )
					strGender = pSex->getSex();
				break;
			}
			case __CHEVENT:
			{
				CHEvent *pEvent = (CHEvent *)pData;
				if( pEvent )
				{
					strGender = pEvent->getSex();
					strEvent  = pEvent->getEvent()+pEvent->getEvent();
				}
				break;
			}
			case __CHPHASE:
			{
				CHPhase *pPhase = (CHPhase *)pData;
				if( pPhase )
				{
					strGender = pPhase->getEventSexCode();
					strEvent  = pPhase->getEventCode()+pPhase->getEventCode();
					strPhase  = pPhase->getPhase();
				}
				break;
			}
			case __CHPOOL:
			{
				CHPool *pPool = (CHPool *)pData;
				if( pPool )
				{
					strGender = pPool->getEventSexCode();
					strEvent  = pPool->getEventCode()+pPool->getEventCode();
					strPhase  = pPool->getPhaseCode();
					sprintf_s(aux,"%02d",pPool->getPool());
					strPool	  = aux;
				}
				break;
			}			
			case __CHMATCH:
			{
				CHMatch *pMatch = (CHMatch *)pData;

				MSLString poolCode;
				poolCode.format("%.2d",pMatch->getPoolCode());

				MSLString matchCode;
				if((pMatch->isTeam()))
					matchCode.format("%.3d%.2d",pMatch->getCode(),pMatch->getSubCode());
				else
					matchCode.format("%.3d%.2d",pMatch->getCode(),pMatch->getSubCode());

				strGender=pMatch->getEventSexCode();
				strEvent=pMatch->getEventCode()+pMatch->getEventParentCode();
				strPhase=pMatch->getPhaseCode();
				strPool=poolCode;
				strUnit=matchCode;				
				break;
			}			
		}
	}

	return sRsc+strGender+strEvent+strPhase+strPool+strUnit;
}

MSLString CHMemoryDataBase::getRSC_Unit(const CHMatch *pMatch)
{
	MSLString rsc = "00";
	if( !pMatch )
		return rsc;

	/* Solo para generar RSCs con Atos como cliente.
	short eu = pMatch->getCode(false); // si hay byes previos fijos, los descuenta
	*/
	short eu = pMatch->getCode(); // si hay byes previos fijos, NO los descuenta
	char euCode[3];
	sprintf_s(euCode,3,"%.2d",eu);
	rsc = euCode;

	return rsc;
}

MSLString CHMemoryDataBase::getRSC_Client(HMODULE hModule, const GData * pData, int typeClient/*=0*/)
{
	MSLString value = CHMemoryDataBase::getRSCCH(pData); // MSL code

	if( !hModule )
		return value;

	MSLString params="";
	int typeTraslate=RSC_ALL;
	if( pData )
	{
		if( pData->isA()==__GSESSION )
		{
			GSession *pSession = (GSession *)pData;
			params="D_"+pSession->getDateAsString("%Y%m%d").toAscii()+"_S_"+TOSTRING(pSession->getAcumulated(),"0");
		}
		else if( pData->isA()==__GEVENT )
			typeTraslate=RSC_EVENT;
		else if( pData->isA()==__GPHASE )
			typeTraslate=RSC_PHASE;
		else if( pData->isA()==__CHMATCH )
			typeTraslate=RSC_UNIT;
	}
	
	PFN_RSC m_pProcedureRSC = (PFN_RSC)::GetProcAddress(hModule,"getRSC");
	if( m_pProcedureRSC )
		((*m_pProcedureRSC)(value,params,"",typeTraslate,typeClient));
	return value;
}

MSLString CHMemoryDataBase::getRSCField_Client(HMODULE hModule, MSLString rsc, int typeTraslate)
{
	if( !rsc.length() )
		return "";
	MSLString value="",g="",ev="",ph="",unit="";
	
	// El rsc pasado es el de msl
	if( rsc.length()==17 )
	{
		g	= rsc(2,1);
		ev	= rsc(6,3);		// Nos saltamos el event parent
		ph	= rsc(9,1);
		unit= rsc(15,2);	// dos ultimos
	}
	switch( typeTraslate )
	{
	case RSC_ALL:		value = rsc;	break;
	case RSC_GENDER:	value = g;		break;
	case RSC_EVENT:		value = ev;		break;
	case RSC_PHASE:		value = ph;		break;
	case RSC_UNIT:		value = unit;		break;
	}
	
	if( !hModule )
		return value;
	
	PFN_RSC_FIELD m_pProcedureRSC = (PFN_RSC_FIELD)::GetProcAddress(hModule,"getRSC_Field");
	if( m_pProcedureRSC )
		value = ((*m_pProcedureRSC)(rsc,typeTraslate));
	return value;
}