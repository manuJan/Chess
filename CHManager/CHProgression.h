/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHProgression.h
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
#include <OVR/gui/GUITHMANAGER/GTHProgression.h>

class CHEvent;
class CHPhase;
class CHPoolResult;
class CHMatchResult;
class CHMatch;

class CHProgression : public GTHProgression
{
public:
	CHProgression(MSLGUIEx* pGUIEx);
	virtual ~CHProgression();


	void setData				(GTHInscription* pInscription, GTHMatchResult* pMatchResult, bool bye, bool includeSubMacthes, bool progression=true);
	void initAllMatchMember		(CHMatchResult * pMatchResult);

	void manageByes					(CHMatch *pMatch);
	void setAutoSubMatchesAssign	(CHMatch *pMatch);
	void removeAutoSubMatchesAssign (CHMatch *pMatch);
	void changeSide					(CHMatch *pMatch);
	void startListMatch				(CHMatch *pMatch);
};
