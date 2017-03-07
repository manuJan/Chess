/*************************************************************************************
*			© Copyright MSL Software, S.L., 2001
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHCnfgDisciplineFormView.cpp
*   Description	: CH Configuration of Discipline
*
*	Author		: Chess Team
*	Date created: 15-12-2005
* 	Project		: CH Manager
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#include "stdafx.h"
#include "CHmanager.h"
#include "CHCnfgDisciplineFormView.h"
#include "CHDefines.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


unsigned getNumAt(RWCString &str,size_t from,size_t n)
{
        if (str.length()<from+n) return 0;
        return atoi(RWCString(str(from,n)));
}

/////////////////////////////////////////////////////////////////////////////
// CCHCnfgDisciplineFormView

IMPLEMENT_DYNCREATE(CCHCnfgDisciplineFormView, CFormView)

CCHCnfgDisciplineFormView::CCHCnfgDisciplineFormView()
:GCnfgDisciplineFormView()
,pDiscipline(0)
,fChange(false)
{
	//{{AFX_DATA_INIT(CCHCnfgDisciplineFormView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CCHCnfgDisciplineFormView::~CCHCnfgDisciplineFormView()
{
}

void CCHCnfgDisciplineFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCHCnfgDisciplineFormView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCHCnfgDisciplineFormView, GCnfgDisciplineFormView)
	//{{AFX_MSG_MAP(CCHCnfgDisciplineFormView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCHCnfgDisciplineFormView diagnostics

#ifdef _DEBUG
void CCHCnfgDisciplineFormView::AssertValid() const
{
	CFormView::AssertValid();
}

void CCHCnfgDisciplineFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCHCnfgDisciplineFormView message handlers

GDiscipline* CCHCnfgDisciplineFormView::getCopyDiscipline()
{ 
	pDiscipline = new CHDiscipline((CHDiscipline &) mem()->getDiscipline());
	return  pDiscipline;
}

BOOL CCHCnfgDisciplineFormView::exit()
{
	if(compareChange())
		setIsChange();
	
	return GCnfgDisciplineFormView::exit();
}

void CCHCnfgDisciplineFormView::init()
{
	GCnfgDisciplineFormView::init();
	
	short yIni=480;

	// CHESS SETTINGS
	w->createLabel(DIS_LBL_TITTLE		,CRect(75,yIni    ,575,yIni+ 30),"Chess Settings",BORDER_NONE,JUST_LEFT,IDBCK,IDCOL,IDFNT_BIG);
	w->createLabel(DIS_LBL_LINE			,CRect(75,yIni+ 32,575,yIni+ 35),"",BORDER_NONE,JUST_LEFT,IDBCK_BOX);

	// Championship Type
	w->createLabel(DIS_LBL_PROGRESSION	,CRect(75,yIni+ 40,300,yIni+ 60),"Progression",BORDER_SINGLE,JUST_CENTER,IDBCK_BUT,IDCOL,IDFNT_BOLD);
	w->createRadio(DIS_RAD_MANUAL		,CRect(75,yIni+ 60,300,yIni+ 80),"Manual Progression"		,JUST_LEFT	,false,100,IDBCK,IDCOL,IDFNT);
	w->createRadio(DIS_RAD_AUTO		,CRect(75,yIni+ 80,300,yIni+100),"Automatic Progression"	,JUST_LEFT	,false,100,IDBCK,IDCOL,IDFNT);

	fillCHControls();
}

void CCHCnfgDisciplineFormView::fillCHControls()
{//pinto en el interface los valores que tiene la disciplina a la entrada del dialogo

	RWBoolean autoProg=pDiscipline->getAutoProg();

	w->changeCheck(DIS_RAD_MANUAL,!autoProg);
	w->changeCheck(DIS_RAD_AUTO,autoProg);

}

RWBoolean CCHCnfgDisciplineFormView::compareChange()
{//comparo si han cambiado mis valores en el dialogo

	//asigno los valores del dialogo a la copia
	setValuesToCopy();

	CHDiscipline & aCHDiscipline=(CHDiscipline &)((CCHManagerApp *)AfxGetApp())->memG()->getDiscipline();

	//comparo copia y memorydatabase
	if ( aCHDiscipline.getAutoProg()			!= pDiscipline->getAutoProg())
		return true;

	return false;
}


void CCHCnfgDisciplineFormView::setValuesToCopy()
{//asigno los valores del dialogo a la copia
	
	// Progression
	if( w->getCheck(DIS_RAD_MANUAL) ) 
		pDiscipline->setAutoProg(false);
	else if( w->getCheck(DIS_RAD_AUTO) ) 
		pDiscipline->setAutoProg(true);

	
}

void CCHCnfgDisciplineFormView::saveDiscipline() // Doy al boton SAVE
{
	if (compareChange())
	{
		CHDiscipline & disc=(CHDiscipline &)((CCHManagerApp *)AfxGetApp())->memG()->getDiscipline();
		disc=*pDiscipline;
		setIsChange(); // Funcion inline en la clase GCnfgDisciplineFormView que es un 
		               // include que esta en el ARDisciplineFormView.h
	}
}