/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHRC32C.h
*	Description	:Export Dll
*
*	Author		:Chess Team
*	Date created:20-12-2005
* 	Project		:Entry List By Event Report
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdVCH.h"
#include "CHRC32C.h"

#include <Sports/CH/Data/CHDiscipline.h>
#include <Sports/CH/Data/CHEvent.h>
#include <Sports/CH/Data/CHInscription.h>
#include <Sports/CH/Data/CHMember.h>
#include <Sports/CH/Data/CHRegister.h>

//////////////////////////////////////////////////////////////////////
static int orderEventByOrder(const GVectorElement** a, const GVectorElement** b)
{
	CHEvent *pEventA = (CHEvent *)(*a)->getElement();
	CHEvent *pEventB = (CHEvent *)(*b)->getElement();
	
	return pEventA->getOrderEvent() - pEventB->getOrderEvent();
}

//////////////////////////////////////////////////////////////////////
static int orderInscriptionsByGroup(const GVectorElement** a, const GVectorElement** b)
{
	CHInscription *pInscA = (CHInscription *)(*a)->getElement();
	CHInscription *pInscB = (CHInscription *)(*b)->getElement();
	
	CHRegister *pRegA = (CHRegister *)pInscA->getRegister();
	CHRegister *pRegB = (CHRegister *)pInscB->getRegister();
	
	int rc = 0;
	
	rc = strcmp(pRegA->getGroup(),pRegB->getGroup());
	if( rc )
		return rc; 

	rc = wcsicoll(pRegA->getPrnLName(),pRegB->getPrnLName());
	if( rc )
		return rc; 

	

	return strcmp(pRegA->getKey(),pRegB->getKey());
	
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHRC32C::CHRC32C(CReportManager& aReportManager,CReportConfig& aReportConfig)
:CHReportTemplate(aReportManager,aReportConfig)
,pReportMng(&aReportManager)
,pLis(0)
,isTeam(false)
,totalEntries(0)
,pEvent(0)
,lastEvent(NULLRWSTRING)
,isFirstEvent(true)
{ 
	aV04Inscription.sort(0,orderEventByOrder);
	aV04Inscription.sort(1,orderInscriptionsByGroup);
}

CHRC32C::CHRC32C(CReportManager& aReportManager,CReportConfig& aReportConfig, CHEvent *pEventSel)
:CHReportTemplate(aReportManager,aReportConfig,pEventSel)
,pReportMng(&aReportManager)
,aV04Inscription(pEventSel)
,pLis(0)
,isTeam(false)
,totalEntries(0)
,pEvent(pEventSel)
,lastEvent(NULLRWSTRING)
,isFirstEvent(true)
{ 
	aV04Inscription.sort(0,orderEventByOrder);
	aV04Inscription.sort(1,orderInscriptionsByGroup);
}
//////////////////////////////////////////////////////////////////////
//Virtual function overwrite
//////////////////////////////////////////////////////////////////////
CReportBase::ReportReturn CHRC32C::OnBody()
{
	RWBoolean isFirstTime = true;
	int rc = END_REPORT;

	// ------------------------------------------------------
	// Bucle de pintado por cada pagina.
	// ------------------------------------------------------
	while( (rc=aV04Inscription++)!=END_REPORT )
	{
		switch ( rc )
		{
		case 0: // Event Level.
			{
				pEvent = (CHEvent*)aV04Inscription.getData(rc);
				isTeam = (((CHEvent*)pEvent)->getTeamMembers()>=2)? true : false;
				pLis->setVari(1001,1011); // "Name"

				if( isFirstTime )
				{
					isFirstTime = false;
					paintHeader();
				}
				if( !isFirstEvent && strcmp(lastEvent,pEvent->getKey()) )
				{
					lastEvent = pEvent->getKey();
					paintTotalEntries();
					return ok;
				}
				isFirstEvent = false;
			}
			break;
		case 1: // Inscription Level.
			{
				if( isFirstTime )
				{
					isFirstTime = false;
					paintHeader();
				}

				CHInscription* pInscription = (CHInscription*)aV04Inscription.getData(rc);
				pEvent = (CHEvent*)pInscription->getEvent();
				
				setDataInscription(pInscription);					
				paintInscription();
				totalEntries++;
			}
			break;
		}

		// Si no hubiera mas datos nos vamos.
		if( rc!=END_REPORT && aV04Inscription.isLast())  
			break;
		
		if( IsPageBreak(short(pLis->getVari(900))) )
		{
			return ok;
		}
	}

	paintTotalEntries();
	
	return exit;
}

void CHRC32C::OnBeginReport()
{
	RWCString sLang = DBApplication::getAppLanguage();
	RWCString sDisc = CHMemoryDataBase::getDiscipline().getCode();
	RWCString sLisName = sDisc + ".C32C." + sLang + ".lis";
	
	// Instanciamos una referencia al lis del report Ctry Event.
	CLis& aLis=pReport->setLis(sLisName);
	pLis=&aLis;
	if( pLis->isValid() )
	{
		// Activamos control de margenes para pintar nuestro body
		pReportMng->setCtrlmargin(true);
		pLis->setVari(1000,getCenter());
		pReport->setCursor(0,0);
		bOkLis=true;
		bHeaderAsOf=true;
		
		// Inicializamos funciones de tablas
		pLis->setCallBack( 101, this );
		pLis->setCallBack( 102, this );
		pLis->setCallBack( 103, this );
		pLis->setCallBack( 104, this );
		
				
		// SetVaris Font
		setVaris(pLis);
		// Codigo NOC, NPC, CGA, dependiente del .lis de cabeceras
		pLis->setData(1012,CReportTemplate::pLis->getData(300)); 
	}
	else
	{	// Si hubo error en el report mostramos el error.
		if ( pReportMng->getError(NOLIS)==pReportMng->getLastError())
			AfxMessageBox(RWWString(pReportMng->getLastError()+"\n"+sLisName,RWWString::ascii));
		else
			AfxMessageBox(RWWString(pReportMng->getLastError(),RWWString::ascii));
	}
}


CReportBase::ReportReturn CHRC32C::paintHeader()
{
	if (isTeam)
	{
		pLis->setVari(1004, pLis->getVari(1006));	// Anchura de Name 
		pLis->setVari(1003,1);		// La celda Role se ejecuta 1 vez
	}
	else
	{
		pLis->setVari(1004,pLis->getVari(1007));	// Anchura de Name 
		pLis->setVari(1003,0);		// La celda Role no se ejecutara ninguna vez
	}

	// Pintamos la cabecera
	if ( !pLis->runline( 1000 ) )
		return OnError(error,1000);

	return ok;
}

CReportBase::ReportReturn CHRC32C::paintInscription()
{
	// Pintamos la linea de datos
	if (isTeam)
	{
		if ( !pLis->runline(1020) )
			return OnError(error, 1020);
	}
	else
	{
		if ( !pLis->runline(1010) )
			return OnError(error,1010);
	}

	return ok;
}

void CHRC32C::setDataInscription(CHInscription* pInscription)
{
	if (!pInscription)
		return;

	RWCString aux=NULLRWSTRING;
	pLis->setData( 2010, aux);	pLis->setData( 2011, aux);
	pLis->setData( 2012, aux);	pLis->setData( 2013, aux);
	pLis->setData( 2014, aux);	pLis->setData( 2015, aux);
	pLis->setData( 2016, aux);	pLis->setData( 2017, aux);
	pLis->setData( 2018, aux);	pLis->setData( 2025, aux);
	pLis->setData( 2026, aux);	pLis->setData( 2027, aux);
	pLis->setData( 2028, aux);

	pLis->setData( 2021, pInscription->getRegister()->getGroup()); // NOC Code
	pLis->setData( 2010, pInscription->getRegister()->getGroupLDescription()); // NOC
	
	
	if (isTeam)
	{
		pLis->setVari(1002,(50*pInscription->getMembersVector().entries())); // Altura del template de equipos
		pLis->setVari(3000,pLis->getVari(3001)); // Offset y de para equipos con members
		if (!pInscription->getMembersVector().entries())
		{
			pLis->setVari(1002,(70)); // Altura del template de equipos
			pLis->setVari(3000,pLis->getVari(3002)); // Offset y de para equipos sin members
		}
		
		for(size_t i=0;i<pInscription->getMembersVector().entries();i++)
		{
			CHMember* pMember=(CHMember*)pInscription->getMembersVector()[i]->getElement();
			pLis->setData( short(2011+i), pMember->getRegister()->getPrnLName());
			pLis->setData( short(2015+i), toUpper(pMember->getRegister()->getBirthDate("%#d %b %Y")));
			if(pMember->getCFunction())
				pLis->setData( short(2025+i), pMember->getFunctionLDescription());
			
		}
	}
	else
	{
		pLis->setData( 2011, pInscription->getRegister()->getPrnLName());
		pLis->setData( 2015, toUpper(pInscription->getRegister()->getBirthDate("%#d %b %Y")));
	}
}

CReportBase::ReportReturn CHRC32C::paintTotalEntries()
{
	RWCString text = NULLRWSTRING;
	char tmp[10] = {0};
	text = pLis->getData(1150);
	text += " ";
	text += itoa(totalEntries,tmp,10);
	text += " ";
	text += pLis->getData(1160);
	pLis->setData(2020, text);
	
	totalEntries = 0;
	// Pintamos la linea de Total Entries
	if( !pLis->runline( 1030 ) )
		return OnError(error,1030);

	return exit;
}


RWDate CHRC32C::OnGetEventDate() const
{
	return INVALID_RWDATE;
}

RWTime CHRC32C::OnGetEventTime() const
{
	return INVALID_RWTIME;
}

RWWString	CHRC32C::OnGetLine(const int lineNumber,const char *language) const
{
	RWWString rc=_T("");

	switch( lineNumber )
	{
	case 0:
		rc = CReportTemplate::OnGetLine(lineNumber,language);
		break;
	case 1:
		{
			if( pEvent )
				rc = pEvent->getLDescription(language);
			else
			{
				if( isFirstEvent )
				{
					// El que Buscamos es el Men Singles Seguro.
					CHEvent aEvent;
					aEvent.setSex(RWCString("0",1));
					aEvent.setEvent(RWCString("001",3));
					CHEvent *pEv = (CHEvent *)CHMemoryDataBase::findEvent(aEvent);
					if( pEv )
						rc = pEv->getLDescription(language);
				}
			}
		}
		break;
	case 2:
		rc = CReportTemplate::OnGetLine(lineNumber,language);
		break;
	}

	return rc;
}
