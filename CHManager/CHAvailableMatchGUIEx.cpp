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
		dataDescription+=( (CHMatch*) pMatch)->getRoundAsString(false, false).toUnicode();
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

