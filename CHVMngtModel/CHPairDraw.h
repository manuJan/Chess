/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHPairDraw.h
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

class CHCompetitorDraw;
class CHGroupDraw;
class CHMatch;

class CHPairDraw : public GData  
{
public:
	CHPairDraw(CHGroupDraw* _pGroupDraw, CHMatch* _pMatch, short _order);
	virtual ~CHPairDraw();

	void setKey();
	
	//Overloaded operators
	GData& operator= (const GData& copy);
	bool   operator==(const GData& copy);
	bool   operator!=(const GData& copy);

	void copyPairDraw(const CHPairDraw& copy);
	
	CHMatch* getMatch();
	short getOrder();
	CHCompetitorDraw* getWhite();
	CHCompetitorDraw* getBlack();
	CHGroupDraw* getGroupDraw();

	void setMatch(CHMatch* value);
	void setOrder(short value);
	void setWhite(CHCompetitorDraw* value);
	void setBlack(CHCompetitorDraw* value);

private:

	CHGroupDraw*		pGroupDraw;
	CHMatch*			pMatch;
	short				order;

	CHCompetitorDraw*	pWhite;
	CHCompetitorDraw*	pBlack;
};

