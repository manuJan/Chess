/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHTVApp.h
*	Description	:
*
*	Author		: 
*	Date created: 11-Dec-2009
* 	Project		: CH TV
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#include <ovr/gui/mslapp/MSLApp.h>

#pragma once
#define APP_CH CHTVApp

class CHTVApp :public MSLApp
{
public:
	CHTVApp();
	virtual  ~CHTVApp();

// Overrides
public:
	void onInit();
	/**** Personalización *******************************************/
	virtual long onGetAppType()const;
	virtual MSLWString onGetTitle()const;
	virtual HICON onGetHIcon() const;
	/**** Modelo de datos *******************************************/
	virtual GMemoryDataBase *onNewMemory();
	/**** Módulos (pestañas) ****************************************/
	virtual MSLAppModule *onGetModule(long id) const;

	// RSC Library
	void				loadRSCLibrary();
	static MSLString	getRSC_TV(const GData * pData);
	static MSLString	getRSC_Field(MSLString atosRSC, int typeTraslate); 

private:
	static HMODULE	m_hModuleRSC;
};