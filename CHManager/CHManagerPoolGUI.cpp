/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHManagerPoolGUI.h
*   Description : 
*
*   Author      : Javier Juste
*   Date created: 2-Feb-2010
*   Project     : CH Manager
*
*   Modification history
*   By      :
*   Date    :
*   Changes :
*
*****************************************************************************************/

#include "StdAfx.h"
#include "CHManagerPoolGUI.h"

CHManagerPoolGUI::CHManagerPoolGUI()
:GTHManagerPoolGUI()
{
}

CHManagerPoolGUI::CHManagerPoolGUI(GTHProgressionData* pProgressionData, long id, GData* pData, MSLString idTrigger, bool isPool)
:GTHManagerPoolGUI(pProgressionData, id, pData, idTrigger, isPool)
{
}


CHManagerPoolGUI::~CHManagerPoolGUI(void)
{
}

void CHManagerPoolGUI::onInitOtherControls()
{
	GTHManagerPoolGUI::onInitOtherControls();
		
	m_gui.setTxtN(ED_PL_ROUNDS,7);	
}

