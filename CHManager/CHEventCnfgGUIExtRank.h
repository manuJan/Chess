/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHEventCnfgGUIExtRank.h
*	Description	:
*
*	Author		:Chess Team
*	Date created:15-12-2005
* 	Project		:CH Manager
*	
***************************************************************************************/

#if !defined(AFX_CHEVENTCNFGGUIEXTRANK_H__3EEC4DE4_A828_4D2B_96AE_4F018A70388D__INCLUDED_)
#define AFX_CHEVENTCNFGGUIEXTRANK_H__3EEC4DE4_A828_4D2B_96AE_4F018A70388D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHRankOrder :public GData
{
public:
	CHRankOrder(short pos,short type);
	virtual ~CHRankOrder();

	virtual CPack& pack(CPack& aPack);
	virtual CPack& unpack(CPack& aPack);
	virtual void setKey();
	virtual RWBoolean uSQL(RWDBConnection& pConnect,RWBoolean remove=false);
public:
	short order;
	short rankType;
};

/////////////////////////////////////////////////////////////////////////////
// CHEventCnfgGUIExtRank window

class CHEventCnfgGUIExtRank : public CWnd
{
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHEventCnfgGUIExtRank)
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CHEventCnfgGUIExtRank)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CHEventCnfgGUIExtRank(CWnd * pParent,CGraphicWnd * _w, int x1,int y1,int x2,int y2,CHEvent *pEvent);
	virtual ~CHEventCnfgGUIExtRank();

	void	init			(int x1,int y1,int x2,int y2);
	BOOL	onPaintGrid		(UINT idGrid,GridItem * gi);
	void	onDblClick		(UINT idGrid,int x,int y,LPARAM lParam);
	void	onClick			(UINT idGrid,int x,int y,LPARAM lParam);

protected:
	LRESULT onSelectEvent	(WPARAM wParam, LPARAM lParam);	//UM_SELECT_EVENT
	

private:
	CHMemoryDataBase *	mem					();
	CCHManagerApp    *  getApp				();
	void				fillGridRank		();
	void				paintListRank		(GridItem *gi);
	RWCString			getRankDescription	(short rankType);
	void				editRankOrder		(UINT idGrid,int x,int y,CHRankOrder * pRankOrder);
	void				setOrderRankInEvent	();
	void				fillComboEvents		();
	void				copyOrderRank		();

private:
	CGraphicWnd				*w;
	CWnd					*m_pParent;
	CHEvent					*m_pEvent;

	RWSet					colRanks;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHEVENTCNFGGUIEXTRANK_H__3EEC4DE4_A828_4D2B_96AE_4F018A70388D__INCLUDED_)
