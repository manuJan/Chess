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
#include "CHClassIDs.h"
#include "UCHInscription.h"
#include "CHEvent.h"
#include "CHRegister.h"
#include "CHMemoryDataBase.h"

int orderMembersInscription(const GVectorElement** a, const GVectorElement** b)
{
	CHMember * pMemberA=(CHMember *)(*a)->getElement();
	CHMember * pMemberB=(CHMember *)(*b)->getElement();

	return pMemberA->getOrder() - pMemberB->getOrder();
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
RWDEFINE_COLLECTABLE(CHInscription, __CHINSCRIPTION)

CHInscription::CHInscription()
:GTHInscription()
,seed(0)
,rating(0)
,kConst(0)
{
	getMembersVector().sort(orderMembersInscription);
}

CHInscription::CHInscription(GRegister *reg,GTHEvent *ev)
:GTHInscription(reg,ev)
,seed(0)
,rating(0)
,kConst(0)
{
	getMembersVector().sort(orderMembersInscription);
}

CHInscription::CHInscription(const CHInscription &copy)
{
	getMembersVector().sort(orderMembersInscription);
	operator=(copy);
}

CHInscription::CHInscription(CPack &iPack)
{
	getMembersVector().sort(orderMembersInscription);
	unpack(iPack);
}

CHInscription::~CHInscription()
{
}

CHInscription& CHInscription::operator = (const CHInscription &copy)
{
	if ( this != &copy )
	{
		GTHInscription::operator	= (copy);
		seed						= copy.seed;
		rating						= copy.rating;
		kConst						= copy.kConst;
		
	}
	return *this;
}

RWBoolean CHInscription::operator == (const CHInscription &copy)
{
	if ( this == &copy )
		return true;

	if( GTHInscription::operator	== (copy)				&&
		seed						== copy.seed			&&
		rating						== copy.rating			&&
		kConst						== copy.kConst)
	{
		return true;
	}
	return false;
}

RWBoolean CHInscription::operator != (const CHInscription &copy)
{
	return !operator==(copy);
}

CHMember * CHInscription::operator [] (const size_t index) const
{
	if( index<getMembersVector().entries() )
		return (CHMember *)getMember(index);
	return 0;
}

RWBoolean CHInscription::uSQL(RWDBConnection& pConnect,RWBoolean remove/*=false*/)
{
	RWBoolean rc=false;
	UCHInscription upd(&pConnect);
	if(remove )
		rc=upd.remove(*this);
	else
		rc=upd.set(*this);
	return rc;
}

RWCString CHInscription::msl() const
{
	RWCString str = GTHInscription::msl();
	if(!str.length() || str == NULLRWSTRING)
		return NULLRWSTRING;

	GBuffer aBuffer;
	return str + RWCString(aBuffer	<< seed
									<< rating
									<< endLine);
}
//pack
CPack& CHInscription::pack(CPack & aPack)
{
	GTHInscription::pack (aPack);
	aPack << seed;
	aPack << rating;
	aPack << kConst;
	
	return aPack;
}

CPack& CHInscription::unpack(CPack &aPack)
{
	GTHInscription::unpack (aPack);
	aPack >> seed;
	aPack >> rating;
	aPack >> kConst;
	
	return aPack;
}
// set
void CHInscription::setSeed(const short value)
{
	seed = value;
}
void CHInscription::setRating(const short value)
{
	rating = value;
}
void CHInscription::setKConst(const short value)
{
	kConst = value;
}

// get
short CHInscription::getSeed() const
{
	return seed;
}
short CHInscription::getRating() const
{
	return rating;
}
short CHInscription::getKConst() const
{
	return kConst;
}

RWCString CHInscription::getSeedAsString() const
{ 
	RWCString aux=NULLRWSTRING;
	char tmp[10];
	
	if (seed)
		aux=itoa(seed,tmp,10);
	return aux; 
}

RWCString CHInscription::getRatingAsString() const
{ 
	RWCString aux="-";
	char tmp[10];
	
	if (rating)
		aux=itoa(rating,tmp,10);
	return aux; 
}
RWCString CHInscription::getKConstAsString() const
{ 
	RWCString aux="-";
	char tmp[10];
	
	if (kConst)
		aux=itoa(kConst,tmp,10);
	return aux; 
}

GRegister::TypeRegister CHInscription::getType() const
{
	return getRegister()->getType();
}

RWWString CHInscription::getGroupLDescription(const char *language/*=DBApplication::getAppLanguage()*/) const
{
	return getRegister()?getRegister()->getGroupLDescription(language):_T("");
}

RWCString CHInscription::getRegisterBirthDate(const char *format/*="%x"*/) const
{
	return getRegister()?getRegister()->getBirthDate(format):"";
}

CHRegister *CHInscription::getMemberRegister(const size_t value) const
{
	return (CHRegister *)(getMember(value)?getMember(value)->getRegister():0);
}

int CHInscription::getRegisterCode() const
{
	return getRegister()->getRegister();
}

RWWString CHInscription::getMemberRegisterPrnLName(const size_t value) const
{
	return getMemberRegister(value)?getMemberRegister(value)->getPrnLName():_T("");
}

short CHInscription::getRegMasterType() const
{
	CHRegister* pRegister = (CHRegister*)getRegister();
	return pRegister?pRegister->getMasterType():0;
}	

RWCString CHInscription::getRegMasterTypeAsString(bool longer/*=true*/) const
{
	CHRegister* pRegister = (CHRegister*)getRegister();
	return pRegister?pRegister->getMasterTypeAsString(longer):NULLRWSTRING;
}

short CHInscription::getRegMasterTypeOrder() const
{
	CHRegister* pRegister = (CHRegister*)getRegister();
	return pRegister?pRegister->getMasterTypeOrder():0;
}

RWWString CHInscription::getTeamScbLName(const RWBoolean bFMember, const RWBoolean bSMember, const RWBoolean bTMember) const
{ //si bXMember es true compongo el nombre del equipo con ellos 
	if (getMembersVector().entries()<2)
		return NULLRWWSTRING;

	RWWString teamScbLName=NULLRWWSTRING;
	RWWString blank=_T(" ");
	RWWString slash=_T("/");
	GSortedVector vMyMembers(getMembersVector());
	for (size_t i=0; i<vMyMembers.entries(); i++)
	{ //elimino el substituto si existe
		CHMember * pMember =(CHMember*) vMyMembers[i]->getElement();
		if (pMember->getFunction()==CHMember::eSubstitute)
		{
			vMyMembers.remove(pMember);
			break;
		}
	}

	CHMember *pFMember=0, *pSMember=0, *pTMember=0;
	if (bFMember && vMyMembers.entries()>=1)
		pFMember=(CHMember *) vMyMembers[0]->getElement();
	if (bSMember && vMyMembers.entries()>=2)
		pSMember=(CHMember *) vMyMembers[1]->getElement();
	if (bTMember  && vMyMembers.entries()>=3)
		pTMember=(CHMember *) vMyMembers[2]->getElement();

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