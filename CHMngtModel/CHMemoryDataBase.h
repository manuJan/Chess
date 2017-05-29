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
	//static MSLString getRSC			(GData * pData,bool withoutDiscipline=false,bool extraRSC=true,RWDate date=INVALID_RWDATE);
	//static MSLString traslateCode	(MSLString sex);
	//static MSLString traslateCode	(GTHEvent *pEvent);
	//static MSLString traslateCode	(GTHPhase * pPhase);
	//static MSLString traslateCode	(CHMatch * pMatch);
	//static MSLString traslateCode	(CHPool * pPool);

/*protected:
    //queries
	GDiscipline * queryDiscipline   (RWDBConnection& aConnection);
	size_t queryColEvents           (RWSet& target);
	size_t queryColMembers			(RWSet& target);
	size_t queryColInscriptions     (RWSet& target);
	size_t queryColEventUnits       (RWSet& target);
	size_t queryColEUnitNames		(RWSet& target);
	size_t queryColJudges	        (RWSet& target);
	size_t queryColPhases           (RWSet& target);
	size_t queryColPools            (RWSet& target);
	size_t queryColPoolResults      (RWSet& target);
	size_t queryColMatchs           (RWSet& target);
	size_t queryColMatchResults     (RWSet& target);
	size_t queryColSplitMatchResults(RWSet& target);
	size_t queryColSplitMatches		(RWSet& target);
	size_t queryColEventResults		(RWSet& target);
	size_t queryColMatchJudge		(RWSet& target);
	size_t queryColSessions			(RWSet& target);
	size_t queryColMatchMember		(RWSet& target);
	size_t queryColPhaseNames		(RWSet& target);
	size_t queryColCourts			(RWSet& target);
	size_t queryColMasterTypes      (RWSet& target);
	size_t queryColTeamMatchsCnfg	(RWSet& target);
	size_t queryColRegisters		(RWSet& target);
	size_t queryColRatingDifs       (RWSet& target);

	// desempaquetado de las colecciones hijas...
	void unpackChildCollections		(MSLPack& aPack);
	GDiscipline * unpackDiscipline	(MSLPack& aPack);
	void unpackColEvents			(MSLPack& aPack,RWSet& target);
	void unpackColInscriptions		(MSLPack& aPack,RWSet& target);
	void unpackColEventUnits		(MSLPack& aPack,RWSet& target);
	void unpackColJudges			(MSLPack& aPack,RWSet& target);
	void unpackColPhases			(MSLPack& aPack,RWSet& target);
	void unpackColPools				(MSLPack& aPack,RWSet& target);
	void unpackColPoolResults		(MSLPack& aPack,RWSet& target);
	void unpackColMatchs			(MSLPack& aPack,RWSet& target);
	void unpackColMatchResults		(MSLPack& aPack,RWSet& target);
	void unpackColSplitMatchResults	(MSLPack& aPack,RWSet& target);
	void unpackColEventResults		(MSLPack& aPack,RWSet& target);
	void unpackColMatchJudge		(MSLPack& aPack,RWSet& target);
	void unpackSplitMatches			(MSLPack& aPack,RWSet& target);
	void unpackColSessions			(MSLPack& aPack,RWSet& target);
	void unpackColMembers			(MSLPack& aPack,RWSet& target);
	void unpackColMatchMember		(MSLPack& aPack,RWSet& target);
	void unpackColPhaseNames		(MSLPack& aPack,RWSet& target);
	void unpackColCourts			(MSLPack& aPack,RWSet& target);
	void unpackColMasterTypes		(MSLPack& aPack,RWSet& target);
	void unpackColTeamMatchsCnfg	(MSLPack& aPack,RWSet& target);
	void unpackColRegisters			(MSLPack& aPack,RWSet& target);
	void unpackColRatingDifs		(MSLPack& aPack,RWSet& target);

protected:
	//reset de las colecciones
	void resetChild();

	void packChildCollections(MSLPack& aPack);

	void queryChildCollections		(RWDBConnection	& aConnection	);	
	void unionChildCollections		(RWHashTable	& sSource		);

private:
	static RWSet colTeamMatchsCnfg;		// CHTeamMatchsCnfg's collection
	static RWSet colJudges;				// CHJudge
	static RWSet colMasterTypes;		// CHMasterType
	static RWSet colRatingDifs;			// CHRatingDif*/
};

