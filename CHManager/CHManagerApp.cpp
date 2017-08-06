// ARManager.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "CHManagerApp.h"
#include "CHSportGUI.h"
#include "CHEventGUI.h"
#include "CHEntriesGUI.h"
#include "CHProgressionGUI.h"
#include "CHScheduleGUI.h"
#include "CHSummaryGUI.h"
//#include "AREventControlGUI.h"
#include "CHMsgGnralGUI.h"
#include "CHMSLODFDataTransfer.h"
#include "resource.h"
#include <OVR/GUI/MSLIPCTransfer/MSLIPCDataTransferDefs.h>
#include <OVR/gui/guimanager/GWeatherGUI.h>
#include <OVR/gui/guimanager/GOfficialsGUI.h>
#include <ovr/gui/guimanager/GDescriptionGUI.h>

#include "..\CHMngtModel\CHMatch.h"

HINSTANCE CHManagerApp::m_hCHMyModule= 0;

CHSendingControl CHSend;

// CHManagerApp construction

CHManagerApp::CHManagerApp()
:GUITHManagerApp()
{
	createStyles();	
}

void CHManagerApp::onInit()
{
	GUITHManagerApp::onInit();
	
	addModule(GSPORTGUI_ID			,L"Configuration"		,0	,L"Tournament Configuration"		,APP_USER_ADMINISTRATOR);
	addModule(GEVENTGUI_ID			,L"Events"				,0	,L"Event Configuration"				,APP_USER_ADMINISTRATOR);
	addModule(GENTRIESGUI_ID		,L"Players"				,0	,L"Entries & Players"				,APP_USER_ADMINISTRATOR);
	addModule(GOFFICIALSGUI_ID		,L"Officials"			,0	,L"Officials & Team Officials"		,APP_USER_ADMINISTRATOR);
	addModule(GTHPROGRESSIONGUI_ID	,L"Progressions"		,0	,L"Tournament Event Format"			,APP_USER_ADMINISTRATOR);	
	addModule(GTHSCHEDULEGUI_ID		,L"Schedule"			,0	,L"Tournament Schedule"				,APP_USER_ADMINISTRATOR);
	//addModule(GTHEVENTCONTROLGUI_ID	,L"Data Entry"			,0	,L"Data Entry"						,ALL_USERS);
	addModule(GSUMMARYGUI_ID		,L"Medals"				,0	,L"Summary & Medallists"			,APP_USER_ADMINISTRATOR);
	addModule(GMSGGNRALGUIEX_ID		,L"Gerenal Msgs"		,0	,L"General Messages"				,APP_USER_ADMINISTRATOR);
	addModule(GDESCRIPTIONGUI_ID	,L"Descriptions"		,0	,L"Descriptions"					,APP_USER_ADMINISTRATOR);
	addModule(DATATRANSFER_GUI		,L"Data transfer"		,0	,L"ODF import/export"				,APP_USER_ADMINISTRATOR);


	// New main logo
	APP_CH::m_hCHMyModule = ((CHManagerApp*)MSLAPP)->m_hInstance;	
}

void CHManagerApp::createStyles()
{
	MSLGUI aGui;	
}

GMemoryDataBase *CHManagerApp::onNewMemory()
{
	return new CHMemoryDataBase();
}

MSLWString CHManagerApp::onGetTitle() const
{
	return L"CH Manager";
}


long CHManagerApp::onGetAppType() const
{
	return APP_TYPE_MANAGER;
}

MSLAppModule *CHManagerApp::onGetModule(long id) const
{
	switch(id)
	{
		case GSPORTGUI_ID			: return new CHSportGUI(GSPORTGUI_ID);
		case GEVENTGUI_ID			: return new CHEventGUI(GEVENTGUI_ID);
		case GENTRIESGUI_ID			: return new CHEntriesGUI(GENTRIESGUI_ID);
		case GOFFICIALSGUI_ID		: return new GOfficialsGUI(GOFFICIALSGUI_ID);
		case GDESCRIPTIONGUI_ID		: return new GDescriptionGUI(GDESCRIPTIONGUI_ID);		
		case GTHPROGRESSIONGUI_ID	: return new CHProgressionGUI(GTHPROGRESSIONGUI_ID);
		case GTHSCHEDULEGUI_ID		: return new CHScheduleGUI(GTHSCHEDULEGUI_ID);
		case GSUMMARYGUI_ID			: return new CHSummaryGUI(GSUMMARYGUI_ID);		
		case GMSGGNRALGUIEX_ID		: return new CHMsgGnralGUI(GMSGGNRALGUIEX_ID);		
		case DATATRANSFER_GUI		: return new CHMSLODFDataTransfer(DATATRANSFER_GUI);
	}
	
	return GUITHManagerApp::onGetModule(id);
}

MSLWString CHManagerApp::getMatchTitle(CHMatch * pMatch,bool lDesc/*=true*/)
{
	MSLWString title;
	title = lDesc ? pMatch->getEventLDescription() : pMatch->getEventLRecordDescription();
	title += L" " + pMatch->getPhaseLDescription();
	title += L" " + pMatch->getPoolDescription(pMatch->getPhase()->getPoolDescription());

	if(pMatch->getIsPool())
	{
		title += L" "+ ((GTHDefinition &)GTHMemoryDataBase::getDefinition()).getSMatchDescription()+MSLWString(' ');
		title += TOWSTRING(pMatch->getCode(),L"0");
	}

	if(pMatch->getSubMatch())
		title += L"-" + TOWSTRING(pMatch->getSubCode(),L"0");

	return title;
}

HBITMAP	CHManagerApp::getBmpColor(HINSTANCE hInst, CHMatchResult::side color)
{
	HBITMAP hBmp=0;
	if(color==CHMatchResult::eWhite)
		hBmp=::LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BMP_WHITE));
	else if(color==CHMatchResult::eBlack)
		hBmp=::LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BMP_BLACK));
		
	return hBmp;
}