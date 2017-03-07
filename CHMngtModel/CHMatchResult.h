/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHMatchResult.h
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

#if !defined(AFX_CHMATCHRESULT_H__BD7CBAA8_FB44_40E4_9EF6_38FCBC1519E4__INCLUDED_)
#define AFX_CHMATCHRESULT_H__BD7CBAA8_FB44_40E4_9EF6_38FCBC1519E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHMNGTMODELDLL_H
#   include "CHMngtModelDll.h" 
#endif // _CH_MNGTMODELDLL_H



class CHMatch;
class CHMatchMember;

class CHModelExport CHMatchResult : public GTHMatchResult  
{
	RWDECLARE_COLLECTABLE(CHMatchResult)
public:
	enum side {eNone=-1, eWhite=0, eBlack=1};
	enum colorPreference {eDraw=0,eWhiteAbsolut=1,eWhiteStrong=2,eWhiteModerate=3,eBlackAbsolut=4,eBlackStrong=5,eBlackModerate=6};


	CHMatchResult();
	CHMatchResult(CHMatch * match,short pos);
	CHMatchResult(const CHMatchResult& copy);
	CHMatchResult(CPack& aPack);
	virtual ~CHMatchResult();
	//Operator
	CHMatchResult & operator = (const CHMatchResult & copy);
	RWBoolean operator == (const CHMatchResult & copy);
	RWBoolean operator != (const CHMatchResult & copy);

	RWBoolean uSQL(RWDBConnection& pConnect,RWBoolean remove=false);
	RWCString msl() const;
	RWCString mslDescription(const char *language) const;
	CPack& pack(CPack& aPack);
	CPack& unpack(CPack& aPack);

	// SETS
	void setPoints(const float value);
	void setUpFloater(const RWBoolean value);
	void setDownFloater(const RWBoolean value);
	void setColor(const short value);

	// GETS
	float getPoints() const;
	RWCString getPointsAsString() const;
	RWBoolean getUpFloater() const;
	RWBoolean getDownFloater() const;

	short getSubMatch() const;
	
	short getColor() const;
	RWCString getColorSDesc() const;
	RWCString getColorLDesc() const;

	short getMatchNumber() const;
	unsigned char getMatchStatus() const;
	int getTeamMembers() const;
	GSortedVector getSubMatches();
	CHMatchResult*	getMatchResultVersus();
	RWBoolean isHome() const;
	RWBoolean isQualitative() const;
	GSortedVector &getInscriptionMembersVector() const;
	RWBoolean areTeams() const;
	short getTeamMatchesWon();
	short getSeed();
	RWCString getSeedAsString();
	float getPointsSO();

	int  getColorRGB();
	
	short getColorVersus();
	RWCString getColorVersusSDesc() const;
	RWCString getColorVersusLDesc() const;

	// From CHMatchMember
	CHMatchMember *getMatchMember();
	RWWString		getMatchMemberLDescription();
	RWWString		getMatchMemberSDescription();

	RWCString		getPreviousMatchesAsString(CHMatch* pMatch);
	void			getPreviousMatchesVector(GSortedVector &vMatchResults,CHMatch* _pMatch);

private:
	float	  points;				// Numero de puntos ganados
	short	  color;				// color de fichas

	RWBoolean upFloater;
	RWBoolean downFloater;
};

#endif // !defined(AFX_CHMATCHRESULT_H__BD7CBAA8_FB44_40E4_9EF6_38FCBC1519E4__INCLUDED_)
