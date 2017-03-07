/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHCheckList.h
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:19-12-2005
*   Project     :CHV Model               
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///
#if !defined(AFX_CHCHECKLIST_H__7650C292_B621_4096_982A_A379FEC4E370__INCLUDED_)
#define AFX_CHCHECKLIST_H__7650C292_B621_4096_982A_A379FEC4E370__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <REPORTS/V/GCheckList.h>
class CHInscription;
class CHCheckList : public GCheckList  
{
public:
	CHCheckList();
	CHCheckList(GRegister * pReg,RWBoolean bEx=false);
	virtual ~CHCheckList();

	void insertInscription(CHInscription *pInscription);
	GSortedVector& getVectorInsc();

private:
	GSortedVector vInscriptions;
};

#endif // !defined(AFX_CHCHECKLIST_H__7650C292_B621_4096_982A_A379FEC4E370__INCLUDED_)
