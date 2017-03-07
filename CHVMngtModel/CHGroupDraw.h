/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHGroupDraw.h
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

#if !defined(AFX_HGROUPDRAW_H)
#define AFX_HGROUPDRAW_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CHCompetitorDraw.h"
#include <core\G\GData.h>

class CHPermutationNumber;

class CHGroupDraw : public GData  
{
public:
	CHGroupDraw(CHPool* _pPool, short _group, short round);
	virtual ~CHGroupDraw();

	void setKey();

	RWBoolean uSQL(RWDBConnection& pConnect,RWBoolean remove=false)
	{
		return false;
		UNREFERENCED_PARAMETER(remove);
		UNREFERENCED_PARAMETER(pConnect);
	}	

	//Overloaded operators
	RWBoolean operator !=(const CHGroupDraw& copy);
	RWBoolean operator ==(const CHGroupDraw& copy);
	CHGroupDraw& operator =(const CHGroupDraw& copy);

	void copyGroupDraw(const CHGroupDraw& copy);
	RWBoolean compareGroupDraw(const CHGroupDraw& copy);

	CPack& pack(CPack& aPack);
	CPack& unpack(CPack& aPack);
	
	short getGroup();
	short getRound();
	short getX();
	short getP();
	short getO();

	short getTranspositions();
	short getChanges();
	
	bool  isHomogenic();
	
	void  increaseTransposition();
	void  resetTransposition();

	void  increaseChange();
	void  resetChange();
	
	// Vector Functions
	GSortedVector&		getCompetitorsDrawVector();
	GVectorElement*		setCompetitorsDraw(CHCompetitorDraw* pCompetitorDraw);
	void				removeCompetitorsDraw(CHCompetitorDraw& aCompetitorDraw);
	CHCompetitorDraw*	getCompetitorsDraw(int index);
	void				sortCompetitorsDraw(CompareFunction compare);

	// Vector Functions
	GSortedVector&		getCompetitorsDrawPairedVector();
	GVectorElement*		setCompetitorsDrawPaired(CHCompetitorDraw* pCompetitorDraw);
	void				removeCompetitorsDrawPaired(CHCompetitorDraw& aGroupDraw);
	CHCompetitorDraw*	getCompetitorsDrawPaired(int index);

	// S1 & S2
	GSortedVector&		getCompetitorsS1Vector();
	CHCompetitorDraw*	getCompetitorsS1(int index);
				
	GSortedVector&		getCompetitorsS2Vector();
	CHCompetitorDraw*	getCompetitorsS2(int index);
	
	CHCompetitorDraw*	InsertCompetitor(CHPoolResult* pPoolResult, short order);
	CHCompetitorDraw*	findOpponent(CHCompetitorDraw* pCompetitorDraw);

	void				calculateVariables();
	void				calculateSubgroups();
	
	void				createTranspositionsInS2();
	RWBoolean			trasposeS2(short nTransposition);
	void				removeTranspositionsInS2();
	void				char_permutation(char str[],char append[]);
	void				char_changes(char str[],char append[]);

	void				createChangesInS1S2();
	RWBoolean			changeInS1S2(short nChange);
	void				removeChangesInS1S2();
	int					getChangesInS1S2();
	int					getTotalChangesInS1S2();
	
	void				changeCompetitorsS2Order(CHPermutationNumber *pPermutationNumber);
	void				changeCompetitorsDrawOrder(CHPermutationNumber *pPermutationNumber);
	int					getTranspositionsInS2();
	int					getTotalTranspositionsInS2();

	bool				hasCompatibleColors(CHCompetitorDraw* pCompetitor1,CHCompetitorDraw* pCompetitor2);

	void				sortCompetitorsDrawByFloatingUp();
	void				sortCompetitorsDrawByRank();
	void				sortCompetitorsDrawByOrder();
private:
	CHPool* pPool;

	short group;
	short round;

	short X; // emparejamientos que no cumpliran las normas
	short P;
	short O;

	GSortedVector vCompetitorsDraw;	
	GSortedVector vCompetitorsDrawPaired;
	
	GSortedVector vS1;
	GSortedVector vS2;

	GSortedVector vS2Permutations;
	GSortedVector vS1S2Changes;

	short transposition;
	short changeS1S2;
};

#endif // !defined(AFX_HGROUPDRAW_H)
