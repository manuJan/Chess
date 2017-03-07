/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHNARegisterFormView.h
*   Description :                                                                      
*                                                                                      
*   Author      :Chess Team
*   Date created:07-12-2005
*   Project     :CH Manager
*                                                                                      
*   Modification history                                                               
*   By      :                                                                          
*   Date    :                                                                          
*   Changes :                                                                          
*                                                                                      
**************************************************************************************///
#if !defined(AFX_CHNAREGISTERFORMVIEW_H__94FA3B20_DAA4_4C82_AB10_197AC3A98234__INCLUDED_)
#define AFX_CHNAREGISTERFORMVIEW_H__94FA3B20_DAA4_4C82_AB10_197AC3A98234__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <GUI\GS\GNARegisterFormView.h>

class CHMemoryDataBase;
class CHJudge;
class CHNARegisterFormView : public GNARegisterFormView  
{
public:
	CHNARegisterFormView();
	virtual ~CHNARegisterFormView();

	DECLARE_DYNCREATE(CHNARegisterFormView)

	// V i r t u a l    m e t h o d s   R e p o r t s
	void onReportRequest(CReportItem    *pItem);
	bool onReportGeneration(CReportManager *pReportMngr,CReportConfig *pReportCfg,CReportItem *pItem);

//	void onInsertRegister(GRegister * pRegister); 
//	void onUpdateRegister(GRegister * pUpdRegister); 
//	void onDeleteRegister(GRegister * pDelRegister);

private:
	// V i r t u a l    m e t h o d s 
	GRegister *	getNewRegister();
	RWBoolean canInsertSexInTree(GSex & aSex);
	void init();
	BOOL onPaintGrid  (UINT idGrid,GridItem *gi);
	void onLButtonDown  (UINT idGrid,int x,int y,LPARAM lParam);
	void onSelChangedRegister(GRegister * pRegister) ;
	RWBoolean canRemoveRegister(GRegister * pRegister);
	// T o o l s	m e t h o d s 
	CHMemoryDataBase * mem();
	void generateVFunctions();	
	void fillFunctionsJudge();
	void paintFunctionsJudge(GridItem *gi);
	void assignFunction(GFunction *pFunction,int y);
	void deleteJudge(CHJudge *pJudge);
	void insertJudge(CHJudge *pJudge);
	void changeJudge(CHJudge *pJudge);
	// R e p o r t s	m e t h o d s 
	void		addReports();

public :
	GSortedVector vFunctions;
};

#endif // !defined(AFX_CHNAREGISTERFORMVIEW_H__94FA3B20_DAA4_4C82_AB10_197AC3A98234__INCLUDED_)
