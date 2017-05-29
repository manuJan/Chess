/*************************************************************************************
*			© Copyright MSL Software, S.L., 2001
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:	CHSession.h
*	Description	:
*
*   Author      :Chess Team
*   Date created:12-12-2005
*   Project     :CH Model
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#if !defined(AFX_CHSESSION_H__97A173E1_BE09_4F1D_8B95_563F53BC8EED__INCLUDED_)
#define AFX_CHSESSION_H__97A173E1_BE09_4F1D_8B95_563F53BC8EED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHMNGTMODELDLL_H
#   include "CHMngtModelDll.h" 
#endif // _CH_MNGTMODELDLL_H

#include <core\TH\GTHSession.h>

class CHModelExport CHSession : public GTHSession  
{
	MSLDECLARE_ITEM(CHSession);
public:

	//Construction/Destruction
	CHSession();
	CHSession(const CHSession &copy);
	CHSession(CPack &iPack);
	virtual ~CHSession();
	
	
	//Operators
	CHSession&	operator  = (const CHSession &copy);
	RWBoolean   operator == (const CHSession &copy);
	RWBoolean   operator != (const CHSession &copy);


	//From GData
	RWCString		msl() const;
	CPack&			pack(CPack & aPack);
	CPack&			unpack(CPack &aPack);
	RWBoolean		uSQL(RWDBConnection& pConnect,RWBoolean remove=false);

	
	//Sets
	void			setDescription(const RWCString value);
	void			setAcumulatSess(const short value);
	void			setStatus(const unsigned char value);


	//Gets
	RWCString		getDescription() const;
	short			getAcumulatSess() const;
	unsigned char	getStatus			() const;

	RWWString			getStatusSDescription(const char *language=DBApplication::getAppLanguage()) const;
	RWWString			getStatusLDescription(const char *language=DBApplication::getAppLanguage()) const;

private:
	RWCString		description;
	short			acumulatSess;
	unsigned char	status;
};

#endif // !defined(AFX_CHSESSION_H__97A173E1_BE09_4F1D_8B95_563F53BC8EED__INCLUDED_)
