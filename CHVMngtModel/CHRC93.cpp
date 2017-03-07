/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHRC93.cpp
*   Description	: 
*
*	Author		: CH Team
*	Date created: 5-1-2006
* 	Project		:
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#include "stdVCH.h"
#include "CHRC93.h"
#include <Reports/V/VMedalsByEvent.h>
#include <SPORTS/CH/DATA/CHMemoryDataBase.h>

static int orderEventByEndDate(const GVectorElement** a, const GVectorElement** b)
{
	CHEvent * pEventA = (CHEvent *)(*a)->getElement();
	CHEvent * pEventB = (CHEvent *)(*b)->getElement();

	int order = strcmp(pEventA->getEndDateAsString(),pEventB->getEndDateAsString());
	if( order )
		return order;

	order = strcmp(pEventA->getEndTimeAsString(),pEventB->getEndTimeAsString());
	if( order )
		return order;

	return strcmp(pEventA->getKey() , pEventB->getKey());
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHRC93::CHRC93(CReportManager& aReportManager,CReportConfig& aReportConfig)
:CHReportTemplate(aReportManager,aReportConfig)
,pLis(0)
,firstMedalOfEvent(false)
,firstMedallist(false)
,pLastMedallist(0)
,pEvent(0)
,membersIndex(0)
,nTotalMedals(0)
,oneEvent(false)
{
	pVMedalsByEvent = new VMedalsByEvent(0);
	pVMedalsByEvent->getEntryPoint().sort(orderEventByEndDate);
}

CHRC93::CHRC93(CReportManager& aReportManager,CReportConfig& aReportConfig,CHEvent * pSelEvent)
:CHReportTemplate(aReportManager,aReportConfig,pSelEvent)
,pLis(0)
,firstMedalOfEvent(false)
,firstMedallist(false)
,pLastMedallist(0)
,pEvent(pSelEvent)
,membersIndex(0)
,nTotalMedals(0)
,oneEvent(true)
{
	pVMedalsByEvent = new VMedalsByEvent(pSelEvent);
	pVMedalsByEvent->getEntryPoint().sort(orderEventByEndDate);
}

CHRC93::~CHRC93()
{
	if( pVMedalsByEvent ) 
		delete pVMedalsByEvent;
}

RWCString CHRC93::getNameOfSourceLis()
{
	RWCString lang=DBApplication::getAppLanguage();
	return CHMemoryDataBase::getDiscipline().getCode()+".C93."+lang+".lis";
}

unsigned short CHRC93::OnCallbackFn(struct USR_TAB * pTabInf)
{
	return CReportTemplate::OnCallbackFn(pTabInf);
}

void CHRC93::OnBeginReport()
{
	bOkLis=false;

	fillColEvents();

	RWCString MBElisName = getNameOfSourceLis();
	CReportManager& aReportMng = pReport->getManager();
	// Controlamos que se tengan elementos para pintar
	if(!pVMedalsByEvent->getEntryPoint().entries())
	{
		AfxMessageBox(RWWString("There aren´t Medallists",RWWString::multiByte));
		return;
	}
	// Instanciamos una referencia al lis del report Medals By Event
	CLis &aLis=pReport->setLis(MBElisName);
	pLis=&aLis;
	if( pLis->isValid() )
	{	// Activamos control de margenes para pintar nuestro body.
		pReport->setZeroAs("0");
		pReport->setCursor(0,0);
		aReportMng.setCtrlmargin(true);
		bHeaderAsOf=true;
		// Asignamos variables
		pLis->setVari(100,getCenter());
		//posicion x de comienzo de la tabla
		pLis->setVari(401,getCenter()-(pLis->getVari(400)/2));
		//posicion x de los datos respecto la tabla
		pLis->setVari(402,pLis->getVari(401) + pLis->getVari(402));
		pLis->setVari(403,pLis->getVari(401) + pLis->getVari(403));
		pLis->setVari(404,pLis->getVari(401) + pLis->getVari(404));
		pLis->setVari(405,pLis->getVari(401) + pLis->getVari(405));
		pLis->setVari(406,pLis->getVari(401) + pLis->getVari(406));
		//posicion y de las leyendas
		int YMaxima=pReport->getManager().getYMax();
		pLis->setVari(601, YMaxima - pLis->getVari(601));

		if( !pLis->setCallBack(100,this) )
			AfxMessageBox(RWWString(aReportMng.getLastError()+"\n"+"MedalsByEvent",RWWString::multiByte));

		if( !pLis->setCallBack(101,this) )
			AfxMessageBox(RWWString(aReportMng.getLastError()+"\n"+"MedalsByEvent",RWWString::multiByte));

		if( !pLis->setCallBack(200,this) )
			AfxMessageBox(RWWString(aReportMng.getLastError()+"\n"+"MedalsByEvent",RWWString::multiByte));

		if( !pLis->setCallBack(201,this) )
			AfxMessageBox(RWWString(aReportMng.getLastError()+"\n"+"MedalsByEvent",RWWString::multiByte));

		if( !pLis->setCallBack(600,this) )
			AfxMessageBox(RWWString(aReportMng.getLastError()+"\n"+"MedalsByEvent",RWWString::multiByte));

		bOkLis=true;
		// Codigo NOC, NPC, CGA, dependiente del .lis de cabeceras 
		pLis->setData(106,CReportTemplate::pLis->getData(300));
		// Codigo NOC Code, NPC Code, CGA Code, dependiente del .lis de cabeceras
		pLis->setData(105,CReportTemplate::pLis->getData(301));
	}
	else
	{	// Si hubo error en el report mostramos el error.
		AfxMessageBox(RWWString(aReportMng.getLastError()+"\n"+"MedalsByEvent",RWWString::multiByte));
	}
}

CReportBase::ReportReturn CHRC93::OnBody()
{
	int rc=END_REPORT;
	// Leyendas de Eventos
	paintLegends();

	// Nombre Report y Cabeceras
	if(oneEvent)
	{		
	}
	else
	{
		CString aux;
		aux.Format(_T("AFTER %d OF %d EVENTS"),pVMedalsByEvent->getEntryPoint().entries(),CHMemoryDataBase::getColEvents().entries());
		pLis->setData(110,aux);
		if( !pLis->runline(110) )
			return error;
		if( !pLis->runline(100) )
			return error;
	}

//	RWBoolean firstMedallist=false;
	int nMedals=0,nTotalMembers=0;
	RWDate date;
	while( (rc=(*pVMedalsByEvent)++) != END_REPORT )
	{
		GData * pData = pVMedalsByEvent->getData(rc);
		switch( rc )
		{
		case 0 : // Event
			{
				nTotalMedals=pVMedalsByEvent->getEntriesLevel(0,1);
				nMedals=0;
				firstMedallist=true;
				
				pEvent=(CHEvent*)pData;
				
				date=getFirstMedallist(pEvent);
				pLis->setData(200,pEvent->getLDescription());
				int ntotmembers=pVMedalsByEvent->getEntriesLevel(1,2)+1;
				int height=0;
				switch (ntotmembers)
				{
				case 1:
					height=nTotalMedals*pLis->getVari(214);
					break;
				case 2:
					height=nTotalMedals*pLis->getVari(215);
					break;
				case 3:
					height=nTotalMedals*pLis->getVari(315);
					break;
				case 4:
					height=nTotalMedals*pLis->getVari(325);
					break;
				case 5:
					height=nTotalMedals*pLis->getVari(415);
					break;
				case 6:
					height=nTotalMedals*pLis->getVari(425);
					break;
				}
				if (IsPageBreak(short(height)))
				{
					return ok;
				}
			}
			break;
		case 1 : // Medallist
			{
				nTotalMembers = pVMedalsByEvent->getEntriesLevel(1,2);
				nMedals++;
				//Date
				pLastMedallist=(GMedallist *)pData;
				/*if( pLastMedallist->getDate().isValid() && firstMedallist)
					pLis->setData(201,toUpper(pLastMedallist->getDate().asString("%d %b %Y")));
				else
				{
					pLis->setData(200,""); //Event 
					pLis->setData(201,""); //Date
				}*/
				
				if( date.isValid() && firstMedallist)
					pLis->setData(201,toUpper(date.asString("%d %b %Y").strip(RWCString::leading,'0')));
				else
				{
					pLis->setData(200,""); //Event 
					pLis->setData(201,""); //Date
				}
				//Medal
				pLis->setData(202,toUpper(pLastMedallist->getMedalLDescription()));
				//Group
				if(oneEvent)
				{
					RWCString group=NULLRWSTRING;
					group=pLastMedallist->getGroup()+" - "+pLastMedallist->getRegister()->getGroupLDescription().toAscii();
					pLis->setData(205,group);
				}
				else pLis->setData(205,pLastMedallist->getGroup());
				//Name
				if(!pEvent->isTeam())
					pLis->setData(203,pLastMedallist->getPrnLName());
				//Pintado de la linea de abajo
				if(nTotalMedals==nMedals)
					pLis->setVari(102,2); //outline_lower
				else
					pLis->setVari(102,0); //outline_lower

				membersIndex=0;
				firstMedallist=false;

				if(!pEvent->isTeam())
				{
					pLis->setVari(210,pLis->getVari(211)); //Individual Run Line
					pLis->setVari(213,pLis->getVari(214)); //Alto de celda
					pLis->setVari(216,pLis->getVari(217)); //Posicion en Y
					if(oneEvent)
					{
						if( !pLis->runline(201) )
							return error;
					}
					else
					{
						if( !pLis->runline(200) )
							return error;
					}
				}
			}
			break;
		case 2 : // Member
			{
				membersIndex++;

				CHMember * pMember=(CHMember*)pData;
				if(membersIndex==1)
				{
					RWCString member=NULLRWSTRING;
					member=pMember->getPrnLName().toAscii();/*+"/";*/
					pLis->setData(203,member);
					pLis->setData(204,"");
				}
				else if(membersIndex==2)
						pLis->setData(204,pMember->getPrnLName());
				else if (membersIndex==3)
					pLis->setData(304,pMember->getPrnLName());
				else if (membersIndex==4)
					pLis->setData(305,pMember->getPrnLName());
				else if (membersIndex==5)
					pLis->setData(306,pMember->getPrnLName());

				if(nTotalMembers==membersIndex)
				{
					pLis->setVari(210,400+membersIndex);						//Dobles Run Line
					pLis->setVari(213,pLis->getVari(315)*short(membersIndex));	//Alto de celda
					pLis->setVari(216,pLis->getVari(315)-10);					//Posicion en Y
					if(oneEvent)
					{
						if( !pLis->runline(201) )
								return error;
					}
					else
					{
						if( !pLis->runline(200) )
								return error;
					}
				}
/*				if(nTotalMembers==membersIndex && membersIndex==2)
				{
					pLis->setVari(210,pLis->getVari(212)); //Dobles Run Line
					pLis->setVari(213,pLis->getVari(215)); //Alto de celda
					pLis->setVari(216,pLis->getVari(218)); //Posicion en Y
					if(oneEvent)
					{
						if( !pLis->runline(201) )
								return error;
					}
					else
					{
						if( !pLis->runline(200) )
								return error;
					}
				}
				else if (nTotalMembers==membersIndex && membersIndex==3)
				{
					pLis->setVari(210,pLis->getVari(312)); //linea 
					pLis->setVari(213,pLis->getVari(315)); //Alto de celda
					pLis->setVari(216,pLis->getVari(318)); //Posicion en Y
					if(oneEvent)
					{
						if( !pLis->runline(201) )
								return error;
					}
					else
					{
						if( !pLis->runline(200) )
								return error;
					}
				}
				else if (nTotalMembers==membersIndex && membersIndex==4)
				{
					pLis->setVari(210,pLis->getVari(322)); //linea 
					pLis->setVari(213,pLis->getVari(325)); //Alto de celda
					pLis->setVari(216,pLis->getVari(328)); //Posicion en Y
					if(oneEvent)
					{
						if( !pLis->runline(201) )
								return error;
					}
					else
					{
						if( !pLis->runline(200) )
								return error;
					}
				}*/
			}
			break;
		}
	}
	return exit;
}

void CHRC93::fillColEvents()
{
	RWSet setIncludes;
	GEvent * pEvent = 0;
	GMedallist * pMedallist = 0;
	RWSetIterator it1(GMemoryDataBase::getColMedallist());
	while( (pMedallist=(GMedallist *)it1()) != 0 )
	{
		pEvent = pMedallist->getEvent();
		if( pEvent )
			setIncludes.insert(pEvent);
	}

	colEventsNoMedals.clear();

	RWSetIterator it2(CHMemoryDataBase::getColEvents());
	while( (pEvent=(GEvent *)it2()) != 0 )
	{
		if( !setIncludes.find(pEvent) )
			colEventsNoMedals.insert(pEvent);
	}
}

void CHRC93::paintLegends()
{
	// Note :
	/*if( !pLis->runline(600) )
		return;
	// Events still to be held
	pLis->setVari(600,601);
	pLis->setData(602,pLis->getData(601));
	if( !pLis->runline(601) )
		return;

	GEvent * pEvent = 0;
	RWSetIterator it(colEventsNoMedals);
	while( (pEvent=(GEvent *)it()) != 0 )
	{
		if( pEvent )
		{
			pLis->setVari(600,602);
			pLis->setData(602,pEvent->getLDescription());
			if( !pLis->runline(601) )
				return;
		}
	}*/
}

RWDate CHRC93::OnGetEventDate() const
{
	return INVALID_RWDATE;
}

RWTime CHRC93::OnGetEventTime() const
{
	return INVALID_RWTIME;
}
RWDate CHRC93::getFirstMedallist(CHEvent *pEvent)
{
	GMedallist * pMedallist = 0;
	RWSetIterator it1(GMemoryDataBase::getColMedallist());
	CHEvent *pEventAux=0;
	RWDate date;
	while( (pMedallist=(GMedallist *)it1()) != 0 )
	{
		pEventAux = (CHEvent*)pMedallist->getEvent();
		if( pEventAux && pEventAux==pEvent )
		{
			return pMedallist->getDate();
		}
	}
	return date;
}