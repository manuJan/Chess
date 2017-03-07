/************************************************************************************* 
*           © Copyright MSL Software, S.L., 1998                                       
*   This document is the property of MSL Software and its content is confidential.     
*   This work must not be reproduced or disclosed to others or used for purposes       
*   other than that for which it is supplied without MSL's prior written permission.   
*   MSL must not be considered liable for any mistake or omission in the edition of    
*   this document. MSL is a registered trademark.                                      
*                                                                                      
*   File name   : CHInscriptionFormView.h
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
#if !defined(AFX_CHINSCRIPTIONFORMVIEW_H__DD36118D_D396_4699_9F49_8EE103FC7AB5__INCLUDED_)
#define AFX_CHINSCRIPTIONFORMVIEW_H__DD36118D_D396_4699_9F49_8EE103FC7AB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include <GUI/GS/GInscriptionFormView.h>

class CHRegister;
class CHInscription;
class CHMember;

class CHInscriptionFormView : public GInscriptionFormView  
{
	DECLARE_DYNCREATE(CHInscriptionFormView)
	DECLARE_MESSAGE_MAP()

protected:
	CHInscriptionFormView();
	virtual ~CHInscriptionFormView();

	GInscription * getNewInscription();
	GMember *	getNewMember();
	GRegister * getNewRegister();

	RWSet *		getIndvCandidatesMembers(GInscription * pInscription);
	RWBoolean	canCreateDeleteInscription(GEvent &aEvent, GRegister &aRegister);
	PFNTVCOMPARE getOrderInscByTreeByEvent();
public:
	void onReportRequest(CReportItem *pItem);
	bool onReportGeneration(CReportManager *pReportMngr,CReportConfig *pReportCfg,CReportItem *pItem);

private:
	void		init();
	void		areThereTeamCompetition();
	void		enableDisableButtons();
	void		onSelChangedRegister(GRegister * pRegister);
	void		onSelChangedEvent(GEvent * pEvent);
	void		paintListEvent(GridItem *gi);
	void		paintListMember(GridItem *gi);
	void		onDblClick(UINT idGrid,int x,int y,LPARAM lParam);
	RWBoolean	repeatSeed(CHInscription* pInscription, short seed);
	void		sendRegister(CHRegister *pRegister);
	void		sendInscription(CHInscription *pInscription);
	void		sendMember(CHMember *pMember);
	void		editRating(int x,int y,CHInscription *pInscription);
	void		editSeed(int x,int y,CHInscription *pInscription);
	void		editKConst(int x,int y,CHInscription *pInscription);
	void		editRatingMember(int x,int y,CHMember *pMember);
	void		editKConstMember(int x,int y,CHMember *pMember);
	void		setRegistrationProperties(GRegister & aRegister);
	void		getRegistrationProperties(GRegister & aRegister);
	void		cancelRegistrationProperties(GRegister & aRegister);
	void		setSeeedByWorldRt(GEvent *pEvent, bool reset);
	RWBoolean	findTeamEvent(GSex *pSex);
	void		fillReports();
	LRESULT		onNewInscription(WPARAM wParam, LPARAM lParam); // UM_NEW_INSCRIPTION
	short		getKConst(CHInscription *pInsc);
	short		getKConst(CHMember *pMemb);
	short		getTeamRating(CHInscription *pIns);
	RWBoolean	canAssignMembers(GEvent & aEvent);


public:
	void		onClick(UINT idCtrl,LPARAM lParam);
	RWWString	getRegisterName(GInscription * pInsc);
// Data
private:
	RWBoolean teamCompetition;
};

#endif // !defined(AFX_CHINSCRIPTIONFORMVIEW_H__DD36118D_D396_4699_9F49_8EE103FC7AB5__INCLUDED_)
