/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : UCHInscription.h
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

#if !defined(AFX_UCHINSCRIPTION_H__750FEB8E_46DE_4A0B_9695_6176655A28E7__INCLUDED_)
#define AFX_UCHINSCRIPTION_H__750FEB8E_46DE_4A0B_9695_6176655A28E7__INCLUDED_

#ifndef _UCHInscription_H
#define _UCHInscription_H
#endif 

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Core/TH/UGTHInscription.h>

class UCHInscription : public UGTHInscription  
{
public:
	UCHInscription(RWDBConnection *pNewConnection);
	virtual ~UCHInscription();

private:
	short     seed,rating,kConst;
	RWDBNullIndicator nullSeed,nullRating,nullKConst;
	
protected:
	void OnAssignAttributes(const GInscription& aInscription);
	void OnInsert(RWDBInserter& aInsert,const GInscription& aInscription);
	void OnUpdate(RWDBUpdater& aUpdate,RWDBTable& table,const GInscription& aInscription);
	void OnDelete(RWDBDeleter& aDelete,RWDBTable& table,const GInscription& aInscription);
};

#endif // !defined(AFX_UCHINSCRIPTION_H__750FEB8E_46DE_4A0B_9695_6176655A28E7__INCLUDED_)
