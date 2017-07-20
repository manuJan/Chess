/*************************************************************************************
*			© Copyright MSL Software, S.L., 2014
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHODF2Participant.cpp
*	Description	:
*
*	Author		: Antonio Balmaseda
*	Date created: 18-12-2014
* 	Project		: AR ODF
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#include "StdAfx.h"
#include "CHODF2Defines.h"
#include "CHODF2Participant.h"
#include "CHODFApp.h"
#include "CHODFModel.h"
#include "..\CHMngtModel\CHEvent.h"
#include "..\CHMngtModel\CHInscription.h"
#include "..\CHMngtModel\CHRegister.h"

CHODF2Participant::CHODF2Participant(ODF2BuildBase * pBuild,XMLElement * pElement,ODF2FileBase * pFile,GRegister * pRegister)
:ODF2ZZParticipant(pBuild,pElement,pFile,pRegister)
{
}

CHODF2Participant::~CHODF2Participant()
{
}

void CHODF2Participant::fillSportRegister(XMLElement *pEl_Reg,GRegister * pRegister)
{
	if( !pEl_Reg || !pRegister )
		return;

	pEl_Reg->setAttribute("MainFunctionId",CHODFMODEL->getFunction(pRegister));
}

void CHODF2Participant::fillSportInscription(XMLElement * pEl_RegEvent,GInscription * pInscription)
{
	CHInscription * pCHInscription=(CHInscription *)pInscription;
	CHEvent * pEvent=(CHEvent*)pCHInscription->getEvent();;
	CHRegister * pRegister=(CHRegister*)pCHInscription->getRegister();

	pEl_RegEvent->setAttribute("Bib",pRegister->getBib());

	//E_MASTER
	MSLString masterCode = CHODFMODEL->getMasterType(pRegister);
	addExtension("","EventEntry",pEl_RegEvent,E2_ENTRY,E2_MASTER,0,masterCode,true);

	//E2_RATING
	MSLString rating = pCHInscription->getRatingAsString();
	if (rating.length())
		addExtension("","EventEntry",pEl_RegEvent,E2_ENTRY,E2_RATING,0, rating,true);

	//E2_SEED
	MSLString seed = pCHInscription->getSeedAsString();
	if (seed.length())
		addExtension("","EventEntry",pEl_RegEvent,E2_ENTRY,E2_SEED,0, seed,true);

	//E2_KCOSNT
	MSLString kConst = pCHInscription->getKConstAsString();
	if (kConst.length())
		addExtension("","EventEntry",pEl_RegEvent,E2_ENTRY,E2_KCONST,0, kConst,true);	
}

void CHODF2Participant::fillSportMember(XMLElement * pEl_RegEvent,GMember * pMember)
{
	if (!pMember)
		return;

	pEl_RegEvent->setAttribute("Bib",pMember->getBib());
}