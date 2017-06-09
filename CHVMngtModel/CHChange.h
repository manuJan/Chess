// CHChange.h: interface for the CHChange class.
//
//////////////////////////////////////////////////////////////////////

#pragma once
#include "CHVMngtModelDefs.h"

class CHChange : public GData  
{
public:
	CHChange(int _numberS1, int _numberS2);
	virtual ~CHChange();

	void setKey();
		
	//Overloaded operators
	GData& operator= (const GData& copy);
	bool   operator==(const GData& copy);
	bool   operator!=(const GData& copy);
		
	int getNumberS1();
	int getNumberS2();

private:
	
	int numberS1;
	int numberS2;
};

