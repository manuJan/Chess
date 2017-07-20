/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHTVTools.h
*	Description	:
*
*	Author		: 
*	Date created: 11-Dec-2009
* 	Project		: WU TV
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#pragma once
#include <ovr\tools\msltools\MSLFileIni.h>

class CHTVGUI;
class GSession;
class CHEvent;
class CHPhase;
class CHMatch;
class CHMatchResult;
class CHEventResult;
class CHInscription;
class GMedalsByNoc;

class CHTVTools
{
public:
	enum TypeRSC {eGender,eEvent,ePhase,eUnit};

	CHTVTools();
	virtual ~CHTVTools();
	
	CHMemoryDataBase *	mem();
	
	void		init(CHTVGUI *pGUI);

	MSLString	getAthleteID	(GRegister * pRegister);	
	MSLString	getResultScore	(CHMatchResult *pMatchResult);
	MSLString	getEventScore	(CHMatchResult *pMatchResult);
	MSLString	getEventRankPo	(CHMatchResult *pMatchResult);
	MSLString	getEventRank	(CHMatchResult *pMatchResult);	

	MSLString	getMode();
	MSLString	getRSCDll();

	// Session
	MSLString	getSessionDesc(GSession * pSession=0) const;
	
	// Phases
	void		getPhases(GSession * pSession, MSLSortedVector &vMatches);

	// Matches
	void		getMatches(MSLSortedVector &vMatches, const bool withByes=false);
	MSLString	getDesc(const CHMatch * pMatch) const;
	long		getStatus(const CHMatch *pMatch) const;
	void		getMembersVector(CHInscription *pInscription, MSLSortedVector& vMembers);

	// saves
	void saveParticipants		();
	void saveRegister			(GRegister * pRegister);
	void saveSessionSchedule	(GSession * pSession);
	void saveSessionScheduleDetailed(GSession * pSession);
	void saveSessionScheduleUnit(GSession * pSession);
	void saveSchedule			(CHPhase * pPhase);
	void saveScheduleDetailed	(CHMatch * pMatch);
	void saveScheduleUnit		(CHMatchResult * pMatchResult);
	void saveEventInfo			(CHMatch * pMatch);
	void saveOfficials			(CHMatch * pMatch);
	void saveOfficial			(GTHMatchJudge * pMatchJudge);
	void saveCompetitor			(CHMatch * pMatch);
	void saveCompetitor			(CHMatchResult *pMatchResult,GData *pData=0,long pos=0,bool showProgression=false);
	void saveBracket			(CHMatch * pMatch);
	void saveBracket			(CHMatchResult *pMatchResult);
	void saveHistory			(CHMatch * pMatch);
	void saveHistory			(CHMatchResult *pMatchResult, MSLString key);
	void saveMedals				(CHMatch * pMatch);
	void saveMedals				(CHEventResult *pEventResult, const long i);
	void saveTeamMembers		(GData* pData, short &pos);
	void savePoolStandings		(CHMatch * pMatch);
	void savePoolInfo			(MSLSortedVector * pColGroupInfo,CHMatch * pMatch);
	void saveKnockoutInfo		(MSLSortedVector * pColGroupInfo,CHMatch * pMatch);

	// changes
	void changedRegister		(bool update,GRegister *pRegister);
	void changedParticipant		(bool update,GRegister *pRegister);
	void changedCompetitor		(bool update,CHMatchResult *pMatchResult);
	void changedEventInfo		(bool update,CHMatch *pMatch);
	void changedHistory			(bool update,CHMatch *pMatch);
	void changedMedals			(bool update,CHEvent *pEvent);
	void changedMedals			(bool update,CHMatch *pMatch);
	
	// help
	void	getWinnsLosses		(CHMatchResult *pMatchResult, short &W, short&L);
	int		getOrderOnCourt		(CHMatchResult* pMatchResult);
	MSLString getMedalDesc		(short rank);

private:
	CHMemoryDataBase*	m_pMem;
	CHTVGUI*			m_pGUI;
	MSLWString			m_fileIni; // fichero ini donde se guarda el modo en que se escribe el Athlete_ID(ACCREDITATION o REGISTER)
};
