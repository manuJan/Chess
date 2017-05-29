/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : QCHPhase.h
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

#pragma once
#include <OVR/CORE/TH/QGTHPhase.h>

class QCHPhase : public QGTHPhase  
{
public:

	QCHPhase()
		:QGTHPhase()
	{;}
	virtual ~QCHPhase() {;}

protected:

	void OnSelect(MSLDBSelector& aSelect,MSLDBTable& tPhase);
	void OnReader(MSLDBReader& aReader,GPhase *pPhase);

};

