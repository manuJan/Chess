/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHCompetitorDraw.h
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:23-12-2005
*   Project     :CHV Model               
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///

#if !defined(AFX_HCOMPETITORDRAW_H)
#define AFX_HCOMPETITORDRAW_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <core\G\GData.h>

class CHCompetitorDraw : public GData  
{
public:

	CHCompetitorDraw(CHPoolResult* _pPoolResult, short _order, short _round);
	virtual ~CHCompetitorDraw();

	void setKey();

	RWBoolean uSQL(RWDBConnection& pConnect,RWBoolean remove=false)
	{
		return false;
		UNREFERENCED_PARAMETER(remove);
		UNREFERENCED_PARAMETER(pConnect);
	}

	//Overloaded operators
	RWBoolean operator !=(const CHCompetitorDraw& copy);
	RWBoolean operator ==(const CHCompetitorDraw& copy);
	CHCompetitorDraw& operator =(const CHCompetitorDraw& copy);

	void copyCompetitorDraw(const CHCompetitorDraw& copy);
	RWBoolean compareCompetitorDraw(const CHCompetitorDraw& copy);

	CPack& pack(CPack& aPack);
	CPack& unpack(CPack& aPack);	

	CHPoolResult* getPoolResult();
	short getOrder();
	short getRound();
	short getPoolResultCode();
	RWBoolean getPoolResultBye();
	CHInscription* getPoolResultInscription();
	bool getAlreadyPaired();
	bool getFloatingDown();
	bool getFloatingUp();

	void setAlreadyPaired(bool value);
	void setFloatingDown(bool value);
	void setFloatingUp(bool value);
	void setOrder(short value);

	bool hasSameColorTwoLast();
	bool hasAlreadyBye(short round);
	bool hasAlreadyNotOpponent();
	
	short getColorDiference(CHPoolResult* pPoolResult);
	
	CHMatchResult::colorPreference getColorPreference(short round);
	CHMatchResult::side  getSidePreference(short round);

private:

	CHPoolResult	*pPoolResult;
	short			order;
	short			round;
	bool			alreadyPaired;
	bool			floatingDown;
	bool			floatingUp;

};

#endif // !defined(AFX_HCOMPETITORDRAW_H)
