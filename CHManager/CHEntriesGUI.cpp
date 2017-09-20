#include "StdAfx.h"
#include "CHManagerApp.h"
#include "CHEntriesGUI.h"
#include "CHEntriesEventGUIEx.h"
#include "CHEntriesMemberGUIEx.h"
#include "CHEntriesToolBar.h"
/*#include "CHInitialLoadGUI.h"*/

#include <OVR\GUI\GUIMANAGER\GEntriesTreeGUIEx.h>
#include <OVR\GUI\GUIMANAGER\GEntriesByNoneGUIEx.h>
#include <OVR\GUI\GUIMANAGER\GFindRegisterGUI.h>
#include <OVR\GUI\GUIMANAGER\GEntriesMemberGUIEx.h>

#include "..\CHMngtModel\CHEvent.h"
#include "..\CHMngtModel\CHRegister.h"
#include "..\CHMngtModel\CHPoolResult.h"
#include "..\CHMngtModel\CHInscription.h"
#include "..\CHMngtModel\CHMember.h"

#include "..\CHVMngtModel\CHVMngtModelDefs.h"
#include "..\CHVMngtModel\CHRC30.h"
#include "..\ChVMngtModel\CHRC32A.h"
#include "..\ChVMngtModel\CHRC32C.h"
#include "..\CHVMngtModel\CHRC38.h"

static
bool eventInscriptions(const MSLItem* p,const void *n)
{
	CHEvent* pEvent = (CHEvent *)n;
	CHInscription* pInscription = (CHInscription *)p;	

	if ( pEvent && 
		 pInscription->getEventKey() == pEvent->getKey() )
		 return true;

	return false;
}

int orderMasterTypeByCode(const MSLItem** a, const MSLItem** b)
{
	CHMasterType *pMasterTypeA = (CHMasterType *)(*a);
	CHMasterType *pMasterTypeB = (CHMasterType *)(*b);
	
	return pMasterTypeA->getMasterType() - pMasterTypeB->getMasterType();
}

static int orderInscByEventRating(const MSLItem** a, const MSLItem** b)
{
	CHInscription *pInscriptionA=(CHInscription*)(*a);
	CHInscription *pInscriptionB=(CHInscription*)(*b);

	CHEvent * pEventA=(CHEvent *)pInscriptionA->getEvent();
	CHEvent * pEventB=(CHEvent *)pInscriptionB->getEvent();

	if (pEventA->getKey()!=pEventB->getKey())
		return (pEventA->getOrder()-pEventB->getOrder());

	if (pInscriptionA->getRating()!=pInscriptionB->getRating())
	{
		if (pInscriptionA->getRating()<=0)
			return(1);

		if (pInscriptionB->getRating()<=0)
			return(-1);

		return (pInscriptionB->getRating()-pInscriptionA->getRating());
	}

	MSLWString nameA=pInscriptionA->getPrnLName();
	MSLWString nameB=pInscriptionB->getPrnLName();

	return _wcsicmp(nameA, nameB);
}
static int orderMembersByKey(const MSLItem** a, const MSLItem** b)
{
	CHMember *pMemberA=(CHMember*)(*a);
	CHMember *pMemberB=(CHMember*)(*b);
	
	return strcmp(pMemberA->getKey(),pMemberB->getKey());
	
}

static
int orderEvents(const MSLItem** a, const MSLItem** b)
{
	CHEvent *pEventA=(CHEvent *)(*a);
	CHEvent *pEventB=(CHEvent *)(*b);

	int order = strcmp(pEventA->getEvent(),pEventB->getEvent());
	if( order )
		return order;
		
	return strcmp(pEventA->getKey(),pEventB->getKey());
}

CHEntriesGUI::CHEntriesGUI(long id)
:GEntriesGUI(id)
{
}

CHEntriesGUI::~CHEntriesGUI()
{
}

MSLGUIEx * CHEntriesGUI::onNewGUIEx(long id)
{
	switch(id)
	{
		case TB_ENTRIES_ID: //Toolbar Entries
		{
			CHEntriesToolBar * pEntriesToolBar= new CHEntriesToolBar(TB_ENTRIES_ID);
			pEntriesToolBar->initToolBar(m_gui.getHWnd(0),m_hWnd,GToolBar::eTop,32);
			return pEntriesToolBar;
		}
		case GENTRIESEVENTGUIEX_ID:
		{
			CHEntriesEventGUIEx * pEventGUIEx=new CHEntriesEventGUIEx(GENTRIESEVENTGUIEX_ID);
			pEventGUIEx->init(m_gui.getHWnd(0),m_hWnd,RC(270,107,1019,224));
			return pEventGUIEx;
		}
		case GENTRIESMEMBERGUIEX_ID:
		{
			CHEntriesMemberGUIEx * pMemberGUIEx=new CHEntriesMemberGUIEx(GENTRIESMEMBERGUIEX_ID);
			pMemberGUIEx->init(m_gui.getHWnd(0),m_hWnd,RC(270,240,1019,610));
			return pMemberGUIEx;
		}
		/*case CHInitialLoadGUI_ID:
		{
			CHInitialLoadGUI dlgInitialLoadGUI( CHInitialLoadGUI_ID);
			MSLDialog(m_hWnd,dlgInitialLoadGUI,800,750,L"Initial Load",0,true,GUI_MB_NONE,GUI_RGB_WHITE,m_hWnd);
			return &dlgInitialLoadGUI;
		}*/
	}
	
	
	return GEntriesGUI::onNewGUIEx(id);
}

LRESULT CHEntriesGUI::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		//case UM_REGISTER_CREATED:	return onRegisterCreated(wParam, lParam);
	}

	return GEntriesGUI::wndProc(hWnd, message, wParam, lParam);
}

LRESULT CHEntriesGUI::onRegisterCreated(WPARAM wParam, LPARAM lParam)
{
	if(m_pTreeGUIEx)
		SendMessage(m_pTreeGUIEx->getHWnd(),UM_CREATE_REGISTER,0,(LPARAM)lParam);
	if(m_pByNoneGUIEx)
		SendMessage(m_pByNoneGUIEx->getHWnd(),UM_CREATE_REGISTER,0,(LPARAM)lParam);
	if(m_pMemberGUIEx)
		SendMessage(m_pMemberGUIEx->getHWnd(),UM_CREATE_REGISTER,0,(LPARAM)lParam);
	if(m_pFindRegisterGUI)
		SendMessage(m_pFindRegisterGUI->getHWnd(),UM_CREATE_REGISTER,0,(LPARAM)lParam);

	return 0;
	UNREFERENCED_PARAMETER(wParam);
}

bool CHEntriesGUI::onInit()
{
	bool rc = GEntriesGUI::onInit();
	onReportsAdd();
	return rc;
}


void CHEntriesGUI::onLButDblClick(long id,long x,long y)
{
	if(id==GR_REGISTER_ENTRIES)
		dblClickGridRegister(x,y);
}

bool CHEntriesGUI::onGridHand(long id,long x,long y)
{
	return true;
	UNREFERENCED_PARAMETER(id);
	UNREFERENCED_PARAMETER(x);
	UNREFERENCED_PARAMETER(y);
}

LRESULT CHEntriesGUI::onLButDownToolBar(WPARAM wParam, LPARAM lParam)
{
	if (lParam==LX_FIDE_LOAD)
	{	
		onFideInitialLoad();
		return 0;
	}
	if (lParam==LX_SEED_CALCULATION)
	{
		if (MSLMsgBox( m_gui.getHWndBase(),"this operation will remove the seeds assigned manually, continue?", GUI_ICO_WARNING, GUI_MB_YESNO, "CHManager Warning")==IDYES)
		{
			calculateTeamsRatings(0,false);
			calculateSeedsFromRating(0,false);			
		}

		return 0;
	}

	return GEntriesGUI::onLButDownToolBar(wParam, lParam);
}

void CHEntriesGUI::createGridRegister()
{
	GEntriesGUI::createGridRegister();

	m_gui.grid_addColumn(GR_REGISTER_ENTRIES,"Master Type",GUI_JUST_CENTER, 100 ,C_REG_MASTER_TYPE);

	// Combo Hand
	m_gui.doCombo(CB_MASTER_TYPE,RC(0,0,0,0));
	fillComboMasterType();
}

void CHEntriesGUI::fillComboMasterType()
{
	m_gui.combo_reset(CB_MASTER_TYPE);
	
	MSLSortedVector vMasterTypes(CHMemoryDataBase::getCol(__CHMASTERTYPE), orderMasterTypeByCode);
	for (short i=0; i<vMasterTypes.entries(); i++)
	{
		CHMasterType *pMasterType = (CHMasterType *) vMasterTypes[i];
		if (pMasterType)
			m_gui.combo_add(CB_MASTER_TYPE, pMasterType->getLDescription(), (LPARAM) pMasterType);
	}
}

bool CHEntriesGUI::paintGridRegister(gui_grid_cell* cell)
{
	if(cell->y==-1 || !cell->lParamLine)
		return false;

	m_gui.paint_solid(RGB(255,255,255));
	
	CHRegister * pRegister=(CHRegister*)cell->lParamLine;
	if (!pRegister)
		return false;
	
	switch (cell->lParamColumn)
	{
		case C_REG_MASTER_TYPE:
			m_gui.paint_text(pRegister->getMasterTypeLDescription(),GUI_USE_DEFAULT,GUI_RGB_BLACK,GUI_JUST_CENTER,cell->paint.rc);
			return false;
	}

	return GEntriesGUI::paintGridRegister(cell);
}


void CHEntriesGUI::dblClickGridRegister(long x,long y)
{
	gui_grid_cell * pCell=m_gui.grid_getCell(GR_REGISTER_ENTRIES,x,y);
	if(!pCell)
		return;

	CHRegister * pRegister = (CHRegister*)pCell->lParamLine;
	if (!pRegister)
		return;

	int col=pCell->lParamColumn;

	if (col==C_REG_MASTER_TYPE)
		editMasterType(pRegister);
}

void CHEntriesGUI::editMasterType(CHRegister *pRegister)
{
	CHMasterType* pMasterType=pRegister->getMasterType();
	m_gui.combo_selL(CB_MASTER_TYPE,(LPARAM)pMasterType);

	LPARAM lParam = m_gui.grid_showCombo(GR_REGISTER_ENTRIES, CB_MASTER_TYPE);
	if (lParam==-1)
		return;
	CHMasterType * pNewMasterType = (CHMasterType*) lParam; 
//	CHMasterType * pNewMasterType = (CHMasterType*) m_gui.grid_showCombo(GR_REGISTER_ENTRIES, CB_MASTER_TYPE);
	if(pNewMasterType!=pMasterType && pNewMasterType)
	{
		pRegister->setMasterTypeCode(pNewMasterType->getMasterType());
		redrawGridRegister();
		CHSend.toServerDB(pRegister);		
	}
}

void CHEntriesGUI::onFideInitialLoad()
{
	onNewGUIEx(CHINITIALLOADGUI_ID);
}

bool CHEntriesGUI::canDeleteInscription(GInscription * pInscription)
{
	if(!pInscription)
		return false;

	MSLSetIterator iter(CHMemoryDataBase::getCol(__GTHPOOLRESULT));

	CHPoolResult * pPoolResult=0;
	while((pPoolResult=(CHPoolResult*)iter())!=0)
	{
		if(pPoolResult->getInscription()==pInscription)
		{
			MSLMsgBox(m_hWnd, L"You can´t delete this inscription because is in a Match",GUI_ICO_STOP,GUI_MB_OK,L"Delete Inscription");
			return false;
		}
	}
	return true;
}

/** REPORTS *********************************************************************/
void CHEntriesGUI::onReportsAdd()
{
	// reports
	int nC30=1000,nC32A=2000,nC32B=3000,nC32C=4000,nC32D=5000,nC32E=6000,nC38=7000, nC45=8000;
	int nC46=9000, nC46Event=9100, nC46Phase=9200;

	APP_CH::report_add(nC30	,0,CH30_NAME  , CH30  );
	APP_CH::report_add(nC32A,0,CH32A_NAME , CH32A );
	APP_CH::report_add(nC32C,0,CH32C_NAME , CH32C );
	APP_CH::report_add(nC38	,0,CH38_NAME  , CH38 );

	/*APP_AR::report_add(++nC30,1000,AR30_EXT_NAME,AR30_EXT);
	APP_AR::report_add(nC30A,0,AR30A_NAME , AR30A );
	APP_AR::report_add(nC32B,0,AR32B_NAME , AR32B );
	APP_AR::report_add(nC32C,0,AR32C_NAME , AR32C );	
	APP_AR::report_add(nC32E,0,AR32E_NAME , AR32E );	
	APP_AR::report_add(nC45,0,AR45_NAME , AR45 );
	APP_AR::report_add(nC46,0,AR46_NAME , AR46 );
		
	GSex * pSex=0;
	MSLSetIterator it(ARMemoryDataBase::getCol(__GSEX));
	while ((pSex=(GSex *)it())!=NULL)
	{
		APP_AR::report_add(++nC32B,3000,pSex->getLDescription(),AR32B,LPARAM(pSex),0);
		APP_AR::report_add(++nC32E,6000,pSex->getLDescription(),AR32E,LPARAM(pSex),0);
	}*/


	CHEvent * pEvent=0;
	MSLSortedVector vEvents(CHMemoryDataBase::getCol(__CHEVENT),orderEvents);
	for(long i=0 ; i<vEvents.entries() ;i++)
	{
		pEvent=(CHEvent*)vEvents[i];
		APP_CH::report_add(++nC32C,4000,pEvent->getLDescription(),CH32C,LPARAM(pEvent),0);		
	}

	GGroup * pGroup = getGroup();
	MSLWString txt;
	if(pGroup)
		txt= MSLWString(pGroup->getGroup()) + L"-" + pGroup->getLDescription();
	else
		txt=L"Selected Group";

	APP_CH::report_add(++nC38,7000,txt,CH38_GROUP);	
}

void CHEntriesGUI::onReportRequest(MSLReportItem  *pReport)
{
	if(!pReport)
		return;

	switch (pReport->getNReport())
	{
		case CH30:
			pReport->setRSC( GET_RSC(0));
			pReport->setORIS("C30");
			break;
		case CH32A:
			pReport->setRSC( GET_RSC(0));
			pReport->setORIS("C32A");
			break;
		case CH32C:
			pReport->setRSC(GET_RSC((CHEvent*)pReport->getLParam1()));
			pReport->setORIS("C32C");
			break;
		case CH38:
		case CH38_GROUP:
		{
			pReport->setRSC(GET_RSC(0));
			pReport->setORIS("C38");
			break;
		}		
	}
}

bool CHEntriesGUI::onReportGeneration(CReportManager *pReportMngr,CReportConfig *pReportCfg,MSLReportItem *pReport)
{
	if (!pReportCfg || !pReport || !pReportMngr)
		return false;

	switch (pReport->getNReport())
	{
		case CH30:
		{
			CHRC30 aReport(*pReportMngr,*pReportCfg);
			return aReport.Run();
		}			
		break;
		
		case CH32A:
		{
			CHRC32A aReport(*pReportMngr, *pReportCfg);
			return aReport.Run();			
		}						
		break;
		
		case CH32C:
		{
			CHEvent * pEvent = (CHEvent *)pReport->getLParam1();
			
			if( pEvent )
			{
				CHRC32C aReport(*pReportMngr, *pReportCfg, pEvent);
				return aReport.Run();
			}		
		}
		break;
		case CH38:
		{
			CHRC38 aReport(*pReportMngr,*pReportCfg);
			return aReport.Run();
		}
		break;
		case CH38_GROUP:
		{
			GGroup * pGroup = getGroup();
			if( !pGroup )
			{
				MSLMsgBox(m_hWnd,L"To print, please select country in the interface.",GUI_ICO_INFORMATION,GUI_MB_NONE,L"Print group");
				return false;
			}

			CHRC38 aReport(*pReportMngr,*pReportCfg,pGroup->getGroup());
			return aReport.Run();
		}
		break;
		/*case AR32E:
		{
			GSex * pSex = (GSex *)pReport->getLParam1();
			if( pSex )
			{
				ARRC32E aReport(*pReportMngr, *pReportCfg, pSex);
				return aReport.Run();
			}
		}						
		break;

		
		case AR45:
		{
			ARRC45 aReport(*pReportMngr,*pReportCfg);
			return aReport.Run();
		}
		break;
		case AR45_GROUP:
		{
			GGroup * pGroup = getGroup();
			if( !pGroup )
			{
				MSLMsgBox(m_hWnd,L"To print, please select country in the interface.",GUI_ICO_INFORMATION,GUI_MB_NONE,L"Print group");
				return false;
			}

			ARRC45 aReport(*pReportMngr,*pReportCfg,pGroup->getGroup());
			return aReport.Run();
		}
		break;
		case AR46:
		{
			GData *pData = (GData *)pReport->getLParam1();
			if (!pData)
				break;
			
			if (pData->isA()==__CHPhase)
			{
				ARRC46 aReport(*pReportMngr, *pReportCfg, (CHPhase*)pData);
				return aReport.Run();
			}
			if (pData->isA()==__AREVENT)
			{
				ARRC46 aReport(*pReportMngr, *pReportCfg, (AREvent*)pData);
				return aReport.Run();
			}			
		}
		break;*/
	}
	
	return false;
}

void CHEntriesGUI::calculateTeamsRatings(GEvent *pEvent, bool reset)
{
	MSLSortedVector vEvents=MSLSortedVector(CHMemoryDataBase::getCol(__CHEVENT));
	for (short i=0;i<vEvents.entries();i++)
	{
		CHEvent * pEvent = (CHEvent * )vEvents[i];
		if (!pEvent->isTeam())
			continue;

		MSLSortedVector vInscriptions = MSLSortedVector(CHMemoryDataBase::getCol(__CHINSCRIPTION).select(eventInscriptions, pEvent));

		for (short i=0; i<vInscriptions.entries(); i++ )
		{
			CHInscription *pInscription=(CHInscription *)vInscriptions[i];			
			short rating=0;
			MSLSortedVector vMembers;
			pInscription->getMembersVector(vMembers);
			for (short j=0;j<vMembers.entries();j++)
			{
				CHMember *pMember=(CHMember *)vMembers[j];	
				rating+=pMember->getRating();
			}

			if (vMembers.entries())
			{
				GScore gRating= 0.0;

				gRating=float(float(rating)/float(vMembers.entries()));
				
				long aux = long(gRating.getScore()*10); 
				if ((aux % 10)>=5)
					gRating += 1;
	
				pInscription->setRating(gRating.getScore()); 

				CHSend.toServerDB(pInscription);	
			}	
		}
	}	
}

void CHEntriesGUI::calculateSeedsFromRating(GEvent *pEvent, bool reset)
{
	MSLSortedVector vMembers=MSLSortedVector(CHMemoryDataBase::getCol(__CHMEMBER), orderMembersByKey);
	CHMember *pMember=0;
		
	for (short i=0; i<vMembers.entries(); i++ )
	{
		pMember=(CHMember *)vMembers[i];			
		pMember->setKConst(getKConst(pMember));
		CHSend.toServerDB(pMember);			
	}
		
	MSLSortedVector vInscriptions=MSLSortedVector(CHMemoryDataBase::getCol(__CHINSCRIPTION), orderInscByEventRating);
	CHInscription *pInscription=0;
	CHEvent *pLastEvent=0;
	CHEvent *pEv=0;
	short seed=1;
	short inscSeed=0;
	for (short i=0; i<vInscriptions.entries(); i++ )
	{
		bool changeSeed=false;
		pInscription=(CHInscription *)vInscriptions[i];
		pEv=(CHEvent *)pInscription->getEvent();

		if (pEvent && pEvent->getKey()!=pEv->getKey())
			continue;

		if (!pLastEvent || pLastEvent->getKey()!=pEv->getKey())
		{
			seed=1;
			pLastEvent=pEv;
		}
		inscSeed=pInscription->getSeed();
		if (reset)
		{
			if (inscSeed!=0)
			{
				changeSeed=true;
				pInscription->setSeed(0);
			}
		}
		else if (inscSeed!=seed)
		{
			changeSeed=true;
			pInscription->setSeed(seed);
		}
		
		pInscription->setKConst(getKConst(pInscription));
		// Le pongo el rating de los miembros
		if(pEv->isTeam())
			pInscription->setRating(getTeamRating(pInscription));

		if (changeSeed)
		{
			CHSend.toServerDB(pInscription);				
			//updateRegisterTreeByEvent(pInsc->getRegister());
		}

		seed++;
	}	
}

short CHEntriesGUI::getKConst(CHInscription *pInscription)
{
	// KConst = 25, si no ha jugado 30 partidas en su vida
	// KConst = 15, si su rating es menor de 2400
	// KConst = 10, si su rating es mayor de 2400
	short kConst=25;
	if(!pInscription)
		return 0;

	if(pInscription->getRating())
	{
		if(pInscription->getRating()>2400)
			return 10;
		else 
			return 15;
	}

	return kConst;
}
short CHEntriesGUI::getKConst(CHMember *pMember)
{
	// KConst = 25, si no ha jugado 30 partidas en su vida
	// KConst = 15, si su rating es menor de 2400
	// KConst = 10, si su rating es mayor de 2400
	short kConst=25;
	if(!pMember)
		return 0;

	if(pMember->getRating())
	{
		if(pMember->getRating()>2400)
			return 10;
		else 
			return 15;
	}

	return kConst;
}
short CHEntriesGUI::getTeamRating(CHInscription *pInscription)
{
	CHMember *pMember=0;
	short teamRating=0;
	MSLSortedVector vMembers;
	pInscription->getMembersVector(vMembers);
	for(short i=0;i<vMembers.entries();i++)
	{
		pMember=(CHMember*)vMembers[i];
		teamRating+=pMember->getRating();
	}

	if(vMembers.entries())
		teamRating/=short(vMembers.entries());

	return teamRating;
}