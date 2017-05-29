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

#pragma once
#include "CHMemoryDataBaseDefs.h"
#include <OVR/CORE/TH/GTHPhaseBase.h>

class CHMngtModelExport CHPhaseBase : public GTHPhaseBase  
{
	MSLDECLARE_ITEM(CHPhaseBase)

public:
	enum TypePhase	{ eElim=1, ePool=2, eSwiss=3, eRepechage=4 };
	
	CHPhaseBase();	
	CHPhaseBase(const CHPhaseBase & copy);	
	virtual ~CHPhaseBase();

	/**** Virtual operators inherited from GData ********************/
	GData& operator= (const GData& copy);
	bool   operator==(const GData& copy);
	bool   operator!=(const GData& copy);

	/**** Virtual methods inherited from GData **********************/
	MSLPack& pack  (MSLPack& pck) const;
	MSLPack& unpack(MSLPack& pck);

	QBase*			onQ() const;
	UBase*			onU() const;

	//set
	void setTypePhase(const short value);
	
	//get
	short getTypePhase() const;
		
	
private:	
	short m_typePhase;	//se utiliza para saber el tipo de fase
		
};
