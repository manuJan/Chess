/*************************************************************************************
*			© Copyright MSL Software, S.L., 2000 - 2008
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHRC38.h
*	Description	: Report  C38
*
*	Author		: Jose Matas
*	Date created: 21 Enero 2009
* 	Project		: BKVMngtModel
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdafx.h"
#include "CHRC38.h"
#include "CHGCheckList.h"
#include "CHRLegends.h"
#include "CHReportTemplate.h"
#include "CHVCheckList.h"

#include "..\CHMngtModel\CHRegister.h"

bool registerOfGroup(const MSLItem* n,const void *param)
{
	MSLString group = (char *)param;
	CHRegister * pReg = (CHRegister*) n;	

	if (pReg->getGroup() == group)
		return true;
	return false;
}




//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHRC38::CHRC38(CReportManager& aReportManager,CReportConfig& aReportConfig,const char *pGroup)
:RC38(aReportManager,aReportConfig,pGroup)
,m_pLis(0)
,m_pLegends(0)
{	
}

CHRC38::CHRC38(CReportManager& aReportManager,CReportConfig& aReportConfig)
:RC38(aReportManager,aReportConfig)
,m_pLis(0)
,m_pLegends(0)
{
}

CReportBase::ReportReturn CHRC38::OnBody()
{
	
	CReportBase::ReportReturn ret = RC38::OnBody();
	
	return ret;
}


bool CHRC38::isValid()
{
	if (!RC38::isValid())
		return false;

	return true;
}

MSLWString CHRC38::OnGetLine(const int lineNumber,const char *language) const
{
	return CReportTemplate::OnGetLine(lineNumber,language);
}

VCheckList * CHRC38::OnNewCheckList()
{
	return new CHVCheckList(m_Group,VCheckList::eC38,m_language);
}

MSLWString CHRC38::getFunction()
{
	return L"";
}

bool CHRC38::OnLoadLabels()
{
	MSLString lis = /*GDefinition::getCode()*/ + "CH.Labels." + m_language + ".lis";

	CLis& aLis=m_pReport->setLis(lis);
	m_pLabelLis=&aLis;

	if( !m_pLabelLis->isValid() )
	{
		CReportManager& aReportMng=m_pReport->getManager();		
		MessageBox(0,aReportMng.getLastError().toUnicode() + L"\n" + lis.toUnicode(),0,0);
		m_pLabelLis=0;
	}
	
	return m_pLabelLis!=0;
}

bool CHRC38::OnLoadLis()
{
	MSLString lis = "CH.C38";
	lis+= ".lis";
	
	CLis& aLis=m_pReport->setLis(lis);
	m_pLis=&aLis;

	if( !m_pLis->isValid() )
	{
		CReportManager& aReportMng=m_pReport->getManager();
		MSLString sMsg;
		sMsg.format("%s\n%s",aReportMng.getLastError().data(),lis.data());	
		//AfxMessageBox(MSLWString(sMsg));
		m_pLis=0;
		return false;
	}

	initLabels();

	return m_pLis->setCallBack(1,this);
}

void CHRC38::initLabels()
{
	// Asigno el cartel del IF Number (necesito sólo una línea)
	m_pLis->setData(1 , getUserLabel(90)); //"FIDE Number"	
	m_pBaseLis->setData(1101,m_pLis->getData(1));
	
	m_pLis->setData(10,	getUserLabel(91)); //"Master Title"	
	m_pLis->setData(12,	getUserLabel(92)); //"Events"		
}

void CHRC38::OnLisLoaded()
{
	initLabels();
}

RLegend * CHRC38::OnCreateLegend()
{
	m_pLegends = new CHRLegends((CHReportTemplate*)this,m_pReport,CH38); 
	
	return m_pLegends;
}


bool CHRC38::OnExtendedLis()
{

	CHGCheckList *pActual=((CHGCheckList *)m_pCurrent);
	if( !pActual )
		return false;

	m_pLis->setVari(1 ,m_pBaseLis->getVari( 111)); // Font
	m_pLis->setVari(6 ,m_pBaseLis->getVari( 112)); // Font

	m_pLis->setVari(2, m_pBaseLis->getVari(1002)); // Coor x
	m_pLis->setVari(3, m_pBaseLis->getVari(1011)); // Offset x

	m_pLis->setData(11, pActual->getMasterType());	
	m_pLis->setData(13, pActual->getEvents());
	
	int nLine = 0;
	int w = m_pBaseLis->getVari(4011) + 
			m_pBaseLis->getVari(4021) + 
			m_pBaseLis->getVari(4031) + 
			m_pBaseLis->getVari(4041);
	
	m_pLis->setVari(4, w/6);						// Width small
	m_pLis->setVari(5, m_pLis->getVari(4)/2);		// Centrado small
	m_pLis->setVari(14, w/2);						// Width Big

	nLine = 1;
		
	if( !m_pLis->runline(nLine) )
		return false;

	return true;
}

void CHRC38::OnNextGroup()
{
	// Recorro los registros del grupo para crear las leyendas dinámicas
	MSLSet colRegister  = CHMemoryDataBase::getCol(__CHREGISTER);
	MSLSet colRegOfGroup = colRegister.select(registerOfGroup,(void*)m_CurrentGroup.data());
	
	MSLSetIterator it(colRegOfGroup);
	CHRegister *pReg=0;
	while ( (pReg = (CHRegister*) it()) != 0 )
	{
		setDynamicLegends(pReg);
	}
	m_pLegends->createDynamic();
}

void CHRC38::setDynamicLegends(CHRegister *pRegister)
{
	if (!pRegister )
		return;

	/*MSLWString pos = pRegister->getSDescFunction();
	if(pRegister->getFunction())
		m_pLegendBK->setDynamic(pos);
	if(pRegister->getPosition())
		m_pLegendBK->setDynamic(L"(" + pRegister->getSDescPosition() +L")");*/

}
