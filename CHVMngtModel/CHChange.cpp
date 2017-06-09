// CHChange.cpp: implementation of the CHChange class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
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
	sprintf_s(tmp,"%d_%d",numberS1,numberS2);
	key=tmp;	
}

bool CHChange::operator !=(const GData& copy)
{
	return !operator==(copy);
}

bool CHChange::operator ==(const GData& copy)
{
	CHChange &aCopy = (CHChange &)copy;

	bool value= false;

	if ( numberS1	==	aCopy.numberS1	&& 
		 numberS2	==	aCopy.numberS2)
		 value= true;

	return value;
}

GData& CHChange::operator =(const GData& copy)
{
	CHChange &aCopy = (CHChange &)copy;

	numberS1 = aCopy.numberS1;	
	numberS2 = aCopy.numberS2;	

	return *this;
}

int CHChange::getNumberS1()
{
	return numberS1;
}	

int CHChange::getNumberS2()
{
	return numberS2;
}	

