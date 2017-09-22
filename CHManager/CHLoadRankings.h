#pragma once
#include "CHManagerDefs.h"

class CHPool;
class CHPoolResult;

class CHLoadRankings
{
public:
	CHLoadRankings(CHPool* pPool);
	~CHLoadRankings(void);

	void			browseFile(HWND handle);
	MSLString		processFile(MSLWString path);
	void			doOut();

private:	
	bool			processLine(MSLString& line, short idx);
	CHPoolResult*	findResult(short code, bool seed);

private:
	MSLSet		m_elems;
	CHPool*		m_pPool;
	short		m_lastRk;
};

