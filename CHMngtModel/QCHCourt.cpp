/*************************************************************************************
*	© Copyright MSL Software, S.L., 2001
*
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:QCHCourt.h
*	Description	:Query Chess Court
*
*	Author		:Chess Team
*	Date created:12-12-2005
* 	Project		:CH Model
*
***************************************************************************************/

#include "stdCHMngt.h"
#include "QCHCourt.h"

void QCHCourt::OnSelect(RWDBSelector& aSelect,RWDBTable& tCourt)
{
	QCourt::OnSelect(aSelect,tCourt);

	aSelect << tCourt["NORDER"];
}

void QCHCourt::OnReader(RWDBReader& aReader,GCourt *pCourt)
{
	QCourt::OnReader(aReader,pCourt);

	short order;
	
	aReader >> order;
			
	((CHCourt*)pCourt)->setOrder(order);
	
}


