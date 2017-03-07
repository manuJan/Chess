/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHEventResult.h                                                                 
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


#ifndef _CHEventResult_H
#define _CHEventResult_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef _CHMNGTMODELDLL_H
#   include "CHMngtModelDll.h" 
#endif // _CH_MNGTMODELDLL_H

#include <Core\TH\GTHEventResult.h>

class CHInscription;
class CHPoolResult;

class CHModelExport CHEventResult : public GTHEventResult
{

	RWDECLARE_COLLECTABLE(CHEventResult)

public:

	//Construction/Destruction
	CHEventResult();
	CHEventResult(CHInscription *pInsc);
	CHEventResult(const CHEventResult & copy);
	CHEventResult(CPack& aPack);
	virtual ~CHEventResult();


	//Operators
	RWBoolean		operator !=(const CHEventResult & copy);
	RWBoolean		operator ==(const CHEventResult & copy);
	CHEventResult&	operator =(const CHEventResult & copy);


	//From GData
	RWBoolean		uSQL(RWDBConnection& pConnect,RWBoolean remove=false);
	CPack&			pack(CPack &iPack);
	CPack&			unpack(CPack &iPack);
	RWCString		msl() const;
	RWCString		mslDescription(const char *language) const;


	//Sets
	void			setQualitative(const char * value);
	void			setRating(const short value);
	

	//Gets
	GQualitative*	getQualitative() const;
	RWCString		getQualitativeCode() const;
	short			getRating() const;
	RWCString		getRatingAsString() const;

	RWCString		getIsoCountry() const;
	RWWString		getGroup() const;
	RWWString		getQualitativeSDescription(const char * language=DBApplication::getAppLanguage()) const;
	RWWString		getQualitativeLDescription(const char * language=DBApplication::getAppLanguage()) const;

	RWBoolean		isQualitative() const;

	// From CHPoolResult
	CHPoolResult *	getPoolResult();
	float			getPointsPoolResult();
	RWCString		getPointsPoolResultStr();

private:	
	
	RWCString		qualitative;
	short			rating;		// Rating con el que acaba la competicion

};

#endif //!defined(AFX_CHEventResult_H)