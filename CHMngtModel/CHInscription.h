/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHInscription.h                                                                 
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

#if !defined(AFX_CHINSCRIPTION_H__FDDA4A1D_1B61_47B1_AFE9_C3FC2F9938E9__INCLUDED_)
#define AFX_CHINSCRIPTION_H__FDDA4A1D_1B61_47B1_AFE9_C3FC2F9938E9__INCLUDED_

#ifndef _CHInscription_H
#define _CHInscription_H
#endif 

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHMNGTMODELDLL_H
#   include "CHMngtModelDll.h" 
#endif // _CH_MNGTMODELDLL_H

#include <Core/TH/GTHInscription.h>
class GRegister;
class GTHEvent;
class CHRegister;
class CHMember;

class CHModelExport CHInscription : public GTHInscription  
{
	RWDECLARE_COLLECTABLE(CHInscription)

public:
	CHInscription();
	CHInscription(GRegister *reg,GTHEvent *ev);
	CHInscription(const CHInscription &copy);
	CHInscription(CPack &iPack);
	virtual ~CHInscription();

	CHInscription & operator = (const CHInscription &copy);
	RWBoolean	    operator == (const CHInscription &copy);
	RWBoolean	    operator != (const CHInscription &copy);
	CHMember *		operator [] (const size_t index) const;

	RWBoolean uSQL(RWDBConnection& pConnect,RWBoolean remove=false);
	RWCString msl() const;
	CPack& pack(CPack & aPack);
	CPack& unpack(CPack &aPack);

	// set
	void setSeed(const short value);
	void setRating(const short value);
	void setKConst(const short value);
	

	// get
	short getSeed() const;
	short getRating() const;
	short getKConst() const;
	RWCString getSeedAsString() const;
	RWCString getRatingAsString() const;
	RWCString getKConstAsString() const;
	
	
	GRegister::TypeRegister getType() const;
	RWWString getGroupLDescription(const char *language=DBApplication::getAppLanguage()) const;

	RWCString getRegisterBirthDate(const char *format/*="%x"*/) const;
	CHRegister *getMemberRegister(const size_t value) const;
	int getRegisterCode() const;
	RWWString getMemberRegisterPrnLName(const size_t value) const;
	RWWString getTeamScbLName(const RWBoolean bFMember, const RWBoolean bSMember, const RWBoolean bTMember) const;
	short getTypeEvent() const;

	// From CHRegister
	short getRegMasterType() const;
	RWCString getRegMasterTypeAsString(bool longer=true) const;
	short getRegMasterTypeOrder() const;


private:
	short		seed;	// cabeza de serie
	short		rating;	// Puntuacion acumulada	
	short		kConst;	// Constante calculo Rating
	
};

#endif // !defined(AFX_CHINSCRIPTION_H__FDDA4A1D_1B61_47B1_AFE9_C3FC2F9938E9__INCLUDED_)
