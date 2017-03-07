/*************************************************************************************
*	© Copyright MSL Software, S.L., 2001
*
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHManager.cpp
*   Description	: 
*
*	Author		:Chess Team
*	Date created:15-07-2005
* 	Project		:CH Manager
*
***************************************************************************************/

#include "stdafx.h"
#include "CHManager.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <GUI/GS/GDBObject.h>
#include "CHDefines.h"

#include "CHCnfgDisciplineFormView.h"
#include "CHProgressionFormView.h"
#include "CHCnfgEventsFormView.h"
#include "CHInscriptionFormView.h"
#include "CHNARegisterFormView.h"
#include "CHScheduleFormView.h"
#include "CHEventControlFormView.h"
#include "CHMatchVisorFormView.h"

// Reports
#include <Sports/CH/Reports/CHReportDefines.h>
#include <Sports/CH/Reports/CHRC93.h>
#include <Sports/CH/Reports/CHRC95.h>
#include <Sports/CH/Reports/CHRC96.h>


#define ID_LOGO			2000
#define	BMP_LOGO		2001

#define LIMIT	20


BEGIN_MESSAGE_MAP(CCHManagerApp, GManagerInterfaceApp)
	//{{AFX_MSG_MAP(CCHManagerApp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CCHManagerApp theApp;

////////////////////////////////////////////////////////////////////////////////////
static int orderEventsCLa(const GVectorElement** a, const GVectorElement** b)
{
	CHEvent * pEvA = (CHEvent *)(*a)->getElement();
	CHEvent * pEvB = (CHEvent *)(*b)->getElement();

	return stricmp(pEvA->getKey(),pEvB->getKey());
}

CCHManagerApp::CCHManagerApp()
:iniFileName("")
,pVMedalsByEvent(0)
,login(0)
{
}

GMemoryDataBase *CCHManagerApp::callForCreateMemoryDB()
{
	return new CHMemoryDataBase();
	
}

CString CCHManagerApp::callForAppName()
{	
	// Devolver nombre de la aplicación.	
	return _T("Chess Manager");
}

void CCHManagerApp::callForLogins()
{
	addLogin(ADMINISTRATOR_LOGIN,"Administrator","msl2003");
    addLogin(DATA_ENTRY_LOGIN   ,"DataEntry");
}
void CCHManagerApp::callForCreateButtons()
{
	// Crear botones principales de la aplicación de la forma:
	addButton("Discipline"		,RUNTIME_CLASS(CCHCnfgDisciplineFormView)	,"Discipline"				,1	);	
	addButton("Events"			,RUNTIME_CLASS(CCHCnfgEventsFormView	)	,"Events"					,1	);	
	addButton("Inscriptions"	,RUNTIME_CLASS(CHInscriptionFormView    )	,"Inscrptions"				,1	);
	addButton("Judges & Off."	,RUNTIME_CLASS(CHNARegisterFormView		)	,"Judges and Officials"		,1	);
	addButton("Progressions"	,RUNTIME_CLASS(CHProgressionFormView	)	,"Progressions"				,1	);	
	addButton("Schedule"		,RUNTIME_CLASS(CHScheduleFormView		)	,"Schedule Configuration"	,1	);
	addButton("Visor"			,RUNTIME_CLASS(CHMatchVisorFormView		)	,"Visor"					,1	);
	//addButton("Event Control"	,RUNTIME_CLASS(CHEventControlFormView	)	,"Data Entry"				,1+2);
	
					
}

UINT CCHManagerApp::callForDefaultButtons()
{
	// Crea botones por defecto de modulos generales según el valor devuelto.
	// p.e. return BUTTON_MEDALS para trabajar con puerto serie.
	return BUTTON_MEDALS;
}

void CCHManagerApp::callWhenConnected()
{
	// Este método es invocado dos veces cuando sabe donde 
	// va a conectarse (servidor, database, ...)
	// antes y despues de hacer la carga (segun parámetro "loaded")
/*	if( loaded )
	{
		CHMemoryDataBase * pMem=(CHMemoryDataBase *)((CCHManagerApp*)AfxGetApp())->memG();
		if( pMem )
		{
			// Cogemos el bitmap
			((CCHManagerApp *)AfxGetApp())->m_pMainWnd->SetWindowText(_T("CHManager"));
			pWUp->addBitmap(BMP_LOGO,IDB_LOGOCH);
			// Cambiamos el logo			
			pWUp->createBitmap(ID_LOGO,BMP_LOGO,5,2,FALSE,BORDER_SINGLE,IDCOL);
		}
	}*/
}

void CCHManagerApp::callForPresentationDown(CGraphicWnd *w)
{
	// Control del interface gráfico de la parte inferior inicial.
	// Control del interface gráfico de la parte inferior inicial.

	w->addBitmapT(1234,IDB_BMP_CH);
	w->createBitmap(1234,1234,0,0,FALSE,BORDER_3DDOWN,IDCOL);
}
void CCHManagerApp::callForPresentationUp(CGraphicWnd *w)
{
	// Control del inteface gráfico de la parte superior.
	// Acceso directo al interface general. ¡¡¡CUIDADO!!!	
	pWUp = w;
}
UINT CCHManagerApp::callForIDBLogo()
{
	// Devolver identificador de bitmap con el logo del deporte o 0 si no se desea.
	// Dimensión recomendada: 200(H)x50(V) pixels
	return IDB_LOGOCH;
		
}

RWCString *CCHManagerApp::callForReportsIniFile()
{
	iniFileName = GDiscipline::getCode();
	iniFileName += "ReportsCfg.ini";

	return &iniFileName;  
}

LRESULT	CCHManagerApp::callForAvancedCase(UINT message,WPARAM wParam,LPARAM lParam)
{
	// Mensajes avanzados desde la aplicación general; entre otros:
	// AVANCED_PERSONAL_INTERFACE, UM_REPORT_REQUEST, UM_REPORT_GENERATION
	
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);
	switch(message)
	{
	case AVANCED_REPORT_MEDALS_AUTOFILL:
		showMedals();
		break;
	case AVANCED_ID_LOGIN_INFO:
		login = lParam;
		break;
	}

	return 0;
}

void CCHManagerApp::showMedals()
{	// Añadimos el submenu de eventos del report Medals By Event.
	addReport(RC92,0,RC92_NAME	,RC92);
	addReport(RC93,0,RC93_NAME	,RC93);
	addReport(RC95,0,RC95_NAME	,RC95);
	
	addReport(RC96,0,RC96_NAME	,RC96);
}
CString	CCHManagerApp::callForVersion()
{
	// Devolver número de versión 
	return _T("1.0");
}

void CCHManagerApp::onReportRequest(CReportItem *pItem)
{
	// Se está solicitando información de un report
	if( !pItem )
		return;

	CWnd * pWnd = getCurrentDownWnd();
	if( !pWnd )
		return;
	
	switch( pItem->getModule() )
	{
	case CH_INSCRIPTION_FORMVIEW:
		((CHInscriptionFormView *)pWnd)->onReportRequest(pItem);
		 break;
	case CH_CNFGNON_ATHLETES_FORMVIEW:
			 ((CHNARegisterFormView *)pWnd)->onReportRequest(pItem);
			 break;
	case CH_PROGRESSION_FORMVIEW:
			 ((CHProgressionFormView *)pWnd)->onReportRequest(pItem);
			 break;
	case CH_SCHEDULE_FORMVIEW:
			 ((CHScheduleFormView *)pWnd)->onReportRequest(pItem);
			 break;
	case CH_EVENTCONTROL_FORM:
			 ((CHEventControlFormView *)pWnd)->onReportRequest(pItem);
			 break;
	case CH_MEDALLIST_FORMVIEW:
			{
				if (pItem->getIdParent()==0 && pItem->getNReport()==RC92)
				{	//si llegamos aqui es medallist
					//borramos los anteriores
					for (size_t i=RC92+1;i<(RC92+LIMIT);i++)
					{
						if (!APP::delReport(i))
						break;
					}

					if( pVMedalsByEvent ) 
						delete pVMedalsByEvent;

					int cont=RC92+1;
					pVMedalsByEvent = new VMedalsByEvent(0);
					BOOL rc=0;
					while( (rc=(*pVMedalsByEvent)++) != END_REPORT )
					{
						if( rc==0 )
						{
							GData  * pData  = pVMedalsByEvent->getData(rc);
							GEvent * pEvent = (GEvent *)pData;
							addReport(cont++,RC92,(CString)pEvent->getLDescription(),RC92,0,LPARAM(pEvent));						
						}
					}
				}
				if (pItem->getIdParent()==0 && pItem->getNReport()==RC96)
				{			
					//Eventos
					GSortedVector vEvents(CHMemoryDataBase::getColEvents(),orderEventsCLa);
					CHEvent * pEvent=0;
					int cont=RC96+1;
					for(size_t i=0 ; i<vEvents.entries() ; i++)
					{
						pEvent=(CHEvent*)vEvents[i]->getElement();
						addReport(cont++,RC96,(CString)pEvent->getLDescription(),RC96,0,LPARAM(pEvent));
												
					}
				}


				GEvent * pEventSel = (GEvent*) pItem->getLParam1();
				if (pEventSel)// Asignamos el codigo de evento como result code.
					 pItem->setResultCode(CHMemoryDataBase::getRSC((CHEvent*)pItem->getLParam1()));
				else pItem->setResultCode(CHMemoryDataBase::getRSC((GData *)0));
			}
			break;
	}
}

bool CCHManagerApp::onReportGeneration(CReportManager *pReportMngr,CReportConfig *pReportCfg,CReportItem *pItem)
{
	// Se está invocando la generación de un report.
	if( !pItem || !pReportMngr || !pReportCfg )
		return false;

	CWnd * pWnd = getCurrentDownWnd();
	if( !pWnd )
		return false;

	switch( pItem->getModule() )
	{
	case CH_INSCRIPTION_FORMVIEW:
		return ((CHInscriptionFormView *)pWnd)->onReportGeneration(pReportMngr,pReportCfg,pItem);
	case CH_CNFGNON_ATHLETES_FORMVIEW:
		 return ((CHNARegisterFormView *)pWnd)->onReportGeneration(pReportMngr,pReportCfg,pItem);
	
	case CH_PROGRESSION_FORMVIEW:
		 return ((CHProgressionFormView *)pWnd)->onReportGeneration(pReportMngr,pReportCfg,pItem);
	case CH_SCHEDULE_FORMVIEW:
		return ((CHScheduleFormView *)pWnd)->onReportGeneration(pReportMngr,pReportCfg,pItem);

	case CH_EVENTCONTROL_FORM:
		return ((CHEventControlFormView *)pWnd)->onReportGeneration(pReportMngr,pReportCfg,pItem);

	case CH_MEDALLIST_FORMVIEW:
			{
				if ( pItem->getNReport() == RC92)
				{	// Un evento
					if(!pItem->getLParam1())
					{
						::msg("Warning", "Please, select the event to print.",ICO_Q, MSG_OK);
						return false;
					}
					CHRC93 aRC93(*pReportMngr, *pReportCfg,(CHEvent*)pItem->getLParam1());
					return aRC93.Run();
				}
				else if ( pItem->getNReport() == RC93)
				{
					CHRC93 aRC93(*pReportMngr, *pReportCfg);
					return aRC93.Run();
				}
				else if ( pItem->getNReport() == RC95)
				{
					CHRC95 aRC95(*pReportMngr, *pReportCfg);
					return aRC95.Run();
				}
				else if ( pItem->getNReport() == RC96)
				{
					// Un evento
					if(!pItem->getLParam1())
					{
						::msg("Warning", "Please, select the event to print.",ICO_Q, MSG_OK);
						return false;
					}

					CHEvent *pEvent=(CHEvent*)pItem->getLParam1();
					/*if(pEvent && pEvent->getStatus()<CHMemoryDataBase::eUnofficial)
					{
						::msg("Warning", "The Status Event should be greater than Running.",ICO_Q, MSG_OK);
						return false;
					}*/
					
					CHRC96 aRC96(*pReportMngr, *pReportCfg,pEvent);
					return aRC96.Run();
					
				}
			}
			 return false;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////
// D B  F U N C T I O N S
////////////////////////////////////////////////////////////////////////////////////
/****************************************************************************************/


void CCHManagerApp::out(short idTrn)
{
	if(!outCol.entries())
		return;

	GDBObject * pDBObj=0;

	APP::out(idTrn);
	for(size_t i=0 ; i<outCol.entries() ;i++)
	{
		pDBObj=(GDBObject*)outCol[i];
		if(pDBObj->getInsertUpdate())
			APP::out(*pDBObj->getData(),OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
		else
			APP::out(*pDBObj->getData(),OP_DELETE,TO_VENUE|TO_DATABASE);
	}
	APP::out();

	outCol.clearAndDestroy();
}

void CCHManagerApp::queueOut(GData* pData,RWBoolean forInsert/*=true*/)
{
	if(pData)
	{
		GDBObject aDBObject(pData,forInsert);
		if(!outCol.find(&aDBObject))
			outCol.insert(new GDBObject(pData,forInsert));
	}
}

////////////////////////////////////////////////////////////////////////////////////
COLORREF CCHManagerApp::callForBkColor()
{
	return COLOR_AZUL4;
	//return COLOR_DEFAULT_BACK;
}

////////////////////////////////////////////////////////////////////////////////////
COLORREF CCHManagerApp::callForBkColorGrid()
{
	return GET_COLOR_DEFAULT_BACK;
	//return COLOR_DEFAULT_GRID;
}

////////////////////////////////////////////////////////////////////////////////////
COLORREF CCHManagerApp::callForBkColorButton()
{
	return COLOR_VERDE3;
	//return COLOR_DEFAULT_BUT;
}

////////////////////////////////////////////////////////////////////////////////////
COLORREF CCHManagerApp::callForBkColorEdit()
{
	return COLOR_DEFAULT_EDT;
}

////////////////////////////////////////////////////////////////////////////////////
COLORREF CCHManagerApp::callForBkColorBox()
{
	return COLOR_VERDE4;
	//return COLOR_DEFAULT_BOX;
}

////////////////////////////////////////////////////////////////////////////////////
COLORREF CCHManagerApp::callForColorOn()
{
	return COLOR_DEFAULT_ON;
}

////////////////////////////////////////////////////////////////////////////////////
COLORREF CCHManagerApp::callForColorOff()
{
	return COLOR_GRIS;
	//return COLOR_DEFAULT_OFF;
}

////////////////////////////////////////////////////////////////////////////////////
COLORREF CCHManagerApp::callForColorHiTx()
{
	return COLOR_AZUL2;
	//return COLOR_DEFAULT_HITX;
}

////////////////////////////////////////////////////////////////////////////////////
COLORREF CCHManagerApp::callForColorHigh()
{
	return COLOR_VERDE2;
	//return COLOR_DEFAULT_HIGH;
}

////////////////////////////////////////////////////////////////////////////////////
COLORREF CCHManagerApp::callForColorL3D()
{
	return COLOR_DEFAULT_L3D;
}

////////////////////////////////////////////////////////////////////////////////////
COLORREF CCHManagerApp::callForColorN3D()
{
	return COLOR_VERDE6;
	//return COLOR_DEFAULT_N3D;
}

////////////////////////////////////////////////////////////////////////////////////
COLORREF CCHManagerApp::callForColorD3D()
{
	return COLOR_DEFAULT_D3D;
}

////////////////////////////////////////////////////////////////////////////////////
COLORREF CCHManagerApp::callForColorLine()
{
	return COLOR_VERDE7;
	//return COLOR_DEFAULT_LINE;
}

////////////////////////////////////////////////////////////////////////////////////
void CCHManagerApp::callForPersonalGraphics(CGraphicWnd *w)
{
	w->addColorSet(IDCOL_BLANCO   ,COLOR_BLANCO   ,GET_COLOR_DEFAULT_OFF,GET_COLOR_DEFAULT_HITX,GET_COLOR_DEFAULT_HIGH,GET_COLOR_DEFAULT_L3D,GET_COLOR_DEFAULT_N3D,GET_COLOR_DEFAULT_D3D);
	w->addColorSet(IDCOL_NEGRO    ,COLOR_NEGRO    ,GET_COLOR_DEFAULT_OFF,GET_COLOR_DEFAULT_HITX,GET_COLOR_DEFAULT_HIGH,GET_COLOR_DEFAULT_L3D,GET_COLOR_DEFAULT_N3D,GET_COLOR_DEFAULT_D3D);
	w->addColorSet(IDCOL_NARANJA  ,COLOR_NARANJA  ,GET_COLOR_DEFAULT_OFF,GET_COLOR_DEFAULT_HITX,GET_COLOR_DEFAULT_HIGH,GET_COLOR_DEFAULT_L3D,GET_COLOR_DEFAULT_N3D,GET_COLOR_DEFAULT_D3D);
	w->addColorSet(IDCOL_AZUL     ,COLOR_AZUL     ,GET_COLOR_DEFAULT_OFF,GET_COLOR_DEFAULT_HITX,GET_COLOR_DEFAULT_HIGH,GET_COLOR_DEFAULT_L3D,GET_COLOR_DEFAULT_N3D,GET_COLOR_DEFAULT_D3D);
	w->addColorSet(IDCOL_AZUL1    ,COLOR_AZUL1    ,GET_COLOR_DEFAULT_OFF,GET_COLOR_DEFAULT_HITX,GET_COLOR_DEFAULT_HIGH,GET_COLOR_DEFAULT_L3D,GET_COLOR_DEFAULT_N3D,GET_COLOR_DEFAULT_D3D);
	w->addColorSet(IDCOL_AZUL2    ,COLOR_AZUL2    ,GET_COLOR_DEFAULT_OFF,GET_COLOR_DEFAULT_HITX,GET_COLOR_DEFAULT_HIGH,GET_COLOR_DEFAULT_L3D,GET_COLOR_DEFAULT_N3D,GET_COLOR_DEFAULT_D3D);
	w->addColorSet(IDCOL_AZUL3    ,COLOR_AZUL3    ,GET_COLOR_DEFAULT_OFF,GET_COLOR_DEFAULT_HITX,GET_COLOR_DEFAULT_HIGH,GET_COLOR_DEFAULT_L3D,GET_COLOR_DEFAULT_N3D,GET_COLOR_DEFAULT_D3D);
	w->addColorSet(IDCOL_AZUL4    ,COLOR_AZUL4    ,GET_COLOR_DEFAULT_OFF,GET_COLOR_DEFAULT_HITX,GET_COLOR_DEFAULT_HIGH,GET_COLOR_DEFAULT_L3D,GET_COLOR_DEFAULT_N3D,GET_COLOR_DEFAULT_D3D);
	w->addColorSet(IDCOL_AZUL5    ,COLOR_AZUL5	  ,GET_COLOR_DEFAULT_OFF,GET_COLOR_DEFAULT_HITX,GET_COLOR_DEFAULT_HIGH,GET_COLOR_DEFAULT_L3D,GET_COLOR_DEFAULT_N3D,GET_COLOR_DEFAULT_D3D);
	w->addColorSet(IDCOL_VERDE1   ,COLOR_VERDE1   ,GET_COLOR_DEFAULT_OFF,GET_COLOR_DEFAULT_HITX,GET_COLOR_DEFAULT_HIGH,GET_COLOR_DEFAULT_L3D,GET_COLOR_DEFAULT_N3D,GET_COLOR_DEFAULT_D3D);
	w->addColorSet(IDCOL_VERDE2   ,COLOR_VERDE2   ,GET_COLOR_DEFAULT_OFF,GET_COLOR_DEFAULT_HITX,GET_COLOR_DEFAULT_HIGH,GET_COLOR_DEFAULT_L3D,GET_COLOR_DEFAULT_N3D,GET_COLOR_DEFAULT_D3D);
	w->addColorSet(IDCOL_VERDE3   ,COLOR_VERDE3   ,GET_COLOR_DEFAULT_OFF,GET_COLOR_DEFAULT_HITX,GET_COLOR_DEFAULT_HIGH,GET_COLOR_DEFAULT_L3D,GET_COLOR_DEFAULT_N3D,GET_COLOR_DEFAULT_D3D);
	w->addColorSet(IDCOL_VERDE4   ,COLOR_VERDE4   ,GET_COLOR_DEFAULT_OFF,GET_COLOR_DEFAULT_HITX,GET_COLOR_DEFAULT_HIGH,GET_COLOR_DEFAULT_L3D,GET_COLOR_DEFAULT_N3D,GET_COLOR_DEFAULT_D3D);
	w->addColorSet(IDCOL_VERDE5   ,COLOR_VERDE5   ,GET_COLOR_DEFAULT_OFF,GET_COLOR_DEFAULT_HITX,GET_COLOR_DEFAULT_HIGH,GET_COLOR_DEFAULT_L3D,GET_COLOR_DEFAULT_N3D,GET_COLOR_DEFAULT_D3D);
	w->addColorSet(IDCOL_VERDE6   ,COLOR_VERDE6   ,GET_COLOR_DEFAULT_OFF,GET_COLOR_DEFAULT_HITX,GET_COLOR_DEFAULT_HIGH,GET_COLOR_DEFAULT_L3D,GET_COLOR_DEFAULT_N3D,GET_COLOR_DEFAULT_D3D);
	w->addColorSet(IDCOL_VERDE7   ,COLOR_VERDE7   ,GET_COLOR_DEFAULT_OFF,GET_COLOR_DEFAULT_HITX,GET_COLOR_DEFAULT_HIGH,GET_COLOR_DEFAULT_L3D,GET_COLOR_DEFAULT_N3D,GET_COLOR_DEFAULT_D3D);
	w->addColorSet(IDCOL_MARRON   ,COLOR_MARRON   ,GET_COLOR_DEFAULT_OFF,GET_COLOR_DEFAULT_HITX,GET_COLOR_DEFAULT_HIGH,GET_COLOR_DEFAULT_L3D,GET_COLOR_DEFAULT_N3D,GET_COLOR_DEFAULT_D3D);
	w->addColorSet(IDCOL_ROSA     ,COLOR_ROSA     ,GET_COLOR_DEFAULT_OFF,GET_COLOR_DEFAULT_HITX,GET_COLOR_DEFAULT_HIGH,GET_COLOR_DEFAULT_L3D,GET_COLOR_DEFAULT_N3D,GET_COLOR_DEFAULT_D3D);
	w->addColorSet(IDCOL_ROJO1    ,COLOR_ROJO1    ,GET_COLOR_DEFAULT_OFF,GET_COLOR_DEFAULT_HITX,GET_COLOR_DEFAULT_HIGH,GET_COLOR_DEFAULT_L3D,GET_COLOR_DEFAULT_N3D,GET_COLOR_DEFAULT_D3D);
	w->addColorSet(IDCOL_ROJO2    ,COLOR_ROJO2    ,GET_COLOR_DEFAULT_OFF,GET_COLOR_DEFAULT_HITX,GET_COLOR_DEFAULT_HIGH,GET_COLOR_DEFAULT_L3D,GET_COLOR_DEFAULT_N3D,GET_COLOR_DEFAULT_D3D);
	w->addColorSet(IDCOL_ROJO3    ,COLOR_ROJO3    ,GET_COLOR_DEFAULT_OFF,GET_COLOR_DEFAULT_HITX,GET_COLOR_DEFAULT_HIGH,GET_COLOR_DEFAULT_L3D,GET_COLOR_DEFAULT_N3D,GET_COLOR_DEFAULT_D3D);
	w->addColorSet(IDCOL_BLANCO   ,COLOR_BLANCO   ,GET_COLOR_DEFAULT_OFF,GET_COLOR_DEFAULT_HITX,GET_COLOR_DEFAULT_HIGH,GET_COLOR_DEFAULT_L3D,GET_COLOR_DEFAULT_N3D,GET_COLOR_DEFAULT_D3D);
	w->addColorSet(IDCOL_AMARILLO1,COLOR_AMARILLO1,GET_COLOR_DEFAULT_OFF,GET_COLOR_DEFAULT_HITX,GET_COLOR_DEFAULT_HIGH,GET_COLOR_DEFAULT_L3D,GET_COLOR_DEFAULT_N3D,GET_COLOR_DEFAULT_D3D);
	w->addColorSet(IDCOL_AMARILLO2,COLOR_AMARILLO2,GET_COLOR_DEFAULT_OFF,GET_COLOR_DEFAULT_HITX,GET_COLOR_DEFAULT_HIGH,GET_COLOR_DEFAULT_L3D,GET_COLOR_DEFAULT_N3D,GET_COLOR_DEFAULT_D3D);
	w->addColorSet(IDCOL_GRIS     ,COLOR_GRIS     ,GET_COLOR_DEFAULT_OFF,GET_COLOR_DEFAULT_HITX,GET_COLOR_DEFAULT_HIGH,GET_COLOR_DEFAULT_L3D,GET_COLOR_DEFAULT_N3D,GET_COLOR_DEFAULT_D3D);

	w->addBackgroundColor(IDBCK_VERDE   ,COLOR_VERDE4   );
	w->addBackgroundColor(IDBCK_AMARILLO,COLOR_AMARILLO2);
	w->addBackgroundColor(IDBCK_GREEN	,COLOR_VERDE1	);
	w->addBackgroundColor(IDBCK_RED		,COLOR_ROJO1	);
	w->addBackgroundColor(IDBCK_RED		,COLOR_ROJO1	);

	w->addBackgroundColor(IDBCK_WHITE	,COLOR_BLANCO	);
	w->addBackgroundColor(IDBCK_BLACK	,COLOR_NEGRO	);
	
	w->addBitmapT(BMP_WHITE			,IDB_BMP_WHITE);
	w->addBitmapT(BMP_BLACK			,IDB_BMP_BLACK);

	w->addBitmapT(BMP_WHITE_EC			,IDB_WHITE);
	w->addBitmapT(BMP_BLACK_EC			,IDB_BLACK);	
}
