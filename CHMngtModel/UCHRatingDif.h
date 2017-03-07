/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:UCHRatingDif.h
*	Description	:
*
*	Author		:Chess Team
*	Date created:26-01-2006
* 	Project		:Chess Management Model DLL
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#if !defined(AFX_UCHRatingDif_H__EC659569_DDDE_413E_AA76_54B9A464DF99__INCLUDED_)
#define AFX_UCHRatingDif_H__EC659569_DDDE_413E_AA76_54B9A464DF99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <CORE/G/UBase.h>

class UCHRatingDif : public UBase  
{
public:
	UCHRatingDif(RWDBConnection *pNewConnection):UBase(pNewConnection) {;}
	virtual ~UCHRatingDif() {;}
	
	void assignAtributes(CHRatingDif& aRatingDif);

protected:
	RWBoolean insert (RWDBConnection& aConnection,GData& aData);
	RWBoolean update (RWDBConnection& aConnection,GData& aData);
	RWBoolean delete_(RWDBConnection& aConnection,GData& aData);

private:
	short code,probability,difference;
	RWDBNullIndicator nullprobability,nulldifference;

};

#endif // !defined(AFX_UCHRatingDif_H__EC659569_DDDE_413E_AA76_54B9A464DF99__INCLUDED_)
