/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHEvent.h                                                                 
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

#if !defined(AFX_CHEVENT_H__E55D37C2_311D_4FC3_A9F1_1890D1400119__INCLUDED_)
#define AFX_CHEVENT_H__E55D37C2_311D_4FC3_A9F1_1890D1400119__INCLUDED_

#ifndef _CHEvent_H
#define _CHEvent_H
#endif 

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHMNGTMODELDLL_H
#   include "CHMngtModelDll.h" 
#endif // _CH_MNGTMODELDLL_H

#include <CORE\TH\GTHEvent.h>

class CHModelExport CHEvent : public GTHEvent  
{

	RWDECLARE_COLLECTABLE(CHEvent)

enum TypeEvent {eNone=0, eClassic=1, eRapid=2, eBlitz=3};
enum TypeMode  {eNoneMode=0, eIndividual=1, eTeam=2};
enum TypeRank  {eEmpty=0, eQualitative=1, ePoints=2,eSolkoff=3, eSonneBerger=4, eMedianSolkoff=5, eProgressiveScore=6, eRating=7, eTeamMatchesWon=8, eMatchesWon=9, eMatchesDrawm=10,eTeamPointsWon=11  };


public:
	CHEvent();
	CHEvent(const CHEvent & copy);
	CHEvent(CPack & aPack);
	virtual ~CHEvent();

	CHEvent & operator  =(const CHEvent & copy);
	RWBoolean operator !=(const CHEvent & copy);
	RWBoolean operator ==(const CHEvent & copy);

	RWBoolean uSQL(RWDBConnection & pConnect,RWBoolean remove=false);
	RWCString msl() const;
	RWCString mslDescription(const char * language) const;
	CPack &   pack(CPack & aPack);
	CPack & unpack(CPack & aPack);

	//Set's
	void setTypeEvent		(const short value);
	void setOrderEvent		(const short value);
	void setTwoBronces		(const short value);
	void setMode			(const short value);
	void setReqRankOrder	(const RWCString value);
	void setIdTeamMatchsCnfg(const short value);
	void setConstRating		(const float value);
	void setPointsBye		(const float value);
	
	
	//Get´s
	short		getTypeEvent		() const;
	short		getOrderEvent		() const;
	short		getTwoBronces 		() const;
	short		getMode	 			() const;
	RWCString	getReqRankOrder		() const;
	short		getInscriptions		() const;
	int			getTeamMembers		() const;
	short		getIdTeamMatchsCnfg	() const;	
	float		getConstRating		() const;	
	RWCString	getConstRatingStr	() const;
	short		getTeamMatchsCnfgMembers() const;
	short		getTeamMatches		() const;
	float		getPointsBye		() const;
	RWCString	getPointsByeStr		() const;
	

	
	RWBoolean isTeam    () const;
/*	RWBoolean isValid   () const;*/

	
	// Help Methods
	CHEvent::TypeRank   getRankOrder(short index) const;
	short				getNumRankOrder() const;
	RWBoolean			findRankOrder(CHEvent::TypeRank rankType) const;
	
private:
	//Atributos
	short	typeEvent;	//tipo del evento: individual, dobles triple o cuatro	
	short	orderEvent,
			twoBronces, //0:no 1:si
			mode;		//1:individual 2:equipos
			
	RWCString reqRankOrder; //tipo de ordenacion para los ranking
	short idTeamMatchsCnfg;
	float constRating;
	float pointsBye;
	


};

CHModelExport CPack& operator << (CPack& aPack, CHEvent * pEvent);
CHModelExport CPack& operator >> (CPack& aPack, CHEvent ** pEvent);

#endif // !defined(AFX_CHEVENT_H__E55D37C2_311D_4FC3_A9F1_1890D1400119__INCLUDED_)
