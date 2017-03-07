/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHMember.h
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

#if !defined(AFX_CHMEMBER_H__010616B3_702B_4DE2_8744_07666645878D__INCLUDED_)
#define AFX_CHMEMBER_H__010616B3_702B_4DE2_8744_07666645878D__INCLUDED_

#ifndef _CHMember_H
#define _CHMember_H
#endif 

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHMNGTMODELDLL_H
#   include "CHMngtModelDll.h" 
#endif // _CH_MNGTMODELDLL_H

class GMember;
class CHEvent;
class CHRegister;
class CHInscription;
class GFunction;
class CHModelExport CHMember : public GMember  
{
	RWDECLARE_COLLECTABLE(CHMember)

		enum Function { eNone=0, eFirst=7, eSecond=8, eThird=9, eSubstitute=11 };
public:
	CHMember();
	CHMember(CHRegister* pRegister,CHInscription* pInscription);
	CHMember(const CHMember &copy);
	CHMember(CPack &iPack);
	virtual ~CHMember();

	CHMember	&operator = (const CHMember &copy);
	RWBoolean    operator == (const CHMember &copy);
	RWBoolean    operator != (const CHMember &copy);

	RWBoolean uSQL(RWDBConnection& pConnect,RWBoolean remove=false);
	RWCString msl() const;
	CPack& pack(CPack & aPack);
	CPack& unpack(CPack &aPack);
	//set
	void setFunction(const short value);
	void setRating(const short value);
	void setKConst(const short value);
	short getRating() const;
	short getKConst() const;
	RWCString getRatingAsString() const;
	RWCString getKConstAsString() const;
	
	//get
	short getFunction() const;
	GFunction *getCFunction() const;
	RWWString getFunctionLDescription() const;
	CHEvent *getEvent() const;
	int getRegisterCode() const;
	RWCString getRegisterBirthDate(const char *format/*="%x"*/) const;

private:
	short		function;
	short		rating;	// Puntuacion acumulada	
	short		kConst;	// Constante calculo Rating
};

#endif // !defined(AFX_CHMEMBER_H__010616B3_702B_4DE2_8744_07666645878D__INCLUDED_)
