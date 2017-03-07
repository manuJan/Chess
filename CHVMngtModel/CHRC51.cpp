/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHRC51.cpp
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
#include "CHRC51.h"
#include "CHRLegends.h"
#include <SPORTS/CH/DATA/CHMsgDefines.h>
#include <SPORTS/CH/DATA/CHRegister.h>

////////////////////////////////////////////////////////////////////////////////////
static int orderPoolResult(const GVectorElement** a, const GVectorElement** b)
{
	CHPoolResult * pPoolResultA = (CHPoolResult *) (*a)->getElement();
	CHPoolResult * pPoolResultB = (CHPoolResult *) (*b)->getElement();

	CHPool *pPoolA=(CHPool*)pPoolResultA->getPool();
	CHPool *pPoolB=(CHPool*)pPoolResultB->getPool();

	// Order by Pool
	int order = pPoolA->getOrder() - pPoolB->getOrder();
	if( order )
		return order;

	// Si alguno de ellos no tienen la sesión asignada va para abajo.
	if (!pPoolResultA->getInscriptionSeed())
		return 1;
	if (!pPoolResultB->getInscriptionSeed())
		return -1;

	// Order by Seed
	order = pPoolResultA->getInscriptionSeed() - pPoolResultB->getInscriptionSeed();
	if( order )
		return order;
	
	// Order by key
	return strcmp(pPoolResultA->getKey(),pPoolResultB->getKey());
}
/////////////////////////////////////////////////////////////////////
CHRC51::CHRC51(CReportManager& aReportManager,CReportConfig& aReportConfig,CHPhase * pSelPhase)
:CHReportTemplate(aReportManager,aReportConfig,pSelPhase)
,pLis(0)
,pPhase(pSelPhase)
,index(0)
,pLegends(0)
{
	pLegends=new CHRLegends(this,pReport,CHRLegends::eC51);
	
}

/////////////////////////////////////////////////////////////////////
CHRC51::~CHRC51()
{
	if ( pLegends )
		delete pLegends;
	vPoolResults.clearAndDestroy();
}

/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
RWCString CHRC51::getNameOfSourceLis(void)
{
	RWCString lang = DBApplication::getAppLanguage();
	
	return CHMemoryDataBase::getDiscipline().getCode()+".C51."+lang+".lis";
	
}

/////////////////////////////////////////////////////////////////////
void CHRC51::OnBeginReport()
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

		//Leyendas
		pLegends->loadLis();
		setDynamicLegends();

		buildVector();

		
	}
	else
	{	// Si hubo error en el report mostramos el error.
		AfxMessageBox(RWWString(aReportMng.getLastError(),RWWString::multiByte)+
					  _T("\n")+RWWString(getNameOfSourceLis(),RWWString::multiByte));
	}
}

/////////////////////////////////////////////////////////////////////
CReportBase::ReportReturn CHRC51::OnBody()
{
		
	// Controlamos que haya datos para pintar
	if( !vPoolResults.entries() )
	{
		AfxMessageBox(_T("There are not competitor/s"));
		return error;
	}
		
	// Template de Cabeceras
	if( paintTemplateHeader() == error )
		return error;
	
	// Template de Results
	return paintTemplateResults();
	

}

CReportBase::ReportReturn CHRC51::paintLegends()
{
	
	if( !pLegends->runLis() )
		return OnError(error,10);
	
	return exit;
}

/////////////////////////////////////////////////////////////////////
CReportBase::ReportReturn CHRC51::paintTemplateHeader()
{
	CHEvent * pEvent = (CHEvent *)pPhase->getEvent();
	
	// Pintamos la cabecera
	if( !pLis->runline(1) )
		return OnError(error,10);

	
	return exit;
}

/////////////////////////////////////////////////////////////////////
CReportBase::ReportReturn CHRC51::paintTemplateResults()
{
	CHEvent * pEvent = (CHEvent *)pPhase->getEvent();
			
	CHPoolResult * pPoolResult = 0;
				
	while( index < vPoolResults.entries() )
	{
		pPoolResult = (CHPoolResult *)vPoolResults[index]->getElement();
		
		if( !pPoolResult )
			return OnError(error,120);
				

		assignDataIndividual(pPoolResult);

		// Pintamos los datos 
		if( !pLis->runline(2) )
			return OnError(error,130);

		index++;
		
		// Comprobamos si hay salto de pagina
		if( IsPageBreak(short(pLis->getVari(800))) && index != vPoolResults.entries() )
		{
			// Leyendas
			if( paintLegends() == error )
				return error;
			return ok;
		}
	}
	
	// Leyendas
	if( paintLegends() == error )
		return error;
	
	return exit;
}
void CHRC51::setGlobalVaris()
{
	
	CHEvent *pEvent=(CHEvent*)pPhase->getEvent();

	// En equipos no se pinta el Master Type, no lo hay.
	if(pEvent->isTeam())
		 pLis->setVari(101,0);
	else pLis->setVari(101,1);

	
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
	pLis->setData(1004,CReportTemplate::pLis->getData(301)); 
}
/////////////////////////////////////////////////////////////////////
RWDate CHRC51::OnGetEventDate() const
{
	return INVALID_RWDATE;
}
RWTime CHRC51::OnGetEventTime() const
{
	return INVALID_RWTIME;
}
RWWString CHRC51::OnGetLine(const int lineNumber,const char *language) const
{
	return CReportTemplate::OnGetLine(lineNumber,language);
}
unsigned short CHRC51::OnCallbackFn( struct USR_TAB * pTableInfo )
{
	return CReportBase::OnCallbackFn(pTableInfo);
}

void CHRC51::assignDataIndividual(CHPoolResult *pPoolResult)
{
	
	CHRegister *pRegister=(CHRegister*)pPoolResult->getRegister();
	CHInscription *pInscription=(CHInscription*)pPoolResult->getInscription();
	
	// Reseteo
	for(short i=0;i<short(pLis->getVari(4));i++)
	{
		pLis->setData(2000+i,"");
	}
	

	// Start Number
	if(pInscription)
		pLis->setData(2000,pPoolResult->getInscriptionSeed());
	
	// Master Type
	if(pRegister)
		pLis->setData(2001,pRegister->getMasterTypeAsString(false));
		
	

	// Name
	if(pRegister)
		pLis->setData(2002,pRegister->getPrnLName());

	// Initial Rating
	if(pInscription)
		pLis->setData(2003,pPoolResult->getInscriptionRating());

	// Group Code
	if(pRegister)
		pLis->setData(2004,pRegister->getGroup());
	
}

void CHRC51::buildVector()
{
		
	RWSetIterator iter(CHMemoryDataBase::getColPoolResults());
	
	CHPoolResult *pPoolResult = 0;
	while ((pPoolResult = (CHPoolResult*) iter())!=0 )
	{
		if (pPoolResult->getPhase() == pPhase )
			vPoolResults.insert(pPoolResult);
	}

	vPoolResults.sort(orderPoolResult);
}

void CHRC51::setDynamicLegends()
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
