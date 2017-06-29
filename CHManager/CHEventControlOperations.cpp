/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHEventControlOperations.cpp
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
#include "CHManagerApp.h"
#include "CHEventControlOperations.h"
#include "CHProgression.h"
#include "CHStatusManager.h"
#include "CHRanking.h"
#include <ovr\core\G\GScore.h>
#include "..\CHMngtModel\CHPhase.h"
#include "..\CHMngtModel\CHPool.h"
#include "..\CHMngtModel\CHMatch.h"
#include "..\CHMngtModel\CHPoolResult.h"
#include "..\CHMngtModel\CHStatisticDefines.h"

// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHEventControlOperations::CHEventControlOperations(MSLGUIEx* pGUIEx)
{	
}

CHEventControlOperations::~CHEventControlOperations()
{
}

void CHEventControlOperations::calculatePointMatchResult(CHMatch *pMatch)
{
	if(!pMatch)
		return;

	float sets1=0; 
	float sets2=0; 
	
	CHMatchResult *pMatchResult1=(CHMatchResult*) pMatch->getHome();
	CHMatchResult *pMatchResult2=(CHMatchResult*) pMatch->getAway();
 
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
	
	CHSend.toServerDB(pMatchResult1);
	CHSend.toServerDB(pMatchResult2);
}

void CHEventControlOperations::setScore(long idEvent,CHMatch *pMatch)
{	
	float score1=0.0, score2=0.0;
	short forfeit=0;

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
	}
		
	CHMatchResult *pWhite =pMatch->getWhite();
	CHMatchResult *pBlack =pMatch->getBlack();
	
	pWhite->setPoints(score1);
	pWhite->setResult(pWhite->getPointsAsString());
	pBlack->setPoints(score2);
	pBlack->setResult(pBlack->getPointsAsString());
	
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
		
		if (MSLMsgBox( m_pGUIEx->getHWnd() ,"Do you want to assign this incidence to the pool results?", GUI_ICO_WARNING, GUI_MB_YESNO, "CHManager Warning")==IDYES)			
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
		CHMatch *pParentMatch=(CHMatch *) pMatch->getParent();
		if(pMatch->getSubCode() && pParentMatch)
		{
			CHMatchResult *pParentMatchResult1 =(CHMatchResult*)pParentMatch->getHome();
			CHMatchResult *pParentMatchResult2 =(CHMatchResult*)pParentMatch->getAway();
		
			MSLSortedVector vSubMatches;
			pParentMatch->getSubMatchesVector(vSubMatches);
			CHMatch *pSubMatch=0;
			float points1=0.0,points2=0.0;
			for(short i=0;i<vSubMatches.entries();i++)
			{
				pSubMatch=(CHMatch*)vSubMatches[i];
				CHMatchResult *pSubMatchResult1= (CHMatchResult *) pSubMatch->getHome();
				CHMatchResult *pSubMatchResult2= (CHMatchResult *) pSubMatch->getAway();
				 
				points1+=pSubMatchResult1->getPoints();
				points2+=pSubMatchResult2->getPoints();
			}
			
			GScore result1=points1;
			pParentMatchResult1->setPoints(points1);
			pParentMatchResult1->setResult(result1.asString("##.#"));
			GScore result2=points2;
			pParentMatchResult2->setPoints(points2);
			pParentMatchResult2->setResult(result2.asString("##.#"));
			
			CHSend.toServerDB(pParentMatchResult1);
			CHSend.toServerDB(pParentMatchResult2);			
		}

		CHSend.toServerDB(pWhite);
		CHSend.toServerDB(pBlack);

		if(pPoolResult1)
			CHSend.toServerDB(pPoolResult1);
			
		if(pPoolResult2)
			CHSend.toServerDB(pPoolResult2);
		
		CHStatusManager statusManager;
		statusManager.setStatus(pMatch,CHMemoryDataBase::eUnofficial);
	}	
}

void CHEventControlOperations::recalculateTeam(CHMatch *pMatch)
{
	//Es un subpartido y tengo que acumular las puntuaciones
	CHMatch *pParentMatch= (CHMatch *) pMatch->getParent();
	if(pParentMatch)
	{
		CHMatchResult *pParentMatchResult1 =(CHMatchResult*)pParentMatch->getHome();
		CHMatchResult *pParentMatchResult2 =(CHMatchResult*)pParentMatch->getAway();
	
		MSLSortedVector vSubMatches;
		pParentMatch->getSubMatchesVector(vSubMatches);
		CHMatch *pSubMatch=0;
		float points1=0.0,points2=0.0;
		for(short i=0;i<vSubMatches.entries();i++)
		{
			pSubMatch=(CHMatch*)vSubMatches[i];
			CHMatchResult *pSubMatchResult1=(CHMatchResult *)pSubMatch->getHome();
			CHMatchResult *pSubMatchResult2=(CHMatchResult *)pSubMatch->getAway();

			points1+=pSubMatchResult1->getPoints();
			points2+=pSubMatchResult2->getPoints();
		}
		
		pParentMatchResult1->setPoints(points1);
		pParentMatchResult2->setPoints(points2);
	
		CHSend.toServerDB(pParentMatchResult1);
		CHSend.toServerDB(pParentMatchResult2);
	}	
}

void CHEventControlOperations::startListMatch(CHMatch *pMatch,bool status)
{
	if(status)
	{
		CHStatusManager statusManager;
		statusManager.setStatus(pMatch,CHMemoryDataBase::eStartList);		
	}
	
	

	// Calculamos rankings
	/*CHRanking aRanking;
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
		aRanking.calculateMedals(pMatch,pEvent);*/
}

void CHEventControlOperations::finishMatch(CHMatch *pMatch,bool status)
{
	if(status)
	{
		CHStatusManager statusManager;
		statusManager.setStatus(pMatch,CHMemoryDataBase::eFinished);		
	}
	
	// Rankings
	CHRanking aRanking((MSLGUIEx*)m_pGUIEx);

	if (pMatch->getStatus()==CHMemoryDataBase::eFinished)
		aRanking.calculateRankings(pMatch);

	if (pMatch->getSubCode())
	{
		CHMatch* pParentMatch = (CHMatch*) pMatch->getParent();
		if (pParentMatch &&
			pParentMatch->getStatus()==CHMemoryDataBase::eFinished)
			aRanking.calculateRankings(pParentMatch);
	}
		
	CHPool * pPool = (CHPool *) pMatch->getPool();
	CHPhase * pPhase = (CHPhase *) pMatch->getPhase();
	CHEvent * pEvent = (CHEvent *) pPhase->getEvent();

	if(pMatch->getFinishedRound() || 
	   (pPool->getStatus()==CHMemoryDataBase::eUnofficial ||
		pPool->getStatus()==CHMemoryDataBase::eFinished ) )
	{
		// Recalculamos Special Points			
		//aRanking.reCalculateSpecialPointsPool(pMatch);	

		// Ranking de pool
		aRanking.calculateRankings(pPool);

		// Ranking de fase
		aRanking.calculateRankings(pPhase);

		// Ranking de evento
		aRanking.calculateRankings(pEvent);
	}

	CHProgression aProgression((MSLGUIEx*)m_pGUIEx);

	if (pPool->getStatus()==CHMemoryDataBase::eUnofficial ||
		pPool->getStatus()==CHMemoryDataBase::eFinished )
	{
		// Pool Progression
		aProgression.doProgression(pPool);
	}

	if (pPhase->getStatus()==CHMemoryDataBase::eUnofficial || 
		pPhase->getStatus()==CHMemoryDataBase::eFinished )
	{
		// Phase Progression
		aProgression.doProgression(pPhase);
	}

	// Calculamos medallas
	aRanking.calculateMedals(pMatch->getPhase());
}

bool CHEventControlOperations::clearResults(CHMatch *pMatch)
{
	/*if (AfxMessageBox(_T("Do you want clean Match data ?"),MB_YESNO) == IDNO)
		return false;
	
	CHProgression aProg;
	
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
	aRanking.calculateRankings(pMatch);*/

	return true;
		
}

bool CHEventControlOperations::statusForbidden(CHMatch *pMatch, bool msg/*=true*/)
{
	/*if (!pMatch)
		return false;

	if (pMatch->getStatus() >= CHMemoryDataBase::eUnofficial)
	{
		if(msg)
			::msg("Warning!","The Match is finished, change status to revision for modifications",ICO_W,MSG_OK);
		return true;
	}*/

	return false;
}

void CHEventControlOperations::processStartGame(CHMatch *pMatch, long idPlay/*=0*/)
{
	if (pMatch && pMatch->getStatus()!=CHMemoryDataBase::eFinished)
	{
		// Arrancamos el partido
		CHStatusManager statusManager;

		if(pMatch->getStatus() < CHMemoryDataBase::eRunning)
			statusManager.setStatus(pMatch,CHMemoryDataBase::eRunning,false);
	}
}

/*BOOL CHEventControlOperations::playForbidden(CHMatch *pMatch, long idPlay)
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


MSLString CHEventControlOperations::getPgnNotation(CHMatch* pMatch)
{
	MSLString pgnNotation=NULLRWSTRING;

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

MSLString CHEventControlOperations::getPgnNotation(GTHHistoric* pHistoric, RWBoolean withPiece)
{
	CHEventControlMoveManager aMoveManager;

	MSLString pgnNotation=NULLRWSTRING;

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

MSLString CHEventControlOperations::getPiecePgnNotation(short Piece)
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

RWBoolean CHEventControlOperations::processResultsFromPgnFile(GSortedVector vMatchesInPlay,MSLString resultPath, GSortedVector &vPgnMatches)
{
	MSLString line;
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
			MSLString aux = line(pos+1,pos+6);	
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

RWBoolean CHEventControlOperations::copyHistoricToMatch(CHPgnMatch* pPgnMatch, CWnd* pGUI)
{
	MSLString historic = pPgnMatch->getHistoric();
	CHMatch* pMatch = (CHMatch*)pPgnMatch->getMatch();
	
	size_t pos1 = 0;
	size_t pos2 = 0;
	size_t pos3 = 0;
	
	int numPlay=0;
	MSLString aux=NULLRWSTRING;
	MSLString play=NULLRWSTRING;
	MSLString playWhite=NULLRWSTRING;
	MSLString playBlack=NULLRWSTRING;
	MSLString result=NULLRWSTRING;

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

void CHEventControlOperations::emptyBlancks(MSLString &value)
{
	size_t pos = value.first(32);
	while (pos!=RW_NPOS)
	{
		value.remove(pos,1);
		pos = value.first(32);
	}
}

void CHEventControlOperations::processPlay(CWnd* pGUI, CHMatch* pMatch, MSLString play, CHMatchResult::side color, int numPlay)
{
	if (!play.length())
		return;

	MSLString aux=play;
	MSLString source=NULLRWSTRING;
	MSLString target=NULLRWSTRING;
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
		rowDrop = atoi(MSLString(target(1,1)));
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

int CHEventControlOperations::getPgnNotationPiece(MSLString piece, CHMatchResult::side color)
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

RWBoolean CHEventControlOperations::isValidCol(MSLString col)
{
	if (col=="a" || col=="b" || col=="c" || col=="d" || 
		col=="e" || col=="f" || col=="g" || col=="h" )
	{
		return true;
	}
	return false;
}

int CHEventControlOperations::getCol(MSLString col)
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
*/