// CHPermutationNumber.cpp: implementation of the CHPermutationNumber class.
//
//////////////////////////////////////////////////////////////////////
#include "stdVCH.h"
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
	sprintf(tmp,"%d",number);
	key=tmp;	
}

RWBoolean CHPermutationNumber::operator !=(const CHPermutationNumber& copy)
{
	return !comparePermutationNumber(copy);
}

RWBoolean CHPermutationNumber::operator ==(const CHPermutationNumber& copy)
{
	return comparePermutationNumber(copy);
}

CHPermutationNumber& CHPermutationNumber::operator =(const CHPermutationNumber& copy)
{
	copyPermutationNumber(copy);
	return *this;
}

void CHPermutationNumber::copyPermutationNumber(const CHPermutationNumber& copy)
{
	number = copy.number;	
}

RWBoolean CHPermutationNumber::comparePermutationNumber(const CHPermutationNumber& copy)
{
	RWBoolean value= false;

	if ( number		==	copy.number	)
		 value= true;

	return value;
}

int CHPermutationNumber::getNumber()
{
	return number;
}	

CPack& CHPermutationNumber::pack(CPack& aPack)
{
	return aPack;
}

CPack& CHPermutationNumber::unpack(CPack& aPack)
{
	return aPack;
}
