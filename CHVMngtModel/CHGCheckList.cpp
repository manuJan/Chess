/*************************************************************************************
*			© Copyright MSL Software, S.L., 2000 - 2008
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHGCheckList.h
*	Description	: Implementation for the CHGCheckList class.
*
*	Author		: Jose Matas
*	Date created: 21 Enero 2009
* 	Project		: BKVMngtModel
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdafx.h"
#include "CHGCheckList.h"
#include "..\CHMngtModel\CHRegister.h"
#include "..\CHMngtModel\CHInscription.h"
#include "..\CHMngtModel\CHEvent.h"

static bool selectInscriptions(const MSLItem* p,const void *n)
{
	CHInscription *pInsc = (CHInscription *)p;	
	if( !pInsc )
		return false;

	CHRegister * pReg = (CHRegister*)n;

	if( pReg && 
		pInsc->getRegisterKey() == pReg->getKey() )
		return true;

	return false;
	UNREFERENCED_PARAMETER(n);
}

static int orderInscriptionsByEventOrder(const MSLItem** a, const MSLItem** b)
{
	CHInscription *pInscriptionA=(CHInscription*)(*a);
	CHInscription *pInscriptionB=(CHInscription*)(*b);

	CHEvent * pEventA=(CHEvent *)pInscriptionA->getEvent();
	CHEvent * pEventB=(CHEvent *)pInscriptionB->getEvent();

	return (pEventA->getOrder() - pEventB->getOrder());
}

/////////////////////////////////////////////////////////////////////
// Constructor/Destructor
/////////////////////////////////////////////////////////////////////
CHGCheckList::CHGCheckList()
:GCheckList()
,m_masterType(NULLWSTRING)
,m_events(NULLWSTRING)
{
	m_bExtended = true;
}

CHGCheckList::~CHGCheckList()
{

}

void CHGCheckList::setRegister(CHRegister *pReg, const char * language/*=0*/)
{

	if (!pReg)
		return;

	m_masterType = pReg->getMasterTypeLDescription();
	m_events=NULLWSTRING;
	MSLSet colInscriptions = CHMemoryDataBase::getCol(__CHINSCRIPTION).select(selectInscriptions, pReg);
	MSLSortedVector vInscriptions =	MSLSortedVector(colInscriptions, orderInscriptionsByEventOrder);
	for (short i=0;i<vInscriptions.entries();i++)
	{
		CHInscription* pIns = (CHInscription*) vInscriptions[i];
		CHEvent *pEvent=(CHEvent*)pIns->getEvent();
		m_events+=pEvent->getSDescription(language);
		m_events+=((vInscriptions.entries()>1 && i+1<vInscriptions.entries())?", ":" ");
	}

	GCheckList::setRegister(pReg);

	setSortCad();

}



/////////////////////////////////////////////////////////////////////
// Get Methods
/////////////////////////////////////////////////////////////////////
MSLWString CHGCheckList::getMasterType() const
{
	return m_masterType;	
}

MSLWString CHGCheckList::getEvents() const
{
	return m_events;	
}

/////////////////////////////////////////////////////////////////////
// Class Methods
/////////////////////////////////////////////////////////////////////
void CHGCheckList::setSortCad()
{
	m_sortCad=NULLWSTRING;
	if ( m_pRegister )
	{
		MSLWString sCad;
		sCad.format(L"%3.3s%s%2d%s%s",	
					MSLWString(m_pRegister->getGroup()).data(),
					MSLWString(m_pRegister->getSex()).data(),
					int(m_pRegister->getType()),
					m_pRegister->getName2().data(),
					m_pRegister->getName1().data());
		m_sortCad=sCad;
	}
}

