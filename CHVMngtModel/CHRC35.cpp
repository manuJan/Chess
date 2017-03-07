/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHRC35.cpp
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
#include "CHRC35.h"

#include "CHROfficialsRole.h"

#include <Sports/CH/Data/CHMemoryDataBase.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHRC35::CHRC35(CReportManager& aReportManager,CReportConfig& aReportConfig)
:CHReportTemplate(aReportManager,aReportConfig)
,pLis(0)
,index(0)
,nLines(0)
,pOfficialsRole(0)
,pFunction(0)
,first(true)
,full(true)
,part(0)
{
	pOfficialsRole = new CHROfficialsRole(this,pReport);
}

CHRC35::~CHRC35()
{
	delete pOfficialsRole ;
	vFunctions.clearAndDestroy();
}

void CHRC35::OnBeginReport()
{
	RWCString lang=DBApplication::getAppLanguage();
	RWCString lis="CH.C35."+lang+".lis";

	CLis& aLis=pReport->setLis(lis);
	pLis=&aLis;

	loadData();
	
	if( pLis && !pLis->isValid() )
	{
		CReportManager& aReportMng=pReport->getManager();
		AfxMessageBox(RWWString(aReportMng.getLastError()+"\n"+lis,RWWString::ascii));
		pLis=0;
	}

	bOkLis=(pLis!=0 && CReportTemplate::isValid()  );
	if( bOkLis )
	{
		// Asignando Varis de las fonts - SetVaris Font
		setVaris(pLis);

		pLis->setCallBack(1,this);
		center();

		// As of
		long center=getCenter();
		if ( !pLis->getVari(1004) )
			pLis->setVari(1004,center);
		
		bHeaderAsOf=true;
	}
}

CReportBase::ReportReturn CHRC35::OnBody()
{
	// Altura As of
	nLines+=pLis->getVari(11); //celda 1
	nLines+=pLis->getVari(21); //celda 2
	int value;
	int groupsListed=0;
	first=true;
	pReport->setCursor(0,pLis->getVari(1002));
	for(;index<int(vFunctions.entries());index++)
	{
		pFunction = (GFunction*)vFunctions[index]->getElement();
		pOfficialsRole->loadData(pFunction,first,full,part); 
		pOfficialsRole->setCorY(short(nLines));
		value = pOfficialsRole->getHeight();
		if (!value)
			continue;
		nLines+= value;
		if(IsPageBreak(short(value)))
		{
			nLines=0;
			if (groupsListed)	//si hay se ha listado en la pagina algun grupo de jueces
			{
				return ok;		// Salto de pagina	
			}
			else //el grupo entero no cabe en una unica pagina
			{
				nLines+=pLis->getVari(11); //celda 1
				nLines+=pLis->getVari(21); //celda 2
				full=false;	
				index--; 
				part++;
				continue;
			}
		}
		pOfficialsRole->runlis();
		groupsListed++;
		if (!full)
		{
			if (pOfficialsRole->isFinish())
			{
				full=true;
				part=0;
			}
			else
			{
				//index--;
				part++;
				nLines=0;
				return ok;	//salto de pagina (ya sabemos que no va a caber)	
			}
		}
		first=false;
	}
	return exit; //listado terminado
}

unsigned short CHRC35::OnCallbackFn(struct USR_TAB * pTabInf)
{
	switch ( pTabInf->Tb ) //tabla
	{
		case 10:
		{
			if ( pOfficialsRole )
				return pOfficialsRole->OnCallbackFn(pTabInf);
			break;
		}
	}
	return CReportBase::OnCallbackFn(pTabInf);
}

void CHRC35::center()
{
	int width = pLis->getVari(1101);

	int corx = getCenter()-(width/2);
	int cory = pLis->getVari(1000);
	
	pLis->setVari(1003,corx);
	pLis->setVari(1002,cory);
}

void CHRC35::loadData()
{
	GFunction* pFunction=0;
	RWSetIterator itFunctions(CHMemoryDataBase::getColFunctions());
	while( (pFunction=(GFunction*)itFunctions())!=0 )
	{
		if (pFunction)
			vFunctions.insert(pFunction);
	}
}

RWDate CHRC35::OnGetEventDate() const
{
	return INVALID_RWDATE;
}

RWTime CHRC35::OnGetEventTime() const
{
	return INVALID_RWTIME;
}