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

#include "stdVCH.h"
#include "CHGroupDraw.h"
#include "CHPermutationNumber.h"
#include "CHChange.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

static int orderCompetitorsByRank(const GVectorElement** a, const GVectorElement** b)
{
	CHCompetitorDraw *pCA=(CHCompetitorDraw *)(*a)->getElement();
	CHCompetitorDraw *pCB=(CHCompetitorDraw *)(*b)->getElement();

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


static int orderCompetitorsDrawByOrder(const GVectorElement** a, const GVectorElement** b)
{
	CHCompetitorDraw *pCA=(CHCompetitorDraw *)(*a)->getElement();
	CHCompetitorDraw *pCB=(CHCompetitorDraw *)(*b)->getElement();

	int order = pCA->getOrder() - pCB->getOrder();
	if (order)
		return order;

	return orderCompetitorsByRank(a,b);
}

static int orderCompetitorsDrawByFloatingUp(const GVectorElement** a, const GVectorElement** b)
{
	CHCompetitorDraw *pCA=(CHCompetitorDraw *)(*a)->getElement();
	CHCompetitorDraw *pCB=(CHCompetitorDraw *)(*b)->getElement();

	if (pCA->getFloatingUp() && pCB->getFloatingUp())
		return orderCompetitorsDrawByOrder(a,b);

	if (pCA->getFloatingUp())
		return -1;

	if (pCB->getFloatingUp())
		return 1;

	return orderCompetitorsDrawByOrder(a,b);
}

static int orderPermutations(const GVectorElement** a, const GVectorElement** b)
{
	CHPermutationNumber *pA=(CHPermutationNumber *)(*a)->getElement();
	CHPermutationNumber *pB=(CHPermutationNumber *)(*b)->getElement();

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
	setKey();
}

CHGroupDraw::~CHGroupDraw()
{
	for (size_t i=0;i<vCompetitorsDraw.entries();i++)
	{
		CHCompetitorDraw* pCompetitorDraw = (CHCompetitorDraw*)vCompetitorsDraw[i]->getElement();
		delete pCompetitorDraw;
	}
	
	vCompetitorsDraw.clearAndDestroy();
}

void CHGroupDraw::sortCompetitorsDraw(CompareFunction compare)
{
	vCompetitorsDraw.sort(compare);
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
	sprintf(tmp,"%d",group);
	key=tmp;
}

RWBoolean CHGroupDraw::operator !=(const CHGroupDraw& copy)
{
	return !compareGroupDraw(copy);
}	

RWBoolean CHGroupDraw::operator ==(const CHGroupDraw& copy)
{
	return compareGroupDraw(copy);
}

CHGroupDraw& CHGroupDraw::operator =(const CHGroupDraw& copy)
{
	copyGroupDraw(copy);
	return *this;
}

void CHGroupDraw::copyGroupDraw(const CHGroupDraw& copy)
{
	group	=	copy.group;	
	P		=	copy.P;
	X		=	copy.X;
}

RWBoolean CHGroupDraw::compareGroupDraw(const CHGroupDraw& copy)
{
	RWBoolean value= false;

	if ( group	==	copy.group	&&
		 P		==	copy.P		&&
		 X		==	copy.X		)
		 value= true;

	return value;
}

CPack& CHGroupDraw::pack(CPack& aPack)
{
	return aPack;
}

CPack& CHGroupDraw::unpack(CPack& aPack)
{
	return aPack;
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

	CHCompetitorDraw* pCompetitorDraw = (CHCompetitorDraw*)vCompetitorsDraw[0]->getElement();
	float groupPoints = 0.0;
	if (pCompetitorDraw->getPoolResult())
		groupPoints=pCompetitorDraw->getPoolResult()->getPointsF();	

	for (size_t i=0;i<vCompetitorsDraw.entries();i++)
	{
		pCompetitorDraw = (CHCompetitorDraw*)vCompetitorsDraw[i]->getElement();
		if (!pCompetitorDraw ||
			!pCompetitorDraw->getPoolResult() || 
			groupPoints!=pCompetitorDraw->getPoolResult()->getPointsF())
			return false;
	}
	return true;
}

GSortedVector& CHGroupDraw::getCompetitorsDrawPairedVector()
{
	return vCompetitorsDrawPaired;
}

GVectorElement*	CHGroupDraw::setCompetitorsDrawPaired(CHCompetitorDraw* pCompetitorDraw)
{
	if (!vCompetitorsDrawPaired.find(pCompetitorDraw))
		return vCompetitorsDrawPaired.insert(pCompetitorDraw, orderCompetitorsByRank);
	return 0;
}

void CHGroupDraw::removeCompetitorsDrawPaired(CHCompetitorDraw& aCompetitorDraw)
{
	vCompetitorsDrawPaired.removeAndDestroy(&aCompetitorDraw);
}	

CHCompetitorDraw* CHGroupDraw::getCompetitorsDrawPaired(int index)
{
	if (vCompetitorsDrawPaired.entries()> size_t(index))
		return (CHCompetitorDraw*)vCompetitorsDrawPaired[index]->getElement();
	return 0;
}

GSortedVector& CHGroupDraw::getCompetitorsDrawVector()
{
	return vCompetitorsDraw;
}

GVectorElement*	CHGroupDraw::setCompetitorsDraw(CHCompetitorDraw* pCompetitorDraw)
{
	if (!vCompetitorsDraw.find(pCompetitorDraw))
		return vCompetitorsDraw.insert(pCompetitorDraw,orderCompetitorsByRank);
	return 0;
}

void CHGroupDraw::removeCompetitorsDraw(CHCompetitorDraw& aCompetitorDraw)
{
	vCompetitorsDraw.removeAndDestroy(&aCompetitorDraw);
}

GSortedVector& CHGroupDraw::getCompetitorsS1Vector()
{
	return vS1;
}

CHCompetitorDraw* CHGroupDraw::getCompetitorsS1(int index)
{
	if (vS1.entries()> size_t(index))
		return (CHCompetitorDraw*)vS1[index]->getElement();
	return 0;
}

GSortedVector& CHGroupDraw::getCompetitorsS2Vector()
{
	return vS2;
}

CHCompetitorDraw* CHGroupDraw::getCompetitorsS2(int index)
{
	if (vS2.entries()> size_t(index))
		return (CHCompetitorDraw*)vS2[index]->getElement();
	return 0;
}

CHCompetitorDraw* CHGroupDraw::getCompetitorsDraw(int index)
{
	if (vCompetitorsDraw.entries()> size_t(index))
		return (CHCompetitorDraw*)vCompetitorsDraw[index]->getElement();
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
	short nEntries = vS2.entries();
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
	short nEntries = vCompetitorsDraw.entries();
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
	itoa(number,tmp,10);
	char append[]="\0";  
	char_permutation(tmp,append);
}

void CHGroupDraw::createChangesInS1S2()
{
	removeChangesInS1S2();

	int number = getChangesInS1S2();
	char tmp[10];
	itoa(number,tmp,10);
	char append[]="\0";  
	char_changes(tmp,append);
}

RWBoolean CHGroupDraw::trasposeS2(short nTransposition)
{
	calculateSubgroups();	
	
	if (nTransposition &&
		nTransposition<=vS2Permutations.entries())
	{
		CHPermutationNumber *pPermutationNumber = (CHPermutationNumber*)vS2Permutations[nTransposition-1]->getElement();
		changeCompetitorsS2Order(pPermutationNumber);
		vS2.sort(orderCompetitorsDrawByOrder);				
		return true;
	}	
	return false;
}

RWBoolean CHGroupDraw::changeInS1S2(short nChange)
{
	if (changeS1S2 &&
		changeS1S2<=vS1S2Changes.entries())
	{
		CHPermutationNumber *pPermutationNumber = (CHPermutationNumber*)vS1S2Changes[changeS1S2-1]->getElement();
		changeCompetitorsDrawOrder(pPermutationNumber);
		
		vCompetitorsDraw.sort(orderCompetitorsDrawByOrder);				
		calculateSubgroups();	
		return true;
	}

	return false;
}

void CHGroupDraw::removeTranspositionsInS2()
{
	for (size_t i=0;i<vS2Permutations.entries();i++)
	{
		CHPermutationNumber* pPermutation = (CHPermutationNumber*)vS2Permutations[i]->getElement();
		delete pPermutation;
	}
	
	vS2Permutations.clearAndDestroy();
}

void CHGroupDraw::removeChangesInS1S2()
{
	for (size_t i=0;i<vS1S2Changes.entries();i++)
	{
		CHPermutationNumber* pPermutationNumber = (CHPermutationNumber*)vS1S2Changes[i]->getElement();
		delete pPermutationNumber;
	}
	
	vS1S2Changes.clearAndDestroy();
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
			vS2Permutations.insert(pPermutationNumber,orderPermutations);	
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
			vS1S2Changes.insert(pPermutationNumber,orderPermutations);	
		}
	}
}


CHCompetitorDraw* CHGroupDraw::findOpponent(CHCompetitorDraw* pCompetitor1)
{
	CHCompetitorDraw* pCompetitor2 = 0;
	CHPoolResult *pPoolResult1=0,*pPoolResult2=0;
	pPoolResult1 = pCompetitor1->getPoolResult();

	calculateSubgroups();

	GSortedVector vS;
	if (vS1.find(pCompetitor1))
		vS=vS2;
	else if (vS2.find(pCompetitor1))
		vS=vS1;
	else
		return 0;

	// EMPAREJAR EL JUGADOR CON EL MAS ALTO DE S2, SI NO ES
	// POSIBLE APLICAR TRANSPOSICION EN S2
	for (size_t i=0;i<vS.entries();i++)
	{
		pCompetitor2 = (CHCompetitorDraw*)vS[i]->getElement();	
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
	itoa(pPermutationNumber->getNumber(),tmp,10);
	for (size_t i=0;i<vS2.entries();i++)
	{
		CHCompetitorDraw* pCompetitor = (CHCompetitorDraw*)vS2[i]->getElement();	
		pCompetitor->setOrder(int(tmp[i]-48));
	}
}

void CHGroupDraw::changeCompetitorsDrawOrder(CHPermutationNumber *pPermutationNumber)
{
	char tmp[10];
	itoa(pPermutationNumber->getNumber(),tmp,10);
	for (size_t i=0;i<vCompetitorsDraw.entries();i++)
	{
		CHCompetitorDraw* pCompetitor = (CHCompetitorDraw*)vCompetitorsDraw[i]->getElement();	
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

	for (size_t i=0;i<vCompetitorsDraw.entries();i++)
	{
		CHCompetitorDraw* pCompetitorDraw = (CHCompetitorDraw*)vCompetitorsDraw[i]->getElement();

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
		short nS1=vCompetitorsDraw.entries() / 2;
		short nS2=vCompetitorsDraw.entries() / 2;

		if (vCompetitorsDraw.entries() % 2)
			nS2++;
	
		P=nS1;
	
		CHCompetitorDraw* pCompetitor=0;
		for (size_t i=0;i<nS1;i++)
		{
			pCompetitor = (CHCompetitorDraw*)vCompetitorsDraw[i]->getElement();	
			vS1.insert(pCompetitor,orderCompetitorsDrawByOrder);
		}

		for (i=nS1;i<vCompetitorsDraw.entries();i++)
		{	
			pCompetitor = (CHCompetitorDraw*)vCompetitorsDraw[i]->getElement();	
			vS2.insert(pCompetitor,orderCompetitorsDrawByOrder);
		}
	}
	else
	{
		float pointsGroup = 0.0;

		/*for (size_t i=0;i<vCompetitorsDraw.entries();i++)
		{
			CHCompetitorDraw* pCompetitorDraw = (CHCompetitorDraw*)vCompetitorsDraw[i]->getElement();
			if (pCompetitorDraw &&
				pCompetitorDraw->getPoolResult() &&
				pCompetitorDraw->getPoolResult()->getPointsF() > pointsGroup)
				pointsGroup = pCompetitorDraw->getPoolResult()->getPointsF();
		}*/

		if (vCompetitorsDraw[0])
			pointsGroup=((CHCompetitorDraw*)vCompetitorsDraw[0]->getElement())->getPoolResult()->getPointsF();

		for (size_t i=0;i<vCompetitorsDraw.entries();i++)
		{
			CHCompetitorDraw* pCompetitorDraw = (CHCompetitorDraw*)vCompetitorsDraw[i]->getElement();
			if (pCompetitorDraw &&
				pCompetitorDraw->getPoolResult() &&
				( pointsGroup==pCompetitorDraw->getPoolResult()->getPointsF() || i==0 ) )
					vS1.insert(pCompetitorDraw,orderCompetitorsDrawByOrder);
				else
					vS2.insert(pCompetitorDraw,orderCompetitorsDrawByOrder);					
						
			P=vS1.entries();
		}
	}
}

void CHGroupDraw::sortCompetitorsDrawByFloatingUp()
{
	vCompetitorsDraw.sort(orderCompetitorsDrawByFloatingUp);
}

void CHGroupDraw::sortCompetitorsDrawByRank()
{
	vCompetitorsDraw.sort(orderCompetitorsByRank);
}

void CHGroupDraw::sortCompetitorsDrawByOrder()
{
	vCompetitorsDraw.sort(orderCompetitorsDrawByOrder);
}