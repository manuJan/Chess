// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__23534E35_C33C_4DC1_9513_147EC77ABE13__INCLUDED_)
#define AFX_STDAFX_H__23534E35_C33C_4DC1_9513_147EC77ABE13__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning( disable : 4516 )

// Insert your headers here
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <windows.h>

// From Rouge Wage Tools
#ifndef __RWCOLLECT_H__
#	include <rw/collect.h>
#endif

#ifndef __RWCSTRING_H__
#	include <rw/cstring.h>
#endif // __RWCSTRING_H__

#ifndef __RWSET_H__
#	include <rw/rwset.h>
#endif // __RWSET_H__

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__23534E35_C33C_4DC1_9513_147EC77ABE13__INCLUDED_)
