/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHRPool.cpp
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
#include "stdVCH.h"
#include "CHRPool.h"
#include <Sports/CH/Data/CHMemoryDataBase.h>

static int orderPoolResultsByRankPo(const GVectorElement** a, const GVectorElement** b)
{
	CHPoolResult * pPoolResultA = (CHPoolResult *)(*a)->getElement();
	CHPoolResult * pPoolResultB = (CHPoolResult *)(*b)->getElement();
	
	if( pPoolResultA->getRankPo() || pPoolResultB->getRankPo() )
	{
		if( !pPoolResultA->getRankPo() )
			return 1;
		if( !pPoolResultB->getRankPo() )
			return -1;
		int order = pPoolResultA->getRankPo() - pPoolResultB->getRankPo();
		if( order )
			return order;
	}

	return pPoolResultA->getOrder() - pPoolResultB->getOrder();
}
static int orderPoolResultsByPos(const GVectorElement** a, const GVectorElement** b)
{
	CHPoolResult * pPoolResultA = (CHPoolResult *)(*a)->getElement();
	CHPoolResult * pPoolResultB = (CHPoolResult *)(*b)->getElement();

	return pPoolResultA->getOrder() - pPoolResultB->getOrder();
}
static int orderPoolResultsByRound(const GVectorElement** a, const GVectorElement** b)
{
	CHPoolResult * pPRA = (CHPoolResult *)(*a)->getElement();
	CHPoolResult * pPRB = (CHPoolResult *)(*b)->getElement();

	CHEvent *pEvent=(CHEvent*)pPRA->getEvent();

	float forder=0.0;
	int order=0;
	for(short i=0;i<pEvent->getNumRankOrder();i++)
	{
		CHEvent::TypeRank typeRnk=pEvent->getRankOrder(i);
		switch(typeRnk)
		{
			case CHEvent::eQualitative:
			{// Qualitative
				if (pPRA->getQualitativeCode()!=OK && pPRA->getQualitativeCode()!=NULLRWSTRING &&
					pPRB->getQualitativeCode()!=OK && pPRB->getQualitativeCode()!=NULLRWSTRING  )
				{
					GQualitative * pQA = pPRA->getQualitative();
					GQualitative * pQB = pPRB->getQualitative();
					if (pQA && pQB)
					{
						order=pQA->getSort() - pQB->getSort();
						if (order)
							return order;
					}
				}
				if (pPRA->getQualitativeCode()!=OK && pPRA->getQualitativeCode()!=NULLRWSTRING)
					return 1;
				if (pPRB->getQualitativeCode()!=OK && pPRB->getQualitativeCode()!=NULLRWSTRING)
					return -1;		
				break;
			}
			case CHEvent::ePoints:
			{// Points
				forder=pPRB->getPointsFR(ordRound) - pPRA->getPointsFR(ordRound);
				order=forder>0?1:(forder<0?-1:0);
				if (order)
					return order;
			}
			case CHEvent::eSolkoff:
			{// Solkoff
				forder=pPRB->getSolkOffF(ordRound) - pPRA->getSolkOffF(ordRound);
				order=forder>0?1:(forder<0?-1:0);
				if (order)
					return order;
				break;
			}
			case CHEvent::eSonneBerger:
			{// SonneBerger
				forder=pPRB->getSonneBergerF(ordRound) - pPRA->getSonneBergerF(ordRound);
				order=forder>0?1:(forder<0?-1:0);
				if (order)
					return order;
				break;
			}
			case CHEvent::eProgressiveScore:
			{// Progressive
				forder=pPRB->getProgresiveF(ordRound) - pPRA->getProgresiveF(ordRound);
				order=forder>0?1:(forder<0?-1:0);
				if (order)
					return order;
				break;
			}

			case CHEvent::eRating:
			{// eRating
				order=pPRB->getInscriptionRating() - pPRA->getInscriptionRating();
				if (order)
					return order;
				break;
			}
		}
	}
	order=pPRB->getInscriptionRating() - pPRA->getInscriptionRating();
	if (order)
		return order;
	return pPRA->getOrder() - pPRB->getOrder();
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHRPool::CHRPool(CHReportTemplate * pTpt,CReport * pRe,CHPool *_pPool,int &nLines, CHRC76::typeReport _repType)
:pReportTemplate(pTpt)
,pReport(pRe)
,pLis(0)
,pPool(_pPool)
,pX(-1)
,pY(-1)
,center(0)
,nIndex(0)
,repType(_repType)
,pCurrentPoolResult(0)
,round(0)
,twice(1)
,heightTwice(1)
,nMaxLines(28)
{
	nLines += loadData();
}

CHRPool::~CHRPool()
{
}

void CHRPool::setKey()
{
	if (pPool)
	{
		key=pPool->getKey();
	}
}

RWCString CHRPool::msl() const
{
	return NULLRWSTRING;
}
	
RWCString CHRPool::mslDescription(const char *language) const
{
	UNREFERENCED_PARAMETER(language);
	return NULLRWSTRING;
}

RWBoolean CHRPool::uSQL(RWDBConnection& pConnect,RWBoolean remove/*=false*/)
{
	UNREFERENCED_PARAMETER(pConnect);
	UNREFERENCED_PARAMETER(remove);
	return false;
}

CPack& CHRPool::pack(CPack &iPack)
{	
	return iPack;
}

CPack& CHRPool::unpack(CPack &iPack)
{
	return iPack;
}

int	CHRPool::loadData()
{
	vPoolResults = pPool->getPoolResultsVector();
	vPoolResults.sort(repType==CHRC76::eSchedule?orderPoolResultsByPos:(repType==CHRC76::ePreliminarySummary?orderPoolResultsByRound:orderPoolResultsByRankPo));
	return vPoolResults.entries();
}

RWCString CHRPool::getNameOfSourceLis()
{
	RWCString lang = DBApplication::getAppLanguage();
	return CHMemoryDataBase::getDiscipline().getCode()+"RPool."+lang+".lis";
}

RWBoolean CHRPool::OnBeginReport()
{
	if (nMaxLines<pPool->getPoolResultsVector().entries())
		return false;
	CReportManager& aReportMng=pReport->getManager();
	CLis& aLis=pReport->setLis(getNameOfSourceLis());
	pLis=&aLis;

	int width=aReportMng.getWidthPaper()-aReportMng.getLeftMargin();
	if (getWidth()>width)
		//tengo que dividirlo en dos veces
		twice=2;

	if( !pLis->isValid() )
	{
		AfxMessageBox(RWWString(aReportMng.getLastError()+"\n"+getNameOfSourceLis(),RWWString::ascii));
		pLis=0;
	}
	// CallBacks
	pLis->setCallBack(100,pReportTemplate);	
	// Codigo NOC, NPC, CGA, dependiente del .lis de cabeceras
	CLis * pHeaderLis = pReportTemplate->getHeaderLis();
    if( pHeaderLis )
		pLis->setData(212,pHeaderLis->getData(300)); 

	int height=aReportMng.getHeightPaper()-aReportMng.getBottonMargin()-aReportMng.getTopMargin();
	if (getHeight()>height)
	{
		//tengo que dividirlo en X veces
		heightTwice=((vPoolResults.entries()%nMaxLines)?((vPoolResults.entries()/nMaxLines)+1):(vPoolResults.entries()/nMaxLines));
	}

	return pLis!=0;
}

unsigned short CHRPool::OnCallbackFn(struct USR_TAB * pTabInf)
{
	if( pTabInf->Tb==100 && 
		pTabInf->Te==2  && 
		pTabInf->Ce==1 )
	{
		if (pPool->getNumRounds()==1)
		poolDesc();	// Pool description ( Group A, B...)
		else if (pPool->getNumRounds()>1)
			roundDesc(); //Round description (Round 1, 2...)
	}

	if( pTabInf->Tb==100 && 
		pTabInf->Te==2   && 
		pTabInf->Ce==3 )
		teamCode(short(pTabInf->C_Count-1));// NOC's horiz.

	
	if( pTabInf->Tb==100 && 
		pTabInf->Te==3)	
	{
		if( pTabInf->Ce==1 )
			teamData();
		else if( pTabInf->Ce==3 )
			teamScores(pTabInf->C_Count,pTabInf->T_Count);			// Scores
	}
	newPage=false;	
    return PRNALL;
}

int CHRPool::getWidth()
{
	int w=0;
	w = pLis->getVari(117) + (repType==CHRC76::eFinalSummary?0:(vPoolResults.entries() * pLis->getVari(103))); // nº de paises de la pool * ancho de una celda
	w += (repType==CHRC76::eSchedule?0:pLis->getVari(124) * pLis->getVari(103)); //nº de celdas estáticas * ancho de celda
	w += pLis->getVari(103); //NOC, CGA ... 
	if (!pLis->getVari(115))
		w -= pLis->getVari(103);
	return w;
}

int CHRPool::getRealWidth()
{
	int w=0;
	w = pLis->getVari(117) + pLis->getVari(104) * pLis->getVari(103); // nº de paises de la pool * ancho de una celda
	w += (pLis->getVari(125)*pLis->getVari(124)) * pLis->getVari(103); //nº de celdas estáticas * ancho de celda
	w += pLis->getVari(103); //NOC, CGA ... 
	if (!pLis->getVari(115))
		w -= pLis->getVari(103);
	return w;
}

int CHRPool::getHeight(short _heightTwice/*=-1*/)
{
	if (_heightTwice==-1)
		return vPoolResults.entries()*pLis->getVari(200)+pLis->getVari(200);
	short maxLines=nMaxLines;
	if (nMaxLines*(_heightTwice+1)>short(vPoolResults.entries()))
		maxLines=vPoolResults.entries()-short(nMaxLines*_heightTwice);
	return maxLines*pLis->getVari(200)+pLis->getVari(200);
}

short CHRPool::getNumRounds()
{
	return pPool?pPool->getNumRounds():0;
}

short CHRPool::getTwice()
{
	return twice;
}
short CHRPool::getHeightTwice()
{
	return heightTwice;
}
RWBoolean CHRPool::runLis(const int x,const int y, int &xPool,short _round,short _twice,short _heightTwice)
{
	round=_round;
	ordRound=_round;
	int nl=pPool->getNumCompetitors();
	if( nl==0 )
		return false;

	int tamCelda = pLis->getVari(103);

	pLis->setVari(104,nl);
	short maxLines=nMaxLines;
	if (nMaxLines*(_heightTwice+1)>short(vPoolResults.entries()))
		maxLines=vPoolResults.entries()-short(nMaxLines*_heightTwice);
	pLis->setVari(126,maxLines);//nl
	pLis->setVari(105,(nl+2)*tamCelda);
	pLis->setVari(106,4*tamCelda);
	pLis->setVari(107,3*tamCelda);
	pLis->setVari(108,pLis->getVari(105)/2);
	pLis->setVari(109,pLis->getVari(106)/2);
	pLis->setVari(110,pLis->getVari(107)/2);

	pLis->setVari(115,0);
	if (repType==CHRC76::ePreliminarySummary)
	{
		pLis->setVari(115,1);
	}

	pLis->setVari(125,1);
	if (twice==2 && repType==CHRC76::ePreliminarySummary)
	{
		pLis->setVari(125,!_twice?0:1);
		pLis->setVari(104,!_twice?nl:0);
	}
	if (repType==CHRC76::eFinalSummary)
		pLis->setVari(104,0);
	if (repType==CHRC76::eSchedule)
		pLis->setVari(125,0);
	// posicion de la tabla
	xPool=x - (getRealWidth()/2);
	if (xPool<0) xPool=0;
	pLis->setVari(101,xPool);
	pLis->setVari(102,y);

	pReport->setZeroAs("0");
	
	vPoolResults.sort(repType==CHRC76::eSchedule?orderPoolResultsByPos:(repType==CHRC76::ePreliminarySummary?orderPoolResultsByRound:orderPoolResultsByRankPo));
	RWBoolean rc=pLis->runline(100);
	pReport->setZeroAs("");		
	
	nIndex=0;
	return rc;
}

void CHRPool::poolDesc()
{
	if (!pPool)
		return;

	RWWString poolDesc = NULLRWWSTRING;
	if (pPool->getPhase()->getIsPool())
	{
		poolDesc += pPool->getLDescription(pPool->getPhase()->getPoolDescription());
	}
	else 
		poolDesc += pPool->getPhase()->getSDescription();

	pLis->setData(411,poolDesc);
}

void CHRPool::roundDesc()
{
		// compongo ronda xxx
		CString ronda;
		ronda.Format(_T("%s %d"),RWWString(pLis->getData(217),RWWString::ascii),round);
		pLis->setData(411,ronda);
}

void CHRPool::teamCode(const short nC)
{
	if (vPoolResults[nC])
	{
		pCurrentPoolResult = (CHPoolResult*) vPoolResults[nC]->getElement();
		if (pCurrentPoolResult)
		{
			// Name
			pLis->setData(402,pCurrentPoolResult->getGroup());
		}
	}
}

void CHRPool::teamScores(const short nC,const short nT)
{	// Si cambia de template se inicializa la X.
	if (pY != nT)
		pX = 1;
	else
		pX=nC;
	
	pY=nT;
	RWCString cad=NULLRWSTRING;

	pLis->setData(425,"");
	if( pX!=pY )
	{
		pLis->setVari(113,0); // Sin relleno
		cad=getResult(pY-1,pX-1);
		if( cad == NULLRWSTRING)// sino invertimos el resultado.
			cad=getResult(pX-1,pY-1,true);
	}
	else
		pLis->setVari(113,pLis->getVari(114));// Relleno
	
	pLis->setVari(157,4050);
	if (repType==CHRC76::ePreliminarySummary)
		pLis->setVari(157,4080);
	int fontSize = pLis->getVari(157);
	size_t a = pLis->widthString(fontSize,cad);
	while (a>pLis->getVari(103)) //no todos los resultados entran
		a = pLis->widthString((fontSize-=10),cad);
	pLis->setVari(157,fontSize);
	pLis->setData(420,cad);
}

void CHRPool::teamData()
{
	GVectorElement * pElement	= vPoolResults[nIndex++];
	pCurrentPoolResult = pElement ? (CHPoolResult*) pElement->getElement() : 0;
	if (!pCurrentPoolResult)
		return;
	// Rank
	if (pCurrentPoolResult->getRank() >0)
		pLis->setData(400,pCurrentPoolResult->getRank());
	else
		pLis->setData(400,"");
	// Name
	pLis->setData(421,pCurrentPoolResult->getPrnSName());
	// NOC
	pLis->setData(402,pCurrentPoolResult->getGroup());
	// No
	pLis->setData(400,pCurrentPoolResult->getRank());
	// PNo
	pLis->setData(404,pCurrentPoolResult->getRankPo());
	// Score
	pLis->setData(405,pCurrentPoolResult->getPoolPointsFStr(round));
	// WP
	pLis->setData(407,pCurrentPoolResult->getSolkOffFStr(round));
	// SB
	pLis->setData(422,pCurrentPoolResult->getSonneBergerFStr(round));
	// PS
	pLis->setData(423,pCurrentPoolResult->getProgressiveFStr(round));
	// rat.
	pLis->setData(408,pCurrentPoolResult->getInscriptionRating());
	//TPR
//	pLis->setData(409,pCurrentPoolResult->());
	// W-We
//	pLis->setData(424,pCurrentPoolResult->());
}

RWCString CHRPool::getResult(const size_t line,const size_t col,const RWBoolean inverse/*=false*/) const
{
	UNREFERENCED_PARAMETER(inverse);

	RWCString rc=NULLRWSTRING;

	if (vPoolResults.entries() <= line || vPoolResults.entries() <= col)
		return rc;

	CHPoolResult *pPRLine=(CHPoolResult *)vPoolResults[line]->getElement();
	short sLine=pPRLine?pPRLine->getOrder():short(-1);

	CHPoolResult *pPRCol=(CHPoolResult *)vPoolResults[col]->getElement();
	short sCol=pPRCol?pPRCol->getOrder():short(-1);

	if( sLine == -1 || sCol == -1 )
		return rc;
	
	CHPool *pPool=(CHPool *)pPRCol->getPool();
	if( !pPool )
		return rc;

	CHMatch *pMatch = 0;
	CHMatchResult *pMRLine=0,*pMRCol=0;

	GSortedVector& vMatchs=pPool->getMatchsVector();
		
	for(size_t i=0;i<vMatchs.entries();i++)
	{	
		pMatch=(CHMatch *)vMatchs[i]->getElement();
		if (!pMatch)
			continue;
		if (pMatch->getRound()!=round)
			continue;

		pLis->setVari(201,repType==CHRC76::eSchedule?1005:1004);
		pMRLine=(CHMatchResult *)(pMatch->getMatchResult(0));
		pMRCol=(CHMatchResult *)(pMatch->getMatchResult(1));
		if (pMRLine->getPoolPosition()==sLine &&
			pMRCol->getPoolPosition()==sCol &&
			repType==CHRC76::eSchedule && pMatch->getStartDate().isValid())
		{
			RWCString time=pMatch->getStartTime().isValid()?RWCString((pMatch->getStartTime().asString("%H:%M")).strip(RWCString::leading,'0')):"";
			pLis->setData(425,time);
			return toUpper(pMatch->getStartDateAsString("%d %b").strip(RWCString::leading,'0'));
		}

		pMRLine=pMatch->getMatchResultHome();
		pMRCol=pMatch->getMatchResultAway();

		if (( pMRLine && pMRLine->getPoolPosition()==sLine )
			 &&
			( pMRCol && pMRCol->getPoolPosition()==sCol ) &&
			repType!=CHRC76::eSchedule)
		{
			pLis->setVari(201,pMatch->getStatus() >= CHMemoryDataBase::eRunning?1004:1005);
			size_t pos=RW_NPOS;
			RWCString home=pMRLine->getPointsAsString();
			pos=home.index(pMRLine->getPoints()>1?".5":"0.5");
			if (pos!=RW_NPOS)
			{
				home.remove(pos,pMRLine->getPoints()>1?2:3);
				home+="½";
			}
			if (pMRLine->isQualitative())
				home+=pMRLine->getQualitativeSDescription().toAscii();
			RWCString away=pMRCol->getPointsAsString();
			pos=away.index(pMRCol->getPoints()>1?".5":"0.5");
			if (pos!=RW_NPOS)
			{
				away.remove(pos,pMRCol->getPoints()>1?2:3);
				away+="½";
			}
			if (pMRCol->isQualitative())
				home+=pMRCol->getQualitativeSDescription().toAscii();
			if( pMatch->getStatus() >= CHMemoryDataBase::eRunning )
			{
				char tmp[20];
				if( inverse )
					sprintf(tmp,"%s-%s",away,home);
				else
					sprintf(tmp,"%s-%s",home,away);
				return tmp;
			}
			else
			{
				RWCString time=pMatch->getStartTime().isValid()?RWCString((pMatch->getStartTime().asString("%H:%M")).strip(RWCString::leading,'0')):"";
				pLis->setData(425,time);
				return toUpper(pMatch->getStartDateAsString("%d %b").strip(RWCString::leading,'0'));
			}
		}
	}
	return rc;
}
