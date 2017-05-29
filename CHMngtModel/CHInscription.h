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

#pragma once
#include "CHMemoryDataBaseDefs.h"
#include <OVR/CORE/TH/GTHInscription.h>

class GRegister;
class GTHEvent;
class CHRegister;
class CHMember;

class CHMngtModelExport CHInscription : public GTHInscription  
{
	MSLDECLARE_ITEM(CHInscription)

public:
	CHInscription();
	CHInscription(GRegister *reg,GTHEvent *ev);
	CHInscription(const CHInscription &copy);	
	virtual ~CHInscription();

	/**** Virtual operators inherited from GData ********************/
	GData& operator= (const GData& copy);
	bool   operator==(const GData& copy);
	bool   operator!=(const GData& copy);

	/**** Virtual methods inherited from GData **********************/
	MSLPack& pack  (MSLPack& pck) const;
	MSLPack& unpack(MSLPack& pck);

	QBase*			onQ() const;
	UBase*			onU() const;

	// set
	void setSeed(const short value);
	void setRating(const short value);
	void setKConst(const short value);
	
	// get
	short getSeed() const;
	short getRating() const;
	short getKConst() const;

	MSLString getSeedAsString() const;
	MSLString getRatingAsString() const;
	MSLString getKConstAsString() const;
		
	GRegister::TypeRegister getType() const;		
	CHRegister *getMemberRegister(const size_t value) const;	
	MSLWString getMemberRegisterPrnLName(const size_t value) const;
	MSLWString getTeamScbLName(const bool bFMember, const bool bSMember, const bool bTMember) const;
	short getTypeEvent() const;

	// From CHRegister
	short getRegMasterType() const;
	MSLString getRegMasterTypeAsString(bool longer=true) const;
	short getRegMasterTypeOrder() const;
	
private:
	short	m_seed;	// cabeza de serie
	short	m_rating;	// Puntuacion acumulada	
	short	m_kConst;	// Constante calculo Rating	
};

