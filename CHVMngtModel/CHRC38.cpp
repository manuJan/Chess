/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHRC38.cpp
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
#include "CHRC38.h"
#include "CHRLegends.h"
#include <Sports/CH/Data/CHInscription.h>
#include <Sports/CH/Data/CHMember.h>
#include <Sports/CH/Data/CHDiscipline.h>
#include <Sports/CH/Data/CHMemoryDataBase.h>
#include "VCHCheckList.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHRC38::CHRC38(CReportManager& aReportManager,CReportConfig& aReportConfig,const char *pGroup)
:RC38(aReportManager,aReportConfig,pGroup)
{
}

CHRC38::CHRC38(CReportManager& aReportManager,CReportConfig& aReportConfig)
:RC38(aReportManager,aReportConfig)
{
}

CHRC38::~CHRC38()
{
}

RWBoolean CHRC38::OnLoadLis()
{
	RWCString lang = DBApplication::getAppLanguage();
	RWCString lis = "CH.C38." + lang + ".lis";

	CLis& aLis=pReport->setLis(lis);
	pLis=&aLis;

	if( !pLis->isValid() )
	{
		CReportManager& aReportMng=pReport->getManager();
		AfxMessageBox(TOWSTRING(aReportMng.getLastError()+"\n"+lis));
		pLis=0;
	}

	pLis->setCallBack(1,this);

	return pLis!=0;
}

void CHRC38::OnLisLoaded()
{
	// cartel FIFA ID
	pBaseLis->setData(1101,pLis->getData(1));

	pLis->setVari( 10,pBaseLis->getVari(31));	//height
	pLis->setVari(132,pBaseLis->getVari(43));	//offset_y
	pLis->setVari(1000,pBaseLis->getVari(111));	//font cabeceras
	pLis->setVari(1001,pBaseLis->getVari(112));	//font datos
}

int CHRC38::OnHeight(const GCheckList * pNext)
{
	GCheckList * pCheckList = (GCheckList *)pNext;
	if( !pCheckList )
		return 0;

	return pBaseLis->getVari(31);
}

RWBoolean CHRC38::OnExtendedLis()
{
	// Actualizamos las varis desde zz
	int a=pBaseLis->getVari( 111);
	a=pBaseLis->getVari(1002);
	a=pBaseLis->getVari(1011);
	pLis->setVari(1 ,pBaseLis->getVari( 111)); // Font
	pLis->setVari(2, pBaseLis->getVari(1002)); // Coor x
	pLis->setVari(3 ,pBaseLis->getVari( 112)); // Font

	pLis->setVari( 12, pBaseLis->getVari(1011));
	pLis->setVari(101, pBaseLis->getVari(1021)); // Width
	pLis->setVari(102, pBaseLis->getVari(1022)); // Offset x
	pLis->setVari(103, pBaseLis->getVari(63)); // Offset y
	
	pLis->setVari(201, pBaseLis->getVari(1031)); // Width
	pLis->setVari(202, pBaseLis->getVari(1032)); // Offset x
	pLis->setVari(203, pBaseLis->getVari(63)); // Offset y

	pLis->setVari(301, pBaseLis->getVari(1041)); // Width
	pLis->setVari(401, pBaseLis->getVari(1051)); // Width
	pLis->setVari(501, pBaseLis->getVari(1061)); // Width
	pLis->setVari(601, pBaseLis->getVari(1071)); // Width
	pLis->setVari(701, pBaseLis->getVari(1081)); // Width
	pLis->setVari(801, pBaseLis->getVari(1091)); // Width
	pLis->setVari(901, pBaseLis->getVari(1101)); // Width

	if( !pLis->runline(1) )
		return false;

	return true;
}

VCheckList * CHRC38::OnNewCheckList()
{
	return new VCHCheckList(m_Group,VCheckList::eC38);
}

RLegend * CHRC38::OnCreateLegend()
{
	return new CHRLegends(this,pReport,CHRLegends::eC38); 
}


