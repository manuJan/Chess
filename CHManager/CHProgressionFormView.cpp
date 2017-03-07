/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHProgressionFormView.cpp
*   Description	:
*
*	Author		: CH Team
*	Date created: 15-Nov-2004
* 	Project		: CHManager
*	
* 	Modification history
*	By		: 
*	Date	:
*	Changes	: 
*
***************************************************************************************/

#include "stdafx.h"
#include "CHmanager.h"
#include "CHProgressionFormView.h"
#include "CHDefines.h"
#include "CHManualEventControl.h"
#include "CHTeamResults.h"
#include "CHTreatPhases.h"
#include "CHTreatPools.h"
#include "CHFinalStandingsDlg.h"
#include "CHRanking.h"


#include <sports\CH\Data\CHDiscipline.h>
#include <sports\CH\Data\CHMatch.h>
#include <sports\CH\Data\CHPoolResult.h>
#include <sports\CH\Data\CHStatisticDefines.h>
#include <sports\CH\Reports\CHRoundDraw.h>
#include <Sports/CH/Reports/CHReportDefines.h>

#include <SPORTS/CH/REPORTS/CHRC51G.h>
#include <SPORTS/CH/REPORTS/CHRC76A.h>
#include <SPORTS/CH/REPORTS/CHRC76B.h>
#include <SPORTS/CH/REPORTS/CHRC74.h>
#include <SPORTS/CH/REPORTS/CHRC75.h>

#include <GUI/FLAGS/flags.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static int orderPhasesByEvents(const GVectorElement** a, const GVectorElement** b)
{
	CHPhase * pPhaseEvA = (CHPhase *)(*a)->getElement();
	CHPhase * pPhaseEvB = (CHPhase *)(*b)->getElement();

	CHEvent *pEventA=(CHEvent*)pPhaseEvA->getEvent();
	CHEvent *pEventB=(CHEvent*)pPhaseEvB->getEvent();

	int order = pEventA->getOrderEvent()-pEventB->getOrderEvent();
	if(order)
		return order;

	order = pPhaseEvA->getOrder() - pPhaseEvB->getOrder();
	if(order)
		return order;

	return stricmp(pPhaseEvA->getKey(),pPhaseEvB->getKey());
}

static int orderEvents(const GVectorElement** a, const GVectorElement** b)
{
	CHEvent * pEvA = (CHEvent *)(*a)->getElement();
	CHEvent * pEvB = (CHEvent *)(*b)->getElement();

	return pEvA->getOrderEvent()-pEvB->getOrderEvent();
	return stricmp(pEvA->getKey(),pEvB->getKey());
}

static
int orderPoolResultByName(const GVectorElement** a, const GVectorElement** b)
{
	CHPoolResult * pA=((CHPoolResult *)(*a)->getElement());
	CHPoolResult * pB=((CHPoolResult *)(*b)->getElement());

	if (!pA->getRegister() && !pB->getRegister() )
		return strcmp(pA->getKey(),pB->getKey());

	if (!pA->getRegister())
		return -1;
	
	if (!pB->getRegister())
		return 1;

	int order = _wcsicoll(pA->getPrnLName(),pB->getPrnLName());
	return (order) ? order:pA->getRegCode()-pB->getRegCode();
}

extern CCHManagerApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CHProgressionFormView

IMPLEMENT_DYNCREATE(CHProgressionFormView, CFormView)

CHProgressionFormView::CHProgressionFormView()
:GTHProgressionFormView(2,true)
,lastMatchLocked("")
,posX(0)
,eventControlOp((CHMemoryDataBase*)mem())
{
	//{{AFX_DATA_INIT(CHProgressionFormView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CHProgressionFormView::~CHProgressionFormView()
{
}


BEGIN_MESSAGE_MAP(CHProgressionFormView, GTHProgressionFormView)
	//{{AFX_MSG_MAP(CHProgressionFormView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		ON_MESSAGE(UM_RBUTDOWN, onRButtonDown)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CHProgressionFormView::init() 
{
	// Esto pinta la informacion general de Progresiones
	GTHProgressionFormView::init(); 

	RWWString txt = ((CHDiscipline &)mem()->getDiscipline()).getSPoolDescription() + _T(" / ") +
					((CHDiscipline &)mem()->getDiscipline()).getSMatchDescription() + _T(" ID");


	w->changeRect        (LSTPOOLRES,CRect(185,145,995,314));
	w->changeRect        (LSTMATCHES,CRect(185,375,995,570));
	w->addGridColumn     (LSTMATCHES,"Result",JUST_CENTER,40);
	w->addGridColumn     (LSTMATCHES,"Round",JUST_CENTER,40);
	w->chgGridColumnJust (LSTMATCHES,3,JUST_CENTER);
	w->chgGridColumnTxt  (LSTMATCHES,0,txt);
	w->chgGridColumnTxt  (LSTMATCHES,1,"MN");
	w->chgGridColumnWidth(LSTMATCHES,1, 30);
	w->chgGridColumnWidth(LSTMATCHES,4,165);
	w->chgGridColumnWidth(LSTMATCHES,5,165);

		// Cambio tamaño de algunas columnas.
	w->chgGridColumnWidth(LSTMATCHES,0,90); // 110
	w->chgGridColumnWidth(LSTMATCHES,1,60); // 80
	w->chgGridColumnWidth(LSTMATCHES,3,70); // 75

	w->changeRect(BUTADDMATCH,CRect(855,583,925,605));
	w->changeRect(BUTDELMATCH,CRect(925,583,995,605));
	w->createButton(CH_BUT_CHANGE_TEAMS,CRect(700,583,825,605),"Change Home-Away"   ,IDBCK_BUT,IDCOL,IDFNT);
	w->createButton(CH_BUT_STANDINGS   ,CRect(700,120,825,142),"Final Standings" ,IDBCK_BUT,IDCOL,IDFNT);

	// Assign 
	w->addBitmapT(CH_BMP_DRAW, IDB_DRAW);
	w->createButton (CH_BUT_DRAW,CRect( 420, 120, 550, 142),"Assign Competitors",IDBCK_BUT,IDCOL,FONTMIN);
	w->changeBmp(CH_BUT_DRAW, CH_BMP_DRAW); // Pone el bitmap al boton
	w->hide(CH_BUT_DRAW);

	// But remove Draw
	w->addBitmapT(CH_BMP_REM, IDB_UNDO);
	w->createButton (CH_BUT_REM,CRect( 560, 120, 690, 142),"Remove Competitors",IDBCK_BUT,IDCOL,FONTMIN);
	w->changeBmp(CH_BUT_REM, CH_BMP_REM); // Pone el bitmap al boton
	w->hide(CH_BUT_REM);

	
	w->hide(CH_BUT_CHANGE_TEAMS);
	w->hide(CH_BUT_SUMMARY);
	w->hide(CH_BUT_STANDINGS);

	w->createButton(CH_BUT_LOG, CRect(265,120,285,142),"L.F",IDBCK,IDCOL,IDFNT);
	w->enable(CH_BUT_LOG, false);

	w->addFont           (IDFNTBG2,5,14,1,0,0,0,_T("Tahoma"));	

	// Menu de visualizacion de possibles resultados
	w->createMenu(MENU_RESULTS,70,22,IDBCK,IDCOL,IDFNTBG2,IDBCK2,IDCOL);

	w->addBitmapT(BMP_CHECKT			,IDB_CH_CHECK);

	// Menu de visualizacion de possibles colores
	w->createMenu(MENU_COLORS,70,22,IDBCK,IDCOL,IDFNTBG2,IDBCK2,IDCOL);

	
	// Menu de visualizacion de possibles incidencias
	w->createMenu(MENU_INCIDENCE,100,22,IDBCK,IDCOL,IDFNTBG2,IDBCK2,IDCOL);

	w->delGridColumn(LSTPOOLRES,10);	// Pos.
	w->delGridColumn(LSTPOOLRES,9);		// Rk. Sc
	w->delGridColumn(LSTPOOLRES,8);		// poolMatchSource
	w->delGridColumn(LSTPOOLRES,7);		// Phase Source
	w->delGridColumn(LSTPOOLRES,6);		// Lucky Loser
	w->delGridColumn(LSTPOOLRES,5);		// P.Rk
	
	w->addGridColumn(LSTPOOLRES,"Rk.Po",JUST_LEFT	,35);	// Rank Po
	w->addGridColumn(LSTPOOLRES,"Seed",JUST_LEFT	,35);	// Seed
	w->addGridColumn(LSTPOOLRES,"Rating",JUST_LEFT	,35);	// Rating
	w->addGridColumn(LSTPOOLRES,"Qual.",JUST_LEFT	,40);	// Points
	w->addGridColumn(LSTPOOLRES,"Played",JUST_LEFT	,40);	// Match Played
	w->addGridColumn(LSTPOOLRES,"Win",JUST_LEFT		,35);	// Match Win
	w->addGridColumn(LSTPOOLRES,"Drawn",JUST_LEFT	,35);	// Match Drawn
	w->addGridColumn(LSTPOOLRES,"Lost",JUST_LEFT	,35);	// Match Lost
	w->addGridColumn(LSTPOOLRES,"Points",JUST_LEFT	,40);	// Points
	w->addGridColumn(LSTPOOLRES,"Solkoff",JUST_LEFT	,35);	// Solkoff
	w->addGridColumn(LSTPOOLRES,"Sonne",JUST_LEFT	,35);	// SonneBerger
	w->addGridColumn(LSTPOOLRES,"Progre.",JUST_LEFT	,35);	// Progressive Points

	fillReports();

}

void CHProgressionFormView::fillReports()
{
	APP::addReport(1,0,RC51G_NAME,RC51G,CH_PROGRESSION_FORMVIEW,0,0);
	APP::addReport(2,0,RC74_NAME,RC74,CH_PROGRESSION_FORMVIEW,0,0);
	APP::addReport(3,0,RC75_NAME,RC75,CH_PROGRESSION_FORMVIEW,0,0);
	APP::addReport(4,0,RC76A_NAME,RC76A,CH_PROGRESSION_FORMVIEW,0,0);	
	APP::addReport(5,0,RC76B_NAME,RC76B,CH_PROGRESSION_FORMVIEW,0,0);
	
	//Eventos
	GSortedVector vEvents(CHMemoryDataBase::getColEvents(),orderEvents);
	CHEvent * pEvent=0;
	for(size_t i=0 ; i<vEvents.entries() ; i++)
	{
		pEvent=(CHEvent*)vEvents[i]->getElement();
		APP::addReport(50+i,1,pEvent->getLDescription(),RC51G,CH_PROGRESSION_FORMVIEW,LPARAM(pEvent),0);
		APP::addReport(100+i,4,pEvent->getLDescription(),RC76A,CH_PROGRESSION_FORMVIEW,LPARAM(pEvent),0);
		APP::addReport(150+i,5,pEvent->getLDescription(),RC76B,CH_PROGRESSION_FORMVIEW,LPARAM(pEvent),0);
	}

	//Phases
	GSortedVector vPhases(CHMemoryDataBase::getColPhases(),orderPhasesByEvents);
	CHPhase * pPhase=0;
	short nRoundC74=3000,nRoundC75=6000;
	char tmp[50];
	for(i=0 ; i<vPhases.entries() ; i++)
	{
		pPhase=(CHPhase*)vPhases[i]->getElement();
				
		RWCString phaseDesc=pPhase->getEventLDescription().toAscii() + " " + pPhase->getLDescription().toAscii();
		APP::addReport(RC74+i,2,phaseDesc,RC74,CH_PROGRESSION_FORMVIEW,LPARAM(pPhase),0);
		APP::addReport(RC75+i,3,phaseDesc,RC75,CH_PROGRESSION_FORMVIEW,LPARAM(pPhase),0);
		
		for(size_t j=0;short(j)<pPhase->getNumRounds();j++)
		{
			sprintf(tmp,"Round %d",j+1);
			APP::addReport(RC74+nRoundC74,RC74+i,tmp,RC74,CH_PROGRESSION_FORMVIEW,LPARAM(pPhase),LPARAM(j+1));
			APP::addReport(RC75+nRoundC75,RC75+i,tmp,RC75,CH_PROGRESSION_FORMVIEW,LPARAM(pPhase),LPARAM(j+1));
			nRoundC74++;
			nRoundC75++;
		}
		APP::addReport(RC74+nRoundC74,RC74+i,"All Rounds",RC74,CH_PROGRESSION_FORMVIEW,LPARAM(pPhase),LPARAM(ALL_ROUNDS));
		nRoundC74++;
	}
}
bool CHProgressionFormView::canInsertProgressMatch(GTHMatch * pMatch)
{
	if(	(((CHMatch *)pMatch)->getSubMatch()==0))
	{
		return true;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////
void CHProgressionFormView::onDblClick(UINT idGrid,int x,int y,LPARAM lParam)
{
	// Match Number
	if( idGrid == LSTMATCHES && x == 1 )
		return;

	// Result
	if( idGrid == LSTMATCHES && x == 6 )
	{
		CHMatch * pMatch = (CHMatch *)getMatchSel();
		if( !pMatch )
		{
			::msg("Warning!!","Please select a match",ICO_X,MSG_OK);
			return;
		}

		if( !pMatch->getMatchResultHome() || !pMatch->getMatchResultAway() )
		{
			::msg("Warning!!","There aren´t asignated teams",ICO_X,MSG_OK);
			return;
		}


		if( pMatch->getStatus() < CHMemoryDataBase::eSchedulled )
		{
			::msg("Warning!!","Match´s status is less than Schedulled",ICO_X,MSG_OK);
				return;
		}

		if( pMatch->getStatus() == CHMemoryDataBase::eFinished )
		{
			if( ::msg("Warning!!","Match's status is official, do you really want to continue?",ICO_W,MSG_YESNO) == RET_NO )
				return;
		}

		if (lockMatch(pMatch) )
		{

			if(pMatch->areTeams())
			{
				CHTeamResults teamResults(this,pMatch);
				if (teamResults.DoModal())
				{
					unLockMatch();
					w->redraw(LSTPOOLRES);
					w->redraw(LSTMATCHES);
				}
			}
			else
			{			
				CHManualEventControl * pResultDlg = new CHManualEventControl(this,pMatch);
				if( pResultDlg )
				{
					pResultDlg->DoModal();
					unLockMatch();
					delete pResultDlg;

					w->redraw(LSTPOOLRES);
					w->redraw(LSTMATCHES);
				}
				return;
			}
		}

		
	}
	
	// Pool Result
	if( idGrid == LSTPOOLRES && x > 3 )
	{
		CHPoolResult * pPoolResult = (CHPoolResult *)w->getSelectedLParam(idGrid);
		if(!pPoolResult)
			return;

		CHPool *pPool=(CHPool*)pPoolResult->getPool();
		/*if(pPool->getStatus()==CHMemoryDataBase::eFinished &&
			::msg("Status Pool==Official","Change Data??",ICO_Q,MSG_OKCANCEL)==RET_CANCEL)
			return;*/

		if(x==4 || x==5) // Rank o RankPo
		{
			CHPool * pPool=(CHPool *)pPoolResult->getPool();
			//if(pPool->getStatus() < CHMemoryDataBase::eRunning)
			//	return; //no dejo hacer cambios

			editRank(idGrid,pPoolResult,x,y);

		}
		if(x==6) // Seed
			editSeed(idGrid,pPoolResult,x,y);
		if(x==7) // Rating
			editRating(idGrid,pPoolResult,x,y);

		if(x==9 || x==10 || x==11 || x==12) // Matches Played, Win, Drawn, Lost
			editMatches(idGrid,pPoolResult,x,y);

		if(x==13 || x==14 || x==15 || x==16) // Points, Solkoff, SonneBerger, Progressive
			editPoints(idGrid,pPoolResult,x,y);
		
		w->redrawLine(LSTPOOLRES,y);
		return;
		
	}
	if( idGrid == LSTMATCHES && x == 3)
	{
		CHMatch * pMatch = (CHMatch *)getMatchSel();
		CHStatusDlg aStatusDlg(this,pMatch);
		aStatusDlg.DoModal();
		
		if(aStatusDlg.hasChanges())
		{
			// Si el Status es igual a StartList tengo que inicializar el partido
			if(aStatusDlg.getStartList() && pMatch->getStatus()==CHMemoryDataBase::eStartList)
				clearResults(pMatch);

			// Si el Status es igual a Protested tengo que desprogresar el partido
			if(pMatch->getStatus()==CHMemoryDataBase::eFinished ||
			   pMatch->getStatus()==CHMemoryDataBase::eProtested)
				eventControlOp.finishMatch(pMatch);
			
			w->redrawLine(LSTMATCHES,y);						
		}
		
		return;
	}

	GTHProgressionFormView::onDblClick(idGrid,x,y,lParam);

	// Result
	if( idGrid == LSTMATCHES && (x == 4 || x == 5))
	{
		CHMatch * pMatch = (CHMatch *)getMatchSel();
		if (pMatch->getStatus()!=CHMemoryDataBase::eFinished)
			eventControlOp.manageByes(pMatch);

		CHStatusManager aStManager;
		// Si tiene a los dos tios y esta en schedule lo paso a startlist
		if (getProgresion() && 
			pMatch->getStatus()==CHMemoryDataBase::eSchedulled && pMatch->isConfigured())
		{
			
			aStManager.run(*pMatch, CHMemoryDataBase::eStartList);
			aStManager.saveTeamSubMatchesStatus(pMatch,CHMemoryDataBase::eStartList);					
		}
		else if (getProgresion() && 
				 pMatch->getStatus()==CHMemoryDataBase::eStartList && !pMatch->isConfigured())
		{
			aStManager.run(*pMatch, CHMemoryDataBase::eSchedulled);
			aStManager.saveTeamSubMatchesStatus(pMatch,CHMemoryDataBase::eSchedulled);				
		}

		w->redrawLine(LSTMATCHES,y);
	}


}

////////////////////////////////////////////////////////////////////////////////////


BOOL CHProgressionFormView::onPaintGrid(UINT idGrid,GridItem *gi)
{
	if (idGrid==LSTMATCHES)
	{
		// For Repaint Matches
		paintMyListMatches(idGrid,gi);		
		return true;
	}
	if (idGrid==LSTPOOLRES && (gi->x>3))
	{
		// For Repaint Matches
		paintMyListPooles(idGrid,gi);		
		return true;
	}
	
	return GTHProgressionFormView::onPaintGrid(idGrid,gi);
}


void CHProgressionFormView::paintMyListMatches(UINT idGrid,GridItem *gi) 
{
	CHMatch *pMatch=(CHMatch *)	gi->lParam;
	if (!pMatch) return;

	if (!gi) 
		return;
	
	int seg_x=gi->x;
	if (gi->x==0)
		gi->x=9999;

	if (pMatch->areTeams() && (gi->x==4 || gi->x==5))
	{
		paintListMatchesTeam(gi);
		return;
	}

	CHMatchResult * pMatchResultHome = (CHMatchResult*)(pMatch->getCompetitorsVector()[0])->getElement();
	CHMatchResult * pMatchResultAway = (CHMatchResult*)(pMatch->getCompetitorsVector()[1])->getElement();

	/*if ( !( (CHProgression*)getProgresion())->checkMatchResult(pMatchResultHome,(CHPoolResult*)pMatchResultHome->getPoolResult(),false ) || 
		 !( (CHProgression*)getProgresion())->checkMatchResult(pMatchResultAway,(CHPoolResult*)pMatchResultAway->getPoolResult(),false ) )
	{
		w->paintGridSolid((gi->sel)?0xF0C0C0:RGB(221,221,221));
	}*/

	GTHProgressionFormView::onPaintGrid(idGrid,gi);
	
	gi->x=seg_x;

	CString match=((GTHDiscipline&)mem()->getDiscipline()).getSMatchDescription();

	char txt[100];

	switch (gi->x)
	{
		case 0:
			{
				if(!getPoolSel())//esta posicionado en la phase, no en la pool
				{
					if(getPhaseSel()->getIsPool())
						sprintf(txt,"%s / %s %d",pMatch->getPoolDescription(pMatch->getPhasePoolDescription()),match,pMatch->getIdParent());
					else
						sprintf(txt,"%d", pMatch->getIdParent());
				}
				else
					sprintf(txt,"%d", pMatch->getIdParent());


				w->paintGridText(gi->rc.Width()/2,0,txt,JUST_CENTER);
				break;
			}
			break;
		
		case 4:
		{
			// Home Competitor
			if (pMatchResultHome->getRegister())
			{
				sprintf(txt,"%s (%d)", pMatchResultHome->getIDCompetitor().toMultiByte(), ((CHMatchResult*)pMatchResultHome)->getSeed());
				w->paintGridText(30,0,txt,JUST_LEFT);
			}

			if(pMatchResultHome->getColor()==CHMatchResult::eWhite)
				 w->paintGridBmp (145,0,BMP_WHITE);
			else w->paintGridBmp(145,0,BMP_BLACK);
			break;
		}	
		case 5:
		{
			// Away Competitor
			
			if (pMatchResultAway->getRegister())
			{
				sprintf(txt,"%s (%d)", pMatchResultAway->getIDCompetitor().toMultiByte(), ((CHMatchResult*)pMatchResultAway)->getSeed());
				w->paintGridText(30,0,txt,JUST_LEFT);
			}

			if(pMatchResultAway->getColor()==CHMatchResult::eWhite)
				 w->paintGridBmp (145,0,BMP_WHITE);
			else w->paintGridBmp(145,0,BMP_BLACK);
			
			break;
		}	
		case 6:
			w->paintGridText(19, 5, pMatch->getResultAsString(),IDFNT_BOLD,COLOR_ROJO1,JUST_CENTER);
			
			break;
		case 7:
			{
				sprintf(txt,"%d", pMatch->getRound());
				w->paintGridText(20,0,txt,IDFNT_BOLD,IDCOL,JUST_CENTER);
			}
			break;
	}
}
void CHProgressionFormView::paintMyListPooles(UINT idGrid,GridItem *gi) 
{
	CHPoolResult *pPoolResult=(CHPoolResult *)	gi->lParam;
	if (!pPoolResult) return;

	if (!gi) 
		return;
	
	int seg_x=gi->x;
	if (gi->x==0)
		gi->x=9999;

	
	CString match=((GTHDiscipline&)mem()->getDiscipline()).getSMatchDescription();

	char txt[200];
	switch (gi->x)
	{
		case 4: // Rank 
		{
			// Rank Pool
			itoa(pPoolResult->getRank(),txt,10);
			w->paintGridText(gi->rc.Width()/2,0,pPoolResult->getRank()?txt:"",JUST_CENTER);
			break;
		}
		case 5:
		{
			// Rank Po Pool
			itoa(pPoolResult->getRankPo(),txt,10);
			w->paintGridText(gi->rc.Width()/2,0,pPoolResult->getRankPo()?txt:"",JUST_CENTER);
			break;
		}
		case 6: // Seed
		{
			itoa(pPoolResult->getInscriptionSeed(),txt,10);
			w->paintGridText(gi->rc.Width()/2,0,pPoolResult->getInscriptionSeed()?txt:"",JUST_CENTER);
			break;
		}
		case 7: // Rating
		{
			itoa(pPoolResult->getInscriptionRating(),txt,10);
			w->paintGridText(gi->rc.Width()/2,0,pPoolResult->getInscriptionRating()?txt:"",JUST_CENTER);
			break;
		}
		case 8 : // Qualitative
		 if(pPoolResult->isQualitative()) 
			w->paintGridText(gi->rc.Width()-1,0,_T(" (")+pPoolResult->getQualitativeSDescription()+_T(")"),IDFNT,COLOR_ROJO1,JUST_RIGHT);
		 break;
		
		case 9 : // Played
		 itoa(pPoolResult->getMPlayed(),txt,10);
		 w->paintGridText(gi->rc.Width()/2,0,pPoolResult->getMPlayed()?txt:"",JUST_CENTER);
		 break;
		case 10 : // Matches Win
		 itoa(pPoolResult->getMWon(),txt,10);
		 w->paintGridText(gi->rc.Width()/2,0,pPoolResult->getMWon()?txt:"",JUST_CENTER);
		 break;
		case 11 : // Matches Drawn
		 itoa(pPoolResult->getMDrawn(),txt,10);
		 w->paintGridText(gi->rc.Width()/2,0,pPoolResult->getMDrawn()?txt:"",JUST_CENTER);
		 break;
		case 12 : // Matches Lost
		 itoa(pPoolResult->getMLost(),txt,10);
		 w->paintGridText(gi->rc.Width()/2,0,pPoolResult->getMLost()?txt:"",JUST_CENTER);
		 break;
		case 13 : // Points
		 w->paintGridText(gi->rc.Width()/2,0,pPoolResult->getPointsFStr(),JUST_CENTER);
		 break;
		case 14 : // Solkoff Points
		 w->paintGridText(gi->rc.Width()/2,0,pPoolResult->getMSolkOffStr(),JUST_CENTER);
		 break;
		case 15 : // SonneBerger Points
		 w->paintGridText(gi->rc.Width()/2,0,pPoolResult->getMSonneBergerStr(),JUST_CENTER);
		 break;
		case 16 : // Progresive Points
		 w->paintGridText(gi->rc.Width()/2,0,pPoolResult->getMProgressiveScoreStr(),JUST_CENTER);
		 break;
	}
}

void CHProgressionFormView::paintListMatchesTeam(GridItem *gi)
{
	if (!gi) return;
	
	CHMatch *pMatch=(CHMatch *) gi->lParam;
	if (!pMatch) 
		return;

	if (!pMatch->areTeams()) 
		return;

	COLORREF color=GET_COLOR_DEFAULT_N3D;
	//si se ha seleccionado un pool result, pinto con otro color los matchs
	//en los que interviene ese pool result
	CHPoolResult *pPoolResult=(CHPoolResult *)getPoolResSel();
	bool clickPoolRes=false;
	GTHMatchResult * pMatchResult=0;
	GSortedVector vectorMatchResult=pMatch->getCompetitorsVector();
	if (pPoolResult)
	{
	for(size_t i=0;i<vectorMatchResult.entries();i++)
	{
		pMatchResult=(GTHMatchResult *)vectorMatchResult[i]->getElement();
		if (pMatchResult->getPoolResult() && 
			pPoolResult->getKey()==pMatchResult->getPoolResult()->getKey())
		{
			clickPoolRes=true;
			break;
		}
	}
	}
	if(clickPoolRes)
	{
		GTHMatchResult * pMatchResult=0;
		GSortedVector vectorMatchResult=pMatch->getCompetitorsVector();
		for(size_t j=0;j<vectorMatchResult.entries();j++)
		{
			pMatchResult=(GTHMatchResult *)vectorMatchResult[j]->getElement();
			if( pMatchResult->getPoolPosition()==pPoolResult->getOrder() &&
				pMatchResult->getPool() == pPoolResult->getPool() )
				color=RGB(200,200,200);
		}
	}

	gi->cdc->FillSolidRect(gi->rc,(gi->sel)?GET_COLOR_DEFAULT_HIGH:color);

	RWCString txt = "";
	// Text		
	switch (gi->x)
	{
	case 4:
		{
			// Home Competitor
			if (pMatch->areTeams())
			{
				if (!pMatch->getCompetitorsVector().entries())
					break;
				if ((pMatch->getCompetitorsVector()[0])->getElement())
				{
					CHMatchResult * pMatchResultHome = (CHMatchResult*)(pMatch->getCompetitorsVector()[0])->getElement();
					paintMyMatchResult(gi,pMatchResultHome);
					
					if(pMatchResultHome->getColor()==CHMatchResult::eWhite)
						w->paintGridBmp (145,0,BMP_WHITE);
					else w->paintGridBmp(145,0,BMP_BLACK);
					
				}
			}
			break;
		}	
	case 5:
		{
			// Away Competitor
			if (pMatch->areTeams() &&
				(pMatch->getCompetitorsVector()[1]))
			{
				if ((pMatch->getCompetitorsVector()[1])->getElement())
				{
					CHMatchResult * pMatchResultAway = (CHMatchResult*)(pMatch->getCompetitorsVector()[1])->getElement();
					paintMyMatchResult(gi,pMatchResultAway);					
					if(pMatchResultAway->getColor()==CHMatchResult::eWhite)
						w->paintGridBmp (145,0,BMP_WHITE);
					else w->paintGridBmp(145,0,BMP_BLACK);
				}
			}
			break;
		}	
	}
}

void CHProgressionFormView::paintMyMatchResult(GridItem *gi, GTHMatchResult *pMatchResult)
{
	if (pMatchResult->getRegister())
	{
		CBitmap aBitmap;
		getFlag(pMatchResult->getGroup(),ICO,&aBitmap);	
		w->paintGridUserBmp(4,2,&aBitmap,false);

		w->paintGridText(1,13,pMatchResult->getGroup(),IDFNT_MIN,gi->sel? GET_COLOR_DEFAULT_HITX : GET_COLOR_DEFAULT_ON,JUST_LEFT);
		w->paintGridText(30,0,getMyMatchResultDescription(pMatchResult),JUST_LEFT);
	}
	else 
		w->paintGridText(gi->rc.Width()/2,0,getMyMatchResultDescription(pMatchResult),JUST_CENTER);
}

RWCString CHProgressionFormView::getMyMatchResultDescription(GTHMatchResult *pMatchResult)
{
	RWCString txt="";
	char tmp[100];
	memset(tmp,0,sizeof(tmp));

	if (pMatchResult->getRegister())
	{
		txt = pMatchResult->getPrnSName().toMultiByte();
	}
	else
	{	
		if (pMatchResult->getBye())
			sprintf(tmp,"%s (BYE)",pMatchResult->getIDCompetitor());
		else if (pMatchResult->getPoolPosition())
		{
			sprintf(tmp,"%s (%d)", pMatchResult->getIDCompetitor().toMultiByte(), ((CHMatchResult*)pMatchResult)->getSeed());
		}
		
		txt=tmp;
	}
	return txt;	
}



void CHProgressionFormView::changeUserTreeSelection()
{
	CHEvent * pEvent = (CHEvent *) getEventSel();
	CHPhase * pPhase = (CHPhase *) getPhaseSel();
	
	w->enable(CH_BUT_LOG,false);

	if( pEvent )
		w->show(CH_BUT_STANDINGS);
	else
		w->hide(CH_BUT_STANDINGS);

	if( pPhase &&
		pPhase ->getIsPool())
	{
		w->show(CH_BUT_DRAW);
		w->show(CH_BUT_SUMMARY);		
		w->hide(CH_BUT_STANDINGS);
		w->hide(CH_BUT_CHANGE_TEAMS);
		w->show(CH_BUT_REM);
	}
	else if (pEvent)
	{
		w->hide(CH_BUT_SUMMARY);
		w->show(CH_BUT_STANDINGS);	
		w->hide(CH_BUT_CHANGE_TEAMS);
		w->hide(CH_BUT_DRAW);
		w->hide(CH_BUT_REM);
	}
	else
	{
		w->hide(CH_BUT_SUMMARY);
		w->hide(CH_BUT_STANDINGS);
		w->hide(CH_BUT_CHANGE_TEAMS);
		w->hide(CH_BUT_DRAW);
		w->hide(CH_BUT_REM);
	}

	if (pPhase &&
		pPhase->getStatus()==CHMemoryDataBase::eFinished)
	{
		w->hide(CH_BUT_DRAW);
		w->hide(CH_BUT_REM);
		//w->hide();
	}

	if (pPhase)
		w->enable(CH_BUT_LOG,true);
}

void CHProgressionFormView::setTreeDescription()
{
	if( pTree )
	{
		pTree->setEventLDescription(true);
		pTree->setPhaseLDescription(true);
	}
}

void CHProgressionFormView::onClick(UINT idCtrl,LPARAM lParam)
{
	switch( idCtrl )
	{
	case MENUPROGRESS:
		{
			if (getPhaseSel()) // insert pool/match
			{
				if (lParam==2)
				{
					GTHPool * pPool=0;
					if(getPhaseSel()->getIsPool())//insertar una pool sacando el dialogo 
						pPool = insertPool(true);
					else//insertar un match en una phase que no es pool
						pPool = insertPool(false);
					if (pPool)
					{
						pTree->Invalidate();
						pTree->fillTree(pPool);
					}
					return;
				}
			}
			else if (getEventSel()) // insert phase
			{
				if (lParam==1)
				{
					GTHPhase* pPhase = insertPhase();
					if (pPhase)
					{
						pTree->Invalidate();
						pTree->fillTree(pPhase);
					}
					return;
				}
			}			
			break;
		}
	case CH_BUT_CHANGE_TEAMS:
		{
			onClickButChangeTeams();
			break;			
		}
	case CH_BUT_SUMMARY :
		{
			onClickButSummary();	
			break;
		}
	case LSTMATCHES:
		{
			CHMatch* pMatch = (CHMatch*)lParam;
			if (pMatch &&
				pMatch->getStatus() <= CHMemoryDataBase::eStartList)
				w->show(CH_BUT_CHANGE_TEAMS);			
			else
				w->hide(CH_BUT_CHANGE_TEAMS);
			
			break;
		}
	case CH_BUT_DRAW:
		{
			onClickButAssign();
			return;
		}
	case BUTDRAW:
		{
			onClickButDraw();
			return;
		}
	case CH_BUT_REM:
		{
			onClickButRemove();
			return;
		}
	case CH_BUT_LOG:
		{
			if (getMatchSel())
			{
				short speed = 1;
				//((CHProgression*)getProgresion())->createLogFile(getMatchSel(),speed);			
			}
			else if (getPoolSel())
			{
				short speed = 1;
				//((CHProgression*)getProgresion())->createLogFile(getPoolSel(),speed);			
			}
			else if (getPhaseSel())
			{	
				short speed = 1;
				//((CHProgression*)getProgresion())->createLogFile(getPhaseSel(),speed);			
			}						
			break;
		}
	case MENU_RESULTS: // Menu de tipos de resultados de un partido
		 onResultsMenu(lParam);
		 break;
	case MENU_COLORS: // Menu de eleccíon de color de fichas
		 onColorsMenu(lParam);
		 break;
	case MENU_INCIDENCE:
		 onQualitativeMenu((GQualitative*)lParam);
		 break;
	case CH_BUT_STANDINGS :
		{
			CHEvent * pEvent = (CHEvent *) getEventSel();
			if( !pEvent )
				return;

			if( pEvent->getStatus() < CHMemoryDataBase::eFinished )
				::msg("Provisional Ranking","The Event isn't Finish",ICO_I,MSG_OK);

			CHFinalStandingsDlg * pFinalStandingsDlg = new CHFinalStandingsDlg(this,pEvent);
			if( pFinalStandingsDlg )
			{
				pFinalStandingsDlg->DoModal();
				delete pFinalStandingsDlg;
			}
		}
		break;
		
	}

	GTHProgressionFormView::onClick(idCtrl,lParam);
}

GTHPhase* CHProgressionFormView::insertPhase()
{
	if (!getEventSel())
		return 0;

	assignPhaseInfoDlg();

	CHTreatPhases dlgPhases((CHMemoryDataBase *)mem(), getEventSel(), getProgresion(),this);
	dlgPhases.SetPhaseInfo(getPhaseInfoDlg());
	dlgPhases.DoModal();	

	return dlgPhases.GetGeneratedPhase();
}

GTHPool* CHProgressionFormView::insertPool(RWBoolean isRealPool/*=true*/)
{
	if (!getPhaseSel() ||!getEventSel())
		return 0;

	CHTreatPools dlgPools((CHMemoryDataBase *)mem(), getPhaseSel(), getProgresion(),isRealPool);
	dlgPools.DoModal();	
	// incremento el numPools de la Phase
	if (dlgPools.GetGeneratedPool())
	{
		getPhaseSel()->setPoolsNumber(short(getPhaseSel()->getPoolsNumber()+1));
		savePhase();
		fillPhase();
	}
	
	return dlgPools.GetGeneratedPool();
}

LRESULT CHProgressionFormView::onRButtonDown(WPARAM wParam, LPARAM lParam)
{
		
	short x=short(lParam);

	switch(wParam)
	{
		
		case LSTMATCHES:
		{
			posX=x;

			CHMatch *pMatch=(CHMatch*)w->getSelectedData(LSTMATCHES);
			if(!pMatch)
				return false;
		

			switch (x) // Columnas del grid
			{ 
				
				case 4:// Home
				case 5:// Away
				{
					CHMatchResult *pMatchResult=0;
					if(x==4) // Home
						 pMatchResult=(CHMatchResult*)pMatch->getMatchResultHome();
					else pMatchResult=(CHMatchResult*)pMatch->getMatchResultAway();
					onCreateMenuColors(lParam,pMatchResult);	
					
				}
				break;
				case 6: // Result 
				{
					CHEvent *pEvent=(CHEvent*)pMatch->getEvent();	
					if(!pEvent->isTeam())
						onCreateMenuResults(lParam,pMatch);	
				}
				break;
			
			}
			
			break;	
		}
		case LSTPOOLRES:
		{
			CHPoolResult *pPoolResult=(CHPoolResult*)w->getSelectedData(LSTPOOLRES);
			if(!pPoolResult)
				return false;
		

			switch (x) // Columnas del grid
			{ 
				
				case 8:// Qualitative
				{
					CHMatchResult *pMatchResult=0;
										
					RWBoolean incidence=false;

					w->delMenuItems(MENU_INCIDENCE);
					short i=1;
					RWSetIterator it(CHMemoryDataBase::getColQualitatives());
					GQualitative * pQualitative=0;
					while((pQualitative=(GQualitative*)it())!=0)
					{
						if(pPoolResult->getQualitative()==pQualitative)
						{	w->addMenuItem(MENU_INCIDENCE,SUBMENU_INCIDENCE1+i,0,pQualitative->getLDescription(),LPARAM(pQualitative),BMP_CHECKT);	
							incidence=true;
						}
						else w->addMenuItem(MENU_INCIDENCE,SUBMENU_INCIDENCE1+i,0,pQualitative->getLDescription(),LPARAM(pQualitative));	
						i++;
					}
												
					w->showMenu(MENU_INCIDENCE);
						
					
				}
				break;
							
			}
			
			break;	
		}
	
	}
	return TRUE;
}
void CHProgressionFormView::onCreateMenuResults(LPARAM lParam, CHMatch *pMatch)
{
 	if(!pMatch)
		return;
	
	RWCString results=NULLRWSTRING;
	w->delMenuItems(MENU_RESULTS);
	

	if (pMatch->getMatchResultHome() && pMatch->getMatchResultAway())
	{
		if(pMatch->getStatus()>=CHMemoryDataBase::eUnofficial)
			// Finish Match
		w->addMenuItem(MENU_RESULTS,SUB_MENU_FINISH,0,"Finish Match",LPARAM(1));	
		// 1:0
		w->addMenuItem(MENU_RESULTS,SUB_MENU_1_0,0,"1 : 0",LPARAM(2));	
		// 1/2:1/2
		w->addMenuItem(MENU_RESULTS,SUB_MENU_1_2_1_2,0,"1/2 : 1/2",LPARAM(3));	
		// 0:1
		w->addMenuItem(MENU_RESULTS,SUB_MENU_0_1,0,"0 : 1",LPARAM(4));	
		// Empty
		w->addMenuItem(MENU_RESULTS,SUB_MENU_0_0,0,"0 : 0",LPARAM(5));	
		// 1F : 0F
		w->addMenuItem(MENU_RESULTS,SUB_MENU_1F_0F,0,"1F : 0F",LPARAM(6));	
		// 0F : 1F
		w->addMenuItem(MENU_RESULTS,SUB_MENU_0F_1F,0,"0F : 1F",LPARAM(7));	
		// 0F : 0F
		w->addMenuItem(MENU_RESULTS,SUB_MENU_0F_0F,0,"0F : 0F",LPARAM(8));	

		w->showMenu(MENU_RESULTS);
				
	}
		
	UNREFERENCED_PARAMETER(lParam);
}
void CHProgressionFormView::onResultsMenu(LPARAM lparam)
{
	CHMatch *pMatch=(CHMatch*)w->getSelectedData(LSTMATCHES);
	if(!pMatch)
		return;
		
	if(lparam>0)
	{	
		if(lparam==1)
			eventControlOp.finishMatch(pMatch,true);
		else
			eventControlOp.putScore(getEventFromMenu(BU_ONE_ZERO+(lparam-2)),pMatch);
		
		w->redrawLine(LSTMATCHES,w->getSelectedLine(LSTMATCHES));
				
	}
	
}
void CHProgressionFormView::onColorsMenu(LPARAM lparam)
{
	CHMatch *pMatch=(CHMatch*)w->getSelectedData(LSTMATCHES);
	if(!pMatch)
		return;
		
	if(lparam>0)
	{	
		CHMatchResult *pMatchResult=0,*pMatchResultVersus=0;
		if(posX==4)
			 pMatchResult=(CHMatchResult*)pMatch->getMatchResultHome();
		else pMatchResult=(CHMatchResult*)pMatch->getMatchResultAway();
		
		pMatchResultVersus=pMatchResult->getMatchResultVersus();
		// Si se cambia de color
		if(pMatchResult->getColor()!=(lparam-1))
		{
			pMatchResult->setColor(short(lparam-1));
			// White
			if(lparam==1)
				pMatchResultVersus->setColor(short(lparam)); // Le pongo negras
			// Negro
			if(lparam==2)
				pMatchResultVersus->setColor(short(lparam-2)); // Le pongo blancas
		}
		
		theApp.queueOut(pMatchResult);
		theApp.queueOut(pMatchResultVersus);
		theApp.out(TRN_CHANGE_MATCHRES);
		
		w->redrawLine(LSTMATCHES,w->getSelectedLine(LSTMATCHES));
				
	}
}
void CHProgressionFormView::onCreateMenuColors(LPARAM lParam, CHMatchResult *pMatchResult)
{
 	if(!pMatchResult)
		return;
	
	RWCString colorts=NULLRWSTRING;
	w->delMenuItems(MENU_COLORS);
	

	if (pMatchResult->getMatchStatus()!=CHMemoryDataBase::eFinished)
	{
		// White
		if(pMatchResult->getColor()==CHMatchResult::eWhite)
			 w->addMenuItem(MENU_COLORS,SUBMENU_WHITE,0,"White",LPARAM(1),BMP_CHECKT);
		else w->addMenuItem(MENU_COLORS,SUBMENU_WHITE,0,"White",LPARAM(1));
		// Black
		if(pMatchResult->getColor()==CHMatchResult::eBlack)
			 w->addMenuItem(MENU_COLORS,SUBMENU_BLACK,0,"Black",LPARAM(2),BMP_CHECKT);
		else w->addMenuItem(MENU_COLORS,SUBMENU_BLACK,0,"Black",LPARAM(2));
		
		w->showMenu(MENU_COLORS);
				
	}
		
	UNREFERENCED_PARAMETER(lParam);
}

void CHProgressionFormView::onClickButDraw()
{
	CHPhase* pPhase = (CHPhase*)getPhaseSel();
	if (!pPhase)
		return;

	if (pPhase && 
	   (pPhase->getStatus() > CHMemoryDataBase::eSchedulled))
	{
		::msg("Error","The status of the phase must be less than schedule",ICO_X,MSG_OK);
		return;
	}

	if (pPhase->hasCompetitors())
	{
		::msg("Error","This event has some competitors, remove all before",ICO_X,MSG_OK);
		return;
	}

	((CHProgression*)getProgresion())->setInitialProgression(pPhase,GTHProgression::eRandom);

	
	RWBoolean validDraw = false;
	for (size_t i=0;i<pPhase->getPoolsVector().entries();i++)
	{
		CHPool* pPool = (CHPool*)pPhase->getPoolsVector()[i]->getElement();
	
		RWSet colMatchResults;
		CHRoundDraw aRoundDraw(colMatchResults,pPool,1);
		validDraw = aRoundDraw.doDraw(CHRoundDraw::eMonrad);
		if (validDraw)
		{
			RWSetIterator it(colMatchResults);
			CHMatchResult *pMatchResult=0;
			APP::out(TRN_CHANGE_MATCHRES);
			while((pMatchResult=(CHMatchResult *)it())!=0)
			{
				getProgresion()->onChangeInscription(pMatchResult->getInscription(),pMatchResult);
				APP::out(*pMatchResult,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
			}
			APP::out();
		}
	}

	// Manage Byes
	if (validDraw)
	{
		for (i=0;i<pPhase->getPoolsVector().entries();i++)
		{
			CHPool* pPool = (CHPool*)pPhase->getPoolsVector()[i]->getElement();
			
			for (size_t j=0;j<pPool->getMatchsVector().entries();j++)
			{
				CHMatch* pMatch = (CHMatch*)pPool->getMatchsVector()[j]->getElement();
				eventControlOp.manageByes(pMatch);					
			}
		}
	}
	
	//((CHProgression*)getProgresion())->setInitialProgression(getPhaseSel(),GTHProgression::eBySeed);
	fillPoolResult();
	fillMatches();	
}

void CHProgressionFormView::onClickButAssign()
{
	CHPhase *pPhase = (CHPhase *) getPhaseSel();
	if (!pPhase)
		return;

	if (pPhase->getStatus()>=CHMemoryDataBase::eStartList || pPhase->hasCompetitors())
	{
		::msg("Error","This event has some competitors, remove all before",ICO_X,MSG_OK);
		return;
	}
	
	getProgresion()->setInitialProgression(pPhase,GTHProgression::eRandom);
				
	fillPoolResult();
	fillMatches();
	fillMatchResult();
}

void CHProgressionFormView::onClickButRemove()
{
	CHPhase *pPhase = (CHPhase *) getPhaseSel();
	if (!pPhase)
		return;

	if (pPhase->getStatus()>=CHMemoryDataBase::eSchedulled )
	{
		::msg("Error","This event has a status that dont allow this operation",ICO_X,MSG_OK);
		return;
	}

	if (!pPhase->hasCompetitors())
	{
		::msg("Error","This event hasn't any competitor to remove",ICO_X,MSG_OK);
		return;	
	}

	if (::msg("Warning","ARE YOU SURE??",ICO_Q,MSG_OKCANCEL)==RET_CANCEL)
		return;

	((CHProgression*)getProgresion())->removeCompetitors(pPhase);

	fillPoolResult();
	fillMatches();
	fillMatchResult();
}

void CHProgressionFormView::onClickButChangeTeams()
{
	CHMatch * pMatch = (CHMatch *)getMatchSel();
	if( !pMatch )
	{
		::msg("Warning!!","Please select a match",ICO_X,MSG_OK);
		return;
	}

	if( pMatch->getStatus() > CHMemoryDataBase::eStartList )
	{
		wchar_t msg[200];
		swprintf(msg,_T("This match can´t be changed, its status is %s"),pMatch->getStatusLDescription());
		::msg(_T("Warning!!"),msg,ICO_X,MSG_OK);
		return;
	}

	CHMatchResult * pHome = pMatch->getMatchResultHome();
	CHMatchResult * pAway = pMatch->getMatchResultAway();
	if( !pHome || !pAway )
	{
		::msg("Warning!!","There aren´t teams asignated",ICO_X,MSG_OK);
		return;
	}

	if ((CHProgression*)getProgresion())
		((CHProgression*)getProgresion())->changeTeamsOrder(pHome,pAway);
	
	w->redraw(LSTMATCHES);

	//fillReports();
}

void CHProgressionFormView::onClickButSummary()
{
	CHPhase * pPhase = (CHPhase *) getPhaseSel();
	if (!pPhase->getIsPool())
		return;
	
/*	CHSummaryDlg * pSummaryDlg = new CHSummaryDlg(this,pPhase,true);
	if( pSummaryDlg )
	{
		pSummaryDlg->DoModal();
		delete pSummaryDlg;
	}*/
}

/////////////////////////////////////////////////////////////////////////////
// Overrided functions. 
/////////////////////////////////////////////////////////////////////////////
bool CHProgressionFormView::canDeletePhase(GTHPhase* pPhase)
{
	if (!pPhase)				return false;
	if (!checkDBThread())		return false;

	if (pPhase->getStatus()>=GMemoryDataBase::eStartList)
	{
		::msg("DELETING PHASE","PHASE STATUS >= STARTLIST\nIt's impossible to delete PHASE",ICO_X,MSG_OK);
		return false;
	}
	if (::msg("DELETING PHASE","ARE YOU SURE??",ICO_Q,MSG_OKCANCEL)==RET_CANCEL)
		return false;

	return true;
}

//A esta funcion nos llama cuando se va a borrar una pool real o cuando se va a borrar
// una pool de una fase que no tiene pooles.
bool CHProgressionFormView::canDeletePool(GTHPool* pPool)
{ 
	if (!pPool)					return false;
	if (!checkDBThread())		return false;

	if (pPool->getStatus()>=GMemoryDataBase::eStartList)
	{
		if (pPool->getPhase()->getIsPool())	// Quieren borrar una pool real.		
			::msg("DELETING POOL","POOL STATUS >= STARTLIST\nIt's impossible to delete POOL",ICO_X,MSG_OK);
		else 
			::msg("DELETING MATCH","MATCH STATUS >= STARTLIST\nIt's impossible to delete MATCH",ICO_X,MSG_OK);
		return false;
	}

	if (pPool->getPhase()->getIsPool())
	{
		if (::msg("DELETING POOL","ARE YOU SURE??",ICO_Q,MSG_OKCANCEL)==RET_CANCEL)
			return false;
	}
	else if (::msg("DELETING MATCH","ARE YOU SURE??",ICO_Q,MSG_OKCANCEL)==RET_CANCEL)
			return false;


	return true;
}

bool CHProgressionFormView::canDeleteMatch(GTHMatch* pMatch)
{ 
	if (!pMatch)			return false;
	if (!checkDBThread())		return false;

	if (pMatch->getStatus()>=GMemoryDataBase::eStartList)
	{
		::msg("DELETING MATCH","MATCH STATUS >= STARTLIST\nIt's impossible to delete MATCH",ICO_X,MSG_OK);
		return false;
	}

	GTHPool* pPool=pMatch->getPool();
	if(!pPool)		return false;

	if (::msg("DELETING MATCH","ARE YOU SURE??",ICO_Q,MSG_OKCANCEL)==RET_CANCEL)
		return false;
	
	return true;
}

bool CHProgressionFormView::canChangePoolResult(GTHPoolResult* pPoolResult, int row)
{
	UNREFERENCED_PARAMETER(row);

	CHPool* pPool = (CHPool*)pPoolResult->getPool();
	CHMatch* pMatch=0;
	CHMatchResult* pMatchResult=0;
	for (size_t i=0;i<pPool->getMatchsVector().entries();i++)
	{
		pMatch = (CHMatch*)pPool->getMatchsVector()[i]->getElement();
		for (size_t j=0;j<pMatch->getCompetitorsVector().entries();j++)
		{
			pMatchResult=(CHMatchResult*)pMatch->getCompetitorsVector()[j]->getElement();
			if ( pMatchResult->getPoolPosition()==pPoolResult->getOrder() &&
				 pMatchResult->getRegister()==pPoolResult->getRegister())
			{
				if (pMatch->getStatus()>=CHMemoryDataBase::eStartList)
				{
					GStatus* pStatus = CHMemoryDataBase::findStatus(pMatch->getStatus());
					CString msg=_T("");
					msg.Format(_T("This competitor is in a %s which status is %s"),((CHDiscipline&)mem()->getDiscipline()).getSMatchDescription(),
																					pStatus->getSDescription());
					::msg(_T("Warning!!"), msg,ICO_X,MSG_OK);
					return false;
				}
			}
		}
	}	
	return true;
}

bool CHProgressionFormView::checkDBThread()
{
	size_t elements = ((CCHManagerApp*)AfxGetApp())->getDBThreadRemainingChanges();

	if(elements)
	{
		::msg("WARNING!!","PLEASE, WAIT!!\nWE ARE SENDING DATA TO DATABASE",ICO_X,MSG_OK);
		return false;
	}

	return true;

}

void CHProgressionFormView::onReportRequest   (CReportItem    *pItem)
{
	if(!pItem)
		return;
	// Result Code + Aditional Parameters
	switch ( pItem->getNReport() )
	{
		case RC51G:
		case RC76A:
		case RC76B:
		{
			CHEvent *pEvent = (CHEvent *)pItem->getLParam1();
			if( pEvent )
				pItem->setResultCode(((CHMemoryDataBase*)mem())->getRSC(pEvent));
		}
		case RC74:
		{
			CHPhase *pPhase = (CHPhase *)pItem->getLParam1();
			if( pPhase )
				pItem->setResultCode(((CHMemoryDataBase*)mem())->getRSC(pPhase));
			
			short round = (short)pItem->getLParam2();

			char tmp[10];
			if(round && round!=ALL_ROUNDS)
				pItem->setParameters(itoa(round,tmp,10));
		}
		break;
		case RC75:
		{
			CHPhase *pPhase = (CHPhase *)pItem->getLParam1();
			if( pPhase )
				pItem->setResultCode(((CHMemoryDataBase*)mem())->getRSC(pPhase));

			short round = (short)pItem->getLParam2();

			char tmp[10];
			if(round && round!=ALL_ROUNDS)
				pItem->setParameters(itoa(round,tmp,10));
		}		
		break;
	}
}
	
bool CHProgressionFormView::onReportGeneration(CReportManager *pReportMngr,CReportConfig *pReportCfg,CReportItem *pItem)
{
	bool IsOk = false;

	if (!pReportCfg || !pItem || !pReportMngr)
		return false;

	switch ( pItem->getNReport() )
	{
		case RC51G:
		case RC76A:
		case RC76B:
		{
			if( !pItem->getLParam1() )
			{
				AfxMessageBox(RWWString("Please select a Event",RWWString::multiByte));
				return false;
			}

			pReportCfg->setOrientation(CReportManager::landScape);
			if (pItem->getNReport()==RC51G)
			{
				CHRC51G aCHRC51G(*pReportMngr,*pReportCfg,(CHEvent*)pItem->getLParam1());
				return aCHRC51G.Run();
			}

			if (pItem->getNReport()==RC76A)
			{
				CHRC76A aCHRC76A(*pReportMngr,*pReportCfg,(CHEvent*)pItem->getLParam1());
				return aCHRC76A.Run();
			}

			if (pItem->getNReport()==RC76B)
			{
				CHRC76B aCHRC76B(*pReportMngr,*pReportCfg,(CHEvent*)pItem->getLParam1());
				return aCHRC76B.Run();
			}
			break;
		}
		case RC74:
		{
			if( !pItem->getLParam1() )
			{
				AfxMessageBox(RWWString("Please select a Event-Phase",RWWString::multiByte));
				return false;
			}
			if( !pItem->getLParam2() )
			{
				AfxMessageBox(RWWString("Please select a Round or All Rounds",RWWString::multiByte));
				return false;
			}

			if (pItem->getNReport()==RC74)
			{
				CHRC74 aCHRC74(*pReportMngr,*pReportCfg,(CHPhase*)pItem->getLParam1(),short(pItem->getLParam2()));
				return aCHRC74.Run();
			}
			break;
		}
		case RC75:
		{
			if( !pItem->getLParam1() )
			{
				AfxMessageBox(RWWString("Please select a Event-Phase",RWWString::multiByte));
				return false;
			}
			if( !pItem->getLParam2() )
			{
				AfxMessageBox(RWWString("Please select a Round",RWWString::multiByte));
				return false;
			}

			if (pItem->getNReport()==RC75)
			{
				CHRC75 aCHRC75(*pReportMngr,*pReportCfg,(CHPhase*)pItem->getLParam1(),short(pItem->getLParam2()));
				return aCHRC75.Run();
			}
			break;
		}
	}
	return IsOk;
}

void CHProgressionFormView::deleteMatch(GTHMatch * pDelMatch)
{
	if (pDelMatch)
	{
		pDelMatch = mem()->removeMatch(*pDelMatch);
		if (pDelMatch)
		{
			int line = w->findGridLParam(LSTMATCHES,LPARAM(pDelMatch));	
			w->gridDeleteItem(LSTMATCHES,line);

			APP::out(TRN_REMOVE_MATCH);
			APP::out(*pDelMatch,OP_DELETE,TO_VENUE|TO_DATABASE);
			APP::out();

			// LA POOL Tiene un partido menos
			
			if(getPoolSel())
				getPoolSel()->setNumMatches(short(getPoolSel()->getNumMatches()-1));
			savePool();
			fillPool();
		}
		fillMatchResult();
		// FALTA QUE JUSTE ME HAGA UN SETMATCHSEL() para ponerlo a cero. pMatchSel=0;
		if(((CHMatch *)pDelMatch)->areTeamIndividual())
		{
			((CHProgression*)getProgresion())->deleteConfrontationMatches((CHMatch*)pDelMatch);
		}
	}
}
bool CHProgressionFormView::lockMatch(CHMatch *pMatch)
{
	if (!pMatch)
		return false;

	RWCString lockStringMatch;
	char match[10];
	
	lockStringMatch += pMatch->getEventCode();
	lockStringMatch += "-" + pMatch->getPhaseCode();
	lockStringMatch += "-" + pMatch->getPoolCode();
	sprintf(match,"%d",pMatch->getCode());
	lockStringMatch += match;

	unLockMatch();

	if(!APP::lock(lockStringMatch))
		return false;
	else
	{
		lastMatchLocked = lockStringMatch;
		return true;
	}

	return true;
}
void CHProgressionFormView::unLockMatch()
{
	APP::unlock(lastMatchLocked);
}

void CHProgressionFormView::assignPhaseInfoDlg()
{
	phaseInfo.phase=true;
	phaseInfo.isPool=true;
	phaseInfo.poolType=false;
	phaseInfo.order=true;
	phaseInfo.pools=true;
	phaseInfo.numPools="";
	phaseInfo.compPool=true;
	phaseInfo.numCompPool="";
	phaseInfo.matches=true;
	phaseInfo.numMatches="";
	phaseInfo.rounds=true;
	phaseInfo.numRounds="7";
	phaseInfo.compMatch=true;
	phaseInfo.numCompMatch="2";
	phaseInfo.splits=false;
	phaseInfo.numSplits="";
}

short CHProgressionFormView::getEventFromMenu(short menu)
{
	switch (menu)
	{
		case BU_ONE_ZERO:	
			return EV_WHITE_WINNER;
		case BU_HALF_HALF:
			return EV_DRAW;
		case BU_ZERO_ONE:
			return EV_BLACK_WINNER;		
		case BU_ONE_ZERO_F:
			return EV_WHITE_WINNER_F;
		case BU_ZERO_ONE_F:
			return EV_BLACK_WINNER_F;
		case BU_ZERO_ZERO_F:
			return EV_DRAW_F;
		case BU_EMPTY:
			return EV_EMPTY;
	}
	return 0;
}
void CHProgressionFormView::editRank(int idGrid,CHPoolResult * pPoolResult,int column,int line)
{
	if(!pPoolResult)
		return;

	char oldTxt[10];
	RWCString newTxt;
	sprintf(oldTxt, "%d",((column==5)?pPoolResult->getRankPo():pPoolResult->getRank()));
	newTxt = w->editGridCell(idGrid, column, line, oldTxt, "##");
	if( newTxt != oldTxt )
	{
		if(column==5)
			pPoolResult->setRankPo (short(atoi(newTxt)));
		else
			pPoolResult->setRank   (short(atoi(newTxt)));

		//w->gridSort(idGrid,orderGridPoolResults);
		w->selectLParam(idGrid,LPARAM(pPoolResult));

		//DataBase
		theApp.queueOut(pPoolResult);
		theApp.out(TRN_CHANGE_POOLRESULT_CH);

		
		//Progression
		CHPool  * pPool  = (CHPool *)  pPoolResult->getPool();
		CHPhase * pPhase = (CHPhase *) pPoolResult->getPhase();
		CHEvent * pEvent = (CHEvent *) pPoolResult->getEvent();

		CHProgression aProg(mem());
		if( pPool->getStatus()  == CHMemoryDataBase::eFinished )
			aProg.setProgression(pPool);
		if( pPhase->getStatus() == CHMemoryDataBase::eFinished )
			aProg.setProgression(pPhase);
		
		/*CHEventResult *pEventResult=(CHEventResult*)CHMemoryDataBase::findEventResult(pPoolResult->getInscription());
		if(pEventResult)
		{
			pEventResult->setRank(pPoolResult->getRank());
			pEventResult->setRankPo(pPoolResult->getRankPo());
			theApp.queueOut(pEventResult);
			theApp.out(TRN_CHANGE_EVENT_RESULT);
		}*/

		if (pEvent->getStatus()==CHMemoryDataBase::eFinished)
		{
			CHRanking aRanking;
			aRanking.calculateMedals(0,pEvent);
		}		
	}
}
void CHProgressionFormView::editSeed(int idGrid,CHPoolResult * pPoolResult,int column,int line)
{
	if(!pPoolResult)
		return;

	char oldTxt[10];
	RWCString newTxt;
	
	CHInscription *pInscription=(CHInscription*)pPoolResult->getInscription();
	if(!pInscription)
		return;

	sprintf(oldTxt, "%d",pPoolResult->getInscriptionSeed());
	newTxt = w->editGridCell(idGrid, column, line, oldTxt, "#####");
	if( newTxt != oldTxt )
	{
		pInscription->setSeed(short(atoi(newTxt)));
		
		//DataBase
		theApp.queueOut(pInscription);
		theApp.out(TRN_SET_INSCRIPTION);
		
	}
}
void CHProgressionFormView::editRating(int idGrid,CHPoolResult * pPoolResult,int column,int line)
{
	if(!pPoolResult)
		return;

	char oldTxt[10];
	RWCString newTxt;
	
	CHInscription *pInscription=(CHInscription*)pPoolResult->getInscription();
	if(!pInscription)
		return;

	sprintf(oldTxt, "%d",pPoolResult->getInscriptionRating());
	newTxt = w->editGridCell(idGrid, column, line, oldTxt, "#####");
	if( newTxt != oldTxt )
	{
		pInscription->setRating(short(atoi(newTxt)));
		
		//DataBase
		theApp.queueOut(pInscription);
		theApp.out(TRN_SET_INSCRIPTION);
		
	}
}

void CHProgressionFormView::onQualitativeMenu(GQualitative *pQualitative)
{
	if(pQualitative)
	{
		
		CHPoolResult *pPoolResult=(CHPoolResult*)w->getSelectedData(LSTPOOLRES);
		if(!pPoolResult)
			return;
		
		pPoolResult->setQualitative(pQualitative->getCode());

		theApp.queueOut(pPoolResult);
		theApp.out(TRN_CHANGE_POOLRESULT_CH);

		CHEventResult *pEventResult=(CHEventResult*)CHMemoryDataBase::findEventResult(pPoolResult->getInscription());
		if(pEventResult)
		{
			pEventResult->setQualitative(pQualitative->getCode());
			theApp.queueOut(pEventResult);
			theApp.out(TRN_CHANGE_EVENT_RESULT);
		}

		w->redraw(LSTPOOLRES);
		
	}
}
void CHProgressionFormView::editMatches(int idGrid,CHPoolResult * pPoolResult,int column,int line)
{
	if(!pPoolResult)
		return;

	char oldTxt[20];
	RWCString newTxt;
	
	if(column==9)
		sprintf(oldTxt, "%d",pPoolResult->getMPlayed());
	else if(column==10)
		sprintf(oldTxt, "%d",pPoolResult->getMWon());
	else if(column==11)
		sprintf(oldTxt, "%d",pPoolResult->getMDrawn());
	else if(column==12)
		sprintf(oldTxt, "%d",pPoolResult->getMLost());
	
	
	newTxt = w->editGridCell(idGrid, column, line, oldTxt, "#####");
	if( newTxt != oldTxt )
	{
		if(column==9)
			pPoolResult->setMPlayed(short(atoi(newTxt)));
		else if(column==10)
			pPoolResult->setMWon(short(atoi(newTxt)));
		else if(column==11)
			pPoolResult->setMDrawn(short(atoi(newTxt)));
		else if(column==12)
			pPoolResult->setMLost(short(atoi(newTxt)));
		
		//DataBase
		theApp.queueOut(pPoolResult);
		theApp.out(TRN_CHANGE_POOLRESULT_CH);
		
	}
}

void CHProgressionFormView::editPoints(int idGrid,CHPoolResult * pPoolResult,int column,int line)
{
	if(!pPoolResult)
		return;

	char oldTxt[20];
	RWCString newTxt;
	
	if(column==13)
		newTxt = w->editGridCell(idGrid, column, line, pPoolResult->getPointsFStr());
	else if(column==14)
		newTxt = w->editGridCell(idGrid, column, line, pPoolResult->getMSolkOffStr());
	else if(column==15)
		newTxt = w->editGridCell(idGrid, column, line, pPoolResult->getMSonneBergerStr());
	else if(column==16)
		newTxt = w->editGridCell(idGrid, column, line, pPoolResult->getMProgressiveScoreStr());

	if( newTxt != oldTxt )
	{
		if(column==13)
			pPoolResult->setPointsF(float(atof(newTxt)));
		else if(column==14)
			pPoolResult->setMSolkoff(float(atof(newTxt)));
		else if(column==15)
			pPoolResult->setMSonneBerger(float(atof(newTxt)));
		else if(column==16)
			pPoolResult->setMProgressiveScore(float(atof(newTxt)));
		
		//DataBase
		theApp.queueOut(pPoolResult);
		theApp.out(TRN_CHANGE_POOLRESULT_CH);
	}
}

void CHProgressionFormView::clearResults(CHMatch *pMatch)
{
	if(eventControlOp.clearResults(pMatch))
		w->redraw(LSTMATCHES);
}

void CHProgressionFormView::setDataOnMatchResult(GTHMatchResult * pMatchResult,GTHPoolResult * pPoolResult)
{
	((CHProgression*)getProgresion())->checkMatchResult((CHMatchResult*)pMatchResult,(CHPoolResult*)pPoolResult, true);

	GTHProgressionFormView::setDataOnMatchResult(pMatchResult,pPoolResult);

	bool save = false;
	CHMatch *pMat = (CHMatch *)pMatchResult->getMatch();
	if (pMat->areTeams() && pMatchResult->getInscription())
	{
		APP::out(TRN_CHANGE_MATCHRES);
		GSortedVector vMatches=pMat->getSubMatches();
		for(size_t i=0;i<vMatches.entries();i++)
		{
			CHMatch *pSubMat=(CHMatch*)vMatches[i]->getElement();
			if(pSubMat)
			{
				CHMatchResult *pMatRes = (CHMatchResult *)pSubMat->getCompetitorsVector()[pMatchResult->getPosition()-1]->getElement();
				
				pMatRes->setPoolPosition(pPoolResult?pPoolResult->getOrder():0);
				APP::out(*pMatRes,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
				save = true;
			}
		}
		if(save)
			APP::out();
	}
	else if (pMat->areTeams() && !pMatchResult->getInscription())
	{
		GSortedVector vMatches=pMat->getSubMatches();
		for(size_t i=0;i<vMatches.entries();i++)
		{
			CHMatch *pSubMat=(CHMatch*)vMatches[i]->getElement();
			if(pSubMat)
			{
				CHMatchResult *pMatRes = (CHMatchResult *)pSubMat->getCompetitorsVector()[pMatchResult->getPosition()-1]->getElement();
				pMatRes->setBye(pMatchResult->getBye());
				GTHProgressionFormView::setDataOnMatchResult(pMatRes,pPoolResult);
				eventControlOp.manageByes(pSubMat);				
			}
		}
	}	
}

LRESULT CHProgressionFormView::onCursorOverGrid(WPARAM wParam, LPARAM lParam)
{
	if (wParam==LSTMATCHES)
	{
		int row = HIWORD(lParam);
		int col = LOWORD(lParam);

		CHMatch* pMatch = (CHMatch*)w->getGridLParam(LSTMATCHES,row);
		if (pMatch)
		{
			CHMatchResult* pMatchResult=0;
			if (col==4 && (pMatch->getCompetitorsVector()[0]))
				pMatchResult=(CHMatchResult*)(pMatch->getCompetitorsVector()[0])->getElement();
			
			if (col==5 && (pMatch->getCompetitorsVector()[1]))
				pMatchResult=(CHMatchResult*)(pMatch->getCompetitorsVector()[1])->getElement();

			if (pMatchResult &&
				pMatchResult->getRegister())
			{
				w->setToolTip(LSTMATCHES,"");
				w->setToolTip(LSTMATCHES,pMatchResult->getPreviousMatchesAsString(pMatch));
			}
			else
			{
				w->setToolTip(LSTMATCHES,"");
			}
		}
		else
		{
			w->setToolTip(LSTMATCHES,"");
		}
	}
	
	return GTHProgressionFormView::onCursorOverGrid(wParam,lParam);
}

void CHProgressionFormView::fillComboCompetitor(int idGrid, GTHPool * pPool)
{
	CHMatch* pMatch = (CHMatch*)getMatchSel();
	if (pMatch)
	{
		w->delAllItems (idGrid);
	
		w->addItem(idGrid,0," NONE",0,0);
		w->addItem(idGrid,-1," BYE",0,1);

		CompareFunction compare = pPool->getPoolResultsVector().getCompare();
		pPool->getPoolResultsVector().sort(orderPoolResultByName);

		for(size_t i=0 ; i<pPool->getPoolResultsVector().entries() ; i++)
		{
			// ADD ITEMS TO COMBO
			CHPoolResult * pPoolResult = (CHPoolResult *)pPool->getPoolResultsVector()[i]->getElement();
			if (pPoolResult && !pPoolResult->isPlayingRound(pMatch,pMatch->getRound()))
			{
				if (pPoolResult->getRegister())
					w->addItem(idGrid,-1,getInscriptionDescription(pPoolResult->getInscription()),0,(LPARAM)pPoolResult);
				else
				{
					CString position = _T("");
					position.Format(_T("%d"),pPoolResult->getOrder());
					w->addItem(idGrid,-1,position,0,(LPARAM)pPoolResult);
				}
			}
		}

		pPool->getPoolResultsVector().sort(compare);
	}
}