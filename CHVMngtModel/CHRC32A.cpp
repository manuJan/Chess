/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHRC32A.cpp
*	Description	: Export Dll
*
*	Author		: Chess Team
*	Date created: 19-12-2005
* 	Project		: Entry List By Noc Report
*	
* 	Modification history
*	By			:                    
*	Date		: 
*	Changes		: 
*
***************************************************************************************/

#include "stdVCH.h"
#include "CHRC32A.h"
#include "CHRLegends.h"

#include <Sports/CH/Data/CHDiscipline.h>
#include <Sports/CH/Data/CHRegister.h>
#include <Sports/CH/Data/CHMember.h>
#include <Sports/CH/Data/CHInscription.h>
#include <Sports/CH/Data/CHEvent.h>

#include <Reports/V/OrderView.h>

//////////////////////////////////////////////////////////////////////
static int orderEventsByTeamSex1(const GVectorElement** a, const GVectorElement** b)
{
	CHEvent *pEventA = (CHEvent *)(*a)->getElement();
	CHEvent *pEventB = (CHEvent *)(*b)->getElement();

	int rc = pEventA->getOrderEvent()-pEventB->getOrderEvent();
	if( rc )
		return rc;

	return strcmp(pEventA->getKey(),pEventB->getKey());
}

static int orderEventsByOrder(const GVectorElement** a, const GVectorElement** b)
{
	CHEvent *pEvent1=(CHEvent *)(*a)->getElement();
	CHEvent *pEvent2=(CHEvent *)(*b)->getElement();

	int rc = pEvent1->getOrderEvent() - pEvent2->getOrderEvent();
	if( !rc )
		rc = strcmp(pEvent1->getKey(),pEvent2->getKey());
	return rc;
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHRC32A::CHRC32A(CReportManager& aReportManager,CReportConfig& aReportConfig)
:CHReportTemplate(aReportManager,aReportConfig)
,pReportMng(&aReportManager)
,pLis(0)
,pRegisterSel(0)
,index(0)
,nRegisters(0)
,counterRegisters(0)
,first(true)
,breakPage(false)
,pLegends(0)
{ 
	vEvents = GSortedVector(CHMemoryDataBase::getColEvents(),orderEventsByTeamSex1);
	for( size_t i=0; i<vEvents.entries(); i++)
		vIndex.insert( new RWCollectableInt(-1) );	
}

CHRC32A::~CHRC32A()
{
	vIndex.clearAndDestroy();
	if (pLegends)
		delete pLegends;
	
}

//////////////////////////////////////////////////////////////////////
void CHRC32A::OnBeginReport()
{
	RWCString lang = DBApplication::getAppLanguage();
	RWCString sLisName = "CH.C32A." + lang + ".lis";
	
	// Instanciamos una referencia al lis del report Ctry Event.
	CLis& aLis = pReport->setLis(sLisName);
	pLis = &aLis;
	if( pLis && pLis->isValid() )
	{
		// Activamos control de margenes para pintar nuestro body
		pReportMng->setCtrlmargin(true);
		pLis->setVari(1000,getCenter());
		pReport->setCursor(0,0);
		bOkLis = true;
		bHeaderAsOf=true;
		
		// Inicializamos funciones de tablas
		pLis->setCallBack(101, this);  
		pLis->setCallBack(102, this);

		// Asignando Varis de las fonts - SetVaris Font
		setVaris(pLis);

		// Asignando Varis Generales
		pLis->setVari(2015, (vEvents.entries()>0?vEvents.entries():0));
		if( vEvents.entries()<=4 )
		{
			int total = pLis->getVari(1005);
			pLis->setVari(1006, total);
			pLis->setVari(1007, total/2);
			pLis->setVari(1008, total/vEvents.entries());
			pLis->setVari(1009, (total/vEvents.entries())/2);		
		}
		else
		{
			int total = pLis->getVari(1008)*vEvents.entries();
			pLis->setVari(1006, total);
			pLis->setVari(1007, total/2);
		}
		// Codigo NOC, NPC, CGA, dependiente del .lis de cabeceras
		pLis->setData(1010,CReportTemplate::pLis->getData(300)); 
		
		pLegends = new CHRLegends(this,pReport,CHRLegends::eC32A);
		if (!pLegends)
		{
			AfxMessageBox(_T("Legends Error"));
			return;
		}
		
		pLegends->loadLis();
		setDynamicLegends();

	}
	else
	{	// Si hubo error en el report mostramos el error.
		if ( pReportMng->getError(NOLIS)==pReportMng->getLastError())
			AfxMessageBox(RWWString(pReportMng->getLastError()+"\n"+sLisName,RWWString::ascii));
		else
			AfxMessageBox(RWWString(pReportMng->getLastError(),RWWString::ascii));
	}
}

//////////////////////////////////////////////////////////////////////
// Funciones estaticas de control de tablas
//////////////////////////////////////////////////////////////////////
unsigned short CHRC32A::OnCallbackFn( struct USR_TAB * pTableInfo )
{
	switch(pTableInfo->Tb)
	{
	case 101:
		return tHeader(pTableInfo);
		break;
	case 102:
		return tDetails(pTableInfo);
		break;
	}
	return CReportBase::OnCallbackFn(pTableInfo);
}

unsigned short CHRC32A::tHeader( struct USR_TAB * pTableInfo )
{
	if( pTableInfo->Te==0 )
	{
		switch ( pTableInfo->Ce )
		{
		case 0:
			index = 0;
			break;
		case 7:
			{
				if( index<vEvents.entries() )
				{
					CHEvent *pEvent = (CHEvent*)vEvents[index]->getElement();
					if( pEvent )
						pLis->setData( 2040, pEvent->getSDescription());
					index++;
				}
			}
			break;
		}
	}
	return PRNALL;
}

unsigned short CHRC32A::tDetails( struct USR_TAB * pTableInfo )
{
	pLis->setData(2000, "");	pLis->setData(2001, "");
	pLis->setData(2011, "");	pLis->setData(2012, "");	pLis->setData(2013, "");
	pLis->setData(2020, "");

	if( pTableInfo->Te==0 )
	{
		switch( pTableInfo->Ce )
		{
		case 0:	// NOC
			{
				index = 0;
				if( breakPage || (counterRegisters==nRegisters) )
				{
					pLis->setVari( 1001, pLis->getVari(1012));
					pLis->setVari( 1010, pLis->getVari(1012));
				}
				else
				{
					pLis->setVari( 1001, 0);
					pLis->setVari( 1010, 0);
				}
				
				if( first )
					pLis->setData( 2001, pRegisterSel->getGroup());
			}
			break;
		case 1: // Country Description
			if( first )
				pLis->setData( 2000, pRegisterSel->getGroupLDescription());
			break;
		case 2: // Register Name
			pLis->setData( 2011, pRegisterSel->getPrnLName());
			break;
		case 3: // Sex
			{
				GSex *pSex = CHMemoryDataBase::findSex(pRegisterSel->getSex());
				pLis->setData( 2012,((pSex)?pSex->getSDescription():NULLRWWSTRING));
			}
			break;
		case 4: // Birth Date
			pLis->setData( 2013, toUpper(pRegisterSel->getBirthDate("%d %b %Y")));	
			break;
		case 5: // Inscrito o no en evento
			{
				if( index<vEvents.entries() )
				{
					RWCString sRk = assignAsterikEvent();
					pLis->setData( 2020, sRk);
				}
				index++;
			}
			break;
		}
	}
    return PRNALL;
}

RWCString CHRC32A::assignAsterikEvent()
{
	RWCString aux = NULLRWSTRING;

	CHEvent *pEvent = (CHEvent *) vEvents[index]->getElement();
	CHInscription *pInscription = 0;

	if( !pEvent->isTeam() )
	{
		pInscription = (CHInscription *)CHMemoryDataBase::findInscription(pRegisterSel,pEvent);
		if( !pInscription )
			return aux;
		
		aux = pLis->getData(1018);
		return aux;
	}

	// Llegados aqui es que es Team, y necesitamos buscar su pareja
	// 1º Buscamos al registro como Member.
	CHMember *pMember = findMember(pEvent,pRegisterSel);
	if( !pMember )
		return aux;
	// 2º Buscamos inscripción de ese member.
	pInscription = (CHInscription *)pMember->getInscription();
	if( !pInscription )
		return aux;
	
	aux = pLis->getData(1018);
	return aux;
	
}


CHMember *CHRC32A::findMember(CHEvent *pEvent, CHRegister *pRegister)
{
	RWSetIterator it(CHMemoryDataBase::getColInscriptions());
	CHInscription *pInsc = 0;
	CHMember *pMember = 0;
	while( (pInsc = (CHInscription *)it())!=0 )
	{
		if( pInsc->getEvent()==pEvent )
		{
			for( size_t i=0; i<pInsc->getMembersVector().entries(); i++)
			{
				pMember = (CHMember *)pInsc->getMembersVector()[i]->getElement();
				if( pMember )
				{
					if( pMember->getRegister()== pRegister )
						return pMember;
				}
			}
		}
	}

	return 0;
}

GVectorElement* CHRC32A::isInscription(CHInscription* pInscription)
{
	if( index>=vEvents.entries() )
		return 0;

	GSortedVector  &aVector  = vEvents[index]->getVector();
	GVectorElement *pElement = aVector.find(pInscription);
	return pElement;
}

void CHRC32A::insertInscription(CHInscription *pInscription)
{
	if( index>=vEvents.entries() )
		return;

	GSortedVector &aVector = vEvents[index]->getVector();
	aVector.insert(pInscription);
}


//////////////////////////////////////////////////////////////////////
//Virtual function overwrite
//////////////////////////////////////////////////////////////////////
CReportBase::ReportReturn CHRC32A::OnBody()
{
	first = true;
	breakPage = false;
	int rc = END_REPORT;

	paintHeader();

	// ------------------------------------------------------
	// Bucle de pintado por cada pagina.
	// ------------------------------------------------------
	GData *pData = 0;
	do
	{
		switch ( rc )
		{
		case 0: // Group Level.
			{
				first = true;
				index = 0;
				nRegisters = aVEntriesByNoc.getEntriesLevel(0,1);
				counterRegisters = 0;
				deleteInscriptionsVector();

				// Calculamos si caben todos los registros de un Pais
				// nRegisters * Alto de una linea + leyenda=250
				int footHeigh = 0;
				if( first )
				{
					footHeigh = (nRegisters * pLis->getVari(1004)) + 250;
					if ( IsPageBreak(short(footHeigh)) )
					{
						breakPage = true;
						pLis->setVari(1010, 1);
					}
				}
			}
			break;
		case 1: // Register Level.
			{
				pRegisterSel = (CHRegister *)pData;
				counterRegisters++;
				if (IsPageBreak(short(pLis->getVari(1004) + 250)))
					{//salto de pagina
						breakPage = true;
						pLis->setVari(1010, 1);
					}
				paintDetails();
				first = false;
			}
			break;
		}

		// Si no hubiera mas datos nos vamos.
		if (rc!=END_REPORT && aVEntriesByNoc.isLast()) 
			break;
		
		if( breakPage )
		{
			//intLegend();
			return ok;
		}

		// Buscamos mas datos.
		rc = aVEntriesByNoc++;
		pData = aVEntriesByNoc.getData(rc);
	}
	while( rc!=END_REPORT );
	
	paintLegend();
	return exit;
}

void CHRC32A::deleteInscriptionsVector()
{
	for( size_t i=0; i<vEvents.entries(); i++ )
		vEvents[i]->getVector().clearAndDestroy();	
	
	RWCollectableInt *pInt=0;
	for( size_t j=0; j<vIndex.entries(); j++ )
	{
		pInt = (RWCollectableInt *)vIndex[j];
		pInt->value(0);
	}
}


CReportBase::ReportReturn CHRC32A::paintHeader()
{	// Pintamos la cabecera
	if ( !pLis->runline( 1000 ) )
		return OnError(error, 1000);

	return exit;
}

CReportBase::ReportReturn CHRC32A::paintDetails()
{	// Pintamos una linea de datos
	if ( !pLis->runline( 1010 ) )
		return OnError(error, 1010);

	return ok;
}

CReportBase::ReportReturn CHRC32A::paintLegend()
{
	pLegends->runLis(); // Pintamos las leyendas.
	return exit;
}


RWDate CHRC32A::OnGetEventDate() const
{
	return INVALID_RWDATE;
}

RWTime CHRC32A::OnGetEventTime() const
{
	return INVALID_RWTIME;
}
void CHRC32A::setDynamicLegends()
{
		
	GSex *pSex = 0;
	GSortedVector vSexs = GSortedVector(CHMemoryDataBase::getColSex(),orderSex );
	for(size_t i=0; i<vSexs.entries(); i++ )
	{
		pSex = (GSex *) vSexs[i]->getElement();
		if( pSex->getSex()!="2" )
			pLegends->setDynamic( pSex->getSDescription());							
							
	}

	CHEvent *pEvent = 0;
	GSortedVector vEvents(CHMemoryDataBase::getColEvents(),orderEventsByOrder);
	for(i=0; i<vEvents.entries(); i++ )
	{
		pEvent = (CHEvent *)vEvents[i]->getElement();
		pLegends->setDynamic( pEvent->getSDescription());							
	}

	pLegends->createDynamic();
}

	
