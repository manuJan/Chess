/*************************************************************************************
*			© Copyright MSL Software, S.L., 2001
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHStatusManager.cpp
*	Description	: Status manager
*
*	Author		: Javier Juste
*	Date created: 16-Feb-2009
* 	Project		: ARManager 
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/


#include "StdAfx.h"
#include "CHStatusManager.h"

CHStatusManager::CHStatusManager(bool send/*=true*/,bool startList/*=true*/)
:GTHStatusManager(send,startList)
{
}

CHStatusManager::~CHStatusManager()
{
}
