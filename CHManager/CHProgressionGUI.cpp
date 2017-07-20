/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHProgressionGUI.h
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
#include "CHProgressionGUI.h"
#include "CHManagerApp.h"
#include "CHProgression.h"
#include "CHProgressionData.h"
#include "CHModalityData.h"
#include "CHManagerPhaseGUI.h"
#include "CHMatchGUIEx.h"
#include "CHPoolResultGUIEx.h"
#include "CHTreeGUIEx.h"

#include "..\CHMngtModel\CHEvent.h"
#include "..\CHMngtModel\CHPhase.h"

#include "..\CHVMngtModel\CHVMngtModelDefs.h"
#include "..\CHVMngtModel\CHRC51.h"
#include "..\CHVMngtModel\CHRC74.h"
#include "..\CHVMngtModel\CHRC75.h"


static
int orderEvents(const MSLItem** a, const MSLItem** b)
{
	CHEvent * pA=(CHEvent *)(*a);
	CHEvent * pB=(CHEvent *)(*b);

	int order = pA->getOrder() - pB->getOrder();
	if (order)
		return order;

	return strcmp(pA->getKey(),pB->getKey());
}

static
bool rankingRoundPhases(const MSLItem* p,const void *n)
{
	CHPhase *pPhase = (CHPhase *)n;

	CHPhase *pMyPhase = (CHPhase *)p;	
	if( pMyPhase->getKey()==pPhase->getKey() )
		return false;

	return pMyPhase->getIsPool();
}


CHProgressionGUI::CHProgressionGUI(long id)
:GTHProgressionGUI(id)
{
}

CHProgressionGUI::~CHProgressionGUI()
{
}

void * CHProgressionGUI::onNewDataObject(long id)
{
	switch (id)
	{
		case GTHPROGRESSION:
		{
			CHProgression * pProgression = new CHProgression(this);
			return pProgression;		
		}
		case GTHPROGRESSIONDATA:
		{
			CHProgressionData * pProgressionData = new CHProgressionData(this);
			return pProgressionData;				
		}
		case GTHMODALITYDATA:
		{
			CHModalityData* pModalityData = new CHModalityData(this);
			return pModalityData;				
		}
	}

	return GTHProgressionGUI::onNewDataObject(id);
}

MSLGUIEx * CHProgressionGUI::onNewGUIEx(long id, WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	switch(id)
	{
		case GTHMANAGERPHASEGUI_ID:
		{
			MSLWString title = getManagerPhaseTitle(getManagerPhaseData(wParam));			
			CHManagerPhaseGUI dlgManagerPhase(getProgressionData(), getManagerPhaseData(wParam) ,GTHMANAGERPHASEGUI_ID);
			MSLDialog(m_hWnd,dlgManagerPhase,420,360,title,0,true,GUI_MB_OKCANCEL,GUI_RGB_WHITE,m_hWnd);
			return &dlgManagerPhase;
		}
		case GTHMATCHGUIEX_ID:
		{
			CHMatchGUIEx * pMatchGUIEx = new CHMatchGUIEx(getProgression(), getProgressionData(), getStatusManager(), GTHMATCHGUIEX_ID);
			pMatchGUIEx->init(m_gui.getHWnd(0),m_hWnd,RC(210,310,1019,609));
			return pMatchGUIEx;
		}
		case GTHPOOLRESULTGUIEX_ID:
		{
			CHPoolResultGUIEx * pTHPoolResultGUIEx=new CHPoolResultGUIEx(getProgression(), getProgressionData(), GTHPOOLRESULTGUIEX_ID);
			pTHPoolResultGUIEx->init(m_gui.getHWnd(0),m_hWnd,RC(210,60,1019,305));
			return pTHPoolResultGUIEx;			
		}		
		case GTHTREEGUIEX_ID:
		{
			CHTreeGUIEx * pTHTreeGUIEx=new CHTreeGUIEx(GTHTREEGUIEX_ID);
			pTHTreeGUIEx->init(m_gui.getHWnd(0),m_hWnd,RC(10,60,205,610));
			return pTHTreeGUIEx;			
		}
	}
	return GTHProgressionGUI::onNewGUIEx(id, wParam, lParam);
}

LRESULT CHProgressionGUI::onChangeStatus(WPARAM wParam, LPARAM lParam)
{
	return 0;
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);
}

bool CHProgressionGUI::onInit()
{
	bool rc = GTHProgressionGUI::onInit();
	onReportsAdd();
	return rc;
}

bool CHProgressionGUI::checkInitialDraw(GTHPhase* pPhase)
{
	if (pPhase->getStatus() >= GTHMemoryDataBase::eStartList)
	{
		MSLMsgBox( m_gui.getHWndBase() ,"The status of the phase is not valid",GUI_ICO_ERROR, GUI_MB_OK, "ARManager Error");					
		return false;
	}

	return true;
}

LRESULT CHProgressionGUI::onLButDownToolBar(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	LRESULT res = GTHProgressionGUI::onLButDownToolBar(wParam,lParam);

	if (wParam == LX_PHASE_DRAW)
	{
		if( MSLMsgBox( m_gui.getHWndBase() ,"do you want to assign all events?", GUI_ICO_WARNING, GUI_MB_YESNO, "Initial assigment")==IDYES)
		{
			guiInitialAssign();
		}
	}
	return res;
}

void CHProgressionGUI::guiInitialAssign()
{
	GData * pData = getManagerPhaseData(LX_PHASE_DRAW);

	if (!pData || 
		 pData->isA()!=__GTHPHASE)
		 return;

	if (!m_pTHProgression)
		return;

	MSLSet colPhases=CHMemoryDataBase::getCol(__CHPHASE).select(rankingRoundPhases,(CHPhase*)pData);
	MSLSetIterator it(colPhases);

	CHPhase* pPhase=0;
	while( (pPhase = (CHPhase *)it()) != 0 )
	{
		if (!checkInitialDraw( pPhase ) )
			continue;
	
		m_pTHProgression->doInitialDraw(pPhase, GTHProgression::TypeDraw(getTypeDraw(pPhase) ) );
	}
}

void CHProgressionGUI::onReportsAdd()
{
	int nC51=3000, nC51Event=3100 , nC51Phase=3200;
	int nC74=4000, nC74Event=4100 , nC74Phase=4200 , nC74Round=4300;
	int nC75=5000, nC75Event=5100 , nC75Phase=5200 , nC75Round=5300;
	
	APP_CH::report_add(nC51,0, CH51_NAME, CH51);
	APP_CH::report_add(nC74,0, CH74_NAME, CH74);
	APP_CH::report_add(nC75,0, CH75_NAME, CH75);

	CHEvent * pEvent=0;
	MSLSortedVector vEvents(CHMemoryDataBase::getCol(__CHEVENT),orderEvents);
	for(long i=0 ; i<vEvents.entries() ;i++)
	{
		pEvent = (CHEvent * )vEvents[i];

		APP_CH::report_add(++nC51Event		,nC51,pEvent->getLDescription(),CH51 ,LPARAM(pEvent));
		APP_CH::report_add(++nC74Event		,nC74,pEvent->getLDescription(),CH74 ,LPARAM(pEvent));
		APP_CH::report_add(++nC75Event		,nC75,pEvent->getLDescription(),CH75 ,LPARAM(pEvent));

		MSLSortedVector vPhases;
		pEvent->getPhasesVector(vPhases);
		for (short j=0;j<vPhases.entries();j++)
		{
			CHPhase* pPhase = (CHPhase*)vPhases[j];
			APP_CH::report_add(++nC51Phase ,nC51Event, pPhase->getLDescription(),CH51 ,LPARAM(pPhase));
			APP_CH::report_add(++nC74Phase ,nC74Event, pPhase->getLDescription(),CH74 ,LPARAM(pPhase));
			APP_CH::report_add(++nC75Phase ,nC75Event, pPhase->getLDescription(),CH75 ,LPARAM(pPhase));

			for(short k=0;k<pPhase->getNumRounds();k++)
			{
				MSLWString round = pPhase->getSDescription() + L" Round ";
				round += TOWSTRING(k+1);
				
				APP::report_add(++nC74Round,nC74Phase,round,CH74,LPARAM(pPhase),LPARAM(k+1));
				APP::report_add(++nC75Round,nC75Phase,round,CH75,LPARAM(pPhase),LPARAM(k+1));
			}

			APP::report_add(++nC74Round,nC74Phase,L"All rounds",CH74,LPARAM(pPhase),LPARAM(ALL_ROUNDS));
		}
	}	

	
}

void CHProgressionGUI::onReportRequest(MSLReportItem  *pReport)
{
	if(!pReport)
		return;

	switch (pReport->getNReport())
	{
		case CH51:
		{
			GData *pData = (GData *)pReport->getLParam1();
			if (!pData)
				break;

			if (pData->isA()!=__CHPHASE)
				break;

			CHPhase * pPhase = (CHPhase*)pData;
			pReport->setRSC(GET_RSC(pPhase));
			pReport->setORIS("C51");						
			break;
		}
		case CH74:
		case CH75:
		{
			GData *pData = (GData *)pReport->getLParam1();
			if (!pData)
				break;

			if (pData->isA()!=__CHPHASE)
				break;

			CHPhase * pPhase = (CHPhase*)pData;
			pReport->setRSC(GET_RSC(pPhase));
			
			short nRound = (short)pReport->getLParam2();
						
			if(	nRound && 
				nRound!=ALL_ROUNDS)
			{
				MSLString round = TOSTRING(nRound);
				pReport->setParameters("R_" + round);
			}
			break;
		}
	}
}

bool CHProgressionGUI::onReportGeneration(CReportManager *pReportMngr, CReportConfig *pReportCfg, MSLReportItem *pReport)
{
	if (!pReportCfg || !pReport || !pReportMngr)
		return false;

	switch (pReport->getNReport())
	{
		case CH51:
		{
			CHPhase *pPhase = (CHPhase*)pReport->getLParam1();
			if( !pPhase )
			{
				MSLMsgBox( m_gui.getHWndBase() ,"Phase not selected",GUI_ICO_ERROR, GUI_MB_OK, "CHManager Error");
				return false;
			}			
			
			CHRC51 aCHRC51(*pReportMngr,*pReportCfg,pPhase);			
			return aCHRC51.Run();
		}

		case CH74:
		{
			CHPhase *pPhase = (CHPhase*)pReport->getLParam1();
			if( !pPhase )
			{
				MSLMsgBox( m_gui.getHWndBase() ,"Phase not selected",GUI_ICO_ERROR, GUI_MB_OK, "CHManager Error");
				return false;
			}			

			CHRC74 aCHRC74(*pReportMngr,*pReportCfg,(CHPhase*)pReport->getLParam1(),short(pReport->getLParam2()));
			return aCHRC74.Run();
		}
		case CH75:
		{
			CHPhase *pPhase = (CHPhase*)pReport->getLParam1();
			if( !pPhase )
			{
				MSLMsgBox( m_gui.getHWndBase() ,"Phase not selected",GUI_ICO_ERROR, GUI_MB_OK, "CHManager Error");
				return false;
			}			

			CHRC75 aCHRC75(*pReportMngr,*pReportCfg,(CHPhase*)pReport->getLParam1(),short(pReport->getLParam2()));
			return aCHRC75.Run();
		}
	}
	return false;
}
