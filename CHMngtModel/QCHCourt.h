/*************************************************************************************
*	© Copyright MSL Software, S.L., 2001
*
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:QCHCourt.h
*	Description	:Query Chess Court
*
*	Author		:Chess Team
*	Date created:12-12-2005
* 	Project		:CH Model
*
***************************************************************************************/

#if !defined(AFX_QCHCOURT_H__AD0D9A1F_C4E8_462E_B906_B4FE474B284D__INCLUDED_)
#define AFX_QCHCOURT_H__AD0D9A1F_C4E8_462E_B906_B4FE474B284D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <CORE/G/QCourt.h>
#include "CHCourt.h"

class QCHCourt : public QCourt  
{
public:
	QCHCourt(RWDBConnection *pNewConnection)
		:QCourt(pNewConnection) 
		{;} 
	virtual ~QCHCourt() 
		{;}

protected:
	void OnSelect(RWDBSelector& aSelect,RWDBTable& tPhase);
	void OnReader(RWDBReader& aReader,GCourt *pCourt);

	GCourt * OnNewCourt()
		{ return new CHCourt(); }
};

#endif // !defined(AFX_QCHCOURT_H__AD0D9A1F_C4E8_462E_B906_B4FE474B284D__INCLUDED_)
