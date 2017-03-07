/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : LRegister.h                                                                 
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

#if !defined(AFX_CHREGISTER_H__EFBFD2EA_5DCE_43C7_8D2F_EC08A7C91AA0__INCLUDED_)
#define AFX_CHREGISTER_H__EFBFD2EA_5DCE_43C7_8D2F_EC08A7C91AA0__INCLUDED_

#ifndef _CHRegister_H
#define _CHRegister_H
#endif 

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHMNGTMODELDLL_H
#   include "CHMngtModelDll.h" 
#endif // _CH_MNGTMODELDLL_H

#include <CORE\G\GDefines.h>

class GRegister;
class CHModelExport CHRegister : public GRegister  
{
	RWDECLARE_COLLECTABLE(CHRegister)

	enum TypeRegister {individual,team,doubles,judge=6,official};
	enum masterType {mNone=0,mGMaster,mFMaster,mIMaster};

public:
	CHRegister();
	CHRegister(const GRegister &copy);
	CHRegister(const CHRegister &copy);
	CHRegister(CPack &iPack);
	virtual ~CHRegister();

	//Operators
	GRegister& operator =(const GRegister& copy);
	RWBoolean  operator ==(const GRegister& copy);
	RWBoolean  operator !=(const GRegister& copy);

	RWBoolean uSQL(RWDBConnection& pConnect,RWBoolean remove=false);
	RWCString msl() const;
	//Packing Methods
	CPack& pack(CPack & aPack);
	CPack& unpack(CPack &aPack);

	// set
	void setMasterType(const short value);

	// get
	short getMasterType() const;
	RWCString getMasterTypeAsString(bool longer=true) const;
	short getMasterTypeOrder() const;

private:	
	short masterType;
};

#endif // !defined(AFX_CHREGISTER_H__EFBFD2EA_5DCE_43C7_8D2F_EC08A7C91AA0__INCLUDED_)
