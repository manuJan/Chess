/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confm_idential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be consm_idered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHTeamMatchsCnfg.cpp
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
#include "CHTeamMatchsCnfg.h"
#include "QCHTeamMatchsCnfg.h"
#include "UCHTeamMatchsCnfg.h"
#include <ovr/core/G/GBuffer.h>

MSLDEFINE_ITEM(CHTeamMatchsCnfg, __CHTEAMMATCHSCNFG)

	//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHTeamMatchsCnfg::CHTeamMatchsCnfg()
:m_id(0)
,m_nMatches(0)
,m_nMatchesEliminatory(0)
,m_nCompetitors(0)
,m_matchesType("")
,m_compMatchesDistribution("")
,m_matchesTypeElim("")
,m_fAwayChar("")
{
	setKey();
}

CHTeamMatchsCnfg::CHTeamMatchsCnfg(short code)
:m_id(code)
,m_nMatches(0)
,m_nMatchesEliminatory(0)
,m_nCompetitors(0)
,m_matchesType("")
,m_compMatchesDistribution("")
,m_matchesTypeElim("")
,m_fAwayChar("")
{
	setKey();
}

CHTeamMatchsCnfg::CHTeamMatchsCnfg(const CHTeamMatchsCnfg & copy)
{
	operator=(copy);
}

CHTeamMatchsCnfg::~CHTeamMatchsCnfg()
{
}

//Operator
bool CHTeamMatchsCnfg::operator !=(const GData & copy)
{
	return !operator==(copy);
}

bool CHTeamMatchsCnfg::operator ==(const GData & copy)
{
	if (this == &copy)
		return true;

	const CHTeamMatchsCnfg & teamMatchsCnfg=(const CHTeamMatchsCnfg &) copy;
	
	return ( m_id						== teamMatchsCnfg.m_id						&&
			 m_nMatches					== teamMatchsCnfg.m_nMatches				&&
			 m_nMatchesEliminatory		== teamMatchsCnfg.m_nMatchesEliminatory		&&
			 m_nCompetitors				== teamMatchsCnfg.m_nCompetitors			&&
			 m_matchesType				== teamMatchsCnfg.m_matchesType				&&
			 m_matchesTypeElim			== teamMatchsCnfg.m_matchesTypeElim			&&
			 m_compMatchesDistribution	== teamMatchsCnfg.m_compMatchesDistribution	&&			 
			 m_desc					    == teamMatchsCnfg.m_desc					&&
			 m_fAwayChar				== teamMatchsCnfg.m_fAwayChar				 );
}

GData & CHTeamMatchsCnfg::operator =(const GData & copy)
{
	if (this != &copy)
	{
		const CHTeamMatchsCnfg & teamMatchsCnfg=(const CHTeamMatchsCnfg &) copy;

		m_id				= teamMatchsCnfg.m_id;
		m_nMatches			= teamMatchsCnfg.m_nMatches;
		m_nMatchesEliminatory	= teamMatchsCnfg.m_nMatchesEliminatory;
		m_nCompetitors		= teamMatchsCnfg.m_nCompetitors;
		m_matchesType		= teamMatchsCnfg.m_matchesType;
		m_matchesTypeElim	= teamMatchsCnfg.m_matchesTypeElim;
		m_compMatchesDistribution	= teamMatchsCnfg.m_compMatchesDistribution;		
		m_desc				= teamMatchsCnfg.m_desc;
		m_fAwayChar			= teamMatchsCnfg.m_fAwayChar;

		
	}
	return * this;
}

void CHTeamMatchsCnfg::setKey()
{
	char aux[10];
	sprintf_s(aux,"%.3d",m_id);
	key=MSLString(aux);
}

QBase* CHTeamMatchsCnfg::onQ() const
{
	return new QCHTeamMatchsCnfg();
}

UBase* CHTeamMatchsCnfg::onU() const
{
	return new UCHTeamMatchsCnfg();
}

MSLPack& CHTeamMatchsCnfg::pack(MSLPack& aPack) const
{
	aPack << m_id;
	aPack << m_nMatches	;
	aPack << m_nMatchesEliminatory;
	aPack << m_nCompetitors	;
	aPack << m_matchesType	;
	aPack << m_matchesTypeElim	;
	aPack << m_compMatchesDistribution	;
	aPack << m_desc;
	aPack << m_fAwayChar;

	return aPack;
}

MSLPack& CHTeamMatchsCnfg::unpack(MSLPack &aPack)
{
	aPack >> m_id	;
	aPack >> m_nMatches	;
	aPack >> m_nMatchesEliminatory;
	aPack >> m_nCompetitors	;
	aPack >> m_matchesType	;
	aPack >> m_matchesTypeElim	;
	aPack >> m_compMatchesDistribution	;
	aPack >> m_desc;
	aPack >> m_fAwayChar;
	
	return aPack;
}
//Set
void CHTeamMatchsCnfg::setId(const short value)
{ 
	m_id=value;
	setKey();
}

void CHTeamMatchsCnfg::setMatches(const short value)
{ 
	m_nMatches=value;
}

void CHTeamMatchsCnfg::setMatchesElim(const short value)
{
	m_nMatchesEliminatory = value;
}

void CHTeamMatchsCnfg::setCompetitors(const short value)
{ 
	m_nCompetitors=value;
}

void CHTeamMatchsCnfg::setMatchesType(const char *value)
{ 
	m_matchesType=value;
}

void CHTeamMatchsCnfg::setCompMatchesDistribution(const char *value)
{ 
	m_compMatchesDistribution=value;
}

void CHTeamMatchsCnfg::setMatchesTypeElim(const char *value)
{ 
	m_matchesTypeElim=value;
}

void CHTeamMatchsCnfg::setDescriptions(GDescription & desc)
{
	m_desc.set(desc);	
}

void CHTeamMatchsCnfg::setFAwayC(const char *value)
{
	m_fAwayChar = value;
}
//Get
short CHTeamMatchsCnfg::getId() const
{ 
	return m_id;
}

short CHTeamMatchsCnfg::getMatches() const
{ 
	return m_nMatches;
}

short CHTeamMatchsCnfg::getMatchesElim() const
{
	return m_nMatchesEliminatory;
}

short CHTeamMatchsCnfg::getCompetitors() const
{ 
	return m_nCompetitors;
}

MSLString CHTeamMatchsCnfg::getMatchesType() const
{ 
	return m_matchesType;
}

MSLString CHTeamMatchsCnfg::getCompMatchesDistribution() const
{ 
	return m_compMatchesDistribution;
}

MSLString CHTeamMatchsCnfg::getMatchesTypeElim() const
{ 
	return m_matchesTypeElim;
}

GDescriptions& CHTeamMatchsCnfg::getDescriptions() const
{
	return (GDescriptions&)m_desc;
}


short CHTeamMatchsCnfg::getMatchType(short value) const
{
	if (value*2>int(m_matchesType.length()))
		return -1; //error

	MSLString aux(m_matchesType(value*2-1,1));
	int val=atoi(aux);
	if (val!=1 && val!=2)
		return -1;
	
	return short(val);
}

short CHTeamMatchsCnfg::getCompOrder(short value,short homeAway,short firstSecond/*=0*/) const
{
	MSLString matComp="";
	if (getMatchType(value)==-1) //error o none
		return -1;

	int pos=(homeAway==1)*2+(firstSecond==1);
/*	MSLString comp=MSLString(m_compMatchesDistribution).Mid(value*5-4+pos,1);
	MSLString first=_T("@");
	if (homeAway==1)
	{ 
		first=char(m_fAwayChar(0)-1);//_T("W");
	}

	char aux1=char(comp.GetAt(0));
	char aux=char(first.GetAt(0));
	pos=aux1-aux;
	if (pos>m_nCompetitors || pos<0)
		return -1;*/

	return short(pos);
}

short CHTeamMatchsCnfg::getCompMember(short homeAway) const
{
	/*CString home(""), away("");
	int pos=0;
	for (short i=0; i<m_nMatches; i++)
	{
		for (short j=0; j<2; j++)
		{
			pos=(homeAway==1)*2+(j==1);
			CString comp=CString(m_compMatchesDistribution).Mm_id(((i+1)*5)-4+pos,1);
			if (comp.Find(' ',0)!=-1)
				continue;
			if (homeAway==1)
			{
				if (away.Find(comp,0)==-1)
					away=away+comp;
			}
			else
			{
				if (home.Find(comp,0)==-1)
					home=home+comp;
			}
		}
	}
	if (homeAway==0)
	{
		if (!home.GetLength())
			return 0;
		return short(home.GetLength());
	}
	if (homeAway==1)
	{
		if (!away.GetLength())
			return 0;
		return short(away.GetLength());
	}*/
	return 0;
}

MSLWString CHTeamMatchsCnfg::getSDescription(const char *lang/*=0*/)  const
{
	return m_desc.get(lang,_SNAME);	
}

MSLWString CHTeamMatchsCnfg::getLDescription(const char *lang/*=0*/)  const
{
	return m_desc.get(lang,_LNAME);	
}

MSLString CHTeamMatchsCnfg::getFAwayC() const
{
	return m_fAwayChar;
}