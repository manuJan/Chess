/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHAfterInitialLoadDlg.cpp
*	Description	:
*
*	Author		: Javier Juste
*	Date created: 27-Sep-2006
* 	Project		: Chess After Initial Load update data
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdafx.h"
#include "CHAfterInitialLoad.h"
#include "CHAfterInitialLoadDlg.h"

#include <core/G/QRegister.h>
#include <TOOLS\MSLNetwork\MSLNetwork.h>
#include <Sports/CH/Data/CHInscription.h>
#include <Sports/CH/Data/CHEventResult.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Sort Functions
static
int sortMembers(const GVectorElement **a,const GVectorElement **b)
{
	CHMember * pA = (CHMember *)(*a)->getElement();
	CHMember * pB = (CHMember *)(*b)->getElement();
	
	int order= pA->getRegister()->getType() - pB->getRegister()->getType();
	if(order)
		return order;

	return wcsicoll(pA->getPrnLName(),pB->getPrnLName());
}

/////////////////////////////////////////////////////////////////////////////
// CCHAfterInitialLoadDlg dialog

CCHAfterInitialLoadDlg::CCHAfterInitialLoadDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCHAfterInitialLoadDlg::IDD, pParent)
	, m_pMem(0)
	, nPosProgress(0)
{

	//{{AFX_DATA_INIT(CCHAfterInitialLoadDlg)
	m_Names = _T("");
	m_Numbering = _T("");
	m_EventResult = _T("");
	//}}AFX_DATA_INIT
	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCHAfterInitialLoadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCHAfterInitialLoadDlg)
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
	DDX_Text(pDX, IDC_NAMES, m_Names);
	DDX_Text(pDX, IDC_NUMBERING, m_Numbering);
	DDX_Text(pDX, IDC_EVENTRESULT, m_EventResult);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCHAfterInitialLoadDlg, CDialog)
	//{{AFX_MSG_MAP(CCHAfterInitialLoadDlg)
	ON_BN_CLICKED(IDC_UPDATE_BT, OnUpdateBt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCHAfterInitialLoadDlg message handlers

GMemoryDataBase	* CCHAfterInitialLoadDlg::OnNewMemoryDB()
{
	return new CHMemoryDataBase;;
}

BOOL CCHAfterInitialLoadDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_pMem    = OnNewMemoryDB();		

	POINT pt={5,0};
	m_pOnline =new MSLNetwork();
	m_pOnline->init(m_hWnd,m_hWnd,pt,m_pMem,true);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CCHAfterInitialLoadDlg::DestroyWindow() 
{
	if(m_pOnline)
		delete m_pOnline;
	
	//El XXMemoryDataBase lo destruye la DLl MSLNetwork.

	return CDialog::DestroyWindow();
}

void CCHAfterInitialLoadDlg::processRegisters()
{
	RWSetIterator iter(CHMemoryDataBase::getColRegisters());

	int last=0,numbering=0,names=0;
	GRegister * pRegister=0;
	while((pRegister=(GRegister *)iter())!=0)
	{
		//Para poner el numero de Registro en la tabla NUMBERING
		last=pRegister->getRegister();
		if( last>numbering )
			numbering=last;

		//*** ACTUALIZACION DE LOS NAMES DE LOS REGISTROS ***//
		if(setNames(pRegister))
			names++;

		m_progress.SetPos(++nPosProgress);
		
		UpdateData(FALSE);	
	}

	//*** ACTUALIZACION DE LA TABLA NUMBERING ***//
	if(numbering)
		setNumbering(numbering);

	m_Names.Format(_T("%d/%d"),CHMemoryDataBase::getColRegisters().entries(),names);
}

void CCHAfterInitialLoadDlg::processInscriptions()
{
	RWSetIterator iter(CHMemoryDataBase::getColInscriptions());

	int eventResult=0;
	CHInscription * pInscription=0;
	while((pInscription=(CHInscription*)iter())!=0)
	{
			//*** CREACION DE LOS EVENT RESULTS ***//
			if(setEventResult(pInscription))
				eventResult++;

			//*** ORDENACION DE LOS MEMBERS ***//
			orderMembers(pInscription);

		m_progress.SetPos(++nPosProgress);

		UpdateData(FALSE);	
	}

	m_EventResult.Format(_T("%d/%d"),GMemoryDataBase::getColInscriptions().entries(),eventResult);
}

RWBoolean CCHAfterInitialLoadDlg::setNames(GRegister * pRegister)
{
	if(!pRegister)
		return false;

	GRegisterNames aNamesToFind;
	aNamesToFind.setCode(DBApplication::getAppLanguage());

	RWSetIterator iter(GMemoryDataBase::getColRegisters());
	
	//Composicion de Names de los registros
	GRegisterNames * pCurrentName = (GRegisterNames *) pRegister->getNames().find(&aNamesToFind);
	if(pCurrentName)
	{
		pCurrentName->setSurname(pCurrentName->getSurname());

		if (pRegister->getCountry().length())
			pCurrentName->calculate(pRegister->getCountry());
		else
			pCurrentName->calculate();

		pRegister->uSQL(aConnect);
			
		return true;
	}
	return false;
}

RWBoolean CCHAfterInitialLoadDlg::setNumbering(int numbering)
{
	if(numbering>0)
	{
		QRegister qReg(&aConnect);
		qReg.getNextFreeNumber(numbering);

		m_Numbering.Format(_T("%d"),numbering);
		
		return true;
	}
	return false;
}

RWBoolean CCHAfterInitialLoadDlg::setEventResult(CHInscription * pInscription)
{
	if(!pInscription)
		return false;

	CHEventResult aNewEventResult;
	aNewEventResult.setInscription(pInscription);

	if(!CHMemoryDataBase::findEventResult(aNewEventResult))
	{
		CHEventResult * pNewEventResult = (CHEventResult *)((CHMemoryDataBase*)m_pMem)->setEventResult(aNewEventResult);
		if(pNewEventResult )
		{
			pNewEventResult->uSQL(aConnect);
			return true;
		}
	}
	return false;
}

void CCHAfterInitialLoadDlg::orderMembers(CHInscription * pInscription)
{
	if(!pInscription)
		return;

	RWSet sMembers;
	getMembers(pInscription,sMembers);
	GSortedVector vMembers(sMembers,sortMembers);

	CHMember * pMember=0;
	int idxInd=1,idxTeam=50;
	for(size_t i=0 ; i<vMembers.entries();i++)
	{
		pMember=(CHMember*)vMembers[i]->getElement();

		if(pMember->getRegister()->getType()==GRegister::individual)
			pMember->setOrder(idxInd++);
		else
			pMember->setOrder(idxTeam++);

		pMember->uSQL(aConnect);
	}
}

void CCHAfterInitialLoadDlg::getMembers(CHInscription * pInscription,RWSet & sMembers)
{
	RWSetIterator iterMember(CHMemoryDataBase::getColMember());

	CHMember * pMember=0;
	while((pMember = (CHMember*)iterMember())!=0)
	{
		if(pMember->getInscription()==pInscription)
			sMembers.insert(pMember);
	}
}
/////////////////////////////////////////////////////////////////////
//Inicializacion de la barra de progreso
/////////////////////////////////////////////////////////////////////
void CCHAfterInitialLoadDlg::initProgressControl()
{
	short totalProgress=short(CHMemoryDataBase::getColRegisters().entries() +
	   	                      CHMemoryDataBase::getColInscriptions().entries());
	m_progress.SetRange(0,totalProgress);

	nPosProgress = 0;
}

/////////////////////////////////////////////////////////////////////
//Punto de entrada para actualizar la base de datos
/////////////////////////////////////////////////////////////////////
void CCHAfterInitialLoadDlg::OnUpdateBt() 
{
	if(!m_pMem)
		return; 

	aConnect=DBApplication::getConnection();

	initProgressControl();

	SetCursor(LoadCursor(0,IDC_WAIT));

	processRegisters();
	processInscriptions();

			
	UpdateData(FALSE);	

	SetCursor(LoadCursor(0,IDC_ARROW));
}
