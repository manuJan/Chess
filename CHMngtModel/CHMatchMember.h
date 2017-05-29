/*************************************************************************************
*	© Copyright MSL Software, S.L., 2001
*
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior wriCHen permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHMatchMember.h
*	Description	:Chess MatchMember
*
*	Author		:Chess Team
*	Date created:13-12-2005
* 	Project		:CH Model
*
***************************************************************************************/

#pragma once
#include "CHMemoryDataBaseDefs.h"
#include <Ovr/Core/TH/GTHMatchMember.h>

class CHMngtModelExport CHMatchMember : public GTHMatchMember  
{
	MSLDECLARE_ITEM(CHMatchMember)

public:
	CHMatchMember();
	CHMatchMember(const CHMatchMember &copy);	
	virtual ~CHMatchMember();

	//Operators
	GData& operator= (const GData & copy);
	bool   operator==(const GData & copy);
	bool   operator!=(const GData & copy);

	/**** Virtual methods inherited from MSLItem ********************/
	virtual MSLPack& pack  (MSLPack& pck) const;
	virtual MSLPack& unpack(MSLPack& pck);

	//Virtual methods inherited from GData
	QBase*			onQ() const;
	UBase*			onU() const;

	//Get
	GSortedVector &getMembersVector() const;
	RWCString getMemberKey() const;

};

#endif // !defined(AFX_CHMATCHMEMBER_H__CB507405_4F6F_4446_B576_768B4805FA3F__INCLUDED_)
