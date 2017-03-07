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
#include "stdVCH.h"
#include "RCHSchedule.h"
#include "VCHSchedule.h"
#include "CHSessionPoolRound.h"
#include "CHReportTemplate.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
RCHSchedule::RCHSchedule(CHReportTemplate * pTpt,CReport * pRe)
:pReportTemplate(pTpt)
,pReport(pRe)
,pLis(0)
,pCurrent(0)
,pLst(0)
,pView(0)
,adjust(0.0)
,nDate(0)
{
	pView=new VCHSchedule();
}

RCHSchedule::~RCHSchedule()
{
	if (pView)			delete pView;
}

RWBoolean RCHSchedule::loadLis()
{
	RWCString lang=DBApplication::getAppLanguage();
	RWCString lisSchedule="CH.C08."+lang+".lis";

	CReportManager& aReportMng=pReport->getManager();
	CLis& aLis=pReport->setLis(lisSchedule);
	pLis=&aLis;
	// Cargamos el Numero de Oris
	if( !pLis->isValid() )
	{
		AfxMessageBox(RWWString(aReportMng.getLastError()+"\n"+lisSchedule,RWWString::ascii));
		pLis=0;
		return false;
	}
	pReportTemplate->setVaris(pLis);

	pReport->setCursor(0,0);
	return true;
}

RWBoolean RCHSchedule::runLis()
{
	RWBoolean rc=pLis->setCallBack(102,pReportTemplate);
	int widthT=pLis->getVari(1101)+pLis->getVari(1201)+pLis->getVari(1301)+
		(pLis->getVari(1401)*pLis->getVari(11))+pLis->getVari(1501)+
		(pLis->getVari(1601)*pLis->getVari(12));
	CReportManager& aReportMng=pReport->getManager();
	pLis->setVari(9,(aReportMng.getWidthPaper()-aReportMng.getLeftMargin()-widthT)/2);
	if( rc ) //dato
		rc=pLis->runline(1010);
	//salto un poco
//	pLis->runline(10);
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
	return pView;
}

void RCHSchedule::assignVari(const short nVble, const int value)
{
	pLis->setVari(nVble, value);
}

int RCHSchedule::getVari(const short nVble) const
{
	return pLis->getVari(nVble);
}

unsigned short RCHSchedule::assignData(struct USR_TAB * pTableInfo)
{
	int rec=0;
	if (!pView)
		return NOPRIN;

	switch ( pTableInfo->Te )
	{
		case 0:
		{	
			switch ( pTableInfo->Ce )
			{
				case 1: //number date
				{
					RWCString aux=NULLRWSTRING;
					rec=(*pView)++;
					pCurrent=(CHSessionPoolRound*)pView->getData(rec);
					pLis->setVari(5,1);
					if (!pLst || pLst->getSessionStartDate()!=pCurrent->getSessionStartDate())
					{
						pLis->setData(2010,++nDate);
						pLis->setVari(5,1);
						pLis->setVari(6,0);
						pLis->setVari(7,1);
						pLis->setVari(8,0);
					}
					else
					{
						if (pLst->getSessionStartDate()==pCurrent->getSessionStartDate())
							pLis->setVari(5,0);
						if (pLst->getSession()==pCurrent->getSession())
							pLis->setVari(7,0);
						if (pView->isLast())
						{
							pLis->setVari(6,1);
							pLis->setVari(8,1);
						}
						pLis->setData(2010,0);
					}
					break;
				}
				case 2: //date
					if (!pLst || pLst->getSessionStartDate()!=pCurrent->getSessionStartDate())
						pLis->setData(2011,RWCString(pCurrent->getSessionStartDate().strip(RWCString::leading,'0')));
					else
						pLis->setData(2011,0);
					break;
				case 3: //Event phase/pool
					pLis->setData(2012,pCurrent->getFullEventDescription());
					break;
				case 4: //session
					if (!pLst || pLst->getSession()!=pCurrent->getSession())
						pLis->setData(2013,pCurrent->getSessionDescription());
					else
						pLis->setData(2013,0);
					break;
				case 5: //start time
					if (!pLst || pLst->getSession()!=pCurrent->getSession())
						pLis->setData(2014,RWCString(pCurrent->getSessionStartTime().strip(RWCString::leading,'0')));
					else
						pLis->setData(2014,0);
					if (!pLis->getVari(12))
						pLst=pCurrent;
					break;
				case 6: //Number of Matches
					pLis->setData(2015,pCurrent->getNumMatches());
					pLst=pCurrent;
					break;
			}
		}
	}
    return PRNALL;
}