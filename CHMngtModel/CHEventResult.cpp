/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be consideHome liable for any mistake or omission in the edition of    
*   this document. MSL is a registeHome trademark.                                      
*                                                                                      
*   File name   : CHEventResult.cpp                                                                 
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
#include "CHEventResult.h"
#include "CHClassIds.h"
#include "UCHEventResult.h"
#include <core/G/GBuffer.h>

RWDEFINE_COLLECTABLE(CHEventResult, __CHEVENTRESULT)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHEventResult::CHEventResult()
:GTHEventResult()
,qualitative("0")
,rating(0)
{
}

CHEventResult::CHEventResult(CHInscription *pInsc)
:GTHEventResult()
,qualitative("0")
,rating(0)
{ 
	setInscription((GTHInscription *)pInsc); 
}

CHEventResult::CHEventResult(const CHEventResult & copy)
{
	operator=(copy);
}

CHEventResult::CHEventResult(CPack& aPack)
{
	unpack(aPack);
}

CHEventResult::~CHEventResult()
{
}


//////////////////////////////////////////////////////////////////////
// Operators
//////////////////////////////////////////////////////////////////////
CHEventResult & CHEventResult::operator =(const CHEventResult & copy)
{
	if (this != &copy)
	{
		GTHEventResult::operator =(copy);
		qualitative			= copy.qualitative;
		rating				= copy.rating;
	}
	return * this;
}

RWBoolean CHEventResult::operator ==(const CHEventResult & copy)
{
	if (this == &copy)
		return true;
	else
		return (GTHEventResult::operator ==(copy)		&& 
				qualitative			== copy.qualitative	&&
				rating				== copy.rating);
}

RWBoolean CHEventResult::operator !=(const CHEventResult & copy)
{
	return !operator==(copy);
}


//////////////////////////////////////////////////////////////////////
// From GData
//////////////////////////////////////////////////////////////////////
RWBoolean CHEventResult::uSQL(RWDBConnection& pConnect,RWBoolean remove /*=false*/ )
{
	RWBoolean rc=false;

	UCHEventResult upd(&pConnect);

	if( remove )  rc=upd.remove(*this);
	else          rc=upd.set   (*this);

	return rc;
}

CPack& CHEventResult::pack(CPack& aPack)
{
	GTHEventResult::pack(aPack);
	
	aPack << qualitative;
	aPack << rating;
	
	return aPack;
}

CPack& CHEventResult::unpack(CPack& aPack)
{
	GTHEventResult::unpack(aPack);
	
	aPack >> qualitative;
	aPack >> rating;
	
	return aPack;
}

RWCString CHEventResult::msl() const
{
	RWCString str = GTHEventResult::msl();


	GBuffer aBuffer;

	//quitamos el otro salto de línea.
	RWCString cadena=str;
	char ant[300];
	char * punt=strstr(cadena,endLine);
	int lon=cadena.length()-strlen(punt);

	strncpy(ant,cadena,lon); ant[lon]=0;

	return RWCString(ant) +  RWCString (aBuffer		<< qualitative
													<< rating
													<< endLine );
}

RWCString CHEventResult::mslDescription(const char *language) const
{
	return GTHEventResult::mslDescription(language);
}



//////////////////////////////////////////////////////////////////////
// Sets
//////////////////////////////////////////////////////////////////////
void CHEventResult::setQualitative(const char * value)
{ 
	qualitative=value; 
}
void CHEventResult::setRating(const short value)
{
	rating = value;
}
//////////////////////////////////////////////////////////////////////
// Gets
//////////////////////////////////////////////////////////////////////

GQualitative * CHEventResult::getQualitative() const
{
	return GMemoryDataBase::findQualitative(qualitative);
}

RWCString CHEventResult::getQualitativeCode() const
{	
	return qualitative;
}
short CHEventResult::getRating() const
{
	return rating;
}
RWCString CHEventResult::getRatingAsString() const
{ 
	RWCString aux="-";
	char tmp[10];
	
	if (rating)
		aux=itoa(rating,tmp,10);
	return aux; 
}
//////////////////////////////////////////////////////////////////////
// Help Methods
//////////////////////////////////////////////////////////////////////
RWCString CHEventResult::getIsoCountry() const
{
	return getRegister() ? getRegister()->getIsoCountry() : "";
}

RWWString CHEventResult::getGroup() const
{
	return RWWString(GTHEventResult::getGroup(),RWWString::multiByte);
}

RWWString CHEventResult::getQualitativeSDescription(const char * language/*=DBApplication::getAppLanguage()*/) const
{
	return getQualitative() ? getQualitative()->getSDescription(language) : NULLRWWSTRING;
}

RWWString CHEventResult::getQualitativeLDescription(const char * language/*=DBApplication::getAppLanguage()*/) const
{
	return getQualitative() ? getQualitative()->getLDescription(language) : NULLRWWSTRING;
}

RWBoolean CHEventResult::isQualitative() const
{
	if(getQualitative() && getQualitativeCode()!=OK)
		return true;

	return false;
}
CHPoolResult * CHEventResult::getPoolResult()
{
	RWSetIterator iter(CHMemoryDataBase::getColPoolResults());
	
	CHPoolResult *pPoolResult = 0;
	while ((pPoolResult = (CHPoolResult*) iter())!=0 )
	{
		if (pPoolResult->getInscription() == getInscription())
			return pPoolResult;
	}

	return NULL;
}
float CHEventResult::getPointsPoolResult()
{
	CHPoolResult *pPoolResult=getPoolResult();
	if(pPoolResult)
		return pPoolResult->getPointsF();
	
	return 0;
}

RWCString CHEventResult::getPointsPoolResultStr()
{
	CHPoolResult *pPoolResult=getPoolResult();
	if(pPoolResult)
		return pPoolResult->getPointsFStr();
	
	return NULLRWSTRING;
}