/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHTeamMatchsCnfg.h
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
#if !defined(AFX_CHTEAMMATCHSCNFG_H__512875F0_1B41_4367_884A_BB130F4B7B49__INCLUDED_)
#define AFX_CHTEAMMATCHSCNFG_H__512875F0_1B41_4367_884A_BB130F4B7B49__INCLUDED_

#ifndef _CHMNGTMODELDLL_H
#   include "CHMngtModelDll.h" 
#endif // _CH_MNGTMODELDLL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Core/G/GNames.h>
#include <Core/G/DBApplication.h>

class CHModelExport CHTeamMatchsCnfg : public GData  
{
	RWDECLARE_COLLECTABLE(CHTeamMatchsCnfg)
	enum cfgMatchType { cfgIndividual=1, cfgDoubles };
public:
	CHTeamMatchsCnfg();
	CHTeamMatchsCnfg(short code);
	CHTeamMatchsCnfg(const CHTeamMatchsCnfg & copy);
	CHTeamMatchsCnfg(CPack& aPack);
	virtual ~CHTeamMatchsCnfg();

//Operator
	RWBoolean operator !=(const CHTeamMatchsCnfg & copy);
	RWBoolean operator ==(const CHTeamMatchsCnfg & copy);
	CHTeamMatchsCnfg & operator =(const CHTeamMatchsCnfg & copy);

	void setKey();
	RWBoolean uSQL(RWDBConnection& pConnect,RWBoolean remove=false);
	RWCString msl() const;
	RWCString mslDescription(const char *language) const;
	CPack& pack(CPack &iPack);
	CPack& unpack(CPack &iPack);

	//Set
	void setId(const short value);
	void setMatches(const short value);
	void setCompetitors(const short value);
	void setMatchesType(const char *value);
	void setCompMatchesDistribution(const char *value);
	void setDescription(const GNames & description);
	void setFAwayC(const char *value);

	//Get
	short getId() const;
	short getMatches() const;
	short getCompetitors() const;
	RWCString getMatchesType() const;
	RWCString getCompMatchesDistribution() const;
	RWSet getNames() const;
	short getMatchType(short value) const;
	short getCompOrder(short value,short homeAway,short firstSecond=0) const;
	short getCompMember(short homeAway) const;
	RWWString getSDescription(const char *language=DBApplication::getAppLanguage()) const;
	RWWString getLDescription(const char *language=DBApplication::getAppLanguage()) const;
	RWCString getFAwayC() const;

private:
	short id;
	short nMatches;
	short nCompetitors;
	RWCString matchesType;
	RWCString compMatchesDistribution;
	RWSet names;
	RWCString fAwayChar;
};

#endif // !defined(AFX_CHTEAMMATCHSCNFG_H__512875F0_1B41_4367_884A_BB130F4B7B49__INCLUDED_)
