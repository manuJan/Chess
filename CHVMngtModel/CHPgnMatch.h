// CHPgnMatch.h: interface for the CHPgnMatch class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHPGNMATCH_H)
#define AFX_CHPGNMATCH_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHVMNGTDLL_H
	#include "CHVMngtModelDll.h"
#endif // _CHVMNGTDLL_H

#include <core\G\GData.h>

class CHVMngtExport CHPgnMatch : public GData  
{
public:
	CHPgnMatch(int _game);
	virtual ~CHPgnMatch();

	RWCString setKey() const;

	RWBoolean uSQL(RWDBConnection& pConnect,RWBoolean remove=false)
	{
		return false;
		UNREFERENCED_PARAMETER(remove);
		UNREFERENCED_PARAMETER(pConnect);
	}

	//Overloaded operators
	RWBoolean operator !=(const CHPgnMatch& copy);
	RWBoolean operator ==(const CHPgnMatch& copy);
	CHPgnMatch& operator =(const CHPgnMatch& copy);

	void copyPgnMatch(const CHPgnMatch& copy);
	RWBoolean comparePgnMatch(const CHPgnMatch& copy);


	CPack& pack(CPack& aPack);
	CPack& unpack(CPack& aPack);

	void process(RWCString line);
	
	int			getGame();
	RWCString	getEventName();
	RWCString	getEventPlace();
	RWCString	getDate();
	RWCString	getRound();
	RWCString	getWhite();
	RWCString	getBlack();
	RWCString	getResult();
	RWCString   getHistoric();
	RWCString   getECO();
	CHMatch*	getMatch();
	
	void		setMatch(CHMatch* value);

private:
	int			game;
	RWCString	eventName;
	RWCString	eventPlace;
	RWCString	date;
	RWCString	round;
	RWCString	white;
	RWCString	black;
	RWCString	result;
	RWCString	historic;	
	RWCString	eco;

	CHMatch*	pMatch;
};

#endif // !defined(AFX_CHPGNMATCH_H)
