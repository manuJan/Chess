/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHRC32A.cpp
*	Description	:
*				 
*	Author		: Javier Juste
*	Date created: 15-Mar-2009
* 	Project		: ARVMngtModel
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdafx.h"
#include "CHRC32A.h"
#include "CHRLegends.h"
#include "..\CHMngtModel\CHEvent.h"
#include "..\CHMngtModel\CHInscription.h"
#include "..\CHMngtModel\CHRegister.h"
#include "..\CHMngtModel\CHMember.h"
#include "..\CHMngtModel\CHDefinition.h"

static bool selectInscriptions(const MSLItem* p,const void *n)
{
	CHInscription *pInsc = (CHInscription *)p;	
	if( !pInsc )
		return false;

	if( pInsc->getRegister()->getType() == GRegister::individual )
		return true;

	return false;
	UNREFERENCED_PARAMETER(n);
}

static
int orderEvents(const MSLItem** a, const MSLItem** b)
{
	CHEvent *pEventA=(CHEvent *)(*a);
	CHEvent *pEventB=(CHEvent *)(*b);

	int order = strcmp(pEventA->getEvent(),pEventB->getEvent());
	if( order )
		return order;
		
	return strcmp(pEventA->getKey(),pEventB->getKey());
}

static 
int orderInscriptionsByGroupEventName(const MSLItem** a, const MSLItem** b)
{
	CHInscription *pInscA=(CHInscription *)(*a);
	CHInscription *pInscB=(CHInscription *)(*b);

	int order=strcmp(pInscA->getGroup(),pInscB->getGroup());
	if( order )
		return order;

	order = strcmp(pInscA->getSex(),pInscB->getSex());
	if( order )
		return order;

	order = strcmp(pInscA->getEventKey(),pInscB->getEventKey());
	if (order)
		return order;

	CHRegister* pRegA=(CHRegister*)pInscA->getRegister();
	CHRegister* pRegB=(CHRegister*)pInscB->getRegister();

	order = _wcsicoll(pRegA->getPrnLName(),pRegB->getPrnLName());
	return (order) ? order:pRegA->getRegister()-pRegB->getRegister();
}

CHRC32A::CHRC32A(CReportManager& aReportManager,CReportConfig& aReportConfig)
:CHReportTemplate(aReportManager,aReportConfig)
,m_pLis(0)
,m_index(0)
,m_pLegend(0)
,m_pInscription(0)
,m_vEvents(orderEvents)
{
	m_pLegend = new CHRLegends(this,m_pReport,CH32A);
	loadData();
}

CHRC32A::~CHRC32A()
{
	if (m_pLegend)
		delete m_pLegend;
}

int	CHRC32A::loadEvents()
{
	m_vEvents=MSLSortedVector(CHMemoryDataBase::getCol(__CHEVENT), orderEvents);
	return m_vEvents.entries();
}

void CHRC32A::OnBeginReport()
{
	// Report Name
	MSLString disc = ((CHDefinition &)CHMemoryDataBase::getDefinition()).getCode();
 	MSLString lis = disc + ".C32A" + ".lis";

	CLis& aLis=m_pReport->setLis(lis);
	m_pLis=&aLis;

	CReportManager& aReportMng=m_pReport->getManager();
	if( !m_pLis->isValid() )
	{
		MessageBox(0,MSLWString(aReportMng.getLastError()+"\n"+lis),L"",MB_OK);
		m_pLis=0;
	}

	bool bOkLis=(m_pLis!=0 && CReportBase::isValid());
	if( bOkLis )
	{
		m_bHeaderAsOf=true;

		if( !m_pLegend || (m_pLegend && !m_pLegend->loadLis()) )
			MessageBox(0,L"Error loading legends",L"",MB_OK);
				
		initVaris();
		initLabels();

		if ( !m_pLis->setCallBack(1,this) )
			MessageBox(0,MSLWString(aReportMng.getLastError()+"\n"+"check header"+"\n"+lis),L"",MB_OK);
		else if ( !m_pLis->setCallBack(2,this) )
			MessageBox(0,MSLWString(aReportMng.getLastError()+"\n"+"check body"+"\n"+lis),L"",MB_OK);
	}
	else // Si hubo error en el report mostramos el error.
		MessageBox(0,MSLWString(aReportMng.getLastError()+"\n"+lis),L"",MB_OK);
}

unsigned short CHRC32A::OnCallbackFn(struct USR_TAB * pTabInf) 
{ 
    switch ( pTabInf->Tb ) 
    { 
		case 1: 
			return reportHeader_CallBack(pTabInf); 
		case 2: 
			return reportBody_CallBack(pTabInf); 
    } 

    return CHReportTemplate::OnCallbackFn(pTabInf); 
} 

CReportBase::ReportReturn CHRC32A::OnBody()
{
	if( !m_vData.entries() )
		return exit;

	m_pReport->setCursor(0,0);
	centerReport();

	// Header
	if( !m_pLis->runline(1) )
		return error;

	MSLString lastGroup=NULLSTRING;
	// Body
	for( short i = m_index; i<m_vData.entries(); i++ )
	{
		m_pInscription = (CHInscription *)m_vData[i];
		if( !m_pInscription )
			continue;

		if (lastGroup!=m_pInscription->getGroup())
		{
			if (!m_pLis->runline(3)) 
				return error;

			m_paintGroup=true;

			// Page Break
			int groupSize = getGroupSize(m_pInscription->getGroup());
			int totalSize = m_pLegend->getHeight() + 50 + groupSize * m_pLis->getVari(21);
			int yMax = m_pReport->getManager().getXMax();

			if (totalSize<yMax)
			{
				if( IsPageBreak( short(m_pLegend->getHeight() + 50 + groupSize * m_pLis->getVari(21)) ) )
				{
					m_index = i;
					return ok;
				}						
			}
		}

		if( IsPageBreak( short(m_pLegend->getHeight() + 50 ) ) )
		{
			m_index = i;
			return ok;
		}	
		
		if (!m_pLis->runline(2)) 
			return error;


		m_paintGroup=false;
		lastGroup=m_pInscription->getGroup();
	}

	if( !m_pLegend->runLis() )
		return error;

	return exit;
}

void CHRC32A::loadData()
{
	m_vData.clear();
	MSLSet colInscriptions=CHMemoryDataBase::getCol(__CHINSCRIPTION).select(selectInscriptions,(void *)0);
	m_vData = MSLSortedVector(colInscriptions,orderInscriptionsByGroupEventName);
	m_numEvents=loadEvents();
}

void CHRC32A::initVaris()
{	
	m_pLis->setVari(15,m_numEvents);
	m_pLis->setVari(115, m_numEvents * m_pLis->getVari(125));
}

void CHRC32A::initLabels()
{
	m_pLis->setData(111,CReportTemplate::m_pHeaderLis->getData(300)); //"NPC"	
	m_pLis->setData(114,getUserLabel(71)); //"M/W"		
	m_pLis->setData(113,getUserLabel(72)); //"Name"
	m_pLis->setData(116,getUserLabel(73)); //"Date of Birth"
	m_pLis->setData(115,getUserLabel(74)); //"Event Participation"	
}

int	CHRC32A::getGroupSize(MSLString group)
{
	int entries=0;
	for (short i=0;i<m_vData.entries();i++)
	{
		CHInscription *pInscription = (CHInscription *)m_vData [i];
		if (pInscription->getGroup()==group)
			entries++;
	}
	return entries;
}

void CHRC32A::centerReport()
{
	// Title coor x
	m_pLis->setVari(3,getCenter());

	int width = m_pLis->getVari(111)+	// NOC 
				m_pLis->getVari(116)+   // Country
				m_pLis->getVari(113)+   // Name
				m_pLis->getVari(114)+   // Back No.
				m_pLis->getVari(115);	// Weight

	int corx  = getCenter()-(width/2);

	m_pLis->setVari(1,corx);
}

unsigned short CHRC32A::reportHeader_CallBack( struct USR_TAB *pTabInf )
{
	if( !pTabInf )
		return PRNALL;

	centerData(m_pLis,pTabInf);

	int dato = (pTabInf->Tb*100) + (pTabInf->Te*10) + pTabInf->Ce;

	// NOC
	if( pTabInf->Te == 1 && pTabInf->Ce == 1 )
		m_pLis->setData(short(dato),CReportTemplate::m_pHeaderLis->getData(300));
	// Event
	if( pTabInf->Te == 2 && pTabInf->Ce == 5 )
	{
		centerData(m_pLis,pTabInf);

		MSLWString tmp = NULLWSTRING;
					
		CHEvent * pEvent = (CHEvent*)m_vEvents[pTabInf->C_Count-1];
		if (pEvent)
			tmp = pEvent->getCodeReports().toUnicode();

		m_pLis->setData(125,tmp);
	}

	return PRNALL;
}

unsigned short CHRC32A::reportBody_CallBack( struct USR_TAB *pTabInf )
{
	if( !pTabInf )
		return PRNALL;

	switch( pTabInf->Te )
	{
	case 1:
		{
			if( !m_pInscription )
			{
				return PRNALL;
			}

			CHRegister * pRegister = (CHRegister*) m_pInscription->getRegister();

			centerData(m_pLis,pTabInf);

			switch( pTabInf->Ce )
			{
			case 1: // Name
				if (m_paintGroup)
				{
					MSLWString group = m_pInscription->getGroup();
					group += " - ";
					group += m_pInscription->getGroupLDescription(m_language);
					m_pLis->setData(211,group);
				}
				else
					m_pLis->setData(211,"");
				break;
			case 3: // Name
				m_pLis->setData(213,m_pInscription->getPrnLName(m_language));
				break;	
			case 4:
				m_pLis->setData(214,m_pInscription->getSex());
				break;	
			case 6:
				if (pRegister)
				{
					MSLWString birthDate = pRegister->getBirthDate("%d %b %Y");
					birthDate.toUpper();
					m_pLis->setData(216,birthDate);	
				}				
				break;
			case 5:
				{					
					MSLWString tmp = NULLWSTRING;
					CHEvent * pEvent = (CHEvent*)m_vEvents[pTabInf->C_Count-1];
					if (pEvent)
					{
						MSLString sRk = inscriptedMark(pEvent);
						m_pLis->setData( 215, sRk);
					}
				}
				break;
			}
		}
		break;
	}
	
	return PRNALL;
}

MSLString CHRC32A::inscriptedMark(CHEvent * pEvent)
{
	if (!pEvent)
		return NULLWSTRING;

	MSLString aux = NULLWSTRING;
		
	CHInscription *pInscription = 0;
	if( !pEvent->isTeam() )
	{
		pInscription = (CHInscription *)CHMemoryDataBase::findInscription(m_pInscription->getRegister(),pEvent);
		if( !pInscription )
			return NULLWSTRING;
				
		return "*";
	}

	CHRegister * pRegister = m_pInscription ? (CHRegister*)m_pInscription->getRegister() : 0;

	// Llegados aqui es que es Team, y necesitamos buscar su pareja
	// 1º Buscamos al registro como Member.
	CHMember *pMember = findMember(pEvent,pRegister);
	if( !pMember )
		return NULLWSTRING;

	// 2º Buscamos inscripción de ese member.
	pInscription = (CHInscription *)pMember->getInscription();
	if( !pInscription )
		return NULLWSTRING;
		
	return "*";	
}

CHMember *CHRC32A::findMember(CHEvent *pEvent, CHRegister *pRegister)
{
	MSLSetIterator it(CHMemoryDataBase::getCol(__CHINSCRIPTION));
	CHInscription *pInsc = 0;
	CHMember *pMember = 0;
	while( (pInsc = (CHInscription *)it())!=0 )
	{
		if( pInsc->getEvent()==pEvent )
		{
			MSLSortedVector vMembers;
			pInsc->getMembersVector(vMembers);
			for( short i=0; i<vMembers.entries(); i++)
			{
				pMember = (CHMember *)vMembers[i];
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