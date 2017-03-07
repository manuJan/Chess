/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHFinalStandingsDlg.cpp
*	Description	: Implementation for the CHFinalStandingsDlg class.
*
*	Author		: CH Team
*	Date created: 19-07-2005
* 	Project		: CHManager
*	
* 	Modification history
*	By			: 
*	Date		: 
*	Changes		: 
*
***************************************************************************************/

#include "stdafx.h"
#include "CHManager.h"
#include "CHDefines.h"
#include "CHFinalStandingsDlg.h"
#include <GUI/FLAGS/flags.h>
#include <CORE/G/GMsgDefines.h>
#include <CORE/TH/GTHMsgDefines.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////
static int orderEventResults(const void* a, const void* b, LPARAM lParamSort)
{
	UNREFERENCED_PARAMETER(lParamSort);

	CHEventResult * pEventResultA = (CHEventResult *)a;
	CHEventResult * pEventResultB = (CHEventResult *)b;

	if( !pEventResultA->getRankPo() && pEventResultB->getRankPo() )
		return 1;
	if( !pEventResultB->getRankPo() && pEventResultA->getRankPo() )
		return -1;

	int order = pEventResultA->getRankPo() - pEventResultB->getRankPo();
	if( order )
		return order;

	return _wcsicoll(pEventResultA->getPrnLName(),pEventResultB->getPrnLName());
}

static int orderQualitativeByCode(const GVectorElement** a, const GVectorElement** b)
{
	GQualitative * pQualitativeA=(GQualitative*)(*a)->getElement();
	GQualitative * pQualitativeB=(GQualitative*)(*b)->getElement();

	return strcmp(pQualitativeA->getCode(),pQualitativeB->getCode());
}

////////////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CHFinalStandingsDlg, CDialog)
	//{{AFX_MSG_MAP(CHFinalStandingsDlg)
	ON_WM_SIZE()
	ON_MESSAGE(UM_PAINTGRID     ,OnPaintGrid     )
	ON_MESSAGE(UM_DBLCLICK      ,OnDblClick      )
	ON_MESSAGE(UM_CURSOROVERGRID,OnCursorOverGrid)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////////////////
CHFinalStandingsDlg::CHFinalStandingsDlg(CWnd * pParent, CHEvent * pSelEvent)
:CDialog(CHFinalStandingsDlg::IDD, pParent)
,pEvent(pSelEvent)
,w(0)
{
	m_pMem = (CHMemoryDataBase *) ((APP *)AfxGetApp())->memG();
}

////////////////////////////////////////////////////////////////////////////////////
CHFinalStandingsDlg::~CHFinalStandingsDlg()
{
	if( w ) delete w;
	APP::unlock("Final Standings");
}

////////////////////////////////////////////////////////////////////////////////////
BOOL CHFinalStandingsDlg::OnInitDialog() 
{
	if( !APP::lock("Final Standings") )
	{
		EndDialog(IDCANCEL);
		return TRUE;
	}

	CDialog::OnInitDialog();

	w = new CGraphicWnd(this);
	INITW(w);

	fillEventResultsVector();

	HINSTANCE hInstOld = AfxGetResourceHandle();
	AfxSetResourceHandle(getResourceHandleGMI());

	// Bitmaps
	w->addBitmapT(CH_BMP_GOLD,5008);
	w->addBitmapT(CH_BMP_SILVER,5007);
	w->addBitmapT(CH_BMP_BRONZE,5006);

	AfxSetResourceHandle(hInstOld);

	w->createLabel (CH_LBL_STANDINGS  ,CRect(5, 5,735,35),"FINAL STANDINGS",BORDER_UP  ,JUST_CENTER,IDBCK,IDCOL,IDFNT_BIG);
	int maximumHeight=615;
	if(maximumHeight>short((80+vEventResults.entries()*25)))
		maximumHeight=(80+vEventResults.entries()*25);

	w->createFrame (CH_FRAME_STANDINGS,CRect(5,40,735,maximumHeight),BORDER_DOWN,IDCOL);

	w->createGrid   (CH_GRID_STANDINGS,CRect(10,45,720,maximumHeight),BORDER_3DUP,25,IDBCK_GRID,IDCOL,IDFNT,TRUE,30);
	w->gridLineColor(CH_GRID_STANDINGS,GET_COLOR_DEFAULT_LINE,GET_COLOR_DEFAULT_LINE);
	w->addGridColumn(CH_GRID_STANDINGS,"Rank"   ,JUST_CENTER, 40);
	w->addGridColumn(CH_GRID_STANDINGS,"Rank Po",JUST_CENTER, 50);
	w->addGridColumn(CH_GRID_STANDINGS,"      Team"    ,JUST_LEFT  ,200);
	w->addGridColumn(CH_GRID_STANDINGS,"Medal",JUST_CENTER  ,70);
	w->addGridColumn(CH_GRID_STANDINGS,"Medal Date",JUST_CENTER  ,65);
	w->addGridColumn(CH_GRID_STANDINGS,"Incidence",JUST_CENTER,75);
	w->addGridColumn(CH_GRID_STANDINGS,"Initial Rating",JUST_CENTER,70);
	w->addGridColumn(CH_GRID_STANDINGS,"Points",JUST_CENTER,70);
	w->addGridColumn(CH_GRID_STANDINGS,"Final Rating",JUST_CENTER,70);
	fillEventResultsGrid();

	w->createGridCombo(CH_CMB_MEDALS,120,BORDER_DOWN,25,IDBCK,IDCOL,IDFNT);
	fillMedalsCombo();

	w->createGridCombo(CH_QUALITATIVE,120,BORDER_SINGLE,25,IDBCK,IDCOL,IDFNT);
	fillComboQualitative();

	SetWindowPos(&CWnd::wndTop,250,115,745,maximumHeight+30,SWP_SHOWWINDOW);

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////
void CHFinalStandingsDlg::fillMedalsCombo()
{
	GMedal * pMedalGold   = m_pMem->findMedal(GMedallist::GOLD  );
	GMedal * pMedalSilver = m_pMem->findMedal(GMedallist::SILVER);
	GMedal * pMedalBronze = m_pMem->findMedal(GMedallist::BRONZE);
	w->addItem(CH_CMB_MEDALS,0,pMedalGold->getLDescription()  ,CH_BMP_GOLD  ,LPARAM(GMedallist::GOLD  ));
	w->addItem(CH_CMB_MEDALS,1,pMedalSilver->getLDescription(),CH_BMP_SILVER,LPARAM(GMedallist::SILVER));
	w->addItem(CH_CMB_MEDALS,2,pMedalBronze->getLDescription(),CH_BMP_BRONZE,LPARAM(GMedallist::BRONZE));
	w->addItem(CH_CMB_MEDALS,3,"NONE",0,0);
}


void CHFinalStandingsDlg::fillComboQualitative()
{   	
   	w->delAllItems(CH_QUALITATIVE);

	GSortedVector vQualitatives(CHMemoryDataBase::getColQualitatives(),orderQualitativeByCode);
	
	GQualitative * pQualitative=0;
	for(size_t i=0 ; i<vQualitatives.entries();i++)
	{
		pQualitative=(GQualitative *)vQualitatives[i]->getElement();
		w->addItem(CH_QUALITATIVE,i+1,pQualitative->getLDescription(),0,LPARAM(pQualitative));		   
	}
	w->addItem(CH_QUALITATIVE,i,"None",0,LPARAM(0));		   
}

////////////////////////////////////////////////////////////////////////////////////
void CHFinalStandingsDlg::fillEventResultsVector()
{
	vEventResults.clearAndDestroy();
	CHEventResult * pEventResult = 0;
	RWSetIterator it(m_pMem->getColEventResult());
	while( (pEventResult=(CHEventResult *)it()) != 0 )
	{
		if( pEvent == pEventResult->getEvent() )
			vEventResults.insert(pEventResult);
	}
}

////////////////////////////////////////////////////////////////////////////////////
void CHFinalStandingsDlg::fillEventResultsGrid()
{
	CHEventResult * pEventResult = 0;
	w->gridDeleteAllItems(CH_GRID_STANDINGS);
	for(size_t i=0 ; i<vEventResults.entries() ; i++)
	{
		pEventResult = (CHEventResult *)vEventResults[i]->getElement();
		if( !pEventResult )
			continue;
		w->addGridLine(CH_GRID_STANDINGS,LPARAM(pEventResult),"");
	}
	w->gridSort(CH_GRID_STANDINGS,orderEventResults);
}

////////////////////////////////////////////////////////////////////////////////////
GMedallist * CHFinalStandingsDlg::isMedallist(CHEventResult * pEventResult)
{
	GMedal * pMedalGold   = m_pMem->findMedal(GMedallist::GOLD  );
	GMedal * pMedalSilver = m_pMem->findMedal(GMedallist::SILVER);
	GMedal * pMedalBronze = m_pMem->findMedal(GMedallist::BRONZE);

	GMedallist * pMedallist = m_pMem->findMedallist(pEvent,pEventResult->getRegister(),pMedalGold);
	if( pMedallist )
		return pMedallist;

	pMedallist = m_pMem->findMedallist(pEvent,pEventResult->getRegister(),pMedalSilver);
	if( pMedallist )
		return pMedallist;

	pMedallist = m_pMem->findMedallist(pEvent,pEventResult->getRegister(),pMedalBronze);
	if( pMedallist )
		return pMedallist;

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////
LRESULT CHFinalStandingsDlg::OnPaintGrid(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);

	GridItem * gi = (GridItem *)lParam;
	if( !gi )
		return false;

	CHEventResult * pEventResult = (CHEventResult *)gi->lParam;
	if( !pEventResult ) 
		return false;

	switch( gi->x )
	{
		case 0 : // Rank
			 w->paintGridVal(gi->rc.Width()/2,5,pEventResult->getRank(),JUST_CENTER);
			 break;
		case 1 : // Rank Po
			 w->paintGridVal(gi->rc.Width()/2,5,pEventResult->getRankPo(),JUST_CENTER);
			 break;
		case 2 : // Team
		{
			 CBitmap aBitmap;
			 getFlag(pEventResult->getGroup().toMultiByte(),ICO,&aBitmap);
			 w->paintGridUserBmp(4,7,&aBitmap,false);
			 w->paintGridText(23,5	,pEventResult->getPrnLName(),JUST_LEFT);
			 break;
		}
		case 3 : // Medal
		{
			GMedallist * pMedallist = isMedallist(pEventResult);
			if( pMedallist )
			{
				w->paintGridBmp(4,1	,CH_BMP_GOLD+atoi(pMedallist->getMedalKey())-1);
				w->paintGridText(30,5,pMedallist->getMedalLDescription(),JUST_LEFT);
			}
			else
				w->paintGridText(30,5,"",JUST_LEFT);
			break;
		}
		case 4: //Medal Date
			{
				GMedallist * pMedallist = isMedallist(pEventResult);
				if( pMedallist )
					w->paintGridText(gi->rc.Width()/2,5,pMedallist->getDateAsString("%d/%m/%Y"),JUST_CENTER);
			}
			break;
		case 5: //Incidencia
			if(pEventResult->isQualitative())
				w->paintGridText(gi->rc.Width()/2,5,_T(" ") + pEventResult->getQualitativeLDescription(),IDFNT_BOLD,RGB(255,0,0),JUST_CENTER);
			break;

		case 6: //Rating Initial
			{
				CHInscription *pInscription=(CHInscription*)pEventResult->getInscription();
				if(!pInscription)
					return false;

				w->paintGridText(gi->rc.Width()/2,5,pInscription->getRatingAsString(),IDFNT_BOLD,RGB(255,0,0),JUST_CENTER);
			}
			break;
		case 7: //Points Pool Result
			{
				w->paintGridText(gi->rc.Width()/2,5,pEventResult->getPointsPoolResultStr(),IDFNT_BOLD,RGB(255,0,0),JUST_CENTER);
			}
			break;
		case 8: //Rating Final
			{
				w->paintGridText(gi->rc.Width()/2,5,pEventResult->getRatingAsString(),IDFNT_BOLD,RGB(255,0,0),JUST_CENTER);
			}
			break;
	}

	return true;
}

////////////////////////////////////////////////////////////////////////////////////
void CHFinalStandingsDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	if( w ) w->resize();
}

////////////////////////////////////////////////////////////////////////////////////
void CHFinalStandingsDlg::OnDblClick(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	if( wParam != CH_GRID_STANDINGS )
		return;

	CHEventResult * pEventResult = (CHEventResult *)w->getSelectedLParam(CH_GRID_STANDINGS);
	if( !pEventResult )
		return;

	//char oldTxt[200];
	//RWCString newTxt;
	int line   = HIWORD(lParam);
	int column = LOWORD(lParam);

	switch( column )
	{
		case 0 : // Rank
			editRank(false,pEventResult,column,line);
			break;
			
		case 1: //Rank Po
			editRank(true,pEventResult,column,line);
			break;

		case 3 : // Medal
			{
				int actualMedal = 0;
				GMedallist * pMedallist = isMedallist(pEventResult);
				if( pMedallist )
				{
					actualMedal = atoi(pMedallist->getMedalKey());
					w->selectItem(CH_CMB_MEDALS,actualMedal);
				}

				int newMedal = (int)w->showGridCombo(CH_GRID_STANDINGS,CH_CMB_MEDALS,column,line);
				if( pMedallist && actualMedal != newMedal )
				{
					destroyMedallist(pMedallist);
					generateMedallist(pEventResult,newMedal);
					w->gridSort(CH_GRID_STANDINGS,orderEventResults);
					w->selectLParam(CH_GRID_STANDINGS,LPARAM(pEventResult));
				}
				else if( newMedal )
				{
					generateMedallist(pEventResult,newMedal);
					w->gridSort(CH_GRID_STANDINGS,orderEventResults);
					w->selectLParam(CH_GRID_STANDINGS,LPARAM(pEventResult));
				}
				break;
			}
		case 4: //Medal Date
			editMedalDate(pEventResult,column,line);
			break;
		case 5: //Incidence
			editQualitative(pEventResult,column,line);
			break;
		case 6: // Initial Rating
			editInitialRating((CHInscription*)pEventResult->getInscription(),column,line);
			break;
		case 7: // Points
			editPointsPoolResult(pEventResult,column,line);
			break;
		case 8: // Final Rating
			editFinalRating(pEventResult,column,line);
			break;
	}
}

void CHFinalStandingsDlg::editRank(RWBoolean rankPo,CHEventResult * pEventResult,int column,int line)
{
	char oldTxt[200];
	RWCString newTxt;
	sprintf(oldTxt, "%d",rankPo?pEventResult->getRankPo():pEventResult->getRank());
	newTxt = w->editGridCell(CH_GRID_STANDINGS, column, line, oldTxt, "##");
	if( newTxt != oldTxt )
	{
		if(rankPo)
		{
			pEventResult->setRankPo  (short(atoi(newTxt)));
			w->gridSort(CH_GRID_STANDINGS,orderEventResults);
			w->selectLParam(CH_GRID_STANDINGS,LPARAM(pEventResult));
		}
		else
		{
			pEventResult->setRank  (short(atoi(newTxt)));
			w->redrawLine(CH_GRID_STANDINGS,line);
		}

		saveEventResult(pEventResult);
	}
}

void CHFinalStandingsDlg::editMedalDate(CHEventResult * pEventResult,int column,int line)
{
	if(!pEventResult)
		return;

	GMedallist * pMedallist = isMedallist(pEventResult);
	if(pMedallist)
	{
		RWCString aux("");
		if(pMedallist->getDate().isValid())
			aux = pMedallist->getDateAsString("%d/%m/%Y");
		RWCString text = w->editGridCell(CH_GRID_STANDINGS,column,line,aux,"##/##/####",0,true,JUST_CENTER);
		if(text == "" || text.length()==10)
		{
			RWDate aDate;
			if(text.length()==10)
				aDate = RWDATE_DDMMYYYY(text);
			else
				aDate = INVALID_RWDATE;

			if (pMedallist->getDate()!=aDate)
			{
				pMedallist->setDate(aDate);
				saveMedallist(pMedallist);
				w->redrawLine(CH_GRID_STANDINGS,line,line);
			}
		}
	}
}

void CHFinalStandingsDlg::editQualitative(CHEventResult * pEventResult,int column,int line)
{
	GQualitative * pOldQualitative=CHMemoryDataBase::findQualitative(pEventResult->getQualitativeCode());
	w->selectItem(CH_QUALITATIVE,LPARAM(pOldQualitative));
	
	GQualitative * pQualitative = (GQualitative*)w->showGridCombo(CH_GRID_STANDINGS,CH_QUALITATIVE,column,line);
	if(pQualitative != pOldQualitative)
	{
		pEventResult->setQualitative(pQualitative?pQualitative->getCode():"0");
		w->redrawLine(CH_GRID_STANDINGS,line);

		saveEventResult(pEventResult);
	}
}
void CHFinalStandingsDlg::editInitialRating(CHInscription * pInscription,int column,int line)
{
	if(!pInscription)
		return;
	
	RWCString aux("");
	aux = pInscription->getRatingAsString();
	RWCString text = w->editGridCell(CH_GRID_STANDINGS,column,line,aux,"#####",0,true,JUST_CENTER);
	if(text!=aux)
	{
		pInscription->setRating(short(atoi(text)));
		saveInscription(pInscription);
		w->redrawLine(CH_GRID_STANDINGS,line,line);
		
	}
}
void CHFinalStandingsDlg::editPointsPoolResult(CHEventResult * pEventResult,int column,int line)
{
	if(!pEventResult)
		return;
	
	RWCString aux("");
	CHPoolResult *pPoolResult=pEventResult->getPoolResult();
	if(!pPoolResult)
		return;

	aux = pPoolResult->getPointsFStr();
	RWCString text = w->editGridCell(CH_GRID_STANDINGS,column,line,aux,"###.#",0,true,JUST_CENTER);
	if(text!=aux)
	{
		pPoolResult->setPointsF(float(atof(text)));
		savePoolResult(pPoolResult);
		w->redrawLine(CH_GRID_STANDINGS,line,line);
		
	}
}
void CHFinalStandingsDlg::editFinalRating(CHEventResult * pEventResult,int column,int line)
{
	if(!pEventResult)
		return;
	
	RWCString aux("");
	aux = pEventResult->getRatingAsString();
	RWCString text = w->editGridCell(CH_GRID_STANDINGS,column,line,aux,"#####",0,true,JUST_CENTER);
	if(text!=aux)
	{
		pEventResult->setRating(short(atoi(text)));
		saveEventResult(pEventResult);
		w->redrawLine(CH_GRID_STANDINGS,line,line);
		
	}
}

////////////////////////////////////////////////////////////////////////////////////
LRESULT CHFinalStandingsDlg::OnCursorOverGrid(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	int col = LOWORD(lParam);

	if( wParam == CH_GRID_STANDINGS && col != 1 )
		return TRUE;

	return FALSE;
}

////////////////////////////////////////////////////////////////////////////////////
BOOL CHFinalStandingsDlg::PreTranslateMessage(MSG * pMsg)
{
	if( pMsg->message == WM_KEYDOWN )
	{
		if( pMsg->wParam == VK_ESCAPE )
		{
			EndDialog(IDOK);
			return true;
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

////////////////////////////////////////////////////////////////////////////////////
void CHFinalStandingsDlg::saveEventResult(CHEventResult * pEventResult)
{
	APP::out(TRN_CHANGE_EVENT_RESULT);
	APP::out(*pEventResult,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
	APP::out();
}
void CHFinalStandingsDlg::saveInscription(CHInscription * pInscription)
{
	APP::out(TRN_SET_INSCRIPTION);
	APP::out(*pInscription,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
	APP::out();
}
////////////////////////////////////////////////////////////////////////////////////
void CHFinalStandingsDlg::savePoolResult(CHPoolResult * pPoolResult)
{
	APP::out(TRN_CHANGE_POOLRES);
	APP::out(*pPoolResult,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
	APP::out();
}
void CHFinalStandingsDlg::saveMedallist(GMedallist * pMedallist)
{
	// Send pMedallist to database.
	APP::out(TRN_NEW_MEDALS);
	APP::out(*pMedallist,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
	APP::out();
}

void CHFinalStandingsDlg::destroyMedallist(GMedallist * pMedallist)
{
	APP::out(TRN_REMOVE_MEDALLIST);
	APP::out(*pMedallist,OP_DELETE,TO_VENUE|TO_DATABASE);
	APP::out();

	m_pMem->removeMedallist(*pMedallist);
}

////////////////////////////////////////////////////////////////////////////////////
void CHFinalStandingsDlg::generateMedallist(CHEventResult * pEventResult, int medal)
{
	GMedal * pMedal = m_pMem->findMedal(char(medal));
	if( !pMedal )
		return;

	GMedallist aMedallist(pEventResult->getEvent(),pEventResult->getRegister(),pMedal,"");
	GMedallist * pMedallist = m_pMem->setMedallist(aMedallist);
	if( !pMedallist )
		return;

	saveMedallist(pMedallist);
}
