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

#include "stdafx.h"
#include "CHReportTemplate.h"
#include <ovr/core/TH/GTHEvent.h>
#include <ovr/core/TH/GTHPhase.h>
#include <ovr/core/TH/GTHMatch.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHReportTemplate::CHReportTemplate(CReportManager& aReportManager,CReportConfig& aReportConfig,const GTHEvent *pEvent/*=0*/)
:THReportTemplate(aReportManager,aReportConfig,(GTHEvent *)pEvent)
,dateSel(INVALID_DATE)
{
	int variFont=m_pReport->getManager().getHeader()->getVari(1010);
	font=variFont/1000;
	// Para que si falla algo le ponga por defecto la fuente 6
	if(!font)
		font=6;
}

CHReportTemplate::CHReportTemplate(CReportManager& aReportManager,CReportConfig& aReportConfig,const GTHPhase *pPhase)
:THReportTemplate(aReportManager,aReportConfig,(GTHPhase *)pPhase)
,dateSel(INVALID_DATE)
{
	int variFont=m_pReport->getManager().getHeader()->getVari(1010);
	font=variFont/1000;
	// Para que si falla algo le ponga por defecto la fuente 6
	if(!font)
		font=6;
}

CHReportTemplate::CHReportTemplate(CReportManager& aReportManager,CReportConfig& aReportConfig,const GTHMatch *pMatch)
:THReportTemplate(aReportManager,aReportConfig,(GTHMatch *)pMatch)
,dateSel(INVALID_DATE)
{
	int variFont=m_pReport->getManager().getHeader()->getVari(1010);
	font=variFont/1000;
	// Para que si falla algo le ponga por defecto la fuente 6
	if(!font)
		font=6;
}

CHReportTemplate::CHReportTemplate(CReportManager& aReportManager,CReportConfig& aReportConfig,MSLDate date)
:THReportTemplate(aReportManager,aReportConfig)
,dateSel(date)
{
	int variFont=m_pReport->getManager().getHeader()->getVari(1010);
	font=variFont/1000;
	// Para que si falla algo le ponga por defecto la fuente 6
	if(!font)
		font=6;
}

CHReportTemplate::~CHReportTemplate()
{
}

MSLDate CHReportTemplate::OnGetEventDate() const
{
	MSLDate aDate;
	aDate.now();

	if( m_pHeaderMatch )
		return m_pHeaderMatch->getStartDate();
	if( m_pHeaderPhase )
		return m_pHeaderPhase->getStartDate();
	return m_pHeaderEvent?m_pHeaderEvent->getStartDate():aDate;
}

MSLTime CHReportTemplate::OnGetEventTime() const
{
	MSLTime aTime;
	aTime.now();

	if( m_pHeaderMatch )
		return m_pHeaderMatch->getStartTime();
	if( m_pHeaderPhase )
		return m_pHeaderPhase->getStartTime();

	return m_pHeaderEvent?m_pHeaderEvent->getStartTime():aTime;
}


bool CHReportTemplate::pageBreak(short value)
{
	return IsPageBreak(value);
}

//////////////////////////////////////////////////////////////////////////////////////
// General Methods
//////////////////////////////////////////////////////////////////////////////////////
void CHReportTemplate::centerData(CLis *pLis, struct USR_TAB *pTabInf, int desplX/*=10*/, int desplY/*=10*/)
{
	if( !pLis || !pTabInf )
		return;

	int	dato = (pTabInf->Tb*100) + (pTabInf->Te*10) + pTabInf->Ce;
	alignData(pLis,pTabInf->Tb,dato,desplX,desplY);
}

void CHReportTemplate::alignData(CLis *pLis,int tab,int dato,int desplX,int desplY)
{
	if( !pLis || !tab || dato < 100 )
		return;

	int		align		= pLis->getDataAlig( short(dato) );
	int		idx_offset	= tab*10;
	int		var_height	= idx_offset + 1;

	// Offset x
	short	var_offsetX = short(idx_offset + 2);
	int		width		= pLis->getVari( short(dato) );
	switch( align )
	{
	case 0: // Left
		pLis->setVari(var_offsetX,desplX);
		break;
	case 1: // Center
		pLis->setVari(var_offsetX,short(width/2));
		break;
	case 2: // Right
		pLis->setVari(var_offsetX,short(width-desplX));
		break;
	}

	// Offset y
	short	var_offsetY = short(idx_offset + 3);
	int		height		= pLis->getVari( short(var_height) );
	
	pLis->setVari(var_offsetY,(height / 2) + desplY);
}


void CHReportTemplate::setFontType(CLis *pRepLis, int fHead, MSLString init, MSLString end/*=""*/)
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
