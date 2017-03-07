/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHPhase.h
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

#if !defined(AFX_CHPHASE_H__7B990CAF_3853_48C2_9B8A_F6B3C98EEF3F__INCLUDED_)
#define AFX_CHPHASE_H__7B990CAF_3853_48C2_9B8A_F6B3C98EEF3F__INCLUDED_

#ifndef _CHPhase_H
#define _CHPhase_H
#endif 

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHMNGTMODELDLL_H
#   include "CHMngtModelDll.h" 
#endif // _CH_MNGTMODELDLL_H

#include <core/THSP/THSPPhase.h>



class CHModelExport CHPhase : public THSPPhase  
{
	RWDECLARE_COLLECTABLE(CHPhase)
	

public:
	CHPhase();
	CHPhase(const CHPhase& copy);
	CHPhase(CPack &iPack);
	virtual ~CHPhase();

	CHPhase & operator = (const CHPhase & copy);
	RWBoolean operator == (const CHPhase & copy);	
	RWBoolean operator != (const CHPhase & copy);

	RWBoolean uSQL(RWDBConnection& pConnect,RWBoolean remove=false);
	RWCString msl() const;
	RWCString mslDescription(const char *language) const;
	CPack &pack(CPack &aPack);
	CPack &unpack(CPack &aPack);
	
	//set
	void setTypePhase		(const short value);
	void setIdTeamMatchsCnfg(const short value);
		
	//get
	short getTypePhase()			const;
	short getIdTeamMatchsCnfg()			const;

	// From CHPool
	short getNumRounds();

	RWBoolean hasCompetitors();
	

private:
	short	typePhase;			//se utiliza para saber el tipo de fase
	short	idTeamMatchsCnfg;	//se utiliza para poder cambiar el tipo de configuracion de partidos 
			
};

#endif // !defined(AFX_CHPHASE_H__7B990CAF_3853_48C2_9B8A_F6B3C98EEF3F__INCLUDED_)
