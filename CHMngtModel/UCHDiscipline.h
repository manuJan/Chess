/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : UCHDiscipline.h                                                                 
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:05-12-2005
*   Project     :CH Model
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///

#if !defined(AFX_UCHDISCIPLINE_H__DA7286A1_A5DD_400D_B03D_BAAA6436D4B6__INCLUDED_)
#define AFX_UCHDISCIPLINE_H__DA7286A1_A5DD_400D_B03D_BAAA6436D4B6__INCLUDED_

#ifndef _UCHDiscipline_H
#define _UCHDiscipline_H
#endif 

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHMNGTMODELDLL_H
#   include "CHMngtModelDll.h" 
#endif // _CH_MNGTMODELDLL_H

#include <CORE\G\UBase.h>

class CHDiscipline;
class UCHDiscipline : public UBase  
{
public:
	UCHDiscipline(RWDBConnection *pNewConnection);
	virtual ~UCHDiscipline();

protected:
	RWBoolean update(RWDBConnection & aConnection,GData & aData);

private:
	void assignAtributes(CHDiscipline & discipline);

//atributos
	RWBoolean autoProg;
	int fShortScore, fLongScore;
	RWCString fRscComposition;
	RWDBDateTime fDate;
	RWDBNullIndicator nullShortScore, nullLongScore,nullDate,nullRscComposition;
	float absencePoints;
};

#endif // !defined(AFX_UCHDISCIPLINE_H__DA7286A1_A5DD_400D_B03D_BAAA6436D4B6__INCLUDED_)
