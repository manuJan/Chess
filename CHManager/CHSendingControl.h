/*************************************************************************************
*			© Copyright MSL Software, S.L., 2000 - 2008
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHSendingControl
*	Description	: header file for the CHSendingControl module application
*
*	Author		: 
*	Date created: 
* 	Project		: CHManager
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#pragma once
#include "CHManagerDefs.h"

class CHSplitMatchResult;
class CHMatchResult;
class CHPoolResult;
class CHEventResult;
class CHMatch;
class CHPhase;
class CHEvent;
class CHPool;
class CHInscription;
class CHRegister;
class CHMember;
class CHDefinition;

class CHSendingControl
{
public:
	CHSendingControl(void);
	virtual ~CHSendingControl();

	// Envio a BD & Venue
	void toServerDB(CHDefinition *pDefinition);
	void toServerDB(GTHMatchMember *pMatchMember);	
	void toServerDB(CHMatchResult *pMatchResult);
	void toServerDB(CHPoolResult *pPoolResult);
	void toServerDB(CHMatch *pMatch);
	void toServerDB(CHPool *pPool);
	void toServerDB(CHPhase *pPhase);
	void toServerDB(CHEvent *pEvent);
	void toServerDB(CHInscription *pInscription);	
	void toServerDB(CHEventResult *pEventResult);
	void toServerDB(CHMember *pMember);
	void toServerDB(CHRegister *pRegister);
	void toServerDB(CHRatingDif* pRatingDif);
};
