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

#if !defined(AFX_HPAIRDRAW_H__2D12F48E_C62B_454D_A02D_B6F3E23BE351__INCLUDED_)
#define AFX_HPAIRDRAW_H__2D12F48E_C62B_454D_A02D_B6F3E23BE351__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <core\G\GData.h>

class CHCompetitorDraw;
class CHGroupDraw;

class CHPairDraw : public GData  
{
public:
	CHPairDraw(CHGroupDraw* _pGroupDraw, CHMatch* _pMatch, short _order);
	virtual ~CHPairDraw();

	void setKey();

	RWBoolean uSQL(RWDBConnection& pConnect,RWBoolean remove=false)
	{
		return false;
		UNREFERENCED_PARAMETER(remove);
		UNREFERENCED_PARAMETER(pConnect);
	}	

	//Overloaded operators
	RWBoolean operator !=(const CHPairDraw& copy);
	RWBoolean operator ==(const CHPairDraw& copy);
	CHPairDraw& operator =(const CHPairDraw& copy);

	void copyPairDraw(const CHPairDraw& copy);
	RWBoolean comparePairDraw(const CHPairDraw& copy);

	CPack& pack(CPack& aPack);
	CPack& unpack(CPack& aPack);

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

#endif // !defined(AFX_HPAIRDRAW_H__2D12F48E_C62B_454D_A02D_B6F3E23BE351__INCLUDED_)
