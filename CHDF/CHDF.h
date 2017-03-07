/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHDF.h
*	Description	:
*
*	Author		: Chess Team
*	Date created: 17-may-2006
* 	Project		: Chess DataFeed
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#if !defined(AFX_CHDFAPP_H__06507187_16FC_4402_A52E_483C49ECD60E__INCLUDED_)
#define AFX_CHDFAPP_H__06507187_16FC_4402_A52E_483C49ECD60E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

/////////////////////////////////////////////////////////////////////////////
// CCHDFApp:
// See CHDF.cpp for the implementation of this class
//

#include <GUI/DF/DFManagerGUI.h>
#include "CHDFGUI.h"

class CCHDFApp : public CDFManagerGUIApp
{
public:
	CCHDFApp();
	BOOL InitInstance();
	
	DFGUI				* getInterface();
	GMemoryDataBase		* newMem();
		
	virtual CString		callForAppName();
	virtual CString		callForVersion();
	virtual void		fillMyCollections(RWHashTable& sSource);

	//{{AFX_VIRTUAL(CCHDFApp)	
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CCHDFApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CHMemoryDataBase * m_pCHMem;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHDFAPP_H__06507187_16FC_4402_A52E_483C49ECD60E__INCLUDED_)
