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

#include "stdafx.h"
#include "CHRC51.h"
#include "CHRLegends.h"

#include "..\CHMngtModel\CHEvent.h"
#include "..\CHMngtModel\CHPhase.h"
#include "..\CHMngtModel\CHPool.h"
#include "..\CHMngtModel\CHPoolResult.h"
#include "..\CHMngtModel\CHInscription.h"
#include "..\CHMngtModel\CHRegister.h"

////////////////////////////////////////////////////////////////////////////////////
static int orderPoolResult(const MSLItem** a, const MSLItem** b)
{
	CHPoolResult * pPoolResultA = (CHPoolResult *) (*a);
	CHPoolResult * pPoolResultB = (CHPoolResult *) (*b);

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
,m_pLis(0)
,m_pPhase(pSelPhase)
,m_index(0)
,m_pLegends(0)
{
	m_pLegends=new CHRLegends(this,m_pReport,CH51);
	
}

/////////////////////////////////////////////////////////////////////
CHRC51::~CHRC51()
{
	if ( m_pLegends )
		delete m_pLegends;	
}

/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
MSLString CHRC51::getNameOfSourceLis(void)
{
	return "CH.C51.lis";	
}

/////////////////////////////////////////////////////////////////////
void CHRC51::OnBeginReport()
{
	CReportManager& aReportMng = m_pReport->getManager();

	// Instanciamos una referencia al lis del report
	MSLString lis = getNameOfSourceLis();
	CLis& aLis = m_pReport->setLis(lis);
	m_pLis = &aLis;
	if( m_pLis && m_pLis->isValid() )
	{
		// Iniciamos variables
		aReportMng.setCtrlmargin(true);
		m_pReport->setCursor(0,0);
		m_pLis->setVari(1,getCenter());
		m_pLis->setVari(2,aReportMng.getXMax()-getRightMargin());

		m_bOkLis = true;
		// SetVaris Font
		initLabels();
		setVaris(m_pLis);				
		setGlobalVaris();
		
		// Iniciamos funcion para el relleno de la tabla
		m_pLis->setCallBack(1,this);
		m_pLis->setCallBack(2,this);

		//Leyendas
		m_pLegends->loadLis();
		setDynamicLegends();

		buildVector();		
	}
	else
	{	// Si hubo error en el report mostramos el error.
		MessageBox(0,MSLWString(aReportMng.getLastError()+"\n"+lis),L"",MB_OK);
	}
}

void CHRC51::initLabels()
{
	m_pLis->setData(1000,getUserLabel(100)); //"Seed Number"	
	m_pLis->setData(1001,getUserLabel(101)); //"Title"			
	m_pLis->setData(1002,getUserLabel(102)); //"Name"			
	m_pLis->setData(1003,getUserLabel(103)); //"Initial Rating"
}

/////////////////////////////////////////////////////////////////////
CReportBase::ReportReturn CHRC51::OnBody()
{
		
	// Controlamos que haya datos para pintar
	if( !m_vPoolResults.entries() )
	{
		MessageBox(0,L"There are not competitor/s",L"",MB_OK);		
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
	
	if( !m_pLegends->runLis() )
		return OnError(error,10);
	
	return exit;
}

/////////////////////////////////////////////////////////////////////
CReportBase::ReportReturn CHRC51::paintTemplateHeader()
{
	// Pintamos la cabecera
	if( !m_pLis->runline(1) )
		return OnError(error,10);
	
	return exit;
}

/////////////////////////////////////////////////////////////////////
CReportBase::ReportReturn CHRC51::paintTemplateResults()
{
	CHPoolResult * pPoolResult = 0;
	while( m_index < m_vPoolResults.entries() )
	{
		pPoolResult = (CHPoolResult *)m_vPoolResults[m_index];
		if( !pPoolResult )
			return OnError(error,120);

		assignDataIndividual(pPoolResult);

		// Pintamos los datos 
		if( !m_pLis->runline(2) )
			return OnError(error,130);

		m_index++;
		
		// Comprobamos si hay salto de pagina
		if( IsPageBreak(short(m_pLis->getVari(800))) && m_index != m_vPoolResults.entries() )
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
	
	CHEvent *pEvent=(CHEvent*)m_pPhase->getEvent();

	// En equipos no se pinta el Master Type, no lo hay.
	if(pEvent->isTeam())
		 m_pLis->setVari(101,0);
	else m_pLis->setVari(101,1);

	
	// Corx centrada de la tabla
	int width=0;
	// Vari[21] son los posibles celdas a pintar
	for(int i=0;i<m_pLis->getVari(4);i++)
		width+=m_pLis->getVari(short(100+i))*m_pLis->getVari(short(200+i));
	
	long center=getCenter();
	long offsetx=center-(width/2);
	if (offsetx>25)
		m_pLis->setVari(3,offsetx-25);
	else
		m_pLis->setVari(3,10);

	// Codigo NOC, NPC, CGA, dependiente del .lis de cabeceras
	m_pLis->setData(1004,CReportTemplate::m_pHeaderLis->getData(301)); 
}

/////////////////////////////////////////////////////////////////////
MSLDate CHRC51::OnGetEventDate() const
{
	return INVALID_DATE;
}

MSLTime CHRC51::OnGetEventTime() const
{
	return INVALID_TIME;
}

MSLWString CHRC51::OnGetLine(const int lineNumber,const char *language) const
{
	if (lineNumber==2 && m_pHeaderPhase && m_pHeaderPhase->getPhase()==SWISS_ROUND)
		return L"";
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
	for(short i=0;i<short(m_pLis->getVari(4));i++)
		m_pLis->setData(2000+i,"");
	
	
	// Start Number
	if(pInscription)
		m_pLis->setData(2000,pPoolResult->getInscriptionSeed());
	
	// Master Type
	if(pRegister)
		m_pLis->setData(2001,pRegister->getMasterTypeSDescription());
		
	

	// Name
	if(pRegister)
		m_pLis->setData(2002,pRegister->getPrnLName());

	// Initial Rating
	if(pInscription)
		m_pLis->setData(2003,pPoolResult->getInscriptionRating());

	// Group Code
	if(pRegister)
		m_pLis->setData(2004,pRegister->getGroup());
	
}

void CHRC51::buildVector()
{		
	MSLSetIterator iter(CHMemoryDataBase::getCol(__CHPOOLRESULT));
	
	CHPoolResult *pPoolResult = 0;
	while ((pPoolResult = (CHPoolResult*) iter())!=0 )
	{
		if (pPoolResult->getBye())
			continue;

		if (pPoolResult->getPhase() == m_pPhase )
			m_vPoolResults.insert(pPoolResult);
	}

	m_vPoolResults.setFcCompare(orderPoolResult);
	m_vPoolResults.sort();
}

void CHRC51::setDynamicLegends()
{
	CHMasterType *pMasterType = 0;
	MSLSetIterator iter(CHMemoryDataBase::getCol(__CHMASTERTYPE));
	
	while ((pMasterType=(CHMasterType*)iter())!=0)
	{
		if(pMasterType->getMasterType())
			m_pLegends->setDynamic( pMasterType->getSDescription());							
	}

	m_pLegends->createDynamic();
}
