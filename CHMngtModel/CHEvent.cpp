/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHEvent.cpp
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
#include "CHEvent.h"
#include "CHClassIds.h"
#include "CHInscription.h"
#include "CHMemoryDataBase.h"
#include "UCHEvent.h"
#include <core/G/GScore.h>

//select
RWBoolean inscriptionsEvent(const RWCollectable *col, const void *param)
{
	CHInscription *pInscription = (CHInscription*)col;
	CHEvent *pEvent = (CHEvent *)param;
	
	if(pInscription->getEvent()->getKey() == pEvent->getKey())
		return true;
	return false;	
}

RWDEFINE_COLLECTABLE(CHEvent,__CHEVENT)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHEvent::CHEvent()
:GTHEvent()
,typeEvent(eNone)
,orderEvent(0)
,mode(eIndividual)
,twoBronces(0)
,reqRankOrder(NULLRWSTRING)
,idTeamMatchsCnfg(0)
,constRating(0.0)
,pointsBye(0.0)
{
}

CHEvent::CHEvent(const CHEvent & copy)
{
	operator=(copy);
}

CHEvent::CHEvent(CPack & aPack)
{
	unpack(aPack);
}

CHEvent::~CHEvent()
{

}

CHEvent & CHEvent::operator =(const CHEvent & copy)
{
	if (this != &copy)
	{
		GTHEvent::operator =(copy);
		typeEvent			= copy.typeEvent;
		orderEvent			= copy.orderEvent;
		mode				= copy.mode;
		twoBronces			= copy.twoBronces;
		reqRankOrder		= copy.reqRankOrder;
		idTeamMatchsCnfg	= copy.idTeamMatchsCnfg;
		constRating			= copy.constRating;
		pointsBye			= copy.pointsBye;
		
	}
	return * this;
}

RWBoolean CHEvent::operator==(const CHEvent & copy)
{
	if (this == &copy)
		return true;
	else
		return (GTHEvent::operator	==(copy)				&& 
				typeEvent		== copy.typeEvent			&&
				orderEvent		== copy.orderEvent			&&
				mode			== copy.mode				&&
				twoBronces		== copy.twoBronces			&&
				reqRankOrder	== copy.reqRankOrder		&&
				idTeamMatchsCnfg== copy.idTeamMatchsCnfg	&&
				constRating		== copy.constRating			&&
				pointsBye		== copy.pointsBye
				);
}

RWBoolean CHEvent::operator!=(const CHEvent & copy)
{
	return !operator==(copy);
}

RWBoolean CHEvent::uSQL(RWDBConnection & pConnect,RWBoolean remove/*=false*/)
{
	UCHEvent u(&pConnect);
	if( remove )
		return u.remove(*this);
	return u.set(*this);
}

RWCString CHEvent::msl() const
{
	RWCString str=GTHEvent::msl();
	GBuffer aBuffer;
	if(str==NULLRWSTRING)
		return str;
		
	aBuffer	<< typeEvent
			<< orderEvent
			<< mode
			<< twoBronces
			<< reqRankOrder
			<< idTeamMatchsCnfg
			<< getConstRatingStr()
			<< endLine ;

	return  str + RWCString(aBuffer);
}

RWCString CHEvent::mslDescription(const char *language) const
{
	return GTHEvent::mslDescription(language);
}

CPack& CHEvent::pack(CPack& aPack)
{
	GTHEvent::pack(aPack);

	aPack << typeEvent;
	aPack << orderEvent;
	aPack << mode;
	aPack << twoBronces;
	aPack << reqRankOrder;
	aPack << idTeamMatchsCnfg;
	aPack << constRating;
	aPack << pointsBye;
	
	return aPack;
}

CPack& CHEvent::unpack(CPack& aPack)
{
	GTHEvent::unpack(aPack);

	aPack >> typeEvent;
	aPack >> orderEvent;
	aPack >> mode;
	aPack >> twoBronces;
	aPack >> reqRankOrder;
	aPack >> idTeamMatchsCnfg;
	aPack >> constRating;
	aPack >> pointsBye;
	
	return aPack;
}
//Set's
void CHEvent::setTypeEvent(const short value)
{
	typeEvent=value;
}

void CHEvent::setOrderEvent(const short value)
{
	orderEvent=value;
}
void CHEvent::setMode(const short value)
{
	mode=value;
}

void CHEvent::setTwoBronces(const short value)
{
	twoBronces=value;
}

//son enum RankOrder guardados condos caractereres
void CHEvent::setReqRankOrder(const RWCString value)
{
	reqRankOrder=value;
}

void CHEvent::setIdTeamMatchsCnfg(const short value)
{ 
	idTeamMatchsCnfg=value;
}
void CHEvent::setConstRating(const float value)
{ 
	constRating=value;
}
void CHEvent::setPointsBye(const float value)
{ 
	pointsBye=value;
}

//Get´s
short CHEvent::getTypeEvent() const
{
	return typeEvent;
}

short CHEvent::getOrderEvent() const
{
	return orderEvent;
}
short CHEvent::getMode() const
{
	return mode;
}
short CHEvent::getTwoBronces() const
{
	return twoBronces;
}

//son enum RankOrder guardados condos caractereres
RWCString CHEvent::getReqRankOrder() const
{
	return reqRankOrder;
}

short CHEvent::getIdTeamMatchsCnfg() const
{ 
	return idTeamMatchsCnfg;
}
float CHEvent::getConstRating() const
{ 
	return constRating;
}
float CHEvent::getPointsBye() const
{ 
	return pointsBye;
}

RWCString CHEvent::getConstRatingStr() const
{
	RWCString format="##";
	float auxRating=getConstRating();

	if((auxRating-int(auxRating))>0)
	{
		format="###.#"; // Decimales
		
	}

	GScore ratingF = GScore(auxRating);
	RWCString p=ratingF.asString(format);
	
	p=p.strip(RWCString::leading,' ');
	return p;
}

RWCString CHEvent::getPointsByeStr() const
{
	RWCString format="##";
	float aux=getPointsBye();

	if((aux-int(aux))>0)
		format="###.#"; // Decimales		
	
	GScore points = GScore(aux);
	RWCString p=points.asString(format);
	
	p=p.strip(RWCString::leading,' ');
	return p;
}

short CHEvent::getInscriptions() const
{
	
	RWSet * colInscriptions = (RWSet *) CHMemoryDataBase::getColInscriptions().select(inscriptionsEvent,(void *)this);

	short nInsc=short(colInscriptions->entries());
	
	delete colInscriptions;

	return nInsc;
}

int CHEvent::getTeamMembers() const
{
	if(getMode()==eTeam)
		return getTeamMatchsCnfgMembers(); //+1 para el recambio

	return 0;

}

short CHEvent::getTeamMatchsCnfgMembers() const
{
	CHTeamMatchsCnfg *pTeamMatchsCnfg=(CHTeamMatchsCnfg *)CHMemoryDataBase::findTeamMatchsCnfg(idTeamMatchsCnfg);
	if (pTeamMatchsCnfg)
		return pTeamMatchsCnfg->getCompetitors();
	return 0;
}

short CHEvent::getTeamMatches() const
{
	CHTeamMatchsCnfg *pTeamMatchsCnfg=(CHTeamMatchsCnfg *)CHMemoryDataBase::findTeamMatchsCnfg(idTeamMatchsCnfg);
	if (pTeamMatchsCnfg)
		return pTeamMatchsCnfg->getMatches();

	return 1;
}
//////////////////////////////////////////////////////////////////////
//Vector Methods
//////////////////////////////////////////////////////////////////////

RWBoolean CHEvent::isTeam() const
{
	if (getMode()==eTeam)
		return true;
	return false;
}
//////////////////////////////////////////////////////////////////////
// Help Methods
//////////////////////////////////////////////////////////////////////

//son enum RankOrder guardados condos caractereres
CHEvent::TypeRank CHEvent::getRankOrder(short index) const
{
	RWCString rankOrder;
	if(getNumRankOrder()>index)
		rankOrder=getReqRankOrder()(index*2,2);

	return CHEvent::TypeRank(atoi(rankOrder));
}

//son enum RankOrder guardados condos caractereres
short CHEvent::getNumRankOrder() const
{
	int n=getReqRankOrder().length();
	if(n)
		return short(n/2);
	return 0;
}

RWBoolean CHEvent::findRankOrder(CHEvent::TypeRank rankType) const
{
	short nRanks=getNumRankOrder();
	for(short i=0 ; i<nRanks ; i++)
	{
		CHEvent::TypeRank rankOrder=getRankOrder(i);

		if(rankOrder==rankType)
			return true;
	}
	return false;
}

CPack& operator << (CPack& aPack, CHEvent *pEvent)
{
	aPack << (pEvent ? pEvent->getEvent() : "");
	aPack << (pEvent ? pEvent->getSex() : "");
	aPack << (pEvent ? pEvent->getEventParent() : "");

	return aPack;
}

CPack& operator >> (CPack& aPack, CHEvent **pEvent)
{
	RWCString event,sex,eventP;

	aPack >> event;
	aPack >> sex;
	aPack >> eventP;
	*pEvent=(CHEvent*)GMemoryDataBase::findEvent(event,sex,eventP);

	return aPack;
}

