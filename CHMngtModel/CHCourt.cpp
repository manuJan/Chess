/*************************************************************************************
*	© Copyright MSL Software, S.L., 2001
*
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHCourt.CPP
*	Description	:
*
*	Author		:Chess Team
*	Date created:12-12-2005
* 	Project		:CH Model
*
*
***************************************************************************************/

#include "stdCHMngt.h"
#include "CHCourt.h"
#include "UCHCourt.h"


MSLDEFINE_ITEM(CHCourt, __CHCOURT);

//////////////////////////////////////////////////////////////////////
// Constructors/Destructor
//////////////////////////////////////////////////////////////////////
CHCourt::CHCourt()
:GCourt()
,m_order(0)
{
}
	
CHCourt::CHCourt(const CHCourt &copy)
:GCourt()
{
	operator=(copy);
}


CHCourt::~CHCourt()
{

}

//////////////////////////////////////////////////////////////////////
// Overloaded Operators
//////////////////////////////////////////////////////////////////////

CHCourt & CHCourt::operator=(const CHCourt & copy)
{
	if ( this != &copy )
	{
		GCourt::operator = (copy);

		m_order		 = copy.m_order;
	}	
	return *this;
}

bool CHCourt::operator==(const GData & copy)
{
	if ( this == &copy )
		return true;

	const CHCourt & court=(const CHCourt &) copy;

	return ( GCourt::operator == (copy)	&&
			m_order		 == court.m_order );	
}


bool CHCourt::operator!=(const GData & copy)
{
	return !operator==(copy);
}

//////////////////////////////////////////////////////////////////////
//From GData
//////////////////////////////////////////////////////////////////////

	/**** Virtual methods inherited from GData **********************/
MSLPack& CHCourt::pack(MSLPack& pack) const
{
	GCourt::pack(pack);

	pack << m_order;
	
	return pack;
}

MSLPack& CHCourt::unpack(MSLPack& pack)
{
	GCourt::unpack(pack);

	pack >> m_order;
	
	return pack;
}

QBase* ARDistance::onQ() const
{
	return new QARDistance();
}

UBase* ARDistance::onU() const
{
	return 0;
}


//SETS
//////////////////////////////////////////////////////////////////////

void CHCourt::setOrder(const short value)
{ 
	m_order = value; 
}

//////////////////////////////////////////////////////////////////////
//GETS
//////////////////////////////////////////////////////////////////////

short CHCourt::getOrder() const
{ 
	return m_order; 
}

//////////////////////////////////////////////////////////////////////
// Packing Methods
//////////////////////////////////////////////////////////////////////

CPack& CHCourt::pack(CPack & aPack)
{
	GCourt::pack (aPack);

	aPack << m_order;
	
	return aPack;
}


CPack& CHCourt::unpack(CPack &aPack)
{
	GCourt::unpack (aPack);
	
	aPack >> m_order;
	
	return aPack;
}
