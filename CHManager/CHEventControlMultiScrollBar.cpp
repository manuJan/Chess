/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHEventControlMultiScrollBar.cpp
*	Description	:
*
*	Author		:Javier Juste 
*	Date created:  
* 	Project		:
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdafx.h"
#include "CHManager.h"
#include "CHEventControlMultiScrollBar.h"
#include "CHMsgDefines.h"
#include "CHDefines.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHEventControlMultiScrollBar

CHEventControlMultiScrollBar::CHEventControlMultiScrollBar(int _entries,CRect _rect, CWnd* pWnd)
:position(0)
,entries(_entries)
{
	Create(WS_VISIBLE|WS_CHILD|SBS_VERT, _rect,pWnd,CH_SCROLL_BAR);
	SetScrollPos(0);
	SetScrollRange(0,_entries);
}

CHEventControlMultiScrollBar::~CHEventControlMultiScrollBar()
{
}


BEGIN_MESSAGE_MAP(CHEventControlMultiScrollBar, CScrollBar)
	//{{AFX_MSG_MAP(CHEventControlMultiScrollBar)
	ON_WM_VSCROLL_REFLECT()
	ON_WM_VSCROLL()
	ON_MESSAGE(UM_ECT_VSCROLL_TOPOSITION,onVScrollToPosition)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHEventControlMultiScrollBar message handlers

void CHEventControlMultiScrollBar::VScroll(UINT nSBCode, UINT nPos) 
{
	// TODO: Add your message handler code here
	int oldPos = GetScrollPos();
	int newPos = 0;
	int pos = GetScrollPos();
			
	int max,min;
	bool change=false;
	GetScrollRange(&min,&max);
	switch (nSBCode)
	{
		case SB_LINEDOWN:
		{
			if (pos<max)
				SetScrollPos(pos+1);
			change=true;
			break;
		}
		case SB_LINEUP:
		{
			if (pos>min)
				SetScrollPos(pos-1);
			change=true;
			break;
		}

		case SB_PAGEDOWN:  
		{
			if (pos+MAX_MULTI_EC<=max)			
				SetScrollPos(pos+MAX_MULTI_EC);
			else
				SetScrollPos(max);
			change=true;
			break;
		}
		case SB_BOTTOM:
		{
			SetScrollPos(max);
			change=true;
			break;
		}
		case SB_TOP:
		{
			SetScrollPos(min);
			change=true;
			break;
		}
		case SB_PAGEUP:
		{
			if (pos-MAX_MULTI_EC>=min)			
				SetScrollPos(pos-MAX_MULTI_EC);
			else
				SetScrollPos(min);
			change=true;
			break;
		}
		case SB_THUMBPOSITION:
		{
			SetScrollPos(nPos);
			change=true;
			break;
		}
		case SB_THUMBTRACK:
		{
			SetScrollPos(nPos);
			change=true;
			break;
		}
	}	

	newPos = GetScrollPos()-oldPos;

	if (oldPos==GetScrollPos()+newPos)
		return;

	if (change)
		SendMessage( UM_ECT_VSCROLL_TOPOSITION, GetDlgCtrlID(), (LPARAM)newPos );
}

void CHEventControlMultiScrollBar::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default

	SetScrollPos(nPos);

	CScrollBar::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CHEventControlMultiScrollBar::setPosition(int pos)
// change the position of the scroll bar
{
	position=pos;
}

void CHEventControlMultiScrollBar::setEntries(int _entries)
// change the position of the scroll bar
{
	entries=_entries;
}

int CHEventControlMultiScrollBar::getPosition()
// getting the position of the vertical scroll bar
{
	return position;
}

int CHEventControlMultiScrollBar::getEntries()
// getting the position of the vertical scroll bar
{
	return entries;
}

LRESULT CHEventControlMultiScrollBar::onVScrollToPosition(WPARAM wParam,LPARAM lParam)
// updates all the form views and the scroll to position
{
	int position = (int)lParam + getPosition();

	int min=0,max=0;
	
	GetScrollRange(&min,&max);
	if (position<=max && position>=min)
	{
		setPosition(position);
		SetScrollPos(position);
		GetParent()->GetParent()->SendMessage(UM_ECT_SHOW_MATCHES);
	}

	return 0;
	UNREFERENCED_PARAMETER(wParam);
}

