/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : UCHPoolResult.h                                                                 
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


#ifndef _UCHPoolResult_H
#define _UCHPoolResult_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <core/TH/UGTHPoolResult.h>
#include "CHPoolResult.h"

class CHModelExport UCHPoolResult : public UGTHPoolResult
{
public:
	UCHPoolResult(RWDBConnection *pNewConnection)
		:UGTHPoolResult(pNewConnection)
		{;}
	virtual ~UCHPoolResult(){}

private:
	short matchesPlayed;
	short wonGames;
	short lostGames;
	short tieGames;
	float pointsF;
	float solkoff;
	float mediansolkoff;
	float sonneBerger;
	float progressiveScore;
		
	RWDBNullIndicator nullmatchesPlayed;
	RWDBNullIndicator nullwonGames;
	RWDBNullIndicator nulllostGames;
	RWDBNullIndicator nulltieGames;
	RWDBNullIndicator nullpointsF;
	RWDBNullIndicator nullsolkoff;
	RWDBNullIndicator nullmediansolkoff;
	RWDBNullIndicator nullsonneBerger;
	RWDBNullIndicator nullprogressiveScore;
	

	void OnAssignAttributes(GTHPoolResult& aPoolResult);
	void OnInsert(RWDBInserter& aInserter,GTHPoolResult& aPoolResult);
	void OnUpdate(RWDBUpdater& aUpdater,RWDBTable& table,GTHPoolResult& aPoolResult);
};

#endif //!defined(AFX_UCHPoolResult_H)