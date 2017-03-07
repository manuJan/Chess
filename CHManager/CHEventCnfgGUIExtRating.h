/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHEventCnfgGUIExtRating.h
*	Description	:
*
*	Author		:Chess Team
*	Date created:27-01-2006
* 	Project		:CH Manager
*	
***************************************************************************************/

#if !defined(AFX_CHEventCnfgGUIExtRating_H__A82C6ECC_7ED9_47B4_A415_2F15B60FBB2F__INCLUDED_)
#define AFX_CHEventCnfgGUIExtRating_H__A82C6ECC_7ED9_47B4_A415_2F15B60FBB2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class		CHRatingDif;

class CHEventCnfgGUIExtRating : public CWnd
{
// Construction
public:
	CHEventCnfgGUIExtRating(CWnd * pParent,CGraphicWnd * _w, int x1,int y1,int x2,int y2);
	virtual ~CHEventCnfgGUIExtRating();

	void		init					(int x1,int y1,int x2,int y2);
				
	void		onClick					(UINT idGrid,int x,int y,LPARAM lParam);		
	void		onDblClick				(UINT idGrid,int x,int y,LPARAM lParam);
	void		onLButtonDown			(UINT idGrid,int x,int y,LPARAM lParam);
				
	BOOL		onPaintGrid				(UINT idGrid,GridItem * gi);
				
	void		fillGridRatings();
	void		paintListRatingDifs		(GridItem *gi);
	
	
	void		changeDifference(UINT idGrid,int x,int y,CHRatingDif *pRatingDif);
	void		saveRatingDif(CHRatingDif *pRatingDif);

		
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHEventCnfgGUIExtRating)
	//}}AFX_VIRTUAL

	
	//{{AFX_MSG(CHEventCnfgGUIExtRating)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
	
private:
	CHMemoryDataBase * mem();

	CGraphicWnd				*w;
	CWnd					*m_pParent;
	CHRatingDif				*m_pRatingDif;
	
	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHEventCnfgGUIExtRating_H__A82C6ECC_7ED9_47B4_A415_2F15B60FBB2F__INCLUDED_)
