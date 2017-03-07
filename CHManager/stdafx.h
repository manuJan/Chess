/*************************************************************************************
*	© Copyright MSL Software, S.L., 2001
*
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: StdAfx.h
*   Description	: 
*
*	Author		:
*	Date created:
* 	Project		:
*
***************************************************************************************/

#if !defined(AFX_STDAFX_H__FA3D02B9_EC8B_11D4_A846_006094F9F662__INCLUDED_)
#define AFX_STDAFX_H__FA3D02B9_EC8B_11D4_A846_006094F9F662__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning( disable : 4516 )

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#pragma warning( disable : 4516 )

#include <core/G/GMsgDefines.h>
#include <core/TH/GTHMsgDefines.h>
#include <Sports/CH/Data/CHMemoryDataBase.h>
#include <Sports/CH/Data/CHClassIds.h>
#include <Sports/CH/Data/CHMsgDefines.h>
#endif // !defined(AFX_STDAFX_H__FA3D02B9_EC8B_11D4_A846_006094F9F662__INCLUDED_)
