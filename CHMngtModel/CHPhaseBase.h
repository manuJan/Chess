/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   :CHPhaseBase.h                                                                 
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

#if !defined(AFX_CHPHASEBASE_H__8C865870_B1EC_4165_A6FF_AF227CC0C44E__INCLUDED_)
#define AFX_CHPHASEBASE_H__8C865870_B1EC_4165_A6FF_AF227CC0C44E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHMNGTMODELDLL_H
#   include "CHMngtModelDll.h" 
#endif // _CH_MNGTMODELDLL_H

#include <core\TH\GTHPhaseGeneric.h>

class CHModelExport CHPhaseBase : public GTHPhaseGeneric  
{
	RWDECLARE_COLLECTABLE(CHPhaseBase)

public:
	enum TypePhase			{ eElim=1, ePool=2, eSwiss=3, eRepechage=4 };
	
	CHPhaseBase();
	
	CHPhaseBase(const CHPhaseBase & copy);
	CHPhaseBase(CPack& aPack);
	virtual ~CHPhaseBase();

	RWBoolean operator !=(const CHPhaseBase & copy);
	RWBoolean operator ==(const CHPhaseBase & copy);
	CHPhaseBase & operator =(const CHPhaseBase & copy);

	// Update SQL
	RWBoolean uSQL(RWDBConnection& pConnect,RWBoolean remove=false);
	//set
	void setTypePhase		(const short value);
	
	//get
	short		getTypePhase()			const;
		

	CPackObject getPackObject();
	CPack& pack(CPack &iPack);
	CPack& unpack(CPack &iPack);

	
private:	
	short		typePhase;		//se utiliza para saber el tipo de fase
		
};

#endif // !defined(AFX_CHPHASEBASE_H__8C865870_B1EC_4165_A6FF_AF227CC0C44E__INCLUDED_)
