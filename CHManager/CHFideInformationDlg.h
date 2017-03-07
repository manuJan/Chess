/*************************************************************************************
*	© Copyright MSL Software, S.L., 2001
*
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHFideInformationDlg.h
*   Description	: 
*
*	Author		: Chess Team
*	Date created: 12-01-2006
* 	Project		:
*
***************************************************************************************/
#if !defined(AFX_CHFideInformationDlg_H__A0CC819B_59C9_42DF_B896_21C7569E0760__INCLUDED_)
#define AFX_CHFideInformationDlg_H__A0CC819B_59C9_42DF_B896_21C7569E0760__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CHFideInformationDlg.h : header file
//

#include "resource.h"
#include <gui/persist/Persistence.h>
/////////////////////////////////////////////////////////////////////////////
// CHFideInformationDlg dialog

class CHFideElement : public GData
{
public:
	CHFideElement()
	:idNumber(0)
	,name("")
	,title("")
	,federation("")
	,games(0)
	,rating(0)
	,yearOfBirth("")
	,flag("")
	{};
	virtual ~CHFideElement(){};

	inline RWBoolean uSQL(RWDBConnection& pConnect,RWBoolean remove=false){ 
		UNREFERENCED_PARAMETER(pConnect); UNREFERENCED_PARAMETER(remove); return false; };
	
	// Packing Methods
	inline CPack& pack(CPack &aPack){return aPack;};
	inline CPack& unpack(CPack &aPack){return aPack;};


	CHFideElement &	operator  = (const CHFideElement & copy);
	RWBoolean					operator == (const CHFideElement & copy);
	RWBoolean					operator != (const CHFideElement & copy);

	// Sets
	inline void					setIdNumber(const int value)
								{ idNumber=value; };
	inline void					setName(const char * value)
								{ name=value; };		
	inline void					setTitle(const char * value)
								{ title=value; };
	inline void					setFederation(const char * value)
								{ federation=value; };
	inline void					setGames(const int value)
								{ games=value; };
	inline void					setRating(const int value)
								{ rating=value; };
	inline void					setYearOfBirth(const char * value)
								{ yearOfBirth=value; };
	inline void					setFlag(const char * value)
								{ flag=value; };

	// Gets
	inline int					getIdNumber() const
								{return idNumber; }
	inline RWCString			getName() const
								{return name; }
	inline RWCString			getTitle() const
								{return title; }
	inline RWCString			getFederation() const
								{return federation; }
	int							getRating() const
								{return rating; }
	int							getGames() const
								{return games; }
	RWCString					getYearOBirth() const
								{return yearOfBirth; }
	RWCString					getFlag() const
								{return flag; }

private:
	int			idNumber;	// Identificador de ajedrezista
	RWCString	name;
	RWCString	title;		// Es nuestro masterType
	RWCString	federation;
	int			games;
	int			rating;
	RWCString	yearOfBirth;
	RWCString	flag;

	
};

class CHMemoryDataBase;
class CHFideInformationDlg : public CDialog
{
// Construction
public:
	CHFideInformationDlg(CHMemoryDataBase* pMem,CWnd* pParent = NULL);   // standard constructor
	virtual ~CHFideInformationDlg();

	
private:
	void			fillFideInformation();
	void			fillInscriptions();
	void			fillMembers();
	void			sortFideInformation(short type);
	void			sortInscriptions(short type);
	void			sortMembers(short type);
	void			paintFideInformation(GridItem* gi);
	void			paintInscriptions(GridItem* gi);
	void			paintMembers(GridItem* gi);
	void			paintCartel();
	void			OnOK();
	RWBoolean		processIn(RWCString line,CHFideElement *pFideElement);
	CHInscription *	existIDNumber(int number);
	RWBoolean		existInFideFile(CHInscription *pInscription);
	RWBoolean		existInFideFile(CHMember *pMember);
	void			setInformation(CHFideElement *pFideElement);
	void			saveFideFile();
	void			editRating(int x,int y,CHInscription *pInscription);
	void			editSeed(int x,int y,CHInscription *pInscription);
	RWBoolean		repeatSeed(CHInscription* pInscription, short seed);
	void			paintInsMember();

// Dialog Data
	//{{AFX_DATA(CHFideInformationDlg)
	enum { IDD = IDD_FIDE_INFORMATION };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHFideInformationDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHFideInformationDlg)
	virtual BOOL OnInitDialog();
	afx_msg LRESULT onClick(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT onDblClick(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT onPaintGrid(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT onClickHeader(WPARAM wParam,LPARAM lParam);
	afx_msg void    OnKeyDown (WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CGraphicWnd*		w;
	CHMemoryDataBase*	pMemory;
	GSortedVector		vFideInformations;
	CPersistence		m_logFile;
	RWBoolean			hasErrors;
	RWBoolean			insMember;
		
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHMASTERTYPEDLG_H__A0CC819B_59C9_42DF_B896_21C7569E0760__INCLUDED_)
