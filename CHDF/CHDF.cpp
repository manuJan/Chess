/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHDF.cpp
*	Description	:
*
*	Author		: Chess Team
*	Date created: 17-may-2006
* 	Project		: Chess DataFeed
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdafx.h"
#include "CHDF.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP(CCHDFApp, CDFManagerGUIApp)
	//{{AFX_MSG_MAP(CCHDFApp)
	//}}AFX_MSG
END_MESSAGE_MAP()

CCHDFApp theApp;

CCHDFApp::CCHDFApp()
:CDFManagerGUIApp()
,m_pCHMem(0)
{
}

DFGUI * CCHDFApp::getInterface()
{
	return new CHDFGUI();
}

GMemoryDataBase * CCHDFApp::newMem()	
{  
	m_pCHMem = new CHMemoryDataBase();
	return m_pCHMem;
}


BOOL CCHDFApp::InitInstance()
{
	return CDFManagerGUIApp::InitInstance();
}

CString CCHDFApp::callForAppName()
{
	return "Chess DataFeed";
}

CString CCHDFApp::callForVersion()
{
	return "1.0";
}

void CCHDFApp::fillMyCollections(RWHashTable& sSource)
{
	UNREFERENCED_PARAMETER(sSource);
}



