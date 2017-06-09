/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHGroupDraw.cpp
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:23-12-2005
*   Project     :CHV Model               
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///

#include "stdafx.h"
#include "CHGroupDraw.h"
#include "CHPermutationNumber.h"
#include "CHCompetitorDraw.h"
#include "CHChange.h"

#include "..\CHMngtModel\CHPoolResult.h"
#include "..\CHMngtModel\CHPool.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

static int orderCompetitorsByRank(const MSLItem** a, const MSLItem** b)
{
	CHCompetitorDraw *pCA=(CHCompetitorDraw *)(*a);
	CHCompetitorDraw *pCB=(CHCompetitorDraw *)(*b);

	CHPoolResult *pA=pCA->getPoolResult();
	CHPoolResult *pB=pCB->getPoolResult();

	if( pA->getRankPo() || pB->getRankPo() )
	{
		if( !pA->getRankPo() )
			return 1;
		if( !pB->getRankPo() )
			return -1;
		int order = pA->getRankPo() - pB->getRankPo();
		if( order )
			return order;
	}

	float forder = pB->getPointsF() - pA->getPointsF();
	if (forder>0.0)
		return 1;
	else if (forder<0.0) 
		return -1;

	int order = pA->getInscriptionSeed() - pB->getInscriptionSeed();
	if (order)
		return order;

	if (pA->getMasterTypeOrder()==0 &&
		pB->getMasterTypeOrder()>0 )
		return 1;

	if (pA->getMasterTypeOrder()>0 &&
		pB->getMasterTypeOrder()==0 )
		return -1;

	order = pA->getMasterTypeOrder() - pB->getMasterTypeOrder();
	if (order)
		return order;

	if (pA->getRegister() && !pB->getRegister() )
		return -1;

	if (pB->getRegister() && !pA->getRegister() )
		return 1;

	if (pA->getRegister() && pB->getRegister() )
	{
		order = _wcsicoll(pA->getRegister()->getPrnLName(),pB->getRegister()->getPrnLName());
		if (order)
			return order;
	}

	return strcmp(pA->getKey(),pB->getKey());
}


static int orderCompetitorsDrawByOrder(const MSLItem** a, const MSLItem** b)
{
	CHCompetitorDraw *pCA=(CHCompetitorDraw *)(*a);
	CHCompetitorDraw *pCB=(CHCompetitorDraw *)(*b);

	int order = pCA->getOrder() - pCB->getOrder();
	if (order)
		return order;

	return orderCompetitorsByRank(a,b);
}

static int orderCompetitorsDrawByFloatingUp(const MSLItem** a, const MSLItem** b)
{
	CHCompetitorDraw *pCA=(CHCompetitorDraw *)(*a);
	CHCompetitorDraw *pCB=(CHCompetitorDraw *)(*b);

	if (pCA->getFloatingUp() && pCB->getFloatingUp())
		return orderCompetitorsDrawByOrder(a,b);

	if (pCA->getFloatingUp())
		return -1;

	if (pCB->getFloatingUp())
		return 1;

	return orderCompetitorsDrawByOrder(a,b);
}

static int orderPermutations(const MSLItem** a, const MSLItem** b)
{
	CHPermutationNumber *pA=(CHPermutationNumber *)(*a);
	CHPermutationNumber *pB=(CHPermutationNumber *)(*b);

	int order = pA->getNumber() - pB->getNumber();
	if (order)
		return order;

	return strcmp(pA->getKey(),pB->getKey());
}


CHGroupDraw::CHGroupDraw(CHPool* _pPool, short _group, short _round)
:group(_group)
,round(_round)
,P(0)
,X(0)
,O(0)
,vCompetitorsDraw(orderCompetitorsByRank)
,vCompetitorsDrawPaired(orderCompetitorsByRank)
,vS1(orderCompetitorsDrawByOrder)
,vS2(orderCompetitorsDrawByOrder)
,transposition(0)
,changeS1S2(0)
,pPool(_pPool)
{
	vCompetitorsDraw.setFcCompare(orderCompetitorsByRank);
	vCompetitorsDrawPaired.setFcCompare(orderCompetitorsByRank);
	vS1.setFcCompare(orderCompetitorsDrawByOrder);
	vS2.setFcCompare(orderCompetitorsDrawByOrder);
	setKey();
}

CHGroupDraw::~CHGroupDraw()
{
	for (short i=0;i<vCompetitorsDraw.entries();i++)
	{
		CHCompetitorDraw* pCompetitorDraw = (CHCompetitorDraw*)vCompetitorsDraw[i];
		delete pCompetitorDraw;
	}
	
	vCompetitorsDraw.clear();
}

void CHGroupDraw::sortCompetitorsDraw(mslToolsFcCompare compare)
{
	vCompetitorsDraw.setFcCompare(compare);
	vCompetitorsDraw.sort();
}	

void CHGroupDraw::increaseTransposition()
{
	transposition++;
}

void CHGroupDraw::increaseChange()
{
	changeS1S2++;
}

void CHGroupDraw::resetTransposition()
{
	transposition=0;
}

void CHGroupDraw::resetChange()
{
	changeS1S2=0;
}

void CHGroupDraw::setKey() 
{
	char tmp[100];
	sprintf_s(tmp,"%d",group);
	key=tmp;
}

bool CHGroupDraw::operator !=(const GData& copy)
{
	return !operator==(copy);
}	

bool CHGroupDraw::operator ==(const GData& copy)
{
	CHGroupDraw& aCopy = (CHGroupDraw&)copy;

	bool value= false;

	if ( group	==	aCopy.group	&&
		 P		==	aCopy.P		&&
		 X		==	aCopy.X		)
		 value= true;

	return value;
}

GData& CHGroupDraw::operator =(const GData& copy)
{
	CHGroupDraw& aCopy = (CHGroupDraw&)copy;

	group	=	aCopy.group;	
	P		=	aCopy.P;
	X		=	aCopy.X;

	return *this;
}

short CHGroupDraw::getGroup()
{
	return group;
}
	
short CHGroupDraw::getRound()
{
	return round;
}

short CHGroupDraw::getX()
{
	return X;
}

short CHGroupDraw::getP()
{
	return P;
}

short CHGroupDraw::getTranspositions()
{
	return transposition;
}

short CHGroupDraw::getChanges()
{
	return changeS1S2;
}

bool CHGroupDraw::isHomogenic()
{
	if (!vCompetitorsDraw.entries())
		return false;

	CHCompetitorDraw* pCompetitorDraw = (CHCompetitorDraw*)vCompetitorsDraw[0];
	float groupPoints = 0.0;
	if (pCompetitorDraw->getPoolResult())
		groupPoints=pCompetitorDraw->getPoolResult()->getPointsF();	

	for (short i=0;i<vCompetitorsDraw.entries();i++)
	{
		pCompetitorDraw = (CHCompetitorDraw*)vCompetitorsDraw[i];
		if (!pCompetitorDraw ||
			!pCompetitorDraw->getPoolResult() || 
			groupPoints!=pCompetitorDraw->getPoolResult()->getPointsF())
			return false;
	}
	return true;
}

MSLSortedVector& CHGroupDraw::getCompetitorsDrawPairedVector()
{
	return vCompetitorsDrawPaired;
}

MSLItem* CHGroupDraw::setCompetitorsDrawPaired(CHCompetitorDraw* pCompetitorDraw)
{
	if (!vCompetitorsDrawPaired.find(pCompetitorDraw))
		return vCompetitorsDrawPaired.insert(pCompetitorDraw);
	return 0;
}

void CHGroupDraw::removeCompetitorsDrawPaired(CHCompetitorDraw& aCompetitorDraw)
{
	vCompetitorsDrawPaired.remove(&aCompetitorDraw);
}	

CHCompetitorDraw* CHGroupDraw::getCompetitorsDrawPaired(int index)
{
	if (vCompetitorsDrawPaired.entries()> short(index))
		return (CHCompetitorDraw*)vCompetitorsDrawPaired[index];
	return 0;
}

MSLSortedVector& CHGroupDraw::getCompetitorsDrawVector()
{
	return vCompetitorsDraw;
}

MSLItem* CHGroupDraw::setCompetitorsDraw(CHCompetitorDraw* pCompetitorDraw)
{
	if (!vCompetitorsDraw.find(pCompetitorDraw))
		return vCompetitorsDraw.insert(pCompetitorDraw);
	return 0;
}

void CHGroupDraw::removeCompetitorsDraw(CHCompetitorDraw& aCompetitorDraw)
{
	vCompetitorsDraw.remove(&aCompetitorDraw);
}

MSLSortedVector& CHGroupDraw::getCompetitorsS1Vector()
{
	return vS1;
}

CHCompetitorDraw* CHGroupDraw::getCompetitorsS1(int index)
{
	if (vS1.entries()> short(index))
		return (CHCompetitorDraw*)vS1[index];
	return 0;
}

MSLSortedVector& CHGroupDraw::getCompetitorsS2Vector()
{
	return vS2;
}

CHCompetitorDraw* CHGroupDraw::getCompetitorsS2(int index)
{
	if (vS2.entries()> short(index))
		return (CHCompetitorDraw*)vS2[index];
	return 0;
}

CHCompetitorDraw* CHGroupDraw::getCompetitorsDraw(int index)
{
	if (vCompetitorsDraw.entries() > short(index))
		return (CHCompetitorDraw*)vCompetitorsDraw[index];
	return 0;
}

CHCompetitorDraw* CHGroupDraw::InsertCompetitor(CHPoolResult* pPoolResult, short order)
{
	CHCompetitorDraw* pCompetitorDraw = new CHCompetitorDraw(pPoolResult,order,round);
	setCompetitorsDraw(pCompetitorDraw);
	return pCompetitorDraw;
}

int CHGroupDraw::getTotalTranspositionsInS2()
{
	return vS2Permutations.entries();

	/*short nEntries = vS2.entries();
	int numberTrns = 1;
	if(nEntries>0)
	{
		size_t index=1;
		for (size_t i=nEntries;i>0;i--)
			numberTrns=numberTrns*i;		
	}
	return numberTrns;*/
}	

int CHGroupDraw::getTotalChangesInS1S2()
{
	return vS1S2Changes.entries();
}

int CHGroupDraw::getTranspositionsInS2()
{
	int nEntries = vS2.entries();
	int numberTrns = 0;
	int number=0;
	if(nEntries>0)
	{
		size_t index=1;
		for (size_t i=nEntries-1;i>0;i--)
		{
			numberTrns+=i;		
			int num=index;
			for (size_t j=0;j<i;j++)
				num = num*10;
			
			number+=num;
			index++;
		}

		number+=nEntries;
	}	
	return number;
}

int	CHGroupDraw::getChangesInS1S2()
{
	int nEntries = vCompetitorsDraw.entries();
	int numberTrns = 0;
	int number=0;
	if(nEntries>0)
	{
		size_t index=1;
		for (size_t i=nEntries-1;i>0;i--)
		{
			numberTrns+=i;		
			int num=index;
			for (size_t j=0;j<i;j++)
				num = num*10;
			
			number+=num;
			index++;
		}

		number+=nEntries;
	}	
	return number;
}

void CHGroupDraw::createTranspositionsInS2()
{
	removeTranspositionsInS2();

	int number = getTranspositionsInS2();
	char tmp[10];
	_itoa_s(number,tmp,10);
	char append[]="\0";  
	char_permutation(tmp,append);
}

void CHGroupDraw::createChangesInS1S2()
{
	removeChangesInS1S2();

	int number = getChangesInS1S2();
	char tmp[10];
	_itoa_s(number,tmp,10);
	char append[]="\0";  
	char_changes(tmp,append);
}

bool CHGroupDraw::trasposeS2(short nTransposition)
{
	calculateSubgroups();	
	
	if (nTransposition &&
		nTransposition<=vS2Permutations.entries())
	{
		CHPermutationNumber *pPermutationNumber = (CHPermutationNumber*)vS2Permutations[nTransposition-1];
		changeCompetitorsS2Order(pPermutationNumber);
		vS2.setFcCompare(orderCompetitorsDrawByOrder);				
		vS2.sort();
		return true;
	}	
	return false;
}

bool CHGroupDraw::changeInS1S2(short nChange)
{
	if (changeS1S2 &&
		changeS1S2<=vS1S2Changes.entries())
	{
		CHPermutationNumber *pPermutationNumber = (CHPermutationNumber*)vS1S2Changes[changeS1S2-1];
		changeCompetitorsDrawOrder(pPermutationNumber);
		
		vCompetitorsDraw.setFcCompare(orderCompetitorsDrawByOrder);				
		vCompetitorsDraw.sort();

		calculateSubgroups();	
		return true;
	}

	return false;
}

void CHGroupDraw::removeTranspositionsInS2()
{
	for (short i=0;i<vS2Permutations.entries();i++)
	{
		CHPermutationNumber* pPermutation = (CHPermutationNumber*)vS2Permutations[i];
		delete pPermutation;
	}
	
	vS2Permutations.clear();
}

void CHGroupDraw::removeChangesInS1S2()
{
	for (short i=0;i<vS1S2Changes.entries();i++)
	{
		CHPermutationNumber* pPermutationNumber = (CHPermutationNumber*)vS1S2Changes[i];
		delete pPermutationNumber;
	}
	
	vS1S2Changes.clear();
}

void CHGroupDraw::char_permutation(char str[],char append[])
{
	int length=strlen(str);
	if(length)
	{
		for(int i=0;i<length;++i)
		{
			char* str1=new char[length+1];
			int cnt;
			int cnt2;
			for(cnt=0,cnt2=0;cnt<length;++cnt,++cnt2)
			{
				if(cnt==i)
				{
					str1[cnt]=str[++cnt2];
					continue; 
				}
				else
					str1[cnt]=str[cnt2];
			}  
			str1[cnt]='\0';
    
			int alength=strlen(append);
			char* append1=new char [alength+2];
			strncpy(append1,append,alength);
			append1[alength]=str[i];
			append1[alength+1]='\0';
      
			if (strlen(str1)==vS2.entries()-1)
				char_permutation(str1,append1);
      
		    delete [] str1;
			delete [] append1; 
		} 
	}
	else
	{
		if (strlen(append)==vS2.entries())
		{
			CHPermutationNumber *pPermutationNumber = new CHPermutationNumber(atoi(append));
			vS2Permutations.insert(pPermutationNumber);	
		}
	}
}


void CHGroupDraw::char_changes(char str[],char append[])
{
	int length=strlen(str);
	if(length)
	{
		for(int i=0;i<length;++i)
		{
			char* str1=new char[length+1];
			int cnt;
			int cnt2;
			for(cnt=0,cnt2=0;cnt<length;++cnt,++cnt2)
			{
				if(cnt==i)
				{
					str1[cnt]=str[++cnt2];
					continue; 
				}
				else
					str1[cnt]=str[cnt2];
			}  
			str1[cnt]='\0';
    
			int alength=strlen(append);
			char* append1=new char [alength+2];
			strncpy(append1,append,alength);
			append1[alength]=str[i];
			append1[alength+1]='\0';

			if (strlen(str1)==vCompetitorsDraw.entries()-1)
				char_changes(str1,append1);
      
		    delete [] str1;
			delete [] append1; 
		} 
	}
	else
	{
		if (strlen(append)==vCompetitorsDraw.entries())
		{
			CHPermutationNumber *pPermutationNumber = new CHPermutationNumber(atoi(append));
			vS1S2Changes.insert(pPermutationNumber);	
		}
	}
}


CHCompetitorDraw* CHGroupDraw::findOpponent(CHCompetitorDraw* pCompetitor1)
{
	CHCompetitorDraw* pCompetitor2 = 0;
	CHPoolResult *pPoolResult1=0,*pPoolResult2=0;
	pPoolResult1 = pCompetitor1->getPoolResult();

	calculateSubgroups();

	MSLSortedVector vS;
	if (vS1.find(pCompetitor1))
		vS=vS2;
	else if (vS2.find(pCompetitor1))
		vS=vS1;
	else
		return 0;

	// EMPAREJAR EL JUGADOR CON EL MAS ALTO DE S2, SI NO ES
	// POSIBLE APLICAR TRANSPOSICION EN S2
	for (short i=0;i<vS.entries();i++)
	{
		pCompetitor2 = (CHCompetitorDraw*)vS[i];	
		pPoolResult2 = pCompetitor2->getPoolResult();

		if (pCompetitor2 == pCompetitor1)
			continue;

		if (!pCompetitor2->getAlreadyPaired() &&
			pCompetitor1->getPoolResult() &&
			!pCompetitor1->getPoolResult()->hasAlreadyPlayed(pPoolResult2,round) &&
			hasCompatibleColors(pCompetitor1,pCompetitor2) &&
			(!pPoolResult2->getBye() || ( pPoolResult2->getBye() &&
			!pCompetitor1->hasAlreadyBye(round))))
		{
			return pCompetitor2;
		}		
	}
	
	return 0;
}

void CHGroupDraw::changeCompetitorsS2Order(CHPermutationNumber *pPermutationNumber)
{
	char tmp[10];
	_itoa_s(pPermutationNumber->getNumber(),tmp,10);
	for (short i=0;i<vS2.entries();i++)
	{
		CHCompetitorDraw* pCompetitor = (CHCompetitorDraw*)vS2[i];	
		pCompetitor->setOrder(int(tmp[i]-48));
	}
}

void CHGroupDraw::changeCompetitorsDrawOrder(CHPermutationNumber *pPermutationNumber)
{
	char tmp[10];
	_itoa_s(pPermutationNumber->getNumber(),tmp,10);
	for (short i=0;i<vCompetitorsDraw.entries();i++)
	{
		CHCompetitorDraw* pCompetitor = (CHCompetitorDraw*)vCompetitorsDraw[i];	
		pCompetitor->setOrder(int(tmp[i]-48));
	}
}


bool CHGroupDraw::hasCompatibleColors(CHCompetitorDraw* pCompetitor1,CHCompetitorDraw* pCompetitor2)
{
	if (pCompetitor1->getPoolResult() && 
		pCompetitor2->getPoolResult() &&
		pPool)
		return pPool->hasCompatibleColors(pCompetitor1->getPoolResult(),pCompetitor2->getPoolResult(),round);
	return false;
}

void CHGroupDraw::calculateVariables()
{
	//(2)
	// SE DETERMINA X (EMPAREJAMIENTOS QUE NO CUMPLIRAN LAS NORMAS DE COLOR) 
	// W(B) NUMERO DE JUGADORES CON PREFERENCIA DE COLOR BLANCAS
	// B(N) NUMERO DE JUGADORES CON PREFERENCIA DE COLOR NEGRAS
	// O = NUMERO DE JUGADORES EN EL GRUPO DE PUNTUACION DIVIDIDOS POR
	// 2 Y REDONDEADOS EN EXCESO.
	// SI B(N) > W(B) ENTONCES X= B(N) - O
	// SI W(B) > B(N) ENTONCES X= N(B) - O

	int R = vCompetitorsDraw.entries() % 2;
	O = vCompetitorsDraw.entries() / 2; 
	if (R>0)
		O++;
	
	short W=0;
	short B=0;

	for (short i=0;i<vCompetitorsDraw.entries();i++)
	{
		CHCompetitorDraw* pCompetitorDraw = (CHCompetitorDraw*)vCompetitorsDraw[i];

		if (pCompetitorDraw->getSidePreference(round)==CHMatchResult::eWhite)
			W++;
		if (pCompetitorDraw->getSidePreference(round)==CHMatchResult::eBlack)
			B++;
	}

	if (B>W)
		X = B - O;
	else if (W>B)
		X = W - O;
}

void CHGroupDraw::calculateSubgroups()
{
	// (3)
	// SE DETERMINA P (NUMERO DE EMFRENTAMIENTOS A REALIZAR),
	// PARA ELLO EL GRUPO DE PUNTUACION SE DIVIDE EN DOS GRUPOS S1 Y S2, SI
	// ES GRUPO HETEROGENEO S1 CONTIENE LOS JUGADORES DESCENDIDOS DE NIVELES
	// SUPERIORES, SI ES GRUPO HOMOGENEO  S1 CONTIENE LA MITAD SUPERIOR 
	// (REDONDEADA HACIA ABAJO) DEL NUMERO DE JUGADORES DEL GRUPO DE PUNTUACION
	// EL NUMERO DE JUGADORES S1 SERA INDICADO POR P, QUE SEÑALA EL NUMERO DE
	// EMPAREJAMIENTOS A REALIZAR. EN AMBOS CASOS S2 CONTIENE EL RESTO DE 
	// JUGADORES DEL GRUPO DE PUNTUACION. AMBOS SE ORDENAN COMO SIEMPRE

	vS1.clearAndDestroy();
	vS2.clearAndDestroy();

	if (isHomogenic())
	{
		long nS1=vCompetitorsDraw.entries() / 2;
		long nS2=vCompetitorsDraw.entries() / 2;

		if (vCompetitorsDraw.entries() % 2)
			nS2++;
	
		P=nS1;
	
		CHCompetitorDraw* pCompetitor=0;
		for (short i=0;i<nS1;i++)
		{
			pCompetitor = (CHCompetitorDraw*)vCompetitorsDraw[i];	
			vS1.insert(pCompetitor);
		}

		for (short i=nS1;i<vCompetitorsDraw.entries();i++)
		{	
			pCompetitor = (CHCompetitorDraw*)vCompetitorsDraw[i];	
			vS2.insert(pCompetitor);
		}
	}
	else
	{
		float pointsGroup = 0.0;

		/*for (size_t i=0;i<vCompetitorsDraw.entries();i++)
		{
			CHCompetitorDraw* pCompetitorDraw = (CHCompetitorDraw*)vCompetitorsDraw[i];
			if (pCompetitorDraw &&
				pCompetitorDraw->getPoolResult() &&
				pCompetitorDraw->getPoolResult()->getPointsF() > pointsGroup)
				pointsGroup = pCompetitorDraw->getPoolResult()->getPointsF();
		}*/

		if (vCompetitorsDraw[0])
			pointsGroup=((CHCompetitorDraw*)vCompetitorsDraw[0])->getPoolResult()->getPointsF();

		for (short i=0;i<vCompetitorsDraw.entries();i++)
		{
			CHCompetitorDraw* pCompetitorDraw = (CHCompetitorDraw*)vCompetitorsDraw[i];
			if (pCompetitorDraw &&
				pCompetitorDraw->getPoolResult() &&
				( pointsGroup==pCompetitorDraw->getPoolResult()->getPointsF() || i==0 ) )
					vS1.insert(pCompetitorDraw);
				else
					vS2.insert(pCompetitorDraw);
						
			P=vS1.entries();
		}
	}
}

void CHGroupDraw::sortCompetitorsDrawByFloatingUp()
{
	vCompetitorsDraw.setFcCompare(orderCompetitorsDrawByFloatingUp);
}

void CHGroupDraw::sortCompetitorsDrawByRank()
{
	vCompetitorsDraw.setFcCompare(orderCompetitorsByRank);
}

void CHGroupDraw::sortCompetitorsDrawByOrder()
{
	vCompetitorsDraw.setFcCompare(orderCompetitorsDrawByOrder);
}