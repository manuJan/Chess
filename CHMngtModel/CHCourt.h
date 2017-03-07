/*************************************************************************************
*	© Copyright MSL Software, S.L., 2001
*
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHCourt.h
*	Description	:Chess
*
*	Author		:Chess Team
*	Date created:12-12-2005
* 	Project		:CH Model
*
*
***************************************************************************************/

#if !defined(AFX_CHCOURT_H__9F760635_0A5B_4D17_9320_C39C9337EEBB__INCLUDED_)
#define AFX_CHCOURT_H__9F760635_0A5B_4D17_9320_C39C9337EEBB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Core/G/GCourt.h>

#ifndef _CHMNGTMODELDLL_H
#   include "CHMngtModelDll.h" 
#endif // _CH_MNGTMODELDLL_H

class CHModelExport CHCourt : public GCourt  
{
	RWDECLARE_COLLECTABLE(CHCourt)

public:
	// Constructors/Destructor
	CHCourt();
	CHCourt(const CHCourt &copy);
	CHCourt(CPack &iPack);
	virtual ~CHCourt();

	// Overloaded operators 
	CHCourt	    &operator = (const CHCourt &copy);
	RWBoolean    operator == (const CHCourt &copy);
	RWBoolean    operator != (const CHCourt &copy);

	//From Data
	RWBoolean uSQL(RWDBConnection& pConnect,RWBoolean remove=false);
	RWCString msl() const;
	RWCString mslDescription(const char *language) const;
	CPack &   pack(CPack & aPack);
	CPack & unpack(CPack & aPack);
	
	//SETS
	void setOrder(const short value);
	
	//GETS
	short getOrder() const;

private:
	short order;		// Numero de Orden 
};

#endif // !defined(AFX_CHCOURT_H__9F760635_0A5B_4D17_9320_C39C9337EEBB__INCLUDED_)
