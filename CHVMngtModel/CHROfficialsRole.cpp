/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHROfficialsRole.cpp
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
#include "CHROfficialsRole.h"
#include <Sports/CH/Data/CHMemoryDataBase.h>
#include <Sports/CH/Data/CHRegister.h>
#include <Sports/CH/Data/CHJudge.h>

static int orderJudgesByCountryName(const GVectorElement** a, const GVectorElement** b)
{	
	CHRegister *pRegA=(CHRegister *)((GVectorElement*)*a)->getElement();
	CHRegister *pRegB=(CHRegister *)((GVectorElement*)*b)->getElement();

	int	order=strcmp(pRegA->getGroup(),pRegB->getGroup());

	if (!order)
		order=_wcsicoll(pRegA->getPrnLName(),pRegB->getPrnLName());
	
	if (!order)
		order =pRegA->getRegister()-pRegB->getRegister();

	return order;
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHROfficialsRole::CHROfficialsRole(CHReportTemplate* _pReportTemplate,CReport* _pReport)
:pReportTemplate(_pReportTemplate)
,pReport(_pReport)
,pFunction (0)
,pLis(0)
,index(0)
,corx(0)
,cory(0)
,ok(true)
,pJudge(0)
,first(true)
,roleAssigned(false)
,finish(true)
{
	ok = loadlis();
}

CHROfficialsRole::~CHROfficialsRole()
{
	vJudges.clearAndDestroy();
}

bool CHROfficialsRole::runlis()
{
	if( ok )
	{
		if( !pLis->runline(1) )
		{	
			CReportManager& aReportMng = pReport->getManager();		
			if ( aReportMng.getLastError()!=aReportMng.getError(WNOERROR) )
				AfxMessageBox(RWWString(aReportMng.getLastError(),RWWString::ascii));
			
			return false;
		}
		return true;
	}
	return false;
}

int CHROfficialsRole::getHeight()
{
	int height=0;
	if( ok )
	{
		if ( vJudges.entries() )
		{
			height+=pLis->getVari(11)*vJudges.entries();	// Jueces
			height+=pLis->getVari(11);						// Salto de línea 
		}
/*		if(first)
		{
			height+=pLis->getVari(11); // Cajetín
			height+=pLis->getVari(21); // Salto
		}
*/
	}
	return height;
}

int CHROfficialsRole::getWidth()
{
	int width=0;
	if( ok )
	{
		width+=pLis->getVari(1101);
		width+=pLis->getVari(1201);
		width+=pLis->getVari(1301);
		width+=pLis->getVari(1401);
	}
	return width;
}

void CHROfficialsRole::setCorY(const short value)
{
	cory = value;
	pLis->setVari(1002,cory);
}

void CHROfficialsRole::setCorX(const short value)
{
	corx = value;
	pLis->setVari(1003,corx);
}

bool CHROfficialsRole::isFinish()
{
	return finish;
}

unsigned short CHROfficialsRole::OnCallbackFn(struct USR_TAB * pTabInf)
{
	switch ( pTabInf->Tb )
	{
		case 10:
			return tableCallBack(pTabInf);
	}

	return PRNALL;
}

unsigned short CHROfficialsRole::tableCallBack( struct USR_TAB * pTabInf )
{
	switch ( pTabInf->Te ) //template
	{
		case 1:
		{
			switch ( pTabInf->Ce )
			{
				case 1:
				{
					GVectorElement * pElement	= vJudges[index++];
					pJudge= pElement ? (CHRegister*) pElement->getElement() : 0;
					assignData();
					break;
				}
			}
			break;
		}
	}

	return PRNALL;
}

RWBoolean CHROfficialsRole::loadlis()
{
	RWCString lang = DBApplication::getAppLanguage();
	RWCString lis  = "CH.OfficialsRole." + lang + ".lis";

	CLis& aLis=pReport->setLis(lis);
	pLis=&aLis;
	CReportManager& aReportMng=pReport->getManager();

	if( !pLis->isValid() )
	{
		AfxMessageBox(RWWString(aReportMng.getLastError()+"\n"+lis,RWWString::ascii));
		pLis=0;
	}
	else
	{
		pLis->setCallBack(10,pReportTemplate);
		CLis *pHeaderLis=pReportTemplate->getHeaderLis();
		if (pHeaderLis)
		{
			pLis->setData(13,pHeaderLis->getData(300));
			pLis->setData(14,pHeaderLis->getData(301));
		}
		center();
	}
	return pLis!=0;
}

void CHROfficialsRole::loadData(GFunction* _pFunction,bool beginPage/*=false*/,bool full/*=true*/,int part/*=0*/)
{
	pFunction=_pFunction;
	if (pFunction->getRegType() == char(GRegister::judge))
		roleAssigned=true;
	index=0;
	first=beginPage;
	vJudges.clearAndDestroy();
	vJudges.sort(orderJudgesByCountryName);
	RWSetIterator it(CHMemoryDataBase::getColRegisters());
	CHRegister* pRegister=0;
	while ((pRegister=(CHRegister*)it())!=0)
	{
		if ((pRegister)  && (pRegister->getType()==GRegister::judge))
		{
			if (!roleAssigned) //solo queremos jueces sin rol asginado
			{
				CHJudge *pJudge =0;
				bool found= false;
				RWSetIterator iterator(CHMemoryDataBase::getColJudges());
				while (((pJudge =(CHJudge *)iterator()) != 0) && (!found))
				{
					if (pJudge->getRegister() == pRegister) //si existe algun juez con cualquier funcion no lo incluimos en la coleccion
						found=true;
				}	
				if (!found)
					vJudges.insert(pRegister);
			}
			else //buscamos jueces con la funcion que tenemos en pFunction
			{
				CHJudge* pJudge = CHMemoryDataBase::findJudge(pRegister,pFunction);
				if (pJudge && (pJudge->getFunctionKey()==pFunction->getKey()))
					vJudges.insert(pRegister);
			}
		}
	}

	if (!full) //vemos los jueces que caben
	{
		int highLine=pLis->getVari(11); //altura del template con datos
		int entries=pLis->getVari(2100)/highLine; //numero de templates con datos que podemos sacar (espacio disponible en la pagina para mostrar solo templates con datos/hihgline)
		int indexBegin=entries * (part-1);
		int indexEnd= unsigned((entries * part)-1) > (vJudges.entries()-1)?(vJudges.entries()-1):(entries * part)-1;
		finish=(unsigned(indexEnd) < (vJudges.entries()-1) )?false:true;
		//quitamos los restantes elementos 1º a la derecha 
		for (size_t i=vJudges.entries()-1;i>unsigned(indexEnd);i--)	
		{
			pRegister=(CHRegister *)vJudges[i]->getElement();
			vJudges.removeAndDestroy(pRegister);
		}
		//2º a la izquierda
		for (i=0;i<unsigned(indexBegin);i++)
		{
			pRegister=(CHRegister *)vJudges[0]->getElement();
			vJudges.removeAndDestroy(pRegister);
		}
	}
	// Numero de Jueces
	pLis->setVari(12,vJudges.entries());
	// Se pinta la cabecera y el salto
/*	if(first)
		pLis->setVari(12,1);
	else
		pLis->setVari(12,0);
*/
}

void CHROfficialsRole::assignData()
{
	if ( pJudge )
	{
		if (index==1) //mostramos la funcion solo en el primer registro
			pLis->setData(21,roleAssigned?pFunction->getLDescription().toMultiByte():pLis->getData(15));
		else
			pLis->setData(21,"");
		pLis->setData(22,pJudge->getPrnLName());			//name		
		pLis->setData(23,pJudge->getGroupLDescription());	//noc
		pLis->setData(24,"("+pJudge->getGroup()+")");		//noc code
	}	
}

void CHROfficialsRole::center()
{
	int width = pLis->getVari(1101)+
				pLis->getVari(1201)+
				pLis->getVari(1301)+
				pLis->getVari(1401);

	int corx = pReportTemplate->getCenter()-(width/2);
	
	pLis->setVari(1003,corx);
	pLis->setVari(1002,cory);
}