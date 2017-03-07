/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : UCHJudge.h                                                                 
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

#if !defined(AFX_UCHJUDGE_H__13A722E1_5567_469D_A0F8_549EC89DF2ED__INCLUDED_)
#define AFX_UCHJUDGE_H__13A722E1_5567_469D_A0F8_549EC89DF2ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <CORE/G/UBase.h>

class CHJudge;

class UCHJudge : public UBase  
{
public:
	UCHJudge(RWDBConnection *pNewConnection)
		:UBase(pNewConnection){};
	virtual ~UCHJudge(){};
	
protected:
	RWBoolean insert (RWDBConnection& aConnection,GData& aData);
	RWBoolean update (RWDBConnection& aConnection,GData& aData);
	RWBoolean delete_(RWDBConnection& aConnection,GData& aData);

private:
	void assignAtributes(CHJudge *pJudge);

private:	
	short fFunction;
	RWDBNullIndicator nullFunction;
	int   fRegister;

};

#endif // !defined(AFX_UCHJUDGE_H__13A722E1_5567_469D_A0F8_549EC89DF2ED__INCLUDED_)
