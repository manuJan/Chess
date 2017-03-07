/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHRC38Ext.cpp
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
#include "CHRC38Ext.h"
#include <Sports/CH/Data/CHMemoryDataBase.h>
#include <Sports/CH/Data/CHEvent.h>
#include <Sports/CH/Data/CHRegister.h>
#include <Sports/CH/Data/CHInscription.h>
#include <Sports/CH/Data/CHMember.h>
#include <Sports/CH/Data/CHDiscipline.h>
#include "CHCheckList.h"
#include "CHRC38.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHRC38Ext::CHRC38Ext(CReportTemplate *pRepTem, CReport *pRep)
:RC38Ext(pRepTem,pRep)
,pCHRegister(0)
,pSpLegend(0)
{
}

CHRC38Ext::~CHRC38Ext()
{
}

bool CHRC38Ext::run()
{
	if(!pCheckList)
		return false;

	CHCheckList *pCheck=(CHCheckList *)pCheckList;
	pCHRegister=(CHRegister *)pCheck->getRegister();
	//solo pinto esta linea para los jugadores
	if (pCHRegister->getType()<CHRegister::judge)
	if (!pLis->runline(2000))
		return false;
	
	return true;
}

short CHRC38Ext::getHeight()
{
	return short(pLis->getVari(1001));
}

void CHRC38Ext::prepare()
{
	RWCString lang=DBApplication::getAppLanguage();
	RWCString SpecialLaneLisName="CH.C38."+lang+".lis";
	// Instanciamos una referencia al lis del report Ctry Event.
	CLis& aLis=pReport->setLis(SpecialLaneLisName);
	pLis=&aLis;

	if (pLis->isValid())
	{
		pLis->setCallBack(2000,this,specialLaneCallBack);

		int withCol1=((CHRC38 *)pReportTemplate)->getRightOffset();
		int withCol2=((CHRC38 *)pReportTemplate)->getWidthPrintNamesColumn()+
					 ((CHRC38 *)pReportTemplate)->getWidthTVNamesColumn();
		int withCol3=((CHRC38 *)pReportTemplate)->getWidthScoreboardNamesColumn()+
					 ((CHRC38 *)pReportTemplate)->getWidthWNPANamesColumn();
		int heightTm=((CHRC38 *)pReportTemplate)->getTemplateHeight();
		int fontData=((CHRC38 *)pReportTemplate)->getFontData();

		pLis->setVari(2001,withCol1);
		pLis->setVari(2011,withCol2);
		pLis->setVari(2012,withCol2/2);
		pLis->setVari(2021,withCol3);
		pLis->setVari(2022,withCol3/2);
		pLis->setVari(1001,heightTm);
		pLis->setVari(1002,heightTm*4/5);
		// Set to normal font
		fontData=(fontData/2)*2;
		pLis->setVari(1011,fontData);
		pLis->setVari(1012,fontData+1);
		
		bOKLis=true;
	}
}

void CHRC38Ext::setLegend(RLegend *value)
{
	pSpLegend=value;
}

unsigned short CHRC38Ext::generalLineOfLegendCallBack (struct USR_TAB *pTabInf)
{
	switch ( pTabInf->Ce )
	{
	case 10:
		pLis->setData(0,getEventOfRegister());
		break;
	case 20:
		{
			CString handed=_T("");
			
			if (pCHRegister->getMasterType())
				handed=pCHRegister->getMasterTypeAsString();
			
			pLis->setData(0,handed);
			break;
		}
	}
	return PRNALL;
}

RWCString CHRC38Ext::getEventOfRegister()
{
	RWCString text=NULLRWSTRING;
	CHInscription *pInscription=0;

	CHCheckList *pCheck=(CHCheckList *)pCheckList;
	GSortedVector& aVInsc=pCheck->getVectorInsc();

	for(size_t i=0; i<aVInsc.entries(); i++)
	{
		pInscription=(CHInscription *)aVInsc[i]->getElement();
		CHEvent *pEvent=(CHEvent*)pInscription->getEvent();
		text+=pEvent->getSDescription().toMultiByte();
		text+=((aVInsc.entries()>1 && i+1<aVInsc.entries())?", ":" ");
//		pSpLegend->addlegend(pEvent->getSDescription(),((SQRC38 *)pReportTemplate)->getLegendSeparator(),pEvent->getLDescription());
	}
	return text;
}

unsigned short CHRC38Ext::specialLaneCallBack( struct USR_TAB * pTabInf )
{
	CHRC38Ext *pReportBase=(CHRC38Ext*)pTabInf->lusrext;
	if( pReportBase )
		return pReportBase->generalLineOfLegendCallBack(pTabInf);

	return OUTTAB;
}