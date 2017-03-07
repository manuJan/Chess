/*************************************************************************************
*	© Copyright MSL Software, S.L., 2001
*
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior wriCHen permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHMatchMember.h
*	Description	:Chess MatchMember
*
*	Author		:Chess Team
*	Date created:13-12-2005
* 	Project		:CH Model
*
***************************************************************************************/

#if !defined(AFX_CHMATCHMEMBER_H__CB507405_4F6F_4446_B576_768B4805FA3F__INCLUDED_)
#define AFX_CHMATCHMEMBER_H__CB507405_4F6F_4446_B576_768B4805FA3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHMNGTMODELDLL_H_
#	include "CHMngtModelDll.h"
#endif // _CHMNGTMODELDLL_H_

#include <CORE/TH/GTHMatchMember.h>

class CHModelExport CHMatchMember : public GTHMatchMember  
{
	RWDECLARE_COLLECTABLE(CHMatchMember)

public:
	CHMatchMember();
	CHMatchMember(const CHMatchMember &copy);
	CHMatchMember(CPack &aPack);
	virtual ~CHMatchMember();

	CHMatchMember  &operator  =(const CHMatchMember &copy);
	RWBoolean		operator ==(const CHMatchMember &copy);
	RWBoolean		operator !=(const CHMatchMember &copy);

	inline RWBoolean uSQL(RWDBConnection &pConnect,RWBoolean remove/*=false*/);
	RWCString msl() const;
	RWCString mslDescription(const char *language) const;
	CPack&		pack(CPack &aPack);
	CPack&		unpack(CPack &iPack);

	//Get
	GSortedVector &getMembersVector() const;
	RWCString getMemberKey() const;

};

#endif // !defined(AFX_CHMATCHMEMBER_H__CB507405_4F6F_4446_B576_768B4805FA3F__INCLUDED_)
