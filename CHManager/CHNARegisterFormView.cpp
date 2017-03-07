/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHNARegisterFormView.cpp
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:07-12-2005
*   Project     :CH Manager
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///
#include "stdafx.h"
#include "CHmanager.h"
#include "CHNARegisterFormView.h"
#include "sports/CH/Data/CHMemoryDataBase.h"
#include "resource.h"
#include "sports/CH/Data/CHRegister.h"
#include "sports/CH/Data/CHJudge.h"
#include "sports/CH/Data/CHMatchJudge.h"
//#include "sports/CH/Data/CHCode.h"
#include "sports/CH/Data/CHMsgDefines.h"
//reports
//#include <Sports/CH/Reports/CHReportsDefines.h>
#include <SPORTS/CH/REPORTS/CHRC35.h>

#define GRDJUDGE	800
#define IDCOLGRD	802
#define LBL_JUDGE	803
#define LBL_LINE	804
#define LINECOLOR	805
#define FONTTEXT	806
#define IDCOLLINE	807

IMPLEMENT_DYNCREATE(CHNARegisterFormView, CFormView)

static int orderByKey(const GVectorElement** a, const GVectorElement** b)
{	
	GFunction *pFunctionA = (GFunction *)(*a)->getElement();
	GFunction *pFunctionB = (GFunction  *)(*b)->getElement();
	
	return strcmp(pFunctionA->getKey(),pFunctionB->getKey());
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHNARegisterFormView::CHNARegisterFormView()
:GNARegisterFormView()
{
}

CHNARegisterFormView::~CHNARegisterFormView()
{
}

CHMemoryDataBase* CHNARegisterFormView:: mem()
{
	return (CHMemoryDataBase *) ( (CCHManagerApp *)AfxGetApp() )->memG(); 
}

void CHNARegisterFormView::generateVFunctions()
{
	vFunctions.sort(orderByKey);
	RWSetIterator it(CHMemoryDataBase::getColFunctions());
	GFunction *pFunction = 0;
	
	while ((pFunction = (GFunction *)it()) != 0)
	{
		if (pFunction->getRegType() == GRegister::judge)
			vFunctions.insert(pFunction);
	}
}

void CHNARegisterFormView::fillFunctionsJudge()
{
	w->gridDeleteAllItems(GRDJUDGE);
	GFunction *pFunction = 0;
	for (size_t i =0; i < vFunctions.entries() ; i++)
	{
		pFunction = (GFunction * ) vFunctions[i]->getElement();
		if (pFunction)
			w->addGridLine(GRDJUDGE,(LPARAM)pFunction,"");
	}
}

void CHNARegisterFormView::paintFunctionsJudge(GridItem *gi)
{
	if (!gi)
		return;

	RWBoolean check = false;
	CHRegister* pRegister = (CHRegister *) getRegister(); 	//obtenemos el registro seleccionado en el arbol
	GFunction* pFunction = (GFunction *) gi->lParam;		//obtenemos la función de juez que se está pintando
	
	CHJudge* pJudge = CHMemoryDataBase::findJudge(pRegister,pFunction);
	if (pJudge && (pJudge->getFunctionKey()==pFunction->getKey()))
		check = true;

	gi->cdc->FillSolidRect( gi->rc, (gi->sel)?  RGB(230,240,15) : RGB(240,240,250));

	switch(gi->x)
	{
		case 0: 
			if (check)
				w->paintGridCheck(true);
			else	
				w->paintGridCheck(false);
			break;
		case 1:
			w->paintGridText(10,0,pFunction->getLDescription());
			break;
		default:
			break;
	}	
}

void CHNARegisterFormView::assignFunction(GFunction *pFunction,int y)		
{
	if (!pFunction )
		return ;

	CHRegister *pRegister = (CHRegister *) getRegister(); 				//obtenemos el registro seleccionado en el arbol
	CHJudge *pJudge = CHMemoryDataBase::findJudge(pRegister,pFunction); //buscamos al juez con la funcion des/marcada
	
	w->gridDeleteItem(GRDJUDGE,y);

	if (pJudge) 
	{
		deleteJudge(pJudge);
	}
	else 
	{
		CHJudge aJudge;
		aJudge.setFunction(pFunction);
		aJudge.setRegister(pRegister);
		aJudge.setKey();
		//pJudge = mem()->setJudge(aJudge);
		//insertJudge(pJudge);
		insertJudge(&aJudge);
	}
/*???
	if (pRegister->getType()==GRegister::judge)
	{
		sendIDSNotify(N_OFFICIALS,pRegister,N_UPDATE);
		::Sleep(300L);
	}
*/
	w->insertGridLine(GRDJUDGE,(LPARAM)pFunction,"",y);
	w->redrawLine(GRDJUDGE,y);
	w->selectNLine(GRDJUDGE,y);
}

void CHNARegisterFormView::deleteJudge(CHJudge *pJudge)
{
	CHJudge *pDeleteJudge = mem()->removeJudge(*pJudge);

	APP::out(TRN_CH_JUDGE_REMOVE);
	APP::out(*pDeleteJudge,OP_DELETE,TO_VENUE|TO_DATABASE);		
	APP::out();
}

void CHNARegisterFormView::insertJudge(CHJudge *pJudge)
{
	CHJudge *pInsertJudge = mem()->setJudge(*pJudge);

	APP::out(TRN_CH_JUDGE_SET);
	APP::out(*pInsertJudge,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);		
	APP::out();
}

GRegister *	CHNARegisterFormView::getNewRegister()
{
	return new CHRegister();
}

RWBoolean CHNARegisterFormView::canInsertSexInTree(GSex & aSex)
{	
	if(atoi(aSex.getSex())==GSex::sMixed)
		 return false;	
	else return true;
}

void CHNARegisterFormView::init()
{
	GNARegisterFormView::init();

	w->createLabel(LBL_JUDGE,CRect(415,160,735,185),"Officials Functions", BORDER_NONE,JUST_LEFT,IDBCK,IDCOLLINE,FONTTEXT );
	w->createLabel(LBL_LINE,CRect(415,187,735,190),"", BORDER_NONE, JUST_LEFT, LINECOLOR);
	w->createGrid   (GRDJUDGE,CRect(415,200,735,360),BORDER_3DDOWN,20);
	w->addGridColumn(GRDJUDGE,"Select",JUST_CENTER,50);
	w->addGridColumn(GRDJUDGE,"Function",JUST_CENTER,270);
	w->gridLineColor(GRDJUDGE,RGB(207,207,207),RGB(207,207,207));

	w->hide(LBL_JUDGE);
	w->hide(LBL_LINE);
	w->hide(GRDJUDGE);

	generateVFunctions();

	addReports();
}

BOOL CHNARegisterFormView::onPaintGrid  (UINT idGrid,GridItem *gi)			
{
	if (idGrid == GRDJUDGE)
		paintFunctionsJudge(gi);
	return true;
	//??GNARegisterFormView::onPaintGrid(idGrid,gi);
}

void CHNARegisterFormView::onLButtonDown  (UINT idGrid,int x,int y,LPARAM lParam)
{
	if(idGrid== GRDJUDGE && x==0)
		assignFunction((GFunction*)lParam,y);		
	return;
	UNREFERENCED_PARAMETER(y);
}

void  CHNARegisterFormView::onSelChangedRegister(GRegister * pRegister) 
{
	if (pRegister && pRegister->getType() == GRegister::judge)
	{
		if (vFunctions.entries())
		{
			fillFunctionsJudge();
			w->redraw(GRDJUDGE);
			w->show(GRDJUDGE);
			w->show(LBL_JUDGE);
			w->show(LBL_LINE);
		}
	}
	else
	{
		w->hide(GRDJUDGE);
		w->hide(LBL_JUDGE);
		w->hide(LBL_LINE);
	}
}

RWBoolean CHNARegisterFormView::canRemoveRegister(GRegister * pRegister) 
{
	RWSetIterator it(CHMemoryDataBase::getColMatchJudge());
	GTHMatchJudge *pMatchJudge = 0;
	
	while ((pMatchJudge =(GTHMatchJudge *)it() ) != 0)
	{
		if (pMatchJudge->getRegister() == pRegister)
			return false;
	}
	// NO existe ningun matchJudge asociado al juez que se quiere borrar, borramos los Judges asociados al registro
	RWSet colDeleteJudges ;
	CHJudge *pJudge =0;
	RWSetIterator it2(CHMemoryDataBase::getColJudges());
	while ((pJudge =(CHJudge *)it2()) != 0)
	{
		if (pJudge->getRegister() == pRegister)
			colDeleteJudges.insert(pJudge);
	}

	RWSetIterator it3(colDeleteJudges);
	while ((pJudge =(CHJudge *)it3() ) != 0)
		deleteJudge(pJudge);

	return true;
}

void CHNARegisterFormView::onReportRequest(CReportItem *pItem)
{
	if (!pItem)
		return;

	switch ( pItem->getNReport() )
	{
		case CH_COMPETITION_OFFICIALS_C35:
		{
			pItem->setResultCode(mem()->getRSC((GData *)0));
			break;
		}
	}
}

bool CHNARegisterFormView::onReportGeneration(CReportManager *pReportMngr,CReportConfig *pReportCfg,CReportItem *pItem)
{
	bool IsOk=false;
	if (!pItem || !pReportCfg || !pReportMngr)
		return false;


	switch ( pItem->getNReport() )
	{
		case CH_COMPETITION_OFFICIALS_C35:
		{
			CHRC35 aCHR35(*pReportMngr,*pReportCfg);
			IsOk = aCHR35.Run();
			break;
		}
	}
	return IsOk;
}

void CHNARegisterFormView::addReports()
{
	int index=0;
	APP::addReport(++index,0,"Competition Officials (35)",CH_COMPETITION_OFFICIALS_C35,CH_OFFICIALS_FORMVIEW);
}