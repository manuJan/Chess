// CHPgnMatchesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "chmanager.h"
#include "chdefines.h"
#include "CHPgnMatchesDlg.h"

#include <Sports\CH\Reports\CHPgnMatch.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHPgnMatchesDlg dialog


CHPgnMatchesDlg::CHPgnMatchesDlg(GSortedVector &_vMatchesInPlay, GSortedVector &_vPgnMatches, CWnd* pParent /*=NULL*/ )
	: CDialog(CHPgnMatchesDlg::IDD, pParent)
	,vMatchesInPlay(&_vMatchesInPlay)
	,vPgnMatches(&_vPgnMatches)
	,eventControlOp((CHMemoryDataBase*)mem())
{
	//{{AFX_DATA_INIT(CHPgnMatchesDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CHPgnMatchesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHPgnMatchesDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHPgnMatchesDlg, CDialog)
	//{{AFX_MSG_MAP(CHPgnMatchesDlg)
	ON_MESSAGE(UM_PAINTGRID, onPaintGrid)
	ON_MESSAGE(UM_DRAG,onGridDrag)
	ON_MESSAGE(UM_DROP,onGridDrop)
	ON_MESSAGE(UM_CLICK, onClick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHPgnMatchesDlg message handlers

BOOL CHPgnMatchesDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	w = new CGraphicWnd(this);
	INITW(w);

	w->createGrid(CH_GRD_PGNMATCHES,CRect(15,15,565,340),BORDER_DOWN,17,IDBCK_GRID,IDCOL,IDFNT);
	w->addGridColumn(CH_GRD_PGNMATCHES,"Pgn Game",JUST_LEFT,420);
	w->addGridColumn(CH_GRD_PGNMATCHES,"Real Game",JUST_LEFT,130);
	w->dragDropRegister  (CH_GRD_PGNMATCHES,"PgnMatches");
	w->dragDropAvailable (CH_GRD_PGNMATCHES,TRUE,TRUE);

	w->createGrid(CH_GRD_MATCHES,CRect(575,15,865,340),BORDER_DOWN,17,IDBCK_GRID,IDCOL,IDFNT);
	w->addGridColumn(CH_GRD_MATCHES,"Game",JUST_LEFT,290);
	w->dragDropRegister  (CH_GRD_MATCHES,"PgnMatches");
	w->dragDropAvailable (CH_GRD_MATCHES,TRUE,TRUE);


	w->createButton(CH_BUT_OK		,CRect(355,350,430,380),"O K",IDBCK_BUT,IDCOL,IDFNT_BOLD);
	w->createButton(CH_BUT_CANCEL	,CRect(460,350,535,380),"C a n c e l",IDBCK_BUT,IDCOL,IDFNT_BOLD);



	fillMatchesGrid();
	fillPgnMatchesGrid();
	
	return TRUE;  	              
}

BOOL CHPgnMatchesDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	if (w)
		delete w;

	return CDialog::DestroyWindow();
}


void CHPgnMatchesDlg::fillMatchesGrid()
{
	w->gridDeleteAllItems(CH_GRD_MATCHES);

	for (size_t i=0;i<vMatchesInPlay->entries();i++)
	{
		CHMatch* pMatch = (CHMatch*) (*vMatchesInPlay)[i]->getElement();
		w->addGridLine(CH_GRD_MATCHES,LPARAM(pMatch),"");
	}
}

void CHPgnMatchesDlg::fillPgnMatchesGrid()
{
	w->gridDeleteAllItems(CH_GRD_PGNMATCHES);

	for (size_t i=0;i<vPgnMatches->entries();i++)
	{
		CHPgnMatch* pPgnMatch = (CHPgnMatch*) (*vPgnMatches)[i]->getElement();
		w->addGridLine(CH_GRD_PGNMATCHES,LPARAM(pPgnMatch),"");
	}
}

BOOL CHPgnMatchesDlg::onPaintGrid(UINT idGrid,GridItem *gi)
{
	if (idGrid==CH_GRD_PGNMATCHES)
	{
		paintListPgnMatches(gi);
		return TRUE;
	}

	if (idGrid==CH_GRD_MATCHES)
	{
		paintListMatches(gi);		
		return TRUE;
	}

	return FALSE;
}

void CHPgnMatchesDlg::paintListMatches(GridItem *gi)
{
	if (!gi) return;
	
	CHMatch *pMatch=(CHMatch *) gi->lParam;
	if (!pMatch) 
		return;

	COLORREF color=RGB(250,250,240);

	gi->cdc->SetTextColor(COLOR_DEFAULT_ON);

	if (gi->sel)	
		gi->cdc->FillSolidRect(gi->rc,GET_COLOR_DEFAULT_HIGH);
	else
	{
		if(gi->y%2)
			 gi->cdc->FillSolidRect(gi->rc,RGB(255,255,255));
		else gi->cdc->FillSolidRect(gi->rc,RGB(243,243,243));
	}

	switch (gi->x)
	{
		case 0:
		{
			// Event - Round - White / Black
			RWCString match= pMatch->getEventLDescription().toMultiByte();
			match+=" - ";
			match+=pMatch->getRoundAsString(false,false);
			match+=" - ";
			match+=" G.";
			match+=pMatch->getMatchNumberAsString();
			match+=" / ";

			if (pMatch->getWhite() &&
				pMatch->getWhite()->getRegister())
				match+=pMatch->getWhite()->getRegister()->getPrnSName().toMultiByte();
			match+=" Vs. ";

			if (pMatch->getBlack() &&
				pMatch->getBlack()->getRegister())
				match+=pMatch->getBlack()->getRegister()->getPrnSName().toMultiByte();

			eventControlOp.paintShadow(gi->cdc,gi->rc.left+2,gi->rc.top,match,RGB(250,0,0),0,IDFNT,w,COLOR_NEGRO); 
			break;
		}
	}
}

void CHPgnMatchesDlg::paintListPgnMatches(GridItem *gi)
{
	if (!gi) return;
	
	CHPgnMatch *pPgnMatch=(CHPgnMatch *) gi->lParam;
	if (!pPgnMatch) 
		return;

	CHMatch* pMatch = pPgnMatch->getMatch();

	COLORREF color=RGB(250,250,240);

	gi->cdc->SetTextColor(COLOR_DEFAULT_ON);

	if (gi->sel)	
		if (pMatch)
			gi->cdc->FillSolidRect(gi->rc,RGB(0,225,0));
		else
			gi->cdc->FillSolidRect(gi->rc,GET_COLOR_DEFAULT_HIGH);
	else
	{
		if (pMatch)
			gi->cdc->FillSolidRect(gi->rc,RGB(0,255,0));
		else
		{
			if(gi->y%2)
				gi->cdc->FillSolidRect(gi->rc,RGB(255,255,255));
			else gi->cdc->FillSolidRect(gi->rc,RGB(243,243,243));
		}
	}

	switch (gi->x)
	{
		case 0:
		{
			RWCString match=pPgnMatch->getEventName();
			match+=" - ";
			match+=pPgnMatch->getRound();
			match+=" / ";
			match+=pPgnMatch->getWhite();
			match+=" Vs. ";
			match+=pPgnMatch->getBlack();
			match+=" ";
			match+=pPgnMatch->getResult();
			eventControlOp.paintShadow(gi->cdc,gi->rc.left+2,gi->rc.top,match,RGB(0,0,255),0,IDFNT,w,COLOR_NEGRO); 
			break;
		}
		case 1:
		{
			if (pMatch)
			{
				RWCString match= pMatch->getEventLDescription().toMultiByte();
				match+=" - ";
				match+=pMatch->getRoundAsString(false,false);
				match+=" - ";
				match+=" G.";
				match+=pMatch->getMatchNumberAsString();
				eventControlOp.paintShadow(gi->cdc,gi->rc.left+2,gi->rc.top,match,RGB(0,0,255),0,IDFNT,w,COLOR_NEGRO); 
			}
			break;
		}
	}
}

BOOL CHPgnMatchesDlg::onGridDrag(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

BOOL CHPgnMatchesDlg::onGridDrop(WPARAM wParam, LPARAM lParam)
{
	if (wParam==UINT(CH_GRD_PGNMATCHES) ||
		wParam==UINT(CH_GRD_MATCHES)	)
	{
		DragDropItem *ddi = (DragDropItem *)lParam;

		// Matches a Pgn Matches

		if (ddi->idSource == CH_GRD_MATCHES &&
			ddi->idTarget == CH_GRD_PGNMATCHES)
		{
			CHMatch* pMatch = (CHMatch*)ddi->lParam;
			CHPgnMatch* pPgnMatch = (CHPgnMatch*)ddi->lParamTarget;
			
			if (pPgnMatch && pMatch)
				pPgnMatch->setMatch(pMatch);
		}

		// Pgn Matches a Matches
		if (ddi->idTarget == CH_GRD_MATCHES &&
			ddi->idSource == CH_GRD_PGNMATCHES)
		{
			CHPgnMatch* pPgnMatch = (CHPgnMatch*)ddi->lParam;
			CHMatch* pMatch = (CHMatch*)ddi->lParamTarget;			
		
			if (pPgnMatch && pPgnMatch->getMatch())
				pPgnMatch->setMatch(0);
		}

		w->redraw(CH_GRD_MATCHES);
		w->redraw(CH_GRD_PGNMATCHES);
	}

	return TRUE;
}

void CHPgnMatchesDlg::onClick(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
		case CH_BUT_OK:
			OnOK();
			break;
		case CH_BUT_CANCEL:
			OnCancel();
			break;
	}

}