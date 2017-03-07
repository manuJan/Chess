/*************************************************************************************
*			© Copyright MSL Software, S.L., 2001
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:	CHTreatPhases.cpp
*	Description	:   Session proccess
*
*	Author		:	Fernando Garcia
*	Date created:   
* 	Project		:	Chess Manager
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdafx.h"
#include "chmanager.h"
#include "CHTreatPhases.h"

#include <Sports\CH\Data\CHDiscipline.h>

#include <CORE/TH/GTHOrderFunctions.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHTreatPhases dialog


CHTreatPhases::CHTreatPhases(GTHMemoryDataBase * pMemory, GTHEvent * aEvent, GTHProgression *aTHProgression, CWnd* pParent)
	: GTreatPhases(pMemory,aEvent,aTHProgression,pParent)
{
	//{{AFX_DATA_INIT(CHTreatPhases)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CHTreatPhases::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHTreatPhases)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHTreatPhases, GTreatPhases)
	//{{AFX_MSG_MAP(CHTreatPhases)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHTreatPhases message handlers
void CHTreatPhases::init (BOOL isPool)
{
	GTreatPhases::init(isPool);

	RWWString pool=((CHDiscipline&)pMemDB->getDiscipline()).getSPoolDescription();
	RWWString match=((CHDiscipline&)pMemDB->getDiscipline()).getSMatchDescription();
	RWWString pools=((CHDiscipline&)pMemDB->getDiscipline()).getLPoolDescription();
	RWWString matches=((CHDiscipline&)pMemDB->getDiscipline()).getLMatchDescription();
	
	// Combo Phase
	GSortedVector phases(CHMemoryDataBase::getColPhaseNames(), orderGenericPhaseByOrder);
	if (phases[0])
		w->selectItem(COMBO_PHASES,(LPARAM)phases[0]->getElement());

	// Order
	w->changeTxt(EDITORDER,"1");

	// Pool
	w->changeTxt(EDITPOOLS,"1");

	CString numbyPool;
	numbyPool.Format(_T("No. %s by Round"),matches);
	w->changeTxt(LBLAUX27,numbyPool);

	CString byPool;
	byPool.Format(_T(" by %s"),pool);	
	CString roundsbyPool;
	roundsbyPool.Format(_T("No. Rounds %s"),byPool);
	w->changeTxt(LBLAUX29,roundsbyPool);

	char tmp[100];
	sprintf(tmp,"%d",((CHEvent*)pEvent)->getInscriptions());
	w->changeTxt(EDITCOMPET,tmp);

	calculateNumMatches();
}


void CHTreatPhases::calculateNumMatches()
{
	RWCString competitorsNumber = w->getTxt(EDITCOMPET);
	int nCompetitors = atoi(competitorsNumber);
	int matches=nCompetitors/2;
	if (nCompetitors%2)
		matches++;	

	char aux[5];
	w->changeTxt(EDITMATCHES,itoa(matches,aux,10));
}