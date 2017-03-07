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
#if !defined(AFX_UCHTEAMMATCHSCNFG_H__780F287B_1315_4403_A3DC_EEA63E4C710E__INCLUDED_)
#define AFX_UCHTEAMMATCHSCNFG_H__780F287B_1315_4403_A3DC_EEA63E4C710E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <core/G/UBase.h>
#include "CHTeamMatchsCnfg.h"

class UCHTeamMatchsCnfg : public UBase  
{
public:
	UCHTeamMatchsCnfg(RWDBConnection *pNewConnection);
	virtual ~UCHTeamMatchsCnfg();

protected:
	RWBoolean insert (RWDBConnection& aConnection,GData& aData);
	RWBoolean update (RWDBConnection& aConnection,GData& aData);
	RWBoolean delete_(RWDBConnection& aConnection,GData& aData);

private:
	void assignAtributes(CHTeamMatchsCnfg& aTeamMatCnfg);
	void assignAtributesNames(GNames *names);

protected:
	RWCString fSex, fEvent, fRound, fPhase, fCompMatchesDistribution,
		fMatchesType, fFAwayC;
	short fId, fnMatches, fnComp;
	RWDBNullIndicator nullRound, nullPhase, nullnComp, nullMatchesType,
		nullCompMatchesDistribution, nullnMatches, nullId, nullFAwayC;
	RWCString flanguage;
	RWWString fsDescription,flDescription;
	RWDBNullIndicator nullSDescription,nullLDescription;
};

#endif // !defined(AFX_UCHTEAMMATCHSCNFG_H__780F287B_1315_4403_A3DC_EEA63E4C710E__INCLUDED_)
