/*************************************************************************************
*			© Copyright MSL Software, S.L., 2012
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHODFGUI.cpp
*	Description	:
*
*	Author		: 
*	Date created: 6-4-2012
* 	Project		: Archery ODF
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#include "StdAfx.h"
#include "CHODFGUI.h"
#include "CHODFOrderExt.h"
#include "CHODFBuildMessage.h"

CHODFGUI::CHODFGUI(long id)
:ODFTHGUI(id)
{
}

CHODFGUI::~CHODFGUI()
{
}

//virtual from ODFGUI
MSLGUIEx * CHODFGUI::onNewODFEx(long id)
{
	switch(id)
	{
	case ODFORDER_ID:
		{
			CHODFOrderExt * pOrder = new CHODFOrderExt(ODFORDER_ID,this);
			return pOrder;
		}
	}
	return ODFGUI::onNewODFEx(id);
}

ODFBuildMessage * CHODFGUI::onNewBuildMessage()
{
	return new CHODFBuildMessage(this);
}
