/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHEventCnfgGUIExtRating.cpp
*	Description	:
*
*	Author		:Chess Team
*	Date created:27-01-2006
* 	Project		:CH Manager
*	
***************************************************************************************/

#include "stdafx.h"
#include "CHmanager.h"
#include "CHEventCnfgGUIExtRating.h"
#include "CHDefines.h"
#include <Sports\CH\Data\CHRatingDif.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static
int fnOrderRatingDifs(const void *lParam1, const void *lParam2, LPARAM null)
{  	
	CHRatingDif *p1= (CHRatingDif *) lParam1;
	CHRatingDif *p2= (CHRatingDif *) lParam2;
	
	int order = p1->getCode() -  p2->getCode();
	if (order)
		return order;

	return strcmp(p1->getKey(), p2->getKey());
	
	UNREFERENCED_PARAMETER(null);
}

/////////////////////////////////////////////////////////////////////////////
// Constructor
/////////////////////////////////////////////////////////////////////////////
CHEventCnfgGUIExtRating::CHEventCnfgGUIExtRating(CWnd * pParent,CGraphicWnd * _w, int x1,int y1,int x2,int y2)
:CWnd()
,w(_w)
,m_pParent(pParent)
,m_pRatingDif(0)
{
	Create(NULL,NULL,WS_VISIBLE,CRect(0,0,1,1),pParent,0);
	init(x1,y1,x2,y2);
}

CHEventCnfgGUIExtRating::~CHEventCnfgGUIExtRating()
{
	w->destroyControl(LBL_RATING_DIF);
	w->destroyControl(LBL_LINE_RAT);
	w->destroyControl(LSTRATINGS);
	
}

CHMemoryDataBase * CHEventCnfgGUIExtRating::mem()
{ 
	return (CHMemoryDataBase *) ((CCHManagerApp*)AfxGetApp())->memG(); 
}

BEGIN_MESSAGE_MAP(CHEventCnfgGUIExtRating, CWnd)
	//{{AFX_MSG_MAP(CHEventCnfgGUIExtRating)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CHEventCnfgGUIExtRating::init(int x1,int y1,int x2,int y2)
{
	w->createLabel  (LBL_RATING_DIF,CRect(x1,y1+15, x1+540,y1+25),"Rating expectancies vs differences",BORDER_NONE,JUST_LEFT,IDBCK,IDCOL,IDFNT_BOLD);
	w->createLabel  (LBL_LINE_RAT,CRect(x1,y1+27,x1+540,y1+30),"",BORDER_NONE,JUST_LEFT,IDBCK_BOX);
	w->createGrid   (LSTRATINGS,CRect(x1,y1+30,x1+540,y2+140),BORDER_DOWN,20,IDBCK_GRID,IDCOL,IDFNT);
	w->gridLineColor(LSTRATINGS,GET_COLOR_DEFAULT_LINE,GET_COLOR_DEFAULT_LINE);
	w->addGridColumn(LSTRATINGS,"Code",				JUST_CENTER ,40 );
	w->addGridColumn(LSTRATINGS,"Probability",	JUST_CENTER	,110);
	w->addGridColumn(LSTRATINGS,"Difference",	JUST_CENTER ,80);
		
	fillGridRatings();
	w->redraw(LSTRATINGS,false);

}	

void CHEventCnfgGUIExtRating::fillGridRatings()
{
	w->gridDeleteAllItems(LSTRATINGS);
	
	RWSet& colRatingDifs=CHMemoryDataBase::getColRatingDifs();
	RWSetIterator it( colRatingDifs );
	CHRatingDif* pRatingDif=0;
	
	while( (pRatingDif=(CHRatingDif*)it())!=0 )
	{
		if(pRatingDif->getCode()<=100)
			w->addGridLine(LSTRATINGS,LPARAM(pRatingDif),"");
	}
		
	
	w->gridSort(LSTRATINGS,fnOrderRatingDifs);
}

BOOL CHEventCnfgGUIExtRating::onPaintGrid(UINT idGrid,GridItem * gi)
{
	switch(idGrid)
	{
		case LSTRATINGS:
			paintListRatingDifs(gi);
		break;
				
	}
	return TRUE;
}

void CHEventCnfgGUIExtRating::paintListRatingDifs(GridItem *gi)
{
	char tmp[50]={0};
			
	CHRatingDif *pRatingDif = (CHRatingDif *) gi->lParam;
	if (!pRatingDif) return; 
	switch (gi->x)
	{
		case 0://  Code
			{
				sprintf(tmp,"%d",pRatingDif->getCode());
				w->paintGridText(gi->rc.Width()/2,0,tmp,JUST_CENTER);		
				break;
			}
		case 1: // probability
			{
				w->paintGridText(gi->rc.Width()/2,0,pRatingDif->getProbabilityCodeStr(),JUST_CENTER);		
				break;
			}
		case 2: // Difference
			{
				sprintf(tmp,"%d",pRatingDif->getDifference());
				w->paintGridText(gi->rc.Width()/2,0,tmp,JUST_CENTER);
				break;
			}
				
		default:
				break;
	}
}

void CHEventCnfgGUIExtRating::onClick(UINT idGrid,int x,int y,LPARAM lParam)
{
	UNREFERENCED_PARAMETER(idGrid);
	UNREFERENCED_PARAMETER(x);
	UNREFERENCED_PARAMETER(y);
	UNREFERENCED_PARAMETER(lParam);
}

void CHEventCnfgGUIExtRating::onLButtonDown(UINT idGrid,int x,int y,LPARAM lParam)
{
	switch(idGrid)
	{
		case LSTRATINGS:
		{
			m_pRatingDif = (CHRatingDif *) lParam;
						
			break;
		}
	}
	
	UNREFERENCED_PARAMETER(x);
	UNREFERENCED_PARAMETER(y);
}

void CHEventCnfgGUIExtRating::onDblClick(UINT idGrid,int x,int y,LPARAM lParam)
{
	switch(idGrid)
	{
		case LSTRATINGS:
		{
			CHRatingDif *pRatingDif = (CHRatingDif *) lParam;
			
			switch (x)
			{
				case 2: // Difference
					changeDifference(idGrid,x,y,pRatingDif);
					break;
			}
			w->redraw(idGrid);
			break;
		}
		default:
			break;
	}
	
}

void CHEventCnfgGUIExtRating::changeDifference(UINT idGrid,int x,int y,CHRatingDif *pRatingDif)
{
	char tmp[10]={0};
	RWCString sOldDif = itoa(pRatingDif->getDifference(),tmp,10);
	RWCString format="####";

	if(atoi(sOldDif)<0)
		format="-####";
	RWCString sNewDif=w->editGridCell(idGrid,x,y,sOldDif,format);
	if (sOldDif!= sNewDif)
	{
		pRatingDif->setDifference(short(atoi(sNewDif)));
		saveRatingDif(pRatingDif);
		
	}
		
}

void CHEventCnfgGUIExtRating::saveRatingDif(CHRatingDif *pRatingDif)
{
	APP::out(TRN_CHANGE_RATING_DIF);
	APP::out(*pRatingDif,OP_INSERTORUPDATE,TO_VENUE|TO_DATABASE);
	APP::out();		
}
