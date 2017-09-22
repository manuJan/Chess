/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:	CHPairingsGUI.cpp
*	Description	:   Dlg configuracion de un partido
*
*	Author		:	Fernando Hicar
*	Date created:   1-Abril-2009
* 	Project		:	Tennis UDP
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "StdAfx.h"
#include "CHPairingsGUI.h"
#include "CHManagerApp.h"
#include "CHManagerDefs.h"
#include <OVR/CORE/TH/GTHMsgDefines.h>
#include "CHStatusManager.h"
#include "CHProgression.h"
#include "CHPairingsToolBar.h"
#include "CHEventControlOperations.h"

#include "..\CHMngtModel\CHStatisticDefines.h"
#include "..\CHMngtModel\CHPhase.h"
#include "..\CHMngtModel\CHPool.h"
#include "..\CHMngtModel\CHPoolResult.h"
#include "..\CHMngtModel\CHMatch.h"
#include "..\CHMngtModel\CHMatchResult.h"
#include "..\CHMngtModel\CHRegister.h"
#include "..\CHMngtModel\CHMember.h"
#include "..\CHMngtModel\CHInscription.h"


#include <OVR\gui\GUIMANAGER\GFileDialog.h>

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

CHPairingsGUI::CHPairingsGUI(GTHProgression* pProgression, GTHProgressionData* pProgressionData, GTHStatusManager* pStatusManager, long id, CHPool * pPool)
:GTHMatchGUIEx(pProgression, pProgressionData, pStatusManager, id)
,m_pPool(pPool)
{
	setDataSel(pPool);

	m_selRound = getNextRound();
}

CHPairingsGUI::~CHPairingsGUI()
{	
}

CHMemoryDataBase * CHPairingsGUI::getMem() const
{
	return (CHMemoryDataBase*)GMemoryDataBase::getMem();
}

MSLGUIEx * CHPairingsGUI::onNewGUIEx(long id)
{
	switch(id)
	{
		case TB_MATCH_ID:
		{
			RECT rect = getRect();

			CHPairingsToolBar * pPairingsToolBar= new CHPairingsToolBar(TB_MATCH_ID, m_pPool, m_selRound);
			pPairingsToolBar->initToolBar(m_gui.getHWnd(0),m_hWnd,GToolBar::eTop,36,0,0,(rect.right-rect.left-16));
			return pPairingsToolBar;	
		}
	}

	return 0;
}

void CHPairingsGUI::onClick(long id,LPARAM lParam)
{
	return GTHManagerGUI::onClick(id,lParam);
}

short CHPairingsGUI::getNextRound()
{
	if (!m_pPool)
		return 0;

	short nTotalRounds = m_pPool->getNumRounds();
	short nRoundsPlayed = m_pPool->getNumRoundsPlayed();
	if (nTotalRounds == nRoundsPlayed)
		return nTotalRounds;

	return nRoundsPlayed+1;
}

bool CHPairingsGUI::canInsertMatch(GTHMatch *pMatch)
{
	return ((CHMatch*)pMatch)->getRound()==m_selRound;
}

LRESULT CHPairingsGUI::onLButDownToolBar(WPARAM wParam/*=0*/, LPARAM lParam/*=0*/)
{
	if (wParam==LX_LOAD_PAIRINGS)
	{
		loadPairings();
		return 0;
	}
	if (wParam==LX_LOAD_RESULTS)
	{
		loadResults();
		return 0;
	}
	if (wParam==CB_ROUND)
	{
		m_selRound = (int)lParam;
		onFillControl(0,0);
	}

	return GTHMatchGUIEx::onLButDownToolBar(wParam, lParam);
}
void CHPairingsGUI::loadResults()
{
	GFileDialog aFile(getHWnd(), L"csv",
				L"*.csv",
				L"Match Files (*.csv)\0*.csv\0All Files (*.*)\0*.*\0\0");

	if(aFile.DoModal(GFileDialog::eRead)==IDOK)
	{
		MSLBinary bin=aFile.read();
		MSLString line=NULLSTRING;
		MSLSet toSend;
		MSLSortedVector vMatches;

		MSLString buffer = bin.buffer();
		long pos1 = 0;
		long pos2 = buffer.index(endLine);
				
		short nLine=0;
		
		while (pos2!=-1)
		{	
			line = buffer(pos1,pos2-pos1);
			
			CHMatch *pMatch  = loadResult(toSend, nLine, line);

			pos1 = pos2+1;
			pos2 = buffer.index(endLine,pos1);			
			
			nLine++;
		}
	}
}

void CHPairingsGUI::loadPairings()
{		
	GFileDialog aFile(getHWnd(), L"csv",
				L"*.csv",
				L"Match Files (*.csv)\0*.csv\0All Files (*.*)\0*.*\0\0");

	if(aFile.DoModal(GFileDialog::eRead)==IDOK)
	{
		MSLBinary bin=aFile.read();
		MSLString line=NULLSTRING;
		MSLSet toSend;
		MSLSortedVector vMatches;

		MSLString buffer = bin.buffer();
		long pos1 = 0;
		long pos2 = buffer.index(endLine);
				
		short nLine=0;
		
		while (pos2!=-1)
		{	
			line = buffer(pos1,pos2-pos1);
			
			CHMatch *pMatch  = loadPair(toSend, nLine, line);

			pos1 = pos2+1;
			pos2 = buffer.index(endLine,pos1);			
			
			nLine++;
		}
	}
}

CHMatch* CHPairingsGUI::loadPair(MSLSet toSend, short nLine, MSLString line)
{
	long pos1 = 0;
	long pos2 = 0;
	long pos3 = 0;

	MSLString match=NULLSTRING;
	MSLString name1=NULLSTRING;
	MSLString seed1=NULLSTRING;
	MSLString seed2=NULLSTRING;
	MSLString name2=NULLSTRING;
	
	MSLString aux=NULLSTRING;
	MSLString trash=NULLSTRING;
	

	// 1; 12; WIM, Vo Thi Kim Phung; VIE; 2349; 1; ; 1 ; GM; Lei Tingjie ; CHN; 2534; 1;
	// Match
	pos2 = line.index(',',pos1);
	if (pos2!=-1)
	{
		aux = line(pos1,pos2-pos1);
		match = aux.strip(MSLString::both,'"');
		pos1=pos2+1;
	}

	// Seed 1
	pos2 = line.index(',',pos1);
	if (pos2!=-1)
	{
		aux = line(pos1,pos2-pos1);
		seed1 = aux.strip(MSLString::both,'"');
		pos1=pos2+1;
	}

	// Master
	pos2 = line.index(',',pos1);
	if (pos2!=-1)
	{
		aux = line(pos1,pos2-pos1);
		trash = aux.strip(MSLString::both,'"');
		pos1=pos2+1;
	}

	// Name 1
	pos2 = line.index(',',pos1);
	if (pos2!=-1)
	{
		aux = line(pos1,pos2-pos1);
		name1 = aux.strip(MSLString::both,'"');
		pos1=pos2+1;
	}


	// Country 1
	pos2 = line.index(',',pos1);
	if (pos2!=-1)
	{
		aux = line(pos1,pos2-pos1);
		trash = aux.strip(MSLString::both,'"');
		pos1=pos2+1;
	}
	// Rating 1
	pos2 = line.index(',',pos1);
	if (pos2!=-1)
	{
		aux = line(pos1,pos2-pos1);
		trash = aux.strip(MSLString::both,'"');
		pos1=pos2+1;
	}
	// Points 1
	pos2 = line.index(',',pos1);
	if (pos2!=-1)
	{
		aux = line(pos1,pos2-pos1);
		trash = aux.strip(MSLString::both,'"');
		pos1=pos2+1;
	}
	// Result
	pos2 = line.index(',',pos1);
	if (pos2!=-1)
	{
		aux = line(pos1,pos2-pos1);
		trash = aux.strip(MSLString::both,'"');
		pos1=pos2+1;
	}
	// Points 2
	pos2 = line.index(',',pos1);
	if (pos2!=-1)
	{
		aux = line(pos1,pos2-pos1);
		trash = aux.strip(MSLString::both,'"');
		pos1=pos2+1;
	}
	// Master
	pos2 = line.index(',',pos1);
	if (pos2!=-1)
	{
		aux = line(pos1,pos2-pos1);
		trash = aux.strip(MSLString::both,'"');
		pos1=pos2+1;
	}

	// Name 1
	pos2 = line.index(',',pos1);
	if (pos2!=-1)
	{
		aux = line(pos1,pos2-pos1);
		name2 = aux.strip(MSLString::both,'"');
		pos1=pos2+1;
	}


	// Country 1
	pos2 = line.index(',',pos1);
	if (pos2!=-1)
	{
		aux = line(pos1,pos2-pos1);
		trash = aux.strip(MSLString::both,'"');
		pos1=pos2+1;
	}
	// Rating 1
	pos2 = line.index(',',pos1);
	if (pos2!=-1)
	{
		aux = line(pos1,pos2-pos1);
		trash = aux.strip(MSLString::both,'"');
		pos1=pos2+1;
	}
	// Seed 2
	aux = line(pos1,line.length()-pos1);
	seed2 = aux.strip(MSLString::both,'"');
	
	MSLSortedVector vRoundMatches;
	m_pPool->getRoundMatchesVector(vRoundMatches,m_selRound);

	CHMatch * pMatch = (CHMatch * ) vRoundMatches[nLine];
	if (pMatch)
	{
		CHMatchResult * pWhite = pMatch->getWhite();
		CHMatchResult * pBlack = pMatch->getBlack();

		if (name1=="bye")
		{
			CHPoolResult *pPoolResult = findBye();	
			if (pPoolResult)
				m_pTHProgression->setData(pPoolResult, pWhite);			
			m_pTHProgression->setData(0, pWhite, true, true, true);
		}
		else
		{			
			CHPoolResult * pPoolResult = findPoolResultSeed(seed1);
			if (pPoolResult && pWhite)
				m_pTHProgression->setData(pPoolResult, pWhite);			
		}
		if (name2=="bye")
		{
			CHPoolResult *pPoolResult = findBye();	
			if (pPoolResult)
				m_pTHProgression->setData(pPoolResult, pBlack);			
			m_pTHProgression->setData(0, pBlack, true, true, true);
		}
		else
		{
			CHPoolResult * pPoolResult = findPoolResultSeed(seed2);
			if (pPoolResult && pBlack)			
				m_pTHProgression->setData(pPoolResult, pBlack);
		}

	}
	return 0;
}

CHMatch* CHPairingsGUI::loadResult(MSLSet toSend, short nLine, MSLString line)
{
	long pos1 = 0;
	long pos2 = 0;
	long pos3 = 0;

	MSLString match=NULLSTRING;
	MSLString name1=NULLSTRING;
	MSLString seed1=NULLSTRING;
	MSLString seed2=NULLSTRING;
	MSLString name2=NULLSTRING;
	MSLString result=NULLSTRING;
	
	MSLString aux=NULLSTRING;
	MSLString trash=NULLSTRING;
	

	// 1; 12; WIM, Vo Thi Kim Phung; VIE; 2349; 1; ; 1 ; GM; Lei Tingjie ; CHN; 2534; 1;
	// Match
	pos2 = line.index(',',pos1);
	if (pos2!=-1)
	{
		aux = line(pos1,pos2-pos1);
		match = aux.strip(MSLString::both,'"');
		pos1=pos2+1;
	}

	// Seed 1
	pos2 = line.index(',',pos1);
	if (pos2!=-1)
	{
		aux = line(pos1,pos2-pos1);
		seed1 = aux.strip(MSLString::both,'"');
		pos1=pos2+1;
	}

	// Master
	pos2 = line.index(',',pos1);
	if (pos2!=-1)
	{
		aux = line(pos1,pos2-pos1);
		trash = aux.strip(MSLString::both,'"');
		pos1=pos2+1;
	}

	// Name 1
	pos2 = line.index(',',pos1);
	if (pos2!=-1)
	{
		aux = line(pos1,pos2-pos1);
		name1 = aux.strip(MSLString::both,'"');
		pos1=pos2+1;
	}


	// Country 1
	pos2 = line.index(',',pos1);
	if (pos2!=-1)
	{
		aux = line(pos1,pos2-pos1);
		trash = aux.strip(MSLString::both,'"');
		pos1=pos2+1;
	}
	// Rating 1
	pos2 = line.index(',',pos1);
	if (pos2!=-1)
	{
		aux = line(pos1,pos2-pos1);
		trash = aux.strip(MSLString::both,'"');
		pos1=pos2+1;
	}
	// Points 1
	pos2 = line.index(',',pos1);
	if (pos2!=-1)
	{
		aux = line(pos1,pos2-pos1);
		trash = aux.strip(MSLString::both,'"');
		pos1=pos2+1;
	}
	// Result
	pos2 = line.index(',',pos1);
	if (pos2!=-1)
	{
		aux = line(pos1,pos2-pos1);
		result = aux.strip(MSLString::both,'"');
		pos1=pos2+1;
	}
	// Points 2
	pos2 = line.index(',',pos1);
	if (pos2!=-1)
	{
		aux = line(pos1,pos2-pos1);
		trash = aux.strip(MSLString::both,'"');
		pos1=pos2+1;
	}
	// Master
	pos2 = line.index(',',pos1);
	if (pos2!=-1)
	{
		aux = line(pos1,pos2-pos1);
		trash = aux.strip(MSLString::both,'"');
		pos1=pos2+1;
	}

	// Name 1
	pos2 = line.index(',',pos1);
	if (pos2!=-1)
	{
		aux = line(pos1,pos2-pos1);
		name2 = aux.strip(MSLString::both,'"');
		pos1=pos2+1;
	}


	// Country 1
	pos2 = line.index(',',pos1);
	if (pos2!=-1)
	{
		aux = line(pos1,pos2-pos1);
		trash = aux.strip(MSLString::both,'"');
		pos1=pos2+1;
	}
	// Rating 1
	pos2 = line.index(',',pos1);
	if (pos2!=-1)
	{
		aux = line(pos1,pos2-pos1);
		trash = aux.strip(MSLString::both,'"');
		pos1=pos2+1;
	}
	// Seed 2
	aux = line(pos1,line.length()-pos1);
	seed2 = aux.strip(MSLString::both,'"');
	
	CHPoolResult * pPoolResult1 = 0;
	CHPoolResult * pPoolResult2 = 0;

	if (name1=="bye")
		pPoolResult1 = findBye();		
	else
		pPoolResult1 = findPoolResultSeed(seed1);		
	if (name2=="bye")
		pPoolResult2 = findBye();		
	else
		pPoolResult2 = findPoolResultSeed(seed2);

	if (pPoolResult1 && pPoolResult2)
	{
		CHMatch * pMatch = m_pPool->findMatch(pPoolResult1,pPoolResult2);
		if (!pMatch)
			return 0;

		CHMatchResult * pWhite = pMatch->getWhite();
		CHMatchResult * pBlack = pMatch->getBlack();

		long resultCode=0;

		if (result=="1 - 0" || result =="1-0")
		{
			resultCode=EV_WHITE_WINNER;
		}
		else if (result=="0 - 1" || result =="0-1")
		{
			resultCode=EV_BLACK_WINNER;
		}
		else if (result=="½ - ½" || result =="½-½")
		{
			resultCode=EV_DRAW;
		}
		else if (result=="+ - -" || result =="+--")
		{
			resultCode=EV_WHITE_WINNER_F;
		}
		else if (result=="- - +" || result =="--+")
		{
			resultCode=EV_BLACK_WINNER_F;
		}
		else if (result=="- - -" || result =="---")
		{
			resultCode=EV_DRAW_F;
		}		
		else
		{
			resultCode=EV_EMPTY;
		}

		if (resultCode!=EV_EMPTY)
		{
			CHEventControlOperations eventControlOp(this);
			eventControlOp.setScore( resultCode, pMatch);
			eventControlOp.finishMatch(pMatch,true);
		}
		return pMatch;
	}
	return 0;
}

CHPoolResult * CHPairingsGUI::findPoolResultSeed(MSLString seed)
{
	if (!m_pPool)
		return 0;

	MSLSortedVector vPoolResults;
	m_pPool->getPoolResultsVector(vPoolResults);
	for (short i=0;i<vPoolResults.entries();i++)
	{
		CHPoolResult * pPoolResult = (CHPoolResult * )vPoolResults[i];
		if (pPoolResult->getInscriptionSeed())
		{
			MSLString insSeed = TOSTRING(pPoolResult->getInscriptionSeed());
			if (insSeed==seed)
				return pPoolResult;
		}
	}

	return 0;
}

CHPoolResult * CHPairingsGUI::findBye()
{
	if (!m_pPool)
		return 0;

	MSLSortedVector vPoolResults;
	m_pPool->getPoolResultsVector(vPoolResults);
	for (short i=0;i<vPoolResults.entries();i++)
	{
		CHPoolResult * pPoolResult = (CHPoolResult * )vPoolResults[i];
		if (pPoolResult->getBye())
			return pPoolResult;
	}
	return 0;
}