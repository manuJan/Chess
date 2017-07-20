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

#pragma once
#include "CHMemoryDataBaseDefs.h"
#include <Ovr/Core/TH/GTHMatchResult.h>

class CHPhase;
class CHMatch;
class CHInscription;
class CHPoolResult;
class CHMatchResult;

class CHMngtModelExport CHMatchResult : public GTHMatchResult  
{
	MSLDECLARE_ITEM(CHMatchResult)

public:
	enum side {eNone=-1, eWhite=0, eBlack=1};
	enum colorPreference {eDraw=0, eWhiteAbsolut=1, eWhiteStrong=2, eWhiteModerate=3, eBlackAbsolut=4, eBlackStrong=5, eBlackModerate=6};


	CHMatchResult();
	CHMatchResult(CHMatch * match,short pos);
	CHMatchResult(const CHMatchResult& copy);	
	virtual ~CHMatchResult();

	//Operators
	GData& operator= (const GData & copy);
	bool   operator==(const GData & copy);
	bool   operator!=(const GData & copy);

	/**** Virtual methods inherited from MSLItem ********************/
	virtual MSLPack& pack  (MSLPack& pck) const;
	virtual MSLPack& unpack(MSLPack& pck);

	//Virtual methods inherited from GData
	QBase*			onQ() const;
	UBase*			onU() const;

	// SETS
	void setPoints(const float value);
	void setUpFloater(const bool value);
	void setDownFloater(const bool value);
	void setColor(const short value);

	// GETS
	short getColor() const;
	float getPoints() const;
	MSLString getPointsAsString() const;
	bool getUpFloater() const;
	bool getDownFloater() const;
		
	MSLString getColorSDesc() const;
	MSLString getColorLDesc() const;

	bool isQualitative() const;
	int getTeamMembers() const;
	CHMatchResult*	getMatchResultVersus();
	bool areTeams() const;
	short getTeamMatchesWon() const;
	short getSeed();
	MSLString getSeedAsString();
	float getPointsSO();
	double getMatchPoints() const;
	MSLString getMatchPointsAsString() const;

	int  getColorRGB();
	
	short getColorVersus();
	MSLString getColorVersusSDesc() const;
	MSLString getColorVersusLDesc() const;

	MSLString		getPreviousMatchesAsString(CHMatch* pMatch);
	void			getPreviousMatchesVector(MSLSortedVector &vMatchResults, CHMatch* _pMatch);

	MSLWString		getSName(const char *lang=0) const;
	MSLWString		getLName(const char *lang=0) const;

	MSLWString		getMatchMemberLDescription() const;
	MSLWString		getMatchMemberSDescription() const;
	
	MSLString		getMatchMemberAcreditation() const;
	MSLString		getAcreditation_CH() const;

	bool			isRankEqual() const;
		
	CHPoolResult*	getSwissRoundResult();
	MSLString		getSwissRoundScore();
	short			getSwissRoundRank();
	short			getMatchRound();

	// Progressions
	CHPhase*		getPhaseSource() const;		// de donde viene en la progresión
	CHMatchResult*	getSourceByInscription();	// de donde viene en la progresión
	CHMatchResult*	getSourceByProgression();	// de donde viene en la progresión
	CHMatchResult*	getTargetByInscription();	// a donde va en la progresión
	void			getTargetByProgression(MSLSet &colMatchResults);	// a donde va en la progresión

	CHMatchResult*	findMatchResult(GRegister * pRegister) const;
	CHMatchResult*	findMatchResult(CHInscription *pInscription) const;
	CHMatchResult*	findMatchResultByProgression(CHMatchResult * pMatchResult) const;

	// select function
	mslToolsFcSelect getSelectFn(const GData *pData);

private:

	float	  m_points;				// Numero de puntos ganados
	bool	  m_upFloater;
	bool	  m_downFloater;
	short	  m_color;				// color de fichas
};
