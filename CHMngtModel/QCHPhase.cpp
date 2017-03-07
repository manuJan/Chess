/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : QCHPhase.cpp
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

#include "stdCHMngt.h"
#include "QCHPhase.h"
#include "CHPhase.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
QCHPhase::QCHPhase(RWDBConnection *pNewConnection)
:QGTHPhase(pNewConnection)
{
}

QCHPhase::~QCHPhase()
{
}

GPhase * QCHPhase::OnNewPhase()
{
	return new CHPhase();
}

void QCHPhase::OnSelect(RWDBSelector& aSelect,RWDBTable& tPhase)
{
	QGTHPhase::OnSelect(aSelect,tPhase);
	
	aSelect <<	tPhase["TYPEPHASE"]
			<<	tPhase["TEAM_MATCH_CNFG"]
				;
		
}

void QCHPhase::OnReader(RWDBReader& aReader,GPhase *pPhase)
{
	QGTHPhase::OnReader(aReader,pPhase);
	
	short typePhase,idTeamMatchsCnfg;
	
	aReader		>> typePhase
				>> idTeamMatchsCnfg;
	
	((CHPhase*)pPhase)->setTypePhase(typePhase);
	((CHPhase*)pPhase)->setIdTeamMatchsCnfg(idTeamMatchsCnfg);
		
}