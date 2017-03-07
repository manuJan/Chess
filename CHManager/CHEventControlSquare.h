#if !defined(AFX_CHEVENTCONTROLSQUARE_H__B36DC3D0_62D8_44C4_9466_CD073D67F15D__INCLUDED_)
#define AFX_CHEVENTCONTROLSQUARE_H__B36DC3D0_62D8_44C4_9466_CD073D67F15D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CHEventControlSquare.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHEventControlSquare window

class CHEventControlSquare : public CWnd
{
// Construction
public:
	CHEventControlSquare(CWnd * _pParent,CGraphicWnd * _w,CRect _rect,short _X, short _Y);

// Attributes
public:

// Operations
public:
	void initSquare();
	void updateSquare();
	void paint();

	void setPiece(int iPiece);
	void setFocus();
	void lostFocus();
	void setColor(int color);

	int getPiece();
	int getColor();
	bool isFocus();	

	void empty();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHEventControlSquare)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHEventControlSquare();

	// Generated message map functions
protected:
	//{{AFX_MSG(CHEventControlSquare)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	
	int getBmp();

private:

	CWnd * pParent;
	CGraphicWnd * w;
	CRect rect;
	short X;
	short Y;
	bool m_focus;
	short m_Piece;
	short m_PieceColor;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHEVENTCONTROLSQUARE_H__B36DC3D0_62D8_44C4_9466_CD073D67F15D__INCLUDED_)
