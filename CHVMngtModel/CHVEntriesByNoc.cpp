/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHVEntriesByNoc.h
*	Description	:Export Dll
*
*	Author		:Chess Team
*	Date created:19-12-2005
* 	Project		:Entries By Noc View
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdVCH.h"
#include "CHVEntriesByNoc.h"
#include "CHViewsIDs.h"
#include <Reports/V/OrderView.h>
#include <Sports/CH/Data/CHRegister.h>
#include <Sports/CH/Data/CHInscription.h>
#include <Sports/CH/Data/CHEvent.h>
#include <Sports/CH/Data/CHMember.h>

/////////////////////////////////////////////////////////////////////
static int orderInscriptionsByEvent1(const GVectorElement** a, const GVectorElement** b)
{
	CHInscription *pInscriptionA = (CHInscription *)(*a)->getElement();
	CHInscription *pInscriptionB = (CHInscription *)(*b)->getElement();

	int rc = strcmp(pInscriptionA->getEvent()->getEvent(),pInscriptionB->getEvent()->getEvent());
	if( rc )
		return rc;

	CHRegister *pRegisterA = (CHRegister *)pInscriptionA->getRegister();
	CHRegister *pRegisterB = (CHRegister *)pInscriptionB->getRegister();

	rc = wcsicoll(pRegisterA->getPrnLName(),pRegisterB->getPrnLName());
	if( rc )
		return rc; 
	else
		return strcmp(pRegisterA->getKey(),pRegisterB->getKey());
}

/////////////////////////////////////////////////////////////////////
static int orderRegisterBySexPrnSName(const GVectorElement** a, const GVectorElement** b)
{
	GRegister * pRegA=(GRegister *)(*a)->getElement();
	GRegister * pRegB=(GRegister *)(*b)->getElement();
	
	int rc = strcmp(pRegA->getSex(),pRegB->getSex());
	if( rc )
		return rc;
		
	rc = wcsicoll(pRegA->getPrnSName(),pRegB->getPrnSName());
	return ((rc) ? rc:pRegA->getRegister()-pRegB->getRegister());
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHVEntriesByNoc::CHVEntriesByNoc()
:CReportView(CHVENTRYBYNOC_DEEP)
{
	build();
}

void CHVEntriesByNoc::build()
{
	m_Vector.sort(orderGroups);		// Por claves:importante para la construcción

	RWSet& colInscriptions=CHMemoryDataBase::getColInscriptions();
	RWSetIterator it(colInscriptions);

	CHInscription *pInscription=0;

	while( (pInscription=(CHInscription *)it() )!=0 )
	{
		if(((CHEvent*)pInscription->getEvent())->isTeam())
		{
			CHMember* pMember=0;
			for (size_t i=0;i<pInscription->getMembersVector().entries();i++)
			{
				pMember=(CHMember*)pInscription->getMembersVector()[i]->getElement();
				insertRegister(pMember->getRegister(),pMember->getRegister()->getGroup());
			}
		}
		else
		{
			insertRegister(pInscription->getRegister(),pInscription->getRegister()->getGroup());
		}
	}
}

GVectorElement* CHVEntriesByNoc::insertRegister(GRegister *pRegister,const char *group)
{
	GVectorElement *pElement=insertGroup(group);
	if( pElement )
	{
		GVectorElement * pRegElement=pElement->getVector().find(pRegister);
		if( !pRegElement )
			return pElement->getVector().insert(pRegister,orderInscriptionsByEvent1);
		return pRegElement;
	}

	return 0;
}

GVectorElement* CHVEntriesByNoc::insertGroup(const char *group)
{
	GGroup aGroup,*pGroup=0;
	aGroup.setGroup(group);

	GVectorElement *pElement=m_Vector.find(&aGroup);
	if( !pElement )
	{
		pGroup=CHMemoryDataBase::findGroup(aGroup);
		if( pGroup )
			return m_Vector.insert(pGroup,orderRegisterBySexPrnSName);
		return 0;
	}

	return pElement;
}

void CHVEntriesByNoc::rebuild()
{
	m_Vector.clearAndDestroy();
	build();
}

RWCString CHVEntriesByNoc::getDescription() const
{
	return CHVENTRYBYNOC_DESC;
}

int CHVEntriesByNoc::getID() const
{
	return CHVENTRYBYNOC;
}
