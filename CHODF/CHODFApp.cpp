/*************************************************************************************
*			© Copyright MSL Software, S.L., 2012
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHODFApp.cpp
*	Description	:
*
*	Author		: 
*	Date created: 4-6-2012
* 	Project		: Archery ODF
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdafx.h"
#include "CHODFApp.h"
#include "CHODFGUI.h"
#include "CHODFModel.h"
#include <OVR/GUI/ODF2/ODFTHMngr/ODFTHGUI.h>

CHODFApp::CHODFApp()
:ODFTHManagerApp()
{	
}

GMemoryDataBase * CHODFApp::onNewMemory()	
{  
	return new CHMemoryDataBase();
}

HICON CHODFApp::onGetHIcon() const
{
	HICON icon=::LoadIcon( ((CHODFApp*)MSLAPP)->m_hInstance, MAKEINTRESOURCE(IDI_CHODF));
	return icon;
}

MSLWString CHODFApp::onGetTitle() const
{
	return MSLWString("CH ODF v.1.0");
}

ODFGUI * CHODFApp::onNewODFGUI() const
{
	return new CHODFGUI(ODFGUI_ID);
}

ODF2Model * CHODFApp::onNewModel() const
{
	return new CHODFModel();
}

MSLString CHODFApp::getDisciplineCode()
{
	return GDefinition::getCode();
}
