
/*************************************************************************************
*			© Copyright MSL Software, S.L., 2001
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHRC96.cpp
*	Description	: Implementation of the CHRC96 class.
*
*	Author		: Chess Team
*	Date created: 24-January-2006
* 	Project		: 
*	
* 	Modification history
*	By			: 
*	Date		: 
*	Changes		: 
*
***************************************************************************************/

#include "stdVCH.h"
#include "CHRC96.h"
#include <Sports\CH\Data\CHEvent.h>
#include <Sports\CH\Data\CHEventResult.h>
#include <Sports\CH\Data\CHInscription.h>
#include <Sports\CH\Data\CHRegister.h>
#include <Sports\CH\Data\CHMemoryDataBase.h>
#include <Sports\CH\Data\CHMsgDefines.h>

static 
int orderByOrderEventResults(const GVectorElement** a, const GVectorElement** b)
{
	CHEventResult *pEventResultA=(CHEventResult *)(*a)->getElement();
	CHEventResult *pEventResultB=(CHEventResult *)(*b)->getElement();

	if (pEventResultA->getQualitativeCode()!=OK &&
		pEventResultB->getQualitativeCode()!=OK )
		return _wcsicoll(pEventResultA->getPrnLName(),pEventResultB->getPrnLName());

	if (pEventResultA->getQualitativeCode()!=OK)
		return 1;

	if (pEventResultB->getQualitativeCode()!=OK)
		return -1;

	if( !pEventResultA->getRank() && pEventResultB->getRank() )
		return 1;
	if( !pEventResultB->getRank() && pEventResultA->getRank() )
		return -1;

	int order = pEventResultA->getRank() - pEventResultB->getRank();
	if( order )
		return order;

	order = pEventResultA->getRankPo() - pEventResultB->getRankPo();
	if( order )
		return order;

	return _wcsicoll(pEventResultA->getPrnLName(),pEventResultB->getPrnLName());
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHRC96::CHRC96(CReportManager& aReportManager,CReportConfig& aReportCfg, CHEvent *pEvent)
:CHReportTemplate(aReportManager,aReportCfg,pEvent)
,pMyLis(0)
,pEventSel(pEvent)
,pEventResult(0)
,pos(0)
,pLegends(0)
,firstPage(true)
{
	pLegends=new CHRLegends(this,pReport,CHRLegends::eC96);
}

CHRC96::~CHRC96()
{
	if ( pLegends )
		delete pLegends;
	vResults.clearAndDestroy();
}

unsigned short CHRC96::OnCallbackFn(struct USR_TAB * pTabInf)
{
	switch(pTabInf->Tb)
	{
		case 101:		// relleno de la Tabla 101: Ranking Cabecera
			//return RankCallBack(pTabInf);
			break;
		case 102:		// relleno de la Tabla 102: Ranking Detalle
		case 103:		// relleno de la Tabla 103: Members
			return RankDetalCallBack(pTabInf);
			break;
	}
	return CReportBase::OnCallbackFn(pTabInf);
}


CReportBase::ReportReturn CHRC96::OnBody()
{
	// Cabecera Ranking
	if (!pMyLis->runline(1))
		return OnError(error,1301);

	// Detalle Ranking
	return paintRanking();

}

void CHRC96::OnBeginReport()
{
	bOkLis=false;

	if (!build_RankingVector())
	{
		AfxMessageBox(_T("Event not finished. No Competitor with Rank"));
		return;
	}

	RWCString lang = DBApplication::getAppLanguage();
	RWCString sLisName = "CH.C96."+lang+".lis";
	CReportManager& aReportMng = pReport->getManager();

	// Obtenemos el lis del report Competition Schedule
	CLis &aLis = pReport->setLis( sLisName );
	pMyLis = &aLis;

	if( pMyLis && pMyLis->isValid() )
	{
		// Obtenemos el lis de GenHeadFooter
		CLis *pHeaderLis = aReportMng.getHeader();
		if( !pHeaderLis || !pHeaderLis->isValid() )
		{
			OnError(error,1303);
			return;
		}
 
		// Inicializamos variables
		aReportMng.setCtrlmargin( true );
		pReport->setCursor( 0, 0 );
		pMyLis->setVari(5,getCenter());

		if ( !pMyLis->setCallBack(1,this) )		// Tabla 1: Ranking Cabecera
		{
			OnError(error,1304);
			return;
		}
		if ( !pMyLis->setCallBack(2,this) )		// Tabla 2: Ranking Detalle
		{
			OnError(error,1305);
			return;
		}

		if ( !pMyLis->setCallBack(3,this) )		// Tabla 3: Members
		{
			OnError(error,1306);
			return;
		}
		bOkLis=true;
		bHeaderAsOf=true;		
		

		//Leyendas
		pLegends->loadLis();
		setDynamicLegends();

		setGlobalVaris();
		setVaris(pMyLis);
	}
	else
	{	// Si hubo error en el report mostramos el error.
		OnError(error,1306);
		return;
	}
}


CReportBase::ReportReturn CHRC96::paintRanking()
{
	if (!vResults.entries())
		return error;
	
	short variToBreakPage=1;
	if(!pEventSel->isTeam())
		variToBreakPage=1;
	else 
		variToBreakPage=2;
		
	
	for(size_t i=pos;i<vResults.entries();i++,pos++)
	{
		pEventResult=(CHEventResult *)vResults[pos]->getElement();
			
		setDataEventResult(pEventResult);

		// Pintamos El ranking, tio y medalla.
		if (!pMyLis->runline(2))
			return OnError(error,1302);
		
		if(pEventSel->isTeam())
		{
			CHInscription *pInscription=(CHInscription*)pEventResult->getInscription();
			if(pInscription)
			{
				for(size_t j=0;j<pInscription->getMembersVector().entries();j++)
				{
					CHMember *pMember=(CHMember*)pInscription->getMembersVector()[j]->getElement();
					
					// Master Type
					CHRegister *pRegister=(CHRegister*)pMember->getRegister();

					if(pRegister)
						pMyLis->setData(308,pRegister->getMasterTypeAsString(false));
					// Name Member
					pMyLis->setData(309,pMember->getPrnLName());

					
					// Pintamos El miembro del equipo
					if (!pMyLis->runline(3))
						return OnError(error,1303);
				}

			}
		}

		if (vResults.entries()==i+1)
		{
			if( paintLegends() == error )
				return error;
			return exit;
		}
		
		if( IsPageBreak(short(pMyLis->getVari(variToBreakPage))) )
		{
			pos++;
			// Leyendas
			firstPage=false;
			return ok;
		}
		
	}
	
	// Leyendas
	if( paintLegends() == error )
		return error;
	
	return exit;
}


RWBoolean CHRC96::build_RankingVector()
{
	RWSet  aResults=CHMemoryDataBase::getColEventResult();	
	
	vResults.clearAndDestroy();

	RWSetIterator iterator(aResults);
	while( (pEventResult=(CHEventResult *)iterator())!=0 )
	{
		// Si no es del evento no me sirve
		if(pEventResult->getEventKey()!=pEventSel->getKey())
			continue;
		
		// Insertamos el Competitor que nos interesa.
		if(pEventResult->getRank() || pEventResult->getQualitativeCode()!=OK)
			vResults.insert(pEventResult);	
	}
	vResults.sort(orderByOrderEventResults);

	return (vResults.entries()>0);
}


unsigned short CHRC96::RankDetalCallBack( struct USR_TAB * pTabInf)
{
	UNREFERENCED_PARAMETER(pTabInf);

	return PRNALL;
}

void CHRC96::setDataEventResult(CHEventResult *pEventResult)
{
	// Reseteo
	for(short i=0;i<short(pMyLis->getVari(4));i++)
		pMyLis->setData(300+i,"");

	if(!pEventResult)
		return;

	
	CHRegister *pRegister=(CHRegister*)pEventResult->getRegister();
	CHInscription *pInscription=(CHInscription*)pEventResult->getInscription();

	CHPoolResult *pPoolResult=(CHPoolResult*)pEventResult->getPoolResult();
	
	// Rank
	if (pEventResult->getQualitativeCode()!=OK)
		pMyLis->setData(300,pEventResult->getQualitativeSDescription());
	else
		pMyLis->setData(300,pEventResult->getRank());

	// Master Type
	if(pRegister)
		pMyLis->setData(301,pRegister->getMasterTypeAsString(false));
	

	// Country
	if(pRegister)
		pMyLis->setData(302,pRegister->getGroup());

	// Register
	pMyLis->setData(303,pEventResult->getPrnLName());
	
	
	// Initial Rating
	if(pInscription)
		pMyLis->setData( 304,pInscription->getRatingAsString() );

	// Points
	if(pPoolResult)
		pMyLis->setData( 305,pPoolResult->getPointsFStr() );

	// Final Rating
	pMyLis->setData( 306,pEventResult->getRatingAsString() );

	// Medal
	if (pEventSel->getStatus()>=CHMemoryDataBase::eFinished && pEventResult->getRank() && pEventResult->getRank()<4)
		pMyLis->setData( 307, pMyLis->getData(short(210+(pEventResult->getRank()-1))) );
	
	
}

RWDate CHRC96::OnGetEventDate() const
{
	return INVALID_RWDATE;
}

RWTime CHRC96::OnGetEventTime() const
{
	return INVALID_RWTIME;
}
void CHRC96::setGlobalVaris()
{
		 
	// Corx centrada de la tabla
	int width=0;

	// Decido si pintar el Final Rating o no, según esté el .lis
	if(pMyLis->getVari(25))
		 pMyLis->setVari(106,1); // Final   Rating
	else pMyLis->setVari(106,0); // Final   Rating

	if(pEventSel->isTeam())
	{
		pMyLis->setVari(104,0); // Initial Rating
		pMyLis->setVari(106,0); // Final   Rating
	}
	for(int i=0;i<pMyLis->getVari(4);i++)
		width+=pMyLis->getVari(short(100+i))*pMyLis->getVari(short(200+i));
	
	

	long center=getCenter();
	long offsetx=center-(width/2);
	if (offsetx>25)
		pMyLis->setVari(7,offsetx-25);
	else
		pMyLis->setVari(7,10);
	

	// Codigo NOC, NPC, CGA, dependiente del .lis de cabeceras
	pMyLis->setData(201,CReportTemplate::pLis->getData(300)); 
}
CReportBase::ReportReturn CHRC96::paintLegends()
{
	
	if( !pLegends->runLis() )
		return OnError(error,10);
	
	
	return exit;
}
void CHRC96::setDynamicLegends()
{
	CHMasterType *pMasterType = 0;
	RWSetIterator iter(CHMemoryDataBase::getColMasterTypes());
	
	while ((pMasterType=(CHMasterType*)iter())!=0)
	{
		if(pMasterType->getMasterType())
			pLegends->setDynamic( pMasterType->getSDescription());							
	}

	pLegends->createDynamic();
}