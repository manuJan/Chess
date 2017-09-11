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

#pragma once
#include "CHMemoryDataBaseDefs.h"
#include <OVR/CORE/G/GRegister.h>

class CHMngtModelExport CHRegister : public GRegister  
{
	MSLDECLARE_ITEM(CHRegister)
			
	enum masterType {mNone=0,mGMaster,mFMaster,mIMaster,mInternational,mCandidate,mCandidateMaster};

public:
	CHRegister();	
	CHRegister(const CHRegister &copy);	
	virtual ~CHRegister();

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
	void setMasterTypeCode(const short value);

	// get
	short getMasterTypeCode() const;

	MSLWString getMasterTypeLDescription() const;
	MSLWString getMasterTypeSDescription() const;
	short getMasterTypeOrder() const;
	CHMasterType * getMasterType();

private:	
	short m_masterType;
};
