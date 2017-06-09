/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHRoundDraw.cpp
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
#include "CHRoundDraw.h"
#include "CHGroupDraw.h"
#include "CHPairDraw.h"
#include "CHCompetitorDraw.h"
#include "..\CHMngtModel\CHPoolResult.h"
#include "..\CHMngtModel\CHPool.h"
#include "..\CHMngtModel\CHInscription.h"
#include "..\CHMngtModel\CHMatch.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

static int orderPairsByOrder(const MSLItem** a, const MSLItem** b)
{
	CHPairDraw *pA=(CHPairDraw *)(*a);
	CHPairDraw *pB=(CHPairDraw *)(*b);

	int order = pB->getOrder() - pA->getOrder();
	if (order)
		return order;

	return strcmp(pA->getKey(),pB->getKey());
}

static int orderGroupsDrawByGroup(const MSLItem** a, const MSLItem** b)
{
	CHGroupDraw *pA=(CHGroupDraw *)(*a);
	CHGroupDraw *pB=(CHGroupDraw *)(*b);

	return strcmp(pA->getKey(),pB->getKey());
}

static int orderPoolResultsByRank(const MSLItem** a, const MSLItem** b)
{
	CHPoolResult *pA=(CHPoolResult *)(*a);
	CHPoolResult *pB=(CHPoolResult *)(*b);

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

static
int orderMatchByCode(const MSLItem** a, const MSLItem** b)
{
	GTHMatch * pA=(GTHMatch *)(*a);
	GTHMatch * pB=(GTHMatch *)(*b);

	int order = pA->getCode() - pB->getCode();
	if (order)
		return order;

	order = pA->getSubCode() - pB->getSubCode();
	if (order)
		return order;

	return strcmp(pA->getKey(),pB->getKey());
}

CHRoundDraw::CHRoundDraw(MSLSet& _colMatchResults, CHPool* _pPool, short _round)
:pPool(_pPool)
,round(_round)
,vGroupDraw(orderGroupsDrawByGroup)
,vGroupDrawProcessed(orderGroupsDrawByGroup)
,vRoundMatches(orderMatchByCode)
,vRoundPairs(orderPairsByOrder)
,colMatchResults(&_colMatchResults)
{

}

CHRoundDraw::~CHRoundDraw()
{
	for (short i=0;i<vGroupDraw.entries();i++)
	{
		CHGroupDraw* pGroupDraw = (CHGroupDraw*)vGroupDraw[i];
		delete pGroupDraw;
	}

	for (short i=0;i<vRoundPairs.entries();i++)
	{
		CHPairDraw* pPairDraw = (CHPairDraw*)vRoundPairs[i];
		delete pPairDraw;
	}	
}

void CHRoundDraw::destroyVector()
{
	for (short i=0;i<vGroupDraw.entries();i++)
	{
		CHGroupDraw* pGroupDraw = (CHGroupDraw*)vGroupDraw[i];
		delete pGroupDraw;
	}

	vGroupDraw.clear();

	for (short i=0;i<vRoundPairs.entries();i++)
	{
		CHPairDraw* pPairDraw = (CHPairDraw*)vRoundPairs[i];
		delete pPairDraw;
	}

	vRoundPairs.clear();
}

bool CHRoundDraw::doDraw(TypeDraw drawType)
{
	typeDraw = drawType;	
	rebuildVector();
	fillMatchesVector();
	if (!vRoundMatches.entries())
	{
		MessageBox(0,L"There aren't any match to pair, remove all pairs first",L"",MB_OK);
		return false;
	}

	short attemps=0;
	
	while (vGroupDraw.entries())
	{
		CHGroupDraw* pGroupDraw = (CHGroupDraw*)vGroupDraw[0];
							
		MSLSet colUnpairedCompetitors;
		if (processGroupPairing(pGroupDraw,colUnpairedCompetitors))
		{
			setGroupsDrawProcessed(pGroupDraw);
			removeGroupsDraw(*pGroupDraw);	
			attemps=0;
		}
		attemps++;
		if(attemps==100)
		{
			MessageBox(0,L"Impossible to make draw. Please, make manually",L"",MB_OK);
			return false;
		}
	}
	return true;
}

short CHRoundDraw::processGroupPairing(CHGroupDraw* pGroupDraw, MSLSet &colUnpairedCompetitors)
{
	short matchOrder=0;
	short nGroupMatches=0;
	
	pGroupDraw->calculateVariables();
	pGroupDraw->calculateSubgroups();
	
	short P=pGroupDraw->getP();
	

	while (pGroupDraw->getCompetitorsDrawVector().entries())
	{
		CHCompetitorDraw* pCompetitorDraw = (CHCompetitorDraw*)pGroupDraw->getCompetitorsDrawVector()[0];
		
		if (!processCompetitor(pGroupDraw,pCompetitorDraw,matchOrder,nGroupMatches,P))
			return processNotFoundOpponent(pCompetitorDraw,pGroupDraw,matchOrder,nGroupMatches,P);
	}
	return 1;
}

CHCompetitorDraw* CHRoundDraw::processCompetitor(CHGroupDraw* pGroupDraw,CHCompetitorDraw* pCompetitorDraw,short &matchOrder, short &groupMatches, short P)
{
	// (C6)
	bool wasNotHomogenic=true;

	CHCompetitorDraw* pCompetitorDrawOpp = pGroupDraw->findOpponent(pCompetitorDraw);
	if (pCompetitorDrawOpp)
	{
		wasNotHomogenic = !pGroupDraw->isHomogenic();
		matchOrder++;
		processPair(pGroupDraw,pCompetitorDraw,pCompetitorDrawOpp,matchOrder);
		groupMatches++;

		pGroupDraw->calculateSubgroups();
		
		if (wasNotHomogenic && pGroupDraw->isHomogenic())
		{
			P=pGroupDraw->getP();
			groupMatches=0;
		}
	}
	return pCompetitorDrawOpp;
}

void CHRoundDraw::changeCompetitorGroup(CHGroupDraw* pGroupDrawSource,CHCompetitorDraw* pCompetitorDraw, CHGroupDraw* pGroupDrawTarget, bool floatingUp, bool floatingDown)
{
	pGroupDrawSource->removeCompetitorsDraw(*pCompetitorDraw);
	
	if (floatingDown)
		pCompetitorDraw->setFloatingDown(true);
	if (floatingUp)
		pCompetitorDraw->setFloatingUp(true);
	
	pGroupDrawTarget->setCompetitorsDraw(pCompetitorDraw);								
	pGroupDrawTarget->resetChange();
	pGroupDrawTarget->resetTransposition();
	pGroupDrawTarget->calculateSubgroups();
	pGroupDrawTarget->createTranspositionsInS2();
	pGroupDrawTarget->createChangesInS1S2();
}

short CHRoundDraw::processNotFoundOpponent(CHCompetitorDraw* pCompetitorDraw,CHGroupDraw *pGroupDraw,short &matchOrder, short &groupMatches, short P)
{
	short groupEntries=short(pGroupDraw->getCompetitorsDrawVector().entries());
	
	if (groupEntries==1)
	{
		// Lo Borro y lo inserto en el siguiente grupo si hay
		if (vGroupDraw[1])
		{			
			changeCompetitorGroup(pGroupDraw,pCompetitorDraw,(CHGroupDraw*)vGroupDraw[1],false,true);
			return 1;
		}
	}

	// INTENTO TRANSPONER EL GRUPO
	if (groupMatches!=P)
	{
		// Desago El grupo y transpongo
		if (pGroupDraw->getTranspositions()<=pGroupDraw->getTotalTranspositionsInS2())
		{
			undoGroup(pGroupDraw);			
			trasposeGroup(pGroupDraw);
			return 0;
		}	
		else if (pGroupDraw->getChanges()<=pGroupDraw->getTotalChangesInS1S2())
		{
			// Aplico cambio entre S1 y S2
			undoGroup(pGroupDraw);			
			changeGroup(pGroupDraw);
			return 0;
		}
	}

	// NO HAY OPONENTE PARA ESE JUGADOR
	if (pCompetitorDraw->getFloatingDown())
	{
		// SI EL JUGADOR FUE DESCENDIDO DESDE UN GRUPO DE PUNTUACION
		// SUPERIOR SE DESHACE EL GRUPO DE PUNTUACION PREVIO. SI EN 
		// ESE GRUPO DE PUNTUACION PREVIO PUEDE HACERSE UN EMPAREJAMIENTO
		// POR EL CUAL OTRO JUGADOR PUEDE SER DESCENDIDO EN LUGAR DEL 
		// ANTERIOR Y PERMITIR QUE AHORA SE HAGAN P EMPAREJAMIENTOS ENTONCES
		// EL CAMBIO DE EMPAREJAMIENTO EN EL GRUPO PREVIO SERA ACEPTADO

		return undoPreviousGroup_C12(pGroupDraw,pCompetitorDraw);		
	}				
	
	if (!vGroupDraw[1])
	{
		// EL GRUPO DE PUNTUACION ES EL MAS BAJO, SE ANULA EL EMPAREJAMIENTO
		// DEL PENULTIMO GRUPO, SE INTENTA BUSCAR OTRO EMPAREJAMIENTO EN
		// EL PENULTIMO GRUPO DE PUNTUACION QUE PERMITA EMPAREJAR AL GRUPO
		// DE PUNTUACION MAS BAJO. SI EN EL PENULTIMO GRUPO DE PUNTUACION
		// P SE HACE 0 (NO SE ENCUENTRA NINGUN EMPAREJAMIENTO QUE PERMITA 
		// A SU VEZ UN CORRECTO EMPAREJAMIENTO EN EL GRUPO DE PUNTUACION
		// MAS BAJO) ENTONCES LOS DOS GRUPOS DE PUNTUACION SERAN UNIDOS EN
		// UN NUEVO GRUPO DE PUNTUACION INFERIOR. DEBIDO A QUE AHORA OTRO 
		// GRUPO DE PUNTUACION ES EL PENULTIMO, PUEDE REPETIRSE ESTE PASO HASTA
		// QUE SE CONSIGA UN EMPAREJAMIENTO ACEPTABLE
		if (!hasBye())
			return undoPreviousGroup_C13(pGroupDraw);			
	}				
	
	if (vGroupDraw[1])
	{
		// EN EL RESTO DE LOS CASOS ESTE JUGANDO DESCIENDE AL GRUPO MAS
		// CERCANO DE PUNTUACION 
		// EN EL CASO DE UN GRUPO DE PUNTUACION HOMOGENEO LOS RESTANTES 
		// SON DESCENDIDOS AL SIGUIENTE GRUPO DE PUNTUACION E INICIAMOS 
		// EL PROCESO DE NUEVO CON EL SIGUIENTE GRUPO (1)

		// EN EL CASO DE UN GRUPO DE PUNTUACION HETEROGENEO SOLO SERAN 
		// EMPAREJADOS LOS JUGADORES DESCENDIENTES COMENZANDO EL PROCESO
		// EN EL PASO (2) CON EL GRUPO HOMOGENEO RESTANTE
		// Lo borro de este grupo y lo inserto en el siguiente
		if (groupMatches!=P)
		{
			// Desago El grupo y transpongo
			if (pGroupDraw->getTranspositions()<pGroupDraw->getTotalTranspositionsInS2())
			{
				undoGroup(pGroupDraw);
				trasposeGroup(pGroupDraw);
				return 0;
			}							
			else if (pGroupDraw->getChanges()<=pGroupDraw->getChangesInS1S2())
			{
				// Aplico cambio entre S1 y S2
				undoGroup(pGroupDraw);
				changeGroup(pGroupDraw);
				return 0;
			}
		}

		changeCompetitorGroup(pGroupDraw,pCompetitorDraw,(CHGroupDraw*)vGroupDraw[1],false,true);
		return 0;

		// APLICAMOS UNA TRANSPOSICION EN S2 DE ACUERDO CON LAS NORMAS E
		// INICIAMOS EN (6)
		// EN CASO DE UN GRUPO HOMOGENEO RESTANTE APLICAMOS UN NUEVO
		// CAMBIO ENTRE S1 Y S2 DE ACUERDO 				
	}
	else
	{
		// No puede ser emparejado con nadie puede ser un BYE	
		// Si eran impares es un BYE
		if (groupEntries%2!=0 && hasBye())
		{
			// Si el tio ya fue BYE no puede volver a serlo, 
			if (pCompetitorDraw->hasAlreadyBye(round))
			{
				// anulacion enfrentamiento penultimo grupo
				undoGroup(pGroupDraw);

				if (pGroupDraw->getTranspositions()<pGroupDraw->getTotalTranspositionsInS2())
				{
					// DESHAGO EL PENULTIMO GRUPO DE PUNTUACION Y HAGO TRANSPOSICION
					if (getGroupsDrawProcessed(getGroupsDrawProcessedVector().entries()-1))
					{
						CHGroupDraw* pGroupDraw = (CHGroupDraw*)getGroupsDrawProcessed(getGroupsDrawProcessedVector().entries()-1);
						undoGroup(pGroupDraw);
						trasposeGroup(pGroupDraw);													
					}
					return 0;
				}
				
				return 0;
			}
			else
			{
				// Busco el partido que esta vacio
				processPair(pGroupDraw,pCompetitorDraw,0,matchOrder);
			}					
		}			
	}

	return 1;
}

bool CHRoundDraw::hasBye()
{
	MSLSortedVector VPoolResults;
	pPool->getPoolResultsVector(VPoolResults);
	return VPoolResults.entries()%2;
}

short CHRoundDraw::undoPreviousGroup_C13(CHGroupDraw* pGroupDraw)
{
	size_t i = getGroupsDrawProcessedVector().entries()-1;

	while (getGroupsDrawProcessedVector().entries())
	{
		if (getGroupsDrawProcessed(i))
		{
			CHGroupDraw* pPrevGroupDraw = (CHGroupDraw*)getGroupsDrawProcessed(i);

			// Si huvo algun partido que deshacer
			if (undoGroup(pPrevGroupDraw))
			{
				setGroupsDraw(pPrevGroupDraw);
				if (!trasposeGroup(pPrevGroupDraw))
					mergeGroups(pGroupDraw,pPrevGroupDraw,true,false);					
				return 0;
			}
		
			removeGroupsDrawProcessed(*pPrevGroupDraw);
			i--;
		}
	}
	return 1;
}

void CHRoundDraw::mergeGroups(CHGroupDraw* pGroupDrawSource,CHGroupDraw* pGroupDrawTarget, bool floatingUp, bool floatingDown)
{
	if (pGroupDrawSource == pGroupDrawTarget)
		return;

	while (pGroupDrawSource->getCompetitorsDrawVector().entries())
	{
		CHCompetitorDraw* pCompetitorDraw = (CHCompetitorDraw*)pGroupDrawSource->getCompetitorsDrawVector()[0];
		pGroupDrawSource->removeCompetitorsDraw(*pCompetitorDraw);
		pCompetitorDraw->setFloatingUp(floatingUp);
		pCompetitorDraw->setFloatingDown(floatingDown);
		pGroupDrawTarget->setCompetitorsDraw(pCompetitorDraw);										
	}

	pGroupDrawTarget->resetChange();
	pGroupDrawTarget->resetTransposition();
	pGroupDrawTarget->calculateSubgroups();
	pGroupDrawTarget->createTranspositionsInS2();
	pGroupDrawTarget->createChangesInS1S2();

	setGroupsDraw(pGroupDrawTarget);
	removeGroupsDrawProcessed(*pGroupDrawTarget);
	pGroupDrawTarget->sortCompetitorsDrawByRank();

	// Elimino el grupo de puntuacion Ultimo
	removeGroupsDraw(*pGroupDrawSource);
	removeGroupsDrawProcessed(*pGroupDrawSource);					
}

short CHRoundDraw::undoPreviousGroup_C12(CHGroupDraw* pGroupDraw,CHCompetitorDraw* pCompetitorDraw)
{
	size_t i = getGroupsDrawProcessedVector().entries()-1;
	
	if (!getGroupsDrawProcessedVector().entries())
	{
		// SI NO HAY GRUPOS DE PUNTUACION PREVIOS DESCIENDO A TODOS
		// LOS COMPETIDORES AL SIGUIENTE GRUPO DE PUNTUACION
		if (vGroupDraw[1])
		{
			CHGroupDraw* pNextGroupDraw = (CHGroupDraw*)vGroupDraw[1];	

			// Desciendo al competidor al siguiente grupo
			changeCompetitorGroup(pGroupDraw,pCompetitorDraw,pNextGroupDraw,false,true);
		
			setGroupsDraw(pNextGroupDraw);	
			removeGroupsDrawProcessed(*pNextGroupDraw);
			pNextGroupDraw->sortCompetitorsDrawByRank();

			return 0;
		}
		else
		{
			// NO HAY GRUPO SIGUIENTE NI GRUPO PROCESADO
			return 1;
		}
	}

	while (getGroupsDrawProcessedVector().entries())
	{
		if (getGroupsDrawProcessed(i))
		{
			CHGroupDraw* pPrevGroupDraw = (CHGroupDraw*)getGroupsDrawProcessed(i);

			// Si huvo algun partido que deshacer
			if (undoGroup(pPrevGroupDraw))
			{
				if (pCompetitorDraw->getFloatingDown() &&
					pCompetitorDraw->getFloatingUp() )
				{
					// Esta haciendo la goma junto los dos grupos
					mergeGroups(pGroupDraw,pPrevGroupDraw,true,false);
					return 0;
				}
				else
				{
					// VUELVO A METER A ESTE COMPETIDOR
					changeCompetitorGroup(pGroupDraw,pCompetitorDraw,pPrevGroupDraw,true,false);	
					setGroupsDraw(pPrevGroupDraw);
					pPrevGroupDraw->sortCompetitorsDrawByFloatingUp();
					return 0;
				}
			}					

			removeGroupsDrawProcessed(*pPrevGroupDraw);
			i--;
		}
	}

	return 0;
}

bool CHRoundDraw::trasposeGroup(CHGroupDraw *pGroupDraw)
{
	pGroupDraw->increaseTransposition();
	pGroupDraw->calculateSubgroups();
	return pGroupDraw->trasposeS2(pGroupDraw->getTranspositions());	
}

bool CHRoundDraw::changeGroup(CHGroupDraw *pGroupDraw)
{
	pGroupDraw->increaseChange();
	pGroupDraw->calculateSubgroups();
	return pGroupDraw->changeInS1S2(pGroupDraw->getChanges());	
}

short CHRoundDraw::undoGroup(CHGroupDraw* pGroupDraw)
{
	return removePairs(pGroupDraw);
}

CHPairDraw*	CHRoundDraw::processPair(CHGroupDraw* pGroupDraw,CHCompetitorDraw* pCompetitorDraw,CHCompetitorDraw* pCompetitorDrawOpp,short matchOrder)
{
	CHPairDraw* pLastPair;
	
	if (pCompetitorDraw &&
		pCompetitorDraw->getFloatingDown())
	{
		if (pCompetitorDrawOpp)
			pCompetitorDrawOpp->setFloatingUp(true);
	}

	if (pCompetitorDraw &&
		pCompetitorDraw->getFloatingUp())
	{
		if (pCompetitorDrawOpp)
			pCompetitorDrawOpp->setFloatingDown(true);
	}

	pLastPair = new CHPairDraw(pGroupDraw,0,matchOrder);			
	CHMatch *pMatch = fillMatch(pCompetitorDraw,pCompetitorDrawOpp,pLastPair);
	setAllRoundPair(pLastPair);
		
	if (pCompetitorDraw)
		pCompetitorDraw->setAlreadyPaired(true);
	if (pCompetitorDrawOpp)
		pCompetitorDrawOpp->setAlreadyPaired(true);

	// Lo borro de este grupo y lo inserto en el de procesados
	if (pCompetitorDraw)
	{
		pGroupDraw->removeCompetitorsDraw(*pCompetitorDraw);
		pGroupDraw->setCompetitorsDrawPaired(pCompetitorDraw);
	}
			
	// Lo borro de este grupo y lo inserto en el de procesados
	if (pCompetitorDrawOpp)
	{
		pGroupDraw->removeCompetitorsDraw(*pCompetitorDrawOpp);
		pGroupDraw->setCompetitorsDrawPaired(pCompetitorDrawOpp);
	}

	return pLastPair;
}

MSLSortedVector& CHRoundDraw::getGroupsDrawVector()
{
	return vGroupDraw;
}

MSLItem* CHRoundDraw::setGroupsDraw(CHGroupDraw* pGroupDraw)
{
	if (!vGroupDraw.find(pGroupDraw))
		return vGroupDraw.insert(pGroupDraw);
	return 0;
}
	
void CHRoundDraw::removeGroupsDraw(CHGroupDraw& aGroupDraw)
{
	vGroupDraw.remove(&aGroupDraw);
}
	
CHGroupDraw* CHRoundDraw::getGroupsDraw(int index)
{
	if (vGroupDraw.entries() > short(index))
		return (CHGroupDraw*)vGroupDraw[index];
	return 0;
}

MSLSortedVector& CHRoundDraw::getRoundMatchesVector()
{
	return vRoundMatches;
}

MSLSortedVector& CHRoundDraw::getGroupsDrawProcessedVector()
{
	return vGroupDrawProcessed;
}

MSLItem* CHRoundDraw::setGroupsDrawProcessed(CHGroupDraw* pGroupDraw)
{
	if (!vGroupDrawProcessed.find(pGroupDraw))
		return vGroupDrawProcessed.insert(pGroupDraw);
	return 0;
}

void CHRoundDraw::removeGroupsDrawProcessed(CHGroupDraw& aGroupDraw)
{
	vGroupDrawProcessed.remove(&aGroupDraw);
}

CHGroupDraw* CHRoundDraw::getGroupsDrawProcessed(int index)
{
	if (vGroupDrawProcessed.entries()> short(index))
		return (CHGroupDraw*)vGroupDrawProcessed[index];
	return 0;
}

MSLItem* CHRoundDraw::setRoundMatch(CHMatch* pMatch)
{
	if (!vRoundMatches.find(pMatch))
		return vRoundMatches.insert(pMatch);
	return 0;
}

void CHRoundDraw::removeRoundMatch(CHMatch& aMatch)
{
	vRoundMatches.remove(&aMatch);
}

CHMatch* CHRoundDraw::getMatch(int index)
{
	if (vRoundMatches.entries()> short(index))
		return (CHMatch*)vRoundMatches[index];
	return 0;
}

MSLSortedVector& CHRoundDraw::getAllRoundPairsVector()
{
	return vRoundPairs;
}

MSLItem* CHRoundDraw::setAllRoundPair(CHPairDraw* pPairDraw)
{
	if (!vRoundPairs.find(pPairDraw))
		return vRoundPairs.insert(pPairDraw);
	return 0;
}

void CHRoundDraw::removeAllRoundPair(CHPairDraw& aPairDraw)
{
	vRoundPairs.remove(&aPairDraw);
}

short CHRoundDraw::removePairs(CHGroupDraw *pGroupDraw)
{
	MSLSet colPairs;
	for (short i=0;i<vRoundPairs.entries();i++)
	{
		CHPairDraw *pPairDraw = (CHPairDraw*)vRoundPairs[i];
		if (pPairDraw &&
			pPairDraw->getGroupDraw()==pGroupDraw)
		{
			// Lo Borro del vector de Pairs
			colPairs.insert(pPairDraw);
						
			if (pPairDraw->getWhite())
			{
				pPairDraw->getWhite()->setAlreadyPaired(false);
				// Lo inserto de este grupo y lo borro del de procesados
				pGroupDraw->setCompetitorsDraw(pPairDraw->getWhite());
				pGroupDraw->removeCompetitorsDrawPaired(*pPairDraw->getWhite());
			}

			if (pPairDraw->getBlack())
			{
				pPairDraw->getBlack()->setAlreadyPaired(false);
				// Lo inserto de este grupo y lo borro del de procesados
				pGroupDraw->setCompetitorsDraw(pPairDraw->getBlack());
				pGroupDraw->removeCompetitorsDrawPaired(*pPairDraw->getBlack());
			}			
		}
	}

	MSLSetIterator it(colPairs);
	CHPairDraw *pPairDraw=0;
	
	while( (pPairDraw=(CHPairDraw*)it())!=0 )
	{
		unfillMatch(pPairDraw->getMatch());
		setRoundMatch(pPairDraw->getMatch());		
		removeAllRoundPair(*pPairDraw);		
	}		
	return short(colPairs.entries());
}

void CHRoundDraw::unfillMatch(CHMatch* pMatch)
{
	CHMatchResult* pWhite = pMatch->getWhite();
	unassignMatchResult(pWhite);

	CHMatchResult* pBlack = pMatch->getBlack();
	unassignMatchResult(pBlack);
}

CHPairDraw*	CHRoundDraw::getPair(int index)
{
	if (vRoundPairs.entries()> short(index))
		return (CHPairDraw*)vRoundPairs[index];
	return 0;
}

void CHRoundDraw::rebuildVector()
{
	destroyVector();
	vRoundMatches.clearAndDestroy();
	MSLSortedVector vCompetitors;
	pPool->getPoolResultsVector(vCompetitors);	
	vCompetitors.setFcCompare(orderPoolResultsByRank);

	float lastPoints = 0.0;
	bool firstTime=true;;
	short group=0;
	short order=1;
	CHPoolResult* pPoolResult=0;
	CHGroupDraw* pLastGroupDraw = 0;
	CHCompetitorDraw* pLastCompetitorDraw = 0;

	for (short i=0;i<vCompetitors.entries();i++)
	{
		pPoolResult = (CHPoolResult*)vCompetitors[i];
		if (firstTime || pPoolResult->getPointsF()!=lastPoints)
		{
			order=1;
			group++;
			CHGroupDraw* pGroupDraw = new CHGroupDraw(pPool,group,round);
			setGroupsDraw(pGroupDraw);
			
			/*if (pLastGroupDraw && 
				pLastGroupDraw->getCompetitorsDrawVector().entries()==1)
			{
				// Me cargo el ultimo grupo de puntuacion e Inserto al competidor
				// en este grupo
				pGroupDraw->InsertCompetitor(pLastCompetitorDraw->getPoolResult(),order);
				order++;

				pLastGroupDraw->removeCompetitorsDraw(*pLastCompetitorDraw);
				delete pLastCompetitorDraw;
				pLastCompetitorDraw=0;

				removeGroupsDraw(*pLastGroupDraw);
				delete pLastGroupDraw;
				pLastGroupDraw=0;
			}*/

			// inserto el competidor
			pLastCompetitorDraw = pGroupDraw->InsertCompetitor(pPoolResult,order);	
			firstTime=false;

			pLastGroupDraw=pGroupDraw;			
		}
		else if (pPoolResult->getPointsF()==lastPoints)
		{
			order++;
			CHGroupDraw aGroupDraw(pPool,group,round);
			MSLItem* pElement = vGroupDraw.find(&aGroupDraw);

			// inserto el competidor
			if (pElement)
			{
				CHGroupDraw *pGroupDraw = (CHGroupDraw*)pElement;
				pLastCompetitorDraw = pGroupDraw->InsertCompetitor(pPoolResult,order);
				pGroupDraw->calculateVariables();
				pGroupDraw->calculateSubgroups();
				
				if (round>1)
				{
					pGroupDraw->createTranspositionsInS2();
					pGroupDraw->createChangesInS1S2();
				}
			}			
		}

		lastPoints = pPoolResult->getPointsF();
	}

	/*if (pLastGroupDraw && 
		pLastGroupDraw->getCompetitorsDrawVector().entries()==1)
	{
		if ((CHGroupDraw*)vGroupDraw[vGroupDraw.entries()-2])
		{
			CHGroupDraw *pGroupDraw = (CHGroupDraw*)vGroupDraw[vGroupDraw.entries()-2];
			
			if (pLastCompetitorDraw)
			{
				pGroupDraw->InsertCompetitor(pLastCompetitorDraw->getPoolResult(),order);
				
				pLastGroupDraw->removeCompetitorsDraw(*pLastCompetitorDraw);
				delete pLastCompetitorDraw;
				pLastCompetitorDraw=0;

				removeGroupsDraw(*pLastGroupDraw);
				delete pLastGroupDraw;
				pLastGroupDraw=0;
			}
		}
	}*/
}

void CHRoundDraw::fillMatchesVector()
{
	CHMatch* pMatch=0;
	MSLSortedVector vMatches;
	pPool->getMatchesVector(vMatches);
	for (short i=0;i<vMatches.entries();i++)
	{
		pMatch = (CHMatch*) vMatches[i];
		if (pMatch->getRound()==round && pMatch->getSubMatch()==0 && pMatch->isEmpty())
			setRoundMatch(pMatch);
	}
}

CHMatch* CHRoundDraw::fillMatch(CHCompetitorDraw* pCompetitorDraw, CHCompetitorDraw* pCompetitorDrawOpp, CHPairDraw* pPairDraw)
{
	for (short i=0;i<vRoundMatches.entries();i++)
	{
		CHMatch* pMatch = (CHMatch*)vRoundMatches[i];
		
		CHMatchResult* pWhite = (CHMatchResult*)pMatch->getWhite();
		CHMatchResult* pBlack = (CHMatchResult*)pMatch->getBlack();
	
		if (pWhite && pBlack &&	!pWhite->getRegister() && !pBlack->getRegister())
		{
			CHMatchResult::side side1 = CHMatchResult::eNone;
			if (pCompetitorDraw)
				side1 = pCompetitorDraw->getSidePreference(round);
			
			CHMatchResult::side side2 = CHMatchResult::eNone;
			if (pCompetitorDrawOpp)
				side2 = pCompetitorDrawOpp->getSidePreference(round);
			
			if (side1==CHMatchResult::eWhite && 
				side2==CHMatchResult::eBlack)
			{
				assignMatchResult(pWhite,pCompetitorDraw);
				assignMatchResult(pBlack,pCompetitorDrawOpp);
				pPairDraw->setMatch(pMatch);
				pPairDraw->setWhite(pCompetitorDraw);
				pPairDraw->setBlack(pCompetitorDrawOpp);
				removeRoundMatch(*pMatch);
				return pMatch;
			}
			else if (side1==CHMatchResult::eBlack && 
					 side2==CHMatchResult::eWhite)
			{
				assignMatchResult(pWhite,pCompetitorDrawOpp);
				assignMatchResult(pBlack,pCompetitorDraw);
				pPairDraw->setMatch(pMatch);
				pPairDraw->setWhite(pCompetitorDrawOpp);
				pPairDraw->setBlack(pCompetitorDraw);
				removeRoundMatch(*pMatch);
				return pMatch;
			}
			else if (side1==CHMatchResult::eWhite && 
					 side2==CHMatchResult::eNone)
			{
				assignMatchResult(pWhite,pCompetitorDraw);
				assignMatchResult(pBlack,pCompetitorDrawOpp);
				pPairDraw->setMatch(pMatch);
				pPairDraw->setWhite(pCompetitorDraw);
				pPairDraw->setBlack(pCompetitorDrawOpp);
				removeRoundMatch(*pMatch);
				return pMatch;
			}
			else if (side1==CHMatchResult::eNone && 
					 side2==CHMatchResult::eWhite)
			{
				assignMatchResult(pWhite,pCompetitorDrawOpp);
				assignMatchResult(pBlack,pCompetitorDraw);
				pPairDraw->setMatch(pMatch);
				pPairDraw->setWhite(pCompetitorDrawOpp);
				pPairDraw->setBlack(pCompetitorDraw);
				removeRoundMatch(*pMatch);
				return pMatch;
			}
			else if (side1==CHMatchResult::eBlack && 
					 side2==CHMatchResult::eNone)
			{
				assignMatchResult(pBlack,pCompetitorDraw);
				assignMatchResult(pWhite,pCompetitorDrawOpp);
				pPairDraw->setMatch(pMatch);
				pPairDraw->setWhite(pCompetitorDrawOpp);
				pPairDraw->setBlack(pCompetitorDraw);
				removeRoundMatch(*pMatch);
				return pMatch;
			}
			else if (side1==CHMatchResult::eNone && 
					 side2==CHMatchResult::eBlack)
			{
				assignMatchResult(pWhite,pCompetitorDraw);
				assignMatchResult(pBlack,pCompetitorDrawOpp);
				pPairDraw->setMatch(pMatch);
				pPairDraw->setWhite(pCompetitorDraw);
				pPairDraw->setBlack(pCompetitorDrawOpp);
				removeRoundMatch(*pMatch);
				return pMatch;
			}
			else if ( (side1==CHMatchResult::eNone && 
					   side2==CHMatchResult::eNone) ||
					  (side1==CHMatchResult::eBlack && 
					   side2==CHMatchResult::eBlack) ||
					  (side1==CHMatchResult::eWhite && 
					   side2==CHMatchResult::eWhite) )
			{
				int color1 = randNum(2);
				
				if (color1==CHMatchResult::eWhite)
				{
					assignMatchResult(pWhite,pCompetitorDraw);
					assignMatchResult(pBlack,pCompetitorDrawOpp);
					pPairDraw->setMatch(pMatch);
					pPairDraw->setWhite(pCompetitorDraw);
					pPairDraw->setBlack(pCompetitorDrawOpp);
					removeRoundMatch(*pMatch);
					return pMatch;
				}
				else
				{
					assignMatchResult(pWhite,pCompetitorDrawOpp);
					assignMatchResult(pBlack,pCompetitorDraw);
					pPairDraw->setMatch(pMatch);
					pPairDraw->setWhite(pCompetitorDrawOpp);
					pPairDraw->setBlack(pCompetitorDraw);
					removeRoundMatch(*pMatch);
					return pMatch;
				}
			}
			else
			{
				CHMatchResult::colorPreference color1 = pCompetitorDraw->getColorPreference(round);
				CHMatchResult::colorPreference color2 = pCompetitorDrawOpp->getColorPreference(round);

				if (color1==CHMatchResult::eWhiteAbsolut &&
				    color2!=CHMatchResult::eWhiteAbsolut)
				{
					assignMatchResult(pBlack,pCompetitorDraw);
					assignMatchResult(pWhite,pCompetitorDrawOpp);
					pPairDraw->setMatch(pMatch);
					pPairDraw->setWhite(pCompetitorDrawOpp);
					pPairDraw->setBlack(pCompetitorDraw);
					removeRoundMatch(*pMatch);
					return pMatch;
				}

				if (color1==CHMatchResult::eBlackAbsolut &&
					color2!=CHMatchResult::eBlackAbsolut)
				{
					assignMatchResult(pWhite,pCompetitorDraw);
					assignMatchResult(pBlack,pCompetitorDrawOpp);
					pPairDraw->setMatch(pMatch);
					pPairDraw->setWhite(pCompetitorDraw);
					pPairDraw->setBlack(pCompetitorDrawOpp);
					removeRoundMatch(*pMatch);
					return pMatch;
				}
			}			
		}
	}
	return 0;
}

void CHRoundDraw::unassignMatchResult(CHMatchResult* pMatchResult)
{
	pMatchResult->setPoolPosition(0);
	pMatchResult->setBye(false);
	pMatchResult->setInscription(0);
	pMatchResult->setDownFloater(false);
	pMatchResult->setUpFloater(false);		

	if (colMatchResults)
		colMatchResults->insert(pMatchResult);
}

void CHRoundDraw::assignMatchResult(CHMatchResult* pMatchResult,CHCompetitorDraw* pCompetitorDraw)
{
	if (pCompetitorDraw)
	{
		pMatchResult->setPoolPosition(pCompetitorDraw->getPoolResultCode());
		pMatchResult->setBye(pCompetitorDraw->getPoolResultBye());
		pMatchResult->setInscription(pCompetitorDraw->getPoolResultInscription());
		pMatchResult->setDownFloater(pCompetitorDraw->getFloatingDown());
		pMatchResult->setUpFloater(pCompetitorDraw->getFloatingUp());		
	}
	else
	{
		pMatchResult->setBye(true);	
	}

	if (colMatchResults)
		colMatchResults->insert(pMatchResult);
}

int CHRoundDraw::randNum(int n)
{
	int t, u; 
	static int nLast=0, tLast=0; 
	if (n <= 1) 
	{
		return 0; 
	}
	n &= RAND_MAX; 
	if (n == nLast) 
	{
		t = tLast; 
	}
	else 
	{ 
		nLast = n; 
		for (t=2; t<n; t<<=1) 
		; 
		t--; 
		tLast = t; 
	} 
	do 
	{ 
		u = t & rand(); 
	}
	while (u >= n); 
	{	
		return u; 
	}
}
