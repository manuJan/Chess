
/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHSummaryGUI.cpp
*   Description : 
*
*   Author      : Javier Juste
*   Date created: 2-Mar-2009
*   Project     : CH Manager
*
*   Modification history
*   By      :
*   Date    :
*   Changes :
*
*****************************************************************************************/

#include "StdAfx.h"
#include "CHSummaryGUI.h"
#include "CHManagerApp.h"
#include "..\CHMngtModel\CHEvent.h"
#include "..\CHVMngtModel\CHVMngtModelDefs.h"

/*#include "CHEventResultGUIEx.h"
#include "..\CHVMngtModel\CHRC92.h"
#include "..\CHVMngtModel\CHRC93.h"
#include "..\CHVMngtModel\CHRC95.h"
#include "..\CHVMngtModel\CHRC97.h"*/


static
int orderDataByKey(const MSLItem** a, const MSLItem** b)
{
	GData * pA = (GData *)(*a);
	GData * pB = (GData *)(*b);
	return strcmp(pA->getKey(),pB->getKey());
}

CHSummaryGUI::CHSummaryGUI(long id)
:GSummaryGUI(id)
{

}

CHSummaryGUI::~CHSummaryGUI()
{
}

MSLGUIEx * CHSummaryGUI::onNewGUIEx	(long id)
{
	switch(id)
	{
		/*case GEVENTRESULTGUIEX_ID:
		{
			CHEventResultGUIEx * pEventResGUIEx=new CHEventResultGUIEx(GEVENTRESULTGUIEX_ID,m_pEvent);
			pEventResGUIEx->init(m_gui.getHWnd(0),m_hWnd,RC(110,60,920,640));
			return pEventResGUIEx;

		}*/
	}
	return GSummaryGUI::onNewGUIEx(id);
}

bool CHSummaryGUI::onInit()
{
	bool ret = GSummaryGUI::onInit();
	
	int nC92A=1000,nC92AParent=1000;
	int nC92B=2000,nC92BParent=2000;
	int nC93=3000,nC95=4000,nC97=5000;

	//C92A
	APP::report_add(nC92A,0,CH92A_NAME,CH92A);
	APP::report_add(nC92B,0,CH92B_NAME,CH92B);

	MSLSortedVector vEvents(CHMemoryDataBase::getCol(__CHEVENT),orderDataByKey);
	CHEvent * pEvent=0;
	for (long i=0 ; i<vEvents.entries() ;i++)
	{
		pEvent=(CHEvent*)vEvents[i];
		if (pEvent->isTeam())
			APP::report_add(++nC92B,nC92BParent,pEvent->getLDescription(),CH92B,LPARAM(pEvent),0);
		else
			APP::report_add(++nC92A,nC92AParent,pEvent->getLDescription(),CH92A,LPARAM(pEvent),0);
	}
	//C93
	APP::report_add(nC93,0,CH93_NAME,CH93);

	//C95
	APP::report_add(nC95,0,CH95_NAME,CH95);
		
	return ret;
}

void CHSummaryGUI::onReportsAdd()
{
	
}

void CHSummaryGUI::onReportRequest(MSLReportItem  *pReport)
{
	if(!pReport)
		return;

	switch (pReport->getNReport())
	{
		case CH92A:
		case CH92B:
		{
			CHEvent *pEvent=(CHEvent*)pReport->getLParam1();
			
			pReport->setRSC(GET_RSC(pEvent));
			if (pReport->getNReport()==CH92A)
				pReport->setORIS("C92A");

			else if (pReport->getNReport()==CH92B)
				pReport->setORIS("C92B");
			break;
		}

		case CH93:
		{
			pReport->setRSC(GET_RSC(0));
			pReport->setORIS("C93");
			break;
		}

		case CH95:
		{
			pReport->setRSC(GET_RSC(0));
			pReport->setORIS("C95");
			break;
		}		
	}
}

bool CHSummaryGUI::onReportGeneration(CReportManager *pReportMngr, CReportConfig *pReportCfg, MSLReportItem *pReport)
{
	if (!pReportCfg || !pReport || !pReportMngr)
		return false;

	switch (pReport->getNReport())
	{
		/*case CH92A:
		case CH92B:
		{
			CHEvent *pEvent = (CHEvent *)pReport->getLParam1();
			if (pEvent)
			{
				CHRC92 aReport(*pReportMngr,*pReportCfg,pEvent);
				return aReport.Run();				
			}
			break;
		}
		case CH93:
		{
			CHRC93 aReport(*pReportMngr,*pReportCfg);
			return aReport.Run();							
		}
		case CH95:
		{
			CHRC95 aReport(*pReportMngr,*pReportCfg);
			return aReport.Run();							
		}
		case CH97:
		{
			CHRC97 aReport(*pReportMngr,*pReportCfg);
			return aReport.Run();							
		}*/
	}

	return false;
}
