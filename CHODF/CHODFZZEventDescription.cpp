/*************************************************************************************
*			© Copyright MSL Software, S.L., 2012
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHODFZZEventDescription.cpp
*	Description	:
*
*	Author		: 
*	Date created: 19-11-2013
* 	Project		: Archery ODF
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#include "StdAfx.h"
#include "CHODFZZEventDescription.h"
#include "CHODFApp.h"
#include "CHODFModel.h"
#include "..\CHMngtModel\CHEvent.h"

static int orderEvents(const MSLItem** a, const MSLItem** b)
{
	CHEvent * pA=(CHEvent*)(*a);
	CHEvent * pB=(CHEvent*)(*b);

	int order = strcmp(pA->getSex(),pB->getSex());
	if( order ) return order;

	order = pA->getOrder() - pB->getOrder();
	return order ? order :strcmp(pA->getKey(),pB->getKey());
}

CHODFZZEventDescription::CHODFZZEventDescription(ODF2BuildBase * pBuild,XMLElement * pElement,ODF2FileBase * pFile)
:ODFZZItem(pBuild,pElement,pFile)
,m_pEntDiscipline(0)
,m_pEntGender(0)
,m_pEntEvent(0)
,m_pEntEventDescription(0){
}

CHODFZZEventDescription::~CHODFZZEventDescription()
{
}

void CHODFZZEventDescription::loadEntities()
{
	m_pEntDiscipline		= (XMLEntity *)m_pBuild->findEntity("Discipline");
	m_pEntGender			= (XMLEntity *)m_pBuild->findEntity("Gender");
	m_pEntEvent				= (XMLEntity *)m_pBuild->findEntity("Event");
	m_pEntEventDescription	= (XMLEntity *)m_pBuild->findEntity("EventDescription");
}

bool CHODFZZEventDescription::run()
{
	if( !m_pElement || !m_pFile )
		return false;

	loadEntities();

	XMLElement * pEl_Discipline = m_pElement->setElement(m_pEntDiscipline);
	if( !pEl_Discipline )
		return false;

	pEl_Discipline->setAttribute("Code",((CHODFApp*)MSLAPP)->getDisciplineCode());

	int eventOrder=0;
	MSLString sex;
	CHEvent * pEvent = 0;
	GLanguage * pLang = 0;
	XMLElement * pEl_Gender = 0;
	XMLElement * pEl_Event = 0;
	XMLElement * pEl_EventDescription = 0;
	MSLSortedVector vEvents(CHMemoryDataBase::getCol(__CHEVENT),orderEvents);
	for(int i=0 ; i<vEvents.entries() ; i++)
	{
		pEvent = (CHEvent *)vEvents[i];
		if( !pEvent || !pEvent->isEnable() )
			continue;

		if( pEvent->getSex() != sex )
		{
			pEl_Gender = pEl_Discipline->setElement(m_pEntGender);
			if( pEl_Gender )
				pEl_Gender->setAttribute("Code", pEvent->getSex());
		}

		pEl_Event = pEl_Gender ? pEl_Gender->setElement(m_pEntEvent) : 0;
		if( !pEl_Event )
			continue;

		pEl_Event->setAttribute("Code", CHODFMODEL->getRSCCodeEvent(pEvent));
		pEl_Event->setAttribute("TeamEvent", pEvent->getRegType()==GRegister::team ? "Y" : "N");
		pEl_Event->setAttribute("OrderId", ++eventOrder /*pEvent->getOrder()*/);

		MSLSetIterator it(GMemoryDataBase::getCol(__GLANGUAGE));		
		while( (pLang=(GLanguage *)it())!=0 )
		{
			if( pLang->getActiveFlag() == 0 )
				continue;

			pEl_EventDescription = pEl_Event->setElement(m_pEntEventDescription);
			if( !pEl_EventDescription )
				continue;

			pEl_EventDescription->setAttribute("Lang", pLang->get());
			pEl_EventDescription->setAttribute("Description",  pEvent->getSDescription(pLang->get()));
			pEl_EventDescription->setAttribute("LDescription", pEvent->getLDescription(pLang->get()));
		}
	}
	return true;
}
