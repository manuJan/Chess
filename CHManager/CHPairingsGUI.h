/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:	CHMatchConfigurationGUI.h
*	Description	:   Dlg configuracion de un partido
*
*	Author		:	Fernando Hicar
*	Date created:   1-Abril-2009
* 	Project		:	Tennis Manager
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/
#pragma once
#include <ovr/gui/guithmanager/GTHMatchGUIEx.h>

class CHPool;
class CHPoolResult;
class CHPairingsToolBar;
class CHEvent;

class CHPairingsGUI : public GTHMatchGUIEx
{
public:
	CHPairingsGUI					(GTHProgression* pProgression, GTHProgressionData* pProgressionData, GTHStatusManager* pStatusManager, long id, CHPool * pPool);
	virtual ~CHPairingsGUI();

	CHMemoryDataBase * getMem		() const;

	/***** Extensions *****/
	virtual MSLGUIEx * onNewGUIEx	(long id);
	
	LRESULT onLButDownToolBar		(WPARAM wParam=0, LPARAM lParam=0);
	void onClick					(long id,LPARAM lParam);

	short getNextRound				();

	bool canInsertMatch				(GTHMatch *pMatch);

	void loadPairings				(CHEvent * pEvent);
	void loadResults				();
	CHMatch* loadPair				(MSLSet toSend, short nLine, MSLString line);
	CHMatch* loadPairTeam			(MSLSet toSend, short nLine, MSLString line);
	CHMatch* loadResult				(MSLSet toSend, short nLine, MSLString line);

	CHPoolResult * findPoolResultSeed(MSLString seed);
	CHPoolResult * findBye			();

private:
		
	CHPairingsToolBar* m_pPairingsToolBar;

	CHPool * m_pPool;
	
	short m_selRound;
};
