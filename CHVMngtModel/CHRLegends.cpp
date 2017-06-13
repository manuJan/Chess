/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHRLegends.cpp
*   Description	:
*
*	Author		: CHTeam
*	Date created: 7-Mar-2009
* 	Project		: CHVMngtModel
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdafx.h"
#include "CHRLegends.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHRLegends::CHRLegends(CReportTemplate *pTpt, CReport *pRe, long id)
:RLegend(pTpt,pRe)
,m_pLis(0)
,m_idReport(id)
,m_idDynamic(0)
,m_idStatic(0)
{
	switch( m_idReport )
	{
	case CH30:	
		m_mode = eCheckWidth | eCellJumpDyn;
		break;	
	}
}

CHRLegends::~CHRLegends()
{

}

void CHRLegends::createDynamic()
{
	RLegend::createDynamic(m_idDynamic);
}

bool CHRLegends::OnLoadLis()
{
 	MSLString lis = NULLSTRING;
	lis ="CHRLegends.";
	lis+=m_pReportTemplate->getLanguage();
	lis+=".lis";
	
	CLis& aLis=m_pReport->setLis(lis);
	m_pLis=&aLis;

	if( !m_pLis->isValid() )
	{
		CReportManager& aReportMng=m_pReport->getManager();
		MessageBox(0,aReportMng.getLastError().toUnicode()+L"\n"+lis.toUnicode(),L"",MB_OK);
		m_pLis=0;
	}
	
	if( m_pLis )
	{
		loadData();
		return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////
// Class Methods
//////////////////////////////////////////////////////////////////////
void CHRLegends::loadData()
{
	switch(m_idReport)
	{
	case CH30:
		printLegend	(200);
		break;
	case CH32A:
		printLegend	(300,3);
		break;
	case CH38:
		printLegend	(400,3);
		break;
	case CH58:
		printLegend	(500,3);
		break;
	case CH51:
		printLegend	(600,3);
		break;
	case CH74:
		printLegend	(700,3);
		break;
	}
}

void CHRLegends::printLegend(int start,int num_cols/*=1*/)
{
	MSLWString d = L"";
	int lastType=-1;
	for(int i=start;d!="end";i++)
	{	
		d = m_pLis->getData(short(i));

		int type = getTypeBuffer(d);
		if( type != lastType )
		{
			switch( type )
			{
			case 0:
				if( d != "end" )
					m_idNote = addReportNote();
				break;
			case 1:
				m_idDynamic = addDynamicLegend(num_cols);
				break;
			case 2:
				m_idStatic = addStaticLegend(num_cols);
				break;
			}
			
			lastType=type;
		}

		if( d == NULLSTRING )
			continue;

		if( d != "end" )
			addItem(d);
	}
}

int CHRLegends::getTypeBuffer(const wchar_t *pBuffer)
{
	wchar_t *p = wcschr((wchar_t *)pBuffer,'|');
	int n=0;
	
	while(p){
		n++;
		p = wcschr(p+1,'|');
	};

	if( n > 2 )
		n=2;

	return n;
}

void CHRLegends::setDynamic(const wchar_t *key)
{
	RLegend::setDynamic(key,m_idDynamic);
}

int CHRLegends::addReportNote(const wchar_t *title/*=0*/)
{
	return RLegend::addReportNote(title);
}