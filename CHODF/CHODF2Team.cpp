/*************************************************************************************
*			© Copyright MSL Software, S.L., 2014
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHODF2Team.cpp
*	Description	:
*
*	Author		: 
*	Date created: 
* 	Project		: AR ODF
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "StdAfx.h"
#include "CHODF2Team.h"
#include "CHODFApp.h"
#include "CHODFModel.h"
#include "CHODF2Defines.h"
#include "..\CHMngtModel\CHInscription.h"

CHODF2Team::CHODF2Team(ODF2BuildBase * pBuild,XMLElement * pElement,ODF2FileBase * pFile,GRegister * pRegister)
:ODF2THZZTeam/*ODF2ZZTeam*/(pBuild,pElement,pFile,pRegister)
{
}

CHODF2Team::~CHODF2Team(void)
{
}

void CHODF2Team::fillEventEntry(XMLElement * pEl_RegEvent,GData * pCompetitor)
{
	if (pCompetitor && pCompetitor->isA()==__GTHINSCRIPTION)
	{
		CHInscription* pCHInscription = (CHInscription*)pCompetitor;

		//E_RATING
		MSLString rating=pCHInscription->getRatingAsString();
		if (rating)
			addExtension("","EventEntry",pEl_RegEvent,E2_ENTRY,E2_RATING,0,rating,true);

		//E2_SEED
		MSLString seed = pCHInscription->getSeedAsString();
		if (seed.length())
			addExtension("","EventEntry",pEl_RegEvent,E2_ENTRY,E2_SEED,0, seed,true);

		//E2_KCOSNT
		MSLString kConst = pCHInscription->getKConstAsString();
		if (kConst.length())
			addExtension("","EventEntry",pEl_RegEvent,E2_ENTRY,E2_KCONST,0, kConst,true);	
	}

	ODF2ZZTeam::fillEventEntry(pEl_RegEvent,pCompetitor);
}


