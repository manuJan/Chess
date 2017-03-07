/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHMatchJudge.h                                                                 
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


#ifndef _CHMatchJudge_H
#define _CHMatchJudge_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef _CHMNGTMODELDLL_H
#   include "CHMngtModelDll.h" 
#endif // _CH_MNGTMODELDLL_H


class CHJudge;
class GTHMatchJudge;

class CHModelExport CHMatchJudge : public GTHMatchJudge
{
	RWDECLARE_COLLECTABLE(CHMatchJudge)

public:

	enum TypeUmpire {eUmpire1 = 1, eUmpire2=2 };
		
	//Construction/Destruction
	CHMatchJudge();
	CHMatchJudge(GTHMatch * pMatch,CHJudge *pJudge);
	CHMatchJudge(const CHMatchJudge & copy);
	CHMatchJudge(CPack& aPack);
	virtual ~CHMatchJudge();


	//Operators
	RWBoolean		operator !=(const CHMatchJudge & copy);
	RWBoolean		operator ==(const CHMatchJudge & copy);
	CHMatchJudge&	operator =(const CHMatchJudge & copy);


	//From GData
	RWBoolean		uSQL(RWDBConnection& pConnect,RWBoolean remove=false);
	CPack&			pack(CPack &iPack);
	CPack&			unpack(CPack &iPack);
	RWCString		msl() const;
	RWCString		mslDescription(const char *language) const;

	short	getFunctionShort();


};

#endif //!defined(AFX_CHMatchJudge_H)