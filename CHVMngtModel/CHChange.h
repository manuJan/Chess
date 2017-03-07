// CHChange.h: interface for the CHChange class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHCHANGE)
#define AFX_CHANGE

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <core\G\GData.h>

class CHChange : public GData  
{
public:
	CHChange(int _numberS1, int _numberS2);
	virtual ~CHChange();

	void setKey();

	RWBoolean uSQL(RWDBConnection& pConnect,RWBoolean remove=false)
	{
		return false;
		UNREFERENCED_PARAMETER(remove);
		UNREFERENCED_PARAMETER(pConnect);
	}	

	//Overloaded operators
	RWBoolean operator !=(const CHChange& copy);
	RWBoolean operator ==(const CHChange& copy);
	CHChange& operator =(const CHChange& copy);

	void copyChange(const CHChange& copy);
	RWBoolean compareChange(const CHChange& copy);

	CPack& pack(CPack& aPack);
	CPack& unpack(CPack& aPack);

	int getNumberS1();
	int getNumberS2();

private:
	
	int numberS1;
	int numberS2;
};

#endif // !defined(AFX_CHANGE)
