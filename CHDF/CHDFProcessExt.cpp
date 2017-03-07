/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHDFProcessExt.cpp
*	Description	:
*
*	Author		: Chess Team
*	Date created: 17-may-2006
* 	Project		: Chess DataFeed
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdafx.h"
#include "CHDFProcessExt.h"

#include <GUI/DF/DFDefines.h>
#include <GUI/DF/DFRecord.h>
#include <Core/G/GMsgDefines.h>

#include <SPORTS/CH/DATA/CHInscription.h>
#include <Sports/CH/Data/CHPool.h>
#include <Sports/CH/Data/CHPoolResult.h>
#include <Sports/CH/Data/CHMatchResult.h>
#include <Sports/CH\Data/CHRegister.h>
#include <Sports/CH\Data/CHMsgDefines.h>
#include <Sports/CH\Data/CHClassIds.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHDFProcessExt::CHDFProcessExt(DFGUI * pGUI)
:DFProcessExt(pGUI)
,m_pCHMem(0)
{
	m_pCHMem = (CHMemoryDataBase *)m_pMem;
}

CHDFProcessExt::~CHDFProcessExt()
{
}

void CHDFProcessExt::processTransactions(CPackTransaction& pt)
{
	if (!pt.getObjectCounter())
		return;	

	switch (pt.getTransactionID())
	{
	case TRN_EVENT_ENABLE_DISABLE:
		proccessRemoveEvent(pt);
		break;
	/*case TRN_REMOVE_REGISTER:
		processRemoveRegister(pt);
		break;*/
	case TRN_REMOVE_INSCRIPTION:
		proccessRemoveInscription(pt);
		break;
	case TRN_SET_MODALITY:
		processSetModality(pt);
		break;
	case TRN_REMOVE_PHASE:
		removePhase(pt);
		break;
	case TRN_REMOVE_POOL:
		proccessRemovePool(pt);
		break;
	case TRN_REMOVE_MATCH:
		proccessRemoveMatch(pt);
		break;
	case TRN_REMOVE_MATCHRES:
		proccessRemoveMatchResult(pt);
		break;
	case TRN_REMOVE_POOLRES:
		proccessRemovePoolResult(pt);
		break;
	default:
		DFProcessExt::processTransactions(pt);
		break;
	}
}

void CHDFProcessExt::proccessRemoveEvent(CPackTransaction &packTransaction)
{
	CPackObject po;
	CPackTransactionITerator it(packTransaction);
	while(it(po))
	{
		m_pCHMem->updateModel(po); // Se actualiza el modelo
		RWClassID classID = (RWClassID)po.getId();
		if( classID != __CHEVENT )
			continue;;

		CHEvent * pEvent = (CHEvent *)m_pCHMem->getObject(classID,po.getPack());
		if( !pEvent )
			continue;

//	askForRemove(__CHEVENT,pEvent);
		addRecord(__CHEVENT,pEvent,OVR_DEL_ALL);
		delete pEvent;
	}
	outDF();
}

void CHDFProcessExt::processRemoveRegister(CPackTransaction &packTransaction)
{	
	CPackObject aPackObject;
	CPackTransactionITerator it(packTransaction);
	while(it(aPackObject))
	{
		m_pCHMem->updateModel(aPackObject); // Se actualiza el modelo
		RWClassID classID = (RWClassID)aPackObject.getId();
		if (classID != __CHREGISTER)
			continue;

		CHRegister * pRegister = (CHRegister *)m_pCHMem->getObject(classID,aPackObject.getPack());
		if (!pRegister)
			continue;

//	askForRemove(__CHREGISTER,pRegister,true);
		addRecord(__CHREGISTER,pRegister,OVR_DEL_ALL);
		delete pRegister;
	}
	outDF();
}

void CHDFProcessExt::proccessRemoveInscription(CPackTransaction &packTransaction)
{	
	CPackObject aPackObject;
	CPackTransactionITerator it(packTransaction);
	while(it(aPackObject))
	{
		m_pCHMem->updateModel(aPackObject); // Se actualiza el modelo
		RWClassID classID = (RWClassID)aPackObject.getId();
	
		if (classID != __CHINSCRIPTION)
			continue;

		CHInscription* pInsc = (CHInscription *)m_pCHMem->getObject(classID,aPackObject.getPack());
		if (!pInsc)
			continue;

		CHEventResult* pEvResult = (CHEventResult *)m_pCHMem->getObject(classID,aPackObject.getPack());
		if (!pEvResult)
			continue;

//	askForRemove(__CHMEMBER,pInsc);
//	askForRemove(__CHINSCRIPTION,pInsc,true);
		addRecord(__CHMEMBER	 ,pInsc,OVR_DEL_ALL);
		addRecord(__CHEVENTRESULT,pEvResult,OVR_DEL_ALL);
		addRecord(__CHINSCRIPTION,pInsc,OVR_DEL_ALL);
		delete pInsc;
	}
	outDF();
}

void CHDFProcessExt::processSetModality(CPackTransaction &packTransaction)
{
	CPackTransactionITerator iter(packTransaction);

	CPackObject aPackObject;
	while (iter(aPackObject))
	{
		m_pCHMem->updateModel(aPackObject); // Se actualiza el modelo
		RWClassID classID = (RWClassID)aPackObject.getId();
		CPackObject::actions objectAction=CPackObject::actions(aPackObject.getAction());

		if(objectAction==CPackObject::eInsertOrUpdateObject)
		{
			GData * pData = m_pCHMem->getObject(classID,aPackObject.getPack());
			if (!pData)
				continue;
//			askForInsert(pData,true);
			addRecord(pData->isA(),pData,OVR_SET);
			delete pData;
		}
		else
		{
			if(classID == __CHPHASE && objectAction==CPackObject::eDeleteObject)
			{
				CHPhase * pPhase = (CHPhase *)m_pCHMem->getObject(classID,aPackObject.getPack());
				if (!pPhase)
					continue;
				proccessRemovePhase(pPhase);
				delete pPhase;
			}
		}
	}
	outDF();
}

void CHDFProcessExt::removePhase(CPackTransaction &packTransaction)
{
	CPackObject aPackObject;
	CPackTransactionITerator it(packTransaction);
	while(it(aPackObject))
	{
		m_pCHMem->updateModel(aPackObject); // Se actualiza el modelo
		RWClassID classID = (RWClassID)aPackObject.getId();
		if (classID  != __CHPHASE)
			continue;

		CHPhase * pPhase = (CHPhase *)m_pCHMem->getObject(classID,aPackObject.getPack());
		if (!pPhase)
			continue;
		
		proccessRemovePhase(pPhase);
		delete pPhase;
	}
	outDF();
}

void CHDFProcessExt::proccessRemovePhase(CHPhase * pPhase)
{
//	askForRemove(__CHMATCHMEMBER,pPhase);
//	askForRemove(__CHSPLITMATCHRESULT,pPhase);
//	askForRemove(__CHMATCHRESULT,pPhase);
//	askForRemove(__CHSPLITMATCH,pPhase);
//	askForRemove(__CHMATCHJUDGE,pPhase);
//	askForRemove(__CHMATCH,pPhase);
//	askForRemove(__CHPOOLRESULT,pPhase);
//	askForRemove(__CHPOOL,pPhase);
//	askForRemove(__CHPHASE,pPhase,true);
	addRecord(__CHMATCHMEMBER	  ,pPhase,OVR_DEL_ALL);
	addRecord(__CHSPLITMATCHRESULT,pPhase,OVR_DEL_ALL);
	addRecord(__CHMATCHRESULT	  ,pPhase,OVR_DEL_ALL);
	addRecord(__CHMATCHMEMBER	  ,pPhase,OVR_DEL_ALL);
	addRecord(__CHMATCHJUDGE	  ,pPhase,OVR_DEL_ALL);
	addRecord(__CHMATCH			  ,pPhase,OVR_DEL_ALL);
	addRecord(__CHPOOLRESULT	  ,pPhase,OVR_DEL_ALL);
	addRecord(__CHPOOL			  ,pPhase,OVR_DEL_ALL);
	addRecord(__CHPHASE			  ,pPhase,OVR_DEL_ALL);
}

void CHDFProcessExt::proccessRemovePool(CPackTransaction &packTransaction)
{
	CPackObject aPackObject;
	CPackTransactionITerator it(packTransaction);
	while(it(aPackObject))
	{
		m_pCHMem->updateModel(aPackObject); // Se actualiza el modelo
		RWClassID classID = (RWClassID)aPackObject.getId();
		if (classID != __CHPOOL)
			continue;

		CHPool* pPool = (CHPool *)m_pCHMem->getObject(classID,aPackObject.getPack());
		if (!pPool)		
			continue;
//	askForRemove(__CHMATCHMEMBER,pPool);
//	askForRemove(__CHSPLITMATCHRESULT,pPool);
//	askForRemove(__CHSPLITMATCH,pPool);
//	askForRemove(__CHMATCHRESULT,pPool);
//	askForRemove(__CHMATCHJUDGE,pPool);
//	askForRemove(__CHMATCH,pPool);
//	askForRemove(__CHPOOLRESULT,pPool);
//	askForRemove(__CHPOOL,pPool,true);
		addRecord(__CHMATCHMEMBER	  ,pPool,OVR_DEL_ALL);
			addRecord(__CHSPLITMATCHRESULT,pPool,OVR_DEL_ALL);
		addRecord(__CHSPLITMATCH	  ,pPool,OVR_DEL_ALL);
		addRecord(__CHMATCHRESULT	  ,pPool,OVR_DEL_ALL);
		addRecord(__CHMATCHJUDGE	  ,pPool,OVR_DEL_ALL);
		addRecord(__CHMATCH			  ,pPool,OVR_DEL_ALL);
		addRecord(__CHPOOLRESULT	  ,pPool,OVR_DEL_ALL);
		addRecord(__CHPOOL			  ,pPool,OVR_DEL_ALL);
		delete pPool;
	}
	outDF();
}

void CHDFProcessExt::proccessRemoveMatch(CPackTransaction &packTransaction)
{
	CPackObject aPackObject;
	CPackTransactionITerator it(packTransaction);
	while(it(aPackObject))
	{
		m_pCHMem->updateModel(aPackObject); // Se actualiza el modelo
		RWClassID classID = (RWClassID)aPackObject.getId();
		if (classID != __CHMATCH)
			continue;

		CHMatch* pMatch = (CHMatch *)m_pCHMem->getObject(classID,aPackObject.getPack());
		if (!pMatch)		
			continue;
//	askForRemove(__CHMATCHMEMBER,pMatch);
//	askForRemove(__CHSPLITMATCHRESULT,pMatch);
//	askForRemove(__CHMATCHRESULT,pMatch);
//	askForRemove(__CHSPLITMATCH,pMatch);
//	askForRemove(__CHMATCHJUDGE,pMatch);
//	askForRemove(__CHMATCH,pMatch,true);
		addRecord(__CHMATCHMEMBER	  ,pMatch,OVR_DEL_ALL);
		addRecord(__CHSPLITMATCHRESULT,pMatch,OVR_DEL_ALL);
		addRecord(__CHMATCHRESULT	  ,pMatch,OVR_DEL_ALL);
		addRecord(__CHSPLITMATCH	  ,pMatch,OVR_DEL_ALL);
		addRecord(__CHMATCHJUDGE	  ,pMatch,OVR_DEL_ALL);
		addRecord(__CHMATCH			  ,pMatch,OVR_DEL_ALL);
		delete pMatch;
	}
	outDF();
}

void CHDFProcessExt::proccessRemoveMatchResult(CPackTransaction &packTransaction)
{
	CPackObject aPackObject;
	CPackTransactionITerator it(packTransaction);
	while(it(aPackObject))
	{
		m_pCHMem->updateModel(aPackObject); // Se actualiza el modelo
		RWClassID classID = (RWClassID)aPackObject.getId();
		if (classID != __CHMATCHRESULT)
			continue;

		CHMatchResult * pMatchResult = (CHMatchResult *)m_pCHMem->getObject(classID,aPackObject.getPack());
		if (!pMatchResult)		
			continue;
//	askForRemove(__CHMATCHMEMBER,pMatchResult);
//	askForRemove(__CHSPLITMATCHRESULT,pMatchResult);
//	askForRemove(__CHMATCHRESULT,pMatchResult,true);
		addRecord(__CHMATCHMEMBER	  ,pMatchResult,OVR_DEL_ALL);
		addRecord(__CHSPLITMATCHRESULT,pMatchResult,OVR_DEL_ALL);
		addRecord(__CHMATCHRESULT	  ,pMatchResult,OVR_DEL_ALL);
		delete pMatchResult;
	}
	outDF();
}

void CHDFProcessExt::proccessRemovePoolResult(CPackTransaction &packTransaction)
{
	CPackObject aPackObject;
	CPackTransactionITerator it(packTransaction);
	while(it(aPackObject))
	{
		m_pCHMem->updateModel(aPackObject); // Se actualiza el modelo
		RWClassID classID = (RWClassID)aPackObject.getId();
		if (classID != __CHPOOLRESULT)
			continue;

		CHPoolResult * pPoolResult = (CHPoolResult *)m_pCHMem->getObject(classID,aPackObject.getPack());
		if (!pPoolResult)		
			continue;
//	askForRemove(__CHPOOLRESULT,pPoolResult,true);
		addRecord(__CHPOOLRESULT,pPoolResult,OVR_DEL_ALL);
		delete pPoolResult;
	}
	outDF();
}

void CHDFProcessExt::addRecord(RWClassID classID, GData * pData, short type)
{
	DFRecord aRecord(classID, pData->getKey(), (type==OVR_SET)?pData->msl():"", type);
	DFProcessExt::addRecord(aRecord);
}