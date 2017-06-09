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
#include "CHInscription.h"
#include "CHMemoryDataBase.h"
#include "QCHEvent.h"
#include "UCHEvent.h"
#include <ovr/core/G/GScore.h>

//select
bool inscriptionsEvent(const MSLItem *col, const void *param)
{
	CHInscription *pInscription = (CHInscription*)col;
	CHEvent *pEvent = (CHEvent *)param;
	
	if(pInscription->getEvent()->getKey() == pEvent->getKey())
		return true;
	return false;	
}

MSLDEFINE_ITEM(CHEvent,__CHEVENT)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHEvent::CHEvent()
:GTHEvent()
,m_typeEvent(eNone)
,m_twoBronces(0)
,m_reqRankOrder(NULLSTRING)
,m_idTeamMatchsCnfg(0)
,m_constRating(0.0)
,m_pointsBye(0.0)
,m_codeReports(NULLSTRING)
{
}

CHEvent::CHEvent(const CHEvent & copy)
{
	operator=(copy);
}


CHEvent::~CHEvent()
{

}

GData & CHEvent::operator =(const GData & copy)
{
	if (this != &copy)
	{
		GTHEvent::operator =(copy);

		const CHEvent & aEvent=(const CHEvent &) copy;

		m_typeEvent			= aEvent.m_typeEvent;
		m_twoBronces		= aEvent.m_twoBronces;
		m_reqRankOrder		= aEvent.m_reqRankOrder;
		m_idTeamMatchsCnfg	= aEvent.m_idTeamMatchsCnfg;
		m_constRating		= aEvent.m_constRating;
		m_pointsBye			= aEvent.m_pointsBye;		
		m_codeReports		= aEvent.m_codeReports;
	}
	return * this;
}

bool CHEvent::operator==(const GData & copy)
{
	if (this == &copy)
		return true;
	
	const CHEvent & aEvent=(const CHEvent &) copy;

	return (GTHEvent::operator	==(copy)						&& 			
			m_twoBronces		== aEvent.m_twoBronces			&&
			m_reqRankOrder		== aEvent.m_reqRankOrder		&&
			m_idTeamMatchsCnfg	== aEvent.m_idTeamMatchsCnfg	&&
			m_constRating		== aEvent.m_constRating			&&
			m_pointsBye			== aEvent.m_pointsBye			&&
			m_codeReports		== aEvent.m_codeReports			);
}

bool CHEvent::operator!=(const GData & copy)
{
	return !operator==(copy);
}

MSLPack& CHEvent::pack(MSLPack& aPack) const
{
	GTHEvent::pack(aPack);

	aPack << m_typeEvent;	
	aPack << m_twoBronces;
	aPack << m_reqRankOrder;
	aPack << m_idTeamMatchsCnfg;
	aPack << m_constRating;
	aPack << m_pointsBye;
	aPack << m_codeReports;
	
	return aPack;
}

MSLPack& CHEvent::unpack(MSLPack& aPack)
{
	GTHEvent::unpack(aPack);

	aPack >> m_typeEvent;	
	aPack >> m_twoBronces;
	aPack >> m_reqRankOrder;
	aPack >> m_idTeamMatchsCnfg;
	aPack >> m_constRating;
	aPack >> m_pointsBye;
	aPack >> m_codeReports;
	
	return aPack;
}

QBase* CHEvent::onQ() const
{
	return new QCHEvent();
}

UBase* CHEvent::onU() const
{
	return new UCHEvent();
}

//Set's
void CHEvent::setTypeEvent(const short value)
{
	m_typeEvent=value;
}

void CHEvent::setTwoBronces(const short value)
{
	m_twoBronces=value;
}

//son enum RankOrder guardados condos caractereres
void CHEvent::setReqRankOrder(const MSLString value)
{
	m_reqRankOrder=value;
}

void CHEvent::setIdTeamMatchsCnfg(const short value)
{ 
	m_idTeamMatchsCnfg=value;
}
void CHEvent::setConstRating(const double value)
{ 
	m_constRating=value;
}
void CHEvent::setPointsBye(const double value)
{ 
	m_pointsBye=value;
}

void CHEvent::setCodeReports(const MSLString value)
{
	m_codeReports = value;
}

//Get´s
short CHEvent::getTypeEvent() const
{
	return m_typeEvent;
}

short CHEvent::getTwoBronces() const
{
	return m_twoBronces;
}

//son enum RankOrder guardados condos caractereres
MSLString CHEvent::getReqRankOrder() const
{
	return m_reqRankOrder;
}

short CHEvent::getIdTeamMatchsCnfg() const
{ 
	return m_idTeamMatchsCnfg;
}
double CHEvent::getConstRating() const
{ 
	return m_constRating;
}
double CHEvent::getPointsBye() const
{ 
	return m_pointsBye;
}

MSLString CHEvent::getCodeReports() const
{
	return m_codeReports;		
}

MSLString CHEvent::getConstRatingStr() const
{
	MSLString format="##";
	double auxRating=getConstRating();

	if((auxRating-int(auxRating))>0)
		format="###.#"; // Decimales		
	
	GScore ratingF = GScore(auxRating);
	MSLString p=ratingF.asString(format);
	
	p=p.strip(MSLString::leading,' ');
	return p;
}

MSLString CHEvent::getPointsByeStr() const
{
	MSLString format="##";
	double aux=getPointsBye();

	if((aux-int(aux))>0)
		format="###.#"; // Decimales		
	
	GScore points = GScore(aux);
	MSLString p=points.asString(format);
	
	p=p.strip(MSLString::leading,' ');
	return p;
}

MSLWString CHEvent::getTypeEventAsString() const
{
	switch (getTypeEvent())
	{
		case eNone:
			return "";
		case eClassic:
			return "Classical";
		case eRapid:
			return "Rapid";
		case eBlitz:
			return "Blitz";
	}

	return NULLWSTRING;
}

MSLWString CHEvent::getRegTypeAsString	() const
{
	GRegType * pRegType = CHMemoryDataBase::findRegType( GRegister::TypeRegister( getRegType()));
	return  (pRegType) ? pRegType->getLDescription() : NULLWSTRING;
}

short CHEvent::getInscriptions() const
{	
	MSLSet colInscriptions = CHMemoryDataBase::getCol(__CHINSCRIPTION).select(inscriptionsEvent, (CHEvent*)this);

	short nInsc=short(colInscriptions.entries());
	
	return nInsc;
}

int CHEvent::getTeamMembers() const
{
	if(isTeam())
		return getTeamMatchsCnfgMembers(); //+1 para el recambio

	return 0;

}

short CHEvent::getTeamMatchsCnfgMembers() const
{
	CHTeamMatchsCnfg *pTeamMatchsCnfg=(CHTeamMatchsCnfg *)CHMemoryDataBase::findTeamMatchsCnfg(m_idTeamMatchsCnfg);
	if (pTeamMatchsCnfg)
		return pTeamMatchsCnfg->getCompetitors();
	return 0;
}

short CHEvent::getTeamMatches() const
{
	CHTeamMatchsCnfg *pTeamMatchsCnfg=(CHTeamMatchsCnfg *)CHMemoryDataBase::findTeamMatchsCnfg(m_idTeamMatchsCnfg);
	if (pTeamMatchsCnfg)
		return pTeamMatchsCnfg->getMatches();

	return 1;
}
//////////////////////////////////////////////////////////////////////
//Vector Methods
//////////////////////////////////////////////////////////////////////

bool CHEvent::isTeam() const
{
	return getRegType()==GRegister::team;
}

bool CHEvent::getSubMatches() const
{
	return isTeam();
}

//////////////////////////////////////////////////////////////////////
// Help Methods
//////////////////////////////////////////////////////////////////////

//son enum RankOrder guardados condos caractereres
CHEvent::TypeRank CHEvent::getRankOrder(short index) const
{
	MSLString rankOrder;
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

bool CHEvent::findRankOrder(CHEvent::TypeRank rankType) const
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

int CHEvent::getRankPosition(CHEvent::TypeRank rankType)
{
	short nRanks=getNumRankOrder();
	for(short i=0 ; i<nRanks ; i++)
	{
		CHEvent::TypeRank rankOrder=getRankOrder(i);
		if(rankOrder==rankType)
			return i;
	}
	return 0;
}

MSLWString CHEvent::getTeamCfgSDescription(const char * language)
{
	CHTeamMatchsCnfg *pTeamMatchsCnfg=(CHTeamMatchsCnfg *)CHMemoryDataBase::findTeamMatchsCnfg(m_idTeamMatchsCnfg);
	if (pTeamMatchsCnfg)
		return pTeamMatchsCnfg->getSDescription(language);

	return NULLWSTRING;
}

MSLWString CHEvent::getTeamCfgLDescription(const char * language)
{
	CHTeamMatchsCnfg *pTeamMatchsCnfg=(CHTeamMatchsCnfg *)CHMemoryDataBase::findTeamMatchsCnfg(m_idTeamMatchsCnfg);
	if (pTeamMatchsCnfg)
		return pTeamMatchsCnfg->getLDescription(language);

	return NULLWSTRING;
}

MSLString CHEvent::getCfgTeamMembers() const
{
	CHTeamMatchsCnfg *pTeamMatchsCnfg=(CHTeamMatchsCnfg *)CHMemoryDataBase::findTeamMatchsCnfg(m_idTeamMatchsCnfg);
	if (pTeamMatchsCnfg)
		return pTeamMatchsCnfg->getMatchesType();

	return NULLSTRING;
}