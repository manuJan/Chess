/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHRC30.cpp
*	Description	:Export Dll
*
*	Author		:Chess Team 
*	Date created:19-12-2005
* 	Project		: Number Entries By Noc Report
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdVCH.h"
#include "CHRC30.h"
#include <Sports/CH/Data/CHRegister.h>
#include <Sports/CH/Data/CHInscription.h>
#include <Sports/CH/Data/CHMember.h>
#include <Sports/CH/Data/CHEvent.h>
#include <Reports/V/OrderView.h>
#include "CHRLegends.h"


//////////////////////////////////////////////////////////////////////
static int orderEventsByTeamSex(const GVectorElement** a, const GVectorElement** b)
{
	CHEvent *pEventA = (CHEvent*)(*a)->getElement();
	CHEvent *pEventB = (CHEvent*)(*b)->getElement();

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
CHRC30::CHRC30(CReportManager& aReportManager,CReportConfig& aReportConfig)
:CHReportTemplate(aReportManager,aReportConfig)
,pReportMng(&aReportManager)
,pData(0)
,pLis(0)
,index(0)
,pGroupSel(0)
,totalMen(0)
,totalWomen(0)
,totalTotal(0)
,pLegends(0)
{ 
	aV03Inscription.sort(0,orderGroups);
	aV03InscAux.sort(0,orderGroups);
	vEvents = GSortedVector(CHMemoryDataBase::getColEvents(),orderEventsByTeamSex);
	for( size_t i=0; i<vEvents.entries(); i++ )
		vIndex.insert( new RWCollectableInt(0) );

	pLegends = new CHRLegends(this,pReport,CHRLegends::eC30);
}

CHRC30::~CHRC30()
{
	colMenRegisters.clear();
	colWomenRegisters.clear();
	vIndex.clearAndDestroy();
	if (pLegends)
		delete pLegends;
}

//////////////////////////////////////////////////////////////////////
// Funciones estaticas de control de tablas
//////////////////////////////////////////////////////////////////////
unsigned short CHRC30::OnCallbackFn( struct USR_TAB * pTableInfo )
{
	switch( pTableInfo->Tb )
	{
	case 101:
		return tablaCabecera(pTableInfo);
		break;
	case 102:
		return tablaGroups(pTableInfo);
		break;
	case 103:
		return tablaTotals(pTableInfo);
		break;
	}
	return CReportBase::OnCallbackFn(pTableInfo);
}

unsigned short CHRC30::tablaCabecera( struct USR_TAB * pTableInfo )
{
	switch( pTableInfo->Te )
	{
	case 0:
		{
			switch ( pTableInfo->Ce )
			{
			case 0:
				index = 0;
				break;
			case 5:
				{
					if( index<vEvents.entries() )
					{
						RWWString aux = NULLRWWSTRING;
						CHEvent *pEvent = (CHEvent*)vEvents[index]->getElement();
						aux = pEvent->getSDescription();
						pLis->setData( 2040, aux);
						index++;
					}
				}
				break;
			}
		}
		break;
	}
    return PRNALL;
}

unsigned short CHRC30::tablaGroups( struct USR_TAB * pTableInfo )
{
	char tmp[10]={0};

	switch( pTableInfo->Te )
	{
	case 0:
		{	
			switch( pTableInfo->Ce )
			{
			case 2:
				//{
					//int entries = getEntriesByEvent();
				pLis->setData( 2002, itoa(getEntriesByEvent(),tmp,10) ); 
									//itoa(entries,tmp,10));
				index++;
				break;
				//}
			case 3:
				//{
					//char tmp[10];
				pLis->setData( 2003, itoa(getMenOfGroup(),tmp,10));
				setMenOfGroup();
				break;
				//}
			case 4:
				//{
					//char tmp[10];
				pLis->setData( 2004, itoa(getWomenOfGroup(),tmp,10));
				setWomenOfGroup();
				break;
				//}
			case 5:
				//{
					//char tmp[10];
				pLis->setData( 2005, itoa(getMenOfGroup()+getWomenOfGroup(),tmp,10));
				break;
				//}
			}
		}
		break;
	}
    return PRNALL;
}

unsigned short CHRC30::tablaTotals( struct USR_TAB * pTableInfo )
{
	char tmp[10]={0};

	switch( pTableInfo->Te )
	{
	case 0:
		{	
			switch( pTableInfo->Ce )
			{
			case 2:
				{
					//char tmp[10];
					RWCollectableInt *pInt = 0;
					pInt = (RWCollectableInt *)vIndex[index];
					int intAux = *pInt;
					pLis->setData( 2011, itoa(intAux,tmp,10));
					index++;
				}
				break;
			}
		}
		break;
	}
    return PRNALL;
}

//////////////////////////////////////////////////////////////////////
//Virtual function overwrite
//////////////////////////////////////////////////////////////////////
CReportBase::ReportReturn CHRC30::OnBody()
{
	int rc=END_REPORT;
	pLis->setVari(2015,vEvents.entries()?vEvents.entries():0);
	paintHeader();
	// ------------------------------------------------------
	// Bucle de pintado por cada pagina.
	// ------------------------------------------------------
	do
	{
		switch ( rc )
		{
		case 0: // Group Level.
			{
				colMenRegisters.clear();
				colWomenRegisters.clear();
				index = 0;
				pGroupSel = (GGroup*)pData;
				setDataGroup(pGroupSel);
				paintGroup();
			}
			break;
		}
		// Si no hubiera mas datos nos vamos.
		if( rc!=END_REPORT && aV03Inscription.isLast() )
			break;
		
		if( IsPageBreak(short(pLis->getVari(900))) )
		{
			paintLegend();
			return ok;
		}

		// Buscamos mas datos.
		rc = aV03Inscription++;
		pData = aV03Inscription.getData(rc);
	}
	while( rc!=END_REPORT );
	
	index=0;
	setDataTotals();
	paintTotals();
	paintLegend();

	return exit;
}

void CHRC30::OnBeginReport()
{
	RWCString lang=DBApplication::getAppLanguage();
	RWCString sDiscipline = CHMemoryDataBase::getDiscipline().getCode();
	RWCString sLisName = sDiscipline + ".C30." + lang + ".lis";
	
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
		// SetVaris Font
		setVaris(pLis);
		setVariables30();
		
		
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

CReportBase::ReportReturn CHRC30::paintHeader()
{
	// Pintamos la cabecera
	if ( !pLis->runline( 1000 ) )
		return OnError(error,101);

	return exit;
}

CReportBase::ReportReturn CHRC30::paintLegend()
{
	pLegends->runLis(); // Pintamos las leyendas.
	return exit;
					 	
}

CReportBase::ReportReturn CHRC30::paintGroup()
{
	if ( !pLis->runline( 1010 ) )
		return OnError(error,101);

	return ok;
}

CReportBase::ReportReturn CHRC30::paintTotals()
{
	if ( !pLis->runline( 1020 ) )
		return OnError(error,101);

	return ok;
}

void CHRC30::setDataGroup(GGroup* pGroup)
{
	pLis->setData( 2000, pGroup->getGroup());
	pLis->setData( 2001, pGroup->getLDescription());
}

void CHRC30::setDataTotals()
{
	char tmp[10];

	pLis->setData( 2010, itoa(totalGroups,tmp,10));
	pLis->setData( 2012, itoa(totalMen,tmp,10));
	pLis->setData( 2013, itoa(totalWomen,tmp,10));
	pLis->setData( 2014, itoa(totalTotal,tmp,10));
}

int CHRC30::getMenOfGroup()
{
	int men=colMenRegisters.entries();
	return men;
}

void CHRC30::setMenOfGroup()
{
	int men=colMenRegisters.entries();
	totalMen+=men;
	totalTotal+=men;
}

int CHRC30::getWomenOfGroup()
{
	int women=colWomenRegisters.entries();
	return women;
}

void CHRC30::setWomenOfGroup()
{
	int women=colWomenRegisters.entries();
	totalWomen+=women;
	totalTotal+=women;
}

int CHRC30::getEntriesByEvent()
{
	int entries=0;
	GSortedVector &aVector = aV03InscAux.getEntryPoint();
	GVectorElement * pElement = aVector.find(pGroupSel);
	if( pElement && index<vEvents.entries() )
	{
		CHEvent *pEvent = (CHEvent *)vEvents[index]->getElement();
		pElement=pElement->getVector().find(pEvent);
		if (pElement)
		{
			GSortedVector& aVectorInscrptions= pElement->getVector();
			entries=int (aVectorInscrptions.entries());
			RWCollectableInt *pInt=0;
			pInt=(RWCollectableInt *)vIndex[index];
			int intAux=*pInt;
			intAux+=entries;
			pInt->value(intAux);
			
			CHInscription* pInscription=0;
			for (size_t i=0;i<aVectorInscrptions.entries();i++)
			{
				pInscription=(CHInscription*)aVectorInscrptions[i]->getElement();
				if (((CHEvent*)pInscription->getEvent())->isTeam())
				{
					GSortedVector& aVectorMembers=pInscription->getMembersVector();
					CHMember* pMember=0;
					for (size_t j=0;j<aVectorMembers.entries();j++)
					{
						pMember=(CHMember*)aVectorMembers[j]->getElement();
						insertRegister((CHRegister*)pMember->getRegister());
					}

				}
				else
				{
					insertRegister((CHRegister*)pInscription->getRegister());
				}
			}
		}
	}
	return entries;
}

void CHRC30::insertRegister(CHRegister* pRegister)
{
	if (pRegister)
	{
		if (pRegister->getSex()=="0")
			colMenRegisters.insert(pRegister);
		else
			colWomenRegisters.insert(pRegister);
	}
}

RWCString CHRC30::getEventsDescription()
{
	RWCString aux = NULLRWSTRING;
	CHEvent *pEvent = 0;
	GSortedVector vEvents(CHMemoryDataBase::getColEvents(),orderEventsByTeamSex);
	for( size_t i=0; i<vEvents.entries(); i++ )
	{
		pEvent = (CHEvent *)vEvents[i]->getElement();
		aux += "  ";
		aux += pEvent->getSDescription().toAscii();
		aux += " - ";
		aux += pEvent->getLDescription().toAscii();
		aux += "  ";
	}
	return aux;
}

void CHRC30::setVariables30()
{
	int total=0;
	if( pLis )
	{
		pLis->setData(1004,getEventsDescription());

		if( vEvents.entries()<=4 )
		{
			total = pLis->getVari(1005);
			pLis->setVari(1006,total);
			pLis->setVari(1007,total/2);
			pLis->setVari(1008,total/vEvents.entries());
			pLis->setVari(1009,pLis->getVari(1008)/2);
			pLis->setVari(1010,(total/vEvents.entries())/2);
		}
		else
		{
			total = (pLis->getVari(1008)*vEvents.entries());
			pLis->setVari(1006,total);
			pLis->setVari(1007,total/2);

			pLis->setVari(1009,pLis->getVari(1008)/2);
		}
		pLis->setVari(1010,total+pLis->getVari(1011));
		GSortedVector& aVector= aV03InscAux.getEntryPoint();
		totalGroups=aVector.entries();
	}
	// Codigo NOC, NPC, CGA, dependiente del .lis de cabeceras
	RWCString noc=CReportTemplate::pLis->getData(300);

	pLis->setData(1010,CReportTemplate::pLis->getData(300)); 

	// Corx centrada de la tabla
	int width=0;
	// Vari[21] son los posibles celdas a pintar
	
	width=pLis->getVari(1012)+pLis->getVari(1013)+pLis->getVari(1014)+pLis->getVari(1006);
	
	long center=getCenter();
	long offsetx=center-(width/2);
	if (offsetx>25)
		pLis->setVari(901,offsetx-25);
	else
		pLis->setVari(901,10);

}

RWDate CHRC30::OnGetEventDate() const
{
	return INVALID_RWDATE;
}

RWTime CHRC30::OnGetEventTime() const
{
	return INVALID_RWTIME;
}

void CHRC30::setDynamicLegends()
{
	RWCString aux = NULLRWSTRING;
	CHEvent *pEvent = 0;
	GSortedVector vEvents(CHMemoryDataBase::getColEvents(),orderEventsByOrder);
	for( size_t i=0; i<vEvents.entries(); i++ )
	{
		pEvent = (CHEvent *)vEvents[i]->getElement();
		////addlegend(pEvent->getSDescription().toAscii(),pEvent->getLDescription().toAscii() );
		pLegends->setDynamic( pEvent->getSDescription());							
	}

	pLegends->createDynamic();
}


	

	
