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
	int nC51A=1000		, nC51AEvent=1100	, nC51AMatch=1200;
	int nC51B=2000		, nC51BEvent=2100	, nC51BMatch=2200;
	int nC51CTeam=2500	, nC51CTeamEvent=2600 , nC51CTeamMatch=2700;
	int nC51C=3000, nC51CEvent=3100;
	int nC51D=4000, nC51DEvent=4100;
	int nC65A=5000, nC65AEvent=5100, nC65ASplitPhase=5200;
	int nC65C=6000, nC65CEvent=6100, nC65CPhase=6200;
	int nC65D=7000, nC65DEvent=7100, nC65DPhase=6300;
	int nC65C_HM=8000, nC65CEvent_HM=8100, nC65CPhase_HM=8200;
	int nC65D_HM=9000, nC65DEvent_HM=9100, nC65DPhase_HM=9200;
	int nC65C_NB=10000, nC65CEvent_NB=10100, nC65CPhase_NB=10200;
	int nC65D_NB=11000, nC65DEvent_NB=11100, nC65DPhase_NB=11200;

	//nC51B=2000,nC51C=3000,nC51D=4000;

	/*APP_AR::report_add(nC51A,0, AR51A_NAME, AR51A);
	APP_AR::report_add(nC51B,0, AR51B_NAME, AR51B);
	APP_AR::report_add(nC51CTeam,0, AR51C_TEAM_NAME, AR51C_TEAM);
	APP_AR::report_add(nC51C,0, AR51C_NAME, AR51C);
	APP_AR::report_add(nC51D,0, AR51D_NAME, AR51D);
	APP_AR::report_add(nC65A,0, AR65A_NAME, AR65A);
	APP_AR::report_add(nC65C,0, AR65C_NAME, AR65C);
	APP_AR::report_add(nC65D,0, AR65D_NAME, AR65D);
	APP_AR::report_add(nC65C_NB,0, AR65C_NB_NAME, AR65C_NB);
	APP_AR::report_add(nC65D_NB,0, AR65D_NB_NAME, AR65D_NB);
	APP_AR::report_add(nC65C_HM,0, AR65C_HM_NAME, AR65C_HM);
	APP_AR::report_add(nC65D_HM,0, AR65D_HM_NAME, AR65D_HM);

	CHEvent * pEvent=0;
	MSLSortedVector vEvents(ARMemoryDataBase::getCol(__AREVENT),orderEvents);
	for(long i=0 ; i<vEvents.entries() ;i++)
	{
		pEvent=(CHEvent*)vEvents[i];
		if (!pEvent->getVisible())
			continue;

		if (!pEvent->isTeam())
		{
			APP_AR::report_add(++nC51AEvent		,nC51A,pEvent->getLDescription(),AR51A ,LPARAM(pEvent));
			APP_AR::report_add(++nC51BEvent		,nC51B,pEvent->getLDescription(),AR51B ,LPARAM(pEvent));
			APP_AR::report_add(++nC51CEvent		,nC51C,pEvent->getLDescription(),AR51C ,LPARAM(pEvent));
			APP_AR::report_add(++nC65AEvent		,nC65A,pEvent->getLDescription(),AR65A ,LPARAM(pEvent));
			APP_AR::report_add(++nC65CEvent		,nC65C,pEvent->getLDescription(),AR65C ,LPARAM(pEvent));
			APP_AR::report_add(++nC65CEvent_HM	,nC65C_HM,pEvent->getLDescription(),AR65C_HM ,LPARAM(pEvent));
			APP_AR::report_add(++nC65CEvent_NB	,nC65C_NB,pEvent->getLDescription(),AR65C_NB ,LPARAM(pEvent));
		}
		else
		{
			APP_AR::report_add(++nC51CTeamEvent ,nC51CTeam,pEvent->getLDescription(),AR51C_TEAM ,LPARAM(pEvent));
			APP_AR::report_add(++nC51DEvent ,nC51D,pEvent->getLDescription(),AR51D ,LPARAM(pEvent));
			APP_AR::report_add(++nC65DEvent ,nC65D,pEvent->getLDescription(),AR65D ,LPARAM(pEvent));
			APP_AR::report_add(++nC65DEvent_HM ,nC65D_HM,pEvent->getLDescription(),AR65D_HM ,LPARAM(pEvent));
			APP_AR::report_add(++nC65DEvent_NB ,nC65D_NB,pEvent->getLDescription(),AR65D_NB ,LPARAM(pEvent));
		}
		
		MSLSortedVector vPhases;
		pEvent->getPhasesVector(vPhases);

		for (short j=0;j<vPhases.entries();j++)
		{
			CHPhase* pPhase = (CHPhase*)vPhases[j];
			if (pPhase->getPhase()!=QUALIF_FITA		&&
				pPhase->getPhase()!=QUALIF			&&
				pPhase->getPhase()!=COURSE_1		&&
				pPhase->getPhase()!=COURSE_2		&&
				pPhase->getPhase()!=COURSE_3		&&
				pPhase->getPhase()!=ELIMINATION_1	&&
				pPhase->getPhase()!=ELIMINATION_2	)
			{
				if (!pEvent->isTeam())
				{
					APP_AR::report_add(++nC65CPhase ,nC65CEvent, pPhase->getLDescription(),AR65C ,LPARAM(pPhase));
					APP_AR::report_add(++nC65CPhase_HM ,nC65CEvent_HM, pPhase->getLDescription(),AR65C_HM ,LPARAM(pPhase));
					APP_AR::report_add(++nC65CPhase_NB ,nC65CEvent_NB, pPhase->getLDescription(),AR65C_NB ,LPARAM(pPhase));
				}
				else
				{
					APP_AR::report_add(++nC65DPhase ,nC65DEvent, pPhase->getLDescription(),AR65D ,LPARAM(pPhase));
					APP_AR::report_add(++nC65DPhase_HM ,nC65DEvent_HM, pPhase->getLDescription(),AR65D_HM ,LPARAM(pPhase));
					APP_AR::report_add(++nC65DPhase_NB ,nC65DEvent_NB, pPhase->getLDescription(),AR65D_NB ,LPARAM(pPhase));
				}
			}		
			else
			{
				MSLSortedVector vPools;
				pPhase->getPoolesVector(vPools);
				for (short k=0;k<vPools.entries();k++)
				{
					ARPool* pPool = (ARPool*)vPools[k];
					MSLSortedVector vMatches;
					pPool->getMatchesVector(vMatches);
					for (short l=0;l<vMatches.entries();l++)
					{
						CHMatch* pMatch = (CHMatch*)vMatches[l];
						if (!pEvent->isTeam())
						{
							APP_AR::report_add(++nC51AMatch ,nC51AEvent, pPhase->getLDescription(),AR51A ,LPARAM(pMatch));
							APP_AR::report_add(++nC51BMatch ,nC51BEvent, pPhase->getLDescription(),AR51B ,LPARAM(pMatch));

							MSLSortedVector vSplits;
							pPhase->getSplitPhasesVector(vSplits);
							for (short m=0;m<vSplits.entries();m++)
							{
								ARSplitPhase * pSplit = (ARSplitPhase*)vSplits[m];
								if (pSplit->getTypeSplit()==ARSplitPhase::eNormal)
									APP_AR::report_add(++nC65ASplitPhase ,nC65AEvent, pSplit->getDistanceSDescription(),AR65A ,LPARAM(pMatch),LPARAM(pSplit));
							}
						}
						else
						{
							APP_AR::report_add(++nC51CTeamMatch ,nC51CTeamEvent, pPhase->getLDescription(),AR51C_TEAM ,LPARAM(pMatch));
						}
					}
				}
			}
		}
	}*/
}

void CHProgressionGUI::onReportRequest(MSLReportItem  *pReport)
{
	if(!pReport)
		return;

	/*switch (pReport->getNReport())
	{
		case AR51A:
		case AR51B:
		case AR51C_TEAM:
		{
			GData *pData = (GData *)pReport->getLParam1();
			if (!pData)
				break;

			if (pData->isA()!=__CHMatch)
				break;

			CHMatch * pMatch = (CHMatch *)pData;
			if( pMatch )
			{
				pReport->setRSC(GET_RSC(pMatch->getPhase()));
				if (pReport->getNReport()==AR51A)
					pReport->setORIS("C51A");			
				else if (pReport->getNReport()==AR51B)
					pReport->setORIS("C51B");
				else if (pReport->getNReport()==AR51C_TEAM)
					pReport->setORIS("C51C");
			}
			break;
		}
		case AR51C:
		case AR51D:
		{
			GData *pData = (GData *)pReport->getLParam1();
			if (!pData)
				break;

			if (pData->isA()!=__AREVENT)
				break;
					
			CHEvent * pEvent = (CHEvent *)pData;
			if( pEvent )
			{
				pReport->setRSC(GET_RSC(pEvent));
				if (pReport->getNReport()==AR51C)
					pReport->setORIS("C51C");
				else if (pReport->getNReport()==AR51D)
					pReport->setORIS("C51D");
			}
			break;
		}
		case AR65A:
		{
			GData *pData1 = (GData *)pReport->getLParam1();
			if (!pData1)
				break;
			
			GData *pData2 = (GData *)pReport->getLParam2();
			if (!pData2)
				break;

			if (pData2->isA()==__ARSPLITPHASE)
			{
				ARSplitPhase * pSplitPhase = (ARSplitPhase *)pData2;
				if( pSplitPhase )
				{
					pReport->setRSC(GET_RSC(pSplitPhase));
					if (pReport->getNReport()==AR65A)
					{
						pReport->setORIS("C65A");									
						
						CHPhase* pPhase = (CHPhase* )pSplitPhase->getPhase();
						MSLWString desc = pPhase->getLDescription();
						desc += " ";
						desc += pSplitPhase->getDistanceSDescription();
						desc += " SCORECARDS";

						GDescription aDescription;
						aDescription.set("ENG");
						aDescription.set(0,desc);
						aDescription.set(1,desc);

						pReport->setDescription(aDescription);
					}
				}
			}
			break;
		}
		case AR65C:
		case AR65D:
		case AR65C_NB:
		case AR65D_NB:
		case AR65C_HM:			
		case AR65D_HM:			
		{
			GData *pData = (GData *)pReport->getLParam1();
			if (!pData)
				break;

			if (pData->isA()==__CHPhase)
			{
				CHPhase * pPhase = (CHPhase *)pData;
				if( pPhase )
				{
					pReport->setRSC(GET_RSC(pPhase));
					if (pReport->getNReport()==AR65C	|| 
						pReport->getNReport()==AR65C_HM ||
						pReport->getNReport()==AR65C_NB)
					{
						MSLWString desc = pPhase->getLDescription();
						desc += " SCORECARDS";

						GDescription aDescription;
						aDescription.set("ENG");
						aDescription.set(0,desc);
						aDescription.set(1,desc);

						pReport->setORIS("C65B");	
						pReport->setDescription(aDescription);
					}
					if (pReport->getNReport()==AR65D	||
						pReport->getNReport()==AR65D_HM ||
						pReport->getNReport()==AR65D_NB)
					{
						MSLWString desc = pPhase->getLDescription();
						desc += " SCORECARDS";

						GDescription aDescription;
						aDescription.set("ENG");
						aDescription.set(0,desc);
						aDescription.set(1,desc);

						pReport->setORIS("C65C");	
						pReport->setDescription(aDescription);
					}
				}
			}
			break;
		}
	}*/
}

bool CHProgressionGUI::onReportGeneration(CReportManager *pReportMngr, CReportConfig *pReportCfg, MSLReportItem *pReport)
{
	if (!pReportCfg || !pReport || !pReportMngr)
		return false;

	/*switch (pReport->getNReport())
	{
		case AR51A:
		case AR51B:
		case AR51C_TEAM:
		{
			GData *pData = (GData *)pReport->getLParam1();
			if (!pData)
				break;

			if (pData->isA()!=__CHMatch)
				break;
				
			CHMatch * pMatch = (CHMatch *)pData;
			if( pMatch )
			{
				if (pReport->getNReport()==AR51A)
				{
					ARRC51A aReport(*pReportMngr, *pReportCfg, pMatch);
					return aReport.Run();
				}
				else if (pReport->getNReport()==AR51B)
				{
					ARRC51B aReport(*pReportMngr, *pReportCfg, pMatch);
					return aReport.Run();
				}
				else if (pReport->getNReport()==AR51C_TEAM)
				{
					ARRC51C aReport(*pReportMngr, *pReportCfg, pMatch);
					return aReport.Run();
				}
			}
			break;
		}
		case AR51C:
		case AR51D:
		{
			GData *pData = (GData *)pReport->getLParam1();
			if (!pData)
				break;

			if (pData->isA()!= __AREVENT)
				break;
				
			CHEvent * pEvent = (CHEvent *)pData;
			if( pEvent )
			{
				if (pReport->getNReport()==AR51C)
				{
					ARRC51C_C75AB aReport(*pReportMngr, *pReportCfg, pEvent, false, ARRC51C_C75AB::eC51C_C75A, AR51C);
					return aReport.Run();
				}
				else if (pReport->getNReport()==AR51D)
				{
					ARRC51D_C75C aReport(*pReportMngr, *pReportCfg, pEvent, false, 2, AR51D);
					return aReport.Run();
				}
			}
			break;
		}		
		case AR65A:
		{
			GData *pData1 = (GData *)pReport->getLParam1();
			if (!pData1)
				break;

			if (pData1->isA()!=__CHMatch)
				break;
			
			GData *pData2 = (GData *)pReport->getLParam2();
			if (!pData2)
				break;

			if (pData2->isA()!=__ARSPLITPHASE)
				break;

			ARSplitPhase * pSplitPhase = (ARSplitPhase *)pData2;
			CHMatch * pMatch = (CHMatch *)pData1;
			if( pSplitPhase && pMatch)
			{
				ARRC65A aReport(*pReportMngr, *pReportCfg, pMatch, pSplitPhase);
				return aReport.Run();
			}			
			break;
		}
		case AR65C:
		case AR65D:
		case AR65C_NB:
		case AR65D_NB:
		case AR65C_HM:
		case AR65D_HM:
		{
			GData *pData = (GData *)pReport->getLParam1();
			if (!pData)
				break;

			if (pData->isA()==__CHPhase)
			{
				CHPhase * pPhase = (CHPhase *)pData;
				if (pReport->getNReport()==AR65C)
				{
					ARRC65C aReport(*pReportMngr, *pReportCfg, pPhase);
					return aReport.Run();
				}
				if (pReport->getNReport()==AR65C_NB)
				{
					ARRC65C aReport(*pReportMngr, *pReportCfg, pPhase,false);
					return aReport.Run();
				}
				else if (pReport->getNReport()==AR65C_HM)
				{
					ARRC65C_HM aReport(*pReportMngr, *pReportCfg, pPhase);
					return aReport.Run();
				}
				else if (pReport->getNReport()==AR65D)
				{
					ARRC65D aReport(*pReportMngr, *pReportCfg, pPhase);
					return aReport.Run();
				}
				else if (pReport->getNReport()==AR65D_NB)
				{
					ARRC65D aReport(*pReportMngr, *pReportCfg, pPhase,false);
					return aReport.Run();
				}
				else if (pReport->getNReport()==AR65D_HM)
				{
					ARRC65D_HM aReport(*pReportMngr, *pReportCfg, pPhase);
					return aReport.Run();
				}
			}
			break;
		}
	}*/
	return false;
}
