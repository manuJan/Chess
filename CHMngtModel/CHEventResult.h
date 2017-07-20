/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHEventResult.h                                                                 
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
#include <OVR/CORE/G/GEventResult.h>

class CHInscription;
class CHPoolResult;

class CHMngtModelExport CHEventResult : public GEventResult
{
	MSLDECLARE_ITEM(CHEventResult)

public:

	//Construction/Destruction
	CHEventResult();	
	CHEventResult(const CHEventResult & copy);	
	virtual ~CHEventResult();
	
	/**** Virtual operators inherited from GData ********************/
	GData& operator= (const GData& copy);
	bool   operator==(const GData& copy);
	bool   operator!=(const GData& copy);

	/**** Virtual methods inherited from GData **********************/
	MSLPack& pack  (MSLPack& pck) const;
	MSLPack& unpack(MSLPack& pck);

	QBase*			onQ() const;
	UBase*			onU() const;

	//Sets
	void			setRating(const short value);
	
	//Gets
	short			getRating() const;
	
	MSLString		getRatingAsString() const;

	// From CHPoolResult
	CHPoolResult *	getPoolResult();
	float			getPointsPoolResult();
	MSLString		getPointsPoolResultStr();

	// select function
	mslToolsFcSelect getSelectFn(const GData *pData);

private:	
		
	short			m_rating;		// Rating con el que acaba la competicion

};

