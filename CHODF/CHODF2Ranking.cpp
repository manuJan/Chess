/*************************************************************************************
*			© Copyright MSL Software, S.L., 2014
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHODF2Ranking.cpp
*	Description	:
*
*	Author		: 
*	Date created: 26-01-2015
* 	Project		: AR ODF
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#include "StdAfx.h"
#include "CHODF2Ranking.h"
#include "CHODFModel.h"

#include "..\CHMngtModel\CHInscription.h"
#include "..\CHMngtModel\CHMember.h"

CHODF2Ranking::CHODF2Ranking(ODF2BuildBase * pBuild,XMLElement * pElement,ODF2FileBase * pFile,GData * pData)
	:ODF2ZZRanking(pBuild,pElement,pFile,pData)
{
}

CHODF2Ranking::~CHODF2Ranking()
{
}

void CHODF2Ranking::fillSportAthlete(MSLItem * pAthlete,XMLElement * pEl_Athlete)
{
	GData* pData=(GData*)pAthlete;
	if (!pData)
		return;
	
	if (pData->isA()==__CHMEMBER)
	{
		CHMember* pMember = (CHMember*)pData;
		GRegister * pRegister=pMember->getRegister();
		if(!pRegister)
			return;

		pEl_Athlete->setAttribute("Code",pRegister->getAcreditation());
		pEl_Athlete->setAttribute("Order",pMember->getOrder());
	}

	if (pData->isA()==__CHINSCRIPTION)
	{
		CHInscription* pInscription = (CHInscription*)pData;
		GRegister * pRegister=pInscription->getRegister();
		if(!pRegister)
			return;

		pEl_Athlete->setAttribute("Code",pRegister->getAcreditation());
		pEl_Athlete->setAttribute("Order",1);
	}
}

void CHODF2Ranking::fillDescription(MSLItem * pCompetitor,XMLElement *pEl_Competitor)
{
	if( !pCompetitor || !pEl_Competitor )
		return;
		
	GEvent * pEvent = CHODFMODEL->getEvent(pCompetitor);
	if( !pEvent )
		return;
	GRegister * pRegister = CHODFMODEL->getRegister(pCompetitor);
	if( !pRegister )
		return;

	bool isTeam = pRegister->getType()==GRegister::individual?false:true;
		
	if( (pEl_Competitor->getLabel()=="Competitor" && isTeam)	|| 
		(pEl_Competitor->getLabel()=="Athlete" && !isTeam))
	{
		XMLElement *pEl_Description = pEl_Competitor->setElement(m_pEntDescription);
		if( !pEl_Description )
			return;

		if(pEl_Competitor->getLabel()=="Competitor")
		{
			if(isTeam)
			{
				pEl_Description->setAttribute("TeamName",pRegister->getPrnLName());
	//			pEl_Description->setAttribute("IFId",pRegister->getIFNumber());
			}
		}
		else /*if(pEl_Competitor->getLabel()=="Athlete")*/
		{
			pEl_Description->setAttribute("GivenName",pRegister->getName1());
			pEl_Description->setAttribute("FamilyName",pRegister->getName2());
			pEl_Description->setAttribute("Gender",pRegister->getSex());
			pEl_Description->setAttribute("Organisation",pRegister->getOrgID());
//			pEl_Description->setAttribute("IFId",pRegister->getIFNumber());
			MSLString dob = pRegister->getBirthDate("%Y-%m-%d");
			pEl_Description->setAttribute("BirthDate",dob);
		}
	}
}

void CHODF2Ranking::fillVectorComposition(MSLItem * pCompetitor,MSLArray& vComposition)
{
	if(!pCompetitor)
		return;

	GEventResult * pEventResult = (GEventResult *)pCompetitor;
	GInscription * pInsc = (GInscription*)pEventResult->getInscription();
	GRegister * pReg = (GRegister *)pInsc->getRegister();
	GMember * pMember = 0;

	if(pReg->getType()==GRegister::individual)
		vComposition.insert(pInsc);
	else
	{
		MSLSortedVector vMembers;
		pInsc->getMembersVector(vMembers,getVectorCompositionCompare());
		for (long i=0;i<vMembers.entries();i++)
		{
			pMember = (GMember*)vMembers[i];
			if (isSelectable(pMember,eMember))
				vComposition.insert(pMember);
		}
	}
}