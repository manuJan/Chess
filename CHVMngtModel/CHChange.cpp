// CHChange.cpp: implementation of the CHChange class.
//
//////////////////////////////////////////////////////////////////////
#include "stdVCH.h"
#include "CHChange.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHChange::CHChange(int _numberS1, int _numberS2)
:numberS1(_numberS1)
,numberS2(_numberS2)
{
	setKey();
}

CHChange::~CHChange()
{

}

void CHChange::setKey() 
{
	char tmp[100];
	sprintf(tmp,"%d_%d",numberS1,numberS2);
	key=tmp;	
}

RWBoolean CHChange::operator !=(const CHChange& copy)
{
	return !compareChange(copy);
}

RWBoolean CHChange::operator ==(const CHChange& copy)
{
	return compareChange(copy);
}

CHChange& CHChange::operator =(const CHChange& copy)
{
	copyChange(copy);
	return *this;
}

void CHChange::copyChange(const CHChange& copy)
{
	numberS1 = copy.numberS1;	
	numberS2 = copy.numberS2;	
}

RWBoolean CHChange::compareChange(const CHChange& copy)
{
	RWBoolean value= false;

	if ( numberS1	==	copy.numberS1	&& 
		 numberS2	==	copy.numberS2)
		 value= true;

	return value;
}

int CHChange::getNumberS1()
{
	return numberS1;
}	

int CHChange::getNumberS2()
{
	return numberS2;
}	

CPack& CHChange::pack(CPack& aPack)
{
	return aPack;
}

CPack& CHChange::unpack(CPack& aPack)
{
	return aPack;
}
