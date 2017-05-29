/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: ARDefinition.cpp
*	Description	:
*
*	Author		: Javier Juste
*	Date created: 02 Junio 2008
* 	Project		: Archery DLL
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "StdCHMngt.h"
#include "CHDefinition.h"
#include "QCHDefinition.h"
#include "UCHDefinition.h"


MSLDEFINE_ITEM(CHDefinition,__CHDEFINITION)

//////////////////////////////////////////////////////////////////////
// Constructors/Destructor
//////////////////////////////////////////////////////////////////////

CHDefinition::CHDefinition()
:GTHDefinition()
,m_autoProg(false)
{
}

CHDefinition::CHDefinition(const CHDefinition & copy)
{
	operator=(copy);
}

CHDefinition::~CHDefinition()
{
}

/**** Virtual operators inherited from GData ********************/
GData& CHDefinition::operator= (const GData& copy)
{
	if (this != &copy)
	{
		GTHDefinition::operator=(copy);

		const CHDefinition & definition=(const CHDefinition  &) copy;
	
		m_autoProg = definition.m_autoProg;	
	}

	return *this;
}

bool CHDefinition::operator==(const GData& copy)
{
	if (this == &copy)
		return true;

	const CHDefinition & definition=(const CHDefinition  &) copy;

	return (GTHDefinition::operator==(copy)	&&		
			m_autoProg == definition.m_autoProg);
}

bool CHDefinition::operator!=(const GData& copy)
{
	return !operator==(copy);
}

/**** Virtual methods inherited from GData **********************/
MSLPack& CHDefinition::pack(MSLPack& pack) const
{
	GTHDefinition::pack(pack);

	pack << m_autoProg;
	
	return pack;
}

MSLPack& CHDefinition::unpack(MSLPack& pack)
{
	GTHDefinition::unpack(pack);
	
	pack >> m_autoProg;
	
	return pack;
}

UBase*  CHDefinition::onU() const
{
	return new UCHDefinition();
}

QBase*  CHDefinition::onQ() const
{
	return new QCHDefinition();	
}

//////////////////////////////////////////////////////////////////////
//SETS
//////////////////////////////////////////////////////////////////////
void CHDefinition::setAutoProg(const bool value)
{
	m_autoProg=value; 
}
//////////////////////////////////////////////////////////////////////
//GETS
//////////////////////////////////////////////////////////////////////

bool CHDefinition::getAutoProg() const
{ 
	return m_autoProg; 
}

