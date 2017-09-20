/**************************************************************************************** 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.
*
*   File name   : CHAvailableMatchGUIEx.h
*   Description : 
*
*   Author      : Javier Juste
*   Date created: 2-Feb-2010
*   Project     : AR Manager
*
*   Modification history
*   By      :
*   Date    :
*   Changes :
*
*****************************************************************************************/

#include "StdAfx.h"
#include "CHManagerApp.h"
#include "CHAvailableMatchGUIEx.h"
#include "..\CHMngtModel\CHMatch.h"
#include "..\CHMngtModel\CHMatchResult.h"
#include "..\CHMngtModel\CHInscription.h"

CHAvailableMatchGUIEx::CHAvailableMatchGUIEx(GTHScheduleData* pScheduleData, GTHProgressionData * pProgressionData, long id)
:GTHAvailableMatchGUIEx(pScheduleData, pProgressionData, id)
{
}

CHAvailableMatchGUIEx::~CHAvailableMatchGUIEx(void)
{
}

void CHAvailableMatchGUIEx::createGridAvailableMatches()
{
	RECT aRect=getRect();
	
	short hCtrl1=16;
	short hCtrl2=40;
	
	m_gui.doGrid(GR_AVAILABLE_MATCHES,RC(aRect.left,aRect.top+hCtrl1+hCtrl2,aRect.right-16,aRect.bottom),getStyGrid(GR_AVAILABLE_MATCHES),getStyGridSel(GR_AVAILABLE_MATCHES),18,getStyHeaderGrid(GR_AVAILABLE_MATCHES));
	m_gui.grid_setLineColor(GR_AVAILABLE_MATCHES,GUI_RGB_OFF,GUI_RGB_OFF);
	m_gui.grid_setSelMult(GR_AVAILABLE_MATCHES,true);
	m_gui.setDragDrop(GR_AVAILABLE_MATCHES,"Schedule");
	m_gui.setDragDropOn(GR_AVAILABLE_MATCHES,true,true);
	
	m_gui.grid_addColumn(GR_AVAILABLE_MATCHES,"",GUI_JUST_CENTER, 40	,C_AV_MATCH_CODE);
	m_gui.grid_addColumn(GR_AVAILABLE_MATCHES,"",GUI_JUST_LEFT  ,128	,C_AV_DESCRIPTION);
	m_gui.grid_addColumn(GR_AVAILABLE_MATCHES,"",GUI_JUST_LEFT  ,150    ,C_AV_HOME);
	m_gui.grid_addColumn(GR_AVAILABLE_MATCHES,"",GUI_JUST_CENTER,150	,C_AV_AWAY);		
}


bool CHAvailableMatchGUIEx::paintGridAvailableMatches(gui_grid_cell* cell)
{
	if(cell->y==-1 || !cell->lParamLine)
		return paintHeaderGrid(cell);		
	
	CHMatch * pMatch=(CHMatch*)cell->lParamLine;
	if (!pMatch)
		return false;

	paintAvailableMatchSolid(cell, pMatch);

	/*bool isSubMatch = ( ( (CHMatch*)pMatch)->isTeam() && !pMatch->getSubMatch());

	switch (cell->lParamColumn)
	{
		case C_AV_HOME:
		{
			if (isSubMatch)
			{
				return false;
			}
			break;
		}
		case C_AV_AWAY:
		{
			if (isSubMatch)
			{
				return false;
			}
			break;
		}
	}*/

	return GTHAvailableMatchGUIEx::paintGridAvailableMatches(cell);
}

MSLWString CHAvailableMatchGUIEx::getDescription(GTHMatch *pMatch)
{
	MSLWString dataDescription = NULLWSTRING;
	if (m_pDataSel && 
		m_pDataSel ->isA()==__GTHEVENT)
	{
		dataDescription+=pMatch->getPhaseSDescription();
		dataDescription+=L"-";
	}

	if (m_pDataSel && 
	   (m_pDataSel ->isA()==__GTHEVENT ||
	    m_pDataSel ->isA()==__GTHPHASE ) )
	{
		if (pMatch->getIsPool())
		{
			GTHPool* pPool = pMatch->getPool();
			dataDescription+=pPool->getPoolDescription();
			dataDescription+=L"-";
		}
	}

	if (m_pDataSel && 
	   (m_pDataSel ->isA()==__GTHEVENT ||
	    m_pDataSel ->isA()==__GTHPHASE ||
		m_pDataSel ->isA()==__GTHPOOL ||
		m_pDataSel ->isA()==__GTHMATCH ) )
	{
		dataDescription+=GUITHManagerApp::getOverallSMatchDescription();
		dataDescription+=L" ";
		dataDescription+=TOWSTRING(pMatch->getCode());
		dataDescription+=L" ";
		dataDescription+=( (CHMatch*) pMatch)->getRoundAsString(false, false);
	}

	return dataDescription;
}

MSLWString CHAvailableMatchGUIEx::getCompetitorDescription (GTHMatchResult *pMatchResult)
{
	if (!pMatchResult)
		return NULLWSTRING;

	MSLWString idCompetitor;
	if(pMatchResult->getRegister())
		idCompetitor=((CHMatchResult*)pMatchResult)->getSName();
	else
		idCompetitor=pMatchResult->getIDCompetitor(false);

	CHInscription * pInsc=(CHInscription *)pMatchResult->getInscription();
	if(pInsc && pInsc->getSeed()!=0 )
		idCompetitor+= MSLWString(L" (" + TOWSTRING(pInsc->getSeed()) + L")");

	if (pMatchResult->getBye())
		idCompetitor+=_T("(BYE)");

	return idCompetitor;
}


bool CHAvailableMatchGUIEx::canInsertAvailableMatch(GTHMatch *pMatch)
{
	if (!pMatch)
		return false;

	if ( ( (CHMatch*)pMatch)->isTeam() && pMatch->getSubMatch())
		return false;

	if ( pMatch->getStatus()==GTHMemoryDataBase::eAvailable && ( (CHMatch*)pMatch)->hasByes())
		return true;

	return GTHAvailableMatchGUIEx::canInsertAvailableMatch(pMatch);
}

