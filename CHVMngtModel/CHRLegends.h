/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHRLegends.h
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:19-12-2005
*   Project     :CHV Model               
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///

#if !defined(AFX_CHRLEGENDS_H__1DBB30D6_9EB1_4007_9523_5B81A51E138E__INCLUDED_)
#define AFX_CHRLEGENDS_H__1DBB30D6_9EB1_4007_9523_5B81A51E138E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _CHVMNGTMODELDLL_H
	#include "CHVMngtModelDll.h"
#endif // _CHVMNGTNODELDLL_H

#include <REPORTS/V/ReportManager.h>
#include <REPORTS/V/RLegend.h>
#include <Sports/CH/DATA/CHEvent.h>
#include <Sports/CH/DATA/CHMatch.h>


class CHRLegends : public RLegend  
{
public:
	enum OrisCode {eC30,eC38, eC32A,eC51,eC58,eC73,eC74,eC75,e76A,e76B,e80, eC95, eC96};


	CHRLegends(CReportTemplate* pRepTem, CReport* pRep, OrisCode id);
	virtual ~CHRLegends();

	CLis* getLegDes();
	void setEvent(CHEvent* _pEvent);
	void setMatch(CHMatch* _pMatch);
	void setDynamic(const wchar_t *key);
	void createDynamic();
	


protected:
	RWBoolean	OnLoadLis();
	void		OnSettings(int id);
private:
	bool loadData();
	bool loadLegendDescription(CReport *pRep);
	RWCString giveMeData(int data);

	// GENERAL LEGEND PRINT FUNCTION
	void printLegend();

	// PARTICULAR LEGEND PRINT FUNCTIONS
	void printMedalStandings();

	
	void printLegendForC30();
	void printLegendForC32A();
	void printLegendResults();
	void printC51Legend();
	void printC58Legend();
	void printC74Legend();
	void printC75Legend();
	void printC76ALegend();
	void printC76BLegend();
	void printC95Legend();
	void printC96Legend();
	

private:
	CLis *pLegendLis;
	CHEvent *pEvent;
	CHMatch *pMatch;
	
	int indice1;
	int indice2;
	OrisCode orisCod;
	int idDynamic;
};

#endif // !defined(AFX_CHRLEGENDS_H__1DBB30D6_9EB1_4007_9523_5B81A51E138E__INCLUDED_)
