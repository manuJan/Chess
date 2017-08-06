/*************************************************************************************
*			© Copyright MSL Software, S.L., 2012
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: FEODFLoadInscription.cpp
*	Description	:
*
*	Author		: Fernando Martin
*	Date created: 09-Sep-2013
* 	Project		: PManager
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#include "StdAfx.h"
#include "CHManagerDefs.h"
#include "CHODFLoadInscription.h"

#include "..\CHMngtModel\CHInscription.h"
#include "..\CHMngtModel\CHRegister.h"

CHODFLoadInscription::CHODFLoadInscription(GInscription* pInsc, MSLIPCDataTransferModule* module)
:ODFLoadInscription(pInsc, module)
{
}

CHODFLoadInscription::~CHODFLoadInscription()
{
}

void CHODFLoadInscription::onEventEntry(XMLElement * pElEventEntry, bool isTeam)
{
	// Atributos dentro del elemento:
	// Code (M), Type(M), Pos(O), Value(O)
	if (!m_pInscription)
		return;

	CHInscription * pInscription = (CHInscription * )m_pInscription;
		
	CHRegister* pRegister = (CHRegister*) pInscription->getRegister();
	if (!pRegister)
		return;

	MSLString type	= pElEventEntry->getAttributeValue("Type");
	MSLString value= pElEventEntry->getAttributeValue("Value");
	MSLString code = pElEventEntry->getAttributeValue("Code");

	if (code=="MASTER")
	{
		pRegister->setMasterTypeCode( getMasterTypeCode(value) );
	}
	else if (code=="RATING")
	{
		pInscription->setRating( atoi(value.data()) );
	}
	else if (code=="SEED")
	{
		pInscription->setSeed ( atoi(value.data()));
	}
	else if (code=="KCONST")
	{
		pInscription->setKConst( atoi(value.data()) );
	}	
}

void CHODFLoadInscription::onMemberEventEntry(XMLElement * pElEventEntry, GMember* pMember)
{
	CHMember* pPMem = (CHMember*) pMember;

	MSLWString type	= pElEventEntry->getAttributeValue("Type");
	MSLWString value= pElEventEntry->getAttributeValue("Value");
	MSLWString code = pElEventEntry->getAttributeValue("Code");

	

}

short CHODFLoadInscription::getMasterTypeCode(MSLString value)
{
	if(value==CH_GM)
		return CHRegister::mGMaster;		
	else if(value==CH_FM)
		return CHRegister::mFMaster;
	else if(value==CH_IM)
		return CHRegister::mIMaster;
	
	return CHRegister::mNone;
}
