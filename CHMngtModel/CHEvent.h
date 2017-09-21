/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHEvent.h
*	Description	:
*
*	Author		: Javier Juste
*	Date created: 3 Junio 2008
* 	Project		: Chess DLL
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#pragma once
#include "CHMemoryDataBaseDefs.h"
#include <OVR/CORE/TH/GTHEvent.h>

class CHPhase;

class CHMngtModelExport CHEvent : public GTHEvent  
{
	MSLDECLARE_ITEM(CHEvent)

	enum TypeEvent {eNone=0, eClassic=1, eRapid=2, eBlitz=3};	
	enum TypeRank  {eEmpty=0, eQualitative=1, ePoints=2, eMatchPoints=3, eDirectEncounter=4, eKoyaTieBreak=5, eSolkoff=6, eSonneBerger=7, eSolkoffCutLowest=8, eSolkoffCutLowestAndHighest=9, eProgressiveScore=10, eRating=11, eTeamMatchesWon=12, eMatchesWon=13, eMatchesDrawm=14,eTeamPointsWon=15, eAvgOppRating=16  };
	
public:
	// Constructors/Destructor
	CHEvent();
	CHEvent(const CHEvent & copy);
	virtual ~CHEvent();

	/**** Virtual operators inherited from GData ********************/
	GData& operator= (const GData& copy);
	bool   operator==(const GData& copy);
	bool   operator!=(const GData& copy);
	
	/**** Virtual methods inherited from GData **********************/
	MSLPack& pack  (MSLPack& pck) const;
	MSLPack& unpack(MSLPack& pck);

	QBase*			onQ() const;
	UBase*			onU() const;

	//Set's
	void setTypeEvent		(const short value);
	void setTwoBronces		(const short value);	
	void setReqRankOrder	(const MSLString value);
	void setIdTeamMatchsCnfg(const short value);
	void setConstRating		(const double value);
	void setPointsBye		(const double value);
	void setCodeReports		(const MSLString value);
	
	
	//Get´s
	short		getTypeEvent		() const;	
	short		getTwoBronces 		() const;	
	MSLString	getReqRankOrder		() const;
	short		getInscriptions		() const;
	int			getTeamMembers		() const;
	short		getIdTeamMatchsCnfg	() const;	
	MSLString	getCodeReports		() const;
	
	double		getConstRating		() const;	
	MSLString	getConstRatingStr	() const;
	short		getTeamMatchsCnfgMembers() const;
	short		getTeamMatches		() const;
	short		getTeamMatchesElim	() const;
	double		getPointsBye		() const;
	MSLString	getPointsByeStr		() const;
	MSLWString	getTypeEventAsString() const;
	MSLWString	getRegTypeAsString	() const;
	MSLString	getCfgTeamMembers	() const;
	MSLString	getCfgTeamMembersElim() const;
	bool isTeam    () const;

	
	// Help Methods
	CHEvent::TypeRank   getRankOrder(short index) const;
	short				getNumRankOrder() const;
	bool				findRankOrder(CHEvent::TypeRank rankType) const;
	int					getRankPosition(CHEvent::TypeRank rankType);
	bool				getSubMatches() const;

	MSLWString			getTeamCfgSDescription(const char * language=0);
	MSLWString			getTeamCfgLDescription(const char * language=0);

	void				getEventResults(MSLSet &colEventResults);
	CHPhase*			getSwissRound();
	CHTeamMatchsCnfg *	getTeamMatchCfg();

private:
	
	//Atributos
	short	m_typeEvent;	//tipo del evento: individual, dobles triple o cuatro	
	short	m_twoBronces;   //0:no 1:si
			
			
	MSLString m_reqRankOrder; //tipo de ordenacion para los ranking
	short m_idTeamMatchsCnfg;
	double m_constRating;
	double m_pointsBye;
	MSLString m_codeReports;
	
};
