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

#pragma once
#include "CHMemoryDataBaseDefs.h"

class CHMngtModelExport CHTeamMatchsCnfg : public GData  
{
	MSLDECLARE_ITEM(CHTeamMatchsCnfg)

	enum cfgMatchType { cfgIndividual=1, cfgDoubles };

public:

	CHTeamMatchsCnfg();
	CHTeamMatchsCnfg(short code);
	CHTeamMatchsCnfg(const CHTeamMatchsCnfg & copy);	
	virtual ~CHTeamMatchsCnfg();

	/**** Virtual operators inherited from GData ********************/
	GData& operator= (const GData& copy);
	bool   operator==(const GData& copy);
	bool   operator!=(const GData& copy);
	
	/**** Virtual methods inherited from GData **********************/
	MSLPack& pack  (MSLPack& pck) const;
	MSLPack& unpack(MSLPack& pck);

	QBase*			onQ() const;
	UBase*			onU() const;
	void			setKey();

	//Set
	void setId(const short value);
	void setMatches(const short value);
	void setCompetitors(const short value);
	void setMatchesType(const char *value);
	void setCompMatchesDistribution(const char *value);
	void setDescriptions(GDescription& desc);
	void setFAwayC(const char *value);

	//Get
	short getId() const;
	short getMatches() const;
	short getCompetitors() const;
	MSLString getMatchesType() const;
	MSLString getCompMatchesDistribution() const;
	GDescriptions&  getDescriptions () const;
	short getMatchType(short value) const;
	short getCompOrder(short value,short homeAway,short firstSecond=0) const;
	short getCompMember(short homeAway) const;

	// Class Methods
	MSLWString getSDescription(const char *lang=0) const;
	MSLWString getLDescription(const char *lang=0) const;

	MSLString getFAwayC() const;

private:

	short m_id;
	short m_nMatches;
	short m_nCompetitors;
	MSLString m_matchesType;
	MSLString m_compMatchesDistribution;
	GDescriptions m_desc;
	MSLString m_fAwayChar;
};
