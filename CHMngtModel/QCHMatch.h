/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : QCHMatch.h
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

#if !defined(AFX_QCHMATCH_H__D7C89BE4_E723_4674_84CE_2002FE9997DF__INCLUDED_)
#define AFX_QCHMATCH_H__D7C89BE4_E723_4674_84CE_2002FE9997DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <CORE/TH/QGTHMatch.h>
#include "CHMatch.h"

class QCHMatch : public QGTHMatch  
{
public:
	QCHMatch(RWDBConnection *pNewConnection);
	virtual ~QCHMatch();

protected:
	GTHMatch * OnNewMatch(const RWDBBlob& aBlob);
	void OnSelect(RWDBSelector& aSelect,RWDBTable& tMatch);
	void OnReader(RWDBReader& aReader,GTHMatch *pMatch);
};

#endif // !defined(AFX_QCHMATCH_H__D7C89BE4_E723_4674_84CE_2002FE9997DF__INCLUDED_)
