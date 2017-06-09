/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: RCHSchedule.cpp
*   Description	: 
*
*	Author		: CH Team
*	Date created:  2-1-2006
* 	Project		:
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#include "stdafx.h"
#include "RCHSchedule.h"
#include "VCHSchedule.h"
#include "CHSessionPoolRound.h"
#include "CHReportTemplate.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
RCHSchedule::RCHSchedule(CHReportTemplate * pTpt,CReport * pRe)
:m_pReportTemplate(pTpt)
,m_pReport(pRe)
,m_pLis(0)
,m_pCurrent(0)
,m_pLst(0)
,m_pView(0)
,m_adjust(0.0)
,m_nDate(0)
,m_index(-1)
{
	m_pView=new VCHSchedule();	
}

RCHSchedule::~RCHSchedule()
{
	if (m_pView)			
		delete m_pView;
}

bool RCHSchedule::loadLis()
{
	MSLString lisSchedule="CH.C08.lis";

	CReportManager& aReportMng=m_pReport->getManager();
	CLis& aLis=m_pReport->setLis(lisSchedule);
	m_pLis=&aLis;
	// Cargamos el Numero de Oris
	if( !m_pLis->isValid() )
	{
		MessageBox(0,MSLWString(aReportMng.getLastError()+"\n"+lisSchedule),L"",MB_OK);		
		m_pLis=0;
		return false;
	}

	initLabels();

	m_pReportTemplate->setVaris(m_pLis);
	m_pReport->setCursor(0,0);
	return true;
}

void RCHSchedule::initLabels()
{
	m_pLis->setData(1010, m_pReportTemplate->getUserLabel(10)); // "Day"					
	m_pLis->setData(1011, m_pReportTemplate->getUserLabel(11)); // "Date"				
	m_pLis->setData(1012, m_pReportTemplate->getUserLabel(12)); // "Event"
	m_pLis->setData(1013, m_pReportTemplate->getUserLabel(13)); // "Session"
	m_pLis->setData(1014, m_pReportTemplate->getUserLabel(14)); // "Start Time"
	m_pLis->setData(1015, m_pReportTemplate->getUserLabel(15)); // "Number of Matches"
}

bool RCHSchedule::runLis()
{
	bool rc=m_pLis->setCallBack(102,m_pReportTemplate);
	int widthT=m_pLis->getVari(1101)+m_pLis->getVari(1201)+m_pLis->getVari(1301)+
		(m_pLis->getVari(1401)*m_pLis->getVari(11))+m_pLis->getVari(1501)+
		(m_pLis->getVari(1601)*m_pLis->getVari(12));
	CReportManager& aReportMng=m_pReport->getManager();
	m_pLis->setVari(9,(aReportMng.getWidthPaper()-aReportMng.getLeftMargin()-widthT)/2);
	if( rc ) //dato
		rc=m_pLis->runline(1010);

	//salto un poco
//	m_pLis->runline(10);
	return rc;
}

unsigned short RCHSchedule::entries(struct USR_TAB * pTableInfo)
{
	switch (pTableInfo->Tb)
	{
	case 102:
		return assignData(pTableInfo);
		break;
	}
	return PRNALL;
}

VCHSchedule *RCHSchedule::getView()
{
	return m_pView;
}

void RCHSchedule::assignVari(const short nVble, const int value)
{
	m_pLis->setVari(nVble, value);
}

int RCHSchedule::getVari(const short nVble) const
{
	return m_pLis->getVari(nVble);
}

unsigned short RCHSchedule::assignData(struct USR_TAB * pTableInfo)
{
	if (!m_pView)
		return NOPRIN;

	switch ( pTableInfo->Te )
	{
		case 0:
		{	
			switch ( pTableInfo->Ce )
			{
				case 1: //number date
				{
					MSLString aux=NULLSTRING;					
					m_index++;
					m_pCurrent=(CHSessionPoolRound*) m_pView->getData(m_index);					
					m_pLis->setVari(5,1);
					if (!m_pLst || m_pLst->getSessionStartDate()!=m_pCurrent->getSessionStartDate())
					{
						m_pLis->setData(2010,++m_nDate);
						m_pLis->setVari(5,1);
						m_pLis->setVari(6,0);
						m_pLis->setVari(7,1);
						m_pLis->setVari(8,0);
					}
					else
					{
						if (m_pLst->getSessionStartDate()==m_pCurrent->getSessionStartDate())
							m_pLis->setVari(5,0);
						if (m_pLst->getSession()==m_pCurrent->getSession())
							m_pLis->setVari(7,0);

						if ( (m_index+1)==m_pView->getEntries() )
						{
							m_index=-1;
							m_pLis->setVari(6,1);
							m_pLis->setVari(8,1);
						}

						m_pLis->setData(2010,0);
					}
					break;
				}
				case 2: //date
					if (!m_pLst || m_pLst->getSessionStartDate()!=m_pCurrent->getSessionStartDate())
						m_pLis->setData(2011,m_pCurrent ? MSLString(m_pCurrent->getSessionStartDate().strip(MSLString::leading,'0')) : L"");
					else
						m_pLis->setData(2011,0);
					break;
				case 3: //Event phase/pool
					m_pLis->setData(2012,m_pCurrent ? m_pCurrent->getFullEventDescription() : L"");
					break;
				case 4: //session
					if (!m_pLst || m_pLst->getSession()!=m_pCurrent->getSession())
						m_pLis->setData(2013,m_pCurrent ? m_pCurrent->getSessionDescription() : L"");
					else
						m_pLis->setData(2013,0);
					break;
				case 5: //start time
					if (!m_pLst || m_pLst->getSession()!=m_pCurrent->getSession())
						m_pLis->setData(2014,m_pCurrent ? MSLString(m_pCurrent->getSessionStartTime().strip(MSLString::leading,'0')) : L"");
					else
						m_pLis->setData(2014,0);
					if (!m_pLis->getVari(12))
						m_pLst=m_pCurrent;
					break;
				case 6: //Number of Matches
					m_pLis->setData(2015,m_pCurrent ? m_pCurrent->getNumMatches() : 0);
					m_pLst=m_pCurrent;
					break;
			}
		}
	}
    return PRNALL;
}