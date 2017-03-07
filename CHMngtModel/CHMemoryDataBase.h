/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHMemoryDataBase.h                                                                 
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:12-12-2005
*   Project     :CH Model                  
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///

#if !defined(AFX_CHMEMORYDATABASE_H__3A0F8BE0_F95B_4F9E_B0C4_AC10ECFE00AE__INCLUDED_)
#define AFX_CHMEMORYDATABASE_H__3A0F8BE0_F95B_4F9E_B0C4_AC10ECFE00AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHMNGTMODELDLL_H
#   include "CHMngtModelDll.h" 
#endif // _CH_MNGTMODELDLL_H

#include <core/THSP/THSPMemoryDataBase.h>
#include "CHSportDefines.h"


#include "CHEvent.h"
#include "CHEventResult.h"
#include "CHMatchResult.h"
#include "CHPhase.h"
#include "CHJudge.h"
#include "CHSession.h"
#include "CHMember.h"
#include "CHMatchMember.h"
#include "CHInscription.h"
#include "CHMatch.h"
#include "CHSplitMatchResult.h"
#include "CHPool.h"
#include "CHPoolResult.h"
#include "CHPhaseBase.h"
#include "CHSplitMatch.h"
#include "CHCourt.h"
#include "CHMasterType.h"
#include "CHTeamMatchsCnfg.h"
#include "CHRatingDif.h"



extern "C" __declspec( dllexport ) GMemoryDataBase * fnGetMemory();
extern "C" __declspec( dllexport ) long fnGetCollection(GMemoryDataBase *pMem,long id,RWSet &set);


class CHModelExport CHMemoryDataBase : public THSPMemoryDataBase  
{
public:
		enum SportStatus {	eAvailable=10,
							eConfigured=20,
							eSchedulled=30,
							eStartList=40,
							eRunning=50,
							eSuspend=60,
							eUnofficial=100,
							eFinished=110,	
							eProtested=120   };
public:

	//Construction/Destruction
	CHMemoryDataBase();
	virtual ~CHMemoryDataBase();


	// Collections
	inline static RWSet&	getColJudges()
		{ return colJudges; }
	inline static RWSet&	getColMasterTypes()
		{ return colMasterTypes; }
	inline static RWSet& getColTeamMatchsCnfg()
	{ return colTeamMatchsCnfg; }
	inline static RWSet&	getColRatingDifs()
		{ return colRatingDifs; }

			

	// Find Methods
	static CHJudge*				findJudge(const CHJudge& aJudge);	
	static CHJudge*				findJudge(GRegister* pRegister,GFunction * pFunction);
	static CHMasterType*		findMasterType(const CHMasterType& aMasterType);	
	static CHMasterType*		findMasterType(short masterType);
	static CHTeamMatchsCnfg*	findTeamMatchsCnfg(CHTeamMatchsCnfg& aTeamMatchsCnfg);
	static CHTeamMatchsCnfg*	findTeamMatchsCnfg(short id);
	static CHTeamMatchsCnfg*	findTeamMatchsCnfg(CHPhase *pPhase);
	static CHTeamMatchsCnfg*	findTeamMatchsCnfg(CHEvent *pEvent);
	static CHRatingDif*			findRatingDif(const CHRatingDif& aRatingDif);	
	static CHRatingDif*			findRatingDif(short ratingCode);

	
	static CHMatch				*findMatchSource		(CHMatchResult *pMR);
	static CHPhase				*findPhaseSource		(CHMatchResult *pMR);
	static CHPool				*findPoolSource		    (CHMatchResult *pMR);
	
	//virtual functions from GMemoryDataBase
	GRegister*				setRegister			(const GRegister			& target);
	GInscription*			setInscription		(const GInscription			& target);
	GEvent*					setEvent			(const GEvent				& target);
	GPhase*					setPhase			(const GPhase				& target);
	GMember*				setMember			(const GMember				& target);
	GTHEventResult*			setEventResult		(const GTHEventResult		& target);
	GTHPool*				setPool				(const GTHPool				& target);
	GTHMatch*				setMatch			(const GTHMatch				& target);
	GTHPoolResult*			setPoolResult		(const GTHPoolResult		& target);
	GTHMatchResult*			setMatchResult		(const GTHMatchResult		& target);
	GTHSplitMatch*			setSplitMatch		(const GTHSplitMatch		& target);
	GTHSplitMatchResult*	setSplitMatchResult	(const GTHSplitMatchResult	& target);
	CHJudge*				setJudge			(const CHJudge				& target);
	GTHMatchJudge*			setMatchJudge		(const GTHMatchJudge		& target);
	GTHSession*				setSession			(const GTHSession			& target);
	GTHMatchMember*			setMatchMember		(const GTHMatchMember		& target);
	GCourt*					setCourt			(const GCourt				& target);
	CHMasterType*			setMasterType		(const CHMasterType			& target);
	CHTeamMatchsCnfg*		setTeamMatchsCnfg	(const CHTeamMatchsCnfg		& target);
	CHRatingDif*			setRatingDif		(const CHRatingDif			& target);
	
	
	GEventUnit *setEventUnit(const GEventUnit& target);

	// remove methods
	virtual GTHSplitMatchResult* removeSplitMatchResult (const GTHSplitMatchResult & target);
	virtual CHJudge*			 removeJudge			(const CHJudge& aJudge);
	virtual CHCourt*			 removeCourt			(const CHCourt& target);
	virtual CHMasterType*		 removeMasterType		(const CHMasterType& aMasterType);
	virtual CHTeamMatchsCnfg*	 removeTeamMatchsCnfg	(const CHTeamMatchsCnfg &target);
	virtual CHRatingDif*		 removeRatingDif		(const CHRatingDif& aRatingDif);
	
	RWBoolean updateModel(CPackObject& aPackObject);
	GData * getObject(RWClassID aClassID,CPack &aPack);

	static int  findColorStatus(unsigned char status);

	
	//Reports Descriptions (ResultCode)
	static RWCString	getRSC(const GData *pData);
	static RWCString getRSC			(GData * pData,RWBoolean withoutDiscipline=false,RWBoolean extraRSC=true,RWDate date=INVALID_RWDATE);
	static RWCString traslateCode	(RWCString sex);
	static RWCString traslateCode	(GTHEvent *pEvent);
	static RWCString traslateCode	(GTHPhase * pPhase);
	static RWCString traslateCode	(CHMatch * pMatch);
	static RWCString traslateCode	(CHPool * pPool);

protected:
    //queries
	GDiscipline * queryDiscipline   (RWDBConnection& aConnection);
	size_t queryColEvents           (RWDBConnection& aConnection,RWSet& target);
	size_t queryColMembers			(RWDBConnection& aConnection,RWSet& target);
	size_t queryColInscriptions     (RWDBConnection& aConnection,RWSet& target);
	size_t queryColEventUnits       (RWDBConnection& aConnection,RWSet& target);
	size_t queryColEUnitNames		(RWDBConnection& aConnection,RWSet& target);
	size_t queryColJudges	        (RWDBConnection& aConnection,RWSet& target);
	size_t queryColPhases           (RWDBConnection& aConnection,RWSet& target);
	size_t queryColPools            (RWDBConnection& aConnection,RWSet& target);
	size_t queryColPoolResults      (RWDBConnection& aConnection,RWSet& target);
	size_t queryColMatchs           (RWDBConnection& aConnection,RWSet& target);
	size_t queryColMatchResults     (RWDBConnection& aConnection,RWSet& target);
	size_t queryColSplitMatchResults(RWDBConnection& aConnection,RWSet& target);
	size_t queryColSplitMatches		(RWDBConnection& aConnection,RWSet& target);
	size_t queryColEventResults		(RWDBConnection& aConnection,RWSet& target);
	size_t queryColMatchJudge		(RWDBConnection& aConnection,RWSet& target);
	size_t queryColSessions			(RWDBConnection& aConnection,RWSet& target);
	size_t queryColMatchMember		(RWDBConnection& aConnection,RWSet& target);
	size_t queryColPhaseNames		(RWDBConnection& aConnection,RWSet& target);
	size_t queryColCourts			(RWDBConnection& aConnection,RWSet& target);
	size_t queryColMasterTypes      (RWDBConnection& aConnection,RWSet& target);
	size_t queryColTeamMatchsCnfg	(RWDBConnection& aConnection,RWSet& target);
	size_t queryColRegisters		(RWDBConnection& aConnection,RWSet& target);
	size_t queryColRatingDifs       (RWDBConnection& aConnection,RWSet& target);

	// desempaquetado de las colecciones hijas...
	void unpackChildCollections		(CPack& aPack);
	GDiscipline * unpackDiscipline	(CPack& aPack);
	void unpackColEvents			(CPack& aPack,RWSet& target);
	void unpackColInscriptions		(CPack& aPack,RWSet& target);
	void unpackColEventUnits		(CPack& aPack,RWSet& target);
	void unpackColJudges			(CPack& aPack,RWSet& target);
	void unpackColPhases			(CPack& aPack,RWSet& target);
	void unpackColPools				(CPack& aPack,RWSet& target);
	void unpackColPoolResults		(CPack& aPack,RWSet& target);
	void unpackColMatchs			(CPack& aPack,RWSet& target);
	void unpackColMatchResults		(CPack& aPack,RWSet& target);
	void unpackColSplitMatchResults	(CPack& aPack,RWSet& target);
	void unpackColEventResults		(CPack& aPack,RWSet& target);
	void unpackColMatchJudge		(CPack& aPack,RWSet& target);
	void unpackSplitMatches			(CPack& aPack,RWSet& target);
	void unpackColSessions			(CPack& aPack,RWSet& target);
	void unpackColMembers			(CPack& aPack,RWSet& target);
	void unpackColMatchMember		(CPack& aPack,RWSet& target);
	void unpackColPhaseNames		(CPack& aPack,RWSet& target);
	void unpackColCourts			(CPack& aPack,RWSet& target);
	void unpackColMasterTypes		(CPack& aPack,RWSet& target);
	void unpackColTeamMatchsCnfg	(CPack& aPack,RWSet& target);
	void unpackColRegisters			(CPack& aPack,RWSet& target);
	void unpackColRatingDifs		(CPack& aPack,RWSet& target);

protected:
	//reset de las colecciones
	void resetChild();

	void packChildCollections(CPack& aPack);

	void queryChildCollections		(RWDBConnection	& aConnection	);	
	void unionChildCollections		(RWHashTable	& sSource		);

private:
	static RWSet colTeamMatchsCnfg;		// CHTeamMatchsCnfg's collection
	static RWSet colJudges;				// CHJudge
	static RWSet colMasterTypes;		// CHMasterType
	static RWSet colRatingDifs;			// CHRatingDif
};

#endif // !defined(AFX_CHMEMORYDATABASE_H__3A0F8BE0_F95B_4F9E_B0C4_AC10ECFE00AE__INCLUDED_)


