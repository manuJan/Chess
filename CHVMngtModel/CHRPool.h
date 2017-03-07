/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHRPool.h
*   Description	: Cuadro clasificatorio de preliminares (uso en listados)
*
*	Author		: CH Team
*	Date created: 22-12-2005
* 	Project		:
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#if !defined(AFX_CHRPOOL_H__026A4F5F_0515_4E72_9903_F07BC6FD2363__INCLUDED_)
#define AFX_CHRPOOL_H__026A4F5F_0515_4E72_9903_F07BC6FD2363__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CHReportTemplate.h"
#include "CHRC76.h"

class CHPool;
class CHPoolResult;
static int ordRound;
class CHRPool : public GData  
{
public:
	CHRPool(CHReportTemplate * pTpt,CReport * pRe,CHPool *_pPool,int &nLines, CHRC76::typeReport _repType);
	virtual ~CHRPool();

	RWBoolean uSQL(RWDBConnection& pConnect,RWBoolean remove=false);

	RWBoolean operator !=(const CHRPool & copy);
	RWBoolean operator ==(const CHRPool & copy);
	CHRPool & operator =(const CHRPool & copy);

	void setKey();

	CPackObject getPackObject();
	CPack& pack(CPack &iPack);
	CPack& unpack(CPack &iPack);

	RWCString msl() const;
	RWCString mslDescription(const char *language) const;

	RWBoolean	runLis(const int x,const int y, int &xPool, short _round=0,
		short _twice=0, short _heightTwice=0); // solo la posición x , porque siempre es centrado

public:
	RWBoolean		OnBeginReport();
	unsigned short	OnCallbackFn(struct USR_TAB * pTableInfo);

	CHPool*			getPool()
	{ return pPool;}

	int				getHeight(short _heightTwice=-1);
	int				getWidth();
	int				getRealWidth();
	short			getNumRounds();
	short			getTwice();
	short			getHeightTwice();

protected:
	RWCString		getNameOfSourceLis();
	
	int				loadData();
	void			poolDesc();
	void			roundDesc();
	void			teamCode(const short nC);
	void			teamScores(const short nC,const short nT);
	void			teamData();
	RWCString		getResult(const size_t line,const size_t col,const RWBoolean inverse=false) const;


private:

	CHReportTemplate * pReportTemplate;
	CHPool			 * pPool;
		
	GSortedVector	vPoolResults;
	CHPoolResult	* pCurrentPoolResult;
	
	CReport			* pReport;
	CLis			* pLis;

	int				pX,
					pY,
					center;

	int				nIndex;
	CHRC76::typeReport repType;
	RWBoolean		newPage;
	short			round, twice, heightTwice, nMaxLines;
};

#endif // !defined(AFX_CHRPOOL_H__026A4F5F_0515_4E72_9903_F07BC6FD2363__INCLUDED_)
