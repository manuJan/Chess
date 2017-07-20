/*************************************************************************************
*			© Copyright MSL Software, S.L., 2012
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHODFOrderExt.cpp
*	Description	:
*
*	Author		: 
*	Date created: 07-05-2012
* 	Project		: Basket ODF
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#include "StdAfx.h"
#include "CHODFOrderExt.h"
#include "CHODFApp.h"
#include "CHODFParamsExt.h"
#include "CHODFModel.h"
#include <OVR/CORE/TH/GTHMsgDefines.h>
#include "..\CHMngtModel\CHPool.h"

CHODFOrderExt::CHODFOrderExt(long id,ODFGUI * pGUI)
:ODFTHOrderExt(id,pGUI)
{
}


CHODFOrderExt::~CHODFOrderExt()
{
}

//virtual from ODFOrderExt
ODFParamsExt * CHODFOrderExt::onNewODFParams()
{
	return new CHODFParamsExt(ODFPARAMS_ID,(CHODFGUI *)m_pGUI);
}

bool CHODFOrderExt::isFullResultsMessage()
{
	return true;
}

bool CHODFOrderExt::processNoParamMessages()
{
	return true;
}

bool CHODFOrderExt::processManualOrder(ODFOrder& aOrder)
{
	return ODFTHOrderExt::processManualOrder(aOrder);
}

void CHODFOrderExt::fillDocCodeOrder(ODFOrder& aOrder)
{
	ODFTHOrderExt::fillDocCodeOrder(aOrder);
}

void CHODFOrderExt::processReportDistributed(const char * fileName,const wchar_t * comment)
{
	//Se la llama cuando un listado se ha distibuido
	MSLString RSC="",parameters="",oris="",lang="";
	getRSCParamsAndOris(fileName,&RSC,&parameters,&oris,&lang);
	GData * pData = getParamByRSC(oris,RSC,parameters);

	UNREFERENCED_PARAMETER(pData);
	UNREFERENCED_PARAMETER(comment);
}

GData * CHODFOrderExt::getParamByRSC(const char* oris, const char* rsc, const char* params)
{
	MSLString rscStr(rsc),key;
	GData * pMSLData= 0;

	//if ( !_stricmp(oris,"C73A") || !_stricmp(oris,"C73B"))
	//	pMSLData=TEGDFApp::getMSLData(oris,rsc);
		
	return pMSLData;
	UNREFERENCED_PARAMETER(oris);
	UNREFERENCED_PARAMETER(params);
}

bool CHODFOrderExt::processTransactions(MSLTransaction &pt)
{
	//TRN_CHANGE_POINTS
	return ODFTHOrderExt::processTransactions(pt);
}

void CHODFOrderExt::processItem(long idTrn,ODFOrder::TypeAction action,GData *pData,long index,ODFDataComms * pDataComms/*=0*/)
{
	bool ret = false;
	
	ODFTHOrderExt::processItem(idTrn,action,pData,index,pDataComms);
}

void CHODFOrderExt::processEndTransaction(long idTrn)
{
	ODFTHOrderExt::processEndTransaction(idTrn);
}

bool CHODFOrderExt::poolStandingsChanged(GData *pData,ODFDataComms * pDataComms,long idTrn,ODFOrder::TypeAction action)
{
	if (!pData)
		return false;

	if (pData->isA()==__GTHPOOL)
	{
		CHPool * pPool = (CHPool*)pData;
		if (!pPool->getIsPool())
			return false;

		return idTrn==TRN_SET_RANKINGS;		
	}

	return false;
}


void CHODFOrderExt::commsRegister(ODFOrder::TypeAction action,GRegister * pRegister,ODFDataComms * pDataComms/*=0*/)
{
	// Si la coleccion de cambios es 1 y ese cambio es el bib no envio nada
	if (!pDataComms)
		return;

	if (pDataComms->getColChanges().entries()==1)
	{
		MSLSetIterator iter(pDataComms->getColChanges());
		ODFItemChanged * pChange = 0;
		while( (pChange=(ODFItemChanged *)iter())!=0 )
		{
			MSLString key = pChange->getItemKey();
			if (key=="BIB_NUMBER")
				return;
		}
	}
	return ODFTHOrderExt::commsRegister(action,pRegister,pDataComms);
}
