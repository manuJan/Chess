// CHPermutationNumber.cpp: implementation of the CHPermutationNumber class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CHPermutationNumber.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHPermutationNumber::CHPermutationNumber(int _number)
:number(_number)
{
	setKey();
}

CHPermutationNumber::~CHPermutationNumber()
{

}

void CHPermutationNumber::setKey() 
{
	char tmp[100];
	sprintf_s(tmp,"%d",number);
	key=tmp;	
}

bool CHPermutationNumber::operator !=(const GData& copy)
{
	return !operator==(copy);
}

bool CHPermutationNumber::operator ==(const GData& copy)
{
	CHPermutationNumber& aCopy = (CHPermutationNumber&)copy;

	bool value= false;

	if ( number		==	aCopy.number	)
		 value= true;

	return value;
}

GData& CHPermutationNumber::operator =(const GData& copy)
{
	CHPermutationNumber& aCopy = (CHPermutationNumber&)copy;

	number = aCopy.number;	

	return *this;
}


int CHPermutationNumber::getNumber()
{
	return number;
}	

