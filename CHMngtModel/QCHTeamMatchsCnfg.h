/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : QCHTeamMatchsCnfg.h
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
#if !defined(AFX_QCHTEAMMATCHSCNFG_H__C32888E2_B686_431C_B196_DF57EB13AB76__INCLUDED_)
#define AFX_QCHTEAMMATCHSCNFG_H__C32888E2_B686_431C_B196_DF57EB13AB76__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <CORE/G/QBase.h>
#include <Core/G/GNames.h>

class QCHTeamMatchsCnfg : public QBase  
{
public:
	QCHTeamMatchsCnfg(RWDBConnection *pNewConnection);
	virtual ~QCHTeamMatchsCnfg();

protected:
	size_t selectCollection(RWDBConnection& aConnection,RWCollection& target);
};

#endif // !defined(AFX_QCHTEAMMATCHSCNFG_H__C32888E2_B686_431C_B196_DF57EB13AB76__INCLUDED_)
