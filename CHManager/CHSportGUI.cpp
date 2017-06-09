
/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHSportGUI.cpp
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
#include "CHManagerApp.h"
#include "CHSportGUI.h"
#include "..\CHMngtModel\CHDefinition.h"


CHSportGUI::CHSportGUI(long id)
:GSportGUI(id)
{
}

CHSportGUI::~CHSportGUI(void)
{
}

bool CHSportGUI::onInit()
{
	bool ret = GSportGUI::onInit();

	RECT aRc;
	GetClientRect(m_hWnd,&aRc);
	
	// Grids for Points Assignement...
	int al=aRc.left;
	int at=aRc.top;

	m_gui.setRect(GR_LANGUAGE,RC(10,157,800,267));
	m_gui.setRect(LB_LANGUAGE,RC(10,140,800,156));

	CHDefinition &aDefinition = (CHDefinition&)CHMemoryDataBase::getDefinition();

	// Check for Clock Statistics Process.
	m_gui.doLbl(LB_AUTO_PROG		 ,RC(al+550,at+300,al+950,at+316),"Auto Progression",GUIM_ID_STY_TITLE);
	m_gui.base_addFrame(FRM_AUTO_PROG,RC(al+550,at+317,al+950,at+341),RGB(180,180,180),1,10,RGB(245,245,245));	
	m_gui.doCheck(CH_AUTO_PROG		 ,RC(al+555,at+320,al+950,at+336),"Automatic Progression", aDefinition.getAutoProg());		

	return ret;
}

void CHSportGUI::onClick(long id, LPARAM lParam)
{
	CHDefinition &aDefinition = (CHDefinition&)CHMemoryDataBase::getDefinition();
	bool bData=false,bCheck=false;

	switch (id)
	{
	case CH_AUTO_PROG:
			bData = aDefinition.getAutoProg();
			bCheck = m_gui.getCheck(CH_AUTO_PROG);
			if (bData != bCheck)
				aDefinition.setAutoProg(bCheck);
			break;
	default:
			GSportGUI::onClick(id,lParam);
			return;
			break;
	}

	if (bData != bCheck)
	{
		CHSend.toServerDB(&aDefinition);
	}
}