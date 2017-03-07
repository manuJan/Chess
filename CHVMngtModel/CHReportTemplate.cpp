/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHReportTemplate.cpp
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:19-12-2005
*   Project     :CHV Model               
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///

#include "stdVCH.h"
#include "CHReportTemplate.h"
#include <Core/TH/GTHEvent.h>
#include <Core/TH/GTHPhase.h>
#include <Core/TH/GTHMatch.h>
#include <Sports/CH/Data/CHMemoryDataBase.h>
#include <Sports/CH/Data/CHDiscipline.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHReportTemplate::CHReportTemplate(CReportManager& aReportManager,CReportConfig& aReportConfig,const GTHEvent *pEvent/*=0*/)
:THReportTemplate(aReportManager,aReportConfig,(GTHEvent *)pEvent)
,dateSel(INVALID_RWDATE)
{
	int variFont=pReport->getManager().getHeader()->getVari(1010);
	font=variFont/1000;
	// Para que si falla algo le ponga por defecto la fuente 6
	if(!font)
		font=6;
}

CHReportTemplate::CHReportTemplate(CReportManager& aReportManager,CReportConfig& aReportConfig,const GTHPhase *pPhase)
:THReportTemplate(aReportManager,aReportConfig,(GTHPhase *)pPhase)
,dateSel(INVALID_RWDATE)
{
	int variFont=pReport->getManager().getHeader()->getVari(1010);
	font=variFont/1000;
	// Para que si falla algo le ponga por defecto la fuente 6
	if(!font)
		font=6;
}

CHReportTemplate::CHReportTemplate(CReportManager& aReportManager,CReportConfig& aReportConfig,const GTHMatch *pMatch)
:THReportTemplate(aReportManager,aReportConfig,(GTHMatch *)pMatch)
,dateSel(INVALID_RWDATE)
{
	int variFont=pReport->getManager().getHeader()->getVari(1010);
	font=variFont/1000;
	// Para que si falla algo le ponga por defecto la fuente 6
	if(!font)
		font=6;
}

CHReportTemplate::CHReportTemplate(CReportManager& aReportManager,CReportConfig& aReportConfig,RWDate date)
:THReportTemplate(aReportManager,aReportConfig)
,dateSel(date)
{
	int variFont=pReport->getManager().getHeader()->getVari(1010);
	font=variFont/1000;
	// Para que si falla algo le ponga por defecto la fuente 6
	if(!font)
		font=6;
}

CHReportTemplate::~CHReportTemplate()
{
}

CReportConfig *CHReportTemplate::getReportConfig()
{
	return pConfig;
}

CLis *CHReportTemplate::getLis() const
{
	return 0;
}

RWBoolean CHReportTemplate::OnRun()
{
	if(!prepareTemplate())
		return false;
	return THReportTemplate::OnRun();
	//return true;
}



RWCString CHReportTemplate::getDateWithoutZero(RWDate date,RWCString format)
{
	RWCString temp=format.subString("%d");
	RWCString weekday=date.asString(temp);
	
	temp=format.remove(0,3);	//Quito el formato del weekday
	RWCString restDate=date.asString(temp);
	RWCString dateWB=restDate.strip(RWCString::leading,'0');
	weekday = weekday.strip(RWCString::leading,'0');
	weekday+=" ";
	weekday+=dateWB;
	weekday.toUpper();

	return weekday;
}
/*
RWCString CHReportTemplate::OnGetEventCode() const
{
	return pHeaderEvent?pHeaderEvent->getSex()+pHeaderEvent->getEvent():NULLRWSTRING;
}


RWCString CHReportTemplate::OnGetPhaseCode() const
{
	return pHeaderPhase?pHeaderPhase->getPhase():NULLRWSTRING;
}
*/
RWCString CHReportTemplate::OnGetVenueCode() const
{
	CHDiscipline  aDiscipline=(CHDiscipline &)CHMemoryDataBase::getDiscipline();
	GVenue *pVenue=CHMemoryDataBase::findVenue(aDiscipline.getVenueCode());  

	return pVenue?pVenue->getVenue():NULLRWSTRING;
}

RWDate CHReportTemplate::OnGetEventDate() const
{
	RWDate aDate;
	aDate.now();

	if( pHeaderMatch )
		return pHeaderMatch->getStartDate();
	if( pHeaderPhase )
		return pHeaderPhase->getStartDate();
	return pHeaderEvent?pHeaderEvent->getStartDate():aDate;
}

RWTime CHReportTemplate::OnGetEventTime() const
{
	RWTime aTime;
	aTime.now();

	if( pHeaderMatch )
		return pHeaderMatch->getStartTime();
	if( pHeaderPhase )
		return pHeaderPhase->getStartTime();

	return pHeaderEvent?pHeaderEvent->getStartTime():aTime;
}



RWBoolean CHReportTemplate::prepareTemplate()
{
	CReportManager& aReportMng  = pReport->getManager();
	return true;
}

RWBoolean CHReportTemplate::pageBreak(short value)
{
	return IsPageBreak(value);
}

void CHReportTemplate::setFontType(CLis *pRepLis, int fHead, RWCString init, RWCString end/*=""*/)
{
	if (!pRepLis)
		return;

	if (init.length()==0)
		return;

	size_t a=atoi(init.data());
	size_t b=(end.length()>0)?atoi(end.data()):a;
	if (a>b)
		return;

	long newF=0, nFont=0,sFont=0, tFont=0, base=0;

	for (size_t i=a; i<=b; i++)
	{
		nFont=pRepLis->getVari(short(i));
		base=(nFont>=10000)?10000:1000;

		tFont=nFont%10;
		if (tFont<0 || tFont>3)
			continue;

		sFont=((nFont%base)/10)+((fHead==4)?-1:+1);
		nFont=nFont/(base);
		if (nFont==fHead || (nFont!=4 && nFont!=6))
			continue;
		// Set new font.
		newF=fHead*base+sFont*10+tFont;
		pRepLis->setVari(short(i), newF);
	}
}
void CHReportTemplate::setVaris(CLis *pLis)
{
	int fontResult=0;
	
	for(short i=500;i<524;i++)
	{
		fontResult=int(pLis->getVari(i));
		int fontInitial=fontResult/1000;

		fontResult=fontResult-fontInitial*1000+font*1000;
		// Verdana es mas grande que las demas y le resto uno para que no se salga
		if(font==4)
			fontResult-=10;
		pLis->setVari(i,fontResult);

	}
}
