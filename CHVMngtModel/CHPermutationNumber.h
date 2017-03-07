// CHPermutationNumber.h: interface for the CHPermutationNumber class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHPERMUTATIONNUMBER_H__C909A61C_04ED_496B_BCDC_29A29ED82835__INCLUDED_)
#define AFX_CHPERMUTATIONNUMBER_H__C909A61C_04ED_496B_BCDC_29A29ED82835__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <core\G\GData.h>

class CHPermutationNumber : public GData  
{
public:
	CHPermutationNumber(int _number);
	virtual ~CHPermutationNumber();

	void setKey();

	RWBoolean uSQL(RWDBConnection& pConnect,RWBoolean remove=false)
	{
		return false;
		UNREFERENCED_PARAMETER(remove);
		UNREFERENCED_PARAMETER(pConnect);
	}	

	//Overloaded operators
	RWBoolean operator !=(const CHPermutationNumber& copy);
	RWBoolean operator ==(const CHPermutationNumber& copy);
	CHPermutationNumber& operator =(const CHPermutationNumber& copy);

	void copyPermutationNumber(const CHPermutationNumber& copy);
	RWBoolean comparePermutationNumber(const CHPermutationNumber& copy);

	CPack& pack(CPack& aPack);
	CPack& unpack(CPack& aPack);

	int getNumber();

private:
	int number;
};

#endif // !defined(AFX_CHPERMUTATIONNUMBER_H__C909A61C_04ED_496B_BCDC_29A29ED82835__INCLUDED_)
