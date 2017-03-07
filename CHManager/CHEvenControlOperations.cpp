/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHEvenControlOperations.cpp
*	Description	:
*
*	Author		:Chess Team
*	Date created:21/12/2005
* 	Project		:Chess Management
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdafx.h"
#include "CHmanager.h"
#include "CHEvenControlOperations.h"
#include "CHProgression.h"
#include "CHStatusManager.h"
#include "CHEventControlMoveManager.h"
#include "CHRanking.h"
#include "CHDefines.h"
#include "CHMsgDefines.h"
#include "CHReadFile.h"
#include <Sports\CH\Data\CHStatisticDefines.h>
#include <Sports\CH\Data\CHDiscipline.h>
#include <Sports\CH\Reports\CHPgnMatch.h>

#include <Core\TH\GTHHistoric.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CCHManagerApp theApp;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHEvenControlOperations::CHEvenControlOperations(CHMemoryDataBase * pMem)
{
	pMemory			= pMem;
	
}

CHEvenControlOperations::~CHEvenControlOperations()
{
}

void CHEvenControlOperations::calculatePointMatchResult(CHMatch *pMatch)
{
	if(!pMatch)
		return;

	CHSplitMatch *pSplitMatch=0;

	float sets1=0; 
	float sets2=0; 
	
	CHMatchResult *pMatchResult1=pMatch->getMatchResultHome();
	CHMatchResult *pMatchResult2=pMatch->getMatchResultAway();
 
	if(pMatchResult1->getQualitativeCode()!=OK && 
	   pMatchResult2->getQualitativeCode()!=OK)
	{
		pMatchResult1->setPoints(0);
		pMatchResult2->setPoints(0);
	}
	else if(pMatchResult1->getQualitativeCode()!=OK)
		// Le pongo un punto 
	{	
		pMatchResult2->setPoints(1);
		pMatchResult1->setPoints(0);
	}
	else if(pMatchResult2->getQualitativeCode()!=OK)
	{	// Le pongo un punto 
		pMatchResult1->setPoints(1);
		pMatchResult2->setPoints(0);
	}
	/*else 
	{
		pMatchResult1->setPoints(0);
		pMatchResult2->setPoints(0);
		
	}*/
	
	theApp.queueOut(pMatchResult1);
	theApp.queueOut(pMatchResult2);
	
	theApp.out(TRN_CHANGE_MATCHRES);
	
}

void CHEvenControlOperations::paintShadow(CDC *pdc,int x,int y,const char *txt,COLORREF col,short align, int font,CGraphicWnd *w,int colorText)
{
	if ((!pdc) || (!txt)) return;


	// Alineacion
	if(align==1)
		 pdc->SetTextAlign(TA_CENTER);
	else if(align==2)
		 pdc->SetTextAlign(TA_RIGHT);
	else pdc->SetTextAlign(TA_LEFT);
	// Font
	pdc->SelectObject(w->getFont(font));
	
	if(colorText)
	{
		pdc->SetTextColor(colorText);
		pdc->TextOut(x,y,txt);
	}
	else 
	{
		pdc->SetTextColor(RGB(216,216,216));
		pdc->TextOut(x+2,y+2,txt);
		pdc->SetTextColor(col);
		pdc->TextOut(x,y,txt);
	}
	
}

void CHEvenControlOperations::putScore(short idEvent,CHMatch *pMatch)
{
	
	float score1=0.0, score2=0.0;
	short forfeit=0;
	//RWBoolean next=false;

	switch(idEvent)
	{
		case EV_WHITE_WINNER:
			score1=1;
			score2=0;
			break;
		case EV_DRAW:
			score1=0.5;
			score2=0.5;
			break;
		case EV_BLACK_WINNER:
			score1=0;
			score2=1;
			break;		
		case EV_WHITE_WINNER_F:
			score1=1;
			score2=0;
			forfeit=2;
			break;
		case EV_BLACK_WINNER_F:
			score1=0;
			score2=1;
			forfeit=1;
			break;
		case EV_DRAW_F:
			score1=0;
			score2=0;
			forfeit=3;
			break;
		default:
		{
			score1=0;
			score2=0;
			break;
		}
		/*case BU_NEXT:
			empty=true;
			break;*/
	}

	
	
	CHMatchResult *pWhite =pMatch->getWhite();
	CHMatchResult *pBlack =pMatch->getBlack();
	
	pWhite->setPoints(score1);
	pBlack->setPoints(score2);
	
	CHPoolResult *pPoolResult1=(CHPoolResult*)pWhite->getPoolResult();
	CHPoolResult *pPoolResult2=(CHPoolResult*)pBlack->getPoolResult();

	if(forfeit)
	{
	
		if(forfeit==1 || forfeit==3)
		{
			pWhite->setQualitative(FO);
			if(forfeit==1)
			{
				pBlack->setQualitative(OK);
				if(pPoolResult2)
					pBlack->setQualitative(OK);
			}
			
		}

		if(forfeit==2 || forfeit==3)
		{
			pBlack->setQualitative(FO);
			if(forfeit==2)
			{
				pWhite->setQualitative(OK);
				if(pPoolResult1)
					pWhite->setQualitative(OK);
			}
		}
		
		if (::msg("Attention","Do you want to put incidence in the pool?",
			   ICO_Q,MSG_YESNO)==RET_YES)	
		{
			if((pPoolResult1) && (forfeit==1 || forfeit==3))
			{
				pPoolResult1->setQualitative(FO);
			}
				
			
			if((pPoolResult2) && (forfeit==2 || forfeit==3))
				pPoolResult2->setQualitative(FO);
						
			
		}
	}
	else
	{
		pWhite->setQualitative(OK);
		pBlack->setQualitative(OK);
		
		if(pPoolResult1)
			pPoolResult1->setQualitative(OK);
		if(pPoolResult2)
			pPoolResult2->setQualitative(OK);
		


	}

	if (idEvent!=EV_EMPTY)
	{
		//Es un subpartido y tengo que acumular las puntuaciones
		CHMatch *pParentMatch=pMatch->getParentMatch();
		if(pMatch->getMatchType()==CHMatch::eTeamIndividual && pParentMatch)
		{
			CHMatchResult *pParentMatchResult1 =(CHMatchResult*)pParentMatch->getWhite();
			CHMatchResult *pParentMatchResult2 =(CHMatchResult*)pParentMatch->getBlack();
		
			GSortedVector vSubMatches=pParentMatch->getSubMatches();
			CHMatch *pSubMatch=0;
			float points1=0.0,points2=0.0;
			for(size_t i=0;i<vSubMatches.entries();i++)
			{
				pSubMatch=(CHMatch*)vSubMatches[i]->getElement();
				CHMatchResult *pSubMatchResult1=pSubMatch->getMatchResultHome();
				CHMatchResult *pSubMatchResult2=pSubMatch->getMatchResultAway();

				points1+=pSubMatchResult1->getPoints();
				points2+=pSubMatchResult2->getPoints();
			}
			
			pParentMatchResult1->setPoints(points1);
			pParentMatchResult2->setPoints(points2);
			
			theApp.queueOut(pParentMatchResult1);
			theApp.queueOut(pParentMatchResult2);
		}
		theApp.queueOut(pWhite);
		theApp.queueOut(pBlack);
		theApp.out(TRN_CHANGE_MATCHRES);

		if(pPoolResult1)
			theApp.queueOut(pPoolResult1);
		if(pPoolResult2)
			theApp.queueOut(pPoolResult2);
		if(pPoolResult1 || pPoolResult2)
			theApp.out(TRN_CHANGE_POOLRES);

		CHStatusManager statusManager;
		statusManager.run(*pMatch,CHMemoryDataBase::eUnofficial);
	}

	/*theApp.queueOut(pMatch);
	theApp.out(TRN_CHANGE_MATCH);*/
	
}
void CHEvenControlOperations::recalculateTeam(CHMatch *pMatch)
{
	//Es un subpartido y tengo que acumular las puntuaciones
	CHMatch *pParentMatch=pMatch->getParentMatch();
	if(pParentMatch)
	{
		CHMatchResult *pParentMatchResult1 =(CHMatchResult*)pParentMatch->getMatchResultHome();
		CHMatchResult *pParentMatchResult2 =(CHMatchResult*)pParentMatch->getMatchResultAway();
	
		GSortedVector vSubMatches=pParentMatch->getSubMatches();
		CHMatch *pSubMatch=0;
		float points1=0.0,points2=0.0;
		for(size_t i=0;i<vSubMatches.entries();i++)
		{
			pSubMatch=(CHMatch*)vSubMatches[i]->getElement();
			CHMatchResult *pSubMatchResult1=pSubMatch->getMatchResultHome();
			CHMatchResult *pSubMatchResult2=pSubMatch->getMatchResultAway();

			points1+=pSubMatchResult1->getPoints();
			points2+=pSubMatchResult2->getPoints();
		}
		
		pParentMatchResult1->setPoints(points1);
		pParentMatchResult2->setPoints(points2);
		
		theApp.queueOut(pParentMatchResult1);
		theApp.queueOut(pParentMatchResult2);
		theApp.out(TRN_CHANGE_MATCHRES);
	}
	
	
}

void CHEvenControlOperations::startListMatch(CHMatch *pMatch,RWBoolean status)
{
	if(status)
	{
		CHStatusManager statusManager;
		statusManager.run(*pMatch,CHMemoryDataBase::eStartList);		
	}
	
	// Calculamos rankings
	CHRanking aRanking;
	aRanking.calculateRankings(pMatch);

	CHPool * pPool = (CHPool *) pMatch->getPool();
	CHPhase * pPhase = (CHPhase *) pMatch->getPhase();
	CHEvent * pEvent = (CHEvent *) pPhase->getEvent();
	if( pPool && pPhase )
	{
		// Desprogresamos
		CHProgression aProg(pMemory);
		CHPoolResult * pPoolResult = 0;
		for(size_t i=0 ; i<pPool->getPoolResultsVector().entries() ; i++)
		{
			pPoolResult = (CHPoolResult *)pPool->getPoolResultsVector()[i]->getElement();
			aProg.unprogressPoolResult(pPoolResult,true);
		}

		// Y volvemos a progresar...
		if( pMatch->getSubMatch()==0 &&
			!aProg.isLastRound(pMatch) && 
			aProg.nextRoundStatus(pMatch) < CHMemoryDataBase::eRunning )
			aProg.progressRound(pMatch,pMatch->getRound());

		if( pPool->getStatus() == CHMemoryDataBase::eFinished )
			aProg.setProgression(pPool);
		if( pPhase->getStatus() == CHMemoryDataBase::eFinished )
			aProg.setProgression(pPhase);
		aProg.sendTransactionMatchProgress(pMatch);
	}

	// Calculamos medallas
	if( pMatch->getPhaseCode() == SWISS_SISTEM)
		aRanking.calculateMedals(pMatch,pEvent);
}

void CHEvenControlOperations::finishMatch(CHMatch *pMatch,RWBoolean status)
{
	if(status)
	{
		CHStatusManager statusManager;
		statusManager.run(*pMatch,CHMemoryDataBase::eFinished);
		/*theApp.queueOut(pMatch);
		theApp.out(TRN_CHANGE_MATCH);*/
	}
	
	// Calculamos rankings
	CHRanking aRanking;
	aRanking.calculateRankings(pMatch);

	CHPool * pPool = (CHPool *) pMatch->getPool();
	CHPhase * pPhase = (CHPhase *) pMatch->getPhase();
	CHEvent * pEvent = (CHEvent *) pPhase->getEvent();

	if( pPool && pPhase )
	{
		// Desprogresamos
		CHProgression aProg(pMemory);
		CHPoolResult * pPoolResult = 0;
	/*	for(size_t i=0 ; i<pPool->getPoolResultsVector().entries() ; i++)
		{
			pPoolResult = (CHPoolResult *)pPool->getPoolResultsVector()[i]->getElement();
			aProg.unprogressPoolResult(pPoolResult,true);
		}*/

		// Tenemos que recalcular los Solkoff, Sonneberger y demás... de todos los partidos de la ronda
		if(pMatch->getFinishedRound())
		{
			// Recalculamos Special Points
			CHRanking aRanking;
			aRanking.reCalculateSpecialPointsPool(pMatch);	

			// Ranking de pool
			aRanking.calculateRankingsPool((CHPool*)pMatch->getPool());

			// Ranking de fase
			aRanking.calculateRankingsPhase((CHPhase*)pMatch->getPhase());

			// Ranking de evento
			aRanking.calculateRankingsEvent((CHEvent*)pMatch->getEvent());
		}

		// Y volvemos a progresar...
		if( pMatch->getSubMatch()==0 &&
			!aProg.isLastRound(pMatch) && 
			aProg.nextRoundStatus(pMatch) < CHMemoryDataBase::eRunning )
			aProg.progressRound(pMatch,pMatch->getRound());
		

				
		// Si hay algun Bye lo progreso
		/*for (i=0;i<pPhase->getPoolsVector().entries();i++)
		{
			CHPool* pPool = (CHPool*)pPhase->getPoolsVector()[i]->getElement();
			for (size_t j=0;j<pPool->getMatchsVector().entries();j++)
			{
				CHMatch* pMatch = (CHMatch*)pPool->getMatchsVector()[j]->getElement();
				manageByes(pMatch);					
			}
		}*/

	/*	if( pPool->getStatus() == CHMemoryDataBase::eFinished )
			aProg.setProgression(pPool);
		if( pPhase->getStatus() == CHMemoryDataBase::eFinished )
			aProg.setProgression(pPhase);*/
		aProg.sendTransactionMatchProgress(pMatch);
	}

	// Calculamos medallas
	if( pMatch->getPhaseCode() == SWISS_SISTEM)
		aRanking.calculateMedals(pMatch,pEvent);
}
RWBoolean CHEvenControlOperations::clearResults(CHMatch *pMatch)
{
	if (AfxMessageBox(_T("Do you want clean Match data ?"),MB_YESNO) == IDNO)
		return false;
	
	CHProgression aProg(pMemory);
	
	if (pMatch->areTeams() && pMatch->getSubMatch()==0)
	{//borro todo de los submatches
		for (size_t i=0; i<pMatch->getSubMatches().entries(); i++)
		{
			CHMatch *pMat = (CHMatch *)pMatch->getSubMatches()[i]->getElement();
			// Cambio el Match
			aProg.clearMatch(pMat);
			// Reseteo los Match Results
			aProg.clearMatchResults(pMat);
		}
	}

	// Cambio el Match
	aProg.clearMatch(pMatch);
	
	// Reseteo los Match Results
	aProg.clearMatchResults(pMatch);

	// Calculamos rankings
	CHRanking aRanking;
	aRanking.calculateRankings(pMatch);

	return true;
		
}

RWCString CHEvenControlOperations::getMatchResultDescription(CHMatchResult* pMatchResult)
{
	RWCString txt=NULLRWSTRING;
		
	if (pMatchResult->getRegister())
	{
		txt = pMatchResult->getPrnSName().toMultiByte();
	}
	else
	{
		char tmp[100]={" "};
		if (pMatchResult->getBye())
			sprintf(tmp,"%s (%s)", pMatchResult->getIDCompetitor(),"Bye");
		else if (pMatchResult->getPoolPosition())
			sprintf(tmp,"%s", pMatchResult->getIDCompetitor());
		txt=tmp;
	}
	return txt;	
}
RWCString CHEvenControlOperations::getMatchMemberDescription(CHMatchResult *pMatchResult)
{
	GSortedVector vMatchMembers=pMatchResult->getMembersVector();
	RWCString txt = NULLRWSTRING;
	CHMatchMember *pMatchMember=0;
	for(size_t i=0;i<vMatchMembers.entries();i++)
	{
		pMatchMember = (CHMatchMember*)vMatchMembers[i]->getElement();
		if(pMatchMember && pMatchMember->getRegister())
		{
			if(i!=0)
				 txt+="-"+pMatchMember->getPrnSName().toMultiByte();
			else txt+=pMatchMember->getPrnSName().toMultiByte();
		}
	}
			
	return txt;
}
CString CHEvenControlOperations::getSessionDescription(CHSession* pSession)
{
	CString aux = _T("");
	if (pSession)
	{
		aux.Format(_T("%d"), pSession->getSession());
		return aux;
	}
	return NULLRWSTRING;
}
CString CHEvenControlOperations::getCourtDescription(GCourt* pCourt)
{
	if (pCourt)
		return pCourt->getSDescription();
	return NULLRWSTRING;
}
void CHEvenControlOperations::manageByes(CHMatch *pMatch)
{
	if(!pMatch)
		return;

	CHEvent* pEvent = (CHEvent*)pMatch->getEvent();
	if (!pEvent)
		return;	

	if(!pMatch->hasByes())
		return;

	CHMatchResult * pMR1 = (CHMatchResult*)pMatch->getCompetitorsVector()[0]->getElement();
	CHMatchResult * pMR2 = (CHMatchResult*)pMatch->getCompetitorsVector()[1]->getElement();	

	if(pMR1->getBye() && pMR2->getBye())
	{
		pMR1->setPoints(0);
		pMR2->setPoints(0);
	}
	else if(pMR1->getBye())
	{
		pMR1->setPoints(0);
		pMR2->setPoints(pEvent->getPointsBye());
	}
	else if(pMR2->getBye())
	{
		pMR1->setPoints(pEvent->getPointsBye());
		pMR2->setPoints(0);
	}

	theApp.queueOut(pMR1);
	theApp.queueOut(pMR2);
	
	theApp.out(TRN_CHANGE_MATCHRES);

	CHStatusManager statusManager;
	statusManager.run(*pMatch,CHMemoryDataBase::eFinished);

	// Calculamos rankings
	CHRanking aRanking;
	aRanking.calculateRankings(pMatch);

	CHPool * pPool = (CHPool *) pMatch->getPool();
	CHPhase * pPhase = (CHPhase *) pMatch->getPhase();

	if( pPool && pPhase )
	{
		// Desprogresamos
		CHProgression aProg(pMemory);
		CHPoolResult * pPoolResult = 0;
		for(size_t i=0 ; i<pPool->getPoolResultsVector().entries() ; i++)
		{
			pPoolResult = (CHPoolResult *)pPool->getPoolResultsVector()[i]->getElement();
			aProg.unprogressPoolResult(pPoolResult,true);
		}

		if(pMatch->getFinishedRound())
		{
			// Recalculamos Special Points
			CHRanking aRanking;
			aRanking.reCalculateSpecialPointsPool(pMatch);	

			// Ranking de pool
			aRanking.calculateRankingsPool((CHPool*)pMatch->getPool());

			// Ranking de fase
			aRanking.calculateRankingsPhase((CHPhase*)pMatch->getPhase());

			// Ranking de evento
			aRanking.calculateRankingsEvent((CHEvent*)pMatch->getEvent());
		}

		// Y volvemos a progresar...
		if( pMatch->getSubMatch()==0 &&
			!aProg.isLastRound(pMatch) && 
			aProg.nextRoundStatus(pMatch) < CHMemoryDataBase::eRunning )
			aProg.progressRound(pMatch,pMatch->getRound());
	
		if( pPool->getStatus() == CHMemoryDataBase::eFinished )
			aProg.setProgression(pPool);
		if( pPhase->getStatus() == CHMemoryDataBase::eFinished )
			aProg.setProgression(pPhase);
	
		aProg.sendTransactionMatchProgress(pMatch);
	}

	// Calculamos medallas
	if( pMatch->getPhaseCode() == SWISS_SISTEM)
		aRanking.calculateMedals(pMatch,pEvent);

	//finishMatch(pMatch,true);
}

BOOL CHEvenControlOperations::statusForbidden(CHMatch *pMatch, RWBoolean msg/*=true*/)
{
	if (!pMatch)
		return FALSE;

	if (pMatch->getStatus() >= CHMemoryDataBase::eUnofficial)
	{
		if(msg)
			::msg("Warning!","The Match is finished, change status to revision for modifications",ICO_W,MSG_OK);
		return TRUE;
	}

	return FALSE;
}

void CHEvenControlOperations::processStartGame(CHMatch *pMatch, long idPlay/*=0*/)
{
	if (pMatch && pMatch->getStatus()!=CHMemoryDataBase::eFinished)
	{
		// Arrancamos el partido
		CHStatusManager statusManager;

		if(pMatch->getStatus() < CHMemoryDataBase::eRunning)
			statusManager.run(*pMatch,CHMemoryDataBase::eRunning,false,false);
	}
}

BOOL CHEvenControlOperations::playForbidden(CHMatch *pMatch, long idPlay)
{
	int resultCode = pMatch->getResultCode();

	if ( (	idPlay==PLAY_MOVEMENT		||
			idPlay==PLAY_SHORT_CASTLING ||
			idPlay==PLAY_LONG_CASTLING	||
			idPlay==PLAY_WHITE_WINNER	||
			idPlay==PLAY_BLACK_WINNER	||
			idPlay==PLAY_DRAW			||
			idPlay==PLAY_WHITE_WINNER_F	||
			idPlay==PLAY_BLACK_WINNER_F	||
			idPlay==PLAY_DRAW_F ) &&
		resultCode!=EV_EMPTY)
		return TRUE;
	
	return FALSE;
}


RWCString CHEvenControlOperations::getPgnNotation(CHMatch* pMatch)
{
	RWCString pgnNotation=NULLRWSTRING;

	if(!pMatch)
		return NULLRWSTRING;

	// Datos del partido
	CHDiscipline aDiscipline = (CHDiscipline&) pMemory->getDiscipline();
	GChampionship aChampionship = aDiscipline.getChampionship();

	// Event
	pgnNotation+="[Event ";
	pgnNotation+="\"";
	pgnNotation+=pMatch->getEventSDescription().toMultiByte();
	pgnNotation+="\"]";
	pgnNotation+="\x0a";

	// Site
	pgnNotation+="[Site ";
	pgnNotation+="\"";
	pgnNotation+=aChampionship.getSDescription().toMultiByte();
	pgnNotation+="\"]";
	pgnNotation+="\x0a";

	// Date
	pgnNotation+="[Date ";
	pgnNotation+="\"";
	pgnNotation+=pMatch->getStartDateAsString("%Y.%m");
	pgnNotation+="\"]";
	pgnNotation+="\x0a";

	// Round
	pgnNotation+="[Round ";
	pgnNotation+="\"";
	pgnNotation+=pMatch->getRoundAsString(false,false);
	pgnNotation+="\"]";
	pgnNotation+="\x0a";

	// white
	pgnNotation+="[White ";
	pgnNotation+="\"";
	if (pMatch->getWhite() &&
		pMatch->getWhite()->getRegister())
		pgnNotation+=pMatch->getWhite()->getPrnSName().toMultiByte();
	pgnNotation+="\"]";
	pgnNotation+="\x0a";

	// black
	pgnNotation+="[Black ";
	pgnNotation+="\"";
	if (pMatch->getBlack() &&
		pMatch->getBlack()->getRegister())
		pgnNotation+=pMatch->getBlack()->getPrnSName().toMultiByte();
	pgnNotation+="\"]";
	pgnNotation+="\x0a";

	// result
	pgnNotation+="[Result ";
	pgnNotation+="\"";
	if (pMatch->getStatus()>CHMemoryDataBase::eRunning)
		pgnNotation+=pMatch->getResultAsString();
	pgnNotation+="\"]";
	pgnNotation+="\x0a";

	// eco
	pgnNotation+="[ECO \" \"]";
	pgnNotation+="\x0a";
	pgnNotation+="\x0a";




	for (size_t i=0; i<size_t(pMatch->getHistoricNumber()); i++)
	{
		GTHHistoric aHist = pMatch->getHistoric(i);

		int Color = aHist.getValueOfData(DATA_PLAYER);
		int numPlay = aHist.getValueOfData(DATA_NUMPLAY);
			
		// retorno de carro cada 4 jugadas
		// Pinto numero de jugada para las blancas
		if (Color==EV_WHITE)
		{
			char tmp[10];
			sprintf(tmp,"%d.",numPlay);
			pgnNotation+=tmp;
		}				

		pgnNotation+=getPgnNotation(&aHist,true);		
		
		if (numPlay>0 && 
			numPlay%4==0 &&
			Color==EV_BLACK)
			pgnNotation+="\x0a";
		else
			pgnNotation+=" ";
	}
	
	pgnNotation+="\x0a";
	pgnNotation+="\x0a";

	return pgnNotation;
}

RWCString CHEvenControlOperations::getPgnNotation(GTHHistoric* pHistoric, RWBoolean withPiece/*=false*/)
{
	CHEventControlMoveManager aMoveManager;

	RWCString pgnNotation=NULLRWSTRING;

	if (!pHistoric)
		return NULLRWSTRING;

	int idPlay = pHistoric->getIdPlay();
	int numPlay = pHistoric->getValueOfData(DATA_NUMPLAY);
	int Color = pHistoric->getValueOfData(DATA_PLAYER);
	int Piece = pHistoric->getValueOfData(DATA_PIECE);
	int result = pHistoric->getValueOfData(DATA_RESULT);
	int eatPiece = pHistoric->getValueOfData(DATA_EATPIECE);
	int newPosi = pHistoric->getValueOfData(DATA_NEWPOSI);
	int oldPosi = pHistoric->getValueOfData(DATA_OLDPOSI);

	// Data general almacena si una ficha del mismo tipo y color podia
	// Haberse movido al mismo sitio
	int dataGeneral = pHistoric->getValueOfData(DATA_GENERAL_PURPOSE);
	
	if (idPlay==PLAY_WHITE_WINNER)
		pgnNotation=WHITE_WINNER_PGN_NOTATION;
	else if (idPlay==PLAY_BLACK_WINNER)					
		pgnNotation=WHITE_BLACK_PGN_NOTATION;
	else if (idPlay==PLAY_DRAW)							
		pgnNotation=DRAW_PGN_NOTATION;
	else if (idPlay==PLAY_WHITE_WINNER_F)					
		pgnNotation=WHITE_WINNER_F_PGN_NOTATION;
	else if (idPlay==PLAY_BLACK_WINNER_F)					
		pgnNotation=WHITE_BLACK_F_PGN_NOTATION;
	else if (idPlay==PLAY_DRAW_F)							
		pgnNotation=DRAW_F_PGN_NOTATION;
	else if (idPlay==PLAY_SHORT_CASTLING)
		pgnNotation=SH_CASTLING_PGN_NOTATION;
	else if (idPlay==PLAY_LONG_CASTLING)
		pgnNotation=LG_CASTLING_PGN_NOTATION;
	else
	{
		if (withPiece)
			pgnNotation=getPiecePgnNotation(Piece);
		
		// Old Posi
		int oldi=0,oldj=0;
		aMoveManager.getPgnRowCol(oldPosi,&oldi,&oldj);
				
		if (idPlay == PLAY_MOVEMENT)
		{
			if (dataGeneral==1 || ( (Piece==W_PAWN || Piece==B_PAWN) && eatPiece!=NOTHING ) )
			{
				char oldCol = oldj+'a';
				pgnNotation+=oldCol;
			}
		}

		// Come pieza		
		if (eatPiece>0)
			pgnNotation+=EAT_PGN_NOTATION;

		// new Posi
		int newi=0,newj=0;
		

		aMoveManager.getPgnRowCol(newPosi,&newi,&newj);
		char newCol = newj+'a';
		pgnNotation+=newCol;

		char tmp[10];
		sprintf(tmp,"%d",newi);
		pgnNotation+=tmp;

		// Result
		if (result==EV_CHECK)
			pgnNotation+=CHECK_PGN_NOTATION;
		if (result==EV_CHECKMATE)
			pgnNotation+=CHECKMATE_PGN_NOTATION;
	}


	return pgnNotation;
}

RWCString CHEvenControlOperations::getPiecePgnNotation(short Piece)
{
	switch (Piece)
	{
		case W_PAWN:
		case B_PAWN:
			return PAWN_PGN_NOTATION;
		case W_KNIGHT:
		case B_KNIGHT:
			return KNIGHT_PGN_NOTATION;
		case W_BISHOP:
		case B_BISHOP:
			return BISHOP_PGN_NOTATION;
		case W_ROOK: 
		case B_ROOK:
			return ROOK_PGN_NOTATION;
		case W_QUEEN:
		case B_QUEEN:
			return QUEEN_PGN_NOTATION;
		case W_KING:
		case B_KING:
			return KING_PGN_NOTATION;
	}
	return NULLRWSTRING;
}

RWBoolean CHEvenControlOperations::processResultsFromPgnFile(GSortedVector vMatchesInPlay,RWCString resultPath, GSortedVector &vPgnMatches)
{
	RWCString line;
	CHReadFile aReadFile(resultPath);	
	if (!aReadFile.getValidFile())
	{
		AfxMessageBox(_T("Invalid File\n"));
		return false;
	}

	int cont = 1;
	CHPgnMatch *pPgnMatch=0;
	while( aReadFile.getLine(line) )
	{
		size_t pos = 0;
		pos = line.first('[');
		if (pos!=RW_NPOS)
		{
			RWCString aux = line(pos+1,pos+6);	
			if (!strcmp(aux,"Event "))
			{
				pPgnMatch = new CHPgnMatch(cont);
				vPgnMatches.insert(pPgnMatch);
				cont++;
			}
		}

		if (pPgnMatch)
			pPgnMatch->process(line);
	}

	return true;
}

RWBoolean CHEvenControlOperations::copyHistoricToMatch(CHPgnMatch* pPgnMatch, CWnd* pGUI)
{
	RWCString historic = pPgnMatch->getHistoric();
	CHMatch* pMatch = (CHMatch*)pPgnMatch->getMatch();
	
	size_t pos1 = 0;
	size_t pos2 = 0;
	size_t pos3 = 0;
	
	int numPlay=0;
	RWCString aux=NULLRWSTRING;
	RWCString play=NULLRWSTRING;
	RWCString playWhite=NULLRWSTRING;
	RWCString playBlack=NULLRWSTRING;
	RWCString result=NULLRWSTRING;

	size_t pos = historic.first(13);
	while (pos!=RW_NPOS)
	{	
		historic.remove(pos,1);
		historic.insert(pos," ");
		pos = historic.first(13);
	}
	

	while (historic.length())
	{
		//1. Busco el primer punto, la jugada es el caracter de antes del punto.
		pos1 = historic.first('.');
		if (pos1!=RW_NPOS)
		{
			//2. Copio la jugada.
			aux = historic(0,pos1);
			numPlay=atoi(aux);
			historic.remove(0,pos1+1);
		}
		//3. Busco el siguiente punto y retrocedo dos posiciones.
		pos2 = historic.first('.');
		if (pos2!=RW_NPOS)
		{
			//4. Ya tengo la jugada de blancas y negras.
			play = historic(0,pos2-2);

			size_t pos4=play.first(13);
			if (pos4!=RW_NPOS)
				play.remove(pos4,1);

			historic.remove(0,pos2-2);
			
			//5. Buscando hasta el espacio el blanco tengo la jugada de blancas.
			pos3 = play.first(" ");
			if (pos3==0)
			{
				play.remove(pos3,1);
				pos3 = play.first(" ");
			}

			if (pos3!=RW_NPOS)
			{
				playWhite=play(0,pos3);
				//6. El resto es de las negras.
				playBlack=play(pos3+1,play.length()-pos3-1);
			}
		}
		else
		{
			// Estamos en la ultima jugada
			pos2 = historic.first(" ");
			if (pos2!=RW_NPOS)
			{
				//5. Buscando hasta el espacio el blanco tengo la jugada de blancas.
				playWhite=historic(0,pos2);
				historic.remove(0,pos2+1);
				pos3 = historic.first(" ");
				if (pos3!=RW_NPOS)
				{
					//5. Buscando hasta el espacio el blanco tengo la jugada de negras.
					playBlack=historic(0,pos3);
					historic.remove(0,pos3);
					result=historic;
					historic.remove(0,historic.length());
				}
			}
		}

		emptyBlancks(playWhite);
		emptyBlancks(playBlack);

		//7. Proceso la jugada.
		processPlay(pGUI, pMatch, playWhite, CHMatchResult::eWhite,numPlay);
		processPlay(pGUI, pMatch, playBlack, CHMatchResult::eBlack,numPlay);
	}

	return true;
}

void CHEvenControlOperations::emptyBlancks(RWCString &value)
{
	size_t pos = value.first(32);
	while (pos!=RW_NPOS)
	{
		value.remove(pos,1);
		pos = value.first(32);
	}
}

void CHEvenControlOperations::processPlay(CWnd* pGUI, CHMatch* pMatch, RWCString play, CHMatchResult::side color, int numPlay)
{
	if (!play.length())
		return;

	RWCString aux=play;
	RWCString source=NULLRWSTRING;
	RWCString target=NULLRWSTRING;
	RWBoolean short_castling=false;
	RWBoolean long_castling=false;
	RWBoolean isCheck=false;
	RWBoolean isCheckMate=false;
	RWBoolean eatPieze=false;
	int myPiece=NOTHING;
	
	// Miramos si hay enroque
	size_t posQ = play.first("-");
	if (posQ!=RW_NPOS)
	{
		size_t posO = play.first("O");
		if (posO!=RW_NPOS)
		{
			if (play.length()==4 || play.length()==3)
				short_castling=true;
			else if (play.length()==6 || play.length()==5)
				long_castling=true;
		}
		else 
		{
			// Jugada Ganadora 1-0, 0-0, 0-1, 1/2-1/2 ...
		
		}
	}
	else
	{
		// Miramos si hay Jaque
		size_t posCH = play.first("+");
		if (posCH!=RW_NPOS)
		{
			isCheck=true;
			play.remove(posCH,1);
		}
		// Miramos si hay Jaque
		size_t posCHM = play.first("#");
		if (posCHM!=RW_NPOS)
		{
			isCheckMate=true;
			play.remove(posCHM,1);
		}

		// Miramos si come pieza
		size_t posX = play.first("x");
		if (posX!=RW_NPOS)
		{
			eatPieze=true;
			play.remove(posX,1);
			//myPiece=getPgnNotationPiece(play(0,1),color);
			//source = play(0,posX-1);
			//target = play(posX,play.length()-posX);
		}
		
		// Es una jugada normal de movimiento
		// Miramos la longitud
		if (play.length()==2) // Movimiento de Peon;
		{
			myPiece = (color==CHMatchResult::eWhite?W_PAWN:B_PAWN);
			target=play;
		}
		else if (play.length()==3) // Movimiento de Otra Pieza no peon;
		{
			myPiece=getPgnNotationPiece(play(0,1),color);				
			target=play(1,2);
		}
		else if (play.length()==4) // Movimiento de Otra Pieza no peon incluye target;
		{
			myPiece=getPgnNotationPiece(play(0,1),color);				
			source=play(1,1);
			target=play(2,2);
		}
		else if (play.length()==5) // Movimiento de Otra Pieza no peon incluye target (fila columna);
		{
			myPiece=getPgnNotationPiece(play(0,1),color);				
			source=play(1,2);
			target=play(3,2);
		}
	}	

	TMOVEMENT aMovement;	
	aMovement.checkSameMov=target.length()!=0;
	aMovement.Color=color==CHMatchResult::eWhite?EV_WHITE:EV_BLACK;

	int colDrag = 0;
	int rowDrag = 0;
	int colDrop = 0;
	int rowDrop = 0;

	if (short_castling)
	{
		aMovement.idPlay=EV_SHORT_CASTLING;
		if (color==CHMatchResult::eWhite)
		{
			rowDrag=W_PGN_ROWDRAG_SH_CAST;
			colDrag=W_PGN_COLDRAG_SH_CAST;			
			rowDrop=W_PGN_ROWDROP_SH_CAST;
			colDrop=W_PGN_COLDROP_SH_CAST;		
		}
		else
		{
			rowDrag=B_PGN_ROWDRAG_SH_CAST;
			colDrag=B_PGN_COLDRAG_SH_CAST;			
			rowDrop=B_PGN_ROWDROP_SH_CAST;
			colDrop=B_PGN_COLDROP_SH_CAST;			
		}
	}
	else if (long_castling)
	{
		aMovement.idPlay=EV_LONG_CASTLING;
		if (color==CHMatchResult::eWhite)
		{
			rowDrag=W_PGN_ROWDRAG_LG_CAST;
			colDrag=W_PGN_COLDRAG_LG_CAST;
			rowDrop=W_PGN_ROWDROP_LG_CAST;
			colDrop=W_PGN_COLDROP_LG_CAST;		
		}
		else
		{
			rowDrag=B_PGN_ROWDRAG_LG_CAST;
			colDrag=B_PGN_COLDRAG_LG_CAST;
			rowDrop=B_PGN_ROWDROP_LG_CAST;
			colDrop=B_PGN_COLDROP_LG_CAST;		
		}
	}
	else 
	{
		aMovement.idPlay=EV_MOVE;

		if (source.length())
			colDrag=getCol(source);
	
		colDrop = getCol(target(0,1));
		rowDrop = atoi(RWCString(target(1,1)));
	}
	
	aMovement.Piece=myPiece;
	aMovement.result=0;

	if (isCheck)
		aMovement.result=EV_CHECK;
	else if (isCheckMate)
		aMovement.result=EV_CHECKMATE;

	CHEventControlMoveManager aMoveManager;
	aMovement.newPosi = aMoveManager.getPosition(MAXSQUARES-rowDrop,colDrop-1);

	if (rowDrag)
		aMovement.oldPosi = aMoveManager.getPosition(MAXSQUARES-rowDrag,colDrag-1);
	else
		aMovement.oldPosi = colDrag-1;

	aMovement.eatedPiece=0;
	
	pGUI->SendMessage(UM_PROCESS_MOVEMENT,(WPARAM)pMatch, (LPARAM)&aMovement);
}

int CHEvenControlOperations::getPgnNotationPiece(RWCString piece, CHMatchResult::side color)
{
	if (piece==KNIGHT_PGN_NOTATION)
		return (color==CHMatchResult::eWhite?W_KNIGHT:B_KNIGHT);		
	else if (piece==BISHOP_PGN_NOTATION)
		return (color==CHMatchResult::eWhite?W_BISHOP:B_BISHOP);
	else if (piece==ROOK_PGN_NOTATION)
		return (color==CHMatchResult::eWhite?W_ROOK:B_ROOK);
	else if (piece==QUEEN_PGN_NOTATION)
		return (color==CHMatchResult::eWhite?W_QUEEN:B_QUEEN);
	else if (piece==KING_PGN_NOTATION)
		return (color==CHMatchResult::eWhite?W_KING:B_KING);
	
	return (color==CHMatchResult::eWhite?W_PAWN:B_PAWN);	
}

RWBoolean CHEvenControlOperations::isValidCol(RWCString col)
{
	if (col=="a" || col=="b" || col=="c" || col=="d" || 
		col=="e" || col=="f" || col=="g" || col=="h" )
	{
		return true;
	}
	return false;
}

int CHEvenControlOperations::getCol(RWCString col)
{
	if	(col=="a")
		return 1;
	
	if	(col=="b")
		return 2;
	
	if	(col=="c")
		return 3;

	if	(col=="d") 
		return 4;
	
	if	(col=="e")
		return 5;

	if	(col=="f") 
		return 6;

	if	(col=="g") 
		return 7;

	if	(col=="h")
		return 8;
	
	return 0;
}