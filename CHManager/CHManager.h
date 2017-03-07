/*************************************************************************************
*	© Copyright MSL Software, S.L., 2001
*
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHManager.h
*   Description	: 
*
*	Author		:Chess Team
*	Date created:14-12-2005
* 	Project		:CH Manager
*
***************************************************************************************/

#if !defined(AFX_CCHManagerApp_H__3372B535_E225_11D4_B834_0060948F6ACB__INCLUDED_)
#define AFX_CCHManagerApp__3372B535_E225_11D4_B834_0060948F6ACB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include <GUI/GMI/GManagerInterface.h>
#include <Sports\CH\Data\CHMsgDefines.h>
#include <Reports\V\VMedalsByEvent.h>

const int CH_INSCRIPTION_FORMVIEW	=	1;
const int CH_SCHEDULE_FORMVIEW		=	2;
const int CH_OFFICIALS_FORMVIEW		=	3;
const int CH_STARTLIST_FORMVIEW		=	4;
const int CH_PROGRESSION_FORMVIEW	=	5;
const int CH_MEDALS_FORMVIEW		=	10;

#define COLOR_GRID_PAR		0xFFFFFF			// Blanco
#define COLOR_GRID_LINE		RGB(190,190,190)	// Color Gris para las lineas
#define COLOR_BACK_FVIEW	RGB(240,240,250)
#define COLOR_EDIT			RGB(250,250,230) // Amarillo
#define COLOR_LABEL			RGB(250,250,255) // Azul (casi blanco)
#define COLOR_AUX			RGB(191,  0,  0) // Color Rojo.

const int BCKG_LABEL 		= 10800;
const int BCKG_EDIT 		= 10801;
const int IDC_COLOR_LABEL	= 10802;
const int IDC_COLOR_EDIT	= 10803;
const int IDC_COLOR_AUX		= 10804;
const int CH_FONTMIN		= 10805;

const int ADMINISTRATOR_LOGIN=	1;
const int DATA_ENTRY_LOGIN	 =	2;

class CCHManagerApp : public GManagerInterfaceApp
{
public:
	CCHManagerApp();
	
	//{{AFX_VIRTUAL(CCHManagerApp)
	//}}AFX_VIRTUAL	
public:
	//{{AFX_MSG(CCHManagerApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	virtual GMemoryDataBase *callForCreateMemoryDB();
	virtual CString			 callForAppName();
	virtual void			 callForLogins();
	virtual void             callForCreateButtons();
	virtual UINT             callForDefaultButtons();	
	virtual void             callWhenConnected();
	virtual void             callForPresentationDown(CGraphicWnd *w);
	virtual void             callForPresentationUp  (CGraphicWnd *w);
	virtual UINT             callForIDBLogo();	
	virtual RWCString*       callForReportsIniFile();
	virtual LRESULT			 callForAvancedCase(UINT message,WPARAM wParam,LPARAM lParam);
	virtual CString			 callForVersion();	

	virtual void onReportRequest   (CReportItem    *pItem);
	virtual bool onReportGeneration(CReportManager *pReportMngr,CReportConfig *pReportCfg,CReportItem *pItem);

	COLORREF			callForBkColor();
	COLORREF			callForBkColorGrid();
	COLORREF			callForBkColorButton();
	COLORREF			callForBkColorEdit();
	COLORREF			callForBkColorBox();
	COLORREF			callForColorOn();
	COLORREF			callForColorOff();
	COLORREF			callForColorHiTx();
	COLORREF			callForColorHigh();
	COLORREF			callForColorL3D();
	COLORREF			callForColorN3D();
	COLORREF			callForColorD3D();
	COLORREF			callForColorLine();
	void				callForPersonalGraphics(CGraphicWnd *w);
	
public:
	int getLogin() { return login; }
		
	void showMedals();

	// D B  F U N C T I O N S
	void out(short idTrn);
	void queueOut(GData* pData,RWBoolean forInsert=true);
private:
	RWCString iniFileName;
	CGraphicWnd *pWUp;
	RWOrdered outCol;					//Coleccion para el envia a DB y VC de objetos
	VMedalsByEvent * pVMedalsByEvent;	// Vista para el Report Medals By Event
	int login;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CCHManagerApp_H__3372B535_E225_11D4_B834_0060948F6ACB__INCLUDED_)

