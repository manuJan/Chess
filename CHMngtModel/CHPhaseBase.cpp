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
#include "QCHPhaseBase.h"
#include <ovr/core/G/GBuffer.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
MSLDEFINE_ITEM(CHPhaseBase, __CHPHASEBASE)
CHPhaseBase::CHPhaseBase()
:GTHPhaseBase()
,m_typePhase(eElim)
{
}
CHPhaseBase::~CHPhaseBase()
{
	
}
CHPhaseBase::CHPhaseBase(const CHPhaseBase & copy)
{
	operator=(copy);
}

//////////////////////////////////////////////////////////////////////
// Overloaded Operators
//////////////////////////////////////////////////////////////////////
GData & CHPhaseBase::operator =(const GData & copy)
{
	if (this != &copy)
	{
		GTHPhaseBase::operator =(copy);

		const CHPhaseBase & aPhaseBase=(const CHPhaseBase &) copy;

		m_typePhase	= aPhaseBase.m_typePhase;
		
	}
	return * this;
}

bool CHPhaseBase::operator ==(const GData & copy)
{
	if (this == &copy)
		return true;
	
	const CHPhaseBase & aPhaseBase=(const CHPhaseBase &) copy;

	return (GTHPhaseBase::operator ==(copy)	&& 
			m_typePhase	== aPhaseBase.m_typePhase	);
}

bool CHPhaseBase::operator !=(const GData & copy)
{
	return !operator==(copy);
}

/**** Virtual methods inherited from GData **********************/
MSLPack& CHPhaseBase::pack(MSLPack& pack) const
{
	GTHPhaseBase::pack(pack);

	pack << m_typePhase;
		
	return pack;
}

MSLPack& CHPhaseBase::unpack(MSLPack& pack)
{
	GTHPhaseBase::unpack(pack);

	pack >> m_typePhase;
	
	return pack;
}


//////////////////////////////////////////////////////////////////////
// SQL function
//////////////////////////////////////////////////////////////////////

QBase*	CHPhaseBase::onQ() const
{
	return new QCHPhaseBase();
}

UBase* CHPhaseBase::onU() const
{
	return 0;
}

//////////////////////////////////////////////////////////////////////
// SETS
//////////////////////////////////////////////////////////////////////
void CHPhaseBase::setTypePhase(const short value)
{
	m_typePhase=value;
}
//////////////////////////////////////////////////////////////////////
// GETS
//////////////////////////////////////////////////////////////////////
short CHPhaseBase::getTypePhase() const
{
	return m_typePhase;
}

