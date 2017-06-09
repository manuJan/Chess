/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHProgressionData.h
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

#pragma once
#include "CHManagerDefs.h"
#include <OVR/gui/GUITHMANAGER/GTHProgressionData.h>

class CHProgressionData : public GTHProgressionData
{
public:
	CHProgressionData(MSLGUIEx *pGUIEx);
	virtual ~CHProgressionData();

	bool preSelectModality			(GTHEvent* pEvent, GTHModality* pModality);

	GTHPhase* createPhase			(GTHEvent* pEvent, MSLString phaseCode, GTHModalityPhase* pModalityPhase);

	void onCreatePhase				(GTHPhase* pPhase, GTHModalityPhase* pModalityPhase);
	void onCreatePoolResult			(GTHPoolResult*	pPoolResult, GTHModalityPool * pModalityPool);	
	void onCreateMatch				(GTHMatch* pMatch, GTHModalityPool * pModalityPool);
	void onCreateMatchResult		(GTHMatchResult* pMatchResult, GTHModalityPool * pModalityPool);

	bool onMatchResultCreated		(GTHMatchResult* pMatchResult, GTHModalityPool* pModalityPool);

	GTHMatchMember * createMatchMember(CHMatchResult* pMatchResult, short matchMember);

	void calculatePoolPosition		(GTHMatch* pMatch, short position, int &local, int &away, int &poolPos);	
	int	calculateMatchesByPool		(int nCompetitors);
};
