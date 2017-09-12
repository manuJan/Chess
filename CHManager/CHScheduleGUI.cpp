/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHScheduleGUI.cpp
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
#include "CHScheduleGUI.h"
#include "CHManagerApp.h"
#include "CHScheduleData.h"
#include "CHAvailableMatchGUIEx.h"
#include "CHScheduleMatchGUIEx.h"

#include "..\CHMngtModel\CHPhase.h"
#include "..\CHMngtModel\CHMatch.h"

#include "..\CHVMngtModel\CHRC08.h"
#include "..\CHVMngtModel\CHRC51.h"
#include "..\CHVMngtModel\CHRC58.h"

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
int orderSessions(const MSLItem** a,const MSLItem** b)
{
	GSession *pA= ((GSession *) (*a));
	GSession *pB= ((GSession *) (*b));

	int order = pA->getDate().value()-pB->getDate().value();
	if (order)
		return order;

	order=strcmp(pA->getTimeAsString("%H%M"),pB->getTimeAsString("%H%M") );
	if (order)
		return order;

	order = pA->getSession()-pB->getSession();
	if (order)
		return order;

	return strcmp(pA->getKey(),pB->getKey());
}

static
bool sessionMatches(const MSLItem* p,const void *n)
{
	GSession* pSession = (GSession*) n;
	CHMatch* pMatch = (CHMatch *)p;	

	if (!pSession)
		return true;

	if ( pSession->getKey() == pMatch->getSessionKey() )
		 return true;

	return false;
}

CHScheduleGUI::CHScheduleGUI(long id)
:GTHScheduleGUI(id)
{
}

CHScheduleGUI::~CHScheduleGUI()
{
}

LRESULT CHScheduleGUI::onMatchScheduled(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	GTHScheduleGUI::onMatchScheduled(wParam,lParam);

	onReportsAdd();

	return 0;
}

LRESULT CHScheduleGUI::onMatchRescheduled(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	GTHScheduleGUI::onMatchRescheduled(wParam,lParam);

	onReportsAdd();

	return 0;
}

void * CHScheduleGUI::onNewDataObject(long id)
{
	switch (id)
	{
		case GTHSCHEDULEDATA:
		{
			CHScheduleData * pScheduleData = new CHScheduleData(this);
			return pScheduleData;		
		}		
	}

	return GTHScheduleGUI::onNewDataObject(id);
}

/***** Controls *****/
MSLGUIEx * CHScheduleGUI::onNewGUIEx(long id, WPARAM wParam, LPARAM lParam)
{
	switch(id)
	{
		case GTHSCHEDULEMATCHGUIEX_ID:
		{
			CHScheduleMatchGUIEx * pTHScheduleMatchGUIEx=new CHScheduleMatchGUIEx(getScheduleData(), GTHSCHEDULEMATCHGUIEX_ID);
			pTHScheduleMatchGUIEx->init(m_gui.getHWnd(0),m_hWnd,RC(210,265,980,610));
			return pTHScheduleMatchGUIEx;			
		}
		case GTHAVAILABLEMATCHGUIEX_ID:
		{
			CHAvailableMatchGUIEx * pTHAvailableMatchGUIEx=new CHAvailableMatchGUIEx(getScheduleData(), getProgressionData(), GTHAVAILABLEMATCHGUIEX_ID);
			pTHAvailableMatchGUIEx->init(m_gui.getHWnd(0),m_hWnd,RC(210,60,695,260));
			return pTHAvailableMatchGUIEx;			
		}		
	}
	return GTHScheduleGUI::onNewGUIEx(id, wParam, lParam);
}
bool CHScheduleGUI::onInit()
{
	bool rc = GTHScheduleGUI::onInit();
	onReportsAdd();
	return rc;
}
							
void CHScheduleGUI::onReportsAdd()	
{
	int nC08=1000;
	int nC58=2000;
	int nC58_Round=3000;
	int nC51=4000, nC51Event=4100, nC51Phase=4200;
	
	APP_CH::report_reset();

	APP_CH::report_add(nC08,0, CH08_NAME, CH08);
	APP_CH::report_add(nC58,0, CH58_NAME, CH58);	
	APP_CH::report_add(nC58_Round,0, CH58_ROUND_NAME, CH58_ROUND);
	APP_CH::report_add(nC51,0, CH51_NAME, CH51);

	GTHMatch *pMatch = 0;
	bool found = false;
	MSLDate date;
	m_availableDates.clearAndDestroy();
			
	// Fill AvailableDates SortedVector
	MSLSetIterator iter(mem()->getCol(__CHMATCH));
	while( (pMatch = (GTHMatch*)iter()) != 0 ) 
	{
		found = false;
		if( pMatch->getStartDate() != INVALID_DATE )
		{
			date = pMatch->getStartDate();
			MSLDate aDate = date;
			
			for( short i=0; i < m_availableDates.entries(); i++)
			{
				MSLDate *tmp = (MSLDate *)m_availableDates[i];
				if( date.value() == tmp->value() )
				{
					found = true;
					break;
				}
			}
			if( !found )
				m_availableDates.insert(new MSLDate(aDate));			
		}
	}

	for( short j=0; j<m_availableDates.entries(); j++)
	{
		MSLDate *pDate=(MSLDate*)m_availableDates[j];
		if( pDate )
			APP_CH::report_add(++nC58,2000,pDate->asString("%a %d %b %Y").toUnicode(),CH58,LPARAM(pDate),0);
	}

	MSLSortedVector vSessions(mem()->getCol(__GSESSION),orderSessions);
	for ( long i=0;i<vSessions.entries();i++) 
	{
		GSession * pSession = (GSession * )vSessions[i];

		MSLWString desc = pSession->getDateAsString("%a %d %b %Y");
		desc += " - ";
		desc += pSession->getTimeAsString("%H:%M").toUnicode();

		APP_CH::report_add(++nC58_Round,3000,desc,CH58_ROUND,LPARAM(pSession),0);
	}

	CHEvent * pEvent=0;
	MSLSortedVector vEvents(CHMemoryDataBase::getCol(__CHEVENT),orderEvents);
	for(long i=0 ; i<vEvents.entries() ;i++)
	{
		pEvent = (CHEvent * )vEvents[i];
		APP_CH::report_add(++nC51Event		,nC51,pEvent->getLDescription(),CH51 ,LPARAM(pEvent));

		MSLSortedVector vPhases;
		pEvent->getPhasesVector(vPhases);
		for (short j=0;j<vPhases.entries();j++)
		{
			CHPhase* pPhase = (CHPhase*)vPhases[j];
			APP_CH::report_add(++nC51Phase ,nC51Event, pPhase->getLDescription(),CH51 ,LPARAM(pPhase));
		}
	}	
}

void CHScheduleGUI::onReportRequest(MSLReportItem  *pReport)
{
	if(!pReport)
		return;

	switch (pReport->getNReport())
	{
		case CH08:
		{
			pReport->setORIS("C08");
			pReport->setRSC(GET_RSC(0));
			break;
		}
		case CH58:
		{
			pReport->setORIS("C58");

			MSLDate *pDate	= (MSLDate*)pReport->getLParam1();
			if( pDate )
			{
				MSLWString params=NULLSTRING;
				params = pDate->asString("%Y%m%d").toUnicode();
				pReport->setParameters("D_"+params.toAscii());	
				pReport->setRSC(GET_RSC(0));				
			}
			break;
		}
		case CH58_ROUND:
		{
			pReport->setORIS("C58");

			GSession *pSession = (GSession*)pReport->getLParam1();
			if( pSession )
			{
				//MSLWString params=NULLSTRING;
				pReport->setParameters("D_"+MSLString(pSession->getDateAsString("%Y%m%d"))+"_S_"+TOSTRING(pSession->getAcumulated(),"0"));
				//params = pSession->getDateAsString("%Y%m%d");
				//pReport->setParameters("D_"+params.toAscii());			
				pReport->setRSC(GET_RSC(0));				
			}
			break;
		}
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
	}
}

bool CHScheduleGUI::onReportGeneration(CReportManager *pReportMngr,CReportConfig *pReportCfg,MSLReportItem *pReport)
{
	if (!pReportCfg || !pReport || !pReportMngr)
		return false;

	switch (pReport->getNReport())
	{
		case CH08:
		{
			CHRC08 aReport(*pReportMngr, *pReportCfg);
			return aReport.Run();			
		}
		case CH58:
		{
			MSLDate *pDate = (MSLDate*)pReport->getLParam1();
			if( !pDate )
			{
				MSLMsgBox( m_gui.getHWndBase() ,"Date not selected",GUI_ICO_ERROR, GUI_MB_OK, "CHManager Error");				
				return 0;
			}			

			CHRC58 aRC58(*pReportMngr,*pReportCfg,*pDate);
			return aRC58.Run();
		}		
		case CH58_ROUND:
		{
			GSession *pSession = (GSession*)pReport->getLParam1();
			if( !pSession )
			{
				MSLMsgBox( m_gui.getHWndBase() ,"Sessopm not selected",GUI_ICO_ERROR, GUI_MB_OK, "CHManager Error");				
				return 0;
			}			

			CHRC58 aRC58(*pReportMngr,*pReportCfg,pSession);
			return aRC58.Run();
		}		
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
	}
	return false;
}
