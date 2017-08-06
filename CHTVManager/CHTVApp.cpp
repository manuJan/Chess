/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHTVApp.cpp
*	Description	:Defines the entry point for the application
*
*	Author		: 
*	Date created: 10-Nov-2009
* 	Project		: Volleyball TV
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#include "StdAfx.h"
#include "CHTVApp.h"
#include "CHTVGUI.h"
#include "CHTVTools.h"
#include "Resource.h"

#include "..\CHMngtModel\CHDefinition.h"

HMODULE CHTVApp::m_hModuleRSC=0;

CHTVApp::CHTVApp()
{
	loadRSCLibrary();
}

CHTVApp::~CHTVApp()
{
	if( m_hModuleRSC )
		::FreeLibrary(m_hModuleRSC);
}

void CHTVApp::onInit()
{
	MSLApp::onInit();
}

long CHTVApp::onGetAppType()const
{
	return APP_TYPE_TVFILES;
}

MSLWString CHTVApp::onGetTitle()const
{
	return MSLWString("CHTV");
}

HICON CHTVApp::onGetHIcon() const
{
	HICON icon=::LoadIcon( ((CHTVApp*)MSLAPP)->m_hInstance, MAKEINTRESOURCE(IDI_CHTVMANAGER));
	return icon;
}


GMemoryDataBase *CHTVApp::onNewMemory()
{
	return new CHMemoryDataBase();
}

MSLAppModule * CHTVApp::onGetModule(long id) const
{
	return new CHTVGUI(id);
}

void CHTVApp::loadRSCLibrary()
{
	CHTVTools aTools;
	aTools.init(0);

	MSLString dllName=((CHDefinition&)GMemoryDataBase::getDefinition()).getRSCComposition();
	if( dllName=="" )
		dllName = aTools.getRSCDll();

	#ifdef _DEBUG
	dllName+="d";
	#endif

	dllName+=".dll";
	m_hModuleRSC=::LoadLibrary( dllName.toUnicode() );
}

MSLString CHTVApp::getRSC_TV(const GData * pData, int typeTraslate)
{
	return CHMemoryDataBase::getRSC_Client(m_hModuleRSC,pData,typeTraslate,APP_TV);
}

MSLString CHTVApp::getRSC_Field(MSLString atosRSC, int typeTraslate)
{
	return CHMemoryDataBase::getRSCField_Client(m_hModuleRSC, atosRSC, typeTraslate);
}