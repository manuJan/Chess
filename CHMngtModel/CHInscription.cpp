/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHInscription.cpp                                                                 
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:07-12-2005
*   Project     :CH Model
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///

#include "stdCHMngt.h"
#include "CHInscription.h"
#include "CHMember.h"
#include "QCHInscription.h"
#include "UCHInscription.h"
#include "CHEvent.h"
#include "CHRegister.h"
#include "CHMemoryDataBase.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
MSLDEFINE_ITEM(CHInscription, __CHINSCRIPTION)

CHInscription::CHInscription()
:GTHInscription()
,m_seed(0)
,m_rating(0)
,m_kConst(0)
{	
}

CHInscription::CHInscription(GRegister *reg,GTHEvent *ev)
:GTHInscription(reg,ev)
,m_seed(0)
,m_rating(0)
,m_kConst(0)
{	
}

CHInscription::CHInscription(const CHInscription &copy)
{	
	operator=(copy);
}

CHInscription::~CHInscription()
{
}

GData& CHInscription::operator = (const GData &copy)
{
	if ( this != &copy )
	{
		const CHInscription & insc=(const CHInscription &) copy;
		
		GTHInscription::operator	= (copy);
		
		m_seed						= insc.m_seed;
		m_rating					= insc.m_rating;
		m_kConst					= insc.m_kConst;
		
	}
	return *this;
}

bool CHInscription::operator == (const GData &copy)
{
	if ( this == &copy )
		return true;

	const CHInscription & insc=(const CHInscription &) copy;

	return( GTHInscription::operator	== (copy)				&&
			m_seed						== insc.m_seed			&&
			m_rating					== insc.m_rating		&&
			m_kConst					== insc.m_kConst);	
}

bool CHInscription::operator != (const GData &copy)
{
	return !operator==(copy);
}

//pack
MSLPack& CHInscription::pack(MSLPack & aPack) const
{
	GTHInscription::pack (aPack);

	aPack << m_seed;
	aPack << m_rating;
	aPack << m_kConst;
	
	return aPack;
}

MSLPack& CHInscription::unpack(MSLPack &aPack)
{
	GTHInscription::unpack (aPack);

	aPack >> m_seed;
	aPack >> m_rating;
	aPack >> m_kConst;
	
	return aPack;
}

QBase* CHInscription::onQ() const
{
	return new QCHInscription();
}

UBase* CHInscription::onU() const
{
	return new UCHInscription();
}


// set
void CHInscription::setSeed(const short value)
{
	m_seed = value;
}
void CHInscription::setRating(const short value)
{
	m_rating = value;
}
void CHInscription::setKConst(const short value)
{
	m_kConst = value;
}

// get
short CHInscription::getSeed() const
{
	return m_seed;
}
short CHInscription::getRating() const
{
	return m_rating;
}
short CHInscription::getKConst() const
{
	return m_kConst;
}

MSLString CHInscription::getSeedAsString() const
{ 
	MSLString aux=NULLSTRING;
	
	if (m_seed)
		aux=TOSTRING(m_seed);
	
	return aux; 
}

MSLString CHInscription::getRatingAsString() const
{ 
	MSLString aux="-";
	
	if (m_rating)
		aux=TOSTRING(m_rating);
		
	return aux; 
}
MSLString CHInscription::getKConstAsString() const
{ 
	MSLString aux="-";
	
	if (m_kConst)
		aux=TOSTRING(m_kConst);
	return aux; 
}

GRegister::TypeRegister CHInscription::getType() const
{
	return getRegister()->getType();
}


short CHInscription::getRegMasterType() const
{
	CHRegister* pRegister = (CHRegister*)getRegister();
	return pRegister?pRegister->getMasterType():0;
}	

MSLString CHInscription::getRegMasterTypeAsString(bool longer/*=true*/) const
{
	CHRegister* pRegister = (CHRegister*)getRegister();
	return pRegister?pRegister->getMasterTypeAsString(longer):NULLSTRING;
}

short CHInscription::getRegMasterTypeOrder() const
{
	CHRegister* pRegister = (CHRegister*)getRegister();
	return pRegister?pRegister->getMasterTypeOrder():0;
}

MSLWString CHInscription::getTeamScbLName(const bool bFMember, const bool bSMember, const bool bTMember) const
{ //si bXMember es true compongo el nombre del equipo con ellos 
	
	MSLSortedVector vMembers;
	getMembersVector(vMembers);

	if (vMembers.entries()<2)
		return NULLWSTRING;

	MSLWString teamScbLName=NULLWSTRING;
	MSLWString blank=_T(" ");
	MSLWString slash=_T("/");

	MSLSortedVector vMyMembers(vMembers);
	for (short i=0; i<vMyMembers.entries(); i++)
	{ //elimino el substituto si existe
		CHMember * pMember =(CHMember*) vMyMembers[i];
		if (pMember->getFunction()==CHMember::eSubstitute)
		{
			vMyMembers.remove(pMember);
			break;
		}
	}

	CHMember *pFMember=0, *pSMember=0, *pTMember=0;
	if (bFMember && vMyMembers.entries()>=1)
		pFMember=(CHMember *) vMyMembers[0];
	if (bSMember && vMyMembers.entries()>=2)
		pSMember=(CHMember *) vMyMembers[1];
	if (bTMember  && vMyMembers.entries()>=3)
		pTMember=(CHMember *) vMyMembers[2];

	if (bFMember || bSMember)
		teamScbLName=(pFMember?(pFMember->getName2()):_T(""))+
		(pSMember?(slash+pSMember->getName2()):_T(""))+
		((vMyMembers.entries()==3 || vMyMembers.entries()==4)?slash:_T(""));
	if (bTMember)
	{
		if (bFMember || bSMember)
			teamScbLName+=slash;

		teamScbLName+=pTMember->getName2();
	}

	return teamScbLName;
}

short CHInscription::getTypeEvent() const
{
	return ((CHEvent *)getEvent())->getTypeEvent();
}