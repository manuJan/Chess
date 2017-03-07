/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHPool.h                                                                 
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:12-12-2005                                                                      
*   Project     :CH Model                                                                      
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///


#ifndef _CHPool_H
#define _CHPool_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef _CHMNGTMODELDLL_H
#   include "CHMngtModelDll.h" 
#endif // _CH_MNGTMODELDLL_H

#include <core/TH/GTHPool.h>


class CHModelExport CHPool : public GTHPool
{

	RWDECLARE_COLLECTABLE(CHPool)

public:

	//Construction/Destruction
	CHPool();
	CHPool(const CHPool & copy);
	CHPool(CPack& aPack);
	virtual ~CHPool();


	//Operators
	RWBoolean	operator !=(const CHPool & copy);
	RWBoolean	operator ==(const CHPool & copy);
	CHPool&		operator =(const CHPool & copy);


	//From GData
	RWBoolean	uSQL(RWDBConnection& pConnect,RWBoolean remove=false);
	CPack&		pack(CPack &iPack);
	CPack&		unpack(CPack &iPack);
	RWCString	msl() const;
	RWCString	mslDescription(const char *language) const;


	// Help Methods
	GTHPhase::DescriptionMode	getDescriptionMode() const;
	RWWString					getOrderAsString(GTHPhase::DescriptionMode mode=GTHPhase::eNumeric) const;

	RWWString getDescription(GTHPhase::DescriptionMode mode=GTHPhase::eNumeric,const char *language=DBApplication::getAppLanguage()) const;
	RWWString getSDescription(GTHPhase::DescriptionMode mode=GTHPhase::eText,const char *language=DBApplication::getAppLanguage()) const;
	RWWString getLDescription(GTHPhase::DescriptionMode mode=GTHPhase::eText,const char *language=DBApplication::getAppLanguage()) const;
	unsigned char getRoundStatus(short nRound);
	short getRoundMatches(short nRound);
	short getNumRoundsPlayed();

	bool		hasCompatibleColors(CHPoolResult* pPR1,CHPoolResult* pPR2, short round);
	RWBoolean	hasCompetitors();
};

#endif //!defined(AFX_CHPool_H)