/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHRC32C.h
*   Description	:
*
*	Author		: ARTeam
*	Date created: 10-Mar-2009
* 	Project		: ARVMngtModel
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/


#include "stdafx.h"
#include "CHRC32C.h"
#include "CHRLegends.h"
#include "..\CHMngtModel\CHDefinition.h"
#include "..\CHMngtModel\CHEvent.h"
#include "..\CHMngtModel\CHInscription.h"
#include "..\CHMngtModel\CHRegister.h"
#include "..\CHMngtModel\CHMember.h"
static
bool eventInscriptions(const MSLItem* p,const void *n)
{
	CHEvent* pEvent = (CHEvent *)n;
	CHInscription* pInscription = (CHInscription *)p;	

	if ( pEvent && 
		 pInscription->getEventKey() == pEvent->getKey() )
		 return true;

	return false;
}

static 
int orderInscriptionsByNOC(const MSLItem** a, const MSLItem** b)
{
	CHInscription *pInscA=(CHInscription *)(*a);
	CHInscription *pInscB=(CHInscription *)(*b);

	CHRegister* pRegA=(CHRegister*)pInscA->getRegister();
	CHRegister* pRegB=(CHRegister*)pInscB->getRegister();

	int order = strcmp(pRegA->getGroup(),pRegB->getGroup());
	if (order)
		return order;

	order = _wcsicoll(pRegA->getPrnLName(),pRegB->getPrnLName());
	return (order) ? order:pRegA->getRegister()-pRegB->getRegister();
}

CHRC32C::CHRC32C(CReportManager& aReportManager,CReportConfig& aReportConfig,CHEvent* _pEvent)
:CHReportTemplate(aReportManager,aReportConfig,_pEvent)
,m_pEvent(_pEvent)
,m_pLis(0)
,m_index(0)
,m_pLegend(0)
,m_pInscription(0)
,m_lastCountry(NULLSTRING)
{
	m_pLegend = new CHRLegends(this, m_pReport, CH32C);
	loadData();
}

CHRC32C::~CHRC32C()
{
	if (m_pLegend)
		delete m_pLegend;
}

void CHRC32C::OnBeginReport()
{
	MSLString disc = ((CHDefinition &)CHMemoryDataBase::getDefinition()).getCode();
 	MSLString lis = disc + ".C32C" + ".lis";

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
		
		initLabels();

		if ( !m_pLis->setCallBack(1,this) )
			MessageBox(0,MSLWString(aReportMng.getLastError()+"\n"+"check header"+"\n"+lis),L"",MB_OK);
		else if ( !m_pLis->setCallBack(2,this) )
			MessageBox(0,MSLWString(aReportMng.getLastError()+"\n"+"check body"+"\n"+lis),L"",MB_OK);
	}
	else // Si hubo error en el report mostramos el error.
		MessageBox(0,MSLWString(aReportMng.getLastError()+"\n"+lis),L"",MB_OK);
}

unsigned short CHRC32C::OnCallbackFn(struct USR_TAB * pTabInf) 
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

CReportBase::ReportReturn CHRC32C::OnBody()
{
	if( !m_vData.entries() )
		return exit;

	m_pReport->setCursor(0,0);
	centerReport();

	if( !m_pLis->runline(1) )
		return error;

	for (short i=m_index; i<m_vData.entries(); i++)
	{
		m_pInscription = (CHInscription*)m_vData[i];

		if (m_lastCountry!=m_pInscription->getCountry())
		{
			if (!m_pLis->runline(3)) 
				return error;
		}

		MSLSortedVector vMembers;
		m_pInscription->getMembersVector(vMembers);
		
		// Page Break
		if( IsPageBreak( short(m_pLegend->getHeight() + 50 + vMembers.entries() * m_pLis->getVari(21)) ) )
		{
			m_index = i;
			return ok;
		}

		if (m_pEvent->isTeam())
		{
			for (short j=0; j<vMembers.entries(); j++)
			{
				m_pMember = (CHMember*)vMembers[j];
				if (!m_pMember->getRegister())
					continue;

				if (!m_pLis->runline(2)) 
					return error;

				m_pInscription=0;
			}			
		}
		else
		{
			m_pMember = 0;

			if (!m_pLis->runline(2)) 
				return error;
		}

		m_lastCountry = m_pInscription?m_pInscription->getCountry():m_pMember->getCountry();
	}

	if( !m_pLegend->runLis() )
		return error;

	return exit;

}

void CHRC32C::loadData()
{
	if (!m_pEvent )
		return;

	if (m_pEvent->isTeam())
	{
		MSLSet colInscriptionsOfEvent = CHMemoryDataBase::getCol(__CHINSCRIPTION).
			select(eventInscriptions,m_pEvent);

		m_vData=MSLSortedVector(colInscriptionsOfEvent, orderInscriptionsByNOC);
	}
	else
	{
		MSLSet colInscriptionsOfEvent = CHMemoryDataBase::getCol(__CHINSCRIPTION).
			select(eventInscriptions,m_pEvent);

		m_vData=MSLSortedVector(colInscriptionsOfEvent,orderInscriptionsByNOC);
	}
}

void CHRC32C::initLabels()
{
	m_pLis->setData(112,getUserLabel(80)); //"Country"		
	m_pLis->setData(113,getUserLabel(81)); //"Name"		
	m_pLis->setData(117,getUserLabel(82)); //"Code"			
	m_pLis->setData(114,getUserLabel(83)); //"Date of Birth"		
}

void CHRC32C::centerReport()
{
	// Title coor x
	m_pLis->setVari(3,getCenter());

	int width = m_pLis->getVari(111)+	// NOC
				m_pLis->getVari(112)+	// Country
				m_pLis->getVari(113)+	// Name	
				m_pLis->getVari(114);	// Date of Birth

	int corx  = getCenter()-(width/2);

	m_pLis->setVari(1,corx);
}

MSLDate CHRC32C::OnGetEventDate() const
{
	return INVALID_DATE;
}

MSLTime CHRC32C::OnGetEventTime() const
{
	return INVALID_TIME;
}
//////////////////////////////////////////////////////////////////////
// CallBack Methods
//////////////////////////////////////////////////////////////////////
unsigned short CHRC32C::reportHeader_CallBack( struct USR_TAB *pTabInf )
{
	if( !pTabInf )
		return PRNALL;

	centerData(m_pLis,pTabInf);
	
	// NOC
	if( pTabInf->Tb == 1 && pTabInf->Te == 1 && pTabInf->Ce == 2 )
		m_pLis->setData(111,CReportTemplate::m_pHeaderLis->getData(300));

	return PRNALL;
}

unsigned short CHRC32C::reportBody_CallBack( struct USR_TAB *pTabInf )
{
	if( !pTabInf )
		return PRNALL;

	CHRegister * pRegister = 0;
	if( m_pMember )
		pRegister = (CHRegister*) m_pMember->getRegister();
	else if (m_pInscription)
		pRegister = (CHRegister*) m_pInscription->getRegister();

	switch( pTabInf->Te )
	{
	case 1:
		{
			if( !m_pInscription )
			{
				m_pLis->setData(211,"");
				m_pLis->setData(212,"");
			}

			if( !m_pMember )
			{
				m_pLis->setData(213,"");
			}

			centerData(m_pLis,pTabInf);

			switch( pTabInf->Ce )
			{
			case 1: // Name
				if (m_pInscription && m_lastCountry!=m_pInscription->getCountry())
					m_pLis->setData(211,m_pInscription->getGroup());
				else
					m_pLis->setData(211,"");

				break;
			case 2: // NOC Code
				if (m_pInscription && m_lastCountry!=m_pInscription->getCountry())
					m_pLis->setData(212,m_pInscription->getGroupLDescription(m_language));
				else
					m_pLis->setData(212,"");
				break;
			case 3: // Name
				if (m_pMember)
					m_pLis->setData(213,m_pMember->getPrnLName(m_language));
				else if (m_pInscription)
					m_pLis->setData(213,m_pInscription->getPrnLName(m_language));
				else
					m_pLis->setData(213,"");

				break;	
			case 4:
				if (pRegister)
				{
					MSLWString birthDate = pRegister->getBirthDate("%d %b %Y");
					birthDate.toUpper();
					m_pLis->setData(214,birthDate);	
				}				
				break;
			}
		}
		break;
	}
	
	return PRNALL;
}

