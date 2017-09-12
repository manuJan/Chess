/*************************************************************************************
*			© Copyright MSL Software, S.L., 2001
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHVMngtModelDefs.h
*	Description	:	
*
*	Author		: Javier Juste
*	Date created: 15-Feb-2009
* 	Project		: AR Reports Model exportable
*	
* 	Modification history
*	By			:
*	Date		:
*	Changes		:
*
***************************************************************************************/

#ifndef _CHVMNGTMODELDEFS_H__
#define _CHVMNGTMODELDEFS_H__	1

#ifdef CHVMNGTMODEL_EXPORTS
#	define CHVMngtModelExport  _declspec(dllexport)
#else
#	define CHVMngtModelExport  _declspec(dllimport)
#endif //CHVMNGTMODEL_EXPORTS

// REPORTS IDs

#define CH30			2000
#define CH30_NAME		L"Number Entries by Noc (C30)"

#define CH32A			2001
#define CH32A_NAME		L"Entry List By NOC (C32A)"			

#define CH32C			2003
#define CH32C_NAME		L"Entry List By Event (C32C)"

#define CH38			2004
#define CH38_GROUP		2005
#define CH38_NAME		L"Entry Data CheckList(C38)"

#define CH08			2006
#define CH08_NAME		L"Competition Schedule (C08)"

#define CH58			2007
#define CH58_NAME		L"Pairings (C58)"

#define CH51			2008
#define CH51_NAME		L"Startlist (C51)"

#define CH74			2009
#define CH74_NAME		L"Results by Round (C74)"

#define CH75			2010
#define CH75_NAME		L"Ranking by Round (C75)"

// Medallists
#define CH92A			2011
#define CH92A_NAME		L"Medallists (C92A)"

// Medallist
#define CH92B			2012
#define CH92B_NAME		L"Medallists (C92B)"

// Medallist by Event
#define CH93			2013
#define CH93_NAME		L"Medallists By Event (C93)"

// Medals Standings
#define CH95			2014
#define CH95_NAME		L"Medals Standings (C95)"

#define CH58_ROUND			2015
#define CH58_ROUND_NAME		L"Pairings by Round (C58)"

#define ALL_ROUNDS 100

#endif _CHVMNGTMODELDEFS_H__
