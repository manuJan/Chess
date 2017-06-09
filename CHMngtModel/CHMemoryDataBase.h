/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:ARMemoryDataBase.h
*	Description	:
*
*	Author		: Javier Juste
*	Date created: 9 Junio 2008
* 	Project		: Archery DLL
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#pragma once

#include <OVR/CORE/TH/GTHMemoryDataBase.h>
#include <OVR/CORE/G/GMsgDefines.h>

#include "CHMasterType.h"
#include "CHTeamMatchsCnfg.h"
#include "CHRatingDif.h"

class CHMngtModelExport CHMemoryDataBase : public GTHMemoryDataBase  
{
public:

	//Construction/Destruction
	CHMemoryDataBase();
	virtual ~CHMemoryDataBase();

	//
	// Init / Reset
	//
	void onInit ();
	
	//
	// Objects
	//
	GData *onNew (long isA);

	// find functions (by Key)/////////////////////////
    static CHMasterType  * findMasterType			(short masterType);
	static CHTeamMatchsCnfg * findTeamMatchsCnfg	(short id);
	static CHRatingDif * findRatingDif				(short ratingCode);
			
	// Find Methods
	/*static CHMasterType*		findMasterType(const CHMasterType& aMasterType);	
	static CHMasterType*		findMasterType(short masterType);
	static CHTeamMatchsCnfg*	findTeamMatchsCnfg(CHTeamMatchsCnfg& aTeamMatchsCnfg);
	static CHTeamMatchsCnfg*	findTeamMatchsCnfg(short id);
	static CHTeamMatchsCnfg*	findTeamMatchsCnfg(CHPhase *pPhase);
	static CHTeamMatchsCnfg*	findTeamMatchsCnfg(CHEvent *pEvent);
	static CHRatingDif*			findRatingDif(const CHRatingDif& aRatingDif);	
	static CHRatingDif*			findRatingDif(short ratingCode);*/

	/*static CHMatch				*findMatchSource		(CHMatchResult *pMR);
	static CHPhase				*findPhaseSource		(CHMatchResult *pMR);
	static CHPool				*findPoolSource		    (CHMatchResult *pMR);*/
	
	//virtual functions from GMemoryDataBase
	/*GRegister*				setRegister			(const GRegister			& target);
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
	
	GEventUnit *setEventUnit(const GEventUnit& target);*/

	// remove methods
	/*virtual GTHSplitMatchResult* removeSplitMatchResult (const GTHSplitMatchResult & target);
	virtual CHJudge*			 removeJudge			(const CHJudge& aJudge);
	virtual CHCourt*			 removeCourt			(const CHCourt& target);
	virtual CHMasterType*		 removeMasterType		(const CHMasterType& aMasterType);
	virtual CHTeamMatchsCnfg*	 removeTeamMatchsCnfg	(const CHTeamMatchsCnfg &target);
	virtual CHRatingDif*		 removeRatingDif		(const CHRatingDif& aRatingDif);
	
	bool updateModel(MSLPackObject& aPackObject);
	GData * getObject(RWClassID aClassID,MSLPack &aPack);*/

	static int  findColorStatus(unsigned char status);

	virtual MSLString getRSC(const GData *pData);
	
	//Reports Descriptions (ResultCode)
	//static MSLString	getRSC(const GData *pData);
	//static MSLString getRSC			(GData * pData,bool withoutDiscipline=false,bool extraRSC=true,MSLDate date=INVALID_MSLDate);
	//static MSLString traslateCode	(MSLString sex);
	//static MSLString traslateCode	(GTHEvent *pEvent);
	//static MSLString traslateCode	(GTHPhase * pPhase);
	//static MSLString traslateCode	(CHMatch * pMatch);
	//static MSLString traslateCode	(CHPool * pPool);

/*protected:
    //queries
	GDiscipline * queryDiscipline   (RWDBConnection& aConnection);
	size_t queryColEvents           (MSLSet& target);
	size_t queryColMembers			(MSLSet& target);
	size_t queryColInscriptions     (MSLSet& target);
	size_t queryColEventUnits       (MSLSet& target);
	size_t queryColEUnitNames		(MSLSet& target);
	size_t queryColJudges	        (MSLSet& target);
	size_t queryColPhases           (MSLSet& target);
	size_t queryColPools            (MSLSet& target);
	size_t queryColPoolResults      (MSLSet& target);
	size_t queryColMatchs           (MSLSet& target);
	size_t queryColMatchResults     (MSLSet& target);
	size_t queryColSplitMatchResults(MSLSet& target);
	size_t queryColSplitMatches		(MSLSet& target);
	size_t queryColEventResults		(MSLSet& target);
	size_t queryColMatchJudge		(MSLSet& target);
	size_t queryColSessions			(MSLSet& target);
	size_t queryColMatchMember		(MSLSet& target);
	size_t queryColPhaseNames		(MSLSet& target);
	size_t queryColCourts			(MSLSet& target);
	size_t queryColMasterTypes      (MSLSet& target);
	size_t queryColTeamMatchsCnfg	(MSLSet& target);
	size_t queryColRegisters		(MSLSet& target);
	size_t queryColRatingDifs       (MSLSet& target);

	// desempaquetado de las colecciones hijas...
	void unpackChildCollections		(MSLPack& aPack);
	GDiscipline * unpackDiscipline	(MSLPack& aPack);
	void unpackColEvents			(MSLPack& aPack,MSLSet& target);
	void unpackColInscriptions		(MSLPack& aPack,MSLSet& target);
	void unpackColEventUnits		(MSLPack& aPack,MSLSet& target);
	void unpackColJudges			(MSLPack& aPack,MSLSet& target);
	void unpackColPhases			(MSLPack& aPack,MSLSet& target);
	void unpackColPools				(MSLPack& aPack,MSLSet& target);
	void unpackColPoolResults		(MSLPack& aPack,MSLSet& target);
	void unpackColMatchs			(MSLPack& aPack,MSLSet& target);
	void unpackColMatchResults		(MSLPack& aPack,MSLSet& target);
	void unpackColSplitMatchResults	(MSLPack& aPack,MSLSet& target);
	void unpackColEventResults		(MSLPack& aPack,MSLSet& target);
	void unpackColMatchJudge		(MSLPack& aPack,MSLSet& target);
	void unpackSplitMatches			(MSLPack& aPack,MSLSet& target);
	void unpackColSessions			(MSLPack& aPack,MSLSet& target);
	void unpackColMembers			(MSLPack& aPack,MSLSet& target);
	void unpackColMatchMember		(MSLPack& aPack,MSLSet& target);
	void unpackColPhaseNames		(MSLPack& aPack,MSLSet& target);
	void unpackColCourts			(MSLPack& aPack,MSLSet& target);
	void unpackColMasterTypes		(MSLPack& aPack,MSLSet& target);
	void unpackColTeamMatchsCnfg	(MSLPack& aPack,MSLSet& target);
	void unpackColRegisters			(MSLPack& aPack,MSLSet& target);
	void unpackColRatingDifs		(MSLPack& aPack,MSLSet& target);

protected:
	//reset de las colecciones
	void resetChild();

	void packChildCollections(MSLPack& aPack);

	void queryChildCollections		(RWDBConnection	& aConnection	);	
	void unionChildCollections		(RWHashTable	& sSource		);

private:
	static MSLSet colTeamMatchsCnfg;		// CHTeamMatchsCnfg's collection
	static MSLSet colJudges;				// CHJudge
	static MSLSet colMasterTypes;		// CHMasterType
	static MSLSet colRatingDifs;			// CHRatingDif*/
};

