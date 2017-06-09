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

#pragma once
#include "CHVMngtModelDefs.h"

class CHPermutationNumber;
class CHCompetitorDraw;
class CHPoolResult;
class CHPool;

class CHGroupDraw : public GData  
{
public:
	CHGroupDraw(CHPool* _pPool, short _group, short round);
	virtual ~CHGroupDraw();

	void setKey();
	
	//Overloaded operators
	GData& operator= (const GData& copy);
	bool   operator==(const GData& copy);
	bool   operator!=(const GData& copy);
		
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
	MSLSortedVector&	getCompetitorsDrawVector();
	MSLItem*			setCompetitorsDraw(CHCompetitorDraw* pCompetitorDraw);
	void				removeCompetitorsDraw(CHCompetitorDraw& aCompetitorDraw);
	CHCompetitorDraw*	getCompetitorsDraw(int index);
	void				sortCompetitorsDraw(mslToolsFcCompare compare);

	// Vector Functions
	MSLSortedVector&	getCompetitorsDrawPairedVector();
	MSLItem*			setCompetitorsDrawPaired(CHCompetitorDraw* pCompetitorDraw);
	void				removeCompetitorsDrawPaired(CHCompetitorDraw& aGroupDraw);
	CHCompetitorDraw*	getCompetitorsDrawPaired(int index);

	// S1 & S2
	MSLSortedVector&	getCompetitorsS1Vector();
	CHCompetitorDraw*	getCompetitorsS1(int index);
				
	MSLSortedVector&	getCompetitorsS2Vector();
	CHCompetitorDraw*	getCompetitorsS2(int index);
	
	CHCompetitorDraw*	InsertCompetitor(CHPoolResult* pPoolResult, short order);
	CHCompetitorDraw*	findOpponent(CHCompetitorDraw* pCompetitorDraw);

	void				calculateVariables();
	void				calculateSubgroups();
	
	void				createTranspositionsInS2();
	bool				trasposeS2(short nTransposition);
	void				removeTranspositionsInS2();
	void				char_permutation(char str[],char append[]);
	void				char_changes(char str[],char append[]);

	void				createChangesInS1S2();
	bool				changeInS1S2(short nChange);
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

	MSLSortedVector vCompetitorsDraw;	
	MSLSortedVector vCompetitorsDrawPaired;
	
	MSLSortedVector vS1;
	MSLSortedVector vS2;

	MSLSortedVector vS2Permutations;
	MSLSortedVector vS1S2Changes;

	short transposition;
	short changeS1S2;
};

