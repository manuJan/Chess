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
// other find functions 
//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////
// Notifications
//////////////////////////////////////////////////////////////////////




MSLString CHMemoryDataBase::getRSC(const GData *pData)
{
	// RSC format: DDSEEEPUUUUU

	MSLString sRsc		 = getDefinition().getCode();
	MSLString strGender  = "0"		;
	MSLString strEvent   = "000000"	;
	MSLString strPhase   = "0"		;
	MSLString strPool	 = "00"		;
	MSLString strUnit	 = "00000"	;
	MSLString strTypeRec = ""	;
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
				if( pMatch )
				{
					strGender = pMatch->getEventSexCode();
					strEvent  = pMatch->getEventCode()+pMatch->getEventCode();
					strPhase  = pMatch->getPhaseCode();
					sprintf_s(aux,"%05d",pMatch->getCode());
					strUnit   = aux;
					sprintf_s(aux,"%02d",pMatch->getPoolCode());
					strPool	  = aux;
				}
				break;
			}			
		}
	}

	return sRsc+strGender+strEvent+strPhase+strPool+strUnit+strTypeRec;
}