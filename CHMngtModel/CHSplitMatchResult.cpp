/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHSplitMatchResult.cpp                                                                 
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:13-12-2005
*   Project     :CH Model
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///


#include "stdCHMngt.h"
#include "CHSplitMatchResult.h"
#include "CHMatchResult.h"
#include "CHClassIds.h"
#include "UCHSplitMatchResult.h"
#include <core/G/GBuffer.h>

RWDEFINE_COLLECTABLE(CHSplitMatchResult, __CHSPLITMATCHRESULT)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHSplitMatchResult::CHSplitMatchResult()
:GTHSplitMatchResult()
{
}
CHSplitMatchResult::CHSplitMatchResult(GTHMatchResult* aMatchResult, short aSplit)
:GTHSplitMatchResult(aMatchResult, aSplit)
{
}

CHSplitMatchResult::CHSplitMatchResult(const CHSplitMatchResult & copy)
{
	operator=(copy);
}

CHSplitMatchResult::CHSplitMatchResult(CPack& aPack)
:GTHSplitMatchResult()
{
	unpack(aPack);
}

CHSplitMatchResult::~CHSplitMatchResult()
{

}

//////////////////////////////////////////////////////////////////////
// Operators
//////////////////////////////////////////////////////////////////////
CHSplitMatchResult & CHSplitMatchResult::operator =(const CHSplitMatchResult & copy)
{
	if (this != &copy)
	{
		GTHSplitMatchResult::operator =(copy);

		
	}
	return * this;
}

RWBoolean CHSplitMatchResult::operator ==(const CHSplitMatchResult & copy)
{
	if (this == &copy)
		return true;
	else
		return (GTHSplitMatchResult::operator ==(copy)	);
}

RWBoolean CHSplitMatchResult::operator !=(const CHSplitMatchResult & copy)
{
	return !operator==(copy);
}


//////////////////////////////////////////////////////////////////////
// From GData
//////////////////////////////////////////////////////////////////////
RWBoolean CHSplitMatchResult::uSQL(RWDBConnection& pConnect,RWBoolean remove /*=false*/ )
{
	RWBoolean rc=false;

	UCHSplitMatchResult upd(&pConnect);

	if( remove )  rc=upd.remove(*this);
	else          rc=upd.set   (*this);

	return rc;
}

CPack& CHSplitMatchResult::pack(CPack& aPack)
{
	GTHSplitMatchResult::pack(aPack);
		
	return aPack;
}

CPack& CHSplitMatchResult::unpack(CPack& aPack)
{
	GTHSplitMatchResult::unpack(aPack);
	
	return aPack;
}

RWCString CHSplitMatchResult::msl() const
{
	RWCString str = GTHSplitMatchResult::msl();

	GBuffer aBuffer;

	return str +  RWCString (aBuffer 	<< endLine
									 );
}

RWCString CHSplitMatchResult::mslDescription(const char *language) const
{
	return GTHSplitMatchResult::mslDescription(language);
}


//////////////////////////////////////////////////////////////////////
// Sets
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Gets
//////////////////////////////////////////////////////////////////////

CHSplitMatch * CHSplitMatchResult::getSplitMatch() const
{
	CHSplitMatch *pSplitMatch=0;
	CHMatch *pMatch=(CHMatch*)getMatch();
	pSplitMatch=(CHSplitMatch*)pMatch->getSplitMatch(getSplit()-1);
	return pSplitMatch;
}

unsigned char CHSplitMatchResult::getSplitMatchStatus()const
{
	CHSplitMatch * pSplitMatch=getSplitMatch();
	if(pSplitMatch)
		return pSplitMatch->getStatus();

	return 0;
}

CHSplitMatchResult *CHSplitMatchResult::getSplitMatchResultVersus()
{
	CHMatchResult *pMatchResultVersus=((CHMatchResult*)getMatchResult())->getMatchResultVersus();
	if(pMatchResultVersus)
	{
		return (CHSplitMatchResult*)pMatchResultVersus->getSplitMatchResult(getSplit()-1);
	}
	return 0;
}

CPack& operator << (CPack& aPack, CHSplitMatchResult * pSplitMatchResult)
{
	aPack << (pSplitMatchResult ? pSplitMatchResult->getMatchResult() : (CHMatchResult *) NULL);
	aPack << (pSplitMatchResult ? pSplitMatchResult->getSplit() : short (-1));
	return aPack;
}

CPack& operator >> (CPack& aPack, CHSplitMatchResult ** pSplitMatchResult)
{
	GTHEvent aEvent;
	GTHPhase aPhase;
	GTHPool aPool;
	GTHMatch aMatch;
	GTHMatchResult aMatchResult;
	RWCString event,sex,eventP,phase;
	short codePool=-1,matchCode=-1,matchPosition=-1,split=-1;

	aPack >> event;
	aPack >> sex;
	aPack >> eventP;
	aPack >> phase;
	aPack >> codePool;
	aPack >> matchCode;
	aPack >> matchPosition;
	aPack >> split;

	aEvent.setEvent(event);
	aEvent.setSex(sex);
	aEvent.setEventParent(eventP);
	aPhase.setEvent(&aEvent);
	aPhase.setPhase(phase);
	aPool.setPhase(&aPhase);
	aPool.setPool(codePool);
	aMatch.setPool(&aPool);
	aMatch.setCode(matchCode);
	aMatchResult.setMatch(&aMatch);
	aMatchResult.setPosition(matchPosition);
	*pSplitMatchResult=(CHSplitMatchResult*)CHMemoryDataBase::findSplitMatchResult(&aMatchResult,split);
	return aPack;
}




