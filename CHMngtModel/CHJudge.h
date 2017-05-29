/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHJudge.h                                                                 
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


#ifndef _CHJudge_H
#define _CHJudge_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef _CHMNGTMODELDLL_H
#   include "CHMngtModelDll.h" 
#endif // _CH_MNGTMODELDLL_H

#include <Core\G\GJudge.h>

class CHModelExport CHJudge : public GJudge
{

	RWDECLARE_COLLECTABLE(CHJudge)

public:
	

	enum TypeJudge {eUmpire = 6, eOfficial=8, eTechnicalDelegate,eJuryAppeal};
	
	//Construction/Destruction
	CHJudge();
	CHJudge(GRegister* pRegister);
	CHJudge(GRegister* pRegister,GFunction * pFunction);
	CHJudge(const CHJudge & copy);
	CHJudge(MSLPack& aPack);
	virtual ~CHJudge();


	//Operators
	bool	operator !=(const CHJudge & copy);
	bool	operator ==(const CHJudge & copy);
	CHJudge&	operator =(const CHJudge & copy);


	//From GData
	void		setKey();
	bool	uSQL(RWDBConnection& pConnect,bool remove=false);
	MSLPack&		pack(MSLPack &iPack);
	MSLPack&		unpack(MSLPack &iPack);
	MSLString	msl() const;
	MSLString	mslDescription(const char *language) const;

	// Sets
	void		setFunction(GFunction *value);
	

	//From GFunction
	const char	getFunctionCode() const;
	
	

	//From GRegister
	MSLWString getGroupLDescription(const char *language=getAppLanguage());
	GRegister::TypeRegister getType();

private:	
	
	
};

#endif //!defined(AFX_CHJudge_H)