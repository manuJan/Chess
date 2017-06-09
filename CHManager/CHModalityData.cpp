/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHModalityData.h
*   Description : 
*
*   Author      : Javier Juste
*   Date created: 2-FEb-2009
*   Project     : AR Manager
*
*   Modification history
*   By      :
*   Date    :
*   Changes :
*
*****************************************************************************************/


#include "StdAfx.h"
#include "CHModalityData.h"

CHModalityData::CHModalityData(MSLGUIEx* pMSLGUIEx)
:GTHModalityData(pMSLGUIEx)
{
}

CHModalityData::~CHModalityData()
{
}

void CHModalityData::onCreateModalityPhase(GTHModalityPhase* pModalityPhase, GTHPhase* pPhase)
{
	/*((ARModalityPhase*)pModalityPhase)->setNumArrows		( ((CHPhase*) pPhase)->getNumArrows());
	((ARModalityPhase*)pModalityPhase)->setNumEnds			( ((CHPhase*) pPhase)->getNumEnds());
	((ARModalityPhase*)pModalityPhase)->setNumArrowsShootOff( ((CHPhase*) pPhase)->getNumArrowsShootOff());
	((ARModalityPhase*)pModalityPhase)->setNumEndsShootOff	( ((CHPhase*) pPhase)->getNumEndsShootOff());
	((ARModalityPhase*)pModalityPhase)->setSOSplit			( ((CHPhase*) pPhase)->getSOSplit());
	((ARModalityPhase*)pModalityPhase)->setClosestSplit		( ((CHPhase*) pPhase)->getClosestSplit());
	((ARModalityPhase*)pModalityPhase)->setScoringType		( ((CHPhase*) pPhase)->getScoringType());*/
}

