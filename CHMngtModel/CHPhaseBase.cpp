/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHPhaseBase.cpp
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

#include "stdCHMngt.h"
#include "CHPhaseBase.h"
#include "UCHPhaseBase.h"
#include "CHClassIds.h"
#include <core/G/GBuffer.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
RWDEFINE_COLLECTABLE(CHPhaseBase, __CHPHASEBASE)
CHPhaseBase::CHPhaseBase()
:GTHPhaseGeneric()
,typePhase(eElim)
{
}
CHPhaseBase::~CHPhaseBase()
{
	
}
CHPhaseBase::CHPhaseBase(const CHPhaseBase & copy)
{
	operator=(copy);
}

CHPhaseBase::CHPhaseBase(CPack& aPack)
:GTHPhaseGeneric()
,typePhase(eElim)
{
	unpack(aPack);
}

//////////////////////////////////////////////////////////////////////
// Overloaded Operators
//////////////////////////////////////////////////////////////////////
CHPhaseBase & CHPhaseBase::operator =(const CHPhaseBase & copy)
{
	if (this != &copy)
	{
		GTHPhaseGeneric::operator =(copy);
		typePhase			= copy.typePhase;
		
	}
	return * this;
}

RWBoolean CHPhaseBase::operator ==(const CHPhaseBase & copy)
{
	if (this == &copy)
		return true;
	else
		return (GTHPhaseGeneric::operator ==(copy)			&& 
				typePhase			== copy.typePhase		);
}

RWBoolean CHPhaseBase::operator !=(const CHPhaseBase & copy)
{
	return !operator==(copy);
}
//////////////////////////////////////////////////////////////////////
// SQL function
//////////////////////////////////////////////////////////////////////
RWBoolean CHPhaseBase::uSQL(RWDBConnection& pConnect,RWBoolean remove/*=false*/)
{
	RWBoolean rc=false;

	UCHPhaseBase upd(&pConnect);
	if( remove )
		rc=upd.remove(*this);
	else
		rc=upd.set(*this);
	return rc;
}
//////////////////////////////////////////////////////////////////////
// SETS
//////////////////////////////////////////////////////////////////////
void CHPhaseBase::setTypePhase(const short value)
{
	typePhase=value;
}
//////////////////////////////////////////////////////////////////////
// GETS
//////////////////////////////////////////////////////////////////////
short CHPhaseBase::getTypePhase() const
{
	return typePhase;
}

//////////////////////////////////////////////////////////////////////
// GPack member funcions & external operators
//////////////////////////////////////////////////////////////////////
CPackObject CHPhaseBase::getPackObject()
{
	CPackObject aPack;
	aPack.setId( isA() );
	pack(aPack);
	return aPack;
}

CPack& CHPhaseBase::pack(CPack& aPack)
{
	GTHPhaseGeneric::pack(aPack);
	
	aPack << typePhase;	
	
	return aPack;
}

CPack& CHPhaseBase::unpack(CPack& aPack)
{
	GTHPhaseGeneric::unpack(aPack);
	
	aPack >> typePhase;
		
	return aPack;
}