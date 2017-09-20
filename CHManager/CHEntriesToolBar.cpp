/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHEntriesToolBar.cpp
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
#include "CHEntriesToolBar.h"
#include "CHManagerApp.h"
#include "resource.h"

#include <ovr\gui\guimanager\resource.h>

CHEntriesToolBar::CHEntriesToolBar(long id)
:GEntriesToolBar(id)
{
}

CHEntriesToolBar::~CHEntriesToolBar(void)
{
}

bool CHEntriesToolBar::onInit()
{
	bool ret = GEntriesToolBar::onInit();

	doSeparator();

	doLabelEx(LX_FIDE_LOAD,"FIDE Import Data",100,"Import data from FIDE file",IDB_BMP_LOAD_ENTRIES);

	doSeparator();

	doLabelEx(LX_SEED_CALCULATION,"Calculate Seed & Ratings",150,"Seed Calculation from initial rating",IDB_BMP_SEED_CALC);

	return ret;
}

HINSTANCE CHEntriesToolBar::getHInstance(int idCtrl,UINT idRes)
{
	if (idCtrl==LX_FIDE_LOAD)
		return CHManagerApp::m_hCHMyModule;

	if (idCtrl==LX_SEED_CALCULATION)
		return CHManagerApp::m_hCHMyModule;

	return GEntriesToolBar::getHInstance(idCtrl,idRes);
}
