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

#pragma once
#include "CHVMngtModelDefs.h"
#include "..\CHMngtModel\CHMatchResult.h"
class CHPoolResult;
class CHInscription;

class CHCompetitorDraw : public GData  
{
public:

	CHCompetitorDraw(CHPoolResult* _pPoolResult, short _order, short _round);
	virtual ~CHCompetitorDraw();

	void setKey();

	//Overloaded operators
	GData& operator= (const GData& copy);
	bool   operator==(const GData& copy);
	bool   operator!=(const GData& copy);
		
	CHPoolResult* getPoolResult();
	short getOrder();
	short getRound();
	short getPoolResultCode();
	bool getPoolResultBye();
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

