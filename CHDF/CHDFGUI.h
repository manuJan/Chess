/*************************************************************************************
*			© Copyright MSL Software, S.L., 1998
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	: CHDFGUI.h
*	Description	:
*
*	Author		: Chess Team
*	Date created: 17-may-2006
* 	Project		: Chess DataFeed
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#if !defined(AFX_CHDFGUI_H__B530C991_AD40_457D_814C_D1F037A63708__INCLUDED_)
#define AFX_CHDFGUI_H__B530C991_AD40_457D_814C_D1F037A63708__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <GUI/DF/DFGUI.h>

class CHDFGUI : public DFGUI
{

public:
	CHDFGUI();

	void	callForCreateTopics();
	void	callForCreateNotifies();
	void	callForCreateItemsDescription(const int idTopic,const RWBoolean isDesc=false);

	DFProcessExt * getNewDFProcessExt();

	
private:
	void fillItemRegister(GBuffer &aBuffer);
	void fillItemEvent(GBuffer &aBuffer);
	void fillItemPhase(GBuffer &aBuffer);
	void fillItemEventResult(GBuffer & aBuffer);
	void fillItemSession(GBuffer &aBuffer);
	void fillItemInscription(GBuffer &aBuffer);
	void fillItemMember(GBuffer &aBuffer);
	void fillItemJudge(GBuffer & aBuffer);
	void fillItemPool(GBuffer &aBuffer);
	void fillItemPoolResult(GBuffer &aBuffer);
	void fillItemMatch(GBuffer &aBuffer);
	void fillItemSplitMatch(GBuffer &aBuffer);
	void fillMatchMember(GBuffer &aBuffer);
	void fillMatchJudge(GBuffer &aBuffer);
	void fillMatchResult(GBuffer &aBuffer);
	void fillSplitMatchResult(GBuffer &aBuffer);
	void fillCourt(GBuffer &aBuffer);
	void fillMasterType(GBuffer &aBuffer);
	void fillRatingDif(GBuffer &aBuffer);
	void fillTeamMatchCnfg(GBuffer &aBuffer);
	void fillMedallist(GBuffer &aBuffer);


protected:
	//{{AFX_MSG(CHDFGUI)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHDFGUI_H__B530C991_AD40_457D_814C_D1F037A63708__INCLUDED_)
