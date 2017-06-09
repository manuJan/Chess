/*************************************************************************************
*			© Copyright MSL Software, S.L., 2000 - 2008
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHSendingControl
*	Description	: Defines the class behaviors for the CHSendingControl module application.
*
*	Author		: Jose Matas
*	Date created: 20 Enero 2008
* 	Project		: CHManager
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "StdAfx.h"
#include "CHManagerApp.h"
#include "CHSendingControl.h"

#include <OVR/Core/G/GMsgDefines.h>
#include <OVR/Core/TH/GTHMsgDefines.h>
#include "..\CHMngtModel\CHSportDefines.h"

#include "..\CHMngtModel\CHDefinition.h"
#include "..\CHMngtModel\CHSplitMatchResult.h"
#include "..\CHMngtModel\CHMatchResult.h"
#include "..\CHMngtModel\CHPoolResult.h"
#include "..\CHMngtModel\CHEventResult.h"
#include "..\CHMngtModel\CHMatch.h"
#include "..\CHMngtModel\CHPhase.h"
#include "..\CHMngtModel\CHEvent.h"
#include "..\CHMngtModel\CHPool.h"
#include "..\CHMngtModel\CHInscription.h"
#include "..\CHMngtModel\CHRegister.h"
#include "..\CHMngtModel\CHMember.h"
#include "..\CHMngtModel\CHDefinition.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHSendingControl::CHSendingControl(void)
{

}

CHSendingControl::~CHSendingControl(void)
{

}

// *** UPDATES BD & VENUE ************************************************************

void CHSendingControl::toServerDB(CHDefinition *pDefinition)
{
	APP::out(*pDefinition);
	APP::out(TRN_SET_DEFINITION);	
}

void CHSendingControl::toServerDB(GTHMatchMember *pMatchMember)
{
	APP::out(*pMatchMember);
	APP::out(TRN_SET_MATCHMEMBER);
}

void CHSendingControl::toServerDB(CHMatchResult *pMatchResult)
{
	APP::out(*pMatchResult);
	APP::out(TRN_SET_MATCHRESULT);
}

void CHSendingControl::toServerDB(CHPoolResult *pPoolResult)
{
	APP::out(*pPoolResult);
	APP::out(TRN_SET_POOLRESULT);
}
	
void CHSendingControl::toServerDB(CHMatch *pMatch)
{
	APP::out(*pMatch);
	APP::out(TRN_SET_MATCH);
}

void CHSendingControl::toServerDB(CHPool *pPool)
{
	APP::out(*pPool);
	APP::out(TRN_SET_POOL);
}

void CHSendingControl::toServerDB(CHPhase *pPhase)
{
	APP::out(*pPhase);
	APP::out(TRN_SET_PHASE);
}

void CHSendingControl::toServerDB(CHEvent *pEvent)
{
	APP::out(*pEvent);
	APP::out(TRN_SET_EVENT);
}

void CHSendingControl::toServerDB(CHInscription *pInscription)
{
	APP::out(*pInscription);
	APP::out(TRN_SET_INSCRIPTION);
}

void CHSendingControl::toServerDB(CHEventResult *pEventResult)
{
	APP::out(*pEventResult);
	APP::out(TRN_SET_EVENTRESULT);
}

void CHSendingControl::toServerDB(CHMember *pMember)
{
	APP::out(*pMember);
	APP::out(TRN_SET_MEMBER);
}

void CHSendingControl::toServerDB(CHRegister *pRegister)
{
	APP::out(*pRegister);
	APP::out(TRN_SET_REGISTER);
}

void CHSendingControl::toServerDB(CHRatingDif* pRatingDif)
{
	APP::out(*pRatingDif);
	APP::out(TRN_SET_RATING_DIF);
}