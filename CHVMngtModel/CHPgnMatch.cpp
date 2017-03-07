// CHPgnMatch.cpp: implementation of the CHPgnMatch class.
//
//////////////////////////////////////////////////////////////////////
#include "stdVCH.h"
#include "CHPgnMatch.h"

CHPgnMatch::CHPgnMatch(int _game)
:game(_game)
,eventName(NULLRWSTRING)
,eventPlace(NULLRWSTRING)
,date(NULLRWSTRING)
,round(NULLRWSTRING)
,white(NULLRWSTRING)
,black(NULLRWSTRING)
,result(NULLRWSTRING)
,historic(NULLRWSTRING)
,pMatch(0)
{
	setKey();
}

CHPgnMatch::~CHPgnMatch()
{
}

RWCString CHPgnMatch::setKey() const
{
	char tmp[10];
	sprintf(tmp,"%d",game);
	return tmp;
}

RWBoolean CHPgnMatch::operator !=(const CHPgnMatch& copy)
{
	return !comparePgnMatch (copy);
}

RWBoolean CHPgnMatch::operator ==(const CHPgnMatch& copy)
{
	return comparePgnMatch(copy);
}

CHPgnMatch& CHPgnMatch::operator =(const CHPgnMatch& copy)
{
	copyPgnMatch(copy);
	return *this;
}

void CHPgnMatch::copyPgnMatch(const CHPgnMatch& copy)
{
	game		= copy.game;
	eventName	= copy.eventName;
	eventPlace	= copy.eventPlace;
	date		= copy.date;
	round		= copy.round;
	white		= copy.white;
	black		= copy.black;
	result		= copy.result;
	historic	= copy.historic;	
	pMatch		= copy.pMatch;
}

RWBoolean CHPgnMatch::comparePgnMatch(const CHPgnMatch& copy)
{
	RWBoolean value= false;

	if (	game		== copy.game		&&
			eventName	== copy.eventName	&&
			eventPlace	== copy.eventPlace	&&
			date		== copy.date		&&
			round		== copy.round		&&
			white		== copy.white		&&
			black		== copy.black		&&
			result		== copy.result		&&
			historic	== copy.historic	&&
			pMatch		== copy.pMatch)			
			value= true;

	return value;
}

int	CHPgnMatch::getGame()
{
	return game;
}

RWCString CHPgnMatch::getEventName()
{
	return eventName;
}

RWCString CHPgnMatch::getEventPlace()
{
	return eventPlace;
}

RWCString CHPgnMatch::getDate()
{	
	return date;
}

RWCString CHPgnMatch::getRound()
{
	return round;
}

RWCString CHPgnMatch::getWhite()
{
	return white;
}

RWCString CHPgnMatch::getBlack()
{
	return black;
}

RWCString CHPgnMatch::getResult()
{
	return result;
}

RWCString CHPgnMatch::getECO()
{
	return eco;
}

RWCString CHPgnMatch::getHistoric()
{
	return historic;
}

CHMatch* CHPgnMatch::getMatch()
{
	return pMatch;
}

void CHPgnMatch::setMatch(CHMatch* value)
{
	pMatch = value;
}

void CHPgnMatch::process(RWCString line)
{
	size_t i = 0;
	
	size_t pos2 = 0;
	size_t pos = 0;
	
	RWCString aux=NULLRWSTRING;

	//Group
	pos = line.first('[');
	if (pos!=RW_NPOS)
	{
		// Event | Site | Date | Round | White | Black | Result | ECO
		pos2 = line.first(']');
		aux = line(pos+1,pos2-1);

		if (eventName==NULLRWSTRING)
			eventName=aux;
		else if (eventPlace==NULLRWSTRING)
			eventPlace=aux;		
		else if (date==NULLRWSTRING)
			date=aux;
		else if (round==NULLRWSTRING)
			round=aux;
		else if (white==NULLRWSTRING)
			white=aux;
		else if (black==NULLRWSTRING)
			black=aux;
		else if (result==NULLRWSTRING)
			result=aux;
		else if (eco==NULLRWSTRING)
			eco=aux;
	}
	else
	{
		historic+=line;
	}
}

CPack& CHPgnMatch::pack(CPack& aPack)
{
	return aPack;
}

CPack& CHPgnMatch::unpack(CPack& aPack)
{
	return aPack;
}
