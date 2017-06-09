// CHPermutationNumber.h: interface for the CHPermutationNumber class.
//
//////////////////////////////////////////////////////////////////////


#pragma once
#include "CHVMngtModelDefs.h"

class CHPermutationNumber : public GData  
{
public:
	CHPermutationNumber(int _number);
	virtual ~CHPermutationNumber();

	void setKey();

	//Overloaded operators
	GData& operator= (const GData& copy);
	bool   operator==(const GData& copy);
	bool   operator!=(const GData& copy);

	int getNumber();

private:
	int number;
};


