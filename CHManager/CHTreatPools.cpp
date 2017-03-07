/*************************************************************************************
*			© Copyright MSL Software, S.L., 2001
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:	CHTreatPools.cpp
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
#include "CHTreatPools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#include <Sports\CH\Data\CHDiscipline.h>

CHTreatPools::CHTreatPools(GTHMemoryDataBase * pMemory, GTHPhase * aPhase, GTHProgression *aTHProgression,RWBoolean isRealPool/*=true*/, CWnd* pParent/*=NULL*/)
	: GTreatPools(pMemory,aPhase,aTHProgression,isRealPool,pParent)
{
	//{{AFX_DATA_INIT(CHTreatPools)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CHTreatPools::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHTreatPools)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHTreatPools, GTreatPools)
	//{{AFX_MSG_MAP(CHTreatPools)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHTreatPools message handlers

BOOL CHTreatPools::OnInitDialog()
{
	BOOL ret=GTreatPools::OnInitDialog();

	RWWString pool=((CHDiscipline&)pMemDB->getDiscipline()).getSPoolDescription();
	RWWString match=((CHDiscipline&)pMemDB->getDiscipline()).getSMatchDescription();
	RWWString pools=((CHDiscipline&)pMemDB->getDiscipline()).getLPoolDescription();
	RWWString matches=((CHDiscipline&)pMemDB->getDiscipline()).getLMatchDescription();
	
	CString numbyPool;
	numbyPool.Format(_T("No. %s by Round"),matches);
	w->changeTxt(LBLAUX23,numbyPool);

	CString byPool;
	byPool.Format(_T(" by %s"),pool);	
	CString roundsbyPool;
	roundsbyPool.Format(_T("No. Rounds %s"),byPool);
	w->changeTxt(LBLAUX24,roundsbyPool);

	return ret;
}

void CHTreatPools::calculateNumMatches()
{
	RWCString competitorsNumber = w->getTxt(EDITCOMPET);
	int nCompetitors=atoi(competitorsNumber);
	int matches=nCompetitors/2;
	if (nCompetitors%2)
		matches++;
	
	char aux[5];
	w->changeTxt(EDITMATCHES,itoa(matches,aux,10));
}