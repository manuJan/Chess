/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHPoolResultGUIEx.cpp
*   Description : 
*
*   Author      : Javier Juste
*   Date created: 12-FEb-2009
*   Project     : AR Manager
*
*   Modification history
*   By      :
*   Date    :
*   Changes :
*
*****************************************************************************************/


#include "StdAfx.h"
#include "CHPoolResultGUIEx.h"
#include "CHPoolResultToolBar.h"
#include "CHManagerApp.h"

#include "..\CHMngtModel\CHPool.h"
#include "..\CHMngtModel\CHMatchResult.h"
#include "..\CHMngtModel\CHMatch.h"

#include <ovr\core\th\GTHPoolResult.h>
#include <ovr\core\th\GTHMatch.h>
#include <ovr\gui\guithmanager\gthprogressiondata.h>
#include <OVR\core\th\gthmsgdefines.h>

static 
int pfc_orderPoolResultsByNamePoolPosition(const void *lParam1, const void *lParam2, LPARAM null)
{
	GTHPoolResult *pA= (GTHPoolResult *) lParam1;
	GTHPoolResult *pB= (GTHPoolResult *) lParam2;

	int	order = pA->getPoolCode()-pB->getPoolCode();
	if (order)
		return order;

	if (!pA->getRegister() && !pB->getRegister())
		return strcmp(pA->getKey(),pB->getKey());

	if (!pA->getRegister())
		return -1;

	if (!pB->getRegister())
		return 1;

	order = pA->getOrder()-pB->getOrder();
	if (order)
		return order;

	return strcmp(pA->getKey(),pB->getKey());

	UNREFERENCED_PARAMETER(null);
}

CHPoolResultGUIEx::CHPoolResultGUIEx(GTHProgression* pProgression, GTHProgressionData* pProgressionData, long id)
:GTHPoolResultGUIEx(pProgression,pProgressionData,id)
{
}

CHPoolResultGUIEx::~CHPoolResultGUIEx()
{
}

MSLGUIEx * CHPoolResultGUIEx::onNewGUIEx(long id)
{
	switch(id)
	{
		case TB_POOLRESULT_ID:
		{
			RECT rect = getRect();

			CHPoolResultToolBar * pPoolResultToolBar= new CHPoolResultToolBar(TB_POOLRESULT_ID);
			pPoolResultToolBar->initToolBar(m_gui.getHWnd(0),m_hWnd,GToolBar::eTop,34,0,0,rect.right-rect.left-16);
			return pPoolResultToolBar;	
		}		
	}

	return GTHPoolResultGUIEx::onNewGUIEx(id);
}

int CHPoolResultGUIEx::onMsgBox(long id)
{
	if (id==GUIM_ID_WARNING_CREATE_PR_MATCHES)
	{
		return MSLMsgBox( m_gui.getHWndBase() ,"Do you want to create the match result for this new competitor?",GUI_ICO_WARNING, GUI_MB_YESNO, "GUITHManager Insert");
	}
	if (id==GUIM_ID_WARNING_REMOVE_PR_MATCHES)
	{
		return MSLMsgBox( m_gui.getHWndBase() ,"Do you want to remove the match result of this competitor?",GUI_ICO_WARNING, GUI_MB_YESNO, "GUITHManager Insert");
	}
	return GTHPoolResultGUIEx::onMsgBox(id);
}

bool CHPoolResultGUIEx::onCreateMatches(GTHPoolResult *pPoolResult)
{
	if (!m_pTHProgressionData)
		return false;

	if (!pPoolResult)
		return false;

	CHPool *pPool = (CHPool *) pPoolResult->getPool();
	if (!pPool)
		return false;

	short numCompByMatch=2;

	GTHMatch* pMatch = pPool->getMatch(0);
	if (!pMatch)
		return false;

	numCompByMatch=pMatch->getNumCompetitors();
	
	CHMatchResult* pMatchResult = (CHMatchResult*) m_pTHProgressionData->progCreateMatchResult(pMatch);
	if (pMatchResult)
	{
		// Atributos de la Fase
		pMatchResult->setPoolPosition(pPoolResult->getOrder());
	
		// OnCreate para crear objetos de la fase
		m_pTHProgressionData->onMatchResultCreated(pMatchResult,false);

		CHMatch* pMatch = (CHMatch*)pMatchResult->getMatch();
		if (pMatch)
		{
			pMatch->setNumCompetitors(short(pMatch->getMatchResults().entries()));
			APP::out(*pMatch);
		}
		
		APP::out(TRN_SET_MATCHRESULT);
		
		// Mando Msg UM_CREATE
		SendMessage(getHWndMsgs(), UM_DATA_CREATED,(WPARAM)GTHPOOLRESULTGUIEX_ID ,(LPARAM)pMatchResult);
		
		return true;
	}
	
	return false;
	
}

bool CHPoolResultGUIEx::onRemoveMatches(GTHPoolResult* pPoolResult)
{
	MSLSortedVector vMatchResults;
	pPoolResult->getMatchResultsVector(vMatchResults);

	if (!m_pTHProgressionData)
		return false;
	
	for (long i=0;i<vMatchResults.entries();i++)
	{
		CHMatchResult* pMatchResult = (CHMatchResult* )vMatchResults[i];
		
		CHMatchResult* pDelMatchResult = (CHMatchResult* ) m_pTHProgressionData->progRemoveMatchResult( pMatchResult );
		if (pDelMatchResult)
		{
			// Mando Msg UM_REMOVE
			SendMessage(getHWndMsgs(), UM_DATA_REMOVED,(WPARAM)GTHMATCHRESULTGUIEX_ID , (LPARAM)pDelMatchResult);
			
			CHMatch* pMatch = (CHMatch*)pDelMatchResult->getMatch();
			if (pMatch)
			{
				pMatch->setNumCompetitors(short(pMatch->getMatchResults().entries()));
				APP::out(*pMatch);
			}

			if(pDelMatchResult)
				APP::out(*pDelMatchResult,false);			
		}
	}

	APP::out(TRN_REMOVE_MATCHRESULT);
	return true;
}

void CHPoolResultGUIEx::onCreatePoolResult(GTHPoolResult*	pPoolResult)
{
	GTHPoolResultGUIEx::onCreatePoolResult(pPoolResult);

	m_gui.grid_ensureVisible(GR_POOLRESULTS,0);
}

PFN_ORDER_FC CHPoolResultGUIEx::getGridSortPoolResults () const
{
	return pfc_orderPoolResultsByNamePoolPosition;
}

bool CHPoolResultGUIEx::canChangePoolResult(GTHPoolResult* pPoolResult, int col)
{
	if (col==C_PR_RANK || col==C_PR_PH_RANK)
		return true;

	MSLSortedVector vMatchResults;
	pPoolResult->getMatchResultsVector(vMatchResults);
	for (long j=0;j<vMatchResults.entries();j++)
	{
		GTHMatchResult* pMatchResult = (GTHMatchResult*)vMatchResults[j];
		if (pMatchResult->getMatchStatus()>=GTHMemoryDataBase::eStartList)
		{
			onMsgBox(GUIM_ID_ERROR_COMPETITOR_PLAYING);
			return false;
		}
	}
	return true;
	UNREFERENCED_PARAMETER(col);
}

bool CHPoolResultGUIEx::fillComboCompetitors(GTHPoolResult* pPoolResult)
{
	bool ret = GTHPoolResultGUIEx::fillComboCompetitors(pPoolResult);

	if(pPoolResult && pPoolResult->getIsPool())
		m_gui.combo_add(CB_COMPETITORS,PROGRESSION_PRG_BYE2,1);

	return ret;
}