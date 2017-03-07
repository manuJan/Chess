/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
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
#include "CHClassIDs.h"
#include "UCHTeamMatchsCnfg.h"
#include <core/G/GBuffer.h>

RWDEFINE_COLLECTABLE(CHTeamMatchsCnfg, __CHTEAMMATCHSCNFG)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHTeamMatchsCnfg::CHTeamMatchsCnfg()
:id(0)
,nMatches(0)
,nCompetitors(0)
,matchesType("")
,compMatchesDistribution("")
,names()
,fAwayChar("")
{
	setKey();
}

CHTeamMatchsCnfg::CHTeamMatchsCnfg(short code)
:id(code)
,nMatches(0)
,nCompetitors(0)
,matchesType("")
,compMatchesDistribution("")
,names()
,fAwayChar("")
{
	setKey();
}

CHTeamMatchsCnfg::CHTeamMatchsCnfg(const CHTeamMatchsCnfg & copy)
{
	operator=(copy);
}

CHTeamMatchsCnfg::CHTeamMatchsCnfg(CPack& aPack)
{
	unpack(aPack);
}

CHTeamMatchsCnfg::~CHTeamMatchsCnfg()
{
}

//Operator
RWBoolean CHTeamMatchsCnfg::operator !=(const CHTeamMatchsCnfg & copy)
{
	return !operator==(copy);
}

RWBoolean CHTeamMatchsCnfg::operator ==(const CHTeamMatchsCnfg & copy)
{
	if (this == &copy)
		return true;
	else
		return ( id			== copy.id	&&
				 nMatches	== copy.nMatches &&	
				 nCompetitors== copy.nCompetitors &&
				 matchesType	== copy.matchesType &&
				 compMatchesDistribution == copy.compMatchesDistribution &&
				 names==copy.names	&&
				 fAwayChar==copy.fAwayChar
				 );
}

CHTeamMatchsCnfg & CHTeamMatchsCnfg::operator =(const CHTeamMatchsCnfg & copy)
{
	if (this != &copy)
	{
		id			= copy.id;
		nMatches	= copy.nMatches;
		nCompetitors= copy.nCompetitors;
		matchesType	= copy.matchesType;
		compMatchesDistribution	= copy.compMatchesDistribution;
		names.clearAndDestroy();
		fAwayChar	= copy.fAwayChar;

		GNames* pNames=0;
		RWSetIterator iterator((RWSet&)copy.names);
		while( (pNames=(GNames*)iterator())!=0 ) 
			names.insert( new GNames(*pNames) );
		setKey();
	}
	return * this;
}

void CHTeamMatchsCnfg::setKey()
{
	char aux[10];
	sprintf(aux,"%.3d",id);
	key=RWCString(aux);
}

RWBoolean CHTeamMatchsCnfg::uSQL(RWDBConnection& pConnect,RWBoolean remove/*=false*/)
{
	RWBoolean rc=false;

	UCHTeamMatchsCnfg upd(&pConnect);

	if( remove )  rc=upd.remove(*this);
	else          rc=upd.set   (*this);

	return rc;
}

RWCString CHTeamMatchsCnfg::msl() const
{
	GBuffer aBuffer;

	return RWCString(	aBuffer	<< isA()
								<< getKey()
								<< nMatches
								<< nCompetitors
								<< matchesType
								<< compMatchesDistribution
								<< fAwayChar
								<< endLine);
}

RWCString CHTeamMatchsCnfg::mslDescription(const char *language) const
{
	return GData::mslDescription(language);
}

CPack& CHTeamMatchsCnfg::pack(CPack &aPack)
{
	size_t namesEntries = names.entries();
	GNames *pNames=0;
	aPack << id	;
	aPack << nMatches	;
	aPack << nCompetitors	;
	aPack << matchesType	;
	aPack << compMatchesDistribution	;
	aPack << namesEntries;
	aPack << fAwayChar;

	RWSetIterator it(names);
	while( (pNames=(GNames *)it())!=0 )
		pNames->pack(aPack);

	return aPack;
}

CPack& CHTeamMatchsCnfg::unpack(CPack &aPack)
{
	size_t namesEntries=0; 
	names.clearAndDestroy();
	aPack >> id	;
	aPack >> nMatches	;
	aPack >> nCompetitors	;
	aPack >> matchesType	;
	aPack >> compMatchesDistribution	;
	aPack >> namesEntries;
	aPack >> fAwayChar;
	
	for (size_t i = 0; i < namesEntries; i++)
		names.insert( new GNames(aPack) );

	setKey();

	return aPack;
}
//Set
void CHTeamMatchsCnfg::setId(const short value)
{ 
	id=value;
	setKey();
}

void CHTeamMatchsCnfg::setMatches(const short value)
{ 
	nMatches=value;
}

void CHTeamMatchsCnfg::setCompetitors(const short value)
{ 
	nCompetitors=value;
}

void CHTeamMatchsCnfg::setMatchesType(const char *value)
{ 
	matchesType=value;
}

void CHTeamMatchsCnfg::setCompMatchesDistribution(const char *value)
{ 
	compMatchesDistribution=value;
}

void CHTeamMatchsCnfg::setDescription(const GNames& description)
{
	GNames* pNames=(GNames*)names.find(&description);
	if( pNames ) 
		*pNames=description;
	else 
		names.insert(new GNames(description));
}

void CHTeamMatchsCnfg::setFAwayC(const char *value)
{
	fAwayChar = value;
}
//Get
short CHTeamMatchsCnfg::getId() const
{ 
	return id;
}

short CHTeamMatchsCnfg::getMatches() const
{ 
	return nMatches;
}

short CHTeamMatchsCnfg::getCompetitors() const
{ 
	return nCompetitors;
}

RWCString CHTeamMatchsCnfg::getMatchesType() const
{ 
	return matchesType;
}

RWCString CHTeamMatchsCnfg::getCompMatchesDistribution() const
{ 
	return compMatchesDistribution;
}

RWSet CHTeamMatchsCnfg::getNames() const
{ 
	return names;
}

short CHTeamMatchsCnfg::getMatchType(short value) const
{
	if (value*2>int(matchesType.length()))
		return -1; //error

	//int val=atoi(CString(matchesType).Mid(value*2-1,1));
	RWCString aux(matchesType(value*2-1,1));
	int val=atoi(aux);
//	CString aux=CString(matchesType).Mid(value*2-1,1);
//	char tmp=aux.GetAt(0);
//	int val=atoi(tmp);
	if (val!=1 && val!=2)
		return -1;
	
	return short(val);
}

short CHTeamMatchsCnfg::getCompOrder(short value,short homeAway,short firstSecond/*=0*/) const
{
	RWCString matComp="";
	if (getMatchType(value)==-1) //error o none
		return -1;

	int pos=(homeAway==1)*2+(firstSecond==1);
	CString comp=CString(compMatchesDistribution).Mid(value*5-4+pos,1);
	CString first=_T("@");
	if (homeAway==1)
	{ 
		first=char(fAwayChar(0)-1);//_T("W");
	}

	char aux1=char(comp.GetAt(0));
	char aux=char(first.GetAt(0));
	pos=aux1-aux;
	if (pos>nCompetitors || pos<0)
		return -1;

	return short(pos);
}

short CHTeamMatchsCnfg::getCompMember(short homeAway) const
{
	CString home(""), away("");
	int pos=0;
	for (short i=0; i<nMatches; i++)
	{
		for (short j=0; j<2; j++)
		{
			pos=(homeAway==1)*2+(j==1);
			CString comp=CString(compMatchesDistribution).Mid(((i+1)*5)-4+pos,1);
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
	}
	return 0;
}

RWWString CHTeamMatchsCnfg::getSDescription(const char *language/*=DBApplication::getAppLanguage()*/) const
{
	GNames aNames,*pNames=0;
	aNames.setCode(language);

	pNames=(GNames*)names.find(&aNames);
	if( pNames ) 
		return pNames->getSName();
	return NULLRWWSTRING;
}

RWWString CHTeamMatchsCnfg::getLDescription(const char *language/*=DBApplication::getAppLanguage()*/) const
{
	GNames aNames,*pNames=0;
	aNames.setCode(language);

	pNames=(GNames*)names.find(&aNames);
	if( pNames ) 
		return pNames->getLName();
	return NULLRWWSTRING;
}

RWCString CHTeamMatchsCnfg::getFAwayC() const
{
	return fAwayChar;
}