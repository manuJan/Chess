/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : UCHTeamMatchsCnfg.h
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
#include <OVR/CORE/G/UBase.h>
#include "CHTeamMatchsCnfg.h"

class UCHTeamMatchsCnfg : public UBase
{

public:
	UCHTeamMatchsCnfg()
		:UBase()
	{;}
	virtual ~UCHTeamMatchsCnfg()
	{;}

protected:
	bool insert (GData& aData);
	bool update (GData& aData);	
	bool delete_(GData& aData);

	long insertLang(MSLDBTable& table,CHTeamMatchsCnfg& aTeamMatchsCnfg);
	long updateLang(MSLDBTable& table,CHTeamMatchsCnfg& aTeamMatchsCnfg);
	long OnInsertLang(MSLDBTable& table,CHTeamMatchsCnfg& aTeamMatchsCnfg);
	long OnUpdateLang(MSLDBTable& table,CHTeamMatchsCnfg& aTeamMatchsCnfg);

	void assignAtributes(CHTeamMatchsCnfg& aTeamMatchsCnfg);
	bool assignNames(CHTeamMatchsCnfg& aTeamMatchsCnfg,const char *language);

protected:

	MSLString fSex, fEvent, fRound, fPhase, fCompMatchesDistribution,fMatchesTypeElim, fMatchesType, fFAwayC;
	short fId, fnMatches,fnMatchesElim, fnComp;
	MSLDBNullIndicator nullRound, nullPhase, nullnComp, nullMatchesType,
		nullCompMatchesDistribution,nullMatchesTypeElim, nullnMatches,nullnMatchesElim,nullId, nullFAwayC;
	MSLString flanguage;
	MSLWString fsDescription,flDescription;
	MSLDBNullIndicator nullSDescription,nullLDescription;
};


