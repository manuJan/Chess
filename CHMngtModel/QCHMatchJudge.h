/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : QCHMatchJudge.h                                                                 
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:13-12-2005
*   Project     :CH Model
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///


#ifndef _QCHMatchJudge_H
#define _QCHMatchJudge_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef _CHMNGTMODELDLL_H
#   include "CHMngtModelDll.h" 
#endif // _CH_MNGTMODELDLL_H

#include <core/TH/QGTHMatchJudge.h>

class GTHMatchJudge;


class CHModelExport QCHMatchJudge : public QGTHMatchJudge
{

public:

	QCHMatchJudge(RWDBConnection *pNewConnection)
	:QGTHMatchJudge(pNewConnection)
	{;}

	virtual ~QCHMatchJudge() {;}

protected:
	void OnSelect(RWDBSelector& aSelect,RWDBTable& table);
	void OnReader(RWDBReader& aReader,GTHMatchJudge *pMatchJudge);
	GTHMatchJudge * OnNewMatchJudge();

};

#endif //!defined(AFX_QCHMatchJudge_H)