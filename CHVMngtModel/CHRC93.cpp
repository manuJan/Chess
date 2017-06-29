/*************************************************************************************
*			© Copyright MSL Software, S.L., 2008
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHRC93.cpp
*	Description	:
*
*	Author		: M.
*	Date created: 19-10-2009
* 	Project		: AR(V) Dll
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdafx.h"
#include "CHRC93.h"
#include "..\CHMngtModel\CHMember.h"

static 
int sortC93WC(const MSLItem** a,const MSLItem** b)
{
	GMedallist *pA = (GMedallist*)(*a);
	GMedallist *pB = (GMedallist*)(*b);

	GEvent	*pEA = pA->getEvent(),
			*pEB = pB->getEvent();

	int rc = pEA->getOrder()-pEB->getOrder();
	if( !rc )
		rc = pEA - pEB;
	
	if( !rc )
	{
		GMedal	*pMA = pA->getMedal(),
				*pMB = pB->getMedal();

		rc = pMA->getMedal()-pMB->getMedal();
	}
		
	return rc;
}

static int orderMembers(const MSLItem** a, const MSLItem** b)
{
	CHMember *pA=(CHMember *)(*a);
	CHMember *pB=(CHMember *)(*b);

	int order = _wcsicoll(pA->getPrnLName(),pB->getPrnLName());
	if( order )
		return order;

	return strcmp(pA->getKey(),pB->getKey());
}

CHRC93::CHRC93(CReportManager& aRM,CReportConfig& aRC)
:RC93(aRM,aRC)
{
}

CHRC93::~CHRC93(void)
{
}

void CHRC93::OnLisLoaded()
{
	m_pC93Lis->setData(111, getUserLabel(630) );
}

void CHRC93::OnSortMedallist()
{
	m_vector.setFcCompare(sortC93WC);
}

void CHRC93::OnGetMembers()
{
	GInscription * pIns = GMemoryDataBase::findInscription(m_pCurrent->getRegister(),m_pCurrent->getEvent());
	if( pIns )
	{
		MSLSortedVector vMembers;
		pIns->getMembersVector(vMembers,orderMembers);
		CHMember * pM = 0;
		for( long i=0;i<vMembers.entries();i++ )
		{
			pM = (CHMember *)vMembers[i];
			MSLWString data = pM->getPrnLName();
			m_vMembers.insert( new MSLWString(data) );			
		}
	}
}
