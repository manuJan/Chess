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

#pragma once
#include "CHMemoryDataBaseDefs.h"
#include <OVR/CORE/G/GMember.h>

class GMember;
class CHEvent;
class CHRegister;
class CHInscription;
class GFunction;

class CHMngtModelExport CHMember : public GMember  
{
	MSLDECLARE_ITEM(CHMember)

	enum Function { eNone=0, eFirst=7, eSecond=8, eThird=9, eSubstitute=11 };

public:
	CHMember();
	CHMember(GRegister * iRegister, GRegister * tRegister);
	CHMember(const CHMember &copy);	
	virtual ~CHMember();

	//Operators
	GData& operator = (const GData & copy);
	bool   operator ==(const GData & copy);
	bool   operator !=(const GData & copy);

	/**** Virtual methods inherited from MSLItem ********************/
	virtual MSLPack& pack  (MSLPack& pck) const;
	virtual MSLPack& unpack(MSLPack& pck);

	//Virtual methods inherited from GData
	QBase*			onQ() const;
	UBase*			onU() const;

	//set
	void setFunction(const short value);
	void setRating(const short value);
	void setKConst(const short value);
	short getRating() const;
	short getKConst() const;
	
	MSLString getRatingAsString() const;
	MSLString getKConstAsString() const;
	
	//get
	short getFunction() const;
	GFunction *getCFunction() const;
	MSLWString getFunctionLDescription() const;
	CHEvent *getEvent() const;
	int getRegisterCode() const;
	
private:
	short		m_function;
	short		m_rating;	// Puntuacion acumulada	
	short		m_kConst;	// Constante calculo Rating
};
