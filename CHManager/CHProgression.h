/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHProgression.h
*	Description	: Interface for the CHProgression class.
*
*	Author		: Chess Team
*	Date created: 15-12-2005
* 	Project		: CHManager
*	
* 	Modification history
*	By			: 
*	Date		: 
*	Changes		: 
*
***************************************************************************************/

#if !defined(AFX_CHPROGRESSION_H__36FD65C5_59F7_493F_B694_B538E8B36D66__INCLUDED_)
#define AFX_CHPROGRESSION_H__36FD65C5_59F7_493F_B694_B538E8B36D66__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <GUI/TH/GTHProgression.h>

class CHProgression : public GTHProgression  
{
public:
	CHProgression(CHMemoryDataBase * pMem);
	virtual ~CHProgression();

	GTHPhase *				getNewPhase();
	GTHPool *				getNewPool();
	GTHPoolResult *			getNewPoolResult();
	GTHMatch *				getNewMatch();
	GTHMatchResult *		getNewMatchResult();
	GTHSplitMatchResult *	getNewSplitMatchResult();
	GTHMatchMember *		getNewMatchMember();
	GTHStatusManager *		getNewStatusManager();

	//llamadas desde Modalidad
	RWBoolean onCreatePoolResult(GTHPoolResult * pPoolResult,GTHModalityPhase * pModalityPhase);
	RWBoolean onCreateMatchResult(GTHMatchResult * pMatchResult,GTHModalityPhase * pModalityPhase);
	RWBoolean onCreateMatch(GTHMatch * pMatch,GTHModalityPhase * pModalityPhase);

	//Methodos llamados desde la Form view de la Progresion para generar los Objetos
	bool onChangeInscription(GTHInscription *pInscription, GTHMatchResult *pMatchResult);

	//llamadas desde Interface de progresion
	RWBoolean onCreatePoolResult(GTHPoolResult * pPoolResult);
	RWBoolean onCreateMatchResult(GTHMatchResult * pMatchResult);
	RWBoolean onCreateMatch(GTHMatch * pMatch);

	// Finish match, pone status a fin, calcula rank...
	// **********************************************//
	RWBoolean		progressRound(CHMatch* pMatch, short round);
	RWBoolean		isFinishRound(CHPool* pPool, short round);

	RWBoolean		createConfrontationMatches(CHMatch* pMatch);
	void			createMatchResultsOfMatch(CHMatch * pMatch,CHTeamMatchsCnfg *pTeamMatchsCnfg);//crea todos los CHMatchResult de un partido 
	CHMatchResult * createMatchResult(CHMatch * pMatch,short position);//crea un CHMatchResult de un partido
	void			createMatchMembers(CHMatchResult * pMatchResult,CHTeamMatchsCnfg *pTeamMatchsCnfg);

	RWBoolean		deleteConfrontationMatches	(CHMatch * pMatch);
	void			deleteMatchResultsOfMatch	(CHMatch * pMatch,CHTeamMatchsCnfg *pTeamMatchsCnfg);
	CHMatchResult * deleteMatchResult			(CHMatch * pMatch,short position);
	void			deleteMatchMembers			(CHMatchResult * pMatchResult,CHTeamMatchsCnfg *pTeamMatchsCnfg);

	short			getYourMatchCode(GTHPool * pPool,short matchCode,bool addMatch);
	short			getMatchCode(GTHPhase * pPhase);
	void			clearMatch(CHMatch * pMatch);
	void			clearMatchResults(CHMatch * pMatch);
	void			setProgression(GTHPool * pPool);
	void			setProgression(GTHPhase * pPhase);
	void			sendTransactionMatchProgress(CHMatch *pMatch);
	void			removeCompetitors(CHPhase* pPhase);

	GTHInscription*	getInscriptionSeed(GTHEvent * pEvent,short seed);
	RWBoolean		changeTeamsOrder(CHMatchResult* pMRHome, CHMatchResult* pMRAway);
	void			copyMatchMembers   (CHMatchResult * pMatchResult, RWOrdered & vector);
	void			changeMatchMembers (CHMatchResult * pMatchResult, RWOrdered & vector);
	void			changeMatchResult  (CHMatchResult * pMatchResult, CHPoolResult * pPoolResult);
	RWBoolean		isLastRound(CHMatch *pMatch);
	unsigned char	nextRoundStatus(CHMatch *pMatch);
	
	RWBoolean		checkMatchResult(CHMatchResult * pMatchResult,CHPoolResult * pPoolResult, RWBoolean showMsgs);

	bool			unprogressUserMatch(GTHMatch *pMatch, bool cascade);
	

private:
	CHMemoryDataBase *		m_pMem;
	RWCString		lastMatchLocked;
};

#endif // !defined(AFX_CHPROGRESSION_H__36FD65C5_59F7_493F_B694_B538E8B36D66__INCLUDED_)
