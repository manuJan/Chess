/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:UCHPhaseBase.h
*	Description	: 
*
*   Author      :Chess Team
*   Date created:07-12-2005
*   Project     :CH Model       
*	
* 	Modification history
*	By		:	
*	Date	:	
*	Changes	:	
*
***************************************************************************************/

#if !defined(AFX_UCHPhaseBase_H__596AB734_7574_11D3_A8F6_0060948F6ACB__INCLUDED_)
#define AFX_UCHPhaseBase_H__596AB734_7574_11D3_A8F6_0060948F6ACB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include <OVR/CORE/G/UBase.h>

class UCHPhaseBase : public UBase
{
public:
	inline UCHPhaseBase()
		:UBase()
		{;}

	inline virtual ~UCHPhaseBase(){}

protected:
	RWBoolean insert(RWDBConnection& aConnection, GData& aData);
	RWBoolean update(RWDBConnection& aConnection, GData& aData);
	RWBoolean delete_(RWDBConnection& aConnection, GData& aData);
};

#endif // !defined(AFX_UCHPhaseBase_H__596AB734_7574_11D3_A8F6_0060948F6ACB__INCLUDED_)
