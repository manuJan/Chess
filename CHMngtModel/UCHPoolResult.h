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


#pragma once
#include <OVR/CORE/TH/UGTHPoolResult.h>

class UCHPoolResult : public UGTHPoolResult
{
public:
	// Constructors && Destructor
	UCHPoolResult()
		:UGTHPoolResult()
	{};

	virtual ~UCHPoolResult()
	{};

protected:
	void	OnAssignAttributes	(GTHPoolResult& aPoolResult);
	void	OnInsert			(MSLDBInserter& aInserter,MSLDBTable& table,GTHPoolResult& aPoolResult);
	void	OnUpdate			(MSLDBUpdater & aUpdater ,MSLDBTable& table,GTHPoolResult& aPoolResult);
	
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
		
	MSLDBNullIndicator nullmatchesPlayed;
	MSLDBNullIndicator nullwonGames;
	MSLDBNullIndicator nulllostGames;
	MSLDBNullIndicator nulltieGames;
	MSLDBNullIndicator nullpointsF;
	MSLDBNullIndicator nullsolkoff;
	MSLDBNullIndicator nullmediansolkoff;
	MSLDBNullIndicator nullsonneBerger;
	MSLDBNullIndicator nullprogressiveScore;
	
};
