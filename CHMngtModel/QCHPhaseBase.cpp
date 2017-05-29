/*************************************************************************************
*			© Copyright MSL Software, S.L., 2001
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:QCHPhaseBase.h
*	Description	:
*
*   Author      :Chess Team
*   Date created:07-12-2005
*   Project     :CH Model       
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
**************************************************************************************/

#include "stdCHMngt.h"
#include "QCHPhaseBase.h"
#include "CHPhaseBase.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


void QCHPhaseBase::OnSelect(MSLDBSelector& aSelect,MSLDBTable& z012phase,MSLDBTable& z512phase)
{
	QGTHPhaseBase::OnSelect(aSelect,z012phase,z512phase);

	aSelect << z012phase["TYPEPHASE"];
			
	
	UNREFERENCED_PARAMETER(z512phase);
}

void QCHPhaseBase::OnReader(MSLDBReader& aReader,GDescription& aDescription,GPhaseBase *pPhaseBase)
{
	CHPhaseBase* pVal = (CHPhaseBase*)pPhaseBase;

	QGTHPhaseBase::OnReader(aReader,aDescription,pPhaseBase);

	short typePhase;
	
	aReader >> typePhase;
	
	pVal->setTypePhase(typePhase);
	
	UNREFERENCED_PARAMETER(aDescription);
}
