/*************************************************************************************
*			© Copyright MSL Software, S.L., 2008
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHCISPaint.cpp
*	Description	:
*
*	Author		: Javier Juste
*	Date created: 28-03-2011
* 	Project		: BKOVR2CIS
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "StdAfx.h"
#include "CHCISPaint.h"
#include "CHCISApp.h"
#include "CHCISDefs.h"
#include "CHCISProcess.h"

#include <ovr\gui\OVR2CIS\GCISScreen.h>
#include <ovr\gui\THOVR2CIS\GTHCISItemSchUnitResult.h>

#include "..\CHMngtModel\CHDefinition.h"
#include "..\CHMngtModel\CHPhase.h"
#include "..\CHMngtModel\CHPool.h"
#include "..\CHMngtModel\CHMatch.h"
#include "..\CHMngtModel\CHPoolResult.h"
#include "..\CHMngtModel\CHMatchResult.h"

CHCISPaint * CHCISPaint::chPaint = 0;

static int orderMatchResultsByRound(const MSLItem** a, const MSLItem** b)
{
	CHMatchResult * pA = (CHMatchResult*)(*a);
	CHMatchResult * pB = (CHMatchResult *)(*b);
	
	CHMatch * pMatchA=(CHMatch *)pA->getMatch();
	CHMatch * pMatchB=(CHMatch *)pB->getMatch();
	
	int order=pMatchA->getRound() - pMatchB->getRound();
	if(order)
		return order;
			
	return strcmp(pA->getKey(),pB->getKey());
}

CHCISPaint::CHCISPaint()
:GTHCISPaint()
{
	chPaint = this;
}

CHCISPaint::~CHCISPaint()
{
}

void CHCISPaint::paintRegister(long idScreen, long idLayer, long column, long line, const wchar_t * text, GRegister * pRegister, GData* pData)
{
	MSLWString txt(text);
	if( idLayer == LIST_SCHEDULE || idScreen == __CISSCREEN_LIVE_RESULTS || idLayer == LST_STARTLIST || idLayer == LST_RESULTS)
	{
		GTHMatch * pMatch = GTHPROCESS->getMatchClass(pData);
		if( pMatch && pMatch->getSubMatch() )
			txt = getSubMatchResultName(idScreen, pMatch, pRegister);
		else
		if( pMatch && !pRegister )
		{
			GTHMatchResult * pMatchResult = line%2 ? pMatch->getHome() : pMatch->getAway();
			GTHCISItemSchUnitResult * pSchUnitRes = (GTHCISItemSchUnitResult *)GTHPROCESS->findItem(pMatchResult);
			if( pMatchResult && pMatchResult->getBye() )
				txt = GTHPAINT->getRefLabel("LABEL_BYE");
			else
			if( pSchUnitRes )
				txt = CHPAINT->getRefCode(pSchUnitRes,REF_IDCOMP_LDESC);
		}
	}
	GCISPaint::paintRegister(idScreen, idLayer, column, line, txt, pRegister, pData);
}

void CHCISPaint::paintStartList(long idScreen, long idLayer, CHMatch* pMatch)
{
	if (!pMatch)
		return;

	if (pMatch->getPhaseCode()==SWISS_ROUND)
	{
		CHPool * pPool = (CHPool * ) pMatch->getPool();
		MSLSortedVector vRoundMatches;
		pPool->getRoundMatchesVector(vRoundMatches,pMatch->getRound());

		paintStartListHeader(idScreen, idLayer, pMatch);

		long lastLine=1;
		for (short i=0;i<vRoundMatches.entries();i++)
		{
			CHMatch* pMatch = (CHMatch*)vRoundMatches[i];			
			paintMatchStartList(idScreen, idLayer, lastLine, pMatch);
			lastLine++;

			if (pMatch->isTeam())
			{
				MSLSortedVector vSubMatches;
				pMatch->getSubMatchesVector(vSubMatches);
				for (short j=0;j<vSubMatches.entries();j++)
				{
					CHMatch* pSubMatch = (CHMatch*)vSubMatches[j];			
					paintSubMatchStartList(idScreen, idLayer, lastLine, pSubMatch);
					lastLine++;
				}
			}
		}

		// End Line
		CISAPP->setListEndLine(idLayer,lastLine);
	}
}

void CHCISPaint::paintStartListHeader(long idScreen, long idLayer, CHMatch* pMatch)
{
	CISAPP->setText(idLayer,COL_STL_GAME		,0, getRefLabel("STL_GAME") );
	if (pMatch->isTeam())
		CISAPP->setText(idLayer,COL_STL_SEED_WHITE	,0, getRefLabel("STL_SEED_TITLE") );
	else
		CISAPP->setText(idLayer,COL_STL_SEED_WHITE	,0, getRefLabel("STL_SEED") );

	CISAPP->setText(idLayer,COL_STL_TITLE_WHITE	,0, getRefLabel("STL_TITLE") );	
	CISAPP->setText(idLayer,COL_STL_NAME_WHITE	,0, getRefLabel("STL_NAME_WHITE") );
	CISAPP->setText(idLayer,COL_STL_NOC_WHITE	,0, getRefLabel("STL_NOC") );
	CISAPP->setText(idLayer,COL_STL_WHITE_POINTS,0, getRefLabel("STL_GAME_POINTS") );
	CISAPP->setText(idLayer,COL_STL_BLACK_POINTS,0, getRefLabel("STL_GAME_POINTS") );
	if (pMatch->isTeam())
		CISAPP->setText(idLayer,COL_STL_SEED_BLACK	,0, getRefLabel("STL_SEED_TITLE") );
	else
		CISAPP->setText(idLayer,COL_STL_SEED_BLACK	,0, getRefLabel("STL_SEED") );

	CISAPP->setText(idLayer,COL_STL_TITLE_BLACK	,0, getRefLabel("STL_TITLE") );
	CISAPP->setText(idLayer,COL_STL_NAME_BLACK	,0, getRefLabel("STL_NAME_BLACK") );
	CISAPP->setText(idLayer,COL_STL_NOC_BLACK	,0, getRefLabel("STL_NOC") );

	UNREFERENCED_PARAMETER(pMatch);
}

void CHCISPaint::paintMatchStartList(long idScreen, long idLayer, short y, CHMatch *pMatch)
{
	CHMatchResult * pWhite = pMatch->getWhite();
	CHMatchResult * pBlack = pMatch->getBlack();

	CISAPP->setText	(idLayer,COL_STL_GAME,y, getRefCode(pMatch,REF_MATCH_NUMBER));
	if (pWhite)	
	{
		// WHITE
		CISAPP->setText	(idLayer,COL_STL_SEED_WHITE,y, getRefCode(pWhite,REF_SEED));					
		if (pWhite->getRegister())
			CISAPP->setText	(idLayer,COL_STL_TITLE_WHITE,y,	getRefCode(pWhite,REF_REG,__GREGISTER,REF_TITLE_SDESC));
		CISAPP->setImage(idLayer,COL_STL_FLAG_WHITE,y, getRefCode(pWhite,REF_REG,__GREGISTER,REF_NOC_CODE).toAscii()+"%#4%",0);
		paintRegister	(idScreen,idLayer,COL_STL_NAME_WHITE,y, getRefCode(pWhite,REF_REG,__GREGISTER,REF_LDESC),pWhite->getRegister(),pWhite);
		if (pWhite->getRegister())
			CISAPP->setText (idLayer,COL_STL_NOC_WHITE,y,getRefCode(pWhite,REF_REG,__GREGISTER,REF_NOC_CODE));

		CISAPP->setText	(idLayer,COL_STL_WHITE_POINTS,y, getRefCode(pWhite,REF_PREV_PTS));
	}
		
	if (pBlack)
	{
		// BLACK
		CISAPP->setText	(idLayer,COL_STL_BLACK_POINTS,y, getRefCode(pBlack,REF_PREV_PTS));
		CISAPP->setText	(idLayer,COL_STL_SEED_BLACK,y, getRefCode(pBlack,REF_SEED));			
		if (pBlack->getRegister())
			CISAPP->setText	(idLayer,COL_STL_TITLE_BLACK,y,	getRefCode(pBlack,REF_REG,__GREGISTER,REF_TITLE_SDESC));
		CISAPP->setImage(idLayer,COL_STL_FLAG_BLACK,y,getRefCode(pBlack,REF_REG,__GREGISTER,REF_NOC_CODE).toAscii()+"%#4%",0);
		paintRegister	(idScreen,idLayer,COL_STL_NAME_BLACK,y, getRefCode(pBlack,REF_REG,__GREGISTER,REF_LDESC),pBlack->getRegister(),pBlack);
		if (pBlack->getRegister())
			CISAPP->setText (idLayer,COL_STL_NOC_BLACK,y,getRefCode(pBlack,REF_REG,__GREGISTER,REF_NOC_CODE));
	}	
}

void CHCISPaint::paintSubMatchStartList(long idScreen, long idLayer, short y, CHMatch *pMatch)
{
	CHMatchResult * pWhite = pMatch->getWhite();
	CHMatchResult * pBlack = pMatch->getBlack();

	CISAPP->setText	(idLayer,COL_STL_GAME,y, getRefCode(pMatch,REF_MATCH_NUMBER));
	if (pWhite)	
	{
		// WHITE
		if (pWhite)
		{
			GTHMatchMember * pMM = pWhite->getMatchMember(0);
			if (pMM && pMM->getRegister())
				CISAPP->setText	(idLayer,COL_STL_SEED_WHITE,y,	getRefCode(pMM,REF_REG,__GREGISTER,REF_TITLE_SDESC));
		}

		CISAPP->setImage(idLayer,COL_STL_FLAG_WHITE,y, getRefCode(pWhite,REF_REG,__GREGISTER,REF_NOC_CODE).toAscii()+"%#4%",0);
		paintRegister	(idScreen,idLayer,COL_STL_NAME_WHITE,y, getRefCode(pWhite,REF_REG,__GREGISTER,REF_LDESC),pWhite->getRegister(),pWhite);
		if (pWhite->getRegister())
			CISAPP->setText (idLayer,COL_STL_NOC_WHITE,y,getRefCode(pWhite,REF_REG,__GREGISTER,REF_NOC_CODE));
	}
		
	if (pBlack)
	{
		// BLACK
		GTHMatchMember * pMM = pBlack->getMatchMember(0);
		if (pMM && pMM->getRegister())
			CISAPP->setText	(idLayer,COL_STL_SEED_BLACK,y,	getRefCode(pMM,REF_REG,__GREGISTER,REF_TITLE_SDESC));
		
		CISAPP->setImage(idLayer,COL_STL_FLAG_BLACK,y,getRefCode(pBlack,REF_REG,__GREGISTER,REF_NOC_CODE).toAscii()+"%#4%",0);
		paintRegister	(idScreen,idLayer,COL_STL_NAME_BLACK,y, getRefCode(pBlack,REF_REG,__GREGISTER,REF_LDESC),pBlack->getRegister(),pBlack);
		if (pBlack->getRegister())
			CISAPP->setText (idLayer,COL_STL_NOC_BLACK,y,getRefCode(pBlack,REF_REG,__GREGISTER,REF_NOC_CODE));
	}	
}

void CHCISPaint::paintResults(long idScreen, long idLayer, CHMatch* pMatch)
{
	if (!pMatch)
		return;

	if (pMatch->getPhaseCode()==SWISS_ROUND)
	{
		CHPool * pPool = (CHPool * ) pMatch->getPool();
		MSLSortedVector vRoundMatches;
		pPool->getRoundMatchesVector(vRoundMatches,pMatch->getRound());

		paintResultsHeader(idScreen, idLayer, pMatch);

		long lastLine=1;
		for (short i=0;i<vRoundMatches.entries();i++)
		{
			CHMatch* pMatch = (CHMatch*)vRoundMatches[i];			
			paintMatchResults(idScreen, idLayer, lastLine, pMatch);
			lastLine++;

			if (pMatch->isTeam())
			{
				MSLSortedVector vSubMatches;
				pMatch->getSubMatchesVector(vSubMatches);
				for (short j=0;j<vSubMatches.entries();j++)
				{
					CHMatch* pSubMatch = (CHMatch*)vSubMatches[j];			
					paintSubMatchResults(idScreen, idLayer, lastLine, pSubMatch);
					lastLine++;
				}
			}
		}

		// End Line
		CISAPP->setListEndLine(idLayer,lastLine);
	}
}

void CHCISPaint::paintResultsHeader(long idScreen, long idLayer, CHMatch* pMatch)
{
	CHPhase* pPhase = (CHPhase*) pMatch->getPhase();
	if (!pPhase)
		return;

	CISAPP->setText(idLayer,COL_RES_GAME		,0, getRefLabel("RES_GAME") );
	if (pMatch->isTeam())
		CISAPP->setText(idLayer,COL_RES_SEED_WHITE	,0, getRefLabel("RES_SEED_TITLE") );
	else
		CISAPP->setText(idLayer,COL_RES_SEED_WHITE	,0, getRefLabel("RES_SEED") );

	CISAPP->setText(idLayer,COL_RES_TITLE_WHITE	,0, getRefLabel("RES_TITLE") );	
	CISAPP->setText(idLayer,COL_RES_NAME_WHITE	,0, getRefLabel("RES_NAME_WHITE") );
	CISAPP->setText(idLayer,COL_RES_NOC_WHITE	,0, getRefLabel("RES_NOC") );
	CISAPP->setText(idLayer,COL_RES_WHITE_POINTS,0, getRefLabel("RES_GAME_POINTS") );
	CISAPP->setText(idLayer,COL_RES_RESULT		,0, getRefLabel("RES_RESULT") );
	CISAPP->setText(idLayer,COL_RES_BLACK_POINTS,0, getRefLabel("RES_GAME_POINTS") );
	if (pMatch->isTeam())
		CISAPP->setText(idLayer,COL_RES_SEED_BLACK	,0, getRefLabel("RES_SEED_TITLE") );
	else
		CISAPP->setText(idLayer,COL_RES_SEED_BLACK	,0, getRefLabel("RES_SEED") );

	CISAPP->setText(idLayer,COL_RES_TITLE_BLACK	,0, getRefLabel("RES_TITLE") );
	CISAPP->setText(idLayer,COL_RES_NAME_BLACK	,0, getRefLabel("RES_NAME_BLACK") );
	CISAPP->setText(idLayer,COL_RES_NOC_BLACK	,0, getRefLabel("RES_NOC") );

	UNREFERENCED_PARAMETER(pMatch);
}

void CHCISPaint::paintMatchResults(long idScreen, long idLayer, short y, CHMatch *pMatch)
{
	CHMatchResult * pWhite = pMatch->getWhite();
	CHMatchResult * pBlack = pMatch->getBlack();

	CISAPP->setText	(idLayer,COL_RES_GAME,y, getRefCode(pMatch,REF_MATCH_NUMBER));
	if (pWhite)	
	{
		// WHITE
		CISAPP->setText	(idLayer,COL_RES_SEED_WHITE,y, getRefCode(pWhite,REF_SEED));					
		if (pWhite->getRegister())
			CISAPP->setText	(idLayer,COL_RES_TITLE_WHITE,y,	getRefCode(pWhite,REF_REG,__GREGISTER,REF_TITLE_SDESC));
		CISAPP->setImage(idLayer,COL_RES_FLAG_WHITE,y, getRefCode(pWhite,REF_REG,__GREGISTER,REF_NOC_CODE).toAscii()+"%#4%",0);
		paintRegister	(idScreen,idLayer,COL_RES_NAME_WHITE,y, getRefCode(pWhite,REF_REG,__GREGISTER,REF_LDESC),pWhite->getRegister(),pWhite);
		if (pWhite->getRegister())
			CISAPP->setText (idLayer,COL_RES_NOC_WHITE,y,getRefCode(pWhite,REF_REG,__GREGISTER,REF_NOC_CODE));

		CISAPP->setText	(idLayer,COL_RES_WHITE_POINTS,y, getRefCode(pWhite,REF_PREV_PTS));
	}

	if (pMatch->getStatus()>=CHMemoryDataBase::eUnofficial)
		CISAPP->setText	(idLayer,COL_RES_RESULT,y, getRefCode(pMatch,REF_RESULT));
		
	if (pBlack)
	{
		// BLACK
		CISAPP->setText	(idLayer,COL_RES_BLACK_POINTS,y, getRefCode(pBlack,REF_PREV_PTS));
		CISAPP->setText	(idLayer,COL_RES_SEED_BLACK,y, getRefCode(pBlack,REF_SEED));			
		if (pBlack->getRegister())
			CISAPP->setText	(idLayer,COL_RES_TITLE_BLACK,y,	getRefCode(pBlack,REF_REG,__GREGISTER,REF_TITLE_SDESC));
		CISAPP->setImage(idLayer,COL_RES_FLAG_BLACK,y,getRefCode(pBlack,REF_REG,__GREGISTER,REF_NOC_CODE).toAscii()+"%#4%",0);
		paintRegister	(idScreen,idLayer,COL_RES_NAME_BLACK,y, getRefCode(pBlack,REF_REG,__GREGISTER,REF_LDESC),pBlack->getRegister(),pBlack);
		if (pBlack->getRegister())
			CISAPP->setText (idLayer,COL_RES_NOC_BLACK,y,getRefCode(pBlack,REF_REG,__GREGISTER,REF_NOC_CODE));
	}	
}

void CHCISPaint::paintSubMatchResults(long idScreen, long idLayer, short y, CHMatch *pSubMatch)
{
	CHMatchResult * pWhite = pSubMatch->getWhite();
	CHMatchResult * pBlack = pSubMatch->getBlack();

	CISAPP->setText	(idLayer,COL_RES_GAME,y, getRefCode(pSubMatch,REF_MATCH_NUMBER));
	if (pWhite)	
	{
		// WHITE
		
		GTHMatchMember * pMM = pWhite->getMatchMember(0);
		if (pMM && pMM->getRegister())
			CISAPP->setText	(idLayer,COL_RES_SEED_WHITE,y,	getRefCode(pMM,REF_REG,__GREGISTER,REF_TITLE_SDESC));
		
		CISAPP->setImage(idLayer,COL_RES_FLAG_WHITE,y, getRefCode(pWhite,REF_REG,__GREGISTER,REF_NOC_CODE).toAscii()+"%#4%",0);
		paintRegister	(idScreen,idLayer,COL_RES_NAME_WHITE,y, getRefCode(pWhite,REF_REG,__GREGISTER,REF_LDESC),pWhite->getRegister(),pWhite);
		if (pWhite->getRegister())
			CISAPP->setText (idLayer,COL_RES_NOC_WHITE,y,getRefCode(pWhite,REF_REG,__GREGISTER,REF_NOC_CODE));
	}

	if (pSubMatch->getStatus()>=CHMemoryDataBase::eUnofficial)
		CISAPP->setText	(idLayer,COL_RES_RESULT,y, getRefCode(pSubMatch,REF_RESULT));
		
	if (pBlack)
	{
		// BLACK
		GTHMatchMember * pMM = pBlack->getMatchMember(0);
		if (pMM && pMM->getRegister())
			CISAPP->setText	(idLayer,COL_RES_SEED_BLACK,y,	getRefCode(pMM,REF_REG,__GREGISTER,REF_TITLE_SDESC));

		CISAPP->setImage(idLayer,COL_RES_FLAG_BLACK,y,getRefCode(pBlack,REF_REG,__GREGISTER,REF_NOC_CODE).toAscii()+"%#4%",0);
		paintRegister	(idScreen,idLayer,COL_RES_NAME_BLACK,y, getRefCode(pBlack,REF_REG,__GREGISTER,REF_LDESC),pBlack->getRegister(),pBlack);
		if (pBlack->getRegister())
			CISAPP->setText (idLayer,COL_RES_NOC_BLACK,y,getRefCode(pBlack,REF_REG,__GREGISTER,REF_NOC_CODE));
	}	
}

void CHCISPaint::paintPoolHeader(long idScreen, long idLayer, long y, GTHPool* pPool )
{
	if (idScreen==__CISTHSCREEN_POOLSUMMARY)
	{
		// Header Properties
		CISAPP->setBackground(idLayer,COL_CHPRS_RK		,y,BCK_LIST_HEADER);CISAPP->setTextColor(idLayer,COL_PRS_RK		,y,RGB(255,255,255));
		CISAPP->setBackground(idLayer,COL_CHPRS_FLAG		,y,-1);
		CISAPP->setBackground(idLayer,COL_CHPRS_NOC		,y,-1);
		CISAPP->setBackground(idLayer,COL_CHPRS_PLAYER	,y,-1);
		CISAPP->setBackground(idLayer,COL_CHPRS_PLAYED	,y,-1);
		CISAPP->setBackground(idLayer,COL_CHPRS_WON		,y,-1);
		CISAPP->setBackground(idLayer,COL_CHPRS_TIED	,y,-1);		
		CISAPP->setBackground(idLayer,COL_CHPRS_LOST	,y,-1);
		CISAPP->setBackground(idLayer,COL_CHPRS_MATCH_PTS	,y,-1);
		CISAPP->setBackground(idLayer,COL_CHPRS_PTS		,y,-1);
		
		CISAPP->setText(idLayer,COL_CHPRS_RK,y,getRefCode(pPool, REF_LDESC));

		// Teams header
		short numRounds = pPool->getNumRounds();
		short initCol = getIniColTeamsHeader(idScreen, idLayer, pPool);

		// Separador
		CISAPP->setBackground(idLayer,initCol,y,-1);	
		initCol++;
		
		// Equipos
		for (short i=0;i<numRounds;i++)
		{
			CISAPP->setBackground(idLayer,initCol+i,y,-1);						
		}
	}
}

void CHCISPaint::paintPoolResultHeader(long idScreen, long idLayer, long y, GTHPool* pPool )
{
	if (idScreen==__CISTHSCREEN_POOLSUMMARY)
	{
		// Table Header
		paintPoolResultTableHeader(idScreen,idLayer,y,pPool);

		// Teams Header
		paintPoolResultTeamsHeader(idScreen,idLayer,y,pPool);
	}
}

void CHCISPaint::paintPoolResultTableHeader(long idScreen, long idLayer, long y, GTHPool* pPool )
{
	if (idScreen==__CISTHSCREEN_POOLSUMMARY)
	{
		// Header Properties
		CISAPP->setBackground(idLayer,COL_CHPRS_RK		,y,BCK_LIST_HEADER);CISAPP->setTextColor(idLayer,COL_CHPRS_RK			,y,RGB(255,255,255));
		CISAPP->setBackground(idLayer,COL_CHPRS_FLAG	,y,BCK_LIST_HEADER);CISAPP->setTextColor(idLayer,COL_CHPRS_FLAG		,y,RGB(255,255,255));
		CISAPP->setBackground(idLayer,COL_CHPRS_NOC		,y,BCK_LIST_HEADER);CISAPP->setTextColor(idLayer,COL_CHPRS_NOC		,y,RGB(255,255,255));
		CISAPP->setBackground(idLayer,COL_CHPRS_PLAYER	,y,BCK_LIST_HEADER);CISAPP->setTextColor(idLayer,COL_CHPRS_PLAYER		,y,RGB(255,255,255));
		CISAPP->setBackground(idLayer,COL_CHPRS_PLAYED	,y,BCK_LIST_HEADER);CISAPP->setTextColor(idLayer,COL_CHPRS_PLAYED		,y,RGB(255,255,255));
		CISAPP->setBackground(idLayer,COL_CHPRS_WON		,y,BCK_LIST_HEADER);CISAPP->setTextColor(idLayer,COL_CHPRS_WON		,y,RGB(255,255,255));
		CISAPP->setBackground(idLayer,COL_CHPRS_TIED	,y,BCK_LIST_HEADER);CISAPP->setTextColor(idLayer,COL_CHPRS_TIED		,y,RGB(255,255,255));	
		CISAPP->setBackground(idLayer,COL_CHPRS_LOST	,y,BCK_LIST_HEADER);CISAPP->setTextColor(idLayer,COL_CHPRS_LOST		,y,RGB(255,255,255));	
		CISAPP->setBackground(idLayer,COL_CHPRS_MATCH_PTS,y,BCK_LIST_HEADER);CISAPP->setTextColor(idLayer,COL_CHPRS_MATCH_PTS	,y,RGB(255,255,255));
		CISAPP->setBackground(idLayer,COL_CHPRS_PTS		,y,BCK_LIST_HEADER);CISAPP->setTextColor(idLayer,COL_CHPRS_PTS		,y,RGB(255,255,255));
		
		// Header
		CISAPP->setText(idLayer,COL_CHPRS_RK			,y,getRefLabel("SUMMARY_RK"));
		CISAPP->setText(idLayer,COL_CHPRS_NOC			,y,getRefLabel("SUMMARY_NOC"));
		CISAPP->setText(idLayer,COL_CHPRS_PLAYER		,y,getRefLabel("SUMMARY_TEAM"));
		CISAPP->setText(idLayer,COL_CHPRS_PLAYED		,y,getRefLabel("SUMMARY_PLAYED"));
		CISAPP->setText(idLayer,COL_CHPRS_WON			,y,getRefLabel("SUMMARY_WON"));
		CISAPP->setText(idLayer,COL_CHPRS_TIED			,y,getRefLabel("SUMMARY_TIED"));
		CISAPP->setText(idLayer,COL_CHPRS_LOST			,y,getRefLabel("SUMMARY_LOST"));
		CISAPP->setText(idLayer,COL_CHPRS_MATCH_PTS		,y,getRefLabel("SUMMARY_MATCH_PTS"));		
		CISAPP->setText(idLayer,COL_CHPRS_PTS			,y,getRefLabel("SUMMARY_PTS"));		
	}

	UNREFERENCED_PARAMETER(pPool);
	UNREFERENCED_PARAMETER(idScreen);
}

void CHCISPaint::paintPoolResultTeamsHeader(long idScreen, long idLayer, long y, GTHPool* pPool )
{
	if (idScreen==__CISTHSCREEN_POOLSUMMARY)
	{
		// Teams header
		
		short numRounds = pPool->getNumRounds();
		short initCol = getIniColTeamsHeader(idScreen, idLayer, pPool);
		
		// Separador
		CISAPP->setBackground(idLayer,initCol,y,BCK_LIST_HEADER);
		initCol++;

		// Equipos
		for (short i=0;i<numRounds;i++)
		{
			CISAPP->setTextColor(idLayer,initCol+i,y,RGB(255,255,255));
			CISAPP->setBackground(idLayer,initCol+i,y,BCK_LIST_HEADER);				
			CISAPP->setText(idLayer,initCol+i,y,TOWSTRING(i+1,L""));
		}
	}
	UNREFERENCED_PARAMETER(idScreen);
}

void CHCISPaint::paintPoolResult(long idScreen, long idLayer, long y, GTHPoolResult * pPoolResult)
{
	if (pPoolResult->getBye() || !pPoolResult->getRegister())
		return;

	if (idScreen==__CISTHSCREEN_POOLSUMMARY)
	{
		// Pool Result Table
		paintPoolResultTable(idScreen, idLayer, y, pPoolResult );

		// Pool Result Matches
		paintPoolResultMatches(idScreen, idLayer, y, pPoolResult );
	}
}

void CHCISPaint::paintPoolResultTable(long idScreen, long idLayer, long y, GTHPoolResult * pPoolResult )
{
	if (!pPoolResult)
		return;

	CISAPP->setText	(idLayer,COL_CHPRS_RK		,y,getRefCode(pPoolResult,REF_RANK			));
	CISAPP->setImage(idLayer,COL_CHPRS_FLAG		,y,getRefCode(pPoolResult,REF_REG,__GREGISTER,REF_NOC_CODE).toAscii()+"%#4%",0);
	CISAPP->setText	(idLayer,COL_CHPRS_NOC		,y,getRefCode(pPoolResult,REF_REG,__GREGISTER,REF_NOC_CODE));
	paintRegister(idScreen,idLayer,COL_CHPRS_PLAYER,y,getRefCode(pPoolResult,REF_REG,__GREGISTER,REF_SDESC),pPoolResult->getRegister(),pPoolResult);
	CISAPP->setText	(idLayer,COL_CHPRS_PLAYED	,y,getRefCode(pPoolResult,REF_MATCHESPLAYED	));
	CISAPP->setText	(idLayer,COL_CHPRS_WON		,y,getRefCode(pPoolResult,REF_MATCHESWON	));
	CISAPP->setText	(idLayer,COL_CHPRS_TIED		,y,getRefCode(pPoolResult,REF_MATCHESTIES	));
	CISAPP->setText	(idLayer,COL_CHPRS_LOST		,y,getRefCode(pPoolResult,REF_MATCHESLOST	));
	CISAPP->setText	(idLayer,COL_CHPRS_MATCH_PTS,y,getRefCode(pPoolResult,REF_MATCH_POINTS	));	
	CISAPP->setText	(idLayer,COL_CHPRS_PTS		,y,getRefCode(pPoolResult,REF_POINTS_F		));	
}	

void CHCISPaint::paintPoolResultMatches(long idScreen, long idLayer, long y, GTHPoolResult * pPoolResult )
{
	if (!pPoolResult)
		return;

	GTHPool * pPool = pPoolResult->getPool();
	if (!pPool)
		return;
	
	// Partidos
	MSLSortedVector vMatchResults;
	((CHPoolResult*)pPoolResult)->getParentMatchResultsVector(vMatchResults, orderMatchResultsByRound);
	short numRounds = pPool->getNumRounds();
	short initCol = getIniColTeamsHeader(idScreen, idLayer, pPool);
		
	// Separador
	CISAPP->setBackground(idLayer,initCol,y,BCK_LIST_HEADER);	
	CISAPP->setText	(idLayer,initCol,y,L"");
	CISAPP->setText(idLayer,initCol,y,L"");
	initCol++;
	
	// Partidos
	for (short i=0;i<numRounds;i++)
	{
		CHMatchResult *pMatchResult = (CHMatchResult*) vMatchResults[i];
		if( !pMatchResult )
			continue;

		if (pMatchResult->getMatchSubCode())
			continue;
				
		CHMatch *pMatch = (CHMatch*) pMatchResult->getMatch();
		if (pMatch)
		{
			CISAPP->setText(idLayer,initCol+i,y, getRefCode(pMatchResult, REF_OPPRK_RESULT) );			
		}		
	}
}


short CHCISPaint::getIniColTeamsHeader(long idScreen, long idLayer, GTHPool* pPool)
{
	return COL_CHPRS_SEPARATOR;
	UNREFERENCED_PARAMETER(idScreen);
	UNREFERENCED_PARAMETER(idLayer);
	UNREFERENCED_PARAMETER(pPool);
}


void CHCISPaint::onLook(long idScreen, GData* pData)
{
	if (idScreen==__CISTHSCREEN_POOLSUMMARY)
	{
		CHCISAPP->setRows(LIST_SUMMARY,"35");		
		CHCISAPP->setColumns(LIST_SUMMARY, "90C|50C|50C|230L|30C|30C|30C|30C|60C|60C|15C|70C");
	}

	if (idScreen==__CISTHSCREEN_TEAM_RESULTS)		
	{
		CHMatch* pMatch=0;
		if (pData->isA()==__CHMATCH)
			pMatch = (CHMatch*)pData;		

		if (pMatch->isTeam() && pMatch->getPhaseCode()==SWISS_ROUND)
		{
			CHCISAPP->setColumns(LST_RESULTS, "40R|80R|0C|50C|230L|50C|85C|100C|85C|80R|0C|50C|230L|50C");
		}
	}

	if (idScreen==__CISTHSCREEN_STARTLIST)		
	{
		CHMatch* pMatch=0;
		if (pData->isA()==__CHMATCH)
			pMatch = (CHMatch*)pData;		

		if (pMatch->isTeam() && pMatch->getPhaseCode()==SWISS_ROUND)
		{
			CHCISAPP->setColumns(LST_STARTLIST, "40R|80R|0C|50C|230L|50C|85C|85C|80R|0C|50C|230L|50C");
		}
	}
	
	if (idScreen==__CISTHSCREEN_BRACKET)		
	{
		CHCISAPP->setWidth(LST_BRACKETS,1300);
		CHCISAPP->setHeight(LST_BRACKETS,700);
		CHCISAPP->setRows(LST_BRACKETS,"25");
	}

	GTHCISPaint::onLook(idScreen,pData);
}

void CHCISPaint::paintListButtons(GCISScreen* pScreen, GData* pData)
{
	if (!pData || !pScreen)
		return;

	CHMatch* pMatch = pData->isA()==__CHMATCH ? (CHMatch*)pData : (pData->isA()==__CHMATCHRESULT ? (CHMatch*)((CHMatchResult*)pData)->getMatch() : 0);
	
	bool isGame = true;
	
	// Generales TH Match
	if( pMatch )
	{
		GTHPhase* pPhase = (GTHPhase*)pMatch->getPhase();
		GTHEvent* pEvent = (GTHEvent*)pPhase->getEvent();

		// Generales
		pScreen->addButton(getRefLabel(__CISSCREEN_SCHEDULE_NAME), getScreenLink(__CISSCREEN_SCHEDULE, pMatch ? TOSTRING(pMatch->getStartDate().value()) : __CISSCREEN_SCHEDULE_TODAY), pScreen->isA()==__CISSCREEN_SCHEDULE);
		pScreen->addButton(getRefLabel(__CISSCREEN_MEDALS_NAME)	 , getScreenLink(__CISSCREEN_MEDALS	 , CHPROCESS->getSportCode())													  , pScreen->isA()==__CISSCREEN_MEDALS);
		pScreen->addButton(getRefLabel(__CISSCREEN_SUMMARY_NAME) , getScreenLink(__CISSCREEN_SUMMARY , pEvent ? pEvent->getKey() : NULLSTRING)										  , pScreen->isA()==__CISSCREEN_SUMMARY);

		// Generales TH
		if (isGame)
		{
			if( pPhase && pPhase->getIsPool() && CHPROCESS->onCreateScreens(__CISTHSCREEN_POOLSUMMARY))
				addButton(pScreen, __CISTHSCREEN_POOLSUMMARY	, __CISTHSCREEN_POOLSUMMARY_NAME	, NULLSTRING, pScreen->isA()==__CISTHSCREEN_POOLSUMMARY	, pPhase, pMatch);
			if( pEvent && GTHPROCESS->onCreateScreens(__CISTHSCREEN_BRACKET)	)
				addButton(pScreen, __CISTHSCREEN_BRACKET		, __CISTHSCREEN_BRACKET_NAME		, NULLSTRING, pScreen->isA()==__CISTHSCREEN_BRACKET		, pEvent, pMatch);
			pScreen->addButtonGap("127C"); // 10 botones por defecto => (127 + 3 ilx) * 10 = 1300 width
		}

		if (GTHPROCESS->onCreateScreens(__CISTHSCREEN_STARTLIST))		
			addButton(pScreen, __CISTHSCREEN_STARTLIST		, __CISTHSCREEN_STARTLIST_NAME		, NULLSTRING, pScreen->isA()==__CISTHSCREEN_STARTLIST	, pMatch);
		if (GTHPROCESS->onCreateScreens(__CISTHSCREEN_TEAM_RESULTS))
			addButton(pScreen, __CISTHSCREEN_TEAM_RESULTS	, __CISTHSCREEN_TEAM_RESULTS_NAME	, NULLSTRING, pScreen->isA()==__CISTHSCREEN_TEAM_RESULTS, pMatch);
	}
}