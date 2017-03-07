/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHRC74.cpp
*	Description	:
*
*	Author		:CH Team
*	Date created:20-01-2006
* 	Project		:CHVMngtModel
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdVCH.h"
#include "CHRC74.h"
#include "CHRLegends.h"
#include <SPORTS/CH/DATA/CHMsgDefines.h>
#include <SPORTS/CH/DATA/CHRegister.h>
#include "CHReportDefines.h"

////////////////////////////////////////////////////////////////////////////////////
static int orderMatches(const GVectorElement** a, const GVectorElement** b)
{
	CHMatch * pMatchA = (CHMatch *) (*a)->getElement();
	CHMatch * pMatchB = (CHMatch *) (*b)->getElement();
	
	// Order by Round
	int order = pMatchA->getRound() - pMatchB->getRound();
	if( order )
		return order;

	// Order by Match Code
	order = pMatchA->getCode() - pMatchB->getCode();
	if( order )
		return order;
	
	// Order by key
	return strcmp(pMatchA->getKey(),pMatchB->getKey());
}
/////////////////////////////////////////////////////////////////////
CHRC74::CHRC74(CReportManager& aReportManager,CReportConfig& aReportConfig,CHPhase * pSelPhase,short roundSel)
:CHReportTemplate(aReportManager,aReportConfig,(CHEvent*)pSelPhase->getEvent())
,pLis(0)
,pPhase(pSelPhase)
,index(0)
,pLegends(0)
,round(roundSel)
,firstPage(true)
{
	pLegends=new CHRLegends(this,pReport,CHRLegends::eC74);
	
}

/////////////////////////////////////////////////////////////////////
CHRC74::~CHRC74()
{
	if ( pLegends )
		delete pLegends;
	vMatches.clearAndDestroy();
}

/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
RWCString CHRC74::getNameOfSourceLis(void)
{
	RWCString lang = DBApplication::getAppLanguage();
	
	return CHMemoryDataBase::getDiscipline().getCode()+".C74."+lang+".lis";
	
}

/////////////////////////////////////////////////////////////////////
void CHRC74::OnBeginReport()
{
	CReportManager& aReportMng = pReport->getManager();

	// Instanciamos una referencia al lis del report
	CLis& aLis = pReport->setLis(getNameOfSourceLis());
	pLis = &aLis;
	if( pLis && pLis->isValid() )
	{
		// Iniciamos variables
		aReportMng.setCtrlmargin(true);
		pReport->setCursor(0,0);
		pLis->setVari(1,getCenter());
		pLis->setVari(2,aReportMng.getXMax()-getRightMargin());

		bOkLis = true;
		// SetVaris Font
		setVaris(pLis);
				
		setGlobalVaris();
		
		// Iniciamos funcion para el relleno de la tabla
		pLis->setCallBack(1,this);
		pLis->setCallBack(2,this);
		pLis->setCallBack(3,this);

		//Leyendas
		pLegends->loadLis();
		setDynamicLegends();

		buildVector();

		if (pPhase->getEvent()->isTeam())
			pLis->setData(1000, pLis->getData(1009));
		else
			pLis->setData(1000, pLis->getData(1008));
	}
	else
	{	// Si hubo error en el report mostramos el error.
		AfxMessageBox(RWWString(aReportMng.getLastError(),RWWString::multiByte)+
					  _T("\n")+RWWString(getNameOfSourceLis(),RWWString::multiByte));
	}
}

/////////////////////////////////////////////////////////////////////
CReportBase::ReportReturn CHRC74::OnBody()
{
		
	// Controlamos que haya datos para pintar
	if( !vMatches.entries() )
	{
		AfxMessageBox(_T("There are not matche/s"));
		return error;
	}
		
	
	// Template de Cabeceras
	if( paintTemplateHeader() == error )
		return error;
	
	// Template de Results
	return paintTemplateResults();
	

}

CReportBase::ReportReturn CHRC74::paintLegends()
{
	// Pintamos las leyendas
	if( !pLegends->runLis() )
		return OnError(error,10);
		
	return exit;
}

/////////////////////////////////////////////////////////////////////
CReportBase::ReportReturn CHRC74::paintTemplateHeader()
{
	CHEvent * pEvent = (CHEvent *)pPhase->getEvent();
	
	
	CHMatch *pMatchAux = (CHMatch *)vMatches[index]->getElement();
	
	if(pMatchAux)
	{
		pLis->setData(2100,pMatchAux->getRoundAsString(true,true));
		// Pintamos la ronda
		if( !pLis->runline(5) )
			return OnError(error,10);
	}

	// Pintamos la cabecera
	if( !pLis->runline(1) )
		return OnError(error,10);

	return exit;
}

/////////////////////////////////////////////////////////////////////
CReportBase::ReportReturn CHRC74::paintTemplateResults()
{
	CHEvent * pEvent = (CHEvent *)pPhase->getEvent();
			
	CHMatch * pMatch = 0;
				
	while( index < vMatches.entries() )
	{
		pMatch = (CHMatch *)vMatches[index]->getElement();
		
		if( !pMatch )
			return OnError(error,120);
				

		assignDataIndividual(pMatch);

		// Pintamos los datos 
		if( !pLis->runline(2) )
			return OnError(error,130);

		if(pMatch->isTeam())
			paintMembers(pMatch);
		
		index++;
		
		// Comprobamos si hay salto de pagina
		if(( IsPageBreak(short(pLis->getVari(800))) || changeRound(pMatch)) && index != vMatches.entries())
		{
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
void CHRC74::setGlobalVaris()
{
	
	CHEvent *pEvent=(CHEvent*)pPhase->getEvent();

	// En equipos no se pinta el Master Type1 ni Master Type2, no lo hay.
	if(pEvent->isTeam())
	{
		pLis->setVari(102,0);
		pLis->setVari(109,0);
		pLis->setVari(203,560);
		pLis->setVari(210,560);
	}
	else
	{
		pLis->setVari(102,1);
		pLis->setVari(109,1);
		pLis->setVari(203,500);
		pLis->setVari(210,500);
	}

	
	
	// Corx centrada de la tabla
	int width=0;
	// Vari[21] son los posibles celdas a pintar
	for(int i=0;i<pLis->getVari(4);i++)
		width+=pLis->getVari(short(100+i))*pLis->getVari(short(200+i));
	
	long center=getCenter();
	long offsetx=center-(width/2);
	if (offsetx>25)
		pLis->setVari(3,offsetx-25);
	else
		pLis->setVari(3,10);

	// Codigo NOC, NPC, CGA, dependiente del .lis de cabeceras
	pLis->setData(1006,CReportTemplate::pLis->getData(300)); 
}
/////////////////////////////////////////////////////////////////////
RWDate CHRC74::OnGetEventDate() const
{
	return INVALID_RWDATE;
}
RWTime CHRC74::OnGetEventTime() const
{
	return INVALID_RWTIME;
}
RWWString CHRC74::OnGetLine(const int lineNumber,const char *language) const
{
	return CReportTemplate::OnGetLine(lineNumber,language);
}
unsigned short CHRC74::OnCallbackFn( struct USR_TAB * pTableInfo )
{
	return CReportBase::OnCallbackFn(pTableInfo);
}

void CHRC74::assignDataIndividual(CHMatch *pMatch)
{
		
	// Reseteo
	for(short i=0;i<short(pLis->getVari(4));i++)
	{
		pLis->setData(2000+i,"");
		// En negrita la parte del equipo y en normal los miembros
		if(pMatch->isTeam())
			 pLis->setDataFont(2000+i,pLis->getVari(507));
		else pLis->setDataFont(2000+i,pLis->getVari(506));
	}
	

	CHMatchResult *pHome=pMatch->getMatchResultHome();
	CHMatchResult *pAway=pMatch->getMatchResultAway();

	CHPoolResult *pPoolHome=(CHPoolResult*)pHome->getPoolResult();
	CHPoolResult *pPoolAway=(CHPoolResult*)pAway->getPoolResult();

	CHInscription *pInsHome=(CHInscription*)pHome->getInscription();
	CHInscription *pInsAway=(CHInscription*)pAway->getInscription();

	// Bout Number
	if(pMatch->isTeam())
		 pLis->setData(2000,pMatch->getRoundMatch());
	else pLis->setData(2000,pMatch->getIdParent());
	
	// Seed Number 1
	if(pInsHome)
		pLis->setData(2001,pInsHome->getSeed());
	
	// Master Type 1
	if(pInsHome)
		pLis->setData(2002,pInsHome->getRegMasterTypeAsString(false));
	

	// Name 1
	if(pInsHome)
		 pLis->setData(2003,pInsHome->getPrnLName());
	else pLis->setData(2003,pLis->getData(1501));

	// NOC Code 1
	if(pInsHome)
		pLis->setData(2004,pInsHome->getGroup());

	// Points 1
	if(pPoolHome)
	{
		//pLis->setData(2005,pHome->getPointsAsString());
		pLis->setData(2005,pPoolHome->getPoolPointsFStr(pMatch->getRound()));
	}

	// Result
	
	if(pMatch->isTeam())
		 pLis->setData(2006,pMatch->getTotalResult(true));
	else pLis->setData(2006,pMatch->getResultAsString());
	

	// Points 2
	if(pPoolAway)
	{
		//pLis->setData(2007,pAway->getPointsAsString());
		pLis->setData(2007,pPoolAway->getPoolPointsFStr(pMatch->getRound()));
	}

	// Seed Number 2
	if(pInsAway)
		pLis->setData(2008,pInsAway->getSeed());

	// Master Type 2
	if(pInsAway)
		pLis->setData(2009,pInsAway->getRegMasterTypeAsString(false));
	

	// Name 2
	if(pInsAway)
		 pLis->setData(2010,pInsAway->getPrnLName());
	else pLis->setData(2010,pLis->getData(1501));

	// NOC Code 2
	if(pInsAway)
		pLis->setData(2011,pInsAway->getGroup());	
	
}

CReportBase::ReportReturn CHRC74::paintMembers(CHMatch *pMatch)
{
	
	GSortedVector vSubMatches=pMatch->getSubMatches();
	CHMatch *pSubMatch=0;
	for(size_t i=0;i<vSubMatches.entries();i++)
	{
		pSubMatch=(CHMatch*)vSubMatches[i]->getElement();
		
		assignDataMember(pSubMatch);
		// Pintamos la members
		if( !pLis->runline(3) )
			return OnError(error,10);
		
	}
	
	return exit;
}
void CHRC74::assignDataMember(CHMatch *pSubMatch)
{
		
	// Reseteo
	for(short i=0;i<short(pLis->getVari(4));i++)
		pLis->setData(3000+i,"");
	


	CHMatchResult *pHome=pSubMatch->getMatchResultHome();
	CHMatchResult *pAway=pSubMatch->getMatchResultAway();

	CHMatchMember *pMatchMemHome=(CHMatchMember*)pHome->getMatchMember();
	CHMatchMember *pMatchMemAway=(CHMatchMember*)pAway->getMatchMember();
	
	CHMember *pMemberHome=0;
	CHMember *pMemberAway=0;
	
	if(pMatchMemHome)
		pMemberHome=(CHMember*)pMatchMemHome->getMember();

	if(pMatchMemAway)
		pMemberAway=(CHMember*)pMatchMemAway->getMember();

	// Bout Number
	pLis->setData(3000,pSubMatch->getSubMatch());
	
		
	// Master Type 1
	if(pMatchMemHome)
	{
		CHRegister *pRegister=(CHRegister*)pMatchMemHome->getRegister();
		if(pRegister)
			pLis->setData(3001,pRegister->getMasterTypeAsString(false));
		
	}

	// Name 1
	if(pMatchMemHome)
		 pLis->setData(3003,pMatchMemHome->getPrnLName());
	else if(pHome->getBye())
		pLis->setData(3003,pLis->getData(1501));

	// NOC Code 1
	if(pMatchMemHome)
		 pLis->setData(3004,pMatchMemHome->getGroup());

	// Rating 1
	/*(pMatchMemHome)
		pLis->setData(3005,pMatchMemHome->getPointsAsString());*/

	// Result
	pLis->setData(3006,pSubMatch->getResultAsString());

	
	// Rating 2
	/*(pMemberAway)
		pLis->setData(3007,pMemberAway->getPointsAsString());*/

	// Seed Number 2
	/*if(pMatchMemAway)
		pLis->setData(3008,pMatchMemAway->getSeed());*/

	// Master Type 2
	if(pMatchMemAway)
	{
		CHRegister *pRegister=(CHRegister*)pMatchMemAway->getRegister();
		if(pRegister)
			pLis->setData(3008,pRegister->getMasterTypeAsString(false));
		
	}

	// Name 2
	if(pMatchMemAway)
		 pLis->setData(3010,pMatchMemAway->getPrnLName());
	else if(pAway->getBye())
		pLis->setData(3010,pLis->getData(1501));
	
	// NOC Code 2
	if(pMatchMemAway)
		 pLis->setData(3011,pMatchMemAway->getGroup());
	
	
}
void CHRC74::buildVector()
{
		
	RWSetIterator iter(CHMemoryDataBase::getColMatchs());
	
	CHMatch *pMatch = 0;
	while ((pMatch = (CHMatch*) iter())!=0 )
	{
		if (pMatch->getPhase() == pPhase && !pMatch->getSubMatch() &&
			(round==pMatch->getRound() || round==ALL_ROUNDS))
			vMatches.insert(pMatch);
	}

	vMatches.sort(orderMatches);
}
 
RWBoolean CHRC74::changeRound(CHMatch *pMatch)
{
	CHMatch *pMatchAux = 0;
	if((index)<vMatches.entries())
		pMatchAux=(CHMatch *)vMatches[index]->getElement();

	if(!pMatchAux)
		return false;

	if(pMatchAux->getRound()!=pMatch->getRound())
		return true;
	

	return false;
}

void CHRC74::setDynamicLegends()
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