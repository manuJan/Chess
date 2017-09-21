/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHRC30.cpp
*   Description	:
*
*	Author		: ARTeam
*	Date created: 5-Julio-2006
* 	Project		: ARVMngtModel
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdafx.h"
#include "CHRC30.h"
#include "..\CHMngtModel\CHDefinition.h"
#include "..\CHMngtModel\CHEvent.h"
#include "..\CHMngtModel\CHInscription.h"
#include "..\CHMngtModel\CHRegister.h"
#include "..\CHMngtModel\CHMember.h"
#include "CHRLegends.h"

static bool selectGroupInscriptions(const MSLItem* p,const void *n)
{
	CHInscription *pInsc = (CHInscription *)p;	
	if( !pInsc )
		return false;

	GGroup * pGroup = (GGroup*)n;
	if (!pGroup)
		return false;

	if( pInsc->getGroup() == pGroup->getGroup() )
		return true;

	return false;
	UNREFERENCED_PARAMETER(n);
}

static
int orderEntriesByGroupEventAndLDesc(const MSLItem** a, const MSLItem** b)
{
	CHInscription *pInsA=(CHInscription *)(*a);
	CHInscription *pInsB=(CHInscription *)(*b);

	GRegister *pRegA = pInsA->getRegister();
	GRegister *pRegB = pInsB->getRegister();

	int order=strcmp(pInsA->getGroup(),pInsB->getGroup());
	if( order )
		return order;

	order = strcmp(pInsA->getEventCode(),pInsB->getEventCode());
	if( order )
		return order;

	order = pRegB->getType() - pRegA->getType();
	if( order )
		return order;

	return strcmp(pInsA->getName2().toAscii(),pInsB->getName2().toAscii());
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

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHRC30::CHRC30(CReportManager& aReportManager,CReportConfig& aReportConfig)
:CHReportTemplate(aReportManager,aReportConfig)
,m_pLis(0)
,m_index(0)
,m_pGroup(0)
,m_men(0)
,m_women(0)
,m_total(0)
,m_countries(0)
,m_t_men(0)
,m_t_women(0)
,m_t_total(0)
,m_numEvents(0)
,m_vEvents(orderEvents)
,m_pLegend(0)
{
	m_pLegend = new CHRLegends(this,m_pReport, CH30);
	loadData();
}

CHRC30::~CHRC30()
{
	if (m_pLegend)
		delete m_pLegend;
}

//////////////////////////////////////////////////////////////////////
// Overloaded Methods
//////////////////////////////////////////////////////////////////////
void CHRC30::OnBeginReport()
{
	// Report Name
	MSLString disc = ((CHDefinition &)CHMemoryDataBase::getDefinition()).getCode();
 	MSLString lis = disc + ".C30" + ".lis";

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

		m_pLis->setData(111,CReportTemplate::m_pHeaderLis->getData(300)); // NOC/NPC/CNO/...
		m_pReport->setZeroAs(L"0");		
		
		if( !m_pLegend || (m_pLegend && !m_pLegend->loadLis()) )
			MessageBox(0,L"Error loading legends",L"",MB_OK);
		
		initLabels();
		initVaris();

		if ( !m_pLis->setCallBack(1,this) )
			MessageBox(0,MSLWString(aReportMng.getLastError()+"\n"+"check header"+"\n"+lis),L"",MB_OK);
		else if ( !m_pLis->setCallBack(2,this) )
			MessageBox(0,MSLWString(aReportMng.getLastError()+"\n"+"check body"+"\n"+lis),L"",MB_OK);			
		else if ( !m_pLis->setCallBack(3,this) )
			MessageBox(0,MSLWString(aReportMng.getLastError()+"\n"+"check totals"+"\n"+lis),L"",MB_OK);
	}
	else // Si hubo error en el report mostramos el error.
	{
		MessageBox(0,MSLWString(aReportMng.getLastError()+"\n"+lis),L"",MB_OK);
	}
}

void CHRC30::initLabels()
{
	m_pLis->setData(122,getUserLabel(30)); //"Men"
	m_pLis->setData(123,getUserLabel(31)); //"Women"
	m_pLis->setData(125,getUserLabel(32)); //"Total"
	m_pLis->setData(112,getUserLabel(33)); //"Entries per event"
	m_pLis->setData(114,getUserLabel(34)); //"Players"
	m_pLis->setData(316,getUserLabel(35)); //"Total:"
}

void CHRC30::initVaris()
{
	m_pLis->setVari(50,1);
	m_pLis->setVari(51,m_numEvents);
	m_pLis->setVari(114,m_numEvents*m_pLis->getVari(124));
}

int	CHRC30::getNumEvents()
{
	m_vEvents=MSLSortedVector(CHMemoryDataBase::getCol(__CHEVENT),orderEvents);
	return m_vEvents.entries();
}

unsigned short CHRC30::OnCallbackFn(struct USR_TAB * pTabInf) 
{ 
    switch ( pTabInf->Tb ) 
    { 
		case 1: 
			return reportHeader_CallBack(pTabInf); 
		case 2: 
			return reportBody_CallBack(pTabInf); 
		case 3: 
			return reportTotals_CallBack(pTabInf); 
    } 

    return CHReportTemplate::OnCallbackFn(pTabInf); 
} 


CReportBase::ReportReturn CHRC30::OnBody()
{
	m_pReport->setCursor(0,0);
	centerReport();

	// Header
	if( !m_pLis->runline(1) )
		return error;

	// Body
	short i=0;
	for( i=m_index; i< m_vData.entries(); i++ )
	{
		CHInscription *pCurrentIns = (CHInscription *)m_vData[i];
		if( !pCurrentIns )
			continue;

		GGroup *pCurrentGroup = CHMemoryDataBase::findGroup(pCurrentIns->getGroup());
		if( pCurrentGroup )
		{
			if( m_pGroup && pCurrentGroup->getGroup() != m_pGroup->getGroup() )
			{
				if( IsPageBreak( short(m_pLis->getVari(21) + short(m_pLegend->getHeight() ) ) ) )
				{
					m_index = i;
					return ok;
				}

				if( !m_pLis->runline(2) )
					return error;

				m_countries++;

				/*m_t_men	+= m_men;
				m_t_women += m_women;
				m_t_total += m_total;*/
				
				for (int j=0;j<m_numEvents;j++)
					m_t_division[j]+=m_division[j];
				
				m_men	= 0;
				m_women	= 0;
				m_total	= 0;

				for (int j=0;j<m_numEvents;j++)
					m_division[j]=0;
			}

			m_pGroup	= pCurrentGroup;
			/*if( pCurrentIns->getSex() == MAN )
				m_men++;
			else if( pCurrentIns->getSex() == WOMAN )
				m_women++;*/

			int indexEvent = m_vEvents.index(pCurrentIns->getEvent());
			if (indexEvent>=0)
				m_division[indexEvent]++;

			//m_total=m_men+m_women;
		}
	}

	if( IsPageBreak( short(m_pLis->getVari(31) + 100)) )
	{
		m_index = i;
		return ok;
	}

	if( !m_pLis->runline(2) )
		return error;

	m_countries++;
	m_t_men	+= m_men;
	m_t_women += m_women;
	m_t_total += m_total;

	for (int j=0;j<m_numEvents;j++)
		m_t_division[j]+=m_division[j];

	// Total
	if( !m_pLis->runline(3) )
		return error;

	if( !m_pLegend->runLis() )
		return error;

	return exit;
}

//////////////////////////////////////////////////////////////////////
// Class Methods
//////////////////////////////////////////////////////////////////////
void CHRC30::loadData()
{
	MSLSortedVector gsvInscriptions(CHMemoryDataBase::getCol(__CHINSCRIPTION),orderEntriesByGroupEventAndLDesc);
	m_numEvents = getNumEvents();
	m_division = new int[m_numEvents];
	m_t_division = new int[m_numEvents];
	for (int j=0;j<m_numEvents;j++)
	{
		m_division[j]=0;
		m_t_division[j]=0;
	}
	m_vData.clear();
	m_vData = gsvInscriptions;
}

void CHRC30::centerReport()
{
	int width = m_pLis->getVari(111)					+ // NOC
				m_pLis->getVari(112)*m_pLis->getVari(50)+ // Men
				m_pLis->getVari(113)*m_pLis->getVari(50)+ // Women
				m_pLis->getVari(114)+  // Divisions
				m_pLis->getVari(115); // Total Competitors

	int corx  = getCenter()-(width/2);

	m_pLis->setVari(1,corx);
}

//////////////////////////////////////////////////////////////////////
// CallBack Methods
//////////////////////////////////////////////////////////////////////
unsigned short CHRC30::reportHeader_CallBack( struct USR_TAB *pTabInf )
{
	if( !pTabInf )
		return PRNALL;

	switch( pTabInf->Te )
	{
		case 1:
		{
			centerData(m_pLis,pTabInf);
			break;
		}
		case 2:
		{
			centerData(m_pLis,pTabInf);
			
			switch( pTabInf->Ce )
			{
				case 4:
				{
					MSLWString tmp = NULLWSTRING;
					
					CHEvent * pEvent = (CHEvent*)m_vEvents[pTabInf->C_Count-1];
					if (pEvent)
						tmp = pEvent->getCodeReports().toUnicode();

					m_pLis->setData(124,tmp);
				}
				break;
			}
		}
	}
	return PRNALL;
}

unsigned short CHRC30::reportBody_CallBack( struct USR_TAB *pTabInf )
{
	if( !pTabInf )
		return PRNALL;

	switch( pTabInf->Te )
	{
	case 1:
		{
			if( !m_pGroup )
				return PRNALL;

			centerData(m_pLis,pTabInf);

			switch( pTabInf->Ce )
			{
			case 1: // NOC
				{
					MSLWString tmp = NULLWSTRING;
					
					tmp+= m_pGroup->getGroup().toUnicode();
					tmp+= L" - ";
					tmp+= m_pGroup->getLDescription(m_language);

					m_pLis->setData(211,tmp);
				}
				break;
			case 2: // Men
				m_men = getPlayers(m_pGroup, MAN);
				m_t_men+=m_men;
				m_pLis->setData(212, m_men);
				break;
			case 3: // Women				
				m_women = getPlayers(m_pGroup, WOMAN);
				m_t_women+=m_women;
				m_pLis->setData(213, m_women);
				break;
			case 4:
				m_pLis->setData(214,m_division[pTabInf->C_Count-1]);
				break;
			case 5: // Totals
				m_total=m_men+m_women;
				m_t_total+=m_total;
				m_pLis->setData(215,m_total);
				break;
			}
		}
		break;
	}

	
	return PRNALL;
}

unsigned short CHRC30::reportTotals_CallBack( struct USR_TAB *pTabInf )
{
	if( !pTabInf )
		return PRNALL;

	switch( pTabInf->Te )
	{
	case 1:
		{
			if( !m_pGroup )
				return PRNALL;

			centerData(m_pLis,pTabInf);

			switch( pTabInf->Ce )
			{
			case 1: // NOC
				{
					MSLWString tmp = NULLWSTRING;
										
					tmp+= m_pLis->getData(316);					
					tmp+= TOWSTRING(m_countries,L"0");

					m_pLis->setData(311,tmp);
				}
				break;
			case 2: // Men				
				m_pLis->setData(312,m_t_men);
				break;
			case 3: // Women
				m_pLis->setData(313,m_t_women);
				break;
			case 4: // Division
				m_pLis->setData(314,m_t_division[pTabInf->C_Count-1]);
				break;
			case 5: // Totals
				m_pLis->setData(315,m_t_total);
				break;
			}
		}
		break;
	}
	
	return PRNALL;
}

int	CHRC30::getPlayers(GGroup * pGroup, MSLString gender)
{
	MSLSet colGroupInscriptions = CHMemoryDataBase::getCol(__CHINSCRIPTION).select(selectGroupInscriptions, pGroup);
		
	MSLSortedVector vInscriptions =	MSLSortedVector(colGroupInscriptions);
	MSLSortedVector vRegisters;
	for (short i=0;i<vInscriptions.entries();i++)
	{
		CHInscription* pIns = (CHInscription*) vInscriptions[i];
		CHEvent *pEvent=(CHEvent*)pIns->getEvent();
		if (pEvent->getSex()!=gender)
			continue;

		if (pIns->getType()==GRegister::individual)
		{
			CHRegister* pReg = (CHRegister*) pIns->getRegister();
			if (pReg)
			{
				if (!vRegisters.find(pReg))
					vRegisters.insert(pReg);			
			}
		}
		else
		{
			MSLSortedVector vMembers;
			pIns->getMembersVector(vMembers);
			for (short j=0;j<vMembers.entries();j++)
			{
				CHMember* pMember = (CHMember*)vMembers[j];
				if (pMember->getRegister())
				{
					CHRegister* pReg = (CHRegister*) pMember->getRegister();
					if (!vRegisters.find(pReg))
						vRegisters.insert(pReg);
				}
			}
		}
	}

	return vRegisters.entries();
}