/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHPoolResultGUIEx.h
*   Description : 
*
*   Author      : Javier Juste
*   Date created: 12-FEb-2009
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
#include <OVR/gui/GUITHMANAGER/GTHPoolResultGUIEx.h>

class CHPoolResultGUIEx : public GTHPoolResultGUIEx
{
public:
	CHPoolResultGUIEx(GTHProgression* pProgression, GTHProgressionData* pProgressionData, long id);
	virtual ~CHPoolResultGUIEx();

	
protected:

	/***** Extensions *****/
	MSLGUIEx * onNewGUIEx				(long id);

	/***** Warnings and Erorrs *****/
	int onMsgBox						(long id);

	bool onCreateMatches				(GTHPoolResult *pPoolResult);
	bool onRemoveMatches				(GTHPoolResult* pPoolResult);
	void onCreatePoolResult				(GTHPoolResult*	pPoolResult);

	bool canChangePoolResult			(GTHPoolResult* pPoolResult, int col);
	bool fillComboCompetitors			(GTHPoolResult* pPoolResult);

	PFN_ORDER_FC getGridSortPoolResults () const;
};
